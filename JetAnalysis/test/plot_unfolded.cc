#include <TSystem.h>        // needed for gSystem
#include <TStyle.h>         // needed for gStyle 
#include <TChain.h>         // needed for TChain
#include "TROOT.h"          // needed for gROOT
#include <TError.h>         // needed for gErrorIgnoreLevel
#include <TVector2.h>       // needed for TVector2::Phi_mpi_pi        
#include <TH2.h>            // needed fror TH1 and TH2
#include <TLegend.h>        // needed for Legend
#include <TCanvas.h>        // needed for Canvas
#include <TMath.h>          //! needed for floating values in plots for some reason
#include <THStack.h>        // needed for THStack
#include <TLatex.h>         // needed for TLatex
#include <TFile.h>          // needed for TFile

#include <iostream>         // needed for I/O

const std::vector<int> min_cent = { 0,  60,   0,  0, 20,  60, 100};
const std::vector<int> max_cent = {60, 180, 180, 20, 60, 100, 180};
const std::size_t ncent = min_cent.size();
TString label="";
TString output_path = "./";

void Plot_hist(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void Plot_hist2D(std::vector<TH2D*> hist,std::vector<TString> histname,TString dopt="colz",std::vector<TString> eopt={"end"});

void overlay(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void plot_unfolded(TString file, TString fileother, int flagdummy=1){
    // file input - flag 0-19 reserved for different MC, flag>=20 for data
    // fileother is used for 2nd MC to calculate priors - otherwise pass same input to both
    // flagdummy == 0 -> Data Corrected
    // flagdummy == 1 -> MC Det level test or greater than 2
    // flagdummy == 2 -> MC efficiency?
    // Range [1,-1] -> All Bins other than Underflow and Overflow

    int bintruexj1 = 1;     
    int bintruexj2 = 2;
    int bintruerg1 = 1;
    int bintruerg2 = 4;
    int iter_ref = 5;    
    
    gROOT->SetBatch();
    gErrorIgnoreLevel = kFatal;
    TString DIR = output_path + "OutputUnfolded_"+label+"/";
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    // ----------------------------------------------------------------------------------------------------------------
    // Histograms

        TH2D* raw;
        TH2D* smeared;
        TH1D* raw1;
        TH1D* ptraw1;

        TH1D* ptdet;
        TH2D* det;
        TH2D* htrue;
        TH1D* htrue1;
        TH2D* htrue_ineff;
        TH2D* pthtrue;
        TH1D* pthtrue1;
        TH1D* smeared1;

        TH2D* unfold2d[20];
        TH2D* fold2d;
        TH1D* unfold[20];
        TH1D* unfold_extreme1[20];
        TH1D* unfold_extreme2[20];
        TH1D* fold[20];

        TH1D* ptunfold[20];
        TH1D* ptfold[20];
        TH1D* denom;
        TH1D* denom1;
        TH1D* denom2;
        TH2D* data;
        TH1D* data1;

        TH1D* denompt;

        TFile* f = new TFile(file);
        TFile* fprior = new TFile(fileother);
        // std:stringstream ssn;
        // ssn << "correff"<< bintruexj1<<"-"<<bintruexj2;           
    
        if(flagdummy>=1) raw=(TH2D*)f->Get("smeared");
        if(flagdummy==0) raw=(TH2D*)f->Get("raw_corrected");
        smeared=(TH2D*)f->Get("smeared");
        data=(TH2D*)f->Get("raw_corrected"); 
        raw1=(TH1D*)raw->ProjectionX("raw1",1,-1);
        smeared1=(TH1D*)smeared->ProjectionX("smeared1",1,1);
        ptraw1=(TH1D*)raw->ProjectionY("ptraw1",1,-1);
        data1=(TH1D*)data->ProjectionX("data1",1,1);
            
        htrue=(TH2D*)f->Get("truef");
        if(flagdummy==2) htrue=(TH2D*)f->Get("true");
        htrue1=(TH1D*)htrue->ProjectionX("true1",bintruexj1,bintruexj2);
        htrue_ineff=(TH2D*)f->Get("true");

        TH1D* eff=htrue_ineff->ProjectionX("eff",bintruexj1,bintruexj2);
        TH1D* effdenom=htrue->ProjectionX("effdenom",bintruexj1,bintruexj2);
        eff->Divide(effdenom);
        TH1D* effxj=htrue_ineff->ProjectionY("effxj",bintruerg1,bintruerg2);
        TH1D* effdenomxj=htrue->ProjectionY("effdenomxj",bintruerg1,bintruerg2);
        effxj->Divide(effdenomxj);

        pthtrue=(TH2D*)f->Get("truef");
        if(flagdummy==2) pthtrue=(TH2D*)f->Get("true");
        pthtrue1=(TH1D*)pthtrue->ProjectionY("true1pt",bintruerg1,bintruerg2);

        htrue1->Scale(1./htrue1->Integral(1,-1));                       
        htrue1->Scale(1,"width");

        pthtrue1->Scale(1./pthtrue1->Integral(1,-1));                       
        pthtrue1->Scale(1,"width");
    // -------- End Histograms
    // ----------------------------------------------------------------------------------------------------------------
    // Iteration Loop

    for(Int_t j=0;j<15;j++){
        unfold2d[j]=(TH2D*)f->Get(Form("Bayesian_Unfoldediter%d.root",j+1));
        fold2d=(TH2D*)f->Get(Form("Bayesian_Foldediter%d.root",j+1));
        unfold[j]=(TH1D*)unfold2d[j]->ProjectionX(Form("unfold%d",j),bintruexj1,bintruexj2,"");
        unfold_extreme1[j]=(TH1D*)unfold2d[j]->ProjectionX(Form("unfold_extreme1%d",j),bintruexj1,bintruexj2,"");
        unfold_extreme2[j]=(TH1D*)unfold2d[j]->ProjectionX(Form("unfold_extreme2%d",j),bintruexj1,bintruexj2,"");
        fold[j]=(TH1D*)fold2d->ProjectionX(Form("fold%d",j),1,-1,"");
        fold[j]->Divide(raw1);

        ptunfold[j]=(TH1D*)unfold2d[j]->ProjectionY(Form("ptunfold%d",j),bintruerg1,bintruerg2);
        ptfold[j]=(TH1D*)fold2d->ProjectionY(Form("ptfold%d",j),1,-1,"");
        ptfold[j]->Divide(ptraw1); 

        if(flagdummy!=2)unfold[j]->Divide(eff);
        unfold[j]->SetLineColor(j+1);
        fold[j]->SetLineColor(j+1);
        unfold[j]->Scale(1./unfold[j]->Integral(1,-1));
        unfold[j]->Scale(1,"width");
        if(flagdummy!=2)ptunfold[j]->Divide(effxj); 
        ptunfold[j]->Scale(1./ptunfold[j]->Integral(1,-1));
        ptunfold[j]->SetLineColor(j+1);
        ptfold[j]->SetLineColor(j+1);
        ptunfold[j]->Scale(1,"width");
    }

    TH1D* eff1=htrue_ineff->ProjectionX("eff1",bintruexj1,bintruexj2);
    TH1D* effdenom1=htrue->ProjectionX("effdenom1",bintruexj1,bintruexj2);
    eff1->Divide(effdenom1);

    std::cout<<"eff1 = "<<eff1->GetEntries()<<std::endl;

    TH1D* eff2=htrue_ineff->ProjectionX("eff2",bintruexj1,bintruexj2);
    TH1D* effdenom2=htrue->ProjectionX("effdenom2",bintruexj1,bintruexj2);
    eff2->Divide(effdenom1);

    denom=(TH1D*)unfold[iter_ref]->Clone("denom");   
    denom1=(TH1D*)unfold_extreme1[iter_ref]->Clone("denom1"); 
    denom2=(TH1D*)unfold_extreme2[iter_ref]->Clone("denom2"); 

    denom1->Divide(eff1);
    denom2->Divide(eff2);
    denom1->Scale(1./denom1->Integral(1,-1));
    denom1->Scale(1,"width");


    denom2->Scale(1./denom2->Integral(1,-1));
    denom2->Scale(1,"width");
	      
    // ---------------- crossing of reg and statistical uncerts
    TH1D *def1, *def2, *def3, *def4;
    TH2D *itera, *iterad, *iterau, *iterp;
    Double_t errprior, errreg1, errreg2, errreg, errstat, errtot;
    TH1D *histotot(0);
    TH1D *historeg(0);
    TH1D *histoprior(0);
    TH1D *histostat(0);
    histotot=new TH1D("histotot","histot",12,0,15);
    historeg=new TH1D("historeg","historeg",12,0,15);
    histoprior=new TH1D("histoprior","histoprior",12,0,15);
    histostat=new TH1D("histostat","histostat",12,0,15);

    // Error Calculation

    for(Int_t k=2;k<13;k++){
	   
        itera=(TH2D*)f->Get(Form("Bayesian_Unfoldediter%d.root",k));
        iterad=(TH2D*)f->Get(Form("Bayesian_Unfoldediter%d.root",k-1));
        iterau=(TH2D*)f->Get(Form("Bayesian_Unfoldediter%d.root",k+2));
        iterp=(TH2D*)fprior->Get(Form("Bayesian_Unfoldediter%d.root",k));

        def1=(TH1D*)itera->ProjectionX(Form("def1_%i",k),bintruexj1,bintruexj2);
        def2=(TH1D*)iterad->ProjectionX(Form("def2_%i",k),bintruexj1,bintruexj2);
        def3=(TH1D*)iterau->ProjectionX(Form("def3_%i",k),bintruexj1,bintruexj2);
        def4=(TH1D*)iterp->ProjectionX(Form("def4_%i",k),bintruexj1,bintruexj2);

        errprior=0;
        errreg1=0;
        errreg2=0;
        errreg=0;
        errstat=0;
        errtot=0;

        for(Int_t i=1;i<=def1->GetNbinsX();i++){
            errprior=errprior+TMath::Abs(def4->GetBinContent(i)-def1->GetBinContent(i))/def1->GetBinContent(i);
            errreg1=TMath::Abs(def2->GetBinContent(i)-def1->GetBinContent(i));
            errreg2=TMath::Abs(def3->GetBinContent(i)-def1->GetBinContent(i));
            errreg=errreg+TMath::Max(errreg1,errreg2)/def1->GetBinContent(i);
            errstat=errstat+def1->GetBinError(i)/def1->GetBinContent(i);
            errtot=TMath::Sqrt(errprior*errprior+errreg*errreg+errstat*errstat);
        }

        histotot->SetBinContent(k,errtot);
        historeg->SetBinContent(k,errreg);
        histoprior->SetBinContent(k,errprior);
        histostat->SetBinContent(k,errstat);
    }

    std::vector<TString>sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, Anti-#it{k}_{T} #it{R}=0.2",100.0,40.0),"Cent. 0-30%","Bayes Unfolded","z_{cut}=0.2","0<x_{J,#gamma}<0.6"};    
    std::vector<TH1D*> hist_input;
    std::vector<TString> histname_input={"denom"};
    sel.push_back("end");
    sel.push_back("noStackHIST");
    Plot_hist({histotot,historeg,histostat,histoprior},{"Total","Regularization","Statistical","Prior","Iterations","Summed Errors","SumErrors"},"rightlabel_opt",sel);
    // Iterations vs Rg plot
        if(flagdummy==0){hist_input.push_back(denom);}
        else{hist_input.push_back(htrue1);}
        for(Int_t iter=0;iter<15;iter++){
            hist_input.push_back(unfold[iter]);
            histname_input.push_back(Form(" iter %d",iter+1));
        }
        histname_input.push_back("R_{g}");
        if(flagdummy==0){histname_input.push_back(Form("Unfolded/Iter %i",iter_ref));}
        else{histname_input.push_back(Form("Unfolded/true"));}
        histname_input.push_back("Unfolded_IterVsRg");
    Plot_hist(hist_input,histname_input,"eff_left_label",sel);
    // Refolded Rg plot
        hist_input={};
        histname_input={};
        for(Int_t iter=0;iter<15;iter++){
            hist_input.push_back((TH1D*)fold[iter]->Clone());
            histname_input.push_back(Form(" iter %d",iter+1));
        }
        histname_input.push_back("R_{g}");
        histname_input.push_back(Form("Folder/Raw"));
        histname_input.push_back("Refolded_IterVsRg");
    Plot_hist(hist_input,histname_input,"left_label",sel);
    // Plot_hist({histotot,historeg,histostat,histoprior},{"Total","Regularization","Statistical","Prior","Iterations","Summed Errors","SumErrors"},"rightlabel",{Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, Anti-#it{k}_{T} #it{R}=0.2",100.0,40.0),"Cent. 0-30%","z_{cut}=0.2","0<x_{J,#gamma}<0.6"});

}

void Plot_hist(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "opt" = drawopt is last element of eopt

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(opt.Contains("log")) gStyle->SetOptLogy(1);
    
    TString drawopt = "nostackE][P0"; 
    if(opt.Contains("opt"))
        drawopt = eopt.back();
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
    c.SaveAs(output_path + "/OutputUnfolded_"+label+"/"+histname.back()+".png");
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}

void Plot_hist2D(std::vector<TH2D*> hist,std::vector<TString> histname,TString dopt,std::vector<TString> eopt){
    // dopt contains draw options

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(eopt.back().Contains("log")) gStyle->SetOptLogz(1);
    
    TString drawopt = dopt; 

    TCanvas c;
    // TLegend *l;
    float leg_x1 = 0.7;
    float leg_y1 = 0.7;
    float leg_x2 = 0.8;
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
            latex.DrawLatexNDC(0.4,0.92,eopt[0]);
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
        c.SaveAs(output_path + "/OutputUnfolded_"+label+"/"+histname[ihist]+".png");
        std::cout<<histname[ihist]<<" has been saved"<<std::endl;
    }

    if(eopt.back().Contains("log")) gStyle->SetOptLogz(0);
    /*
    delete l;*/
}


void overlay(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // Based on the old Ratio Plot script from https://root.cern/doc/master/ratioplotOld_8C.html

    // opt contains options
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
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
    
    TString drawopt = "E][P0"; 
    if(opt.Contains("opt"))
        drawopt = eopt.back();
    const std::vector<int> colarray  = { 1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606,
                                       1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41,
                                        20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};
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
    else
        hist[0]->SetMaximum(ymax*2);
        
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
    c.SaveAs(output_path + "/OutputUnfolded_"+label+"/"+histname.back()+".png");
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}

int main(int argc, char* argv[]){

    // printf("argc = %d\n",argc);
    // printf("argv = %s\n",argv[0]);
    if(argc==6){
        output_path = argv[1];
        label = argv[2];
        plot_unfolded(argv[3],argv[4],atoi(argv[5]));
    }
    else{
        printf("Run with \n ./plot_unfolded <output dir> <label> <file1> <file2> <flag>\n");
    }

    return 0;
}