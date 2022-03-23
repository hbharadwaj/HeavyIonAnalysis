from WMCore.Configuration import Configuration
config = Configuration()

#from CRABClient.UserUtilities import config, getUsernameFromSiteDB
#config = config()

### General ###
config.section_('General')
config.General.requestName = 'substructure_photonjet_pthat80_v2'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#### JobType ####
config.section_('JobType')
config.JobType.pluginName = "Analysis"
config.JobType.psetName = "runForestAOD_pponAA_MIX_103X_subs_gamma.py"
config.JobType.maxMemoryMB = 3000
config.JobType.allowUndistributedCMSSW = True
config.JobType.numCores = 1

#### Data ####
config.section_("Data")
##this is dijet PbPb embedded
#config.Data.inputDataset = "/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM"
##this is pp pythia
#config.Data.inputDataset = "/QCD_pThat-15_Dijet_TuneCP5_PbPb_5p02TeV_pythia8/HINPbPbAutumn18DR-NoPU_103X_upgrade2018_realistic_HI_v11-v1/AODSIM"
#this is gamma-jet embedded
config.Data.inputDataset = "/QCDPhoton_pThat-80_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM" 
#config.Data.inputDataset = "/Bjet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM"
#config.Data.inputDataset = "/MuJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v3/AODSIM"
#config.Data.inputDataset = "/muEnriched_cJet_embedded/mnguyen-muEnriched_cJet_embedded_RECO-758a9d95eb6b8bfb08f025aff8d007d6/USER"
#config.Data.inputDataset = "/muEnriched_cJet_embedded/mnguyen-muEnriched_cJet_embedded_RECO_part2-758a9d95eb6b8bfb08f025aff8d007d6/USER"


config.Data.inputDBS = "global"
#config.Data.inputDBS = "phys03"
config.Data.splitting = "FileBased"
#config.Data.splitting = "Automatic"
config.Data.unitsPerJob = 1
#config.Data.unitsPerJob = 180
#config.Data.unitsPerJob = 600

config.Data.totalUnits = 500
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/lcunquei/photonjet_hybrid_/'
config.Data.outputDatasetTag = config.General.requestName
#commented out for  pp
#config.Data.ignoreLocality = True
config.Data.allowNonValidInputDataset = True

#### Site ####
config.section_('Site')
##just for pp
#config.Site.whitelist = ['T2_FR_GRIF_*', "T2_CH_*","T2_US_MIT"] 
#for Hybrid
#config.Site.whitelist = ['T2_FR_*', "T2_CH_*","T2_US_MIT"]
#config.Site.whitelist = ['T2_FR_*', "T2_CH_*"]
config.Site.storageSite = 'T2_FR_GRIF_LLR'
