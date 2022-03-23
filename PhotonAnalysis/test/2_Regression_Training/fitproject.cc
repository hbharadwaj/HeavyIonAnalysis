// photonPurity.C
// Author: Alex Barbieri
// Cobbled together from code written by Yongsun Kim

// Calculates and plots the photon purity using a sideband estimation
// of the background and a MC calculation of the signal. This info is
// used to do a template fit in the sigmaIetaIeta variable.

#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TString.h"
#include "TLatex.h"

#include "TH1.h"
#include "TNtuple.h"
#include "TCut.h"
#include "TF1.h"

#include <string>

#include <vector>
#include <string>
#include <iostream>
#include "THStack.h"
#include "TSystem.h"

const TCut noiseCut = "";//"!((phoE3x3/phoE5x5 > 2./3.-0.03 && phoE3x3/phoE5x5 < 2./3.+0.03) && (phoE1x5/phoE5x5 > 1./3.-0.03 && phoE1x5/phoE5x5 < 1./3.+0.03) && (phoE2x5/phoE5x5 > 2./3.-0.03 && phoE2x5/phoE5x5 < 2./3.+0.03))";

const std::vector<int> min_cent = {0, 0, 60, 0, 20, 60, 100};
const std::vector<int> max_cent = {180, 60, 180, 20, 60, 100, 180};
const std::size_t ncent = min_cent.size();

const std::vector<float> min_pt = {40, 60, 40, 50, 60, 80, 80, 100};
const std::vector<float> max_pt = {9999, 9999, 50, 60, 80, 9999, 100, 9999};
const std::size_t npt = min_pt.size();

void TemplatePlot(TString ,std::size_t , std::size_t, float, float );

void mySmallText(Double_t x,Double_t y,Color_t color,const char *text) {
  Double_t tsize=0.045;
  TLatex l;
  l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextColor(color);
  l.DrawLatex(x,y,text);
}


void drawHeader(void) {

  TLatex *prelim = new TLatex;
  prelim->SetNDC();
  prelim->SetTextSize(0.042);
  prelim->DrawLatex(0.12, 0.95, "CMS #it{#bf{Internal Simulation}}");
  prelim->Draw();
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
   gStyle->SetPadTopMargin(0.1);
   gStyle->SetPadRightMargin(0.05);
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

   gStyle->SetOptLogy(1);
}

