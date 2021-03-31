#define combined_cut_fit_cxx
#include "combined_cut_fit.h"
#include <TH2.h>
#include <TStyle.h>
#include "scripts/fit_spectrum.C"
#include <iostream>

//run by doing:
//$ root -l /share/lazy/D2KKpi/combined_cut.root
//$ DecayTree->Process("combined_cut_fit.C")



//************customization section**************88
//these variables are changeable

Int_t cutoffMass = 1920; // above (inclusive) this mass we use ds data, below we use dp data

bool sameCB = 0; //1 if using sameCB, 0 otherwise

Int_t fitStart = 1830;//1790 minimum
Int_t fitEnd = 2010;//2050 maximum
Int_t nBins = fitEnd - fitStart;


bool takeMagUp = 1; //1:include, 0:dont
bool takeMagDown = 1; //1:include, 0:dont




//********Definition Section************
TH1 * dpdspHist = NULL;
TH1 * pullHist = NULL;

TF1 * dpdspFit = NULL;

TF1 * backgroundFit = NULL;
TF1 * firstGaussianFit = NULL;
TF1 * firstCBFit = NULL;
TF1 * secondGaussianFit = NULL;
TF1 * secondCBFit = NULL;


//need to initialize these to resolve later confusions...
TString CBn2Str;
TString CBn2Strpm;
TString CBalpha2Str;
TString CBalpha2Strpm;


void combined_cut_fit::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

//*********Initialization Section**********





if (sameCB) {
dpdspFit = new TF1("dpdspFit",fit1MeVspectrum_Gaussian_sameCB_ExpBG,fitStart,fitEnd, 16);
} else {
dpdspFit = new TF1("dpdspFit",fit1MeVspectrum_Gaussian_CB_ExpBG,fitStart,fitEnd, 16);
}
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



firstGaussianFit = new TF1("firstGaussianFit",Gaussian,fitStart,fitEnd, 5);
	firstGaussianFit->SetParName(0, "nSignal1");
	firstGaussianFit->SetParName(1, "mu1");	
	firstGaussianFit->SetParName(2, "rms_wdth1");	
	firstGaussianFit->SetParName(3, "sigma_11");	
	firstGaussianFit->SetParName(4, "gaus_frac1");		
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

secondGaussianFit = new TF1("secondGaussianFit",Gaussian,fitStart,fitEnd, 5);
	secondGaussianFit->SetParName(0, "nSignal2");
	secondGaussianFit->SetParName(1, "mu2");	
	secondGaussianFit->SetParName(2, "rms_wdth2");	
	secondGaussianFit->SetParName(3, "sigma_12");	
	secondGaussianFit->SetParName(4, "gaus_frac2");	
	secondGaussianFit->SetLineColor(kSpring-1);
	secondGaussianFit->SetLineStyle(8);
	secondGaussianFit->SetLineWidth(2);
secondCBFit = new TF1("secondCBFit", CB, fitStart, fitEnd, 7);
	secondCBFit->SetParName(0, "nSignal1");
	secondCBFit->SetParName(1, "mu1");	
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






dpdspHist = new TH1D("dpdspHist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit",nBins,fitStart,fitEnd);
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




