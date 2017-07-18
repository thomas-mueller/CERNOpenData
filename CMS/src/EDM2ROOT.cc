
#include <iostream>
#include <vector>

#include <CERNOpenData/CMS/interface/EDM2ROOT.h>


//
// constructors and destructor
//
EDM2ROOT::EDM2ROOT(const edm::ParameterSet& iConfig)

{
	//now do what ever initialization is needed

}


EDM2ROOT::~EDM2ROOT()
{
 
	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
EDM2ROOT::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;

	// https://github.com/cms-cvs-history/DataFormats-MuonReco/blob/master/interface/Muon.h
	Handle<std::vector<reco::Muon> > muonsHandle;
	iEvent.getByLabel("muons", muonsHandle);
	const std::vector<reco::Muon>* muons = muonsHandle.product();
	
	nMuons = muons->size();
	
	muon1Pt = muons->size() > 0 ? muons->at(0).p4().Pt() : 0.0;
	muon1Eta = muons->size() > 0 ? muons->at(0).p4().Eta() : 0.0;
	muon1Phi = muons->size() > 0 ? muons->at(0).p4().Phi() : 0.0;
	muon1Iso = muons->size() > 0 ? EDM2ROOT::pfIso(muons->at(0)) : 0.0;
	
	muon2Pt = muons->size() > 1 ? muons->at(1).p4().Pt() : 0.0;
	muon2Eta = muons->size() > 1 ? muons->at(1).p4().Eta() : 0.0;
	muon2Phi = muons->size() > 1 ? muons->at(1).p4().Phi() : 0.0;
	muon2Iso = muons->size() > 1 ? EDM2ROOT::pfIso(muons->at(1)) : 0.0;

	// https://github.com/cms-cvs-history/DataFormats-EgammaCandidates/blob/master/interface/GsfElectron.h
	Handle<std::vector<reco::GsfElectron> > electronsHandle;
	iEvent.getByLabel("gsfElectrons", electronsHandle);
	const std::vector<reco::GsfElectron>* electrons = electronsHandle.product();
	
	nElectrons = electrons->size();
	
	electron1Pt = electrons->size() > 0 ? electrons->at(0).p4().Pt() : 0.0;
	electron1Eta = electrons->size() > 0 ? electrons->at(0).p4().Eta() : 0.0;
	electron1Phi = electrons->size() > 0 ? electrons->at(0).p4().Phi() : 0.0;
	electron1Iso = electrons->size() > 0 ? EDM2ROOT::pfIso(electrons->at(0)) : 0.0;
	
	electron2Pt = electrons->size() > 1 ? electrons->at(1).p4().Pt() : 0.0;
	electron2Eta = electrons->size() > 1 ? electrons->at(1).p4().Eta() : 0.0;
	electron2Phi = electrons->size() > 1 ? electrons->at(1).p4().Phi() : 0.0;
	electron2Iso = electrons->size() > 1 ? EDM2ROOT::pfIso(electrons->at(1)) : 0.0;
	
	outputTree->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
EDM2ROOT::beginJob()
{
	outputTree = fileService->make<TTree>("events", "");
	
	outputTree->Branch("nMuons", &nMuons, "nMuons/I");
	
	outputTree->Branch("muon1Pt", &muon1Pt, "muon1Pt/F");
	outputTree->Branch("muon1Eta", &muon1Eta, "muon1Eta/F");
	outputTree->Branch("muon1Phi", &muon1Phi, "muon1Phi/F");
	outputTree->Branch("muon1Iso", &muon1Iso, "muon1Iso/F");
	
	outputTree->Branch("muon2Pt", &muon2Pt, "muon2Pt/F");
	outputTree->Branch("muon2Eta", &muon2Eta, "muon2Eta/F");
	outputTree->Branch("muon2Phi", &muon2Phi, "muon2Phi/F");
	outputTree->Branch("muon2Iso", &muon2Iso, "muon2Iso/F");
	
	outputTree->Branch("nElectrons", &nElectrons, "nElectrons/I");
	
	outputTree->Branch("electron1Pt", &electron1Pt, "electron1Pt/F");
	outputTree->Branch("electron1Eta", &electron1Eta, "electron1Eta/F");
	outputTree->Branch("electron1Phi", &electron1Phi, "electron1Phi/F");
	outputTree->Branch("electron1Iso", &electron1Iso, "electron1Iso/F");
	
	outputTree->Branch("electron2Pt", &electron2Pt, "electron2Pt/F");
	outputTree->Branch("electron2Eta", &electron2Eta, "electron2Eta/F");
	outputTree->Branch("electron2Phi", &electron2Phi, "electron2Phi/F");
	outputTree->Branch("electron2Iso", &electron2Iso, "electron2Iso/F");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EDM2ROOT::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
EDM2ROOT::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
EDM2ROOT::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
EDM2ROOT::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
EDM2ROOT::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
EDM2ROOT::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

float EDM2ROOT::pfIso(reco::Muon const& muon, float puFraction)
{
	reco::MuonPFIsolation iso = muon.pfIsolationR03();
	return iso.sumChargedHadronPt + std::max(0.0f, iso.sumNeutralHadronEt + iso.sumPhotonEt - puFraction * iso.sumPUPt);
}
float EDM2ROOT::pfIso(reco::GsfElectron const& electron, float puFraction)
{
	reco::GsfElectron::PflowIsolationVariables iso = electron.pfIsolationVariables();
	return iso.chargedHadronIso + std::max(0.0f, iso.neutralHadronIso + iso.photonIso - puFraction * 0.0f); // no delta beta correction
}

