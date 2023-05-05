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

TString label="May_3_pp_2017_WP_update"; // "Substructure_up_jets";//"QCDPhoton_jets"; // "Data_2018_jets";//
TString output_path = "Uncertainty";//"./OutputPlots/Skimsys/"; // Uncertainty/ OutputPlots
TString in_file="QCDPhoton_jets";
TFile *fout;

// namespace MyEnum{
    enum SystematicsTreatment_pp {       // Systematics treatment
        kData       =0,               //* Nominal PbPb 2018 Data 
        kNominal    =1,               //* Nominal Pythia8 (centrality +4.5%)  
        kPhoPurity  =2,               //* ABCD Photon Purity Data 
        kJERup      =3,               //* Pythia8 with JER up 
        kJERdown    =4,               //* Pythia8 with JER down 
        kJECup      =5,               //* Pythia8 with JEC up 
        kJECdown    =6,               //* Pythia8 with JEC down 
        kPFScaleup  =7,               //* Pythia8 with +1% PF scale substructure 
        kPFScaledown=8,               //* Pythia8 with -1% PF scale substructure 
        kAltMC      =9                //* HERWIG7 
    };
    
    static const SystematicsTreatment_pp sys_list[] =  
    {
        kData       ,
        kNominal    ,
        kPhoPurity  ,
        kJERup      ,
        kJERdown    ,
        kJECup      ,
        kJECdown    ,
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
        "PFScale_up"    ,
        "PFScale_down"  ,
        "AltMC"      
    };
// }

