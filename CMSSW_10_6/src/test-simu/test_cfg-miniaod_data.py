import FWCore.ParameterSet.Config as cms

#from Configuration.Eras.Modifier_ctpps_2016_cff import ctpps_2016
#process = cms.Process('CTPPSTestAcceptance', ctpps_2016)
from Configuration.StandardSequences.Eras import eras
process = cms.Process('TEST', eras.Run2_2017)

process.load("FWCore.MessageService.MessageLogger_cfi")

runOnMC = False
useAOD = True
MINIAOD = True

#xangle = 150

# load common code
#process.load("direct_simu_reco_cff")
#from customisation_cff import *
#SetDefaults(process)
#UseCrossingAngle(xangle, process)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('PATuple.root'),
    outputCommands = cms.untracked.vstring(
#        'drop *',
#        'keep *_offline*PrimaryVertices*_*_*',
#        'keep *_selectedPatMuons*_*_*',
#        'keep *_*lectron*_*_*',
#        'keep *_selectedPatElectrons*_*_*',
#        'keep *_selectedPat*Photons*_*_*',
#        'keep *_selectedPatJets*_*_*',
#        'keep *_*MET*_*_*',
#        'keep *_*particleFlow*_*_*',
        'keep *_*_*_*'
    ),
)

from PhysicsTools.PatAlgos.tools.helpers import getPatAlgosToolsTask
patAlgosToolsTask = getPatAlgosToolsTask(process)

process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
patAlgosToolsTask.add(process.patCandidatesTask)

process.load("PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff")
patAlgosToolsTask.add(process.selectedPatCandidatesTask)

from PhysicsTools.PatAlgos.tools.coreTools import runOnData
if not runOnMC:
 runOnData( process )

# minimal logger settings
#process.MessageLogger = cms.Service("MessageLogger",
#  statistics = cms.untracked.vstring(),
#  destinations = cms.untracked.vstring('cerr'),
#  cerr = cms.untracked.PSet(
#    threshold = cms.untracked.string('WARNING')
#  )
#)

# event source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/m/mthiel/public/To_Miquel/samples/RECO_RAW2DIGI_L1Reco_RECO_ALCA_SKIM_EI_PAT_DQM_inMINIAOD.root"),
    secondaryFileNames = cms.untracked.vstring("file:/afs/cern.ch/user/m/mthiel/public/To_Miquel/samples/RECO_RAW2DIGI_L1Reco_RECO_ALCA_SKIM_EI_PAT_DQM.root")
#    fileNames = cms.untracked.vstring("/store/mc/RunIIFall17MiniAODv2/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1/20000/88BE601E-6B44-E811-94D0-44A842CFD619.root")
#    fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/m/malvesga/work/ProtonRecon/CMSSW_9_4_7/src/workspace/ProductionSamples_DoubleDiss/TOP-RunIIFall17MiniAOD-00091.root")
#    fileNames = cms.untracked.vstring("/store/mc/RunIIFall17MiniAODv2/GGToMuMu_Pt-50_Elastic_13TeV-lpair/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/10000/A27AD9A6-3444-E811-A0C1-FA163E15F054.root")
	 #fileNames = cms.untracked.vstring("")
)

process.options=cms.untracked.PSet(wantSummary=cms.untracked.bool(True))

# number of events
process.maxEvents = cms.untracked.PSet(
  #input = cms.untracked.int32(-1)
  input = cms.untracked.int32(100)
)

# update settings of beam-smearing module
#process.beamDivergenceVtxGenerator.src = cms.InputTag("")
#process.beamDivergenceVtxGenerator.srcGenParticle = cms.VInputTag(
#  cms.InputTag("genPUProtons", "genPUProtons"),
#  cms.InputTag("prunedGenParticles")
#)

# do not apply vertex smearing again
#process.ctppsBeamParametersESSource.vtxStddevX = 0
#process.ctppsBeamParametersESSource.vtxStddevY = 0
#process.ctppsBeamParametersESSource.vtxStddevZ = 0

# undo CMS vertex shift
#process.ctppsBeamParametersESSource.vtxOffsetX45 = +0.2475 * 1E-1
#process.ctppsBeamParametersESSource.vtxOffsetY45 = -0.6924 * 1E-1
#process.ctppsBeamParametersESSource.vtxOffsetZ45 = -8.1100 * 1E-1


#########################
#        Triggers       #
#########################

