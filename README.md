# Run 3 ECAL study

### Running the Setup
```
cmsrel CMSSW_10_3_3_patch1
cd CMSSW_10_3_3_patch1/src
cmsenv
# this must always be forest_CMSSW_10_3_1, regardless of the version used earlier
git cms-merge-topic CmsHI:forest_CMSSW_10_3_1
git remote add cmshi git@github.com:CmsHI/cmssw.git

```
Copy the files from this repo to PhotonAnalysis directory

```
scram b -j 8
cd HeavyIonsAnalysis/PhotonAnalysis/test/
# Analysis folders and scripts in order are here. 
# To create a test NTuple
cd crabJobs/
cmsRun runForestAOD_pponAA_MIX_103X_subs_gamma_ECAL.py

```

Sample crab config file available in `crabJobs/crabConfig_ECALStudy.py`

---
### Photon object studies

```
cd HeavyIonsAnalysis/PhotonAnalysis/test/ECAL_Study/
./compile Plot_ZS
./Plot_ZS <optional to give a label> 
```
The directory structure is hardcoded in the [Plot_ZS.cc](PhotonAnalysis/test/ECAL_Study/Plot_ZS.cc) script. 
Modify:

|Line | Comment|
|:---:|:---:|
|[L24](https://github.com/hbharadwaj/HeavyIonAnalysis/blob/4330d829769c18451544bedb403238fd7621433d/PhotonAnalysis/test/ECAL_Study/Plot_ZS.cc#L24) | Common directory with the different ZS settings HiForestAOD|
|[L998-1004](https://github.com/hbharadwaj/HeavyIonAnalysis/blob/4330d829769c18451544bedb403238fd7621433d/PhotonAnalysis/test/ECAL_Study/Plot_ZS.cc#L998-L1004) | Reference to the individual ZS setting folder name and label|
||(optional)|
|[L32-40](https://github.com/hbharadwaj/HeavyIonAnalysis/blob/4330d829769c18451544bedb403238fd7621433d/PhotonAnalysis/test/ECAL_Study/Plot_ZS.cc#L32-L40) | Specify eta and centrality ranges|
|[L1015-1039](https://github.com/hbharadwaj/HeavyIonAnalysis/blob/4330d829769c18451544bedb403238fd7621433d/PhotonAnalysis/test/ECAL_Study/Plot_ZS.cc#L1015-L1039)| Plotting specific eta and centrality ranges and choice of histograms|
