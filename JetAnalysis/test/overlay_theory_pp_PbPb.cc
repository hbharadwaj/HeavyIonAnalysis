#include <TLegend.h>        // needed for Legend
#include <TCanvas.h>        // needed for Canvas
#include <TMath.h>          //! needed for floating values in plots for some reason
#include <THStack.h>        // needed for THStack
#include <TLatex.h>         // needed for TLatex
#include "TFile.h"          // needed for TFile

TString centstring="";
TString label="";
TCanvas c;
TString output_path = "Overlay_theory";
Bool_t flag_add_theory = true;

void write_theory(TString out_filename){
    const int nbins = 14;
    Double_t bin_center[] = {0.0025,0.0075,0.0125,0.0175,0.0225,0.0275,0.0325,0.0375,0.045,0.055,0.065,0.08,0.1075,0.1375}; 
    Double_t vacuum_center[] = {0.704774,2.33436,7.7861,14.8642,18.8961,20.7584,19.6572,17.785,15.4143,11.5469,8.49999,4.81468,0.999461,0.00730948};
    Double_t vacuum_err[] = {0.0691644,0.0915652,0.162143,0.261015,0.296149,0.341575,0.340316,0.344485,0.237784,0.209247,0.18301,0.0970873,0.0334525,0.00255189};
    Double_t medium_up[] = {1.03284742215687,2.83347421819892,9.24791143333554,17.5147971902724,23.1177985856312,25.1018718866859,23.4661494197575,20.4896569093417,15.4797490714611,9.92429083191286,6.20570490064862,2.96882287137053,0.519753113556775,0.004401882822613};
    Double_t medium_do[] = {0.96003794864313,2.74848424280108,9.09135734726446,17.2878371637276,22.8416796763688,24.7887908913141,23.1495648482425,20.1826185646583,15.2842428585389,9.76506633348714,6.07743026975138,2.90470222882947,0.500637191923225,0.002664498381587};
    Double_t ratio_up[] = {1.56190096479151,1.24591477609978,1.20419853340677,1.19261550252738,1.23652203710247,1.22286102661245,1.20776673411791,1.1672137221034,1.01455325954627,0.869500608898365,0.739828277918956,0.623946651561149,0.530050257746967,0.689774021732687};
    Double_t ratio_do[] = {1.26579326172649,1.14530100081552,1.15118718994639,1.14875734996384,1.19569827618969,1.18053532272083,1.16366532477146,1.11967272568968,0.98125530328175,0.835663302229297,0.705248148100368,0.595973488552005,0.490890334712369,0.276967963223835};

    Double_t errx_up[20],errx_do[20], medium_center[20],ratio_center[20], vacuum_up[20], vacuum_do[20];

    std::copy(std::begin(vacuum_err), std::end(vacuum_err), std::begin(vacuum_up));
    std::copy(std::begin(vacuum_err), std::end(vacuum_err), std::begin(vacuum_do));
    errx_do[0] = bin_center[0];
    errx_up[nbins-1] =  0;
    medium_center[0] = (medium_up[0] + medium_do[0])/2.0;
    medium_up[0] -= medium_center[0];
    medium_do[0]  = medium_center[0] - medium_do[0];
    ratio_center[0]  = (ratio_up[0]  + ratio_do[0] )/2.0;
    ratio_up[0] -= ratio_center[0];
    ratio_do[0]  = ratio_center[0]-ratio_do[0];
    for(int i=1;i<nbins;i++){
        errx_up[i-1] = ((bin_center[i-1]+bin_center[i])/2.0) - bin_center[i-1];
        errx_do[i] = errx_up[i-1];

        medium_center[i] = (medium_up[i] + medium_do[i])/2.0;
        medium_up[i] -= medium_center[i];
        medium_do[i]  = medium_center[i]-medium_do[i];
        
        ratio_center[i]  = (ratio_up[i]  + ratio_do[i] )/2.0;
        ratio_up[i] -= ratio_center[i];
        ratio_do[i]  = ratio_center[i]-ratio_do[i];

    }
    auto vacuum_graph = new TGraphAsymmErrors(nbins,bin_center,vacuum_center,errx_up,errx_do,vacuum_up,vacuum_do);
    auto medium_graph = new TGraphAsymmErrors(nbins,bin_center,medium_center,errx_up,errx_do,medium_up,medium_do);
    auto ratio_graph  = new TGraphAsymmErrors(nbins,bin_center,ratio_center ,errx_up,errx_do,ratio_up ,ratio_do );

    TString DIR = output_path +"/";
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);
    
    TFile *f_out = new TFile(output_path+"/"+out_filename+".root", "recreate");
    vacuum_graph->Write("vacuum_graph",TObject::kWriteDelete);
    medium_graph->Write("medium_graph",TObject::kWriteDelete);
    ratio_graph->Write("ratio_graph",TObject::kWriteDelete);

    f_out->Close();

}

