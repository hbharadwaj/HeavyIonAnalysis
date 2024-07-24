// overlay_Data_ratio("Uncertainty/OutputCombined/pp_Data_May_5_pp_2017_sys_WP_update_Data_Rg_unfold_X.root","pp_Data_May_5_pp_2017_sys_WP_update_Data_Rg_unfold_X",{"OutputPlots/OutputPlots_pp_QCDPhoton_jets/Output_pp_QCDPhoton_jets.root","OutputPlots/OutputPlots_pp_Herwig7_jets/Output_pp_Herwig7_jets.root"},{"Pythia8 CP5","Herwig7 CH3"},"h_Rg_truef_0","Rg")

#include <TLegend.h>        // needed for Legend
#include <TCanvas.h>        // needed for Canvas
#include <TMath.h>          //! needed for floating values in plots for some reason
#include <THStack.h>        // needed for THStack
#include <TLatex.h>         // needed for TLatex
#include "TFile.h"          // needed for TFile

TString centstring="";
TString label="";
// TCanvas c;
TLegend *l;
TString output_path = "OverlayData";
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
float lumiTextSize     = 0.6; //0.38;//0.6;
float lumiTextOffset   = 0.15; //0.2;
float cmsTextSize      = 0.75; //0.5;//0.75;
float cmsTextOffset    = 0.12; //0.1;  // only used in outOfFrame version

float relPosX    = 0.1;//0.125;//0.045;
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
//   tdrStyle->SetErrorX(0.);
  
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

