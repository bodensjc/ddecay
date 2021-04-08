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

string extraStr = "x";//change this string to add something fancy to end of plot save file

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


//need to initialize these to resolve later confusions...
TString CBn2Str;
TString CBn2Strpm;
TString CBalpha2Str;
TString CBalpha2Strpm;







void FinalCuts::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   //***************INITIALIZATION SECTION***************

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
      dpdspHist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");
      dpdspHist->SetMinimum(100);//set min so logy doesnt break and ignore uninteresting stuff
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

	if (takeData && goodPolarity)
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
   if (takeMagUp && takeMagDown) {
      //numbers from perviously made graphs
      Int_t nSignal1Guess = 4000000;
      Int_t nSignal2Guess = 7000000;
   } else {
      //if only taking one polarity, approximately 1/2
      Int_t nSignal1Guess = 2000000;
      Int_t nSignal2Guess = 3500000;
   }
   Double_t firstBin = dpdspHist->GetBinContent(1);//used for exp_int guess
   Double_t lastBin = dpdspHist->GetBinContent(nBins);
   Double_t expCoefGuess = (lastBin-firstBin)/(nBins*1000);//might need to address this division


   //put in fixed parameters for fit settings
   dpdspFit->FixParameter(0, binWidth);
   dpdspFit->FixParameter(1, isFirstPeakDoubleGaus);
   dpdspFit->FixParameter(2, isSecondPeakDoubleGaus);
   dpdspFit->FixParameter(3, isSameCB);
   dpdspFit->FixParameter(4, isMassDiff);
   //first signal main parameters
   dpdspFit->SetParameter(5, nSignal1Guess);
   dpdspFit->SetParameter(6, 1869);//approx Dplus mass
   dpdspFit->SetParameter(7, 4);//rms width
   dpdspFit->SetParameter(8, 7);//sigma
   dpdspFit->SetParameter(9, 0.6);//fraction in first gaus
      dpdspFit->SetParLimits(9, 0.000001, 0.999999);//ensure between 0 and 1
   dpdspFit->SetParameter(10, 1.5);//CB alpha
   dpdspFit->SetParameter(11, 2.5);//CB n
   //second signal main parameters
   dpdspFit->SetParameter(12, nSignal2Guess);
   if (isMassDiff) {
      dpdspFit->SetParameter(13, 98);//approx mass difference
   } else {
      dpdspFit->SetParameter(13, 1969);//approx Ds mass
   }
   dpdspFit->SetParameter(14, 4);//rms width
   dpdspFit->SetParameter(15, 7);//sigma
   dpdspFit->SetParameter(16, 0.6);//fraction in first gaus
      dpdspFit->SetParLimits(16, 0.000001, 0.999999);//ensure between 0 and 1
   dpdspFit->SetParameter(17, 1.5);//CB alpha
   dpdspFit->SetParameter(18, 2.5);//CB n
   //background parameters
   dpdspFit->SetParameter(19, firstBin);//exp_int
   dpdspFit->SetParameter(20, expCoefGuess);
   //extra parameters for double gaussians
   if (isFirstPeakDoubleGaus) {
      dpdspFit->SetParameter(21, 8);//sigma2 of peak1
      dpdspFit->SetParameter(22, 0.05);//fraction in second gaus
         dpdspFit->SetParLimits(22, 0.000001, 0.25);//small between 0 and 1
   } else {
      //make 0s so that the fit function still takes something, though meaningless
      dpdspFit->SetParameter(21, 0);
      dpdspFit->SetParameter(22, 0);
   }
   if (isSecondPeakDoubleGaus) {
      dpdspFit->SetParameter(23, 8);//sigma2 of peak1
      dpdspFit->SetParameter(24, 0.05);//fraction in second gaus
         dpdspFit->SetParLimits(24, 0.000001, 0.25);//small between 0 and 1
   } else {
      //make 0s so that the fit function still takes something, though meaningless
      dpdspFit->SetParameter(23, 0);
      dpdspFit->SetParameter(24, 0);
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
      if (isMassDiff) {
            Double_t massDiff = dpdspFit->GetParameter(13);
      } else {
            Double_t muPeak2 = dpdspFit->GetParameter(13);
      }
      Double_t rmsPeak2 = dpdspFit->GetParameter(14);
      Double_t sigmaGaus1Peak2 = dpdspFit->GetParameter(15);
      Double_t f1Peak2 = dpdspFit->GetParameter(16);
      Double_t CB_alphaPeak2 = dpdspFit->GetParameter(17);
      Double_t CB_nPeak2 = dpdspFit->GetParameter(18);
      /*this might be the better way of doing it. need to test
      Double_t CB_alphaPeak2 = (isSameCB) ? dpdspFit->GetParameter(10) : dpdspFit->GetParameter(17);
      Double_t CB_nPeak2 = (isSameCB) ? dpdspFit->GetParameter(11) : dpdspFit->GetParameter(18);
      */

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
      //first secondary faussian
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
      //second secondary faussian
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

      auto fitlegend = new TLegend(00,0.77,0.8,0.925);//(0.7,0.7,0.9,0.9);
         fitlegend->SetTextSize(0.08);
         fitlegend->AddEntry(dpdspFit, "Total Fit", "l");
         fitlegend->AddEntry(firstGaus1Fit, "Primary Gaus Fit", "l");
         if (isFirstPeakDoubleGaus || isSecondPeakDoubleGaus) {
            fitlegend->AddEntry(firstGaus2Fit, "Secondary Gaus Fit", "l");
         }
         fitlegend->AddEntry(firstCBFit, "CB Fit", "l");
         fitlegend->AddEntry(backgroundFit, "Exp Fit", "l");
         fitlegend->Draw();


      //generating strings for the output information
      TString nSignal1Str;
			TString nSignal1Strpm;
			nSignal1Str.Form("%5.0f\n",nSignalPeak1);
			nSignal1Strpm.Form("%5.0f\n",dpdspFit->GetParError(5));
		TString mu1Str;
			TString mu1Strpm;
			mu1Str.Form("%5.6f\n",muPeak1);
			mu1Strpm.Form("%5.6f\n",dpdspFit->GetParError(6));
		TString rmsWidth1Str;
			TString rmsWidth1Strpm;
			rmsWidth1Str.Form("%5.3f\n",rmsPeak1);
			rmsWidth1Strpm.Form("%5.3f\n",dpdspFit->GetParError(7));
      TString sigma1Peak1Str;
			TString rmsWidth1Strpm;
			rmsWidth1Str.Form("%5.3f\n",rms1);
			rmsWidth1Strpm.Form("%5.3f\n",dpdspFit->GetParError(8));
		TString gaus_frac1Peak1Str;
			TString gaus_frac1Strpm;
			gaus_frac1Str.Form("%5.3f\n",f1);
			gaus_frac1Strpm.Form("%5.3f\n",dpdspFit->GetParError(9));
		TString CBalpha1Str;
			TString CBalpha1Strpm;
			CBalpha1Str.Form("%5.3f\n",CB_alpha1);
			CBalpha1Strpm.Form("%5.3f\n",dpdspFit->GetParError(10));
		TString CBn1Str;
			TString CBn1Strpm;
			CBn1Str.Form("%5.3f\n",CB_n1);
			CBn1Strpm.Form("%5.3f\n",dpdspFit->GetParError(11));











   //create a string to save the file name as something roughly unique and identifiying
   string massDiffStr = (isMassDiff) ? "MassDiff_" : "DoubleMass_";
   string binWidthStr = to_string(binWidth)+"MeV_";
   string cutOffMassStr = to_string(cutoffMass)+"MeVcutoff_";
   string magUpStr = (takeMagUp) ? "MagUp_" : "";
   string magDownStr = (takeMagDown) ? "MagDown_" : "";
   string firstDoubleGausStr = (isFirstPeakDoubleGaus) ? "DoubleGaus_" : "SingleGaus_";
   string secondDoubleGausStr = (isSecondPeakDoubleGaus) ? "DoubleGaus_" : "SingleGaus_";
   string sameCBStr = (isSameCB) ? "sameCB_" : "diffCB_";

   string fileName = "image/DpDspFit_"+massDiffStr+magUpStr+magDownStr+firstDoubleGausStr
                     +secondDoubleGausStr+sameCBStr+"ExpBG_"+extraStr+".png";

   totalPullCan->SaveAs(fileName);
}