pullHist = new TH1D("pullHist", "Pull Plot", nBins,fitStart,fitEnd);
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

	Bool_t goodPolarity = ((takeMagUp && (*Polarity == 1)) || (takeMagDown && (*Polarity == -1)));


	if (takeData && goodPolarity)
	{
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
Double_t firstbin = dpdspHist->GetBinContent(1);//also used as exp_intercept guess
Double_t lastbin = dpdspHist->GetBinContent(nBins);

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
	dpdspFit->SetParameter(0,nSignal1Guess);//nSignal
	//dpdspFit->SetParLimits(0,4000000,5000000);
	dpdspFit->SetParameter(1,1869);//mu
	dpdspFit->SetParameter(2,4.);//rms of gaussian
	//dpdspFit->SetParLimits(2,0.,20.);
	dpdspFit->SetParameter(3,7);//sigma of gaussian
	//dpdspFit->SetParLimits(3,1,15);
	dpdspFit->SetParameter(4,0.1);//fraction of signal in  gaussian
	dpdspFit->SetParLimits(4,0.000001,0.99999);
	dpdspFit->SetParameter(5, 1.5);//crystal ball alpha
	dpdspFit->SetParameter(6,2.5);//crystal ball n
	//dpdspFit->SetParLimits(6,1.00001,10);
//dsp mass peak
	dpdspFit->SetParameter(7,nSignal2Guess);//nSignal
	//dpdspFit->SetParLimits(7,7000000,8000000);
	dpdspFit->SetParameter(8,1969);//mu
	dpdspFit->SetParameter(9,4.);//rms of gaussian
	//dpdspFit->SetParLimits(9,0.,20.);
	dpdspFit->SetParameter(10,7);//sigma_2 of gaussian
	//dpdspFit->SetParLimits(10,1,15);
	dpdspFit->SetParameter(11,0.1);//fraction of signal in gaussian
	dpdspFit->SetParLimits(11,0.000001,0.99999);
	dpdspFit->SetParameter(12, 1.5);//crystal ball alpha
	dpdspFit->SetParameter(13,2.5);//crystal ball n
	//dpdspFit->SetParLimits(13,1.00001,6.);
//exponential background
	dpdspFit->SetParameter(14,firstbin);//exp intercept
	dpdspFit->SetParameter(15,expCoefGuess);//coefficient background exponential
	//dpdspFit->SetParLimits(15, 0, -0.001);

















auto totalpullcan = new TCanvas("totalpullcan", "totalpullcan", 1400, 800);

TPad *pad1 = new TPad("pad1","pad1",0,0.25,0.75,1.0);//for the main hist
TPad *pad2 = new TPad("pad2","pad2",0,0.0,0.75,0.25);//for the pull plot
TPad *pad3 = new TPad("pad3","pad3",0.75,0.0,1.0,1.0);//for info
	pad1->Draw();
	pad2->Draw();
	pad3->Draw();



pad1->cd();
	pad1->SetBottomMargin(0);
	pad1->SetLeftMargin(0.15);
	pad1->SetRightMargin(0.05);
	pad1->SetLogy();
	pad1->SetGridy();

dpdspHist->Fit("dpdspFit","R");
//TF1 *fit = dpdspHist->GetFunction("dpdspFit");
//TFitResultPtr fitResultPointer = dpdspHist->Fit("dpdspFit","R");

	//get the parameters back for isolated signal plotting
	//signal 2
		Double_t nSignal1   = dpdspFit->GetParameter(0);
		Double_t mu1        = dpdspFit->GetParameter(1);
		Double_t rms1       = dpdspFit->GetParameter(2);
		Double_t sigma1     = dpdspFit->GetParameter(3);
		Double_t f1         = dpdspFit->GetParameter(4);
		Double_t CB_alpha1  = dpdspFit->GetParameter(5);
		Double_t CB_n1      = dpdspFit->GetParameter(6);
	//signal 2
		Double_t nSignal2   = dpdspFit->GetParameter(7);
		Double_t mu2        = dpdspFit->GetParameter(8);
		Double_t rms2       = dpdspFit->GetParameter(9);
		Double_t sigma2     = dpdspFit->GetParameter(10);
		Double_t f2         = dpdspFit->GetParameter(11);
		Double_t CB_alpha2  = dpdspFit->GetParameter(12);
		Double_t CB_n2      = dpdspFit->GetParameter(13);
if (sameCB) {
		cout << "CB is same" << endl;
		Double_t CB_alpha2 = CB_alpha1;
		Double_t CB_n2 = CB_n1;
}


	//exp background
		Double_t exp_int    = dpdspFit->GetParameter(14);
		Double_t exp_coef   = dpdspFit->GetParameter(15);

	//manually fill first gaussian
		firstGaussianFit->SetParameter(0, nSignal1);
		firstGaussianFit->SetParameter(1, mu1);
		firstGaussianFit->SetParameter(2, rms1);
		firstGaussianFit->SetParameter(3, sigma1);
		firstGaussianFit->SetParameter(4, f1);
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









	pad2->cd();
		pad2->SetTopMargin(0);
		pad2->SetBottomMargin(0.4);
		pad2->SetLeftMargin(0.15);
		pad2->SetRightMargin(0.05);
		pad2->SetGridx();


	 Double_t xVals[nBins];
	 Double_t yVals[nBins];
	 for (Int_t i=1;i<nBins;i++) {
	 Double_t x = dpdspHist->GetBinCenter(i);
	 Double_t val = dpdspFit->Eval(dpdspHist->GetBinCenter(i));
	 Double_t sigma = sqrt(val);
	 Double_t pull = (dpdspHist->GetBinContent(i)-val)/sigma;
	 pullHist->SetBinContent(i,pull);
	   xVals[i]=x;
	   yVals[i]=pull;
	   }
	pullHist->Draw();





	pad3->cd();
		//pad3->SetTopMargin(0);
		pad3->SetBottomMargin(0);
		pad3->SetLeftMargin(-0.15);
		pad3->SetRightMargin(0);

	auto fitlegend = new TLegend(00,0.77,0.8,0.925);//(0.7,0.7,0.9,0.9);
		fitlegend->SetTextSize(0.08);
		fitlegend->AddEntry(dpdspFit, "Total Fit", "l");
		fitlegend->AddEntry(firstGaussianFit, "Gaussian Fit", "l");
		fitlegend->AddEntry(firstCBFit, "CB Fit", "l");
		fitlegend->AddEntry(backgroundFit, "Exp Fit", "l");
		fitlegend->Draw();



		TString nSignal1Str;
			TString nSignal1Strpm;
			nSignal1Str.Form("%5.0f\n",nSignal1);
			nSignal1Strpm.Form("%5.0f\n",dpdspFit->GetParError(0));
		TString mu1Str;
			TString mu1Strpm;
			mu1Str.Form("%5.6f\n",mu1);
			mu1Strpm.Form("%5.6f\n",dpdspFit->GetParError(1));
		TString rmsWidth1Str;
			TString rmsWidth1Strpm;
			rmsWidth1Str.Form("%5.3f\n",rms1);
			rmsWidth1Strpm.Form("%5.3f\n",dpdspFit->GetParError(2));
		TString gaus_frac1Str;
			TString gaus_frac1Strpm;
			gaus_frac1Str.Form("%5.3f\n",f1);
			gaus_frac1Strpm.Form("%5.3f\n",dpdspFit->GetParError(4));
		TString CBalpha1Str;
			TString CBalpha1Strpm;
			CBalpha1Str.Form("%5.3f\n",CB_alpha1);
				Double_t CB_alpha_err = dpdspFit->GetParError(5);
			CBalpha1Strpm.Form("%5.3f\n",CB_alpha_err);
		TString CBn1Str;
			TString CBn1Strpm;
			CBn1Str.Form("%5.3f\n",CB_n1);
				Double_t CB_n_err = dpdspFit->GetParError(6);
			CBn1Strpm.Form("%5.3f\n",CB_n_err);

		TString nSignal2Str;
			TString nSignal2Strpm;
			nSignal2Str.Form("%5.0f\n",nSignal2);
			nSignal2Strpm.Form("%5.0f\n",dpdspFit->GetParError(7));
		TString mu2Str;
			TString mu2Strpm;
			mu2Str.Form("%5.6f\n",mu2);
			mu2Strpm.Form("%5.6f\n",dpdspFit->GetParError(8));
		TString rmsWidth2Str;
			TString rmsWidth2Strpm;
			rmsWidth2Str.Form("%5.3f\n",rms2);
			rmsWidth2Strpm.Form("%5.3f\n",dpdspFit->GetParError(9));
		TString gaus_frac2Str;
			TString gaus_frac2Strpm;
			gaus_frac2Str.Form("%5.3f\n",f2);
			gaus_frac2Strpm.Form("%5.3f\n",dpdspFit->GetParError(11));


if (sameCB) {
			CBalpha2Str.Form("%5.3f\n",CB_alpha1);//change if sameCB
			CBalpha2Strpm.Form("%5.3f\n",CB_alpha_err);
			CBn2Str.Form("%5.3f\n",CB_n1);//change if s
			CBn2Strpm.Form("%5.3f\n",CB_n_err);
} else {
			CBalpha2Str.Form("%5.3f\n",CB_alpha2);//change if sameCB
			CBalpha2Strpm.Form("%5.3f\n",dpdspFit->GetParError(12));
			CBn2Str.Form("%5.3f\n",CB_n2);//change if s
			CBn2Strpm.Form("%5.3f\n",dpdspFit->GetParError(13));
}



		TString expIntStr;
			TString expIntStrpm;
			expIntStr.Form("%5.3f\n",exp_int);
			expIntStrpm.Form("%5.3f\n",dpdspFit->GetParError(14));
		TString expCoefStr;
			TString expCoefStrpm;
			expCoefStr.Form("%.3e\n",exp_coef);
			expCoefStrpm.Form("%.3e\n",dpdspFit->GetParError(15));

		TString EDMStr;
			Double_t EDMval = 1.537e-06;//have to manually type this in for now...
			EDMStr.Form("%.3e\n",EDMval);



		auto lt = new TLatex();
			lt->SetTextSize(0.05);
			lt->DrawLatexNDC(0, 0.72, "D^{+} Signal Events = "+nSignal1Str+" #pm "+nSignal1Strpm);
			lt->DrawLatexNDC(0, 0.69, "m(D^{+}) = "+mu1Str+" #pm "+mu1Strpm+" MeV/c^{2}");
			lt->DrawLatexNDC(0, 0.66, "D^{+} RMS Width = "+rmsWidth1Str+" #pm "+rmsWidth1Strpm);
			lt->DrawLatexNDC(0, 0.63, "D^{+} Fraction Gaus = "+gaus_frac1Str+" #pm "+gaus_frac1Strpm);
			lt->DrawLatexNDC(0, 0.60, "D^{+} CB alpha = "+CBalpha1Str+" #pm "+CBalpha1Strpm);
			lt->DrawLatexNDC(0, 0.57, "D^{+} CB n = "+CBn1Str+" #pm "+CBn1Strpm);

			lt->DrawLatexNDC(0, 0.50, "D_{s} Signal Events = "+nSignal2Str+" #pm "+nSignal2Strpm);
			lt->DrawLatexNDC(0, 0.47, "m(D_{s}) = "+mu2Str+" #pm "+mu2Strpm+" MeV/c^{2}");
			lt->DrawLatexNDC(0, 0.44, "D_{s} RMS Width = "+rmsWidth2Str+" #pm "+rmsWidth2Strpm);
			lt->DrawLatexNDC(0, 0.41, "D_{s} Fraction Gaus = "+gaus_frac2Str+" #pm "+gaus_frac2Strpm);
			lt->DrawLatexNDC(0, 0.38, "D_{s} CB alpha = "+CBalpha2Str+" #pm "+CBalpha2Strpm);
			lt->DrawLatexNDC(0, 0.35, "D_{s} CB n = "+CBn2Str+" #pm "+CBn2Strpm);

			lt->DrawLatexNDC(0, 0.28, "Exp Int. = "+expIntStr+" #pm "+expIntStrpm);
			lt->DrawLatexNDC(0, 0.25, "Exp Coef. = "+expCoefStr+" #pm "+expCoefStrpm);

			lt->DrawLatexNDC(0, 0.15, "EDM = "+EDMStr);








totalpullcan->cd();
if (sameCB) {
totalpullcan->SaveAs("image/aaafinal_dp_dsp_gaus-cb-exp_log_tighter_sameCB.png");
} else {
totalpullcan->SaveAs("image/aaafinal_dp_dsp_gaus-cb-exp_log_tighter.png");
}



}
