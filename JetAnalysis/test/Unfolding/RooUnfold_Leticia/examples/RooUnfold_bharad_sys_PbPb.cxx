
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using "\n";

#include "TRandom.h"
#include "TH1D.h"

#include "TFile.h"
#include "TVectorD.h"

#include "TROOT.h"
#include <TSystem.h>        // needed for gSystem
#include "TString.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TRandom.h"
#include "TPostScript.h"
#include "TH2D.h"
#include "TFile.h"
#include "TLine.h"
#include "TNtuple.h"
#include "TProfile.h"
#include "TRandom3.h"        // needed for TRandom3

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldInvert.h"
#include "sstream"
#endif

const int bin_det_xj=1;
const int bin_true_xj=2;

const float min_cent_val = 0;
const float max_cent_val = 30;
TString label = "May_5_PbPb_2018_sys_WP_update";
TString in_path = "/home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/JetAnalysis/test/";
TString in_file = in_path+"Uncertainty/Output_May_3_PbPb_2018_sys_WP_update_0_30.root";
TString out_path = "/home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/JetAnalysis/test/Unfolding/OutputDir/";
TFile* fout;

enum TestsTreatment {       // Unfolding tests -> Bottomline, Trivial, Split, CrossFolding
    kNoTest        =0,      // Loop Over All Systematic Uncertainties 
    kTrivial       =1,      // Trivial Test -> Full Nominal MC as Both Data and Response
    kSplitNominal  =2,      // Split Nominal Test -> Split Nominal MC into independent samples
    kBottomline    =3,      // TODO: Bottomline Test -> Data with Nominal MC, //? Check adding covariance matrix
    kCrossfold     =4,      // CrossFolding Test -> Nominal with Alt and vice-versa
    kSplitAltMC    =5       // Split Alt Test -> Split Alt MC into independent samples
};
static const TestsTreatment test_list[] =  
{
    kNoTest       ,         
    kTrivial      ,
    kSplitNominal ,
    kBottomline   ,
    kCrossfold    ,
    kSplitAltMC      
};
static const TString test_label[] = 
{
    "Data"          ,
    "Trivial"       ,    
    "Split_nom"     ,   
    "Bottomline"    ,
    "Prior"         ,    
    "Split_Alt"         

};

enum SystematicsTreatment_PbPb {       // Systematics treatment
    kData       =0,               //* Nominal PbPb 2018 Data 
    kNominal    =1,               //* Nominal Pythia8 (centrality +4.5%)  
    kPhoPurity  =2,               //* ABCD Photon Purity Data 
    kJERup      =3,               //* Pythia8 with JER up 
    kJERdown    =4,               //* Pythia8 with JER down 
    kJECup      =5,               //* Pythia8 with JEC up 
    kJECdown    =6,               //* Pythia8 with JEC down 
    kCentup     =7,               //* Pythia8 with Centrality +6% 
    kCentdown   =8,               //* Pythia8 with Centrality +3% 
    kPFScaleup  =9,               //* Pythia8 with +1% PF scale substructure 
    kPFScaledown=10,              //* Pythia8 with -1% PF scale substructure 
    kAltMC      =11,              //* Pythia8 with quark/gluon fraction reweighted 
    kResponse   =12               //* Propagating Pythia8 Response stats while unfolding
}sys_index;
static const SystematicsTreatment_PbPb sys_list[] =  
{
    kData       ,
    kNominal    ,
    kPhoPurity  ,
    kJERup      ,
    kJERdown    ,
    kJECup      ,
    kJECdown    ,
    kCentup     ,
    kCentdown   ,
    kPFScaleup  ,
    kPFScaledown,
    kAltMC      ,
    kResponse 
};
static const TString sys_label[] = 
{
    "Data"          ,
    "Pythia8_nom"   ,
    "ABCD_purity"   ,
    "JER_up"        ,
    "JER_down"      ,
    "JEC_up"        ,
    "JEC_down"      ,
    "Cent_up"       ,
    "Cent_down"     ,
    "PFScale_up"    ,
    "PFScale_down"  ,
    "AltMC"         ,
    "response"
};
void Fill_hist_sys(TTree*, TTree*,TestsTreatment );

void Unfold_hist(std::vector<TH2D*> vecHist2D,RooUnfoldResponse *response, TestsTreatment test_index,TString unfold_label="xJ");

void SetHistErrZero(TH2D* hist2D){

    for(Int_t j=0;j<=hist2D->GetNbinsX();j++){
        for(Int_t k=0;k<=hist2D->GetNbinsY();k++){
            hist2D->SetBinError(j,k,0.0);
        }
    }
}

