import sys
import os
import subprocess
import readline
import string

#### SAMPLES

mc2018_samples_pthat80Filter30 = {}
mc2018_samples_Unfilter = {}
mc2018_samples_Filter_30 = {}
mc2018_samples_Filter_50 = {}
mc2018_samples_pthat15 = {}

mc2018_samples_Unfilter['QCDPhoton_pThat_30'] = ['/QCDPhoton_pThat-30_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Unfilter['QCDPhoton_pThat_50'] = ['/QCDPhoton_pThat-50_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Unfilter['QCDPhoton_pThat_80'] = ['/QCDPhoton_pThat-80_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Unfilter['QCDPhoton_pThat_120'] = ['/QCDPhoton_pThat-120_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v2/AODSIM']
mc2018_samples_Unfilter['QCDPhoton_pThat_170'] = ['/QCDPhoton_pThat-170_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v2/AODSIM']

mc2018_samples_Filter_30['QCDPhoton_pThat_30_Filter30'] = ['/QCDPhoton_pThat-30_Filter30GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Filter_30['QCDPhoton_pThat_50_Filter30'] = ['/QCDPhoton_pThat-50_Filter30GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Filter_30['QCDPhoton_pThat_80_Filter30'] = ['/QCDPhoton_pThat-80_Filter30GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Filter_30['QCDPhoton_pThat_120_Filter30'] = ['/QCDPhoton_pThat-120_Filter30GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Filter_30['QCDPhoton_pThat_170_Filter30'] = ['/QCDPhoton_pThat-170_Filter30GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v2/AODSIM']

mc2018_samples_Filter_50['QCDPhoton_pThat_30_Filter50'] = ['/QCDPhoton_pThat-30_Filter50GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Filter_50['QCDPhoton_pThat_50_Filter50'] = ['/QCDPhoton_pThat-50_Filter50GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Filter_50['QCDPhoton_pThat_80_Filter50'] = ['/QCDPhoton_pThat-80_Filter50GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Filter_50['QCDPhoton_pThat_120_Filter50'] = ['/QCDPhoton_pThat-120_Filter50GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_Filter_50['QCDPhoton_pThat_170_Filter50'] = ['/QCDPhoton_pThat-170_Filter50GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v2/AODSIM']

mc2018_samples_pthat80Filter30['QCDPhoton_pThat_80_Filter30'] = ['/QCDPhoton_pThat-80_Filter30GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']

mc2018_samples_pthat15['QCDPhoton_pThat_15'] = ['/QCDPhoton_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']
mc2018_samples_pthat15['QCDPhoton_pThat_15_Filter30'] = ['/QCDPhoton_pThat-15_Filter30GeV_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM']