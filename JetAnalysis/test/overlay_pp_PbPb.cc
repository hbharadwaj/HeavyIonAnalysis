// overlay_theory({"Overlay_theory/Theory_graph/HYBRID_Elastic_Wake_0_Rg_xJ_gp8.root","Overlay_theory/Theory_graph/HYBRID_Elastic_Wake_1_Rg_xJ_gp8.root","Overlay_theory/Theory_graph/HYBRID_NoElastic_Wake_0_Rg_xJ_gp8.root","Overlay_theory/Theory_graph/HYBRID_NoElastic_Wake_1_Rg_xJ_gp8.root"},{"Elastic NoWake","Elastic Wake","NoElastic NoWake","NoElastic Wake"},"Uncertainty/OutputCombined_Jul_31_Decorrelate_PF/Data_0_30_Jul_31_PbPb_2018_sys_Decorrelate_PF_xJ_gp8_Data_Rg_unfold_X.root","Data_0_30_Jul_31_PbPb_2018_sys_Decorrelate_PF_xJ_gp8_Data_Rg_unfold_X","~/pp_analysis/Analysis/Uncertainty/OutputCombined_Jul_31_Decorrelate_PF/pp_Data_Jul_31_pp_2017_sys_Decorrelate_PF_xJ_gp8_Data_Rg_unfold_X.root","pp_Data_Jul_31_pp_2017_sys_Decorrelate_PF_xJ_gp8_Data_Rg_unfold_X","PbPb_pp_0_30_Jul_31_Rg_xJ_gp8_Preliminary_ratio","Rg_xJ_gp8")
#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include "TBox.h"
#include "TASImage.h"
#include <iostream>
#include "TStyle.h"

#include <TLegend.h>        // needed for Legend
#include <TCanvas.h>        // needed for Canvas
#include <TMath.h>          //! needed for floating values in plots for some reason
#include <THStack.h>        // needed for THStack
#include <TLatex.h>         // needed for TLatex
#include "TFile.h"          // needed for TFile
 
TString centstring="";
TString label="";
// TCanvas c;
TString output_path = "Overlay_ppPbPb";
Bool_t flag_add_theory = true;

//--------------------------------------------------------------------------------
// CMS_lumi.h
//--------------------------------------------------------------------------------
//
// Global variables
//

TString cmsText     = "CMS";
float cmsTextFont   = 61;  // default is helvetic-bold

bool writeExtraText = false;
TString extraText   = "Preliminary";
float extraTextFont = 52;  // default is helvetica-italics

// text sizes and text offsets with respect to the top frame
// in unit of the top margin size
float lumiTextSize     = 0.6;
float lumiTextOffset   = 0.15;
float cmsTextSize      = 0.75;
float cmsTextOffset    = 0.12;  // only used in outOfFrame version

float relPosX    = 0.1;//0.045;
float relPosY    = 0.035;//0.035;
float relExtraDY = 1.2;

// ratio of "CMS" and extra text size
float extraOverCmsTextSize  = 0.8;//0.76;

TString lumi_13TeV      = "20.1 fb^{-1}";
TString lumi_8TeV       = "19.7 fb^{-1}";
TString lumi_7TeV       = "5.1 fb^{-1}";
TString lumi_5TeV_PbPb  = "PbPb 1.7 nb^{-1}";
TString lumi_5TeV_pp    = "pp 301 pb^{-1}";
TString lumi_sqrtS = "";

bool drawLogo      = false;

void CMS_lumi( TPad* pad, int iPeriod=3, int iPosX=10 );

//--------------------------------------------------------------------------------
// CMS_lumi.C
//--------------------------------------------------------------------------------

