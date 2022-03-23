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

