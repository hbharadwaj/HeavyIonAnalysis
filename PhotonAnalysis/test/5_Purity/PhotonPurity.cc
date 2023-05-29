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

#include <vector>
#include <string>
#include <iostream>
#include "THStack.h"
#include "TSystem.h"

#include "Purity.h"

const TCut noiseCut = "";//"!((phoE3x3/phoE5x5 > 2./3.-0.03 && phoE3x3/phoE5x5 < 2./3.+0.03) && (phoE1x5/phoE5x5 > 1./3.-0.03 && phoE1x5/phoE5x5 < 1./3.+0.03) && (phoE2x5/phoE5x5 > 2./3.-0.03 && phoE2x5/phoE5x5 < 2./3.+0.03))";

const std::vector<int> min_cent = { 0,  60,   0,  0,  40};
const std::vector<int> max_cent = {60, 180, 180, 40, 180};
// const std::vector<int> min_cent = { 9,  69,   9,  9, 29,  69, 109};   // Centrality nominal
// const std::vector<int> max_cent = {69, 189, 189, 29, 69, 109, 189};
const std::vector<int> min_cent_mc = { 9,  69,   9,  9,  49};   // MC Centrality nominal
const std::vector<int> max_cent_mc = {69, 189, 189, 49, 189};
const std::size_t ncent = min_cent.size();

const std::vector<float> min_pt = {100};
const std::vector<float> max_pt = {9999};
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

  TLatex *lumi = new TLatex;
  lumi->SetNDC();
  lumi->SetTextSize(0.042);
  lumi->DrawLatex(0.75, 0.95, "PbPb #bf{5.02 TeV (2018)}");
  lumi->Draw();

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

