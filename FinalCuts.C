#define FinalCuts_cxx
#include "FinalCuts.h"
#include <TH2.h>
#include <TStyle.h>
#include "scripts/new_fit_spectrum.C"
#include <iostream>

//run by doing:
//$ root -l /share/lazy/D2KKpi/combined_cut.root
//$ DecayTree->Process("FinalCuts.C")

//This will be my final approach to analysis for the D->KKpi decay channel.
//It should provide most* meaningful fits and corresponding plots.




//***************CUSTOMIZATION***************
//change these variables to modify settings for the fit

string extraFileStr = "aaa_aaa";//adds extra notation to beginning of save file string

Int_t fitStart = 1830; //1790 minimum
Int_t fitEnd = 2040; //2050 maximum
Double_t binWidth = 1; //MeV
   Int_t nBins = (fitEnd-fitStart)/binWidth;
Int_t cutoffMass = 1920; //above (inclusive) this value we use Ds data, below is D+

Bool_t takeMagUp = 1; //1: include, 0: don't
Bool_t takeMagDown = 1; //1: include, 0: don't

Bool_t isSameCB = 1; //1: use same CB params for both peaks, 0: don't
Bool_t isMassDiff = 1; //1: mass difference fit, 0: two mass fit
Bool_t isFirstPeakDoubleGaus = 0; //1: double gaus in D+, 0: single
Bool_t isSecondPeakDoubleGaus = 1; //1: double gaus in Ds, 0: single

// upper and lower limits for momentum-restricted plots (GeV)
// make PLOWER 0 and PUPPER outrageously large to ignore this
//t his is prtty new so the signalpeak guesses may need to be adjusted
Int_t P_LOWER = 0;
Int_t P_UPPER = 10000000000;




//***************DEFINITION SECTION***************
TH1 * dpdspHist = NULL;
TH1 * pullHist = NULL;

TF1 * dpdspFit = NULL;

TF1 * backgroundFit = NULL;
TF1 * firstGaus1Fit = NULL;
TF1 * firstGaus2Fit = NULL;
TF1 * firstCBFit = NULL;
TF1 * secondGaus1Fit = NULL;
TF1 * secondGaus2Fit = NULL;
TF1 * secondCBFit = NULL;






