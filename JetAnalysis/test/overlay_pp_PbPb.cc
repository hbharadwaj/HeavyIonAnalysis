// overlay_uncert("~/analysis/Uncertainty/OutputCombined/Data_0_30_Dec_07_Rg_xJ_gp4_l3_bin_2.root","Data_0_30_Dec_07_Rg_xJ_gp4_l3_bin_2","~/pp_analysis/Analysis/Uncertainty/OutputCombined/pp_Data_0_30_Dec_07_pp_xJ_gp4_l3_Rg.root","pp_Data_0_30_Dec_07_pp_xJ_gp4_l3_Rg")

#include <TSystem.h>        // needed for gSystem
#include <TStyle.h>         // needed for gStyle 
// #include <TChain.h>         // needed for TChain
#include "TROOT.h"          // needed for gROOT
#include <TError.h>         // needed for gErrorIgnoreLevel
#include <TVector2.h>       // needed for TVector2::Phi_mpi_pi        
#include <TH2.h>            // needed fror TH1 and TH2
#include <TLegend.h>        // needed for Legend
#include <TCanvas.h>        // needed for Canvas
#include <TMath.h>          //! needed for floating values in plots for some reason
#include <THStack.h>        // needed for THStack
#include <TLatex.h>         // needed for TLatex
#include "TRatioPlot.h"     // needed for RatioPlot
#include "TFile.h"          // needed for TFile
// #include "plotTools.h"      // my plotting functions

#include <iostream>         // needed for I/O

TString centstring="";
TString label="";
TCanvas c;
/*
void overlay_stack(std::vector<TH1F*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void overlay(std::vector<TH1F*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void overlay_stack(std::vector<TH1F*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
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
                                       922,910,851,877,811,804,434,606,
                                       1,632,600,616,419,800,425,898,
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

    THStack *hs = new THStack("hs","hs");
    
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
        l->AddEntry(hist[ihist], histname[ihist], "lep");

        if(ihist==0) continue;
        hs->Add(hist[ihist]);
    }
    float ymax = hist[0]->GetMaximum();
    if(hs->GetMaximum()>ymax) ymax = hs->GetMaximum();
    auto rp1 = new TRatioPlot(hs,hist[0]);
    rp1->SetUpTopMargin(0.15);
    rp1->SetRightMargin(0.05);
    rp1->SetLowBottomMargin(0.3);
    rp1->SetLeftMargin(0.12);
    rp1->SetH1DrawOpt(drawopt);
    rp1->SetH2DrawOpt(drawopt);
    rp1->SetGraphDrawOpt(drawopt);
    rp1->Draw();
    rp1->GetLowerRefYaxis()->SetNdivisions(10);
    rp1->GetLowerRefYaxis()->SetLabelSize(0.03);
    rp1->GetCalculationOutputGraph()->SetLineColor(colarray[1]);
    rp1->GetCalculationOutputGraph()->SetMarkerColor(colarray[1]);
    rp1->GetCalculationOutputGraph()->SetMarkerStyle(markarray[1]);
    if(!opt.Contains("log")){
        rp1->GetLowerRefGraph()->SetMaximum(1.5);
        rp1->GetLowerRefGraph()->SetMinimum(0.5);
    }
    rp1->GetLowerRefYaxis()->SetTitle("Ratio");
    if(!opt.Contains("log"))
        hs->SetMaximum(ymax*1.1);
    else
        hs->SetMaximum(ymax*2);
    if(opt.Contains("label")){
        // rp1->GetLowerRefXaxis()->SetTitle(histname.at(histname.size()-3));
        rp1->GetUpperRefYaxis()->SetTitle(histname.at(histname.size()-3));
        hs->GetXaxis()->SetTitle(histname.at(histname.size()-2));
    }
    else{
        // rp1->GetLowerRefXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());  // for some reason this doesn't work for THStack
        rp1->GetUpperRefYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle()); 
        hs->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
    }
    l->Draw();

    TLatex latex;
    latex.SetTextSize(0.035);
    latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Internal}}");

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
    c.SaveAs(output_path + "/OverlayPlots_ppPbPb/"+histname.back()+"_"+centstring+".png");
    std::cout<<histname.back()<<"_"<<centstring<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
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
                                       922,910,851,877,811,804,434,606,
                                       1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41,
                                        20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};

    
    TCanvas c;
    TLegend *l;
    float leg_x1 = 0.7;
    float leg_y1 = 0.6;
    float leg_x2 = 0.8;
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

    l->Draw();

    TLatex latex;
    latex.SetTextSize(0.045);
    latex.DrawLatexNDC(0.12,0.9,"CMS #it{#bf{Internal}}");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.9,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.4,0.9,eopt[0]);
        latex.DrawLatexNDC(0.78,0.9,eopt[1]);
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

    gPad->Update();
    c.SaveAs(output_path + "/OverlayPlots_ppPbPb/"+histname.back()+"_"+centstring+".png");
    c.Write(histname.back());
    std::cout<<histname.back()<<"_"<<centstring<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}
*/

