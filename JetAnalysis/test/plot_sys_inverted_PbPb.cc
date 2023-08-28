#include <TSystem.h>        // needed for gSystem
#include <TStyle.h>         // needed for gStyle 
#include <TChain.h>         // needed for TChain
#include "TROOT.h"          // needed for gROOT
#include <TError.h>         // needed for gErrorIgnoreLevel
#include <TVector2.h>       // needed for TVector2::Phi_mpi_pi        
#include <TH2.h>            // needed fror TH1 and TH2
#include <TLegend.h>        // needed for Legend
#include <TCanvas.h>        // needed for Canvas
#include <TMath.h>          //! needed for floating values in plots for some reason
#include <THStack.h>        // needed for THStack
#include <TLatex.h>         // needed for TLatex
#include <TFile.h>          // needed for TFile

#include <iostream>         // needed for I/O

const int bin_det_xj=1;
const int bin_true_xj=2;//2;
const float xjmin_det = 0.4;
const float min_pho_et = 100.0;
bool flag_invert = false;

const float min_cent_val = 0;
const float max_cent_val = 30;
TString label="Jul_31_PbPb_2018_sys_Decorrelate_PF";
TString output_path = "./Unfolded_Plots/";
TString centstring = Form("Cent. %.0f-%.0f%%",min_cent_val,max_cent_val);
TString dir_cent_string = Form("%.0f_%.0f_",min_cent_val,max_cent_val);
TString var_arr[]={"Rg","girth"};
TString var_nam[]={"R_{g}","#it{g}"};
const int nvar = 2;


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
    kData          =0,               //* Nominal PbPb 2018 Data 
    kNominal       =1,               //* Nominal Pythia8 (centrality +4.5%)  
    kPhoPurity     =2,               //* ABCD Photon Purity Data 
    kJERup         =3,               //* Pythia8 with JER up 
    kJERdown       =4,               //* Pythia8 with JER down 
    kJECup         =5,               //* Pythia8 with JEC up 
    kJECdown       =6,               //* Pythia8 with JEC down 
    kCentup        =7,               //* Pythia8 with Centrality +6% 
    kCentdown      =8,               //* Pythia8 with Centrality +3% 
    kPScaleup      =9,               //* Pythia8 with +1% Photon scale substructure 
    kPScaledown    =10,              //* Pythia8 with -1% Photon scale substructure 
    kChScaleup     =11,              //* Pythia8 with +1% Charged Hadron scale substructure 
    kChScaledown   =12,              //* Pythia8 with -1% Charged Hadron scale substructure 
    kNScaleup      =13,              //* Pythia8 with +3% Neutral Hadron scale substructure 
    kNScaledown    =14,              //* Pythia8 with -3% Neutral Hadron scale substructure 
    kAltMC         =15,              //* Pythia8 with quark/gluon fraction reweighted 
    kResponse      =16               //* Propagating Pythia8 Response stats while unfolding
}sys_index;
static const SystematicsTreatment_PbPb sys_list[] =  
{
    kData          ,
    kNominal       ,
    kPhoPurity     ,
    kJERup         ,
    kJERdown       ,
    kJECup         ,
    kJECdown       ,
    kCentup        ,
    kCentdown      ,
    kPScaleup      ,
    kPScaledown    ,
    kChScaleup     ,
    kChScaledown   ,
    kNScaleup      ,
    kNScaledown    ,
    kAltMC         ,
    kResponse 
};
static const TString sys_label[] = 
{
    "Data"            ,
    "Pythia8_nom"     ,
    "ABCD_purity"     ,
    "JER_up"          ,
    "JER_down"        ,
    "JEC_up"          ,
    "JEC_down"        ,
    "Cent_up"         ,
    "Cent_down"       ,
    "PScale_up"       ,
    "PScale_down"     ,
    "ChScale_up"      ,
    "ChScale_down"    ,
    "NScale_up"       ,
    "NScale_down"     ,
    "AltMC"           ,
    "response"
};

