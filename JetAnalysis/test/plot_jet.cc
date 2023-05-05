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

std::vector<int> min_cent_val = { 0,  60,   0,  0,  40};
std::vector<int> max_cent_val = {60, 180, 180, 40, 180};


std::vector<int> min_cent = { 9,  69,   9,  9,  49};   // MC Centrality nominal
std::vector<int> max_cent = {69, 189, 189, 49, 189};
// std::vector<int> min_cent = {12,  72,  12, 12,  52};   // MC Centrality up
// std::vector<int> max_cent = {72, 192, 192, 52, 192};
// std::vector<int> min_cent = { 6,  66,   6,  6,  56};   // MC Centrality down
// std::vector<int> max_cent = {66, 186, 186, 56, 196};
// std::vector<int> min_cent = { 0,  60,   0,  0,  40};
// std::vector<int> max_cent = {60, 180, 180, 40, 180};
const std::size_t ncent = 5;//min_cent.size();
TString label="Data_2018_jets"; // "Substructure_up_jets";//"QCDPhoton_jets"; // "Data_2018_jets";//
TString output_path = "./OutputPlots/"; // Uncertainty/ OutputPlots

std::vector<double> rho_weight = {0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.1237833 ,0.2448678 ,0.4851410 ,0.5496915 ,0.5527335 ,0.5450190 ,0.5239799 ,0.5008505 ,0.5195929 ,0.5332869 ,0.5166109 ,0.5155024 ,0.5280507 ,0.6157440 ,1.0460693 ,1.5848926 ,1.6505300 ,1.6796490 ,1.6854259 ,1.7155044 ,1.7169375 ,1.6923578 ,1.7101517 ,1.7219163 ,1.7913101 ,2.0315394 ,3.3030708 ,9.9789515 ,69.3535614 ,766.6729736 ,208048.4375000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,0.0000000};
std::vector<double> vz_weight = {1.5167011 ,0.8576906 ,0.9099118 ,1.1778998 ,1.1266822 ,0.9996321 ,1.3267114 ,1.2380642 ,1.2732384 ,1.2615132 ,1.2169536 ,1.2407824 ,1.2066655 ,1.1912715 ,1.1439103 ,1.1035628 ,1.0853250 ,1.0363530 ,1.0335017 ,1.0064293 ,0.9933138 ,0.9838185 ,0.9721337 ,0.9481471 ,0.9393314 ,0.9090054 ,0.9006600 ,0.8941706 ,0.8812072 ,0.8448598 ,0.8381445 ,0.7948514 ,0.7870941 ,0.7165342 ,0.6406508 ,0.7594909 ,0.7076170 ,0.6397762 ,0.5146740 ,0.6004016 ,0.4577079};
std::vector<double> jetpt_weight = {0.0000000 ,0.0000000 ,0.0000000 ,0.0000000 ,1.9292705 ,1.9929389 ,1.5985236 ,1.3182900 ,1.0951819 ,0.9843343 ,0.8907351 ,0.7211941 ,0.7355317 ,0.6352192 ,0.8126823 ,0.6404173 ,0.7543695 ,0.6968250 ,0.7909313 ,0.7813836 ,0.8726654 ,0.5983925 ,0.7458980 ,0.7350793 ,0.7360337 ,0.7237559};
void Plot_hist(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void Plot_hist2D(std::vector<TH2D*> hist,std::vector<TString> histname,TString dopt="colz",std::vector<TString> eopt={"end"});

void overlay(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void plot_jet(){
    gROOT->SetBatch();
    gErrorIgnoreLevel = kFatal;
    TString DIR = output_path + "OutputPlots_"+label+"/";
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    // ----------------------------------------------------------------------------------------------------------------
    //Tree Variable Declaration

        TChain jet_tree("jet_tree");
        jet_tree.Add(label+".root/jet_tree");

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
    // Histograms
        TH1::SetDefaultSumw2();
        TH2::SetDefaultSumw2();
        TTree *tree_xj_Rg,*tree_xj_angu,*tree_xj_dynkt;
        tree_xj_Rg = new TTree("tree_xj_Rg","tree_xj_Rg");
        Float_t var_xJ_det = 0;
        Float_t var_Rg_det = 0;
        Float_t var_angu_det = 0;
        Float_t var_dynkt_det = 0;

        Float_t var_xJ_true = 0;
        Float_t var_Rg_true = 0;
        Float_t var_angu_true = 0;
        Float_t var_dynkt_true = 0;

        Float_t var_hiBin = 0;
        Float_t var_phoEtCorrected = 0;
        Float_t var_weightFinal = 0;

        tree_xj_Rg->Branch("xJ_det", &var_xJ_det);
        tree_xj_Rg->Branch("Rg_det", &var_Rg_det);
        tree_xj_Rg->Branch("angu_det", &var_angu_det);
        tree_xj_Rg->Branch("dynkt_det", &var_dynkt_det);
        tree_xj_Rg->Branch("xJ_true", &var_xJ_true);
        tree_xj_Rg->Branch("Rg_true", &var_Rg_true);
        tree_xj_Rg->Branch("angu_true", &var_angu_true);
        tree_xj_Rg->Branch("dynkt_true", &var_dynkt_true);
        tree_xj_Rg->Branch("hiBin", &var_hiBin);
        tree_xj_Rg->Branch("phoEtCorrected", &var_phoEtCorrected);
        tree_xj_Rg->Branch("weightFinal", &var_weightFinal);

        tree_xj_angu = new TTree("tree_xj_angu","tree_xj_angu");

        tree_xj_angu->Branch("xJ_det", &var_xJ_det);
        tree_xj_angu->Branch("Rg_det", &var_Rg_det);
        tree_xj_angu->Branch("angu_det", &var_angu_det);
        tree_xj_angu->Branch("dynkt_det", &var_dynkt_det);
        tree_xj_angu->Branch("xJ_true", &var_xJ_true);
        tree_xj_angu->Branch("Rg_true", &var_Rg_true);
        tree_xj_angu->Branch("angu_true", &var_angu_true);
        tree_xj_angu->Branch("dynkt_true", &var_dynkt_true);
        tree_xj_angu->Branch("hiBin", &var_hiBin);
        tree_xj_angu->Branch("phoEtCorrected", &var_phoEtCorrected);
        tree_xj_angu->Branch("weightFinal", &var_weightFinal);

        tree_xj_dynkt = new TTree("tree_xj_dynkt","tree_xj_dynkt");

        tree_xj_dynkt->Branch("xJ_det", &var_xJ_det);
        tree_xj_dynkt->Branch("Rg_det", &var_Rg_det);
        tree_xj_dynkt->Branch("angu_det", &var_angu_det);
        tree_xj_dynkt->Branch("dynkt_det", &var_dynkt_det);
        tree_xj_dynkt->Branch("xJ_true", &var_xJ_true);
        tree_xj_dynkt->Branch("Rg_true", &var_Rg_true);
        tree_xj_dynkt->Branch("angu_true", &var_angu_true);
        tree_xj_dynkt->Branch("dynkt_true", &var_dynkt_true);
        tree_xj_dynkt->Branch("hiBin", &var_hiBin);
        tree_xj_dynkt->Branch("phoEtCorrected", &var_phoEtCorrected);
        tree_xj_dynkt->Branch("weightFinal", &var_weightFinal);

        // True Plots
        TH1D* h_true_pho_Et[ncent];
        TH1D* h_true_jet_pt[ncent];
        TH1D* h_true_xJ[ncent];
        TH1D* h_true_Rg[ncent];
        TH1D* h_true_angu[ncent];

        // ----

        TH1D* hweight[ncent];
        TH1D* hweight_q[ncent];
        TH1D* hweight_g[ncent];
        TH1D* hnPho[ncent];
        TH1D* hnPhosel[ncent];
        TH1D* hnJet[ncent];

        TH2D* h_jetpt_weight[ncent];
        TH2D* h_angu_weight[ncent];
        TH2D* h_Rg_weight[ncent];
        TH2D* h_jetpt_angu[ncent];

        TH2D* h_weight_rho[ncent];

        TH1D* hHibin[ncent];
        TH1D* hrho[ncent];
        TH1D* hvz[ncent];

        TH2D* h_eta_phi_gamma[ncent];
        TH2D* h_eta_phi_jet[ncent];

        TH1D* h_jet_pt[ncent];
        TH1D* h_jet_eta[ncent];
        TH1D* h_jet_phi[ncent];

        TH1D* hres_jetpt[ncent];
        TH1D* hres_xJ[ncent];
        TH1D* hres_Rg[ncent];
        TH1D* hres_angu[ncent];
        
        TH1D* hdphi_all[ncent];
        TH1D* hxJ_all[ncent];
        TH1D* hRg_all[ncent];
        TH1D* hangu_all[ncent];
        TH1D* hktdyn_all[ncent];

        TH1D* hdphi_lead[ncent];
        TH1D* hxJ_lead[ncent];
        TH1D* hRg_lead[ncent];
        TH1D* hangu_lead[ncent];
        TH1D* hktdyn_lead[ncent];
        TH1D* hzg_lead[ncent];
        TH1D* hrefparton_lead[ncent];

        TH1D* hxJ_lead_true[ncent];
        TH1D* hRg_lead_true[ncent];
        TH1D* hangu_lead_true[ncent];
        TH1D* hktdyn_lead_true[ncent];
        TH1D* hzg_lead_true[ncent];

        TH2D* h_Rg_xJ[ncent];
        TH2D* h_angu_xJ[ncent];
        TH2D* h_ktdyn_xJ[ncent];
        // TH2D* h_lnktdyn_xJ[ncent]; ln kt for later?

        TH2D* h_xJ_xJ[ncent];
        TH2D* h_Rg_Rg[ncent];
        TH2D* h_angu_angu[ncent];
        TH2D* h_ktdyn_ktdyn[ncent];

        TH2D* h_xJ_l0p4_Rg_Rg[ncent];
        TH2D* h_xJ_l0p4_angu_angu[ncent];
        TH2D* h_xJ_l0p4_dynkt_dynkt[ncent];
        TH2D* h_xJ_g0p4_Rg_Rg[ncent];
        TH2D* h_xJ_g0p4_angu_angu[ncent];
        TH2D* h_xJ_g0p4_dynkt_dynkt[ncent];

        TH2D* h_jetpt_recogen[ncent];
        TH2D* h_jeteta_recogen[ncent];

        TH1D* hbkg_jet_pt[ncent];
        TH1D* hbkg_jet_eta[ncent];
        TH1D* hbkg_jet_phi[ncent];

        TH1D* hbkg_nPhosel[ncent];
        TH1D* hbkg_nJet[ncent];

        TH1D* hbkg_xJ_all[ncent];
        TH1D* hbkg_Rg_all[ncent];
        TH1D* hbkg_angu_all[ncent];
        TH1D* hbkg_ktdyn_all[ncent];

        TH1D* hbkg_xJ_lead[ncent];
        TH1D* hbkg_Rg_lead[ncent];
        TH1D* hbkg_angu_lead[ncent];
        TH1D* hbkg_ktdyn_lead[ncent];
        TH1D* hbkg_zg_lead[ncent];

        // Unfolding Plots

        TH2D* h_Rg_xJ_det[ncent];
        TH2D* h_Rg_xJ_mc_true[ncent];
        TH2D* h_Rg_xJ_mc_truef[ncent];
        TH2D* h_Rg_xJ_eff_match_num[ncent];
        TH2D* h_Rg_xJ_eff_match_den[ncent];
        TH2D* h_Rg_xJ_pur_num[ncent];
        TH2D* h_Rg_xJ_pur_den[ncent];

        TH2D* hbkg_Rg_xJ_det[ncent];

        TH2D* h_angu_xJ_det[ncent];
        TH2D* h_angu_xJ_mc_true[ncent];
        TH2D* h_angu_xJ_mc_truef[ncent];
        TH2D* h_angu_xJ_pur_num[ncent];
        TH2D* h_angu_xJ_pur_den[ncent];

        TH2D* hbkg_angu_xJ_det[ncent];
        
        TH2D* h_dynkt_xJ_det[ncent];
        TH2D* h_dynkt_xJ_mc_true[ncent];
        TH2D* h_dynkt_xJ_mc_truef[ncent];

        TH2D* hbkg_dynkt_xJ_det[ncent];

        // inputs for Unfolding 
            const int bin_det_xj  = 1;
            const int bin_true_xj = 2;//2;
            const int bin_det_Rg =     5;// 9;// 9;//6;// 5;
            const int bin_true_Rg =    6;// 9;// 9;//6;// 6;
            const int bin_det_angu =   5;//10;// 8;//5;// 5;
            const int bin_true_angu =  6;// 5;// 8;//5;// 6;
            const int bin_det_dynkt=3;
            const int bin_true_dynkt=5;

            Double_t xjmin_det=0.4;
            Double_t xjmin_true=0.0;//0.0;

            Double_t xjmax_det=3;
            Double_t xjmax_true=3;

            Double_t Rgmax_det=0.2;
            Double_t Rgmax_true=0.3;
            
            Double_t Rgmin_det=-0.05;
            Double_t Rgmin_true=-0.05;

            Double_t angumax_det=0.1;
            Double_t angumax_true=0.3;
            
            Double_t angumin_det=0.;
            Double_t angumin_true=0.;

            Double_t dynktmax_det=10.0;
            Double_t dynktmax_true=50.0;
            
            Double_t dynktmin_det=1.5;
            Double_t dynktmin_true=0.;

            Double_t xJ_det_edges[bin_det_xj+1]   = {           xjmin_det,xjmax_det};
            Double_t xJ_true_edges[bin_true_xj+1] = {xjmin_true,xjmin_det,xjmax_true};
            Double_t Rg_det_edges[bin_det_Rg+1]   = {-0.05,0.00, 0.04, 0.08, 0.12, Rgmax_det};
            Double_t Rg_true_edges[bin_true_Rg+1] = {-0.05,0.00, 0.04, 0.08, 0.12, Rgmax_det, Rgmax_true};
            // Double_t Rg_det_edges[bin_det_Rg+1] = {-0.05,Rgmin_det, 0.03, 0.06, 0.1, 0.14, Rgmax_det};
            // Double_t Rg_true_edges[bin_true_Rg+1] = {-0.05,Rgmin_true, 0.03, 0.06, 0.1, 0.14, 0.2, Rgmax_true};
            // Double_t angu_det_edges[bin_det_angu+1] = {angumin_det, 0.025, 0.035, 0.045, 0.055, 0.07, angumax_det};
            // Double_t angu_true_edges[bin_true_angu+1] = {angumin_true, 0.025, 0.035, 0.045, 0.055, 0.07, 0.1, angumax_true};
            Double_t angu_det_edges[bin_det_angu+1]   = {angumin_det, 0.02, 0.04, 0.06, 0.08, angumax_det};
            Double_t angu_true_edges[bin_true_angu+1] = {angumin_det, 0.02, 0.04, 0.06, 0.08, angumax_det, angumax_true};//{angumin_true, 0.02, 0.04, 0.06, 0.08, 0.1, angumax_true};
            Double_t dynkt_det_edges[bin_det_dynkt+1] = {dynktmin_det, 2.5,4.0,dynktmax_det};
            Double_t dynkt_true_edges[bin_true_dynkt+1] = {dynktmin_true, 1.5,2.5,4.0,10.0,dynktmax_true};
        
        const Int_t nkt_bins = 8;
        Double_t kt_edges[nkt_bins+1] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 8.0, 12.0, 20.0};

        for (std::size_t i = 0; i < ncent; ++i) {
            int nbins = 20;
            h_true_pho_Et[i] = new TH1D(Form("h_true_pho_Et_%zu", i), Form("h_true_pho_Et_%zu;True #gamma E_{T};Norm. Events", i), 50, 100, 300);
            h_true_jet_pt[i] = new TH1D(Form("h_true_jet_pt_%zu", i), Form("h_true_jet_pt_%zu;True Recoil Jet p_{T};Norm. Events", i), 50, 30, 200);
            h_true_xJ[i] = new TH1D(Form("h_true_xJ_%zu", i), Form("h_true_xJ_%zu;True x_{J};Norm. Events", i), 40, 0, 2);
            h_true_Rg[i] = new TH1D(Form("h_true_Rg_%zu", i), Form("h_true_Rg_%zu;True R_{g};Norm. Events", i),bin_true_Rg,Rg_true_edges);//20, 0.0001, 0.25);
            h_true_angu[i] = new TH1D(Form("h_true_angu_%zu", i), Form("h_true_angu_%zu;True Angularity;Norm. Events", i),bin_true_angu,angu_true_edges);//20, 0, 0.12);

            hweight[i] = new TH1D(Form("hweight_%zu", i), Form("hweight_%zu;hweight;Norm. Events", i), 1, 0, 99999);
            hweight_q[i] = new TH1D(Form("hweight_q_%zu", i), Form("hweight_q_%zu;hweight_q;Norm. Events", i), 1, 0, 99999);
            hweight_g[i] = new TH1D(Form("hweight_g_%zu", i), Form("hweight_g_%zu;hweight_g;Norm. Events", i), 1, 0, 99999);

            h_jetpt_weight[i]=new TH2D(Form("h_jetpt_weight_%zu",i),Form("h_jetpt_weight_%zu;Jet pT;Event weights",i),25, 0, 250,50,0,2000.0);
            h_angu_weight[i]=new TH2D(Form("h_angu_weight_%zu",i),Form("h_angu_weight_%zu;Angularity;Event weights",i),nbins, 0, 0.12,50,0,2000.0);
            h_Rg_weight[i]=new TH2D(Form("h_Rg_weight_%zu",i),Form("h_Rg_weight_%zu;R_{g};Event weights",i),nbins, 0.0001, 0.25,50,0,2000.0);
            h_jetpt_angu[i]=new TH2D(Form("h_jetpt_angu_%zu",i),Form("h_jetpt_angu_%zu;Jet pT;Angularity",i),25, 0, 250,nbins, 0, 0.12);

            h_weight_rho[i] = new TH2D(Form("h_weight_rho_%zu", i), Form("h_weight_rho_%zu;rho;Event weights", i), 50, 0, 250,50,0,2000.0);

            hnPho[i] = new TH1D(Form("hnPho_%zu", i), Form("hnPho_%zu;nPho;Norm. Events", i), 1, 0, 2);
            hnPhosel[i] = new TH1D(Form("hnPhosel_%zu", i), Form("hnPhosel_%zu;nPho;Norm. Events", i), 1, 0, 2);
            hnJet[i] = new TH1D(Form("hnJet_%zu", i), Form("hnJet_%zu;nJet;Norm. Events", i), 1, 0, 2);

            hHibin[i] = new TH1D(Form("hHibin_%zu", i), Form("hHibin_%zu;hiBin;Norm. Events", i), 200, 0, 200);
            hrho[i] = new TH1D(Form("hrho_%zu", i), Form("hrho_%zu;rho;Norm. Events", i), 50, 0, 250);
            hvz[i] = new TH1D(Form("hvz_%zu", i), Form("hrho_%zu;vz;Norm. Events", i), 40, -20, 20);

            h_eta_phi_gamma[i]=new TH2D(Form("h_eta_phi_gamma_%zu",i),Form("h_eta_phi_gamma_%zu;#gamma #eta;#gamma #phi",i),50,-1.44,1.44,30,-3.14,3.14);
            h_eta_phi_jet[i]=new TH2D(Form("h_eta_phi_jet_%zu",i),Form("h_eta_phi_jet_%zu;Leading Jet #eta;Leading #phi",i),50,-2.0,2.0,30,-3.14,3.14);

            // Double_t jet_pt_edges[23] = {40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,150,170,190,220,250,300,400};

            h_jetpt_recogen[i] = new TH2D(Form("h_jetpt_recogen_%zu",i),Form("h_jetpt_recogen_%zu;Reco Jet p_{T} (GeV);#frac{Reco Jet p_{T}}{Gen Jet p_{T}}",i),25, 0, 250,30,0,1.5);
            h_jeteta_recogen[i] = new TH2D(Form("h_jeteta_recogen_%zu",i),Form("h_jeteta_recogen_%zu;Reco Jet #eta;#frac{Reco Jet p_{T}}{Gen Jet p_{T}}",i),50, -2.0, 2.0,30,0,1.5);

            h_jet_pt[i] = new TH1D(Form("h_jet_pt_%zu", i), Form("h_jet_pt_%zu;Recoil Jet p_{T};Norm. Events", i),25, 0, 250);//22,jet_pt_edges); //25, 0, 250);
            h_jet_eta[i] = new TH1D(Form("h_jet_eta_%zu", i), Form("h_jet_eta_%zu;Recoil Jet #eta;Norm. Events", i), 50, -2.0, 2.0);
            h_jet_phi[i] = new TH1D(Form("h_jet_phi_%zu", i), Form("h_jet_phi_%zu;Recoil Jet #phi;Norm. Events", i), 30, -3.14, 3.14);

            hres_jetpt[i] = new TH1D(Form("hres_jetpt_%zu", i), Form("hres_jetpt_%zu;(Jet Reco p_{T} - True p_{T})/True p_{T};Events", i), 64, -1, 1);
            hres_xJ[i] = new TH1D(Form("hres_xJ_%zu", i), Form("hres_xJ_%zu;(Reco x_{J} - True x_{J})/True x_{J};Events", i), 64, -1, 1);
            hres_Rg[i] = new TH1D(Form("hres_Rg_%zu", i), Form("hres_Rg_%zu;(Reco R_{g} - True R_{g})/True R_{g};Events", i), 64, -1, 1);
            hres_angu[i] = new TH1D(Form("hres_angu_%zu", i), Form("hres_angu_%zu;(Reco Angu - True Angu)/True Angu;Events", i), 64, -1, 1);

            hdphi_all[i] = new TH1D(Form("hdphi_all_%zu", i), Form("hdphi_all_%zu;#Delta #phi;Events", i), nbins, 0, 3.2);
            hxJ_all[i] = new TH1D(Form("hxJ_all_%zu", i), Form("hxJ_all_%zu;All Recoil Jet p_{T}/Photon E_{T};Events", i), nbins, 0, 2.0);
            hRg_all[i] = new TH1D(Form("hRg_all_%zu", i), Form("hRg_all_%zu;R_{g};Events", i), nbins, 0.0001, 0.25);
            hangu_all[i] = new TH1D(Form("hangu_all_%zu", i), Form("hangu_all_%zu;Angularity(girth);Events", i), nbins, 0, 0.12);
            hktdyn_all[i] = new TH1D(Form("hktdyn_all_%zu", i), Form("hktdyn_all_%zu;dyn k_{T};Events", i), nkt_bins, kt_edges);

            hdphi_lead[i] = new TH1D(Form("hdphi_lead_%zu", i), Form("hdphi_lead_%zu;#Delta #phi;1/N_{jet} dN/d#Delta #phi", i), nbins, 0, 3.2);
            hxJ_lead[i] = new TH1D(Form("hxJ_lead_%zu", i), Form("hxJ_lead_%zu;Lead Recoil Jet p_{T}/Photon E_{T};1/N_{jet} dN/dp_{T,Jet}", i), nbins, 0, 2.0);
            hRg_lead[i] = new TH1D(Form("hRg_lead_%zu", i), Form("hRg_lead_%zu;R_{g};1/N_{jet} dN/dR_{g}", i), nbins, 0.0001, 0.25);
            hangu_lead[i] = new TH1D(Form("hangu_lead_%zu", i), Form("hangu_lead_%zu;Angularity(girth);1/N_{jet} dN/dAngularity", i), nbins, 0, 0.12);
            hktdyn_lead[i] = new TH1D(Form("hktdyn_lead_%zu", i), Form("hktdyn_lead_%zu;dyn k_{T};1/N_{jet} dN/dk_{T}", i), nkt_bins, kt_edges);
            hrefparton_lead[i] = new TH1D(Form("hrefparton_lead_%zu", i), Form("hrefparton_lead_%zu;Ref Parton PID;Events", i),60,-29,30);
            hzg_lead[i] = new TH1D(Form("hzg_lead_%zu", i), Form("hzg_lead_%zu;zg;1/N_{jet} dN/dzg", i), nbins, 0.2, 0.51);

            hxJ_lead_true[i] = new TH1D(Form("hxJ_lead_true_%zu", i), Form("hxJ_lead_true_%zu;True Lead Recoil Jet p_{T}/Photon E_{T};1/N_{jet} dN/dp_{T,Jet}", i), nbins, 0, 2.0);
            hRg_lead_true[i] = new TH1D(Form("hRg_lead_true_%zu", i), Form("hRg_lead_true_%zu;True R_{g};1/N_{jet} dN/dR_{g}", i), nbins, 0.0001, 0.25);
            hangu_lead_true[i] = new TH1D(Form("hangu_lead_true_%zu", i), Form("hangu_lead_true_%zu;True Angularity(girth);1/N_{jet} dN/dAngularity", i), nbins, 0, 0.12);
            hktdyn_lead_true[i] = new TH1D(Form("hktdyn_lead_true_%zu", i), Form("hktdyn_lead_true_%zu;True dyn k_{T};1/N_{jet} dN/dk_{T}", i), nkt_bins, kt_edges);
            hzg_lead_true[i] = new TH1D(Form("hzg_lead_true_%zu", i), Form("hzg_lead_true_%zu;True zg;1/N_{jet} dN/dzg", i), nbins, 0.2, 0.51);

            h_Rg_xJ[i]=new TH2D(Form("h_Rg_xJ_%zu",i),Form("h_Rg_xJ_%zu;R_{g};x_{#gamma,jet}",i),18,0.0001,0.3,30,0,3.0);
            h_angu_xJ[i]=new TH2D(Form("h_angu_xJ_%zu",i),Form("h_angu_xJ_%zu;Angularity(girth);x_{#gamma,jet}",i),16,0,0.12,30,0,3.0);
            h_ktdyn_xJ[i]=new TH2D(Form("h_ktdyn_xJ_%zu",i),Form("h_ktdyn_xJ_%zu;dyn k_{T};x_{#gamma,jet}",i),20,0,20,30,0,3.0);

            h_xJ_xJ[i]=new TH2D(Form("h_xJ_xJ_%zu",i),Form("h_xJ_xJ_%zu;x_{#gamma,jet} Reco;x_{#gamma,jet} True",i),30,0,3.0,30,0,3.0);
            h_Rg_Rg[i]=new TH2D(Form("h_Rg_Rg_%zu",i),Form("h_Rg_Rg_%zu;R_{g} Reco;R_{g} True",i),18,0.0001,0.3,18,0.0001,0.3);
            h_angu_angu[i]=new TH2D(Form("h_angu_angu_%zu",i),Form("h_angu_angu_%zu;Angularity Reco;Angularity True",i),16,0,0.12,16,0,0.12);
            h_ktdyn_ktdyn[i]=new TH2D(Form("h_ktdyn_ktdyn_%zu",i),Form("h_ktdyn_ktdyn_%zu;dyn k_{T} Reco;dyn k_{T} True",i),20,0,20,20,0,20);

            h_xJ_l0p4_Rg_Rg[i]=new TH2D(Form("h_xJ_l0p4_Rg_Rg_%zu",i),Form("h_xJ_l0p4_Rg_Rg_%zu;R_{g} Reco;R_{g} True",i),bin_det_Rg,Rg_det_edges,bin_true_Rg,Rg_true_edges);
            h_xJ_l0p4_angu_angu[i]=new TH2D(Form("h_xJ_l0p4_angu_angu_%zu",i),Form("h_xJ_l0p4_angu_angu_%zu;Angularity Reco;Angularity True",i),bin_det_angu,angu_det_edges,bin_true_angu,angu_true_edges);
            h_xJ_l0p4_dynkt_dynkt[i]=new TH2D(Form("h_xJ_l0p4_dynkt_dynkt_%zu",i),Form("h_xJ_l0p4_dynkt_dynkt_%zu;dyn k_{T} Reco;dyn k_{T} True",i),bin_det_dynkt,dynkt_det_edges,bin_true_dynkt,dynkt_true_edges);

            h_xJ_g0p4_Rg_Rg[i]=new TH2D(Form("h_xJ_g0p4_Rg_Rg_%zu",i),Form("h_xJ_g0p4_Rg_Rg_%zu;R_{g} Reco;R_{g} True",i),bin_det_Rg,Rg_det_edges,bin_true_Rg,Rg_true_edges);
            h_xJ_g0p4_angu_angu[i]=new TH2D(Form("h_xJ_g0p4_angu_angu_%zu",i),Form("h_xJ_g0p4_angu_angu_%zu;Angularity Reco;Angularity True",i),bin_det_angu,angu_det_edges,bin_true_angu,angu_true_edges);
            h_xJ_g0p4_dynkt_dynkt[i]=new TH2D(Form("h_xJ_g0p4_dynkt_dynkt_%zu",i),Form("h_xJ_g0p4_dynkt_dynkt_%zu;dyn k_{T} Reco;dyn k_{T} True",i),bin_det_dynkt,dynkt_det_edges,bin_true_dynkt,dynkt_true_edges);

            // --- Bkg Histograms

            hbkg_nPhosel[i] = new TH1D(Form("hbkg_nPhosel_%zu", i), Form("hbkg_nPhosel_%zu;nPho;Norm. Events", i), 1, 0, 1);
            hbkg_nJet[i] = new TH1D(Form("hbkg_nJet_%zu", i), Form("hbkg_nJet_%zu;nJet;Norm. Events", i), 1, 0, 1);

            hbkg_jet_pt[i] = new TH1D(Form("hbkg_jet_pt_%zu", i), Form("hbkg_jet_pt_%zu;Recoil Jet p_{T};Norm. Events", i),25, 0, 250);//22,jet_pt_edges); //25, 0, 250);
            hbkg_jet_eta[i] = new TH1D(Form("hbkg_jet_eta_%zu", i), Form("hbkg_jet_eta_%zu;Recoil Jet #eta;Norm. Events", i), 50, -2.0, 2.0);
            hbkg_jet_phi[i] = new TH1D(Form("hbkg_jet_phi_%zu", i), Form("hbkg_jet_phi_%zu;Recoil Jet #phi;Norm. Events", i), 30, -3.14, 3.14);

            hbkg_xJ_all[i] = new TH1D(Form("hbkg_xJ_all_%zu", i), Form("hbkg_xJ_all_%zu;All Recoil Jet p_{T}/Photon E_{T};Events", i), nbins, 0, 2.0);
            hbkg_Rg_all[i] = new TH1D(Form("hbkg_Rg_all_%zu", i), Form("hbkg_Rg_all_%zu;R_{g};Events", i), nbins, 0.0001, 0.25);
            hbkg_angu_all[i] = new TH1D(Form("hbkg_angu_all_%zu", i), Form("hbkg_angu_all_%zu;Angularity(girth);Events", i), nbins, 0, 0.12);
            hbkg_ktdyn_all[i] = new TH1D(Form("hbkg_ktdyn_all_%zu", i), Form("hbkg_ktdyn_all_%zu;dyn k_{T};Events", i), nkt_bins, kt_edges);

            hbkg_xJ_lead[i] = new TH1D(Form("hbkg_xJ_lead_%zu", i), Form("hbkg_xJ_lead_%zu;Lead Recoil Jet p_{T}/Photon E_{T};1/N_{jet} dN/dp_{T,Jet}", i), nbins, 0, 2.0);
            hbkg_Rg_lead[i] = new TH1D(Form("hbkg_Rg_lead_%zu", i), Form("hbkg_Rg_lead_%zu;R_{g};1/N_{jet} dN/dR_{g}", i), nbins, 0.0001, 0.25);
            hbkg_angu_lead[i] = new TH1D(Form("hbkg_angu_lead_%zu", i), Form("hbkg_angu_lead_%zu;Angularity(girth);1/N_{jet} dN/dAngularity", i),nbins, 0, 0.12);
            hbkg_ktdyn_lead[i] = new TH1D(Form("hbkg_ktdyn_lead_%zu", i), Form("hbkg_ktdyn_lead_%zu;dyn k_{T};1/N_{jet} dN/dk_{T}", i), nkt_bins, kt_edges);
            hbkg_zg_lead[i] = new TH1D(Form("hbkg_zg_lead_%zu", i), Form("hbkg_zg_lead_%zu;zg;1/N_{jet} dN/dzg", i), nbins, 0.2, 0.51);

            // ---- Unfolding Histograms

            h_Rg_xJ_det[i]=new TH2D(Form("h_Rg_xJ_det_%zu",i),Form("h_Rg_xJ_det_%zu;R_{g};x_{#gamma,jet}",i),bin_det_Rg,Rg_det_edges,bin_det_xj,xJ_det_edges);
            h_Rg_xJ_mc_true[i]=new TH2D(Form("h_Rg_xJ_mc_true_%zu",i),Form("h_Rg_xJ_mc_true_%zu;All Gen True R_{g};All Gen True x_{#gamma,jet}",i),bin_true_Rg,Rg_true_edges,bin_true_xj,xJ_true_edges);
            h_Rg_xJ_mc_truef[i]=new TH2D(Form("h_Rg_xJ_mc_truef_%zu",i),Form("h_Rg_xJ_mc_truef_%zu;All Gen True R_{g};All Gen True x_{#gamma,jet}",i),bin_true_Rg,Rg_true_edges,bin_true_xj,xJ_true_edges);
            h_Rg_xJ_eff_match_num[i]=new TH2D(Form("h_Rg_xJ_eff_match_num_%zu",i),Form("h_Rg_xJ_eff_match_num_%zu;R_{g};x_{#gamma,jet}",i),bin_true_Rg,Rg_true_edges,bin_true_xj,xJ_true_edges);
            h_Rg_xJ_eff_match_den[i]=new TH2D(Form("h_Rg_xJ_eff_match_den_%zu",i),Form("h_Rg_xJ_eff_match_den_%zu;R_{g};x_{#gamma,jet}",i),bin_true_Rg,Rg_true_edges,bin_true_xj,xJ_true_edges);
            h_Rg_xJ_pur_num[i]=new TH2D(Form("h_Rg_xJ_pur_num_%zu",i),Form("h_Rg_xJ_pur_num_%zu;R_{g};x_{#gamma,jet}",i),bin_det_Rg,Rg_det_edges,bin_det_xj,xJ_det_edges);
            h_Rg_xJ_pur_den[i]=new TH2D(Form("h_Rg_xJ_pur_den_%zu",i),Form("h_Rg_xJ_pur_den_%zu;R_{g};x_{#gamma,jet}",i),bin_det_Rg,Rg_det_edges,bin_det_xj,xJ_det_edges);

            hbkg_Rg_xJ_det[i]=new TH2D(Form("hbkg_Rg_xJ_det_%zu",i),Form("hbkg_Rg_xJ_det_%zu;R_{g};x_{#gamma,jet}",i),bin_det_Rg,Rg_det_edges,bin_det_xj,xJ_det_edges);

            h_angu_xJ_det[i]=new TH2D(Form("h_angu_xJ_det_%zu",i),Form("h_angu_xJ_det_%zu;Angularity(girth);x_{#gamma,jet}",i),bin_det_angu,angu_det_edges,bin_det_xj,xJ_det_edges);
            h_angu_xJ_mc_true[i]=new TH2D(Form("h_angu_xJ_mc_true_%zu",i),Form("h_angu_xJ_mc_true_%zu;Angularity(girth);x_{#gamma,jet}",i),bin_true_angu,angu_true_edges,bin_true_xj,xJ_true_edges);
            h_angu_xJ_mc_truef[i]=new TH2D(Form("h_angu_xJ_mc_truef_%zu",i),Form("h_angu_xJ_mc_truef_%zu;Angularity(girth);x_{#gamma,jet}",i),bin_true_angu,angu_true_edges,bin_true_xj,xJ_true_edges);
            h_angu_xJ_pur_num[i]=new TH2D(Form("h_angu_xJ_pur_num_%zu",i),Form("h_angu_xJ_pur_num_%zu;R_{g};x_{#gamma,jet}",i),bin_det_angu,angu_det_edges,bin_det_xj,xJ_det_edges);
            h_angu_xJ_pur_den[i]=new TH2D(Form("h_angu_xJ_pur_den_%zu",i),Form("h_angu_xJ_pur_den_%zu;R_{g};x_{#gamma,jet}",i),bin_det_angu,angu_det_edges,bin_det_xj,xJ_det_edges);

            hbkg_angu_xJ_det[i]=new TH2D(Form("hbkg_angu_xJ_det_%zu",i),Form("hbkg_angu_xJ_det_%zu;Angularity(girth);x_{#gamma,jet}",i),bin_det_angu,angu_det_edges,bin_det_xj,xJ_det_edges);

            h_dynkt_xJ_det[i]=new TH2D(Form("h_dynkt_xJ_det_%zu",i),Form("h_dynkt_xJ_det_%zu;dynkt;x_{#gamma,jet}",i),bin_det_dynkt,dynkt_det_edges,bin_det_xj,xJ_det_edges);
            h_dynkt_xJ_mc_true[i]=new TH2D(Form("h_dynkt_xJ_mc_true_%zu",i),Form("h_dynkt_xJ_mc_true_%zu;dynkt;x_{#gamma,jet}",i),bin_true_dynkt,dynkt_true_edges,bin_true_xj,xJ_true_edges);
            h_dynkt_xJ_mc_truef[i]=new TH2D(Form("h_dynkt_xJ_mc_truef_%zu",i),Form("h_dynkt_xJ_mc_truef_%zu;dynkt;x_{#gamma,jet}",i),bin_true_dynkt,dynkt_true_edges,bin_true_xj,xJ_true_edges);

            hbkg_dynkt_xJ_det[i]=new TH2D(Form("hbkg_dynkt_xJ_det_%zu",i),Form("hbkg_dynkt_xJ_det_%zu;dynkt;x_{#gamma,jet}",i),bin_det_dynkt,dynkt_det_edges,bin_det_xj,xJ_det_edges);
        }

    // -------- End Histograms
    // ----------------------------------------------------------------------------------------------------------------
    // Event Loop

    const float min_pho_et = 100;
    const float cut_HoverE = 0.119947;//0.137168;  // 0.0696672;
    const float cut_SIEIE  = 0.010392;//0.0103766; // 0.00983515;
    const float cut_SumIso = 2.099277;//1.45486;   // 1.33546;
    const float min_jet_pt = 0.4;        // Changed to xJ >0.4
    const float purity_values[ncent] =  {0.774996,0.891456,0.805383,0.757357,0.872783};//{0.829,0.894,0.843,0.809,0.898};// ABCD Purity - {0.823,0.883,0.837,0.803,0.887};
    // const float purity_values[ncent] ={0.83,0.89,0.84,0.81,0.90};// ABCD Purity - {0.82,0.88,0.84,0.80,0.89};
    const float orig_qg[ncent] = {0.634,0.632};//{0.634,0.632,0.6325,0.633,0.633};   // Quark Fraction
    const float fit_qg[ncent] = {0.485,0.528};//{0.485,0.528,0.496,0.472,0.541}; // From angu - {0.483,0.533,0.494,0.467,0.529};

    float max_xJ = 0;
    float nsel = 0;

    JetCorrectionUncertainty *jecUnc ;
    if(!label.Contains("Data")){
        jecUnc = new JetCorrectionUncertainty("/grid_mnt/vol_home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/JetAnalysis/test/Uncertainty/JEC/Autumn18_HI_V6_MC_Uncertainty_AK2PF.txt");
    }
    
    JME::JetResolution resolution ; //this is for the case where the det-level jet is not matched to a truth-level jet
    resolution = JME::JetResolution("/grid_mnt/vol_home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/JetAnalysis/test/Uncertainty/JER/Autumn18_RunD_V7b_MC_PtResolution_AK4PF.txt");
    
    JME::JetResolutionScaleFactor resolution_sf ; //this is for the case where the det-level jet is matched to a truth-level jet
    resolution_sf = JME::JetResolutionScaleFactor("/grid_mnt/vol_home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/JetAnalysis/test/Uncertainty/JER/Autumn18_RunD_V7b_MC_SF_AK4PF.txt");

    Int_t nEv=jet_tree.GetEntries();
    for(int iEntry=0; iEntry<nEv; iEntry++){
        jet_tree.GetEntry(iEntry);
        float scale =1.0;
        float weight_rho=1.0;
        float weight_vz=1.0;
                
        if(!label.Contains("Data")){
            weight_rho = 1.0;//rho_weight[(int)(rho/5)]; // 1.0;// 
            weight_vz = 1.0;//vz_weight[int(vz)+20];// 1.0;// 
            scale*=weight*weight_pthat*weight_cent*weight_rho*weight_vz;
            if(pho_genMatchedIndex<0) continue;
            if(abs(mcPID)!=22) continue;
        }
        
        for (std::size_t i = 0; i < ncent; ++i) {
            if(!(hiBin>=min_cent[i] && hiBin<max_cent[i])) continue;           
            
            // True Jet -------------------------------
            if(!label.Contains("Data") && abs(mcEta)<1.44){
            if(mcEt>90){
            h_true_pho_Et[i]->Fill(mcEt,scale);
            }
            if(mcEt>min_pho_et){
                int jet_index = -1;
                float jet_det_pt_max = -1;
                float jet_pt_max = -1;
                float jet_true_Rg_max=-1;
                float jet_xJ_max=-1;
                float jet_true_xJ_max=-1;
                float jet_Rg_max=-1;
                for(int ijet=0; ijet<nref;ijet++){
                    float jetPtCorrected = jtpt[ijet];
                    if(!(abs(refeta[ijet])<2)) continue;
                    // if(!(refpt[ijet]>min_jet_pt)) continue; 
                    if(!label.Contains("Data")){
                        //* JER
                        JME::JetParameters parameters_1;
                        parameters_1.setJetPt(refpt[ijet]);
                        parameters_1.setJetEta(jteta[ijet]);
                        parameters_1.setRho(rho);
                        // float sim_resolution = resolution.getResolution(parameters_1);
                        float sf = resolution_sf.getScaleFactor(parameters_1); // This is nominal,  Variation::UP DOWN
                        if(sf<=1) sf=1.0;
                        float corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/refpt[ijet])))*std::sqrt(sf*sf-1); // std::sqrt(0.06*0.06 + (0.8*0.8/jetPtCorrected))
                        jetPtCorrected*=corr_sf;
                    }
                    float true_xJ = refpt[ijet]/mcEt;
                    float xJ = jetPtCorrected/phoEtCorrected;
                    // if(true_xJ<0.4) continue;
                    float dphi = abs(TVector2::Phi_mpi_pi(mcPhi-refphi[ijet]));// ROOT::Math::VectorUtil::Phi_mpi_pi(phoPhi,jtphi[ijet]);
                    if(dphi>2*TMath::Pi()/3){
                        if(jet_pt_max<refpt[ijet]){
                            jet_det_pt_max = jetPtCorrected;
                            jet_pt_max = refpt[ijet];
                            jet_Rg_max = jtrg[ijet];
                            jet_true_Rg_max = refrg[ijet];
                            jet_index = ijet;
                            jet_xJ_max = xJ;
                            jet_true_xJ_max = true_xJ;
                        }
                    }
                }// End Jet Loop
                if(jet_index!=-1){
                    if(refpt[jet_index]>60 && refpt[jet_index]<80){
                        hres_xJ[i]->Fill((jet_xJ_max-jet_true_xJ_max)/jet_true_xJ_max,scale);
                        hres_jetpt[i]->Fill((jet_det_pt_max-refpt[jet_index])/refpt[jet_index],scale);
                        if(!(jet_true_Rg_max<=0 || jet_Rg_max<=0)){
                            hres_Rg[i]->Fill((jet_Rg_max-jet_true_Rg_max)/jet_true_Rg_max,scale);
                        }
                        hres_angu[i]->Fill((jtangu[jet_index]-refangu[jet_index])/refangu[jet_index],scale);
                    }
                    if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
                    h_true_jet_pt[i]->Fill(jet_pt_max,scale);
                    h_true_xJ[i]->Fill(jet_true_xJ_max,scale);
                    h_true_Rg[i]->Fill(jet_true_Rg_max,scale);
                    h_true_angu[i]->Fill(refangu[jet_index],scale);
                    // h_Rg_xJ_mc_truef[i]->Fill(jet_true_Rg_max,jet_true_xJ_max,scale);
                    // h_angu_xJ_mc_truef[i]->Fill(refangu[jet_index],jet_true_xJ_max,scale);
                    // hxJ_true[i]->Fill(refpt[jet_index]/mcEt,scale);
                    // hRg_true[i]->Fill(jet_true_Rg_max,scale);
                    // hangu_true[i]->Fill(refangu[jet_index],scale);
                    
                    /*
                    if(refpt[jet_index]>60 && refpt[jet_index]<80){
                        // hres_xJ[i]->Fill((jet_xJ_max-jet_true_xJ_max)/jet_true_xJ_max,scale);
                        hres_jetpt[i]->Fill((jet_pt_max-refpt[jet_index])/refpt[jet_index],scale);
                        // if(!(jet_true_Rg_max<=0 || jet_Rg_max<=0)){
                        //     hres_Rg[i]->Fill((jet_Rg_max-jet_true_Rg_max)/jet_true_Rg_max,scale);
                        // }
                        hres_angu[i]->Fill((jtangu[jet_index]-refangu[jet_index])/refangu[jet_index],scale);
                    }
                    */
                }
            }
            }
            // End True Jet ----------------------------------   
            if(phoSCEta<-1.39 && phoPhi<-0.9 && phoPhi>-1.6) continue;         
            if(!(fabs(phoSCEta)<1.442)) continue;
            if(!(phoEtCorrected>min_pho_et)) continue;
            // if(!L1_SingleEG21_BptxAND) continue;    // TRIGGERS APPLIED AT NTUPLIZER
            if(!HLT_HIGEDPhoton40_v1) continue;
            // if(rho<150) continue;
            hrho[i]->Fill(rho,scale);
            hvz[i]->Fill(vz,scale); 
            h_weight_rho[i]->Fill(rho,scale,1);

            int flagHoverE=1;   
            int flagSigmaEtaEta=1;
            int flagIso=1;

            int flagIso_sideband=1;

            // Final signal and background region flags
            int flagsig=0;
            int flagbkg=0;

            if(phoHoverE<=cut_HoverE) flagHoverE = 0;
            if(phoSigmaIEtaIEta_2012<=cut_SIEIE) flagSigmaEtaEta = 0;
            if(SumCalIso<=cut_SumIso) flagIso = 0;

            if(SumCalIso>10 && SumCalIso<=20) flagIso_sideband = 0; 

            
            if(!flagHoverE && !eleRej && !flagIso && !flagSigmaEtaEta) flagsig = 1;
            // if(!flagHoverE && !eleRej && !flagSigmaEtaEta && !flagIso_sideband) flagbkg = 1; // Iso Sideband as Bkg
            if(!flagHoverE && !eleRej && !flagIso && flagSigmaEtaEta) flagbkg = 1;           // High SIEIE as Bkg

            if(!flagsig && !flagbkg) continue;

            if(flagsig){
                hnPhosel[i]->Fill(1,scale);
                h_eta_phi_gamma[i]->Fill(phoSCEta,phoSCPhi,scale);
            }
            else if(flagbkg){
                hbkg_nPhosel[i]->Fill(1,scale);
            }

            // -------- End Photon Selection
            // Jet Loop----------------------------------------------------------------------------------
            // std::cout<<iEntry<<"   End Photon Selection"<<std::endl;
            std::vector<int> recoil_jet_index;
            std::vector<int> true_recoil_jet_index;
            int jet_index=-1;
            int jet_true_index=-1;
            int jet_true_index_gen=-1;
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
            float zg_temp = -1;

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

                if(!label.Contains("Data")){
                //* JER
                JME::JetParameters parameters_1;
                parameters_1.setJetPt(refpt[ijet]);
                parameters_1.setJetEta(jteta[ijet]);
                parameters_1.setRho(rho);
                // float sim_resolution = resolution.getResolution(parameters_1);
                float sf = resolution_sf.getScaleFactor(parameters_1); // This is nominal,  Variation::UP DOWN
                if(sf<=1) sf=1.0;
                float corr_sf = 1+gRandom->Gaus(0,std::sqrt(0.06*0.06 + (0.8*0.8/refpt[ijet])))*std::sqrt(sf*sf-1); // std::sqrt(0.06*0.06 + (0.8*0.8/jetPtCorrected))
                jetPtCorrected*=corr_sf;
                }

                // std::cout<<"i = "<<iEntry<<"   pT:"<<jetPtCorrected<<"   Resolution: "<<sim_resolution<<"   SF:"<<sf<<std::endl;
                
                if(jteta[ijet]<-1.39 && jtphi[ijet]<-0.9 && jtphi[ijet]>-1.6 ) continue; // HEM Failure
                if(fabs(jteta[ijet])>2) continue;
                float dEta = jteta[ijet] - phoEta;
                float dphi = abs(TVector2::Phi_mpi_pi(phoPhi-jtphi[ijet]));// ROOT::Math::VectorUtil::Phi_mpi_pi(phoPhi,jtphi[ijet]);
                float xJ = jetPtCorrected/phoEtCorrected;
                float true_xJ = -1;
                // if(jetPtCorrected<=min_jet_pt) continue;
                // if(sqrt(dEta*dEta + dphi*dphi)<0.5) continue; 
                // if(xJ<min_jet_pt) continue; 
                if(!label.Contains("Data"))
                    true_xJ = refpt[ijet]/mcEt;
                // if(sqrt(dEta*dEta + dphi*dphi)>0.2)
                    hdphi_all[i]->Fill(dphi,scale);       
                
                float dEta_ref = refeta[ijet] - phoEta;
                float dphi_ref = abs(TVector2::Phi_mpi_pi(phoPhi-refphi[ijet]));// ROOT::Math::VectorUtil::Phi_mpi_pi(phoPhi,jtphi[ijet]);
                
                // if(dphi_ref>2*TMath::Pi()/3){

                //     if(jet_true_pt_max<refpt[ijet]){
                //         jet_true_pt_max = refpt[ijet];
                //         jet_true_index = ijet;  
                //         jet_true_xJ_max = true_xJ; 
                //         jet_true_Rg_max = refrg[ijet];                     
                //     }
                // }


                if(dphi>2*TMath::Pi()/3){
                    if(jet_pt_max<jetPtCorrected){
                        jet_pt_max = jetPtCorrected;
                        jet_dphi_max = dphi;
                        jet_xJ_max = xJ;
                        jet_Rg_max = jtrg[ijet];
                        zg_temp = jtsym[ijet];
                        jet_index = ijet;

                        jet_true_Rg_max = refrg[ijet];
                        jet_true_xJ_max = true_xJ;
                        
                    }
                    if(jet_true_pt_max<refpt[ijet]){
                        jet_true_pt_max = refpt[ijet];
                        jet_true_index = ijet;  
                    }

                    if(flagsig && xJ>0.4){
                        recoil_jet_index.push_back(ijet);

                        hdphi_all[i]->Fill(dphi,scale);
                        hxJ_all[i]->Fill(xJ,scale);
                        if(jtrg[ijet]>0){
                            hRg_all[i]->Fill(jtrg[ijet],scale);
                        }
                        else{
                            hRg_all[i]->Fill(-0.025,scale);
                        }
                        hangu_all[i]->Fill(jtangu[ijet],scale);
                        hktdyn_all[i]->Fill(jtdynkt[ijet],scale);
                    }
                    if(flagbkg && xJ>0.4){

                        hbkg_xJ_all[i]->Fill(xJ,scale);
                        if(jtrg[ijet]>0){
                            hbkg_Rg_all[i]->Fill(jtrg[ijet],scale);
                        }
                        else{
                            hbkg_Rg_all[i]->Fill(-0.025,scale);
                        }
                        hbkg_angu_all[i]->Fill(jtangu[ijet],scale);
                        hbkg_ktdyn_all[i]->Fill(jtdynkt[ijet],scale);
                    }
                }
            }
            
            if(jet_index==-1) continue;
            if(i==0){
                nsel++; // Total Number of selected events
                if(flagsig) max_xJ++;
                if(jet_true_index_gen>=0){
                    // if(allgenmatchindex[jet_true_index_gen]==jet_index) max_xJ++; // Number of events with mismatch jet pT
                    // if(jet_true_index!=jet_index) max_xJ++;
                    // if(allgenmatchindex[jet_true_index_gen]==jet_index && recoil_jet_index.size()==2) max_xJ++;
                }
            }
            
            float weight_jet = 1.0;
            float scale_jet = scale;
            if(!label.Contains("Data")){
                //* Jet pT weighting
                // if(jet_pt_max<250){
                //     weight_jet*=jetpt_weight[(int)(jet_pt_max/10)]; // 1.0; //
                // }
                // else{
                //     weight_jet*=jetpt_weight[(int)(250/10)];
                // }
                // if(jet_pt_max>60){
                //     weight_jet=(1.49677-(3.48667*exp(-0.0218529*jet_pt_max)));
                // }
                // else{
                //     weight_jet=(1.49677-(3.48667*exp(-0.0218529*60)));
                // }
                scale_jet*=weight_jet;
                //* Quark vs Gluon 
                    // if(!(refparton_flavor[jet_index]==21)) continue; // Gluon only
                    // if((refparton_flavor[jet_index]>-9 && refparton_flavor[jet_index]<9)) continue;       // Not Quark 
                    // if(!(refparton_flavor[jet_index]>-9 && refparton_flavor[jet_index]<9)) continue; // continue if Not Quark -> Quark only
                if(refparton_flavor[jet_index]>-9 && refparton_flavor[jet_index]<9)    hweight_q[i]->Fill(1,scale_jet); // Quark only
                if(!(refparton_flavor[jet_index]>-9 && refparton_flavor[jet_index]<9)) hweight_g[i]->Fill(1,scale_jet); // Not Quark
            
                // if(!(refparton_flavor[jet_index]>-9 && refparton_flavor[jet_index]<9)) scale_jet*= (1-fit_qg[i])/(1-orig_qg[i]);          // Not Quark  0.95/(1-orig_qg[i]);
                // if(refparton_flavor[jet_index]>-9 && refparton_flavor[jet_index]<9)    scale_jet*= fit_qg[i]/orig_qg[i];                  // Quark Only  0.05/orig_qg[i]; 
                
            }
            // if(scale_jet>1500) continue;
            // if(i==0)
            // std::cout<<"Total weight = "<<scale_jet<<"\t weight*weight_pthat*weight_cent = "<<weight*weight_pthat*weight_cent<<"\t weight_rho = "<<weight_rho<<"\t weight_jetpt = "<<weight_jet<<"\t pthat = "<<pthat<<"\t refpt = "<<refpt[jet_index]<<"\t jetpt = "<<jet_pt_max<<" \t flagsig = "<<flagsig<<std::endl;
            // if(jet_true_Rg_max>0 && jet_true_Rg_max<max_xJ)
            //     max_xJ = jet_true_Rg_max;
            // if(jet_Rg_max>0 && jet_Rg_max<max_xJ)
            //     max_xJ = jet_Rg_max;
            // if(max_xJ<jet_xJ_max) max_xJ=jet_xJ_max;
            if(zg_temp<0.2) zg_temp = 0.505;
            if(jet_true_Rg_gen<=0) jet_true_Rg_gen = -0.025;
            if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
            if(jet_Rg_max<=0) jet_Rg_max = -0.025;
            // std::cout<<iEntry<<"   End Jet Loop"<<std::endl;
            if(jet_xJ_max>=min_jet_pt){
                hweight[i]->Fill(1,scale_jet);
                hHibin[i]->Fill(hiBin,scale_jet);
                h_jetpt_weight[i]->Fill(jet_pt_max,scale_jet,1);
                h_angu_weight[i]->Fill(jtangu[jet_index],scale_jet,1);
                h_Rg_weight[i]->Fill(jet_Rg_max,scale_jet,1);
                hdphi_lead[i]->Fill(jet_dphi_max,scale_jet);

                h_jetpt_angu[i]->Fill(jet_pt_max,jtangu[jet_index],1);

                h_jetpt_recogen[i]->Fill(jet_pt_max,jet_pt_max/refpt[jet_index],scale_jet);
            }
            if(refpt[jet_index]>60 && refpt[jet_index]<80)
                h_jeteta_recogen[i]->Fill(jteta[jet_index],jet_pt_max/refpt[jet_index],scale_jet);
        
            if(flagsig){
                hnJet[i]->Fill(1,scale_jet);
                h_jet_pt[i]->Fill(jet_pt_max,scale_jet);
                h_jet_eta[i]->Fill(jteta[jet_index],scale_jet);
                h_jet_phi[i]->Fill(jtphi[jet_index],scale_jet);
                h_eta_phi_jet[i]->Fill(jteta[jet_index],jtphi[jet_index],scale_jet);

                if(jet_xJ_max>0.4){
                hxJ_lead[i]->Fill(jet_xJ_max,scale_jet);
                if(jet_Rg_max>0){
                    hRg_lead[i]->Fill(jet_Rg_max,scale);
                }
                else{
                    hRg_lead[i]->Fill(-0.025,scale);
                }
                hangu_lead[i]->Fill(jtangu[jet_index],scale_jet);
                hktdyn_lead[i]->Fill(jtdynkt[jet_index],scale_jet);
                hzg_lead[i]->Fill(zg_temp,scale_jet);
                }

                hxJ_lead_true[i]->Fill(jet_xJ_max,scale_jet);
                hRg_lead_true[i]->Fill(jet_Rg_max,scale_jet);
                hangu_lead_true[i]->Fill(jtangu[jet_index],scale_jet);
                hktdyn_lead_true[i]->Fill(jtdynkt[jet_index],scale_jet);
                hzg_lead_true[i]->Fill(zg_temp,scale_jet);                

                if(!label.Contains("Data")){
                    
                    // if(refpt[jet_index]>60 && refpt[jet_index]<80){
                    //     hres_xJ[i]->Fill((jet_xJ_max-jet_true_xJ_max)/jet_true_xJ_max,scale_jet);
                    //     hres_jetpt[i]->Fill((jet_pt_max-refpt[jet_index])/refpt[jet_index],scale_jet);
                    //     if(!(jet_true_Rg_max<=0 || jet_Rg_max<=0)){
                    //         hres_Rg[i]->Fill((jet_Rg_max-jet_true_Rg_max)/jet_true_Rg_max,scale_jet);
                    //     }
                    //     hres_angu[i]->Fill((jtangu[jet_index]-refangu[jet_index])/refangu[jet_index],scale_jet);
                    // }   
           
                    //* Rg Efficiency for gen-reco matching
                    if(jet_true_Rg_gen<=0) jet_true_Rg_gen = -0.025;
                        h_Rg_xJ_eff_match_den[i]->Fill(jet_true_Rg_gen,jet_true_xJ_gen,scale_jet);
                    
                    if(allgenmatchindex[jet_true_index_gen]==jet_index && fabs(allgenpt[jet_true_index_gen]-refpt[jet_index]<0.01)){
                        h_Rg_xJ_eff_match_num[i]->Fill(jet_true_Rg_gen,jet_true_xJ_gen,scale_jet);
                    }

                    //* Rg Efficiency for matched jets
                    if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
                        h_Rg_xJ_mc_truef[i]->Fill(jet_true_Rg_max,jet_true_xJ_max,scale_jet);
                    
                    if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                    && jet_Rg_max>=Rgmin_det && jet_Rg_max<Rgmax_det){
                        if(jet_Rg_max<=0) jet_Rg_max = -0.025;

                        h_Rg_xJ_mc_true[i]->Fill(jet_true_Rg_max,jet_true_xJ_max,scale_jet);
                    }

                    //* Rg Efficiency considering all Gen Jets
                    // if(jet_true_Rg_gen<=0) jet_true_Rg_gen = -0.025;
                    //     h_Rg_xJ_mc_truef[i]->Fill(jet_true_Rg_gen,jet_true_xJ_gen,scale_jet);
                    
                    // if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                    // && jet_Rg_max>=Rgmin_det && jet_Rg_max<Rgmax_det){
                    //     if(jet_Rg_max<=0) jet_Rg_max = -0.025;

                    //     h_Rg_xJ_mc_true[i]->Fill(jet_true_Rg_gen,jet_true_xJ_gen,scale_jet);
                    // }

                    // if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
                    //     h_Rg_xJ_mc_truef[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);
                    
                    // if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                    // && jet_Rg_max>=Rgmin_det && jet_Rg_max<Rgmax_det){
                    //     if(jet_Rg_max<=0) jet_Rg_max = -0.025;

                    //     h_Rg_xJ_mc_true[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);
                    // }

                    if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                        && jet_Rg_max>=Rgmin_det && jet_Rg_max<Rgmax_det){
                            if(jet_Rg_max<=0) jet_Rg_max = -0.025;
                            h_Rg_xJ_pur_den[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);

                            if(allgenmatchindex[jet_true_index_gen]==jet_index && fabs(allgenpt[jet_true_index_gen]-refpt[jet_index]<0.01) &&
                            jet_true_xJ_gen>=xjmin_true && jet_true_xJ_gen<xjmax_true 
                            && jet_true_Rg_gen>=Rgmin_true && jet_true_Rg_gen<Rgmax_true){
                                if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
                                h_Rg_xJ_pur_num[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);
                            }
                    }
                        //* Original Filling the Rg Response
                        if(allgenmatchindex[jet_true_index_gen]==jet_index && fabs(allgenpt[jet_true_index_gen]-refpt[jet_index]<0.01) &&
                        jet_true_xJ_max>=xjmin_true && jet_true_xJ_max<xjmax_true 
                        && jet_true_Rg_max>=Rgmin_true && jet_true_Rg_max<Rgmax_true){
                            if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
                            // h_Rg_xJ_mc_truef[i]->Fill(jet_true_Rg_max,jet_true_xJ_max,scale_jet);

                            if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                            && jet_Rg_max>=Rgmin_det && jet_Rg_max<Rgmax_det){
                                if(jet_Rg_max<=0) jet_Rg_max = -0.025;

                                // h_Rg_xJ_mc_true[i]->Fill(jet_true_Rg_max,jet_true_xJ_max,scale_jet);
                                h_Rg_xJ_det[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);//scale_jet

                                var_xJ_det = jet_xJ_max;
                                var_Rg_det = jet_Rg_max;
                                var_angu_det = jtangu[jet_index];
                                var_dynkt_det = jtdynkt[jet_index];
                                var_xJ_true = jet_true_xJ_max;
                                var_Rg_true = jet_true_Rg_max;
                                var_angu_true = refangu[jet_index];
                                var_dynkt_true = refdynkt[jet_index];
                                var_hiBin = hiBin;
                                var_phoEtCorrected = phoEtCorrected;
                                var_weightFinal = scale_jet;
                                tree_xj_Rg->Fill();
                            }
                        }

                    if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
                        h_Rg_xJ_mc_truef[i]->Fill(jet_true_Rg_max,jet_true_xJ_max,scale_jet);
                    
                    if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                    && jet_Rg_max>=Rgmin_det && jet_Rg_max<Rgmax_det){
                        if(jet_Rg_max<=0) jet_Rg_max = -0.025;

                        h_Rg_xJ_mc_true[i]->Fill(jet_true_Rg_max,jet_true_xJ_max,scale_jet);
                    }

                    // if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
                    //     h_Rg_xJ_mc_truef[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);
                    
                    // if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                    // && jet_Rg_max>=Rgmin_det && jet_Rg_max<Rgmax_det){
                    //     if(jet_Rg_max<=0) jet_Rg_max = -0.025;

                    //     h_Rg_xJ_mc_true[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);
                    // }

                    if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                        && jet_Rg_max>=Rgmin_det && jet_Rg_max<Rgmax_det){
                            if(jet_Rg_max<=0) jet_Rg_max = -0.025;
                            h_Rg_xJ_pur_den[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);

                            if(jet_true_xJ_max>=xjmin_true && jet_true_xJ_max<xjmax_true 
                            && jet_true_Rg_max>=Rgmin_true && jet_true_Rg_max<Rgmax_true){
                                if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
                                h_Rg_xJ_pur_num[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);
                            }
                    }

                    if(jet_true_xJ_max>=xjmin_true && jet_true_xJ_max<xjmax_true 
                    && refangu[jet_index]>=angumin_true && refangu[jet_index]<angumax_true){
                        // h_angu_xJ_mc_truef[i]->Fill(refangu[jet_index],jet_true_xJ_max,scale_jet);

                        // hxJ_lead_true[i]->Fill(jet_xJ_max,scale_jet);
                        // hRg_lead_true[i]->Fill(jet_Rg_max,scale_jet);
                        // hangu_lead_true[i]->Fill(jtangu[jet_index],scale_jet);
                        // hktdyn_lead_true[i]->Fill(jtdynkt[jet_index],scale_jet);
                        // hzg_lead_true[i]->Fill(zg_temp,scale_jet);

                        if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                        && jtangu[jet_index]>=angumin_det && jtangu[jet_index]<angumax_det){

                            // h_angu_xJ_mc_true[i]->Fill(refangu[jet_index],jet_true_xJ_max,scale_jet);
                            h_angu_xJ_det[i]->Fill(jtangu[jet_index],jet_xJ_max,scale_jet);//scale_jet

                            var_xJ_det = jet_xJ_max;
                            var_Rg_det = jet_Rg_max;
                            var_angu_det = jtangu[jet_index];
                            var_dynkt_det = jtdynkt[jet_index];
                            var_xJ_true = jet_true_xJ_max;
                            var_Rg_true = jet_true_Rg_max;
                            var_angu_true = refangu[jet_index];
                            var_dynkt_true = refdynkt[jet_index];
                            var_hiBin = hiBin;
                            var_phoEtCorrected = phoEtCorrected;
                            var_weightFinal = scale_jet;
                            tree_xj_angu->Fill();
                        }
                    }

                    if(jet_true_xJ_max>=xjmin_true && jet_true_xJ_max<xjmax_true 
                    && refdynkt[jet_index]>=dynktmin_true && refdynkt[jet_index]<dynktmax_true){
                        h_dynkt_xJ_mc_truef[i]->Fill(refdynkt[jet_index],jet_true_xJ_max,scale_jet);

                        if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                        && jtdynkt[jet_index]>=dynktmin_det && jtdynkt[jet_index]<dynktmax_det){

                            h_dynkt_xJ_mc_true[i]->Fill(refdynkt[jet_index],jet_true_xJ_max,scale_jet);
                            h_dynkt_xJ_det[i]->Fill(jtdynkt[jet_index],jet_xJ_max,scale_jet);

                            var_xJ_det = jet_xJ_max;
                            var_Rg_det = jet_Rg_max;
                            var_angu_det = jtangu[jet_index];
                            var_dynkt_det = jtdynkt[jet_index];
                            var_xJ_true = jet_true_xJ_max;
                            var_Rg_true = jet_true_Rg_max;
                            var_angu_true = refangu[jet_index];
                            var_dynkt_true = refdynkt[jet_index];
                            var_hiBin = hiBin;
                            var_phoEtCorrected = phoEtCorrected;
                            var_weightFinal = scale_jet;
                            tree_xj_dynkt->Fill();
                        }
                    }
                }
                else{
                    if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                        && jet_Rg_max>=Rgmin_det && jet_Rg_max<Rgmax_det){
                        if(jet_Rg_max<=0) jet_Rg_max = -0.025;
                        h_Rg_xJ_det[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);
                    }
                    if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                        && jtangu[jet_index]>=angumin_det && jtangu[jet_index]<=angumax_det){
                        h_angu_xJ_det[i]->Fill(jtangu[jet_index],jet_xJ_max,scale_jet);
                    }
                    if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                        && jtdynkt[jet_index]>=dynktmin_det && jtdynkt[jet_index]<=dynktmax_det){
                        h_dynkt_xJ_det[i]->Fill(jtdynkt[jet_index],jet_xJ_max,scale_jet);
                    }
                }
            }
            else if(flagbkg){
                hbkg_nJet[i]->Fill(1,scale_jet);

                hbkg_jet_pt[i]->Fill(jet_pt_max,scale_jet);
                hbkg_jet_eta[i]->Fill(jteta[jet_index],scale_jet);
                hbkg_jet_phi[i]->Fill(jtphi[jet_index],scale_jet);

                // hbkg_xJ_lead[i]->Fill(jet_xJ_max,scale_jet);
                // hbkg_Rg_lead[i]->Fill(jet_Rg_max,scale_jet);
                // hbkg_angu_lead[i]->Fill(jtangu[jet_index],scale_jet);
                // hbkg_ktdyn_lead[i]->Fill(jtdynkt[jet_index],scale_jet);
                // hbkg_zg_lead[i]->Fill(zg_temp,scale_jet);

                if(jet_xJ_max>0.4){
                hbkg_xJ_lead[i]->Fill(jet_xJ_max,scale_jet);
                if(jet_Rg_max>0){
                    hbkg_Rg_lead[i]->Fill(jet_Rg_max,scale);
                }
                else{
                    hbkg_Rg_lead[i]->Fill(-0.025,scale);
                }
                hbkg_angu_lead[i]->Fill(jtangu[jet_index],scale_jet);
                hbkg_ktdyn_lead[i]->Fill(jtdynkt[jet_index],scale_jet);
                hbkg_zg_lead[i]->Fill(zg_temp,scale_jet);
                }

                if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                    && jet_Rg_max>=Rgmin_det && jet_Rg_max<Rgmax_det){
                    if(jet_Rg_max<=0) jet_Rg_max = -0.025;
                    hbkg_Rg_xJ_det[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);
                }
                if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                    && jtangu[jet_index]>=angumin_det && jtangu[jet_index]<=angumax_det){
                    hbkg_Rg_xJ_det[i]->Fill(jtangu[jet_index],jet_xJ_max,scale_jet);
                }
                if(jet_xJ_max>=xjmin_det && jet_xJ_max<xjmax_det 
                    && jtdynkt[jet_index]>=dynktmin_det && jtdynkt[jet_index]<=dynktmax_det){
                    hbkg_dynkt_xJ_det[i]->Fill(jtdynkt[jet_index],jet_xJ_max,scale_jet);
                }
            }

            h_Rg_xJ[i]->Fill(jet_Rg_max,jet_xJ_max,scale_jet);
            h_angu_xJ[i]->Fill(jtangu[jet_index],jet_xJ_max,scale_jet);
            h_ktdyn_xJ[i]->Fill(jtdynkt[jet_index],jet_xJ_max,scale_jet);

            if(!label.Contains("Data")){        
                hrefparton_lead[i]->Fill(refparton_flavor[jet_index],scale_jet);          
                h_xJ_xJ[i]->Fill(jet_xJ_max,jet_true_xJ_max,scale_jet);
                h_Rg_Rg[i]->Fill(jet_Rg_max,jet_true_Rg_max,scale_jet);
                h_angu_angu[i]->Fill(jtangu[jet_index],refangu[jet_index],scale_jet);
                h_ktdyn_ktdyn[i]->Fill(jtdynkt[jet_index],refdynkt[jet_index],scale_jet);

                if(jet_true_xJ_max>0.4){
                    h_xJ_g0p4_Rg_Rg[i]->Fill(jet_Rg_max,jet_true_Rg_max,scale_jet);
                    h_xJ_g0p4_angu_angu[i]->Fill(jtangu[jet_index],refangu[jet_index],scale_jet);
                    h_xJ_g0p4_dynkt_dynkt[i]->Fill(jtdynkt[jet_index],refdynkt[jet_index],scale_jet);
                }
                else if(jet_true_xJ_max>=0){
                    h_xJ_l0p4_Rg_Rg[i]->Fill(jet_Rg_max,jet_true_Rg_max,scale_jet);
                    h_xJ_l0p4_angu_angu[i]->Fill(jtangu[jet_index],refangu[jet_index],scale_jet);
                    h_xJ_l0p4_dynkt_dynkt[i]->Fill(jtdynkt[jet_index],refdynkt[jet_index],scale_jet);
                }
            }
        }
    }
    std::cout<<"\n Total sel Events = "<<nsel<<std::endl;
    std::cout<<"\n NEvents mismatch - Matched gen jets = "<<max_xJ<<std::endl;

    // ------ Normalization and Purity Subtraction 
    for (std::size_t i = 0; i < ncent; ++i) {
        
        // Photon Purity
        if(label.Contains("Data")){
            // h_jet_pt[i]->Scale(1.0/purity_values[i]);
            // h_jet_eta[i]->Scale(1.0/purity_values[i]);
            // h_jet_phi[i]->Scale(1.0/purity_values[i]);
            hxJ_all[i]->Scale(1.0/purity_values[i]);
            hRg_all[i]->Scale(1.0/purity_values[i]);
            hangu_all[i]->Scale(1.0/purity_values[i]);
            hktdyn_all[i]->Scale(1.0/purity_values[i]);

            hxJ_lead[i]->Scale(1.0/purity_values[i]);
            hRg_lead[i]->Scale(1.0/purity_values[i]);
            hangu_lead[i]->Scale(1.0/purity_values[i]);
            hktdyn_lead[i]->Scale(1.0/purity_values[i]);
            hzg_lead[i]->Scale(1.0/purity_values[i]);
            h_Rg_xJ_det[i]->Scale(1.0/purity_values[i]);
            h_angu_xJ_det[i]->Scale(1.0/purity_values[i]);
            h_dynkt_xJ_det[i]->Scale(1.0/purity_values[i]);

            // hbkg_jet_pt[i]->Scale((1-purity_values[i])/purity_values[i]);
            // hbkg_jet_eta[i]->Scale((1-purity_values[i])/purity_values[i]);
            // hbkg_jet_phi[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_xJ_all[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_Rg_all[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_angu_all[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_ktdyn_all[i]->Scale((1-purity_values[i])/purity_values[i]);

            hbkg_xJ_lead[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_Rg_lead[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_angu_lead[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_ktdyn_lead[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_zg_lead[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_Rg_xJ_det[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_angu_xJ_det[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_dynkt_xJ_det[i]->Scale((1-purity_values[i])/purity_values[i]);

            // h_jet_pt[i]->Add(hbkg_jet_pt[i],-1);
            // h_jet_eta[i]->Add(hbkg_jet_eta[i],-1);
            // h_jet_phi[i]->Add(hbkg_jet_phi[i],-1);
            hxJ_all[i]->Add(hbkg_xJ_all[i],-1);
            hRg_all[i]->Add(hbkg_Rg_all[i],-1);
            hangu_all[i]->Add(hbkg_angu_all[i],-1);
            hktdyn_all[i]->Add(hbkg_ktdyn_all[i],-1);

            hxJ_lead[i]->Add(hbkg_xJ_lead[i],-1);
            hRg_lead[i]->Add(hbkg_Rg_lead[i],-1);
            hangu_lead[i]->Add(hbkg_angu_lead[i],-1);
            hktdyn_lead[i]->Add(hbkg_ktdyn_lead[i],-1);
            hzg_lead[i]->Add(hbkg_zg_lead[i],-1);
            h_Rg_xJ_det[i]->Add(hbkg_Rg_xJ_det[i],-1);
            h_angu_xJ_det[i]->Add(hbkg_Rg_xJ_det[i],-1);
            h_dynkt_xJ_det[i]->Add(hbkg_Rg_xJ_det[i],-1);
        }
        // else{
        //     hxJ_lead[i]->Scale(1.0/hxJ_lead[i]->Integral());
        //     hRg_lead[i]->Scale(1.0/hRg_lead[i]->Integral());
        //     hangu_lead[i]->Scale(1.0/hangu_lead[i]->Integral());
        //     hktdyn_lead[i]->Scale(1.0/hktdyn_lead[i]->Integral());
        // }
        else{
            h_Rg_xJ_pur_num[i]->Divide(h_Rg_xJ_pur_num[i],h_Rg_xJ_pur_den[i],1,1,"B");
            h_Rg_xJ_det[i]->Multiply(h_Rg_xJ_pur_num[i]);
        }
        
    }
    // -------- End Purity Subtraction
    // ------ Save histograms to File

    TFile *fout;
    fout = new TFile(output_path + "/OutputPlots_"+label+"/Output_"+label+".root", "recreate");
    tree_xj_Rg->Write("",TObject::kOverwrite);
    tree_xj_angu->Write("",TObject::kOverwrite);
    tree_xj_dynkt->Write("",TObject::kOverwrite);
    for (std::size_t i = 0; i < ncent; ++i) {

        h_true_pho_Et[i]->Write("",TObject::kOverwrite);
        h_true_jet_pt[i]->Write("",TObject::kOverwrite);
        h_true_xJ[i]->Write("",TObject::kOverwrite);
        h_true_Rg[i]->Write("",TObject::kOverwrite);
        h_true_angu[i]->Write("",TObject::kOverwrite);

        hweight[i]->Write("",TObject::kOverwrite);
        hweight_q[i]->Write("",TObject::kOverwrite);
        hweight_g[i]->Write("",TObject::kOverwrite);

        h_jetpt_weight[i]->Write("",TObject::kOverwrite);
        h_angu_weight[i]->Write("",TObject::kOverwrite);
        h_Rg_weight[i]->Write("",TObject::kOverwrite);

        hnPho[i]->Write("",TObject::kOverwrite);
        hnPhosel[i]->Write("",TObject::kOverwrite);
        hnJet[i]->Write("",TObject::kOverwrite);

        hHibin[i]->Write("",TObject::kOverwrite);
        hrho[i]->Write("",TObject::kOverwrite);
        hvz[i]->Write("",TObject::kOverwrite);

        h_weight_rho[i]->Write("",TObject::kOverwrite);

        h_eta_phi_gamma[i]->Write("",TObject::kOverwrite);
        h_eta_phi_jet[i]->Write("",TObject::kOverwrite);

        h_jetpt_recogen[i]->Write("",TObject::kOverwrite);
        h_jeteta_recogen[i]->Write("",TObject::kOverwrite);

        h_jet_pt[i]->Write("",TObject::kOverwrite);
        h_jet_eta[i]->Write("",TObject::kOverwrite);
        h_jet_phi[i]->Write("",TObject::kOverwrite);

        hres_jetpt[i]->Write("",TObject::kOverwrite);
        hres_xJ[i]->Write("",TObject::kOverwrite);
        hres_Rg[i]->Write("",TObject::kOverwrite);
        hres_angu[i]->Write("",TObject::kOverwrite);

        hdphi_all[i]->Write("",TObject::kOverwrite);
        hxJ_all[i]->Write("",TObject::kOverwrite);
        hRg_all[i]->Write("",TObject::kOverwrite);
        hangu_all[i]->Write("",TObject::kOverwrite);
        hktdyn_all[i]->Write("",TObject::kOverwrite);

        hdphi_lead[i]->Write("",TObject::kOverwrite);
        hxJ_lead[i]->Write("",TObject::kOverwrite);
        hRg_lead[i]->Write("",TObject::kOverwrite);
        hangu_lead[i]->Write("",TObject::kOverwrite);
        hktdyn_lead[i]->Write("",TObject::kOverwrite);
        hrefparton_lead[i]->Write("",TObject::kOverwrite);
        hzg_lead[i]->Write("",TObject::kOverwrite);

        hxJ_lead_true[i]->Write("",TObject::kOverwrite);
        hRg_lead_true[i]->Write("",TObject::kOverwrite);
        hangu_lead_true[i]->Write("",TObject::kOverwrite);
        hktdyn_lead_true[i]->Write("",TObject::kOverwrite);
        hzg_lead_true[i]->Write("",TObject::kOverwrite);

        h_Rg_xJ[i]->Write("",TObject::kOverwrite);
        h_angu_xJ[i]->Write("",TObject::kOverwrite);
        h_ktdyn_xJ[i]->Write("",TObject::kOverwrite);

        h_xJ_xJ[i]->Write("",TObject::kOverwrite);
        h_Rg_Rg[i]->Write("",TObject::kOverwrite);
        h_angu_angu[i]->Write("",TObject::kOverwrite);
        h_ktdyn_ktdyn[i]->Write("",TObject::kOverwrite);

        h_xJ_l0p4_Rg_Rg[i]->Write("",TObject::kOverwrite);
        h_xJ_l0p4_angu_angu[i]->Write("",TObject::kOverwrite);
        h_xJ_l0p4_dynkt_dynkt[i]->Write("",TObject::kOverwrite);
        h_xJ_g0p4_Rg_Rg[i]->Write("",TObject::kOverwrite);
        h_xJ_g0p4_angu_angu[i]->Write("",TObject::kOverwrite);
        h_xJ_g0p4_dynkt_dynkt[i]->Write("",TObject::kOverwrite);

        hbkg_nPhosel[i]->Write("",TObject::kOverwrite);
        hbkg_nJet[i]->Write("",TObject::kOverwrite);

        hbkg_xJ_all[i]->Write("",TObject::kOverwrite);
        hbkg_Rg_all[i]->Write("",TObject::kOverwrite);
        hbkg_angu_all[i]->Write("",TObject::kOverwrite);
        hbkg_ktdyn_all[i]->Write("",TObject::kOverwrite);

        hbkg_xJ_lead[i]->Write("",TObject::kOverwrite);
        hbkg_Rg_lead[i]->Write("",TObject::kOverwrite);
        hbkg_angu_lead[i]->Write("",TObject::kOverwrite);
        hbkg_ktdyn_lead[i]->Write("",TObject::kOverwrite);
        hbkg_zg_lead[i]->Write("",TObject::kOverwrite);

        h_Rg_xJ_det[i]->Write("",TObject::kOverwrite);      //* Current Binning xJ -> 0,0.4,3.0 -> Projecting [0.4,3.0]
        h_Rg_xJ_det[i]->ProjectionY(Form("h_xJ_det_%zu",i))->Write("",TObject::kOverwrite);
        h_Rg_xJ_det[i]->ProjectionX(Form("h_Rg_det_%zu",i),1,1)->Write("",TObject::kOverwrite);
        h_Rg_xJ_mc_true[i]->Write("",TObject::kOverwrite);
        h_Rg_xJ_mc_truef[i]->Write("",TObject::kOverwrite);
        h_Rg_xJ_mc_truef[i]->ProjectionX(Form("h_Rg_truef_%zu",i),2,2)->Write("",TObject::kOverwrite);
        h_Rg_xJ_mc_true[i]->ProjectionX(Form("h_Rg_true_%zu",i),2,2)->Write("",TObject::kOverwrite);

        h_Rg_xJ_mc_truef[i]->ProjectionY(Form("h_xJ_truef_%zu",i),2,2)->Write("",TObject::kOverwrite);
        h_Rg_xJ_mc_true[i]->ProjectionY(Form("h_xJ_true_%zu",i),2,2)->Write("",TObject::kOverwrite);

        hbkg_Rg_xJ_det[i]->Write("",TObject::kOverwrite);

        h_angu_xJ_det[i]->Write("",TObject::kOverwrite);
        h_angu_xJ_det[i]->ProjectionX(Form("h_angu_det_%zu",i),1,1)->Write("",TObject::kOverwrite);
        h_angu_xJ_mc_true[i]->Write("",TObject::kOverwrite);
        h_angu_xJ_mc_truef[i]->Write("",TObject::kOverwrite);
        h_angu_xJ_mc_truef[i]->ProjectionX(Form("h_angu_truef_%zu",i),2,2)->Write("",TObject::kOverwrite);
        h_angu_xJ_mc_true[i]->ProjectionX(Form("h_angu_true_%zu",i),2,2)->Write("",TObject::kOverwrite);

        hbkg_angu_xJ_det[i]->Write("",TObject::kOverwrite);

        h_dynkt_xJ_det[i]->Write("",TObject::kOverwrite);
        h_dynkt_xJ_det[i]->ProjectionX(Form("h_dynkt_det_%zu",i),1,1)->Write("",TObject::kOverwrite);
        h_dynkt_xJ_mc_true[i]->Write("",TObject::kOverwrite);
        h_dynkt_xJ_mc_truef[i]->Write("",TObject::kOverwrite);

        hbkg_dynkt_xJ_det[i]->Write("",TObject::kOverwrite);
    }
    /*
    float S = hdphi_all[0]->Integral(hdphi_all[0]->FindBin(2*TMath::Pi()/3),hdphi_all[0]->GetNbinsX()+2);
    float S_B = hdphi_all[0]->Integral(hdphi_all[0]->FindBin(TMath::Pi()/3),hdphi_all[0]->FindBin(2*TMath::Pi()/3)-1);
    std::cout<<"S = "<<S<<"    |  S+B = "<<S_B<<std::endl;
    std::cout<<"S/S+B = "<<S/S_B<<std::endl;
    
    for (std::size_t i = 0; i < ncent; ++i) {
        // std::cout<<"Number of Bkg Photons in "<<min_cent[i]/2<<" - "<<max_cent[i]/2<<" = "<<hbkg_nPho[i]->GetSum()<<std::endl;
        std::cout<<"Number of Bkg Selected Photons in "<<min_cent[i]/2<<" - "<<max_cent[i]/2<<" = "<<hbkg_nPhosel[i]->GetSum()<<std::endl;
        std::cout<<"Number of Bkg Leading Jets for Selected Photons in "<<min_cent[i]/2<<" - "<<max_cent[i]/2<<" = "<<hbkg_nJet[i]->GetSum()<<std::endl;
    }
    */
    // -------- End Save histograms
    // ------ Plotting Histograms
    
        std::vector<TString>sel = {Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),"|#eta|<1.44",Form("H/E<%6.4f",cut_HoverE),Form("SumIso<%6.4f",cut_SumIso),Form("#sigma_{#eta#eta}<%6.4f",cut_SIEIE)};    

        const int ind1 = 0;
        const int ind2 = 1;
        const int ind3 = 2;

        // Plot_hist2D({h_jetpt_angu[0]},{"JetpT_Angu_0_30"},"text_colz",{"Event weight>1500","Cent. 0-30%"});

        // Plot_hist2D({h_Rg_xJ[0],h_angu_xJ[0],h_ktdyn_xJ[0]},{"Rg_xJ_0_30","Angu_xJ_0_30","Ktdyn_xJ_0_30"},"text",{"Cent. 0-30%"});
        // Plot_hist2D({h_eta_phi_gamma[0],h_eta_phi_jet[0]},{"Gamma_eta_phi_0_30","Jet_eta_phi_0_30"},"colz",{"Cent. 0-30%"});
        // Plot_hist2D({h_eta_phi_gamma[1],h_eta_phi_jet[1]},{"Gamma_eta_phi_30_90","Jet_eta_phi_30_90"},"colz",{"Cent. 30-90%"});
        // Plot_hist2D({h_jetpt_weight[0],h_angu_weight[0],h_Rg_weight[0]},{"JetpT_weight_0_30","Angu_weight_0_30","Rg_weight_0_30"},"text_colz_flow",{"Cent. 0-30%"});
        
        if(!label.Contains("Data")){
            // Plot_hist2D({h_xJ_xJ[0],h_Rg_Rg[0],h_angu_angu[0],h_ktdyn_ktdyn[0]},{"xJ_xJ_0_30","Rg_Rg_0_30","Angu_Angu_0_30","Ktdyn_Ktdyn_0_30"},"colz",{Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),"|#eta|<1.44, Cent. 0-30%","endlog"});
            // Plot_hist2D({h_xJ_g0p4_Rg_Rg[0],h_xJ_g0p4_angu_angu[0],h_xJ_g0p4_dynkt_dynkt[0]},{"xJ_g0p4_Rg_Rg_0_30","xJ_g0p4_Angu_Angu_0_30","xJ_g0p4_Ktdyn_Ktdyn_0_30"},"colztext",{"x_{J}>0.4","|#eta|<1.44, Cent. 0-30%","end"});
            // Plot_hist2D({h_xJ_l0p4_Rg_Rg[0],h_xJ_l0p4_angu_angu[0],h_xJ_l0p4_dynkt_dynkt[0]},{"xJ_l0p4_Rg_Rg_0_30","xJ_l0p4_Angu_Angu_0_30","xJ_l0p4_Ktdyn_Ktdyn_0_30"},"colztext",{"x_{J}<=0.4","|#eta|<1.44, Cent. 0-30%","end"});      
            // Plot_hist2D({h_xJ_g0p4_Rg_Rg[1],h_xJ_g0p4_angu_angu[1],h_xJ_g0p4_dynkt_dynkt[1]},{"xJ_g0p4_Rg_Rg_30_90","xJ_g0p4_Angu_Angu_30_90","xJ_g0p4_Ktdyn_Ktdyn_30_90"},"colztext",{"x_{J}>0.4","|#eta|<1.44, Cent. 30-90%","end"});
            // Plot_hist2D({h_xJ_l0p4_Rg_Rg[1],h_xJ_l0p4_angu_angu[1],h_xJ_l0p4_dynkt_dynkt[1]},{"xJ_l0p4_Rg_Rg_30_90","xJ_l0p4_Angu_Angu_30_90","xJ_l0p4_Ktdyn_Ktdyn_30_90"},"colztext",{"x_{J}<=0.4","|#eta|<1.44, Cent. 30-90%","end"});        
            
            // Plot_hist2D({h_Rg_xJ_mc_true[0],h_Rg_xJ_det[0],h_Rg_xJ_mc_truef[0]},{"Rg_xJ_mc_true_0_30","Rg_xJ_det_0_30","Rg_xJ_mc_truef_0_30"},"text",{"|#eta|<1.44, Cent. 0-30%"});      
            // sel.pop_back();
            // sel.pop_back();
            // sel.pop_back();
            // sel.pop_back();
            // Plot_hist({hres_jetpt[ind1],hres_jetpt[ind2],hres_jetpt[ind3]},{Form("Cent. %d-%d%% #sigma = %4.2f",min_cent_val[ind1]/2,max_cent_val[ind1]/2,hres_jetpt[ind1]->GetRMS()),Form("Cent. %d-%d%% #sigma = %4.2f",min_cent_val[ind2]/2,max_cent_val[ind2]/2,hres_jetpt[ind2]->GetRMS()),Form("Cent. %d-%d%% #sigma = %4.2f",min_cent_val[ind3]/2,max_cent_val[ind3]/2,hres_jetpt[ind3]->GetRMS()),"jet_res"},"normflow",sel);
            // Plot_hist({hres_jetpt[0]},{Form("Cent. %d-%d%% #sigma = %4.2f, #mu = %4.2f",min_cent_val[0]/2,max_cent_val[0]/2,hres_jetpt[0]->GetRMS(),hres_jetpt[0]->GetMean()),"Jet Reco p_{T}-True p_{T}","Events","jet_diff_0_30"},"flowlabel",sel);
            // Plot_hist({hres_xJ[0]},{Form("Cent. %d-%d%% #sigma = %4.2f, #mu = %4.2f",min_cent_val[0]/2,max_cent_val[0]/2,hres_xJ[0]->GetRMS(),hres_xJ[0]->GetMean()),"xJ_res_0_30"},"normflow",sel);
            // Plot_hist({hres_Rg[0]},{Form("Cent. %d-%d%% #sigma = %4.2f, #mu = %4.2f",min_cent_val[0]/2,max_cent_val[0]/2,hres_Rg[0]->GetRMS(),hres_Rg[0]->GetMean()),"Rg_res_0_30"},"normflow",sel);
            // Plot_hist({hres_angu[0]},{Form("Cent. %d-%d%% #sigma = %4.2f, #mu = %4.2f",min_cent_val[0]/2,max_cent_val[0]/2,hres_angu[0]->GetRMS(),hres_angu[0]->GetMean()),"angu_res_0_30"},"normflow",sel);
            // Plot_hist({hrefparton_lead[ind1]},{"","parton_pid"},"right",sel);
            // sel = {Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt), Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2)};
            // Plot_hist2D({h_jetpt_recogen[ind1],h_jeteta_recogen[ind1]},{"recogen_jetpt_0_30","recogen_jeteta_0_30"},"colz",{Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),"end"});
            // Plot_hist({(TH1D*)h_jetpt_recogen[ind1]->ProfileX()},{Form("ProfileX_recogen_jetpt_%d_%d",min_cent_val[ind1]/2,max_cent_val[ind1]/2),"Reco Jet p_{T} (GeV)","#frac{Reco Jet p_{T}}{Gen Jet p_{T}}",Form("ProfileX_recogen_jetpt_%d_%d",min_cent_val[ind1]/2,max_cent_val[ind1]/2)},"leg_label",sel); // ,"Jet p_{T} (GeV)","#frac{Reco Jet p_{T}}{Gen Jet p_{T}}"
            // Plot_hist({(TH1D*)h_jetpt_recogen[ind1]->ProfileY()},{Form("ProfileY_recogen_jetpt_%d_%d",min_cent_val[ind1]/2,max_cent_val[ind1]/2),"#frac{Reco Jet p_{T}}{Gen Jet p_{T}}","Reco Jet p_{T} (GeV)",Form("ProfileY_recogen_jetpt_%d_%d",min_cent_val[ind1]/2,max_cent_val[ind1]/2)},"leg",sel);
            // sel.push_back("60GeV< Gen Jet p_{T} < 80GeV");
            // Plot_hist({(TH1D*)h_jeteta_recogen[ind1]->ProfileX()},{Form("ProfileX_recogen_jeteta_%d_%d",min_cent_val[ind1]/2,max_cent_val[ind1]/2),"Reco Jet #eta","#frac{Reco Jet p_{T}}{Gen Jet p_{T}}",Form("ProfileX_recogen_jeteta_%d_%d",min_cent_val[ind1]/2,max_cent_val[ind1]/2)},"leg_label",sel);
            // Plot_hist({(TH1D*)h_jeteta_recogen[ind1]->ProfileY()},{Form("ProfileY_recogen_jeteta_%d_%d",min_cent_val[ind1]/2,max_cent_val[ind1]/2),"#frac{Reco Jet p_{T}}{Gen Jet p_{T}}","Reco Jet #eta",Form("ProfileY_recogen_jeteta_%d_%d",min_cent_val[ind1]/2,max_cent_val[ind1]/2)},"leg",sel);

            // sel = {Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt), Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2)};
            // Plot_hist2D({h_jetpt_recogen[ind2],h_jeteta_recogen[ind2]},{"recogen_jetpt_0_30","recogen_jeteta_0_30"},"colz",{Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),"end"});
            // Plot_hist({(TH1D*)h_jetpt_recogen[ind2]->ProfileX()},{Form("ProfileX_recogen_jetpt_%d_%d",min_cent_val[ind2]/2,max_cent_val[ind2]/2),"Reco Jet p_{T} (GeV)","#frac{Reco Jet p_{T}}{Gen Jet p_{T}}",Form("ProfileX_recogen_jetpt_%d_%d",min_cent_val[ind2]/2,max_cent_val[ind2]/2)},"leg_label",sel); // ,"Jet p_{T} (GeV)","#frac{Reco Jet p_{T}}{Gen Jet p_{T}}"
            // Plot_hist({(TH1D*)h_jetpt_recogen[ind2]->ProfileY()},{Form("ProfileY_recogen_jetpt_%d_%d",min_cent_val[ind2]/2,max_cent_val[ind2]/2),"#frac{Reco Jet p_{T}}{Gen Jet p_{T}}","Reco Jet p_{T} (GeV)",Form("ProfileY_recogen_jetpt_%d_%d",min_cent_val[ind2]/2,max_cent_val[ind2]/2)},"leg",sel);
            // sel.push_back("60GeV< Gen Jet p_{T} < 80GeV");
            // Plot_hist({(TH1D*)h_jeteta_recogen[ind2]->ProfileX()},{Form("ProfileX_recogen_jeteta_%d_%d",min_cent_val[ind2]/2,max_cent_val[ind2]/2),"Reco Jet #eta","#frac{Reco Jet p_{T}}{Gen Jet p_{T}}",Form("ProfileX_recogen_jeteta_%d_%d",min_cent_val[ind2]/2,max_cent_val[ind2]/2)},"leg_label",sel);
            // Plot_hist({(TH1D*)h_jeteta_recogen[ind2]->ProfileY()},{Form("ProfileY_recogen_jeteta_%d_%d",min_cent_val[ind2]/2,max_cent_val[ind2]/2),"#frac{Reco Jet p_{T}}{Gen Jet p_{T}}","Reco Jet #eta",Form("ProfileY_recogen_jeteta_%d_%d",min_cent_val[ind2]/2,max_cent_val[ind2]/2)},"leg",sel);
        
        }
        // sel = {Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),"|#eta|<1.44",Form("H/E<%6.4f",cut_HoverE),Form("SumIso<%6.4f",cut_SumIso),Form("#sigma_{#eta#eta}<%6.4f",cut_SIEIE)};    
        // All Recoil Jets
        // Plot_hist({hdphi_all[ind1],hdphi_all[ind2],hdphi_all[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"dphi_all"},"leftlog_norm",sel);
        // Plot_hist({hxJ_all[ind1],hxJ_all[ind2],hxJ_all[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"xJ_all"},"right_norm",sel);
        // Plot_hist({hRg_all[ind1],hRg_all[ind2],hRg_all[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"Rg_all"},"right_norm",sel);
        // Plot_hist({hangu_all[ind1],hangu_all[ind2],hangu_all[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"angu_all"},"right_norm",sel);
        // Plot_hist({hktdyn_all[ind1],hktdyn_all[ind2],hktdyn_all[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"ktdyn_all"},"rightlog_norm",sel);
        
        sel = {Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),"|#eta|<1.44, Cent. 0-30%"};
        overlay({hdphi_all[0],hdphi_lead[0]},{"All Recoil Jets","Leading Recoil Jet","#Delta #phi","Norm. Events","dphi_all_lead"},"leftlog_norm_label",sel);
        overlay({hxJ_all[0],hxJ_lead[0]},{"All Recoil Jets","Leading Recoil Jet","xJ","Norm. Events","xJ_all_lead"},"right_norm_label",sel);
        overlay({hRg_all[0],hRg_lead[0]},{"All Recoil Jets","Leading Recoil Jet","R_{g}","Norm. Events","Rg_all_lead"},"right_norm_label",sel);
        overlay({hangu_all[0],hangu_lead[0]},{"All Recoil Jets","Leading Recoil Jet","Angularity","Norm. Events","angu_all_lead"},"right_norm_label",sel);
        overlay({hktdyn_all[0],hktdyn_lead[0]},{"All Recoil Jets","Leading Recoil Jet","dyn k_{T}","Norm. Events","ktdyn_all_lead"},"rightlog_norm_label",sel);
        Plot_hist({hzg_lead[0]},{"Leading Recoil Jet","zg","Norm. Events","zg_all_lead"},"right_norm_label",sel);

        sel = {Form("#gamma p_{T}>%.0f, x_{J}>%.1f",min_pho_et,min_jet_pt),"|#eta|<1.44"};
        Plot_hist({hdphi_all[0],hdphi_all[1]},{Form("Cent. %d-%d%%",min_cent_val[0]/2,max_cent_val[0]/2),Form("Cent. %d-%d%%",min_cent_val[1]/2,max_cent_val[1]/2),"dphi_all_cent"},"leftflowlognorm",sel);

        // Signal Leading Recoil Jet
        // sel = {Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),"|#eta|<1.44",Form("H/E<%6.4f",cut_HoverE),Form("SumIso<%6.4f",cut_SumIso),Form("#sigma_{#eta#eta}<%6.4f",cut_SIEIE)};
        // sel.push_back("Sig Reg - Corrected");    
        // Plot_hist({hdphi_lead[ind1],hdphi_lead[ind2],hdphi_lead[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"dphi_lead"},"leftflowlog_norm",sel);
        // Plot_hist({hxJ_lead[ind1],hxJ_lead[ind2],hxJ_lead[ind3]},{Form("Cent. %d-%d%% #mu = %4.2f",min_cent_val[ind1]/2,max_cent_val[ind1]/2,hxJ_lead[ind1]->GetMean()),Form("Cent. %d-%d%% #mu = %4.2f",min_cent_val[ind2]/2,max_cent_val[ind2]/2,hxJ_lead[ind2]->GetMean()),Form("Cent. %d-%d%% #mu = %4.2f",min_cent_val[ind3]/2,max_cent_val[ind3]/2,hxJ_lead[ind3]->GetMean()),"xJ_lead"},"rightflow_norm",sel);
        // Plot_hist({hRg_lead[ind1],hRg_lead[ind2],hRg_lead[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"Rg_lead"},"rightflow_norm",sel);
        // Plot_hist({hangu_lead[ind1],hangu_lead[ind2],hangu_lead[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"angu_lead"},"rightflow_norm",sel);
        // Plot_hist({hktdyn_lead[ind1],hktdyn_lead[ind2],hktdyn_lead[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"ktdyn_lead"},"rightflowlog",sel);
        // Plot_hist({hzg_lead[ind1],hzg_lead[ind2],hzg_lead[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"zg_lead"},"rightflow_norm",sel);
        // sel.pop_back();

        // Background Leading Recoil Jet
        // sel.pop_back();
        // sel.pop_back();
        // sel.push_back(Form("#sigma_{#eta#eta}<%6.4f",cut_SIEIE));
        // sel.push_back("10<SumIso<=20");
        // sel.push_back(Form("#sigma_{#eta#eta}>=%6.4f",cut_SIEIE));
        // sel.push_back("Bkg Reg - SIEIE");
        // Plot_hist({hbkg_xJ_lead[ind1],hbkg_xJ_lead[ind2],hbkg_xJ_lead[ind3]},{Form("Cent. %d-%d%% #mu = %4.2f",min_cent_val[ind1]/2,max_cent_val[ind1]/2,hbkg_xJ_lead[ind1]->GetMean()),Form("Cent. %d-%d%% #mu = %4.2f",min_cent_val[ind2]/2,max_cent_val[ind2]/2,hbkg_xJ_lead[ind2]->GetMean()),Form("Cent. %d-%d%% #mu = %4.2f",min_cent_val[ind3]/2,max_cent_val[ind3]/2,hbkg_xJ_lead[ind3]->GetMean()),"xJ_lead_bkg"},"rightflownorm",sel);
        // Plot_hist({hbkg_Rg_lead[ind1],hbkg_Rg_lead[ind2],hbkg_Rg_lead[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"Rg_lead_bkg"},"rightflownorm",sel);
        // Plot_hist({hbkg_angu_lead[ind1],hbkg_angu_lead[ind2],hbkg_angu_lead[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"angu_lead_bkg"},"rightflownorm",sel);
        // Plot_hist({hbkg_ktdyn_lead[ind1],hbkg_ktdyn_lead[ind2],hbkg_ktdyn_lead[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"ktdyn_lead_bkg"},"rightflowlognorm",sel);
        // Plot_hist({hbkg_zg_lead[ind1],hbkg_zg_lead[ind2],hbkg_zg_lead[ind3]},{Form("Cent. %d-%d%%",min_cent_val[ind1]/2,max_cent_val[ind1]/2),Form("Cent. %d-%d%%",min_cent_val[ind2]/2,max_cent_val[ind2]/2),Form("Cent. %d-%d%%",min_cent_val[ind3]/2,max_cent_val[ind3]/2),"zg_lead_bkg"},"rightflownorm",sel);
        TH2D* eff_2d=(TH2D*)h_Rg_xJ_mc_true[0]->Clone("eff_2d");
        eff_2d->Divide(h_Rg_xJ_mc_true[0],h_Rg_xJ_mc_truef[0],1,1,"B");
        Plot_hist2D({eff_2d},{"eff_2d_Rg_xJ_text"},"textE_colz",{"Substructure Efficiency","Cent. 0-30%"});
        // Plot_hist({eff_X},{"Efficiency with xJ","eff_Rg"},"right",sel);
        // Plot_hist({eff_Y},{"Efficiency with Rg","eff_xJ"},"right",sel);

        TH2D* h_Rg_eff_match_2d=(TH2D*)h_Rg_xJ_eff_match_num[0]->Clone("h_Rg_eff_match_2d");
        h_Rg_xJ_eff_match_num[0]->Write("Rg_xJ_eff_match_num");
        h_Rg_xJ_eff_match_den[0]->Write("Rg_xJ_eff_match_den");
        h_Rg_eff_match_2d->Divide(h_Rg_xJ_eff_match_num[0],h_Rg_xJ_eff_match_den[0],1,1,"B");
        Plot_hist2D({h_Rg_eff_match_2d},{"eff_matching_2d_Rg_xJ_text"},"textE_colz",{"Matching Efficiency","Cent. 0-30%"});

        TH2D *h_Rg_tot_eff = (TH2D*)eff_2d->Clone("h_Rg_tot_eff");
        h_Rg_tot_eff->Multiply(h_Rg_eff_match_2d);
        Plot_hist2D({h_Rg_tot_eff},{"eff_total_2d_Rg_xJ_text"},"textE_colz",{"Total Efficiency","Cent. 0-30%"});

        Plot_hist2D({h_Rg_xJ_pur_num[0]},{"pur_2d_Rg_xJ_text"},"textE_colz",{"Cent. 0-30%"});
        // Plot_hist({pur_X},{"Purity with xJ","pur_Rg"},"right",sel);
        // Plot_hist({pur_Y},{"Purity with Rg","pur_xJ"},"right",sel);

        printf("\n");
        fout->Close();
    // ------ End Plotting Histograms
}

void Plot_hist(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "leg" = DO NOT draw legend
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
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41,
                                        20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};

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
            hist[ihist+1]->SetLineColor(colarray[ihist]);
            hist[ihist+1]->SetMarkerColor(colarray[ihist]);
            hist[ihist+1]->SetMarkerStyle(markarray[ihist]);
            hist[ihist+1]->Divide(hist[ihist+1],hist[0],1,1);
            ihist++;
        }
        else{
            hist[ihist]->SetLineColor(colarray[ihist]);
            hist[ihist]->SetMarkerColor(colarray[ihist]);
            hist[ihist]->SetMarkerStyle(markarray[ihist]);
        }
        if(opt.Contains("norm_width")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2),"width");
        }
        else if(opt.Contains("norm")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(1,hist[ihist]->GetNbinsX()+1));
        }
        if(opt.Contains("flow"))
            hist[ihist]->GetXaxis()->SetRange(0,hist[ihist]->GetNbinsX()+2);
        hs.Add(hist[ihist]);      
        l->AddEntry(hist[ihist], histname[ihist], "lep");
        if(!opt.Contains("eff")) ihist++;
    }
    hs.Draw(drawopt);
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


    TLatex latex;
    latex.SetTextSize(0.035);
    if(label.Contains("Data"))
        latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Preliminary}} PbPb 1.6967nb^{-1}(5.02 TeV)");
    else
        latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Preliminary Simulation}}");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.41,0.92,eopt[0]);
        latex.DrawLatexNDC(0.78,0.92,eopt[1]);
    }    
    latex.SetTextSize(0.025);
    if(eopt.size()>2){
        for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
            if(opt.Contains("bcenter")){
                leg_y2+=0.05;
                latex.DrawLatexNDC(leg_x1,leg_y2,eopt[ind]);
            }
            else{
                leg_y1-=0.05;
                latex.DrawLatexNDC(leg_x1,leg_y1,eopt[ind]);
            }
        }
    }
    gPad->Update();
    c->SaveAs(output_path + "/OutputPlots_"+label+"/"+histname.back()+".png");
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

    TCanvas *c;
    // TLegend *l;
    float leg_x1 = 0.7;
    float leg_y1 = 0.7;
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
        leg_y1 = 0.7;
        leg_x2 = 0.25;
        leg_y2 = 0.85;
    }

    // l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    // l->SetFillStyle(0);
    // l->SetFillColor(0);
    // l->SetLineColor(0);
    // l->SetTextSize(0.025);
    // l->SetTextFont(42);
    // l->Draw();
    


    for(std::size_t ihist=0; ihist<hist.size();ihist++){
        c = new TCanvas();
        gStyle->SetPaintTextFormat("4.3f");
        hist[ihist]->SetMarkerSize(1.5);  
        
        if(eopt.back().Contains("flow")){
            hist[ihist]->GetXaxis()->SetRange(1,hist[ihist]->GetNbinsX()+2);
            hist[ihist]->GetYaxis()->SetRange(0,hist[ihist]->GetNbinsY()+2);
        }
        hist[ihist]->Draw(drawopt);   
        TLatex latex;
        latex.SetTextSize(0.035);
        if(label.Contains("Data"))
            latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Preliminary}} PbPb 1.6967nb^{-1}(5.02 TeV)");
        else
            latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Preliminary Simulation}}");

        if(eopt[0].Contains("Cent")){
            latex.DrawLatexNDC(0.78,0.92,eopt[0]);
        }
        else if(eopt.size()>=2){
            latex.DrawLatexNDC(0.5,0.92,eopt[0]);
            latex.DrawLatexNDC(0.78,0.92,eopt[1]);
        }    
        latex.SetTextSize(0.025);
        if(eopt.size()>2){
            for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
                if(eopt.back().Contains("bcenter")){
                    leg_y2+=0.05;
                    latex.DrawLatexNDC(leg_x1,leg_y2,eopt[ind]);
                }
                else{
                    leg_y1-=0.05;
                    latex.DrawLatexNDC(leg_x1,leg_y1,eopt[ind]);
                }
            }
        }
        gPad->Update();
        c->SaveAs(output_path + "/OutputPlots_"+label+"/"+histname[ihist]+".png");
        c->Write(histname[ihist],TObject::kWriteDelete);
        std::cout<<histname[ihist]<<" has been saved"<<std::endl;
    }

    if(eopt.back().Contains("log")) gStyle->SetOptLogz(0);
    
    // delete l;
}

