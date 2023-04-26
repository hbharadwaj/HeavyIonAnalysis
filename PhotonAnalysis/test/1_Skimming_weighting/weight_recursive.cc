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
#include <TSystemDirectory.h>
#include <TSystemFile.h>

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
#endif

using namespace std;

const int NCUTOFF = 5;
// const float CUTOFF[NCUTOFF] = {0,29.808813095,49.885753632,79.932403564,119.952224731,169.969177246};
// const float CUTOFF_MAX[NCUTOFF] = {29.808813095,49.885753632,79.932403564,119.952224731,169.969177246,0};
const float CUTOFF[NCUTOFF] = {0,50,80,120,170};
const float CUTOFF_MAX[NCUTOFF] = {50,80,120,170,0};
// const float CUTOFF[NCUTOFF] = {30,50,80,120,170};
Double_t scale[NCUTOFF]; 

void DrawLatex(Float_t x, Float_t y, Int_t color, const char* text, Float_t textSize = 0.06)                                             
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
   gStyle->SetOptStat(1);
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

float calc_scale(float pthat){
        if(pthat<CUTOFF_MAX[0]){
            return (scale[0]);
        }
        else if(pthat<CUTOFF_MAX[1]){
            return (scale[1]);
        }
        else if(pthat<CUTOFF_MAX[2]){
            return (scale[2]);
        }
        else if(pthat<CUTOFF_MAX[3]){
            return (scale[3]);
        }
        else{ // if(pthat<CUTOFF_MAX[4]){
            return (scale[4]);
        }
        // else {
        //     return (scale[5]);
        // }
}

