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
	dpdspFit->SetLineColor(kRed);
	dpdspFit->SetLineWidth(2);


dpdspHist = new TH1D("dpdspHist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit",260,1790,2050);
	dpdspHist->SetStats(0);
	dpdspHist->SetTitleFont(43);
	dpdspHist->SetTitleSize(35);
	dpdspHist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");
	dpdspHist->SetMinimum(10);//make minimum 1 so logy doesnt break
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
/*
dpdspHist->GetXaxis()->SetRangeUser(1840,1900);
Double_t dpPeak = dpdspHist->GetBinContent(dpdspHist->GetMaximumBin());
dpdspHist->GetXaxis()->SetRangeUser(1940,2000);
Double_t dspPeak = dpdspHist->GetBinContent(dpdspHist->GetMaximumBin());
dpdspHist->GetXaxis()->setRangeUser(1790, 2050);

cout << "signal 1 peak content: " << dpPeak << endl;
cout << "signal 2 peak content: " << dspPeak << endl;
*/
Double_t dpPeak = 300000;
Double_t dspPeak = 500000;

//roughly first and last bin to guess exponential background
Double_t firstbin = dpdspHist->GetBinContent(3);
Double_t lastbin = dpdspHist->GetBinContent(257);

Double_t nSignal1Guess = (dpPeak-firstbin)*15;
Double_t nSignal2Guess = (dspPeak-firstbin)*15;
Double_t expCoefGuess = (lastbin-firstbin)/260;


cout << "first bin: " << firstbin << endl;
cout << "last bin: " << lastbin << endl;
cout << "exp coef: " << expCoefGuess << endl;


//first bin is about 3k, use this for rough signal limits
//dp: 4-5 mil
//dsp: 7-8 mil


dpdspFit->SetParameter(0,nSignal1Guess);//nSignal
	dpdspFit->SetParLimits(0,4000000,5000000);//this is a yikes... need to address
	dpdspFit->SetParameter(1,1869);//mu
	dpdspFit->SetParameter(2,4.);//rms of double gaussian
	dpdspFit->SetParLimits(2,0.,20.);
	dpdspFit->SetParameter(3,7);//sigma_1 of primary gaussian
	dpdspFit->SetParLimits(3,1,15);
	dpdspFit->SetParameter(4,0.85);//fraction of signal in primary gaussian
	dpdspFit->SetParLimits(4,0.00001,0.33333);
	dpdspFit->SetParameter(5, 1.5);//crystal ball alpha
	dpdspFit->SetParameter(6,2.5);//crystal ball n
	dpdspFit->SetParLimits(6,1.00001,6.);
	dpdspFit->SetParameter(7,nSignal2Guess);//nSignal
	dpdspFit->SetParLimits(7,7000000,8000000);//this is a yikes... need to address
	dpdspFit->SetParameter(8,1969);//mu
	dpdspFit->SetParameter(9,4.);//rms of double gaussian
	dpdspFit->SetParLimits(9,0.,20.);
	dpdspFit->SetParameter(10,7);//sigma_2 of primary gaussian
	dpdspFit->SetParLimits(10,1,15);
	dpdspFit->SetParameter(11,0.85);//fraction of signal in primary gaussian
	dpdspFit->SetParLimits(11,0.000001,0.33333);
	dpdspFit->SetParameter(12, 1.5);//crystal ball alpha
	dpdspFit->SetParameter(13,2.5);//crystal ball n
	dpdspFit->SetParLimits(13,1.00001,6.);
	dpdspFit->SetParameter(14,firstbin);//exp intercept
	dpdspFit->SetParameter(15,expCoefGuess);//coefficient background exponential
	dpdspFit->SetParLimits(15, 0, -0.001);



dpdspHist->Fit("dpdspFit","R");

auto totalpullcan = new TCanvas("totalpullcan", "totalpullcan", 1000, 800);
totalpullcan->SetLogy();
dpdspHist->Draw();

totalpullcan->SaveAs("image/aaaa_Dp_Dsp_fit_log.png");




}