void overlay_uncert(TString file_PbPb, TString label_PbPb, TString file_pp, TString label_pp="", TString out_label=""){
    gErrorIgnoreLevel = kFatal;
    if(label_pp==""){
        label_pp = label_PbPb;
        out_label = label_PbPb;
    } 
    label = out_label;
    TFile *f_PbPb = TFile::Open(file_PbPb);
    TFile *f_pp = TFile::Open(file_pp);

    TH1D *hPbPb_nom = (TH1D*)f_PbPb->Get(label_PbPb+"_nom");
    TGraphAsymmErrors *hPbPb_stat = (TGraphAsymmErrors*)f_PbPb->Get("stat_uncert");
    TGraphAsymmErrors *hPbPb_sys = (TGraphAsymmErrors*)f_PbPb->Get("sys_uncert");
    TGraphAsymmErrors *hPbPb_tot = (TGraphAsymmErrors*)f_PbPb->Get("tot_uncert");

    TH1D *hpp_nom = (TH1D*)f_pp->Get(label_pp+"_nom");
    TGraphAsymmErrors *hpp_stat = (TGraphAsymmErrors*)f_pp->Get("stat_uncert");
    TGraphAsymmErrors *hpp_sys = (TGraphAsymmErrors*)f_pp->Get("sys_uncert");
    TGraphAsymmErrors *hpp_tot = (TGraphAsymmErrors*)f_pp->Get("tot_uncert");

    Double_t PbPb_untagged = hPbPb_nom->Integral(0,1)/hPbPb_nom->Integral(0,-1);
    Double_t pp_untagged = hpp_nom->Integral(0,1)/hpp_nom->Integral(0,-1);

    // Define the ratio plot
    TH1D *hratio = (TH1D*)hPbPb_nom->Clone("ratio");
    hratio->Sumw2();
    hratio->Divide(hpp_nom);

    Double_t vec_x[20],vec_y[20],errx_do[20],errx_up[20],erry_do[20],erry_up[20],errstat_do[20],errstat_up[20],errtot_do[20],errtot_up[20];
    for(Int_t j=0;j<=hratio->GetNbinsX()+1;j++){ 

        Double_t erry_stat_a = hratio->GetBinError(j); 
        Double_t erry_stat_b=erry_stat_a;

        Double_t temp_pp_x,temp_pp_y,temp_PbPb_x,temp_PbPb_y;
        hpp_sys->GetPoint(j,temp_pp_x,temp_pp_y);
        hPbPb_sys->GetPoint(j,temp_PbPb_x,temp_PbPb_y);

        Double_t erry_pp_sys_a = hpp_sys->GetErrorYhigh(j)/temp_pp_y;
        Double_t erry_pp_sys_b = hpp_sys->GetErrorYlow(j)/temp_pp_y;

        Double_t erry_PbPb_sys_a = hPbPb_sys->GetErrorYhigh(j)/temp_PbPb_y;
        Double_t erry_PbPb_sys_b = hPbPb_sys->GetErrorYlow(j)/temp_PbPb_y;

        Double_t erry_uncorr_up = TMath::Sqrt(erry_pp_sys_a*erry_pp_sys_a + erry_PbPb_sys_a*erry_PbPb_sys_a);
        Double_t erry_uncorr_do = TMath::Sqrt(erry_pp_sys_b*erry_pp_sys_b + erry_PbPb_sys_b*erry_PbPb_sys_b);

        Double_t erry_ratio_total_up = TMath::Sqrt(erry_stat_a*erry_stat_a + erry_uncorr_up*erry_uncorr_up);
        Double_t erry_ratio_total_do = TMath::Sqrt(erry_stat_b*erry_stat_b + erry_uncorr_do*erry_uncorr_do);

        // Error x and vectors
        vec_x[j] = hratio->GetBinCenter(j);
        vec_y[j] = hratio->GetBinContent(j);

        errstat_up[j] = erry_stat_a;
        errstat_do[j] = erry_stat_b;      
        errx_do[j] = 0.5*hratio->GetBinWidth(j);
        errx_up[j] = errx_do[j];
        erry_up[j] = erry_uncorr_up;
        erry_do[j] = erry_uncorr_do;
        errtot_up[j] = erry_ratio_total_up;
        errtot_do[j] = erry_ratio_total_do;
    }
    // auto hratio_stat = new TGraphAsymmErrors(hratio->GetNbinsX(),vec_x,vec_y,errx_up,errx_do,errstat_up,errstat_do);
    auto hratio_sys = new TGraphAsymmErrors(hratio->GetNbinsX()+1,vec_x,vec_y,errx_up,errx_do,erry_up,erry_do);
    auto hratio_tot = new TGraphAsymmErrors(hratio->GetNbinsX()+1,vec_x,vec_y,errx_up,errx_do,errtot_up,errtot_do);

    TString DIR = "Overlay_ppPbPb/";
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    TFile *fout = new TFile("Overlay_ppPbPb/"+label+".root","RECREATE");
    TLegend *l;
    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetHistTopMargin(0);
    // gStyle->SetOptLogy(1);

    // Histogram Styling

        // Palette 
            gStyle->SetPalette(1);
            TColor *pal = new TColor();
            // good for primary marker colors                                                                                             

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
        hPbPb_nom->SetLineColor(kRed+1); // Red Box
        hPbPb_nom->SetMarkerColor(kRed+1);
        hPbPb_nom->SetMarkerStyle(21);
        //hPbPb_nom->SetMarkerSize(0.2);

        hPbPb_sys->SetFillStyle(3354); //  Light Pink box
        hPbPb_sys->SetFillColor(kpink);
        hPbPb_sys->SetLineColor(kpink); 
        hPbPb_sys->SetMarkerColor(kpink);
        hPbPb_sys->SetMarkerStyle(21);
        hPbPb_sys->SetMarkerSize(0);

        hPbPb_tot->SetFillStyle(3002); 
        hPbPb_tot->SetFillColor(korangeLight);
        hPbPb_tot->SetLineColor(korangeLight); 
        hPbPb_tot->SetMarkerColor(korangeLight);
        hPbPb_tot->SetMarkerStyle(21);
        hPbPb_tot->SetMarkerSize(0);

        hpp_nom->SetLineColor(kblue);
        hpp_nom->SetMarkerColor(kblue);
        hpp_nom->SetMarkerStyle(20);
        // hpp_nom->SetMarkerSize(0.2);

        hpp_sys->SetFillStyle(3345); 
        hpp_sys->SetFillColor(kcyan);
        hpp_sys->SetLineColor(kcyan); 
        hpp_sys->SetMarkerColor(kcyan);
        hpp_sys->SetMarkerStyle(20);
        hpp_sys->SetMarkerSize(0);
        
        hpp_tot->SetFillStyle(3002); 
        hpp_tot->SetFillColor(kazureLight);
        hpp_tot->SetLineColor(kazureLight); 
        hpp_tot->SetMarkerColor(kazureLight);
        hpp_tot->SetMarkerStyle(20);
        hpp_tot->SetMarkerSize(0);
        
        hratio->SetLineColor(kBlack);
        hratio->SetMarkerColor(kBlack);
        hratio->SetMarkerStyle(20);
        hratio->SetMarkerSize(0.2);

        hratio_sys->SetFillStyle(3244); // Grey Box //1001 for solid 
        hratio_sys->SetFillColor(kGray+3);
        hratio_sys->SetLineColor(kGray+3); 
        hratio_sys->SetMarkerColor(kGray+3);
        hratio_sys->SetMarkerStyle(20);
        // hratio_sys->SetMarkerSize(0.2);

        hratio_tot->SetFillStyle(3002); 
        hratio_tot->SetFillColor(kGray+1);
        hratio_tot->SetLineColor(kGray+1); 
        hratio_tot->SetMarkerColor(kGray+1);
        hratio_tot->SetMarkerStyle(20);
        hratio_tot->SetMarkerSize(0);

    // Upper plot will be in pad1
        TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
        pad1->SetTopMargin(0.15);
        pad1->SetRightMargin(0.05); 
        pad1->SetLeftMargin(0.12); 
        pad1->SetBottomMargin(0.05); 
        pad1->Draw();             // Draw the upper pad: pad1
        pad1->cd();               // pad1 becomes the current pad
        float ymax = 1.2*hpp_nom->GetMaximum();
        if(hPbPb_nom->GetMaximum()>hpp_nom->GetMaximum()) ymax = 1.2*hPbPb_nom->GetMaximum();
        
        // hPbPb_stat->Draw("AP5");
        
        hPbPb_tot->Draw("AP5");
        hPbPb_sys->Draw("P5");
        // hpp_stat->Draw("P5");
        
        hpp_tot->Draw("P5");
        hpp_sys->Draw("P5");
        hPbPb_nom->Draw("SAME_E1_][P0");
        hpp_nom->Draw("SAME_E1_][P0");

        hPbPb_tot->SetMaximum(ymax);
        hPbPb_tot->GetXaxis()->SetLabelSize(0);
        hpp_sys->GetXaxis()->SetLabelSize(0);
        hPbPb_tot->GetXaxis()->SetTitleOffset(999999);
        hpp_sys->GetXaxis()->SetTitleOffset(999999);
        hPbPb_tot->GetXaxis()->SetRangeUser(hPbPb_nom->GetXaxis()->GetBinLowEdge(1),hPbPb_nom->GetXaxis()->GetBinUpEdge(hPbPb_nom->GetNbinsX()));
        
        float leg_x1 = 0.6;
        float leg_y1 = 0.55;
        float leg_x2 = 0.85;
        float leg_y2 = 0.82;
        l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
        l->SetFillStyle(0);
        l->SetFillColor(0);
        l->SetLineColor(0);
        l->SetTextSize(0.045);
        l->SetTextFont(42);

        l->AddEntry(hPbPb_nom, "PbPb stat. uncert", "lep");
        l->AddEntry(hPbPb_sys, "PbPb sys. uncert", "f");
        l->AddEntry(hPbPb_tot, "PbPb total(stat. + sys.)", "f");
        l->AddEntry(hpp_nom, "pp stat. uncert", "lep");
        l->AddEntry(hpp_sys, "pp sys. uncert", "f");
        l->AddEntry(hpp_tot, "pp total(stat. + sys.)", "f");

        // l->AddEntry(hPbPb_nom, "MatInvert stat. uncert", "lep");
        // l->AddEntry(hPbPb_sys, "MatInvert sys. uncert", "f");
        // l->AddEntry(hPbPb_tot, "MatInvert total(stat. + sys.)", "f");
        // l->AddEntry(hpp_nom, "D'Agostini stat. uncert", "lep");
        // l->AddEntry(hpp_sys, "D'Agostini sys. uncert", "f");
        // l->AddEntry(hpp_tot, "D'Agostini total(stat. + sys.)", "f");
        l->Draw();

        TLatex latex;
        latex.SetTextSize(0.05);
        latex.DrawLatexNDC(0.12,0.9,"CMS #it{#bf{Preliminary}}");
        latex.DrawLatexNDC(0.55,0.9,"PbPb 1.69 nb^{-1}, pp 300.6 pb^{-1} (5.02 TeV)");
        latex.SetTextSize(0.045);
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Cent. 0-30%");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"#gamma p_{T}>100 GeV,x_{J}>0.4,|#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi");
        if(label.Contains("Rg")){
            leg_y1-=0.08;
            latex.DrawLatexNDC(leg_x1,leg_y1,Form("PbPb untagged = %4.2f%%",PbPb_untagged*100));
            // latex.DrawLatexNDC(leg_x1,leg_y1,Form("MatInvert untagged = %4.2f%%",PbPb_untagged*100));
            leg_y1-=0.08;
            latex.DrawLatexNDC(leg_x1,leg_y1,Form("pp untagged = %4.2f%%",pp_untagged*100));
            // latex.DrawLatexNDC(leg_x1,leg_y1,Form("D'Agostini untagged = %4.2f%%",pp_untagged*100));
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

        hratio->Draw("E1P0");
        // hratio_stat->Draw("SAME_P5");
        hratio_tot->Draw("SAME_P5");
        hratio_sys->Draw("SAME_P5");
        hratio->Draw("SAME_E1_][P0");
        hratio->SetMinimum(0.5);
        hratio->SetMaximum(1.5);

        // Y axis ratio plot settings
            hratio->GetYaxis()->SetTitle("#frac{PbPb}{pp}   ");
            hratio->GetYaxis()->SetNdivisions(-4);
            hratio->GetYaxis()->SetTitleSize(0.14);
            hratio->GetYaxis()->SetTitleOffset(0.32);
            hratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
            hratio->GetYaxis()->SetLabelSize(15);
            
        // X axis ratio plot settings
            hratio->GetXaxis()->SetTitleSize(0.14);
            hratio->GetXaxis()->SetTitleOffset(1.0);
            hratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
            hratio->GetXaxis()->SetLabelSize(15);
        
        if(label.Contains("Rg")){
            hratio->GetXaxis()->SetTitle("R_{g}");
            hPbPb_tot->GetYaxis()->SetTitle("1/N_{jet} dN/dR_{g}");
            hPbPb_tot->SetMinimum(0.0);
            hPbPb_tot->SetMaximum(12.0);
        }
        else{
            hratio->GetXaxis()->SetTitle("Girth ");
            hPbPb_tot->GetYaxis()->SetTitle("1/N_{jet} dN/dg");
            hPbPb_tot->SetMinimum(0.0);
            hPbPb_tot->SetMaximum(24.0);
        }

        // hratio->GetXaxis()->SetTitle(hPbPb_nom->GetXaxis()->GetTitle());
        // hPbPb_stat->GetYaxis()->SetTitle(hPbPb_nom->GetYaxis()->GetTitle());
   
    // Y axis upper plot settings
        hPbPb_tot->GetYaxis()->SetTitleSize(18);
        hPbPb_tot->GetYaxis()->SetTitleFont(43);
        hPbPb_tot->GetYaxis()->SetTitleOffset(1.0);
        hPbPb_tot->GetYaxis()->SetLabelSize(0.05);
        // hPbPb_nom->GetYaxis()->SetTitleSize(15);
        // hPbPb_nom->GetYaxis()->SetTitleFont(43);
        // hPbPb_nom->GetYaxis()->SetTitleOffset(1.5);
        // hPbPb_nom->GetYaxis()->SetLabelSize(0.05);

        // hPbPb_stat->GetYaxis()->SetTitleSize(15);
        // hPbPb_stat->GetYaxis()->SetTitleFont(43);
        // hPbPb_stat->GetYaxis()->SetTitleOffset(1.5);
        // hPbPb_stat->GetYaxis()->SetLabelSize(0.05);

    gPad->Update();

    hPbPb_nom->Write("",TObject::kOverwrite);
    hPbPb_sys->Write("",TObject::kOverwrite);
    hPbPb_tot->Write("",TObject::kOverwrite);
    hpp_nom->Write("",TObject::kOverwrite);
    hpp_sys->Write("",TObject::kOverwrite);
    hpp_tot->Write("",TObject::kOverwrite);
    hratio->Write("",TObject::kOverwrite);
    hratio_sys->Write("",TObject::kOverwrite);
    hratio_tot->Write("",TObject::kOverwrite);

    c.SaveAs("Overlay_ppPbPb/"+label+".png"); 
    c.SaveAs("Overlay_ppPbPb/"+label+".root"); 
    c.Write(label,TObject::kOverwrite);

    fout->Close();
    
}

/*
int main(int argc, char* argv[]){

    // gROOT->SetBatch();
    output_path = "./Overlay_ppPbPb/";  //! Defined in header 
    label = "tmp_label";                //! Defined in header
    gErrorIgnoreLevel = kFatal;
    TString DIR = output_path;
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    TString temphistname = (TString)argv[argc-2];
    
    if(argc%2!=0 && argc>=7 && !temphistname.EndsWith(".root")){  // last entry is the histogram label string
        std::vector<TH1F*> h;
        std::vector<TString>hname;
        label = (TString)argv[argc-1];
        TString hlabel = (TString)argv[argc-2]; //+"_"+centstring;

        for(int i=1; i<argc-2;i+=2){
            TFile *f;
            TString temppath = (TString)argv[i];
            TString templabel = (TString)argv[i+1];
            if(!temppath.EndsWith(".root")){
                printf("\n<file> Not a Root file\n");
                printf("Run with \n ./overlay_pp_PbPb <file1> <label1> <file2> <label2> <histname> <label>\n");
                return -1;
            } 
            f = TFile::Open(temppath);
            // TCanvas* ctemp = (TCanvas*)f->Get(hlabel);
            // TList* listtemp = (TList*)ctemp->GetListOfPrimitives();
            // THStack* stacktemp = (THStack*)listtemp->At(1);
            // TList* listtemp_hist = (TList*)stacktemp->GetHists();
            TH1F* htemp = (TH1F*)f->Get(hlabel);
            h.push_back((TH1F*)htemp->Clone());
            hname.push_back(templabel);
            std::cout<<"Argument "<<i<<" = "<<temppath<<std::endl;
            std::cout<<"Argument "<<i+1<<" = "<<templabel<<std::endl;
        }
        std::cout<<std::endl;
        hname.push_back("#Delta #phi");
        hname.push_back("#frac{1}{N}#frac{dN}{d #Delta #phi}");    //
        hname.push_back(hlabel);
        // Signal Selection
        std::vector<TString>sel = {" ","PbPb 2018(0-30%), pp 2017",
        "Anti-#it{k}_{T} #it{R}=0.2","z_{cut}=0.2"};// "#gamma p_{T}>100, Jet p_{T}>40, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi"

        TFile *fout;
        fout = new TFile(DIR+"/Output_"+label+".root", "recreate");
        fout->cd();

        // sel.insert(std::end(sel),std::begin(sigsel),std::end(sigsel));  
        // sel.push_back("Sig Reg - Corrected");
        Plot_hist(h,hname,"left_label_log_norm",sel);
        fout->Close();
    }
    else{
        printf("Run with \n ./overlay_pp_PbPb <file1> <label1> <file2> <label2> <histname> <label>\n");
    }

    return 0;
}
*/