TCanvas* overlay_pp_MC(TString file_pp, TString label_pp,std::vector<TString>file_list,std::vector<TString>label_list, TString hname="",TString out_label="",TString varname="Rg"){
    int iPeriod = 300;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
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

    label = out_label;

    // Style settings
        // gStyle->SetOptStat(0);      // No Stat Box
        // gStyle->SetOptTitle(0);     // No Title
        // gStyle->SetPadTickX(1);
        // gStyle->SetPadTickY(1);
        // gStyle->SetPalette(1);
        // gStyle->SetHistLineWidth(1);
        // gStyle->SetMarkerSize(0.5);
        TColor *pal = new TColor();
        // good for primary marker colors         
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
        const std::vector<int> colarray  = {kRed,kSpring-6,kRed+3,kOrange+7,kMagenta+2,kBlue,kViolet-1,kPink+7};// {kred,kgrass,kpurple,kteal,kviolet,kskyblue,korange, kpink,klblue,korange,kteal,kviolet,kskyblue,kgrass,kpink,klblue }; // kred,
        const std::vector<int> linearray = {1,3,6,2,7};//{kSolid,kDashDotted,6,2,10,8,7};
        const std::vector<int> markarray = {25, 22, 32, 29, 28, 39, 40, 24, 21, 26, 23, 30, 34, 37, 41};
        Int_t kred_hybrid = pal->GetColor(213, 94,  0);
        std::vector<int> col_pal = {
            // pal->GetColor(213, 94,  0),   // Red
            pal->GetColor(  0,114,178),   // Blue
            pal->GetColor(204,121,167),   // Pink
            pal->GetColor(  0,158,115),   // Green

            pal->GetColor( 72,  0,190),   // Violet
            pal->GetColor(153, 79,  0),   // Brown
            pal->GetColor(  0, 92, 46),   // Teal
            pal->GetColor( 86,180,233),   // Light blue

            pal->GetColor(230,159,  0),   // Orange     // The original colors from the palette
            pal->GetColor(240,228, 66),   // Yellow     // The original colors from the palette

        };
      
    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();
    gErrorIgnoreLevel = kFatal;
    TString DIR = output_path;
    output_path = DIR;
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    TFile *f_out = new TFile(output_path+"/"+label+".root", "recreate");
    TDirectory *target = gDirectory;

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

        h_theory_Elastic_noWake  = (TGraphAsymmErrors*)f_theory_Elastic_noWake->Get("vacuum_graph");
        h_theory_Elastic_Wake    = (TGraphAsymmErrors*)f_theory_Elastic_Wake->Get("vacuum_graph");
        h_theory_noElastic_noWake= (TGraphAsymmErrors*)f_theory_noElastic_noWake->Get("vacuum_graph");
        h_theory_noElastic_Wake  = (TGraphAsymmErrors*)f_theory_noElastic_Wake->Get("vacuum_graph");        
    }

    TFile *f_pp = TFile::Open(file_pp);

    TH1D* hnom = (TH1D*)f_pp->Get(Form("%s_nom",label_pp.Data()));
    TGraphAsymmErrors *stat_uncert = (TGraphAsymmErrors*)f_pp->Get("stat_uncert");
    TGraphAsymmErrors *sys_uncert = (TGraphAsymmErrors*)f_pp->Get("sys_uncert");
    TGraphAsymmErrors *hpp_tot = (TGraphAsymmErrors*)f_pp->Get("tot_uncert");

    // Define the ratio plot
    TH1D *hratio = (TH1D*)hnom->Clone("ratio");
    // hratio->Sumw2();
    hratio->Divide(hnom);

    // std::cout<<"Ratio done\n"<<hratio->GetNbinsX()<<"\n";

    Double_t vec_x[20],vec_y[20],errx_do[20],errx_up[20],errtot_do[20],errtot_up[20];

    Double_t hybrid_vec_y[20],hybrid_errtot_do[20],hybrid_errtot_up[20];

    for(Int_t j=0;j<hratio->GetNbinsX()+2;j++){ 

        vec_x[j] = 0;
        vec_y[j] = 0; 
        errx_do[j] = 0;
        errx_up[j] = 0;
        errtot_up[j] = 0;
        errtot_do[j] = 0;

        hybrid_vec_y[j] = 0;

        hybrid_errtot_up[j] = 0;
        hybrid_errtot_do[j] = 0;

        if(hratio->GetBinContent(j)==0)continue;

        Double_t erry_data_a = hpp_tot->GetErrorYhigh(j); 
        Double_t erry_data_b = hpp_tot->GetErrorYlow(j); 

        Double_t erry_ratio_data_up = erry_data_a/hnom->GetBinContent(j);//TMath::Sqrt(erry_data_a*erry_data_a + erry_data_a*erry_data_a);
        Double_t erry_ratio_data_do = erry_data_b/hnom->GetBinContent(j);//TMath::Sqrt(erry_data_b*erry_data_b + erry_data_b*erry_data_b);

        // Error x and vectors
        vec_x[j] = hratio->GetBinCenter(j);
        vec_y[j] = hratio->GetBinContent(j);   
        errx_do[j] = 0.5*hratio->GetBinWidth(j);
        errx_up[j] = errx_do[j];

        errtot_up[j] = erry_ratio_data_up;
        errtot_do[j] = erry_ratio_data_do;

        int lower_limit =1;
        if(label.Contains("Rg")) lower_limit=2;
        
        if(j>=lower_limit){
          // Error x and vectors

          if(hnom->GetBinContent(j)!=0){
            Double_t in_x,in_y;
            h_theory_Elastic_noWake->GetPoint(j-lower_limit,in_x,in_y);
            // std::cout<<" j = "<<j<<"\t in_x = "<<in_x<<"\t BinCenter = "<<hnom->GetBinCenter(j)<<"\n";

            hybrid_vec_y[j] = in_y/hnom->GetBinContent(j);
            hybrid_errtot_up[j] = h_theory_Elastic_noWake->GetErrorYhigh(j-lower_limit)/hnom->GetBinContent(j);
            hybrid_errtot_do[j] = hybrid_errtot_up[j];
          }

        }

    }
    // std::cout<<"End Ratio Loop\n";
    auto hratio_tot = new TGraphAsymmErrors(hratio->GetNbinsX()+2,vec_x,vec_y,errx_up,errx_do,errtot_up,errtot_do);
    auto hratio_hybrid = new TGraphAsymmErrors(hratio->GetNbinsX()+2,vec_x,hybrid_vec_y,errx_up,errx_do,hybrid_errtot_up,hybrid_errtot_do);

    // Histogram Colors

        float transparency = 0.45;

        hnom->SetLineColor(kBlack);
        hnom->SetMarkerColor(kBlack);
        hnom->SetMarkerStyle(kFullCircle);
        hnom->SetMarkerSize(2.0);
        // hnom->SetErrorX(0);

        hratio->SetLineColor(kBlack);
        hratio->SetMarkerColor(kBlack);
        hratio->SetMarkerStyle(kFullCircle);
        hratio->SetMarkerSize(2.0);

        hpp_tot->SetFillStyle(1000); // Grey Box //1001 for solid 
        hpp_tot->SetFillColorAlpha(kGray+2,transparency);
        hpp_tot->SetLineColor(kGray+2); 
        hpp_tot->SetMarkerColor(kBlack);
        hpp_tot->SetMarkerStyle(kFullCircle);
        // hpp_tot->SetMarkerSize(0.2);

        hratio_tot->SetFillStyle(1000); // Grey Box //1001 for solid 
        hratio_tot->SetFillColorAlpha(kGray+2,transparency);
        hratio_tot->SetLineColor(kGray+2); 
        hratio_tot->SetMarkerColor(kBlack);
        hratio_tot->SetMarkerStyle(kFullCircle);
        // hpp_tot->SetMarkerSize(0.2);

        if(flag_add_theory){
          // transparency = 1.0;
          // std::cout<<"HatchesLineWidth = "<<gStyle->GetHatchesLineWidth()<<"\n";
          // std::cout<<"HatchesSpacing = "<<gStyle->GetHatchesSpacing()<<"\n";
            gStyle->SetHatchesLineWidth(1);
            gStyle->SetHatchesSpacing(1);
            // h_theory_Elastic_noWake->SetFillStyle(3345);
            // // h_theory_Elastic_noWake->SetLineWidth(1002);
            // // h_theory_Elastic_noWake->SetLineStyle(9);
            // h_theory_Elastic_noWake->SetLineStyle(1);
            // h_theory_Elastic_noWake->SetLineColor(kOrange-3);
            // h_theory_Elastic_noWake->SetFillColorAlpha(kOrange-3,transparency);

            // h_theory_Elastic_Wake->SetFillStyle(3354);
            // h_theory_Elastic_Wake->SetLineStyle(1);
            // h_theory_Elastic_Wake->SetLineColor(kAzure-3);
            // h_theory_Elastic_Wake->SetFillColorAlpha(kAzure-3,transparency);
            
            // h_theory_noElastic_noWake->SetFillStyle(3345);
            // // h_theory_Elastic_noWake->SetFillStyle(1002);
            // h_theory_noElastic_noWake->SetLineStyle(1);
            // h_theory_noElastic_noWake->SetLineColor(kMagenta+2);
            // h_theory_noElastic_noWake->SetFillColorAlpha(kMagenta+2,transparency);
            
            // h_theory_noElastic_Wake->SetFillStyle(3354);
            // h_theory_noElastic_Wake->SetLineStyle(1);
            // h_theory_noElastic_Wake->SetLineColor(kGreen+2);
            // h_theory_noElastic_Wake->SetFillColorAlpha(kGreen+2,transparency);

            h_theory_Elastic_noWake->SetMarkerSize(2.0);
            h_theory_Elastic_noWake->SetMarkerColorAlpha(kAzure,0.9);
            h_theory_Elastic_noWake->SetMarkerStyle(kFullCrossX);
            h_theory_Elastic_noWake->SetFillStyle(1001);
            h_theory_Elastic_noWake->SetFillColorAlpha(kAzure-3,transparency);
            
            h_theory_Elastic_noWake->SetLineColor(kAzure-3);

            hratio_hybrid->SetMarkerSize(2.0);
            hratio_hybrid->SetMarkerColorAlpha(kAzure,0.9);
            hratio_hybrid->SetMarkerStyle(kFullCrossX);
            hratio_hybrid->SetFillStyle(1001);
            hratio_hybrid->SetFillColorAlpha(kAzure-3,transparency);
            
            hratio_hybrid->SetLineColor(kAzure-3);
        }

    std::vector<TH1D*> hist_input;
    std::vector<TString> histname_input;

    hist_input.push_back((TH1D*)hnom->Clone());
    histname_input.push_back("pp Data");

    std::vector<TH1D*> ratio_input;
    std::vector<TString> rationame_input;

    // std::cout<<"Before reading Files\n";

    for(int i=0;i<file_list.size();i++){
        TFile *f = TFile::Open(file_list[i]);
        TH1D* htemp = (TH1D*)f->Get(Form("%s",hname.Data()));
        target->cd();
        TH1D *htemp_ratio = (TH1D*)htemp->Clone(label_list[i]);
        // htemp->Write(label_list.back()+"_"+label_list[i],TObject::kWriteDelete);
        if(htemp->GetNbinsX()!=(hnom->GetNbinsX()-1)){  // MC prediction is already normalized and doesn't have overflow bin
            htemp->Scale(1.0/htemp->Integral(0,htemp->GetNbinsX()+2),"width");
            htemp_ratio->Scale(1.0/htemp_ratio->Integral(0,htemp_ratio->GetNbinsX()+2),"width");
        }

        for(int ibin=0; ibin<=htemp_ratio->GetNbinsX()+1; ibin++){
            if(hnom->GetBinContent(ibin)!=0){
                htemp_ratio->SetBinContent(ibin,htemp->GetBinContent(ibin)/hnom->GetBinContent(ibin));
                htemp_ratio->SetBinError(ibin,htemp->GetBinError(ibin)/hnom->GetBinContent(ibin));
            }
        }

        htemp->SetLineColorAlpha(colarray[i],0.9);
        htemp->SetLineStyle(linearray[i]);
        htemp->SetLineWidth(5);
        htemp->SetMarkerColor(colarray[i]);
        htemp->SetMarkerStyle(markarray[i]);
        // htemp->SetMarkerSize(2.0);
        htemp->SetMarkerSize(0.0);

        htemp_ratio->SetLineColorAlpha(colarray[i],0.9);
        htemp_ratio->SetLineStyle(linearray[i]);
        htemp_ratio->SetLineWidth(5);
        htemp_ratio->SetMarkerColor(colarray[i]);
        htemp_ratio->SetMarkerStyle(markarray[i]);
        // htemp_ratio->SetMarkerSize(2.0);
        htemp_ratio->SetMarkerSize(0.0);


        hist_input.push_back((TH1D*)htemp->Clone());
        // hist_input.push_back((TH1D*)hnom->Clone(label_list[i]));
        histname_input.push_back(label_list[i]);

        ratio_input.push_back((TH1D*)htemp_ratio->Clone());
        // hist_input.push_back((TH1D*)hnom->Clone(label_list[i]));
        rationame_input.push_back(label_list[i]);

        std::cout<<"Got "<<label_list[i]<<std::endl;
    }

    // c.SetCanvasSize(700,820);
    // c.SetWindowSize(750,910);

