//* Script to plot only the ratio considering PbPb/pp fully correlated uncertainty 
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
TCanvas c;
TString output_path = "Overlay_ratio/Uncert_Breakdown/"; // 
Bool_t flag_add_theory = false;

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
float lumiTextSize     = 0.35;
float lumiTextOffset   = 0.1;
float cmsTextSize      = 0.4;
float cmsTextOffset    = 0.1;  // only used in outOfFrame version

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
  tdrStyle->SetTitleSize(0.04, "XYZ"); // 0.06
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.04, "XYZ"); // 0.05

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


void Plot_hist_up(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "width" = Divide by Bin Width
    // "OBJ" = optional stuff for later? 

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    // gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(opt.Contains("log")) gStyle->SetOptLogy(1);
    
    TString drawopt = "nostackE][P0"; 
    if(opt.Contains("opt"))
        drawopt = eopt.back();
        /*
    const std::vector<int> colarray  = { 1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};*/

    // gStyle->SetPalette(1);
    TColor *pal = new TColor();
    /*
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
    

    // 15 Color-Blind Friendly RGB

    Int_t kblack  = pal->GetColor(  0,  0,  0);
    Int_t kteal   = pal->GetColor(  0, 73, 73);
    Int_t kpink   = pal->GetColor(255,109,182);
    Int_t kpurple = pal->GetColor( 73,  0,146);
    Int_t kblue   = pal->GetColor(  0,109,219);
    Int_t kviolet = pal->GetColor(182,109,255);
    Int_t kred    = pal->GetColor(146,  0,  0);
    Int_t kbrown  = pal->GetColor(146, 73,  0);
    Int_t korange = pal->GetColor(219,109,  0);
    Int_t kgreen  = pal->GetColor( 36,255, 36);

    Int_t kolive  = pal->GetColor(  0,146,146);  // 
    Int_t kyellow = pal->GetColor(255,255,109);
    Int_t klpink  = pal->GetColor(255,109,182);  //
    Int_t klblue  = pal->GetColor(109,182,255);  //
    Int_t kvlblue = pal->GetColor(182,219,255);  //
    */
    // 

    Int_t kblack   = pal->GetColor(  0,  0,  0);// pal->GetColor("#000000");
    
    Int_t kred     = pal->GetColor(255,  0,  0);
    Int_t kskyblue = pal->GetColor(  0,114,178);// pal->GetColor("#0072B2");

    Int_t kgrass   = pal->GetColor(  0,158,115);// pal->GetColor("#009E73");
    Int_t kpink    = pal->GetColor(204,121,167);// pal->GetColor("#CC79A7");
    Int_t kpurple  = pal->GetColor( 51, 34,136);// pal->GetColor("#332288");
    Int_t korange  = pal->GetColor(230,159,  0);// pal->GetColor("#E69F00");
    Int_t klblue   = pal->GetColor( 86,180,233);// pal->GetColor("#56B4E9");
    Int_t kyellow  = pal->GetColor(240,228, 66);// pal->GetColor("#F0E442");
    Int_t kviolet  = pal->GetColor(170, 51,119);// pal->GetColor("#AA3377");
    Int_t kredish  = pal->GetColor(213, 94,  0);// pal->GetColor("#D55E00");  
    Int_t kteal   = pal->GetColor(  0, 73, 73);
    // const std::vector<int> colarray  = { kOrange+4,kOrange+4,kCyan+2, kCyan+2 , 600, 600, 616, 616, 419, 419,922,922,kspring,kspring,632, 632, 1, 1,
    //                                    910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> colarray  = { korange,                      // Statistical                                      
                                         kteal,                     // Regularization
                                         kviolet,                      // Purity
                                         kskyblue,                     // JEC
                                         kgrass,                       // JER
                                         kpink,                        // Response 
                                         klblue,                        // Substructure
                                         kOrange-6,                            // Substructure
                                         kPink+10,                         // Substructure
                                         kpurple,                      // Centrality
                                         kredish,                      // MC
                                         kblack                        // Total

    };
    const std::vector<int> markarray = { kOpenCircle, kFullCircle,                  // Statistical                                      
                                         kOpenTriangleUp, kFullTriangleUp,          // Regularization
                                         kOpenDiamond, kFullDiamond,                // Purity
                                         kOpenCross, kFullCross,                    // JEC
                                         kOpenTriangleDown,kFullTriangleDown,       // JER
                                         kOpenDoubleDiamond,kFullDoubleDiamond,     // Response 
                                         kOpenCrossX, kFullCrossX,                  // Substructure
                                         kOpenStar, kFullStar,                      // Centrality
                                         kOpenThreeTriangles, kFullThreeTriangles,  // MC
                                         kOpenSquare, kFullSquare,                  // Total
                                         kOpenCrossX, kFullCrossX
    };

    // TCanvas c;
    c.cd();
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

    THStack *hs = new THStack("hs_up","hs_up");

    for(std::size_t ihist=0; ihist<hist.size();){
        if(opt.Contains("eff")){
            if((ihist+1)>=hist.size()) break;
            hist[ihist+1]->SetLineColor(colarray[ihist]);
            hist[ihist+1]->SetFillColor(colarray[ihist]);
            hist[ihist+1]->SetMarkerColor(colarray[ihist]);
            hist[ihist+1]->SetMarkerStyle(markarray[ihist]);
            hist[ihist+1]->Divide(hist[ihist+1],hist[0],1,1);
            ihist++;
        }
        else{
            hist[ihist]->SetLineColor(colarray[ihist]);
            hist[ihist]->SetFillColor(colarray[ihist]);
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

        // hist[ihist]->GetXaxis()->SetRange(1,hist[ihist]->GetNbinsX()-1);
        hs->Add(hist[ihist]);     
        // if(ihist%2==1) 
        l->AddEntry(hist[ihist], histname[ihist], "f");
        if(!opt.Contains("eff")) ihist++;
    }
    hs->Draw(drawopt);
    hs->GetHistogram()->GetXaxis()->SetTickLength(0);
    // hs->Draw("NOSTACKB_HIST");
    double uncert_min = -0.3;
    double uncert_max =  0.8;

    hs->SetMinimum(uncert_min);
    hs->SetMaximum(uncert_max);
    // if(hs->GetMinimum()>=uncert_min){
    //     hs->SetMinimum(uncert_min);
    // }
    // else{
    //     hs->SetMinimum(hs->GetMinimum()*1.1);
    // }
    // if(hs->GetMaximum()<=uncert_max){
    //     hs->SetMaximum(uncert_max);
    // }
    // else{
    //     hs->SetMinimum(hs->GetMinimum()*1.1);
    // }
    hs->GetYaxis()->SetTitleOffset(0.9);
    //! TO remove Overflow Bin -> Also remove Line +1
    hs->GetXaxis()->SetRange(1,hist[0]->GetNbinsX()-1);
    if(opt.Contains("label")){
        hs->GetXaxis()->SetTitle(histname.at(histname.size()-3));
        hs->GetYaxis()->SetTitle(histname.at(histname.size()-2));
    }
    else{
        hs->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
        hs->GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());
    }
    // l->Draw();

    // TLine *line=new TLine(hist[0]->GetXaxis()->GetXmin(),0.0,hist[0]->GetXaxis()->GetBinLowEdge(hist[0]->GetNbinsX()+1),0.0);
    // line->SetLineStyle(2);
    // line->Draw("SAME");

    // for(std::size_t ibin=2;ibin<hist[0]->GetNbinsX()+1;ibin++){
    //     TLine *l_temp=new TLine(hist[0]->GetXaxis()->GetBinLowEdge(ibin),uncert_min,hist[0]->GetXaxis()->GetBinLowEdge(ibin),uncert_max);
    //     l_temp->SetLineColor(1);
    //     l_temp->SetLineWidth(1);
    //     l_temp->SetLineStyle(2);
    //     l_temp->Draw("SAME");
    // }

    // TLatex latex;
    // latex.SetTextSize(0.035);
    // if(label.Contains("Data"))
    //     latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary}}");
    // else
    //     latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary Simulation}}");

    // if(eopt[0].Contains("Cent")){
    //     latex.DrawLatexNDC(0.75,0.92,eopt[0]);
    // }
    // else if(eopt.size()>=2){
    //     latex.DrawLatexNDC(0.41,0.92,eopt[0]);
    //     latex.DrawLatexNDC(0.5,0.92,eopt[1]);
    // }    

    //! Text in Right
    leg_x1 = 0.6;
    leg_y1 = 0.88;

    // latex.SetTextSize(0.035);
    // if(eopt.size()>2){
    //     for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
    //         leg_y1-=0.06;
    //         latex.DrawLatexNDC(leg_x1,leg_y1,eopt[ind]);
    //     }
    // }
    gPad->Update();
    // c.SaveAs(output_path +histname.back()+".png");
    // c.SaveAs(output_path +histname.back()+".C");
    // c.Write(histname.back(),TObject::kWriteDelete);
    // std::cout<<histname.back()<<" has been saved"<<std::endl;
    // delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
    return c;
}


