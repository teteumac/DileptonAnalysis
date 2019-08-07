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
#config.JobType.outputFiles = ['out.root']
#config.JobType.outputFiles = ['output_HepMC.root', 'output_track_xy.root']

config.section_('Data')
config.Data.inputDBS = 'global'
#config.Data.splitting = 'Automatic' #'FileBased'
config.Data.splitting = 'EventAwareLumiBased' #'FileBased'
config.Data.unitsPerJob = 6200
#config.Data.totalUnits = 100
#config.Data.outLFNDirBase = 'gsiftp://eosuserftp.cern.ch/eos/user/m/malvesga' #%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.outputDatasetTag = 'background'

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERNBOX'
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
    #config.General.requestName = 'Dimuon_Elastic_Fall2017-xangle140'
    #config.JobType.psetName = 'test_cfg-el.py'
    #config.Data.inputDataset = '/GGToMuMu_Pt-50_Elastic_13TeV-lpair/RunIIFall17DRPremix-94X_mc2017_realistic_v11-v1/AODSIM'
    #config.Data.outLFNDirBase = '/store/user/malvesga/aod'
    #submit(config)
    
    config.General.workArea = 'crab_projects'
    config.General.requestName = 'Dimuon_Elastic_Fall2017-xangle140-MINIAOD'
    config.JobType.psetName = 'test_cfg-miniaod.py'
    config.Data.inputDataset = '/GGToMuMu_Pt-50_Elastic_13TeV-lpair/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
    config.Data.outLFNDirBase = '/store/user/malvesga/miniaod'
    submit(config)
    
    #config.General.workArea = 'crab_projects'
    #config.General.requestName = 'Dimuon_SingleDiss_Summer2017-xangle140'
    #config.JobType.psetName = 'test_cfg-miniaod.py'
    #config.Data.inputDataset = '/GGToMuMu_Pt-50_Inel-El_13TeV-lpair/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v1/MINIAODSIM'
    #config.Data.outLFNDirBase = '/store/user/malvesga/miniaod'
    #submit(config)
    
    config.General.workArea = 'crab_projects'
    config.General.requestName = 'Dimuon_DrellYan_Fall2017-xangle140-MINIAOD'
    config.JobType.psetName = 'test_cfg-miniaod.py'
    config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
    config.Data.outLFNDirBase = '/store/user/malvesga/miniaod'
    submit(config)
    
    config.General.workArea = 'crab_projects'
    config.General.requestName = 'Dimuon_DrellYan_Fall2017_ext1-xangle140-MINIAOD'
    config.JobType.psetName = 'test_cfg-miniaod.py'
    config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM'
    config.Data.outLFNDirBase = '/store/user/malvesga/miniaod'
    submit(config)