process.load("DiffractiveForwardAnalysis.GammaGammaLeptonLepton.HLTFilter_cfi")
process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
process.hltFilter.HLTPaths = cms.vstring(
    'HLT_DoubleMu43NoFiltersNoVtx_*',
    'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_*',
    'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_*'
#    'HLT_DoubleEle33_CaloIdL_MW_v*',
#    'HLT_Ele27_HighEta_Ele20_Mass55_v*',
#    'HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v*',
)

#########################
#      Preskimming      #
#########################
# declare global tag
process.load("Configuration.StandardSequences.GeometryDB_cff") ## FIXME need to ensure that this is the good one                                     
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, "106X_dataRun2_testPPS_v1")
#process.GlobalTag = GlobalTag(process.GlobalTag, "auto:run2_mc");

#JH - for tests of 2018 alignment candidate
#from CalibPPS.ESProducers.ctppsRPAlignmentCorrectionsDataESSourceXML_cfi import *

"""
process.ctppsRPAlignmentCorrectionsDataESSourceXML = cms.ESSource("CTPPSRPAlignmentCorrectionsDataESSourceXML",
    verbosity = cms.untracked.uint32(0),

    MeasuredFiles = cms.vstring(),
    RealFiles = cms.vstring(),
    MisalignedFiles = cms.vstring()
)
"""
"""
process.ctppsRPAlignmentCorrectionsDataESSourceXML.RealFiles = cms.vstring(
  # internal pixel alignment
  "CalibPPS/ESProducers/data/alignment/RPixGeometryCorrections-2017-2018.xml",

  # global alignment of tracking RPs (strips and pixels)
  "CalibPPS/ESProducers/data/alignment/alignment_export_2019_05_09.1.xml",

  # alignment of timing RPs (diamonds and UFSDs)
  "CalibPPS/ESProducers/data/alignment/timing_RP_2017_preTS2_v2.xml",
  "CalibPPS/ESProducers/data/alignment/timing_RP_2017_postTS2_v2.xml",
  "CalibPPS/ESProducers/data/alignment/timing_RP_2018_v2.xml"
)

process.esPreferLocalAlignment = cms.ESPrefer("CTPPSRPAlignmentCorrectionsDataESSourceXML", "ctppsRPAlignmentCorrectionsDataESSourceXML")
"""

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")


# local RP reconstruction chain with standard settings
process.load("RecoCTPPS.Configuration.recoCTPPS_cff")