int PhotonPurity(const TString skim_data, const TString skim_mc, const TString label) {
  bool VERBOSE = false;
  if(label.Contains("verbose")) VERBOSE = true;
  gStyle->SetOptStat(0);

  TString makedir = "mkdir -p Overlay/"+label+"/";
  const char *mkDIR = makedir.Data();
  gSystem->Exec(mkDIR);

  TH1::SetDefaultSumw2();

  // trigger is named differently in MC, hardcode for now :(
  std::string trigger_mc = "HLT_HIGEDPhoton40_v1"; // "HLT_HIPhoton40_HoverELoose_v1";
  std::string trigger = "HLT_HIGEDPhoton40_v1"; // "HLT_HIPhoton40_HoverELoose_v1";

  TFile* fskim_data = TFile::Open(skim_data);
  TTree* data_tree  = (TTree*)fskim_data->Get("jet_tree");
  TFile* fskim_mc = TFile::Open(skim_mc);
  TTree* mc_tree  = (TTree*)fskim_mc->Get("jet_tree");
  TFile* output = new TFile("Overlay/"+label+"/"+label+".root", "RECREATE");

  const float orig_purity_values[ncent][npt] = {0};//{{0.0},{0.0},{0.0},{0.786},{0.863},{0.908},{0.890}};

/*
  const float orig_purity_values[ncent][npt] = {{0},
  {0},
  {0},
  {0,0,0.779,0.736,0.703,0,0.714,0.708},
  {0,0,0.800,0.797,0.792,0,0.800,0.818},
  {0,0,0.823,0.824,0.840,0,0.861,0.890},
  {0,0,0.821,0.849,0.869,0,0.862,0.827}};
*/

  float purity_values[ncent][npt] = {0};

  const TCut eta_cut = "(abs(phoEta) < 1.442) && phoSigmaIEtaIEta_2012>0.002 && !(phoEta<-1.39 && phoPhi<-0.9 && phoPhi>-1.6)";
  const TCut ele_cut = "!eleRej";

  const TCut candidate_isolation =  "(SumCalIso) < 2.099277 && phoHoverE<0.119947"; // "(SumCalIso) < -0.479 && phoHoverE<0.0233";//
  const TCut sideband_isolation =  "((SumCalIso)>10) && ((SumCalIso)<20) && phoHoverE<0.119947"; // "((SumCalIso)>10) && ((SumCalIso)<20) && phoHoverE<0.0233";//
  const TCut signal_selection = "(pho_genMatchedIndex!= -1) && mcCalIsoDR04<5 && mcPID == 22 && (abs(mcMomPID)<=22 || mcMomPID == -999)";

  const std::string weight_string = "weight*weight_pthat*weight_cent";//*weight_cent";
  TCut weight_label = weight_string.c_str();

  for (std::size_t i = 0; i < ncent; ++i) {
    for (std::size_t j = 0; j < npt; ++j) {
      TString pt_cut = Form("(phoEtCorrected >= %f) && (phoEtCorrected < %f)", min_pt[j], max_pt[j]);
      TString cent_cut = Form("(hiBin >= %i) && (hiBin < %i)", min_cent[i], max_cent[i]);
      TString cent_cut_MC = Form("(hiBin >= %i) && (hiBin < %i)", min_cent_mc[i], max_cent_mc[i]);

      TCut trigger_selection = Form("%s", trigger.c_str());
      TCut trigger_selection_mc = Form("%s", trigger_mc.c_str());

      TCut candidate_cut = candidate_isolation && eta_cut && ele_cut && pt_cut && cent_cut && noiseCut && trigger_selection;
      TCut sideband_cut = sideband_isolation && eta_cut && ele_cut && pt_cut && cent_cut && noiseCut && trigger_selection;
      TCut signal_cut = signal_selection && eta_cut && ele_cut && pt_cut && cent_cut_MC && trigger_selection_mc;
      signal_cut = signal_cut * weight_label;

      const int nbins = 80;
      const int divisions = 1;
      float sig_shift = 0;//config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySignalShift];
      float bkg_shift = 0;//config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityBackgroundShift];

      TH1D* hdata = new TH1D(Form("hdata_%zu_%zu", i, j), "", nbins, 0, 0.025);
      data_tree->Project(hdata->GetName(), "phoSigmaIEtaIEta_2012", candidate_cut, "");
      if(VERBOSE){
      std::cout << "data count: " << hdata->GetEntries() << std::endl;
      }

      TH1D* hbkg = new TH1D(Form("hbkg_%zu_%zu", i, j), "", nbins * divisions, 0, 0.025);
      data_tree->Project(hbkg->GetName(), Form("phoSigmaIEtaIEta_2012 + %f", bkg_shift), sideband_cut, "");
      TH1D* hsig = new TH1D(Form("hsig_%zu_%zu", i, j), "", nbins * divisions, 0, 0.025);
      mc_tree->Project(hsig->GetName(), Form("phoSigmaIEtaIEta_2012 + %f", sig_shift), signal_cut, "");
      
      if(VERBOSE){
        std::cout << "bkg count: " << hbkg->GetEntries() << std::endl;
        std::cout << "sig count: " << hsig->GetEntries() << std::endl;
      }

      float range_low =  0.005;
      float range_high = 0.018;
      float sieie_cut =  0.010392; // 0.01;//

      /* fit using binned templates */
      Templates* templates = new Templates(hdata, hsig, hbkg, divisions);

      Purity* purity = new Purity();
      purity->fit(templates, hdata, range_low, range_high, sieie_cut);

      if(VERBOSE){
        std::cout << "nsig: " << purity->nsig << std::endl;
        std::cout << "purity: " << purity->purity << std::endl;
        std::cout << "chisq: " << purity->chisq << std::endl;
        std::cout << "ndf: " << purity->ndf << std::endl;
        std::cout << "p-val: " << TMath::Prob(purity->chisq, nbins) << std::endl;
      }

      purity->write();

      purity_values[i][j] = purity->purity;
      // if(VERBOSE)
        std::cout<<"i = "<<i<<"   j = "<<j<<"   Purity = "<<purity_values[i][j]<<std::endl;
    }
  }

  output->Close();
  /*

  printf("|Cent/$p_{T}$| ");

  for (std::size_t j=0; j<npt; ++j){
    // if(j==0||j==1||j==5) continue;
    printf(" %.0f-%.0f| ",min_pt[j],max_pt[j]);
  }
  printf("\n");
  */

  int count_Accept = 0;
  int count_Greater = 0;
  
  for (int i=ncent-1; i>=0; --i){
    // if(i==0||i==1||i==2) continue;
      printf("| %.1f-%.1f | ",min_cent[i]/2.0,max_cent[i]/2.0);
      for (std::size_t j=0; j<npt; ++j){      
        // if(j==0||j==1||j==5) continue;
        printf(" %.3f (%.3f) | ", purity_values[i][j],0.0);
        // std::cout<<"Print value\n";
        TemplatePlot(label,i,j,purity_values[i][j],0.0);
        // if(fabs(purity_values[i][j]-orig_purity_values[i][j])<0.04)count_Accept++;
        // if(purity_values[i][j]>orig_purity_values[i][j])count_Greater++;
      }
    printf("\n");
  }
  printf("\n Number of cases with Difference <0.04 = %i\n",count_Accept);
  printf("\n Number of cases with Greater Purity   = %i\n",count_Greater);
    

  return 0;
}