void RooUnfold_bharad_sys_PbPb(TestsTreatment input_test_index = kNoTest){

    // gSystem->Load("libRooUnfold.so");
    

    gROOT->SetBatch();
    gErrorIgnoreLevel = kFatal;
    TFile *input_file = TFile::Open(in_file);

    if(input_file==NULL){ std::cout<<"File doesn't Exist\n Check Path and File\n"; return;}

    sys_index = kData;
    TTree* in_data_tree  = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    sys_index = kNominal;
    TTree* in_mc_tree    = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    sys_index = kAltMC;
    TTree* in_AltMC_tree = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));

    sys_index = kPhoPurity;
    TTree* in_PhoPurity_tree        = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    sys_index = kJERup;
    TTree* in_JERup_tree            = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    sys_index = kJERdown;
    TTree* in_JERdown_tree          = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    sys_index = kJECup;
    TTree* in_JECup_tree            = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    sys_index = kJECdown;
    TTree* in_JECdown_tree          = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    sys_index = kCentup;
    TTree* in_Centup_tree           = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    sys_index = kCentdown;
    TTree* in_Centdown_tree         = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    sys_index = kPFScaleup;
    TTree* in_PFScaleup_tree        = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    sys_index = kPFScaledown;
    TTree* in_PFScaledown_tree      = (TTree*)input_file->Get(Form("sys_tree_%s",sys_label[sys_index].Data()));
    
    

    TString cent_string = Form("%.0f_%.0f_",min_cent_val,max_cent_val);

    // std::cout<<"Number of Entries = "<< in_data_tree->GetEntries()<<"\n";
    if(in_mc_tree==NULL){ std::cout<<"Nominal MC doesn't Exist\n"; return;}

    if(input_test_index==kTrivial){
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_mc_tree->CloneTree(),(TTree*)in_mc_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+".root" <<"  created \n";
    }
    
    if(in_data_tree==NULL){ std::cout<<"Data doesn't Exist\n"; return;}
    if(input_test_index==kBottomline){
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_mc_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+".root" <<"  created \n";
    }

    if(input_test_index==kSplitNominal){
        for(int i=1;i<=4;i++){
            fout = new TFile(Form("%sUnfold_%s%s_%s_%d.root",out_path.Data(),cent_string.Data(),label.Data(),test_label[input_test_index].Data(),i),"RECREATE");
            Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_mc_tree->CloneTree(),input_test_index);
            fout->Close();
            std::cout<<"\nOutput File : "<<Form("%sUnfold_%s%s_%s_%d.root",out_path.Data(),cent_string.Data(),label.Data(),test_label[input_test_index].Data(),i) <<"  created \n";    
        }
    }
    if(in_AltMC_tree==NULL){ std::cout<<"Alternate MC doesn't Exist\n"; return;}

    if(input_test_index==kSplitAltMC){
        for(int i=1;i<=4;i++){
            fout = new TFile(Form("%sUnfold_%s%s_%s_%d.root",out_path.Data(),cent_string.Data(),label.Data(),test_label[input_test_index].Data(),i),"RECREATE");
            Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_AltMC_tree->CloneTree(),input_test_index);
            fout->Close();
            std::cout<<"\nOutput File : "<<Form("%sUnfold_%s%s_%s_%d.root",out_path.Data(),cent_string.Data(),label.Data(),test_label[input_test_index].Data(),i) <<"  created \n";    
        }
    }      
    if(input_test_index==kCrossfold){
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_Nominal_AltMC.root","RECREATE");
        Fill_hist_sys((TTree*)in_mc_tree->CloneTree(),(TTree*)in_AltMC_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_Nominal_AltMC.root" <<"  created \n";

        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_AltMC_Nominal.root","RECREATE");
        Fill_hist_sys((TTree*)in_AltMC_tree->CloneTree(),(TTree*)in_mc_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_AltMC_Nominal.root" <<"  created \n";
    
    }

    if(input_test_index==kNoTest){
        sys_index=kNominal;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_mc_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kPhoPurity;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_PhoPurity_tree->CloneTree(),(TTree*)in_mc_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kJERup;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_JERup_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kJERdown;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_JERdown_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kJECup;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_JECup_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kJECdown;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_JECdown_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kCentup;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_Centup_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kCentdown;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_Centdown_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kPFScaleup;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_PFScaleup_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kPFScaledown;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_PFScaledown_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kAltMC;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_AltMC_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

        sys_index=kResponse;
        fout = new TFile(out_path+"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root","RECREATE");
        Fill_hist_sys((TTree*)in_data_tree->CloneTree(),(TTree*)in_mc_tree->CloneTree(),input_test_index);
        fout->Close();
        std::cout<<"\nOutput File : "<<"Unfold_"+cent_string+label+"_"+test_label[input_test_index]+"_"+sys_label[sys_index]+".root" <<"  created \n";

    }
    
}

void Fill_hist_sys(TTree* data_tree, TTree* mc_tree,TestsTreatment in_test_index){

    fout->cd();
    gDirectory->mkdir(test_label[in_test_index]);

    //* Tree Variable Declaration
    // Data
        Int_t   data_jet_index   = -9999;
        Float_t data_weight      = -9999;
        Float_t data_flagsig     = -9999;
        Float_t data_pho_purity  = -9999;
        Float_t data_phoEt       = -9999;
        Float_t data_mcEt        = -9999;
        Float_t data_jetpt_det   = -9999;
        Float_t data_jetpt_true  = -9999;
        Float_t data_xJ_det      = -9999;
        Float_t data_xJ_true     = -9999;
        Float_t data_Rg_det      = -9999;
        Float_t data_Rg_true     = -9999;
        Float_t data_girth_det   = -9999;
        Float_t data_girth_true  = -9999;

        Int_t   data_gen_jet_index   = -9999;
        Float_t data_gen_jetpt_true  = -9999;
        Float_t data_gen_xJ_true     = -9999;
        Float_t data_gen_Rg_true     = -9999;
        Float_t data_gen_girth_true  = -9999;

        data_tree->SetBranchAddress("jet_index"         ,&data_jet_index);
        data_tree->SetBranchAddress("weight"            ,&data_weight);
        data_tree->SetBranchAddress("flagsig"           ,&data_flagsig);
        data_tree->SetBranchAddress("pho_purity"        ,&data_pho_purity);
        data_tree->SetBranchAddress("phoEt"             ,&data_phoEt);
        data_tree->SetBranchAddress("mcEt"              ,&data_mcEt);
        data_tree->SetBranchAddress("jetpt_det"         ,&data_jetpt_det);
        data_tree->SetBranchAddress("jetpt_true"        ,&data_jetpt_true);
        data_tree->SetBranchAddress("xJ_det"            ,&data_xJ_det);
        data_tree->SetBranchAddress("xJ_true"           ,&data_xJ_true);
        data_tree->SetBranchAddress("Rg_det"            ,&data_Rg_det);
        data_tree->SetBranchAddress("Rg_true"           ,&data_Rg_true);
        data_tree->SetBranchAddress("girth_det"         ,&data_girth_det);
        data_tree->SetBranchAddress("girth_true"        ,&data_girth_true);

        data_tree->SetBranchAddress("gen_jet_index"     ,&data_gen_jet_index);
        data_tree->SetBranchAddress("gen_jetpt_true"    ,&data_gen_jetpt_true);
        data_tree->SetBranchAddress("gen_xJ_true"       ,&data_gen_xJ_true);
        data_tree->SetBranchAddress("gen_Rg_true"       ,&data_gen_Rg_true);
        data_tree->SetBranchAddress("gen_girth_true"    ,&data_gen_girth_true);
    // MC
        Int_t   mc_jet_index   = -9999;
        Float_t mc_weight      = -9999;
        Float_t mc_flagsig     = -9999;
        Float_t mc_pho_purity  = -9999;
        Float_t mc_phoEt       = -9999;
        Float_t mc_mcEt        = -9999;
        Float_t mc_jetpt_det   = -9999;
        Float_t mc_jetpt_true  = -9999;
        Float_t mc_xJ_det      = -9999;
        Float_t mc_xJ_true     = -9999;
        Float_t mc_Rg_det      = -9999;
        Float_t mc_Rg_true     = -9999;
        Float_t mc_girth_det   = -9999;
        Float_t mc_girth_true  = -9999;

        Int_t   mc_gen_jet_index   = -9999;
        Float_t mc_gen_jetpt_true  = -9999;
        Float_t mc_gen_xJ_true     = -9999;
        Float_t mc_gen_Rg_true     = -9999;
        Float_t mc_gen_girth_true  = -9999;

        mc_tree->SetBranchAddress("jet_index"         ,&mc_jet_index);
        mc_tree->SetBranchAddress("weight"            ,&mc_weight);
        mc_tree->SetBranchAddress("flagsig"           ,&mc_flagsig);
        mc_tree->SetBranchAddress("pho_purity"        ,&mc_pho_purity);
        mc_tree->SetBranchAddress("phoEt"             ,&mc_phoEt);
        mc_tree->SetBranchAddress("mcEt"              ,&mc_mcEt);
        mc_tree->SetBranchAddress("jetpt_det"         ,&mc_jetpt_det);
        mc_tree->SetBranchAddress("jetpt_true"        ,&mc_jetpt_true);
        mc_tree->SetBranchAddress("xJ_det"            ,&mc_xJ_det);
        mc_tree->SetBranchAddress("xJ_true"           ,&mc_xJ_true);
        mc_tree->SetBranchAddress("Rg_det"            ,&mc_Rg_det);
        mc_tree->SetBranchAddress("Rg_true"           ,&mc_Rg_true);
        mc_tree->SetBranchAddress("girth_det"         ,&mc_girth_det);
        mc_tree->SetBranchAddress("girth_true"        ,&mc_girth_true);

        mc_tree->SetBranchAddress("gen_jet_index"     ,&mc_gen_jet_index);
        mc_tree->SetBranchAddress("gen_jetpt_true"    ,&mc_gen_jetpt_true);
        mc_tree->SetBranchAddress("gen_xJ_true"       ,&mc_gen_xJ_true);
        mc_tree->SetBranchAddress("gen_Rg_true"       ,&mc_gen_Rg_true);
        mc_tree->SetBranchAddress("gen_girth_true"    ,&mc_gen_girth_true);
    

    // -------- End Tree Variable Declaration
    // ----------------------------------------------------------------------------------------------------------------
    //* Histograms

        TH1::SetDefaultSumw2();
        TH2::SetDefaultSumw2();
        // inputs for Unfolding 
            const int bin_det_Rg =     5;
            const int bin_true_Rg =    6;
            const int bin_det_girth =  5;
            const int bin_true_girth = 6;

            Double_t xjmin_det =0.4;//0.4;
            Double_t xjmin_true=0.0;

            Double_t xjmax_det =3;//5
            Double_t xjmax_true=3;//5

            Double_t Rgmax_det = 0.2;// 0.22;// 0.2;
            Double_t Rgmax_true= 0.3;// 0.22;// 0.3;
            
            Double_t Rgmin_det =-0.05;
            Double_t Rgmin_true=-0.05;

            Double_t girthmax_det = 0.1;// 0.15;// 0.1;
            Double_t girthmax_true= 0.3;// 0.15;// 0.3;
            
            Double_t girthmin_det =0.;
            Double_t girthmin_true=0.;

            Double_t xJ_det_edges[bin_det_xj+1]   = {           xjmin_det,xjmax_det};
            Double_t xJ_true_edges[bin_true_xj+1] = {xjmin_true,xjmin_det,xjmax_true};

            // Double_t xJ_det_edges[bin_det_xj+1]   = {xjmin_det,xjmax_det};
            // Double_t xJ_true_edges[bin_true_xj+1] = {xjmin_true,xjmax_true};

            Double_t Rg_det_edges[bin_det_Rg+1]   = {-0.05,0.00, 0.04, 0.08, 0.12, Rgmax_det};
            Double_t Rg_true_edges[bin_true_Rg+1] = {-0.05,0.00, 0.04, 0.08, 0.12, Rgmax_det, Rgmax_true};
            // Double_t Rg_det_edges[bin_det_Rg+1]   = {-0.05,0.00, 0.03, 0.06, 0.1, 0.15, Rgmax_det};
            // Double_t Rg_true_edges[bin_true_Rg+1] = {-0.05,0.00, 0.03, 0.06, 0.1, 0.15, Rgmax_det};
            // Double_t Rg_det_edges[bin_det_Rg+1]   = {-0.05,0.00, 0.04, 0.08, 0.12, Rgmax_det};
            // Double_t Rg_true_edges[bin_true_Rg+1] = {-0.05,0.00, 0.04, 0.08, 0.12, Rgmax_det};

            
            Double_t girth_det_edges[bin_det_girth+1] =   {girthmin_det, 0.02, 0.04, 0.06, 0.08, girthmax_det};
            Double_t girth_true_edges[bin_true_girth+1] = {girthmin_det, 0.02, 0.04, 0.06, 0.08, girthmax_det, girthmax_true};
            
            // Double_t girth_det_edges[bin_det_girth+1] =   {girthmin_det, 0.02, 0.04, 0.06, 0.08, girthmax_det};
            // Double_t girth_true_edges[bin_true_girth+1] = {girthmin_det, 0.02, 0.04, 0.06, 0.08, girthmax_det};
             
        // Data
            TH2D* h_Rg_xJ_det;
            TH2D* hbkg_Rg_xJ_det;
            TH1D* h_Rg_xJ_det_X;
            TH1D* h_Rg_xJ_det_Y;

            TH2D* h_girth_xJ_det;
            TH2D* hbkg_girth_xJ_det;
            TH1D* h_girth_xJ_det_X;
            TH1D* h_girth_xJ_det_Y;

        // Pseudodata
            TH2D* h_data_Rg_xJ_eff;
            TH2D* h_data_Rg_xJ_eff_num;
            TH2D* h_data_Rg_xJ_eff_den;
            TH2D* h_data_Rg_xJ_eff_match_num;
            TH2D* h_data_Rg_xJ_eff_match_den;
            TH2D* h_data_girth_xJ_eff;
            TH2D* h_data_girth_xJ_eff_num;
            TH2D* h_data_girth_xJ_eff_den;
            TH2D* h_data_girth_xJ_eff_match_num;
            TH2D* h_data_girth_xJ_eff_match_den;

            TH2D* h_data_Rg_xJ_pur;
            TH2D* h_data_Rg_xJ_pur_num;
            TH2D* h_data_Rg_xJ_pur_den;
            TH2D* h_data_girth_xJ_pur;
            TH2D* h_data_girth_xJ_pur_num;
            TH2D* h_data_girth_xJ_pur_den;

        // MC
            TH2D* h_mc_Rg_xJ_det;
            TH2D* h_mc_girth_xJ_det;

            TH2D* h_Rg_xJ_eff;
            TH2D* h_Rg_xJ_eff_num;
            TH2D* h_Rg_xJ_eff_den;
            TH2D* h_Rg_xJ_eff_match;
            TH2D* h_Rg_xJ_eff_match_num;
            TH2D* h_Rg_xJ_eff_match_den;
            TH2D* h_girth_xJ_eff;
            TH2D* h_girth_xJ_eff_num;
            TH2D* h_girth_xJ_eff_den;
            TH2D* h_girth_xJ_eff_match;
            TH2D* h_girth_xJ_eff_match_num;
            TH2D* h_girth_xJ_eff_match_den;

            TH2D* h_Rg_xJ_pur;
            TH2D* h_Rg_xJ_pur_num;
            TH2D* h_Rg_xJ_pur_den;
            TH2D* h_girth_xJ_pur;
            TH2D* h_girth_xJ_pur_num;
            TH2D* h_girth_xJ_pur_den;

            TEfficiency* eff_Rg_xJ;

    // Constructor
        h_Rg_xJ_det    = new TH2D(test_label[in_test_index]+"_h_Rg_xJ_det",test_label[in_test_index]+"_h_Rg_xJ_det;R_{g};x_{#gamma,jet}"         ,bin_det_Rg,Rg_det_edges,  bin_det_xj,xJ_det_edges);
        h_mc_Rg_xJ_det = new TH2D(test_label[in_test_index]+"_h_mc_Rg_xJ_det",test_label[in_test_index]+"_h_mc_Rg_xJ_det;R_{g};x_{#gamma,jet}"   ,bin_det_Rg,Rg_det_edges,  bin_det_xj,xJ_det_edges);
        hbkg_Rg_xJ_det = new TH2D(test_label[in_test_index]+"_hbkg_Rg_xJ_det",test_label[in_test_index]+"_hbkg_Rg_xJ_det;R_{g};x_{#gamma,jet}"   ,bin_det_Rg,Rg_det_edges,  bin_det_xj,xJ_det_edges);

        h_girth_xJ_det    = new TH2D(test_label[in_test_index]+"_h_girth_xJ_det",test_label[in_test_index]+"_h_girth_xJ_det;#it{g};x_{#gamma,jet}"             ,bin_det_girth,girth_det_edges,   bin_det_xj,xJ_det_edges);
        h_mc_girth_xJ_det = new TH2D(test_label[in_test_index]+"_h_mc_girth_xJ_det",test_label[in_test_index]+"_h_mc_girth_xJ_det;#it{g};x_{#gamma,jet}"       ,bin_det_girth,girth_det_edges,   bin_det_xj,xJ_det_edges);
        hbkg_girth_xJ_det = new TH2D(test_label[in_test_index]+"_hbkg_girth_xJ_det",test_label[in_test_index]+"_hbkg_girth_xJ_det;#it{g};x_{#gamma,jet}"       ,bin_det_girth,girth_det_edges,   bin_det_xj,xJ_det_edges);
        
        h_Rg_xJ_eff_num             = new TH2D(test_label[in_test_index]+"_h_Rg_xJ_eff_num",test_label[in_test_index]+"_h_Rg_xJ_eff_num;R_{g};x_{#gamma,jet}"           ,bin_true_Rg,Rg_true_edges,   bin_true_xj,xJ_true_edges);
        h_data_Rg_xJ_eff_num        = new TH2D(test_label[in_test_index]+"_h_data_Rg_xJ_eff_num",test_label[in_test_index]+"_h_data_Rg_xJ_eff_num;R_{g};x_{#gamma,jet}" ,bin_true_Rg,Rg_true_edges,   bin_true_xj,xJ_true_edges);   
        h_Rg_xJ_eff_den             = new TH2D(test_label[in_test_index]+"_h_Rg_xJ_eff_den",test_label[in_test_index]+"_h_Rg_xJ_eff_den;R_{g};x_{#gamma,jet}"           ,bin_true_Rg,Rg_true_edges,   bin_true_xj,xJ_true_edges);
        h_data_Rg_xJ_eff_den        = new TH2D(test_label[in_test_index]+"_h_data_Rg_xJ_eff_den",test_label[in_test_index]+"_h_data_Rg_xJ_eff_den;R_{g};x_{#gamma,jet}" ,bin_true_Rg,Rg_true_edges,   bin_true_xj,xJ_true_edges);   
        h_Rg_xJ_eff_match_num       = new TH2D(test_label[in_test_index]+"_h_Rg_xJ_eff_match_num",test_label[in_test_index]+"_h_Rg_xJ_eff_match_num;R_{g};x_{#gamma,jet}"           ,bin_true_Rg,Rg_true_edges,   bin_true_xj,xJ_true_edges);
        h_data_Rg_xJ_eff_match_num  = new TH2D(test_label[in_test_index]+"_h_data_Rg_xJ_eff_match_num",test_label[in_test_index]+"_h_data_Rg_xJ_eff_match_num;R_{g};x_{#gamma,jet}" ,bin_true_Rg,Rg_true_edges,   bin_true_xj,xJ_true_edges);   
        h_Rg_xJ_eff_match_den       = new TH2D(test_label[in_test_index]+"_h_Rg_xJ_eff_match_den",test_label[in_test_index]+"_h_Rg_xJ_eff_match_den;R_{g};x_{#gamma,jet}"           ,bin_true_Rg,Rg_true_edges,   bin_true_xj,xJ_true_edges);
        h_data_Rg_xJ_eff_match_den  = new TH2D(test_label[in_test_index]+"_h_data_Rg_xJ_eff_match_den",test_label[in_test_index]+"_h_data_Rg_xJ_eff_match_den;R_{g};x_{#gamma,jet}" ,bin_true_Rg,Rg_true_edges,   bin_true_xj,xJ_true_edges);   
        h_Rg_xJ_pur_num             = new TH2D(test_label[in_test_index]+"_h_Rg_xJ_pur_num",test_label[in_test_index]+"_h_Rg_xJ_pur_num;R_{g};x_{#gamma,jet}"           ,bin_det_Rg,Rg_det_edges,     bin_det_xj,xJ_det_edges);
        h_data_Rg_xJ_pur_num        = new TH2D(test_label[in_test_index]+"_h_data_Rg_xJ_pur_num",test_label[in_test_index]+"_h_data_Rg_xJ_pur_num;R_{g};x_{#gamma,jet}" ,bin_det_Rg,Rg_det_edges,     bin_det_xj,xJ_det_edges);
        h_Rg_xJ_pur_den             = new TH2D(test_label[in_test_index]+"_h_Rg_xJ_pur_den",test_label[in_test_index]+"_h_Rg_xJ_pur_den;R_{g};x_{#gamma,jet}"           ,bin_det_Rg,Rg_det_edges,     bin_det_xj,xJ_det_edges);
        h_data_Rg_xJ_pur_den        = new TH2D(test_label[in_test_index]+"_h_data_Rg_xJ_pur_den",test_label[in_test_index]+"_h_data_Rg_xJ_pur_den;R_{g};x_{#gamma,jet}" ,bin_det_Rg,Rg_det_edges,     bin_det_xj,xJ_det_edges);
        
        h_girth_xJ_eff_num             = new TH2D(test_label[in_test_index]+"_h_girth_xJ_eff_num",test_label[in_test_index]+"_h_girth_xJ_eff_num;#it{g};x_{#gamma,jet}"              ,bin_true_girth,girth_true_edges,     bin_true_xj,xJ_true_edges);
        h_data_girth_xJ_eff_num        = new TH2D(test_label[in_test_index]+"_h_data_girth_xJ_eff_num",test_label[in_test_index]+"_h_data_girth_xJ_eff_num;#it{g};x_{#gamma,jet}"    ,bin_true_girth,girth_true_edges,     bin_true_xj,xJ_true_edges);   
        h_girth_xJ_eff_den             = new TH2D(test_label[in_test_index]+"_h_girth_xJ_eff_den",test_label[in_test_index]+"_h_girth_xJ_eff_den;#it{g};x_{#gamma,jet}"              ,bin_true_girth,girth_true_edges,     bin_true_xj,xJ_true_edges);
        h_data_girth_xJ_eff_den        = new TH2D(test_label[in_test_index]+"_h_data_girth_xJ_eff_den",test_label[in_test_index]+"_h_data_girth_xJ_eff_den;#it{g};x_{#gamma,jet}"    ,bin_true_girth,girth_true_edges,     bin_true_xj,xJ_true_edges);   
        h_girth_xJ_eff_match_num       = new TH2D(test_label[in_test_index]+"_h_girth_xJ_eff_match_num",test_label[in_test_index]+"_h_girth_xJ_eff_match_num;#it{g};x_{#gamma,jet}"              ,bin_true_girth,girth_true_edges,     bin_true_xj,xJ_true_edges);
        h_data_girth_xJ_eff_match_num  = new TH2D(test_label[in_test_index]+"_h_data_girth_xJ_eff_match_num",test_label[in_test_index]+"_h_data_girth_xJ_eff_match_num;#it{g};x_{#gamma,jet}"    ,bin_true_girth,girth_true_edges,     bin_true_xj,xJ_true_edges);   
        h_girth_xJ_eff_match_den       = new TH2D(test_label[in_test_index]+"_h_girth_xJ_eff_match_den",test_label[in_test_index]+"_h_girth_xJ_eff_match_den;#it{g};x_{#gamma,jet}"              ,bin_true_girth,girth_true_edges,     bin_true_xj,xJ_true_edges);
        h_data_girth_xJ_eff_match_den  = new TH2D(test_label[in_test_index]+"_h_data_girth_xJ_eff_match_den",test_label[in_test_index]+"_h_data_girth_xJ_eff_match_den;#it{g};x_{#gamma,jet}"    ,bin_true_girth,girth_true_edges,     bin_true_xj,xJ_true_edges);   
        h_girth_xJ_pur_num             = new TH2D(test_label[in_test_index]+"_h_girth_xJ_pur_num",test_label[in_test_index]+"_h_girth_xJ_pur_num;#it{g};x_{#gamma,jet}"              ,bin_det_girth,girth_det_edges,       bin_det_xj,xJ_det_edges);
        h_data_girth_xJ_pur_num        = new TH2D(test_label[in_test_index]+"_h_data_girth_xJ_pur_num",test_label[in_test_index]+"_h_data_girth_xJ_pur_num;#it{g};x_{#gamma,jet}"    ,bin_det_girth,girth_det_edges,       bin_det_xj,xJ_det_edges);
        h_girth_xJ_pur_den             = new TH2D(test_label[in_test_index]+"_h_girth_xJ_pur_den",test_label[in_test_index]+"_h_girth_xJ_pur_den;#it{g};x_{#gamma,jet}"              ,bin_det_girth,girth_det_edges,       bin_det_xj,xJ_det_edges);
        h_data_girth_xJ_pur_den        = new TH2D(test_label[in_test_index]+"_h_data_girth_xJ_pur_den",test_label[in_test_index]+"_h_data_girth_xJ_pur_den;#it{g};x_{#gamma,jet}"    ,bin_det_girth,girth_det_edges,       bin_det_xj,xJ_det_edges);

        eff_Rg_xJ = new TEfficiency(test_label[in_test_index]+"_eff_Rg_xJ",test_label[in_test_index]+"_eff_Rg_xJ;R_{g};x_{#gamma,jet}"           ,bin_true_Rg,Rg_true_edges,   bin_true_xj,xJ_true_edges);

    // Response 
        RooUnfoldResponse response_Rg(h_Rg_xJ_det,h_Rg_xJ_eff_num);
        RooUnfoldResponse response_girth(h_girth_xJ_det,h_girth_xJ_eff_num);

    // -------- End Histograms
    // ----------------------------------------------------------------------------------------------------------------
    //* Fill Data
    
    for(int iEntry_Data=0; iEntry_Data<data_tree->GetEntries(); iEntry_Data++){ 
        data_tree->GetEntry(iEntry_Data);
        if(!data_flagsig && in_test_index!=kTrivial){   // For Data Photon Purity subtraction
            hbkg_Rg_xJ_det->Fill(data_Rg_det,data_xJ_det,data_weight);         
            hbkg_girth_xJ_det->Fill(data_girth_det,data_xJ_det,data_weight); 
        }
        if(data_flagsig){
            if(data_xJ_det>=xjmin_det && data_xJ_det<xjmax_det
            && data_Rg_det>=Rgmin_det && data_Rg_det<Rgmax_det){
                h_Rg_xJ_det->Fill(data_Rg_det,data_xJ_det,data_weight);       
            }

            if(data_xJ_det>=xjmin_det && data_xJ_det<xjmax_det
            && data_girth_det>=girthmin_det && data_girth_det<girthmax_det){
                h_girth_xJ_det->Fill(data_girth_det,data_xJ_det,data_weight);       
            }
            
            if(!(in_test_index==kTrivial || in_test_index==kCrossfold))  continue; 

            h_data_Rg_xJ_eff_match_den->Fill(data_gen_Rg_true ,data_gen_xJ_true,data_weight);
            if(data_gen_jet_index==data_jet_index && true){
                h_data_Rg_xJ_eff_match_num->Fill(data_gen_Rg_true ,data_gen_xJ_true,data_weight);
            }
            
            if(data_gen_jet_index==data_jet_index && true){
                h_data_Rg_xJ_eff_den->Fill(data_gen_Rg_true,data_gen_xJ_true,data_weight);
                if(data_xJ_det>=xjmin_det && data_xJ_det<xjmax_det
                && data_Rg_det>=Rgmin_det && data_Rg_det<Rgmax_det){
                    h_data_Rg_xJ_eff_num->Fill(data_gen_Rg_true,data_gen_xJ_true,data_weight);
                }
            }

            h_data_Rg_xJ_pur_den->Fill(data_Rg_det,data_xJ_det,data_weight);
            if(data_gen_jet_index==data_jet_index && true &&
            data_gen_xJ_true>=xjmin_true && data_gen_xJ_true<xjmax_true
            && data_gen_Rg_true>=Rgmin_true && data_gen_Rg_true<Rgmax_true){
                h_data_Rg_xJ_pur_num->Fill(data_Rg_det,data_xJ_det,data_weight);
            }

            // ----------------------------------------------------------------------------------

            h_data_girth_xJ_eff_match_den->Fill(data_gen_girth_true ,data_gen_xJ_true,data_weight);
            if(data_gen_jet_index==data_jet_index && true){
                h_data_girth_xJ_eff_match_num->Fill(data_gen_girth_true ,data_gen_xJ_true,data_weight);
            }

            if(data_gen_jet_index==data_jet_index && true){
                h_data_girth_xJ_eff_den->Fill(data_gen_girth_true,data_gen_xJ_true,data_weight);
                if(data_xJ_det>=xjmin_det && data_xJ_det<xjmax_det
                && data_girth_det>=girthmin_det && data_girth_det<girthmax_det){
                    h_data_girth_xJ_eff_num->Fill(data_gen_girth_true,data_gen_xJ_true,data_weight);
                }
            }

            h_data_girth_xJ_pur_den->Fill(data_girth_det,data_xJ_det,data_weight);
            if(data_gen_jet_index==data_jet_index && true &&
            data_gen_xJ_true>=xjmin_true && data_gen_xJ_true<xjmax_true
            && data_gen_girth_true>=girthmin_true && data_gen_girth_true<girthmax_true){
                h_data_girth_xJ_pur_num->Fill(data_girth_det,data_xJ_det,data_weight);
            }

        }
    }

    //* Photon Purity Corrections in Data
    if(!(in_test_index==kTrivial || in_test_index==kCrossfold)){
        // data_tree->GetEntry(0);
        h_Rg_xJ_det->Scale(1.0/data_pho_purity);
        hbkg_Rg_xJ_det->Scale((1.0-data_pho_purity)/data_pho_purity);
        h_Rg_xJ_det->Add(hbkg_Rg_xJ_det,-1.0);

        h_girth_xJ_det->Scale(1.0/data_pho_purity);
        hbkg_girth_xJ_det->Scale((1.0-data_pho_purity)/data_pho_purity);
        h_girth_xJ_det->Add(hbkg_girth_xJ_det,-1.0);
    }
    //* Fill MC 
    for(int iEntry_mc=0; iEntry_mc<mc_tree->GetEntries() && !(in_test_index==kSplitNominal ||in_test_index==kSplitAltMC); iEntry_mc++){ 
        mc_tree->GetEntry(iEntry_mc);
        if(!mc_flagsig) continue;  // This should never happen

        if(mc_gen_jet_index==mc_jet_index && true &&
        mc_gen_xJ_true>=xjmin_true && mc_gen_xJ_true<xjmax_true
        && mc_gen_Rg_true>=Rgmin_true && mc_gen_Rg_true<Rgmax_true){
            if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
            && mc_Rg_det>=Rgmin_det && mc_Rg_det<Rgmax_det){
                response_Rg.Fill(mc_Rg_det,mc_xJ_det,mc_gen_Rg_true,mc_gen_xJ_true,mc_weight);
                h_mc_Rg_xJ_det->Fill(mc_Rg_det,mc_xJ_det,mc_weight);
            }
            // else{
            //     response_Rg.Fake(mc_Rg_det,mc_xJ_det,mc_weight);
            // }
        }  
        // else{
        //     response_Rg.Miss(mc_gen_Rg_true,mc_gen_xJ_true,mc_weight);            
        // }    

        h_Rg_xJ_eff_match_den->Fill(mc_gen_Rg_true ,mc_gen_xJ_true,mc_weight);
        if(mc_gen_jet_index==mc_jet_index && true){
            h_Rg_xJ_eff_match_num->Fill(mc_gen_Rg_true ,mc_gen_xJ_true,mc_weight);
        }     

        Bool_t pass_Rg_xJ = false;
        if(mc_gen_jet_index==mc_jet_index && true){
            h_Rg_xJ_eff_den->Fill(mc_gen_Rg_true,mc_gen_xJ_true,mc_weight);
            if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
            && mc_Rg_det>=Rgmin_det && mc_Rg_det<Rgmax_det){
                h_Rg_xJ_eff_num->Fill(mc_gen_Rg_true,mc_gen_xJ_true,mc_weight);
                pass_Rg_xJ = true;
            }
            eff_Rg_xJ->FillWeighted(pass_Rg_xJ,mc_weight,mc_gen_Rg_true,mc_gen_xJ_true);
        }

        h_Rg_xJ_pur_den->Fill(mc_Rg_det,mc_xJ_det,mc_weight);
        if(mc_gen_jet_index==mc_jet_index && true
        && mc_gen_xJ_true>=xjmin_true && mc_gen_xJ_true<xjmax_true
        && mc_gen_Rg_true>=Rgmin_true && mc_gen_Rg_true<Rgmax_true){
            h_Rg_xJ_pur_num->Fill(mc_Rg_det,mc_xJ_det,mc_weight);
        }

        // ----------------------------------------------------------------------------------

        if(mc_gen_jet_index==mc_jet_index && true &&
        mc_gen_xJ_true>=xjmin_true && mc_gen_xJ_true<xjmax_true
        && mc_gen_girth_true>=girthmin_true && mc_gen_girth_true<girthmax_true){
            if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
            && mc_girth_det>=girthmin_det && mc_girth_det<girthmax_det){
                response_girth.Fill(mc_girth_det,mc_xJ_det,mc_gen_girth_true,mc_gen_xJ_true,mc_weight);
                h_mc_girth_xJ_det->Fill(mc_girth_det,mc_xJ_det,mc_weight);   
            }
            // else{
            //     response_girth.Fake(mc_girth_det,mc_xJ_det,mc_weight);
            // }
        }   
        // else{
        //     response_girth.Miss(mc_gen_girth_true,mc_gen_xJ_true,mc_weight);            
        // }  
        h_girth_xJ_eff_match_den->Fill(mc_gen_girth_true ,mc_gen_xJ_true,mc_weight);
        if(mc_gen_jet_index==mc_jet_index && true){
            h_girth_xJ_eff_match_num->Fill(mc_gen_girth_true ,mc_gen_xJ_true,mc_weight);
        } 
        
        if(mc_gen_jet_index==mc_jet_index && true){
            h_girth_xJ_eff_den->Fill(mc_gen_girth_true,mc_gen_xJ_true,mc_weight);
            if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
            && mc_girth_det>=girthmin_det && mc_girth_det<girthmax_det){
                h_girth_xJ_eff_num->Fill(mc_gen_girth_true,mc_gen_xJ_true,mc_weight);
            }
        }

        h_girth_xJ_pur_den->Fill(mc_girth_det,mc_xJ_det,mc_weight);
        if(mc_gen_jet_index==mc_jet_index && true
        && mc_gen_xJ_true>=xjmin_true && mc_gen_xJ_true<xjmax_true
        && mc_gen_girth_true>=girthmin_true && mc_gen_girth_true<girthmax_true){
            h_girth_xJ_pur_num->Fill(mc_girth_det,mc_xJ_det,mc_weight);
        }
    }

    // Split Test Loop
    float split_frac=0.25; //0.17; 
      
    
    if(in_test_index==kSplitNominal ||in_test_index==kSplitAltMC){
        Double_t data_int,data_err,mc_int,mc_err;
        data_int = h_Rg_xJ_det->IntegralAndError(1,bin_det_Rg,bin_det_xj,bin_det_xj,data_err); // h_girth_xJ_det->IntegralAndError(1,bin_det_girth,bin_det_xj,bin_det_xj,data_err);//

        //* Write to File and Reset Data Histograms 
            fout->cd(test_label[in_test_index]);

            h_Rg_xJ_det->SetName(Form("%s_Data",h_Rg_xJ_det->GetName()));
            h_Rg_xJ_det->Write("",TObject::kWriteDelete);
            TH1D* h_Data_Rg =(TH1D*)h_Rg_xJ_det->ProjectionX(Form("%s_norm_X",h_Rg_xJ_det->GetName()),bin_det_xj,bin_det_xj,"");
            h_Data_Rg->Scale(1.0/h_Data_Rg->Integral(0,-1),"width");
            h_Data_Rg->Write("",TObject::kWriteDelete);
            h_Rg_xJ_det->SetName(test_label[in_test_index]+"_h_Rg_xJ_det");
            h_Rg_xJ_det->Reset("ICESM");
            h_girth_xJ_det->SetName(Form("%s_Data",h_girth_xJ_det->GetName()));
            h_girth_xJ_det->Write(Form("%s_Data",h_girth_xJ_det->GetName()),TObject::kWriteDelete);
            TH1D* h_Data_girth =(TH1D*)h_girth_xJ_det->ProjectionX(Form("%s_norm_X",h_girth_xJ_det->GetName()),bin_det_xj,bin_det_xj,"");
            h_Data_girth->Scale(1.0/h_Data_girth->Integral(0,-1),"width");
            h_Data_girth->Write("",TObject::kWriteDelete);
            h_girth_xJ_det->SetName(test_label[in_test_index]+"_h_girth_xJ_det");
            h_girth_xJ_det->Reset("ICESM");
            fout->cd();
        
        TRandom3* rand = new TRandom3(0);  // 0 for random seed
        for(int iEntry_mc=0; iEntry_mc<mc_tree->GetEntries(); iEntry_mc++){ 
            mc_tree->GetEntry(iEntry_mc);
            if(!mc_flagsig) continue;  // This should never happen

            if(rand->Rndm()<split_frac){

                if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
                && mc_Rg_det>=Rgmin_det && mc_Rg_det<Rgmax_det){
                    h_Rg_xJ_det->Fill(mc_Rg_det,mc_xJ_det,mc_weight);       
                }

                h_data_Rg_xJ_eff_match_den->Fill(mc_gen_Rg_true ,mc_gen_xJ_true,mc_weight);
                if(mc_gen_jet_index==mc_jet_index && true){
                    h_data_Rg_xJ_eff_match_num->Fill(mc_gen_Rg_true ,mc_gen_xJ_true,mc_weight);
                } 
                
                if(mc_gen_jet_index==mc_jet_index && true){
                    h_data_Rg_xJ_eff_den->Fill(mc_gen_Rg_true,mc_gen_xJ_true,mc_weight);
                    if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
                    && mc_Rg_det>=Rgmin_det && mc_Rg_det<Rgmax_det){
                        h_data_Rg_xJ_eff_num->Fill(mc_gen_Rg_true,mc_gen_xJ_true,mc_weight);
                    }
                }

                h_data_Rg_xJ_pur_den->Fill(mc_Rg_det,mc_xJ_det,mc_weight);
                if(mc_gen_jet_index==mc_jet_index && true
                && mc_gen_xJ_true>=xjmin_true && mc_gen_xJ_true<xjmax_true
                && mc_gen_Rg_true>=Rgmin_true && mc_gen_Rg_true<Rgmax_true){
                    h_data_Rg_xJ_pur_num->Fill(mc_Rg_det,mc_xJ_det,mc_weight);
                }

                // ----------------------------------------------------------------------------------

                if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
                && mc_girth_det>=girthmin_det && mc_girth_det<girthmax_det){
                    h_girth_xJ_det->Fill(mc_girth_det,mc_xJ_det,mc_weight);       
                }

                h_data_girth_xJ_eff_match_den->Fill(mc_gen_girth_true ,mc_gen_xJ_true,mc_weight);
                if(mc_gen_jet_index==mc_jet_index && true){
                    h_data_girth_xJ_eff_match_num->Fill(mc_gen_girth_true ,mc_gen_xJ_true,mc_weight);
                } 

                if(mc_gen_jet_index==mc_jet_index && true){
                    h_data_girth_xJ_eff_den->Fill(mc_gen_girth_true,mc_gen_xJ_true,mc_weight);
                    if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
                    && mc_girth_det>=girthmin_det && mc_girth_det<girthmax_det){
                        h_data_girth_xJ_eff_num->Fill(mc_gen_girth_true,mc_gen_xJ_true,mc_weight);
                    }
                }

                h_data_girth_xJ_pur_den->Fill(mc_girth_det,mc_xJ_det,mc_weight);
                if(mc_gen_jet_index==mc_jet_index && true
                && mc_gen_xJ_true>=xjmin_true && mc_gen_xJ_true<xjmax_true
                && mc_gen_girth_true>=girthmin_true && mc_gen_girth_true<girthmax_true){
                    h_data_girth_xJ_pur_num->Fill(mc_girth_det,mc_xJ_det,mc_weight);
                }

            }
            else{

                if(mc_gen_jet_index==mc_jet_index && true
                && mc_gen_xJ_true>=xjmin_true && mc_gen_xJ_true<xjmax_true
                && mc_gen_Rg_true>=Rgmin_true && mc_gen_Rg_true<Rgmax_true){
                    if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
                    && mc_Rg_det>=Rgmin_det && mc_Rg_det<Rgmax_det){
                        response_Rg.Fill(mc_Rg_det,mc_xJ_det,mc_gen_Rg_true,mc_gen_xJ_true,mc_weight);
                        h_mc_Rg_xJ_det->Fill(mc_Rg_det,mc_xJ_det,mc_weight);
                    }
                }  

                h_Rg_xJ_eff_match_den->Fill(mc_gen_Rg_true ,mc_gen_xJ_true,mc_weight);
                if(mc_gen_jet_index==mc_jet_index && true){
                    h_Rg_xJ_eff_match_num->Fill(mc_gen_Rg_true ,mc_gen_xJ_true,mc_weight);
                }         

                if(mc_gen_jet_index==mc_jet_index && true){
                    h_Rg_xJ_eff_den->Fill(mc_gen_Rg_true,mc_gen_xJ_true,mc_weight);
                    if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
                    && mc_Rg_det>=Rgmin_det && mc_Rg_det<Rgmax_det){
                        h_Rg_xJ_eff_num->Fill(mc_gen_Rg_true,mc_gen_xJ_true,mc_weight);
                    }
                }

                h_Rg_xJ_pur_den->Fill(mc_Rg_det,mc_xJ_det,mc_weight);
                if(mc_gen_jet_index==mc_jet_index && true
                && mc_gen_xJ_true>=xjmin_true && mc_gen_xJ_true<xjmax_true
                && mc_gen_Rg_true>=Rgmin_true && mc_gen_Rg_true<Rgmax_true){
                    h_Rg_xJ_pur_num->Fill(mc_Rg_det,mc_xJ_det,mc_weight);
                }

                // ----------------------------------------------------------------------------------

                if(mc_gen_jet_index==mc_jet_index && true
                && mc_gen_xJ_true>=xjmin_true && mc_gen_xJ_true<xjmax_true
                && mc_gen_girth_true>=girthmin_true && mc_gen_girth_true<girthmax_true){
                    if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
                    && mc_girth_det>=girthmin_det && mc_girth_det<girthmax_det){
                        response_girth.Fill(mc_girth_det,mc_xJ_det,mc_gen_girth_true,mc_gen_xJ_true,mc_weight);
                        h_mc_girth_xJ_det->Fill(mc_girth_det,mc_xJ_det,mc_weight);   
                    }
                }   

                h_girth_xJ_eff_match_den->Fill(mc_gen_girth_true ,mc_gen_xJ_true,mc_weight);
                if(mc_gen_jet_index==mc_jet_index && true){
                    h_girth_xJ_eff_match_num->Fill(mc_gen_girth_true ,mc_gen_xJ_true,mc_weight);
                } 

                h_girth_xJ_eff_den->Fill(mc_gen_girth_true,mc_gen_xJ_true,mc_weight);
                if(mc_xJ_det>=xjmin_det && mc_xJ_det<xjmax_det
                && mc_girth_det>=girthmin_det && mc_girth_det<girthmax_det){
                    h_girth_xJ_eff_num->Fill(mc_gen_girth_true,mc_gen_xJ_true,mc_weight);
                }

                h_girth_xJ_pur_den->Fill(mc_girth_det,mc_xJ_det,mc_weight);
                if(mc_gen_jet_index==mc_jet_index && true
                && mc_gen_xJ_true>=xjmin_true && mc_gen_xJ_true<xjmax_true
                && mc_gen_girth_true>=girthmin_true && mc_gen_girth_true<girthmax_true){
                    h_girth_xJ_pur_num->Fill(mc_girth_det,mc_xJ_det,mc_weight);
                }

            }

        }
        mc_int = h_Rg_xJ_det->IntegralAndError(1,bin_det_Rg,bin_det_xj,bin_det_xj,mc_err); // h_girth_xJ_det->IntegralAndError(1,bin_det_girth,bin_det_xj,bin_det_xj,mc_err);//
        std::cout<<"Split Test seed:"<<rand->GetSeed()<<"\t Ratio "<<split_frac<<" -> Relative Errors\n";
        std::cout<<"      Data Relative Error = \t"<<data_err/data_int<<"\n";
        std::cout<<"Pseudodata Relative Error = \t"<<mc_err/mc_int<<"\n";
    }
    
    

    //* Efficiency and Purity using MC
        h_Rg_xJ_pur = (TH2D*)h_Rg_xJ_pur_num->Clone(test_label[in_test_index]+"_h_Rg_xJ_pur");
        h_Rg_xJ_pur->SetTitle(test_label[in_test_index]+"_h_Rg_xJ_pur;R_{g};x_{#gamma,jet}");
        h_Rg_xJ_pur->Divide(h_Rg_xJ_pur,h_Rg_xJ_pur_den,1,1,"B");
        // SetHistErrZero(h_Rg_xJ_pur);

        h_Rg_xJ_det->Multiply(h_Rg_xJ_pur);
        
        h_Rg_xJ_eff_match = (TH2D*)h_Rg_xJ_eff_match_num->Clone(test_label[in_test_index]+"_h_Rg_xJ_eff_match");
        h_Rg_xJ_eff_match->SetTitle(test_label[in_test_index]+"_h_Rg_xJ_eff_match;R_{g};x_{#gamma,jet}");
        h_Rg_xJ_eff_match->Divide(h_Rg_xJ_eff_match_num,h_Rg_xJ_eff_match_den,1,1,"B");

        h_Rg_xJ_eff = (TH2D*)h_Rg_xJ_eff_num->Clone(test_label[in_test_index]+"_h_Rg_xJ_eff");
        h_Rg_xJ_eff->SetTitle(test_label[in_test_index]+"_h_Rg_xJ_eff;R_{g};x_{#gamma,jet}");
        h_Rg_xJ_eff->Divide(h_Rg_xJ_eff,h_Rg_xJ_eff_den,1,1,"B");
        // SetHistErrZero(h_Rg_xJ_eff);

        h_Rg_xJ_eff->Multiply(h_Rg_xJ_eff_match);

        h_girth_xJ_pur = (TH2D*)h_girth_xJ_pur_num->Clone(test_label[in_test_index]+"_h_girth_xJ_pur");
        h_girth_xJ_pur->SetTitle(test_label[in_test_index]+"_h_girth_xJ_pur;#it{g};x_{#gamma,jet}");
        h_girth_xJ_pur->Divide(h_girth_xJ_pur,h_girth_xJ_pur_den,1,1,"B");
        // SetHistErrZero(h_girth_xJ_pur);

        h_girth_xJ_det->Multiply(h_girth_xJ_pur);

        h_girth_xJ_eff_match = (TH2D*)h_girth_xJ_eff_match_num->Clone(test_label[in_test_index]+"_h_girth_xJ_eff_match");
        h_girth_xJ_eff_match->SetTitle(test_label[in_test_index]+"_h_girth_xJ_eff_match;R_{g};x_{#gamma,jet}");
        h_girth_xJ_eff_match->Divide(h_girth_xJ_eff_match_num,h_girth_xJ_eff_match_den,1,1,"B");

        h_girth_xJ_eff = (TH2D*)h_girth_xJ_eff_num->Clone(test_label[in_test_index]+"_h_girth_xJ_eff");
        h_girth_xJ_eff->SetTitle(test_label[in_test_index]+"_h_girth_xJ_eff;#it{g};x_{#gamma,jet}");
        h_girth_xJ_eff->Divide(h_girth_xJ_eff,h_girth_xJ_eff_den,1,1,"B");
        // SetHistErrZero(h_girth_xJ_eff);

        h_girth_xJ_eff->Multiply(h_girth_xJ_eff_match);

    //* Write Output to File
        fout->cd(test_label[in_test_index]);

        h_Rg_xJ_eff_match->Write("",TObject::kWriteDelete);  
        h_girth_xJ_eff_match->Write("",TObject::kWriteDelete);        

        h_Rg_xJ_det_X =(TH1D*)h_Rg_xJ_det->ProjectionX(Form("%s_norm_X",h_Rg_xJ_det->GetName()),bin_det_xj,bin_det_xj,"");
        h_Rg_xJ_det_X->Scale(1.0/h_Rg_xJ_det_X->Integral(0,-1),"width");
        h_Rg_xJ_det_X->Write("",TObject::kWriteDelete);

        h_Rg_xJ_det_Y =(TH1D*)h_Rg_xJ_det->ProjectionY(Form("%s_norm_Y",h_Rg_xJ_det->GetName()),1,bin_det_Rg,"");
        h_Rg_xJ_det_Y->Scale(1.0/h_Rg_xJ_det_Y->Integral(0,-1),"width");
        h_Rg_xJ_det_Y->Write("",TObject::kWriteDelete);

        h_girth_xJ_det_X =(TH1D*)h_girth_xJ_det->ProjectionX(Form("%s_norm_X",h_girth_xJ_det->GetName()),bin_det_xj,bin_det_xj,"");
        h_girth_xJ_det_X->Scale(1.0/h_girth_xJ_det_X->Integral(0,-1),"width");
        h_girth_xJ_det_X->Write("",TObject::kWriteDelete);

        h_girth_xJ_det_Y =(TH1D*)h_girth_xJ_det->ProjectionY(Form("%s_norm_Y",h_girth_xJ_det->GetName()),1,bin_det_girth,"");
        h_girth_xJ_det_Y->Scale(1.0/h_girth_xJ_det_Y->Integral(0,-1),"width");
        h_girth_xJ_det_Y->Write("",TObject::kWriteDelete);

        h_Rg_xJ_pur_num->Write("",TObject::kWriteDelete);
        h_Rg_xJ_pur_den->Write("",TObject::kWriteDelete);
        h_Rg_xJ_eff_num->Write("",TObject::kWriteDelete);
        h_Rg_xJ_eff_den->Write("",TObject::kWriteDelete);
        h_Rg_xJ_eff_match_num->Write("",TObject::kWriteDelete);
        h_Rg_xJ_eff_match_den->Write("",TObject::kWriteDelete);        

        h_girth_xJ_pur_num->Write("",TObject::kWriteDelete);
        h_girth_xJ_pur_den->Write("",TObject::kWriteDelete);
        h_girth_xJ_eff_num->Write("",TObject::kWriteDelete);
        h_girth_xJ_eff_den->Write("",TObject::kWriteDelete);
        h_girth_xJ_eff_match_num->Write("",TObject::kWriteDelete);
        h_girth_xJ_eff_match_den->Write("",TObject::kWriteDelete);

        h_data_Rg_xJ_pur_num->Write("",TObject::kWriteDelete);
        h_data_Rg_xJ_pur_den->Write("",TObject::kWriteDelete);
        h_data_Rg_xJ_eff_num->Write("",TObject::kWriteDelete);
        h_data_Rg_xJ_eff_den->Write("",TObject::kWriteDelete);
        h_data_Rg_xJ_eff_match_num->Write("",TObject::kWriteDelete);
        h_data_Rg_xJ_eff_match_den->Write("",TObject::kWriteDelete);

        h_data_girth_xJ_pur_num->Write("",TObject::kWriteDelete);
        h_data_girth_xJ_pur_den->Write("",TObject::kWriteDelete);
        h_data_girth_xJ_eff_num->Write("",TObject::kWriteDelete);
        h_data_girth_xJ_eff_den->Write("",TObject::kWriteDelete);
        h_data_girth_xJ_eff_match_num->Write("",TObject::kWriteDelete);
        h_data_girth_xJ_eff_match_den->Write("",TObject::kWriteDelete);

        
        fout->cd();
        eff_Rg_xJ->Write("",TObject::kWriteDelete);
        h_Rg_xJ_pur->Write("",TObject::kWriteDelete);
        h_Rg_xJ_eff->Write("",TObject::kWriteDelete);
        h_Rg_xJ_det->Write("",TObject::kWriteDelete);

        h_girth_xJ_pur->Write("",TObject::kWriteDelete);
        h_girth_xJ_eff->Write("",TObject::kWriteDelete);
        h_girth_xJ_det->Write("",TObject::kWriteDelete);

        h_mc_Rg_xJ_det->Write("",TObject::kWriteDelete);

        h_mc_girth_xJ_det->Write("",TObject::kWriteDelete);

    //* Unfold
    if(in_test_index==kBottomline && bin_det_Rg==bin_true_Rg && bin_det_girth==bin_true_girth){ 
        TDecompSVD *svd_Rg= new TDecompSVD (response_Rg.Mresponse()); //this is the singular value decomposition (SVD) matrix
        svd_Rg->Write("SVD_matrix_Rg_xJ",TObject::kWriteDelete);
        auto singular_values_Rg = svd_Rg->GetSig(); //this is a vector with the singular values, i.e., the diagonal elements of S. They are ordered from largest to smallest.
        std::cout<<"Singular Values for Rg \n";
        for(int i_cond=0;i_cond<singular_values_Rg.GetNoElements();i_cond++){
           std::cout<<i_cond<<"\t"<<singular_values_Rg[i_cond]<<"\n";
        }
        std::cout<<"Condition Number for Rg = "<<singular_values_Rg.Max()/singular_values_Rg.Min()<<"\n";
        // svd_Rg->Print();
        TDecompSVD *svd_girth= new TDecompSVD (response_girth.Mresponse()); //this is the singular value decomposition (SVD) matrix
        svd_girth->Write("SVD_matrix_girth_xJ",TObject::kWriteDelete);
        auto singular_values_girth = svd_girth->GetSig(); //this is a vector with the singular values, i.e., the diagonal elements of S. They are ordered from lagirthest to smallest.
        std::cout<<"Singular Values for girth \n";
        for(int i_cond=0;i_cond<singular_values_girth.GetNoElements();i_cond++){
           std::cout<<i_cond<<"\t"<<singular_values_girth[i_cond]<<"\n";
        }
        std::cout<<"Condition Number for #it{g} = "<<singular_values_girth.Max()/singular_values_girth.Min()<<"\n";
        // svd_girth->Print();
    }
    if(in_test_index==kNoTest || in_test_index==kBottomline){
        Unfold_hist({h_Rg_xJ_det,h_Rg_xJ_eff,h_Rg_xJ_eff_match_den},(RooUnfoldResponse*)response_Rg.Clone(),in_test_index,"Rg_xJ");
        Unfold_hist({h_girth_xJ_det,h_girth_xJ_eff,h_girth_xJ_eff_match_den},(RooUnfoldResponse*)response_girth.Clone(),in_test_index,"girth_xJ");
    }
    else{
        Unfold_hist({h_Rg_xJ_det,h_Rg_xJ_eff,h_data_Rg_xJ_eff_match_den},(RooUnfoldResponse*)response_Rg.Clone(),in_test_index,"Rg_xJ");
        Unfold_hist({h_girth_xJ_det,h_girth_xJ_eff,h_data_girth_xJ_eff_match_den},(RooUnfoldResponse*)response_girth.Clone(),in_test_index,"girth_xJ");
    }
}

