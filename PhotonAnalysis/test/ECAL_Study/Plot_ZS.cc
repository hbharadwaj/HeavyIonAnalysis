#include <TSystem.h>        // needed for gSystem
#include <TStyle.h>         // needed for gStyle 
#include <TChain.h>         // needed for TChain
#include "TROOT.h"          // needed for gROOT
#include <TError.h>         // needed for gErrorIgnoreLevel
#include <TVector2.h>       // needed for TVector2::Phi_mpi_pi        
#include <TH1.h>            // needed fror TH1 and TH2
#include <TH2.h>            // needed fror TH1 and TH2
#include <TLegend.h>        // needed for Legend
#include <TCanvas.h>        // needed for Canvas
#include <TMath.h>          //! needed for floating values in plots for some reason
#include <THStack.h>        // needed for THStack
#include <TLatex.h>         // needed for TLatex
#include <TFile.h>          // needed for TFile

#include <iostream>         // needed for I/O

TString label="2018_QCDPhoton_Embedded"; // "HiMinimumBias2_Data_2018";
TString output_path = "./";

TFile *fout;

// Common directory in which the different ZS samples are stored
TString input_dir  = "/data_CMS/cms/bharikri/ECAL_study/";

// Individual TTrees in the AOD
TString input_pho_tree     = "/HiForestAOD*.root/ggHiNtuplizerGED/EventTree";
TString input_HiTree       = "/HiForestAOD*.root/hiEvtAnalyzer/HiTree";
TString input_skimanalysis = "/HiForestAOD*.root/skimanalysis/HltTree";
TString input_hltanalysis  = "/HiForestAOD*.root/hltanalysis/HltTree";

// Eta ranges considered for the study {|eta|<1.44, 1.566<|eta|<2.1}  // index i
std::vector<float> min_eta = {  0,  1.566};   
std::vector<float> max_eta = {1.44,   2.1};
const std::size_t neta = 2;

// PbPb centrality ranges considered for the study // index j
std::vector<int> min_cent = {  0,  0,  60};   
std::vector<int> max_cent = {180, 60, 180};
const std::size_t ncent = 3;  