void Plot_hist_ratio(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void Plot_hist(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void Plot_hist2D(std::vector<TH2D*> hist,std::vector<TString> histname,TString dopt="colz",std::vector<TString> eopt={"end"});

void plot_sys(TString in_file,TString in_test_label);

void plot_sys_inverted_PbPb(TString file_label="",TString in_test_label="Data"){
    if(file_label=="")file_label=label;

    TString file_path = Form("/home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/JetAnalysis/test/Unfolding/OutputDir/Unfold_%.0f_%.0f_%s",min_cent_val,max_cent_val,label.Data());
    plot_sys(file_path,in_test_label);

}

void plot_sys(TString in_file,TString in_test_label){

    TestsTreatment test_index;
    if(in_test_label=="Data"){
        test_index = kNoTest;
    }else if(in_test_label=="Trivial"){
        test_index = kTrivial;
    }else if(in_test_label=="Split_nom"){
        test_index = kSplitNominal;
    }else if(in_test_label=="Bottomline"){
        test_index = kBottomline;
    }else if(in_test_label=="Prior"){
        test_index = kCrossfold;
    }else if(in_test_label=="Split_Alt"){
        test_index = kSplitAltMC;
    }
    else{
        std::cout<<"Provide a Test Index"; return;
    }

    gROOT->SetBatch();
    gErrorIgnoreLevel = kFatal;
    label+="_"+in_test_label;
    TString DIR = output_path + "OutputUnfolded_"+dir_cent_string+label+"/";
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();
    
    int loop_index = 1;
    bool loop_flag = false;
    do
    {
        sys_index = sys_list[loop_index];
        TString file_string = "";
        switch(test_index){
            case kNoTest: file_string="_"+sys_label[sys_index]; break;
            case kSplitNominal:
            case kSplitAltMC:
                            file_string=Form("_%d",loop_index); break;
            case kCrossfold:
                            if(loop_index==1){      file_string="_Nominal_AltMC"; break;}
                            else if(loop_index==2){ file_string="_AltMC_Nominal"; break;}
            default: break;
        }  
        
        TFile *input_file = TFile::Open(in_file+"_"+test_label[test_index]+file_string+".root");
        
        for(int ivar=0;ivar<nvar;ivar++){
            
        Int_t iter_ref = 10;
        const int niter = 50;
        TH1D *hist_chi2_Invert(0),*hist_chi2_Bayesian(0),*hist_chi2_smeared(0),*hist_pval_smeared(0);
        hist_chi2_Invert=new TH1D("hist_chi2_Invert","hist_chi2_Invert",niter,0,niter);
        hist_chi2_Bayesian=new TH1D("hist_chi2_Bayesian","hist_chi2_Bayesian",niter,0,niter);
        hist_chi2_smeared=new TH1D("hist_chi2_smeared","hist_chi2_smeared",niter,0,niter);
        hist_pval_smeared=new TH1D("hist_pval_smeared","hist_pval_smeared",niter,0,niter);

        TH2D *h2_Probability = (TH2D*)input_file->Get(test_label[test_index]+"_ProbabilityMatrix_"+var_arr[ivar]+"_xJ");
        TH2D *h2_Covariance  = (TH2D*)input_file->Get(test_label[test_index]+"_CovarianceMatrix_"+var_arr[ivar]+"_xJ");
        
        TH2D *h2_pur = (TH2D*)input_file->Get(test_label[test_index]+"_h_"+var_arr[ivar]+"_xJ_pur");
        TH2D *h2_eff = (TH2D*)input_file->Get(test_label[test_index]+"_h_"+var_arr[ivar]+"_xJ_eff");
        
        TH2D *h2_Folded_Invert = (TH2D*)input_file->Get(test_label[test_index]+"_MatInvert_Folded_"+var_arr[ivar]+"_xJ");
        TH1D *h_Folded_Invert_X = (TH1D*)h2_Folded_Invert->ProjectionX("h_Folded_Invert_X",bin_det_xj,bin_det_xj,"");
        h_Folded_Invert_X->Scale(1.0/h_Folded_Invert_X->Integral(0,-1),"width");

        TH2D *h2_Raw = (TH2D*)input_file->Get(test_label[test_index]+"_h_"+var_arr[ivar]+"_xJ_det"); 
        TH1D *h_Raw_X  = (TH1D*)h2_Raw->ProjectionX("h_Raw_X",bin_det_xj,bin_det_xj,"");
        h_Raw_X->Scale(1.0/h_Raw_X->Integral(0,-1),"width");

        TH2D *h2_Raw_mc = (TH2D*)input_file->Get(test_label[test_index]+"_h_mc_"+var_arr[ivar]+"_xJ_det"); 
        TH1D *h_Raw_mc_X  = (TH1D*)h2_Raw_mc->ProjectionX("h_Raw_mc_X",bin_det_xj,bin_det_xj,"");
        h_Raw_mc_X->Scale(1.0/h_Raw_mc_X->Integral(0,-1),"width");

        TH1D *h_Folded_Raw_X = (TH1D*)h_Folded_Invert_X->Clone(test_label[test_index]+"_hfold_raw_"+var_arr[ivar]+"_xJ_X");
        h_Folded_Raw_X->Divide(h_Raw_X);

        TH1D *h_Unfolded_Invert_X = (TH1D*)input_file->Get(test_label[test_index]+"_MatInvert_Unfolded_"+var_arr[ivar]+"_xJ_norm_X");
        h_Unfolded_Invert_X->SetName("matinvert_X");
        h_Unfolded_Invert_X->SetTitle(Form("matinvert_X;%s;1/N_{jet} dN/d%s",var_nam[ivar].Data(),var_nam[ivar].Data()));
        TH1D *h_Unfolded_True_X = (TH1D*)input_file->Get(test_label[test_index]+"_hunf_true_"+var_arr[ivar]+"_xJ_X");

        TH1D *h_True_X = (TH1D*)input_file->Get(test_label[test_index]+"_True_"+var_arr[ivar]+"_xJ_norm_X");  

        // For bottom line test 
        if(test_index==kBottomline){
            float sumChi2 = 0;

            TH1D *htemp1_smeared = (TH1D*)h_Raw_X->Clone();
            TH1D *htemp2_smeared = (TH1D*)h_Raw_mc_X->Clone(); // (TH1D*)raw_X_mc->Clone();//

            for (Int_t k = 0; k < (h_Raw_mc_X->GetNbinsX()+1); k++){  
                if (htemp1_smeared->GetBinContent(k) > 0) sumChi2+= (htemp1_smeared->GetBinContent(k)-htemp2_smeared->GetBinContent(k))*(htemp1_smeared->GetBinContent(k)-htemp2_smeared->GetBinContent(k))/(htemp1_smeared->GetBinError(k)*htemp1_smeared->GetBinError(k) ); //+ htemp2_smeared->GetBinError(k)*htemp2_smeared->GetBinError(k)
            }
            sumChi2/=(h_Raw_mc_X->GetNbinsX());
            std::cout<<"Bottomline -> Chi2 Smeared =  "<<sumChi2<<"\n";
            for(Int_t j=1;j<niter;j++) hist_chi2_smeared->SetBinContent(j,sumChi2);

            // ---- Unfolded Chi2 - Invert

            sumChi2 = 0;
            
            TH1D *htemp1 = (TH1D*)h_Unfolded_Invert_X->Clone();
            TH1D *htemp2 = (TH1D*)h_True_X->Clone(); 

            for (Int_t k = 0; k < (h_Raw_mc_X->GetNbinsX()+1); k++){  
                if (htemp1->GetBinContent(k) > 0) sumChi2+= (htemp1->GetBinContent(k)-htemp2->GetBinContent(k))*(htemp1->GetBinContent(k)-htemp2->GetBinContent(k))/(htemp1->GetBinError(k)*htemp1->GetBinError(k)); // + htemp2->GetBinError(k)*htemp2->GetBinError(k)
            }
            sumChi2/=(h_Raw_mc_X->GetNbinsX());
            std::cout<<"Matrix Inversion \t Chi2Unfolded =  "<<sumChi2<<"\n";
            for(Int_t j=1;j<niter;j++) hist_chi2_Invert->SetBinContent(j,sumChi2);
        }

        int flag_pval = 0;
        TH1D *h_Bayesian_Unfolded_X[niter],*h_Bayesian_Refolded_X[niter];
        for(Int_t j=1;j<niter;j++){
            TH2D *h2_Bayesian_Unfolded_corr = (TH2D*)input_file->Get(Form("%s/%s/%s_Bayesian_Unfoldediter_%s_xJ_eff_corr_%d",test_label[test_index].Data(),"DAgostini",test_label[test_index].Data(),var_arr[ivar].Data(),j)); 
            h_Bayesian_Unfolded_X[j]=(TH1D*)h2_Bayesian_Unfolded_corr->ProjectionX(Form("h_Bayesian_Unfolded_X_%d",j),bin_true_xj,bin_true_xj,"");
            h_Bayesian_Unfolded_X[j]->Scale(1.0/h_Bayesian_Unfolded_X[j]->Integral(0,-1),"width");

            TH2D *h2_Bayesian_Refolded = (TH2D*)input_file->Get(Form("%s/%s/%s_Bayesian_Refoldediter_%s_xJ_%d",test_label[test_index].Data(),"DAgostini",test_label[test_index].Data(),var_arr[ivar].Data(),j)); 
            h_Bayesian_Refolded_X[j]=(TH1D*)h2_Bayesian_Refolded->ProjectionX(Form("h_Bayesian_Refolded_X_%d",j),bin_det_xj,bin_det_xj,"");
            h_Bayesian_Refolded_X[j]->Scale(1.0/h_Bayesian_Refolded_X[j]->Integral(0,-1),"width");

            // ---- Unfolded Chi2 - Bayesian

            float sumChi2 = 0;
            
            TH1D *htemp1 = (TH1D*)h_Bayesian_Unfolded_X[j]->Clone();
            TH1D *htemp2 = (TH1D*)h_True_X->Clone(); 

            for (Int_t k = 0; k < (h_Bayesian_Refolded_X[j]->GetNbinsX()+1); k++){  
                if (htemp1->GetBinContent(k) > 0) sumChi2+= (htemp1->GetBinContent(k)-htemp2->GetBinContent(k))*(htemp1->GetBinContent(k)-htemp2->GetBinContent(k))/(htemp1->GetBinError(k)*htemp1->GetBinError(k)); // + htemp2->GetBinError(k)*htemp2->GetBinError(k)
            }
            sumChi2/=(h_Bayesian_Refolded_X[j]->GetNbinsX());
            hist_chi2_Bayesian->SetBinContent(j,sumChi2);

            // ---- Refolded Chi2
            if(test_index==kBottomline) continue;

            sumChi2 = 0;

            TH1D *htemp1_smeared = (TH1D*)h_Raw_X->Clone();
            TH1D *htemp2_smeared = (TH1D*)h_Bayesian_Refolded_X[j]->Clone(); // (TH1D*)raw_X_mc->Clone();//

            for (Int_t k = 0; k < (h_Bayesian_Refolded_X[j]->GetNbinsX()+1); k++){                  
                if (htemp1_smeared->GetBinContent(k) > 0) sumChi2+= (htemp1_smeared->GetBinContent(k)-htemp2_smeared->GetBinContent(k))*(htemp1_smeared->GetBinContent(k)-htemp2_smeared->GetBinContent(k))/(htemp1_smeared->GetBinError(k)*htemp1_smeared->GetBinError(k) ); //+ htemp2_smeared->GetBinError(k)*htemp2_smeared->GetBinError(k)
            }
            float pval = TMath::Prob(sumChi2, (h_Bayesian_Refolded_X[j]->GetNbinsX()));
            sumChi2/=(h_Bayesian_Refolded_X[j]->GetNbinsX());
            if(pval>0.95 && !flag_pval){
                std::cout<<" \t Chi2smeared =  "<<sumChi2<<"  \t  "<<(htemp1_smeared->GetNbinsX())<<" \t  p-value = "<<pval<<"\t iter "<<j<<std::endl;
                flag_pval=1;
                iter_ref = j;
            }
            hist_chi2_smeared->SetBinContent(j,sumChi2);
            hist_pval_smeared->SetBinContent(j,pval);

        }

        TFile *fout;
        fout = new TFile(output_path + "OutputUnfolded_"+dir_cent_string+label+"/OutputUnfolded_"+dir_cent_string+label+file_string+"_"+var_arr[ivar]+".root", "recreate");

        fout->cd();
        h2_Probability->Write("",TObject::kWriteDelete);
        h2_Covariance->Write("",TObject::kWriteDelete);
        h2_pur->Write("",TObject::kWriteDelete);
        h2_eff->Write("",TObject::kWriteDelete);
        h_Raw_X->Write("",TObject::kWriteDelete);
        h_True_X->Write("",TObject::kWriteDelete);
        h_Folded_Invert_X->Write("",TObject::kWriteDelete);
        h_Unfolded_Invert_X->Write("",TObject::kWriteDelete);
        h_Folded_Raw_X->Write("",TObject::kWriteDelete);
        h_Unfolded_True_X->Write("",TObject::kWriteDelete);
        h_Bayesian_Unfolded_X[iter_ref]->Write("unfold_X",TObject::kWriteDelete);
        h_Bayesian_Refolded_X[iter_ref]->Write("",TObject::kWriteDelete);

        fout->cd();
        gDirectory->mkdir("Unfolding_Tests");
        fout->cd("Unfolding_Tests");
        hist_pval_smeared->Write("",TObject::kWriteDelete);
        hist_chi2_smeared->Write("",TObject::kWriteDelete);
        hist_chi2_Bayesian->Write("",TObject::kWriteDelete);
        hist_chi2_Invert->Write("",TObject::kWriteDelete);
        fout->cd();

        if(test_index==kNoTest && sys_index==kNominal){
            fout->cd();
            gDirectory->mkdir("Bayesian");
            fout->cd("Bayesian");
            for(Int_t j=1;j<niter;j++){
                h_Bayesian_Unfolded_X[j]->Write(Form("unfold_X%d",j),TObject::kWriteDelete);
            }
            fout->cd();
        }

        std::vector<TString>sel;
        std::vector<TH1D*> hist_input;
        std::vector<TString> histname_input;
        if(test_index==kBottomline){
            sel = {centstring,Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,xjmin_det)};  
            if(flag_invert){ sel.insert(sel.begin(), {"Purity","Matrix Inversion"});}
            else{            sel.insert(sel.begin(), {"Purity","D'Agostini"});}
            gStyle->SetPaintTextFormat("4.2f");
            Plot_hist2D({h2_pur},{"Purity"+file_string+"_"+var_arr[ivar]},"text_E_colz",sel);
            sel = {centstring,Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,xjmin_det)};  
            if(flag_invert){ sel.insert(sel.begin(), {"Efficiency","Matrix Inversion"});}
            else{            sel.insert(sel.begin(), {"Efficiency","D'Agostini"});}
            Plot_hist2D({h2_eff},{"Efficiency"+file_string+"_"+var_arr[ivar]},"text_E_colz",sel);
            sel = {"Probability Matrix",var_nam[ivar]};
            gStyle->SetPaintTextFormat("4.3f");
            Plot_hist2D({h2_Probability},{"Probability"+file_string+"_"+var_arr[ivar]},"text_colz",sel);
            gStyle->SetPaintTextFormat();
        }
        if(test_index==kNoTest){
            sel = {"","Corrected Data Counts "+var_nam[ivar]};
            gStyle->SetPaintTextFormat("6.1f");
            Plot_hist2D({h2_Raw},{test_label[test_index]+"_Raw_X_Y"+file_string+"_"+var_arr[ivar]},"text_E_colz",sel);
            sel = {"","Covariance Matrix "+var_nam[ivar]};
            gStyle->SetPaintTextFormat("4.1f");
            Plot_hist2D({h2_Covariance},{test_label[test_index]+"_MatCovariance"+file_string+"_"+var_arr[ivar]},"text_colz",sel);
        }
        switch(test_index){
            case kTrivial:  sel = {" ","Trivial Test"      ,centstring,Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,xjmin_det)};  break;
            case kSplitNominal:
            case kSplitAltMC:
                            sel = {" ","Split Test - 25/75"        ,centstring,Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,xjmin_det)};  break;  
            default:        sel = {centstring,Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,xjmin_det)};  
                            if(flag_invert){ sel.insert(sel.begin(), {" ","Matrix Inversion"});}
                            else{            sel.insert(sel.begin(), {" ","D'Agostini"});}
                            break;  
        }

        if(flag_invert){
            Plot_hist_ratio({h_Folded_Raw_X},{"Folded_Raw",var_nam[ivar],"Refolded/Raw","PbPb_"+dir_cent_string+test_label[test_index]+"_Refolded_MatInvertVs"+var_arr[ivar]+file_string},"bcenter_label_leg",sel);
            if(test_index!=kNoTest)
                Plot_hist_ratio({h_Unfolded_True_X},{"Unfolded_True",var_nam[ivar],"Unfolded/True","PbPb_"+dir_cent_string+test_label[test_index]+"_Unfolded_MatInvertVs"+var_arr[ivar]+file_string},"bcenter_label_leg",sel);

            Plot_hist({h_True_X,h_Bayesian_Unfolded_X[iter_ref],h_Unfolded_Invert_X},{"True MC","D'Agostini","Matrix Inversion",var_nam[ivar],"1/N_{jet} dN/d"+var_nam[ivar],"PbPb_"+dir_cent_string+test_label[test_index]+"_True_Unfolded_Matinvert_"+var_arr[ivar]+file_string},"rightlabel",sel);
        }
        else{
            TH1D *h_Folded_Raw_Bayesian_X = (TH1D*)h_Bayesian_Refolded_X[iter_ref]->Clone(test_label[test_index]+"_hfold_Bayesian_raw_"+var_arr[ivar]+"_xJ_X");
            h_Folded_Raw_Bayesian_X->Divide(h_Raw_X);
            h_Folded_Raw_Bayesian_X->Write("",TObject::kWriteDelete);

            TH1D *h_Folded_Raw_Bayesian_X_niter = (TH1D*)h_Bayesian_Refolded_X[niter-1]->Clone(test_label[test_index]+"_hfold_Bayesian_raw_"+var_arr[ivar]+"_xJ_X_niter");
            h_Folded_Raw_Bayesian_X_niter->Divide(h_Raw_X);
            h_Folded_Raw_Bayesian_X_niter->Write("",TObject::kWriteDelete);

            TH1D *h_Folded_Raw_Bayesian_X_niter_2 = (TH1D*)h_Bayesian_Refolded_X[(niter/2) -1]->Clone(test_label[test_index]+"_hfold_Bayesian_raw_"+var_arr[ivar]+"_xJ_X_niter_2");
            h_Folded_Raw_Bayesian_X_niter_2->Divide(h_Raw_X);
            h_Folded_Raw_Bayesian_X_niter_2->Write("",TObject::kWriteDelete);
            
            TH1D *h_Unfolded_True_Bayesian_X = (TH1D*)h_Bayesian_Unfolded_X[iter_ref]->Clone(test_label[test_index]+"_hunf_Bayesian_true_"+var_arr[ivar]+"_xJ_X");
            h_Unfolded_True_Bayesian_X->Divide(h_True_X);
            h_Unfolded_True_Bayesian_X->Write("",TObject::kWriteDelete);

            TH1D *h_Unfolded_True_Bayesian_X_niter = (TH1D*)h_Bayesian_Unfolded_X[niter-1]->Clone(test_label[test_index]+"_hunf_Bayesian_true_"+var_arr[ivar]+"_xJ_X_niter");
            h_Unfolded_True_Bayesian_X_niter->Divide(h_True_X);
            h_Unfolded_True_Bayesian_X_niter->Write("",TObject::kWriteDelete);
            
            TH1D *h_Unfolded_True_Bayesian_X_niter_2 = (TH1D*)h_Bayesian_Unfolded_X[(niter/2) -1]->Clone(test_label[test_index]+"_hunf_Bayesian_true_"+var_arr[ivar]+"_xJ_X_niter_2");
            h_Unfolded_True_Bayesian_X_niter_2->Divide(h_True_X);
            h_Unfolded_True_Bayesian_X_niter_2->Write("",TObject::kWriteDelete);

            Plot_hist_ratio({h_Folded_Raw_Bayesian_X,h_Folded_Raw_Bayesian_X_niter_2,h_Folded_Raw_Bayesian_X_niter},{Form("Iter %d (p val>0.95)",iter_ref),Form("Iter %d",(niter/2)+1),Form("Iter %d",niter),var_nam[ivar],"Refolded/Raw","PbPb_"+dir_cent_string+test_label[test_index]+"_Refolded_BayesianVs"+var_arr[ivar]+file_string},"bcenter_label",sel);
            if(test_index!=kNoTest || test_index!=kBottomline)
                Plot_hist_ratio({h_Unfolded_True_Bayesian_X,h_Unfolded_True_Bayesian_X_niter_2,h_Unfolded_True_Bayesian_X_niter},{Form("Iter %d (p val>0.95)",iter_ref),Form("Iter %d",(niter/2)),Form("Iter %d",niter),var_nam[ivar],"Unfolded/True","PbPb_"+dir_cent_string+test_label[test_index]+"_Unfolded_BayesianVs"+var_arr[ivar]+file_string},"bcenter_label",sel);

            Plot_hist({h_True_X,h_Bayesian_Unfolded_X[iter_ref]},{"True MC","D'Agostini",var_nam[ivar],"1/N_{jet} dN/d"+var_nam[ivar],"PbPb_"+dir_cent_string+test_label[test_index]+"_True_Unfolded_Bayesian_"+var_arr[ivar]+file_string},"rightlabel",sel);
        }
        
        sel = {var_nam[ivar],centstring,Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,xjmin_det),"end","noStackHIST"};
        if(flag_invert){ sel.insert(sel.begin(), "Matrix Inversion");}
        else{            sel.insert(sel.begin(), "D'Agostini");}
        if(test_index==kBottomline){
            hist_input={};
            hist_input.push_back((TH1D*)hist_chi2_smeared->Clone());
            histname_input.push_back("#chi^{2}_{smeared}");
            hist_input.push_back((TH1D*)hist_chi2_Bayesian->Clone());
            histname_input.push_back("#chi^{2}_{D'Agostini}");
            if(flag_invert){
                hist_input.push_back((TH1D*)hist_chi2_Invert->Clone());
                histname_input.push_back("#chi^{2}_{Matrix Inversion}");
            }
            histname_input.push_back("Iterations");
            histname_input.push_back("#chi^{2}/NDF");
            histname_input.push_back("PbPb_"+dir_cent_string+test_label[test_index]+"_Chi2_ndf_bottomline_"+var_arr[ivar]+file_string);
            Plot_hist(hist_input,histname_input,"rightlabel_opt",sel);

            // Graphical Bottomline test
            hist_input={};
            histname_input={};
            TH1D* htemp = (TH1D*)h_True_X->Clone();               // True Level
            if(flag_invert){
                htemp->Divide((TH1D*)h_Unfolded_Invert_X->Clone());  // For D'Agostini
                hist_input.push_back((TH1D*)htemp->Clone());                
            }
            else{
                htemp->Divide((TH1D*)h_Bayesian_Unfolded_X[iter_ref]->Clone());  // For D'Agostini
                hist_input.push_back((TH1D*)htemp->Clone());
            }
            histname_input.push_back(Form("MC True"));
            htemp = (TH1D*)h_Raw_mc_X->Clone();     
            htemp->Divide((TH1D*)h_Raw_X->Clone());
            hist_input.push_back((TH1D*)htemp->Clone());
            histname_input.push_back(Form("MC Det"));
            histname_input.push_back(var_nam[ivar]);
            histname_input.push_back(Form("Ratio to Data"));
            // histname_input.push_back("Graphical_Bottomline_test");
            histname_input.push_back("PbPb_"+dir_cent_string+test_label[test_index]+"_Graphical_Bottomline_test_"+var_arr[ivar]+file_string);
            Plot_hist(hist_input,histname_input,"bcenterlabel",sel);
        }

        fout->Close();
        }


        switch(test_index){
            case kNoTest: 
                        if(sys_label[sys_index].Contains("response")){loop_flag=false;}
                        else{sys_index=sys_list[++loop_index];loop_flag=true;}
                        break;                            
            case kTrivial: loop_flag = false; break;
            case kSplitNominal:
            case kSplitAltMC: 
                            if(loop_index<4){loop_index++; loop_flag = true;}
                            else{ loop_flag = false;}
                            break;
            case kCrossfold:
                            if(loop_index<2){loop_index++; loop_flag = true;}
                            else{ loop_flag = false;}
                            break;
            default: break;
        }
    }while(loop_flag);

}

