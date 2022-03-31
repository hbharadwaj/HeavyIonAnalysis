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

#include <iostream>         // needed for I/O

const std::vector<int> min_cent = {0,   60,   0,  0,  40, 100};
const std::vector<int> max_cent = {60, 180, 180, 40, 100, 180};
const std::size_t ncent = min_cent.size();
TString label="";
TString input_path = "";

void Plot_hist(std::vector<TH1F*>,std::vector<TString> ,TString opt="label",std::vector<TString> eopt={"end"});

void Plot_hist2D(std::vector<TH2F*> hist,std::vector<TString> histname,TString dopt="colz",std::vector<TString> eopt={"end"});

void plot_jet(){
    gROOT->SetBatch();
    gErrorIgnoreLevel = kFatal;
    TString DIR = input_path + "/OutputPlots_"+label+"/";
    TString makedir = "mkdir -p " + DIR;
    const char *mkDIR = makedir.Data();
    gSystem->Exec(mkDIR);

    // ----------------------------------------------------------------------------------------------------------------
    //Tree Variable Declaration

        TChain jet_tree("jet_tree");
        jet_tree.Add(input_path+label+".root/jet_tree");

        Float_t phoSCRawE = 0;
        Float_t phoSCEta = 0;
        Float_t phoSCPhi = 0;
        Float_t phoSigmaIEtaIEta_2012 = 0;
        Float_t rho = 0;

        Float_t phoEt = 0;
        Float_t phoEtCorrected = 0;
        Float_t phoEta = 0;
        Float_t phoPhi = 0;
        Float_t phoHoverE = 0;
        Float_t pho_ecalClusterIsoR3 = 0;
        Float_t pho_hcalRechitIsoR3 = 0;
        Float_t pho_trackIsoR3PtCut20 = 0;
        Float_t pho_ecalClusterIsoR4 = 0;
        Float_t pho_hcalRechitIsoR4 = 0;
        Float_t pho_trackIsoR4PtCut20 = 0;
        Float_t phoSigmaEtaEta_2012 = 0;

        Float_t pfcIso3subUE = 0;
        Float_t pfnIso3subUE = 0;
        Float_t pfpIso3subUE = 0;
        Float_t SumPFIso = 0;
        Float_t SumCalIso = 0;

        Bool_t  eleRej = 0;

        Int_t   hiBin = 0;
        Int_t   L1_SingleEG21_BptxAND = 0;
        Int_t   HLT_HIGEDPhoton40_v1 = 0;

        jet_tree.SetBranchAddress("phoSCRawE",&phoSCRawE);
        jet_tree.SetBranchAddress("phoSCEta",&phoSCEta);
        jet_tree.SetBranchAddress("phoSCPhi",&phoSCPhi);
        jet_tree.SetBranchAddress("phoSigmaIEtaIEta_2012",&phoSigmaIEtaIEta_2012);
        jet_tree.SetBranchAddress("rho",&rho);

        jet_tree.SetBranchAddress("phoEt",&phoEt);
        jet_tree.SetBranchAddress("phoEtCorrected",&phoEtCorrected);
        jet_tree.SetBranchAddress("phoEta",&phoEta);
        jet_tree.SetBranchAddress("phoPhi",&phoPhi);
        jet_tree.SetBranchAddress("phoHoverE",&phoHoverE);
        jet_tree.SetBranchAddress("pho_ecalClusterIsoR3",&pho_ecalClusterIsoR3);
        jet_tree.SetBranchAddress("pho_hcalRechitIsoR3",&pho_hcalRechitIsoR3);
        jet_tree.SetBranchAddress("pho_trackIsoR3PtCut20",&pho_trackIsoR3PtCut20);
        jet_tree.SetBranchAddress("pho_ecalClusterIsoR4",&pho_ecalClusterIsoR4);
        jet_tree.SetBranchAddress("pho_hcalRechitIsoR4",&pho_hcalRechitIsoR4);
        jet_tree.SetBranchAddress("pho_trackIsoR4PtCut20",&pho_trackIsoR4PtCut20);
        jet_tree.SetBranchAddress("phoSigmaEtaEta_2012",&phoSigmaEtaEta_2012);

        jet_tree.SetBranchAddress("pfcIso3subUE",&pfcIso3subUE);
        jet_tree.SetBranchAddress("pfnIso3subUE",&pfnIso3subUE);
        jet_tree.SetBranchAddress("pfpIso3subUE",&pfpIso3subUE);
        jet_tree.SetBranchAddress("SumPFIso",&SumPFIso);
        jet_tree.SetBranchAddress("SumCalIso",&SumCalIso);
        jet_tree.SetBranchAddress("hiBin",&hiBin);

        jet_tree.SetBranchAddress("eleRej",&eleRej);

        jet_tree.SetBranchAddress("L1_SingleEG21_BptxAND",&L1_SingleEG21_BptxAND);
        jet_tree.SetBranchAddress("HLT_HIGEDPhoton40_v1",&HLT_HIGEDPhoton40_v1);

        Int_t nref = 0;
        Int_t jet_index = -1;
        Float_t jtpt[500]={-1};
        Float_t jteta[500]={-1};
        Float_t jtphi[500]={-1};
        Float_t jtsym[500]={-1};
        Float_t jtrg[500]={-1};
        Float_t jtdynkt[500]={-1};
        Float_t jtangu[500]={-1};

        jet_tree.SetBranchAddress("nref", &nref);
        jet_tree.SetBranchAddress("jet_index", &jet_index);
        jet_tree.SetBranchAddress("jtpt", &jtpt);
        jet_tree.SetBranchAddress("jteta", &jteta);
        jet_tree.SetBranchAddress("jtphi", &jtphi);
        jet_tree.SetBranchAddress("jtsym", &jtsym);
        jet_tree.SetBranchAddress("jtrg", &jtrg);
        jet_tree.SetBranchAddress("jtdynkt", &jtdynkt);
        jet_tree.SetBranchAddress("jtangu", &jtangu);

    // -------- End Tree Variable Declaration
    // ----------------------------------------------------------------------------------------------------------------
    // Histograms
        TH1F* hnPho[ncent];
        TH1F* hnPhosel[ncent];
        TH1F* hnJet[ncent];
        
        TH1F* hdphi_all[ncent];
        TH1F* hxJ_all[ncent];
        TH1F* hRg_all[ncent];
        TH1F* hangu_all[ncent];
        TH1F* hktdyn_all[ncent];

        TH1F* hdphi_lead[ncent];
        TH1F* hxJ_lead[ncent];
        TH1F* hRg_lead[ncent];
        TH1F* hangu_lead[ncent];
        TH1F* hktdyn_lead[ncent];

        TH2F* h_Rg_xJ[ncent];
        TH2F* h_angu_xJ[ncent];
        TH2F* h_ktdyn_xJ[ncent];
        // TH2F* h_lnktdyn_xJ[ncent]; ln kt for later?

        for (std::size_t i = 0; i < ncent; ++i) {
            hnPho[i] = new TH1F(Form("hnPho_%zu", i), Form("hnPho_%zu;nPho;Norm. Events", i), 1, 0, 1);
            hnPhosel[i] = new TH1F(Form("hnPhosel_%zu", i), Form("hnPhosel_%zu;nPho;Norm. Events", i), 1, 0, 1);
            hnJet[i] = new TH1F(Form("hnJet_%zu", i), Form("hnJet_%zu;nJet;Norm. Events", i), 1, 0, 1);

            int nbins = 80;

            hdphi_all[i] = new TH1F(Form("hdphi_all_%zu", i), Form("hdphi_all_%zu;#Delta #phi;Norm. Events", i), nbins, 0, 3.2);
            hxJ_all[i] = new TH1F(Form("hxJ_all_%zu", i), Form("hxJ_all_%zu;All Recoil Jet p_{T}/Photon E_{T};Norm. Events", i), nbins, 0, 2.0);
            hRg_all[i] = new TH1F(Form("hRg_all_%zu", i), Form("hRg_all_%zu;R_{g};Norm. Events", i), nbins, 0, 0.3);
            hangu_all[i] = new TH1F(Form("hangu_all_%zu", i), Form("hangu_all_%zu;Angularity;Norm. Events", i), nbins, 0, 0.12);
            hktdyn_all[i] = new TH1F(Form("hktdyn_all_%zu", i), Form("hktdyn_all_%zu;dyn k_{T};Norm. Events", i), nbins, 0, 20);

            hdphi_lead[i] = new TH1F(Form("hdphi_lead_%zu", i), Form("hdphi_lead_%zu;#Delta #phi;Norm. Events", i), nbins, 0, 3.2);
            hxJ_lead[i] = new TH1F(Form("hxJ_lead_%zu", i), Form("hxJ_lead_%zu;Lead Recoil Jet p_{T}/Photon E_{T};Norm. Events", i), nbins, 0, 2.0);
            hRg_lead[i] = new TH1F(Form("hRg_lead_%zu", i), Form("hRg_lead_%zu;R_{g};Norm. Events", i), nbins, 0, 0.3);
            hangu_lead[i] = new TH1F(Form("hangu_lead_%zu", i), Form("hangu_lead_%zu;Angularity;Norm. Events", i), nbins, 0, 0.12);
            hktdyn_lead[i] = new TH1F(Form("hktdyn_lead_%zu", i), Form("hktdyn_lead_%zu;dyn k_{T};Norm. Events", i), nbins, 0, 20);

            h_Rg_xJ[i]=new TH2F("h_Rg_xJ","h_Rg_xJ;Rg;x_{#gamma,jet}",16,0,0.4,20,0,2.0);
            h_angu_xJ[i]=new TH2F("h_angu_xJ","h_angu_xJ;Angularity;x_{#gamma,jet}",16,0,0.16,20,0,2.0);
            h_ktdyn_xJ[i]=new TH2F("h_ktdyn_xJ","h_ktdyn_xJ;dyn k_{T};x_{#gamma,jet}",20,0,20,20,0,2.0);
        }

    // -------- End Histograms
    // ----------------------------------------------------------------------------------------------------------------
    // Event Loop

    const float min_pho_et = 100;
    const float cut_HoverE = 0.0696672;
    const float cut_SIEIE  = 0.00983515;
    const float cut_SumIso = 1.33546;

    Int_t nEv=jet_tree.GetEntries();
    for(int iEntry=0; iEntry<nEv; iEntry++){
        float scale =1;
        jet_tree.GetEntry(iEntry);
        for (std::size_t i = 0; i < ncent; ++i) {
            if(!(hiBin>min_cent[i] && hiBin<=max_cent[i])) continue;
            if(!(abs(phoSCEta)<1.44)) continue;
            if(!(phoEtCorrected>min_pho_et)) continue;
            if(!L1_SingleEG21_BptxAND) continue;    // TRIGGERS FULLY EFFICIENCT
            if(!HLT_HIGEDPhoton40_v1) continue;

            int flagHoverE=1;   
            int flagSigmaEtaEta=1;
            int flagIso=1;

            if(phoHoverE<=cut_HoverE) flagHoverE = 0;
            if(phoSigmaIEtaIEta_2012<=cut_SIEIE) flagSigmaEtaEta = 0;
            if(SumCalIso<=cut_SumIso) flagIso = 0;

            hnPho[i]->Fill(1);

            if(flagHoverE || flagSigmaEtaEta || flagIso || eleRej) continue;
            
            hnPhosel[i]->Fill(1);

            // -------- End Photon Selection
            // Jet Loop----------------------------------------------------------------------------------

            int jet_index=-1;
            float jet_pt_max=-1;
            float jet_dphi_max=-1;
            float jet_xJ_max=-1;

            for(int ijet=0; ijet<nref;ijet++){
                if(jtpt[ijet]<40) continue;
                if(abs(jteta[ijet])>2) continue;
                float dphi = abs(TVector2::Phi_mpi_pi(phoPhi-jtphi[ijet]));// ROOT::Math::VectorUtil::Phi_mpi_pi(phoPhi,jtphi[ijet]);
                float xJ = jtpt[ijet]/phoEtCorrected;
                hdphi_all[i]->Fill(dphi,scale);

                if(dphi>2*TMath::Pi()/3){
                    if(jet_pt_max<jtpt[ijet]){
                        jet_pt_max = jtpt[ijet];
                        jet_dphi_max = dphi;
                        jet_xJ_max = xJ;
                        jet_index = ijet;
                    }
                    hxJ_all[i]->Fill(xJ,scale);
                    hRg_all[i]->Fill(jtrg[ijet],scale);
                    hangu_all[i]->Fill(jtangu[ijet],scale);
                    hktdyn_all[i]->Fill(jtdynkt[ijet],scale);
                }
            }
            if(jet_index==-1) continue;
            hnJet[i]->Fill(1);

            hdphi_lead[i]->Fill(jet_dphi_max,scale);
            hxJ_lead[i]->Fill(jet_xJ_max,scale);
            hRg_lead[i]->Fill(jtrg[jet_index],scale);
            hangu_lead[i]->Fill(jtangu[jet_index],scale);
            hktdyn_lead[i]->Fill(jtdynkt[jet_index],scale);

            h_Rg_xJ[i]->Fill(jtrg[jet_index],jet_xJ_max,scale);
            h_angu_xJ[i]->Fill(jtangu[jet_index],jet_xJ_max,scale);
            h_ktdyn_xJ[i]->Fill(jtdynkt[jet_index],jet_xJ_max,scale);
        }
    }

    float S = hdphi_all[0]->Integral(hdphi_all[0]->FindBin(2*TMath::Pi()/3),hdphi_all[0]->GetNbinsX()+2);
    float S_B = hdphi_all[0]->Integral(hdphi_all[0]->FindBin(TMath::Pi()/3),hdphi_all[0]->FindBin(2*TMath::Pi()/3)-1);
    std::cout<<"S = "<<S<<"    |  S+B = "<<S_B<<std::endl;
    std::cout<<"S/S+B = "<<S/S_B<<std::endl;

    for (std::size_t i = 0; i < ncent; ++i) {
        std::cout<<"Number of Photons in "<<min_cent[i]/2<<" - "<<max_cent[i]/2<<" = "<<hnPho[i]->GetSum()<<std::endl;
        std::cout<<"Number of Selected Photons in "<<min_cent[i]/2<<" - "<<max_cent[i]/2<<" = "<<hnPhosel[i]->GetSum()<<std::endl;
        std::cout<<"Number of Leading Jets for Selected Photons in "<<min_cent[i]/2<<" - "<<max_cent[i]/2<<" = "<<hnJet[i]->GetSum()<<std::endl;
        if(i>2){
            hdphi_all[i]->Rebin(4);
            hxJ_all[i]->Rebin(4);
            hRg_all[i]->Rebin(4);
            hangu_all[i]->Rebin(4);
            hktdyn_all[i]->Rebin(4);
            hdphi_lead[i]->Rebin(4);
            hxJ_lead[i]->Rebin(4);
            hRg_lead[i]->Rebin(4);
            hangu_lead[i]->Rebin(4);
            hktdyn_lead[i]->Rebin(4);
        }
    }

    std::vector<TString>sel = {"#gamma_{pT}>100","|#eta|<1.44",Form("H/E<%6.4f",cut_HoverE),Form("#sigma_{#eta#eta}<%6.4f",cut_SIEIE),Form("SumIso<%6.4f",cut_SumIso)};    

    Plot_hist({hdphi_all[3],hdphi_all[4],hdphi_all[5]},{"Cent. 0-20%","Cent. 20-50%","Cent. 50-90%","dphi_all"},"leftlog",sel);
    Plot_hist({hxJ_all[3],hxJ_all[4],hxJ_all[5]},{"Cent. 0-20%","Cent. 20-50%","Cent. 50-90%","xJ_all"},"right",sel);
    Plot_hist({hRg_all[3],hRg_all[4],hRg_all[5]},{"Cent. 0-20%","Cent. 20-50%","Cent. 50-90%","Rg_all"},"right",sel);
    Plot_hist({hangu_all[3],hangu_all[4],hangu_all[5]},{"Cent. 0-20%","Cent. 20-50%","Cent. 50-90%","angu_all"},"right",sel);
    Plot_hist({hktdyn_all[3],hktdyn_all[4],hktdyn_all[5]},{"Cent. 0-20%","Cent. 20-50%","Cent. 50-90%","ktdyn_all"},"rightlog",sel);

    Plot_hist({hdphi_lead[3],hdphi_lead[4],hdphi_lead[5]},{"Cent. 0-20%","Cent. 20-50%","Cent. 50-90%","dphi_lead"},"leftflowlog",sel);
    Plot_hist({hxJ_lead[3],hxJ_lead[4],hxJ_lead[5]},{"Cent. 0-20%","Cent. 20-50%","Cent. 50-90%","xJ_lead"},"rightflow",sel);
    Plot_hist({hRg_lead[3],hRg_lead[4],hRg_lead[5]},{"Cent. 0-20%","Cent. 20-50%","Cent. 50-90%","Rg_lead"},"rightflow",sel);
    Plot_hist({hangu_lead[3],hangu_lead[4],hangu_lead[5]},{"Cent. 0-20%","Cent. 20-50%","Cent. 50-90%","angu_lead"},"rightflow",sel);
    Plot_hist({hktdyn_lead[3],hktdyn_lead[4],hktdyn_lead[5]},{"Cent. 0-20%","Cent. 20-50%","Cent. 50-90%","ktdyn_lead"},"rightflowlog",sel);

    Plot_hist2D({h_Rg_xJ[0],h_angu_xJ[0],h_ktdyn_xJ[0]},{"Rg_xJ_0_30","Angu_xJ_0_30","Ktdyn_xJ_0_30"},"text",{"Cent. 0-30%"});
    
    printf("\n");
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
    float leg_x1 = 0.75;
    float leg_y1 = 0.7;
    float leg_x2 = 0.85;
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
        latex.DrawLatexNDC(0.5,0.92,eopt[0]);
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
    c.SaveAs(input_path + "/OutputPlots_"+label+"/"+histname.back()+".png");
    std::cout<<histname.back()<<" has been saved"<<std::endl;
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
        c.SaveAs(input_path + "/OutputPlots_"+label+"/"+histname[ihist]+".png");
        std::cout<<histname[ihist]<<" has been saved"<<std::endl;
    }
    /*
    
    
    delete l;*/
}

int main(int argc, char* argv[]){

    // printf("argc = %d\n",argc);
    // printf("argv = %s\n",argv[0]);
    if(argc==3){
        input_path = argv[1];
        label = argv[2];
        plot_jet();
    }
    else{
        printf("Run with \n ./plot_jet <input file> <label>\n");
    }

    return 0;
}