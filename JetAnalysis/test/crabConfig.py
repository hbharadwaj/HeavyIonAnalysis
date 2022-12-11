from WMCore.Configuration import Configuration
config = Configuration()


### General ###
config.section_('General')
config.General.requestName = 'Oct_31_pp_Herwig_part2_z_0p2_R2'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#### JobType ####
config.section_('JobType')
config.JobType.pluginName = "Analysis"
config.JobType.psetName = "runForestAOD_pp_MC_94X.py"
#config.JobType.maxMemoryMB = 16000
#config.JobType.maxMemoryMB = 20000
config.JobType.maxMemoryMB = 4000
config.JobType.allowUndistributedCMSSW = True
config.JobType.numCores = 1

#### Data ####
config.section_("Data")

#config.Data.inputDataset = "/QCDPhoton_pThat-30_Filter30GeV_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v2/AODSIM"
#config.Data.inputDataset = "/pyquen80_GJet/mnguyen-pyquen80_GJet_RECO-9729ad36c848138bb3596c5c0b8413d8/USER"
#config.Data.inputDataset = "/herwig_GJet/mnguyen-herwig_GJet_RECO-9729ad36c848138bb3596c5c0b8413d8/USER"
config.Data.inputDataset = "/herwig_GJet/mnguyen-herwig_GJet_part2_RECO-9729ad36c848138bb3596c5c0b8413d8/USER"
#config.Data.inputDataset = "/QCD_pThat-170_EMEnrichedDijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v1/AODSIM"

#config.Data.lumiMask = 'Cert_306546-306826_5TeV_EOY2017ReReco_Collisions17_JSON.txt'
#config.Data.lumiMask = 'crab_projects/crab_bJet2018_HIHardProbes_deepCSVAVF/results/notFinishedLumis.json'
config.Data.inputDBS = 'phys03'#"global" # 'phys03'
#config.Data.splitting = "LumiBased"
config.Data.splitting = "FileBased"
#config.Data.unitsPerJob = 5
config.Data.unitsPerJob = 1
#config.Data.totalUnits = 500
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/bharikri/Oct_31_pp_Herwig_part2_z_0p2_R2/' 
config.Data.outputDatasetTag = config.General.requestName
config.Data.ignoreLocality = True  # turn on for pp
config.Data.allowNonValidInputDataset = True

#### Site ####
config.section_('Site')
config.Site.whitelist = ['T2_FR_GRIF_*', "T2_RU_*","T2_BR_*","T2_US*"]
config.Site.storageSite = 'T2_FR_GRIF_LLR'
