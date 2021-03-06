//Package:    ME0SegmentAnalyzer
// Class:      ME0SegmentAnalyzer
// 
/**\class ME0SegmentAnalyzer ME0SegmentAnalyzer ME0SegmentAnalyzer/ME0SegmentAnalyzer/plugins/ME0SegmentAnalyzer.cc
 
 Description: [one line class summary]
 
 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  
//         Created:  Fri, 09 Oct 2015 10:34:53 GMT
// $Id$
//
//


// system include files
#include <memory>
#include <algorithm>
#include <iostream>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "RecoMuon/MuonIdentification/interface/ME0MuonSelector.h"
#include <DataFormats/MuonReco/interface/ME0Muon.h>
#include <DataFormats/MuonReco/interface/Muon.h>
#include <DataFormats/MuonReco/interface/ME0MuonCollection.h>
#include <DataFormats/GEMRecHit/interface/ME0RecHit.h>
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
#include "DataFormats/GEMRecHit/interface/ME0RecHitCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/GeometrySurface/interface/LocalError.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/Scalers/interface/DcsStatus.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
//Geom
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/GEMGeometry/interface/ME0Geometry.h"
#include <Geometry/GEMGeometry/interface/ME0EtaPartition.h>
#include <DataFormats/MuonDetId/interface/ME0DetId.h>

#include "Geometry/GEMGeometry/interface/GEMEtaPartition.h"
#include "Geometry/GEMGeometry/interface/GEMEtaPartitionSpecs.h"
#include "Geometry/CommonTopologies/interface/StripTopology.h"


#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "DataFormats/GEMDigi/interface/ME0DigiPreRecoCollection.h"



#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "RecoMuon/MuonIdentification/plugins/ME0MuonSelector.cc"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include <memory>
#include <vector>
#include <cmath>
#include "TLorentzVector.h"
//
// class declaration
//
using namespace std;
using namespace edm;
class ME0SegmentAnalyzer : public edm::EDAnalyzer {
public:
	explicit ME0SegmentAnalyzer(const edm::ParameterSet&);
	~ME0SegmentAnalyzer();
	void Initialize(); 
	
	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
	
	
private:
	virtual void beginJob() override;
	virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
	virtual void endJob() override;
	std::string wp_;
	double timeMin_;
	double timeMax_;
	double minEta_;
	double maxEta_;
	
	edm::Service<TFileService> fs;
	
	TH1F *hNEvZmm;  TH1F * hDPhi; TH1F *  hme0machtMuonPt;  TH1F *  hme0machtMuonEta;  TH1F *  hme0machtMuonPhi;  TH1F *  hme0machtMuonCharge;
	TH1F *  hNME0Time ;  TH1F *  hNME0RecHits; TH1F *  hPtRes ;  
	TH1F *  hSimPt; TH1F *  hSimEta;
	TH1F *  hNzmm;  TH1F *  hNEv;  TH1F *hNGenMu;  TH1F * hNME0Mu;  TH1F *   hNMatchME0Mu;
	
	TH2F *  hPtVSDphi;TH2F *  hPtVSDEta; TH2F *  hPVSDphi ;  TH2F *   hPtVSDX;  TH2F *   hPtVSDY;  TH2F *   hPtVSDXLocal;  TH2F *   hPtVSDYLocal; TH2F *  hPtResVSDPhi;TH2F *   hSimPtVSDphi;  
	
	
	TH1F *   hGenMuPt; TH1F *   hGenMuEta;
	TH1F *   hNumTight_Pt; TH1F *   hNumTight_Eta; TH1F *   hNumLoose_Pt; TH1F *   hNumLoose_Eta; TH1F *   hNumNoID_Eta; TH1F *   hNumNoID_Pt; 
	TH1F * hAbsDPhi ; TH1F * hAbsDEta;  TH1F * hDEta;
	TH1F *   hGenMass;  TH1F *   hRecoMass; TH1F *   hRecoMassIntime;	TH1F * 	hRecoMass_matchID;

	TH2F * hSimPtVSDeta;
	TH1F *   hSimDEta;
	TH1F *   hSimDPhi;
	
	TH1F * hSelectedSimTrack;
	TH1F * hGenMuonsME0;
	TH1F * hME0MuonsID; TH1F * hME0MuonsInMatchCone;
	
	TH1F * hNSimHitsME0;
	TH1F * hNRecHitsME0;
	TH1F * hRatioRecoToSimHits;
	TH1F * hNME0Segment;
	TH1F * hNBkgHitsME0;
	TH1F * hRecHitTime;
	
	TH1F * hNDigiMatchedRH;
	TH1F * hNPrompt;
	TH1F * hN_noPrompt;
	
	TH1F * 	hNPromptMuHit;
	TH1F * 	hNPromptNoMuHit;
	TH1F * 	hNPromptHit_pdgId;
	TH1F *  hME0SimTrackPdgID;
	
	 TH1F *  hSimElePtME0;			
	 TH1F *   hSimMuPtME0;
	 TH1F *   hSimPionPtME0;
	TH1F * 	hSimEleNHitsME0;
	TH1F * 	hSimMuonNHitsME0;
	TH1F * 	hSimPionNHitsME0; TH1F * hPdgIDCheck; 
	TH2F *  hMuonDigiDPhiVsPT; TH2F * hNoEleDigiDPhiVsPT;
	
	TH1F * hDRME0SimTrack;
	TH1F * hDRME0SimMuonEle;
	TH1F * hN_noEleHit;
	TH1F * hN_noPromptHit_pdgId;
	TH1F *	hSegmentComposition;
	TH1F * hNME0SegmentAfterDigiMatch;
	TH1F * hMuEleinME0Segm;
	TH1F * hMuEleOthersinME0Segm;
	TH1F * hMuOnlyinME0Segm;
	
	// virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
	//virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
	//virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
	//virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
	
	// ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ME0SegmentAnalyzer::ME0SegmentAnalyzer(const edm::ParameterSet& iConfig):
wp_(iConfig.getParameter<std::string>("wp")),
timeMin_(iConfig.getParameter<double>("timeMin")),
timeMax_(iConfig.getParameter<double>("timeMax")),
minEta_(iConfig.getParameter<double>("minEta")),
maxEta_(iConfig.getParameter<double>("maxEta"))

{
	
}


ME0SegmentAnalyzer::~ME0SegmentAnalyzer()
{
	
	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)
	
}

bool isSimMatched(edm::SimTrackContainer::const_iterator simTrack, edm::PSimHitContainer::const_iterator itHit)
{
	
	bool result = false;
	
	int trackId = simTrack->trackId();
	int trackId_sim = itHit->trackId();
	if(trackId == trackId_sim) result = true;
	
	//std::cout<<"ID: "<<trackId<<" "<<trackId_sim<<" "<<result<<std::endl;
	
	
	
	return result;
	
}


edm::PSimHitContainer isTrackMatched(SimTrackContainer::const_iterator simTrack, const Event & event, const EventSetup& eventSetup)
{
	edm::PSimHitContainer selectedME0Hits;
	
	edm::ESHandle<ME0Geometry> me0geom;
	eventSetup.get<MuonGeometryRecord>().get(me0geom);
	
	edm::Handle<edm::PSimHitContainer> ME0Hits;
	event.getByLabel(edm::InputTag("g4SimHits","MuonME0Hits"), ME0Hits);
	
	ESHandle<GlobalTrackingGeometry> theTrackingGeometry;
	eventSetup.get<GlobalTrackingGeometryRecord>().get(theTrackingGeometry);
	
	for (edm::PSimHitContainer::const_iterator itHit =  ME0Hits->begin(); itHit != ME0Hits->end(); ++itHit){
		
		DetId id = DetId(itHit->detUnitId());
		if (!(id.subdetId() == MuonSubdetId::ME0)) continue;
		if(itHit->particleType() != (*simTrack).type()) continue;
		
		bool result = isSimMatched(simTrack, itHit);
		if(result) selectedME0Hits.push_back(*itHit);
					
	}
	
//	std::cout<<"N simHit in ME0segm : "<<selectedME0Hits.size()<<std::endl;
	return selectedME0Hits;
	
}

struct MyME0Digi
{
    Int_t detId, particleType;
    Short_t layer;
//    Float_t x, y;
    Float_t g_eta, g_phi;
	Float_t tof;
	Float_t prompt;
  //  Float_t x_sim, y_sim;
  //  Float_t g_eta_sim, g_phi_sim, g_x_sim, g_y_sim, g_z_sim;
};

void
ME0SegmentAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	//Initialize();
	using namespace edm;
	
	edm::Handle<SimTrackContainer> simTracks;
	iEvent.getByLabel("g4SimHits",simTracks);

	edm::Handle <std::vector<reco::ME0Muon> > OurMuons;
	iEvent.getByLabel <std::vector<reco::ME0Muon> > ("me0SegmentMatching", OurMuons);
	
	edm::Handle<ME0SegmentCollection> me0Segments;
	iEvent.getByLabel("me0Segments", me0Segments);
	
	edm::Handle <reco::GenParticleCollection> genparticles;
	iEvent.getByLabel("genParticles",genparticles);
	
	edm::Handle <std::vector<reco::Muon> > muons;    
	iEvent.getByLabel("muons", muons ); 
	
	edm::Handle<ME0DigiPreRecoCollection> me0_digis;
	iEvent.getByLabel("simMuonME0Digis",  me0_digis); 
	
	edm::ESHandle<ME0Geometry> me0geom;
	iSetup.get<MuonGeometryRecord>().get(me0geom);
	const ME0Geometry* me0Geom;
	me0Geom= &*me0geom;

		
	/*
	 Run   = iEvent.id().run();
	 Event = iEvent.id().event();
	 Lumi  = iEvent.luminosityBlock();
	 Bunch = iEvent.bunchCrossing();
	 */
	
	std::cout<<"********************************************BeginEvent******************************************** "<<std::endl;
	std::vector<int> indexgenmu;
	hNEv->Fill(1);  
	
