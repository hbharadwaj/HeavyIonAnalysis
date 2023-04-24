// overlay_Data_true({"Uncertainty/OutputCombined/Data_0_30_Jan_26_Rg_updatedMC_bin_2.root","Uncertainty/OutputPlots_QCDPhoton_jets_JER_nom/Output_QCDPhoton_jets.root","Uncertainty/OutputPlots_Pythia_pthat80_refparton_jets/Output_Pythia_pthat80_refparton_jets.root","~/pp_analysis/Analysis/OutputPlots/OutputPlots_pp_Pyquen_jets/Output_pp_Pyquen_jets.root"},{"PbPb Data 2018","Pythia8 nominal-true","Pythia8 q/g Modified-true","Pyquen-true","h_Rg_truef_1"},"OverlayData/Output_0_30_Rg_true_updatedMC.root","Data_0_30_Jan_26_Rg_updatedMC_bin_2_nom")

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
#include <TLatex.h>         // needed for TLatex
#include "TRatioPlot.h"     // needed for RatioPlot
#include "TFile.h"         // needed for TFile

#include <iostream>         // needed for I/O

const std::vector<int> min_cent = { 0,  60,   0,  0, 20,  60, 100};
const std::vector<int> max_cent = {60, 180, 180, 20, 60, 100, 180};
const std::size_t ncent = min_cent.size();
const float min_pho_et = 100;
const float cut_HoverE = 0.0233;    // 0.009731;
const float cut_SIEIE  = 0.01;      // 0.009905;
const float cut_SumIso = -0.479;    //-0.014755;
const float min_jet_pt = 40;
TString label="";
TString centstring="Cent. 0-30%";
TString output_path = "./OverlayData/";
TCanvas c;
TLegend *l;

