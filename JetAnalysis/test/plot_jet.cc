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

const std::vector<int> min_cent = { 0,  60,   0,  0, 20,  60, 100};
const std::vector<int> max_cent = {60, 180, 180, 20, 60, 100, 180};
const std::size_t ncent = min_cent.size();
TString label="";
TString output_path = "./";

void Plot_hist(std::vector<TH1F*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void Plot_hist2D(std::vector<TH2F*> hist,std::vector<TString> histname,TString dopt="colz",std::vector<TString> eopt={"end"});

void overlay(std::vector<TH1F*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

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
        Int_t   L1_SingleEG21_BptxAND = 0;
        Int_t   HLT_HIGEDPhoton40_v1 = 0;

        jet_tree.SetBranchAddress("phoSCRawE",&phoSCRawE);
        jet_tree.SetBranchAddress("phoSCEta",&phoSCEta);
        jet_tree.SetBranchAddress("phoSCPhi",&phoSCPhi);
        jet_tree.SetBranchAddress("phoSigmaIEtaIEta_2012",&phoSigmaIEtaIEta_2012);
        jet_tree.SetBranchAddress("rho",&rho);

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

        jet_tree.SetBranchAddress("nref", &nref);
        jet_tree.SetBranchAddress("jet_index", &jet_index);
        jet_tree.SetBranchAddress("jtpt", &jtpt);
        jet_tree.SetBranchAddress("jteta", &jteta);
        jet_tree.SetBranchAddress("jtphi", &jtphi);
        jet_tree.SetBranchAddress("jtsym", &jtsym);
        jet_tree.SetBranchAddress("jtrg", &jtrg);
        jet_tree.SetBranchAddress("jtdynkt", &jtdynkt);
        jet_tree.SetBranchAddress("jtangu", &jtangu);

        if(!label.Contains("Data")){
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
        }

    // -------- End Tree Variable Declaration
    // ----------------------------------------------------------------------------------------------------------------
    // Histograms
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

        TH1F* hnPho[ncent];
        TH1F* hnPhosel[ncent];
        TH1F* hnJet[ncent];

        TH1F* hres_jetpt[ncent];
        
        TH1F* hdphi_all[ncent];
        TH1F* hxJ_all[ncent];
        TH1F* hRg_all[ncent];
        TH1F* hangu_all[ncent];
        TH1F* hktdyn_all[ncent];

        TH1F* hdphi_lead[ncent];
        TH1F* hxJ_lead[ncent];
        TH1F* hRg_lead[ncent];
        TH1F* hangu_lead[ncent];
        TH1F* hktdyn_lead[ncent];

        TH2F* h_Rg_xJ[ncent];
        TH2F* h_angu_xJ[ncent];
        TH2F* h_ktdyn_xJ[ncent];
        // TH2F* h_lnktdyn_xJ[ncent]; ln kt for later?

        TH2F* h_xJ_xJ[ncent];
        TH2F* h_Rg_Rg[ncent];
        TH2F* h_angu_angu[ncent];
        TH2F* h_ktdyn_ktdyn[ncent];

        TH2F* h_xJ_l0p6_Rg_Rg[ncent];
        TH2F* h_xJ_l0p6_angu_angu[ncent];
        TH2F* h_xJ_l0p6_dynkt_dynkt[ncent];
        TH2F* h_xJ_g0p6_Rg_Rg[ncent];
        TH2F* h_xJ_g0p6_angu_angu[ncent];
        TH2F* h_xJ_g0p6_dynkt_dynkt[ncent];

        TH1F* hbkg_nPhosel[ncent];
        TH1F* hbkg_nJet[ncent];

        TH1F* hbkg_xJ_all[ncent];
        TH1F* hbkg_Rg_all[ncent];
        TH1F* hbkg_angu_all[ncent];
        TH1F* hbkg_ktdyn_all[ncent];

        TH1F* hbkg_xJ_lead[ncent];
        TH1F* hbkg_Rg_lead[ncent];
        TH1F* hbkg_angu_lead[ncent];
        TH1F* hbkg_ktdyn_lead[ncent];

        // Unfolding Plots

        TH2F* h_Rg_xJ_det[ncent];
        TH2F* h_Rg_xJ_mc_true[ncent];
        TH2F* h_Rg_xJ_mc_truef[ncent];

        TH2F* hbkg_Rg_xJ_det[ncent];

        TH2F* h_angu_xJ_det[ncent];
        TH2F* h_angu_xJ_mc_true[ncent];
        TH2F* h_angu_xJ_mc_truef[ncent];

        TH2F* hbkg_angu_xJ_det[ncent];
        
        TH2F* h_dynkt_xJ_det[ncent];
        TH2F* h_dynkt_xJ_mc_true[ncent];
        TH2F* h_dynkt_xJ_mc_truef[ncent];

        TH2F* hbkg_dynkt_xJ_det[ncent];

        // inputs for Unfolding 
            const int bin_det_xj=2;
            const int bin_true_xj=3;
            const int bin_det_Rg=4;
            const int bin_true_Rg=5;
            const int bin_det_angu=4;
            const int bin_true_angu=5;
            const int bin_det_dynkt=3;
            const int bin_true_dynkt=5;

            Double_t xjmin_det=0.;
            Double_t xjmin_true=0;

            Double_t xjmax_det=1.6;
            Double_t xjmax_true=2;

            Double_t Rgmax_det=0.2;
            Double_t Rgmax_true=0.3;
            
            Double_t Rgmin_det=0.0;
            Double_t Rgmin_true=0.0;

            Double_t angumax_det=0.08;
            Double_t angumax_true=0.1;
            
            Double_t angumin_det=0.;
            Double_t angumin_true=0.;

            Double_t dynktmax_det=10.0;
            Double_t dynktmax_true=50.0;
            
            Double_t dynktmin_det=1.5;
            Double_t dynktmin_true=0.;

            Double_t xJ_det_edges[bin_det_xj+1] = {xjmin_det, 0.6, xjmax_det};
            Double_t xJ_true_edges[bin_true_xj+1] = {xjmin_true, 0.6, 1.6, xjmax_true};
            Double_t Rg_det_edges[bin_det_Rg+1] = {-0.05, 0, 0.05, 0.1, Rgmax_det};
            Double_t Rg_true_edges[bin_true_Rg+1] = {-0.05, 0, 0.05, 0.1, 0.2, Rgmax_true};
            Double_t angu_det_edges[bin_det_angu+1] = {angumin_det, 0.02, 0.04, 0.06, angumax_det};
            Double_t angu_true_edges[bin_true_angu+1] = {angumin_true, 0.02, 0.04, 0.06, 0.08, angumax_true};
            Double_t dynkt_det_edges[bin_det_dynkt+1] = {dynktmin_det, 2.5,4.0,dynktmax_det};
            Double_t dynkt_true_edges[bin_true_dynkt+1] = {dynktmin_true, 1.5,2.5,4.0,10.0,dynktmax_true};
        
        const Int_t nkt_bins = 8;
        Double_t kt_edges[nkt_bins+1] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 8.0, 12.0, 20.0};

        for (std::size_t i = 0; i < ncent; ++i) {
            hnPho[i] = new TH1F(Form("hnPho_%zu", i), Form("hnPho_%zu;nPho;Norm. Events", i), 1, 0, 2);
            hnPhosel[i] = new TH1F(Form("hnPhosel_%zu", i), Form("hnPhosel_%zu;nPho;Norm. Events", i), 1, 0, 2);
            hnJet[i] = new TH1F(Form("hnJet_%zu", i), Form("hnJet_%zu;nJet;Norm. Events", i), 1, 0, 2);

            hres_jetpt[i] = new TH1F(Form("hres_jetpt_%zu", i), Form("hres_jetpt_%zu;(Jet Reco p_{T} - True p_{T})/True p_{T};Events", i), 64, -1, 1);

            int nbins = 20;

            hdphi_all[i] = new TH1F(Form("hdphi_all_%zu", i), Form("hdphi_all_%zu;#Delta #phi;Events", i), nbins, 0, 3.2);
            hxJ_all[i] = new TH1F(Form("hxJ_all_%zu", i), Form("hxJ_all_%zu;All Recoil Jet p_{T}/Photon E_{T};Events", i), nbins, 0, 2.0);
            hRg_all[i] = new TH1F(Form("hRg_all_%zu", i), Form("hRg_all_%zu;R_{g};Events", i), nbins, 0, 0.25);
            hangu_all[i] = new TH1F(Form("hangu_all_%zu", i), Form("hangu_all_%zu;Angularity;Events", i), nbins, 0, 0.12);
            hktdyn_all[i] = new TH1F(Form("hktdyn_all_%zu", i), Form("hktdyn_all_%zu;dyn k_{T};Events", i), nkt_bins, kt_edges);

            hdphi_lead[i] = new TH1F(Form("hdphi_lead_%zu", i), Form("hdphi_lead_%zu;#Delta #phi;1/N_{jet} dN/d#Delta #phi", i), nbins, 0, 3.2);
            hxJ_lead[i] = new TH1F(Form("hxJ_lead_%zu", i), Form("hxJ_lead_%zu;Lead Recoil Jet p_{T}/Photon E_{T};1/N_{jet} dN/dp_{T,Jet}", i), nbins, 0, 2.0);
            hRg_lead[i] = new TH1F(Form("hRg_lead_%zu", i), Form("hRg_lead_%zu;R_{g};1/N_{jet} dN/dR_{g}", i), nbins, 0, 0.25);
            hangu_lead[i] = new TH1F(Form("hangu_lead_%zu", i), Form("hangu_lead_%zu;Angularity;1/N_{jet} dN/dAngularity", i), nbins, 0, 0.12);
            hktdyn_lead[i] = new TH1F(Form("hktdyn_lead_%zu", i), Form("hktdyn_lead_%zu;dyn k_{T};1/N_{jet} dN/dk_{T}", i), nkt_bins, kt_edges);

            h_Rg_xJ[i]=new TH2F(Form("h_Rg_xJ_%zu",i),Form("h_Rg_xJ_%zu;Rg;x_{#gamma,jet}",i),16,0,0.4,20,0,2.0);
            h_angu_xJ[i]=new TH2F(Form("h_angu_xJ_%zu",i),Form("h_angu_xJ_%zu;Angularity;x_{#gamma,jet}",i),16,0,0.12,20,0,2.0);
            h_ktdyn_xJ[i]=new TH2F(Form("h_ktdyn_xJ_%zu",i),Form("h_ktdyn_xJ_%zu;dyn k_{T};x_{#gamma,jet}",i),20,0,20,20,0,2.0);

            h_xJ_xJ[i]=new TH2F(Form("h_xJ_xJ_%zu",i),Form("h_xJ_xJ_%zu;x_{#gamma,jet} Reco;x_{#gamma,jet} True",i),20,0,2.0,20,0,2.0);
            h_Rg_Rg[i]=new TH2F(Form("h_Rg_Rg_%zu",i),Form("h_Rg_Rg_%zu;R_{g} Reco;R_{g} True",i),16,0,0.25,16,0,0.25);
            h_angu_angu[i]=new TH2F(Form("h_angu_angu_%zu",i),Form("h_angu_angu_%zu;Angularity Reco;Angularity True",i),16,0,0.12,16,0,0.12);
            h_ktdyn_ktdyn[i]=new TH2F(Form("h_ktdyn_ktdyn_%zu",i),Form("h_ktdyn_ktdyn_%zu;dyn k_{T} Reco;dyn k_{T} True",i),20,0,20,20,0,20);

            h_xJ_l0p6_Rg_Rg[i]=new TH2F(Form("h_xJ_l0p6_Rg_Rg_%zu",i),Form("h_xJ_l0p6_Rg_Rg_%zu;R_{g} Reco;R_{g} True",i),bin_det_Rg,Rg_det_edges,bin_true_Rg,Rg_true_edges);
            h_xJ_l0p6_angu_angu[i]=new TH2F(Form("h_xJ_l0p6_angu_angu_%zu",i),Form("h_xJ_l0p6_angu_angu_%zu;Angularity Reco;Angularity True",i),bin_det_angu,angu_det_edges,bin_true_angu,angu_true_edges);
            h_xJ_l0p6_dynkt_dynkt[i]=new TH2F(Form("h_xJ_l0p6_dynkt_dynkt_%zu",i),Form("h_xJ_l0p6_dynkt_dynkt_%zu;dyn k_{T} Reco;dyn k_{T} True",i),bin_det_dynkt,dynkt_det_edges,bin_true_dynkt,dynkt_true_edges);

            h_xJ_g0p6_Rg_Rg[i]=new TH2F(Form("h_xJ_g0p6_Rg_Rg_%zu",i),Form("h_xJ_g0p6_Rg_Rg_%zu;R_{g} Reco;R_{g} True",i),bin_det_Rg,Rg_det_edges,bin_true_Rg,Rg_true_edges);
            h_xJ_g0p6_angu_angu[i]=new TH2F(Form("h_xJ_g0p6_angu_angu_%zu",i),Form("h_xJ_g0p6_angu_angu_%zu;Angularity Reco;Angularity True",i),bin_det_angu,angu_det_edges,bin_true_angu,angu_true_edges);
            h_xJ_g0p6_dynkt_dynkt[i]=new TH2F(Form("h_xJ_g0p6_dynkt_dynkt_%zu",i),Form("h_xJ_g0p6_dynkt_dynkt_%zu;dyn k_{T} Reco;dyn k_{T} True",i),bin_det_dynkt,dynkt_det_edges,bin_true_dynkt,dynkt_true_edges);

            // --- Bkg Histograms

            hbkg_nPhosel[i] = new TH1F(Form("hbkg_nPhosel_%zu", i), Form("hbkg_nPhosel_%zu;nPho;Norm. Events", i), 1, 0, 1);
            hbkg_nJet[i] = new TH1F(Form("hbkg_nJet_%zu", i), Form("hbkg_nJet_%zu;nJet;Norm. Events", i), 1, 0, 1);

            hbkg_xJ_all[i] = new TH1F(Form("hbkg_xJ_all_%zu", i), Form("hbkg_xJ_all_%zu;All Recoil Jet p_{T}/Photon E_{T};Events", i), nbins, 0, 2.0);
            hbkg_Rg_all[i] = new TH1F(Form("hbkg_Rg_all_%zu", i), Form("hbkg_Rg_all_%zu;R_{g};Events", i), nbins, 0, 0.25);
            hbkg_angu_all[i] = new TH1F(Form("hbkg_angu_all_%zu", i), Form("hbkg_angu_all_%zu;Angularity;Events", i), nbins, 0, 0.12);
            hbkg_ktdyn_all[i] = new TH1F(Form("hbkg_ktdyn_all_%zu", i), Form("hbkg_ktdyn_all_%zu;dyn k_{T};Events", i), nkt_bins, kt_edges);

            hbkg_xJ_lead[i] = new TH1F(Form("hbkg_xJ_lead_%zu", i), Form("hbkg_xJ_lead_%zu;Lead Recoil Jet p_{T}/Photon E_{T};1/N_{jet} dN/dp_{T,Jet}", i), nbins, 0, 2.0);
            hbkg_Rg_lead[i] = new TH1F(Form("hbkg_Rg_lead_%zu", i), Form("hbkg_Rg_lead_%zu;R_{g};1/N_{jet} dN/dR_{g}", i), nbins, 0, 0.25);
            hbkg_angu_lead[i] = new TH1F(Form("hbkg_angu_lead_%zu", i), Form("hbkg_angu_lead_%zu;Angularity;1/N_{jet} dN/dAngularity", i), nbins, 0, 0.12);
            hbkg_ktdyn_lead[i] = new TH1F(Form("hbkg_ktdyn_lead_%zu", i), Form("hbkg_ktdyn_lead_%zu;dyn k_{T};1/N_{jet} dN/dk_{T}", i), nkt_bins, kt_edges);

            // ---- Unfolding Histograms

            h_Rg_xJ_det[i]=new TH2F(Form("h_Rg_xJ_det_%zu",i),Form("h_Rg_xJ_det_%zu;Rg;x_{#gamma,jet}",i),bin_det_Rg,Rg_det_edges,bin_det_xj,xJ_det_edges);
            h_Rg_xJ_mc_true[i]=new TH2F(Form("h_Rg_xJ_mc_true_%zu",i),Form("h_Rg_xJ_mc_true_%zu;Rg;x_{#gamma,jet}",i),bin_true_Rg,Rg_true_edges,bin_true_xj,xJ_true_edges);
            h_Rg_xJ_mc_truef[i]=new TH2F(Form("h_Rg_xJ_mc_truef_%zu",i),Form("h_Rg_xJ_mc_truef_%zu;Rg;x_{#gamma,jet}",i),bin_true_Rg,Rg_true_edges,bin_true_xj,xJ_true_edges);

            hbkg_Rg_xJ_det[i]=new TH2F(Form("hbkg_Rg_xJ_det_%zu",i),Form("hbkg_Rg_xJ_det_%zu;Rg;x_{#gamma,jet}",i),bin_det_Rg,Rg_det_edges,bin_det_xj,xJ_det_edges);

            h_angu_xJ_det[i]=new TH2F(Form("h_angu_xJ_det_%zu",i),Form("h_angu_xJ_det_%zu;angu;x_{#gamma,jet}",i),bin_det_angu,angu_det_edges,bin_det_xj,xJ_det_edges);
            h_angu_xJ_mc_true[i]=new TH2F(Form("h_angu_xJ_mc_true_%zu",i),Form("h_angu_xJ_mc_true_%zu;angu;x_{#gamma,jet}",i),bin_true_angu,angu_true_edges,bin_true_xj,xJ_true_edges);
            h_angu_xJ_mc_truef[i]=new TH2F(Form("h_angu_xJ_mc_truef_%zu",i),Form("h_angu_xJ_mc_truef_%zu;angu;x_{#gamma,jet}",i),bin_true_angu,angu_true_edges,bin_true_xj,xJ_true_edges);

            hbkg_angu_xJ_det[i]=new TH2F(Form("hbkg_angu_xJ_det_%zu",i),Form("hbkg_angu_xJ_det_%zu;angu;x_{#gamma,jet}",i),bin_det_angu,angu_det_edges,bin_det_xj,xJ_det_edges);

            h_dynkt_xJ_det[i]=new TH2F(Form("h_dynkt_xJ_det_%zu",i),Form("h_dynkt_xJ_det_%zu;dynkt;x_{#gamma,jet}",i),bin_det_dynkt,dynkt_det_edges,bin_det_xj,xJ_det_edges);
            h_dynkt_xJ_mc_true[i]=new TH2F(Form("h_dynkt_xJ_mc_true_%zu",i),Form("h_dynkt_xJ_mc_true_%zu;dynkt;x_{#gamma,jet}",i),bin_true_dynkt,dynkt_true_edges,bin_true_xj,xJ_true_edges);
            h_dynkt_xJ_mc_truef[i]=new TH2F(Form("h_dynkt_xJ_mc_truef_%zu",i),Form("h_dynkt_xJ_mc_truef_%zu;dynkt;x_{#gamma,jet}",i),bin_true_dynkt,dynkt_true_edges,bin_true_xj,xJ_true_edges);

            hbkg_dynkt_xJ_det[i]=new TH2F(Form("hbkg_dynkt_xJ_det_%zu",i),Form("hbkg_dynkt_xJ_det_%zu;dynkt;x_{#gamma,jet}",i),bin_det_dynkt,dynkt_det_edges,bin_det_xj,xJ_det_edges);
        }

    // -------- End Histograms
    // ----------------------------------------------------------------------------------------------------------------
    // Event Loop

    const float min_pho_et = 100;
    const float cut_HoverE = 0.137168;  // 0.0696672;
    const float cut_SIEIE  = 0.0103766; // 0.00983515;
    const float cut_SumIso = 1.45486;   // 1.33546;
    const float min_jet_pt = 40;
    const float purity_values[ncent] = {0.791,0.899,0.819,0.737,0.838,0.903,0.895};

    Int_t nEv=jet_tree.GetEntries();
    for(int iEntry=0; iEntry<nEv; iEntry++){
        jet_tree.GetEntry(iEntry);
        float scale =1;
                
        if(!label.Contains("Data")){
            scale*=weight*weight_pthat*weight_cent;
            if(pho_genMatchedIndex<0) continue;
            if(abs(mcPID)!=22) continue;
        }
        
        for (std::size_t i = 0; i < ncent; ++i) {
            if(!(hiBin>=min_cent[i] && hiBin<max_cent[i])) continue;
            if(!(abs(phoSCEta)<1.44)) continue;
            if(!(phoEtCorrected>min_pho_et)) continue;
            if(!L1_SingleEG21_BptxAND) continue;    // TRIGGERS APPLIED AT NTUPLIZER
            if(!HLT_HIGEDPhoton40_v1) continue;

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
            }
            else if(flagbkg){
                hbkg_nPhosel[i]->Fill(1,scale);
            }

            // -------- End Photon Selection
            // Jet Loop----------------------------------------------------------------------------------

            int jet_index=-1;
            float jet_pt_max=-1;
            float jet_dphi_max=-1;
            float jet_xJ_max=-1;
            float jet_true_xJ_max=-1;
            float jet_Rg_max=-1;
            float jet_true_Rg_max=-1;

            for(int ijet=0; ijet<nref;ijet++){
                if(jtpt[ijet]<min_jet_pt) continue;
                if(abs(jteta[ijet])>2) continue;
                float dphi = abs(TVector2::Phi_mpi_pi(phoPhi-jtphi[ijet]));// ROOT::Math::VectorUtil::Phi_mpi_pi(phoPhi,jtphi[ijet]);
                float xJ = jtpt[ijet]/phoEtCorrected;
                float true_xJ = -1;
                if(!label.Contains("Data"))
                    true_xJ = refpt[ijet]/mcEt;
                hdphi_all[i]->Fill(dphi,scale);
                hres_jetpt[i]->Fill((jtpt[ijet]-refpt[ijet])/refpt[ijet],scale);

                if(dphi>2*TMath::Pi()/3){
                    if(jet_pt_max<jtpt[ijet]){
                        jet_pt_max = jtpt[ijet];
                        jet_dphi_max = dphi;
                        jet_xJ_max = xJ;
                        jet_true_xJ_max = true_xJ;
                        jet_Rg_max = jtrg[ijet];
                        jet_true_Rg_max = refrg[ijet];
                        jet_index = ijet;
                    }
                    if(flagsig){
                        hxJ_all[i]->Fill(xJ,scale);
                        hRg_all[i]->Fill(jtrg[ijet],scale);
                        hangu_all[i]->Fill(jtangu[ijet],scale);
                        hktdyn_all[i]->Fill(jtdynkt[ijet],scale);
                    }
                    else if(flagbkg){
                        hbkg_xJ_all[i]->Fill(xJ,scale);
                        hbkg_Rg_all[i]->Fill(jtrg[ijet],scale);
                        hbkg_angu_all[i]->Fill(jtangu[ijet],scale);
                        hbkg_ktdyn_all[i]->Fill(jtdynkt[ijet],scale);
                    }
                }
            }
            if(jet_index==-1) continue;

            hdphi_lead[i]->Fill(jet_dphi_max,scale);
            if(flagsig){
                hnJet[i]->Fill(1,scale);

                hxJ_lead[i]->Fill(jet_xJ_max,scale);
                hRg_lead[i]->Fill(jet_Rg_max,scale);
                hangu_lead[i]->Fill(jtangu[jet_index],scale);
                hktdyn_lead[i]->Fill(jtdynkt[jet_index],scale);

                if(!label.Contains("Data")){
                    if(jet_true_xJ_max>=xjmin_true && jet_true_xJ_max<=xjmax_true 
                    && jet_true_Rg_max>=Rgmin_true && jet_true_Rg_max<=Rgmax_true){
                        if(jet_true_Rg_max<=0) jet_true_Rg_max = -0.025;
                        h_Rg_xJ_mc_truef[i]->Fill(jet_true_Rg_max,jet_true_xJ_max,scale);

                        if(jet_xJ_max>=xjmin_det && jet_xJ_max<=xjmax_det 
                        && jet_Rg_max>=Rgmin_det && jet_Rg_max<=Rgmax_det){
                            if(jet_Rg_max<=0) jet_Rg_max = -0.025;

                            h_Rg_xJ_mc_true[i]->Fill(jet_true_Rg_max,jet_true_xJ_max,scale);
                            h_Rg_xJ_det[i]->Fill(jet_Rg_max,jet_xJ_max,scale);

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
                            var_weightFinal = scale;
                            tree_xj_Rg->Fill();
                        }
                    }

                    if(jet_true_xJ_max>=xjmin_true && jet_true_xJ_max<=xjmax_true 
                    && refangu[jet_index]>=angumin_true && refangu[jet_index]<=angumax_true){
                        h_angu_xJ_mc_truef[i]->Fill(refangu[jet_index],jet_true_xJ_max,scale);

                        if(jet_xJ_max>=xjmin_det && jet_xJ_max<=xjmax_det 
                        && jtangu[jet_index]>=angumin_det && jtangu[jet_index]<=angumax_det){

                            h_angu_xJ_mc_true[i]->Fill(refangu[jet_index],jet_true_xJ_max,scale);
                            h_angu_xJ_det[i]->Fill(jtangu[jet_index],jet_xJ_max,scale);

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
                            var_weightFinal = scale;
                            tree_xj_angu->Fill();
                        }
                    }

                    if(jet_true_xJ_max>=xjmin_true && jet_true_xJ_max<=xjmax_true 
                    && refdynkt[jet_index]>=dynktmin_true && refdynkt[jet_index]<=dynktmax_true){
                        h_dynkt_xJ_mc_truef[i]->Fill(refdynkt[jet_index],jet_true_xJ_max,scale);

                        if(jet_xJ_max>=xjmin_det && jet_xJ_max<=xjmax_det 
                        && jtdynkt[jet_index]>=dynktmin_det && jtdynkt[jet_index]<=dynktmax_det){

                            h_dynkt_xJ_mc_true[i]->Fill(refdynkt[jet_index],jet_true_xJ_max,scale);
                            h_dynkt_xJ_det[i]->Fill(jtdynkt[jet_index],jet_xJ_max,scale);

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
                            var_weightFinal = scale;
                            tree_xj_dynkt->Fill();
                        }
                    }
                }
                else{
                    if(jet_xJ_max>=xjmin_det && jet_xJ_max<=xjmax_det 
                        && jet_Rg_max>=Rgmin_det && jet_Rg_max<=Rgmax_det){
                        if(jet_Rg_max<=0) jet_Rg_max = -0.025;
                        h_Rg_xJ_det[i]->Fill(jet_Rg_max,jet_xJ_max,scale);
                    }
                    if(jet_xJ_max>=xjmin_det && jet_xJ_max<=xjmax_det 
                        && jtangu[jet_index]>=angumin_det && jtangu[jet_index]<=angumax_det){
                        h_angu_xJ_det[i]->Fill(jtangu[jet_index],jet_xJ_max,scale);
                    }
                    if(jet_xJ_max>=xjmin_det && jet_xJ_max<=xjmax_det 
                        && jtdynkt[jet_index]>=dynktmin_det && jtdynkt[jet_index]<=dynktmax_det){
                        h_dynkt_xJ_det[i]->Fill(jtdynkt[jet_index],jet_xJ_max,scale);
                    }
                }
            }
            else if(flagbkg){
                hbkg_nJet[i]->Fill(1,scale);

                hbkg_xJ_lead[i]->Fill(jet_xJ_max,scale);
                hbkg_Rg_lead[i]->Fill(jtrg[jet_index],scale);
                hbkg_angu_lead[i]->Fill(jtangu[jet_index],scale);
                hbkg_ktdyn_lead[i]->Fill(jtdynkt[jet_index],scale);

                if(jet_xJ_max>=xjmin_det && jet_xJ_max<=xjmax_det 
                    && jet_Rg_max>=Rgmin_det && jet_Rg_max<=Rgmax_det){
                    if(jet_Rg_max<=0) jet_Rg_max = -0.025;
                    hbkg_Rg_xJ_det[i]->Fill(jet_Rg_max,jet_xJ_max,scale);
                }
                if(jet_xJ_max>=xjmin_det && jet_xJ_max<=xjmax_det 
                    && jtangu[jet_index]>=angumin_det && jtangu[jet_index]<=angumax_det){
                    hbkg_Rg_xJ_det[i]->Fill(jtangu[jet_index],jet_xJ_max,scale);
                }
                if(jet_xJ_max>=xjmin_det && jet_xJ_max<=xjmax_det 
                    && jtdynkt[jet_index]>=dynktmin_det && jtdynkt[jet_index]<=dynktmax_det){
                    hbkg_dynkt_xJ_det[i]->Fill(jtdynkt[jet_index],jet_xJ_max,scale);
                }
            }

            h_Rg_xJ[i]->Fill(jet_Rg_max,jet_xJ_max,scale);
            h_angu_xJ[i]->Fill(jtangu[jet_index],jet_xJ_max,scale);
            h_ktdyn_xJ[i]->Fill(jtdynkt[jet_index],jet_xJ_max,scale);

            if(!label.Contains("Data")){            
                h_xJ_xJ[i]->Fill(jet_xJ_max,jet_true_xJ_max,scale);
                h_Rg_Rg[i]->Fill(jet_Rg_max,jet_true_Rg_max,scale);
                h_angu_angu[i]->Fill(jtangu[jet_index],refangu[jet_index],scale);
                h_ktdyn_ktdyn[i]->Fill(jtdynkt[jet_index],refdynkt[jet_index],scale);

                if(jet_true_xJ_max>0.6){
                    h_xJ_g0p6_Rg_Rg[i]->Fill(jet_Rg_max,jet_true_Rg_max,scale);
                    h_xJ_g0p6_angu_angu[i]->Fill(jtangu[jet_index],refangu[jet_index],scale);
                    h_xJ_g0p6_dynkt_dynkt[i]->Fill(jtdynkt[jet_index],refdynkt[jet_index],scale);
                }
                else if(jet_true_xJ_max>=0){
                    h_xJ_l0p6_Rg_Rg[i]->Fill(jet_Rg_max,jet_true_Rg_max,scale);
                    h_xJ_l0p6_angu_angu[i]->Fill(jtangu[jet_index],refangu[jet_index],scale);
                    h_xJ_l0p6_dynkt_dynkt[i]->Fill(jtdynkt[jet_index],refdynkt[jet_index],scale);
                }
            }
        }
    }

    // ------ Normalization and Purity Subtraction 
    for (std::size_t i = 0; i < ncent; ++i) {

        // Normalize per Jet
        hxJ_lead[i]->Scale(1.0/hnJet[i]->GetSum());
        hRg_lead[i]->Scale(1.0/hnJet[i]->GetSum());
        hangu_lead[i]->Scale(1.0/hnJet[i]->GetSum());
        hktdyn_lead[i]->Scale(1.0/hnJet[i]->GetSum());

        hbkg_xJ_lead[i]->Scale(1.0/hbkg_nJet[i]->GetSum());
        hbkg_Rg_lead[i]->Scale(1.0/hbkg_nJet[i]->GetSum());
        hbkg_angu_lead[i]->Scale(1.0/hbkg_nJet[i]->GetSum());
        hbkg_ktdyn_lead[i]->Scale(1.0/hbkg_nJet[i]->GetSum());

        // Purity
        if(label.Contains("Data")){
            hxJ_lead[i]->Scale(1.0/purity_values[i]);
            hRg_lead[i]->Scale(1.0/purity_values[i]);
            hangu_lead[i]->Scale(1.0/purity_values[i]);
            hktdyn_lead[i]->Scale(1.0/purity_values[i]);
            h_Rg_xJ_det[i]->Scale(1.0/purity_values[i]);
            h_angu_xJ_det[i]->Scale(1.0/purity_values[i]);
            h_dynkt_xJ_det[i]->Scale(1.0/purity_values[i]);

            hbkg_xJ_lead[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_Rg_lead[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_angu_lead[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_ktdyn_lead[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_Rg_xJ_det[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_angu_xJ_det[i]->Scale((1-purity_values[i])/purity_values[i]);
            hbkg_dynkt_xJ_det[i]->Scale((1-purity_values[i])/purity_values[i]);

            hxJ_lead[i]->Add(hbkg_xJ_lead[i],-1);
            hRg_lead[i]->Add(hbkg_Rg_lead[i],-1);
            hangu_lead[i]->Add(hbkg_angu_lead[i],-1);
            hktdyn_lead[i]->Add(hbkg_ktdyn_lead[i],-1);
            h_Rg_xJ_det[i]->Add(hbkg_Rg_xJ_det[i],-1);
            h_angu_xJ_det[i]->Add(hbkg_Rg_xJ_det[i],-1);
            h_dynkt_xJ_det[i]->Add(hbkg_Rg_xJ_det[i],-1);
        }/*
        else{
            hxJ_lead[i]->Scale(1.0/hxJ_lead[i]->Integral());
            hRg_lead[i]->Scale(1.0/hRg_lead[i]->Integral());
            hangu_lead[i]->Scale(1.0/hangu_lead[i]->Integral());
            hktdyn_lead[i]->Scale(1.0/hktdyn_lead[i]->Integral());
        }*/
    }
    // -------- End Purity Subtraction
    // ------ Save histograms to File

    TFile *fout;
    fout = new TFile(output_path + "/OutputPlots_"+label+"/Output_"+label+".root", "recreate");
    tree_xj_Rg->Write("",TObject::kOverwrite);
    tree_xj_angu->Write("",TObject::kOverwrite);
    tree_xj_dynkt->Write("",TObject::kOverwrite);
    for (std::size_t i = 0; i < ncent; ++i) {

        hnPho[i]->Write("",TObject::kOverwrite);
        hnPhosel[i]->Write("",TObject::kOverwrite);
        hnJet[i]->Write("",TObject::kOverwrite);

        hres_jetpt[i]->Write("",TObject::kOverwrite);

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

        h_Rg_xJ[i]->Write("",TObject::kOverwrite);
        h_angu_xJ[i]->Write("",TObject::kOverwrite);
        h_ktdyn_xJ[i]->Write("",TObject::kOverwrite);

        h_xJ_xJ[i]->Write("",TObject::kOverwrite);
        h_Rg_Rg[i]->Write("",TObject::kOverwrite);
        h_angu_angu[i]->Write("",TObject::kOverwrite);
        h_ktdyn_ktdyn[i]->Write("",TObject::kOverwrite);

        h_xJ_l0p6_Rg_Rg[i]->Write("",TObject::kOverwrite);
        h_xJ_l0p6_angu_angu[i]->Write("",TObject::kOverwrite);
        h_xJ_l0p6_dynkt_dynkt[i]->Write("",TObject::kOverwrite);
        h_xJ_g0p6_Rg_Rg[i]->Write("",TObject::kOverwrite);
        h_xJ_g0p6_angu_angu[i]->Write("",TObject::kOverwrite);
        h_xJ_g0p6_dynkt_dynkt[i]->Write("",TObject::kOverwrite);

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

        h_Rg_xJ_det[i]->Write("",TObject::kOverwrite);
        h_Rg_xJ_det[i]->ProjectionY(Form("h_xJ_det_%zu",i))->Write("",TObject::kOverwrite);
        h_Rg_xJ_det[i]->ProjectionX(Form("h_Rg_det_%zu",i),1,1)->Write("",TObject::kOverwrite);
        h_Rg_xJ_mc_true[i]->Write("",TObject::kOverwrite);
        h_Rg_xJ_mc_truef[i]->Write("",TObject::kOverwrite);

        hbkg_Rg_xJ_det[i]->Write("",TObject::kOverwrite);

        h_angu_xJ_det[i]->Write("",TObject::kOverwrite);
        h_angu_xJ_det[i]->ProjectionX(Form("h_angu_det_%zu",i),1,1)->Write("",TObject::kOverwrite);
        h_angu_xJ_mc_true[i]->Write("",TObject::kOverwrite);
        h_angu_xJ_mc_truef[i]->Write("",TObject::kOverwrite);

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
        std::vector<TString>sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),"|#eta|<1.44",Form("H/E<%6.4f",cut_HoverE),Form("SumIso<%6.4f",cut_SumIso),Form("#sigma_{#eta#eta}<%6.4f",cut_SIEIE)};    

        const int ind1 = 3;
        const int ind2 = 4;
        const int ind3 = 1;

        Plot_hist2D({h_Rg_xJ[0],h_angu_xJ[0],h_ktdyn_xJ[0]},{"Rg_xJ_0_30","Angu_xJ_0_30","Ktdyn_xJ_0_30"},"text",{"Cent. 0-30%"});
        
        if(!label.Contains("Data")){
            // Plot_hist2D({h_xJ_xJ[0],h_Rg_Rg[0],h_angu_angu[0],h_ktdyn_ktdyn[0]},{"xJ_xJ_0_30","Rg_Rg_0_30","Angu_Angu_0_30","Ktdyn_Ktdyn_0_30"},"colz",{Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),"|#eta|<1.44, Cent. 0-30%","endlog"});
            Plot_hist2D({h_xJ_g0p6_Rg_Rg[0],h_xJ_g0p6_angu_angu[0],h_xJ_g0p6_dynkt_dynkt[0]},{"xJ_g0p6_Rg_Rg_0_30","xJ_g0p6_Angu_Angu_0_30","xJ_g0p6_Ktdyn_Ktdyn_0_30"},"colztext",{"x_{J}>0.6","|#eta|<1.44, Cent. 0-30%","end"});
            Plot_hist2D({h_xJ_l0p6_Rg_Rg[0],h_xJ_l0p6_angu_angu[0],h_xJ_l0p6_dynkt_dynkt[0]},{"xJ_l0p6_Rg_Rg_0_30","xJ_l0p6_Angu_Angu_0_30","xJ_l0p6_Ktdyn_Ktdyn_0_30"},"colztext",{"x_{J}<=0.6","|#eta|<1.44, Cent. 0-30%","end"});      
            Plot_hist2D({h_xJ_g0p6_Rg_Rg[1],h_xJ_g0p6_angu_angu[1],h_xJ_g0p6_dynkt_dynkt[1]},{"xJ_g0p6_Rg_Rg_30_90","xJ_g0p6_Angu_Angu_30_90","xJ_g0p6_Ktdyn_Ktdyn_30_90"},"colztext",{"x_{J}>0.6","|#eta|<1.44, Cent. 30-90%","end"});
            Plot_hist2D({h_xJ_l0p6_Rg_Rg[1],h_xJ_l0p6_angu_angu[1],h_xJ_l0p6_dynkt_dynkt[1]},{"xJ_l0p6_Rg_Rg_30_90","xJ_l0p6_Angu_Angu_30_90","xJ_l0p6_Ktdyn_Ktdyn_30_90"},"colztext",{"x_{J}<=0.6","|#eta|<1.44, Cent. 30-90%","end"});        
            
            Plot_hist2D({h_Rg_xJ_mc_true[0],h_Rg_xJ_det[0],h_Rg_xJ_mc_truef[0]},{"Rg_xJ_mc_true_0_30","Rg_xJ_det_0_30","Rg_xJ_mc_truef_0_30"},"text",{"|#eta|<1.44, Cent. 0-30%"});      
            sel.pop_back();
            sel.pop_back();
            sel.pop_back();
            sel.pop_back();
            Plot_hist({hres_jetpt[ind1],hres_jetpt[ind2],hres_jetpt[ind3]},{Form("Cent. %d-%d%% #sigma = %4.2f",min_cent[ind1]/2,max_cent[ind1]/2,hres_jetpt[ind1]->GetRMS()),Form("Cent. %d-%d%% #sigma = %4.2f",min_cent[ind2]/2,max_cent[ind2]/2,hres_jetpt[ind2]->GetRMS()),Form("Cent. %d-%d%% #sigma = %4.2f",min_cent[ind3]/2,max_cent[ind3]/2,hres_jetpt[ind3]->GetRMS()),"jet_res"},"normflow",sel);
        }
        sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),"|#eta|<1.44",Form("H/E<%6.4f",cut_HoverE),Form("SumIso<%6.4f",cut_SumIso),Form("#sigma_{#eta#eta}<%6.4f",cut_SIEIE)};    
        /* // All Recoil Jets
        Plot_hist({hdphi_all[ind1],hdphi_all[ind2],hdphi_all[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"dphi_all"},"leftlog_norm",sel);
        Plot_hist({hxJ_all[ind1],hxJ_all[ind2],hxJ_all[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"xJ_all"},"right_norm",sel);
        Plot_hist({hRg_all[ind1],hRg_all[ind2],hRg_all[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"Rg_all"},"right_norm",sel);
        Plot_hist({hangu_all[ind1],hangu_all[ind2],hangu_all[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"angu_all"},"right_norm",sel);
        Plot_hist({hktdyn_all[ind1],hktdyn_all[ind2],hktdyn_all[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"ktdyn_all"},"rightlog_norm",sel);
        */
        sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),"|#eta|<1.44, Cent. 0-90%"};
        overlay({hdphi_all[2],hdphi_lead[2]},{"All Recoil Jets","Leading Recoil Jet","#Delta #phi","Norm. Events","dphi_all_lead"},"leftlog_norm_label",sel);
        overlay({hxJ_all[2],hxJ_lead[2]},{"All Recoil Jets","Leading Recoil Jet","xJ","Norm. Events","xJ_all_lead"},"right_norm_label",sel);
        overlay({hRg_all[2],hRg_lead[2]},{"All Recoil Jets","Leading Recoil Jet","R_{g}","Norm. Events","Rg_all_lead"},"right_norm_label",sel);
        overlay({hangu_all[2],hangu_lead[2]},{"All Recoil Jets","Leading Recoil Jet","Angularity","Norm. Events","angu_all_lead"},"right_norm_label",sel);
        overlay({hktdyn_all[2],hktdyn_lead[2]},{"All Recoil Jets","Leading Recoil Jet","dyn k_{T}","Norm. Events","ktdyn_all_lead"},"rightlog_norm_label",sel);

        // Signal Leading Recoil Jet
        sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",min_pho_et,min_jet_pt),"|#eta|<1.44",Form("H/E<%6.4f",cut_HoverE),Form("SumIso<%6.4f",cut_SumIso),Form("#sigma_{#eta#eta}<%6.4f",cut_SIEIE)};
        sel.push_back("Sig Reg - Corrected");    
        Plot_hist({hdphi_lead[ind1],hdphi_lead[ind2],hdphi_lead[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"dphi_lead"},"leftflowlog",sel);
        Plot_hist({hxJ_lead[ind1],hxJ_lead[ind2],hxJ_lead[ind3]},{Form("Cent. %d-%d%% #mu = %4.2f",min_cent[ind1]/2,max_cent[ind1]/2,hxJ_lead[ind1]->GetMean()),Form("Cent. %d-%d%% #mu = %4.2f",min_cent[ind2]/2,max_cent[ind2]/2,hxJ_lead[ind2]->GetMean()),Form("Cent. %d-%d%% #mu = %4.2f",min_cent[ind3]/2,max_cent[ind3]/2,hxJ_lead[ind3]->GetMean()),"xJ_lead"},"rightflow",sel);
        Plot_hist({hRg_lead[ind1],hRg_lead[ind2],hRg_lead[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"Rg_lead"},"rightflow",sel);
        Plot_hist({hangu_lead[ind1],hangu_lead[ind2],hangu_lead[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"angu_lead"},"rightflow",sel);
        Plot_hist({hktdyn_lead[ind1],hktdyn_lead[ind2],hktdyn_lead[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"ktdyn_lead"},"rightflowlog",sel);
        sel.pop_back();

        // Background Leading Recoil Jet
        sel.pop_back();
        // sel.pop_back();
        // sel.push_back(Form("#sigma_{#eta#eta}<%6.4f",cut_SIEIE));
        // sel.push_back("10<SumIso<=20");
        sel.push_back(Form("#sigma_{#eta#eta}>=%6.4f",cut_SIEIE));
        sel.push_back("Bkg Reg - SIEIE");
        Plot_hist({hbkg_xJ_lead[ind1],hbkg_xJ_lead[ind2],hbkg_xJ_lead[ind3]},{Form("Cent. %d-%d%% #mu = %4.2f",min_cent[ind1]/2,max_cent[ind1]/2,hbkg_xJ_lead[ind1]->GetMean()),Form("Cent. %d-%d%% #mu = %4.2f",min_cent[ind2]/2,max_cent[ind2]/2,hbkg_xJ_lead[ind2]->GetMean()),Form("Cent. %d-%d%% #mu = %4.2f",min_cent[ind3]/2,max_cent[ind3]/2,hbkg_xJ_lead[ind3]->GetMean()),"xJ_lead_bkg"},"rightflownorm",sel);
        Plot_hist({hbkg_Rg_lead[ind1],hbkg_Rg_lead[ind2],hbkg_Rg_lead[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"Rg_lead_bkg"},"rightflownorm",sel);
        Plot_hist({hbkg_angu_lead[ind1],hbkg_angu_lead[ind2],hbkg_angu_lead[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"angu_lead_bkg"},"rightflownorm",sel);
        Plot_hist({hbkg_ktdyn_lead[ind1],hbkg_ktdyn_lead[ind2],hbkg_ktdyn_lead[ind3]},{Form("Cent. %d-%d%%",min_cent[ind1]/2,max_cent[ind1]/2),Form("Cent. %d-%d%%",min_cent[ind2]/2,max_cent[ind2]/2),Form("Cent. %d-%d%%",min_cent[ind3]/2,max_cent[ind3]/2),"ktdyn_lead_bkg"},"rightflowlognorm",sel);

        printf("\n");
        fout->Close();
    // ------ Plotting Histograms
}

void Plot_hist(std::vector<TH1F*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "width" = Divide by Bin Width
    // "OBJ" = optional stuff for later? 

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(opt.Contains("log")) gStyle->SetOptLogy(1);
    
    TString drawopt = "nostackE][P0"; 
    const std::vector<int> colarray  = { 1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};

    TCanvas c;
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

    THStack hs("hs","hs");

    for(std::size_t ihist=0; ihist<hist.size();ihist++){
        if(opt.Contains("eff")){
            hist[ihist+1]->SetLineColor(colarray[ihist]);
            hist[ihist+1]->SetMarkerColor(colarray[ihist]);
            hist[ihist+1]->SetMarkerStyle(markarray[ihist]);
            hist[ihist+1]->Divide(hist[ihist+1],hist[0],1,1,"B");
            ihist++;
        }
        else{
            hist[ihist]->SetLineColor(colarray[ihist]);
            hist[ihist]->SetMarkerColor(colarray[ihist]);
            hist[ihist]->SetMarkerStyle(markarray[ihist]);
        }
        if(opt.Contains("norm")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2));
        }
        if(opt.Contains("width")){
            hist[ihist]->Scale(1.0,"width");
        }
        if(opt.Contains("flow"))
            hist[ihist]->GetXaxis()->SetRange(0,hist[ihist]->GetNbinsX()+2);
        hs.Add(hist[ihist]);      
        l->AddEntry(hist[ihist], histname[ihist], "lep");
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
    l->Draw();


    TLatex latex;
    latex.SetTextSize(0.035);
    if(label.Contains("Data"))
        latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Internal}} PbPb 2018");
    else
        latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Internal Simulation}}");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.4,0.92,eopt[0]);
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
    c.SaveAs(output_path + "/OutputPlots_"+label+"/"+histname.back()+".png");
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}

