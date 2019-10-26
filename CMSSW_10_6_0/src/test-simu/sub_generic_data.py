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

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
#config.JobType.psetName = 'test_cfg-el.py'
#config.JobType.psetName = 'test_cfg-sd.py'
#config.JobType.maxJobRuntimeMin = 60
config.JobType.psetName = 'null'
#config.JobType.maxMemoryMB = 760
config.JobType.inputFiles = ['alignment.xml','direct_simu_reco_cff.py','customisation_cff.py','PUHistos_data.root','PUHistos_mc.root']
#config.JobType.outputFiles = ['output_HepMC.root', 'output_track_xy.root']

config.section_('Data')
config.Data.useParent = True
config.Data.ignoreLocality = True
config.Data.lumiMask = '/afs/cern.ch/user/m/malvesga/work/ProtonRecon/TEST/CMSSW_10_6_0/src/test-simu/json_file_rpin_2017.txt'
config.Data.inputDBS = 'global'
#config.Data.splitting = 'Automatic' #'FileBased'
config.Data.splitting = 'EventAwareLumiBased' #'FileBased'
config.Data.unitsPerJob = 8200
#config.Data.totalUnits = 100
#config.Data.outLFNDirBase = 'gsiftp://eosuserftp.cern.ch/eos/user/m/malvesga' #%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.outputDatasetTag = 'background'

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERNBOX'
config.Site.whitelist = ['T2_CH_CERN','T2_DE_*','T2_IT_Bari','T2_US_*']
#config.Site.storageSite = 'T2_IT_Bari'

def submit(config):
    try:
        crabCommand('submit', config = config)
    except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
    except ClientException as cle:
        print "Failed submitting task: %s" % (cle)

if __name__ == '__main__':
    
    #config.General.workArea = 'crab_projects'
    #config.General.requestName = 'DoubleMuon_Data_2017B'
    #config.JobType.psetName = 'test_cfg-miniaod_data.py'
    #config.Data.inputDataset = '/DoubleMuon/Run2017B-31Mar2018-v1/MINIAOD'
    #config.Data.outLFNDirBase = '/store/user/malvesga/miniaod'
    #submit(config)
    
    config.General.workArea = 'crab_projects'
    config.General.requestName = 'DoubleMuon_Data_2017C_limitRun'
    config.JobType.psetName = 'test_cfg-miniaod_data.py'
    config.Data.runRange = '299337-300785'
    config.Data.inputDataset = '/DoubleMuon/Run2017C-31Mar2018-v1/MINIAOD'
    config.Data.outLFNDirBase = '/store/user/malvesga/miniaod'
    submit(config)

    #config.General.workArea = 'crab_projects'
    #config.General.requestName = 'DoubleMuon_Data_2017D'
    #config.JobType.psetName = 'test_cfg-miniaod_data.py'
    #config.Data.inputDataset = '/DoubleMuon/Run2017D-31Mar2018-v1/MINIAOD'
    #config.Data.outLFNDirBase = '/store/user/malvesga/miniaod'
    #submit(config)

    #config.General.workArea = 'crab_projects'
    #config.General.requestName = 'DoubleMuon_Data_2017E'
    #config.JobType.psetName = 'test_cfg-miniaod_data.py'
    #config.Data.inputDataset = '/DoubleMuon/Run2017E-31Mar2018-v1/MINIAOD'
    #config.Data.outLFNDirBase = '/store/user/malvesga/miniaod'
    #submit(config)
    
    config.General.workArea = 'crab_projects'
    config.General.requestName = 'DoubleMuon_Data_2017F_limitRun'
    config.JobType.psetName = 'test_cfg-miniaod_data.py'
    config.Data.runRange = '304911-305114'
    config.Data.inputDataset = '/DoubleMuon/Run2017F-31Mar2018-v1/MINIAOD'
    config.Data.outLFNDirBase = '/store/user/malvesga/miniaod'
    submit(config)