void Plot_hist(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});
void Plot_hist_err(std::vector<TH1D*>,std::vector<TGraphAsymmErrors*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void overlay_Data_true(std::vector<TString>file_list,std::vector<TString>label_list,TString out_filepath, TString hname){
    if(label_list.size()!=(file_list.size()+1)){
        printf("Run with \n root -l\n .L overlay_Data_true.cc \n overlay_Data_true({<path_to_files>},{<labels>,out_hname},out_filepath,hname)\n");
        return; //"h_Rg_det_0"
    }
    gErrorIgnoreLevel = kFatal;
    TString DIR = output_path;
    output_path = DIR;
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    TFile *f_out = new TFile(out_filepath, "recreate");
    TDirectory *target = gDirectory;

    label = label_list.back();
    TFile *f_Data = TFile::Open(file_list[0]);
    TH1D* hnom = (TH1D*)f_Data->Get(Form("%s",hname.Data()));
    TGraphAsymmErrors *stat_uncert = (TGraphAsymmErrors*)f_Data->Get("stat_uncert");
    TGraphAsymmErrors *sys_uncert = (TGraphAsymmErrors*)f_Data->Get("sys_uncert");
    stat_uncert->SetName("stat_uncert");
    sys_uncert->SetName("sys_uncert");
    if(hnom && stat_uncert && sys_uncert)
        std::cout<<"Got Data"<<std::endl;

    std::vector<TH1D*> hist_input;
    std::vector<TString> histname_input;
    hist_input.push_back((TH1D*)hnom->Clone());
    histname_input.push_back(label_list[0]);
    for(int i=1;i<file_list.size();i++){
        TFile *f = TFile::Open(file_list[i]);
        TH1D* htemp = (TH1D*)f->Get(Form("%s",label.Data()));
        target->cd();
        // htemp->Write(label_list.back()+"_"+label_list[i],TObject::kWriteDelete);
        // htemp->Scale(1.0/htemp->Integral(1,htemp->GetNbinsX()-1),"width");
        hist_input.push_back((TH1D*)htemp->Clone());
        // hist_input.push_back((TH1D*)hnom->Clone(label_list[i]));
        histname_input.push_back(label_list[i]);
        std::cout<<"Got "<<label_list[i]<<std::endl;
    }
    std::cout<<"hname = "<<hname<<std::endl;
    if(hname.Contains("Rg")){
        std::cout<<"Inside Rg "<<std::endl;
        std::cout<<"Nominal Integral = "<<hnom->Integral()<<"\n";
        hnom->SetMinimum(0.0);
        hnom->SetMaximum(12.0);
        hnom->SetTitle(";R_{g};1/N_{jet} dN/dR_{g}");
        histname_input.push_back("R_{g}");
        histname_input.push_back("1/N_{jet} dN/dR_{g}");
    }
    else{
        hnom->SetMinimum(0.0);
        hnom->SetMaximum(24.0);
        hnom->SetTitle(";Angularity (girth);1/N_{jet} dN/dAngularity");
        histname_input.push_back("Angularity (girth)");
        histname_input.push_back("1/N_{jet} dN/dAngularity");
    }
    histname_input.push_back("R_{g}");
    histname_input.push_back("1/N_{jet} dN/dR_{g}");
    histname_input.push_back("Overlay_"+hname);
    std::vector<TString>sel = {"",centstring,Form("#gamma p_{T}>%.0f, x_{J}>%.1f,|#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.40)}; 
    target->cd();
    std::cout<<"Before Err Plot function \n";
    Plot_hist_err({hnom},{sys_uncert},{"sys. uncert","R_{g}","1/N_{jet} dN/dR_{g}",label+"_combined"},"right_label",sel); // stat_uncert,  "stat. uncert",
    //  Angularity(g)  1/N_{jet} dN/dg
    std::cout<<"Plot Data "<<std::endl;
    Plot_hist(hist_input,histname_input,"right_label",sel);
    // c.SaveAs(output_path +histname_input.back()+".C");
    c.Write("Output_Overlay_data_true_MC");
    c.Draw();
    f_out->Close();
}

void Plot_hist_err(std::vector<TH1D*> hist,std::vector<TGraphAsymmErrors*> err_graph,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "leg" = DO NOT draw legend
    // "OBJ" = optional stuff for later? 

    if(hist.size()!=1){
        printf("\n Requires only 1 histogram with errors");
        return;
    }

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(opt.Contains("log")) gStyle->SetOptLogy(1);
    
    TString drawopt = "P2"; 

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
    const std::vector<int> colarray  = {kblue,kmagenta,kgreen,kviolet,kazure,korange,kcyan,kteal,kspring,kpink,kyellow,kmagenta,kviolet,kblue}; // kred,
    // const std::vector<int> colarray  = {2,2,9,9,kviolet,kazure,korange,kcyan,kteal,kspring,kpink,kyellow,kmagenta,kviolet,kblue};
    const std::vector<int> markarray = {25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};

    // TLegend *l;
    float leg_x1 = 0.55;
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
    l->SetTextSize(0.03);
    l->SetTextFont(42);

    std::cout<<"Inside Plot Hist Err\n";

    hist[0]->SetLineColor(1);
    hist[0]->SetMarkerColor(1);
    hist[0]->SetMarkerStyle(20);
    hist[0]->SetMarkerSize(0.2);
    hist[0]->Draw();

        for(std::size_t ihist=0; ihist<err_graph.size();ihist++){
        err_graph[ihist]->SetFillStyle(3001);
        err_graph[ihist]->SetFillColorAlpha(colarray[ihist],0.5);//(ihist%2)?0.8:0.1
        err_graph[ihist]->SetLineColor(colarray[ihist]);
        err_graph[ihist]->SetMarkerColor(colarray[ihist]);
        err_graph[ihist]->SetMarkerSize(0);
        
        if(opt.Contains("flow"))
            err_graph[ihist]->GetXaxis()->SetRange(0,hist[ihist]->GetNbinsX()+2);
        err_graph[ihist]->Draw((ihist==0)?"A"+drawopt:drawopt);      
        // err_graph[ihist]->Draw(drawopt);     
        l->AddEntry(err_graph[ihist], histname[ihist], "f");
    }
    if(opt.Contains("label")){
        hist[0]->GetXaxis()->SetTitle(histname.at(histname.size()-3));
        hist[0]->GetYaxis()->SetTitle(histname.at(histname.size()-2));
    }
    else{
        hist[0]->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
        hist[0]->GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());
    }
    if(!opt.Contains("leg"))
        l->Draw();


    TLatex latex;
    latex.SetTextSize(0.035);
    latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary}} PbPb 1.69 nb^{-1}(5.02 TeV)");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.41,0.92,eopt[0]);
        latex.DrawLatexNDC(0.78,0.92,eopt[1]);
    }    
    latex.SetTextSize(0.03);
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
    // c.SaveAs(output_path +histname.back()+".C");
    // c.Write(histname.back()+"_canv",TObject::kWriteDelete);
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    // delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}


