#define dp_sample_cxx
#include "dp_sample.h"
#include <TH2.h>
#include <TStyle.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"



TH1 * dptotalcuthist = NULL;
TF1 * myDpFit = NULL;

const Int_t binmax = 1960;
const Int_t binmin = 1790;
const Int_t nbins = binmax-binmin;



void dp_sample::Begin(TTree * /*tree*/)
{
   TString option = GetOption();





myDpFit = new TF1("myDpFit",fit1MeV_GaussianPlusCBWithExp_redo,binmin+1,binmax-1, 9);
   myDpFit->SetParNames("nSignal", "mu", "rms_wdth", "sigma_1", "gaus_frac", "exp_int","exp_coef","CB_alpha","CB_n");
  myDpFit->SetLineColor(kRed+1);
  myDpFit->SetLineWidth(2);




dptotalcuthist = new TH1D("D^{+} cuts","D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit",nbins,binmin,binmax);
	dptotalcuthist->SetStats(0);
    dptotalcuthist->SetTitleFont(43);
    dptotalcuthist->SetTitleSize(33);
    dptotalcuthist->GetYaxis()->SetTitle("Events / 1 MeV/c^{2}");//Candidates/(1 MeV/c^{2})
	dptotalcuthist->SetMinimum(0);//make >0 (100 or 1000) for logy plots
    dptotalcuthist->GetYaxis()->SetTitleFont(43);
	dptotalcuthist->GetYaxis()->SetTitleSize(35);
	dptotalcuthist->GetYaxis()->CenterTitle(true);
    dptotalcuthist->GetXaxis()->SetTitle("m(K^{+}K^{-}#pi^{+}) [MeV]");//"m(K^{+}K^{-}#pi^{+}) [MeV]"
    dptotalcuthist->GetXaxis()->SetTitleFont(43);
	dptotalcuthist->GetXaxis()->SetTitleSize(30);
	dptotalcuthist->GetXaxis()->CenterTitle(true);
	dptotalcuthist->SetLineColor(kRed);
	dptotalcuthist->SetLineWidth(3);
	dptotalcuthist->GetXaxis()->SetTitleOffset(1.4);



}




void dp_sample::SlaveBegin(TTree * /*tree*/) {}





Bool_t dp_sample::Process(Long64_t entry)
{

	fReader.SetLocalEntry(entry);
	GetEntry(entry);


dptotalcuthist->Fill(*Dplus_MM);



   return kTRUE;
}




void dp_sample::SlaveTerminate() {}




void dp_sample::Terminate()
{

  Double_t maxbin = dptotalcuthist->GetBinContent(dptotalcuthist->GetMaximumBin());
  Double_t firstbin = dptotalcuthist->GetBinContent(1);//used for intercept guess
  Double_t lastbin = dptotalcuthist->GetBinContent(99);//used for slope guess

  Double_t nSignalGuess = (maxbin-firstbin)*15;
  Double_t expCoefGuess = (lastbin-firstbin)/100;

  myDpFit->SetParameter(0,nSignalGuess);//nSignal
  myDpFit->SetParameter(1,1869);//mu
  myDpFit->SetParameter(2,4.);//rms of double gaussian
  myDpFit->SetParLimits(2,0.,20.);
  myDpFit->SetParameter(3,7);//sigma_1 of primary gaussian
  myDpFit->SetParameter(4,0.85);//fraction of signal in primary gaussian
  myDpFit->SetParameter(5,firstbin);//exp intercept
  myDpFit->SetParameter(6,expCoefGuess);//coefficient background exponential
  myDpFit->SetParameter(7, 1.5);//crystal ball alpha
  myDpFit->SetParameter(8,2.5);//crystal ball n
  myDpFit->SetParLimits(8,1.00001,6.);


auto dplegendliny = new TLegend(0.7,0.75,0.91,0.9);
	dplegendliny->AddEntry(dptotalcuthist, "D^{+}  Data ", "r");
	dplegendliny->AddEntry(myDpFit, "Signal Fit", "l");

auto totalpullcan = new TCanvas("totalpullcan", "totalpullcan", 1000, 800);
TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1.0);
pad1->cd();
pad1->SetBottomMargin(0);
pad1->SetLeftMargin(0.15);

dptotalcuthist->Fit("myDpFit","RL");
dptotalcuthist->Draw();

//dplegendliny->Draw("same");

totalpullcan->SaveAs("image/dp_fit_rdf.png");









}
