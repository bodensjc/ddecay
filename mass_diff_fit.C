#define mass_diff_fit_cxx
#include "mass_diff_fit.h"
#include <TH2.h>
#include <TStyle.h>
#include "scripts/fit_spectrum.C"




//run by doing:
//$ root -l /share/lazy/D2KKpi/combined_cut.root
//$ DecayTree->Process("combined_cut_fit.C")


Int_t cutoffMass = 1920; // above (inclusive) this mass we use ds data, below we use dp data

//********Definition Section************
TH1 * dpdspHist = NULL;
TH1 * pullHist = NULL;

TF1 * massDiffFit = NULL;



TF1 * backgroundFit = NULL;
TF1 * firstGaussianFit = NULL;
TF1 * firstCBFit = NULL;
TF1 * secondGaussianFit = NULL;
TF1 * secondCBFit = NULL;


Int_t fitStart = 1790;//1790 minimum
Int_t fitEnd = 2050;//2050 maximum




void mass_diff_fit::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

//*********Initialization Section**********


massDiffFit = new TF1("massDiffFit",fit1MeVdifference_Gaussian_CB_ExpBG,fitStart,fitEnd, 16);
	massDiffFit->SetParName(0, "nSignal1");
	massDiffFit->SetParName(1, "mu1");	
	massDiffFit->SetParName(2, "rms_wdth1");	
	massDiffFit->SetParName(3, "sigma_11");	
	massDiffFit->SetParName(4, "gaus_frac1");	
	massDiffFit->SetParName(5, "CB_alpha1");	
	massDiffFit->SetParName(6, "CB_n1");	
	massDiffFit->SetParName(7, "nSignal2");	
	massDiffFit->SetParName(8, "massDiff");	
	massDiffFit->SetParName(9, "rms_wdth2");	
	massDiffFit->SetParName(10, "sigma_12");	
	massDiffFit->SetParName(11, "gaus_frac2");	
	massDiffFit->SetParName(12, "CB_alpha2");	
	massDiffFit->SetParName(13, "CB_n2");	
	massDiffFit->SetParName(14, "exp_int");
	massDiffFit->SetParName(15, "exp_coef");
	massDiffFit->SetLineColor(kRed);
	massDiffFit->SetLineWidth(2);



firstGaussianFit = new TF1("firstGaussianFit",Gaussian,fitStart,fitEnd, 7);
	firstGaussianFit->SetParName(0, "nSignal1");
	firstGaussianFit->SetParName(1, "mu1");	
	firstGaussianFit->SetParName(2, "rms_wdth1");	
	firstGaussianFit->SetParName(3, "sigma_11");	
	firstGaussianFit->SetParName(4, "gaus_frac1");	
	firstGaussianFit->SetParName(5, "CB_alpha1");	
	firstGaussianFit->SetParName(6, "CB_n1");	
	firstGaussianFit->SetLineColor(kSpring-1);
	firstGaussianFit->SetLineStyle(8);
	firstGaussianFit->SetLineWidth(2);
firstCBFit = new TF1("firstCBFit", CB, fitStart, fitEnd, 7);
	firstCBFit->SetParName(0, "nSignal1");
	firstCBFit->SetParName(1, "mu1");	
	firstCBFit->SetParName(2, "rms_wdth1");	
	firstCBFit->SetParName(3, "sigma_11");	
	firstCBFit->SetParName(4, "gaus_frac1");	
	firstCBFit->SetParName(5, "CB_alpha1");	
	firstCBFit->SetParName(6, "CB_n1");	
	firstCBFit->SetLineColor(kAzure-1);
	firstCBFit->SetLineStyle(5);
	firstCBFit->SetLineWidth(2);

secondGaussianFit = new TF1("secondGaussianFit",Gaussian,fitStart,fitEnd, 7);
	secondGaussianFit->SetParName(0, "nSignal2");
	secondGaussianFit->SetParName(1, "mu2");	
	secondGaussianFit->SetParName(2, "rms_wdth2");	
	secondGaussianFit->SetParName(3, "sigma_12");	
	secondGaussianFit->SetParName(4, "gaus_frac2");	
	secondGaussianFit->SetParName(5, "CB_alpha2");	
	secondGaussianFit->SetParName(6, "CB_n2");	
	secondGaussianFit->SetLineColor(kSpring-1);
	secondGaussianFit->SetLineStyle(8);
	secondGaussianFit->SetLineWidth(2);
