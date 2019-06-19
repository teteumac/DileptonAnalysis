from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Dimuon_Elastic_Fall2017-v1'

config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'test_cfg-mod.py'
config.JobType.inputFiles = ['alignment.xml','direct_simu_reco_cff.py','customisation_cff.py','PUHistos_data.root','PUHistos_mc.root']

config.Data.inputDataset = '/GGToMuMu_Pt-50_Elastic_13TeV-lpair/RunIIFall17DRPremix-94X_mc2017_realistic_v11-v1/AODSIM'

config.Data.inputDBS = 'global'
config.Data.splitting = 'Automatic' #'FileBased'
#config.Data.outLFNDirBase = 'gsiftp://eosuserftp.cern.ch/eos/user/m/malvesga' #%s/' % (getUsernameFromSiteDB())
config.Data.outLFNDirBase = '/store/user/malvesga' #%s/' % (getUsernameFromSiteDB())
config.Data.publication = False

config.Data.outputDatasetTag = 'background'

#config.JobType.outputFiles = ['out.root']
config.JobType.outputFiles = ['output_HepMC.root', 'output_track_xy.root']

config.Site.storageSite = 'T2_CH_CERNBOX'
#config.Site.storageSite = 'T2_US_Nebraska'

