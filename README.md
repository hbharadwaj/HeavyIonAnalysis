# Gamma-Jet analysis 

### Running the Setup
```
cmsrel CMSSW_10_3_3_patch1
cd CMSSW_10_3_3_patch1/src
cmsenv
# this must always be forest_CMSSW_10_3_1, regardless of the version used earlier
git cms-merge-topic CmsHI:forest_CMSSW_10_3_1
git remote add cmshi git@github.com:CmsHI/cmssw.git
cd HeavyIonsAnalysis/PhotonAnalysis/test/
# Analysis folders and scripts in order are here. 
# To create a test NTuple
cd crabJobs/
cmsRun runForestAOD_pponAA_MIX_103X_subs_gamma.py
```

### Skimming the HiForest

The HiForest NTuples are skimmed to get all photons for energy regression:

[PhotonAnalysis/test/1\_Skimming\_weighting/](PhotonAnalysis/test/1_Skimming_weighting/)

After regression, the leading photon in the event is selected for analysis in:

[PhotonAnalysis/test/3\_Skimming\_with\_corrections/](PhotonAnalysis/test/3_Skimming_with_corrections/)

Photon energy regression, and Electron rejection are applied at this step and all jets are stored. 
This is used for Photon Purity and Photon ID studies.

---
### Jet Analysis

For studying all jets we use the skim produced earlier. 

Leading and recoil jet selection can be applied here.
JEC and JER require the CMSSW setup. Run as a root macro:
```
cd JetAnalysis/test/
root -l plot_jet.cc
```

#### Jets for Systematic Uncertainty

RooUnfold needs latest version of root which conflicts with CMSSW. 
```
source /cvmfs/sft.cern.ch/lcg/views/LCG_100/x86_64-centos7-gcc10-opt/setup.sh
```

The substructure variables for unfolding are stored in another skim using:

```
# In CMSSW
cd JetAnalysis/test/
root -l skim_sys_PbPb.cc
```

And then read into RooUnfold using:

```
source /cvmfs/sft.cern.ch/lcg/views/LCG_100/x86_64-centos7-gcc10-opt/setup.sh
cd Unfolding/RooUnfold_Leticia/
root -l 
# In ROOT Prompt 
gSystem->Load("libRooUnfold.so");
.x examples/RooUnfold_bharad_sys_PbPb.cxx
```

The unfolding script has options for the unfolding tests:

|Case|Option|
|:--:|:---:|
|kNoTest | All Systematic Uncertainties|
|kTrivial| Trivial Unfolding of MC with same response|
|kSplitNominal| Split Test where MC pseudodata is representative of relative error in Data|
|kCrossfold   | Nominal MC Unfolded with Alt MC and vice-versa|
|kBottomline  | Data unfolded with nominal MC, used for tests|

The results can be plotted with:
```
cd JetAnalysis/test/
root -l plot_sys_inverted_PbPb.cc
cd Uncertainty/ 
root -l
# In ROOT Prompt for D'Agostini 
.L plot_combine.cc
combine(TString in_varname="",int iter_ref,int iter_prior)
.q


# This combines the results of the systematic uncertainty variations for the given variable into a single file
# In a new ROOT prompt

.L plot_combine.cc
plot_combine(<FILE>)

# Relative Systematic Uncertainties are plotted and Total Uncertainties are evaluated
``` 





