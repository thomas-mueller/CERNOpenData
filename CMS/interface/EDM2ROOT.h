
#pragma once

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <DataFormats/MuonReco/interface/Muon.h>
#include <DataFormats/EgammaCandidates/interface/GsfElectron.h>

#include <TTree.h>

//
// class declaration
//

class EDM2ROOT : public edm::EDAnalyzer {
public:
	explicit EDM2ROOT(const edm::ParameterSet&);
	~EDM2ROOT();

	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
	virtual void beginJob() ;
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void endJob() ;

	virtual void beginRun(edm::Run const&, edm::EventSetup const&);
	virtual void endRun(edm::Run const&, edm::EventSetup const&);
	virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
	virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
	
	static float pfIso(reco::Muon const& muon, float puFraction=0.5);
	static float pfIso(reco::GsfElectron const& electron, float puFraction=0.5);

	// ----------member data ---------------------------
	edm::Service<TFileService> fileService;
	TTree* outputTree = nullptr;
	
	int nPV = 0;
	
	float pvX = 0.0;
	float pvY = 0.0;
	float pvZ = 0.0;
	
	int nMuons = 0;
	
	float muon1Pt = 0.0;
	float muon1Eta = 0.0;
	float muon1Phi = 0.0;
	float muon1Iso = 0.0;
	float muon1Dxy = 0.0;
	float muon1Dz = 0.0;
	
	float muon2Pt = 0.0;
	float muon2Eta = 0.0;
	float muon2Phi = 0.0;
	float muon2Iso = 0.0;
	float muon2Dxy = 0.0;
	float muon2Dz = 0.0;
	
	int nElectrons = 0;
	
	float electron1Pt = 0.0;
	float electron1Eta = 0.0;
	float electron1Phi = 0.0;
	float electron1Iso = 0.0;
	float electron1Dxy = 0.0;
	float electron1Dz = 0.0;
	
	float electron2Pt = 0.0;
	float electron2Eta = 0.0;
	float electron2Phi = 0.0;
	float electron2Iso = 0.0;
	float electron2Dxy = 0.0;
	float electron2Dz = 0.0;
};

//define this as a plug-in
DEFINE_FWK_MODULE(EDM2ROOT);