void Plot_hist_down(std::vector<TH1D*> hist,std::vector<TString> histname,TString opt,std::vector<TString> eopt){
    // opt contains options
    // "eff" = Efficiency Plot. Divide by 0th index
    // "left","right", "bcenter" = Legend location 
    // "label" = 2 before the last entries of histname is the X and Y label otherwise use the default 
    // "log" = Set log scale
    // "width" = Divide by Bin Width
    // "OBJ" = optional stuff for later? 

    gStyle->SetOptStat(0);      // No Stat Box
    gStyle->SetOptTitle(0);     // No Title
    // gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    if(opt.Contains("log")) gStyle->SetOptLogy(1);
    
    TString drawopt = "nostackE][P0"; 
    if(opt.Contains("opt"))
        drawopt = eopt.back();
        /*
    const std::vector<int> colarray  = { 1,632,600,616,419,800,425,898,
                                       922,910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> markarray = {20, 25, 22, 32, 29, 28, 39, 40,
                                        24, 21, 26, 23, 30, 34, 37, 41};*/

    // gStyle->SetPalette(1);
    TColor *pal = new TColor();
    /*
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
    

    // 15 Color-Blind Friendly RGB

    Int_t kblack  = pal->GetColor(  0,  0,  0);
    Int_t kteal   = pal->GetColor(  0, 73, 73);
    Int_t kpink   = pal->GetColor(255,109,182);
    Int_t kpurple = pal->GetColor( 73,  0,146);
    Int_t kblue   = pal->GetColor(  0,109,219);
    Int_t kviolet = pal->GetColor(182,109,255);
    Int_t kred    = pal->GetColor(146,  0,  0);
    Int_t kbrown  = pal->GetColor(146, 73,  0);
    Int_t korange = pal->GetColor(219,109,  0);
    Int_t kgreen  = pal->GetColor( 36,255, 36);

    Int_t kolive  = pal->GetColor(  0,146,146);  // 
    Int_t kyellow = pal->GetColor(255,255,109);
    Int_t klpink  = pal->GetColor(255,109,182);  //
    Int_t klblue  = pal->GetColor(109,182,255);  //
    Int_t kvlblue = pal->GetColor(182,219,255);  //
    */
    // 

    Int_t kblack   = pal->GetColor(  0,  0,  0);// pal->GetColor("#000000");
    
    Int_t kred     = pal->GetColor(255,  0,  0);
    Int_t kskyblue = pal->GetColor(  0,114,178);// pal->GetColor("#0072B2");

    Int_t kgrass   = pal->GetColor(  0,158,115);// pal->GetColor("#009E73");
    Int_t kpink    = pal->GetColor(204,121,167);// pal->GetColor("#CC79A7");
    Int_t kpurple  = pal->GetColor( 51, 34,136);// pal->GetColor("#332288");
    Int_t korange  = pal->GetColor(230,159,  0);// pal->GetColor("#E69F00");
    Int_t klblue   = pal->GetColor( 86,180,233);// pal->GetColor("#56B4E9");
    Int_t kyellow  = pal->GetColor(240,228, 66);// pal->GetColor("#F0E442");
    Int_t kviolet  = pal->GetColor(170, 51,119);// pal->GetColor("#AA3377");
    Int_t kredish  = pal->GetColor(213, 94,  0);// pal->GetColor("#D55E00");  
    Int_t kteal   = pal->GetColor(  0, 73, 73);
    // const std::vector<int> colarray  = { kOrange+4,kOrange+4,kCyan+2, kCyan+2 , 600, 600, 616, 616, 419, 419,922,922,kspring,kspring,632, 632, 1, 1,
    //                                    910,851,877,811,804,434,606};// { 1, 2, 4, 6, 8,20,28};
    const std::vector<int> colarray  = { korange,                       // Statistical                                      
                                         kteal,                         // Regularization
                                         kviolet,                       // Purity
                                         kskyblue,                      // JEC
                                         kgrass,                        // JER
                                         kpink,                         // Response 
                                         klblue,                        // Substructure
                                         kOrange-6,                     // Substructure
                                         kPink+10,                      // Substructure
                                         kpurple,                       // Centrality
                                         kredish,                       // MC
                                         kblack                         // Total

    };
    const std::vector<int> markarray = { kOpenCircle, kFullCircle,                  // Statistical                                      
                                         kOpenTriangleUp, kFullTriangleUp,          // Regularization
                                         kOpenDiamond, kFullDiamond,                // Purity
                                         kOpenCross, kFullCross,                    // JEC
                                         kOpenTriangleDown,kFullTriangleDown,       // JER
                                         kOpenDoubleDiamond,kFullDoubleDiamond,     // Response 
                                         kOpenCrossX, kFullCrossX,                  // Substructure
                                         kOpenStar, kFullStar,                      // Centrality
                                         kOpenThreeTriangles, kFullThreeTriangles,  // MC
                                         kOpenSquare, kFullSquare,                  // Total
                                         kOpenCrossX, kFullCrossX
    };

    // TCanvas c;
    c.cd();
    c.SetTicky(1);
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
    l->SetBorderSize(0);

    THStack *hs = new THStack("hs_down","hs_down");

    for(std::size_t ihist=0; ihist<hist.size();){
        if(opt.Contains("eff")){
            if((ihist+1)>=hist.size()) break;
            hist[ihist+1]->SetLineColor(colarray[ihist]);
            hist[ihist+1]->SetFillColor(colarray[ihist]);
            hist[ihist+1]->SetMarkerColor(colarray[ihist]);
            hist[ihist+1]->SetMarkerStyle(markarray[ihist]);
            hist[ihist+1]->Divide(hist[ihist+1],hist[0],1,1);
            ihist++;
        }
        else{
            hist[ihist]->SetLineColor(colarray[ihist]);
            hist[ihist]->SetFillColor(colarray[ihist]);
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

        // hist[ihist]->GetXaxis()->SetRange(1,hist[ihist]->GetNbinsX()-1);
        hs->Add(hist[ihist]);     
        //if(ihist%2==1) 
        l->AddEntry(hist[ihist], histname[ihist], "f");
        if(!opt.Contains("eff")) ihist++;
    }
    hs->Draw(drawopt);
    hs->GetHistogram()->GetXaxis()->SetTickLength(0);
    // hs->Draw("NOSTACKB_HIST");
    double uncert_min = -0.3;
    double uncert_max =  0.8;

    hs->SetMinimum(uncert_min);
    hs->SetMaximum(uncert_max);
    // if(hs->GetMinimum()>=uncert_min){
    //     hs->SetMinimum(uncert_min);
    // }
    // else{
    //     hs->SetMinimum(hs->GetMinimum()*1.1);
    // }
    // if(hs->GetMaximum()<=uncert_max){
    //     hs->SetMaximum(uncert_max);
    // }
    // else{
    //     hs->SetMinimum(hs->GetMinimum()*1.1);
    // }
    hs->GetYaxis()->SetTitleOffset(0.9);
    //! TO remove Overflow Bin -> Also remove Line +1
    hs->GetXaxis()->SetRange(1,hist[0]->GetNbinsX()-1);
    if(opt.Contains("label")){
        hs->GetXaxis()->SetTitle(histname.at(histname.size()-3));
        hs->GetYaxis()->SetTitle(histname.at(histname.size()-2));
    }
    else{
        hs->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
        hs->GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());
    }
    l->Draw();

    TLine *line=new TLine(hist[0]->GetXaxis()->GetXmin(),0.0,hist[0]->GetXaxis()->GetBinLowEdge(hist[0]->GetNbinsX()),0.0);
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    line->Draw("SAME");

    for(std::size_t ibin=2;ibin<hist[0]->GetNbinsX();ibin++){
        TLine *l_temp=new TLine(hist[0]->GetXaxis()->GetBinLowEdge(ibin),uncert_min,hist[0]->GetXaxis()->GetBinLowEdge(ibin),uncert_max);
        l_temp->SetLineColor(1);
        l_temp->SetLineWidth(1);
        l_temp->SetLineStyle(2);
        l_temp->Draw("SAME");
    }

    TLatex latex;
    latex.SetTextSize(0.035);
    // if(label.Contains("Data"))
        latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary}}");
    // else
    //     latex.DrawLatexNDC(0.1,0.92,"CMS #it{#bf{Preliminary Simulation}}");

    if(eopt[0].Contains("Cent")){
        latex.DrawLatexNDC(0.75,0.92,eopt[0]);
    }
    else if(eopt.size()>=2){
        latex.DrawLatexNDC(0.41,0.92,eopt[0]);
        latex.DrawLatexNDC(0.5,0.92,eopt[1]);
    }    

    //! Text in Right
    leg_x1 = 0.6;
    leg_y1 = 0.88;

    latex.SetTextSize(0.035);
    if(eopt.size()>2){
        for(std::size_t ind=2;ind<eopt.size() && !eopt[ind].Contains("end"); ind++){
            leg_y1-=0.06;
            latex.DrawLatexNDC(leg_x1,leg_y1,eopt[ind]);
        }
    }
    gPad->Update();
    c.SaveAs(output_path +histname.back()+".png");
    // c.SaveAs(output_path +histname.back()+".C");
    c.Write(histname.back(),TObject::kWriteDelete);
    std::cout<<histname.back()<<" has been saved"<<std::endl;
    // delete l;
    if(opt.Contains("log")) gStyle->SetOptLogy(0);
    return c;
}


