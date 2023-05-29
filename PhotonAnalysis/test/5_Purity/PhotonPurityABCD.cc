// photonPurity.C
// Author: Alex Barbieri
// Cobbled together from code written by Yongsun Kim

// Calculates and plots the photon purity using a sideband estimation
// of the background and a MC calculation of the signal. This info is
// used to do a template fit in the sigmaIetaIeta variable.

#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TString.h"
#include "TLatex.h"
#include "TROOT.h"          // needed for gROOT
#include <TError.h>         // needed for gErrorIgnoreLevel

#include <vector>
#include <string>
#include <iostream>
#include "THStack.h"
#include "TSystem.h"

const TCut noiseCut = "";//"!((phoE3x3/phoE5x5 > 2./3.-0.03 && phoE3x3/phoE5x5 < 2./3.+0.03) && (phoE1x5/phoE5x5 > 1./3.-0.03 && phoE1x5/phoE5x5 < 1./3.+0.03) && (phoE2x5/phoE5x5 > 2./3.-0.03 && phoE2x5/phoE5x5 < 2./3.+0.03))";

const std::vector<int> min_cent = { 0,  60,   0,  0,  40};
const std::vector<int> max_cent = {60, 180, 180, 40, 180};
// const std::vector<int> min_cent = { 9,  69,   9,  9, 29,  69, 109};   // Centrality nominal
// const std::vector<int> max_cent = {69, 189, 189, 29, 69, 109, 189};
// const std::vector<int> min_cent_mc = { 9,  69,   9,  9,  49};   // MC Centrality nominal
// const std::vector<int> max_cent_mc = {69, 189, 189, 49, 189};
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
  lumi->DrawLatex(0.75, 0.95, "#bf{5.02 TeV (2018)}");
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

