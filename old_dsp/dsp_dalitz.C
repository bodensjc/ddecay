#define dsp_dalitz_cxx
#include "dsp_dalitz.h"
#include <TH2.h>
#include <TStyle.h>

//***********************DEFINITION SECTION********************
TH1 * kpkm = NULL;
TH1 * kppi = NULL;
TH1 * kmpi = NULL;
TH1 * kpkm_kmpi = NULL;
TH1 * kpkm_kppi = NULL;
TH1 * kppi_kmpi = NULL;




void dsp_dalitz::Begin(TTree * /*tree*/)
{
   TString option = GetOption();


//*********************INITIALIZATION SECTION*********************
   
kpkm = new TH1F("kpkm", "K+ K- Invariant Mass",100,0.9,3.7);
   kpkm->GetXaxis()->SetTitle("m^{2}(K+K-) [GeV/c^{2}]^{2}");
   kpkm->GetYaxis()->SetTitle("events");

kppi = new TH1F("kppi", "K+ Pi+ Invariant Mass",100,0.3,2.5);
   kppi->GetXaxis()->SetTitle("m^{2}(K+Pi+) [GeV/c^{2}]^{2}");
   kppi->GetYaxis()->SetTitle("events");

kmpi = new TH1F("kmpi", "K- Pi+ Invariant Mass",100,0.3,2.5);
   kmpi->GetXaxis()->SetTitle("m^{2}(K-Pi+) [GeV/c^{2}]^{2}");
   kmpi->GetYaxis()->SetTitle("events");



kpkm_kmpi = new TH2F("kpkm_kmpi", "D^{+}_{s} #rightarrow  K^{+}K^{-}#pi^{+} Dalitz Plot",200,0.8,3.7,200,0.1,2.5);
kpkm_kmpi->SetStats(0);
   kpkm_kmpi->GetXaxis()->SetTitle("m^{2}(K^{+}K^{-}) [GeV/c^{2}]^{2}");
   kpkm_kmpi->GetYaxis()->SetTitle("m^{2}(K^{-}#pi^{+}) [GeV/c^{2}]^{2}");

   kpkm_kppi = new TH2F("kpkm_kppi", "D^{+}_{s} #rightarrow  K^{+}K^{-}#pi^{+} Dalitz Plot",200,0.8,3.7,200,0.1,2.5);
kpkm_kppi->SetStats(0);
   kpkm_kppi->GetXaxis()->SetTitle("m^{2}(K^{+}K^{-}) [GeV/c^{2}]^{2}");
   kpkm_kppi->GetYaxis()->SetTitle("m^{2}(K^{+}#pi^{+}) [GeV/c^{2}]^{2}");

kppi_kmpi = new TH2F("kppi_kmpi", "D^{+}_{s} #rightarrow  K^{+}K^{-}#pi^{+} Dalitz Plot",200,0.1,2.5,200,0.1,2.5);
kppi_kmpi->SetStats(0);
   kppi_kmpi->GetXaxis()->SetTitle("m^{2}(K^{+}#pi^{+}) [GeV/c^{2}]^{2}");
   kppi_kmpi->GetYaxis()->SetTitle("m^{2}(K^{-}#pi^{+}) [GeV/c^{2}]^{2}");

}

void dsp_dalitz::SlaveBegin(TTree * /*tree*/) {}

Bool_t dsp_dalitz::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);
   GetEntry(entry);

//**********************LOOP SECTION******************
   //filling the actual Lorentz Vectors
   TLorentzVector kpLV(*Kplus_PX, *Kplus_PY, *Kplus_PZ, *Kplus_PE);
   TLorentzVector kmLV(*Kminus_PX, *Kminus_PY, *Kminus_PZ, *Kminus_PE);
   TLorentzVector piLV(*Piplus_PX, *Piplus_PY, *Piplus_PZ, *Piplus_PE);
   //initializing the Lorentz Vectors for pairing
   TLorentzVector kpkmLV(kpLV + kmLV);
   TLorentzVector kppiLV(kpLV + piLV);
   TLorentzVector kmpiLV(kmLV + piLV);
   //calculating invariant mass pairs
   double_t mkpkm = kpkmLV.Mag2()/1000000;
   double_t mkppi = kppiLV.Mag2()/1000000;
   double_t mkmpi = kmpiLV.Mag2()/1000000;
   //filling single pair distributions
   kpkm->Fill(mkpkm);
   kppi->Fill(mkppi);
   kmpi->Fill(mkmpi);
   //filling the three dalitz plots
   kpkm_kmpi->Fill(mkpkm,mkmpi);
   kpkm_kppi->Fill(mkpkm,mkppi);
   kppi_kmpi->Fill(mkppi,mkmpi);


   return kTRUE;


}

void dsp_dalitz::SlaveTerminate() {}

void dsp_dalitz::Terminate()
{
  //********************WRAP-UP SECTION*****************
/*
  auto kpkmcan = new TCanvas("kpkmcan","kpkmcan",1600,1200);
  kpkm->Draw();
  kpkmcan->SaveAs("image/dsp_imd_kpkm.png");

  auto kppican = new TCanvas("kppican","kppican",1600,1200);
  kppi->Draw();
  kppican->SaveAs("image/dsp_imd_kppi.png");

  auto kmpican = new TCanvas("kmpican","kmpican",1600,1200);
  kmpi->Draw();
  kmpican->SaveAs("image/dsp_imd_kmpi.png");
*/

	gStyle->SetPalette(55, 0);

  auto kpkmkmpican = new TCanvas("kpkmkmpican","kpkmkmpican",1200,1200);
kpkmkmpican->SetRightMargin(0.15);
  kpkm_kmpi->Draw("colz");
  kpkmkmpican->SaveAs("image/dsp_dalitz_kpkm_kmpi.png");

  auto kpkmkppican = new TCanvas("kpkmkppican","kpkmkppican",1200,1200);
  kpkm_kppi->Draw("colz");
  kpkmkppican->SaveAs("image/dsp_dalitz_kpkm_kppi.png");

  auto kppikmpican = new TCanvas("kppikmpican","kppikmpican",1200,1200);
  kppi_kmpi->Draw("colz");
  kppikmpican->SaveAs("image/dsp_dalitz_kppi_kmpi.png");

}
