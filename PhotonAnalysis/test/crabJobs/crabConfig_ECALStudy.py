from WMCore.Configuration import Configuration
config = Configuration()


### General ###
config.section_('General')
config.General.requestName = '2023_Aug_20_QCDPhoton_15_ECAL_ZS_EB_EE_10_SR_HI_4_MI_2'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#### JobType ####
config.section_('JobType')
config.JobType.pluginName = "Analysis"
config.JobType.psetName = "runForestAOD_pponAA_MIX_103X_subs_gamma.py"
#config.JobType.maxMemoryMB = 16000
#config.JobType.maxMemoryMB = 20000
config.JobType.maxMemoryMB = 4000
config.JobType.allowUndistributedCMSSW = True
config.JobType.numCores = 1

#### Data ####
config.section_("Data")

#config.Data.inputDataset = "/QCDPhoton_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM"
#config.Data.inputDataset = "/QCDPhoton_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/tsheng-HINPbPbAutumn18GSHIMix-103X_upgrade2018_realistic_HI_v11-v1_RECO_ECAL_ZS_EB_EE_4_SR_HI_4_MI_2-9d6276cdc6045615bacf105699937a6f/USER"
#config.Data.inputDataset = "/QCDPhoton_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/tsheng-HINPbPbAutumn18GSHIMix-103X_upgrade2018_realistic_HI_v11-v1_RECO_ECAL_ZS_EB_EE_8_SR_HI_4_MI_2-9d6276cdc6045615bacf105699937a6f/USER"
config.Data.inputDataset = "/QCDPhoton_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/tsheng-HINPbPbAutumn18GSHIMix-103X_upgrade2018_realistic_HI_v11-v1_RECO_ECAL_ZS_EB_EE_10_SR_HI_4_MI_2-9d6276cdc6045615bacf105699937a6f/USER"

#config.Data.lumiMask = 'Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt'
#config.Data.lumiMask = 'crab_projects/crab_bJet2018_HIHardProbes_deepCSVAVF/results/notFinishedLumis.json'
#config.Data.inputDBS = "global"
config.Data.inputDBS = "phys03"
#config.Data.splitting = "LumiBased"
config.Data.splitting = "FileBased"
config.Data.unitsPerJob = 1
#config.Data.unitsPerJob = 1
config.Data.totalUnits = -1
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/bharikri/ECAL_ZS/2023_Aug_20_QCDPhoton_15_ECAL_ZS_EB_EE_10_SR_HI_4_MI_2/' 
config.Data.outputDatasetTag = config.General.requestName
#config.Data.ignoreLocality = True
config.Data.allowNonValidInputDataset = True

#### Site ####
config.section_('Site')
#config.Site.whitelist = ['T2_FR_GRIF_*', "T2_RU_*","T2_BR_*"]
config.Site.storageSite = 'T2_FR_GRIF_LLR'#'T3_CH_CERNBOX'#'T2_FR_GRIF_LLR'