int PhotonEnergyResolution(const TString skim_mc, const TString label) {
  bool VERBOSE = false;
  if(label.Contains("verbose")) VERBOSE = true;
  gStyle->SetOptStat(0);

  TString makedir = "mkdir -p Overlay_"+label+"/";
  const char *mkDIR = makedir.Data();
  gSystem->Exec(mkDIR);

  TH1::SetDefaultSumw2();

  // trigger is named differently in MC, hardcode for now :(
  std::string trigger_mc = "";//"L1_SingleEG21_BptxAND && HLT_HIGEDPhoton40_v1";

  TFile* fskim_mc = TFile::Open(skim_mc);
  TTree* mc_tree  = (TTree*)fskim_mc->Get("pho_tree");

  float res_values[ncent][npt] = {0};

  const TCut eta_cut = "(abs(phoEta) < 1.44) && phoSigmaIEtaIEta_2012>0.002 && !(phoEta<-1.39 && phoPhi<-0.9 && phoPhi>-1.6)";
  // const TCut ele_cut = "!(elePt>=10 && eleEoverP<=100 && fabs(eleEta-phoEta)<0.02 && fabs(elePhi-phoPhi))";

  const TCut signal_selection = "(pho_genMatchedIndex!= -1) && mcCalIsoDR04<5 && mcPID == 22 && (abs(mcMomPID)<=22 || mcMomPID == -999)";

  const std::string weight_string = "";
  TCut weight_label = weight_string.c_str();

  for (std::size_t i = 0; i < ncent; ++i) {
    for (std::size_t j = 0; j < npt; ++j) {
      TString pt_cut = Form("(mcEt >= %f) && (mcEt < %f)", min_pt[j], max_pt[j]);
      TString cent_cut = Form("(hiBin >= %i) && (hiBin < %i)", min_cent[i], max_cent[i]);

      TCut trigger_selection_mc = Form("%s", trigger_mc.c_str());

      TCut signal_cut = signal_selection && eta_cut && pt_cut && cent_cut && trigger_selection_mc;
      signal_cut = signal_cut * weight_label;

      const int nbins = 100;
      const int divisions = 1;
      float sig_shift = 0;//config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySignalShift];
      float bkg_shift = 0;//config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityBackgroundShift];

      TH1D* hsig_raw = new TH1D(Form("hsig_raw_%zu_%zu", i, j), "", nbins * divisions, 0.8, 1.15);
      mc_tree->Project(hsig_raw->GetName(), Form("(phoSCRawE/TMath::CosH(phoSCEta))/mcEt"), signal_cut, "");

      TH1D* hsig_corrected = new TH1D(Form("hsig_corrected_%zu_%zu", i, j), "", nbins * divisions, 0.8, 1.15);
      mc_tree->Project(hsig_corrected->GetName(), Form("(phoEtCorrected)/mcEt"), signal_cut, "");
      
      if(VERBOSE){
        std::cout << "sig count: " << hsig_raw->GetEntries() << std::endl;
      }

      THStack hs("hs", "hs");
      TCanvas c;

      hsig_raw->Scale(1.0/hsig_raw->Integral(0, hsig_raw->GetNbinsX() + 2));
      hsig_raw->GetYaxis()->SetRangeUser(0.00001,1);
      hsig_raw->SetLineColor(1);
      hsig_raw->SetMarkerColor(1);
      hsig_raw->SetMarkerStyle(8);

      hsig_corrected->Scale(1.0/hsig_corrected->Integral(0, hsig_corrected->GetNbinsX() + 2));
      hsig_corrected->GetYaxis()->SetRangeUser(0.00001,1);
      hsig_corrected->SetLineColor(2);
      hsig_corrected->SetMarkerColor(2);
      hsig_corrected->SetMarkerStyle(24);

      hs.Add(hsig_raw);
      hs.Add(hsig_corrected,"sames");

      hs.Draw("nostack");
      hs.GetXaxis()->SetTitle("(Reco E_{T})/True E_{T}");
      hs.GetYaxis()->SetTitle("Normalized Events");
      hs.GetXaxis()->SetRangeUser(0.8,1.15);
      hs.GetYaxis()->SetRangeUser(0.00001,hsig_raw->GetMaximum()*1.01);

      TLegend *l;
      char sample[500];
      l = new TLegend(0.25, 0.70, 0.35, 0.85,"","brNDC");
      l->SetFillColor(0);
      l->SetFillStyle(0);
      l->SetLineColor(0);
      l->SetTextSize(0.03);
      
      l->AddEntry(hsig_raw, Form("Uncorrected E_{T} #sigma = %.3f",hsig_raw->GetRMS()), "lep");
      l->AddEntry(hsig_corrected, Form("Corrected E_{T} #sigma = %.3f",hsig_corrected->GetRMS()), "lep");
      l->Draw();
      drawHeader();

      TLatex *lumi = new TLatex;
      lumi->SetNDC();
      lumi->SetTextSize(0.042);
      lumi->DrawLatex(0.75, 0.95, Form("Cent. %i - %i%%", min_cent[i]/2, max_cent[i]/2));
      lumi->Draw();

      TLatex *reg = new TLatex;
      reg->SetNDC();
      reg->SetTextSize(0.042);
      reg->DrawLatex(0.55, 0.95, Form("%.0f < E_{T}^{#gamma} <%.0f", min_pt[j], max_pt[j]));
      reg->Draw();
      gPad->Update();

      c.SaveAs(Form("Overlay_"+label+"/fit_%zu_%zu.jpeg",i,j));   
    }
  }

  // output->Close();


  return 0;
}


