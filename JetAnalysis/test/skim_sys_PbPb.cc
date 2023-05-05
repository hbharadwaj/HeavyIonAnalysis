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

#include <TLatex.h>         // needed for TLatex
#include <TFile.h>          // needed for TFile

#include <iostream>         // needed for I/O

TString label="May_3_PbPb_2018_sys_WP_update"; // "Substructure_up_jets";//"QCDPhoton_jets"; // "Data_2018_jets";//
TString output_path = "Uncertainty";//"./OutputPlots/Skimsys/"; // Uncertainty/ OutputPlots
TString in_file="QCDPhoton_jets";
const float min_cent_val = 0;
const float max_cent_val = 30;
TFile *fout;

// namespace MyEnum{
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
        kAltMC      =11               //* Pythia8 with quark/gluon fraction reweighted 
    };
    
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
        kAltMC      
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
        "AltMC"      
    };
// }

float getpurity(float in_min_cent,float in_max_cent,SystematicsTreatment_PbPb in_sys_index){ 
    // Function to find the photon purity using the template fit and ABCD method 
    const int ncent = 5; // {(0,30),(30,90),(0,90),(0,20),(20,90)}
    const float purity_values_nom[ncent]  = {0.774996,0.891456,0.805383,0.757357,0.872783};// {0.829,0.894,0.843,0.809,0.898};
    const float purity_values_ABCD[ncent] = {0.780897,0.889843,0.809544,0.765261,0.870248};// {0.823,0.883,0.837,0.803,0.887};
    
    
    switch(in_sys_index){
        case kData:
            if(in_min_cent==0 && in_max_cent==30) return purity_values_nom[0];
            if(in_min_cent==30&& in_max_cent==90) return purity_values_nom[1];
            if(in_min_cent==0 && in_max_cent==90) return purity_values_nom[2];
            if(in_min_cent==0 && in_max_cent==20) return purity_values_nom[3];
            if(in_min_cent==20&& in_max_cent==90) return purity_values_nom[4];
            
        case kPhoPurity:
            if(in_min_cent==0 && in_max_cent==30) return purity_values_ABCD[0];
            if(in_min_cent==30&& in_max_cent==90) return purity_values_ABCD[1];
            if(in_min_cent==0 && in_max_cent==90) return purity_values_ABCD[2];
            if(in_min_cent==0 && in_max_cent==20) return purity_values_ABCD[3];
            if(in_min_cent==20&& in_max_cent==90) return purity_values_ABCD[4];
        default: std::cout<<"Photon Purity error"<<std::endl;
    }
    return -1.0;
}

void get_qfrac(float in_min_cent,float in_max_cent,float &out_orig_frac, float &out_fit_frac){ 
    // Function to Find the original and Fit quark fraction -> Used to obtain an Alternative MC sample for response matrix uncertainty
    const int ncent = 5; // {(0,30),(30,90),(0,90),(0,20),(20,90)}
    const float orig_qg[ncent] = {0.57889581,0.58154138,0.57951658,0.57672473,0.58561608};//{0.634,0.632,0.6325,0.633,0.633};   // Quark Fraction
    const float fit_qg[ncent]  = {0.446405,0.439685,0.439685,0.431104,0.46912}; //              {0.485,0.528,0.496,0.472,0.541}; // From angu - {0.483,0.533,0.494,0.467,0.529};
    
    if(in_min_cent==0 && in_max_cent==30) out_orig_frac =orig_qg[0]; out_fit_frac =fit_qg[0];  return;
    if(in_min_cent==30&& in_max_cent==90) out_orig_frac =orig_qg[1]; out_fit_frac =fit_qg[1];  return;
    if(in_min_cent==0 && in_max_cent==90) out_orig_frac =orig_qg[2]; out_fit_frac =fit_qg[2];  return;
    if(in_min_cent==0 && in_max_cent==20) out_orig_frac =orig_qg[3]; out_fit_frac =fit_qg[3];  return;
    if(in_min_cent==20&& in_max_cent==90) out_orig_frac =orig_qg[4]; out_fit_frac =fit_qg[4];  return;

    std::cout<<"Quark Fraction error"<<std::endl;
    return;
}

