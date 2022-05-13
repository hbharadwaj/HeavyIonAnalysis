#include <TSystem.h>        // needed for gSystem
#include <TChain.h>         // needed for TChain
#include "TROOT.h"          // needed for gROOT
#include <TError.h>         // needed for gErrorIgnoreLevel
#include <TFile.h>          // needed for TFile
#include "TRandom3.h"        // needed for TRandom3

#include <iostream>         // needed for I/O

void Skim_SplitMC(TString file, float split_frac=0.3){
    
    gROOT->SetBatch();
    gErrorIgnoreLevel = kFatal;
    TFile oldfile(file);
    TTree *oldtree;
    oldfile.GetObject("jet_tree",oldtree);

    TFile Split1("Split1.root", "recreate");
    auto newtree1 = oldtree->CloneTree(0);

    TFile Split2("Split2.root", "recreate");
    auto newtree2 = oldtree->CloneTree(0);

    TRandom3* rand = new TRandom3(0);  

    Int_t nEv=oldtree->GetEntries();
    for(int iEntry=0; iEntry<nEv; iEntry++){
        oldtree->GetEntry(iEntry);
        if(rand->Rndm()<split_frac){
            newtree1->Fill();
        }
        else{
            newtree2->Fill();
        }
    }

    Split1.WriteTObject(newtree1);
    Split2.WriteTObject(newtree2);

    Split1.Close();
    Split2.Close();
}

int main(int argc, char* argv[]){

    if(argc==3){
        Skim_SplitMC(argv[1],atof(argv[2]));
    }
    else{
        Skim_SplitMC("Run with \n ./Skim_SplitMC <Input File> <Split Fraction>\n");
    }
    return 0;
}