secondCBFit = new TF1("secondCBFit", CB, fitStart, fitEnd, 7);
	secondCBFit->SetParName(0, "nSignal1");
	secondCBFit->SetParName(1, "mu2");	
	secondCBFit->SetParName(2, "rms_wdth1");	
	secondCBFit->SetParName(3, "sigma_11");	
	secondCBFit->SetParName(4, "gaus_frac1");	
	secondCBFit->SetParName(5, "CB_alpha1");	
	secondCBFit->SetParName(6, "CB_n1");	
	secondCBFit->SetLineColor(kAzure-1);
	secondCBFit->SetLineStyle(5);
	secondCBFit->SetLineWidth(2);

backgroundFit = new TF1("backgroundFit",backgroundExp,fitStart,fitEnd, 2);
	backgroundFit->SetParNames("exp_int","exp_coef");
	backgroundFit->SetLineColor(kOrange-3);
	backgroundFit->SetLineStyle(2);
	backgroundFit->SetLineWidth(2);





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

void mass_diff_fit::SlaveBegin(TTree * /*tree*/) {}

Bool_t mass_diff_fit::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);
   GetEntry(entry);

//********Loop Section********

	Bool_t takeData = ((*particle_MM < cutoffMass) && (*isDp == 1)) || ((*particle_MM >= cutoffMass) && (*isDp == 0));



	if (takeData) // && *Polarity == 1
	{
		dpdspHist->Fill(*particle_MM);
	}



   return kTRUE;
}

void mass_diff_fit::SlaveTerminate() {}