void 
CMS_lumi( TPad* pad, int iPeriod, int iPosX )
{            
    
  bool outOfFrame    = false;
  if( iPosX/10==0 ) 
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  //if( iPosX == 0  ) relPosX = 0.12;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  //  float e = 0.025;

  // std::cout<<"\n Pad Name for lumi plot : "<<pad->GetName();
  // std::cout<<"\n Pad Left margin : "<<l<<"\t Pad Top margin : "<<t;

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 ) 
    {
      lumiText = lumi_8TeV; 
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
    }
  else if ( iPeriod==7 )
    { 
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV; 
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV; 
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }
  else if ( iPeriod==100 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_5TeV_PbPb;
      lumiText += ", ";
      lumiText += lumi_5TeV_pp;
      lumiText += " (5.02 TeV)";
      if( outOfFrame) lumiText += "}";
    }  
  else if ( iPeriod==200 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_5TeV_PbPb;
      lumiText += " (5.02 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==300 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_5TeV_pp;
      lumiText += " (5.02 TeV)";
      if( outOfFrame) lumiText += "}";
    } 
    
  else if ( iPeriod==0 )
    {
      lumiText += lumi_sqrtS;
    }
   
  // std::cout <<"\n"<< lumiText << endl;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(lumiTextSize*t);    
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if( outOfFrame )
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextAlign(11); 
      latex.SetTextSize(cmsTextSize*t);    
      latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
    }
  
  pad->cd();

  float posX_=0;
  if( iPosX%10<=1 )
    {
      posX_ =   l + relPosX*(1-l-r);
    }
  else if( iPosX%10==2 )
    {
      posX_ =  l + 0.5*(1-l-r);
    }
  else if( iPosX%10==3 )
    {
      posX_ =  1-r - relPosX*(1-l-r);
    }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
    {
      if( drawLogo )
	{
	  posX_ =   l + 0.045*(1-l-r)*W/H;
	  posY_ = 1-t - 0.045*(1-t-b);
	  float xl_0 = posX_;
	  float yl_0 = posY_ - 0.15;
	  float xl_1 = posX_ + 0.15*H/W;
	  float yl_1 = posY_;
	  TASImage* CMS_logo = new TASImage("CMSlogo_color_label_1024_May2014.png");
	  TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
	  pad_logo->Draw();
	  pad_logo->cd();
	  CMS_logo->Draw("X");
	  pad_logo->Modified();
	  pad->cd();
	}
      else
	{
	  latex.SetTextFont(cmsTextFont);
	  latex.SetTextSize(cmsTextSize*t);
	  latex.SetTextAlign(align_);
	  latex.DrawLatex(posX_, posY_, cmsText);
	  if( writeExtraText ) 
	    {
	      latex.SetTextFont(extraTextFont);
	      latex.SetTextAlign(align_);
	      latex.SetTextSize(extraTextSize*t);
	      latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
	    }
	}
    }
  else if( writeExtraText )
    {
      if( iPosX==0) 
	{
	  posX_ =   l +  relPosX*(1-l-r);
	  posY_ =   1-t+lumiTextOffset*t;
	}
      latex.SetTextFont(extraTextFont);
      latex.SetTextSize(extraTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, extraText);      
    }
  return;
}

//--------------------------------------------------------------------------------
// tdrstyle.C
//--------------------------------------------------------------------------------

// tdrGrid: Turns the grid lines on (true) or off (false)

// void tdrGrid(bool gridOn) {
//   tdrStyle->SetPadGridX(gridOn);
//   tdrStyle->SetPadGridY(gridOn);
// }

// fixOverlay: Redraws the axis

void fixOverlay() {
  gPad->RedrawAxis();
}

void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);
  
// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
  // tdrStyle->SetErrorMarker(20);
  // tdrStyle->SetErrorX(0.);
  
  tdrStyle->SetMarkerStyle(20);
  
//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

// Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

// For the Global title:

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

// For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

// For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->SetHatchesLineWidth(5);
  tdrStyle->SetHatchesSpacing(0.05);

  // Turns the grid lines on (true) or off (false)
  // tdrStyle->SetPadGridX(true);
  // tdrStyle->SetPadGridY(true);

  tdrStyle->cd();

}