int PhotonPurity(const TString skim_data, const TString label) {
  bool VERBOSE = false;
  if(label.Contains("verbose")) VERBOSE = true;
  gStyle->SetOptStat(0);

  TString makedir = "mkdir -p OverlayABCD/"+label+"/";
  const char *mkDIR = makedir.Data();
  gSystem->Exec(mkDIR);

  TH1::SetDefaultSumw2();

  // trigger is named differently in MC, hardcode for now :(
  std::string trigger_mc = "HLT_HIGEDPhoton40_v1";// "HLT_HIPhoton40_HoverELoose_v1";//
  std::string trigger = "HLT_HIGEDPhoton40_v1";// "HLT_HIPhoton40_HoverELoose_v1";//

  TFile* fskim_data = TFile::Open(skim_data);
  TTree* data_tree  = (TTree*)fskim_data->Get("jet_tree");
  TFile* output = new TFile("OverlayABCD/"+label+"/"+label+".root", "RECREATE");

  float purity_values[ncent][npt] = {0};

  const float orig_purity_values[ncent][npt] = {0};//{{0.819},{0.791},{0.899},{0.737},{0.838},{0.903},{0.895}};// {{0.938}};

  const TCut eta_cut = "(abs(phoEta) < 1.44) && phoSigmaIEtaIEta_2012>0.002 && !(phoEta<-1.39 && phoPhi<-0.9 && phoPhi>-1.6)";
  const TCut ele_cut = "!eleRej && phoHoverE<0.119947";

  const TCut reg_A = "phoSigmaIEtaIEta_2012<=0.010392 && (SumCalIso) <= 2.099277";
  const TCut reg_B = "phoSigmaIEtaIEta_2012<=0.010392 && 10<(SumCalIso)<20";
  const TCut reg_C = "phoSigmaIEtaIEta_2012 >0.010392  && (SumCalIso) <= 2.099277";
  const TCut reg_D = "phoSigmaIEtaIEta_2012 >0.010392  &&  10<(SumCalIso)<20";

  const TCut signal_selection = "";//"(pho_genMatchedIndex!= -1) && mcCalIsoDR04<5 && mcPID == 22 && (abs(mcMomPID)<=22 || mcMomPID == -999)";

  const std::string weight_string = "";//"weight*weight_pthat*weight_cent";
  TCut weight_label = weight_string.c_str();

  for (std::size_t i = 0; i < ncent; ++i) {
    for (std::size_t j = 0; j < npt; ++j) {
      TString pt_cut = Form("(phoEtCorrected >= %f) && (phoEtCorrected < %f)", min_pt[j], max_pt[j]);
      TString cent_cut = Form("(hiBin >= %i) && (hiBin < %i)", min_cent[i], max_cent[i]);

      TCut trigger_selection = Form("%s", trigger.c_str());
      TCut trigger_selection_mc = Form("%s", trigger_mc.c_str());

      TCut MC_selection = eta_cut && ele_cut && signal_selection && pt_cut && noiseCut && trigger_selection && cent_cut;
      MC_selection = MC_selection * weight_label;

      // const int nbins = 200;
      // const int divisions = 1;
      // float sig_shift = 0;//config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySignalShift];
      // float bkg_shift = 0;//config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityBackgroundShift];
      const Double_t Sumiso_edges[5]={-100,2.099277,10,20,500};
      const Double_t SIEIE_edges[3]={0,0.010392,0.025};

      TH2D* h2_Iso_SIEIE = new TH2D(Form("h2_Iso_SIEIE_%zu_%zu", i, j), "", 4,Sumiso_edges,2,SIEIE_edges);
      data_tree->Project(h2_Iso_SIEIE->GetName(),"phoSigmaIEtaIEta_2012:SumCalIso",MC_selection, "");

      float count_A = h2_Iso_SIEIE->GetBinContent(1,1);
      float count_B = h2_Iso_SIEIE->GetBinContent(3,1);
      float count_C = h2_Iso_SIEIE->GetBinContent(1,2);
      float count_D = h2_Iso_SIEIE->GetBinContent(3,2);

      purity_values[i][j] = 1 - ( (count_C/count_A)/(count_D/count_B) );
      std::cout<<"i = "<<i<<"   j = "<<j<<"   Purity = "<<purity_values[i][j]<<std::endl;

      h2_Iso_SIEIE->Write();
      TCanvas c;
      gStyle->SetOptLogx(1);
      // h2_Iso_SIEIE->Draw("text");
      // c.SaveAs(Form("Overlay/%s/text_h2_Iso_SIEIE_%zu_%zu.png",label.Data(), i, j));
      // h2_Iso_SIEIE->Draw("colz");
      // c.SaveAs(Form("Overlay/%s/col_h2_Iso_SIEIE_%zu_%zu.png",label.Data(), i, j));
      h2_Iso_SIEIE->Draw("textcolz");
      c.SaveAs(Form("OverlayABCD/%s/textcol_h2_Iso_SIEIE_%zu_%zu.png",label.Data(), i, j));
    }
  }

  output->Close(); 

  printf("|Cent/$p_{T}$| ");

  for (std::size_t j=0; j<npt; ++j){
    // if(j==0||j==1||j==5) continue;
    printf(" %.0f-%.0f| ",min_pt[j],max_pt[j]);
  }
  printf("\n");

  int count_Accept = 0;
  int count_Greater = 0;
  
  for (int i=ncent-1; i>=0; --i){
    // if(i==0||i==1||i==2) continue;
      printf("| %.1f-%.1f | ",min_cent[i]/2.0,max_cent[i]/2.0);
      for (std::size_t j=0; j<npt; ++j){      
        // if(j==0||j==1||j==5) continue;
        printf(" %.3f (%.3f) | ", purity_values[i][j],orig_purity_values[i][j]);
        // TemplatePlot(label,i,j,purity_values[i][j],orig_purity_values[i][j]);
        if(fabs(purity_values[i][j]-orig_purity_values[i][j])<0.04)count_Accept++;
        if(purity_values[i][j]>orig_purity_values[i][j])count_Greater++;
      }
    printf("\n");
  }   

  return 0;
}
/*
void TemplatePlot(TString label,std::size_t i, std::size_t j, float purity, float orig_purity){

    TFile *input_file = TFile::Open("/home/llr/cms/bharikri/Projects/Template_fit/Overlay/"+label+"/"+label+".root");

    THStack hs("hs", "hs");
    TCanvas c;

    TH1F* h_data      = (TH1F *)input_file->Get(Form("hdata_%zu_%zu_template_fit",i,j)); 
    TH1F* h_sig_fit   = (TH1F *)input_file->Get(Form("hdata_%zu_%zu_template_fit_sig",i,j)); 
    TH1F* h_bkg_fit   = (TH1F *)input_file->Get(Form("hdata_%zu_%zu_template_fit_bkg",i,j)); 
    TH1F* h_total_fit = (TH1F *)input_file->Get(Form("hdata_%zu_%zu_template_fit_total",i,j)); 
    h_data->SetTitle(";#sigma_{#eta#eta};Events");
    h_sig_fit->SetTitle(";#sigma_{#eta#eta};Events");
    h_bkg_fit->SetTitle(";#sigma_{#eta#eta};Events");
    h_total_fit->SetTitle(";#sigma_{#eta#eta};Events");

    h_data->Rebin();
    h_sig_fit->Rebin();
    h_bkg_fit->Rebin();
    h_total_fit->Rebin();

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

    h_data->Draw("E");
    h_total_fit->Draw("SameE");
    hs.Draw("SamehistE");

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
    mySmallText(0.55,0.5,1,Form("Cent. %i - %i%%", min_cent[i]/2, max_cent[i]/2));
    mySmallText(0.55,0.4,1,Form("%.0f < E_{T}^{#gamma} <%.0f", min_pt[j], max_pt[j]));
    mySmallText(0.55,0.3,1,Form("Purity : %.3f (%.3f)", purity, orig_purity)); 
    drawHeader();

    c.SaveAs(Form("Overlay/"+label+"/Template_fit_%zu_%zu.jpeg",i,j));   

    input_file->Close();

}
*/

int main(int argc, char* argv[]) {
  
  if (argc == 3){
    gROOT->SetBatch();
    SetPlotStyle();
    gErrorIgnoreLevel = kWarning;
    return PhotonPurity(argv[1], argv[2]);

  }

  return 1;
}
