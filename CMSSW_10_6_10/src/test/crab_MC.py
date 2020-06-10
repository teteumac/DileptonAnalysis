#from CRABClient.UserUtiilities import config, getUsernameFromSiteDB

from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException

# We want to put all the CRAB project directories from the tasks we submit here into one common directory.
# That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).

from WMCore.Configuration import Configuration

config = Configuration()
config.section_('General')
config.General.transferOutputs = True
config.General.transferLogs = True
config.General.workArea = 'crab_projects'

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'RunGGLL_UL_MC_cfg.py'
#config.JobType.maxMemoryMB = 760
config.JobType.inputFiles = ['direct_simu_reco_cff.py','xangle_UL2017.root','PUHistos_data.root','PUHistos_mc.root']
#config.JobType.outputFiles = ['output_HepMC.root', 'output_track_xy.root']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')
config.Data.inputDBS = 'global'
config.Data.splitting = 'EventAwareLumiBased' #'FileBased'
#config.Data.splitting = 'Automatic' #'FileBased'
#config.Data.totalUnits = 100
config.Data.publication = False

config.section_('Site')
config.Site.storageSite = 'T2_BR_UERJ'
config.Site.whitelist = ['T2_CH_*','T2_BE_*', 'T2_DE_*', 'T2_RU_*','T2_US_*', 'T2_IT_*', 'T2_ES_*']
#config.Site.storageSite = 'T2_IT_Bari'

def submit(config):
   try:
      crabCommand('submit', config = config)
   except HTTPException as hte:
      print "Failed submitting task: %s" % (hte.headers)
   except ClientException as cle:
      print "Failed submitting task: %s" % (cle)

if __name__ == '__main__':

   config.General.requestName = 'DYJetsToLL-RunIISummer19UL17'
   config.Data.unitsPerJob = 11000
   config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM'
   config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/DYJetsToLL-RunIISummer19UL17'
   submit(config)

   config.General.requestName = 'GGToMuMu-Semi-Exclusive-RunIISummer17'
   config.Data.unitsPerJob = 6200
   config.Data.inputDataset = '/GGToMuMu_Pt-50_Inel-El_13TeV-lpair/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v1/MINIAODSIM'
   config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/GGToMuMu-Semi-Exclusive-RunIISummer17'
   submit(config)

   config.General.requestName = 'GGToMuMu-Exclusive-RunIIFall17'
   config.Data.unitsPerJob = 6200
   config.Data.inputDataset = '/GGToMuMu_Pt-50_Elastic_13TeV-lpair/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
   config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/GGToMuMu-Exclusive-RunIIFall17'
   submit(config)