void Plot_hist2D(std::vector<TH2F*> hist,std::vector<TString> histname,TString dopt,std::vector<TString> eopt){
    // dopt contains draw options

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(eopt.back().Contains("log")) gStyle->SetOptLogz(1);
    
    TString drawopt = dopt; 

    TCanvas c;
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
    }/*
    l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    l->SetFillStyle(0);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->SetTextSize(0.025);
    l->SetTextFont(42);
    l->Draw();
    */


    for(std::size_t ihist=0; ihist<hist.size();ihist++){
        hist[ihist]->Draw(drawopt);   
        TLatex latex;
        latex.SetTextSize(0.035);
        if(label.Contains("Data"))
        latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Internal}} PbPb 2018");
        else
            latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Internal Simulation}}");

        if(eopt[0].Contains("Cent")){
            latex.DrawLatexNDC(0.78,0.92,eopt[0]);
        }
        else if(eopt.size()>=2){
            latex.DrawLatexNDC(0.4,0.92,eopt[0]);
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
        c.SaveAs(output_path + "/OutputPlots_"+label+"/"+histname[ihist]+".png");
        std::cout<<histname[ihist]<<" has been saved"<<std::endl;
    }

    if(eopt.back().Contains("log")) gStyle->SetOptLogz(0);
    /*
    delete l;*/
}