void TemplatePlot(TString label,std::size_t i, std::size_t j, float purity, float orig_purity){

    TFile *input_file = TFile::Open("Overlay/"+label+"/"+label+".root","UPDATE");

    THStack hs("hs", "hs");
    TCanvas c;
    // std::cout<<"Open File\n";
    

    TH1F* h_data      = (TH1F *)input_file->Get(Form("hdata_%zu_%zu_template_fit",i,j)); 
    TH1F* h_sig_fit   = (TH1F *)input_file->Get(Form("hdata_%zu_%zu_template_fit_sig",i,j)); 
    TH1F* h_bkg_fit   = (TH1F *)input_file->Get(Form("hdata_%zu_%zu_template_fit_bkg",i,j)); 
    TH1F* h_total_fit = (TH1F *)input_file->Get(Form("hdata_%zu_%zu_template_fit_total",i,j)); 
    h_data->SetTitle(";#sigma_{#eta#eta};Events");
    h_sig_fit->SetTitle(";#sigma_{#eta#eta};Events");
    h_bkg_fit->SetTitle(";#sigma_{#eta#eta};Events");
    h_total_fit->SetTitle(";#sigma_{#eta#eta};Events");

    // h_data->Rebin();
    // h_sig_fit->Rebin();
    // h_bkg_fit->Rebin();
    // h_total_fit->Rebin();

    h_data->SetLineColor(1);
    h_data->SetMarkerColor(1);
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerSize(.7);      

    h_total_fit->SetLineColor(8);
    h_total_fit->SetMarkerColor(8);
    h_total_fit->SetMarkerStyle(23);
    h_total_fit->SetMarkerSize(.7);   

    h_bkg_fit->SetLineColor(4);
    h_bkg_fit->SetFillColorAlpha(4,0.35);
    h_bkg_fit->SetFillStyle(3345);
    h_bkg_fit->SetMarkerColor(4);
    
    hs.Add(h_bkg_fit);

    h_sig_fit->SetLineColor(2);
    h_sig_fit->SetFillColorAlpha(2,0.35);
    h_sig_fit->SetFillStyle(3305);
    h_sig_fit->SetMarkerColor(2);

    hs.Add(h_sig_fit); 
    // std::cout<<"Add to stack\n";

    h_data->Draw("E");
    h_total_fit->Draw("SameE");
    hs.Draw("SamehistE");
    // std::cout<<"Draw plots\n";

    hs.GetXaxis()->SetTitle("#sigma_{#eta#eta}");
    hs.GetYaxis()->SetTitle("Events");

    TLegend* leg = new TLegend(0.55, 0.62, 0.75, 0.92,"","brNDC");
    leg->SetFillStyle(0);
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->SetTextSize(0.042);
    leg->AddEntry(h_data, "Data", "lep");
    leg->AddEntry(h_total_fit, "Total Fit", "lep");
    leg->AddEntry(h_sig_fit, "Signal Fit", "lep");
    leg->AddEntry(h_bkg_fit, "Bkg (Sideband) Fit", "lep");
    leg->SetTextFont(42);
    leg->Draw();
    mySmallText(0.55,0.5,1,Form("Cent. %0.0f - %0.0f%%", min_cent[i]/2.0, max_cent[i]/2.0));
    mySmallText(0.55,0.4,1,Form("%.0f < E_{T}^{#gamma} <%.0f", min_pt[j], max_pt[j]));
    mySmallText(0.55,0.3,1,Form("Purity : %.3f (%.3f)", purity, orig_purity)); 
    drawHeader();
    // std::cout<<"Legend draw\n";

    c.SaveAs(Form("Overlay/"+label+"/Template_fit_%zu_%zu.jpeg",i,j));   
    c.Write(Form("Template_fit_%zu_%zu",i,j),TObject::kOverwrite);   

    input_file->Close();

}

int main(int argc, char* argv[]) {
  
  if (argc == 4){
    gROOT->SetBatch();
    SetPlotStyle();
    gErrorIgnoreLevel = kWarning;
    return PhotonPurity(argv[1], argv[2], argv[3]);

  }

  return 1;
}