void Plot_hist_ratio(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "width" = Divide by Bin Width
    // "opt" = drawopt is last element of eopt

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(opt.Contains("log")) gStyle->SetOptLogy(1);
    
    TString drawopt = "nostackE1][P0"; 
    if(opt.Contains("opt"))
        drawopt = eopt.back();
    const std::vector<int> colarray  = { 1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606,
                                       1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29,   //  28, 39, 40
                                        24, 21, 26, 23, 30};  //  34, 37, 41

    TCanvas *c= new TCanvas();
    TLegend *l;
    float leg_x1 = 0.6;
    float leg_y1 = 0.58;
    float leg_x2 = 0.8;
    float leg_y2 = 0.88;
    if(opt.Contains("bcenter")){
        leg_x1 = 0.4;
        leg_y1 = 0.15;
        leg_x2 = 0.6;
        leg_y2 = 0.3;
    }
    else if(opt.Contains("left")){
        leg_x1 = 0.15;
        leg_y1 = 0.55;
        leg_x2 = 0.35;
        leg_y2 = 0.88;
    }
    l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    l->SetFillStyle(0);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->SetTextSize(0.035);
    l->SetTextFont(42);

    THStack hs("hs","hs");

    for(std::size_t ihist=0; ihist<hist.size();){
        if(opt.Contains("eff")){
            if((ihist+1)>=hist.size()) break;
            hist[ihist+1]->SetLineColor(colarray[ihist%10]);
            hist[ihist+1]->SetMarkerColor(colarray[ihist%10]);
            hist[ihist+1]->SetMarkerStyle(markarray[ihist%10]);
            hist[ihist+1]->Divide(hist[ihist+1],hist[0],1,1);
            ihist++;
        }
        else{
            hist[ihist]->SetLineColor(colarray[ihist%10]);
            hist[ihist]->SetMarkerColor(colarray[ihist%10]);
            hist[ihist]->SetMarkerStyle(markarray[ihist%10]);
        }
        if(opt.Contains("norm_width")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2),"width");
        }
        else if(opt.Contains("norm")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2));
        }

        if(opt.Contains("flow"))
            hist[ihist]->GetXaxis()->SetRange(0,hist[ihist]->GetNbinsX()+2);
        hs.Add(hist[ihist]);      
        l->AddEntry(hist[ihist], histname[ihist], "lep");
        if(!opt.Contains("eff")) ihist++;
    }
    // if(opt.Contains("eff")){
        hs.SetMaximum(1.3);
        hs.SetMinimum(0.5);
    // }
    hs.Draw(drawopt);
    //! TO remove Overflow Bin
    float line_right_edge = hist[0]->GetXaxis()->GetBinLowEdge(hist[0]->GetNbinsX()+1);
    if((histname.back().Contains("Unfolded")||histname.back().Contains("unfolded")||histname.back().Contains("Graphical")) && !histname.back().Contains("Y") && !flag_invert){
    hs.GetXaxis()->SetRange(1,hist[0]->GetNbinsX()-1);
    line_right_edge = hist[0]->GetXaxis()->GetBinLowEdge(hist[0]->GetNbinsX());
    }
    if(opt.Contains("label")){
        hs.GetXaxis()->SetTitle(histname.at(histname.size()-3));
        hs.GetYaxis()->SetTitle(histname.at(histname.size()-2));
    }
    else{
        hs.GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
        hs.GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());
    }
    if(!opt.Contains("leg"))
        l->Draw();

    TLine *line=new TLine(hist[0]->GetXaxis()->GetXmin(),1.0,line_right_edge,1.0);
    line->SetLineColor(kRed);
    line->SetLineStyle(2);
    line->Draw("SAME");

    TLatex latex;
    latex.SetTextSize(0.035);
    if(label.Contains("Data"))
        latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary}} #bf{PbPb 1.69 nb^{-1} (5.02 TeV)}");
    else
        latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary Simulation}}");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.41,0.92,eopt[0]);
        latex.DrawLatexNDC(0.68,0.92,eopt[1]);
    }    
    latex.SetTextSize(0.035);
    if(eopt.size()>2){
        for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
            if(opt.Contains("bcenter")){
                leg_y2+=0.06;
                latex.DrawLatexNDC(leg_x1,leg_y2,eopt[ind]);
            }
            else{
                leg_y1-=0.06;
                latex.DrawLatexNDC(leg_x1,leg_y1,eopt[ind]);
            }
        }
    }
    gPad->Update();
    c->SaveAs(output_path + "/OutputUnfolded_"+dir_cent_string+label+"/"+histname.back()+".png");
    c->Write(histname.back(),TObject::kWriteDelete);
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}