void overlay_theory(TString file_PbPb, TString label_PbPb, TString file_pp, TString label_pp="", TString out_label="",TString varname="Rg"){
    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();
    gErrorIgnoreLevel = kFatal;
    if(label_pp==""){
        label_pp = label_PbPb;
        out_label = label_PbPb;
    } 
    label = out_label;
    TFile *f_PbPb = TFile::Open(file_PbPb);
    TFile *f_pp = TFile::Open(file_pp);

    TFile *f_theory_Elastic_noWake;   
    TFile *f_theory_Elastic_Wake;     
    TFile *f_theory_noElastic_noWake; 
    TFile *f_theory_noElastic_Wake;   

    TGraphAsymmErrors *h_theory_Elastic_noWake;   
    TGraphAsymmErrors *h_theory_Elastic_Wake;     
    TGraphAsymmErrors *h_theory_noElastic_noWake; 
    TGraphAsymmErrors *h_theory_noElastic_Wake; 

    if(flag_add_theory){
        f_theory_Elastic_noWake  = TFile::Open(output_path+"/Theory_graph/HYBRID_Elastic_Wake_0_"+varname+".root");
        f_theory_Elastic_Wake    = TFile::Open(output_path+"/Theory_graph/HYBRID_Elastic_Wake_1_"+varname+".root");
        f_theory_noElastic_noWake= TFile::Open(output_path+"/Theory_graph/HYBRID_NoElastic_Wake_0_"+varname+".root");
        f_theory_noElastic_Wake  = TFile::Open(output_path+"/Theory_graph/HYBRID_NoElastic_Wake_1_"+varname+".root");

        h_theory_Elastic_noWake  = (TGraphAsymmErrors*)f_theory_Elastic_noWake->Get("ratio_graph");
        h_theory_Elastic_Wake    = (TGraphAsymmErrors*)f_theory_Elastic_Wake->Get("ratio_graph");
        h_theory_noElastic_noWake= (TGraphAsymmErrors*)f_theory_noElastic_noWake->Get("ratio_graph");
        h_theory_noElastic_Wake  = (TGraphAsymmErrors*)f_theory_noElastic_Wake->Get("ratio_graph");        
    }

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

    TString DIR = output_path;//"Overlay_theory/";
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    TFile *fout = new TFile(output_path+"/"+label+".root","RECREATE");
    TLegend *l;
    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetHistTopMargin(0);
    // gStyle->SetCanvasDefH(800); 
    // gStyle->SetCanvasDefW(500);
    c.SetCanvasSize(700,820);
    c.SetWindowSize(750,910);
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

        if(flag_add_theory){
            h_theory_Elastic_noWake->SetFillColor(kredLight);
            h_theory_Elastic_Wake->SetFillColor(kspringLight);
            h_theory_noElastic_noWake->SetFillColor(kazureLight);
            h_theory_noElastic_Wake->SetFillColor(korangeLight);
        }

    float lower_pad_ratio = 0.3;
    float upper_pad_ratio = 1-lower_pad_ratio;

    // Upper plot will be in pad1
        TPad *pad1 = new TPad("pad1", "pad1", 0, lower_pad_ratio, 1, 1.0);
        pad1->SetTopMargin(0.4*lower_pad_ratio);
        pad1->SetRightMargin(0.05); 
        pad1->SetLeftMargin(0.15); 
        pad1->SetBottomMargin(0.025); 
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
        hPbPb_tot->GetXaxis()->SetRangeUser(hPbPb_nom->GetXaxis()->GetBinLowEdge(1),hPbPb_nom->GetXaxis()->GetBinUpEdge(hPbPb_nom->GetNbinsX()-1));
        
        float leg_x1 = 0.5;
        float leg_y1 = 0.58;
        float leg_x2 = 0.85;
        float leg_y2 = 0.85;
        l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
        l->SetFillStyle(0);
        l->SetFillColor(0);
        l->SetLineColor(0);
        l->SetTextSize(0.11*lower_pad_ratio);
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
        latex.SetTextSize(0.11*lower_pad_ratio);
        latex.DrawLatexNDC(0.15,0.92,"CMS #it{#bf{Preliminary}}");
        latex.DrawLatexNDC(0.42,0.92,"#bf{PbPb 1.69 nb^{-1}, pp 300.6 pb^{-1} (5.02 TeV)}");
        latex.SetTextSize(0.11*lower_pad_ratio);
        leg_y1-=0.06;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Cent. 0-30%");
        leg_y1-=0.06;
        latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma }>100 GeV,x_{J}>0.4,|#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi");
        leg_x1=0.2;
        leg_y1=0.85;
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
        TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, lower_pad_ratio);
        pad2->SetTopMargin(0.025);
        pad2->SetRightMargin(0.05); 
        pad2->SetLeftMargin(0.15); 
        pad2->SetBottomMargin(0.4*upper_pad_ratio); 
        // pad2->SetGrid();
        pad2->Draw();
        pad2->cd();       // pad2 becomes the current pad

        leg_x1 = 0.6;
        leg_y1 = 0.75;
        leg_x2 = 0.9;
        leg_y2 = 0.95;
        TLegend *l_ratio_1 = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
        l_ratio_1->SetFillStyle(0);
        l_ratio_1->SetFillColor(0);
        l_ratio_1->SetLineColor(0);
        l_ratio_1->SetTextSize(0.09*upper_pad_ratio);
        l_ratio_1->SetTextFont(42);

        // l_ratio_1->AddEntry(hratio, "Ratio", "lep");
        l_ratio_1->AddEntry(h_theory_Elastic_noWake,   "Hybrid Elastic, no Wake ", "f");
        l_ratio_1->AddEntry(h_theory_Elastic_Wake,     "Hybrid Elastic,    Wake ", "f");
        // l_ratio_1->AddEntry(h_theory_noElastic_noWake, "Hybrid no Elastic, no Wake ", "f");
        // l_ratio_1->AddEntry(h_theory_noElastic_Wake,   "Hybrid no Elastic,    Wake ", "f");

        leg_x1 = 0.2;
        leg_y1 = 0.75;
        leg_x2 = 0.5;
        leg_y2 = 0.95;

        TLegend *l_ratio_2 = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
        l_ratio_2->SetFillStyle(0);
        l_ratio_2->SetFillColor(0);
        l_ratio_2->SetLineColor(0);
        l_ratio_2->SetTextSize(0.09*upper_pad_ratio);
        l_ratio_2->SetTextFont(42);

        // l_ratio_2->AddEntry(hratio, "Ratio", "lep");
        // l_ratio_2->AddEntry(h_theory_Elastic_noWake,   "Hybrid    Elastic, no Wake ", "f");
        // l_ratio_2->AddEntry(h_theory_Elastic_Wake,     "Hybrid    Elastic,    Wake ", "f");
        l_ratio_2->AddEntry(h_theory_noElastic_noWake, "Hybrid no Elastic, no Wake ", "f");
        l_ratio_2->AddEntry(h_theory_noElastic_Wake,   "Hybrid no Elastic,    Wake ", "f");

        hratio->Draw("E1P0");
        if(flag_add_theory){
            h_theory_Elastic_noWake->Draw("SAME_P3");
            h_theory_Elastic_Wake->Draw("SAME_P3");
            h_theory_noElastic_noWake->Draw("SAME_P3");
            h_theory_noElastic_Wake->Draw("SAME_P3");
            l_ratio_1->Draw();
            l_ratio_2->Draw();
        }
        // hratio_stat->Draw("SAME_P5");
        hratio_tot->Draw("SAME_P5");
        hratio_sys->Draw("SAME_P5");
        hratio->Draw("SAME_E1_][P0");
        hratio->GetXaxis()->SetRangeUser(hPbPb_nom->GetXaxis()->GetBinLowEdge(1),hPbPb_nom->GetXaxis()->GetBinUpEdge(hPbPb_nom->GetNbinsX()-1));

        TLine *line=new TLine(hPbPb_nom->GetXaxis()->GetBinLowEdge(1),1.0,hratio->GetXaxis()->GetBinLowEdge(hratio->GetNbinsX()),1.0);
        line->SetLineColor(kRed);
        // line->SetLineStyle(2);
        line->SetLineWidth(3);
        line->Draw("SAME");

        hratio->SetMinimum(0.);
        hratio->SetMaximum(2.);


        // Y axis ratio plot settings
            hratio->GetYaxis()->SetTitle("#frac{PbPb}{pp}         ");
            hratio->GetYaxis()->SetNdivisions(-4);
            hratio->GetYaxis()->SetTitleSize(0.12*upper_pad_ratio);
            hratio->GetYaxis()->SetTitleOffset(1.0*upper_pad_ratio);
            hratio->GetYaxis()->SetLabelFont(42); // Absolute font size in pixel (precision 3)
            hratio->GetYaxis()->SetLabelSize(0.1*upper_pad_ratio);
            
        // X axis ratio plot settings
            hratio->GetXaxis()->SetTitleSize(0.12*upper_pad_ratio);
            hratio->GetXaxis()->SetTitleOffset(1.5*upper_pad_ratio);
            hratio->GetXaxis()->SetLabelFont(42); // Absolute font size in pixel (precision 3)
            hratio->GetXaxis()->SetLabelSize(0.1*upper_pad_ratio);
        
        if(label.Contains("Rg")){
            hratio->GetXaxis()->SetTitle("R_{g}");
            hPbPb_tot->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{dR_{g}}");
            hPbPb_tot->SetMinimum(0.0);
            hPbPb_tot->SetMaximum(15.0);
        }
        else{
            hratio->GetXaxis()->SetTitle("#it{g}");
            hPbPb_tot->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{d#it{g}}");
            hPbPb_tot->SetMinimum(0.0);
            hPbPb_tot->SetMaximum(30.0);
        }

        // hratio->GetXaxis()->SetTitle(hPbPb_nom->GetXaxis()->GetTitle());
        // hPbPb_stat->GetYaxis()->SetTitle(hPbPb_nom->GetYaxis()->GetTitle());
   
    // Y axis upper plot settings
        hPbPb_tot->GetYaxis()->SetTitleSize(0.12*lower_pad_ratio);
        hPbPb_tot->GetYaxis()->SetTitleFont(42);
        hPbPb_tot->GetYaxis()->SetTitleOffset(5.0*lower_pad_ratio);
        hPbPb_tot->GetYaxis()->SetLabelSize(0.1*lower_pad_ratio);

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

    c.SaveAs(output_path+"/"+label+".png"); 
    c.SaveAs(output_path+"/"+label+".root"); 
    c.Write(label,TObject::kOverwrite);

    fout->Close();
    
}