void loop_sys(SystematicsTreatment_PbPb sys_index){
    gROOT->SetBatch();
    gErrorIgnoreLevel = kFatal;
    TString DIR = output_path;
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    // ----------------------------------------------------------------------------------------------------------------
    //Tree Variable Declaration

        TChain jet_tree("jet_tree");
        jet_tree.Add(in_file+".root/jet_tree");

        Float_t weight = 0;
        Float_t weight_pthat = 0;
        Float_t weight_cent = 0;

        Float_t mcCalIsoDR04 = 0;
        Float_t mcE = 0;
        Float_t mcEt = 0;
        Float_t mcEta = 0;
        Float_t mcPhi = 0;

        Int_t   pho_genMatchedIndex = 0;
        Int_t   mcPID = 0;
        Int_t   mcMomPID = 0;
        
        Float_t phoSCRawE = 0;
        Float_t phoSCEta = 0;
        Float_t phoSCPhi = 0;
        Float_t phoSigmaIEtaIEta_2012 = 0;
        Float_t rho = 0;
        Float_t vz = 0;

        Float_t phoEt = 0;
        Float_t phoEtCorrected = 0;
        Float_t phoEta = 0;
        Float_t phoPhi = 0;
        Float_t phoHoverE = 0;
        Float_t pho_ecalClusterIsoR3 = 0;
        Float_t pho_hcalRechitIsoR3 = 0;
        Float_t pho_trackIsoR3PtCut20 = 0;
        Float_t pho_ecalClusterIsoR4 = 0;
        Float_t pho_hcalRechitIsoR4 = 0;
        Float_t pho_trackIsoR4PtCut20 = 0;
        Float_t phoSigmaEtaEta_2012 = 0;

        Float_t pfcIso3subUE = 0;
        Float_t pfnIso3subUE = 0;
        Float_t pfpIso3subUE = 0;
        Float_t SumPFIso = 0;
        Float_t SumCalIso = 0;

        Bool_t  eleRej = 0;

        Int_t   hiBin = 0;
        Float_t pthat=0;
        Int_t   L1_SingleEG21_BptxAND = 0;
        Int_t   HLT_HIGEDPhoton40_v1 = 0;

        jet_tree.SetBranchAddress("phoSCRawE",&phoSCRawE);
        jet_tree.SetBranchAddress("phoSCEta",&phoSCEta);
        jet_tree.SetBranchAddress("phoSCPhi",&phoSCPhi);
        jet_tree.SetBranchAddress("phoSigmaIEtaIEta_2012",&phoSigmaIEtaIEta_2012);
        jet_tree.SetBranchAddress("rho",&rho);
        jet_tree.SetBranchAddress("vz",&vz);

        jet_tree.SetBranchAddress("phoEt",&phoEt);
        jet_tree.SetBranchAddress("phoEtCorrected",&phoEtCorrected);
        jet_tree.SetBranchAddress("phoEta",&phoEta);
        jet_tree.SetBranchAddress("phoPhi",&phoPhi);
        jet_tree.SetBranchAddress("phoHoverE",&phoHoverE);
        jet_tree.SetBranchAddress("pho_ecalClusterIsoR3",&pho_ecalClusterIsoR3);
        jet_tree.SetBranchAddress("pho_hcalRechitIsoR3",&pho_hcalRechitIsoR3);
        jet_tree.SetBranchAddress("pho_trackIsoR3PtCut20",&pho_trackIsoR3PtCut20);
        jet_tree.SetBranchAddress("pho_ecalClusterIsoR4",&pho_ecalClusterIsoR4);
        jet_tree.SetBranchAddress("pho_hcalRechitIsoR4",&pho_hcalRechitIsoR4);
        jet_tree.SetBranchAddress("pho_trackIsoR4PtCut20",&pho_trackIsoR4PtCut20);
        jet_tree.SetBranchAddress("phoSigmaEtaEta_2012",&phoSigmaEtaEta_2012);

        jet_tree.SetBranchAddress("pfcIso3subUE",&pfcIso3subUE);
        jet_tree.SetBranchAddress("pfnIso3subUE",&pfnIso3subUE);
        jet_tree.SetBranchAddress("pfpIso3subUE",&pfpIso3subUE);
        jet_tree.SetBranchAddress("SumPFIso",&SumPFIso);
        jet_tree.SetBranchAddress("SumCalIso",&SumCalIso);
        jet_tree.SetBranchAddress("hiBin",&hiBin);

        jet_tree.SetBranchAddress("eleRej",&eleRej);

        jet_tree.SetBranchAddress("L1_SingleEG21_BptxAND",&L1_SingleEG21_BptxAND);
        jet_tree.SetBranchAddress("HLT_HIGEDPhoton40_v1",&HLT_HIGEDPhoton40_v1);

        Int_t nref = 0;
        Int_t jet_index = -1;
        Float_t jtpt[500]={-1};
        Float_t jteta[500]={-1};
        Float_t jtphi[500]={-1};
        Float_t jtsym[500]={-1};
        Float_t jtrg[500]={-1};
        Float_t jtdynkt[500]={-1};
        Float_t jtangu[500]={-1};

        Float_t refpt[500]={-1};
        Float_t refeta[500]={-1};
        Float_t refphi[500]={-1};
        Float_t refsym[500]={-1};
        Float_t refrg[500]={-1};
        Float_t refdynkt[500]={-1};
        Float_t refangu[500]={-1};
        Float_t refparton_pt[500]={-999};
        Int_t refparton_flavor[500]={-999};

        Int_t nallgen = 0;
        Int_t allgenmatchindex[500]={-999};
        Float_t allgenpt[500]={-1};
        Float_t allgeneta[500]={-1};
        Float_t allgenphi[500]={-1};
        Float_t allgensym[500]={-1};
        Float_t allgenrg[500]={-1};
        Float_t allgendynkt[500]={-1};
        Float_t allgenangu[500]={-1};

        jet_tree.SetBranchAddress("nref", &nref);
        jet_tree.SetBranchAddress("jet_index", &jet_index);
        jet_tree.SetBranchAddress("jtpt", &jtpt);
        jet_tree.SetBranchAddress("jteta", &jteta);
        jet_tree.SetBranchAddress("jtphi", &jtphi);
        jet_tree.SetBranchAddress("jtsym", &jtsym);
        jet_tree.SetBranchAddress("jtrg", &jtrg);
        jet_tree.SetBranchAddress("jtdynkt", &jtdynkt);
        jet_tree.SetBranchAddress("jtangu", &jtangu);
        if(jet_tree.GetBranch("refparton_flavor")){
            jet_tree.SetBranchAddress("refparton_pt", &refparton_pt);
            jet_tree.SetBranchAddress("refparton_flavor", &refparton_flavor);
        }

        if(jet_tree.GetBranch("allgenmatchindex")){
            jet_tree.SetBranchAddress("pthat",&pthat);
            jet_tree.SetBranchAddress("weight",&weight);
            jet_tree.SetBranchAddress("weight_pthat",&weight_pthat);
            jet_tree.SetBranchAddress("weight_cent",&weight_cent);
            jet_tree.SetBranchAddress("mcCalIsoDR04",&mcCalIsoDR04);
            jet_tree.SetBranchAddress("mcE",&mcE);
            jet_tree.SetBranchAddress("mcEt",&mcEt);
            jet_tree.SetBranchAddress("mcEta",&mcEta);
            jet_tree.SetBranchAddress("mcPhi",&mcPhi);
            jet_tree.SetBranchAddress("pho_genMatchedIndex",&pho_genMatchedIndex);
            jet_tree.SetBranchAddress("mcPID",&mcPID);
            jet_tree.SetBranchAddress("mcMomPID",&mcMomPID);

            jet_tree.SetBranchAddress("refpt", &refpt);
            jet_tree.SetBranchAddress("refeta", &refeta);
            jet_tree.SetBranchAddress("refphi", &refphi);
            jet_tree.SetBranchAddress("refsym", &refsym);
            jet_tree.SetBranchAddress("refrg", &refrg);
            jet_tree.SetBranchAddress("refdynkt", &refdynkt);
            jet_tree.SetBranchAddress("refangu", &refangu);

            jet_tree.SetBranchAddress("nallgen", &nallgen);
            jet_tree.SetBranchAddress("allgenmatchindex", &allgenmatchindex);
            jet_tree.SetBranchAddress("allgenpt", &allgenpt);
            jet_tree.SetBranchAddress("allgeneta", &allgeneta);
            jet_tree.SetBranchAddress("allgenphi", &allgenphi);
            jet_tree.SetBranchAddress("allgensym", &allgensym);
            jet_tree.SetBranchAddress("allgenrg", &allgenrg);
            jet_tree.SetBranchAddress("allgendynkt", &allgendynkt);
            jet_tree.SetBranchAddress("allgenangu", &allgenangu);
        }

    // -------- End Tree Variable Declaration
    // ----------------------------------------------------------------------------------------------------------------
    // Output Histogram and TTree

        TH1::SetDefaultSumw2();
        TH2::SetDefaultSumw2();
        TTree *sys_tree;
        Int_t   var_jet_index   = -9999;
        Float_t var_weight      = -9999;
        Float_t var_flagsig     = -9999;
        Float_t var_pho_purity  = -9999;
        Float_t var_phoEt       = -9999;
        Float_t var_mcEt        = -9999;
        Float_t var_jetpt_det   = -9999;
        Float_t var_jetpt_true  = -9999;
        Float_t var_xJ_det      = -9999;
        Float_t var_xJ_true     = -9999;
        Float_t var_Rg_det      = -9999;
        Float_t var_Rg_true     = -9999;
        Float_t var_girth_det   = -9999;
        Float_t var_girth_true  = -9999;

        Int_t   var_gen_jet_index   = -9999;
        Float_t var_gen_jetpt_true  = -9999;
        Float_t var_gen_xJ_true     = -9999;
        Float_t var_gen_Rg_true     = -9999;
        Float_t var_gen_girth_true  = -9999;

        sys_tree = new TTree(Form("sys_tree_%s",sys_label[sys_index].Data()),Form("sys_tree_%s",sys_label[sys_index].Data()));
    
        sys_tree->Branch("jet_index"    ,&var_jet_index);
        sys_tree->Branch("weight"       ,&var_weight);
        sys_tree->Branch("flagsig"      ,&var_flagsig);
        sys_tree->Branch("pho_purity"   ,&var_pho_purity);
        sys_tree->Branch("phoEt"        ,&var_phoEt);
        sys_tree->Branch("mcEt"         ,&var_mcEt);
        sys_tree->Branch("jetpt_det"    ,&var_jetpt_det);
        sys_tree->Branch("jetpt_true"   ,&var_jetpt_true);
        sys_tree->Branch("xJ_det"       ,&var_xJ_det);
        sys_tree->Branch("xJ_true"      ,&var_xJ_true);
        sys_tree->Branch("Rg_det"       ,&var_Rg_det);
        sys_tree->Branch("Rg_true"      ,&var_Rg_true);
        sys_tree->Branch("girth_det"    ,&var_girth_det);
        sys_tree->Branch("girth_true"   ,&var_girth_true);

        sys_tree->Branch("gen_jet_index"     ,&var_gen_jet_index);
        sys_tree->Branch("gen_jetpt_true"    ,&var_gen_jetpt_true);
        sys_tree->Branch("gen_xJ_true"       ,&var_gen_xJ_true);
        sys_tree->Branch("gen_Rg_true"       ,&var_gen_Rg_true);
        sys_tree->Branch("gen_girth_true"    ,&var_gen_girth_true);
        
    // -------- End Histograms
    // ----------------------------------------------------------------------------------------------------------------
    // Constants
        const float min_pho_et = 100;
        const float cut_HoverE = 0.119947;     // 0.137168;  // 0.0696672;
        const float cut_SIEIE  = 0.010392;    // 0.0103766; // 0.00983515;
        const float cut_SumIso = 2.099277;      // 1.45486;   // 1.33546;
        const float min_xJ = 0.4;     // 0.4        
        // const float purity_values[ncent] =  {0.829,0.894,0.843,0.809,0.898};// ABCD Purity - {0.823,0.883,0.837,0.803,0.887};
        float purity_value = 1.0;   // Photon Purity 
        float orig_qg = 0.0;        // Original Quark Fraction
        float fit_qg = 0.0;         // Quark Fraction from Template Fit for Response Matrix Uncertainty     

        JetCorrectionUncertainty *jecUnc ;   
        switch(sys_index){
            case kData:      purity_value = getpurity(min_cent_val,max_cent_val,kData);      break;
            case kPhoPurity: purity_value = getpurity(min_cent_val,max_cent_val,kPhoPurity); break;
            case kJECup:
            case kJECdown:            
                jecUnc = new JetCorrectionUncertainty("/grid_mnt/vol_home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/JetAnalysis/test/Uncertainty/JEC/Autumn18_HI_V6_MC_Uncertainty_AK2PF.txt");
                break;
            case kAltMC:get_qfrac(min_cent_val,max_cent_val,orig_qg,fit_qg); break;
            default: break;
        }

        JME::JetResolution resolution ; //this is for the case where the det-level jet is not matched to a truth-level jet
        resolution = JME::JetResolution("/grid_mnt/vol_home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/JetAnalysis/test/Uncertainty/JER/Autumn18_RunD_V7b_MC_PtResolution_AK4PF.txt");
    
        JME::JetResolutionScaleFactor resolution_sf ; //this is for the case where the det-level jet is matched to a truth-level jet
        resolution_sf = JME::JetResolutionScaleFactor("/grid_mnt/vol_home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/JetAnalysis/test/Uncertainty/JER/Autumn18_RunD_V7b_MC_SF_AK4PF.txt");


    // -------- End Constants
    // ----------------------------------------------------------------------------------------------------------------
    // Event Loop
    int count = 0;
   
    for(int iEntry=0; iEntry<jet_tree.GetEntries(); iEntry++){ 
        jet_tree.GetEntry(iEntry);
        float scale =1.0;

        //* Centrality Condition
        switch(sys_index){
            case kData:         
            case kPhoPurity:    if(!(hiBin>=(min_cent_val*2   ) && hiBin<(max_cent_val*2   )))      continue; break;
            case kCentup:       if(!(hiBin>=(min_cent_val*2+12) && hiBin<(max_cent_val*2+12)))      continue; break;
            case kCentdown:     if(!(hiBin>=(min_cent_val*2+ 6) && hiBin<(max_cent_val*2+ 6)))      continue; break;
            default:            if(!(hiBin>=(min_cent_val*2+ 9) && hiBin<(max_cent_val*2+ 9)))      continue;
        }
        //* Photon Conditions
            if(phoSCEta<-1.39 && phoPhi<-0.9 && phoPhi>-1.6) continue;         
            if(!(fabs(phoSCEta)<1.442)) continue;
            if(!(phoEtCorrected>min_pho_et)) continue;
            if(!HLT_HIGEDPhoton40_v1) continue;

            // Final signal and background region flags
            int flagsig=0;
            int flagbkg=0;

            int flagHoverE=1;   
            int flagSigmaEtaEta=1;
            int flagIso=1;

            if(phoHoverE<=cut_HoverE) flagHoverE = 0;
            if(phoSigmaIEtaIEta_2012<=cut_SIEIE) flagSigmaEtaEta = 0;
            if(SumCalIso<=cut_SumIso) flagIso = 0;

            if(!flagHoverE && !eleRej && !flagIso && !flagSigmaEtaEta) flagsig = 1;
            if(!flagHoverE && !eleRej && !flagIso &&  flagSigmaEtaEta) flagbkg = 1;           // High SIEIE as Bkg

        switch(sys_index){
            case kData:         
            case kPhoPurity:    if(!flagsig && !flagbkg) continue; break;
            default:            
                                if(!flagsig) continue; 
                                if(pho_genMatchedIndex<0) continue;
                                if(abs(mcPID)!=22) continue;
        }
        
        //* Jet Loop----------------------------------------------------------------------------------
            // std::vector<int>   vec_jet_index=-1;
            int   jet_index=-1;
            int   jet_true_index=-1;
            int   jet_true_index_gen=-1;
            float jet_pt_max=-1;
            float jet_true_pt_max=-1;
            float jet_true_pt_gen=-1;
            float jet_dphi_max=-1;
            float jet_xJ_max=-1;
            float jet_true_xJ_max=-1;
            float jet_true_xJ_gen=-1;
            float jet_Rg_max=-1;
            float jet_true_Rg_max=-1;
            float jet_true_Rg_gen=-1;   

            for(int igen=0; igen<nallgen;igen++){
                if(allgeneta[igen]<-1.39 && allgenphi[igen]<-0.9 && allgenphi[igen]>-1.6 ) continue; // HEM Failure
                if(fabs(allgeneta[igen])>2) continue;
                float true_xJ = -1;
                true_xJ = allgenpt[igen]/mcEt;// /phoEtCorrected; //mcEt;

                float dEta = allgeneta[igen] - phoEta; // -mcEta;
                float dphi = abs(TVector2::Phi_mpi_pi(phoPhi-allgenphi[igen])); // mcPhi

                if(dphi>2*TMath::Pi()/3){
                    if(jet_true_pt_gen<allgenpt[igen]){
                        jet_true_pt_gen = allgenpt[igen];
                        jet_true_index_gen = igen;    
                        jet_true_xJ_gen = true_xJ; 
                        jet_true_Rg_gen = allgenrg[igen];                     
                    }
                }

            }         
        
            for(int ijet=0; ijet<nref;ijet++){
                float jetPtCorrected = jtpt[ijet];

                //* JER Uncertainty
                    JME::JetParameters parameters_1;
                    double sf = 1;
                    float corr_sf = 1.0;
                //* JEC Uncertainty
                    double jtpt_unc = 0;     
                    double jtpt_corr = 1; 
                switch(sys_index){
                    case kData:
                    case kPhoPurity:    break;
                    case kJECup:          
                                jecUnc->setJetEta(jteta[ijet]);
                                jecUnc->setJetPt(jtpt[ijet]);
                                jtpt_unc = jecUnc->getUncertainty(true);
                                jtpt_corr = 1+( 1*jtpt_unc);
                                jetPtCorrected *= jtpt_corr;

                                parameters_1.setJetPt(refpt[ijet]);
                                parameters_1.setJetEta(jteta[ijet]);
                                parameters_1.setRho(rho);
                                sf = resolution_sf.getScaleFactor(parameters_1);
                                if(sf<=1) sf=1.0;                                
                                corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/refpt[ijet])))*std::sqrt(sf*sf-1);
                                jetPtCorrected *=corr_sf;     
                                break;
                    case kJECdown:      
                                jecUnc->setJetEta(jteta[ijet]);
                                jecUnc->setJetPt(jtpt[ijet]);
                                jtpt_unc = jecUnc->getUncertainty(true);
                                jtpt_corr = 1+(-1*jtpt_unc);
                                jetPtCorrected *= jtpt_corr;

                                parameters_1.setJetPt(refpt[ijet]);
                                parameters_1.setJetEta(jteta[ijet]);
                                parameters_1.setRho(rho);
                                sf = resolution_sf.getScaleFactor(parameters_1);
                                if(sf<=1) sf=1.0;
                                corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/refpt[ijet])))*std::sqrt(sf*sf-1);
                                jetPtCorrected *=corr_sf; 
                                break;
                    case kJERup:
                                parameters_1.setJetPt(refpt[ijet]);
                                parameters_1.setJetEta(jteta[ijet]);
                                parameters_1.setRho(rho);
                                sf = resolution_sf.getScaleFactor(parameters_1,Variation::UP);
                                if(sf<=1) sf=1.0;
                                corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/refpt[ijet])))*std::sqrt(sf*sf-1);
                                jetPtCorrected *=corr_sf; 
                                break;
                    case kJERdown:
                                parameters_1.setJetPt(refpt[ijet]);
                                parameters_1.setJetEta(jteta[ijet]);
                                parameters_1.setRho(rho);
                                sf = resolution_sf.getScaleFactor(parameters_1,Variation::DOWN);
                                if(sf<=1) sf=1.0;
                                corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/refpt[ijet])))*std::sqrt(sf*sf-1);
                                jetPtCorrected *=corr_sf; 
                                break;
                    default:    // All MC apply nominal JER
                                parameters_1.setJetPt(refpt[ijet]);
                                parameters_1.setJetEta(jteta[ijet]);
                                parameters_1.setRho(rho);
                                sf = resolution_sf.getScaleFactor(parameters_1);
                                if(sf<=1) sf=1.0;
                                corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/refpt[ijet])))*std::sqrt(sf*sf-1);
                                jetPtCorrected *=corr_sf;
                                break;
                }
                
                //* Jet Conditions
                    if(jteta[ijet]<-1.39 && jtphi[ijet]<-0.9 && jtphi[ijet]>-1.6 ) continue; // HEM Failure
                    if(fabs(jteta[ijet])>2) continue;
                    float dEta = jteta[ijet] - phoEta;
                    float dphi = abs(TVector2::Phi_mpi_pi(phoPhi-jtphi[ijet]));// ROOT::Math::VectorUtil::Phi_mpi_pi(phoPhi,jtphi[ijet]);
                    float xJ = jetPtCorrected/phoEtCorrected;
                    float true_xJ = -1;
                    true_xJ = refpt[ijet]/mcEt;
                    if(dphi>2*TMath::Pi()/3){
                        if(jet_pt_max<jetPtCorrected){
                            jet_pt_max = jetPtCorrected;
                            jet_dphi_max = dphi;
                            jet_xJ_max = xJ;
                            jet_true_xJ_max = true_xJ;
                            jet_Rg_max = jtrg[ijet];
                            jet_true_Rg_max = refrg[ijet];
                            jet_index = ijet;
                            
                        }
                        if(jet_true_pt_max<jetPtCorrected){
                            jet_true_pt_max = jetPtCorrected;
                            jet_true_index = ijet;                        
                        }
                    }
                
            }
            if(jet_index==-1) continue;
            if(jet_true_Rg_gen<=0) jet_true_Rg_gen = -0.025;
            if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
            if(jet_Rg_max<=0) jet_Rg_max = -0.025;
        
        //* Event Weights
        scale =1.0;
        switch(sys_index){
            case kData:
            case kPhoPurity:    scale = 1.0; break;
            case kAltMC:         
                    if(!(refparton_flavor[jet_index]>-9 && refparton_flavor[jet_index]<9)) scale*= (1-fit_qg)/(1-orig_qg);          // Not Quark  
                    if(refparton_flavor[jet_index]>-9 && refparton_flavor[jet_index]<9)    scale*= fit_qg/orig_qg;                  // Quark Only 
            default:scale*=weight*weight_pthat*weight_cent;
        }
        

        //* Output Filling

            if(flagsig) flagsig = 1;
            else if(flagbkg) flagsig = 0;
            
            var_jet_index   = jet_index;
            var_weight      = scale;
            var_flagsig     = flagsig;
            var_pho_purity  = purity_value;
            var_phoEt       = phoEtCorrected;
            var_mcEt        = mcEt;
            var_jetpt_det   = jet_pt_max;
            var_jetpt_true  = refpt[jet_index];
            var_xJ_det      = jet_xJ_max;
            var_xJ_true     = jet_true_xJ_max;
            var_Rg_det      = jet_Rg_max;
            var_Rg_true     = jet_true_Rg_max;
            var_girth_det   = jtangu[jet_index];
            var_girth_true  = refangu[jet_index];
            
            var_gen_jet_index   = allgenmatchindex[jet_true_index_gen];
            var_gen_jetpt_true  = allgenpt[jet_true_index_gen];
            var_gen_xJ_true     = jet_true_xJ_gen;
            var_gen_Rg_true     = jet_true_Rg_gen;
            var_gen_girth_true  = allgenangu[jet_true_index_gen];
            sys_tree->Fill();

        if(flagsig) ++count;

        
    }
    std::cout<<"Number of Selected Events in "<<sys_label[sys_index]<<"  = "<<count<<std::endl;
    fout->cd();
    sys_tree->Write("",TObject::kWriteDelete);
}

void skim_sys_PbPb(){
    label += Form("_%.0f_%.0f",min_cent_val,max_cent_val);
    fout = new TFile(output_path + "/Output_"+label+".root", "recreate");
    std::cout<<"\nOutput File : "<<output_path+ "/Output_"+label+".root" <<"  created \n";

    in_file="Data_2018_jets";
    loop_sys(kData);
    in_file = "QCDPhoton_jets";//"QCDPhoton_jets";
    loop_sys(kNominal);
    
    in_file = "Data_2018_jets";
    loop_sys(kPhoPurity);
    in_file = "QCDPhoton_jets";
    loop_sys(kJERup);
    loop_sys(kJERdown);
    loop_sys(kJECup);
    loop_sys(kJECdown);
    loop_sys(kCentup);
    loop_sys(kCentdown);
    in_file = "Substructure_up_jets_FULL";
    loop_sys(kPFScaleup);
    in_file = "Substructure_down_jets_FULL"; 
    loop_sys(kPFScaledown);
    in_file = "QCDPhoton_jets";
    loop_sys(kAltMC);

    printf("\n");
    fout->Close();
}