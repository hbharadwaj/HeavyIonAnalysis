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
TString x_label = "dyn k_{T}";
TString y_label = "x_{J,#gamma}";

void Plot_hist(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void Plot_hist2D(std::vector<TH2D*> hist,std::vector<TString> histname,TString dopt="colz",std::vector<TString> eopt={"end"});

void overlay(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void plot_unfolded(TString file, TString fileother, int flagdummy=1){
    // Unfolding input contains - flag 0-19 for data, flag>=20 for different MC
    // fileother is used for 2nd MC to calculate priors - otherwise pass same input to both
    // flagdummy == 0 -> Data Corrected
    // flagdummy == 1 -> MC Det level test
    // flagdummy == 2 -> MC True at Det level
    // Range [1,-1] -> All Bins other than Underflow and Overflow

    const int bintrueY_min = 1;     
    const int bintrueY_max = 2;
    const int bintrueX_min = 1;
    const int bintrueX_max = 7;
    const int iter_ref = 5;    

    // inputs for Unfolding 
        const int bin_true_xj=3;
        const int bin_true_Rg=5;
        const int bin_true_angu=5;
        const int bin_true_dynkt=7;

        Double_t xjmin_true=0;
        Double_t xjmax_true=2;

        Double_t Rgmax_true=0.3;

        Double_t angumax_true=0.1;
        Double_t angumin_true=0.;

        Double_t dynktmax_true=12.0;
        Double_t dynktmin_true=0.;

        Double_t xJ_true_edges[bin_true_xj+1] = {xjmin_true, 0.6, 1.6, xjmax_true};
        Double_t Rg_true_edges[bin_true_Rg+1] = {-0.05, 0, 0.05, 0.1, 0.2, Rgmax_true};
        Double_t angu_true_edges[bin_true_angu+1] = {angumin_true, 0.02, 0.04, 0.06, 0.08, angumax_true};
        Double_t dynkt_true_edges[bin_true_dynkt+1] = {dynktmin_true, 1.0,2.0,3.0,4.0,5.0,8.0,dynktmax_true};
        Double_t xlabel_min,xlabel_max,ylabel_min,ylabel_max;

        if(x_label.Contains("dyn")){
            xlabel_min = dynkt_true_edges[bintrueX_min-1];
            xlabel_max = dynkt_true_edges[bintrueX_max];
        }
        else if(x_label.Contains("angu")){
            xlabel_min = angu_true_edges[bintrueX_min-1];
            xlabel_max = angu_true_edges[bintrueX_max];
        }
        else{   // Rg
            xlabel_min = Rg_true_edges[bintrueX_min-1];
            xlabel_max = Rg_true_edges[bintrueX_max];
        }
        ylabel_min = xJ_true_edges[bintrueY_min-1];
        ylabel_max = xJ_true_edges[bintrueY_max];
        
    
    gROOT->SetBatch();
    gErrorIgnoreLevel = kFatal;
    TString DIR = output_path + "OutputUnfolded_"+label+"/";
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    // ----------------------------------------------------------------------------------------------------------------
    // Histograms

        TH2D* raw;              //  Detector smeared - 0->Data : else ->MC
        TH2D* htrue;            //  MC - Gen level Cuts : 2-> Det level Cuts
        TH2D* htrue_ineff;      //  MC - Det level Cuts
        TH2D* unfold2d_iter;    //  Unfolded result - updated for each iteration
        TH2D* fold2d_iter;      //  Refolded result - updated for each iteration

        // Projections
        TH1D* raw_X;            //  Detector smeared - Full range X var
        TH1D* htrue_X;          //  MC True - X in specified Y range
        TH1D* eff_X;            //  To calculate Efficiency //* MC True Det level - X in specified Y range

        TH1D* unfold_X[20];     //  Unfolded - X in specified Y range
        TH1D* fold_X[20];       //  Refolded - X in specified Y range

        TH1D* raw_Y;            //  Detector smeared - Full range Y var
        TH1D* htrue_Y;          //  MC True - Y in specified X range
        TH1D* eff_Y;            //  To calculate Efficiency //* MC True Det level - Y in specified X range

        TH1D* unfold_Y[20];     //  Unfolded - Y in specified X range
        TH1D* fold_Y[20];       //  Refolded - Y in specified X range

    // -------- End Histograms
    // ----------------------------------------------------------------------------------------------------------------
    // Read histograms 

        TFile* f = new TFile(file);
        TFile* fprior = new TFile(fileother);       // Only used for prior error calculation       
    
        raw=(TH2D*)f->Get("smeared");
        if(flagdummy==0) raw=(TH2D*)f->Get("raw_corrected");
        htrue=(TH2D*)f->Get("truef");
        if(flagdummy==2) htrue=(TH2D*)f->Get("true");
        htrue_ineff=(TH2D*)f->Get("true");
        
        raw_X=(TH1D*)raw->ProjectionX("raw_X",1,-1);        
        htrue_X=(TH1D*)htrue->ProjectionX("true_X",bintrueY_min,bintrueY_max);
        eff_X=htrue_ineff->ProjectionX("eff_X",bintrueY_min,bintrueY_max);
        eff_X->Divide(htrue_X);

        raw_Y=(TH1D*)raw->ProjectionY("raw_Y",1,-1);
        htrue_Y=(TH1D*)htrue->ProjectionY("true_Y",bintrueX_min,bintrueX_max);
        eff_Y=htrue_ineff->ProjectionY("eff_Y",bintrueX_min,bintrueX_max);
        eff_Y->Divide(htrue_Y);
        
    // -------- End Read Histograms
    // ----------------------------------------------------------------------------------------------------------------
    // Iteration Loop

    htrue_X->Scale(1./htrue_X->Integral(1,-1));                       
    htrue_X->Scale(1,"width");

    htrue_Y->Scale(1./htrue_Y->Integral(1,-1));                       
    htrue_Y->Scale(1,"width");

    for(Int_t j=0;j<15;j++){
        unfold2d_iter=(TH2D*)f->Get(Form("Bayesian_Unfoldediter%d",j+1));
        fold2d_iter=(TH2D*)f->Get(Form("Bayesian_Foldediter%d",j+1));

        unfold_X[j]=(TH1D*)unfold2d_iter->ProjectionX(Form("unfold_X%d",j),bintrueY_min,bintrueY_max,"");
        unfold_X[j]->Divide(eff_X); 
        unfold_X[j]->Scale(1./unfold_X[j]->Integral(1,-1));
        unfold_X[j]->Scale(1,"width");

        fold_X[j]=(TH1D*)fold2d_iter->ProjectionX(Form("fold_X%d",j),1,-1,"");
        fold_X[j]->Divide(raw_X);     
        
        //* Y unfold 
        unfold_Y[j]=(TH1D*)unfold2d_iter->ProjectionY(Form("unfold_Y%d",j),bintrueX_min,bintrueX_max,"");
        unfold_Y[j]->Divide(eff_Y); 
        unfold_Y[j]->Scale(1./unfold_Y[j]->Integral(1,-1));
        unfold_Y[j]->Scale(1,"width");

        fold_Y[j]=(TH1D*)fold2d_iter->ProjectionY(Form("fold_Y%d",j),1,-1,"");
        fold_Y[j]->Divide(raw_Y); 
    }
   
	TH1D *histotot(0);
    TH1D *historeg(0);
    TH1D *histoprior(0);
    TH1D *histostat(0);
    // ---------------- Error Calculation - crossing of reg and statistical uncerts
        TH1D *def1, *def2, *def3, *def4;
        TH2D *itera, *iterad, *iterau, *iterp;
        Double_t errprior, errreg1, errreg2, errreg, errstat, errtot;
        histotot=new TH1D("histotot","histot",12,0,15);
        historeg=new TH1D("historeg","historeg",12,0,15);
        histoprior=new TH1D("histoprior","histoprior",12,0,15);
        histostat=new TH1D("histostat","histostat",12,0,15);

        
        for(Int_t k=2;k<13;k++){
        
            itera=(TH2D*)f->Get(Form("Bayesian_Unfoldediter%d",k));
            iterad=(TH2D*)f->Get(Form("Bayesian_Unfoldediter%d",k-1));
            iterau=(TH2D*)f->Get(Form("Bayesian_Unfoldediter%d",k+2));
            iterp=(TH2D*)fprior->Get(Form("Bayesian_Unfoldediter%d",k));

            def1=(TH1D*)itera->ProjectionX(Form("def1_%i",k),bintrueY_min,bintrueY_max);
            def2=(TH1D*)iterad->ProjectionX(Form("def2_%i",k),bintrueY_min,bintrueY_max);
            def3=(TH1D*)iterau->ProjectionX(Form("def3_%i",k),bintrueY_min,bintrueY_max);
            def4=(TH1D*)iterp->ProjectionX(Form("def4_%i",k),bintrueY_min,bintrueY_max);

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

    // -------- End Error Calculation
    // ------ Plotting Histograms
    TFile *fout;
    fout = new TFile(output_path + "/OutputUnfolded_"+label+"/OutputUnfolded_"+label+".root", "recreate");

    std::vector<TString>sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, Anti-#it{k}_{T} #it{R}=0.2",100.0,40.0),"Cent. 0-30%","Bayes Unfolded","z_{cut}=0.2",y_label+" vs "+x_label};    
    std::vector<TH1D*> hist_input;
    std::vector<TString> histname_input;
    sel.push_back("end");
    sel.push_back("noStackHIST");
    Plot_hist({histotot,historeg,histostat,histoprior},{"Total","Regularization","Statistical","Prior","Iterations","Summed Errors","SumErrors"},"rightlabel_opt",sel);
    sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, Anti-#it{k}_{T} #it{R}=0.2",100.0,40.0),"Cent. 0-30%","Bayes Unfolded","z_{cut}=0.2",Form("%3.2f<%s<%3.2f",ylabel_min,y_label.Data(),ylabel_max)};    
    // Iterations vs x axis plot
        hist_input={};
        histname_input={Form("UnfoldedXiter%d",iter_ref)};
        if(flagdummy==0){hist_input.push_back(unfold_X[iter_ref]);}
        else{hist_input.push_back(htrue_X);}
        for(Int_t iter=0;iter<15;iter++){
            hist_input.push_back((TH1D*)unfold_X[iter]->Clone());
            histname_input.push_back(Form(" iter %d",iter+1));
        }
        histname_input.push_back(x_label);
        if(flagdummy==0){histname_input.push_back(Form("Unfolded/Iter %i",iter_ref));}
        else{histname_input.push_back(Form("Unfolded/true"));}
        histname_input.push_back("Unfolded_IterVsX");
    Plot_hist(hist_input,histname_input,"eff_bcenter_label",sel);
    // Refolded x axis plot
        hist_input={};
        histname_input={};
        for(Int_t iter=0;iter<15;iter++){
            hist_input.push_back((TH1D*)fold_X[iter]->Clone());
            histname_input.push_back(Form(" iter %d",iter+1));
        }
        histname_input.push_back(x_label);
        histname_input.push_back(Form("Folder/Raw"));
        histname_input.push_back("Refolded_IterVsX");
    Plot_hist(hist_input,histname_input,"bcenter_label",sel);
    sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, Anti-#it{k}_{T} #it{R}=0.2",100.0,40.0),"Cent. 0-30%","Bayes Unfolded","z_{cut}=0.2",Form("%3.2f<%s<%3.2f",xlabel_min,x_label.Data(),xlabel_max)};   
    // Iterations vs y axis plot
        hist_input={};
        histname_input={Form("UnfoldedYiter%d",iter_ref)};
        if(flagdummy==0){hist_input.push_back(unfold_Y[iter_ref]);}
        else{hist_input.push_back(htrue_Y);}
        for(Int_t iter=0;iter<15;iter++){
            hist_input.push_back((TH1D*)unfold_Y[iter]->Clone());
            histname_input.push_back(Form(" iter %d",iter+1));
        }
        histname_input.push_back(y_label);
        if(flagdummy==0){histname_input.push_back(Form("Unfolded/Iter %i",iter_ref));}
        else{histname_input.push_back(Form("Unfolded/true"));}
        histname_input.push_back("Unfolded_IterVsY");
    Plot_hist(hist_input,histname_input,"eff_bcenter_label",sel);
    // Refolded y axis plot
        hist_input={};
        histname_input={};
        for(Int_t iter=0;iter<15;iter++){
            hist_input.push_back((TH1D*)fold_Y[iter]->Clone());
            histname_input.push_back(Form(" iter %d",iter+1));
        }
        histname_input.push_back(y_label);
        histname_input.push_back(Form("Folder/Raw"));
        histname_input.push_back("Refolded_IterVsY");
    Plot_hist(hist_input,histname_input,"bcenter_label",sel);
    sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, Anti-#it{k}_{T} #it{R}=0.2",100.0,40.0),"Cent. 0-30%"}; 
    Plot_hist({eff_X},{Form("Efficiency for true %3.2f<%s<%3.2f",ylabel_min,y_label.Data(),ylabel_max),x_label,"Efficiency","Kineff_X"},"bcenter_label",sel);
    Plot_hist({eff_Y},{Form("Efficiency for true %3.2f<%s<%3.2f",xlabel_min,x_label.Data(),xlabel_max),y_label,"Efficiency","Kineff_Y"},"bcenter_label",sel);
    sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, Anti-#it{k}_{T} #it{R}=0.2",100.0,40.0),"Cent. 0-30%","Bayes Unfolded","z_{cut}=0.2",Form("%3.2f<%s<%3.2f",ylabel_min,y_label.Data(),ylabel_max)};   
    overlay({unfold_X[iter_ref],htrue_X},{"data unfolded","pythia true",x_label,flagdummy==0?"Unfolded":"True MC","X_unfolded_overlay"},"rightlog_label",sel);
    Plot_hist({unfold_X[iter_ref],htrue_X},{"data unfolded","pythia true",x_label,flagdummy==0?"Unfolded":"True MC","X_unfolded"},"rightlog_label",sel);
    sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, Anti-#it{k}_{T} #it{R}=0.2",100.0,40.0),"Cent. 0-30%","Bayes Unfolded","z_{cut}=0.2",Form("%3.2f<%s<%3.2f",xlabel_min,x_label.Data(),xlabel_max)};   
    overlay({unfold_Y[iter_ref],htrue_Y},{"data unfolded","pythia true",y_label,flagdummy==0?"Unfolded":"True MC","Y_unfolded_overlay"},"right_label",sel);
    Plot_hist({unfold_Y[iter_ref],htrue_Y},{"data unfolded","pythia true",y_label,flagdummy==0?"Unfolded":"True MC","Y_unfolded"},"right_label",sel);
    sel = {Form("#gamma p_{T}>%.0f, Jet p_{T}>%.0f, Anti-#it{k}_{T} #it{R}=0.2",100.0,40.0),"Cent. 0-30%"}; 
    Plot_hist2D({raw},{"Raw_Y_X"},"text",sel);
    fout->Close();    

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

    TCanvas *c= new TCanvas();
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
    c->SaveAs(output_path + "/OutputUnfolded_"+label+"/"+histname.back()+".png");
    c->Write(histname.back(),TObject::kWriteDelete);
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

    TCanvas *c;
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
    }
    /*
    l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    l->SetFillStyle(0);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->SetTextSize(0.025);
    l->SetTextFont(42);
    l->Draw();
    */


    for(std::size_t ihist=0; ihist<hist.size();ihist++){
        c = new TCanvas();
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
        c->SaveAs(output_path + "/OutputUnfolded_"+label+"/"+histname[ihist]+".png");
        c->Write(histname[ihist],TObject::kWriteDelete);
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
    const std::vector<int> colarray  = {1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606,
                                       1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41,
                                        20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};

    TCanvas *c= new TCanvas();
    c->cd();
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
    c->cd();          // Go back to the main canvas before defining pad2
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
    c->cd();  

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
    c->SaveAs(output_path + "/OutputUnfolded_"+label+"/"+histname.back()+".png");
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
    else if(argc==7){
        output_path = argv[1];
        label = argv[2];
        x_label = argv[6];
        plot_unfolded(argv[3],argv[4],atoi(argv[5]));
    }
    else{
        printf("Run with \n ./plot_unfolded <output dir> <label> <file1> <file2> <flag>\n");
    }

    return 0;
}