void FinalCuts::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   //***************INITIALIZATION SECTION***************
ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(5000);

   dpdspFit = new TF1("dpdspFit", customFit_Dp_Ds, fitStart, fitEnd, 25);
      dpdspFit->SetParName(0, "binWidth");
      dpdspFit->SetParName(1, "isDpDoubleGaus");	
      dpdspFit->SetParName(2, "isDsDoubleGaus");	
      dpdspFit->SetParName(3, "isSameCB");	
      dpdspFit->SetParName(4, "isMassDiff");
   	dpdspFit->SetParName(5, "nSignal1");
      dpdspFit->SetParName(6, "mu1");	
      dpdspFit->SetParName(7, "rms_width1");	
      dpdspFit->SetParName(8, "sigma_11");	
      dpdspFit->SetParName(9, "gaus_frac11");	
      dpdspFit->SetParName(10, "CB_alpha1");	
      dpdspFit->SetParName(11, "CB_n1");	
      dpdspFit->SetParName(12, "nSignal2");	
      if (isMassDiff) {
         dpdspFit->SetParName(13, "massDiff");	
      } else {
         dpdspFit->SetParName(13, "mu2");
      }   
      dpdspFit->SetParName(14, "rms_width2");	
      dpdspFit->SetParName(15, "sigma_21");	
      dpdspFit->SetParName(16, "gaus_frac21");	
      dpdspFit->SetParName(17, "CB_alpha2");	
      dpdspFit->SetParName(18, "CB_n2");	
      dpdspFit->SetParName(19, "exp_int");
      dpdspFit->SetParName(20, "exp_coef");
      dpdspFit->SetParName(21, "sigma12");	
      dpdspFit->SetParName(22, "gaus_frac12");	
      dpdspFit->SetParName(23, "sigma22");
      dpdspFit->SetParName(24, "gaus_frac22");
      dpdspFit->SetLineColor(kRed);
      dpdspFit->SetLineWidth(3);


   firstGaus1Fit = new TF1("firstGaus1Fit",Gaussian,fitStart,fitEnd, 6);		
      firstGaus1Fit->SetLineColor(kSpring-6);
      firstGaus1Fit->SetLineStyle(8);
      firstGaus1Fit->SetLineWidth(3);
   firstGaus2Fit = new TF1("firstGaus2Fit",Gaussian,fitStart,fitEnd, 6);		
      firstGaus2Fit->SetLineColor(kMagenta+1);
      firstGaus2Fit->SetLineStyle(8);
      firstGaus2Fit->SetLineWidth(3);
   firstCBFit = new TF1("firstCBFit", CB, fitStart, fitEnd, 8);
      firstCBFit->SetLineColor(kAzure-1);
      firstCBFit->SetLineStyle(5);
      firstCBFit->SetLineWidth(3);

   secondGaus1Fit = new TF1("secondGaus1Fit",Gaussian,fitStart,fitEnd, 6);		
      secondGaus1Fit->SetLineColor(kSpring-6);
      secondGaus1Fit->SetLineStyle(8);
      secondGaus1Fit->SetLineWidth(3);
   secondGaus2Fit = new TF1("secondGaus2Fit",Gaussian,fitStart,fitEnd, 6);		
      secondGaus2Fit->SetLineColor(kMagenta+1);
      secondGaus2Fit->SetLineStyle(8);
      secondGaus2Fit->SetLineWidth(3);
   secondCBFit = new TF1("secondCBFit", CB, fitStart, fitEnd, 8);
      secondCBFit->SetLineColor(kAzure-1);
      secondCBFit->SetLineStyle(5);
      secondCBFit->SetLineWidth(3);

   backgroundFit = new TF1("backgroundFit",backgroundExp,fitStart,fitEnd, 2);
      backgroundFit->SetParNames("exp_int","exp_coef");
      backgroundFit->SetLineColor(kOrange+7);
      backgroundFit->SetLineStyle(2);
      backgroundFit->SetLineWidth(3);



   dpdspHist = new TH1D("dpdspHist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit",nBins,fitStart,fitEnd);
      dpdspHist->SetStats(0);
      dpdspHist->SetTitleFont(43);
      dpdspHist->SetTitleSize(35);
		//*********NEED TO FIX BELOW LINE TO CHANGE PER binWidth INPUT**********
      dpdspHist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");
      dpdspHist->SetMinimum(10);//set min to 100 for logy so it doesnt break and ignore uninteresting stuff
		if (binWidth < 1) {dpdspHist->SetMinimum(10);}
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

void FinalCuts::SlaveBegin(TTree * /*tree*/) {}

Bool_t FinalCuts::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);
   GetEntry(entry);

   //***************LOOP SECTION***************
	Bool_t takeData = ((*particle_MM < cutoffMass) && (*isDp == 1)) || ((*particle_MM >= cutoffMass) && (*isDp == 0));
	Bool_t goodPolarity = ((takeMagUp && (*Polarity == 1)) || (takeMagDown && (*Polarity == -1)));

	Double_t particle_P = TMath::Sqrt(TMath::Power(*particle_PX,2) + TMath::Power(*particle_PY,2) + TMath::Power(*particle_PZ,2))/1000;
	Bool_t goodMomentum = ((particle_P >= P_LOWER) && (particle_P < P_UPPER));

	if (takeData && goodPolarity && goodMomentum)
	{
		dpdspHist->Fill(*particle_MM);
	}
   return kTRUE;
}

void FinalCuts::SlaveTerminate() {}