void overlay(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // Based on the old Ratio Plot script from https://root.cern/doc/master/ratioplotOld_8C.html

    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "width" = Divide by Bin Width
    // "opt" = drawopt is last element of eopt

    if(hist.size()<2){
        std::cout<<"Not Enough Histograms"<<std::endl;
        return;
    }

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetHistTopMargin(0);
    if(opt.Contains("log")) gStyle->SetOptLogy(1);
    
    TString drawopt = "E1][P0"; 
    if(opt.Contains("opt"))
        drawopt = eopt.back();
    const std::vector<int> colarray  = {1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606,
                                       1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41,
                                        20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};

    TCanvas *c= new TCanvas();
    c->cd();
    TLegend *l;
    float leg_x1 = 0.7;
    float leg_y1 = 0.7;
    float leg_x2 = 0.8;
    float leg_y2 = 0.85;
    if(opt.Contains("bcenter")){
        leg_x1 = 0.45;
        leg_y1 = 0.15;
        leg_x2 = 0.55;
        leg_y2 = 0.3;
    }
    else if(opt.Contains("left")){
        leg_x1 = 0.15;
        leg_y1 = 0.7;
        leg_x2 = 0.25;
        leg_y2 = 0.85;
    }
    l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    l->SetFillStyle(0);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->SetTextSize(0.025);
    l->SetTextFont(42);
        
    // Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetTopMargin(0.15);
    pad1->SetRightMargin(0.05); 
    pad1->SetLeftMargin(0.12); 
    pad1->SetBottomMargin(0.05); 
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    float ymax = -99999;
    for(std::size_t ihist=0; ihist<hist.size();ihist++){

        hist[ihist]->SetLineColor(colarray[ihist]);
        hist[ihist]->SetMarkerColor(colarray[ihist]);
        hist[ihist]->SetMarkerStyle(markarray[ihist]);        
        if(opt.Contains("norm_width")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2),"width");
        }
        else if(opt.Contains("norm")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2));
        }
        if(opt.Contains("flow"))
            hist[ihist]->GetXaxis()->SetRange(0,hist[ihist]->GetNbinsX()+2);   
        
        if(hist[ihist]->GetMaximum()>ymax) ymax = hist[ihist]->GetMaximum();
        hist[ihist]->Draw(drawopt);
        hist[ihist]->GetXaxis()->SetLabelSize(0);
        hist[ihist]->GetXaxis()->SetTitleOffset(999999);
        l->AddEntry(hist[ihist], histname[ihist], "lep");
        if(ihist==0) drawopt+="SAME";
    }
    if(!opt.Contains("log"))
        hist[0]->SetMaximum(ymax*1.1);
    else
        hist[0]->SetMaximum(ymax*2);
        
    // lower plot will be in pad
    c->cd();          // Go back to the main canvas before defining pad2
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3);
    // pad2->SetFillStyle(4000);
    pad2->SetTopMargin(0.05);
    pad2->SetRightMargin(0.05); 
    pad2->SetLeftMargin(0.12); 
    pad2->SetBottomMargin(0.3); 
    pad2->SetGrid();
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad

    // Define the ratio plot
    TH1D *hratio = (TH1D*)hist[0]->Clone(histname[0]);
    for(std::size_t ihist=1; ihist<hist.size();ihist++){
        hratio = (TH1D*)hist[ihist]->Clone(histname[ihist]);
        hratio->SetLineColor(colarray[ihist]);
        hratio->SetMarkerColor(colarray[ihist]);
        hratio->SetMarkerStyle(markarray[ihist]);   

        if(!opt.Contains("log")){
            hratio->SetMinimum(0.5);  // Define Y ..
            hratio->SetMaximum(1.5); // .. range
        }

        hratio->Sumw2();
        hratio->Divide(hist[0]);
        hratio->Draw(drawopt);

        // Y axis ratio plot settings
        hratio->GetYaxis()->SetTitle("Ratio   ");
        hratio->GetYaxis()->SetNdivisions(10);
        hratio->GetYaxis()->SetTitleSize(0.12);
        hratio->GetYaxis()->SetTitleOffset(0.32);
        hratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
        hratio->GetYaxis()->SetLabelSize(15);
        
        // X axis ratio plot settings
        hratio->GetXaxis()->SetTitleSize(0.12);
        hratio->GetXaxis()->SetTitleOffset(1.0);
        hratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
        hratio->GetXaxis()->SetLabelSize(15);
    }
    c->cd();  

    if(opt.Contains("label")){
        hratio->GetXaxis()->SetTitle(histname.at(histname.size()-3));
        hist[0]->GetYaxis()->SetTitle(histname.at(histname.size()-2));
    }
    else{
        hratio->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
        hist[0]->GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());
    }

    // Y axis upper plot settings
        hist[0]->GetYaxis()->SetTitleSize(15);
        hist[0]->GetYaxis()->SetTitleFont(43);
        hist[0]->GetYaxis()->SetTitleOffset(1.5);
        hist[0]->GetYaxis()->SetLabelSize(0.05);

    l->Draw();

    TLatex latex;
    latex.SetTextSize(0.035);
    if(label.Contains("Data"))
        latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Preliminary}} PbPb 1.6967nb^{-1}(5.02 TeV)");
    else
        latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Preliminary Simulation}}");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.41,0.92,eopt[0]);
        latex.DrawLatexNDC(0.78,0.92,eopt[1]);
    }    
    latex.SetTextSize(0.025);
    if(eopt.size()>2){
        for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
            if(opt.Contains("bcenter")){
                leg_y2+=0.05;
                latex.DrawLatexNDC(leg_x1,leg_y2,eopt[ind]);
            }
            else{
                leg_y1-=0.05;
                latex.DrawLatexNDC(leg_x1,leg_y1,eopt[ind]);
            }
        }
    }
    gPad->Update();
    c->SaveAs(output_path + "/OutputPlots_"+label+"/"+histname.back()+".png");
    c->Write(histname.back(),TObject::kWriteDelete);
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}


int main(int argc, char* argv[]){

    // printf("argc = %d\n",aRgc);
    // printf("argv = %s\n",aRgv[0]);
    if(argc==3){
        output_path = argv[1];
        label = argv[2];
        plot_jet();
    }
    else{
        printf("Run with \n ./plot_jet <output dir> <label>\n");
    }

    return 0;
}
