#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TInterpreter.h>
#include <TString.h>
#include <TObjString.h>
#include <TObjArray.h>
#include <TMath.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TString.h>
#include <TF1.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TDatabasePDG.h>
#include <TGraph.h>
#include <TTree.h>
#include <TDirectoryFile.h>
#include <TMath.h>
#include <TSystem.h>

#include "TLatex.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TLeaf.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "phoERegression_Bharad_updated.h"
#endif

void DrawLatex(Float_t , Float_t , Int_t , const char* , Float_t );
void SetPlotStyle();
void displayProgress(long, long);

Double_t RelativePhi(Double_t mphi,Double_t vphi) {

  if (vphi < -1 * TMath::Pi())
    vphi += (2 * TMath::Pi());
  else if (vphi > TMath::Pi())
    vphi -= (2 * TMath::Pi());
  if (mphi < -1 * TMath::Pi())
    mphi += (2 * TMath::Pi());
  else if (mphi > TMath::Pi())
    mphi -= (2 * TMath::Pi());
  double dphi = mphi - vphi;
  if (dphi < -1 * TMath::Pi())
    dphi += (2 * TMath::Pi());
  else if (dphi > TMath::Pi())
    dphi -= (2 * TMath::Pi());
  return dphi; // dphi in [-Pi, Pi]
}

