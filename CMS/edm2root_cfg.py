import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'root://eospublic.cern.ch//eos/opendata/cms/Run2011A/DoubleMu/AOD/12Oct2013-v1/10000/000D143E-9535-E311-B88B-002618943934.root'
    )
)

process.TFileService = cms.Service("TFileService",
	fileName = cms.string("output.root"),
	closeFileFast = cms.untracked.bool(True)
)

process.events = cms.EDAnalyzer('EDM2ROOT'
)

process.p = cms.Path(process.events)