void overlay(std::vector<TH1F*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // Based on the old Ratio Plot script from https://root.cern/doc/master/ratioplotOld_8C.html

    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "width" = Divide by Bin Width
    // "OBJ" = optional stuff for later? 

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
    
    TString drawopt = "E][P0"; 
    const std::vector<int> colarray  = { 1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};

    TCanvas c;
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
        if(opt.Contains("norm")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2));
        }
        if(opt.Contains("width")){
            hist[ihist]->Scale(1.0,"width");
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
    c.cd();          // Go back to the main canvas before defining pad2
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3);
    pad2->SetTopMargin(0.05);
    pad2->SetRightMargin(0.05); 
    pad2->SetLeftMargin(0.12); 
    pad2->SetBottomMargin(0.3); 
    pad2->SetGrid();
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad

    // Define the ratio plot
    TH1F *hratio = (TH1F*)hist[0]->Clone(histname[0]);
    for(std::size_t ihist=1; ihist<hist.size();ihist++){
        hratio = (TH1F*)hist[ihist]->Clone(histname[ihist]);
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
    c.cd();  

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
        latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Internal}} PbPb 2018");
    else
        latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Internal Simulation}}");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.4,0.92,eopt[0]);
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
    c.SaveAs(output_path + "/OutputPlots_"+label+"/"+histname.back()+".png");
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
