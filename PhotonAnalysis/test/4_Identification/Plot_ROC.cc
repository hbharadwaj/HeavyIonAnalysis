#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TColor.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include "TMVA/TMVAMultiClassGui.h"
#include "TMVA/MethodCuts.h"
#include "TMVA/Reader.h"

#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void mySmallText(Double_t x,Double_t y,Color_t color,const char *text); 
void SetPlotStyle();
void drawHeader();
TCanvas c;
TLegend *l;
int col_i = 1;

void Plot_ROC(TString path, TString name){

    TFile *output_file;
    output_file = new TFile(path);

    TH1F* TestingROC = (TH1F*)output_file->Get("dataset/Method_Cuts/Cuts/MVA_Cuts_rejBvsS");
    // TestingROC->Rebin();
    TestingROC->SetName(name);
    TestingROC->SetTitle(name+";Signal Efficiency; Background Rejection");
    // TestingROC->SetLineColor(gStyle->GetColorPalette(col_i));
    // TestingROC->SetMarkerColor(gStyle->GetColorPalette(col_i));
    TestingROC->SetMarkerStyle(24);
    c.cd();

    TestingROC->GetYaxis()->SetRangeUser(0.0,1.01);
    TestingROC->GetXaxis()->SetName("Signal Efficiency");
    TestingROC->GetYaxis()->SetName("Background Rejection");
    TestingROC->Draw("SAMEHIST PLC PMC");
    l->AddEntry(TestingROC, name, "lep");
    // gPad->Update();

    col_i++;
}


void mySmallText(Double_t x,Double_t y,Color_t color,const char *text) {
  Double_t tsize=0.045;
  TLatex lat;
  lat.SetTextSize(tsize); 
  lat.SetNDC();
  lat.SetTextColor(color);
  lat.DrawLatex(x,y,text);
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

   gStyle->SetPalette(kRainBow);

   // set the paper & margin sizes
   gStyle->SetPaperSize(26, 26);
   gPad->SetTopMargin(0.1);
   gPad->SetRightMargin(0.05);
   gPad->SetBottomMargin(0.15);
   gPad->SetLeftMargin(0.15);

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
   gStyle->SetHistLineWidth(4.);
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


   // ADD GRIDS
/*
  gStyle->SetPadGridX(true);
  gStyle->SetPadGridY(true);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);*/
}


int main(int argc, char* argv[]){

  //./Plot_ROC Updated_Kaya.root "Kaya's ROC" Calorimeter_Isolation/bharad_3/EB_TMVA.root "PF Iso R3" Calorimeter_Isolation/bharad_4/EB_TMVA.root "Detector Iso R3" Calorimeter_Isolation/kaya_1/EB_TMVA.root "Reproduced Kaya's Result" Calorimeter_Isolation/bharad_WP90/EB_TMVA.root "Loose ROC"

    gROOT->SetBatch();
    SetPlotStyle();
    gErrorIgnoreLevel = kWarning;

    l = new TLegend(0.3, 0.3, 0.45, 0.5,"","brNDC");
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->SetTextSize(0.03);
    c.SetGrid();
    c.cd();

    for(int i=1; i<argc;i+=2){
        Plot_ROC(argv[i],argv[i+1]);
    }
    l->Draw();
    drawHeader();
    c.SaveAs("ROC_overlay.png");
    
    return 0;
}