TCanvas* overlay_uncert(TString file_PbPb, TString label_PbPb, TString file_pp, TString label_pp="", TString out_label="",TString varname="Rg"){
    int iPeriod = 100;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
    // 100=PbPb+pp ,200=PbPb , 300=pp

    // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
    // iPos=11 : top-left, left-aligned
    // iPos=33 : top-right, right-aligned
    // iPos=22 : center, centered
    // iPos=0 : out of frame (in exceptional cases)
    // mode generally : 
    //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)
    int iPos = 0;
    setTDRStyle();
    // Read Input Files and histograms
    
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

    TH1D *hPbPb_nom = (TH1D*)f_PbPb->Get(label_PbPb+"_nom");
    TGraphAsymmErrors *hPbPb_stat = (TGraphAsymmErrors*)f_PbPb->Get("stat_uncert");
    TGraphAsymmErrors *hPbPb_sys = (TGraphAsymmErrors*)f_PbPb->Get("sys_uncert");
    TGraphAsymmErrors *hPbPb_tot = (TGraphAsymmErrors*)f_PbPb->Get("tot_uncert");

    TH1D *hpp_nom = (TH1D*)f_pp->Get(label_pp+"_nom");
    TGraphAsymmErrors *hpp_stat = (TGraphAsymmErrors*)f_pp->Get("stat_uncert");
    TGraphAsymmErrors *hpp_sys = (TGraphAsymmErrors*)f_pp->Get("sys_uncert");
    TGraphAsymmErrors *hpp_tot = (TGraphAsymmErrors*)f_pp->Get("tot_uncert");

    Double_t error_PbPb_num,error_PbPb_den, error_pp_num,error_pp_den;
    Double_t PbPb_num = hPbPb_nom->IntegralAndError(0,1,error_PbPb_num,"width");
    Double_t PbPb_den = hPbPb_nom->IntegralAndError(0,-1,error_PbPb_den,"width");
    Double_t PbPb_untagged = PbPb_num/PbPb_den; //hPbPb_nom->Integral(0,1)/hPbPb_nom->Integral(0,-1);

    Double_t PbPb_untagged_Err =  TMath::Abs( ( (1. - 2.* PbPb_num / PbPb_den) * (error_PbPb_num*error_PbPb_num)  + (PbPb_num*PbPb_num) * (error_PbPb_den*error_PbPb_den) / (PbPb_den*PbPb_den) ) / (PbPb_den*PbPb_den) );// TMath::Sqrt(PbPb_untagged*(1-PbPb_untagged)/PbPb_num);
    //(error_PbPb_num/PbPb_num) + (error_PbPb_den/PbPb_den); // TMath::Sqrt((error_PbPb_num/PbPb_num)*(error_PbPb_num/PbPb_num) + (error_PbPb_den/PbPb_den)*(error_PbPb_den/PbPb_den));

    Double_t pp_num = hpp_nom->IntegralAndError(0,1,error_pp_num,"width");
    Double_t pp_den = hpp_nom->IntegralAndError(0,-1,error_pp_den,"width");
    Double_t pp_untagged = pp_num/pp_den;//hpp_nom->Integral(0,1)/hpp_nom->Integral(0,-1);

    Double_t pp_untagged_Err = TMath::Abs( ( (1. - 2.* pp_num / pp_den) * (error_pp_num*error_pp_num)  + (pp_num*pp_num) * (error_pp_den*error_pp_den) / (pp_den*pp_den) ) / (pp_den*pp_den) );//TMath::Sqrt(pp_untagged*(1-pp_untagged)/pp_num);
    //TMath::Sqrt((error_pp_num/pp_num)*(error_pp_num/pp_num) + (error_pp_den/pp_den)*(error_pp_den/pp_den));//(error_pp_num/pp_num) + (error_pp_den/pp_den);

    Double_t PbPb_total_sys_err_up=0,PbPb_total_sys_err_do=0,pp_total_sys_err_up=0,pp_total_sys_err_do=0;
    Double_t PbPb_untag_sys_err_up=0,PbPb_untag_sys_err_do=0,pp_untag_sys_err_up=0,pp_untag_sys_err_do=0;

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

        Double_t erry_pp_sys_a = 0;
        Double_t erry_pp_sys_b = 0;

        Double_t erry_PbPb_sys_a = 0;
        Double_t erry_PbPb_sys_b = 0;

        Double_t erry_uncorr_up = 0;
        Double_t erry_uncorr_do = 0;

        Double_t erry_ratio_total_up = 0;
        Double_t erry_ratio_total_do = 0;

        if(temp_pp_y!=0 && temp_PbPb_y!=0) {

        erry_pp_sys_a = hpp_sys->GetErrorYhigh(j)/temp_pp_y;
        erry_pp_sys_b = hpp_sys->GetErrorYlow(j)/temp_pp_y;

        erry_PbPb_sys_a = hPbPb_sys->GetErrorYhigh(j)/temp_PbPb_y;
        erry_PbPb_sys_b = hPbPb_sys->GetErrorYlow(j)/temp_PbPb_y;

        erry_uncorr_up = TMath::Sqrt(erry_pp_sys_a*erry_pp_sys_a + erry_PbPb_sys_a*erry_PbPb_sys_a);
        erry_uncorr_do = TMath::Sqrt(erry_pp_sys_b*erry_pp_sys_b + erry_PbPb_sys_b*erry_PbPb_sys_b);

        erry_ratio_total_up = TMath::Sqrt(erry_stat_a*erry_stat_a + erry_uncorr_up*erry_uncorr_up);
        erry_ratio_total_do = TMath::Sqrt(erry_stat_b*erry_stat_b + erry_uncorr_do*erry_uncorr_do);
        }
        

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

        // Total systematic uncert for untagged error
        PbPb_total_sys_err_up+=erry_PbPb_sys_a*erry_PbPb_sys_a;
        PbPb_total_sys_err_do+=erry_PbPb_sys_b*erry_PbPb_sys_b;

        pp_total_sys_err_up+=erry_pp_sys_a*erry_pp_sys_a;
        pp_total_sys_err_do+=erry_pp_sys_b*erry_pp_sys_b;

        if(j<=1){
          PbPb_untag_sys_err_up+=erry_PbPb_sys_a*erry_PbPb_sys_a;
          PbPb_untag_sys_err_do+=erry_PbPb_sys_b*erry_PbPb_sys_b;

          pp_untag_sys_err_up+=erry_pp_sys_a*erry_pp_sys_a;
          pp_untag_sys_err_do+=erry_pp_sys_b*erry_pp_sys_b;
        }
        // std::cout<<" Point "<<j<<" \t x = "<<temp_PbPb_x<<"\t y = "<<temp_PbPb_y<<" \t sys err up = "<<PbPb_total_sys_err_up<<"\n";
    }

    // std::cout<<"PbPb sys err up = "<<PbPb_untag_sys_err_up<<"\n";

    PbPb_untag_sys_err_up = TMath::Sqrt(PbPb_untag_sys_err_up);
    PbPb_untag_sys_err_do = TMath::Sqrt(PbPb_untag_sys_err_do);

    pp_untag_sys_err_up = TMath::Sqrt(pp_untag_sys_err_up);
    pp_untag_sys_err_do = TMath::Sqrt(pp_untag_sys_err_do);
    
    PbPb_total_sys_err_up = TMath::Sqrt(PbPb_total_sys_err_up);
    PbPb_total_sys_err_do = TMath::Sqrt(PbPb_total_sys_err_do);

    pp_total_sys_err_up = TMath::Sqrt(pp_total_sys_err_up);
    pp_total_sys_err_do = TMath::Sqrt(pp_total_sys_err_do);
    // auto hratio_stat = new TGraphAsymmErrors(hratio->GetNbinsX(),vec_x,vec_y,errx_do,errx_up,errstat_do,errstat_up);
    auto hratio_sys = new TGraphAsymmErrors(hratio->GetNbinsX()+1,vec_x,vec_y,errx_do,errx_up,erry_do,erry_up);
    auto hratio_tot = new TGraphAsymmErrors(hratio->GetNbinsX()+1,vec_x,vec_y,errx_do,errx_up,errtot_do,errtot_up);

    if(label.Contains("Rg")){
      std::cout<<"\nPbPb Untagged = "<<PbPb_num/PbPb_den <<" +- "<<PbPb_untagged_Err<<" (stat.) \t +- "<<PbPb_untag_sys_err_up/PbPb_total_sys_err_up <<"(sys up.) \t +-"<< PbPb_untag_sys_err_do/PbPb_total_sys_err_do  <<"(sys down.)\n";
      std::cout<<"\n  pp Untagged = "<<pp_num/pp_den <<" +- "<<pp_untagged_Err<<" (stat.) \t +- "<<pp_untag_sys_err_up/pp_total_sys_err_up<<"(sys up.) \t +-"<< pp_untag_sys_err_do/pp_total_sys_err_do <<"(sys down.)\n";
    }

    TString DIR = output_path;//"Overlay_theory/";
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    TFile *fout = new TFile(output_path+"/"+label+".root","RECREATE");
    
