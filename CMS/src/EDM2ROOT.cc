
#include <iostream>
#include <vector>

#include <DataFormats/MuonReco/interface/Muon.h>
#include <DataFormats/EgammaCandidates/interface/GsfElectron.h>

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

	// https://github.com/cms-cvs-history/DataFormats-EgammaCandidates/blob/master/interface/GsfElectron.h
	Handle<std::vector<reco::GsfElectron> > electronsHandle;
	iEvent.getByLabel("gsfElectrons", electronsHandle);
	const std::vector<reco::GsfElectron>* electrons = electronsHandle.product();
	
	std::cout << muons->size() << ", " << electrons->size() << std::endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
EDM2ROOT::beginJob()
{
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

