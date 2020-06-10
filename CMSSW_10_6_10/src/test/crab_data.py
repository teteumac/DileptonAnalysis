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
config.JobType.psetName = 'RunGGLL_UL_data_cfg.py'
#config.JobType.maxMemoryMB = 760
config.JobType.inputFiles = ['direct_simu_reco_cff.py','PUHistos_data.root']
#config.JobType.outputFiles = ['output_HepMC.root', 'output_track_xy.root']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')
#config.Data.useParent = True
config.Data.ignoreLocality = True
config.Data.lumiMask = '/home/malvesga/CMSSW_10_6_10/src/test/json_file_rpin_2017.txt'
config.Data.inputDBS = 'global'
config.Data.splitting = 'Automatic' #'FileBased'
#config.Data.totalUnits = 100
config.Data.publication = False
config.Data.outputDatasetTag = 'data'

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

   #config.General.requestName = 'DoubleMuon_Data_UL2017B'
   #config.Data.inputDataset = '/DoubleMuon/Run2017B-09Aug2019_UL2017-v1/MINIAOD'
   #config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/DoubleMuon_Data_UL2017B'
   #submit(config)

   #config.General.requestName = 'DoubleMuon_Data_UL2017C1'
   #config.Data.runRange = '299337-300785'
   #config.Data.inputDataset = '/DoubleMuon/Run2017C-09Aug2019_UL2017-v1/MINIAOD'
   #config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/DoubleMuon_Data_UL2017C1'
   #submit(config)

   #config.General.requestName = 'DoubleMuon_Data_UL2017C2'
   #config.Data.runRange = '300806-302029'
   #config.Data.inputDataset = '/DoubleMuon/Run2017C-09Aug2019_UL2017-v1/MINIAOD'
   #config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/DoubleMuon_Data_UL2017C2'
   #submit(config)

   config.General.requestName = 'DoubleMuon_Data_UL2017D'
   config.Data.inputDataset = '/DoubleMuon/Run2017D-09Aug2019_UL2017-v1/MINIAOD'
   config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/DoubleMuon_Data_UL2017D'
   submit(config)

   config.General.requestName = 'DoubleMuon_Data_UL2017E'
   config.Data.inputDataset = '/DoubleMuon/Run2017E-09Aug2019_UL2017-v1/MINIAOD'
   config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/DoubleMuon_Data_UL2017E'
   submit(config)

   #config.General.requestName = 'DoubleMuon_Data_UL2017F1'
   #config.Data.runRange = '304911-305114'
   #config.Data.inputDataset = '/DoubleMuon/Run2017F-09Aug2019_UL2017-v1/MINIAOD'
   #config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/DoubleMuon_Data_UL2017F1'
   #submit(config)

   #config.General.requestName = 'DoubleMuon_Data_UL2017F2'
   #config.Data.runRange = '305178-305902'
   #config.Data.inputDataset = '/DoubleMuon/Run2017F-09Aug2019_UL2017-v1/MINIAOD'
   #config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/DoubleMuon_Data_UL2017F2'
   #submit(config)

   #config.General.requestName = 'DoubleMuon_Data_UL2017F3'
   #config.Data.runRange = '305965-306462'
   #config.Data.inputDataset = '/DoubleMuon/Run2017F-09Aug2019_UL2017-v1/MINIAOD'
   #config.Data.outLFNDirBase = '/store/user/malvesga/miniaod/DoubleMuon_Data_UL2017F3'
   #submit(config)
