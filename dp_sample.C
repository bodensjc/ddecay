#define dp_sample_cxx
#include "dp_sample.h"
#include <TH2.h>
#include <TStyle.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"



TH1 * dptotalcuthist = NULL;
TH1 * totalcutpull = NULL;
TF1 * myDpFit = NULL;

Int_t binmax = 1950;//1950
Int_t binmin = 1790;//1790
Int_t nbins = binmax-binmin;



void dp_sample::Begin(TTree * /*tree*/)
{
   TString option = GetOption();





myDpFit = new TF1("myDpFit",fit1MeV_GaussianPlusCBWithExp_redo,1819,1919, 9);// maybe 1800, 1930 or so instead of binX
   myDpFit->SetParNames("nSignal", "mu", "rms_wdth", "sigma_1", "gaus_frac", "exp_int","exp_coef","CB_alpha","CB_n");
  myDpFit->SetLineColor(kRed+1);
  myDpFit->SetLineWidth(2);




dptotalcuthist = new TH1D("D^{+} cuts","D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit",100,1819,1919);
   //dptotalcuthist->GetXaxis()->SetTitle("D^{+} Mass [MeV/c^{2}]");
	dptotalcuthist->SetStats(0);
    dptotalcuthist->SetTitleFont(43);
    dptotalcuthist->SetTitleSize(35);
    dptotalcuthist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");
    dptotalcuthist->SetMinimum(10);//make minimum 1 so logy doesnt break
    dptotalcuthist->GetYaxis()->SetTitleFont(43);
	dptotalcuthist->GetYaxis()->SetTitleSize(30);
	dptotalcuthist->GetYaxis()->CenterTitle(true);



totalcutpull = new TH1D("total cut pull plot", "Pull Plot",100,1819,1919);
	totalcutpull->SetStats(0);
	totalcutpull->GetYaxis()->SetTitle("Pull");
	totalcutpull->GetYaxis()->SetTitleSize(30);
	totalcutpull->GetYaxis()->SetTitleFont(43);
	totalcutpull->GetYaxis()->CenterTitle(true);
	totalcutpull->GetYaxis()->SetLabelSize(0.1);
	totalcutpull->GetXaxis()->SetTitle("D^{+} mass [MeV/c^{2}]");
	//totalcutpull->GetXaxis()->SetTitle("m(K^{+} K^{-} #pi^{+}) [MeV/c^{2}]");
	totalcutpull->GetXaxis()->SetTitleSize(30);
	totalcutpull->GetXaxis()->SetTitleFont(43);
	totalcutpull->GetXaxis()->CenterTitle(true);
	totalcutpull->GetXaxis()->SetLabelSize(0.15);
	totalcutpull->GetXaxis()->SetTitleOffset(4);
	totalcutpull->SetFillColor(kBlue);
	totalcutpull->SetLineColor(kBlue);
	totalcutpull->SetBit(TH1::kNoTitle);
	totalcutpull->GetYaxis()->SetNdivisions(7);





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
  Double_t lastbin = dptotalcuthist->GetBinContent(100-1);//used for slope guess

dptotalcuthist->SetMaximum(1.1*maxbin);

  Double_t nSignalGuess = (maxbin-firstbin)*15;
  Double_t expCoefGuess = (lastbin-firstbin)/100;

  myDpFit->SetParameter(0,nSignalGuess);//nSignal
  myDpFit->SetParameter(1,1869);//mu
  myDpFit->SetParameter(2,4.);//rms of double gaussian
  //myDpFit->SetParLimits(2,0.,20.);
  myDpFit->SetParameter(3,7);//sigma_1 of primary gaussian
  myDpFit->SetParameter(4,0.85);//fraction of signal in primary gaussian
  myDpFit->SetParameter(5,firstbin);//exp intercept
  myDpFit->SetParameter(6,expCoefGuess);//coefficient background exponential
  myDpFit->SetParameter(7, 1.5);//crystal ball alpha
  myDpFit->SetParameter(8,2.5);//crystal ball n
  //myDpFit->SetParLimits(8,1.00001,6.);




auto totalpullcan = new TCanvas("totalpullcan", "totalpullcan", 1000, 800);

TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1.0);
TPad *pad2 = new TPad("pad2","pad2",0,0.0,1,0.25);
	pad1->Draw();
	pad2->Draw();

pad1->cd();
	pad1->SetBottomMargin(0);
	pad1->SetLeftMargin(0.15);
	pad1->SetLogy();



dptotalcuthist->Fit("myDpFit","RL");
dptotalcuthist->Draw();
myDpFit->Draw("same");




/*
auto dplegend = new TLegend(0.7,0.75,0.91,0.9);
	dplegend->AddEntry(dptotalcuthist, "D^{+}  Data ", "r");
	dplegend->AddEntry(myDpFit, "Signal Fit", "l");
dplegend->Draw("same");
*/

/*
pad2->cd();
pad2->SetTopMargin(0);
 pad2->SetBottomMargin(0.4);
 pad2->SetLeftMargin(0.15);
 pad2->SetGridx();



 Double_t xVals[100];
 Double_t yVals[100];
 for (Int_t i=1;i<100;i++) {
 Double_t x = dptotalcuthist->GetBinCenter(i);
 Double_t val = myDpFit->Eval(dptotalcuthist->GetBinCenter(i));
 Double_t sigma = sqrt(val);
 Double_t pull = (dptotalcuthist->GetBinContent(i)-val)/sigma;
 totalcutpull->SetBinContent(i,pull);
   xVals[i]=x;
   yVals[i]=pull;
   }
totalcutpull->Draw();


totalpullcan->cd();

totalpullcan->SaveAs("image/dp_fit_makeSelector.png");
*/








}