//	if(( iEvent.id().run()==1381 &&  iEvent.luminosityBlock()==277)) {
	///////////////////////////////////////////////////////////////////////////////////////////////////Loop over simTracks//////////////////////////////////////////////////////////////////////////////////////////
//	std::cout<<" me0DigiSize="<<me0_digis->size()<<std::endl;
	 
	
	SimTrackContainer::const_iterator simTrack;
	double numberOfSimTracks =0.;
	std::cout<<" num Simulated tracks: "<<simTracks->size()<<std::endl;
	std::vector<double> simHitPhi;
	std::vector<double> simHitEta;
	std::vector<int> numME0SimHits;
	SimTrackContainer ME0Tracks;
	for (simTrack = simTracks->begin(); simTrack != simTracks->end(); ++simTrack){
	
		//if (!(abs((*simTrack).type()) == 13)) continue; 
		//if ((*simTrack).noVertex()) continue;
		//if ((*simTrack).noGenpart()) continue;
		
		//cout<<"Sim pT: "<<(*simTrack).momentum().pt()<<endl;
		double simPt=(*simTrack).momentum().pt();
		
		//cout<<"Sim Eta: "<<(*simTrack).momentum().eta()<<endl;
		double simEta = (*simTrack).momentum().eta();
		
		//cout<<"Sim Phi: "<<(*simTrack).momentum().phi()<<endl;
		//double simPhi = (*simTrack).momentum().phi();
		
		if (abs(simEta) > maxEta_ || abs(simEta) < minEta_) continue;
			    
		edm::PSimHitContainer selME0SimHits = isTrackMatched(simTrack, iEvent , iSetup);
	
		//int ME0SimHitsize = selME0SimHits.size();
		//std::cout<<"# me0 sim hits="<< selME0SimHits.size() <<std::endl;
		
		if( selME0SimHits.size() ==0 ) continue;
	
		hME0SimTrackPdgID->Fill( fabs((*simTrack).type()) );
		hSimEta->Fill((*simTrack).momentum().eta());
		hSimPt->Fill((*simTrack).momentum().pt());
		
		if (fabs((*simTrack).type())==11){ hSimElePtME0->Fill(simPt);	hSimEleNHitsME0->Fill(selME0SimHits.size());	}
		if (fabs((*simTrack).type())==13) {hSimMuPtME0->Fill(simPt);     hSimMuonNHitsME0->Fill(selME0SimHits.size());}
		if (fabs((*simTrack).type())==211) {hSimPionPtME0->Fill(simPt);  hSimPionNHitsME0->Fill(selME0SimHits.size());} 
		
		ME0Tracks.push_back(*simTrack);
		numberOfSimTracks++;
		std::cout<<"TrackID="<<simTrack->trackId()<<" track type="<<(*simTrack).type()<<"# me0 sim hits="<< selME0SimHits.size() <<" simPt="<<simPt<<std::endl;
		simHitPhi.clear();
		simHitEta.clear();
		int selhitcounter =0;
		
		
		for (edm::PSimHitContainer::const_iterator itHit =  selME0SimHits.begin(); itHit != selME0SimHits.end(); ++itHit){
			ME0DetId idme0 = ME0DetId(itHit->detUnitId());	
			int layer_sim = idme0.layer();		
			LocalPoint lp = itHit->entryPoint();
			GlobalPoint hitGP_sim( me0geom->idToDet(itHit->detUnitId())->surface().toGlobal(lp));		
			simHitPhi.push_back(hitGP_sim.phi());
			simHitEta.push_back(hitGP_sim.eta());
			selhitcounter	++;
			std::cout<<" simHit eta="<<hitGP_sim.eta()<<" phi="<<hitGP_sim.phi()<<" simHit detID="<<idme0<<" layer sim="<<layer_sim<<" X="<<hitGP_sim.x()<<" trackID="<<itHit->trackId()<<std::endl;
		}
		numME0SimHits.push_back(selhitcounter);
		int sizeSimPhi = simHitPhi.size()-1;
		double SimDeltaPhi = TMath::Abs( simHitPhi[0] - simHitPhi[sizeSimPhi] );
		double SimDeltaEta= TMath::Abs( simHitEta[0] - simHitEta[sizeSimPhi] );
		//cout<<"Track:"<<simTrack->trackId()<<" SimDphi="<<SimDeltaPhi<<" pT="<<simPt<<endl;
		hSimPtVSDphi->Fill(SimDeltaPhi, simPt);
		hSimPtVSDeta->Fill(SimDeltaEta, simPt);
		hSimDEta->Fill( simHitEta[0] - simHitEta[sizeSimPhi]);
		hSimDPhi->Fill( simHitPhi[0] - simHitPhi[sizeSimPhi]);
		
	}
	std::cout<<" Num simTrack in ME0  "<<numberOfSimTracks<<" ME0Track.size()="<<ME0Tracks.size()<<" Num me0 segm="<<me0Segments->size()<<std::endl;
	if (ME0Tracks.size()>0) hSelectedSimTrack->Fill(ME0Tracks.size());
	if (me0Segments->size()>0) hNME0Segment->Fill(me0Segments->size());
	
	
		for(uint k=0; k<ME0Tracks.size(); k++){
				for(uint r=k+1; r<ME0Tracks.size(); r++){
					double DRSimTrack=TMath::Sqrt( (ME0Tracks.at(k).momentum().eta() - ME0Tracks.at(r).momentum().eta())*(ME0Tracks.at(k).momentum().eta() - ME0Tracks.at(r).momentum().eta()) + (ME0Tracks.at(k).momentum().phi() - ME0Tracks.at(r).momentum().phi())*(ME0Tracks.at(k).momentum().phi() - ME0Tracks.at(r).momentum().phi()) ) ;
					hDRME0SimTrack->Fill(DRSimTrack);
					if((fabs(ME0Tracks.at(k).type())==13 && fabs(ME0Tracks.at(r).type())==11) || (fabs(ME0Tracks.at(r).type())==13 && fabs(ME0Tracks.at(k).type())==11)) {
							//std::cout<<" me0Track="<<k<<" pdgID="<<ME0Tracks.at(k).type()<<" me0Track="<<r<<" pdgID="<<ME0Tracks.at(r).type()<<" DR="<<DRSimTrack<<std::endl;
							hDRME0SimMuonEle->Fill(DRSimTrack);
					}
				}
		}

		//////////////////////////////////////////////////////////////////////////////////////////Loop over gen particles//////////////////////////////////////////////////////////////////////////////////////////
	
		
		for(unsigned int i = 0; i < genparticles->size();i++) {
		if((abs(genparticles->at(i).pdgId()) == 13) && (genparticles->at(i).status() == 1) && (genparticles->at(i).numberOfMothers() > 0)) {
			
			if(fabs(genparticles->at(i).mother()->pdgId()) == 23) {
				indexgenmu.push_back(i); 
				
			}
			else if(abs(genparticles->at(i).pdgId()) == abs(genparticles->at(i).mother()->pdgId())) {
				
				if(genparticles->at(i).mother()->numberOfMothers() > 0) {
					
					if(abs(genparticles->at(i).mother()->mother()->pdgId()) == 23) {
						indexgenmu.push_back(i); }
				}
				
				if(genparticles->at(i).mother()->mother()->numberOfMothers() > 0) {
					
					if(abs(genparticles->at(i).mother()->mother()->mother()->pdgId()) == 23) {
						indexgenmu.push_back(i);}
				}
				
				if(genparticles->at(i).mother()->mother()->mother() ->numberOfMothers() > 0) {
					
					if(abs(genparticles->at(i).mother()->mother()->mother()->mother()->pdgId()) == 23 || fabs(genparticles->at(i).mother()->pdgId()) == 22) {
					indexgenmu.push_back(i);}
					
				}
			}//genealogia
		}//mu status 1
	}//filtro eventi
	
	std::cout<< "N gen muon " << indexgenmu.size() << std::endl;
	std::cout<< "N me0 muon " << OurMuons->size() << std::endl;
	
	
	int counterZmm =0;
	if (indexgenmu.size()>0) {counterZmm ++; hNzmm->Fill(1);}
	
	std::vector<int>  indexGenMuInME0;
	std::vector<int>  indexGenMuElseWhere;
	std::vector<int>  indexRecoMuElseWhere;
	
	for(uint i =0; i<indexgenmu.size(); i++){
		std::cout<<i<<" particle= "<<genparticles->at(indexgenmu[i]).pdgId()<<" status="<<genparticles->at(indexgenmu[i]).status()<<" eta="<<genparticles->at(indexgenmu[i]).eta()<<" phi="<<genparticles->at(indexgenmu[i]).phi()<<" pt="<<genparticles->at(indexgenmu[i]).pt()<<std::endl;
		if((abs(genparticles->at(indexgenmu[i]).eta())<maxEta_ ) && ( (genparticles->at(indexgenmu[i]).eta() > minEta_ )||(genparticles->at(indexgenmu[i]).eta()< (-minEta_ )) )  ){
			indexGenMuInME0.push_back(indexgenmu[i]);
			//std::cout<<i<<" particle= "<<genparticles->at(indexgenmu[i]).pdgId()<<" status="<<genparticles->at(indexgenmu[i]).status()<<" eta="<<genparticles->at(indexgenmu[i]).eta()<<" phi="<<genparticles->at(indexgenmu[i]).phi()<<" pt="<<genparticles->at(indexgenmu[i]).pt()<<std::endl;
			if(genparticles->at(indexgenmu[i]).pt()>5) hGenMuEta->Fill( abs(genparticles->at(indexgenmu[i]).eta())  );
			hGenMuPt->Fill( abs(genparticles->at(indexgenmu[i]).pt())  );
		}else{
			indexGenMuElseWhere.push_back(indexgenmu[i]);
		}
	}
	hGenMuonsME0->Fill(indexGenMuInME0.size());
	std::cout<< "N gen muon in me0 " << indexGenMuInME0.size() <<""<< std::endl;
	TLorentzVector genmu1, genmu2, genZ;
	TLorentzVector recomu1, recomu2, recoZ;
	TLorentzVector recomu1Intime, recomu2Intime, recoZIntime;
	
	if ( indexGenMuInME0.size() ==2){
		genmu1.SetPtEtaPhiM(genparticles->at(indexGenMuInME0[0]).pt(),genparticles->at(indexGenMuInME0[0]).eta(), genparticles->at(indexGenMuInME0[0]).phi(), 0.105   );
		genmu2.SetPtEtaPhiM(genparticles->at(indexGenMuInME0[1]).pt(),genparticles->at(indexGenMuInME0[1]).eta(), genparticles->at(indexGenMuInME0[1]).phi(), 0.105   );
		genZ = genmu1 +genmu2;
		//std::cout<<" gen pt1="<<genmu1.Pt()<<" eta="<<genmu1.Eta()<<std::endl;
		//std::cout<<" gen pt2="<<genmu2.Pt()<<" eta="<<genmu2.Eta()<<std::endl;
		hGenMass->Fill(genZ.M());
		}
		
	hNGenMu->Fill(indexgenmu.size());
	hNME0Mu->Fill(OurMuons->size());
	
	unsigned int k = 0;
	std::vector<double>   me0SegAbsDPhi;  std::vector<double>   me0SegDPhi;
	std::vector<double>   me0SegAbsDEta;  std::vector<double>   me0SegDEta;
	std::vector<int>  idxtmpreco;
	std::vector<uint>  idxtmpgen;
	
	//find all the me0 muon next to the genMuon in DR<0.1
	for ( std::vector<reco::ME0Muon>::const_iterator thisMuon = OurMuons->begin(); thisMuon != OurMuons->end(); ++thisMuon, ++k){
		
		for(unsigned int i = 0; i<indexGenMuInME0.size(); i++){
			int m =indexGenMuInME0.at(i);
			// std::cout<<i<<" particle= "<<genparticles->at(m).pdgId()<<" status="<<genparticles->at(m).status()<<"  pt= "<<genparticles->at(m).pt()<<" eta="<<genparticles->at(m).eta()<<std::endl;
			double dr= reco::deltaR(genparticles->at(m),*thisMuon);
			if(dr < 0.25) {
				idxtmpreco.push_back(k);
				idxtmpgen.push_back(m);
				// std::cout<<" DR genmu, me0mu "<< dr <<std::endl;
			}
			
		}//dr gen particle
		
	}//me0muon loop
	
	hME0MuonsInMatchCone->Fill(idxtmpreco.size());
	//std::cout<<" genmu in matching cone   "<<indexgenmu.size()<<" recomu in matching cone  "<<idxtmpreco.size()<<std::endl;
	
	//find the nearest me0 muon to the genMu and double-check that dist<0.1
	std::vector<int> minDRgen;
	std::vector<int> minDRreco;
	std::vector<int> bkgidx;
	for(uint k =0; k<indexgenmu.size(); k++){
		double drprova = 5;
		int idxprovagen =-99;
		int idxprovareco =-99;
		
		for(uint i =0; i<idxtmpreco.size(); i++){
			double drnew= reco::deltaR(genparticles->at(indexgenmu[k]),OurMuons->at(idxtmpreco[i]));
			//std::cout<<"gen idx="<<indexgenmu.at(k)<<"  reco idx="<<idxtmpreco.at(i)<<" DR matched mu  "<<drnew<<std::endl;
			if(drnew<drprova){
				drprova = drnew;
				idxprovagen = indexgenmu.at(k);
				idxprovareco = idxtmpreco.at(i);
				//std::cout<<" drprova "<<drprova<<" idx reco "<<idxprovareco<<"  idxgen "<<idxprovagen<<std::endl;
				
			}
		}
		//std::cout<<" DR MINIMO DELLE MIE PALLE "<< drprova<<" idx gen "<<idxprovagen<<" idx reco  "<<idxprovareco<<std::endl;
		if(drprova<0.25){
			minDRreco.push_back(idxprovareco);
			minDRgen.push_back(idxprovagen);
		}
		
	}	    
	
	
	///verify matched muons with minDR
	std::cout<<"N me0 matched muon " <<  minDRreco.size() << std::endl;
	hNMatchME0Mu->Fill(minDRreco.size());
	
	////////////////////////////////////////////////////////////////Loop on me0 matched muons////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<int> idxMatchME0id;
	std::vector<int> numME0RecHits;
	
	std::vector<MyME0Digi> me0DigiVector;
	for(unsigned int m=0;m< minDRreco.size();m++ ){

		int me0idx =  minDRreco.at(m);
		
		bool isLoose = muon::isGoodMuon(me0geom, OurMuons->at(me0idx), muon::Loose);
		bool isTight = muon::isGoodMuon(me0geom, OurMuons->at(me0idx), muon::Tight);
		
		bool IDwp =   (wp_ == "loose") ? isLoose : isTight;
		
		if (!IDwp) continue;
		idxMatchME0id.push_back(me0idx);
	
		
		hme0machtMuonPt->Fill(OurMuons->at(me0idx).pt());	
		hme0machtMuonEta->Fill(OurMuons->at(me0idx).eta());	
		hme0machtMuonPhi->Fill(OurMuons->at(me0idx).phi());	
		hme0machtMuonCharge->Fill(OurMuons->at(me0idx).charge());	
		//int SegId=OurMuons->at(me0idx).me0segid();
		//std::cout<<" me0muon pt="<<OurMuons->at(me0idx).pt()<<" me0 mu eta "<<OurMuons->at(me0idx).eta()<<std::endl;
		//ME0DetId id = (OurMuons->at(me0idx).me0segment()).me0DetId();
		//std::cout <<" Original ME0DetID "<<id<<std::endl;
		auto me0rhs =  (OurMuons->at(me0idx).me0segment()).specificRecHits();
		
		hNME0Time->Fill((OurMuons->at(me0idx).me0segment()).time());
		hNME0RecHits->Fill(me0rhs.size());
		//numME0RecHits.push_back(me0rhs.size());
		
		//for each segment, loop over the rechits
		int  hitCounter=0;
		std::vector<double>   me0RHPhi;
		std::vector<double>   me0RHEta;
		std::vector<double>   me0RHX;
		std::vector<double>   me0RHY;
		std::vector<double>   me0RHXlocal;
		std::vector<double>   me0RHYlocal;
		std::vector<double>   me0RHPhiMuonOnly, me0RHPhiNoEle;
		std::vector<int> Nrechit; 
		std::vector<int> NPromptHit; 
		std::vector<int> N_noPromptHit; 
		std::vector<int> NBkgHit; 
		std::vector<int> NPromptMuHit, N_noEleHit;
		std::vector<int> NPromptNoMuHit, NPromptNoMuHit_pdgId, NMuAllHit, NEleAllHit , NOtherAllHit;
		
		MyME0Digi me0Digi_tmp;
		me0DigiVector.clear();
		for (auto rh = me0rhs.begin(); rh!= me0rhs.end(); rh++){
		
			hitCounter++;
			auto rhLP = rh->localPosition();
			double localX = rhLP.x();
			double localY = rhLP.y();
			
			auto me0id = rh->me0Id();
				
			auto rhr = me0Geom->etaPartition(me0id);
			auto rhGP = rhr->toGlobal(rhLP);
			double globalEta = rhGP.eta();
			double globalPhi = rhGP.phi();
			double globalX = rhGP.x();
			double globalY = rhGP.y();

			//auto rhtime = rh->TOF();
			//std::cout<< hitCounter<<" rechit global phi="<< globalPhi<<" global eta="<<globalEta<<" global x="<<globalX<<" global Y="<<globalY<<" tof="<<rh->tof()<<" rechit layer "<< me0id.layer()<<std::endl;
			
				
			//std::cout<< hitCounter<<" rechit local  x="<< rhLP.x() <<" local y="<< rhLP.y()<<"layer  "<< me0id.layer()<<<std::endl;
			me0RHPhi.push_back(globalPhi);
			me0RHEta.push_back(globalEta);
			
			me0RHX.push_back(globalX);
			me0RHY.push_back(globalY);
		
			me0RHXlocal.push_back(localX);
			me0RHYlocal.push_back(localY);
			//hRecHitTime->Fill(rh->tof());
				
			
			for(ME0DigiPreRecoCollection::DigiRangeIterator cItr = me0_digis->begin(); cItr != me0_digis->end(); ++cItr){
				
				ME0DetId id = (*cItr).first;
				//	me0_digi_.detId = id();
				//   me0_digi_.region = (Short_t) id.region();
				//   me0_digi_.ring = 0;
				//   me0_digi_.station = 0;
				Short_t  me0_digiLayer =  id.layer();
				
				const GeomDet* gdet = me0Geom->idToDet(id);
				const BoundPlane & surface = gdet->surface();
				//std::cout<<" id= "<<id()<<std::endl;
				
				ME0DigiPreRecoCollection::const_iterator digiItr;
				//loop over digis of given roll
				for (digiItr = (*cItr ).second.first; digiItr != (*cItr ).second.second; ++digiItr)
				{
					
					LocalPoint lp(digiItr->x(), digiItr->y(), 0);
					GlobalPoint gp = surface.toGlobal(lp);
					Float_t me0_digiEta = gp.eta();
					Float_t me0_digiPhi = gp.phi();
					Float_t me0_digiX = gp.x();
					Float_t me0_digiY = gp.y();
					
					//std::vector<int> NBkgHit; 
					
					if(globalX == me0_digiX && globalY == me0_digiY && me0_digiLayer==me0id.layer()){ 
					  std::cout<<" DIGI global phi "<<me0_digiPhi<<" global eta "<<me0_digiEta<<" global X "<< me0_digiX << " global Y "<< me0_digiY  <<" layer "<<me0_digiLayer<<" pdg="<<digiItr->pdgid()<<" is prompt? "<<digiItr->prompt()<<"  tof="<<digiItr->tof()<<std::endl;
						me0Digi_tmp.particleType=digiItr->pdgid();
						me0Digi_tmp.layer =me0_digiLayer;
						me0Digi_tmp.g_eta=me0_digiEta;
						me0Digi_tmp.g_phi=me0_digiPhi;
						me0Digi_tmp.tof=digiItr->tof();
						me0Digi_tmp.prompt=digiItr->prompt();
						

						
						Nrechit.push_back(1);
						
						if(TMath::Abs( digiItr->pdgid())==13) NMuAllHit.push_back(1);
						if(TMath::Abs( digiItr->pdgid())==11) NEleAllHit.push_back(1);
						if(TMath::Abs( digiItr->pdgid())>200) NOtherAllHit.push_back(1);
						
						if(digiItr->prompt()==0){ 
							N_noPromptHit.push_back(1);
							hN_noPromptHit_pdgId->Fill(digiItr->pdgid()); 
						}
						if(digiItr->prompt()==1){
							NPromptHit.push_back(1);
							hNPromptHit_pdgId->Fill(fabs(digiItr->pdgid()));
							if(TMath::Abs( digiItr->pdgid())==13){
								NPromptMuHit.push_back(1); 
								me0RHPhiMuonOnly.push_back(me0_digiPhi);
							}
						if(TMath::Abs( digiItr->pdgid())!=13) {
							NPromptNoMuHit.push_back(1);
							NPromptNoMuHit_pdgId.push_back(digiItr->pdgid());
						}
						if(TMath::Abs( digiItr->pdgid())!=11){
							me0RHPhiNoEle.push_back(me0_digiPhi);
							hPdgIDCheck->Fill(digiItr->pdgid());
							N_noEleHit.push_back(1);
						}
						}
					}//DIGI MATCHED WITH RH
				}
			}//loop over digi
			me0DigiVector.push_back(me0Digi_tmp);
		}//loop over rechit
		std::cout<<"---------digiVecSize "<<me0DigiVector.size()<<std::endl;
		if(Nrechit.size()) hNME0SegmentAfterDigiMatch->Fill(1);
		if((NMuAllHit.size()>0) &&  (NEleAllHit.size()>0)  && (NOtherAllHit.size()==0) ) {hSegmentComposition->SetBinContent(1,1); hMuEleinME0Segm->Fill(1);}
		if((NMuAllHit.size()>0) &&  (NEleAllHit.size()>0)  && (NOtherAllHit.size()>0)  ) {hSegmentComposition->SetBinContent(2,1); hMuEleOthersinME0Segm->Fill(1);}
		if((NMuAllHit.size()>0) &&  (NEleAllHit.size()==0) && (NOtherAllHit.size()==0) ) {hSegmentComposition->SetBinContent(3,1); hMuOnlyinME0Segm->Fill(1);}
	//	std::cout<<" NRH="<<Nrechit.size()<<" nPrompt="<<NPromptHit.size()<<" nBkg="<<N_noPromptHit.size()<<" muHit="<<NPromptMuHit.size()<<" no mu prompt hit="<<NPromptNoMuHit.size()<<"MuonRH DPhi="<<fabs(me0RHPhiMuonOnly[0]-me0RHPhiMuonOnly[me0RHPhiMuonOnly.size()-1])<<endl;
		
		hNDigiMatchedRH->Fill(Nrechit.size());
		hNPrompt->Fill(NPromptHit.size());
		hN_noPrompt->Fill(N_noPromptHit.size());
		hNPromptMuHit->Fill(NPromptMuHit.size());
		hNPromptNoMuHit->Fill(NPromptNoMuHit.size());
		hN_noEleHit->Fill(N_noEleHit.size());
		hMuonDigiDPhiVsPT->Fill(fabs(me0RHPhiMuonOnly[0]-me0RHPhiMuonOnly[me0RHPhiMuonOnly.size()-1]), genparticles->at(minDRgen[m]).pt());
		hNoEleDigiDPhiVsPT->Fill(fabs(me0RHPhiNoEle[0]-me0RHPhiNoEle[me0RHPhiMuonOnly.size()-1]), genparticles->at(minDRgen[m]).pt());
		
		
		numME0RecHits.push_back(hitCounter);
		std::vector<double> simHitPhiForMatch;
		
			
		for (SimTrackContainer::const_iterator me0it = ME0Tracks.begin(); me0it  != ME0Tracks.end(); ++me0it ){
			edm::PSimHitContainer selME0SimHitsforMatch = isTrackMatched(me0it, iEvent , iSetup);
		 
			if( selME0SimHitsforMatch.size() ==0 ) continue;
			simHitPhiForMatch.clear();
		
			for (edm::PSimHitContainer::const_iterator itHit =  selME0SimHitsforMatch.begin(); itHit != selME0SimHitsforMatch.end(); ++itHit){
				//ME0DetId idme0 = ME0DetId(itHit->detUnitId());	
				//int layer_sim = idme0.layer();		
				LocalPoint lp = itHit->entryPoint();
				GlobalPoint hitGP_sim( me0geom->idToDet( itHit->detUnitId())->surface().toGlobal(lp));		
				simHitPhiForMatch.push_back(hitGP_sim.phi());
				}
		 
		}
				
		hNSimHitsME0->Fill(simHitPhiForMatch.size());
		hNRecHitsME0->Fill(me0rhs.size());
		hNBkgHitsME0->Fill( (me0rhs.size() -  simHitPhiForMatch.size()));
		
	
	}
	