void SkimFile_Data(){

    TString type="QCDPhoton";
    TString type_dir = "/home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/PhotonAnalysis/test/";            

   gROOT->SetBatch();
   gErrorIgnoreLevel = kWarning;

   SetPlotStyle();
    TChain data("data"), EventTree("EventTree"), HiTree("HiTree"), skimanalysis("skimanalysis"),hltanalysis("hltanalysis");

   data.Add("/data_CMS/cms/bharikri/Data_2018/HiForestAOD_*.root/akCs2PFJetAnalyzer_substructure/t");
   EventTree.Add("/data_CMS/cms/bharikri/Data_2018/HiForestAOD_*.root/ggHiNtuplizerGED/EventTree");
   HiTree.Add("/data_CMS/cms/bharikri/Data_2018/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
   skimanalysis.Add("/data_CMS/cms/bharikri/Data_2018/HiForestAOD_*.root/skimanalysis/HltTree");
   hltanalysis.Add("/data_CMS/cms/bharikri/Data_2018/HiForestAOD_*.root/hltanalysis/HltTree");

   data.AddFriend("EventTree");
   data.AddFriend("HiTree");
   data.AddFriend("skimanalysis");
   data.AddFriend("hltanalysis");

  // ----------------------------------------------------------------------------------------------------------------
  // Variables

   Int_t hiBin=0;
   
   data.SetBranchAddress("hiBin", &hiBin);

   // reco::Photon
   std::vector<float>*  phoE;
   std::vector<float>*  phoEt;
   std::vector<float>*  phoEta;
   std::vector<float>*  phoPhi;
   std::vector<float>*  phoHoverE;
   std::vector<float>*  pho_ecalClusterIsoR3;
   std::vector<float>*  pho_hcalRechitIsoR3;
   std::vector<float>*  pho_trackIsoR3PtCut20;
   std::vector<float>*  pho_ecalClusterIsoR4;
   std::vector<float>*  pho_hcalRechitIsoR4;
   std::vector<float>*  pho_trackIsoR4PtCut20;
   std::vector<int>*    pho_genMatchedIndex;
   std::vector<float>*  phoSigmaEtaEta_2012;
   std::vector<float>*  pfcIso3subUE;
   std::vector<float>*  pfnIso3subUE;
   std::vector<float>*  pfpIso3subUE;
   std::vector<float>*  phoE1x5_2012;
   std::vector<float>*  phoE2x5_2012;
   std::vector<float>*  phoE3x5_2012;
   std::vector<float>*  phoE5x5_2012;
   // std::vector<float>*  phoE3x3_2012;
   std::vector<float>*  pho_swissCrx;
   std::vector<float>*  pho_seedTime;

   std::vector<float>* phoSCRawE;
   std::vector<float>* phoSCEta;
   std::vector<float>* phoSCPhi;
   std::vector<float>* phoSCEtaWidth;
   std::vector<float>* phoSCPhiWidth;
   std::vector<float>* phoE3x3_2012;
   std::vector<float>* phoMaxEnergyXtal_2012;
   std::vector<float>* phoE2nd_2012;
   std::vector<float>* phoELeft_2012;
   std::vector<float>* phoERight_2012;
   std::vector<float>* phoETop_2012;
   std::vector<float>* phoEBottom_2012;
   std::vector<float>* phoSigmaIEtaIEta_2012;
   std::vector<float>* phoSigmaIEtaIPhi_2012;
   std::vector<float>* phoSigmaIPhiIPhi_2012;
   Float_t rho;
   std::vector<float>* phoESEn;

   // reco::Electron
   std::vector<float>* elePt;
   std::vector<float>* eleEta;
   std::vector<float>* elePhi;
   std::vector<float>* eleEoverP;

   /// ----
/*
   mcPID = 0;
   mcPt = 0;
   mcEta = 0;
   mcPhi = 0;
   mcE = 0;
   mcEt = 0;
   mcMass = 0;
*/
   // reco::Photon
   phoE = 0;
   phoEt = 0;
   phoEta = 0;
   phoPhi = 0;
   phoHoverE = 0;
   pho_ecalClusterIsoR3 = 0;
   pho_hcalRechitIsoR3 = 0;
   pho_trackIsoR3PtCut20 = 0;
   pho_ecalClusterIsoR4 = 0;
   pho_hcalRechitIsoR4 = 0;
   pho_trackIsoR4PtCut20 = 0;
   // pho_genMatchedIndex = 0;
   phoSigmaEtaEta_2012 = 0;
   pfcIso3subUE = 0;
   pfnIso3subUE = 0;
   pfpIso3subUE = 0;

   phoSCRawE = 0;
   phoSCEta = 0;
   phoSCPhi = 0;
   phoSCEtaWidth = 0;
   phoSCPhiWidth = 0;
   phoE3x3_2012 = 0;
   phoMaxEnergyXtal_2012 = 0;
   phoE2nd_2012 = 0;
   phoELeft_2012 = 0;
   phoERight_2012 = 0;
   phoETop_2012 = 0;
   phoEBottom_2012 = 0;
   phoSigmaIEtaIEta_2012 = 0;
   phoSigmaIEtaIPhi_2012 = 0;
   phoSigmaIPhiIPhi_2012 = 0;
   rho = 0;
   phoESEn = 0;
   
   phoE1x5_2012 = 0;
   phoE2x5_2012 = 0;
   phoE3x5_2012 = 0;
   phoE5x5_2012 = 0;
   // phoE3x3_2012 = 0;
   pho_swissCrx = 0;
   pho_seedTime = 0;

   elePt = 0;
   eleEta = 0;
   elePhi = 0;
   eleEoverP = 0;
   /*
   data.SetBranchAddress("mcPID",        &mcPID);
   data.SetBranchAddress("mcPt",         &mcPt);
   data.SetBranchAddress("mcEta",        &mcEta);
   data.SetBranchAddress("mcPhi",        &mcPhi);
   data.SetBranchAddress("mcE",          &mcE);
   data.SetBranchAddress("mcEt",         &mcEt);
   data.SetBranchAddress("mcMass",       &mcMass);*/

   data.SetBranchAddress("phoE",                  &phoE);
   data.SetBranchAddress("phoEt",                 &phoEt);
   data.SetBranchAddress("phoEta",                &phoEta);
   data.SetBranchAddress("phoPhi",                &phoPhi);
   data.SetBranchAddress("phoHoverE",             &phoHoverE);
   data.SetBranchAddress("pho_ecalClusterIsoR3",  &pho_ecalClusterIsoR3);
   data.SetBranchAddress("pho_hcalRechitIsoR3",   &pho_hcalRechitIsoR3);
   data.SetBranchAddress("pho_trackIsoR3PtCut20", &pho_trackIsoR3PtCut20);
   data.SetBranchAddress("pho_ecalClusterIsoR4",  &pho_ecalClusterIsoR4);
   data.SetBranchAddress("pho_hcalRechitIsoR4",   &pho_hcalRechitIsoR4);
   data.SetBranchAddress("pho_trackIsoR4PtCut20", &pho_trackIsoR4PtCut20);
   // data.SetBranchAddress("pho_genMatchedIndex",   &pho_genMatchedIndex);
   data.SetBranchAddress("phoSigmaEtaEta_2012",   &phoSigmaEtaEta_2012);
   data.SetBranchAddress("pfcIso3subUE",          &pfcIso3subUE);
   data.SetBranchAddress("pfnIso3subUE",          &pfnIso3subUE);
   data.SetBranchAddress("pfpIso3subUE",          &pfpIso3subUE);

   data.SetBranchAddress("phoSCRawE",          &phoSCRawE);
   data.SetBranchAddress("phoSCEta",          &phoSCEta);
   data.SetBranchAddress("phoSCPhi",          &phoSCPhi);
   data.SetBranchAddress("phoSCEtaWidth",          &phoSCEtaWidth);
   data.SetBranchAddress("phoSCPhiWidth",          &phoSCPhiWidth);
   data.SetBranchAddress("phoE3x3_2012",          &phoE3x3_2012);
   data.SetBranchAddress("phoMaxEnergyXtal_2012",          &phoMaxEnergyXtal_2012);
   data.SetBranchAddress("phoE2nd_2012",          &phoE2nd_2012);
   data.SetBranchAddress("phoELeft_2012",          &phoELeft_2012);
   data.SetBranchAddress("phoERight_2012",          &phoERight_2012);
   data.SetBranchAddress("phoETop_2012",          &phoETop_2012);
   data.SetBranchAddress("phoEBottom_2012",          &phoEBottom_2012);
   data.SetBranchAddress("phoSigmaIEtaIEta_2012",          &phoSigmaIEtaIEta_2012);
   data.SetBranchAddress("phoSigmaIEtaIPhi_2012",          &phoSigmaIEtaIPhi_2012);
   data.SetBranchAddress("phoSigmaIPhiIPhi_2012",          &phoSigmaIPhiIPhi_2012);
   data.SetBranchAddress("rho",          &rho);
   data.SetBranchAddress("phoESEn",          &phoESEn);
   
   data.SetBranchAddress("phoE1x5_2012",&phoE1x5_2012);
   data.SetBranchAddress("phoE2x5_2012",&phoE2x5_2012);
   // data.SetBranchAddress("phoE3x3_2012",&phoE3x3_2012);
   data.SetBranchAddress("phoE5x5_2012",&phoE5x5_2012);
   data.SetBranchAddress("pho_swissCrx",&pho_swissCrx);
   data.SetBranchAddress("pho_seedTime",&pho_seedTime);

   data.SetBranchAddress("elePt",   &elePt);
   data.SetBranchAddress("eleEta",  &eleEta);
   data.SetBranchAddress("elePhi",  &elePhi);
   data.SetBranchAddress("eleEoverP",  &eleEoverP);

   int pprimaryVertexFilter = 0;
   int pclusterCompatibilityFilter = 0;
   int phfCoincFilter2Th4 = 0;

   data.SetBranchAddress("pprimaryVertexFilter",  &pprimaryVertexFilter);
   data.SetBranchAddress("pclusterCompatibilityFilter",  &pclusterCompatibilityFilter);
   data.SetBranchAddress("phfCoincFilter2Th4",  &phfCoincFilter2Th4);

   Int_t L1_SingleEG21_BptxAND = 0;
   Int_t HLT_HIGEDPhoton40_v1 = 0;

   data.SetBranchAddress("L1_SingleEG21_BptxAND",  &L1_SingleEG21_BptxAND);
   data.SetBranchAddress("HLT_HIGEDPhoton40_v1",  &HLT_HIGEDPhoton40_v1);

// ----------------------------------------------------------------------------------------------------------------
// Histograms
    TTree *weight_tree;
   weight_tree = new TTree("weight_tree","weight_tree");

   Float_t train_phoSCRawE = 0;
   Float_t train_phoSCEta = 0;
   Float_t train_phoSCPhi = 0;
   Float_t train_phoSCEtaWidth = 0;
   Float_t train_phoSCPhiWidth = 0;
   Float_t train_phoE3x3_2012 = 0;
   Float_t train_phoMaxEnergyXtal_2012 = 0;
   Float_t train_phoE2nd_2012 = 0;
   Float_t train_phoELeft_2012 = 0;
   Float_t train_phoERight_2012 = 0;
   Float_t train_phoETop_2012 = 0;
   Float_t train_phoEBottom_2012 = 0;
   Float_t train_phoSigmaIEtaIEta_2012 = 0;
   Float_t train_phoSigmaIEtaIPhi_2012 = 0;
   Float_t train_phoSigmaIPhiIPhi_2012 = 0;
   Float_t train_rho = 0;
   Float_t train_phoESEn = 0;

   Float_t train_phoEt = 0;
   Float_t train_phoEtCorrected = 0;
   Float_t train_phoEta = 0;
   Float_t train_phoPhi = 0;
   Float_t train_phoHoverE = 0;
   Float_t train_pho_ecalClusterIsoR3 = 0;
   Float_t train_pho_hcalRechitIsoR3 = 0;
   Float_t train_pho_trackIsoR3PtCut20 = 0;
   Float_t train_pho_ecalClusterIsoR4 = 0;
   Float_t train_pho_hcalRechitIsoR4 = 0;
   Float_t train_pho_trackIsoR4PtCut20 = 0;
   Float_t train_phoE = 0;
   Float_t train_phoSigmaEtaEta_2012 = 0;
   
   Float_t train_pfcIso3subUE = 0;
   Float_t train_pfnIso3subUE = 0;
   Float_t train_pfpIso3subUE = 0;
   Float_t train_SumPFIso = 0;
   Float_t train_SumCalIso = 0;

   std::vector<float>* train_elePt = 0;
   std::vector<float>* train_eleEta = 0;
   std::vector<float>* train_elePhi = 0;
   std::vector<float>* train_eleDeta = 0;
   std::vector<float>* train_eleDphi = 0;
   std::vector<float>* train_eleEoverP = 0;
   Bool_t  train_eleRej = 0;

   Int_t   train_hiBin = 0;
   Int_t   train_L1_SingleEG21_BptxAND = 0;
   Int_t   train_HLT_HIGEDPhoton40_v1 = 0;
   
   weight_tree->Branch("phoSCRawE",&train_phoSCRawE);
   weight_tree->Branch("phoSCEta",&train_phoSCEta);
   weight_tree->Branch("phoSCPhi",&train_phoSCPhi);
   weight_tree->Branch("phoSCEtaWidth",&train_phoSCEtaWidth);
   weight_tree->Branch("phoSCPhiWidth",&train_phoSCPhiWidth);
   weight_tree->Branch("phoE3x3_2012",&train_phoE3x3_2012);
   weight_tree->Branch("phoMaxEnergyXtal_2012",&train_phoMaxEnergyXtal_2012);
   weight_tree->Branch("phoE2nd_2012",&train_phoE2nd_2012);
   weight_tree->Branch("phoELeft_2012",&train_phoELeft_2012);
   weight_tree->Branch("phoERight_2012",&train_phoERight_2012);
   weight_tree->Branch("phoETop_2012",&train_phoETop_2012);
   weight_tree->Branch("phoEBottom_2012",&train_phoEBottom_2012);
   weight_tree->Branch("phoSigmaIEtaIEta_2012",&train_phoSigmaIEtaIEta_2012);
   weight_tree->Branch("phoSigmaIEtaIPhi_2012",&train_phoSigmaIEtaIPhi_2012);
   weight_tree->Branch("phoSigmaIPhiIPhi_2012",&train_phoSigmaIPhiIPhi_2012);
   weight_tree->Branch("rho",&train_rho);
   weight_tree->Branch("phoESEn",&train_phoESEn);

   weight_tree->Branch("phoEt",&train_phoEt);
   weight_tree->Branch("phoEtCorrected",&train_phoEtCorrected);
   weight_tree->Branch("phoEta",&train_phoEta);
   weight_tree->Branch("phoPhi",&train_phoPhi);
   weight_tree->Branch("phoHoverE",&train_phoHoverE);
   weight_tree->Branch("pho_ecalClusterIsoR3",&train_pho_ecalClusterIsoR3);
   weight_tree->Branch("pho_hcalRechitIsoR3",&train_pho_hcalRechitIsoR3);
   weight_tree->Branch("pho_trackIsoR3PtCut20",&train_pho_trackIsoR3PtCut20);
   weight_tree->Branch("pho_ecalClusterIsoR4",&train_pho_ecalClusterIsoR4);
   weight_tree->Branch("pho_hcalRechitIsoR4",&train_pho_hcalRechitIsoR4);
   weight_tree->Branch("pho_trackIsoR4PtCut20",&train_pho_trackIsoR4PtCut20);
   weight_tree->Branch("phoE",&train_phoE);
   weight_tree->Branch("phoSigmaEtaEta_2012",&train_phoSigmaEtaEta_2012);
   
   weight_tree->Branch("pfcIso3subUE",&train_pfcIso3subUE);
   weight_tree->Branch("pfnIso3subUE",&train_pfnIso3subUE);
   weight_tree->Branch("pfpIso3subUE",&train_pfpIso3subUE);
   weight_tree->Branch("SumPFIso",&train_SumPFIso);
   weight_tree->Branch("SumCalIso",&train_SumCalIso);
   weight_tree->Branch("hiBin",&train_hiBin);

   // weight_tree->Branch("elePt",&train_elePt);
   // weight_tree->Branch("eleEta",&train_eleEta);
   // weight_tree->Branch("elePhi",&train_elePhi);
   // weight_tree->Branch("eleDeta",&train_eleDeta);
   // weight_tree->Branch("eleDphi",&train_eleDphi);
   // weight_tree->Branch("eleEoverP",&train_eleEoverP);
   weight_tree->Branch("eleRej",&train_eleRej);

   weight_tree->Branch("L1_SingleEG21_BptxAND",&train_L1_SingleEG21_BptxAND);
   weight_tree->Branch("HLT_HIGEDPhoton40_v1",&train_HLT_HIGEDPhoton40_v1);

   phoERegression myPhoERegr;
   myPhoERegr.initiliazeReaderEB("/home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/PhotonAnalysis/test/2_Regression_Training/dataset/weights/tmvaTrainRegr_BDTG_pbpb18_EB.weights.xml");
   myPhoERegr.initiliazeReaderEE("/home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/PhotonAnalysis/test/2_Regression_Training/dataset/weights/tmvaTrainRegr_BDTG_pbpb18_EE.weights.xml");


// ----------------------------------------------------------------------------------------------------------------
//        * * * * *     S T A R T   O F   A C T U A L   R U N N I N G   O N   E V E N T S     * * * * *
// ----------------------------------------------------------------------------------------------------------------

   Int_t nEv=data.GetEntries();
   float scale = 1;

   for(int iEntry=0; iEntry< nEv; iEntry++){
      displayProgress(iEntry,nEv);
      data.GetEntry(iEntry);

      int pho_index=-1, genin=-1;;
      float Etmax=-1;
      float corrected_Et = -1;

      std::vector<float> phoVars;
      phoVars.reserve(17);

      if(pprimaryVertexFilter<=0) continue;
      if(pclusterCompatibilityFilter<=0) continue;
      if(phfCoincFilter2Th4<=0) continue;
      // if(hiBin>180) continue;

      for(int ipho=0; ipho<phoEt->size(); ipho++){
         // if(!(fabs(phoEta->at(ipho))<1.44)) continue; // || (fabs(phoEta->at(ipho))>1.6 && fabs(phoEta->at(ipho))<2.0)
         // if(pho_genMatchedIndex->at(ipho)==-1) continue;
         // if(mcPID->at(pho_genMatchedIndex->at(ipho)) != 22) continue;
         // if(mcCalIsoDR04->at(pho_genMatchedIndex->at(ipho))>=5) continue;
         // if(phoSigmaEtaEta_2012->at(ipho)<=0.002) continue;
         if(fabs(pho_seedTime->at(ipho))>=3 || pho_swissCrx->at(ipho)>=0.9) continue;


         phoVars[0] = phoSCRawE->at(ipho);
         phoVars[1] = phoSCEta->at(ipho);
         phoVars[2] = phoSCPhi->at(ipho);
         phoVars[3] = phoSCEtaWidth->at(ipho);
         phoVars[4] = phoSCPhiWidth->at(ipho);
         phoVars[5] = phoE3x3_2012->at(ipho);
         phoVars[6] = phoMaxEnergyXtal_2012->at(ipho);
         phoVars[7] = phoE2nd_2012->at(ipho);
         phoVars[8] = phoELeft_2012->at(ipho);
         phoVars[9] = phoERight_2012->at(ipho);
         phoVars[10] = phoETop_2012->at(ipho);
         phoVars[11] = phoEBottom_2012->at(ipho);
         phoVars[12] = phoSigmaIEtaIEta_2012->at(ipho);
         phoVars[13] = phoSigmaIEtaIPhi_2012->at(ipho);
         phoVars[14] = phoSigmaIPhiIPhi_2012->at(ipho);
         phoVars[15] = rho;
         phoVars[16] = phoESEn->at(ipho);

         corrected_Et = myPhoERegr.getCorrectedPt(phoVars, phoEt->at(ipho), phoEta->at(ipho), phoSCEta->at(ipho));

         if(Etmax<corrected_Et){
            Etmax = corrected_Et;
            pho_index = ipho;
         }

      }
      if(pho_index==-1) continue;

      Bool_t flagEle = false;
      for(int iele=0;iele<elePt->size();iele++){

         double dee=TMath::Abs(eleEta->at(iele)-phoEta->at(pho_index));
         double dephi=RelativePhi(elePhi->at(iele),phoPhi->at(pho_index));

         // train_elePt->push_back(elePt->at(iele));
         // train_eleEta->push_back(eleEta->at(iele));
         // train_elePhi->push_back(elePhi->at(iele));
         // train_eleDeta->push_back(dee);
         // train_eleDphi->push_back(dephi);
         // train_eleEoverP->push_back(eleEoverP->at(iele));

         if(elePt->at(iele)<10) continue;
         if(eleEoverP->at(iele)>100) continue;
         if(dee<0.02 && dephi<0.015) flagEle=true;
      }

    train_phoSCRawE = phoSCRawE->at(pho_index);
    train_phoSCEta = phoSCEta->at(pho_index);
    train_phoSCPhi = phoSCPhi->at(pho_index);
    train_phoSCEtaWidth = phoSCEtaWidth->at(pho_index);
    train_phoSCPhiWidth = phoSCPhiWidth->at(pho_index);
    train_phoE3x3_2012 = phoE3x3_2012->at(pho_index);
    train_phoMaxEnergyXtal_2012 = phoMaxEnergyXtal_2012->at(pho_index);
    train_phoE2nd_2012 = phoE2nd_2012->at(pho_index);
    train_phoELeft_2012 = phoELeft_2012->at(pho_index);
    train_phoERight_2012 = phoERight_2012->at(pho_index);
    train_phoETop_2012 = phoETop_2012->at(pho_index);
    train_phoEBottom_2012 = phoEBottom_2012->at(pho_index);
    train_phoSigmaIEtaIEta_2012 = phoSigmaIEtaIEta_2012->at(pho_index);
    train_phoSigmaIEtaIPhi_2012 = phoSigmaIEtaIPhi_2012->at(pho_index);
    train_phoSigmaIPhiIPhi_2012 = phoSigmaIPhiIPhi_2012->at(pho_index);
    train_rho = rho;
    train_phoESEn = phoESEn->at(pho_index);
    train_phoEt = phoEt->at(pho_index);
    train_phoEtCorrected = Etmax;
    train_phoEta = phoEta->at(pho_index);
    train_phoPhi = phoPhi->at(pho_index);
    train_phoHoverE = phoHoverE->at(pho_index);
    train_pho_ecalClusterIsoR3 = pho_ecalClusterIsoR3->at(pho_index);
    train_pho_hcalRechitIsoR3 = pho_hcalRechitIsoR3->at(pho_index);
    train_pho_trackIsoR3PtCut20 = pho_trackIsoR3PtCut20->at(pho_index);
    train_pho_ecalClusterIsoR4 = pho_ecalClusterIsoR4->at(pho_index);
    train_pho_hcalRechitIsoR4 = pho_hcalRechitIsoR4->at(pho_index);
    train_pho_trackIsoR4PtCut20 = pho_trackIsoR4PtCut20->at(pho_index);
    train_phoE = phoE->at(pho_index);     
    train_phoSigmaEtaEta_2012 = phoSigmaEtaEta_2012->at(pho_index);    
    train_pfcIso3subUE = pfcIso3subUE->at(pho_index);
    train_pfnIso3subUE = pfnIso3subUE->at(pho_index);
    train_pfpIso3subUE = pfpIso3subUE->at(pho_index);
    train_SumPFIso = pfcIso3subUE->at(pho_index)+pfnIso3subUE->at(pho_index)+pfpIso3subUE->at(pho_index);
    train_SumCalIso = pho_ecalClusterIsoR3->at(pho_index)+pho_hcalRechitIsoR3->at(pho_index)+pho_trackIsoR3PtCut20->at(pho_index);
    train_hiBin = hiBin;
    train_eleRej = flagEle;
    train_L1_SingleEG21_BptxAND = L1_SingleEG21_BptxAND;
    train_HLT_HIGEDPhoton40_v1 = HLT_HIGEDPhoton40_v1;
    weight_tree->Fill();

      // cout<<"i = "<< iEntry << " hiBin = "<<hiBin <<" Genin = "<<genin<<endl;

   } // End Event loop

   TFile *fout;
   fout = new TFile(type_dir + "Data_2018.root", "recreate");
   weight_tree->Write("",TObject::kOverwrite);

   fout->Close();

}

void DrawLatex(Float_t x, Float_t y, Int_t color, const char* text, Float_t textSize = 0.042)                                             
{                                                                                                                                        
  TLatex* latex = new TLatex(x, y, text);                                                                                                
  latex->SetNDC();                                                                                                                       
  latex->SetTextSize(textSize);                                                                                                          
  latex->SetTextColor(color);                                                                                                            
  latex->SetTextFont(42);                                                                                                                
  latex->Draw();                                                                                                                         
}    


void SetPlotStyle()
{
   // from ATLAS plot style macro

   // use plain black on white colors
   gStyle->SetFrameBorderMode(0);
   gStyle->SetFrameFillColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadColor(0);
   gStyle->SetStatColor(0);
   gStyle->SetHistLineColor(1);

   gStyle->SetPalette(1);

   // set the paper & margin sizes
   gStyle->SetPaperSize(20, 26);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadRightMargin(0.15);
   gStyle->SetPadBottomMargin(0.16);
   gStyle->SetPadLeftMargin(0.16);

   // set title offsets (for axis label)
   gStyle->SetTitleXOffset(1.4);
   gStyle->SetTitleYOffset(1.4);

   // use large fonts
   gStyle->SetTextFont(42);
   gStyle->SetTextSize(0.05);
   gStyle->SetLabelFont(42, "x");
   gStyle->SetTitleFont(42, "x");
   gStyle->SetLabelFont(42, "y");
   gStyle->SetTitleFont(42, "y");
   gStyle->SetLabelFont(42, "z");
   gStyle->SetTitleFont(42, "z");
   gStyle->SetLabelSize(0.05, "x");
   gStyle->SetTitleSize(0.05, "x");
   gStyle->SetLabelSize(0.05, "y");
   gStyle->SetTitleSize(0.05, "y");
   gStyle->SetLabelSize(0.05, "z");
   gStyle->SetTitleSize(0.05, "z");

   // use bold lines and markers
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerSize(1.2);
   gStyle->SetHistLineWidth(2.);
   gStyle->SetLineStyleString(2, "[12 12]");

   // get rid of error bar caps
   gStyle->SetEndErrorSize(0.);

   // do not display any of the standard histogram decorations
   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);

   // put tick marks on top and RHS of plots
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
}

void displayProgress(long current, long max)
{
   using std::cerr;
   if (max < 2500)
      return;
   if (current % (max / 2500) != 0 && current < max - 1)
      return;

   int width = 52; // Hope the terminal is at least that wide.
   int barWidth = width - 2;
   cerr << "\x1B[2K";    // Clear line
   cerr << "\x1B[2000D"; // Cursor left
   cerr << '[';
   for (int i = 0; i < barWidth; ++i)
   {
      if (i < barWidth * current / max)
      {
         cerr << '=';
      }
      else
      {
         cerr << ' ';
      }
   }
   cerr << ']';
   cerr << " " << Form("%8d/%8d (%5.2f%%)", (int)current, (int)max, 100.0 * current / max);
   cerr.flush();
}

int main(){
   SkimFile_Data();
   return 0;
}