TCanvas* overlay_theory(std::vector<TString>theory_list,std::vector<TString>label_list,TString file_PbPb, TString label_PbPb, TString file_pp, TString label_pp="", TString out_label="",TString varname="Rg"){
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

    if(theory_list.size()!=label_list.size()){ std::cout<<"Number of theory files mismatch\n"; return NULL;}
    
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

    TFile *f_theory;
    std::vector<TGraphAsymmErrors*> h_theory; 
    for (int i_file = 0 ; i_file<theory_list.size();i_file++){
        f_theory  = TFile::Open(theory_list[i_file]);
        TGraphAsymmErrors *h_temp = (TGraphAsymmErrors*)f_theory->Get("ratio_graph");
        h_theory.push_back((TGraphAsymmErrors*)h_temp->Clone());
    }

    TH1D *hPbPb_nom = (TH1D*)f_PbPb->Get(label_PbPb+"_nom");
    TGraphAsymmErrors *hPbPb_stat = (TGraphAsymmErrors*)f_PbPb->Get("stat_uncert");
    TGraphAsymmErrors *hPbPb_sys = (TGraphAsymmErrors*)f_PbPb->Get("sys_uncert");
    TGraphAsymmErrors *hPbPb_tot = (TGraphAsymmErrors*)f_PbPb->Get("tot_uncert");

    TH1D *hpp_nom = (TH1D*)f_pp->Get(label_pp+"_nom");
    TGraphAsymmErrors *hpp_stat = (TGraphAsymmErrors*)f_pp->Get("stat_uncert");
    TGraphAsymmErrors *hpp_sys = (TGraphAsymmErrors*)f_pp->Get("sys_uncert");
    TGraphAsymmErrors *hpp_tot = (TGraphAsymmErrors*)f_pp->Get("tot_uncert");

    // Calculate fully correlated uncertainty
        // PbPb uncertainties
        TH1D *hPbPb_unfoldm1 = (TH1D*)f_PbPb->Get(label_PbPb+"_unfoldm1");
        TH1D *hPbPb_unfoldp1 = (TH1D*)f_PbPb->Get(label_PbPb+"_unfoldp1");
        TH1D *hPbPb_purity_up = (TH1D*)f_PbPb->Get(label_PbPb+"_ABCD");
        TH1D *hPbPb_purity_down = (TH1D*)f_PbPb->Get(label_PbPb+"_ABCD");
        TH1D *hPbPb_JECup = (TH1D*)f_PbPb->Get(label_PbPb+"_JECup");
        TH1D *hPbPb_JECdown = (TH1D*)f_PbPb->Get(label_PbPb+"_JECdown");
        TH1D *hPbPb_JERup = (TH1D*)f_PbPb->Get(label_PbPb+"_JERup");
        TH1D *hPbPb_JERdown = (TH1D*)f_PbPb->Get(label_PbPb+"_JERdown");
        TH1D *hPbPb_response_up = (TH1D*)f_PbPb->Get(label_PbPb+"_response");
        TH1D *hPbPb_response_down = (TH1D*)f_PbPb->Get(label_PbPb+"_response");
        TH1D *hPbPb_Photon_up = (TH1D*)f_PbPb->Get(label_PbPb+"_Photon_up");
        TH1D *hPbPb_Photon_down = (TH1D*)f_PbPb->Get(label_PbPb+"_Photon_down");
        TH1D *hPbPb_Charged_up = (TH1D*)f_PbPb->Get(label_PbPb+"_Charged_up");
        TH1D *hPbPb_Charged_down = (TH1D*)f_PbPb->Get(label_PbPb+"_Charged_down");
        TH1D *hPbPb_Neutral_up = (TH1D*)f_PbPb->Get(label_PbPb+"_Neutral_up");
        TH1D *hPbPb_Neutral_down = (TH1D*)f_PbPb->Get(label_PbPb+"_Neutral_down");
        TH1D *hPbPb_Centup = (TH1D*)f_PbPb->Get(label_PbPb+"_Centup");
        TH1D *hPbPb_Centdown = (TH1D*)f_PbPb->Get(label_PbPb+"_Centdown");
        TH1D *hPbPb_Pythia_prior_up = (TH1D*)f_PbPb->Get(label_PbPb+"_AltMC");
        TH1D *hPbPb_Pythia_prior_down = (TH1D*)f_PbPb->Get(label_PbPb+"_AltMC");

        // pp uncertainties
        TH1D *hpp_unfoldm1 = (TH1D*)f_pp->Get(label_pp+"_unfoldm1");
        TH1D *hpp_unfoldp1 = (TH1D*)f_pp->Get(label_pp+"_unfoldp1");
        TH1D *hpp_purity_up = (TH1D*)f_pp->Get(label_pp+"_ABCD");
        TH1D *hpp_purity_down = (TH1D*)f_pp->Get(label_pp+"_ABCD");
        TH1D *hpp_JECup = (TH1D*)f_pp->Get(label_pp+"_JECup");
        TH1D *hpp_JECdown = (TH1D*)f_pp->Get(label_pp+"_JECdown");
        TH1D *hpp_JERup = (TH1D*)f_pp->Get(label_pp+"_JERup");
        TH1D *hpp_JERdown = (TH1D*)f_pp->Get(label_pp+"_JERdown");
        TH1D *hpp_response_up = (TH1D*)f_pp->Get(label_pp+"_response");
        TH1D *hpp_response_down = (TH1D*)f_pp->Get(label_pp+"_response");
        TH1D *hpp_Photon_up = (TH1D*)f_pp->Get(label_pp+"_Photon_up");
        TH1D *hpp_Photon_down = (TH1D*)f_pp->Get(label_pp+"_Photon_down");
        TH1D *hpp_Charged_up = (TH1D*)f_pp->Get(label_pp+"_Charged_up");
        TH1D *hpp_Charged_down = (TH1D*)f_pp->Get(label_pp+"_Charged_down");
        TH1D *hpp_Neutral_up = (TH1D*)f_pp->Get(label_pp+"_Neutral_up");
        TH1D *hpp_Neutral_down = (TH1D*)f_pp->Get(label_pp+"_Neutral_down");
        TH1D *hpp_herwig_up = (TH1D*)f_pp->Get(label_pp+"_AltMC");
        TH1D *hpp_herwig_down = (TH1D*)f_pp->Get(label_pp+"_AltMC");

        // Ratio uncertainties

        TH1D *herr_uncorr_nom = (TH1D*)f_PbPb->Get(label_PbPb+"_nom");
        TH1D *herr_uncorr_unfoldm1 = (TH1D*)f_PbPb->Get(label_PbPb+"_unfoldm1");
        TH1D *herr_uncorr_unfoldp1 = (TH1D*)f_PbPb->Get(label_PbPb+"_unfoldp1");
        TH1D *herr_uncorr_purity_up = (TH1D*)f_PbPb->Get(label_PbPb+"_ABCD");
        TH1D *herr_uncorr_purity_down = (TH1D*)f_PbPb->Get(label_PbPb+"_ABCD");
        TH1D *herr_uncorr_JECup = (TH1D*)f_PbPb->Get(label_PbPb+"_JECup");
        TH1D *herr_uncorr_JECdown = (TH1D*)f_PbPb->Get(label_PbPb+"_JECdown");
        TH1D *herr_uncorr_JERup = (TH1D*)f_PbPb->Get(label_PbPb+"_JERup");
        TH1D *herr_uncorr_JERdown = (TH1D*)f_PbPb->Get(label_PbPb+"_JERdown");
        TH1D *herr_uncorr_response_up = (TH1D*)f_PbPb->Get(label_PbPb+"_response");
        TH1D *herr_uncorr_response_down = (TH1D*)f_PbPb->Get(label_PbPb+"_response");
        TH1D *herr_uncorr_Photon_up = (TH1D*)f_PbPb->Get(label_PbPb+"_Photon_up");
        TH1D *herr_uncorr_Photon_down = (TH1D*)f_PbPb->Get(label_PbPb+"_Photon_down");
        TH1D *herr_uncorr_Charged_up = (TH1D*)f_PbPb->Get(label_PbPb+"_Charged_up");
        TH1D *herr_uncorr_Charged_down = (TH1D*)f_PbPb->Get(label_PbPb+"_Charged_down");
        TH1D *herr_uncorr_Neutral_up = (TH1D*)f_PbPb->Get(label_PbPb+"_Neutral_up");
        TH1D *herr_uncorr_Neutral_down = (TH1D*)f_PbPb->Get(label_PbPb+"_Neutral_down");
        TH1D *herr_uncorr_Centup = (TH1D*)f_PbPb->Get(label_PbPb+"_Centup");
        TH1D *herr_uncorr_Centdown = (TH1D*)f_PbPb->Get(label_PbPb+"_Centdown");
        TH1D *herr_uncorr_Pythia_prior_up = (TH1D*)f_PbPb->Get(label_PbPb+"_AltMC");
        TH1D *herr_uncorr_Pythia_prior_down = (TH1D*)f_PbPb->Get(label_PbPb+"_AltMC");

        TH1D *herr_uncorr_total_up = (TH1D*)herr_uncorr_nom->Clone("herr_uncorr_total");
        TH1D *herr_uncorr_total_down = (TH1D*)herr_uncorr_nom->Clone("herr_uncorr_total");

        herr_uncorr_nom->SetTitle("Stat.");
        herr_uncorr_unfoldm1->SetTitle("Regularization Bias");
        herr_uncorr_unfoldp1->SetTitle("Regularization Bias (sym)");
        herr_uncorr_purity_up->SetTitle("Photon purity");
        herr_uncorr_purity_down->SetTitle("Photon purity (sym)");
        herr_uncorr_JECup->SetTitle("Jet energy scale up");
        herr_uncorr_JECdown->SetTitle("Jet energy scale");
        herr_uncorr_JERup->SetTitle("Jet energy resolution up");
        herr_uncorr_JERdown->SetTitle("Jet energy resolution");
        herr_uncorr_response_up->SetTitle("Response matrix stats");
        herr_uncorr_response_down->SetTitle("Response matrix stats");
        herr_uncorr_Photon_up->SetTitle("EGamma PF scale up");
        herr_uncorr_Photon_down->SetTitle("EGamma PF scale");
        herr_uncorr_Charged_up->SetTitle("Charged PF scale up");
        herr_uncorr_Charged_down->SetTitle("Charged PF scale");
        herr_uncorr_Neutral_up->SetTitle("Neutral PF scale up");
        herr_uncorr_Neutral_down->SetTitle("Neutral PF scale");
        herr_uncorr_Centup->SetTitle("Centrality up");
        herr_uncorr_Centdown->SetTitle("Centrality");
        herr_uncorr_Pythia_prior_up->SetTitle("Fragmentation model");
        herr_uncorr_Pythia_prior_down->SetTitle("Fragmentation model (sym)");

        herr_uncorr_total_up->SetTitle("Total");
        herr_uncorr_total_down->SetTitle("Total uncert. ");

        TH1D *herr_corr_nom = (TH1D*)f_PbPb->Get(label_PbPb+"_nom");
        TH1D *herr_corr_unfoldm1 = (TH1D*)f_PbPb->Get(label_PbPb+"_unfoldm1");
        TH1D *herr_corr_unfoldp1 = (TH1D*)f_PbPb->Get(label_PbPb+"_unfoldp1");
        TH1D *herr_corr_purity_up = (TH1D*)f_PbPb->Get(label_PbPb+"_ABCD");
        TH1D *herr_corr_purity_down = (TH1D*)f_PbPb->Get(label_PbPb+"_ABCD");
        TH1D *herr_corr_JECup = (TH1D*)f_PbPb->Get(label_PbPb+"_JECup");
        TH1D *herr_corr_JECdown = (TH1D*)f_PbPb->Get(label_PbPb+"_JECdown");
        TH1D *herr_corr_JERup = (TH1D*)f_PbPb->Get(label_PbPb+"_JERup");
        TH1D *herr_corr_JERdown = (TH1D*)f_PbPb->Get(label_PbPb+"_JERdown");
        TH1D *herr_corr_response_up = (TH1D*)f_PbPb->Get(label_PbPb+"_response");
        TH1D *herr_corr_response_down = (TH1D*)f_PbPb->Get(label_PbPb+"_response");
        TH1D *herr_corr_Photon_up = (TH1D*)f_PbPb->Get(label_PbPb+"_Photon_up");
        TH1D *herr_corr_Photon_down = (TH1D*)f_PbPb->Get(label_PbPb+"_Photon_down");
        TH1D *herr_corr_Charged_up = (TH1D*)f_PbPb->Get(label_PbPb+"_Charged_up");
        TH1D *herr_corr_Charged_down = (TH1D*)f_PbPb->Get(label_PbPb+"_Charged_down");
        TH1D *herr_corr_Neutral_up = (TH1D*)f_PbPb->Get(label_PbPb+"_Neutral_up");
        TH1D *herr_corr_Neutral_down = (TH1D*)f_PbPb->Get(label_PbPb+"_Neutral_down");
        TH1D *herr_corr_Centup = (TH1D*)f_PbPb->Get(label_PbPb+"_Centup");
        TH1D *herr_corr_Centdown = (TH1D*)f_PbPb->Get(label_PbPb+"_Centdown");
        TH1D *herr_corr_Pythia_prior_up = (TH1D*)f_PbPb->Get(label_PbPb+"_AltMC");
        TH1D *herr_corr_Pythia_prior_down = (TH1D*)f_PbPb->Get(label_PbPb+"_AltMC");

        TH1D *herr_corr_total_up = (TH1D*)herr_corr_nom->Clone("herr_corr_total");
        TH1D *herr_corr_total_down = (TH1D*)herr_corr_nom->Clone("herr_corr_total");

        herr_corr_nom->SetTitle("Stat.");
        herr_corr_unfoldm1->SetTitle("Regularization Bias");
        herr_corr_unfoldp1->SetTitle("Regularization Bias (sym)");
        herr_corr_purity_up->SetTitle("Corr. Photon purity");
        herr_corr_purity_down->SetTitle("Corr. Photon purity (sym)");
        herr_corr_JECup->SetTitle("Corr. Jet energy scale up");
        herr_corr_JECdown->SetTitle("Corr. Jet energy scale");
        herr_corr_JERup->SetTitle("Corr. Jet energy resolution up");
        herr_corr_JERdown->SetTitle("Corr. Jet energy resolution");
        herr_corr_response_up->SetTitle("Response matrix stats");
        herr_corr_response_down->SetTitle("Response matrix stats");
        herr_corr_Photon_up->SetTitle("Corr. EGamma PF scale up");
        herr_corr_Photon_down->SetTitle("Corr. EGamma PF scale");
        herr_corr_Charged_up->SetTitle("Corr. Charged PF scale up");
        herr_corr_Charged_down->SetTitle("Corr. Charged PF scale");
        herr_corr_Neutral_up->SetTitle("Corr. Neutral PF scale up");
        herr_corr_Neutral_down->SetTitle("Corr. Neutral PF scale");
        herr_corr_Centup->SetTitle("Centrality up");
        herr_corr_Centdown->SetTitle("Centrality");
        herr_corr_Pythia_prior_up->SetTitle("Fragmentation model");
        herr_corr_Pythia_prior_down->SetTitle("Fragmentation model (sym)");

        herr_corr_total_up->SetTitle("Total Corr. uncert. ");
        herr_corr_total_down->SetTitle("Total Corr. uncert. ");
        
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

    Double_t vec_x[20],vec_y[20],errx_do[20],errx_up[20],erry_do[20],erry_up[20],errstat_do[20],errstat_up[20],errtot_do[20],errtot_up[20],erry_syscorr_do[20],erry_syscorr_up[20],errtot_corr_do[20],errtot_corr_up[20];
    for(Int_t j=0;j<=hratio->GetNbinsX()+1;j++){ 

        Double_t erry_stat_a = hratio->GetBinError(j); 
        Double_t erry_stat_b=erry_stat_a;

        Double_t temp_pp_x,temp_pp_y,temp_PbPb_x,temp_PbPb_y;
        hpp_sys->GetPoint(j,temp_pp_x,temp_pp_y);
        hPbPb_sys->GetPoint(j,temp_PbPb_x,temp_PbPb_y);

        float test_PbPb = float(temp_PbPb_y);

        Double_t erry_pp_sys_a = 0;
        Double_t erry_pp_sys_b = 0;

        Double_t erry_PbPb_sys_a = 0;
        Double_t erry_PbPb_sys_b = 0;

        Double_t erry_sys_uncorr_up = 0;
        Double_t erry_sys_uncorr_do = 0;

        Double_t erry_uncorr_up = 0;
        Double_t erry_uncorr_do = 0;

        Double_t erry_corr_up = 0;
        Double_t erry_corr_do = 0;

        Double_t erry_ratio_total_up = 0;
        Double_t erry_ratio_total_do = 0;

        Double_t erry_ratio_total_uncorr_up = 0;
        Double_t erry_ratio_total_uncorr_do = 0;

        Double_t erry_ratio_total_corr_up = 0;
        Double_t erry_ratio_total_corr_do = 0;

        //Statistical
            Double_t erry_stat_a_PbPb = 9999;
            Double_t erry_stat_a_pp = 9999;
            // if(hinput[0]->GetBinContent(j)!=0)
                erry_stat_a_PbPb=hPbPb_nom->GetBinError(j);
                erry_stat_a_pp=hpp_nom->GetBinError(j);
            Double_t erry_stat_b_PbPb=erry_stat_a_PbPb;
            Double_t erry_stat_b_pp=erry_stat_a_pp;

        // Regularization
            Double_t erryiter_PbPb=-1*hPbPb_nom->GetBinContent(j)+hPbPb_unfoldp1->GetBinContent(j); 
            Double_t erry_reg_a_PbPb=-1, erry_reg_b_PbPb=-1;

            erry_reg_a_PbPb = fabs(erryiter_PbPb)/temp_PbPb_y;
            erry_reg_b_PbPb = erry_reg_a_PbPb;

            Double_t erryiter_pp=-1*hpp_nom->GetBinContent(j)+hpp_unfoldp1->GetBinContent(j); 
            Double_t erry_reg_a_pp=-1, erry_reg_b_pp=-1;

            erry_reg_a_pp = fabs(erryiter_pp)/temp_pp_y;
            erry_reg_b_pp = erry_reg_a_pp;

        // Response Matrix Stats -> Symmetrized
            Double_t erry_response_a_PbPb = fabs(hPbPb_response_up->GetBinError(j))/temp_PbPb_y;   
            Double_t erry_response_b_PbPb = erry_response_a_PbPb;

            Double_t erry_response_a_pp = fabs(hpp_response_up->GetBinError(j))/temp_pp_y;   
            Double_t erry_response_b_pp = erry_response_a_pp;
        
        // Centrality
            Double_t erry_cent_a = fabs(-1*hPbPb_nom->GetBinContent(j)+hPbPb_Centup->GetBinContent(j))/temp_PbPb_y;   
            Double_t erry_cent_b = fabs(-1*hPbPb_nom->GetBinContent(j)+hPbPb_Centdown->GetBinContent(j))/temp_PbPb_y;

        // Modelling Uncorrelated -> Pythia q/g Prior

            Double_t erry_Pythia_prior_a = fabs(hPbPb_Pythia_prior_up->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/temp_PbPb_y;   // q/g Modified
            Double_t erry_Pythia_prior_b = erry_Pythia_prior_a;

        // Herwig Prior
            Double_t erry_herwig_a = fabs(-1*hpp_nom->GetBinContent(j)+hpp_herwig_up->GetBinContent(j))/temp_pp_y;   
            Double_t erry_herwig_b = erry_herwig_a;
        
        //* Correlated 

        if(temp_pp_y!=0 && temp_PbPb_y!=0) {

            // Photon Purity -> Symmetrized
                Double_t erry_purity_a = fabs((hPbPb_purity_up->GetBinContent(j)/hpp_purity_up->GetBinContent(j)) - hratio->GetBinContent(j))/ hratio->GetBinContent(j);   
                Double_t erry_purity_b = erry_purity_a;

                Double_t erry_purity_a_PbPb = fabs(hPbPb_purity_up->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);   
                Double_t erry_purity_b_PbPb = erry_purity_a_PbPb;

                Double_t erry_purity_a_pp = fabs(hpp_purity_up->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);   
                Double_t erry_purity_b_pp = erry_purity_a_pp;

            // JEC
                Double_t erry_JEC_a = fabs((hPbPb_JECup->GetBinContent(j)/hpp_JECup->GetBinContent(j)) - hratio->GetBinContent(j))/ hratio->GetBinContent(j);   
                Double_t erry_JEC_b = fabs((hPbPb_JECdown->GetBinContent(j)/hpp_JECdown->GetBinContent(j)) - hratio->GetBinContent(j))/ hratio->GetBinContent(j);   

                Double_t erry_JEC_a_PbPb = fabs(hPbPb_JECup->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);
                Double_t erry_JEC_b_PbPb = fabs(hPbPb_JECdown->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);

                Double_t erry_JEC_a_pp = fabs(hpp_JECup->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);
                Double_t erry_JEC_b_pp = fabs(hpp_JECdown->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);

            // JER
                Double_t erry_JER_a = fabs((hPbPb_JERup->GetBinContent(j)/hpp_JERup->GetBinContent(j)) - hratio->GetBinContent(j)) /  hratio->GetBinContent(j);   
                Double_t erry_JER_b = fabs((hPbPb_JERdown->GetBinContent(j)/hpp_JERdown->GetBinContent(j)) - hratio->GetBinContent(j)) / hratio->GetBinContent(j);

                Double_t erry_JER_a_PbPb = fabs(hPbPb_JERup->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);
                Double_t erry_JER_b_PbPb = fabs(hPbPb_JERdown->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);

                Double_t erry_JER_a_pp = fabs(hpp_JERup->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);
                Double_t erry_JER_b_pp = fabs(hpp_JERdown->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);                

            // Substructure
                Double_t erry_photon_a = fabs((hPbPb_Photon_up->GetBinContent(j)/hpp_Photon_up->GetBinContent(j)) - hratio->GetBinContent(j)) /  hratio->GetBinContent(j);   
                Double_t erry_photon_b = fabs((hPbPb_Photon_down->GetBinContent(j)/hpp_Photon_down->GetBinContent(j)) - hratio->GetBinContent(j)) /  hratio->GetBinContent(j);
                Double_t erry_charged_a = fabs((hPbPb_Charged_up->GetBinContent(j)/hpp_Charged_up->GetBinContent(j)) - hratio->GetBinContent(j)) /  hratio->GetBinContent(j);   
                Double_t erry_charged_b = fabs((hPbPb_Charged_down->GetBinContent(j)/hpp_Charged_down->GetBinContent(j)) - hratio->GetBinContent(j)) /  hratio->GetBinContent(j);
                Double_t erry_neutral_a = fabs((hPbPb_Neutral_up->GetBinContent(j)/hpp_Neutral_up->GetBinContent(j)) - hratio->GetBinContent(j)) /  hratio->GetBinContent(j);   
                Double_t erry_neutral_b = fabs((hPbPb_Neutral_down->GetBinContent(j)/hpp_Neutral_down->GetBinContent(j)) - hratio->GetBinContent(j)) /  hratio->GetBinContent(j);

                Double_t erry_photon_a_PbPb = fabs(hPbPb_Photon_up->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);
                Double_t erry_photon_b_PbPb = fabs(hPbPb_Photon_down->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);
                Double_t erry_charged_a_PbPb = fabs(hPbPb_Charged_up->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);
                Double_t erry_charged_b_PbPb = fabs(hPbPb_Charged_down->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);
                Double_t erry_neutral_a_PbPb = fabs(hPbPb_Neutral_up->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);
                Double_t erry_neutral_b_PbPb = fabs(hPbPb_Neutral_down->GetBinContent(j)-hPbPb_nom->GetBinContent(j))/ hPbPb_nom->GetBinContent(j);

                Double_t erry_photon_a_pp = fabs(hpp_Photon_up->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);
                Double_t erry_photon_b_pp = fabs(hpp_Photon_down->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);
                Double_t erry_charged_a_pp = fabs(hpp_Charged_up->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);
                Double_t erry_charged_b_pp = fabs(hpp_Charged_down->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);
                Double_t erry_neutral_a_pp = fabs(hpp_Neutral_up->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);
                Double_t erry_neutral_b_pp = fabs(hpp_Neutral_down->GetBinContent(j)-hpp_nom->GetBinContent(j))/ hpp_nom->GetBinContent(j);      

            // Modelling Correlated

                // Double_t erry_prior_corr_a = fabs((hPbPb_Pythia_prior_up->GetBinContent(j)/hpp_herwig_up->GetBinContent(j)) - hratio->GetBinContent(j)) /  hratio->GetBinContent(j);   
                // Double_t erry_prior_corr_b = fabs((hPbPb_Pythia_prior_down->GetBinContent(j)/hpp_herwig_down->GetBinContent(j)) - hratio->GetBinContent(j)) /  hratio->GetBinContent(j);   

            erry_pp_sys_a = hpp_sys->GetErrorYhigh(j)/temp_pp_y;
            erry_pp_sys_b = hpp_sys->GetErrorYlow(j)/temp_pp_y;

            erry_PbPb_sys_a = hPbPb_sys->GetErrorYhigh(j)/temp_PbPb_y;
            erry_PbPb_sys_b = hPbPb_sys->GetErrorYlow(j)/temp_PbPb_y;

            erry_uncorr_up = TMath::Sqrt(erry_pp_sys_a*erry_pp_sys_a + erry_PbPb_sys_a*erry_PbPb_sys_a);
            erry_uncorr_do = TMath::Sqrt(erry_pp_sys_b*erry_pp_sys_b + erry_PbPb_sys_b*erry_PbPb_sys_b);

        erry_ratio_total_up = TMath::Sqrt(erry_stat_a*erry_stat_a + erry_uncorr_up*erry_uncorr_up);
        erry_ratio_total_do = TMath::Sqrt(erry_stat_b*erry_stat_b + erry_uncorr_do*erry_uncorr_do);

            erry_sys_uncorr_up = TMath::Sqrt(
                erry_reg_a_PbPb*erry_reg_a_PbPb + erry_reg_a_pp*erry_reg_a_pp
                + erry_response_a_PbPb*erry_response_a_PbPb + erry_response_a_pp*erry_response_a_pp 
                + erry_cent_a*erry_cent_a
                + erry_Pythia_prior_a*erry_Pythia_prior_a + erry_herwig_a*erry_herwig_a 
                + erry_purity_a_PbPb*erry_purity_a_PbPb  + erry_purity_a_pp*erry_purity_a_pp
                + erry_JEC_a_PbPb*erry_JEC_a_PbPb  + erry_JEC_a_pp*erry_JEC_a_pp
                + erry_JER_a_PbPb*erry_JER_a_PbPb  + erry_JER_a_pp*erry_JER_a_pp
                + erry_photon_a_PbPb*erry_photon_a_PbPb  + erry_photon_a_pp*erry_photon_a_pp
                + erry_charged_a_PbPb*erry_charged_a_PbPb  + erry_charged_a_pp*erry_charged_a_pp
                + erry_neutral_a_PbPb*erry_neutral_a_PbPb  + erry_neutral_a_pp*erry_neutral_a_pp
            ); // /temp_PbPb_y
            erry_sys_uncorr_do = TMath::Sqrt(
                erry_reg_b_PbPb*erry_reg_b_PbPb + erry_reg_b_pp*erry_reg_b_pp
                + erry_response_b_PbPb*erry_response_b_PbPb + erry_response_b_pp*erry_response_b_pp 
                + erry_cent_b*erry_cent_b
                + erry_Pythia_prior_b*erry_Pythia_prior_b + erry_herwig_b*erry_herwig_b 
                + erry_purity_b_PbPb*erry_purity_b_PbPb + erry_purity_b_pp*erry_purity_b_pp
                + erry_JEC_b_PbPb*erry_JEC_b_PbPb + erry_JEC_b_pp*erry_JEC_b_pp
                + erry_JER_b_PbPb*erry_JER_b_PbPb + erry_JER_b_pp*erry_JER_b_pp
                + erry_photon_b_PbPb*erry_photon_b_PbPb + erry_photon_b_pp*erry_photon_b_pp
                + erry_charged_b_PbPb*erry_charged_b_PbPb + erry_charged_b_pp*erry_charged_b_pp
                + erry_neutral_b_PbPb*erry_neutral_b_PbPb + erry_neutral_b_pp*erry_neutral_b_pp
            ); // /temp_PbPb_y

              // if(temp_pp_y!=hpp_nom->GetBinContent(j)) std::cout<<"Calculated = "<<hpp_nom->GetBinContent(j)<<"\t Obtained = "<<temp_pp_y<<"\n";
              // if(erry_sys_uncorr_up!=erry_PbPb_sys_b) 
              // std::cout<<"Calculated PbPb up = "<<erry_sys_uncorr_up<<"\t Obtained PbPb up = "<<erry_PbPb_sys_a<<"\t Nom PbPb = "<<temp_PbPb_y<<"\n";
              // if(erry_sys_uncorr_do!=erry_PbPb_sys_a) std::cout<<"Calculated PbPb do = "<<erry_sys_uncorr_do<<"\t Obtained PbPb do = "<<erry_PbPb_sys_a<<"\t Nom PbPb = "<<temp_PbPb_y<<"\n\n";

              //  std::cout<<"Calculated PbPb stat = "<<erry_stat_a_PbPb<<"\t Obtained PbPb stat = "<<hPbPb_stat->GetErrorYhigh(j)<<"\t Nom PbPb = "<<temp_PbPb_y<<"\n\n";

              // std::cout<<"Reg         a = "<<erry_reg_a_PbPb<<"\n"; //
              // std::cout<<"Response    a = "<<erry_response_a_PbPb<<"\n";//
              // std::cout<<"Cent        a = "<<erry_cent_a<<"\n";//
              // std::cout<<"MC          a = "<<erry_Pythia_prior_a<<"\n"; //
              // std::cout<<"purity      a = "<<erry_purity_a_PbPb<<"\n"; //
              // std::cout<<"JEC         a = "<<erry_JEC_a_PbPb<<"\n";//
              // std::cout<<"JER         a = "<<erry_JER_a_PbPb<<"\n"; //
              // std::cout<<"pho         a = "<<erry_photon_a_PbPb<<"\n"; //
              // std::cout<<"charged     a = "<<erry_charged_a_PbPb<<"\n"; //
              // std::cout<<"neutral     a = "<<erry_neutral_a_PbPb<<"\n\n"; //

            erry_corr_up = TMath::Sqrt(
                erry_reg_a_PbPb*erry_reg_a_PbPb + erry_reg_a_pp*erry_reg_a_pp
                + erry_response_a_PbPb*erry_response_a_PbPb + erry_response_a_pp*erry_response_a_pp 
                + erry_cent_a*erry_cent_a
                + erry_Pythia_prior_a*erry_Pythia_prior_a + erry_herwig_a*erry_herwig_a 
                + erry_purity_a*erry_purity_a
                + erry_JEC_a*erry_JEC_a
                + erry_JER_a*erry_JER_a
                + erry_photon_a*erry_photon_a
                + erry_charged_a*erry_charged_a
                + erry_neutral_a*erry_neutral_a
            );
            erry_corr_do = TMath::Sqrt(
                erry_reg_b_PbPb*erry_reg_b_PbPb + erry_reg_b_pp*erry_reg_b_pp
                + erry_response_b_PbPb*erry_response_b_PbPb + erry_response_b_pp*erry_response_b_pp 
                + erry_cent_b*erry_cent_b
                + erry_Pythia_prior_b*erry_Pythia_prior_b + erry_herwig_b*erry_herwig_b 
                + erry_purity_b*erry_purity_b
                + erry_JEC_b*erry_JEC_b
                + erry_JER_b*erry_JER_b
                + erry_photon_b*erry_photon_b
                + erry_charged_b*erry_charged_b
                + erry_neutral_b*erry_neutral_b
            );

        erry_ratio_total_corr_up = TMath::Sqrt(erry_stat_a*erry_stat_a + erry_corr_up*erry_corr_up);
        erry_ratio_total_corr_do = TMath::Sqrt(erry_stat_b*erry_stat_b + erry_corr_do*erry_corr_do);

        //* Histograms for each uncertainty in the ratio correlated and uncorrelated
         
          herr_uncorr_nom->SetBinContent(j,TMath::Sqrt(erry_stat_a*erry_stat_a));
          herr_uncorr_unfoldm1->SetBinContent(j,TMath::Sqrt(erry_reg_a_PbPb*erry_reg_a_PbPb + erry_reg_a_pp*erry_reg_a_pp));
          herr_uncorr_unfoldp1->SetBinContent(j,-TMath::Sqrt(erry_reg_b_PbPb*erry_reg_b_PbPb + erry_reg_b_pp*erry_reg_b_pp));
          herr_uncorr_purity_up->SetBinContent(j,TMath::Sqrt(erry_purity_a_PbPb*erry_purity_a_PbPb  + erry_purity_a_pp*erry_purity_a_pp));
          herr_uncorr_purity_down->SetBinContent(j,-TMath::Sqrt(erry_purity_b_PbPb*erry_purity_b_PbPb + erry_purity_b_pp*erry_purity_b_pp));
          herr_uncorr_JECup->SetBinContent(j,TMath::Sqrt(erry_JEC_a_PbPb*erry_JEC_a_PbPb  + erry_JEC_a_pp*erry_JEC_a_pp));
          herr_uncorr_JECdown->SetBinContent(j,-TMath::Sqrt(erry_JEC_b_PbPb*erry_JEC_b_PbPb + erry_JEC_b_pp*erry_JEC_b_pp));
          herr_uncorr_JERup->SetBinContent(j,TMath::Sqrt(erry_JER_a_PbPb*erry_JER_a_PbPb  + erry_JER_a_pp*erry_JER_a_pp));
          herr_uncorr_JERdown->SetBinContent(j,-TMath::Sqrt(erry_JER_b_PbPb*erry_JER_b_PbPb + erry_JER_b_pp*erry_JER_b_pp));
          herr_uncorr_response_up->SetBinContent(j,TMath::Sqrt(erry_response_a_PbPb*erry_response_a_PbPb + erry_response_a_pp*erry_response_a_pp ));
          herr_uncorr_response_down->SetBinContent(j,-TMath::Sqrt(erry_response_b_PbPb*erry_response_b_PbPb + erry_response_b_pp*erry_response_b_pp ));
          herr_uncorr_Photon_up->SetBinContent(j,TMath::Sqrt(erry_photon_a_PbPb*erry_photon_a_PbPb  + erry_photon_a_pp*erry_photon_a_pp));
          herr_uncorr_Photon_down->SetBinContent(j,-TMath::Sqrt(erry_photon_b_PbPb*erry_photon_b_PbPb + erry_photon_b_pp*erry_photon_b_pp));
          herr_uncorr_Charged_up->SetBinContent(j,TMath::Sqrt(erry_charged_a_PbPb*erry_charged_a_PbPb  + erry_charged_a_pp*erry_charged_a_pp));
          herr_uncorr_Charged_down->SetBinContent(j,-TMath::Sqrt(erry_charged_b_PbPb*erry_charged_b_PbPb + erry_charged_b_pp*erry_charged_b_pp));
          herr_uncorr_Neutral_up->SetBinContent(j,TMath::Sqrt(erry_neutral_a_PbPb*erry_neutral_a_PbPb  + erry_neutral_a_pp*erry_neutral_a_pp));
          herr_uncorr_Neutral_down->SetBinContent(j,-TMath::Sqrt(erry_neutral_b_PbPb*erry_neutral_b_PbPb + erry_neutral_b_pp*erry_neutral_b_pp));
          herr_uncorr_Centup->SetBinContent(j,TMath::Sqrt(erry_cent_a*erry_cent_a));
          herr_uncorr_Centdown->SetBinContent(j,-TMath::Sqrt(erry_cent_b*erry_cent_b));
          herr_uncorr_Pythia_prior_up->SetBinContent(j,TMath::Sqrt(erry_Pythia_prior_a*erry_Pythia_prior_a + erry_herwig_a*erry_herwig_a ));
          herr_uncorr_Pythia_prior_down->SetBinContent(j,-TMath::Sqrt(erry_Pythia_prior_b*erry_Pythia_prior_b + erry_herwig_b*erry_herwig_b ));

          herr_uncorr_total_up->SetBinContent(j,erry_ratio_total_up);
          herr_uncorr_total_down->SetBinContent(j,-erry_ratio_total_do);


          herr_corr_nom->SetBinContent(j,TMath::Sqrt(erry_stat_a*erry_stat_a));
          herr_corr_unfoldm1->SetBinContent(j,TMath::Sqrt(erry_reg_a_PbPb*erry_reg_a_PbPb + erry_reg_a_pp*erry_reg_a_pp));
          herr_corr_unfoldp1->SetBinContent(j,-TMath::Sqrt(erry_reg_b_PbPb*erry_reg_b_PbPb + erry_reg_b_pp*erry_reg_b_pp));
          herr_corr_purity_up->SetBinContent(j,TMath::Sqrt(erry_purity_a*erry_purity_a));
          herr_corr_purity_down->SetBinContent(j,-TMath::Sqrt(erry_purity_b*erry_purity_b));
          herr_corr_JECup->SetBinContent(j,TMath::Sqrt(erry_JEC_a*erry_JEC_a));
          herr_corr_JECdown->SetBinContent(j,-TMath::Sqrt(erry_JEC_b*erry_JEC_b));
          herr_corr_JERup->SetBinContent(j,TMath::Sqrt(erry_JER_a*erry_JER_a));
          herr_corr_JERdown->SetBinContent(j,-TMath::Sqrt(erry_JER_b*erry_JER_b));
          herr_corr_response_up->SetBinContent(j,TMath::Sqrt(erry_response_a_PbPb*erry_response_a_PbPb + erry_response_a_pp*erry_response_a_pp ));
          herr_corr_response_down->SetBinContent(j,-TMath::Sqrt(erry_response_b_PbPb*erry_response_b_PbPb + erry_response_b_pp*erry_response_b_pp ));
          herr_corr_Photon_up->SetBinContent(j,TMath::Sqrt(erry_photon_a*erry_photon_a));
          herr_corr_Photon_down->SetBinContent(j,-TMath::Sqrt(erry_photon_b*erry_photon_b));
          herr_corr_Charged_up->SetBinContent(j,TMath::Sqrt(erry_charged_a*erry_charged_a));
          herr_corr_Charged_down->SetBinContent(j,-TMath::Sqrt(erry_charged_b*erry_charged_b));
          herr_corr_Neutral_up->SetBinContent(j,TMath::Sqrt(erry_neutral_a*erry_neutral_a));
          herr_corr_Neutral_down->SetBinContent(j,-TMath::Sqrt(erry_neutral_b*erry_neutral_b));
          herr_corr_Centup->SetBinContent(j,TMath::Sqrt(erry_cent_a*erry_cent_a));
          herr_corr_Centdown->SetBinContent(j,-TMath::Sqrt(erry_cent_b*erry_cent_b));
          herr_corr_Pythia_prior_up->SetBinContent(j,TMath::Sqrt(erry_Pythia_prior_a*erry_Pythia_prior_a + erry_herwig_a*erry_herwig_a ));
          herr_corr_Pythia_prior_down->SetBinContent(j,-TMath::Sqrt(erry_Pythia_prior_b*erry_Pythia_prior_b + erry_herwig_b*erry_herwig_b ));

          herr_corr_total_up->SetBinContent(j,erry_ratio_total_corr_up);
          herr_corr_total_down->SetBinContent(j,-erry_ratio_total_corr_do);
        }
        

        // Error x and vectors
        vec_x[j] = hratio->GetBinCenter(j);
        vec_y[j] = hratio->GetBinContent(j);

        errstat_up[j] = erry_stat_a;
        errstat_do[j] = erry_stat_b;      
        errx_do[j] = 0.5*hratio->GetBinWidth(j);
        errx_up[j] = errx_do[j];
        // erry_up[j] = erry_uncorr_up; 
        // erry_do[j] = erry_uncorr_do; 

        errtot_up[j] = erry_ratio_total_up;
        errtot_do[j] = erry_ratio_total_do;

        erry_syscorr_up[j] = erry_corr_up;
        erry_syscorr_do[j] = erry_corr_do;

        errtot_corr_up[j] = erry_ratio_total_corr_up;
        errtot_corr_do[j] = erry_ratio_total_corr_do;

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
    
    //  Plot systematic uncertainty comparisons
    std::vector<TString>sel = {" ","#bf{PbPb 1.7 nb^{-1}, pp 301 pb^{-1}(5.02 TeV)}","Cent. 0-30%",Form("p_{T}^{#gamma}>%.0f, x_{J}>%.1f,|#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.4)}; ;
      if(label.Contains("xJ_gp4")){
        sel = {" ","#bf{PbPb 1.7 nb^{-1}, pp 301 pb^{-1}(5.02 TeV)}","Cent. 0-30%",Form("p_{T}^{#gamma}>%.0f, x_{J}>%.1f,|#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.4)}; 
      }
      else if(label.Contains("xJ_gp8")){
        sel = {" ","#bf{PbPb 1.7 nb^{-1}, pp 301 pb^{-1}(5.02 TeV)}","Cent. 0-30%",Form("p_{T}^{#gamma}>%.0f, x_{J}>%.1f,|#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi",100.0,0.8)}; 
      }
      //* Correlated Splitting Up and Down Variations 

        std::vector<TH1D*> hist_input_corr_ratio_up;
        std::vector<TString> histname_input_corr_ratio_up;
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_nom->Clone());
        // herr_corr_nom->Scale(-1.0);
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_nom->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_unfoldm1->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_unfoldp1->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_purity_up->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_purity_down->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_JECup->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_JECdown->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_JERup->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_JERdown->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_response_up->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_response_down->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_Photon_up->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_Photon_down->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_Charged_up->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_Charged_down->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_Neutral_up->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_Neutral_down->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_Centup->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_Centdown->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_Pythia_prior_up->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_Pythia_prior_down->Clone());
        hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_total_up->Clone());
        // hist_input_corr_ratio_up.push_back((TH1D*)herr_corr_total_down->Clone());

        histname_input_corr_ratio_up.push_back("Stat. unc");
        // histname_input_corr_ratio_up.push_back("Stat. Unc (sym)");
        histname_input_corr_ratio_up.push_back(herr_corr_unfoldm1->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_unfoldp1->GetTitle());
        histname_input_corr_ratio_up.push_back(herr_corr_purity_up->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_purity_down->GetTitle());
        histname_input_corr_ratio_up.push_back(herr_corr_JECup->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_JECdown->GetTitle());
        histname_input_corr_ratio_up.push_back(herr_corr_JERup->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_JERdown->GetTitle());
        histname_input_corr_ratio_up.push_back(herr_corr_response_up->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_response_down->GetTitle());
        histname_input_corr_ratio_up.push_back(herr_corr_Photon_up->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_Photon_down->GetTitle());
        histname_input_corr_ratio_up.push_back(herr_corr_Charged_up->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_Charged_down->GetTitle());
        histname_input_corr_ratio_up.push_back(herr_corr_Neutral_up->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_Neutral_down->GetTitle());
        histname_input_corr_ratio_up.push_back(herr_corr_Centup->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_Centdown->GetTitle());
        histname_input_corr_ratio_up.push_back(herr_corr_Pythia_prior_up->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_Pythia_prior_down->GetTitle());
        histname_input_corr_ratio_up.push_back(herr_corr_total_up->GetTitle());
        // histname_input_corr_ratio_up.push_back(herr_corr_total_down->GetTitle());

        //* DOWN ------------------------------------------------

        std::vector<TH1D*> hist_input_corr_ratio_down;
        std::vector<TString> histname_input_corr_ratio_down;
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_nom->Clone());
        herr_corr_nom->Scale(-1.0);
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_nom->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_unfoldm1->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_unfoldp1->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_purity_up->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_purity_down->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_JECup->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_JECdown->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_JERup->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_JERdown->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_response_up->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_response_down->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_Photon_up->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_Photon_down->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_Charged_up->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_Charged_down->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_Neutral_up->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_Neutral_down->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_Centup->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_Centdown->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_Pythia_prior_up->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_Pythia_prior_down->Clone());
        // hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_total_up->Clone());
        hist_input_corr_ratio_down.push_back((TH1D*)herr_corr_total_down->Clone());

        // histname_input_corr_ratio_down.push_back("Stat. Unc");
        histname_input_corr_ratio_down.push_back("Stat. unc");
        // histname_input_corr_ratio_down.push_back(herr_corr_unfoldm1->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_unfoldp1->GetTitle());
        // histname_input_corr_ratio_down.push_back(herr_corr_purity_up->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_purity_down->GetTitle());
        // histname_input_corr_ratio_down.push_back(herr_corr_JECup->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_JECdown->GetTitle());
        // histname_input_corr_ratio_down.push_back(herr_corr_JERup->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_JERdown->GetTitle());
        // histname_input_corr_ratio_down.push_back(herr_corr_response_up->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_response_down->GetTitle());
        // histname_input_corr_ratio_down.push_back(herr_corr_Photon_up->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_Photon_down->GetTitle());
        // histname_input_corr_ratio_down.push_back(herr_corr_Charged_up->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_Charged_down->GetTitle());
        // histname_input_corr_ratio_down.push_back(herr_corr_Neutral_up->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_Neutral_down->GetTitle());
        // histname_input_corr_ratio_down.push_back(herr_corr_Centup->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_Centdown->GetTitle());
        // histname_input_corr_ratio_down.push_back(herr_corr_Pythia_prior_up->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_Pythia_prior_down->GetTitle());
        // histname_input_corr_ratio_down.push_back(herr_corr_total_up->GetTitle());
        histname_input_corr_ratio_down.push_back(herr_corr_total_down->GetTitle());
    
      if(label.Contains("Rg")){
          histname_input_corr_ratio_up.push_back("R_{g}");
          histname_input_corr_ratio_down.push_back("R_{g}");
      }
      else{
          histname_input_corr_ratio_up.push_back("#it{g}");
          histname_input_corr_ratio_down.push_back("#it{g}");
      }
      histname_input_corr_ratio_up.push_back("PbPb/pp ratio Rel. uncertainties");
      histname_input_corr_ratio_up.push_back(label+"_corr_rel_uncert");

      histname_input_corr_ratio_down.push_back("PbPb/pp ratio Rel. uncertainties");
      histname_input_corr_ratio_down.push_back(label+"_corr_rel_uncert");

      sel.push_back("end");
      sel.push_back("NOSTACKB_HIST");
      Plot_hist_up(hist_input_corr_ratio_up,histname_input_corr_ratio_up,"left_opt_label_leg",sel);
      sel.pop_back();
      sel.push_back("NOSTACKB_HIST_SAME");
      Plot_hist_down(hist_input_corr_ratio_down,histname_input_corr_ratio_down,"left_opt_label",sel);

    //* Uncorrelated Splitting Up and Down Variations 

        std::vector<TH1D*> hist_input_uncorr_ratio_up;
        std::vector<TString> histname_input_uncorr_ratio_up;
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_nom->Clone());
        // herr_uncorr_nom->Scale(-1.0);
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_nom->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_unfoldm1->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_unfoldp1->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_purity_up->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_purity_down->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_JECup->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_JECdown->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_JERup->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_JERdown->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_response_up->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_response_down->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_Photon_up->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_Photon_down->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_Charged_up->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_Charged_down->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_Neutral_up->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_Neutral_down->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_Centup->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_Centdown->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_Pythia_prior_up->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_Pythia_prior_down->Clone());
        hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_total_up->Clone());
        // hist_input_uncorr_ratio_up.push_back((TH1D*)herr_uncorr_total_down->Clone());

        histname_input_uncorr_ratio_up.push_back("Stat. unc");
        // histname_input_uncorr_ratio_up.push_back("Stat. Unc (sym)");
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_unfoldm1->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_unfoldp1->GetTitle());
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_purity_up->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_purity_down->GetTitle());
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_JECup->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_JECdown->GetTitle());
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_JERup->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_JERdown->GetTitle());
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_response_up->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_response_down->GetTitle());
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_Photon_up->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_Photon_down->GetTitle());
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_Charged_up->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_Charged_down->GetTitle());
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_Neutral_up->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_Neutral_down->GetTitle());
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_Centup->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_Centdown->GetTitle());
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_Pythia_prior_up->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_Pythia_prior_down->GetTitle());
        histname_input_uncorr_ratio_up.push_back(herr_uncorr_total_up->GetTitle());
        // histname_input_uncorr_ratio_up.push_back(herr_uncorr_total_down->GetTitle());

        //* DOWN ------------------------------------------------

        std::vector<TH1D*> hist_input_uncorr_ratio_down;
        std::vector<TString> histname_input_uncorr_ratio_down;
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_nom->Clone());
        herr_uncorr_nom->Scale(-1.0);
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_nom->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_unfoldm1->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_unfoldp1->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_purity_up->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_purity_down->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_JECup->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_JECdown->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_JERup->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_JERdown->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_response_up->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_response_down->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_Photon_up->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_Photon_down->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_Charged_up->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_Charged_down->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_Neutral_up->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_Neutral_down->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_Centup->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_Centdown->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_Pythia_prior_up->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_Pythia_prior_down->Clone());
        // hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_total_up->Clone());
        hist_input_uncorr_ratio_down.push_back((TH1D*)herr_uncorr_total_down->Clone());

        // histname_input_uncorr_ratio_down.push_back("Stat. Unc");
        histname_input_uncorr_ratio_down.push_back("Stat. unc");
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_unfoldm1->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_unfoldp1->GetTitle());
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_purity_up->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_purity_down->GetTitle());
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_JECup->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_JECdown->GetTitle());
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_JERup->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_JERdown->GetTitle());
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_response_up->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_response_down->GetTitle());
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_Photon_up->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_Photon_down->GetTitle());
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_Charged_up->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_Charged_down->GetTitle());
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_Neutral_up->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_Neutral_down->GetTitle());
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_Centup->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_Centdown->GetTitle());
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_Pythia_prior_up->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_Pythia_prior_down->GetTitle());
        // histname_input_uncorr_ratio_down.push_back(herr_uncorr_total_up->GetTitle());
        histname_input_uncorr_ratio_down.push_back(herr_uncorr_total_down->GetTitle());
    
      if(label.Contains("Rg")){
          histname_input_uncorr_ratio_up.push_back("R_{g}");
          histname_input_uncorr_ratio_down.push_back("R_{g}");
      }
      else{
          histname_input_uncorr_ratio_up.push_back("#it{g}");
          histname_input_uncorr_ratio_down.push_back("#it{g}");
      }
      histname_input_uncorr_ratio_up.push_back("PbPb/pp ratio Rel. uncertainties");
      histname_input_uncorr_ratio_up.push_back(label+"_uncorr_rel_uncert");

      histname_input_uncorr_ratio_down.push_back("PbPb/pp ratio Rel. uncertainties");
      histname_input_uncorr_ratio_down.push_back(label+"_uncorr_rel_uncert");

      sel.push_back("end");
      sel.push_back("NOSTACKB_HIST");
      Plot_hist_up(hist_input_uncorr_ratio_up,histname_input_uncorr_ratio_up,"left_opt_label_leg",sel);
      sel.pop_back();
      sel.push_back("NOSTACKB_HIST_SAME");
      Plot_hist_down(hist_input_uncorr_ratio_down,histname_input_uncorr_ratio_down,"left_opt_label",sel);

    // std::cout<<"PbPb sys err up = "<<PbPb_untag_sys_err_up<<"\n";

    PbPb_untag_sys_err_up = TMath::Sqrt(PbPb_untag_sys_err_up);
    PbPb_untag_sys_err_do = TMath::Sqrt(PbPb_untag_sys_err_do);

    pp_untag_sys_err_up = TMath::Sqrt(pp_untag_sys_err_up);
    pp_untag_sys_err_do = TMath::Sqrt(pp_untag_sys_err_do);
    
    PbPb_total_sys_err_up = TMath::Sqrt(PbPb_total_sys_err_up);
    PbPb_total_sys_err_do = TMath::Sqrt(PbPb_total_sys_err_do);

    pp_total_sys_err_up = TMath::Sqrt(pp_total_sys_err_up);
    pp_total_sys_err_do = TMath::Sqrt(pp_total_sys_err_do);
    // auto hratio_stat = new TGraphAsymmErrors(hratio->GetNbinsX(),vec_x,vec_y,errx_up,errx_do,errstat_up,errstat_do);
    auto hratio_sys = new TGraphAsymmErrors(hratio->GetNbinsX()+1,vec_x,vec_y,errx_do,errx_up,erry_do,erry_up);
    auto hratio_tot = new TGraphAsymmErrors(hratio->GetNbinsX()+1,vec_x,vec_y,errx_do,errx_up,errtot_do,errtot_up);

    auto hratio_sys_corr = new TGraphAsymmErrors(hratio->GetNbinsX()+1,vec_x,vec_y,errx_do,errx_up,erry_syscorr_do,erry_syscorr_up);
    auto hratio_tot_corr = new TGraphAsymmErrors(hratio->GetNbinsX()+1,vec_x,vec_y,errx_do,errx_up,errtot_corr_do,errtot_corr_up);

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

    gStyle->SetHatchesLineWidth(2);
    gStyle->SetHatchesSpacing(0.8);
    
    hratio->SetLineColor(kRed+1); // Red Box
    hratio->SetMarkerColor(kRed+1);
    hratio->SetMarkerStyle(21);
    hratio->SetMarkerSize(1.2);
    hratio->SetFillStyle(1000); 
    // hratio->SetFillStyle(3945); // Not yet working
    hratio->SetFillColorAlpha(kRed-7,transparency);

    // hratio_tot->SetFillStyle(1000); 
    hratio_tot->SetFillStyle(3005); 
    hratio_tot->SetFillColorAlpha(kRed-7,transparency);
    hratio_tot->SetLineColor(kRed-7); 
    hratio_tot->SetMarkerColor(kRed-7);
    hratio_tot->SetMarkerStyle(21);
    hratio_tot->SetMarkerSize(0);

    // hratio_tot_corr->SetFillStyle(1000); 
    hratio_tot_corr->SetFillStyle(3004); 
    hratio_tot_corr->SetFillColorAlpha(kBlue-7,transparency);
    hratio_tot_corr->SetLineColor(kBlue-7); 
    hratio_tot_corr->SetMarkerColor(kBlue-7);
    hratio_tot_corr->SetMarkerStyle(24);
    hratio_tot_corr->SetMarkerSize(0);

    std::vector<unsigned int> fill_col_arr = {kOrange-3,kAzure-3,kMagenta+2,kGreen+2,kRed-7,kBlue-7,kSpring+10,kViolet-3};
    std::vector<unsigned int> mark_col_arr = {kOrange+2,kAzure+0,kMagenta+0,kGreen-2,kRed+1,kBlue+1,kSpring+4 ,kViolet+0};
    std::vector<unsigned int> mark_sty_arr = {kFullStar,kFullTriangleUp,kFullCrossX,kFullSquare,kFullDiamond,kFullCircle,kFourSquaresX,kFourSquaresPlus};

    std::vector<int> mark_col_pal = {korange,kazure,kmagenta,kgreen,kred,kblue,kspring,kviolet};
    std::vector<int> fill_col_pal = {korangeLight,kazureLight,kmagentaLight,kgreenLight,kredLight,kblueLight,kspringLight,kvioletLight};

    std::vector<int> col_pal = {
      pal->GetColor(213, 94,  0),   // Red
      pal->GetColor(  0,114,178),   // Blue
      pal->GetColor(204,121,167),   // Pink
      pal->GetColor(  0,158,115),   // Green
      pal->GetColor(230,159,  0),   // Orange
      pal->GetColor( 86,180,233),   // Light blue
      pal->GetColor(240,228, 66),   // Yellow

      pal->GetColor( 72,  0,190),   // Violet
      pal->GetColor(153, 79,  0),   // Brown
      pal->GetColor(  0, 92, 46),   // Teal

    };

    for (int i_file = 0 ; i_file<theory_list.size();i_file++){
        transparency = 0.55;
        h_theory[i_file]->SetMarkerSize(1.5);
        h_theory[i_file]->SetFillStyle(1001);
        h_theory[i_file]->SetLineStyle(1);

        h_theory[i_file]->SetMarkerColorAlpha(col_pal[i_file],0.9);
        h_theory[i_file]->SetMarkerStyle(mark_sty_arr[i_file]);
        h_theory[i_file]->SetLineColor(col_pal[i_file]);
        h_theory[i_file]->SetFillColorAlpha(col_pal[i_file],transparency);
    }

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
    float T = 0.1*H_ref;  //0.08*H_ref;
    float B = 0.12*H_ref;  //0.12*H_ref; 
    float L = 0.15*W_ref;  //0.12*W_ref;
    float R = 0.08*W_ref;  //0.04*W_ref;

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

    leg_x1 = 0.48;
    leg_y1 = 0.6;
    leg_x2 = 0.88;
    leg_y2 = 0.885;

    TLegend *l;
    l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
    l->SetFillStyle(0);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->SetTextSize(0.035);
    l->SetTextFont(42);
    l->SetBorderSize(0);

    // l->AddEntry(hratio, "Data", "lepf");

    l->AddEntry(hratio_tot, "Uncorrelated", "pf");
    l->AddEntry(hratio_tot_corr, "Correlated", "pf");

    hratio->Draw("E1_][P0");
    // hratio->Draw("E1P0");
    hratio_tot->Draw("P5");
    hratio_tot_corr->Draw("P5");

    for (int i_file = 0 ; i_file<theory_list.size();i_file++){
        h_theory[i_file]->Draw("P5");
        l->AddEntry(h_theory[i_file], label_list[i_file], "pf");
    }  

    l->Draw();

    float line_left_edge = hratio->GetXaxis()->GetBinLowEdge(1);
    if(label.Contains("Rg")){
        line_left_edge = hratio->GetXaxis()->GetBinLowEdge(2);
    }
    hratio->GetXaxis()->SetRangeUser(line_left_edge,hratio->GetXaxis()->GetBinUpEdge(hratio->GetNbinsX()-1));
    
    // hratio->SetMinimum(0);
    // hratio->SetMaximum(3);

    TLine *line=new TLine(line_left_edge,1.0,hratio->GetXaxis()->GetBinLowEdge(hratio->GetNbinsX()),1.0);
    line->SetLineColor(kGray+2);
    line->SetLineStyle(9);
    line->SetLineWidth(2);
    line->Draw("SAME");

    if(label.Contains("Rg") && label.Contains("xJ_gp8")){
        hratio->SetMinimum(0.25);
        hratio->SetMaximum(1.9999);
    }
    else if(label.Contains("Rg") && label.Contains("xJ_gp4")){
        hratio->SetMinimum(0.45);
        hratio->SetMaximum(1.7999);
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp8")){
        hratio->SetMinimum(0.4);
        hratio->SetMaximum(2.19999);
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp4")){
        hratio->SetMinimum(0.4);
        hratio->SetMaximum(2.39999);
    }
    else{
        hratio->SetMinimum(0.4);
        hratio->SetMaximum(1.6);
    }
    // pad1->RedrawAxis();
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
        hPbPb_nom->GetYaxis()->SetTitleFont(42);
        hPbPb_nom->GetYaxis()->SetTitleSize(0.075/upper_pad_ratio);
        hPbPb_nom->GetYaxis()->SetTitleOffset(1);
        hPbPb_nom->GetYaxis()->SetLabelFont(42);
        hPbPb_nom->GetYaxis()->SetLabelSize(0.06/upper_pad_ratio);
        hPbPb_nom->GetYaxis()->SetLabelOffset(0.007/upper_pad_ratio);
        hPbPb_nom->GetYaxis()->SetTickLength(0.03/upper_pad_ratio);

    // Y axis ratio plot settings
        hratio->GetYaxis()->SetTitle("#frac{PbPb}{pp}       ");
        // hratio->GetYaxis()->SetNdivisions(-4);
        hratio->GetYaxis()->SetTitleFont(42);
        hratio->GetYaxis()->SetTitleSize(0.075/lower_pad_ratio);
        hratio->GetYaxis()->SetTitleOffset(1);
        hratio->GetYaxis()->SetLabelFont(42); // Absolute font size in pixel (precision 3)
        hratio->GetYaxis()->SetLabelSize(0.06/lower_pad_ratio);
        hratio->GetYaxis()->SetLabelOffset(0.007/lower_pad_ratio);
        hratio->GetYaxis()->SetTickLength(0.03/lower_pad_ratio);
        
    // X axis ratio plot settings
        hratio->GetXaxis()->SetTitleFont(42);
        hratio->GetXaxis()->SetTitleSize(0.075/lower_pad_ratio);
        hratio->GetXaxis()->SetTitleOffset(1.0);
        hratio->GetXaxis()->SetLabelFont(42); // Absolute font size in pixel (precision 3)
        hratio->GetXaxis()->SetLabelSize(0.06/lower_pad_ratio);
        hratio->GetXaxis()->SetLabelOffset(0.007/lower_pad_ratio);
        hratio->GetXaxis()->SetTickLength(0.03/lower_pad_ratio);
        hratio->GetXaxis()->SetNdivisions(hPbPb_nom->GetXaxis()->GetNdivisions());
    if(label.Contains("Rg") && label.Contains("xJ_gp8")){
        hratio->GetXaxis()->SetTitle("Groomed jet radius R_{g}");
        hPbPb_nom->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{dR_{g}}    ");
        hPbPb_nom->SetMinimum(0.0);
        hPbPb_nom->SetMaximum(22.0);
    }
    else if(label.Contains("Rg") && label.Contains("xJ_gp4")){
        hratio->GetXaxis()->SetTitle("Groomed jet radius R_{g}");
        hPbPb_nom->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{dR_{g}}    ");
        hPbPb_nom->SetMinimum(0.0);
        hPbPb_nom->SetMaximum(16.0); 
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp8")){
        hratio->GetXaxis()->SetTitle("Jet girth #it{g}");
        hPbPb_nom->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{d#it{g}}   ");
        hPbPb_nom->SetMinimum(0.0);
        hPbPb_nom->SetMaximum(43.0); 
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp4")){
        hratio->GetXaxis()->SetTitle("Jet girth #it{g}");
        hPbPb_nom->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{d#it{g}}   ");
        hPbPb_nom->SetMinimum(0.0);
        hPbPb_nom->SetMaximum(35.0);
    }

// Additional text
    canv->cd();
    CMS_lumi( pad1, iPeriod, iPos );

    pad1->cd();
    TLatex latex;
    // latex.SetNDC(1);
    latex.SetTextFont(42);
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    
    latex.SetTextSize(0.035);    
    latex.SetTextAlign(12); 

    if(label.Contains("Rg") && label.Contains("xJ_gp8")){
        leg_x1 = 0.48;
        leg_y1 = 0.6;
        leg_x2 = 0.88;
        leg_y2 = 0.885;

        leg_y1-=0.03;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
        leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");

        
        leg_x1 = 0.2;
        leg_y1 = 0.82;
        // leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV , #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.8");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44 , |#eta_{jet}| < 2");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
    }
    else if(label.Contains("Rg") && label.Contains("xJ_gp4")){
        leg_x1 = 0.48;
        leg_y1 = 0.6;
        leg_x2 = 0.88;
        leg_y2 = 0.885;
        leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");

        leg_x1 = 0.2;
        leg_y1 = 0.82;

        // leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV , #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.4");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44 , |#eta_{jet}| < 2");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp8")){
        leg_x1 = 0.48;
        leg_y1 = 0.6;
        leg_x2 = 0.88;
        leg_y2 = 0.885;
        leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
        // leg_y1-=0.08;
        // latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");

        leg_x1 = 0.2;
        leg_y1 = 0.82;

        // leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV , #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.8");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44 , |#eta_{jet}| < 2");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp4")){
        leg_x1 = 0.48;
        leg_y1 = 0.6;
        leg_x2 = 0.88;
        leg_y2 = 0.885;
        leg_y1-=0.05;
        latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
        // leg_y1-=0.08;
        // latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");

        leg_x1 = 0.2;
        leg_y1 = 0.82;

        // leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV , #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.4");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44 , |#eta_{jet}| < 2");
        leg_y1-=0.08;
        latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
    }
    else{
      leg_x1 = 0.58;
      leg_y1 = 0.72;
      leg_x2 = 0.8;
      leg_y2 = 0.87;

      leg_y1-=0.08;
      latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV , #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.4");
      leg_y1-=0.08;
      latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44 , |#eta_{jet}| < 2");
      leg_y1-=0.08;
      latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
      
      leg_x1 = 0.22;
      leg_y1 = 0.72;
      leg_y1-=0.08;
      latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
      leg_y1-=0.08;
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

void overlay_ratio_correlated(){
    
    gROOT->SetBatch();

    TString input_theory_path = "Overlay_theory/Theory_graph/";
    std::vector<TString> theory_case = 
    {
      // "HYBRID_Elastic_Wake_0_","HYBRID_Elastic_Wake_1_","HYBRID_NoElastic_Wake_0_","HYBRID_NoElastic_Wake_1_",
     // "HYBRID_NoElastic_Lres2_Wake_0_","HYBRID_NoElastic_Lres2_Wake_1_","HYBRID_NoElastic_LresInf_Wake_0_","HYBRID_NoElastic_LresInf_Wake_1_",
    };
    std::vector<TString> theory_case_label = 
    {
      // "Elastic L_{res}=0, no wake","Elastic L_{res}=0, wake","No elastic L_{res}=0, no wake","No elastic L_{res}=0, wake",
     //"No elastic L_{res}=2/#piT, no wake","No elastic L_{res}=2/#piT, wake","No elastic L_{res}=#infty, no wake","No elastic L_{res}=#infty, wake",
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
        theory_list.clear();
        label_list.clear();
        for(int i=0;i<theory_case.size();i++){ 
            theory_list.push_back(input_theory_path+theory_case[i]+var+".root");
            label_list.push_back(theory_case_label[i]);
        }
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

        TCanvas *c_temp = overlay_theory(theory_list,label_list,file_PbPb,label_PbPb,file_pp,label_pp,"PbPb_pp_0_30_Jul_31_Plot_Feb_15_"+var+"_ratio_all_rel",var);
        // delete c_temp;
        std::cout<<"PbPb_pp_0_30_Jul_31_Plot_Feb_15_"+var+"_ratio_all_rel has been saved\n";
        std::cout<<"\n-------------------------------------------\n";
        // break;
    }        
    
}
