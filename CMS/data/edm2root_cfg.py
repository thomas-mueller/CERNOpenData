import FWCore.ParameterSet.Config as cms

# http://opendata.cern.ch/record/32
#test_inputs = ["root://eospublic.cern.ch//eos/opendata/cms/Run2011A/SingleMu/AOD/12Oct2013-v1/10000/00082EAF-C03D-E311-8E53-003048F00B1C.root"]

# http://opendata.cern.ch/record/17
test_inputs = ["root://eospublic.cern.ch//eos/opendata/cms/Run2011A/DoubleMu/AOD/12Oct2013-v1/10000/000D143E-9535-E311-B88B-002618943934.root"]

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing("python")
options.register("input", test_inputs, VarParsing.multiplicity.list, VarParsing.varType.string, "Input files")
options.register("output", "output.root", VarParsing.multiplicity.singleton, VarParsing.varType.string, "Output file")
options.parseArguments()

process = cms.Process("EDM2ROOT")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
	# replace "myfile.root" with the source file you want to use
	fileNames = cms.untracked.vstring(*options.input)
)

process.TFileService = cms.Service("TFileService",
	fileName = cms.string(options.output),
	closeFileFast = cms.untracked.bool(True)
)

# https://twiki.cern.ch/twiki/bin/viewauth/CMS/TriggerResultsFilter#Use_for_Offline_analysis
# https://twiki.cern.ch/twiki/bin/view/Main/AndreHolznerCMSSW#How_do_I_select_events_which_pas
import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt
process.triggerResultsFilter = hlt.triggerResultsFilter.clone(
	hltResults = cms.InputTag("TriggerResults","","HLT"),
	triggerConditions = cms.vstring("HLT_Mu17_Mu8_v*", ),
	l1tResults = "",
	throw = cms.bool(True)
)

process.events = cms.EDAnalyzer("EDM2ROOT"
)

process.p = cms.Path(process.triggerResultsFilter + process.events)
