from WMCore.Configuration import Configuration
config = Configuration()


### General ###
config.section_('General')
config.General.requestName = 'Mar_11_data_2018_z_0p2_R234_centrality_tag_update'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#### JobType ####
config.section_('JobType')
config.JobType.pluginName = "Analysis"
config.JobType.psetName = "runForestAOD_pponAA_DATA_103X_subs_gamma.py"
#config.JobType.maxMemoryMB = 16000
#config.JobType.maxMemoryMB = 20000
config.JobType.maxMemoryMB = 4000
config.JobType.allowUndistributedCMSSW = True
config.JobType.numCores = 1

#### Data ####
config.section_("Data")

config.Data.inputDataset = "/HIHardProbes/HIRun2018A-04Apr2019-v1/AOD"

config.Data.lumiMask = 'Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt'
#config.Data.lumiMask = 'crab_projects/crab_bJet2018_HIHardProbes_deepCSVAVF/results/notFinishedLumis.json'
config.Data.inputDBS = "global"
#config.Data.splitting = "LumiBased"
config.Data.splitting = "FileBased"
config.Data.unitsPerJob = 3
#config.Data.unitsPerJob = 1
#config.Data.totalUnits = 500
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/bharikri/Mar_11_data_2018_z_0p2_R234_centrality_tag_update/' 
config.Data.outputDatasetTag = config.General.requestName
#config.Data.ignoreLocality = True  // turn on for pp
config.Data.allowNonValidInputDataset = True

#### Site ####
config.section_('Site')
#config.Site.whitelist = ['T2_FR_GRIF_*', "T2_RU_*","T2_BR_*"]
config.Site.storageSite = 'T2_FR_GRIF_LLR'