void loop_sys(SystematicsTreatment_pp sys_index){
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

        Float_t pthat=0;
        Int_t   HLT_HIPhoton40_HoverELoose_v1 = 0;
        Int_t   HLT_HISinglePhoton40_Eta1p5ForPPRef_v8 = 0;

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

        jet_tree.SetBranchAddress("eleRej",&eleRej);

        jet_tree.SetBranchAddress("HLT_HIPhoton40_HoverELoose_v1",&HLT_HIPhoton40_HoverELoose_v1);
        jet_tree.SetBranchAddress("HLT_HISinglePhoton40_Eta1p5ForPPRef_v8",&HLT_HISinglePhoton40_Eta1p5ForPPRef_v8);

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
        const float cut_HoverE = 0.009732;    
        const float cut_SIEIE  = 0.009905;    
        const float cut_SumIso = -0.014755;   
        const float min_xJ = 0.4;         
        float purity_value = 1.0;   // Photon Purity 
        
        JetCorrectionUncertainty *jecUnc ;   
        switch(sys_index){
            case kData:      purity_value = 0.934517;      break;
            case kPhoPurity: purity_value = 0.91148;      break;
            case kJECup:
            case kJECdown:            
                jecUnc = new JetCorrectionUncertainty("/grid_mnt/vol_home/llr/cms/bharikri/Projects/ppHiForest/CMSSW_9_4_10/src/HeavyIonsAnalysis/JetAnalysis/test/Analysis/Uncertainty/JEC/Spring18_ppRef5TeV_V4_MC_Uncertainty_AK2PF.txt");
                break;
            default: break;
        }

        JME::JetResolution resolution ; //this is for the case where the det-level jet is not matched to a truth-level jet
        resolution = JME::JetResolution("/grid_mnt/vol_home/llr/cms/bharikri/Projects/ppHiForest/CMSSW_9_4_10/src/HeavyIonsAnalysis/JetAnalysis/test/Analysis/Uncertainty/JER/Fall17_V3b_MC_PtResolution_AK4PF.txt");
        
        JME::JetResolutionScaleFactor resolution_sf ; //this is for the case where the det-level jet is matched to a truth-level jet
        resolution_sf = JME::JetResolutionScaleFactor("/grid_mnt/vol_home/llr/cms/bharikri/Projects/ppHiForest/CMSSW_9_4_10/src/HeavyIonsAnalysis/JetAnalysis/test/Analysis/Uncertainty/JER/Fall17_V3b_MC_SF_AK4PF.txt");


    // -------- End Constants
    // ----------------------------------------------------------------------------------------------------------------
    // Event Loop
    int count = 0;
   
    for(int iEntry=0; iEntry<jet_tree.GetEntries(); iEntry++){ 
        jet_tree.GetEntry(iEntry);
        float scale =1.0;

        //* Photon Conditions
            if(phoSCEta<-1.39 && phoPhi<-0.9 && phoPhi>-1.6) continue;         
            if(!(fabs(phoSCEta)<1.442)) continue;
            if(!(phoEtCorrected>min_pho_et)) continue;
            if(!HLT_HIPhoton40_HoverELoose_v1) continue;

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
                // if(allgeneta[igen]<-1.39 && allgenphi[igen]<-0.9 && allgenphi[igen]>-1.6 ) continue; // HEM Failure
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

                                parameters_1.setJetPt(jetPtCorrected);
                                parameters_1.setJetEta(jteta[ijet]);
                                parameters_1.setRho(rho);
                                sf = resolution_sf.getScaleFactor(parameters_1);
                                if(sf<=1) sf=1.0;                                
                                corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/jetPtCorrected)))*std::sqrt(sf*sf-1);
                                jetPtCorrected *=corr_sf;     
                                break;
                    case kJECdown:      
                                jecUnc->setJetEta(jteta[ijet]);
                                jecUnc->setJetPt(jtpt[ijet]);
                                jtpt_unc = jecUnc->getUncertainty(true);
                                jtpt_corr = 1+(-1*jtpt_unc);
                                jetPtCorrected *= jtpt_corr;

                                parameters_1.setJetPt(jetPtCorrected);
                                parameters_1.setJetEta(jteta[ijet]);
                                parameters_1.setRho(rho);
                                sf = resolution_sf.getScaleFactor(parameters_1);
                                if(sf<=1) sf=1.0;
                                corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/jetPtCorrected)))*std::sqrt(sf*sf-1);
                                jetPtCorrected *=corr_sf; 
                                break;
                    case kJERup:
                                parameters_1.setJetPt(jetPtCorrected);
                                parameters_1.setJetEta(jteta[ijet]);
                                parameters_1.setRho(rho);
                                sf = resolution_sf.getScaleFactor(parameters_1,Variation::UP);
                                if(sf<=1) sf=1.0;
                                corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/jetPtCorrected)))*std::sqrt(sf*sf-1);
                                jetPtCorrected *=corr_sf; 
                                break;
                    case kJERdown:
                                parameters_1.setJetPt(jetPtCorrected);
                                parameters_1.setJetEta(jteta[ijet]);
                                parameters_1.setRho(rho);
                                sf = resolution_sf.getScaleFactor(parameters_1,Variation::DOWN);
                                if(sf<=1) sf=1.0;
                                corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/jetPtCorrected)))*std::sqrt(sf*sf-1);
                                jetPtCorrected *=corr_sf; 
                                break;
                    default:    // All MC apply nominal JER
                                parameters_1.setJetPt(jetPtCorrected);
                                parameters_1.setJetEta(jteta[ijet]);
                                parameters_1.setRho(rho);
                                sf = resolution_sf.getScaleFactor(parameters_1);
                                if(sf<=1) sf=1.0;
                                corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/jetPtCorrected)))*std::sqrt(sf*sf-1);
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
            default:scale*=weight*weight_pthat;
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

void skim_sys_pp(){
    fout = new TFile(output_path + "/Output_"+label+".root", "recreate");
    std::cout<<"\nOutput File : "<<output_path+ "/Output_"+label+".root" <<"  created \n";

    in_file="pp_Data_2017_jets";
    loop_sys(kData);
    in_file = "pp_QCDPhoton_jets";
    loop_sys(kNominal);
    
    in_file = "pp_Data_2017_jets";
    loop_sys(kPhoPurity);
    in_file = "pp_QCDPhoton_jets";
    loop_sys(kJERup);
    loop_sys(kJERdown);
    loop_sys(kJECup);
    loop_sys(kJECdown);
    in_file = "pp_Substructure_up_jets";
    loop_sys(kPFScaleup);
    in_file = "pp_Substructure_down_jets";
    loop_sys(kPFScaledown);
    in_file = "pp_Herwig7_jets";
    loop_sys(kAltMC);

    printf("\n");
    fout->Close();
}