void Plot_hist(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "width" = Divide by Bin Width
    // "opt" = drawopt is last element of eopt

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(opt.Contains("log")) gStyle->SetOptLogy(1);
    
    TString drawopt = "nostackE1][P0"; 
    if(opt.Contains("opt"))
        drawopt = eopt.back();
    const std::vector<int> colarray  = { 1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606,
                                       1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29,   //  28, 39, 40
                                        24, 21, 26, 23, 30};  //  34, 37, 41

    TCanvas *c= new TCanvas();
    TLegend *l;
    float leg_x1 = 0.6;
    float leg_y1 = 0.58;
    float leg_x2 = 0.8;
    float leg_y2 = 0.88;
    if(opt.Contains("bcenter")){
        leg_x1 = 0.4;
        leg_y1 = 0.15;
        leg_x2 = 0.6;
        leg_y2 = 0.3;
    }
    else if(opt.Contains("left")){
        leg_x1 = 0.15;
        leg_y1 = 0.55;
        leg_x2 = 0.35;
        leg_y2 = 0.88;
    }
    l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    l->SetFillStyle(0);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->SetTextSize(0.035);
    l->SetTextFont(42);

    THStack hs("hs","hs");

    for(std::size_t ihist=0; ihist<hist.size();){
        if(opt.Contains("eff")){
            if((ihist+1)>=hist.size()) break;
            hist[ihist+1]->SetLineColor(colarray[ihist%10]);
            hist[ihist+1]->SetMarkerColor(colarray[ihist%10]);
            hist[ihist+1]->SetMarkerStyle(markarray[ihist%10]);
            hist[ihist+1]->Divide(hist[ihist+1],hist[0],1,1);
            ihist++;
        }
        else{
            hist[ihist]->SetLineColor(colarray[ihist%10]);
            hist[ihist]->SetMarkerColor(colarray[ihist%10]);
            hist[ihist]->SetMarkerStyle(markarray[ihist%10]);
        }
        if(opt.Contains("norm_width")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2),"width");
        }
        else if(opt.Contains("norm")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2));
        }

        if(opt.Contains("flow"))
            hist[ihist]->GetXaxis()->SetRange(0,hist[ihist]->GetNbinsX()+2);
        hs.Add(hist[ihist]);      
        l->AddEntry(hist[ihist], histname[ihist], "lep");
        if(!opt.Contains("eff")) ihist++;
    }
    if(opt.Contains("eff")){
        hs.SetMaximum(1.3);
        hs.SetMinimum(0.5);
    }
    hs.Draw(drawopt);
    //! TO remove Overflow Bin
    if((histname.back().Contains("Unfolded")||histname.back().Contains("unfolded")||histname.back().Contains("Graphical")) && !histname.back().Contains("Y") && !flag_invert)
    hs.GetXaxis()->SetRange(1,hist[0]->GetNbinsX()-1);
    if(opt.Contains("label")){
        hs.GetXaxis()->SetTitle(histname.at(histname.size()-3));
        hs.GetYaxis()->SetTitle(histname.at(histname.size()-2));
    }
    else{
        hs.GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
        hs.GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());
    }
    l->Draw();


    TLatex latex;
    latex.SetTextSize(0.035);
    if(label.Contains("Data"))
        latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary}} #bf{PbPb 1.69 nb^{-1} (5.02 TeV)}");
    else
        latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary Simulation}}");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.41,0.92,eopt[0]);
        latex.DrawLatexNDC(0.68,0.92,eopt[1]);
    }    
    latex.SetTextSize(0.035);
    if(eopt.size()>2){
        for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
            if(opt.Contains("bcenter")){
                leg_y2+=0.06;
                latex.DrawLatexNDC(leg_x1,leg_y2,eopt[ind]);
            }
            else{
                leg_y1-=0.06;
                latex.DrawLatexNDC(leg_x1,leg_y1,eopt[ind]);
            }
        }
    }
    gPad->Update();
    c->SaveAs(output_path + "/OutputUnfolded_"+dir_cent_string+label+"/"+histname.back()+".png");
    c->Write(histname.back(),TObject::kWriteDelete);
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}

