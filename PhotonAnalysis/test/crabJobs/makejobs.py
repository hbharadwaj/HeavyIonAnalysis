# Run with python makejobs.py --n "DATE" --l "z_0p2_R234_NOMINAL"

import argparse
import subprocess
import sys
import os
import readline
import string
import PbPbSamples

# set up an argument parser
parser = argparse.ArgumentParser()
parser.add_argument('--n', dest='DATE')
parser.add_argument('--l', dest='LABEL',default= "z_0p2_R234")     # Name tag for request and outputfolder

parser.add_argument('--s', dest = 'SELECTED', default= None) 
parser.add_argument('--d', dest = 'DATASET', default= None) 

ARGS = parser.parse_args()

SAMPLES = {}  # list of MC samples to submit -> Make a list for pthat80Filter30, unfilter, Filter30 and Filter 50
SAMPLES.update(PbPbSamples.mc2018_samples_Unfilter)
SAMPLES.update(PbPbSamples.mc2018_samples_Filter_30)
# SAMPLES.update(PbPbSamples.mc2018_samples_Filter_50)
# SAMPLES.update(PbPbSamples.mc2018_samples_pthat15)
# SAMPLES.update(PbPbSamples.mc2018_samples_pthat80Filter30)

dirname = 'CRABtasks' ## If we want to change this then we should make it an ARG so we can edit name is script below
os.system('mkdir -p '+ dirname )
print "make CRABtasks directory to store CRAB submit scripts"

SUBMIT_SCRIPT = '''                                                                                                                                       
#!/usr/bin/env python                                                                                                                                        

import os, subprocess                                                                                                                                                  
print "Now submitting your CRAB jobs for PbPb MC HiForest"

'''

## list of keys we ran over to use for the CRAB submit script
ids = []

for key, item in SAMPLES.items() :
#    ARGS.DATASET = samp

    #if ARGS.SELECTED != None :
    #    if key != ARGS.SELECTED :
    #        continue
    # if ("QCDPhoton_pThat_80_Filter50" not in key) and ("QCDPhoton_pThat_120" not in key):
    #     continue
    print "-------------------------"  
    print key 
    # print item
    # print SAMPLES[key]

    ARGS.SELECTED = key
    ARGS.DATASET = item[0]

    # make a CRAB config file with template arguments
    CRAB_CFG = '''
from WMCore.Configuration import Configuration
config = Configuration()

### General ###
config.section_("General")
config.General.requestName = '%s_%s_%s' % ( '{DATE}', '{SELECTED}' ,'{LABEL}')
config.General.workArea = "jobs"
config.General.transferOutputs = True
config.General.transferLogs = True

#### JobType ####
config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForestAOD_pponAA_MIX_103X_subs_gamma.py'
config.JobType.maxMemoryMB = 4000
config.JobType.allowUndistributedCMSSW = True
config.JobType.numCores = 1

#### Data ####
config.section_("Data")
config.Data.inputDataset = "{DATASET}"
config.Data.inputDBS = "global"
config.Data.splitting = "FileBased"
config.Data.unitsPerJob = 1
config.Data.totalUnits = -1
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/bharikri/%s/%s_%s_%s/' % ( '{DATE}','{DATE}', '{SELECTED}' ,'{LABEL}')
config.Data.outputDatasetTag = config.General.requestName
config.Data.allowNonValidInputDataset = True

#### Site ####
config.section_('Site')
#config.Site.whitelist = ['T2_FR_GRIF_*', "T2_RU_*","T2_BR_*","T2_IN_TIFR"]
config.Site.storageSite = 'T2_FR_GRIF_LLR' #'T3_CH_CERNBOX'#'T2_FR_GRIF_LLR'

'''
    open('%s/crabConfig%s.py'% (dirname , key ) , 'w').write(CRAB_CFG.format(**ARGS.__dict__))
    ids.append(key)

#subprocess.call('cd %s' % (dirname), shell=True)
subprocess.call('cp runForestAOD_pponAA_MIX_103X_subs_gamma.py %s/ ' % (dirname), shell=True)

SUBMIT_SCRIPT = '''                                                                                                                                       
#!/usr/bin/env python                                                                                                                                        

import os, subprocess                                                                                                                                                  
print "Now submitting your CRAB jobs for PbPb MC HiForest"

'''


sublist = []
for aid in ids :
    ARGS.ID = aid
#idname%s = '%s'
    subCommand = '''                                                                                                                                         
print " --------------------------------------------------------------------------------- "      
print " Submitting CRAB job for dataset : %s "                                                                                              
subprocess.call('crab submit -c crabConfig%s.py' , shell=True)                                                                            
subprocess.call('echo "crab submit -c crabConfig%s.py" ' , shell=True)                                                                     
                                                                                                                        
'''% (aid, aid, aid)
 
    sublist.append(subCommand)   
    SUBMIT_SCRIPT += subCommand
#print sublist    

#for s in sublist :
#    SUBMIT_SCRIPT += subCommand

open('%s/crab_submitter.py' % (dirname), 'w').write(SUBMIT_SCRIPT.format(**ARGS.__dict__))
print "You have successfully created CRAB submit scripts =D"
print "now you need to submit your jobs"
print "get a grid proxy by doing : "
print "voms-proxy-init --voms cms"
print "then cd to the CRABtasks directory and run:"
print "python crab_submitter.py"
print "That script will contain commands to run all of the scripts you just created..."