void mass_diff_fit::Terminate()
{
//*********Wrap-up section********
Double_t dpPeak = 300000;
Double_t dspPeak = 500000;

//roughly first and last bin to guess exponential background
Double_t firstbin = dpdspHist->GetBinContent(5);//also used as exp_intercept guess
Double_t lastbin = dpdspHist->GetBinContent(250);

Double_t nSignal1Guess = (dpPeak-firstbin)*15;
Double_t nSignal2Guess = (dspPeak-firstbin)*15;
Double_t expCoefGuess = (lastbin-firstbin)/245000;



cout << "first bin: " << firstbin << endl;
cout << "last bin: " << lastbin << endl;
cout << "exp coef: " << expCoefGuess << endl;


//first bin is about 3k, use this for rough signal limits
//dp: 4-5 mil
//dsp: 7-8 mil

//dp mass peak
	massDiffFit->SetParameter(0,nSignal1Guess);//nSignal
	//massDiffFit->SetParLimits(0,4000000,5000000);
	massDiffFit->SetParameter(1,1869);//mu
	massDiffFit->SetParameter(2,4.);//rms of gaussian
	//massDiffFit->SetParLimits(2,0.,20.);
	massDiffFit->SetParameter(3,7);//sigma of gaussian
	//massDiffFit->SetParLimits(3,1,15);
	massDiffFit->SetParameter(4,0.1);//fraction of signal in  gaussian
	massDiffFit->SetParLimits(4,0.000001,0.99999);
	massDiffFit->SetParameter(5, 1.5);//crystal ball alpha
	massDiffFit->SetParameter(3,2.5);//crystal ball n
	//massDiffFit->SetParLimits(6,1.00001,6.);
//dsp mass peak (this is where the mass difference vairable is )
	massDiffFit->SetParameter(7,nSignal2Guess);//nSignal
	//massDiffFit->SetParLimits(7,7000000,8000000);
	massDiffFit->SetParameter(8,100);//mass Difference
		massDiffFit->SetParLimits(8,95,105);
	massDiffFit->SetParameter(9,4.);//rms of gaussian
	//massDiffFit->SetParLimits(9,0.,20.);
	massDiffFit->SetParameter(10,7);//sigma_2 of gaussian
	//massDiffFit->SetParLimits(10,1,15);
	massDiffFit->SetParameter(11,0.1);//fraction of signal in gaussian
	massDiffFit->SetParLimits(11,0.000001,0.99999);
	massDiffFit->SetParameter(12, 1.5);//crystal ball alpha
	massDiffFit->SetParameter(13,2.5);//crystal ball n
	//massDiffFit->SetParLimits(13,1.00001,6.);
//exponential background
	massDiffFit->SetParameter(14,firstbin);//exp intercept
	massDiffFit->SetParameter(15,expCoefGuess);//coefficient background exponential
	//massDiffFit->SetParLimits(15, 0, -0.001);








auto totalpullcan = new TCanvas("totalpullcan", "totalpullcan", 1000, 800);
totalpullcan->SetLogy();
dpdspHist->Fit("massDiffFit","R");

	//get the parameters back for isolated signal plotting
	//signal 2
		Double_t nSignal1   = massDiffFit->GetParameter(0);
		Double_t mu1        = massDiffFit->GetParameter(1);
		Double_t rms1       = massDiffFit->GetParameter(2);
		Double_t sigma1     = massDiffFit->GetParameter(3);
		Double_t f1         = massDiffFit->GetParameter(4);
		Double_t CB_alpha1  = massDiffFit->GetParameter(5);
		Double_t CB_n1      = massDiffFit->GetParameter(6);
	//signal 2
		Double_t nSignal2   = massDiffFit->GetParameter(7);
		Double_t massDiff   = massDiffFit->GetParameter(8);
			Double_t mu2    = mu1+massDiff;
		Double_t rms2       = massDiffFit->GetParameter(9);
		Double_t sigma2     = massDiffFit->GetParameter(10);
		Double_t f2         = massDiffFit->GetParameter(11);
		Double_t CB_alpha2  = massDiffFit->GetParameter(12);
		Double_t CB_n2      = massDiffFit->GetParameter(13);
	//exp background
		Double_t exp_int    = massDiffFit->GetParameter(14);
		Double_t exp_coef   = massDiffFit->GetParameter(15);

	//manually fill first gaussian
		firstGaussianFit->SetParameter(0, nSignal1);
		firstGaussianFit->SetParameter(1, mu1);
		firstGaussianFit->SetParameter(2, rms1);
		firstGaussianFit->SetParameter(3, sigma1);
		firstGaussianFit->SetParameter(4, f1);
		firstGaussianFit->SetParameter(5, CB_alpha1);
		firstGaussianFit->SetParameter(6, CB_n1);
	//manually fill first CB
		firstCBFit->SetParameter(0, nSignal1);
		firstCBFit->SetParameter(1, mu1);
		firstCBFit->SetParameter(2, rms1);
		firstCBFit->SetParameter(3, sigma1);
		firstCBFit->SetParameter(4, f1);
		firstCBFit->SetParameter(5, CB_alpha1);
		firstCBFit->SetParameter(6, CB_n1);

	//manually fill second gaussian
		secondGaussianFit->SetParameter(0, nSignal2);
		secondGaussianFit->SetParameter(1, mu2);
		secondGaussianFit->SetParameter(2, rms2);
		secondGaussianFit->SetParameter(3, sigma2);
		secondGaussianFit->SetParameter(4, f2);
		secondGaussianFit->SetParameter(5, CB_alpha2);
		secondGaussianFit->SetParameter(6, CB_n2);
	//manually fill second CB
		secondCBFit->SetParameter(0, nSignal2);
		secondCBFit->SetParameter(1, mu2);
		secondCBFit->SetParameter(2, rms2);
		secondCBFit->SetParameter(3, sigma2);
		secondCBFit->SetParameter(4, f2);
		secondCBFit->SetParameter(5, CB_alpha2);
		secondCBFit->SetParameter(6, CB_n2);

	//manually fill background exponential information
		backgroundFit->SetParameter(0,exp_int);
		backgroundFit->SetParameter(1,exp_coef);

dpdspHist->Draw();
firstGaussianFit->Draw("same");
firstCBFit->Draw("same");
secondGaussianFit->Draw("same");
secondCBFit->Draw("same");
backgroundFit->Draw("same");

totalpullcan->SaveAs("image/aaafinal_dp_dsp_massDiff_gaus-cb-exp_log.png");

}