void Plot_hist2D(std::vector<TH2D*> hist,std::vector<TString> histname,TString dopt,std::vector<TString> eopt){
    // dopt contains draw options


    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(eopt.back().Contains("log")) gStyle->SetOptLogz(1);
    
    TString drawopt = dopt; 
    gStyle->SetPalette(kBird);

    TCanvas *c;
    // TLegend *l;
    float leg_x1 = 0.6;
    float leg_y1 = 0.9; //! No legend -> just changed for text
    float leg_x2 = 0.8;
    float leg_y2 = 0.85;
    
    if(eopt.back().Contains("bcenter")){
        leg_x1 = 0.45;
        leg_y1 = 0.15;
        leg_x2 = 0.55;
        leg_y2 = 0.3;
    }
    else if(eopt.back().Contains("left")){
        leg_x1 = 0.15;
        leg_y1 = 0.9;  //! No legend -> just changed for text
        leg_x2 = 0.25;
        leg_y2 = 0.85;
    }
    /*
    l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    l->SetFillStyle(0);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->SetTextSize(0.025);
    l->SetTextFont(42);
    l->Draw();
    */


    for(std::size_t ihist=0; ihist<hist.size();ihist++){
        c = new TCanvas();
        hist[ihist]->SetMarkerSize(1.5);   
        hist[ihist]->Draw(drawopt);   
        //! TO remove Overflow Bin
        if((histname.back().Contains("Efficiency")) && !flag_invert){
        hist[ihist]->GetXaxis()->SetRange(1,hist[ihist]->GetNbinsX()-1);
        hist[ihist]->GetYaxis()->SetRange(2,hist[ihist]->GetNbinsY());
        }
        TLatex latex;
        latex.SetTextSize(0.035);
        if(label.Contains("Data"))
            latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary}} #bf{PbPb 1.69 nb^{-1} (5.02 TeV)}");
        else
            latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary Simulation}}");

        if(eopt[0].Contains("Cent")){
            latex.DrawLatexNDC(0.78,0.92,eopt[0]);
        }
        else if(eopt.size()>=2){
            latex.DrawLatexNDC(0.41,0.92,eopt[0]);
            latex.DrawLatexNDC(0.68,0.92,eopt[1]);
        }    
        latex.SetTextSize(0.035);
        if(eopt.size()>2){
            for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
                if(eopt.back().Contains("bcenter")){
                    leg_y2+=0.06;
                    latex.DrawLatexNDC(leg_x1,leg_y2,eopt[ind]);
                }
                else{
                    leg_y1-=0.06;
                    latex.DrawLatexNDC(leg_x1,leg_y1,eopt[ind]);
                }
            }
        }
        gPad->Update();
        c->SaveAs(output_path + "/OutputUnfolded_"+dir_cent_string+label+"/"+histname[ihist]+".png");
        c->Write(histname[ihist],TObject::kWriteDelete);
        std::cout<<histname[ihist]<<" has been saved"<<std::endl;
    }

    if(eopt.back().Contains("log")) gStyle->SetOptLogz(0);
    /*
    delete l;*/
}

int main(int argc, char* argv[]){

    // printf("argc = %d\n",argc);
    // printf("argv = %s\n",argv[0]);
    // if(argc==7){
        // output_path = argv[1];
        // label = argv[2];
        // plot_sys_inverted_PbPb(argv[3],argv[4],atoi(argv[5]),atoi(argv[6]));
    // }

    return 0;
}