void Plot_hist(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
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
    
    TString drawopt = "SAMEnostackE1][P0"; 
    if(opt.Contains("opt"))
        drawopt = eopt.back();
        
    const std::vector<int> colarray  = { 1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};

    // const std::vector<int> colarray  = { 1, 1, 632, 632, 600, 600, 616, 616, 419, 419,800,800, 425, 425, 898, 898,
    //                                    922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    // const std::vector<int> markarray = {4, 20, 25, 21, 26, 22, 32, 23, 30, 29, 28, 34,40,39,
    //                                     25, 21, 26, 22, 32, 23, 30, 29, 28, 34,40,39};*/

    // TCanvas c;
    // TLegend *l;    
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
    // l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    // l->SetFillStyle(0);
    // l->SetFillColor(0);
    // l->SetLineColor(0);
    // l->SetTextSize(0.025);
    // l->SetTextFont(42);

    THStack hs("hs","hs");

    for(std::size_t ihist=0; ihist<hist.size();){
        if(opt.Contains("eff")){
            if((ihist+1)>=hist.size()) break;
            hist[ihist+1]->SetLineColor(colarray[ihist]);
            hist[ihist+1]->SetMarkerColor(colarray[ihist]);
            hist[ihist+1]->SetMarkerStyle(markarray[ihist]);
            hist[ihist+1]->Divide(hist[ihist+1],hist[0],1,1);
            ihist++;
        }
        else{
            hist[ihist]->SetLineColor(colarray[ihist]);
            hist[ihist]->SetMarkerColor(colarray[ihist]);
            hist[ihist]->SetMarkerStyle(markarray[ihist]);
        }
        if(opt.Contains("norm_width")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2),"width");
        }
        else if(opt.Contains("norm")){
            hist[ihist]->Scale(1.0/hist[ihist]->Integral(0,hist[ihist]->GetNbinsX()+2));
        }
        if(opt.Contains("flow"))
            hist[ihist]->GetXaxis()->SetRange(0,hist[ihist]->GetNbinsX()+2);
        hs.Add(hist[ihist]);      
        l->AddEntry(hist[ihist], histname[ihist], "lep");
        if(!opt.Contains("eff")) ihist++;
    }
    hs.Draw(drawopt);
    
    if(opt.Contains("label")){
        hs.GetXaxis()->SetTitle(histname.at(histname.size()-3));
        hs.GetYaxis()->SetTitle(histname.at(histname.size()-2));
    }
    else{
        hs.GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
        hs.GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());
    }
    l->Draw();


    // TLatex latex;
    // latex.SetTextSize(0.035);
    // if(label.Contains("Data"))
    //     latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Preliminary}} PbPb 2018 Unfolded");
    // else
    //     latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Preliminary Simulation}} Unfolded");

    // if(eopt[0].Contains("Cent")){
    //     latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    // }
    // else if(eopt.size()>=2){
    //     latex.DrawLatexNDC(0.6,0.92,eopt[0]);
    //     latex.DrawLatexNDC(0.85,0.92,eopt[1]);
    // }    
    // latex.SetTextSize(0.025);
    // if(eopt.size()>2){
    //     for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
    //         if(opt.Contains("bcenter")){
    //             leg_y2+=0.05;
    //             latex.DrawLatexNDC(leg_x1,leg_y2,eopt[ind]);
    //         }
    //         else{
    //             leg_y1-=0.05;
    //             latex.DrawLatexNDC(leg_x1,leg_y1,eopt[ind]);
    //         }
    //     }
    // }
    gPad->Update();
    c.SaveAs(output_path +histname.back()+".C");
    c.Write(histname.back(),TObject::kWriteDelete);
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    // delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}