void Unfold_hist(std::vector<TH2D*> vecHist2D,RooUnfoldResponse *response, TestsTreatment test_index,TString unfold_label="xJ"){
    // h2input contains
    //      0 -> Detector input
    //      1 -> efficiency correction
    //      2 -> True to be compared with unfolded

    if(vecHist2D.size()!=3){ std::cout<<"Provide 3 histograms - input, eff corr, True"; return;}

    RooUnfold::ErrorTreatment errorTreatment = RooUnfold::kCovariance;
    if(sys_index==kResponse)  errorTreatment = RooUnfold::kCovToy;

    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();

    TH2D* h2input = (TH2D*)vecHist2D[0]->Clone();

    //* Matrix Inversion
        RooUnfoldInvert unfoldInverse(response, h2input);
        unfoldInverse.SetVerbose(0);
        if(sys_index==kResponse) unfoldInverse.IncludeSystematics(2);
        unfoldInverse.SetNToys(1000);
        TH2D* hunf_invert= (TH2D*) unfoldInverse.Hreco(errorTreatment);
        hunf_invert->SetName(test_label[test_index]+"_MatInvert_Unfolded_"+unfold_label);
        TH2D* hfold_invert= (TH2D*)response->ApplyToTruth(hunf_invert,"");
        hfold_invert->SetName(test_label[test_index]+"_MatInvert_Folded_"+unfold_label);

    //* Probability and Covariance Matrix
        TMatrixD ProbabilityMatrix = (TMatrixD)response->Mresponse();
        // TCanvas c_temp;
        // ProbabilityMatrix.Draw();
        TH2D Probability_hist2D(ProbabilityMatrix);// = (TH2D*)c_temp.GetPad(0)->GetPrimitive("TMatrixDBase");
        Probability_hist2D.SetName(Form("%s_ProbabilityMatrix_%s",test_label[test_index].Data(),unfold_label.Data()));
        Probability_hist2D.SetTitle(Form("%s_ProbabilityMatrix_%s;True Bin Number;Reco Bin Number",test_label[test_index].Data(),unfold_label.Data()));

        auto mat_covariance = unfoldInverse.Ereco();
        // mat_covariance.Draw();
        TH2D mat_covariance_hist2D(mat_covariance);// = (TH2D*)c_temp.GetPad(0)->GetPrimitive("TMatrixDBase");
        mat_covariance_hist2D.SetName(Form("%s_CovarianceMatrix_%s",test_label[test_index].Data(),unfold_label.Data()));
        mat_covariance_hist2D.SetTitle(Form("%s_CovarianceMatrix_%s;Bin Number;Bin Number",test_label[test_index].Data(),unfold_label.Data()));

    //* Matrix Inversion Histograms

        TH2D* hunf_invert_eff_corr = (TH2D*)hunf_invert->Clone(test_label[test_index]+"_MatInvert_Unfolded_"+unfold_label+"_eff_corr");
        hunf_invert_eff_corr->Divide((TH2D*)vecHist2D[1]->Clone());

        //! Projection Bin choice to be made general
        
        TH1D* hunf_norm_X = (TH1D*)hunf_invert_eff_corr->ProjectionX(test_label[test_index]+"_MatInvert_Unfolded_"+unfold_label+"_norm_X",bin_true_xj,bin_true_xj,"");
        TH1D* hunf_norm_Y = (TH1D*)hunf_invert_eff_corr->ProjectionY(test_label[test_index]+"_MatInvert_Unfolded_"+unfold_label+"_norm_Y");

        hunf_norm_X->Scale(1.0/hunf_norm_X->Integral(0,-1),"width");
        hunf_norm_Y->Scale(1.0/hunf_norm_Y->Integral(0,-1),"width");

        TH2D* h2true = (TH2D*)vecHist2D[2]->Clone();
        TH1D* htrue_norm_X = (TH1D*)h2true->ProjectionX(test_label[test_index]+"_True_"+unfold_label+"_norm_X",bin_true_xj,bin_true_xj,"");
        TH1D* htrue_norm_Y = (TH1D*)h2true->ProjectionY(test_label[test_index]+"_True_"+unfold_label+"_norm_Y");

        htrue_norm_X->Scale(1.0/htrue_norm_X->Integral(0,-1),"width");
        htrue_norm_Y->Scale(1.0/htrue_norm_Y->Integral(0,-1),"width");

        TH1D* hunf_true_X = (TH1D*)hunf_norm_X->Clone(test_label[test_index]+"_hunf_true_"+unfold_label+"_X");
        hunf_true_X->Divide(htrue_norm_X);
        hunf_true_X->SetTitle(Form("%s;%s;#frac{Unfolded}{True}",hunf_true_X->GetName(),hunf_true_X->GetXaxis()->GetTitle()));

        TH1D* hunf_true_Y = (TH1D*)hunf_norm_Y->Clone(test_label[test_index]+"_hunf_true_"+unfold_label+"_Y");
        hunf_true_Y->Divide(htrue_norm_Y);
        hunf_true_Y->SetTitle(Form("%s;%s;#frac{Unfolded}{True}",hunf_true_Y->GetName(),hunf_true_Y->GetXaxis()->GetTitle()));

        fout->cd();
        response->Write("",TObject::kWriteDelete);
        hfold_invert->Write("",TObject::kWriteDelete);
        hunf_invert_eff_corr->Write("",TObject::kWriteDelete);
        hunf_norm_X->Write("",TObject::kWriteDelete);
        htrue_norm_X->Write("",TObject::kWriteDelete);
        hunf_true_X->Write("",TObject::kWriteDelete);
        Probability_hist2D.Write("",TObject::kWriteDelete);
        mat_covariance_hist2D.Write("",TObject::kWriteDelete);

        fout->cd(test_label[test_index]);
        hunf_invert->Write("",TObject::kWriteDelete);
        htrue_norm_Y->Write("",TObject::kWriteDelete);
        hunf_norm_Y->Write("",TObject::kWriteDelete);
        hunf_true_Y->Write("",TObject::kWriteDelete);
        fout->cd();
    
    // TODO: Include D'Agostini

    fout->cd(test_label[test_index]);
    gDirectory->mkdir("DAgostini");
    
    for(Int_t iter=1;iter<101;iter++){
        // RooUnfold::ErrorTreatment errorTreatment_iter = RooUnfold::kCovariance;  

        RooUnfoldBayes   unfold(response, h2input, iter);    // OR
        unfold.SetVerbose(0);
        if(sys_index==kResponse) unfold.IncludeSystematics(2);
        unfold.SetNToys(1000);
        //! USING CovToys for Bayesian Response Stats as well
        TH2D* hunf= (TH2D*) unfold.Hreco(errorTreatment); // TH2D* hunf= (TH2D*) unfold.Hreco(errorTreatment);
        //FOLD BACK
        TH2D* hfold= (TH2D*)response->ApplyToTruth(hunf,"");

        auto covariance = unfold.Ereco();
        // covariance.Write(Form("covariance%d",iter),TObject::kWriteDelete);
        if(iter<100 || iter==1000){
            // covariance.Draw();
            TH2D covariance_hist2D(covariance);// = (TH2D*)c_temp.GetPad(0)->GetPrimitive("TMatrixDBase");
            covariance_hist2D.SetName(Form("%s_CovarianceMatrix_%s_%d",test_label[test_index].Data(),unfold_label.Data(),iter));
            covariance_hist2D.SetTitle(Form("%s_CovarianceMatrix_%s_%d;Bin Number;Bin Number",test_label[test_index].Data(),unfold_label.Data(),iter));
            fout->cd();
            fout->cd(test_label[test_index]+"/DAgostini");
            covariance_hist2D.Write("",TObject::kWriteDelete);
            fout->cd();
        }

        TH2D *htempUnf=(TH2D*)hunf->Clone("htempUnf");          
        htempUnf->SetName(Form("%s_Bayesian_Unfoldediter_%s_%d",test_label[test_index].Data(),unfold_label.Data(),iter));

        TH2D *htempFold=(TH2D*)hfold->Clone("htempFold");          
        htempFold->SetName(Form("%s_Bayesian_Refoldediter_%s_%d",test_label[test_index].Data(),unfold_label.Data(),iter));   
        
        TH2D* hunf_eff_corr = (TH2D*)hunf->Clone(Form("%s_Bayesian_Unfoldediter_%s_eff_corr_%d",test_label[test_index].Data(),unfold_label.Data(),iter));
        hunf_eff_corr->Divide((TH2D*)vecHist2D[1]->Clone());   

        if(iter<60 || iter==100){
            fout->cd();
            fout->cd(test_label[test_index]+"/DAgostini");
            htempUnf->Write("",TObject::kWriteDelete);
            htempFold->Write("",TObject::kWriteDelete);
            hunf_eff_corr->Write("",TObject::kWriteDelete);
            fout->cd();
        }
    }
    fout->cd();

}
