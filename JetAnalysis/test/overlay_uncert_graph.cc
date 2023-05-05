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

void overlay_uncert_graph(TString file_PbPb, TString label_PbPb, TString file_pp, TString label_pp="", TString out_label=""){
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
    TGraphAsymmErrors *hPbPb_tot = (TGraphAsymmErrors*)f_PbPb->Get("sys_uncert");// (TGraphAsymmErrors*)f_PbPb->Get("tot_uncert");

    TH1D *hpp_nom = (TH1D*)f_pp->Get(label_pp+"_nom");
    TGraphAsymmErrors *hpp_stat = (TGraphAsymmErrors*)f_pp->Get("stat_uncert");
    TGraphAsymmErrors *hpp_sys = (TGraphAsymmErrors*)f_pp->Get("sys_uncert");
    TGraphAsymmErrors *hpp_tot = (TGraphAsymmErrors*)f_pp->Get("tot_uncert");

    Double_t PbPb_untagged = hPbPb_nom->Integral(0,1)/hPbPb_nom->Integral(0,-1);
    Double_t pp_untagged = hpp_nom->Integral(0,1)/hpp_nom->Integral(0,-1);

    TString DIR = "Overlay_uncert/";
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    TFile *fout = new TFile("Overlay_uncert/"+label+".root","RECREATE");
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
     
    // Upper plot will be in pad1
        TPad *pad1 = new TPad("pad1", "pad1", 0, 0., 1, 1.0);
        pad1->SetTopMargin(0.1);
        pad1->SetRightMargin(0.05); 
        pad1->SetLeftMargin(0.12); 
        pad1->SetBottomMargin(0.12); 
        pad1->Draw();             // Draw the upper pad: pad1
        pad1->cd();               // pad1 becomes the current pad
        float ymax = 1.2*hpp_nom->GetMaximum();
        if(hPbPb_nom->GetMaximum()>hpp_nom->GetMaximum()) ymax = 1.2*hPbPb_nom->GetMaximum();
        
        // hPbPb_stat->Draw("AP2");
        
        hPbPb_tot->Draw("AP5");
        // hPbPb_sys->Draw("P5");
        // hpp_stat->Draw("P2");
        
        hpp_tot->Draw("P5");
        hpp_sys->Draw("P5");
        hPbPb_nom->Draw("SAME_E1_][P0");
        hpp_nom->Draw("SAME_E1_][P0");

        hPbPb_tot->SetMaximum(ymax);
        // hPbPb_tot->GetXaxis()->SetLabelSize(0);
        // hpp_sys->GetXaxis()->SetLabelSize(0);
        // hPbPb_tot->GetXaxis()->SetTitleOffset(999999);
        // hpp_sys->GetXaxis()->SetTitleOffset(999999);
        hPbPb_tot->GetXaxis()->SetRangeUser(hPbPb_nom->GetXaxis()->GetBinLowEdge(1),hPbPb_nom->GetXaxis()->GetBinUpEdge(hPbPb_nom->GetNbinsX()));
        
        float leg_x1 = 0.6;
        float leg_y1 = 0.58;
        float leg_x2 = 0.8;
        float leg_y2 = 0.85;
        l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
        l->SetFillStyle(0);
        l->SetFillColor(0);
        l->SetLineColor(0);
        l->SetTextSize(0.035);
        l->SetTextFont(42);

        // l->AddEntry(hPbPb_nom, "PbPb stat. uncert", "lep");
        // l->AddEntry(hPbPb_sys, "PbPb sys. uncert", "f");
        // l->AddEntry(hPbPb_tot, "PbPb total(stat. + sys.)", "f");
        // l->AddEntry(hpp_nom, "pp stat. uncert", "lep");
        // l->AddEntry(hpp_sys, "pp sys. uncert", "f");
        // l->AddEntry(hpp_tot, "pp total(stat. + sys.)", "f");

        // l->AddEntry(hPbPb_nom, "MatInvert stat. uncert", "lep");
        // l->AddEntry(hPbPb_sys, "MatInvert sys. uncert", "f");
        // l->AddEntry(hPbPb_tot, "MatInvert total(stat. + sys.)", "f");
        // l->AddEntry(hpp_nom, "D'Agostini stat. uncert", "lep");
        // l->AddEntry(hpp_sys, "D'Agostini sys. uncert", "f");
        // l->AddEntry(hpp_tot, "D'Agostini total(stat. + sys.)", "f");

        l->AddEntry(hPbPb_nom, "Pre-Approval Result", "lep");
        // l->AddEntry(hPbPb_sys, "MatInvert sys. uncert", "f");
        l->AddEntry(hPbPb_tot, "Pre-Approval sys", "f");
        l->AddEntry(hpp_nom, "Updated stat. uncert", "lep");
        l->AddEntry(hpp_sys, "Updated sys. uncert", "f");
        l->AddEntry(hpp_tot, "Updated total(stat. + sys.)", "f");
        l->Draw();

        TLatex latex;
        latex.SetTextSize(0.035);
        latex.DrawLatexNDC(0.12,0.92,"CMS #it{#bf{Preliminary}}");
        // latex.DrawLatexNDC(0.55,0.9,"PbPb 1.69 nb^{-1}, pp 300.6 pb^{-1} (5.02 TeV)");
        latex.SetTextSize(0.035);
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Cent. 0-30%");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma }>100 GeV,x_{J}>0.4,|#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi");
        if(label.Contains("Rg")){
            leg_y1-=0.08;
            // latex.DrawLatexNDC(leg_x1,leg_y1,Form("PbPb untagged = %4.2f%%",PbPb_untagged*100));
            // latex.DrawLatexNDC(leg_x1,leg_y1,Form("MatInvert untagged = %4.2f%%",PbPb_untagged*100));
            latex.DrawLatexNDC(leg_x1,leg_y1,Form("Pre-Approval untagged = %4.2f%%",PbPb_untagged*100));
            leg_y1-=0.08;
            // latex.DrawLatexNDC(leg_x1,leg_y1,Form("pp untagged = %4.2f%%",pp_untagged*100));
            // latex.DrawLatexNDC(leg_x1,leg_y1,Form("D'Agostini untagged = %4.2f%%",pp_untagged*100));
            latex.DrawLatexNDC(leg_x1,leg_y1,Form("Updated untagged = %4.2f%%",pp_untagged*100));
        }

            
        // X axis ratio plot settings
            // hratio->GetXaxis()->SetTitleSize(0.14);
            // hratio->GetXaxis()->SetTitleOffset(1.0);
            // hratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
            // hratio->GetXaxis()->SetLabelSize(15);
        
        if(label.Contains("Rg")){
            hPbPb_tot->GetXaxis()->SetTitle("R_{g}");
            hPbPb_tot->GetYaxis()->SetTitle("1/N_{jet} dN/dR_{g}");
            hPbPb_tot->SetMinimum(0.0);
            hPbPb_tot->SetMaximum(12.0);
        }
        else{
            hPbPb_tot->GetXaxis()->SetTitle("Girth ");
            hPbPb_tot->GetYaxis()->SetTitle("1/N_{jet} dN/dg");
            hPbPb_tot->SetMinimum(0.0);
            hPbPb_tot->SetMaximum(24.0);
        }

        // hratio->GetXaxis()->SetTitle(hPbPb_nom->GetXaxis()->GetTitle());
        // hPbPb_stat->GetYaxis()->SetTitle(hPbPb_nom->GetYaxis()->GetTitle());
   
    // Y axis upper plot settings

        hPbPb_tot->GetYaxis()->SetTitleSize(20);
        hPbPb_tot->GetYaxis()->SetTitleFont(43);
        hPbPb_tot->GetYaxis()->SetTitleOffset(1.0);
        hPbPb_tot->GetYaxis()->SetLabelSize(0.04);
        // hPbPb_nom->GetYaxis()->SetTitleSize(15);
        // hPbPb_nom->GetYaxis()->SetTitleFont(43);
        // hPbPb_nom->GetYaxis()->SetTitleOffset(1.5);
        // hPbPb_nom->GetYaxis()->SetLabelSize(0.05);

        // hPbPb_stat->GetYaxis()->SetTitleSize(15);
        // hPbPb_stat->GetYaxis()->SetTitleFont(43);
        // hPbPb_stat->GetYaxis()->SetTitleOffset(1.5);
        // hPbPb_stat->GetYaxis()->SetLabelSize(0.05);

        hPbPb_tot->GetXaxis()->SetTitleSize(20);
        hPbPb_tot->GetXaxis()->SetTitleFont(43);
        hPbPb_tot->GetXaxis()->SetTitleOffset(1.0);
        hPbPb_tot->GetXaxis()->SetLabelSize(0.04);
    

    gPad->Update();
    c.SaveAs("Overlay_uncert/"+label+".png"); 
    c.SaveAs("Overlay_uncert/"+label+".C"); 
    // c.SaveAs("Overlay_ppPbPb/"+label+".root"); 
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
        "Anti-#it{k}_{T} #it{R}=0.2","z_{cut}=0.2"};// "p_{T}^{#gamma }>100, Jet p_{T}>40, |#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi"

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