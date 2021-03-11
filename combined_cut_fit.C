#define combined_cut_fit_cxx
#include "combined_cut_fit.h"
#include <TH2.h>
#include <TStyle.h>
#include "scripts/fit_spectrum.C"

//run by doing:
//$ root -l /share/lazy/D2KKpi/combined_cut.root
//$ DecayTree->Process("combined_cut_fit.C")


Int_t cutoffMass = 1900; // above (inclusive) this mass we use ds data, below we use dp data

//********Definition Section************
TH1 * dpdspHist = NULL;
TH1 * pullHist = NULL;

TF1 * dpdspFit = NULL;




void combined_cut_fit::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

//*********Initialization Section**********
dpdspFit = new TF1("dpdspFit",fit1MeV_DoubleGaussian_DoubleCB_ExpBG,1790,2050, 16);
	dpdspFit->SetParName(0, "nSignal1");
	dpdspFit->SetParName(1, "mu1");	
	dpdspFit->SetParName(2, "rms_wdth1");	
	dpdspFit->SetParName(3, "sigma_11");	
	dpdspFit->SetParName(4, "gaus_frac1");	
	dpdspFit->SetParName(5, "CB_alpha1");	
	dpdspFit->SetParName(6, "CB_n1");	
	dpdspFit->SetParName(7, "nSignal2");	
	dpdspFit->SetParName(8, "mu2");	
	dpdspFit->SetParName(9, "rms_wdth2");	
	dpdspFit->SetParName(10, "sigma_12");	
	dpdspFit->SetParName(11, "gaus_frac2");	
	dpdspFit->SetParName(12, "CB_alpha2");	
	dpdspFit->SetParName(13, "CB_n2");	
	dpdspFit->SetParName(14, "exp_int");
	dpdspFit->SetParName(15, "exp_coef");
	dpdspFit->SetLineColor(kRed+1);
	dpdspFit->SetLineWidth(2);


dpdspHist = new TH1D("dpdspHist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit",260,1790,2050);
	dpdspHist->SetStats(0);
	dpdspHist->SetTitleFont(43);
	dpdspHist->SetTitleSize(35);
	dpdspHist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");
	//dpdspHist->SetMinimum(10);//make minimum 1 so logy doesnt break
	dpdspHist->GetYaxis()->SetTitleFont(43);
	dpdspHist->GetYaxis()->SetTitleSize(30);
	dpdspHist->GetYaxis()->CenterTitle(true);
	dpdspHist->SetLineColor(kBlack);
	dpdspHist->SetLineWidth(3);


pullHist = new TH1D("pullHist", "Pull Plot", 260,1790,2050);
	pullHist->SetStats(0);
	pullHist->GetYaxis()->SetTitle("Pull");
	pullHist->GetYaxis()->SetTitleSize(30);
	pullHist->GetYaxis()->SetTitleFont(43);
	pullHist->GetYaxis()->CenterTitle(true);
	pullHist->GetYaxis()->SetLabelSize(0.1);
	pullHist->GetXaxis()->SetTitle("D^{+}_{(s)} mass [MeV/c^{2}]");
	pullHist->GetXaxis()->SetTitleSize(30);
	pullHist->GetXaxis()->SetTitleFont(43);
	pullHist->GetXaxis()->CenterTitle(true);
	pullHist->GetXaxis()->SetLabelSize(0.15);
	pullHist->GetXaxis()->SetTitleOffset(4);
	pullHist->SetFillColor(kBlue);
	pullHist->SetLineColor(kBlue);
	pullHist->SetBit(TH1::kNoTitle);
	pullHist->GetYaxis()->SetNdivisions(7);



}



void combined_cut_fit::SlaveBegin(TTree * /*tree*/) {}



Bool_t combined_cut_fit::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);
   GetEntry(entry);

//********Loop Section********

	Bool_t takeData = ((*particle_MM < cutoffMass) && (*isDp == 1)) || ((*particle_MM >= cutoffMass) && (*isDp == 0));

	if (takeData) {
		dpdspHist->Fill(*particle_MM);
	}



   return kTRUE;
}



void combined_cut_fit::SlaveTerminate() {}



void combined_cut_fit::Terminate()
{
//*********Wrap-up section********
dpdspHist->GetXaxis()->SetRangeUser(1840,1900);
Double_t dpPeak = dpdspHist->GetBinContent(dpdspHist->GetMaximumBin());
dpdspHist->GetXaxis()->SetRangeUser(1940,2000);
Double_t dspPeak = dpdspHist->GetBinContent(dpdspHist->GetMaximumBin());
dpdspHist->GetXaxis()->setRangeUser(1790, 2050);

cout << "signal 1 peak content: " << dpPeak << endl;
cout << "signal 2 peak content: " << dspPeak << endl;


//roughly first and last bin to guess exponential background
Double_t firstbin = dpdspHist->GetBinContent(3);
Double_t lastbin = dpdspHist->GetBinContent(257);

Double_t nSignal1Guess = (dpPeak-firstbin)*15;
Double_t nSignal2Guess = (dspPeak-firstbin)*15;
Double_t expCoefGuess = (lastbin-firstbin)/260;







}