//fine loop me0 muon matchati

//	std::cout<<"------------------# me0 matched muons with ID="<<idxMatchME0id.size()<<std::endl;
	
	hME0MuonsID->Fill(idxMatchME0id.size());
	hNEvZmm->Fill(counterZmm); 
//	}
	}



// ------------ method called once each job just before starting event loop  ------------
void 
ME0SegmentAnalyzer::beginJob()
{
	hNEvZmm = fs->make<TH1F>("hNEvZmm","hNEvZmm",10,0,10); 
	hNSimHitsME0= fs->make<TH1F>("hNSimHitsME0","hNSimHitsME0",20,0,20); 
	hNRecHitsME0= fs->make<TH1F>("hNRecHitsME0","hNRecHitsME0",100,0,100);
	hNBkgHitsME0= fs->make<TH1F>("hNBkgHitsME0","hNBkgHitsME0",60,-10,50);
	
	hNDigiMatchedRH= fs->make<TH1F>("hNDigiMatchedRH","hNDigiMatchedRH",21,-0.5,20.5);
	hNPrompt= fs->make<TH1F>("hNPrompt","hNPrompt",21,-0.5,20.5);
	hN_noPrompt= fs->make<TH1F>("hN_noPrompt","hN_noPrompt",21,-0.5,20.5);
	
	hRatioRecoToSimHits= fs->make<TH1F>("hRatioRecoToSimHits","hRatioRecoToSimHits",1000,0,100);
	
	hNPromptMuHit= fs->make<TH1F>("hNPromptMuHit","hNPromptMuHit",21,-0.5,20.5);
	hNPromptNoMuHit= fs->make<TH1F>("hNPromptNoMuHit","hNPromptNoMuHit",21,-0.5,20.5);
	hNPromptHit_pdgId= fs->make<TH1F>("hNPromptHit_pdgId","hNPromptHit_pdgId",3001,0,3000.5);
	hN_noPromptHit_pdgId= fs->make<TH1F>("hN_noPromptHit_pdgId","hN_noPromptHit_pdgId",3001,0,3000.5);
	hN_noEleHit= fs->make<TH1F>("hN_noEleHit","hN_noEleHit",21,-0.5,20.5);
	
	hSimEta  = fs->make<TH1F>("hSimEta","hSimEta",100,-4,4);  
	hSimPt  = fs->make<TH1F>("hSimPt","hSimPt",200, 0,200);  
	hPtVSDphi = fs->make<TH2F>("hPtVSDphi","hPtVSDphi",5000, 0, 0.05 , 200,0,200); 
	hSimPtVSDphi = fs->make<TH2F>("hSimPtVSDphi","hSimPtVSDphi",5000, 0, 0.05 , 200,0,200); 
	hSimPtVSDeta = fs->make<TH2F>("hSimPtVSDeta","hSimPtVSDeta",10000, 0, 0.1 , 200,0,200); 
	hSimDEta = fs->make<TH1F>("hSimDEta","hSimDEta",1000,-0.5,0.5);  
	hSimDPhi = fs->make<TH1F>("hSimDPhi","hSimDPhi",1000,-0.5,0.5);  
 
	hMuonDigiDPhiVsPT= fs->make<TH2F>("hMuonDigiDPhiVsPT","hMuonDigiDPhiVsPT", 5000, 0, 0.05 , 200,0,200); 
	hNoEleDigiDPhiVsPT= fs->make<TH2F>("hNoEleDigiDPhiVsPT","hNoEleDigiDPhiVsPT", 5000, 0, 0.05 , 200,0,200); 
	
	hAbsDPhi = fs->make<TH1F>("hAbsDPhi","hAbsDPhi",1000,0.,0.5);  
	hAbsDEta = fs->make<TH1F>("hAbsDEta","hAbsDEta",1000,0.,0.5);  
	hDEta = fs->make<TH1F>("hDEta","hDEta",1000,-0.5,0.5);  
	hDPhi = fs->make<TH1F>("hDPhi","hDPhi",1000,-0.1,0.1);  
	hPtVSDEta = fs->make<TH2F>("hPtVSDeta","hPtVSDeta",5000, 0, 0.1 , 200,0,200);
	
	
	hme0machtMuonPt = fs->make<TH1F>("hme0machtMuonPt","hme0machtMuonPt",200,0,200);  
	hme0machtMuonEta= fs->make<TH1F>("hme0machtMuonEta","hme0machtMuonEta",200,-4,4);  
	hme0machtMuonPhi= fs->make<TH1F>("hme0machtMuonPhi","hme0machtMuonPhi",200,-4,4);  
	hme0machtMuonCharge= fs->make<TH1F>("hme0machtMuonCharge","hme0machtMuonCharge",10,-5,5);  
	hNME0Time = fs->make<TH1F>("hNME0Time","hNME0Time",300,0,300);  
	hNME0RecHits = fs->make<TH1F>("hNME0RecHits","hNME0RecHits",100,0,100); 
		
	hNzmm  = fs->make<TH1F>("hNzmm","hNzmm",10,0,10); 
	hNEv  = fs->make<TH1F>("hNEv","hNEv",10,0,10); 
	hNGenMu = fs->make<TH1F>("hNGenMu","hNGenMu",10,0,10); 
	hNME0Mu = fs->make<TH1F>("hNME0Mu","hNME0Mu",10,0,10);
	hNMatchME0Mu = fs->make<TH1F>("hNMatchME0Mu","hNMatchME0Mu",10,0,10);
	
	hPVSDphi  = fs->make<TH2F>("hPVSDPhi","hPVSDPhi",1000, 0, 0.01 , 200,0,200); 

	
	hPtVSDX = fs->make<TH2F>("hPtVSDX","hPtVSDX",1000, 0, 10 , 200,0,200); 
	hPtVSDY = fs->make<TH2F>("hPtVSDY","hPtVSDY",1000, 0, 10 , 200,0,200); 
	
	
	hPtVSDXLocal = fs->make<TH2F>("hPtVSDXLocal","hPtVSDXLocal",1000, 0, 10 , 200,0,200); 
	hPtVSDYLocal =  fs->make<TH2F>("hPtVSDYLocal","hPtVSDYLocal",1000, 0, 10 , 200,0,200);
	
	
		
	hGenMuPt = fs->make<TH1F>("hGenMuPt","hGenMuPt",200,0,200);
	hGenMuEta = fs->make<TH1F>("hGenMuEta","hGenMuEta",200,0,4);
	
	hNumTight_Pt = fs->make<TH1F>("hNumTight_Pt","hNumTight_Pt",200,0,200);
	hNumTight_Eta = fs->make<TH1F>("hNumTight_Eta","hNumTight_Eta",200,0,4);
	hNumLoose_Pt = fs->make<TH1F>("hNumLoose_Pt","hNumLoose_Pt",200,0,200);
	hNumLoose_Eta = fs->make<TH1F>("hNumLoose_Eta","hNumLoose_Eta",200,0,4);
	hNumNoID_Eta = fs->make<TH1F>("hNumNoID_Eta","hNumNoID_Eta",200,0,4);
	hNumNoID_Pt = fs->make<TH1F>("hNumNoID_Pt","hNumNoID_Pt",200,0,200);
	
	hGenMass =  fs->make<TH1F>("hGenMass","hGenMass",200,0,200);
	hRecoMass =  fs->make<TH1F>("hRecoMass","hRecoMass",200,0,200);
	hRecoMassIntime =  fs->make<TH1F>("hRecoMassIntime","hRecoMassIntime",200,0,200);
	hRecoMass_matchID = fs->make<TH1F>("hRecoMass_matchID","hRecoMass_matchID",200,0,200);
	
	hSelectedSimTrack =  fs->make<TH1F>("hSelectedSimTrack","hSelectedSimTrack",20,0,20);
	hNME0Segment =  fs->make<TH1F>("hNME0Segment","hNME0Segment ",20,0,20);
	hGenMuonsME0= fs->make<TH1F>("hGenMuonsME0","hGenMuonsME0",20,0,20);
	hME0MuonsInMatchCone = fs->make<TH1F>("hME0MuonsInMatchCone","hME0MuonsInMatchCone",20,0,20);
	hME0MuonsID = fs->make<TH1F>("hME0MuonsID","hME0MuonsID",20,0,20);
	hME0SimTrackPdgID = fs->make<TH1F>("hME0SimTrackPdgID","hME0SimTrackPdgID",3000,0,3000);
	
	hSimElePtME0  = fs->make<TH1F>("hSimElePtME0","hSimElePtME0",100,0,10);			
	hSimMuPtME0   = fs->make<TH1F>("hSimMuPtME0","hSimMuPtME0",100,0,100);
	hSimPionPtME0 = fs->make<TH1F>("hSimPionPtME0","hSimPionPtME0",100,0,10);
	
	hSimEleNHitsME0 = fs->make<TH1F>("hSimEleNHitsME0","hSimEleNHitsME0",10,0,10);	
	hSimMuonNHitsME0 = fs->make<TH1F>("hSimMuonNHitsME0","hSimMuonNHitsME0",10,0,10);
	hSimPionNHitsME0 = fs->make<TH1F>("hSimPionNHitsME0","hSimPionNHitsME0",10,0,10);
	hPdgIDCheck= fs->make<TH1F>("hPdgIDCheck","hPdgIDCheck",220,0,220);
	hDRME0SimTrack  = fs->make<TH1F>("hDRME0SimTrack","hDRME0SimTrack",200,0,10);
	hDRME0SimMuonEle= fs->make<TH1F>("hDRME0SimMuonEle","hDRME0SimMuonEle",200,0,10);
	
	hNME0SegmentAfterDigiMatch= fs->make<TH1F>("hNME0SegmentAfterDigiMatch","hNME0SegmentAfterDigiMatch",3,0,3);
	hSegmentComposition= fs->make<TH1F>("hSegmentComposition","hSegmentComposition",3,0,3);
	hSegmentComposition->GetXaxis()->SetBinLabel(1,"13 || 11");
	hSegmentComposition->GetXaxis()->SetBinLabel(2,"13 || 11 || >200");
	hSegmentComposition->GetXaxis()->SetBinLabel(3,"13 only");
	
	hMuEleinME0Segm = fs->make<TH1F>("hMuEleinME0Segm","hMuEleinME0Segm",3,0,3);
	hMuEleOthersinME0Segm = fs->make<TH1F>("hMuEleOthersinME0Seg","hMuEleOthersinME0Seg",3,0,3);
	hMuOnlyinME0Segm = fs->make<TH1F>("hMuOnlyinME0Segm","hMuOnlyinME0Segm",3,0,3);

	
}



// ------------ method called once each job just after ending the event loop  ------------
void 
ME0SegmentAnalyzer::endJob() 
{
	/*
	 rootfile->cd();
	 mytree->Write();
	 rootfile->Close();*/
	
}

// ------------ method called when starting to processes a run  ------------

//void ME0SegmentAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
//{



// ------------ method called when ending the processing of a run  ------------
/*
 void 
 ME0SegmentAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method called when starting to processes a luminosity block  ------------
/*
 void 
 ME0SegmentAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
 void 
 ME0SegmentAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ME0SegmentAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ME0SegmentAnalyzer);
