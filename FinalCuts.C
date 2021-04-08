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
Bool_t isFirstPeakDoubleGaus = 1; //1: double gaus in D+, 0: single
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