//? Histogram Styling - Update the colors and line styles
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

    float transparency = 0.6;
    hPbPb_nom->SetLineColor(kRed+1); // Red Box
    hPbPb_nom->SetMarkerColor(kRed+1);
    hPbPb_nom->SetMarkerStyle(21);
    hPbPb_nom->SetMarkerSize(1.8);
    hPbPb_nom->SetFillStyle(1000); 
    // hPbPb_nom->SetFillStyle(3945); // Not yet working
    hPbPb_nom->SetFillColorAlpha(kRed-7,transparency);

    hPbPb_tot->SetFillStyle(1000); 
    // hPbPb_tot->SetFillStyle(3945); 
    hPbPb_tot->SetFillColorAlpha(kRed-7,transparency);
    hPbPb_tot->SetLineColor(kRed-7); 
    hPbPb_tot->SetMarkerColor(kRed-7);
    hPbPb_tot->SetMarkerStyle(21);
    hPbPb_tot->SetMarkerSize(0);
     
    hpp_nom->SetLineColor(kBlue+1);
    hpp_nom->SetMarkerColor(kBlue+1);
    hpp_nom->SetMarkerStyle(24);
    hpp_nom->SetMarkerSize(1.8); //1.1
    hpp_nom->SetFillStyle(1000); 
    // hpp_nom->SetFillStyle(3054); 
    hpp_nom->SetFillColorAlpha(kBlue-7,transparency);

    hpp_tot->SetFillStyle(1000); 
    // hpp_tot->SetFillStyle(3054); 
    hpp_tot->SetFillColorAlpha(kBlue-7,transparency);
    hpp_tot->SetLineColor(kBlue-7); 
    hpp_tot->SetMarkerColor(kBlue-7);
    hpp_tot->SetMarkerStyle(24);
    hpp_tot->SetMarkerSize(0);
    
    hratio->SetLineColor(kBlack);
    hratio->SetMarkerColor(kBlack);
    hratio->SetMarkerStyle(20);
    // hratio->SetMarkerSize(0.2);
    hratio->SetFillStyle(1000); 
    hratio->SetFillColorAlpha(kGray+2,transparency);

    // hratio_tot->SetFillStyle(3244); // Grey Box //1001 for solid 
    hratio_tot->SetFillStyle(1000);
    hratio_tot->SetFillColorAlpha(kGray+2,transparency);
    hratio_tot->SetLineColor(kGray+2); 
    hratio_tot->SetMarkerColor(kBlack);
    hratio_tot->SetMarkerStyle(20);
    // hratio_tot->SetMarkerSize(0.2);

    std::vector<unsigned int> fill_col_arr = {kOrange-3,kAzure-3,kMagenta+2,kGreen+2,kRed-7,kBlue-7,kSpring+10,kViolet-3};
    std::vector<unsigned int> mark_col_arr = {kOrange+2,kAzure+0,kMagenta+0,kGreen-2,kRed+1,kBlue+1,kSpring+4 ,kViolet+0};
    std::vector<unsigned int> mark_sty_arr = {kFullStar,kFullTriangleUp,kFullCrossX,kFullSquare,kFullDiamond,kFullCircle,kFourSquaresX,kFourSquaresPlus};

    gStyle->SetHatchesLineWidth(2);
    gStyle->SetHatchesSpacing(0.8);

    hPbPb_nom->Write("",TObject::kOverwrite);
    hPbPb_sys->Write("",TObject::kOverwrite);
    hPbPb_tot->Write("",TObject::kOverwrite);
    hpp_nom->Write("",TObject::kOverwrite);
    hpp_sys->Write("",TObject::kOverwrite);
    hpp_tot->Write("",TObject::kOverwrite);
    hratio->Write("",TObject::kOverwrite);
    hratio_sys->Write("",TObject::kOverwrite);
    hratio_tot->Write("",TObject::kOverwrite);