// personal histogram plotting script 
void Plot_hist(std::vector<TH1F*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});
void overlay_ZS(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

// const int nBins = 200;
// const Double_t binTable[nBins+1] = {0, 12.1014, 12.9409, 13.7187, 14.5433, 15.3543, 16.1875, 16.9102, 17.801, 18.665, 19.5774, 20.6719, 21.6113, 22.5568, 23.6527, 24.7793, 26.0147, 27.2201, 28.5074, 29.7483, 31.066, 32.6163, 34.1774, 35.5841, 37.0575, 38.8299, 40.405, 42.0362, 43.8421, 45.7347, 47.5933, 49.5335, 51.7829, 53.987, 56.2259, 58.3895, 60.8064, 63.5136, 66.2525, 69.2949, 72.2317, 74.9814, 78.1833, 81.3128, 84.4529, 88.1094, 92.3253, 96.3918, 100.687, 104.956, 109.04, 113.883, 118.587, 123.625, 128.83, 134.46, 140.025, 146.041, 152.413, 158.679, 165.572, 172.216, 179.23, 186.064, 193.389, 200.059, 207.968, 215.298, 223.005, 231.687, 240.374, 249.678, 259.174, 268.706, 278.396, 287.677, 298.63, 308.51, 318.988, 329.398, 341.02, 353.122, 364.607, 375.846, 389.006, 401.262, 414.962, 428.378, 442.75, 456.619, 470.537, 485.682, 500.978, 514.673, 529.879, 546.615, 563.395, 581.434, 598.956, 616.781, 633.978, 652.738, 672.571, 689.594, 710.215, 731.52, 753.06, 774.438, 796.381, 820.056, 845.08, 867.021, 890.232, 915.19, 937.91, 961.302, 986.364, 1012.26, 1037.33, 1061.64, 1088.36, 1117.92, 1145.47, 1173.3, 1202.12, 1231.54, 1261.71, 1293.29, 1324, 1354.33, 1386.23, 1420.48, 1454.03, 1489.97, 1523.91, 1558.51, 1596.42, 1634.32, 1670.92, 1711.18, 1747.27, 1788.59, 1827.43, 1863.27, 1895.46, 1934.09, 1975.41, 2014.96, 2055.59, 2099.99, 2144.59, 2192.65, 2240.31, 2291.81, 2340.11, 2388.38, 2432.7, 2485.1, 2540.69, 2589.08, 2642.46, 2692.26, 2746.72, 2800.16, 2852.02, 2913.51, 2973.06, 3029.59, 3088.32, 3149.53, 3209.89, 3277.1, 3339.51, 3406.57, 3478.69, 3549.31, 3617.84, 3690.46, 3776.56, 3855.55, 3929.26, 4007.74, 4079.2, 4151.39, 4240.1, 4326.91, 4422.12, 4507.51, 4602.4, 4704.53, 4798.26, 4895.34, 5000.31, 5109.08, 5198.81, 5317.47, 5426.28, 5546.66, 5697.73, 5850.37, 6689.23};

// Int_t getHiBinFromhiHF(const Double_t hiHF)
// {
//     Int_t binPos = -1;
//       for(int i = 0; i < nBins; ++i){
//             if(hiHF >= binTable[i] && hiHF < binTable[i+1]){
//                     binPos = i;
//                           break; 
//                               }
//               }                   

//         binPos = nBins - 1 - binPos;

//           return (Int_t)(200*((Double_t)binPos)/((Double_t)nBins));
// }

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

void Plot_ZS(TString in_file_path,TString in_label){
    // in_file_path = Directory name for the specified ZS setting
    // in_label = Corresponding legend label

    // Centrality weights 
    const float Ncoll[200] = {1976.95, 1944.02, 1927.29, 1891.9, 1845.3, 1807.2, 1760.45, 1729.18, 1674.8, 1630.3, 1590.52, 1561.72, 1516.1, 1486.5, 1444.68, 1410.88, 1376.4, 1347.32, 1309.71, 1279.98, 1255.31, 1219.89, 1195.13, 1165.96, 1138.92, 1113.37, 1082.26, 1062.42, 1030.6, 1009.96, 980.229, 955.443, 936.501, 915.97, 892.063, 871.289, 847.364, 825.127, 806.584, 789.163, 765.42, 751.187, 733.001, 708.31, 690.972, 677.711, 660.682, 640.431, 623.839, 607.456, 593.307, 576.364, 560.967, 548.909, 530.475, 519.575, 505.105, 490.027, 478.133, 462.372, 451.115, 442.642, 425.76, 416.364, 405.154, 392.688, 380.565, 371.167, 360.28, 348.239, 340.587, 328.746, 320.268, 311.752, 300.742, 292.172, 281.361, 274.249, 267.025, 258.625, 249.931, 240.497, 235.423, 228.63, 219.854, 214.004, 205.425, 199.114, 193.618, 185.644, 180.923, 174.289, 169.641, 161.016, 157.398, 152.151, 147.425, 140.933, 135.924, 132.365, 127.017, 122.127, 117.817, 113.076, 109.055, 105.16, 101.323, 98.098, 95.0548, 90.729, 87.6495, 84.0899, 80.2237, 77.2201, 74.8848, 71.3554, 68.7745, 65.9911, 63.4136, 61.3859, 58.1903, 56.4155, 53.8486, 52.0196, 49.2921, 47.0735, 45.4345, 43.8434, 41.7181, 39.8988, 38.2262, 36.4435, 34.8984, 33.4664, 31.8056, 30.351, 29.2074, 27.6924, 26.7754, 25.4965, 24.2802, 22.9651, 22.0059, 21.0915, 19.9129, 19.1041, 18.1487, 17.3218, 16.5957, 15.5323, 14.8035, 14.2514, 13.3782, 12.8667, 12.2891, 11.61, 11.0026, 10.3747, 9.90294, 9.42648, 8.85324, 8.50121, 7.89834, 7.65197, 7.22768, 6.7755, 6.34855, 5.98336, 5.76555, 5.38056, 5.11024, 4.7748, 4.59117, 4.23247, 4.00814, 3.79607, 3.68702, 3.3767, 3.16309, 2.98282, 2.8095, 2.65875, 2.50561, 2.32516, 2.16357, 2.03235, 1.84061, 1.72628, 1.62305, 1.48916, 1.38784, 1.28366, 1.24693, 1.18552, 1.16085, 1.12596, 1.09298, 1.07402, 1.06105, 1.02954};
    TChain photonTree("photonTree"), EventTree("EventTree"), HiTree("HiTree"),skimanalysis("skimanalysis"),hltanalysis("hltanalysis");

    photonTree.Add(input_dir+in_file_path+input_pho_tree);
    HiTree.Add(input_dir+in_file_path+input_HiTree);
    skimanalysis.Add(input_dir+in_file_path+input_skimanalysis);

    // photonTree.AddFriend("EventTree");
    photonTree.AddFriend("HiTree");
    photonTree.AddFriend("skimanalysis");

    // ----------------------------------------------------------------------------------------------------------------
    // Variables

        Int_t hiBin=0;
        // float pthat=0;
        Float_t weight = 0;

        photonTree.SetBranchAddress("hiBin", &hiBin);
        // photonTree.SetBranchAddress("pthat", &pthat);
        photonTree.SetBranchAddress("weight", &weight);

        // reco::GenParticle
        std::vector<int>*    mcStatus = 0;
        std::vector<int>*    mcPID = 0;
        std::vector<int>*    mcMomPID = 0;
        std::vector<float>*  mcPt = 0;
        std::vector<float>*  mcEta = 0;
        std::vector<float>*  mcPhi = 0;
        std::vector<float>*  mcE = 0;
        std::vector<float>*  mcEt = 0;
        std::vector<float>*  mcMass = 0;
        std::vector<float>*  mcCalIsoDR03 = 0;
        std::vector<float>*  mcCalIsoDR04 = 0;
        std::vector<float>*  mcTrkIsoDR03 = 0;
        std::vector<float>*  mcTrkIsoDR04 = 0;

        // reco::Photon
        std::vector<float>*  phoE = 0;
        std::vector<float>*  phoEt = 0;
        std::vector<float>*  phoEta = 0;
        std::vector<float>*  phoPhi = 0;
        std::vector<float>*  phoHoverE = 0;
        std::vector<float>*  pho_ecalClusterIsoR3 = 0;
        std::vector<float>*  pho_hcalRechitIsoR3 = 0;
        std::vector<float>*  pho_trackIsoR3PtCut20 = 0;
        std::vector<float>*  pho_ecalClusterIsoR4 = 0;
        std::vector<float>*  pho_hcalRechitIsoR4 = 0;
        std::vector<float>*  pho_trackIsoR4PtCut20 = 0;
        std::vector<int>*    pho_genMatchedIndex = 0;
        std::vector<float>*  phoSigmaEtaEta_2012 = 0;

        std::vector<float>*  pfcIso3subUE = 0;
        std::vector<float>*  pfnIso3subUE = 0;
        std::vector<float>*  pfpIso3subUE = 0; //! For MiniAOD by default this does not exclude the cone!!
        std::vector<float>*  pfcIso4subUE = 0;
        std::vector<float>*  pfnIso4subUE = 0;
        std::vector<float>*  pfpIso4subUE = 0;

        std::vector<float>*  pfpIso3subSCsubUE = 0; //! For MiniAOD by default this does not exclude the cone!!
        std::vector<float>*  pfpIso4subSCsubUE = 0; 

        // Additional photon PF iso variables used in MiniAOD

        // std::vector<float>*  pfcIso3subUEec = 0;
        // std::vector<float>*  pfnIso3subUEec = 0;
        // std::vector<float>*  pfpIso3subUEec = 0;
        // std::vector<float>*  pfcIso4subUEec = 0;
        // std::vector<float>*  pfnIso4subUEec = 0;
        // std::vector<float>*  pfpIso4subUEec = 0;

        // // photon pf isolation SC energy subtracted, UE-subtracted and cone excluded 
        // std::vector<float>* pfpIso2subSCsubUEec = 0;
        // std::vector<float>* pfpIso3subSCsubUEec = 0;
        // std::vector<float>* pfpIso4subSCsubUEec = 0;

        // std::vector<float>* pfcIso2subSCsubUEec = 0;
        // std::vector<float>* pfcIso3subSCsubUEec = 0;
        // std::vector<float>* pfcIso4subSCsubUEec = 0;

        // std::vector<float>* pfnIso2subSCsubUEec = 0;
        // std::vector<float>* pfnIso3subSCsubUEec = 0;
        // std::vector<float>* pfnIso4subSCsubUEec = 0;

        // // photon pf isolation No Removal, UE-subtracted and cone excluded 
        // std::vector<float>* pfpIso2NoRemovalsubUEec = 0;
        // std::vector<float>* pfpIso3NoRemovalsubUEec = 0;
        // std::vector<float>* pfpIso4NoRemovalsubUEec = 0;

        // std::vector<float>* pfcIso2NoRemovalsubUEec = 0;
        // std::vector<float>* pfcIso3NoRemovalsubUEec = 0;
        // std::vector<float>* pfcIso4NoRemovalsubUEec = 0;

        // std::vector<float>* pfnIso2NoRemovalsubUEec = 0;
        // std::vector<float>* pfnIso3NoRemovalsubUEec = 0;
        // std::vector<float>* pfnIso4NoRemovalsubUEec = 0;

        std::vector<float>*  pfcIso3FPsubUE = 0;
        std::vector<float>*  pfnIso3FPsubUE = 0;
        // std::vector<float>*  pfpIso3FPsubUE = 0;

        std::vector<float>*  pho_swissCrx = 0;
        std::vector<float>*  pho_seedTime = 0;

        std::vector<float>* phoSCRawE = 0;
        std::vector<float>* phoSCEta = 0;
        std::vector<float>* phoSCPhi = 0;
        std::vector<float>* phoSCEtaWidth = 0;
        std::vector<float>* phoSCPhiWidth = 0;
        std::vector<float>* phoE3x3_2012 = 0;
        std::vector<float>* phoMaxEnergyXtal_2012 = 0;
        std::vector<float>* phoE2nd_2012 = 0;
        std::vector<float>* phoELeft_2012 = 0;
        std::vector<float>* phoERight_2012 = 0;
        std::vector<float>* phoETop_2012 = 0;
        std::vector<float>* phoEBottom_2012 = 0;
        std::vector<float>* phoSigmaIEtaIEta_2012 = 0;
        std::vector<float>* phoSigmaIEtaIPhi_2012 = 0;
        std::vector<float>* phoSigmaIPhiIPhi_2012 = 0;
        Float_t rho = 0;
        std::vector<float>* phoESEn = 0;

        std::vector<int>* phoSCnHits = 0;
        std::vector<float>* phoE5x5_2012 = 0;
        std::vector<float>* phoHadTowerOverEm = 0;
        std::vector<float>* phoHadTowerOverEm1 = 0;
        std::vector<float>* phoHadTowerOverEm2 = 0;
        std::vector<float>* phoR9_2012 = 0;

        // reco::Electron
        std::vector<float>* elePt = 0;
        std::vector<float>* eleEta = 0;
        std::vector<float>* elePhi = 0;
        std::vector<float>* eleEoverP = 0;

        std::vector<float>* eleSigmaIEtaIEta_2012 = 0;
        std::vector<float>* eledEtaSeedAtVtx = 0;
        std::vector<float>* eledPhiAtVtx = 0;
        std::vector<float>* eleHoverE = 0;
        std::vector<float>* eleEoverPInv = 0;
        std::vector<int>* eleMissHits = 0;
        std::vector<float>* eleIP3D = 0;

        photonTree.SetBranchAddress("mcStatus",     &mcStatus);
        photonTree.SetBranchAddress("mcPID",        &mcPID);
        photonTree.SetBranchAddress("mcPt",         &mcPt);
        photonTree.SetBranchAddress("mcEta",        &mcEta);
        photonTree.SetBranchAddress("mcPhi",        &mcPhi);
        photonTree.SetBranchAddress("mcE",          &mcE);
        photonTree.SetBranchAddress("mcEt",         &mcEt);   
        photonTree.SetBranchAddress("mcCalIsoDR03", &mcCalIsoDR03);
        photonTree.SetBranchAddress("mcCalIsoDR04", &mcCalIsoDR04);
        photonTree.SetBranchAddress("mcTrkIsoDR03", &mcTrkIsoDR03);
        photonTree.SetBranchAddress("mcTrkIsoDR04", &mcTrkIsoDR04);
        photonTree.SetBranchAddress("mcMass",       &mcMass);
        photonTree.SetBranchAddress("mcMomPID",     &mcMomPID);

        photonTree.SetBranchAddress("phoE",                  &phoE);
        photonTree.SetBranchAddress("phoEt",                 &phoEt);
        photonTree.SetBranchAddress("phoEta",                &phoEta);
        photonTree.SetBranchAddress("phoPhi",                &phoPhi);
        photonTree.SetBranchAddress("phoHoverE",             &phoHoverE);
        photonTree.SetBranchAddress("pho_ecalClusterIsoR3",  &pho_ecalClusterIsoR3);
        photonTree.SetBranchAddress("pho_hcalRechitIsoR3",   &pho_hcalRechitIsoR3);
        photonTree.SetBranchAddress("pho_trackIsoR3PtCut20", &pho_trackIsoR3PtCut20);
        photonTree.SetBranchAddress("pho_ecalClusterIsoR4",  &pho_ecalClusterIsoR4);
        photonTree.SetBranchAddress("pho_hcalRechitIsoR4",   &pho_hcalRechitIsoR4);
        photonTree.SetBranchAddress("pho_trackIsoR4PtCut20", &pho_trackIsoR4PtCut20);
        photonTree.SetBranchAddress("pho_genMatchedIndex",   &pho_genMatchedIndex);
        photonTree.SetBranchAddress("phoSigmaEtaEta_2012",   &phoSigmaEtaEta_2012);
        photonTree.SetBranchAddress("pfcIso3subUE",          &pfcIso3subUE);
        photonTree.SetBranchAddress("pfnIso3subUE",          &pfnIso3subUE);
        photonTree.SetBranchAddress("pfpIso3subUE",          &pfpIso3subUE);
        photonTree.SetBranchAddress("pfcIso4subUE",          &pfcIso4subUE);
        photonTree.SetBranchAddress("pfnIso4subUE",          &pfnIso4subUE);
        photonTree.SetBranchAddress("pfpIso4subUE",          &pfpIso4subUE);

        photonTree.SetBranchAddress("pfpIso3subSCsubUE",          &pfpIso3subSCsubUE);
        photonTree.SetBranchAddress("pfpIso4subSCsubUE",          &pfpIso4subSCsubUE);

        // photonTree.SetBranchAddress("pfcIso3subUEec",          &pfcIso3subUEec);
        // photonTree.SetBranchAddress("pfnIso3subUEec",          &pfnIso3subUEec);
        // photonTree.SetBranchAddress("pfpIso3subUEec",          &pfpIso3subUEec);
        // photonTree.SetBranchAddress("pfcIso4subUEec",          &pfcIso4subUEec);
        // photonTree.SetBranchAddress("pfnIso4subUEec",          &pfnIso4subUEec);
        // photonTree.SetBranchAddress("pfpIso4subUEec",          &pfpIso4subUEec);

        //* photon pf isolation SC energy subtracted, UE-subtracted and cone excluded 
        // photonTree.SetBranchAddress("pfpIso2subSCsubUEec" ,&pfpIso2subSCsubUEec);
        // photonTree.SetBranchAddress("pfpIso3subSCsubUEec" ,&pfpIso3subSCsubUEec);
        // photonTree.SetBranchAddress("pfpIso4subSCsubUEec" ,&pfpIso4subSCsubUEec);

        // photonTree.SetBranchAddress("pfcIso2subSCsubUEec" ,&pfcIso2subSCsubUEec);
        // photonTree.SetBranchAddress("pfcIso3subSCsubUEec" ,&pfcIso3subSCsubUEec);
        // photonTree.SetBranchAddress("pfcIso4subSCsubUEec" ,&pfcIso4subSCsubUEec);

        // photonTree.SetBranchAddress("pfnIso2subSCsubUEec" ,&pfnIso2subSCsubUEec);
        // photonTree.SetBranchAddress("pfnIso3subSCsubUEec" ,&pfnIso3subSCsubUEec);
        // photonTree.SetBranchAddress("pfnIso4subSCsubUEec" ,&pfnIso4subSCsubUEec);

        //* photon pf isolation No Removal, UE-subtracted and cone excluded 
        // photonTree.SetBranchAddress("pfpIso2NoRemovalsubUEec" ,&pfpIso2NoRemovalsubUEec);
        // photonTree.SetBranchAddress("pfpIso3NoRemovalsubUEec" ,&pfpIso3NoRemovalsubUEec);
        // photonTree.SetBranchAddress("pfpIso4NoRemovalsubUEec" ,&pfpIso4NoRemovalsubUEec);

        // photonTree.SetBranchAddress("pfcIso2NoRemovalsubUEec" ,&pfcIso2NoRemovalsubUEec);
        // photonTree.SetBranchAddress("pfcIso3NoRemovalsubUEec" ,&pfcIso3NoRemovalsubUEec);
        // photonTree.SetBranchAddress("pfcIso4NoRemovalsubUEec" ,&pfcIso4NoRemovalsubUEec);

        // photonTree.SetBranchAddress("pfnIso2NoRemovalsubUEec" ,&pfnIso2NoRemovalsubUEec);
        // photonTree.SetBranchAddress("pfnIso3NoRemovalsubUEec" ,&pfnIso3NoRemovalsubUEec);
        // photonTree.SetBranchAddress("pfnIso4NoRemovalsubUEec" ,&pfnIso4NoRemovalsubUEec);


        photonTree.SetBranchAddress("pfcIso3FPsubUE",          &pfcIso3FPsubUE);
        photonTree.SetBranchAddress("pfnIso3FPsubUE",          &pfnIso3FPsubUE);
        // photonTree.SetBranchAddress("pfpIso3FPsubUE",          &pfpIso3FPsubUE);

        photonTree.SetBranchAddress("phoSCRawE",          &phoSCRawE);
        photonTree.SetBranchAddress("phoSCEta",          &phoSCEta);
        photonTree.SetBranchAddress("phoSCPhi",          &phoSCPhi);
        photonTree.SetBranchAddress("phoSCEtaWidth",          &phoSCEtaWidth);
        photonTree.SetBranchAddress("phoSCPhiWidth",          &phoSCPhiWidth);
        photonTree.SetBranchAddress("phoE3x3_2012",          &phoE3x3_2012);
        photonTree.SetBranchAddress("phoMaxEnergyXtal_2012",          &phoMaxEnergyXtal_2012);
        photonTree.SetBranchAddress("phoE2nd_2012",          &phoE2nd_2012);
        photonTree.SetBranchAddress("phoELeft_2012",          &phoELeft_2012);
        photonTree.SetBranchAddress("phoERight_2012",          &phoERight_2012);
        photonTree.SetBranchAddress("phoETop_2012",          &phoETop_2012);
        photonTree.SetBranchAddress("phoEBottom_2012",          &phoEBottom_2012);
        photonTree.SetBranchAddress("phoSigmaIEtaIEta_2012",          &phoSigmaIEtaIEta_2012);
        photonTree.SetBranchAddress("phoSigmaIEtaIPhi_2012",          &phoSigmaIEtaIPhi_2012);
        photonTree.SetBranchAddress("phoSigmaIPhiIPhi_2012",          &phoSigmaIPhiIPhi_2012);
        photonTree.SetBranchAddress("rho",          &rho);
        photonTree.SetBranchAddress("phoESEn",          &phoESEn);

        photonTree.SetBranchAddress("phoSCnHits",            &phoSCnHits);
        photonTree.SetBranchAddress("phoE5x5_2012",          &phoE5x5_2012);
        photonTree.SetBranchAddress("phoHadTowerOverEm",     &phoHadTowerOverEm);
        photonTree.SetBranchAddress("phoHadTowerOverEm1",    &phoHadTowerOverEm1);
        photonTree.SetBranchAddress("phoHadTowerOverEm2",    &phoHadTowerOverEm2);
        photonTree.SetBranchAddress("phoR9_2012",            &phoR9_2012);

        photonTree.SetBranchAddress("pho_swissCrx",&pho_swissCrx);
        photonTree.SetBranchAddress("pho_seedTime",&pho_seedTime);

        photonTree.SetBranchAddress("elePt",   &elePt);
        photonTree.SetBranchAddress("eleEta",  &eleEta);
        photonTree.SetBranchAddress("elePhi",  &elePhi);
        photonTree.SetBranchAddress("eleEoverP",  &eleEoverP);

        photonTree.SetBranchAddress("eleSigmaIEtaIEta_2012",   &eleSigmaIEtaIEta_2012);
        photonTree.SetBranchAddress("eledEtaSeedAtVtx",  &eledEtaSeedAtVtx);
        photonTree.SetBranchAddress("eledPhiAtVtx",  &eledPhiAtVtx);
        photonTree.SetBranchAddress("eleHoverE",  &eleHoverE);
        photonTree.SetBranchAddress("eleEoverPInv",  &eleEoverPInv);
        photonTree.SetBranchAddress("eleMissHits",  &eleMissHits);
        photonTree.SetBranchAddress("eleIP3D",  &eleIP3D);

        int pprimaryVertexFilter = 0;
        int pclusterCompatibilityFilter = 0;
        int phfCoincFilter2Th4 = 0;

        photonTree.SetBranchAddress("pprimaryVertexFilter",  &pprimaryVertexFilter);
        photonTree.SetBranchAddress("pclusterCompatibilityFilter",  &pclusterCompatibilityFilter);
        photonTree.SetBranchAddress("phfCoincFilter2Th4",  &phfCoincFilter2Th4);

    // -------- End Tree Variable Declaration
    // ----------------------------------------------------------------------------------------------------------------
    // Histograms
        TH1::SetDefaultSumw2();
        TH2::SetDefaultSumw2();

        TH1D* h_lead_pho_et[neta][ncent];
        TH1D* h_lead_pho_eta[neta][ncent];
        TH1D* h_lead_pho_SIEIE[neta][ncent];
        TH1D* h_lead_pho_phi[neta][ncent];
        TH1D* h_lead_pho_HoverE[neta][ncent];
        TH1D* h_lead_pho_SumCalIso[neta][ncent];
        TH1D* h_lead_pho_ECALIso[neta][ncent];
        TH1D* h_lead_pho_HCALIso[neta][ncent];
        TH1D* h_lead_pho_TRKIso[neta][ncent];
        TH1D* h_lead_pho_PFPIso[neta][ncent];
        TH1D* h_lead_pho_PFNIso[neta][ncent];
        TH1D* h_lead_pho_PFCIso[neta][ncent];
        TH1D* h_lead_pho_PFPIso_FP[neta][ncent];
        TH1D* h_lead_pho_PFNIso_FP[neta][ncent];
        TH1D* h_lead_pho_PFCIso_FP[neta][ncent];

        TH1D* h_all_pho_et[neta][ncent];
        TH1D* h_all_pho_eta[neta][ncent];
        TH1D* h_all_pho_SIEIE[neta][ncent];
        TH1D* h_all_pho_phi[neta][ncent];
        TH1D* h_all_pho_HoverE[neta][ncent];
        TH1D* h_all_pho_SumCalIso[neta][ncent];
        TH1D* h_all_pho_ECALIso[neta][ncent];
        TH1D* h_all_pho_HCALIso[neta][ncent];
        TH1D* h_all_pho_TRKIso[neta][ncent];
        TH1D* h_all_pho_PFPIso[neta][ncent];
        TH1D* h_all_pho_PFNIso[neta][ncent];
        TH1D* h_all_pho_PFCIso[neta][ncent];
        TH1D* h_all_pho_PFPIso_FP[neta][ncent];
        TH1D* h_all_pho_PFNIso_FP[neta][ncent];
        TH1D* h_all_pho_PFCIso_FP[neta][ncent];

        const Int_t net_bins = 10;
        Double_t et_edges[net_bins+1] = {0.0, 15, 20, 25, 30, 40, 50, 60, 80, 120, 200};

        const Int_t iso_bins = 12;
        Double_t isolation_edges[iso_bins+1] = {-50,-20,-10,-5,-3,-1,1,3,5,10,20,50,100};

        for (std::size_t i = 0; i < neta; ++i){
            for (std::size_t j = 0; j < ncent; ++j){

                h_lead_pho_et[i][j] = new TH1D(Form("h_lead_pho_et_%zu_%zu",i,j),Form("h_lead_pho_et_%zu_%zu;Leading #gamma p_{T} (GeV);Norm. Events",i,j),net_bins,et_edges); // 30,0,150
                if(i==0){
                    h_lead_pho_eta[i][j] = new TH1D(Form("h_lead_pho_eta_%zu_%zu",i,j),Form("h_lead_pho_eta_%zu_%zu;Leading #gamma |#eta|;Norm. Events",i,j),30,0,1.44);
                    h_lead_pho_SIEIE[i][j] = new TH1D(Form("h_lead_pho_SIEIE_%zu_%zu",i,j),Form("h_lead_pho_SIEIE_%zu_%zu;Leading #gamma #sigma_{#eta #eta};Norm. Events",i,j),15,0,0.03);
                }
                if(i==1){
                    h_lead_pho_eta[i][j] = new TH1D(Form("h_lead_pho_eta_%zu_%zu",i,j),Form("h_lead_pho_eta_%zu_%zu;Leading #gamma SC |#eta|;Norm. Events",i,j),30,1.566,2.1);
                    h_lead_pho_SIEIE[i][j] = new TH1D(Form("h_lead_pho_SIEIE_%zu_%zu",i,j),Form("h_lead_pho_SIEIE_%zu_%zu;Leading #gamma #sigma_{#eta #eta};Norm. Events",i,j),30,0,0.1);
                }
                h_lead_pho_phi[i][j] = new TH1D(Form("h_lead_pho_phi_%zu_%zu",i,j),Form("h_lead_pho_phi_%zu_%zu;Leading #gamma SC #phi;Norm. Events",i,j),15,-3.14,3.14);
                h_lead_pho_HoverE[i][j] = new TH1D(Form("h_lead_pho_HoverE_%zu_%zu",i,j),Form("h_lead_pho_HoverE_%zu_%zu;Leading #gamma H/E;Norm. Events",i,j),20,0,0.1);
                h_lead_pho_SumCalIso[i][j] = new TH1D(Form("h_lead_pho_SumCalIso_%zu_%zu",i,j),Form("h_lead_pho_SumCalIso_%zu_%zu;Leading #gamma #Sigma Det-Iso;Norm. Events",i,j),30,-50,100);
                h_lead_pho_ECALIso[i][j] = new TH1D(Form("h_lead_pho_ECALIso_%zu_%zu",i,j),Form("h_lead_pho_ECALIso_%zu_%zu;Leading #gamma ECAL Cluster IsoR3;Norm. Events",i,j),iso_bins, isolation_edges);
                h_lead_pho_HCALIso[i][j] = new TH1D(Form("h_lead_pho_HCALIso_%zu_%zu",i,j),Form("h_lead_pho_HCALIso_%zu_%zu;Leading #gamma HCAL Rechit IsoR3;Norm. Events",i,j),iso_bins, isolation_edges);
                h_lead_pho_TRKIso[i][j] = new TH1D(Form("h_lead_pho_TRKIso_%zu_%zu",i,j),Form("h_lead_pho_TRKIso_%zu_%zu;Leading #gamma trackIsoR3PtCut20;Norm. Events",i,j),iso_bins, isolation_edges);
                h_lead_pho_PFPIso[i][j] = new TH1D(Form("h_lead_pho_PFPIso_%zu_%zu",i,j),Form("h_lead_pho_PFPIso_%zu_%zu;Leading #gamma pfpIso3subUEec;Norm. Events",i,j),iso_bins, isolation_edges);
                h_lead_pho_PFNIso[i][j] = new TH1D(Form("h_lead_pho_PFNIso_%zu_%zu",i,j),Form("h_lead_pho_PFNIso_%zu_%zu;Leading #gamma pfnIso3subUEec;Norm. Events",i,j),iso_bins, isolation_edges);
                h_lead_pho_PFCIso[i][j] = new TH1D(Form("h_lead_pho_PFCIso_%zu_%zu",i,j),Form("h_lead_pho_PFCIso_%zu_%zu;Leading #gamma pfcIso3subUEec;Norm. Events",i,j),iso_bins, isolation_edges);
                h_lead_pho_PFPIso_FP[i][j] = new TH1D(Form("h_lead_pho_PFPIso_FP_%zu_%zu",i,j),Form("h_lead_pho_PFPIso_FP_%zu_%zu;Leading #gamma pfpIso3SubSCsubUE;Norm. Events",i,j),iso_bins, isolation_edges);
                h_lead_pho_PFNIso_FP[i][j] = new TH1D(Form("h_lead_pho_PFNIso_FP_%zu_%zu",i,j),Form("h_lead_pho_PFNIso_FP_%zu_%zu;Leading #gamma pfnIso3subUE footprint included;Norm. Events",i,j),iso_bins, isolation_edges);
                h_lead_pho_PFCIso_FP[i][j] = new TH1D(Form("h_lead_pho_PFCIso_FP_%zu_%zu",i,j),Form("h_lead_pho_PFCIso_FP_%zu_%zu;Leading #gamma pfcIso3subUE footprint included;Norm. Events",i,j),iso_bins, isolation_edges);

                h_all_pho_et[i][j] = new TH1D(Form("h_all_pho_et_%zu_%zu",i,j),Form("h_all_pho_et_%zu_%zu;All #gamma p_{T} (GeV);Norm. Events",i,j),net_bins,et_edges); // 30,0,150
                if(i==0){
                    h_all_pho_eta[i][j] = new TH1D(Form("h_all_pho_eta_%zu_%zu",i,j),Form("h_all_pho_eta_%zu_%zu;All #gamma |#eta|;Norm. Events",i,j),30,0,1.44);
                    h_all_pho_SIEIE[i][j] = new TH1D(Form("h_all_pho_SIEIE_%zu_%zu",i,j),Form("h_all_pho_SIEIE_%zu_%zu;All #gamma #sigma_{#eta #eta};Norm. Events",i,j),15,0,0.03);
                }
                if(i==1){
                    h_all_pho_eta[i][j] = new TH1D(Form("h_all_pho_eta_%zu_%zu",i,j),Form("h_all_pho_eta_%zu_%zu;All #gamma SC |#eta|;Norm. Events",i,j),30,1.566,2.1);
                    h_all_pho_SIEIE[i][j] = new TH1D(Form("h_all_pho_SIEIE_%zu_%zu",i,j),Form("h_all_pho_SIEIE_%zu_%zu;All #gamma #sigma_{#eta #eta};Norm. Events",i,j),30,0,0.1);
                }
                h_all_pho_phi[i][j] = new TH1D(Form("h_all_pho_phi_%zu_%zu",i,j),Form("h_all_pho_phi_%zu_%zu;All #gamma SC #phi;Norm. Events",i,j),10,-3.14,3.14);
                h_all_pho_HoverE[i][j] = new TH1D(Form("h_all_pho_HoverE_%zu_%zu",i,j),Form("h_all_pho_HoverE_%zu_%zu;Leading #gamma H/E;Norm. Events",i,j),20,0,0.1);
                h_all_pho_SIEIE[i][j] = new TH1D(Form("h_all_pho_SIEIE_%zu_%zu",i,j),Form("h_all_pho_SIEIE_%zu_%zu;All #gamma #sigma_{#eta #eta};Norm. Events",i,j),20,0,0.05);
                h_all_pho_SumCalIso[i][j] = new TH1D(Form("h_all_pho_SumCalIso_%zu_%zu",i,j),Form("h_all_pho_SumCalIso_%zu_%zu;All #gamma #Sigma Det-Iso;Norm. Events",i,j),30,-50,100);
                h_all_pho_ECALIso[i][j] = new TH1D(Form("h_all_pho_ECALIso_%zu_%zu",i,j),Form("h_all_pho_ECALIso_%zu_%zu;All #gamma ECAL Cluster IsoR3;Norm. Events",i,j),iso_bins, isolation_edges);
                h_all_pho_HCALIso[i][j] = new TH1D(Form("h_all_pho_HCALIso_%zu_%zu",i,j),Form("h_all_pho_HCALIso_%zu_%zu;All #gamma HCAL Rechit IsoR3;Norm. Events",i,j),iso_bins, isolation_edges);
                h_all_pho_TRKIso[i][j] = new TH1D(Form("h_all_pho_TRKIso_%zu_%zu",i,j),Form("h_all_pho_TRKIso_%zu_%zu;All #gamma trackIsoR3PtCut20;Norm. Events",i,j),iso_bins, isolation_edges);
                h_all_pho_PFPIso[i][j] = new TH1D(Form("h_all_pho_PFPIso_%zu_%zu",i,j),Form("h_all_pho_PFPIso_%zu_%zu;All #gamma pfpIso3subUEec;Norm. Events",i,j),iso_bins, isolation_edges);
                h_all_pho_PFNIso[i][j] = new TH1D(Form("h_all_pho_PFNIso_%zu_%zu",i,j),Form("h_all_pho_PFNIso_%zu_%zu;All #gamma pfnIso3subUEec;Norm. Events",i,j),iso_bins, isolation_edges);
                h_all_pho_PFCIso[i][j] = new TH1D(Form("h_all_pho_PFCIso_%zu_%zu",i,j),Form("h_all_pho_PFCIso_%zu_%zu;All #gamma pfcIso3subUEec;Norm. Events",i,j),iso_bins, isolation_edges);
                h_all_pho_PFPIso_FP[i][j] = new TH1D(Form("h_all_pho_PFPIso_FP_%zu_%zu",i,j),Form("h_all_pho_PFPIso_FP_%zu_%zu;All #gamma pfpIso3SubSCsubUE footprint included;Norm. Events",i,j),iso_bins, isolation_edges);
                h_all_pho_PFNIso_FP[i][j] = new TH1D(Form("h_all_pho_PFNIso_FP_%zu_%zu",i,j),Form("h_all_pho_PFNIso_FP_%zu_%zu;All #gamma pfnIso3subUE footprint included;Norm. Events",i,j),iso_bins, isolation_edges);
                h_all_pho_PFCIso_FP[i][j] = new TH1D(Form("h_all_pho_PFCIso_FP_%zu_%zu",i,j),Form("h_all_pho_PFCIso_FP_%zu_%zu;All #gamma pfcIso3subUE footprint included;Norm. Events",i,j),iso_bins, isolation_edges);
            }
        }



// ----------------------------------------------------------------------------------------------------------------
//        * * * * *     S T A R T   O F   A C T U A L   R U N N I N G   O N   E V E N T S     * * * * *
// ----------------------------------------------------------------------------------------------------------------

    Int_t nEv=photonTree.GetEntries();
    std::cout<<in_label<<" \t => "<<nEv<<"\n";

    for(int iEntry=0; iEntry< nEv; iEntry++){
        // displayProgress(iEntry,nEv);
        photonTree.GetEntry(iEntry);
        // skimanalysis.GetEntry(iEntry);
        // std::cout<<"Inside event loop = "<<iEntry;
        // printf("\n");
        float scale = 1;

        int pho_index=-1, genin=-1;
        float Etmax=-1;
        float corrected_Et = -1;
        scale*=weight*Ncoll[hiBin];
        // std::cout<<"Event = "<<iEntry<<"    photon = "<<phoEt->size()<<"\t pprimaryVertexFilter ="<<pprimaryVertexFilter<<"\n";

        if(pprimaryVertexFilter<=0) continue;
        if(pclusterCompatibilityFilter<=0) continue;
        if(phfCoincFilter2Th4<=0) continue;
        // if(hiBin>180) continue;

        for(int ipho=0; ipho<phoEt->size(); ipho++){
            // if(!(fabs(phoEta->at(ipho))<2.4)) continue; // || (fabs(phoEta->at(ipho))>1.6 && fabs(phoEta->at(ipho))<2.0)
            if(phoEta->at(ipho)<-1.39 && phoPhi->at(ipho)<-0.9 && phoPhi->at(ipho)>-1.6) continue;  // HEM Failure
            if(phoEt->at(ipho)<15) continue;                          // Minimum ET cut
            if(phoSigmaEtaEta_2012->at(ipho)<=0.002) continue;        // Spike Cuts                  
            if(fabs(pho_seedTime->at(ipho))>=3 || pho_swissCrx->at(ipho)>=0.9) continue;


            if(phoHoverE->at(ipho)>=0.1) continue;    

            if(pho_genMatchedIndex->at(ipho)<0) continue;   // True photon selection
            if(abs(mcPID->at(pho_genMatchedIndex->at(ipho)))!=22) continue;

            //! Choosing only NOT MATCHED Photons
            // if(pho_genMatchedIndex->at(ipho)>=0 && abs(mcPID->at(pho_genMatchedIndex->at(ipho)))==22) continue;

            corrected_Et = phoEt->at(ipho);//myPhoERegr.getCorrectedPt(phoVars, phoEt->at(ipho), phoEta->at(ipho), phoSCEta->at(ipho));

            if(Etmax<corrected_Et){
                Etmax = corrected_Et;
                pho_index = ipho;
                // genin = pho_genMatchedIndex->at(ipho);
            }

            // std::cout<<"Photon = "<<ipho<<"\n";

            for (std::size_t i = 0; i < neta; ++i){
                if(!(fabs(phoSCEta->at(ipho))>=min_eta[i] && fabs(phoSCEta->at(ipho))<max_eta[i])) continue;   

                for (std::size_t j = 0; j < ncent; ++j){
                    if(!(hiBin>=min_cent[j] && hiBin<max_cent[j])) continue;   

                    h_all_pho_et[i][j]->Fill(         phoEt->at(ipho), scale);
                    h_all_pho_eta[i][j]->Fill(        phoSCEta->at(ipho), scale);
                    h_all_pho_phi[i][j]->Fill(        phoSCPhi->at(ipho), scale);
                    h_all_pho_HoverE[i][j]->Fill(     phoHoverE->at(ipho), scale);
                    h_all_pho_SIEIE[i][j]->Fill(      phoSigmaIEtaIEta_2012->at(ipho), scale);
                    h_all_pho_SumCalIso[i][j]->Fill(  pho_ecalClusterIsoR3->at(ipho)+pho_hcalRechitIsoR3->at(ipho)+pho_trackIsoR3PtCut20->at(ipho), scale);
                    h_all_pho_ECALIso[i][j]->Fill(    pho_ecalClusterIsoR3->at(ipho), scale);
                    h_all_pho_HCALIso[i][j]->Fill(    pho_hcalRechitIsoR3->at(ipho), scale);
                    h_all_pho_TRKIso[i][j]->Fill(     pho_trackIsoR3PtCut20->at(ipho), scale);
                    h_all_pho_PFPIso[i][j]->Fill(     pfpIso3subUE->at(ipho), scale);
                    h_all_pho_PFNIso[i][j]->Fill(     pfnIso3subUE->at(ipho), scale);
                    h_all_pho_PFCIso[i][j]->Fill(     pfcIso3subUE->at(ipho), scale);
                    h_all_pho_PFPIso_FP[i][j]->Fill(  pfpIso3subSCsubUE->at(ipho), scale);
                    h_all_pho_PFNIso_FP[i][j]->Fill(  pfnIso3FPsubUE->at(ipho), scale);
                    h_all_pho_PFCIso_FP[i][j]->Fill(  pfcIso3FPsubUE->at(ipho), scale);
                }
            }
            // std::cout<<"End histogram filling loop = "<<ipho<<"\n";
        
        }
        if(pho_index==-1) continue;

        for (std::size_t i = 0; i < neta; ++i){
            if(!(fabs(phoSCEta->at(pho_index))>=min_eta[i] && fabs(phoSCEta->at(pho_index))<max_eta[i])) continue;   

            for (std::size_t j = 0; j < ncent; ++j){
                if(!(hiBin>=min_cent[j] && hiBin<max_cent[j])) continue;   

                h_lead_pho_et[i][j]->Fill(         phoEt->at(pho_index), scale);
                h_lead_pho_eta[i][j]->Fill(        phoSCEta->at(pho_index), scale);
                h_lead_pho_phi[i][j]->Fill(        phoSCPhi->at(pho_index), scale);
                h_lead_pho_HoverE[i][j]->Fill(     phoHoverE->at(pho_index), scale);
                h_lead_pho_SIEIE[i][j]->Fill(      phoSigmaIEtaIEta_2012->at(pho_index), scale);
                h_lead_pho_SumCalIso[i][j]->Fill(  pho_ecalClusterIsoR3->at(pho_index)+pho_hcalRechitIsoR3->at(pho_index)+pho_trackIsoR3PtCut20->at(pho_index), scale);
                h_lead_pho_ECALIso[i][j]->Fill(    pho_ecalClusterIsoR3->at(pho_index), scale);
                h_lead_pho_HCALIso[i][j]->Fill(    pho_hcalRechitIsoR3->at(pho_index), scale);
                h_lead_pho_TRKIso[i][j]->Fill(     pho_trackIsoR3PtCut20->at(pho_index), scale);
                h_lead_pho_PFPIso[i][j]->Fill(     pfpIso3subUE->at(pho_index), scale);
                h_lead_pho_PFNIso[i][j]->Fill(     pfnIso3subUE->at(pho_index), scale);
                h_lead_pho_PFCIso[i][j]->Fill(     pfcIso3subUE->at(pho_index), scale);
                h_lead_pho_PFPIso_FP[i][j]->Fill(  pfpIso3subSCsubUE->at(pho_index), scale);
                h_lead_pho_PFNIso_FP[i][j]->Fill(  pfnIso3FPsubUE->at(pho_index), scale);
                h_lead_pho_PFCIso_FP[i][j]->Fill(  pfcIso3FPsubUE->at(pho_index), scale);
            }
        }
        

    } // End event loop

    // std::cout<<"Number of selected events = "<<h_lead_pho_et[0][0]->GetEntries()<<"\n";

    // ------ Save histograms to File
    fout->cd();
    gDirectory->mkdir(in_label);
    fout->cd(in_label);

    for (std::size_t i = 0; i < neta; ++i){

        for (std::size_t j = 0; j < ncent; ++j){

            h_lead_pho_et[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_eta[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_phi[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_HoverE[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_SIEIE[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_SumCalIso[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_ECALIso[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_HCALIso[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_TRKIso[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_PFPIso[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_PFNIso[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_PFCIso[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_PFPIso_FP[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_PFNIso_FP[i][j]->Write("",TObject::kOverwrite);
            h_lead_pho_PFCIso_FP[i][j]->Write("",TObject::kOverwrite);

            h_all_pho_et[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_eta[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_phi[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_HoverE[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_SIEIE[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_SumCalIso[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_ECALIso[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_HCALIso[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_TRKIso[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_PFPIso[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_PFNIso[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_PFCIso[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_PFPIso_FP[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_PFNIso_FP[i][j]->Write("",TObject::kOverwrite);
            h_all_pho_PFCIso_FP[i][j]->Write("",TObject::kOverwrite);
        }
    }

    fout->cd();
}

void overlay_ZS(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
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
    gStyle->SetPalette(1);
    TColor *pal = new TColor();
    // good for primary marker colors      

    /*                                                                                       
    Int_t kmagenta = pal->GetColor(124,  0,124);
    Int_t kviolet  = pal->GetColor( 72,  0,190);
    Int_t kblue    = pal->GetColor(  9,  0,200);
    Int_t kazure   = pal->GetColor(  0, 48, 97);
    Int_t kcyan    = pal->GetColor(  0, 83, 98);
    Int_t kteal    = pal->GetColor(  0, 92, 46);
    Int_t kgreen   = pal->GetColor( 15, 85, 15);
    Int_t kspring  = pal->GetColor( 75, 97, 53);
    Int_t kyellow  = pal->GetColor(117,118,  0);
    Int_t korange  = pal->GetColor(101, 42,  0);
    Int_t kred     = pal->GetColor(190,  0,  3);
    Int_t kpink    = pal->GetColor(180, 35,145);

    Int_t kmagentaLight = pal->GetColor(215,165,215);
    Int_t kvioletLight  = pal->GetColor(200,160,255);
    Int_t kblueLight    = pal->GetColor(178,185,254);
    Int_t kazureLight   = pal->GetColor(153,195,225);
    Int_t kcyanLight    = pal->GetColor(140,209,224);
    Int_t ktealLight    = pal->GetColor( 92,217,141);
    Int_t kgreenLight   = pal->GetColor(135,222,135);
    Int_t kspringLight  = pal->GetColor(151,207,116);
    Int_t kyellowLight  = pal->GetColor(225,225,100);
    Int_t korangeLight  = pal->GetColor(255,168,104);
    Int_t kredLight     = pal->GetColor(253,169,179);
    Int_t kpinkLight    = pal->GetColor(255,192,224);
    */
    //const std::vector<int> colarray  = {kred,kblue,kmagenta,kgreen,kviolet,kazure,korange,kcyan,kteal,kspring,kpink,kyellow,kmagenta,kviolet,kblue};
    //const std::vector<int> markarray = {25, 22, 32, 29, 28, 39, 40,
    //                                    24, 21, 26, 23, 30, 34, 37, 41};
//
    const std::vector<int> colarray  = {1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606,
                                       1,632,600,616,419,804,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41,
                                        20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};

    
    TCanvas c;
    c.cd();
    TLegend *l;
    float leg_x1 = 0.7;
    float leg_y1 = 0.6;
    float leg_x2 = 0.85;
    float leg_y2 = 0.75;
    if(opt.Contains("bcenter")){
        leg_x1 = 0.45;
        leg_y1 = 0.2;
        leg_x2 = 0.55;
        leg_y2 = 0.4;
    }
    else if(opt.Contains("left")){
        leg_x1 = 0.15;
        leg_y1 = 0.6;
        leg_x2 = 0.25;
        leg_y2 = 0.75;
    }
    l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    l->SetFillStyle(0);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->SetTextSize(0.035);
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
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(1,hist[ihist]->GetNbinsX()+1),"width");
        }
        else if(opt.Contains("norm")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2));
        }
        if(opt.Contains("flow"))
            hist[ihist]->GetXaxis()->SetRange(1,hist[ihist]->GetNbinsX()+1);   
        
        if(hist[ihist]->GetMaximum()>ymax) ymax = hist[ihist]->GetMaximum();
        hist[ihist]->Draw(drawopt);
        hist[ihist]->GetXaxis()->SetLabelSize(0);
        hist[ihist]->GetXaxis()->SetTitleOffset(999999);
        l->AddEntry(hist[ihist], histname[ihist], "lep");
        if(ihist==0) drawopt+="SAME";
    }
    hist[0]->SetMinimum(0.0);
    if(!opt.Contains("log"))
        hist[0]->SetMaximum(ymax*1.1);
    else
        hist[0]->SetMaximum(ymax*2);
    l->Draw();

    TLatex latex;
    latex.SetTextSize(0.05);
    latex.DrawLatexNDC(0.12,0.9,"CMS #it{#bf{Run 3 ECAL Study}} "+label); // PbPb 1.69nb^{-1}, pp 300.6pb^{-1} (5.02 TeV)

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.9,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.55,0.9,eopt[0]);
        latex.DrawLatexNDC(0.82,0.9,eopt[1]);
    }    
    latex.SetTextSize(0.035);
    if(eopt.size()>2){
        for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
            if(opt.Contains("bcenter")){
                leg_y2+=0.08;
                latex.DrawLatexNDC(leg_x1,leg_y2,eopt[ind]);
            }
            else{
                leg_y1-=0.08;
                latex.DrawLatexNDC(leg_x1,leg_y1,eopt[ind]);
            }
        }
    }
    
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
        if(hratio)
        hratio->Divide(hist[0]);
        // hratio->Write("Ratio_"+(TString)hist[ihist]->GetName()+"_"+ihist,TObject::kOverwrite);
        hratio->Draw(drawopt);

        // To Get histogram entries in an array
        // double *bins = new double[hratio->GetSize()];
        // std::cout<<"\n{";
        // for (Int_t i=1;i<hratio->GetSize();i++) bins[i] = hratio->GetBinContent(i);
        // for (Int_t i=1;i<hratio->GetSize();i++)printf("%.7f ,",bins[i]); // <<" ,"
        // std::cout<<"}\n";        

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

    
    gPad->Update();
    c.SaveAs(output_path +histname.back()+".png");
    c.Write(histname.back(),TObject::kOverwrite);
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
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
    
    TString drawopt = "nostackE1][P0"; 
    const std::vector<int> colarray  = { 1,632,600,616,419,800,427,898,
                                       922,910,851,877,811,804,434,606,
                                       1,632,600,616,419,800,427,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41,
                                        20, 25, 22, 32, 29, 28, 39, 40,
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

    for(std::size_t ihist=0; ihist<hist.size();){
        if(opt.Contains("eff")){
            if((ihist+1)>=hist.size()) break;
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
        if(!opt.Contains("eff")) ihist++;
    }
    hs.Draw(drawopt);
    if(opt.Contains("eff")){
        hs.SetMaximum(1.1);
        hs.SetMinimum(0);
    }
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
    latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Run 3 ECAL Study}} "+label);

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.6,0.92,eopt[0]);
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
    c.SaveAs(output_path +"/"+histname.back()+".png");
    c.Write(histname.back(),TObject::kWriteDelete);
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}

int main(int argc, char* argv[]){
    // Run with 
    // ./Plot_ZS <optional output label>


    bool flag_overlay=true;

    if(argc%2==0)
        label = (TString)argv[argc-1];

    gROOT->SetBatch();
    gErrorIgnoreLevel = kFatal;
    TString DIR = output_path + "plots_"+label+"/";
    output_path = DIR;
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    fout = new TFile(DIR+"/Output_"+label+".root", "UPDATE");
    fout->cd();

    Plot_ZS("Reference","Reference");

    Plot_ZS("EB_EE_4_SR_HI_4_MI_2","EB_EE_4");
    
    Plot_ZS("EB_EE_8_SR_HI_4_MI_2","EB_EE_8");

    Plot_ZS("EB_EE_10_SR_HI_4_MI_2","EB_EE_10");

    std::cout<<"Output_"<<label<<".root file created";

    fout->Close();

    fout = TFile::Open(DIR+"/Output_"+label+".root", "UPDATE");

    // Overlay
    if(flag_overlay){

        std::vector<TString>histlist = {
            "pho_et",
            "pho_eta",
            "pho_phi",
            "pho_HoverE",
            "pho_SIEIE",
            "pho_SumCalIso",
            "pho_ECALIso",
            "pho_HCALIso",
            "pho_TRKIso",
            "pho_PFPIso",
            "pho_PFNIso",
            "pho_PFCIso",
            "pho_PFPIso_FP",
            "pho_PFNIso_FP",
            "pho_PFCIso_FP",
        };

        for(TString input_hist:histlist){
            TString outplotname = input_hist;
            for (std::size_t k = 0; k <= 1; ++k){    // k=0 -> lead k=1->all
                if(k==0) outplotname = Form("h_lead_%s",input_hist.Data());
                if(k==1) outplotname = Form("h_all_%s",input_hist.Data());
                for (std::size_t i = 0; i < neta; ++i){ //neta
                    for (std::size_t j = 0; j < 1; ++j){ // ncent
                        
                        TString input_histname = Form("%s_%zu_%zu",outplotname.Data(),i,j);
                        // std::cout<<"input hist = "<<input_hist<<"\n";

                        std::vector<TH1D*> h;
                        std::vector<TString>hname;
                        std::vector<TString>sel = {"",Form("Cent. %d-%d%%",min_cent[j]/2,max_cent[j]/2),"p_{T}^{#gamma}>15","H/E<0.1","PID==22"}; // ,"NOT GEN MATCHED"

                        TH1D *hist_reference = (TH1D*)fout->Get(Form("Reference/%s",input_histname.Data()));
                        TH1D *hist_EB_EE_4  = (TH1D*)fout->Get(Form("EB_EE_4/%s",input_histname.Data()));
                        TH1D *hist_EB_EE_8  = (TH1D*)fout->Get(Form("EB_EE_8/%s",input_histname.Data()));
                        TH1D *hist_EB_EE_10 = (TH1D*)fout->Get(Form("EB_EE_10/%s",input_histname.Data()));

                        h.push_back((TH1D*)hist_reference->Clone());
                        h.push_back((TH1D*)hist_EB_EE_4->Clone());
                        h.push_back((TH1D*)hist_EB_EE_8->Clone());
                        h.push_back((TH1D*)hist_EB_EE_10->Clone());

                        hname.push_back("Reference");
                        if(i==0){
                            hname.push_back("ZS EB = 4");
                            hname.push_back("ZS EB = 8");
                            hname.push_back("ZS EB = 10");
                            hname.push_back(Form("%s_EB_cent_%d_%d",outplotname.Data(),min_cent[j]/2,max_cent[j]/2));
                            sel.push_back(Form("|#eta|<%1.2f",max_eta[i]));
                        }
                        else if(i==1){
                            hname.push_back("ZS EE = 4");
                            hname.push_back("ZS EE = 8");
                            hname.push_back("ZS EE = 10");
                            hname.push_back(Form("%s_EE_cent_%d_%d",outplotname.Data(),min_cent[j]/2,max_cent[j]/2));
                            sel.push_back(Form("%1.3f<|#eta|<%1.1f",min_eta[i],max_eta[i]));
                        }

                        fout->cd();
                        overlay_ZS(h,hname,"right_norm_width",sel);

                    } // End centrality loop
                }// End eta loop
            } // End lead vs all histogram
        } // End hist list loop

    }

    printf("\n");
    fout->Close();
}