int PhotonEnergyResolution(const TString skim_mc2, const TString label2, const TString skim_mc, const TString label) {
  bool VERBOSE = false;
  if(label.Contains("verbose")) VERBOSE = true;
  gStyle->SetOptStat(0);

  TString makedir = "mkdir -p Overlay_"+label+"/";
  const char *mkDIR = makedir.Data();
  gSystem->Exec(mkDIR);

  TH1::SetDefaultSumw2();

  // trigger is named differently in MC, hardcode for now :(
  std::string trigger_mc = "";//"L1_SingleEG21_BptxAND && HLT_HIGEDPhoton40_v1";

  TFile* fskim_mc = TFile::Open(skim_mc);
  TTree* mc_tree  = (TTree*)fskim_mc->Get("pho_tree");

  TFile* fskim_mc2 = TFile::Open(skim_mc2);
  TTree* mc_tree2  = (TTree*)fskim_mc2->Get("pho_tree");

  float res_values[ncent][npt] = {0};

  const TCut eta_cut = "(abs(phoEta) < 1.44) && phoSigmaIEtaIEta_2012>0.002 && !(phoEta<-1.39 && phoPhi<-0.9 && phoPhi>-1.6)";
  // const TCut ele_cut = "!(elePt>=10 && eleEoverP<=100 && fabs(eleEta-phoEta)<0.02 && fabs(elePhi-phoPhi))";

  const TCut signal_selection = "(pho_genMatchedIndex!= -1) && mcCalIsoDR04<5 && mcPID == 22 && (abs(mcMomPID)<=22 || mcMomPID == -999)";

  const std::string weight_string = "";
  TCut weight_label = weight_string.c_str();

  for (std::size_t i = 0; i < ncent; ++i) {
    for (std::size_t j = 0; j < npt; ++j) {
      TString pt_cut = Form("(mcEt >= %f) && (mcEt < %f)", min_pt[j], max_pt[j]);
      TString cent_cut = Form("(hiBin >= %i) && (hiBin < %i)", min_cent[i], max_cent[i]);

      TCut trigger_selection_mc = Form("%s", trigger_mc.c_str());

      TCut signal_cut = signal_selection && eta_cut && pt_cut && cent_cut && trigger_selection_mc;
      signal_cut = signal_cut * weight_label;

      const int nbins = 100;
      const int divisions = 1;
      float sig_shift = 0;//config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySignalShift];
      float bkg_shift = 0;//config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityBackgroundShift];

      TH1D* hsig_raw = new TH1D(Form("hsig_raw_%zu_%zu", i, j), "", nbins * divisions, 0.8, 1.15);
      mc_tree->Project(hsig_raw->GetName(), Form("(phoSCRawE/TMath::CosH(phoSCEta))/mcEt"), signal_cut, "");

      TH1D* hsig_corrected = new TH1D(Form("hsig_corrected_%zu_%zu", i, j), "", nbins * divisions, 0.8, 1.15);
      mc_tree->Project(hsig_corrected->GetName(), Form("(phoEtCorrected)/mcEt"), signal_cut, "");

      TH1D* hsig2_corrected = new TH1D(Form("hsig2_corrected_%zu_%zu", i, j), "", nbins * divisions, 0.8, 1.15);
      mc_tree2->Project(hsig2_corrected->GetName(), Form("(phoEtCorrected)/mcEt"), signal_cut, "");
      
      if(VERBOSE){
        std::cout << "sig count: " << hsig_raw->GetEntries() << std::endl;
      }

      THStack hs("hs", "hs");
      TCanvas c;

      hsig_raw->Scale(1.0/hsig_raw->Integral(0, hsig_raw->GetNbinsX() + 2));
      hsig_raw->GetYaxis()->SetRangeUser(0.00001,1);
      hsig_raw->SetLineColor(1);
      hsig_raw->SetMarkerColor(1);
      hsig_raw->SetMarkerStyle(8);

      hsig_corrected->Scale(1.0/hsig_corrected->Integral(0, hsig_corrected->GetNbinsX() + 2));
      hsig_corrected->GetYaxis()->SetRangeUser(0.00001,1);
      hsig_corrected->SetLineColor(2);
      hsig_corrected->SetMarkerColor(2);
      hsig_corrected->SetMarkerStyle(24);

      hsig2_corrected->Scale(1.0/hsig2_corrected->Integral(0, hsig2_corrected->GetNbinsX() + 2));
      hsig2_corrected->GetYaxis()->SetRangeUser(0.00001,1);
      hsig2_corrected->SetLineColor(4);
      hsig2_corrected->SetMarkerColor(4);
      hsig2_corrected->SetMarkerStyle(22);

      hs.Add(hsig_raw);
      hs.Add(hsig_corrected,"sames");
      hs.Add(hsig2_corrected,"sames");

      hs.Draw("nostack");
      hs.GetXaxis()->SetTitle("(Reco E_{T})/True E_{T}");
      hs.GetYaxis()->SetTitle("Normalized Events");
      hs.GetXaxis()->SetRangeUser(0.8,1.15);
      hs.GetYaxis()->SetRangeUser(0.00001,hsig_raw->GetMaximum()*1.01);

      TLegend *l;
      char sample[500];
      l = new TLegend(0.25, 0.70, 0.35, 0.85,"","brNDC");
      l->SetFillColor(0);
      l->SetFillStyle(0);
      l->SetLineColor(0);
      l->SetTextSize(0.03);
      
      l->AddEntry(hsig_raw, Form("Uncorrected E_{T} #sigma = %.3f",hsig_raw->GetRMS()), "lep");
      l->AddEntry(hsig_corrected, Form("%s #sigma = %.3f",label.Data(),hsig_corrected->GetRMS()), "lep");
      l->AddEntry(hsig2_corrected, Form("%s #sigma = %.3f",label2.Data(),hsig_corrected->GetRMS()), "lep");
      l->Draw();
      drawHeader();

      TLatex *lumi = new TLatex;
      lumi->SetNDC();
      lumi->SetTextSize(0.042);
      lumi->DrawLatex(0.75, 0.95, Form("Cent. %i - %i%%", min_cent[i]/2, max_cent[i]/2));
      lumi->Draw();

      TLatex *reg = new TLatex;
      reg->SetNDC();
      reg->SetTextSize(0.042);
      reg->DrawLatex(0.55, 0.95, Form("%.0f < E_{T}^{#gamma} <%.0f", min_pt[j], max_pt[j]));
      reg->Draw();
      gPad->Update();

      c.SaveAs(Form("/home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/PhotonAnalysis/test/2_Regression_Training/Overlay_"+label+"/fit_%zu_%zu.jpeg",i,j));   
    } 
  }

  // output->Close();


  return 0;
}


int main(int argc, char* argv[]) {

  gROOT->SetBatch();
  SetPlotStyle();
  gErrorIgnoreLevel = kWarning;
  
  if (argc == 3){
    return PhotonEnergyResolution(argv[1], argv[2]);
  }
  else if (argc == 5){
    return PhotonEnergyResolution(argv[1], argv[2], argv[3], argv[4]);
  }
  else{
    printf("Run with \n ./fitproject <path> <label>");
  }

  return 1;
}