// Defining canvas parameters with TDR style
    int W = 800;// 600; // 700;
    int H = 900;// 800; // 850;

    int W_ref = 800;// 600;// 700; 
    int H_ref = 900;// 800;// 850; 

    // references for T, B, L, R
    float T = 0.12*H_ref; //0.08*H_ref;
    float B = 0.162*H_ref;  //0.12*H_ref; 
    float L = 0.15*W_ref;  //0.12*W_ref;
    float R = 0.035*W_ref;

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

    float lower_pad_limit = 0.4;
    // float upper_pad_limit = 1-lower_pad_limit;

    // float lower_pad_area = W_ref*pad1->GetWNDC()*H_ref->GetWh()*pad1->GetHNDC();
    // float upper_pad_area = W_ref*pad2->GetWNDC()*H_ref->GetWh()*pad2->GetHNDC();

    float lower_pad_area = W_ref*1.0*H_ref*lower_pad_limit;
    float upper_pad_area = W_ref*1.0*H_ref*(1-lower_pad_limit);

    float upper_pad_ratio = 2*upper_pad_area/(upper_pad_area+lower_pad_area);
    float lower_pad_ratio = 2*lower_pad_area/(upper_pad_area+lower_pad_area);

    // Upper plot will be in pad1
    canv->cd();
        TPad *pad1 = new TPad("pad1", "pad1", 0, lower_pad_limit, 1, 1.0);
        pad1->SetLeftMargin(  (L/W) );
        pad1->SetRightMargin( (R/W) );
        pad1->SetTopMargin(   (T/H)/upper_pad_ratio );
        // pad1->SetBottomMargin( B/H );

        // pad1->SetTopMargin(T);
        // pad1->SetRightMargin(0.05); 
        // pad1->SetLeftMargin(0.15); 
        pad1->SetBottomMargin(0.02);
        pad1->Draw();             // Draw the upper pad: pad1
        pad1->cd();               // pad1 becomes the current pad
        
        // hPbPb_stat->Draw("AP5");
        
        hpp_tot->Draw("AP5");
        if(flag_add_theory){
            h_theory_Elastic_noWake->Draw("SAME_P5");
            // h_theory_Elastic_Wake->Draw("SAME_P5");
            // h_theory_noElastic_noWake->Draw("SAME_P5");
            // h_theory_noElastic_Wake->Draw("SAME_P5");
        }

        
        float leg_x1;
        float leg_y1;
        float leg_x2;
        float leg_y2;

        // leg_x1 = 0.2;
        // leg_y1 = 0.58;
        // leg_x2 = 0.5;
        // leg_y2 = 0.85;
        // TLegend *l_ratio_1 = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
        // l_ratio_1->SetFillStyle(0);
        // l_ratio_1->SetFillColor(0);
        // l_ratio_1->SetLineColor(0);
        // l_ratio_1->SetTextSize(0.12*lower_pad_ratio);
        // l_ratio_1->SetTextFont(42);

        // l_ratio_1->AddEntry(hratio, "Ratio", "lep");
        // l_ratio_1->AddEntry(h_theory_Elastic_noWake,   "Hybrid Elastic, no Wake ", "f");
        // l_ratio_1->AddEntry(h_theory_Elastic_Wake,     "Hybrid Elastic,    Wake ", "f");
        // l_ratio_1->AddEntry(h_theory_noElastic_noWake, "Hybrid, no Wake ", "f");
        // l_ratio_1->AddEntry(h_theory_noElastic_Wake,   "Hybrid no Elastic,    Wake ", "f");

        // leg_x1 = 0.65;
        // leg_y1 = 0.45;
        // leg_x2 = 0.85;
        // leg_y2 = 0.85;

        leg_x1 = 0.55;
        leg_y1 = 0.45;
        leg_x2 = 0.8;
        leg_y2 = 0.85;

        l = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2,"","brNDC");
        l->SetFillStyle(0);
        l->SetFillColor(0);
        l->SetLineColor(0);
        l->SetBorderSize(0);
        // l->SetTextSize(0.047);
        // l->SetTextFont(42);


        l->SetTextSize(26);
        l->SetTextFont(43);

        l->AddEntry(hpp_tot,"Data","lepf");
        if(flag_add_theory){
          l->AddEntry(h_theory_Elastic_noWake, "Hybrid", "pf");
        //   l->AddEntry(h_theory_Elastic_Wake, "Hybrid", "pf");
        }

        for(int i=1;i<file_list.size()+1;i++){

            // if(i>0){
                hist_input[i]->Draw("SAME_E1_]["); // P
                l->AddEntry(hist_input[i],histname_input[i],"l");
            // }
            // else{
                // hist_input[i]->Draw("SAME_E1X0_][P");
            // }
        }
        hist_input[0]->Draw("SAME_E1X0_][P");

        // hpp_tot->SetMaximum(ymax);
        // hpp_tot->GetXaxis()->SetLabelSize(0);
        // hpp_tot->GetXaxis()->SetTitleOffset(999999);

        float line_left_edge = hratio->GetXaxis()->GetBinLowEdge(1);
        if(label.Contains("Rg")){
            line_left_edge = hratio->GetXaxis()->GetBinLowEdge(2);
        }
        // hpp_tot->GetXaxis()->SetRangeUser(line_left_edge,hratio->GetXaxis()->GetBinUpEdge(hratio->GetNbinsX()-1));
        hpp_tot->GetXaxis()->SetLimits(line_left_edge,hratio->GetXaxis()->GetBinUpEdge(hratio->GetNbinsX()-1));
          
        l->Draw();

        // TLatex latex;
        // latex.SetTextSize(0.12*lower_pad_ratio);
        // latex.DrawLatexNDC(0.15,0.92,"CMS #it{#bf{Preliminary}}");
        // latex.DrawLatexNDC(0.62,0.92,"#bf{pp 300.6 pb^{-1} (5.02 TeV)}");
        // latex.SetTextSize(0.12*lower_pad_ratio);
        // // leg_y1-=0.06;
        // // latex.DrawLatexNDC(leg_x1,leg_y1,"Cent. 0-30%");
        // leg_y1-=0.06;
        // latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma }>100 GeV,x_{J}>0.4,|#Delta #phi_{#gamma,jet}|>#frac{2}{3}#pi");
        // leg_x1=0.2;
        // leg_y1=0.85;
        // if(label.Contains("Rg")){
        //     // leg_y1-=0.08;
        //     // latex.DrawLatexNDC(leg_x1,leg_y1,Form("PbPb untagged = %4.2f%%",PbPb_untagged*100));
        //     // latex.DrawLatexNDC(leg_x1,leg_y1,Form("MatInvert untagged = %4.2f%%",PbPb_untagged*100));
        //     // leg_y1-=0.08;
        //     // latex.DrawLatexNDC(leg_x1,leg_y1,Form("pp untagged = %4.2f%%",pp_untagged*100));
        //     // latex.DrawLatexNDC(leg_x1,leg_y1,Form("D'Agostini untagged = %4.2f%%",pp_untagged*100));
        // }
        // pad1->RedrawAxis();
    // lower plot will be in pad
    canv->cd();          // Go back to the main canvas before defining pad2
        TPad *pad2 = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, lower_pad_limit);
        pad2->SetLeftMargin(   (L/W) );
        pad2->SetRightMargin(  (R/W) );
        pad2->SetBottomMargin( (B/H)/lower_pad_ratio );
        // pad1->SetTopMargin( T/H );

        pad2->SetTopMargin(0.02); // 0.025
        // pad2->SetRightMargin(0.05); 
        // pad2->SetLeftMargin(0.15); 
        // pad2->SetBottomMargin(0.4*upper_pad_ratio); 
        // pad2->SetGrid();
        pad2->Draw();
        pad2->cd();       // pad2 becomes the current pad

        hratio_tot->Draw("AP5");
        
        if(flag_add_theory){
          hratio_hybrid->Draw("SAME_P5");
        }

        for(int i=0;i<file_list.size();i++){
            ratio_input[i]->Draw("SAME_E1_]["); // P
        }    

        hratio->Draw("SAME_E1X0_][P");

        //! Already set in upper pad
        // float line_left_edge = hratio->GetXaxis()->GetBinLowEdge(1);
        // if(label.Contains("Rg")){
        //     line_left_edge = hratio->GetXaxis()->GetBinLowEdge(2);
        // }
        // hratio_tot->GetXaxis()->SetRangeUser(line_left_edge,hratio->GetXaxis()->GetBinUpEdge(hratio->GetNbinsX()-1));
        hratio_tot->GetXaxis()->SetLimits(line_left_edge,hratio->GetXaxis()->GetBinUpEdge(hratio->GetNbinsX()-1));
        // hratio_hybrid->GetXaxis()->SetLimits(line_left_edge,hratio->GetXaxis()->GetBinUpEdge(hratio->GetNbinsX()-1));

        TLine *line=new TLine(line_left_edge,1.0,hratio->GetXaxis()->GetBinLowEdge(hratio->GetNbinsX()),1.0);
        line->SetLineColor(kBlack);
        line->SetLineStyle(1);
        line->SetLineWidth(2);
        line->Draw("SAME");

        if(label.Contains("Rg") && label.Contains("xJ_gp8")){
          hratio_tot->GetHistogram()->SetMinimum(0.2);
          hratio_tot->GetHistogram()->SetMaximum(1.3999);
        }
        else if(label.Contains("Rg") && label.Contains("xJ_gp4")){
          hratio_tot->GetHistogram()->SetMinimum(0.4);
          hratio_tot->GetHistogram()->SetMaximum(1.29999);
        }
        else if(label.Contains("girth") && label.Contains("xJ_gp8")){
          hratio_tot->GetHistogram()->SetMinimum(0.3);
          hratio_tot->GetHistogram()->SetMaximum(1.79999);
        }
        else if(label.Contains("girth") && label.Contains("xJ_gp4")){
          hratio_tot->GetHistogram()->SetMinimum(0.1);
          hratio_tot->GetHistogram()->SetMaximum(1.59999);
        }
        else{
          hratio_tot->GetHistogram()->SetMinimum(0.);
          hratio_tot->GetHistogram()->SetMaximum(1.99999);
        }
        // pad2->RedrawAxis();

    // Axis settings
        canv->cd();

        // X axis upper plot settings
            hpp_tot->GetXaxis()->SetLabelSize(0);
            hpp_tot->GetXaxis()->SetTitleSize(0);
            if(label.Contains("Rg")){
              hpp_tot->GetXaxis()->SetNdivisions(4,5,0,kTRUE);
            }
            else if(label.Contains("girth")){
              hpp_tot->GetXaxis()->SetNdivisions(5,5,0,kTRUE);
            }

        // Y axis upper plot settings
            // hpp_tot->GetYaxis()->SetTitleFont(42);
            // hpp_tot->GetYaxis()->SetTitleSize(0.07/upper_pad_ratio);
            // hpp_tot->GetYaxis()->SetTitleOffset(1.25);
            // hpp_tot->GetYaxis()->SetLabelFont(42);
            // hpp_tot->GetYaxis()->SetLabelSize(0.06/upper_pad_ratio);
            // hpp_tot->GetYaxis()->SetLabelOffset(0.007/upper_pad_ratio);
            // hpp_tot->GetYaxis()->SetTickLength(0.03/upper_pad_ratio);

            hpp_tot->GetYaxis()->SetTitleFont(43);
            hpp_tot->GetYaxis()->SetTitleSize(30);
            hpp_tot->GetYaxis()->SetTitleOffset(1.8);
            hpp_tot->GetYaxis()->SetLabelFont(43);
            hpp_tot->GetYaxis()->SetLabelSize(28);
            // hpp_tot->GetYaxis()->SetLabelOffset(0.007/upper_pad_ratio);
            // hpp_tot->GetYaxis()->SetTickLength(0.03);

        // Y axis ratio plot settings
            hratio_tot->GetYaxis()->SetTitle("#frac{Pred.}{Data}          ");
            // hratio_tot->GetYaxis()->SetNdivisions(-4);
            // hratio_tot->GetYaxis()->SetTitleFont(42);
            // hratio_tot->GetYaxis()->SetTitleSize(0.07/lower_pad_ratio);
            // hratio_tot->GetYaxis()->SetTitleOffset(0.85);
            // hratio_tot->GetYaxis()->SetLabelFont(42); // Absolute font size in pixel (precision 3)
            // hratio_tot->GetYaxis()->SetLabelSize(0.06/lower_pad_ratio);
            // hratio_tot->GetYaxis()->SetLabelOffset(0.007/lower_pad_ratio);
            // hratio_tot->GetYaxis()->SetTickLength(0.03/lower_pad_ratio);

            hratio_tot->GetYaxis()->SetTitleFont(43);
            hratio_tot->GetYaxis()->SetTitleSize(30);
            hratio_tot->GetYaxis()->SetTitleOffset(1.8);
            hratio_tot->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
            hratio_tot->GetYaxis()->SetLabelSize(28);
            // hratio_tot->GetYaxis()->SetLabelOffset(0.007/lower_pad_ratio);
            // hratio_tot->GetYaxis()->SetTickLength(0.03);
            
        // X axis ratio plot settings
            // hratio_tot->GetXaxis()->SetTitleFont(42);
            // hratio_tot->GetXaxis()->SetTitleSize(0.07/lower_pad_ratio);
            // hratio_tot->GetXaxis()->SetTitleOffset(1.0);
            // hratio_tot->GetXaxis()->SetLabelFont(42); // Absolute font size in pixel (precision 3)
            // hratio_tot->GetXaxis()->SetLabelSize(0.06/lower_pad_ratio);
            // hratio_tot->GetXaxis()->SetLabelOffset(0.007/lower_pad_ratio);
            // hratio_tot->GetXaxis()->SetTickLength(0.03/lower_pad_ratio);
            hratio_tot->GetXaxis()->SetNdivisions(hpp_tot->GetXaxis()->GetNdivisions());

            hratio_tot->GetXaxis()->SetTitleFont(43);
            hratio_tot->GetXaxis()->SetTitleSize(30);
            hratio_tot->GetXaxis()->SetTitleOffset(2.5);
            hratio_tot->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
            hratio_tot->GetXaxis()->SetLabelSize(28);
            // hratio_tot->GetXaxis()->SetLabelOffset(0.007/lower_pad_ratio);
            // hratio_tot->GetXaxis()->SetTickLength(0.03);
        
        if(label.Contains("Rg") && label.Contains("xJ_gp8")){
            hratio_tot->GetXaxis()->SetTitle("Groomed jet radius R_{g}");
            hpp_tot->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{dR_{g}}    ");
            hpp_tot->GetHistogram()->SetMinimum(0.0);
            hpp_tot->GetHistogram()->SetMaximum(29.0);
        }
        else if(label.Contains("Rg") && label.Contains("xJ_gp4")){
            hratio_tot->GetXaxis()->SetTitle("Groomed jet radius R_{g}");
            hpp_tot->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{dR_{g}}    ");
            hpp_tot->GetHistogram()->SetMinimum(0.0);
            hpp_tot->GetHistogram()->SetMaximum(22.0);
        }
        else if(label.Contains("girth") && label.Contains("xJ_gp8")){
            hratio_tot->GetXaxis()->SetTitle("Jet girth #it{g}");
            hpp_tot->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{d#it{g}}   ");
            hpp_tot->GetHistogram()->SetMinimum(0.0);
            hpp_tot->GetHistogram()->SetMaximum(47.0);
        }
        else if(label.Contains("girth") && label.Contains("xJ_gp4")){
            hratio_tot->GetXaxis()->SetTitle("Jet girth #it{g}");
            hpp_tot->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN}{d#it{g}}   ");
            hpp_tot->GetHistogram()->SetMinimum(0.0);
            hpp_tot->GetHistogram()->SetMaximum(47.0);
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
    // latex.SetTextSize(0.047);    
    latex.SetTextAlign(12); 

    latex.SetTextFont(43);
    latex.SetTextSize(26);  

    if(label.Contains("Rg") && label.Contains("xJ_gp8")){
    //   std::cout<<"\n Inside Rg and xJ_gp8 \n";
      leg_x1 = 0.55;
      leg_y1 = 0.45;
      leg_x2 = 0.8;
      leg_y2 = 0.85;

      leg_y1-=0.12;
      leg_x1 = 0.55;
      latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");
    
      leg_x1 = 0.19;
      leg_y1 = 0.78;
      // leg_y1-=0.12;
      // latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
      // leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV, #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.8");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44, |#eta_{jet}| < 2");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
    }
    else if(label.Contains("Rg") && label.Contains("xJ_gp4")){
    //   std::cout<<"\n Inside Rg and xJ_gp4 \n";
      leg_x1 = 0.55;
      leg_y1 = 0.45;
      leg_x2 = 0.8;
      leg_y2 = 0.85;

      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");
    
      leg_x1 = 0.19;
      leg_y1 = 0.78;
      // leg_y1-=0.12;
      // latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
      // leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV, #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.4");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44, |#eta_{jet}| < 2");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp8")){
    //   std::cout<<"\n Inside girth and xJ_gp8 \t Label : "<<label<<"\n";
      leg_x1 = 0.55;
      leg_y1 = 0.45;
      leg_x2 = 0.8;
      leg_y2 = 0.85;

      // leg_y1-=0.12;
      // latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");
    
      leg_x1 = 0.19;
      leg_y1 = 0.78;
      // leg_y1-=0.12;
      // latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
      // leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV, #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.8");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44, |#eta_{jet}| < 2");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
    }
    else if(label.Contains("girth") && label.Contains("xJ_gp4")){
    //   std::cout<<"\n Inside girth and xJ_gp4 \t Label : "<<label<<"\n";
      leg_x1 = 0.55;
      leg_y1 = 0.45;
      leg_x2 = 0.8;
      leg_y2 = 0.85;

      // leg_y1-=0.12;
      // latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");
    
      leg_x1 = 0.19;
      leg_y1 = 0.78;
      // leg_y1-=0.12;
      // latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
      // leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV, #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.4");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44, |#eta_{jet}| < 2");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
    }
    else{
      std::cout<<"\n Inside Default \n";
      leg_x1 = 0.6;
      leg_y1 = 0.72;
      leg_x2 = 0.8;
      leg_y2 = 0.87;

      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"p_{T}^{#gamma} > 100 GeV, #frac{p_{T}^{jet}}{p_{T}^{#gamma}} > 0.4");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"|#eta_{#gamma}| < 1.44, |#eta_{jet}| < 2");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"#Delta#varphi_{#gamma,jet} > #frac{2}{3}#pi");
      
      leg_x1 = 0.19;
      leg_y1 = 0.72;
      // leg_y1-=0.12;
      // latex.DrawLatexNDC(leg_x1,leg_y1,"Centrality: 0-30%");
      leg_y1-=0.12;
      latex.DrawLatexNDC(leg_x1,leg_y1,"Soft drop z_{cut} = 0.2, #beta = 0");
    }

    canv->Update();
    fixOverlay();
    // canv->RedrawAxis();
    canv->Draw();
    // canv->GetFrame()->Draw();

    canv->Print(output_path+"/"+label+".pdf",".pdf");
    // canv->Print(output_path+"/"+label+".png",".png");
    canv->Write(label,TObject::kOverwrite);

    return canv;

}