// Defining canvas parameters with TDR style
    int W = 800;
    int H = 600;

    int W_ref = 800; 
    int H_ref = 600; 

    // references for T, B, L, R
    float T = 0.09*H_ref;//0.1*H_ref;  //0.08*H_ref;
    float B = 0.122*H_ref;//0.12*H_ref;  //0.12*H_ref; 
    float L = 0.15*W_ref;//0.15*W_ref;  //0.12*W_ref;
    float R = 0.035*W_ref;//0.08*W_ref;  //0.04*W_ref;

    TString canvName = label;
    canvName += W;
    canvName += "-";
    canvName += H;
    canvName += "_";  
    canvName += iPeriod;
    if( writeExtraText ) canvName += "-prelim";
    if( iPos%10==0 ) canvName += "-out";
    else if( iPos%10==1 ) canvName += "-left";
    else if( iPos%10==2 )  canvName += "-center";
    else if( iPos%10==3 )  canvName += "-right";

    TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
    canv->SetFillColor(0);
    canv->SetBorderMode(0);
    canv->SetFrameFillStyle(0);
    canv->SetFrameBorderMode(0);
    // canv->SetLeftMargin( L/W );
    // canv->SetRightMargin( R/W );
    // canv->SetTopMargin( T/H );
    // canv->SetBottomMargin( B/H );

    canv->SetLeftMargin(  0.05 );
    canv->SetRightMargin( 0.05 );
    canv->SetTopMargin(   0.05 );
    canv->SetBottomMargin(0.05 );

    canv->SetTickx(0);
    canv->SetTicky(0);

    canv->cd();
    TPad *pad1 = new TPad("pad1", "pad1", 0.0, 0.0, 1.0, 1.0);
    pad1->SetLeftMargin(  (L/W) );
    pad1->SetRightMargin( (R/W) );
    pad1->SetTopMargin(   (T/H) );
    pad1->SetBottomMargin((B/H) );

    // pad1->SetTopMargin(0.05);
    // pad1->SetRightMargin(0.05); 
    // pad1->SetLeftMargin(0.05); 
    // pad1->SetBottomMargin(0.05);
    pad1->Draw();
    pad1->cd();  

    float leg_x1;
    float leg_y1;
    float leg_x2;
    float leg_y2;

    leg_x1 = 0.6;
    leg_y1 = 0.75;
    leg_x2 = 0.88;
    leg_y2 = 0.88;

    TLegend *l;
    l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    l->SetFillStyle(0);
    l->SetFillColor(0);
    l->SetLineColor(0);
    // l->SetTextSize(0.04);
    // l->SetTextFont(43);
    l->SetBorderSize(0);
    
    l->SetTextSize(28);
    l->SetTextFont(43);

    l->AddEntry(hPbPb_nom, "PbPb", "lepf");
    l->AddEntry(hpp_nom, "pp", "lepf");

    float ymax = 1.2*hpp_nom->GetMaximum();
    if(hPbPb_nom->GetMaximum()>hpp_nom->GetMaximum()) ymax = 1.2*hPbPb_nom->GetMaximum();

    hPbPb_nom->Draw("SAME_E1_][P0");
    hpp_nom->Draw("SAME_E1_][P0");

    hPbPb_tot->Draw("P5");
    // hPbPb_sys->Draw("P5");
    hpp_tot->Draw("P5");
    // hpp_sys->Draw("P5");
    hPbPb_nom->Draw("SAME_E1_][P0");
    hpp_nom->Draw("SAME_E1_][P0");

    l->Draw();

    float line_left_edge = hPbPb_nom->GetXaxis()->GetBinLowEdge(1);
    if(label.Contains("Rg")){
        line_left_edge = hPbPb_nom->GetXaxis()->GetBinLowEdge(2);
    }
    hPbPb_nom->GetXaxis()->SetRangeUser(line_left_edge,hPbPb_nom->GetXaxis()->GetBinUpEdge(hPbPb_nom->GetNbinsX()-1));

