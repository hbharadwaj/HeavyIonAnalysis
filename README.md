# Gamma-Jet analysis 

### Running the Setup

```
cmsrel CMSSW_9_4_10
cd CMSSW_9_4_10/src
cmsenv
git cms-merge-topic -u CmsHI:forest_CMSSW_9_4_10
git remote add cmshi git@github.com:CmsHI/cmssw.git
cd HeavyIonsAnalysis/JetAnalysis/python/jets
./makeJetSequences.sh
cd ../../../..
scram build -j4
cd HeavyIonsAnalysis/JetAnalysis/test
# Analysis folders and scripts in order are here. 
# To create a test NTuple
cd crabJobs/
cmsRun runForestAOD_pp_MC_94X.py
```

2017 pp ReReco Ntuples require this `CMSSW_9_4_X` version. This will not work for 2018 PbPb or 2017 pp UL samples 

**Switch to `CMSSW_10_3_X` for analysis scripts**. 
The JEC and JER files cannot be read in `CMSSW_9_4_X`

---

### Skimming the HiForest

The HiForest NTuples are skimmed to get leading photon in the event:
