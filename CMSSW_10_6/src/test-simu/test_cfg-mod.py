import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Modifier_ctpps_2016_cff import ctpps_2016
process = cms.Process('CTPPSTestAcceptance', ctpps_2016)

runOnMC = True
useAOD = True

xangle = 120

# load common code
process.load("direct_simu_reco_cff")
from customisation_cff import *
#SetDefaults(process)
UseCrossingAngle(xangle, process)

#process.out = cms.OutputModule("PoolOutputModule",
#    fileName = cms.untracked.string('PATuple.root'),
#    outputCommands = cms.untracked.vstring(
#        'drop *',
#        'keep *_offline*PrimaryVertices*_*_*',
#        'keep *_selectedPatMuons*_*_*',
#        'keep *_*lectron*_*_*',
#        'keep *_selectedPatElectrons*_*_*',
#        'keep *_selectedPat*Photons*_*_*',
#        'keep *_selectedPatJets*_*_*',
#        'keep *_*MET*_*_*',
#        'keep *_*particleFlow*_*_*',
#        'keep *_*_*_*'
#    ),
#)

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
process.MessageLogger = cms.Service("MessageLogger",
  statistics = cms.untracked.vstring(),
  destinations = cms.untracked.vstring('cerr'),
  cerr = cms.untracked.PSet(
    threshold = cms.untracked.string('WARNING')
  )
)

# event source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/m/malvesga/work/ProtonRecon/archives/10_6_0/input/2017/MC/LPAIRmumuElastic_Fall17/GGToMuMu_Pt-50_Inel-El_13TeV-lpairAODSIM92X.root")
	 #fileNames = cms.untracked.vstring("")
)

# number of events
process.maxEvents = cms.untracked.PSet(
  #input = cms.untracked.int32(-1)
  input = cms.untracked.int32(1000)
)

# update settings of beam-smearing module
process.beamDivergenceVtxGenerator.src = cms.InputTag("")
process.beamDivergenceVtxGenerator.srcGenParticle = cms.VInputTag(
  cms.InputTag("genPUProtons", "genPUProtons"),
  cms.InputTag("prunedGenParticles")
)

# do not apply vertex smearing again
process.ctppsBeamParametersESSource.vtxStddevX = 0
process.ctppsBeamParametersESSource.vtxStddevY = 0
process.ctppsBeamParametersESSource.vtxStddevZ = 0

# undo CMS vertex shift
process.ctppsBeamParametersESSource.vtxOffsetX45 = +0.2475 * 1E-1
process.ctppsBeamParametersESSource.vtxOffsetY45 = -0.6924 * 1E-1
process.ctppsBeamParametersESSource.vtxOffsetZ45 = -8.1100 * 1E-1


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
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, "106X_dataRun2_testPPS_v1")
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:run2_mc");

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

# prepare the output file
# copiar o output depois de rodar o crab para a pasta /afs/cern.ch/user/m/malvesga/work/ProtonRecon/archives/10_6_0/output/2017/MC/LPAIRmumuElastic_Fall17/
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('output_xangle120.root'),
    closeFileFast = cms.untracked.bool(True)
)

#https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGenParticlePruner
process.prunedGenParticles = cms.EDProducer(
"GenParticlePruner",
src = cms.InputTag("genParticles"),
select = cms.vstring('drop *',
# for miniAOD matching
'keep status == 1')
)

# processing path
process.p = cms.Path(
  process.prunedGenParticles *
  #process.dump *
  process.beamDivergenceVtxGenerator *
  process.ctppsDirectProtonSimulation *

  process.reco_local  *
 
  process.ctppsProtons *

  process.ctppsHepMCDistributionPlotter *
  process.ctppsTrackDistributionPlotter *

  process.hltFilter *

  process.ggll_aod
)

#process.outpath = cms.EndPath(process.out, patAlgosToolsTask)
process.outpath = cms.EndPath(patAlgosToolsTask)

