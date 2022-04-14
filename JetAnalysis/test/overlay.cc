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
#include "TFile.h"         // needed for TFile

#include <iostream>         // needed for I/O

const std::vector<int> min_cent = { 0,  60,   0,  0, 20,  60, 100};
const std::vector<int> max_cent = {60, 180, 180, 20, 60, 100, 180};
const std::size_t ncent = min_cent.size();
TString label="";
TString centstring="";
TString output_path = "./";

void Plot_hist(std::vector<TH1F*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void Plot_hist2D(std::vector<TH2F*> hist,std::vector<TString> histname,TString dopt="colz",std::vector<TString> eopt={"end"});

void overlay_stack(std::vector<TH1F*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void overlay(std::vector<TH1F*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void overlay_stack(std::vector<TH1F*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
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
    const std::vector<int> colarray  = { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20,21,22,23,29,34,39};

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
        if(opt.Contains("norm")){
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
    std::cout<<"max 0 = "<<hist[0]->GetMaximum()<<"   max hs = "<<hs->GetMaximum()<<"   ymax = "<<ymax<<std::endl;
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
    rp1->GetLowerRefGraph()->SetMaximum(1.5);
    rp1->GetLowerRefGraph()->SetMinimum(0.5);
    rp1->GetLowerRefYaxis()->SetTitle("Ratio");
    if(!opt.Contains("log"))
        hs->SetMaximum(ymax*1.1);
    if(opt.Contains("label")){
        // rp1->GetLowerRefXaxis()->SetTitle(histname.at(histname.size()-2));
        rp1->GetUpperRefYaxis()->SetTitle(histname.at(histname.size()-1));
        hs->GetXaxis()->SetTitle(histname.at(histname.size()-1));
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
    c.SaveAs(output_path + "/OverlayPlots/"+histname.back()+"_"+centstring+".png");
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
    const std::vector<int> colarray  = { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20,21,22,23,29,34,39};

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
    TH1F *hratio;
    for(std::size_t ihist=1; ihist<hist.size();ihist++){
        hratio = (TH1F*)hist[ihist]->Clone(histname[ihist]);
        hratio->SetLineColor(colarray[ihist]);
        hratio->SetMarkerColor(colarray[ihist]);
        hratio->SetMarkerStyle(markarray[ihist]);   

        hratio->SetMinimum(0.5);  // Define Y ..
        hratio->SetMaximum(1.5); // .. range

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
        hratio->GetXaxis()->SetTitle(histname.at(histname.size()-2));
        hist[0]->GetYaxis()->SetTitle(histname.at(histname.size()-1));
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
    c.SaveAs(output_path + "/OverlayPlots/"+histname.back()+"_"+centstring+".png");
    std::cout<<histname.back()<<"_"<<centstring<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}


void Plot_hist(std::vector<TH1F*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "OBJ" = optional stuff for later? 

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(opt.Contains("log")) gStyle->SetOptLogy(1);
    
    TString drawopt = "nostackE][P0"; 
    const std::vector<int> colarray  = { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20,21,22,23,29,34,39};

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
        if(opt.Contains("flow"))
            hist[ihist]->GetXaxis()->SetRange(0,hist[ihist]->GetNbinsX()+2);
        hs.Add(hist[ihist]);      
        l->AddEntry(hist[ihist], histname[ihist], "lep");
    }
    hs.Draw(drawopt);
    if(opt.Contains("label")){
        hs.GetXaxis()->SetTitle(histname.at(histname.size()-2));
        hs.GetYaxis()->SetTitle(histname.at(histname.size()-1));
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
    c.SaveAs(output_path + "/OverlayPlots/"+histname.back()+"_"+centstring+".png");
    std::cout<<histname.back()<<"_"<<centstring<<" has been saved"<<std::endl;
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
    const std::vector<int> colarray  = { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20,21,22,23,29,34,39};

    TCanvas c;
    // TLegend *l;
    float leg_x1 = 0.75;
    float leg_y1 = 0.7;
    float leg_x2 = 0.85;
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
            latex.DrawLatexNDC(0.5,0.92,eopt[0]);
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
    c.SaveAs(output_path + "/OverlayPlots/"+histname.back()+"_"+centstring+".png");
    std::cout<<histname.back()<<"_"<<centstring<<" has been saved"<<std::endl;
    }
    /*
    
    
    delete l;*/
}


int main(int argc, char* argv[]){

    gROOT->SetBatch();
    gErrorIgnoreLevel = kFatal;
    
    if(argc%2!=0 && argc>=7){  // last entry is the histogram label string
        TString DIR = output_path + "OverlayPlots";
        TString makedir = "mkdir -p " + DIR;
        const char *mkDIR = makedir.Data();
        gSystem->Exec(mkDIR);

        std::vector<TH1F*> h;
        std::vector<TString>hname;
        centstring = argv[argc-1]; 
        Int_t icent = centstring.Atoi();
        label = (TString)argv[argc-2];
        TString hlabel = label +"_"+centstring;

        for(int i=1; i<argc-2;i+=2){
            TFile *f;
            TString temppath = (TString)argv[i];
            TString templabel = (TString)argv[i+1];
            if(!temppath.EndsWith(".root")){
                printf("\n<file> Not a Root file\n");
                printf("Run with \n ./overlay <file1> <label1> <file2> <label2> <histname> <centrality_index>\n");
                return -1;
            } 
            f = TFile::Open(temppath);
            TH1F* htemp = (TH1F*)f->Get(hlabel);
            h.push_back(htemp);
            hname.push_back(templabel);
            std::cout<<"Argument "<<i<<" = "<<temppath<<std::endl;
            std::cout<<"Argument "<<i+1<<" = "<<templabel<<std::endl;
        }
        hname.push_back(label);
        // Signal Selection
        std::vector<TString>sel = {"#gamma p_{T}>100, Jet p_{T}>40, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",Form("|#eta|<1.44,%d-%d%%",min_cent[icent]/2,max_cent[icent]/2),"H/E<0.1372"};
        std::vector<TString>sigsel ={"SumIso<1.4549","#sigma_{#eta#eta}<0.0104"};      
        std::vector<TString>bkg1_sel = {"SumIso<1.4549","#sigma_{#eta#eta}>=0.0104"}; 
        std::vector<TString>bkg2_sel = {"10<SumIso<=20","#sigma_{#eta#eta}<0.0104"};  

        sel.insert(std::end(sel),std::begin(sigsel),std::end(sigsel));  
        // sel.push_back("Sig Reg - Corrected");
        overlay(h,hname,"rightflow",sel);
    }
    else if(argc%2==0){ // Loop over all histograms in the root file
        printf("To be implemented");
    }
    else{
        printf("Run with \n ./overlay <file1> <label1> <file2> <label2> <histname> <centrality_index>\n");
    }

    return 0;
}