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
bool VERBOSE = false;
// const std::vector<int> min_cent = {0, 0, 60, 0, 20, 60, 100};
// const std::vector<int> max_cent = {180, 60, 180, 20, 60, 100, 180};
const std::vector<int> min_cent_val = { 0,  60,   0,  0,  40};   
const std::vector<int> max_cent_val = {60, 180, 180, 40, 180};

const std::vector<int> min_cent = { 9,  69,   9,  9,  49};   // Centrality nominal
const std::vector<int> max_cent = {69, 189, 189, 49, 189};
const std::size_t ncent = 1;//min_cent.size();

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

int Purity_Prior(const TString skim_data, const TString skim_mc, const TString skim_mc_bkg, const TString label) { //const TString skim_mc_bkg,
  if(label.Contains("verbose")) VERBOSE = true;
  gStyle->SetOptStat(0);

  TString makedir = "mkdir -p OverlayPrior/"+label+"/";
  const char *mkDIR = makedir.Data();
  gSystem->Exec(mkDIR);

  TH1::SetDefaultSumw2();

  // trigger is named differently in MC, hardcode for now :(
  std::string trigger_mc = "L1_SingleEG21_BptxAND && HLT_HIGEDPhoton40_v1";// "HLT_HIPhoton40_HoverELoose_v1";//
  std::string trigger = "L1_SingleEG21_BptxAND && HLT_HIGEDPhoton40_v1";// "HLT_HIPhoton40_HoverELoose_v1";//

  TFile* fskim_data = TFile::Open(skim_data);
  // TTree* data_tree  = (TTree*)fskim_data->Get("jet_tree");
  TFile* fskim_mc = TFile::Open(skim_mc);
  // TTree* mc_tree  = (TTree*)fskim_mc->Get("jet_tree");

  TFile* fskim_mc_2 = TFile::Open(skim_mc_bkg);
  TFile* output = new TFile("OverlayPrior/"+label+"/"+label+".root", "RECREATE");

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
  float purity_unc[ncent][npt] = {0};

  const TCut eta_cut = "(abs(phoEta) < 1.442) && phoSigmaIEtaIEta_2012>0.002 && !(phoEta<-1.39 && phoPhi<-0.9 && phoPhi>-1.6)";
  const TCut ele_cut = "!eleRej";

  const TCut candidate_isolation =  "(SumCalIso) < 1.45486 && phoHoverE<0.137168";//"(SumCalIso) < -0.479 && phoHoverE<0.0233";// 
  const TCut sideband_isolation =  "((SumCalIso)>1) && ((SumCalIso)<25) && phoHoverE<0.137168";//"((SumCalIso)>10) && ((SumCalIso)<20) && phoHoverE<0.0233";// 
  const TCut signal_selection = "(pho_genMatchedIndex!= -1) && mcCalIsoDR04<5 && mcPID == 22 && (abs(mcMomPID)<=22 || mcMomPID == -999)";

  const std::string weight_string = "weight*weight_pthat*weight_cent";//
  TCut weight_label = weight_string.c_str();

  for (std::size_t i = 0; i < ncent; ++i) {
    for (std::size_t j = 0; j < npt; ++j) {
      TString pt_cut = Form("(phoEtCorrected >= %f) && (phoEtCorrected < %f)", min_pt[j], max_pt[j]);
      TString cent_cut = Form("(hiBin >= %i) && (hiBin < %i)", min_cent[i], max_cent[i]);

      TCut trigger_selection = Form("%s", trigger.c_str());
      TCut trigger_selection_mc = Form("%s", trigger_mc.c_str());

      TCut candidate_cut = candidate_isolation && eta_cut && ele_cut && pt_cut && cent_cut && noiseCut && trigger_selection;
      TCut sideband_cut = sideband_isolation && eta_cut && ele_cut && pt_cut && cent_cut && noiseCut && trigger_selection;
      TCut signal_cut = signal_selection && eta_cut && ele_cut && pt_cut && cent_cut && trigger_selection_mc;
      signal_cut = signal_cut * weight_label;

      const int nbins = 200;
      const int divisions = 1;
      float sig_shift = 0;//config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySignalShift];
      float bkg_shift = 0;//config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityBackgroundShift];

      TH1D* hdata = (TH1D*) fskim_data->Get(Form("hangu_lead_%zu",i)); // new TH1D(Form("hdata_%zu_%zu", i, j), "", nbins, 0, 0.025);
      // hdata->Rebin();
      hdata->SetName(Form("data_hist_%zu",i));
      hdata->Write("", TObject::kOverwrite);
      // data_tree->Project(hdata->GetName(), "phoSigmaIEtaIEta_2012", candidate_cut, "");
      if(VERBOSE){
      std::cout << "data count: " << hdata->GetEntries() << std::endl;
      }

      TH1D* hbkg = (TH1D*) fskim_mc_2->Get(Form("hangu_lead_%zu",i));// new TH1D(Form("hbkg_%zu_%zu", i, j), "", nbins * divisions, 0, 0.025);
      // hbkg->Rebin();
      hbkg->SetName(Form("bkg_hist_%zu",i));
      // hbkg->Scale(hdata->Integral()*0.35/hbkg->Integral());
      hbkg->Write("", TObject::kOverwrite);
      // data_tree->Project(hbkg->GetName(), Form("phoSigmaIEtaIEta_2012 + %f", bkg_shift), sideband_cut, "");
      TH1D* hsig = (TH1D*) fskim_mc->Get(Form("hangu_lead_%zu",i));//new TH1D(Form("hsig_%zu_%zu", i, j), "", nbins * divisions, 0, 0.025);
      // hsig->Rebin();
      hsig->SetName(Form("sig_hist_%zu",i));
      // hsig->Scale(hdata->Integral()*0.65/hsig->Integral());
      hsig->Write("", TObject::kOverwrite);
      // mc_tree->Project(hsig->GetName(), Form("phoSigmaIEtaIEta_2012 + %f", sig_shift), signal_cut, "");
      
      if(VERBOSE){
        std::cout << "bkg count: " << hbkg->GetEntries() << std::endl;
        std::cout << "sig count: " << hsig->GetEntries() << std::endl;
      }

      float range_low =  0;
      float range_high = 0.2;
      float sieie_cut =  0.2;//0.0103766;

      /* fit using binned templates */
      Templates* templates = new Templates(hdata, hsig, hbkg, divisions);

      // templates->Write();

      Purity* purity = new Purity();
      purity->fit(templates, hdata, range_low, range_high, sieie_cut);

        TF1* f = new TF1("f", templates, &Templates::evaluate, range_low, range_high, 3);
        f->SetParameters(hdata->Integral(1, hdata->GetNbinsX()), 0.25, 0.0);
        f->SetParLimits(1, 0, 1);
        f->FixParameter(2, 0.0);
        // f->SetParLimits(2, -0.0001, 0.0001);

        hdata->Fit("f", "WL 0 Q", "", range_low, range_high);
        hdata->Fit("f", "WL 0 Q", "", range_low, range_high);
        hdata->Fit("f", "WL M 0", "", range_low, range_high);

        std::cout<<i<<"  Parameter 0 ="<<f->GetParameter(0)<<std::endl;
        std::cout<<i<<"  Parameter 1 ="<<f->GetParameter(1)<<std::endl;
        std::cout<<i<<"  Parameter 2 ="<<f->GetParameter(2)<<std::endl;

      if(VERBOSE){
        std::cout << "nsig: " << purity->nsig << std::endl;
        std::cout << "purity: " << purity->purity << std::endl;
        std::cout << "chisq: " << purity->chisq << std::endl;
        std::cout << "ndf: " << purity->ndf << std::endl;
        //? To draw confidence intervals of the fit 
        /*Create a histogram to hold the confidence intervals*/
        //  TH1D *hint = new TH1D("hint",
        //     "Fitted Gaussian with .95 conf.band", 100, -3, 3);
        //  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint);
        //  //Now the "hint" histogram has the fitted function values as the
        //  //bin contents and the confidence intervals as bin errors
        //  hint->SetStats(false);
        //  hint->SetFillColor(2);
        //  hint->Draw("e3 same");
      }

      purity->write();

      purity_values[i][j] = purity->purity;
      purity_unc[i][j] = f->GetParError(1);
      if(VERBOSE){
        std::cout<<"i = "<<i<<"   j = "<<j<<"   Purity = "<<purity_values[i][j]<<std::endl;
      }
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
        if(VERBOSE){
        std::cout<<"Print value\n";
        }
        TemplatePlot(label,i,j,purity_values[i][j],purity_unc[i][j]);
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

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);

    TFile *input_file = TFile::Open("OverlayPrior/"+label+"/"+label+".root","UPDATE");

    THStack hs("hs", "hs");
    TCanvas c;
    // c.SetLogy(1);
    if(VERBOSE){
        std::cout<<"Open File\n";
    }
    

    TH1F* h_data      = (TH1F *)input_file->Get(Form("data_hist_%zu_template_fit",i)); 
    TH1F* h_sig_fit   = (TH1F *)input_file->Get(Form("data_hist_%zu_template_fit_sig",i)); 
    TH1F* h_bkg_fit   = (TH1F *)input_file->Get(Form("data_hist_%zu_template_fit_bkg",i)); 
    TH1F* h_total_fit = (TH1F *)input_file->Get(Form("data_hist_%zu_template_fit_total",i));
    TH1::SetDefaultSumw2(); 

    // TH1F* h_data      = (TH1F *)input_file->Get(Form("data_hist_%zu",i)); 
    // TH1F* h_sig_fit   = (TH1F *)input_file->Get(Form("sig_hist_%zu",i)); 
    // TH1F* h_bkg_fit   = (TH1F *)input_file->Get(Form("bkg_hist_%zu",i)); 
    // TH1F* h_total_fit = (TH1F *)input_file->Get(Form("sig_hist_%zu",i)); 
    // h_total_fit->Add(h_bkg_fit);
    Float_t den = (h_sig_fit->Integral()+h_bkg_fit->Integral());
    // h_sig_fit->Scale(h_data->Integral()/den);
    // h_bkg_fit->Scale(h_data->Integral()/den);
    // h_total_fit->Scale(h_data->Integral()/h_total_fit->Integral());

    h_data->SetTitle(";#it{g};Events");
    h_sig_fit->SetTitle(";#it{g};Events");
    h_bkg_fit->SetTitle(";#it{g};Events");
    h_total_fit->SetTitle(";#it{g};Events");

    // h_data->Rebin();
    // h_sig_fit->Rebin();
    // h_bkg_fit->Rebin();
    // h_total_fit->Rebin();

    h_data->SetLineColor(1);
    h_data->SetMarkerColor(1);
    h_data->SetMarkerStyle(kFullCircle);
    // h_data->SetMarkerSize(.7); 
    

    h_total_fit->SetLineColor(kTeal+3);
    h_total_fit->SetMarkerColor(kTeal+3);
    h_total_fit->SetMarkerStyle(23);
    // h_total_fit->SetMarkerSize(.7); 
    // hs.Add(h_total_fit);      

    h_bkg_fit->SetLineColor(4);
    h_bkg_fit->SetFillColorAlpha(4,0.35);
    h_bkg_fit->SetFillStyle(3345);
    h_bkg_fit->SetMarkerColor(4);
    
    hs.Add(h_bkg_fit);

    h_sig_fit->SetLineColor(2);
    h_sig_fit->SetFillColorAlpha(2,0.35);
    h_sig_fit->SetFillStyle(3345);
    h_sig_fit->SetMarkerColor(2);

    hs.Add(h_sig_fit); 
    if(VERBOSE){
        std::cout<<"Add to stack\n";
    }

    h_data->Draw("E");
    hs.Draw("SamehistE");
    // h_sig_fit->Draw("Samehist_E");
    h_total_fit->Draw("Samehist_L");
    if(VERBOSE){
        std::cout<<"Draw plots\n";
    }

    // hs.GetXaxis()->SetTitle("#sigma_{#eta#eta}");
    // hs.GetYaxis()->SetTitle("Events");

    float leg_x1 = 0.58;
    float leg_y1 = 0.65;
    float leg_x2 = 0.8;
    float leg_y2 = 0.85;
    TLegend* leg = new TLegend(leg_x1,leg_y1,leg_x2,leg_y2,"","brNDC");
    leg->SetFillStyle(0);
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->SetTextSize(0.042);
    leg->AddEntry(h_data, "Data", "lep");
    leg->AddEntry(h_total_fit,"Total Fit" , "l");//"Total Fit" "Quark+Gluon"
    leg->AddEntry(h_sig_fit, "Quark fit stacked", "lep");
    leg->AddEntry(h_bkg_fit, "Gluon fit stacked", "lep");
    leg->SetTextFont(42);
    leg->Draw();

    TLatex latex;
    latex.SetTextSize(0.042);
    latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Preliminary}} #bf{pp 300.6 pb^{-1} (5.02 TeV)}"); // PbPb 1.69 nb^{-1}
    leg_y1-=0.06;
    latex.DrawLatexNDC(leg_x1,leg_y1,Form("Quark Fraction : %.3f", purity)); // ,orig_purity
    leg_y1-=0.06;
    latex.DrawLatexNDC(leg_x1,leg_y1,Form("Cent. %.0f - %.0f%%", min_cent_val[i]/2.0, max_cent_val[i]/2.0));
    leg_y1-=0.06;
    latex.DrawLatexNDC(leg_x1,leg_y1,Form("x_{J}>0.8"));
    // mySmallText(0.55,0.5,1,Form("Cent. %.0f - %.0f%%", min_cent_val[i]/2, max_cent_val[i]/2));
    // mySmallText(0.55,0.4,1,Form("Quark Fraction : %.3f", purity)); 
    // mySmallText(0.55,0.4,1,Form("%.0f < E_{T}^{#gamma} <%.0f", min_pt[j], max_pt[j]));
    // mySmallText(0.55,0.4,1,"Pre-fit"); 
    // drawHeader();
    if(VERBOSE){
        std::cout<<"Legend draw\n";
    }

    c.SaveAs(Form("OverlayPrior/"+label+"/Template_fit_%zu_%zu.png",i,j));   
    // c.Write(Form("Template_fit_%zu_%zu",i,j),TObject::kOverwrite);   

    input_file->Close();

}

int main(int argc, char* argv[]) {
  
  if (argc == 5){
    gROOT->SetBatch();
    // SetPlotStyle();
    gErrorIgnoreLevel = kWarning;
    return Purity_Prior(argv[1], argv[2], argv[3], argv[4]);

  }

  return 1;
}