# load default alignment settings
process.load("CalibPPS.ESProducers.ctppsAlignment_cff")
# local RP reconstruction chain with standard settings
process.load("RecoCTPPS.Configuration.recoCTPPS_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "106X_dataRun2_v15")



# suppress local conditions sources
del process.ctppsRPAlignmentCorrectionsDataESSourceXML
del process.esPreferLocalAlignment

#del process.ctppsOpticalFunctionsESSource
#del process.esPreferLocalOptics

# get optics from a DB tag
from CondCore.CondDB.CondDB_cfi import *
process.CondDBOptics = CondDB.clone( connect = 'frontier://FrontierProd/CMS_CONDITIONS' )
process.PoolDBESSourceOptics = cms.ESSource("PoolDBESSource",
	process.CondDBOptics,
	DumpStat = cms.untracked.bool(False),
	toGet = cms.VPSet(cms.PSet(
		record = cms.string('CTPPSOpticsRcd'),
		tag = cms.string("PPSOpticalFunctions offline v4")
	)),
)

process.esPreferDBFileOptics = cms.ESPrefer("PoolDBESSource", "PoolDBESSourceOptics")

# get alignment from a DB tag
from CondCore.CondDB.CondDB_cfi import *
process.CondDBAlignment = CondDB.clone( connect = 'frontier://FrontierProd/CMS_CONDITIONS' )
process.PoolDBESSourceAlignment = cms.ESSource("PoolDBESSource",
	process.CondDBAlignment,
	#timetype = cms.untracked.string('runnumber'),
	toGet = cms.VPSet(cms.PSet(
		record = cms.string('RPRealAlignmentRecord'),
		tag = cms.string('CTPPSRPAlignment real offline v3')
	))
)

process.esPreferDBFileAlignment = cms.ESPrefer("PoolDBESSource", "PoolDBESSourceAlignment")

'''
# HepMC plotter
process.ctppsHepMCDistributionPlotter = cms.EDAnalyzer("CTPPSHepMCDistributionPlotter",
  tagHepMC = cms.InputTag("beamDivergenceVtxGenerator"),
  lhcInfoLabel = cms.string(""),
  #outputFile = cms.string("/afs/cern.ch/user/m/malvesga/work/ProtonRecon/archives/10_6_0/output/2017/MC/LPAIRmumuElastic_Fall17/output_HepMC.root")
  outputFile = cms.string("output_HepMC.root")
)

# XY distribution plotter
process.ctppsTrackDistributionPlotter = cms.EDAnalyzer("CTPPSTrackDistributionPlotter",
  tagTracks = cms.InputTag("ctppsLocalTrackLiteProducer"),
  #outputFile = cms.string("/afs/cern.ch/user/m/malvesga/work/ProtonRecon/archives/10_6_0/output/2017/MC/LPAIRmumuElastic_Fall17/output_track_xy.root")
  outputFile = cms.string("output_track_xy.root")
)
'''
process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.load("DiffractiveForwardAnalysis.GammaGammaLeptonLepton.GammaGammaLL_cfi")

process.ggll_aod.triggersList = process.hltFilter.HLTPaths
process.ggll_aod.leptonsType = cms.string('Muon')
#process.ggll_aod.leptonsType = cms.string('ElectronMuon')
#process.ggll_aod.leptonsType = cms.string('Electron')
process.ggll_aod.runOnMC = cms.bool(runOnMC)
process.ggll_aod.fetchProtons = cms.bool(True)
process.ggll_aod.saveExtraTracks = cms.bool(False)
process.ggll_aod.year = cms.string('2017MC')
process.ggll_aod.mcpufile = cms.string('PUHistos_mc.root')
process.ggll_aod.datapufile = cms.string('PUHistos_data.root')
process.ggll_aod.mcpupath = 'input_Event/N_TrueInteractions'

process.ggll_miniaod.triggersList = process.hltFilter.HLTPaths
process.ggll_miniaod.leptonsType = cms.string('Muon')
#process.ggll_miniaod.leptonsType = cms.string('ElectronMuon')
#process.ggll_miniaod.leptonsType = cms.string('Electron')
process.ggll_miniaod.runOnMC = cms.bool(runOnMC)
process.ggll_miniaod.fetchProtons = cms.bool(True)
process.ggll_miniaod.saveExtraTracks = cms.bool(False)
process.ggll_miniaod.year = cms.string('2017')
process.ggll_miniaod.mcpufile = cms.string('PUHistos_mc.root')
process.ggll_miniaod.datapufile = cms.string('PUHistos_data.root')
process.ggll_miniaod.mcpupath = 'input_Event/N_TrueInteractions'

# prepare the output file
# copiar o output depois de rodar o crab para a pasta /afs/cern.ch/user/m/malvesga/work/ProtonRecon/archives/10_6_0/output/2017/MC/LPAIRmumuElastic_Fall17/
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('output_data.root'),
    closeFileFast = cms.untracked.bool(True)
)
'''
#https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGenParticlePruner
process.prunedGenParticles = cms.EDProducer(
"GenParticlePruner",
src = cms.InputTag("genParticles"),
select = cms.vstring('drop *',
# for miniAOD matching
'keep status == 1')
)
'''
# processing path
if MINIAOD == False:
	process.p = cms.Path(
  		process.prunedGenParticles *
  		#process.dump *
  		process.beamDivergenceVtxGenerator *
  		process.ctppsDirectProtonSimulation *

  		process.reco_local  *
 
 		process.ctppsProtons *

 	 	#process.ctppsHepMCDistributionPlotter *
  		#process.ctppsTrackDistributionPlotter *

  		process.hltFilter *

  		process.ggll_aod
	)
else:
	process.p = cms.Path(
  		#process.dump *
  		#process.beamDivergenceVtxGenerator *
  		#process.ctppsDirectProtonSimulation *

  		#process.reco_local  *

  		#process.ctppsProtons *

  		#process.ctppsHepMCDistributionPlotter *
  		#process.ctppsTrackDistributionPlotter *

		process.totemRPUVPatternFinder *
		process.totemRPLocalTrackFitter *

#		process.ctppsDiamondRecHits *
#		process.ctppsDiamondLocalTracks *

		process.ctppsPixelLocalTracks *

		process.ctppsLocalTrackLiteProducer *

		process.ctppsProtons *
  		process.hltFilter *

  		process.ggll_miniaod
	)

#process.outpath = cms.EndPath(process.out, patAlgosToolsTask)
process.outpath = cms.EndPath(patAlgosToolsTask)