void FinalCuts::Terminate()
{
   //***************FINALIZATION SECTION***************

   //calculate first guess approximations for parameters
	Int_t nSignal1Guess = 0;
	Int_t nSignal2Guess = 0;
   if (takeMagUp && takeMagDown) {
      //numbers from perviously made graphs
      nSignal1Guess = 4200000;//4200000
      nSignal2Guess = 7200000;//7200000
   } else {
      //if only taking one polarity, approximately 1/2
      nSignal1Guess = 2100000;
      nSignal2Guess = 3600000;
   }
   Double_t firstBin = dpdspHist->GetBinContent(1);//used for exp_int guess
   Double_t lastBin = dpdspHist->GetBinContent(nBins);
   Double_t expCoefGuess = (lastBin-firstBin)/(nBins*500);//might need to address this division



   //put in fixed parameters for fit settings
   dpdspFit->FixParameter(0, binWidth);
   dpdspFit->FixParameter(1, isFirstPeakDoubleGaus);
   dpdspFit->FixParameter(2, isSecondPeakDoubleGaus);
   dpdspFit->FixParameter(3, isSameCB);
   dpdspFit->FixParameter(4, isMassDiff);
   //first signal main parameters
   dpdspFit->SetParameter(5, nSignal1Guess);
   dpdspFit->SetParameter(6, 1869);//approx Dplus mass
   dpdspFit->SetParameter(7, 6);//rms width
   dpdspFit->SetParameter(8, 7);//sigma
   dpdspFit->SetParameter(9, 0.7);//fraction in first gaus
      dpdspFit->SetParLimits(9, 0.000001, 0.999999);//ensure between 0 and 1
   dpdspFit->SetParameter(10, 2);//CB alpha
		dpdspFit->SetParLimits(10, 0, 10);
   dpdspFit->SetParameter(11, 3);//CB n
		dpdspFit->SetParLimits(11, 1.000001, 15);
   //second signal main parameters
   dpdspFit->SetParameter(12, nSignal2Guess);
   if (isMassDiff) {
      dpdspFit->SetParameter(13, 98);//approx mass difference
   } else {
      dpdspFit->SetParameter(13, 1969);//approx Ds mass
   }
   dpdspFit->SetParameter(14, 6);//rms width
   dpdspFit->SetParameter(15, 7);//sigma
   dpdspFit->SetParameter(16, 0.7);//fraction in first gaus
      dpdspFit->SetParLimits(16, 0.000001, 0.999999);//ensure between 0 and 1
   dpdspFit->SetParameter(17, 2);//CB alpha
		dpdspFit->SetParLimits(17, 0, 10);
   dpdspFit->SetParameter(18, 3);//CB n
		dpdspFit->SetParLimits(18, 1.000001, 15);
   //background parameters
   dpdspFit->SetParameter(19, firstBin);//exp_int
		//dpdspFit->SetParLimits(19, firstBin-20, firstBin+20);
   dpdspFit->SetParameter(20, expCoefGuess);
   //extra parameters for double gaussians
   if (isFirstPeakDoubleGaus) {
      dpdspFit->SetParameter(21, 10);//sigma2 of peak1
		dpdspFit->SetParLimits(21,1,15);
      dpdspFit->SetParameter(22, 0.05);//fraction in second gaus
         dpdspFit->SetParLimits(22, 0.000001, 0.25);//small between 0 and 1
   } else {
      //make 0s so that the fit function still takes something, though meaningless
      dpdspFit->FixParameter(21, 0);
      dpdspFit->FixParameter(22, 0);
   }
   if (isSecondPeakDoubleGaus) {
      dpdspFit->SetParameter(23, 10);//sigma2 of peak1
		dpdspFit->SetParLimits(23,1,15);
      dpdspFit->SetParameter(24, 0.05);//fraction in second gaus
         dpdspFit->SetParLimits(24, 0.000001, 0.25);//small between 0 and 1
   } else {
      //make 0s so that the fit function still takes something, though meaningless
      dpdspFit->FixParameter(23, 0);
      dpdspFit->FixParameter(24, 0);
   }


   //setup the canvas
   auto totalPullCan = new TCanvas("totalPullCan", "totalPullCan", 1400, 800);
      TPad *pad1 = new TPad("pad1","pad1",0,0.25,0.75,1.0);//for the main hist
      TPad *pad2 = new TPad("pad2","pad2",0,0.0,0.75,0.25);//for the pull plot
      TPad *pad3 = new TPad("pad3","pad3",0.75,0.0,1.0,1.0);//for info
         pad1->Draw();//main pad with mass plot
         pad2->Draw();//pull plot pad
         pad3->Draw();//output information pad

   pad1->cd();
      pad1->SetBottomMargin(0);
      pad1->SetLeftMargin(0.15);
      pad1->SetRightMargin(0.05);
      pad1->SetLogy();
      pad1->SetGridy();

      dpdspHist->Fit("dpdspFit","R");//fit the data


      //get the parameters for isolated fitting
      //first signal primaries
      Double_t nSignalPeak1 = dpdspFit->GetParameter(5);
      Double_t muPeak1 = dpdspFit->GetParameter(6);
      Double_t rmsPeak1 = dpdspFit->GetParameter(7);
      Double_t sigmaGaus1Peak1 = dpdspFit->GetParameter(8);
      Double_t f1Peak1 = dpdspFit->GetParameter(9);
      Double_t CB_alphaPeak1 = dpdspFit->GetParameter(10);
      Double_t CB_nPeak1 = dpdspFit->GetParameter(11);

      //second signal primaries
      Double_t nSignalPeak2 = dpdspFit->GetParameter(12);
		Double_t muPeak2 = 0;
		Double_t massDiff = 0;
      if (isMassDiff) {
            massDiff = dpdspFit->GetParameter(13);
            muPeak2 = massDiff + muPeak1;
      } else {
            muPeak2 = dpdspFit->GetParameter(13);
      }
      Double_t rmsPeak2 = dpdspFit->GetParameter(14);
      Double_t sigmaGaus1Peak2 = dpdspFit->GetParameter(15);
      Double_t f1Peak2 = dpdspFit->GetParameter(16);
      Double_t CB_alphaPeak2 = (isSameCB) ? dpdspFit->GetParameter(10) : dpdspFit->GetParameter(17);
      Double_t CB_nPeak2 = (isSameCB) ? dpdspFit->GetParameter(11) : dpdspFit->GetParameter(18);

      //exponential background
      Double_t exp_int = dpdspFit->GetParameter(19);
      Double_t exp_coef = dpdspFit->GetParameter(20);

      //extra gaussians
      Double_t sigmaGaus2Peak1 = dpdspFit->GetParameter(21);
      Double_t f2Peak1 = dpdspFit->GetParameter(22);
      Double_t sigmaGaus2Peak2 = dpdspFit->GetParameter(23);
      Double_t f2Peak2 = dpdspFit->GetParameter(24);


      //manually fill each part of the fit function
      //first primary gaussian
		firstGaus1Fit->SetParameter(0, binWidth);
		firstGaus1Fit->SetParameter(1, nSignalPeak1);
		firstGaus1Fit->SetParameter(2, muPeak1);
		firstGaus1Fit->SetParameter(3, rmsPeak1);
		firstGaus1Fit->SetParameter(4, sigmaGaus1Peak1);
		firstGaus1Fit->SetParameter(5, f1Peak1);
      //first secondary gaussian
		firstGaus2Fit->SetParameter(0, binWidth);
		firstGaus2Fit->SetParameter(1, nSignalPeak1);
		firstGaus2Fit->SetParameter(2, muPeak1);
		firstGaus2Fit->SetParameter(3, rmsPeak1);
		firstGaus2Fit->SetParameter(4, sigmaGaus2Peak1);
		firstGaus2Fit->SetParameter(5, f2Peak1);
      //first Crystal Ball
      firstCBFit->SetParameter(0, binWidth);
      firstCBFit->SetParameter(1, nSignalPeak1);
		firstCBFit->SetParameter(2, muPeak1);
		firstCBFit->SetParameter(3, rmsPeak1);
		firstCBFit->SetParameter(4, sigmaGaus1Peak1);
		firstCBFit->SetParameter(5, f1Peak1+f2Peak1);//f2 = 0 if no second gaus
		firstCBFit->SetParameter(6, CB_alphaPeak1);
		firstCBFit->SetParameter(7, CB_nPeak1);

      //second primary gaussian
		secondGaus1Fit->SetParameter(0, binWidth);
		secondGaus1Fit->SetParameter(1, nSignalPeak2);
		secondGaus1Fit->SetParameter(2, muPeak2);
		secondGaus1Fit->SetParameter(3, rmsPeak2);
		secondGaus1Fit->SetParameter(4, sigmaGaus1Peak2);
		secondGaus1Fit->SetParameter(5, f1Peak2);
      //second secondary gaussian
		secondGaus2Fit->SetParameter(0, binWidth);
		secondGaus2Fit->SetParameter(1, nSignalPeak2);
		secondGaus2Fit->SetParameter(2, muPeak2);
		secondGaus2Fit->SetParameter(3, rmsPeak2);
		secondGaus2Fit->SetParameter(4, sigmaGaus2Peak2);
		secondGaus2Fit->SetParameter(5, f2Peak2);
      //second Crystal Ball
	 	secondCBFit->SetParameter(0, binWidth);
	  	secondCBFit->SetParameter(1, nSignalPeak2);
		secondCBFit->SetParameter(2, muPeak2);
		secondCBFit->SetParameter(3, rmsPeak2);
		secondCBFit->SetParameter(4, sigmaGaus1Peak2);
		secondCBFit->SetParameter(5, f1Peak2+f2Peak2);//f2 = 0 if no second gaus
		secondCBFit->SetParameter(6, CB_alphaPeak2);
		secondCBFit->SetParameter(7, CB_nPeak2);

      //exponential background
		backgroundFit->SetParameter(0,exp_int);
		backgroundFit->SetParameter(1,exp_coef);


      //draw all the plots on pad1 (the main pad)
      dpdspHist->Draw();
      firstGaus1Fit->Draw("same");
      firstCBFit->Draw("same");
      secondGaus1Fit->Draw("same");
      secondCBFit->Draw("same");
      backgroundFit->Draw("same");
		if (isFirstPeakDoubleGaus) {firstGaus2Fit->Draw("same");}
		if (isSecondPeakDoubleGaus) {secondGaus2Fit->Draw("same");}


	pad2->cd();
		pad2->SetTopMargin(0);
		pad2->SetBottomMargin(0.4);
		pad2->SetLeftMargin(0.15);
		pad2->SetRightMargin(0.05);
		pad2->SetGridx();

      //create and draw the pull plot
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
		pad3->SetBottomMargin(0);
		pad3->SetLeftMargin(-0.15);
		pad3->SetRightMargin(0);

      auto fitlegend = new TLegend(00,0.8,0.8,0.95);//(0.7,0.7,0.9,0.9);
         fitlegend->SetTextSize(0.06);
         fitlegend->AddEntry(dpdspFit, "Total Fit", "l");
         fitlegend->AddEntry(firstGaus1Fit, "Gaussian_{1} Fit", "l");
         if (isFirstPeakDoubleGaus || isSecondPeakDoubleGaus) {
            fitlegend->AddEntry(firstGaus2Fit, "Gaussian_{2} Fit", "l");
         }
         fitlegend->AddEntry(firstCBFit, "CB Fit", "l");
         fitlegend->AddEntry(backgroundFit, "Exp Fit", "l");
         fitlegend->Draw();


      //generating strings for the output information
      TString binWidthStr;
         binWidthStr.Form("%3.3f\n",binWidth);
      TString cutoffMassStr;
         cutoffMassStr.Form("%5.0d\n",cutoffMass);

      TString nSignalPeak1Str;
			TString nSignalPeak1Strpm;
			nSignalPeak1Str.Form("%5.0f\n",nSignalPeak1);
			nSignalPeak1Strpm.Form("%5.0f\n",dpdspFit->GetParError(5));
		TString muPeak1Str;
			TString muPeak1Strpm;
			muPeak1Str.Form("%5.6f\n",muPeak1);
			muPeak1Strpm.Form("%5.6f\n",dpdspFit->GetParError(6));
		TString rmsPeak1Str;
			TString rmsPeak1Strpm;
			rmsPeak1Str.Form("%5.3f\n",rmsPeak1);
			rmsPeak1Strpm.Form("%5.3f\n",dpdspFit->GetParError(7));
      TString sigmaGaus1Peak1Str;
			TString sigmaGaus1Peak1Strpm;
			sigmaGaus1Peak1Str.Form("%5.3f\n",sigmaGaus1Peak1);
			sigmaGaus1Peak1Strpm.Form("%5.3f\n",dpdspFit->GetParError(8));
		TString f1Peak1Str;
			TString f1Peak1Strpm;
			f1Peak1Str.Form("%5.3f\n",f1Peak1);
			f1Peak1Strpm.Form("%5.3f\n",dpdspFit->GetParError(9));
		TString CB_alphaPeak1Str;
			TString CB_alphaPeak1Strpm;
			CB_alphaPeak1Str.Form("%5.3f\n",CB_alphaPeak1);
			CB_alphaPeak1Strpm.Form("%5.3f\n",dpdspFit->GetParError(10));
		TString CB_nPeak1Str;
			TString CB_nPeak1Strpm;
			CB_nPeak1Str.Form("%5.3f\n",CB_nPeak1);
			CB_nPeak1Strpm.Form("%5.3f\n",dpdspFit->GetParError(11));

		TString nSignalPeak2Str;
			TString nSignalPeak2Strpm;
			nSignalPeak2Str.Form("%5.0f\n",nSignalPeak2);
			nSignalPeak2Strpm.Form("%5.0f\n",dpdspFit->GetParError(12));
		TString massDiffStr;
		TString massDiffStrpm;
        TString muPeak2Str;
        TString muPeak2Strpm;
      if (isMassDiff) {
            massDiffStr.Form("%5.6f\n",massDiff);
            massDiffStrpm.Form("%5.6f\n",dpdspFit->GetParError(13));
      } else {
            muPeak2Str.Form("%5.6f\n",muPeak2);
            muPeak2Strpm.Form("%5.6f\n",dpdspFit->GetParError(13));
      }
		TString rmsPeak2Str;
			TString rmsPeak2Strpm;
			rmsPeak2Str.Form("%5.3f\n",rmsPeak2);
			rmsPeak2Strpm.Form("%5.3f\n",dpdspFit->GetParError(14));	
		TString sigmaGaus1Peak2Str;
			TString sigmaGaus1Peak2Strpm;
			sigmaGaus1Peak2Str.Form("%5.3f\n",sigmaGaus1Peak2);
			sigmaGaus1Peak2Strpm.Form("%5.3f\n",dpdspFit->GetParError(15));
		TString f1Peak2Str;
			TString f1Peak2Strpm;
			f1Peak2Str.Form("%5.3f\n",f1Peak2);
			f1Peak2Strpm.Form("%5.3f\n",dpdspFit->GetParError(16));
		TString CB_alphaPeak2Str;
			TString CB_alphaPeak2Strpm;
			CB_alphaPeak2Str.Form("%5.3f\n",CB_alphaPeak2);
		if (isSameCB) {
			CB_alphaPeak2Strpm.Form("%5.3f\n",dpdspFit->GetParError(10));
		} else {
			CB_alphaPeak2Strpm.Form("%5.3f\n",dpdspFit->GetParError(17));
		}
		TString CB_nPeak2Str;
			TString CB_nPeak2Strpm;
			CB_nPeak2Str.Form("%5.3f\n",CB_nPeak2);
		if (isSameCB) {
			CB_nPeak2Strpm.Form("%5.3f\n",dpdspFit->GetParError(11));
		} else {
			CB_nPeak2Strpm.Form("%5.3f\n",dpdspFit->GetParError(18));
		}
		TString expIntStr;
			TString expIntStrpm;
			expIntStr.Form("%5.3f\n",exp_int);
			expIntStrpm.Form("%5.3f\n",dpdspFit->GetParError(19));
		TString expCoefStr;
			TString expCoefStrpm;
			expCoefStr.Form("%.3e\n",exp_coef);
			expCoefStrpm.Form("%.3e\n",dpdspFit->GetParError(20));

	//strings for extra gaussians
		TString sigmaGaus2Peak1Str;
			TString sigmaGaus2Peak1Strpm;
			sigmaGaus2Peak1Str.Form("%5.3f\n",sigmaGaus2Peak1);
			sigmaGaus2Peak1Strpm.Form("%5.3f\n",dpdspFit->GetParError(21));
		TString f2Peak1Str;
			TString f2Peak1Strpm;
			f2Peak1Str.Form("%5.3f\n",f2Peak1);
			f2Peak1Strpm.Form("%5.3f\n",dpdspFit->GetParError(22));
		TString sigmaGaus2Peak2Str;
			TString sigmaGaus2Peak2Strpm;
			sigmaGaus2Peak2Str.Form("%5.3f\n",sigmaGaus2Peak2);
			sigmaGaus2Peak2Strpm.Form("%5.3f\n",dpdspFit->GetParError(23));
		TString f2Peak2Str;
			TString f2Peak2Strpm;
			f2Peak2Str.Form("%5.3f\n",f2Peak2);
			f2Peak2Strpm.Form("%5.3f\n",dpdspFit->GetParError(24));





      
      //write all of the information strings
      auto lt = new TLatex();
			lt->SetTextSize(0.05);
			lt->DrawLatexNDC(0, 0.776, "D^{+} Signal Events = "+nSignalPeak1Str+" #pm "+nSignalPeak1Strpm);
			lt->DrawLatexNDC(0, 0.75, "m(D^{+}) = "+muPeak1Str+" #pm "+muPeak1Strpm+" MeV/c^{2}");
			lt->DrawLatexNDC(0, 0.72, "D^{+} RMS Width = "+rmsPeak1Str+" #pm "+rmsPeak1Strpm);
			lt->DrawLatexNDC(0, 0.69, "D^{+} #sigma_{1} = "+sigmaGaus1Peak1Str+" #pm "+sigmaGaus1Peak1Strpm);
			lt->DrawLatexNDC(0, 0.66, "D^{+} Fraction Gaus_{1} = "+f1Peak1Str+" #pm "+f1Peak1Strpm);
				if (isFirstPeakDoubleGaus) {
					lt->DrawLatexNDC(0.05, 0.63, "D_{s} #sigma_2 = "+sigmaGaus2Peak1Str+" #pm "+sigmaGaus2Peak1Strpm);
					lt->DrawLatexNDC(0.05, 0.60, "D_{s} Fraction Gaus_{2} = "+f2Peak1Str+" #pm "+f2Peak1Strpm);
				} else {
					lt->DrawLatexNDC(0.05,0.63, "No second gaussian");
					lt->DrawLatexNDC(0.05,0.60, "No second gaussian");
				}

			lt->DrawLatexNDC(0, 0.57, "D^{+} CB alpha = "+CB_alphaPeak1Str+" #pm "+CB_alphaPeak1Strpm);
			lt->DrawLatexNDC(0, 0.54, "D^{+} CB n = "+CB_nPeak1Str+" #pm "+CB_nPeak1Strpm);


			lt->DrawLatexNDC(0, 0.49, "D_{s} Signal Events = "+nSignalPeak2Str+" #pm "+nSignalPeak2Strpm);
         if (isMassDiff) {
            lt->DrawLatexNDC(0, 0.46, "m(D_{s} - D^{+}) = "+massDiffStr+" #pm "+massDiffStrpm+" MeV/c^{2}");
         } else {
			   lt->DrawLatexNDC(0, 0.46, "m(D_{s}) = "+muPeak2Str+" #pm "+muPeak2Strpm+" MeV/c^{2}");
         }
         lt->DrawLatexNDC(0, 0.43, "D_{s} RMS Width = "+rmsPeak2Str+" #pm "+rmsPeak2Strpm);
         lt->DrawLatexNDC(0, 0.40, "D_{s} #sigma_{1} = "+sigmaGaus1Peak2Str+" #pm "+sigmaGaus1Peak2Str);
			lt->DrawLatexNDC(0, 0.37, "D_{s} Fraction Gaus_{1} = "+f1Peak2Str+" #pm "+f1Peak2Strpm);

				if (isSecondPeakDoubleGaus) {
					lt->DrawLatexNDC(0.05, 0.34, "D_{s} #sigma_{2} = "+sigmaGaus2Peak2Str+" #pm "+sigmaGaus2Peak2Strpm);
					lt->DrawLatexNDC(0.05, 0.31, "D_{s} Fraction Gaus_{2} = "+f2Peak2Str+" #pm "+f2Peak2Strpm);
				} else {
					lt->DrawLatexNDC(0.05,0.34, "No second gaussian");
					lt->DrawLatexNDC(0.05,0.31, "No second gaussian");
				}

			lt->DrawLatexNDC(0, 0.28, "D_{s} CB alpha = "+CB_alphaPeak2Str+" #pm "+CB_alphaPeak2Strpm);
			lt->DrawLatexNDC(0, 0.25, "D_{s} CB n = "+CB_nPeak2Str+" #pm "+CB_nPeak2Strpm);


			lt->DrawLatexNDC(0, 0.20, "Exp Int. = "+expIntStr+" #pm "+expIntStrpm);
			lt->DrawLatexNDC(0, 0.17, "Exp Coef. = "+expCoefStr+" #pm "+expCoefStrpm);

			lt->DrawLatexNDC(0,0.12, "Bin Width: "+binWidthStr+" MeV");
			lt->DrawLatexNDC(0,0.09, "Cutoff mass: "+cutoffMassStr+" MeV");
			if (isSameCB) {lt->DrawLatexNDC(0,0.06, "Same CB parameters");}
			if (takeMagUp) {lt->DrawLatexNDC(0,0.03, "Mag up data");}
			if (takeMagDown) {lt->DrawLatexNDC(0.3,0.03, "Mag down data");}











      




   totalPullCan->cd();
      //create a string to save the file name as something roughly unique and identifiying

      string massDiffStr2 = (isMassDiff) ? "MassDiff_" : "DoubleMass_";
      string cutOffMassStr = to_string(cutoffMass)+"MeVcutoff_";
      string magUpStr = (takeMagUp) ? "MagUp_" : "";
      string magDownStr = (takeMagDown) ? "MagDown_" : "";
      string firstDoubleGausStr = (isFirstPeakDoubleGaus) ? "DoubleGaus_" : "SingleGaus_";
      string secondDoubleGausStr = (isSecondPeakDoubleGaus) ? "DoubleGaus_" : "SingleGaus_";
      string sameCBStr = (isSameCB) ? "sameCB_" : "diffCB_";

      TString fileName = "finalImages/"+extraFileStr+"_DpDspFit_"+massDiffStr2+magUpStr+magDownStr+firstDoubleGausStr
                        +secondDoubleGausStr+sameCBStr+"ExpBG.png";

   totalPullCan->SaveAs(fileName);

}
