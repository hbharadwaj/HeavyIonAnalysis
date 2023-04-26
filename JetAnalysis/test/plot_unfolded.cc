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
TString centstring = "Cent. 0-30%";

void Plot_hist(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void Plot_hist2D(std::vector<TH2D*> hist,std::vector<TString> histname,TString dopt="colz",std::vector<TString> eopt={"end"});

void overlay(std::vector<TH1D*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void plot_unfolded(TString file, TString fileother, int flagdummy=1, int bintrueY_max = 1){
    // Unfolding input contains - flag 0-19 for data, flag>=20 for different MC
    // fileother is used for 2nd MC to calculate priors - otherwise pass same input to both
    // flagdummy == 0 -> Data Corrected
    // flagdummy == 1 -> MC Det level test
    // flagdummy == 2 -> MC True at Det level - Split Test
    // Range [1,-1] -> All Bins other than Underflow and Overflow
    

    // Bins to Project
    int bintrueY_min = 1;//2;   
    int bintrueX_min = 1; // x_label.Contains("dyn")?2:1
    int bintrueX_max = 5; // x_label.Contains("Girth")?4:4;

    int binrawY_min = 1;
    int binrawY_max = 1;
    int binrawX_min = bintrueX_min;
    int binrawX_max = bintrueX_max;
    //-----------------------

    //                       Pythia                              Prior
    // 0-30%  - >  x_label.Contains("Girth")?20:6;       x_label.Contains("Girth")?25:7;
    // 30-90% - >  x_label.Contains("Girth")?1:7;        x_label.Contains("Girth")?3:8;

    const int iter_ref = x_label.Contains("Girth")?7:7;
    float nbins = 1; 

    // inputs for Unfolding 
        const int bin_true_xj=1;//2;
        const int bin_true_Rg=5;//6;
        const int bin_true_angu=5;//6;
        const int bin_true_dynkt=5;

        Double_t xjmin_true=0.4;//0;
        Double_t xjmax_true=3;

        Double_t Rgmin_true=0.0;
        Double_t Rgmax_true=0.2;//0.3;

        Double_t angumin_true=0.;
        Double_t angumax_true=0.1;//0.3;

        Double_t dynktmax_true=50.0;
        Double_t dynktmin_true=0.;

        Double_t xJ_true_edges[bin_true_xj+1] ={xjmin_true, xjmax_true}; //{xjmin_true, 0.4, xjmax_true};
        Double_t Rg_true_edges[bin_true_Rg+1] = {-0.05,Rgmin_true, 0.04, 0.08, 0.12, Rgmax_true};//{-0.05,Rgmin_true, 0.04, 0.08, 0.12, 0.2, Rgmax_true};
        Double_t angu_true_edges[bin_true_angu+1] = {angumin_true, 0.02, 0.04, 0.06, 0.08, angumax_true};//{angumin_true, 0.02, 0.04, 0.06, 0.08, 0.1, angumax_true};
        Double_t dynkt_true_edges[bin_true_dynkt+1] = {dynktmin_true, 1.5,2.5,4.0,10.0,dynktmax_true};
        Double_t xlabel_min,xlabel_max,ylabel_min,ylabel_max;

        if(x_label.Contains("dyn")){
            xlabel_min = dynkt_true_edges[bintrueX_min-1];
            xlabel_max = dynkt_true_edges[bintrueX_max];
            nbins = bin_true_xj*bin_true_dynkt;
        }
        else if(x_label.Contains("Girth")){
            xlabel_min = angu_true_edges[bintrueX_min-1];
            xlabel_max = angu_true_edges[bintrueX_max];
            nbins = bin_true_xj*bin_true_angu;
        }
        else{   // Rg
            xlabel_min = Rg_true_edges[bintrueX_min-1];
            xlabel_max = Rg_true_edges[bintrueX_max];
            nbins = bin_true_xj*bin_true_Rg;
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
        TH1::SetDefaultSumw2();
        TH2::SetDefaultSumw2();

        TH2D* raw;              //  Detector smeared - 0->Data : else ->MC
        TH2D* htrue;            //  MC - Gen level Cuts : 2-> Det level Cuts for Split
        TH2D* raw_mc;           //  MC - 0-> Bottomline Test
        TH2D* htrue_ineff;      //  MC - Det level Cuts
        TH2D* unfold2d_iter;    //  Unfolded result - updated for each iteration
        TH2D* fold2d_iter;      //  Refolded result - updated for each iteration
        TH2D* matinvert2d;      //  Matrix Inversion result
        TH2D* matfolded2d;      //  Refolded Matrix Inversion result
        TH2D* eff_2d;           //  To calculate Efficiency //* MC True Det level - X in specified Y range

        // Projections
        TH1D* raw_X;            //  Detector smeared - Full range X var
        TH1D* htrue_X;          //  MC True - X in specified Y range
        TH1D* eff_X;            //  To calculate Efficiency //* MC True Det level - X in specified Y range
        TH1D* raw_X_mc;         //  MC Det smeared

        TH1D* unfold_X[200];     //  Unfolded - X in specified Y range
        TH1D* fold_X[200];       //  Refolded - X in specified Y range

        TH1D* matinvert_X;       //  Matrix Inversion - X in specified Y range
        TH1D* matfold_X;         //  Matrix Refolded  - X in specified Y range

        TH1D* raw_Y;            //  Detector smeared - Full range Y var
        TH1D* htrue_Y;          //  MC True - Y in specified X range
        TH1D* eff_Y;            //  To calculate Efficiency //* MC True Det level - Y in specified X range

        TH1D* unfold_Y[200];     //  Unfolded - Y in specified X range
        TH1D* fold_Y[200];       //  Refolded - Y in specified X range

        TH1D* matinvert_Y;       //  Matrix Inversion - Y in specified X range
        TH1D* matfold_Y;         //  Matrix Refolded  - Y in specified X range

        TH1D* nPho_data;        //  Number of Selected Photons in data
        TH1D* nJet_data;        //  Number of Selected Jets in data
        TH1D* nPho_mc;          //  Number of Selected Photons in MC
        TH1D* nJet_mc;          //  Number of Selected Jets in MC

    // -------- End Histograms
    // ----------------------------------------------------------------------------------------------------------------
    // Read histograms 

        TFile* f = new TFile(file);
        TFile* fprior = new TFile(fileother);       // Only used for prior error calculation       
    
        raw=(TH2D*)f->Get("smeared");
        raw_mc=(TH2D*)f->Get("smeared");
        if(flagdummy==0 || flagdummy==2) raw=(TH2D*)f->Get("raw_corrected");    // Pseudodata or Data
        htrue=(TH2D*)f->Get("truef");
        // if(flagdummy==2) htrue=(TH2D*)f->Get("true");
        htrue_ineff=(TH2D*)f->Get("true");
        if(flagdummy==2){
            htrue=(TH2D*)f->Get("truef_pseudodata");
            htrue_ineff=(TH2D*)f->Get("true_pseudodata");
            // htrue->Sumw2();
            // htrue_pseudodata->Sumw2();
            // htrue->Add(htrue_pseudodata);
        }
        // Projection bins include the histograms underflow(0) and overflow(nbins+1) 

        eff_2d=(TH2D*)htrue_ineff->Clone("eff_2d");
        eff_2d->Divide(htrue_ineff,htrue,1,1,"B");  //! This should be Binomial or Bayes Division since Numerator is a subset of denominator
        eff_X=(TH1D*)eff_2d->ProjectionX("eff_X",bintrueY_min,bintrueY_max);
        eff_Y=(TH1D*)eff_2d->ProjectionY("eff_Y",bintrueX_min,bintrueX_max);
        
        raw_X=(TH1D*)raw->ProjectionX("raw_X",binrawY_min,binrawY_max);
        raw_X->Scale(1.0/raw_X->Integral(binrawX_min,binrawX_max),"width");    
        raw_X_mc=(TH1D*)raw_mc->ProjectionX("raw_X_mc",binrawY_min,binrawY_max);             
        raw_X_mc->Scale(1.0/raw_X_mc->Integral(binrawX_min,binrawX_max),"width"); 

        htrue_X=(TH1D*)htrue->ProjectionX("true_X",bintrueY_min,bintrueY_max);
        // eff_X=htrue_ineff->ProjectionX("eff_X",bintrueY_min,bintrueY_max);
        // eff_X->Divide(htrue_X);


        raw_Y=(TH1D*)raw->ProjectionY("raw_Y",binrawX_min,binrawX_max);
        raw_Y->Scale(1.0/raw_Y->Integral(binrawY_min,binrawY_max),"width");
        htrue_Y=(TH1D*)htrue->ProjectionY("true_Y",bintrueX_min,bintrueX_max);
        // eff_Y=htrue_ineff->ProjectionY("eff_Y",bintrueX_min,bintrueX_max);
        // eff_Y->Divide(htrue_Y);

        // nPho_data=(TH1D*)f->Get("nPho_data");
        // nJet_data=(TH1D*)f->Get("nJet_data");
        // nPho_mc=(TH1D*)f->Get("nPho_mc");
        // nJet_mc=(TH1D*)f->Get("nJet_mc");

        htrue_X->Scale(1.0/htrue_X->Integral(bintrueX_min,bintrueX_max),"width");
        // htrue_X->Scale(1,"width");

        htrue_Y->Scale(1.0/htrue_Y->Integral(bintrueY_min,bintrueY_max),"width");
        // htrue_Y->Scale(1,"width");


    // -------- End Read Histograms
    // ----------------------------------------------------------------------------------------------------------------
    // Iteration Loop

    matinvert2d=(TH2D*)f->Get(Form("MatInver_Unfolded"));
    matinvert2d->Divide(eff_2d);    //! Not a subset and can remain the default division
    matfolded2d=(TH2D*)f->Get(Form("MatInver_Folded"));

    matinvert_X=(TH1D*)matinvert2d->ProjectionX(Form("matinvert_X"),bintrueY_min,bintrueY_max,"");
    matinvert_X->Divide(eff_X); 
    matinvert_X->Scale(1.0/matinvert_X->Integral(bintrueX_min,bintrueX_max),"width");

    matfold_X=(TH1D*)matfolded2d->ProjectionX(Form("matfold_X"),binrawY_min,binrawY_max,"");
    matfold_X->Scale(1.0/matfold_X->Integral(binrawX_min,binrawX_max),"width");

    matinvert_Y=(TH1D*)matinvert2d->ProjectionY(Form("matinvert_Y"),bintrueX_min,bintrueX_max,"");
    // matinvert_Y->Divide(eff_Y); 
    matinvert_Y->Scale(1.0/matinvert_Y->Integral(bintrueY_min,bintrueY_max),"width");
    
    matfold_Y=(TH1D*)matfolded2d->ProjectionY(Form("matfold_Y"),binrawX_min,binrawX_max,"");
    matfold_Y->Scale(1.0/matfold_Y->Integral(binrawY_min,binrawY_max),"width");
    
    TH1D *hist_chi2(0),*hist_chi2_smeared(0),*hist_pval_smeared(0);
    hist_chi2=new TH1D("hist_chi2","hist_chi2",80,0,80);
    hist_chi2_smeared=new TH1D("hist_chi2_smeared","hist_chi2_smeared",80,0,80);
    hist_pval_smeared=new TH1D("hist_pval_smeared","hist_pval_smeared",80,0,80);
    int flag_pval = 0;

    for(Int_t j=0;j<80;j++){
        unfold2d_iter=(TH2D*)f->Get(Form("Bayesian_Unfoldediter%d",j+1));
        unfold2d_iter->Divide(eff_2d);
        fold2d_iter=(TH2D*)f->Get(Form("Bayesian_Foldediter%d",j+1));

        unfold_X[j]=(TH1D*)unfold2d_iter->ProjectionX(Form("unfold_X%d",j),bintrueY_min,bintrueY_max,"");
        // unfold_X[j]->Divide(eff_X); 
        unfold_X[j]->Scale(1.0/unfold_X[j]->Integral(bintrueX_min,bintrueX_max),"width");
        // unfold_X[j]->Scale(1,"width");

        fold_X[j]=(TH1D*)fold2d_iter->ProjectionX(Form("fold_X%d",j),binrawY_min,binrawY_max,"");
        fold_X[j]->Scale(1.0/fold_X[j]->Integral(binrawX_min,binrawX_max),"width");
        
        //* Y unfold 
        unfold_Y[j]=(TH1D*)unfold2d_iter->ProjectionY(Form("unfold_Y%d",j),bintrueX_min,bintrueX_max,"");
        // unfold_Y[j]->Divide(eff_Y); 
        unfold_Y[j]->Scale(1.0/unfold_Y[j]->Integral(bintrueY_min,bintrueY_max),"width");
        // unfold_Y[j]->Scale(1,"width");

        fold_Y[j]=(TH1D*)fold2d_iter->ProjectionY(Form("fold_Y%d",j),binrawX_min,binrawX_max,"");
        fold_Y[j]->Scale(1.0/fold_Y[j]->Integral(binrawY_min,binrawY_max),"width");

        // ---- Unfolded Chi2

        float sumChi2 = 0;
        
        TH1D *htemp1 = (TH1D*)unfold_X[j]->Clone();
        TH1D *htemp2 = (TH1D*)htrue_X->Clone(); 

        for (Int_t k = 1; k < (htemp1->GetNbinsX()); k++){  // Ignoring the last x Bin
            // if(j<10)std::cout<<"Unfolded iter "<<j<<"    =  "<<k<<"     "<<sumChi2<<"     \t"<<htemp1->GetBinContent(k)-htemp2->GetBinContent(k)<<"     "<<htemp1->GetBinError(k)<<std::endl;
            if (htemp1->GetBinContent(k) > 0) sumChi2+= (htemp1->GetBinContent(k)-htemp2->GetBinContent(k))*(htemp1->GetBinContent(k)-htemp2->GetBinContent(k))/(htemp1->GetBinError(k)*htemp1->GetBinError(k)); // + htemp2->GetBinError(k)*htemp2->GetBinError(k)
        }
        sumChi2/=(htemp1->GetNbinsX()-1);
        // if(j<8) std::cout<<"iter "<<j<<" \t Chi2unfolded =  "<<sumChi2<<"  \t  "<<(htemp1->GetNbinsX()-1)<<" \t  p-value = "<<TMath::Prob(sumChi2, (htemp1->GetNbinsX()-1))<<std::endl;
        // sumChi2=htemp1->Chi2Test(htemp2,"UWCHI2/NDF");
        hist_chi2->SetBinContent(j,sumChi2);

        // ---- Refolded Chi2

        sumChi2 = 0;

        // For bottom line test 

        TH1D *htemp1_smeared = (TH1D*)raw_X->Clone();
        TH1D *htemp2_smeared = (TH1D*)fold_X[j]->Clone(); // (TH1D*)raw_X_mc->Clone();//

        for (Int_t k = 1; k < (htemp1_smeared->GetNbinsX()+1); k++){  
            // if(j<10)            std::cout<<"Smeared  iter "<<j<<"    =  "<<k<<"     "<<sumChi2<<"     \t"<<htemp1_smeared->GetBinContent(k)-htemp2_smeared->GetBinContent(k)<<"     "<<htemp1_smeared->GetBinError(k)<<std::endl;
            if (htemp1_smeared->GetBinContent(k) > 0) sumChi2+= (htemp1_smeared->GetBinContent(k)-htemp2_smeared->GetBinContent(k))*(htemp1_smeared->GetBinContent(k)-htemp2_smeared->GetBinContent(k))/(htemp1_smeared->GetBinError(k)*htemp1_smeared->GetBinError(k) ); //+ htemp2_smeared->GetBinError(k)*htemp2_smeared->GetBinError(k)
            // if (htemp1_smeared->GetBinContent(k) > 0)std::cout<<k<<"\t"<<(htemp1_smeared->GetBinContent(k)-htemp2_smeared->GetBinContent(k))*(htemp1_smeared->GetBinContent(k)-htemp2_smeared->GetBinContent(k))/(htemp1_smeared->GetBinError(k)*htemp1_smeared->GetBinError(k) );
        }
        float pval = TMath::Prob(sumChi2, (htemp1_smeared->GetNbinsX()));
        sumChi2/=(htemp1_smeared->GetNbinsX());
        if(pval>0.95 && !flag_pval){
            std::cout<<"iter "<<j<<" \t Chi2smeared =  "<<sumChi2<<"  \t  "<<(htemp1_smeared->GetNbinsX())<<" \t  p-value = "<<pval<<std::endl;
            flag_pval=1;
        }
        // if(j<8) std::cout<<"iter "<<j<<" \t Chi2smeared =  "<<sumChi2<<"  \t  "<<(htemp1_smeared->GetNbinsX())<<" \t  p-value = "<<pval<<std::endl;
        // sumChi2=htemp1_smeared->Chi2Test(htemp2_smeared,"WWCHI2/NDF");
        hist_chi2_smeared->SetBinContent(j,sumChi2);
        hist_pval_smeared->SetBinContent(j,pval);
        // if(j<8) std::cout<<"Iter "<<j<<"\t p-val = "<<pval<<std::endl;
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

    for(Int_t iter=0;iter<60;iter++){
        unfold_X[iter]->Write("",TObject::kOverwrite);
        unfold_Y[iter]->Write("",TObject::kOverwrite);
    }
    htrue_X->Write("",TObject::kOverwrite);
    htrue_Y->Write("",TObject::kOverwrite);
    matinvert_X->Write("",TObject::kOverwrite);
    matinvert_Y->Write("",TObject::kOverwrite);

    std::vector<TString>sel = {" ",centstring,y_label+" vs "+x_label,Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.4)};    
    std::vector<TH1D*> hist_input;
    std::vector<TString> histname_input;
    sel.push_back("end");
    sel.push_back("noStackHIST");
    // Plot_hist({hist_chi2_smeared,hist_chi2},{"#chi^{2}_{smeared}","#chi^{2}_{unfolded}","Iterations","#chi^{2}/NDF","Chi2_ndf_bottomline"},"rightlabel_opt",sel);

    Plot_hist({histotot,historeg,histostat,histoprior},{"Total","Regularization","Statistical","Prior","Iterations","Summed Errors","SumErrors"},"rightlabel_opt",sel);
    Plot_hist({hist_chi2},{x_label.Data(),"Iterations","#chi^{2}/NDF","Chi2_ndf_unfolded"},"rightlabel_opt",sel);
    Plot_hist({hist_chi2},{x_label.Data(),"Iterations","#chi^{2}/NDF","Chi2_ndf_unfolded_log"},"rightlabel_opt_log",sel);
    sel = {" ",centstring,y_label+" vs "+x_label,"#chi^{2} Refolded-Raw",Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.4),"end","noStackHIST"};    
    Plot_hist({hist_chi2_smeared},{x_label.Data(),"Iterations","#chi^{2}/NDF","Chi2_ndf_refolded"},"rightlabel_opt",sel);
    Plot_hist({hist_chi2_smeared},{x_label.Data(),"Iterations","#chi^{2}/NDF","Chi2_ndf_refolded_log"},"rightlabel_opt_log",sel);
    Plot_hist({hist_pval_smeared},{x_label.Data(),"Iterations","p-value","p-value_refolded"},"rightlabel_opt",sel);
    sel = {" ",centstring,Form("%3.2f<%s<%3.2f",ylabel_min,y_label.Data(),ylabel_max),Form("#gamma p_{T}>%.0f,|#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0)};    
    if(x_label.Contains("R")){
        Double_t full_error;
        Double_t full_integral = unfold_X[iter_ref]->IntegralAndError(0, unfold_X[iter_ref]->GetNbinsX()+1, full_error, "width"); // "" or "width"
        Double_t untag_error;
        Double_t untag_integral = unfold_X[iter_ref]->IntegralAndError(1, 1, untag_error, "width"); // "" or "width"
        float untagged_Err = (untag_error/untag_integral) + (full_integral/full_error);
        sel.push_back(Form("Untagged Fraction = %5.3f %%",untag_integral*100.0/full_integral));    
    } 
    // Graphical Bottomline test
        hist_input={};
        histname_input={};
        TH1D* htemp = (TH1D*)htrue_X->Clone();               // True Level
        // htemp->Divide((TH1D*)unfold_X[iter_ref]->Clone());  // For D'Agostini
        htemp->Divide((TH1D*)matinvert_X->Clone()); 
        hist_input.push_back((TH1D*)htemp->Clone());
        histname_input.push_back(Form("MC True"));
        htemp = (TH1D*)raw_X_mc->Clone();                     // Det Level
        htemp->Divide((TH1D*)raw_X->Clone());
        hist_input.push_back((TH1D*)htemp->Clone());
        histname_input.push_back(Form("MC Det"));
        histname_input.push_back(x_label);
        histname_input.push_back(Form("Ratio to Data"));
        histname_input.push_back("Graphical_Bottomline_test");
    Plot_hist(hist_input,histname_input,"bcenter_label",sel);
    // Iterations vs x axis plot
        hist_input={};
        histname_input={Form("UnfoldedXiter%d",iter_ref)};
        if(flagdummy==0){hist_input.push_back(unfold_X[iter_ref]);}
        else{hist_input.push_back(htrue_X);}
        for(Int_t iter=0;iter<45;iter+=3){
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
        histname_input={Form("RefoldedXiter%d",iter_ref)};
        // if(flagdummy==0){hist_input.push_back(fold_X[iter_ref]);}
        // else{hist_input.push_back(raw_X);}
        hist_input.push_back(raw_X);
        for(Int_t iter=0;iter<45;iter+=3){
            hist_input.push_back((TH1D*)fold_X[iter]->Clone());
            histname_input.push_back(Form(" iter %d",iter+1));
        }
        histname_input.push_back(x_label);
        histname_input.push_back(Form("Folded/Raw"));
        histname_input.push_back("Refolded_IterVsX");
    Plot_hist(hist_input,histname_input,"eff_bcenter_label",sel);
    overlay({matfold_X,raw_X},{"data-Mat Inversion Refolded","MC Raw",x_label,flagdummy==0?"Matrix Inverted":"Raw MC","X_invert_refolded_overlay"},"right_label",sel);
    overlay({matinvert_X,htrue_X},{"data-Mat Inversion","MC true",x_label,flagdummy==0?"Matrix Inverted":"True MC","X_inverted_overlay"},"right_label",sel);
    
    Plot_hist({raw_X,matfold_X},{"MC Raw",x_label,"Matrix Invertion Refolded/MC Raw","Refolded_MatInvertVsX"},"eff_bcenter_label_leg",sel);
    Plot_hist({htrue_X,matinvert_X},{"MC true",x_label,"Matrix Inverted/True","Unfolded_MatInvertVsX"},"eff_bcenter_label_leg",sel);
    sel = {" ",centstring,Form("%3.2f<%s<%3.2f",xlabel_min,x_label.Data(),xlabel_max),Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.4)};   
    // Iterations vs y axis plot
        hist_input={};
        histname_input={Form("UnfoldedYiter%d",iter_ref)};
        if(flagdummy==0){hist_input.push_back(unfold_Y[iter_ref]);}
        else{hist_input.push_back(htrue_Y);}
        for(Int_t iter=0;iter<45;iter+=3){
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
        histname_input={Form("RefoldedYiter%d",iter_ref)};
        // if(flagdummy==0){hist_input.push_back(fold_Y[iter_ref]);}
        // else{hist_input.push_back(raw_Y);}
        hist_input.push_back(raw_Y);
        for(Int_t iter=0;iter<45;iter+=3){
            hist_input.push_back((TH1D*)fold_Y[iter]->Clone());
            histname_input.push_back(Form(" iter %d",iter+1));
        }
        histname_input.push_back(y_label);
        histname_input.push_back(Form("Folder/Raw"));
        histname_input.push_back("Refolded_IterVsY");
    Plot_hist(hist_input,histname_input,"eff_bcenter_label",sel);
    overlay({matfold_Y,raw_Y},{"data-Mat Inversion Refolded","MC Raw",y_label,flagdummy==0?"Matrix Inverted":"Raw MC","Y_invert_refolded_overlay"},"right_label",sel);
    overlay({matinvert_Y,htrue_Y},{"data-Mat Inversion","MC true",y_label,flagdummy==0?"Matrix Inverted":"True MC","Y_inverted_overlay"},"right_label",sel);
    // Plot_hist({unfold_Y[iter_ref],matinvert_Y,htrue_Y},{"data-Unfolded","data-Mat Inversion","MC true",y_label,flagdummy==0?"Matrix Inverted":"True MC","Y_inverted"},"right_label",sel);
    sel = {" ",centstring,Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.4)}; 
    Plot_hist({eff_X},{Form("Efficiency for true %3.2f<%s<%3.2f",ylabel_min,y_label.Data(),ylabel_max),x_label,"Efficiency","Kineff_X"},"bcenter_label",sel);
    Plot_hist({eff_Y},{Form("Efficiency for true %3.2f<%s<%3.2f",xlabel_min,x_label.Data(),xlabel_max),y_label,"Efficiency","Kineff_Y"},"bcenter_label",sel);
    sel = {" ",centstring,Form("%3.2f<%s<%3.2f",ylabel_min,y_label.Data(),ylabel_max),Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.4)};  
    overlay({unfold_X[iter_ref],htrue_X},{"data unfolded","MC true",x_label,flagdummy==0?"Unfolded":"True MC","X_unfolded_overlay"},x_label.Contains("dyn")?"rightlog_label":"right_label",sel);
    Plot_hist({unfold_X[iter_ref],htrue_X},{"data unfolded","MC true",x_label,flagdummy==0?"Unfolded":"True MC","X_unfolded"},x_label.Contains("dyn")?"rightlog_label":"right_label",sel);
    sel = {" ",centstring,Form("%3.2f<%s<%3.2f",xlabel_min,x_label.Data(),xlabel_max),Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.4)};   
    overlay({unfold_Y[iter_ref],htrue_Y},{"data unfolded","MC true",y_label,flagdummy==0?"Unfolded":"True MC","Y_unfolded_overlay"},"right_label",sel);
    Plot_hist({unfold_Y[iter_ref],htrue_Y},{"data unfolded","MC true",y_label,flagdummy==0?"Unfolded":"True MC","Y_unfolded"},"right_label",sel);
    sel = {" ",centstring,Form("#gamma p_{T}>%.0f, x_{J}>%.1f, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.4)}; 
    Plot_hist2D({raw},{"Raw_Y_X"},"text_colz",sel);
    overlay({unfold_Y[iter_ref],htrue_Y},{"data unfolded","MC true",y_label,flagdummy==0?"Unfolded":"True MC","Y_unfolded_overlay"},"right_label",sel);
    fout->Close();    

}

void Plot_hist(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "width" = Divide by Bin Width
    // "opt" = drawopt is last element of eopt

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(opt.Contains("log")) gStyle->SetOptLogy(1);
    
    TString drawopt = "nostackE1][P0"; 
    if(opt.Contains("opt"))
        drawopt = eopt.back();
    const std::vector<int> colarray  = { 1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606,
                                       1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29,   //  28, 39, 40
                                        24, 21, 26, 23, 30};  //  34, 37, 41

    TCanvas *c= new TCanvas();
    TLegend *l;
    float leg_x1 = 0.6;
    float leg_y1 = 0.58;
    float leg_x2 = 0.8;
    float leg_y2 = 0.88;
    if(opt.Contains("bcenter")){
        leg_x1 = 0.4;
        leg_y1 = 0.15;
        leg_x2 = 0.6;
        leg_y2 = 0.3;
    }
    else if(opt.Contains("left")){
        leg_x1 = 0.15;
        leg_y1 = 0.55;
        leg_x2 = 0.35;
        leg_y2 = 0.88;
    }
    l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    l->SetFillStyle(0);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->SetTextSize(0.035);
    l->SetTextFont(42);

    THStack hs("hs","hs");

    for(std::size_t ihist=0; ihist<hist.size();){
        if(opt.Contains("eff")){
            if((ihist+1)>=hist.size()) break;
            hist[ihist+1]->SetLineColor(colarray[ihist%10]);
            hist[ihist+1]->SetMarkerColor(colarray[ihist%10]);
            hist[ihist+1]->SetMarkerStyle(markarray[ihist%10]);
            hist[ihist+1]->Divide(hist[ihist+1],hist[0],1,1);
            ihist++;
        }
        else{
            hist[ihist]->SetLineColor(colarray[ihist%10]);
            hist[ihist]->SetMarkerColor(colarray[ihist%10]);
            hist[ihist]->SetMarkerStyle(markarray[ihist%10]);
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
    if(opt.Contains("eff")){
        hs.SetMaximum(1.3);
        hs.SetMinimum(0.5);
    }
    hs.Draw(drawopt);
    //! TO remove Overflow Bin
    // if((histname.back().Contains("Unfolded")||histname.back().Contains("unfolded")||histname.back().Contains("Graphical")) && !histname.back().Contains("Y"))
        // hs.GetXaxis()->SetRange(1,hist[0]->GetNbinsX()-1);
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
        latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary}} PbPb 1.69nb^{-1} (5.02 TeV)");
    else
        latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary Simulation}}");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.41,0.92,eopt[0]);
        latex.DrawLatexNDC(0.78,0.92,eopt[1]);
    }    
    latex.SetTextSize(0.035);
    if(eopt.size()>2){
        for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
            if(opt.Contains("bcenter")){
                leg_y2+=0.06;
                latex.DrawLatexNDC(leg_x1,leg_y2,eopt[ind]);
            }
            else{
                leg_y1-=0.06;
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
    gStyle->SetPalette(kBird);

    TCanvas *c;
    // TLegend *l;
    float leg_x1 = 0.6;
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
        // hist[ihist]->SetMarkerSize(0.05);   
        hist[ihist]->Draw(drawopt);   
        TLatex latex;
        latex.SetTextSize(0.035);
        if(label.Contains("Data"))
            latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary}} PbPb 1.69nb^{-1} (5.02 TeV)");
        else
            latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary Simulation}}");

        if(eopt[0].Contains("Cent")){
            latex.DrawLatexNDC(0.78,0.92,eopt[0]);
        }
        else if(eopt.size()>=2){
            latex.DrawLatexNDC(0.41,0.92,eopt[0]);
            latex.DrawLatexNDC(0.78,0.92,eopt[1]);
        }    
        latex.SetTextSize(0.035);
        if(eopt.size()>2){
            for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
                if(eopt.back().Contains("bcenter")){
                    leg_y2+=0.06;
                    latex.DrawLatexNDC(leg_x1,leg_y2,eopt[ind]);
                }
                else{
                    leg_y1-=0.06;
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
    // "width" = Divide by Bin Width
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
    
    TString drawopt = "E1][P0"; 
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
        latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary}} PbPb 1.69nb^{-1} (5.02 TeV)");
    else
        latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary Simulation}}");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.78,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.41,0.92,eopt[0]);
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
    c->Write("",TObject::kOverwrite);
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
}


int main(int argc, char* argv[]){

    // printf("argc = %d\n",argc);
    // printf("argv = %s\n",argv[0]);
    if(argc==7){
        output_path = argv[1];
        label = argv[2];
        plot_unfolded(argv[3],argv[4],atoi(argv[5]),atoi(argv[6]));
    }
    else if(argc==8){
        output_path = argv[1];
        label = argv[2];
        x_label = argv[7];
        plot_unfolded(argv[3],argv[4],atoi(argv[5]),atoi(argv[6]));
    }
    else{
        printf("Run with \n ./plot_unfolded <output dir> <label> <file1> <file2> <flag> <xJ bin> <<x label>>\n");
    }

    return 0;
}