void weight_pthat(TString temp_sample="QCDPhoton_pthat_15", TString add_sample="QCDPhoton_pthat_30", Int_t range = 1
                ){

    TString type_dir = "/home/llr/cms/bharikri/Projects/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/JetAnalysis/test/Pthat_weighting/";
    
    TChain template_sample("template_sample"),sample("sample");

    // if(temp_sample.Contains("QCDPhoton_pthat_15")){
    //     template_sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_15/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    // }
    if(temp_sample.Contains("QCDPhoton_pthat_30")){
        // template_sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_30/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
        template_sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_30/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");   // pthat template
    }
    if(temp_sample.Contains("QCDPhoton_pthat_50")){
        // template_sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_50/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
        template_sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_50/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");   // pthat template
    }
    if(temp_sample.Contains("QCDPhoton_pthat_80")){
        // template_sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_80/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
        template_sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_80/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");   // pthat template
    }
    if(temp_sample.Contains("QCDPhoton_pthat_120")){
        // template_sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_120/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
        template_sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_120/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");   // pthat template
    }
    if(temp_sample.Contains("QCDPhoton_pthat_170")){
        // template_sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_170/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
        template_sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_170/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");   // pthat template
    }

    // if(add_sample.Contains("QCDPhoton_pthat_15")){
    //     sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_15/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    // }
    if(add_sample.Contains("QCDPhoton_pthat_30")){
        // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_30/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");    // List of samples 
        sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_30/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    }
    if(add_sample.Contains("QCDPhoton_pthat_50")){
        // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_50/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");    // List of samples 
        sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_50/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    }
    if(add_sample.Contains("QCDPhoton_pthat_80")){
        // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_80/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");    // List of samples 
        sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_80/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    }
    if(add_sample.Contains("QCDPhoton_pthat_120")){
        // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_120/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");    // List of samples 
        sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_120/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    }
    if(add_sample.Contains("QCDPhoton_pthat_170")){
        // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_170/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");    // List of samples 
        sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_170/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    }


    if(temp_sample.Contains("EMEnrichedDijet-pthat_30")){
        template_sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_30/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    if(temp_sample.Contains("EMEnrichedDijet-pthat_50")){
        template_sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_50/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    if(temp_sample.Contains("EMEnrichedDijet-pthat_80")){
        template_sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_80/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    if(temp_sample.Contains("EMEnrichedDijet-pthat_120")){
        template_sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_120/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    if(temp_sample.Contains("EMEnrichedDijet-pthat_170")){
        template_sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_170/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    if(temp_sample.Contains("EMEnrichedDijet-pthat_220")){
        template_sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_220/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }

    if(add_sample.Contains("EMEnrichedDijet-pthat_30")){
        sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_30/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    if(add_sample.Contains("EMEnrichedDijet-pthat_50")){
        sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_50/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    if(add_sample.Contains("EMEnrichedDijet-pthat_80")){
        sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_80/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    if(add_sample.Contains("EMEnrichedDijet-pthat_120")){
        sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_120/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    if(add_sample.Contains("EMEnrichedDijet-pthat_170")){
        sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_170/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    if(add_sample.Contains("EMEnrichedDijet-pthat_220")){
        sample.Add("/data_CMS/cms/bharikri/EMEnrichedDijet-pthat_220/HiForestAOD_*.root/hiEvtAnalyzer/HiTree"); 
    }
    
    float pthat = 0;
    float pthat_2 = 0;

    sample.SetBranchAddress("pthat", &pthat);
    template_sample.SetBranchAddress("pthat", &pthat_2);

    float weight=0;
    float weight_2=0;

    sample.SetBranchAddress("weight", &weight);
    template_sample.SetBranchAddress("weight", &weight_2);

    int nbins = 20000;
    TH1F* h_pthat_1=new TH1F("h_pthat_1","h_pthat_1;pthat;Events",nbins,0,2000);
    TH1F* h_pthat_2=new TH1F("h_pthat_2","h_pthat_2;pthat;Events",nbins,0,2000);

    Int_t nEv=sample.GetEntries();

    std::cout<<endl;
    for(int iEntry=0; iEntry< template_sample.GetEntries(); iEntry++){
        template_sample.GetEntry(iEntry);
        displayProgress(iEntry,template_sample.GetEntries());
        h_pthat_2->Fill(pthat_2,weight_2*calc_scale(pthat_2));
    }
    std::cout<<endl;
    for(int iEntry=0; iEntry< nEv; iEntry++){
        sample.GetEntry(iEntry);
        displayProgress(iEntry,nEv);
        h_pthat_1->Fill(pthat,weight*1);
    }
    std::cout<<endl;    

    TCanvas c1;

    int binMin = 0;
    int binMax = 0;

    binMin = (CUTOFF[range] != 0) ? h_pthat_1->FindBin(CUTOFF[range]) : 0;
    binMax = (CUTOFF_MAX[range] != 0) ? h_pthat_1->FindBin(CUTOFF_MAX[range])-1 : h_pthat_1->GetNbinsX()+1;
    double tot1 = h_pthat_1->Integral(binMin, binMax);

    binMin = (CUTOFF[range] != 0) ? h_pthat_2->FindBin(CUTOFF[range]) : 0;
    binMax = (CUTOFF_MAX[range] != 0) ? h_pthat_2->FindBin(CUTOFF_MAX[range])-1 : h_pthat_2->GetNbinsX()+1;
    double tot2 = h_pthat_2->Integral(binMin, binMax);

    for(;range<NCUTOFF;range++) scale[range] = tot2/tot1;
    delete h_pthat_1;
    delete h_pthat_2;

    // scale[0]*=1;
    // scale[1]*=1;
    // scale[2]*=1;
    // scale[3]*=1;
    // scale[4]*=1;
    // scale[5]*=1;

 
}

void plot_pthat(){
    TString type_dir = "/home/llr/cms/bharikri/Projects/Photon_Analysis/CMSSW_10_3_3_patch1/src/HeavyIonsAnalysis/PhotonAnalysis/test/1_Skimming_weighting/";
    TChain sample5("sample5"),sample4("sample4"),sample3("sample3"), sample2("sample2"),sample1("sample1"),sample("sample");
    
    // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_15/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");    // List of samples 
    // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_30/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_50/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_80/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_120/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");    
    // sample.Add("/data_CMS/cms/bharikri/QCDPhoton_pthat_170/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");

    sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_30/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_50/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_80/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_120/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    sample.Add("/data_CMS/cms/bharikri/Signal_MC_RefParton_R_0_234/QCDPhoton_pthat_170/HiForestAOD_*.root/hiEvtAnalyzer/HiTree");
    

    // sample.Add("/eos/user/b/bharikri/CERNBox_synced/Projects/HeavyIon/Results/2022_03_17_Photon_Final_Reproduction/1_Skimming_weighting/QCDPhoton_Kaya.root/pho_tree");
    
    float pthat = 0;

    sample.SetBranchAddress("pthat", &pthat);

    float weight=0;
    float weight_pthat=0;

    sample.SetBranchAddress("weight", &weight);
    // sample.SetBranchAddress("weight_pthat", &weight);

    int nbins = 1000;

    TH1F* h_pthat_1=new TH1F("h_pthat_1","h_pthat_1;pthat;Events",nbins,0,1000);
    TH1F* h_pthat_2=new TH1F("h_pthat_2","h_pthat_2;pthat;Events",nbins,0,1000);
    TH1F* h_pthat=new TH1F("h_pthat","h_pthat;pthat combined and scaled;Events",nbins,0,1000);
    TH1F* h_pthat_zoom=new TH1F("h_pthat_zoom","h_pthat_zoom;pthat combined and scaled;Events",nbins,165,175);

    // Double_t SIGpthat_weight[6] = {1,0.209208082,0.055167059,0.013352246,0.003149858,0.000786793}; 

    Int_t nEv=sample.GetEntries();
    
    for(int iEntry=0; iEntry< nEv; iEntry++){
        displayProgress(iEntry,nEv);
        sample.GetEntry(iEntry);
        Float_t tempscale = weight; 

        if(pthat<CUTOFF_MAX[0]){
            tempscale *=scale[0];
        }
        else if(pthat<CUTOFF_MAX[1]){
            tempscale *=scale[1];
        }
        else if(pthat<CUTOFF_MAX[2]){
            tempscale *=scale[2];
        }
        else if(pthat<CUTOFF_MAX[3]){
            tempscale *=scale[3];
        }
        else {//if(pthat<CUTOFF_MAX[4]){
            tempscale *=scale[4];
        }
        // else {
        //     tempscale *=scale[5];
        // }
        h_pthat->Fill(pthat,tempscale);
    }

    TCanvas c;
    TString DIR = type_dir;
    gPad->SetLogy(1);

    h_pthat->GetXaxis()->SetRangeUser(10,130);
    h_pthat->SetLineColor(4);
    h_pthat->SetMarkerColor(4);
    h_pthat->SetMarkerStyle(22);
    h_pthat->Draw();
    c.SaveAs(DIR+"pthat_combined_log.jpeg");

    h_pthat->GetXaxis()->SetRangeUser(110,200);
    h_pthat->SetLineColor(4);
    h_pthat->SetMarkerColor(4);
    h_pthat->SetMarkerStyle(22);
    h_pthat->Draw();
    c.SaveAs(DIR+"pthat_combined_log_tail.jpeg");

    gPad->SetLogy(0);
    gStyle->SetOptStat(1);
    gStyle->SetStatX(0.38);
    gStyle->SetStatY(0.85);
    gStyle->SetStatW(0.11);
    gStyle->SetStatFontSize(0.03);
    gStyle->SetStatFont(42);

    h_pthat->GetXaxis()->SetRangeUser(10,130);
    h_pthat->SetLineColor(4);
    h_pthat->SetMarkerColor(4);
    h_pthat->SetMarkerStyle(22);
    h_pthat->Draw();
    c.SaveAs(DIR+"pthat_combined.jpeg");

    h_pthat->GetXaxis()->SetRangeUser(110,200);
    h_pthat->SetLineColor(4);
    h_pthat->SetMarkerColor(4);
    h_pthat->SetMarkerStyle(22);
    h_pthat->Draw();
    c.SaveAs(DIR+"pthat_combined_tail.jpeg");

}


int main(){

    // gROOT->SetBatch();
    SetPlotStyle();
    gErrorIgnoreLevel = kWarning;

    // TString sample0 = "QCDPhoton_pthat_15";
    TString sample0 = "QCDPhoton_pthat_30";
    TString sample1 = "QCDPhoton_pthat_50";
    TString sample2 = "QCDPhoton_pthat_80";
    TString sample3 = "QCDPhoton_pthat_120";
    TString sample4 = "QCDPhoton_pthat_170";
/*
    TString sample0 = "EMEnrichedDijet-pthat_30";
    TString sample1 = "EMEnrichedDijet-pthat_50";
    TString sample2 = "EMEnrichedDijet-pthat_80";
    TString sample3 = "EMEnrichedDijet-pthat_120";
    TString sample4 = "EMEnrichedDijet-pthat_170";
    TString sample5 = "EMEnrichedDijet-pthat_220";
*/

    scale[0]=1; // 15-30 = 1
    scale[1]=1; // 30-50
    scale[2]=1; // 50-80    
    scale[3]=1; // 80-120   
    scale[4]=1; // 120-170  
    scale[5]=1; // 170-end

    weight_pthat(sample0,sample0+sample1,1);
    weight_pthat(sample0+sample1,sample0+sample1+sample2,2);
    weight_pthat(sample0+sample1+sample2,sample0+sample1+sample2+sample3,3);
    weight_pthat(sample0+sample1+sample2+sample3,sample0+sample1+sample2+sample3+sample4,4);
    // weight_pthat(sample0+sample1+sample2+sample3+sample4,sample0+sample1+sample2+sample3+sample4+sample5,5);

    plot_pthat();

    printf("\nscale in [%0.3f,%0.3f] = %.9f\n",CUTOFF[0],CUTOFF_MAX[0],scale[0]);
    printf("\nscale in [%0.3f,%0.3f] = %.9f\n",CUTOFF[1],CUTOFF_MAX[1],scale[1]);
    printf("\nscale in [%0.3f,%0.3f] = %.9f\n",CUTOFF[2],CUTOFF_MAX[2],scale[2]);
    printf("\nscale in [%0.3f,%0.3f] = %.9f\n",CUTOFF[3],CUTOFF_MAX[3],scale[3]);
    printf("\nscale in [%0.3f,%0.3f] = %.9f\n",CUTOFF[4],CUTOFF_MAX[4],scale[4]);
    // printf("\nscale in [%0.3f,%0.3f] = %.9f\n",CUTOFF[5],CUTOFF_MAX[5],scale[5]);

    
    return 0;
}