void overlay_Data_MC(){
    
    gROOT->SetBatch();

    TString input_MC_path = "OverlayData/Theory_graph/";
    std::vector<TString> MC_case = 
    {
      "Output_pp_QCDPhoton_jets","Output_pp_Herwig7_jets","herwig7dipole_gammaJet","pythia8_dire","pythia8_vincia"
    };
    std::vector<TString> MC_case_label = 
    {
        "PYTHIA8 CP5","HERWIG7 CH3","HERWIG7 dipole","PYTHIA8+DIRE","PYTHIA8+VINCIA"
    };

    std::vector<TString> plot_cases = {
        "Rg_xJ_gp4",
        "girth_xJ_gp4",
        "Rg_xJ_gp8",
        "girth_xJ_gp8"
        };

    std::vector<TString>MC_list;
    std::vector<TString>label_list;
    
    // TString out_label="";
    // TString varname="Rg";

    for(auto var:plot_cases){
        TString file_PbPb = "Uncertainty/OutputCombined_2024_Apr_HEPDATA/Data_0_30_2024_Apr_PbPb_2018_sys_";
        TString label_PbPb = "Data_0_30_2024_Apr_PbPb_2018_sys_"; // xJ_gp8_Data_Rg_unfold_X 
        TString file_pp = "~/pp_analysis/Analysis/Uncertainty/OutputCombined_2024_Apr_HEPDATA/pp_Data_2024_Apr_pp_2017_sys_";
        TString label_pp="pp_Data_2024_Apr_pp_2017_sys_"; 
        TString MC_end = "";
        TString hname = "";
        
        if(var.Contains("xJ_gp4")){
            file_PbPb+="xJ_gp4_HEPDATA_Data_";
            label_PbPb+="xJ_gp4_HEPDATA_Data_";
            file_pp+="xJ_gp4_HEPDATA_Data_";
            label_pp+="xJ_gp4_HEPDATA_Data_";
        }
        else{
            file_PbPb+="xJ_gp8_HEPDATA_Data_";
            label_PbPb+="xJ_gp8_HEPDATA_Data_";
            file_pp+="xJ_gp8_HEPDATA_Data_";
            label_pp+="xJ_gp8_HEPDATA_Data_";
            MC_end+="_xJ8";
        }

        if(var.Contains("Rg")){
            file_PbPb+="Rg_unfold_X.root";
            label_PbPb+="Rg_unfold_X";
            file_pp+="Rg_unfold_X.root";
            label_pp+="Rg_unfold_X";
            hname = "h_Rg_truef_0";
        }
        else{
            file_PbPb+="girth_unfold_X.root";
            label_PbPb+="girth_unfold_X";
            file_pp+="girth_unfold_X.root";
            label_pp+="girth_unfold_X";
            hname = "h_angu_truef_0";
        }    
        MC_list.clear();
        label_list.clear();
        for(int i=0;i<MC_case.size();i++){
            MC_list.push_back(input_MC_path+MC_case[i]+MC_end+".root");
            label_list.push_back(MC_case_label[i]);
        }

        // std::cout<<file_PbPb<<"\n";
        std::cout<<"\n";

        TCanvas *c_temp = overlay_pp_MC(file_pp,label_pp,MC_list,label_list,hname,"pp_2024_Apr_Plot_Apr_16_"+var+"_HEPDATA",var);
        // delete c_temp;
        std::cout<<"pp_2024_Apr_Plot_Apr_16_"+var+"_HEPDATA has been saved\n";
        std::cout<<"\n-------------------------------------------\n";
        // break;
    }        
    
}