// Axis settings
    canv->cd();

    float upper_pad_ratio = 1.5;
    float lower_pad_ratio = 1.5;


    // X axis upper plot settings
        hPbPb_nom->GetXaxis()->SetTitleSize(0);
        // hPbPb_nom->GetXaxis()->SetTitleOffset(1.25);
        // hPbPb_nom->GetXaxis()->SetLabelFont(42);
        hPbPb_nom->GetXaxis()->SetLabelSize(0.0);
        // hPbPb_nom->GetXaxis()->SetLabelOffset(0.007/upper_pad_ratio);
        // hPbPb_nom->GetXaxis()->SetTickLength(0.03/upper_pad_ratio);
        if(label.Contains("Rg")){
          hPbPb_nom->GetXaxis()->SetNdivisions(4,5,0,kTRUE);
        }
        else if(label.Contains("girth")){
          hPbPb_nom->GetXaxis()->SetNdivisions(5,5,0,kTRUE);
        }

    // Y axis upper plot settings
        hPbPb_nom->GetYaxis()->SetTitleFont(43);
        hPbPb_nom->GetYaxis()->SetTitleSize(30);
        hPbPb_nom->GetYaxis()->SetTitleOffset(1.);
        hPbPb_nom->GetYaxis()->SetLabelFont(43);
        hPbPb_nom->GetYaxis()->SetLabelSize(28);
        // hPbPb_nom->GetYaxis()->SetLabelOffset(0.007/upper_pad_ratio);
        hPbPb_nom->GetYaxis()->SetTickLength(0.03);

    // Y axis ratio plot settings
        hratio->GetYaxis()->SetTitle("#frac{PbPb}{pp}       ");
        // hratio->GetYaxis()->SetNdivisions(-4);
        hratio->GetYaxis()->SetTitleFont(43);
        hratio->GetYaxis()->SetTitleSize(30);
        hratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
        hratio->GetYaxis()->SetLabelSize(28);
        hratio->GetYaxis()->SetTickLength(0.03);

        hratio->GetYaxis()->SetTitleOffset(1.);
        
    // X axis  plot settings
        hPbPb_nom->GetXaxis()->SetTitleFont(43);
        hPbPb_nom->GetXaxis()->SetTitleSize(30);
        hPbPb_nom->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
        hPbPb_nom->GetXaxis()->SetLabelSize(28);
        hPbPb_nom->GetXaxis()->SetTickLength(0.03);

        hPbPb_nom->GetXaxis()->SetTitleOffset(1.);
        hPbPb_nom->GetXaxis()->SetNdivisions(hPbPb_nom->GetXaxis()->GetNdivisions());
    if(label.Contains("Rg") && label.Contains("xJ_gp8")){
        hPbPb_nom->GetXaxis()->SetTitle("Groomed jet radius R_{g}");
        hPbPb_nom->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{dR_{g}}    ");
        hPbPb_nom->SetMinimum(0.001);
        hPbPb_nom->SetMaximum(15.999);
    }
    else if(label.Contains("Rg") && label.Contains("xJ_gp4")){
        hPbPb_nom->GetXaxis()->SetTitle("Groomed jet radius R_{g}");
        hPbPb_nom->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{dR_{g}}    ");
        hPbPb_nom->SetMinimum(0.001);
        hPbPb_nom->SetMaximum(9.999); 
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp8")){
        hPbPb_nom->GetXaxis()->SetTitle("Jet girth #it{g}");
        hPbPb_nom->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{d#it{g}}   ");
        hPbPb_nom->SetMinimum(0.001);
        hPbPb_nom->SetMaximum(29.999); 
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp4")){
        hPbPb_nom->GetXaxis()->SetTitle("Jet girth #it{g}");
        hPbPb_nom->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{d#it{g}}   ");
        hPbPb_nom->SetMinimum(0.001);
        hPbPb_nom->SetMaximum(24.999);
    }

// Additional text
    canv->cd();
    CMS_lumi( pad1, iPeriod, iPos );

    pad1->cd();
    TLatex latex;
    // latex.SetNDC(1);
    // latex.SetTextFont(42);
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    
    // latex.SetTextSize(0.04);    
    latex.SetTextAlign(12); 


    latex.SetTextSize(28);
    latex.SetTextFont(43);

    if(label.Contains("Rg") && label.Contains("xJ_gp8")){
        leg_x1 = 0.6;
        leg_y1 = 0.75;
        leg_x2 = 0.88;
        leg_y2 = 0.88;
        leg_x1-=0.05;
        leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV, #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.8");
        leg_y1-= 0.12;
        // leg_x1+=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44, |#eta_{jet}| < 2");
        leg_y1-= 0.1;
        latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");       

        
        // leg_x1 = 0.2;
        // leg_y1 = 0.85;
        // leg_y1-=0.05;
        leg_y1-= 0.1;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
        leg_y1-= 0.1;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");
        
    }
    else if(label.Contains("Rg") && label.Contains("xJ_gp4")){
        leg_x1 = 0.6;
        leg_y1 = 0.75;
        leg_x2 = 0.88;
        leg_y2 = 0.88;
        
        leg_x1-=0.05;
        leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV, #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.4");
        leg_y1-= 0.12;
        // leg_x1+=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44, |#eta_{jet}| < 2");
        leg_y1-= 0.1;
        latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");

        leg_x1 = 0.18;
        leg_y1 = 0.37;

        leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
        leg_y1-= 0.1;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp8")){
        leg_x1 = 0.6;
        leg_y1 = 0.75;
        leg_x2 = 0.88;
        leg_y2 = 0.88;

        leg_x1-=0.01;
        leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV, #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.8");
        leg_y1-= 0.12;
        leg_x1+=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44, |#eta_{jet}| < 2");
        leg_y1-= 0.1;
        latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
        leg_y1-= 0.1;
        // latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");

        // leg_x1 = 0.2;
        // leg_y1 = 0.87;

        // leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp4")){
        leg_x1 = 0.6;
        leg_y1 = 0.75;
        leg_x2 = 0.88;
        leg_y2 = 0.88;

        leg_x1-=0.01;
        leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV, #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.4");
        leg_y1-= 0.12;
        leg_x1+=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44, |#eta_{jet}| < 2");
        leg_y1-= 0.1;
        latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
        // leg_y1-= 0.1;
        // latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");

        leg_x1 = 0.2;
        leg_y1 = 0.9;

        leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
    }
    else{
      leg_x1 = 0.58;
      leg_y1 = 0.72;
      leg_x2 = 0.8;
      leg_y2 = 0.87;

      leg_y1-= 0.1;
      latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV, #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.4");
      leg_y1-= 0.1;
      latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44, |#eta_{jet}| < 2");
      leg_y1-= 0.1;
      latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
      
      leg_x1 = 0.22;
      leg_y1 = 0.72;
      leg_y1-= 0.1;
      latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
      leg_y1-= 0.1;
      latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");
    }

    canv->Update();
    fixOverlay();
    canv->Draw();
    // canv->RedrawAxis();
    // canv->GetFrame()->Draw();

    canv->SaveAs(output_path+"/"+label+".pdf");
    // canv->SaveAs(output_path+"/"+label+".svg");
    canv->Write(label,TObject::kOverwrite);

    fout->Close();
    delete l;
    delete fout;
    delete pad1;
    delete canv;

    return canv;

}

void overlay_pp_PbPb(){
    
    gROOT->SetBatch();

    TString input_theory_path = "Overlay_ppPbPb/Theory_graph/";
    std::vector<TString> theory_case = 
    {"HYBRID_Elastic_Wake_0_","HYBRID_NoElastic_Wake_0_","HYBRID_NoElastic_Lres2_Wake_0_","HYBRID_NoElastic_LresInf_Wake_0_",
     // "HYBRID_Elastic_Wake_1_","HYBRID_NoElastic_Wake_1_","HYBRID_NoElastic_Lres2_Wake_1_","HYBRID_NoElastic_LresInf_Wake_1_"
    };
    std::vector<TString> theory_case_label = 
    {"Elastic NoWake","NoElastic NoWake","NoElastic L_{res}=2/#pi T NoWake","NoElastic L_{res}=#infty NoWake",
   //   "Elastic Wake","NoElastic Wake","NoElastic L_{res}=2/#pi T Wake","NoElastic L_{res}=#infty Wake",
    };

    std::vector<TString> plot_cases = {
        "Rg_xJ_gp4",
        "girth_xJ_gp4",
        "Rg_xJ_gp8",
        "girth_xJ_gp8"
        };

    std::vector<TString>theory_list;
    std::vector<TString>label_list;
    
    // TString out_label="";
    // TString varname="Rg";

    for(auto var:plot_cases){
        TString file_PbPb = "Uncertainty/OutputCombined_Jul_31_Decorrelate_PF/Data_0_30_Jul_31_PbPb_2018_sys_Decorrelate_PF_";
        TString label_PbPb = "Data_0_30_Jul_31_PbPb_2018_sys_Decorrelate_PF_"; // xJ_gp8_Data_Rg_unfold_X 
        TString file_pp = "~/pp_analysis/Analysis/Uncertainty/OutputCombined_Jul_31_Decorrelate_PF/pp_Data_Jul_31_pp_2017_sys_Decorrelate_PF_";
        TString label_pp="pp_Data_Jul_31_pp_2017_sys_Decorrelate_PF_"; 
        // theory_list.clear();
        // label_list.clear();
        // for(int i=0;i<theory_case.size();i++){
        //     theory_list.push_back(input_theory_path+theory_case[i]+var+".root");
        //     label_list.push_back(theory_case_label[i]);
        // }
        if(var.Contains("xJ_gp4")){
            file_PbPb+="Data_";
            label_PbPb+="Data_";
            file_pp+="Data_";
            label_pp+="Data_";
        }
        else{
            file_PbPb+="xJ_gp8_Data_";
            label_PbPb+="xJ_gp8_Data_";
            file_pp+="xJ_gp8_Data_";
            label_pp+="xJ_gp8_Data_";
        }

        if(var.Contains("Rg")){
            file_PbPb+="Rg_unfold_X.root";
            label_PbPb+="Rg_unfold_X";
            file_pp+="Rg_unfold_X.root";
            label_pp+="Rg_unfold_X";
        }
        else{
            file_PbPb+="girth_unfold_X.root";
            label_PbPb+="girth_unfold_X";
            file_pp+="girth_unfold_X.root";
            label_pp+="girth_unfold_X";
        }    

        // std::cout<<file_PbPb<<"\n";
        std::cout<<"\n";

        TCanvas *c_temp = overlay_uncert(file_PbPb,label_PbPb,file_pp,label_pp,"PbPb_pp_0_30_Jul_31_Plot_Mar_5_"+var+"",var);
        // delete c_temp;
        std::cout<<"PbPb_pp_0_30_Jul_31_Plot_Mar_5_"+var+" has been saved\n";
        std::cout<<"\n-------------------------------------------\n";
        // break;
    }        
    
}