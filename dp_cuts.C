#define dp_cuts_cxx
#include "dp_cuts.h"
#include <TH2.h>
#include <TStyle.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"


//**************** Definition Section **************
TH1 * totalcuthist = NULL;
TH1 * totalcutpull = NULL;

TF1 * myDpFit = NULL;

TF1 * signalfit = NULL;
TF1 * backgroundfit = NULL;



void dp_cuts::Begin(TTree * /*tree*/)
{
TString option = GetOption();


//************** Initialization Section ************
myDpFit = new TF1("myDpFit",fit1MeV_GaussianPlusCBWithExp_redo,1819,1919, 9);
	myDpFit->SetParNames("nSignal", "mu", "rms_wdth", "sigma_1", "gaus_frac", "exp_int","exp_coef","CB_alpha","CB_n");
	myDpFit->SetLineColor(kRed+1);
	myDpFit->SetLineWidth(2);


signalfit = new TF1("signalfit",primaryGaussian,1819,1919, 9);
	signalfit->SetParNames("nSignal", "mu", "rms_wdth", "sigma_1", "gaus_frac", "exp_int","exp_coef","CB_alpha","CB_n");
	signalfit->SetLineColor(kGreen+1);
	signalfit->SetLineStyle(8);
	signalfit->SetLineWidth(2);


backgroundfit = new TF1("backgroundfit",backgroundCB,1819,1919, 9);
	backgroundfit->SetParNames("nSignal", "mu", "rms_wdth", "sigma_1", "gaus_frac", "exp_int","exp_coef","CB_alpha","CB_n");
	backgroundfit->SetLineColor(kBlack);
	backgroundfit->SetLineStyle(2);
	backgroundfit->SetLineWidth(2);


totalcuthist = new TH1D("D^{+} cuts","D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit",100,1819,1919);
	totalcuthist->SetStats(0);
	totalcuthist->SetTitleFont(43);
	totalcuthist->SetTitleSize(35);
	totalcuthist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");
	totalcuthist->SetMinimum(10);//make minimum 1 so logy doesnt break
	totalcuthist->GetYaxis()->SetTitleFont(43);
	totalcuthist->GetYaxis()->SetTitleSize(30);
	totalcuthist->GetYaxis()->CenterTitle(true);


totalcutpull = new TH1D("total cut pull plot", "Pull Plot", 100,1819,1919);
	totalcutpull->SetStats(0);
	totalcutpull->GetYaxis()->SetTitle("Pull");
	totalcutpull->GetYaxis()->SetTitleSize(30);
	totalcutpull->GetYaxis()->SetTitleFont(43);
	totalcutpull->GetYaxis()->CenterTitle(true);
	totalcutpull->GetYaxis()->SetLabelSize(0.1);
	totalcutpull->GetXaxis()->SetTitle("D^{+} mass [MeV/c^{2}]");
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



void dp_cuts::SlaveBegin(TTree * /*tree*/) {}



Bool_t dp_cuts::Process(Long64_t entry)
{
	fReader.SetLocalEntry(entry);
	GetEntry(entry);
//*************** Loop Section ********************
	totalcuthist->Fill(*Dplus_MM);

	return kTRUE;
}



void dp_cuts::SlaveTerminate() {}



void dp_cuts::Terminate()
{
 //**************** Wrap-up Section ****************


Double_t maxbin = totalcuthist->GetBinContent(totalcuthist->GetMaximumBin());
Double_t firstbin = totalcuthist->GetBinContent(1);//used for intercept guess
Double_t lastbin = totalcuthist->GetBinContent(99);//used for slope guess
Double_t nSignalGuess = (maxbin-firstbin)*15;
Double_t expCoefGuess = (lastbin-firstbin)/100;

cout << "signal guess is: " << nSignalGuess << endl;

myDpFit->SetParameter(0,nSignalGuess);//nSignal
	myDpFit->SetParLimits(0,100000,140000);//this is a yikes... need to address
	myDpFit->SetParameter(1,1869);//mu
	myDpFit->SetParameter(2,4.);//rms of double gaussian
	myDpFit->SetParLimits(2,0.,20.);
	myDpFit->SetParameter(3,7);//sigma_1 of primary gaussian
	myDpFit->SetParameter(4,0.85);//fraction of signal in primary gaussian
	myDpFit->SetParLimits(4,0.001,0.099999);
	myDpFit->SetParameter(5,firstbin);//exp intercept
	myDpFit->SetParameter(6,expCoefGuess);//coefficient background exponential
	myDpFit->SetParameter(7, 1.5);//crystal ball alpha
	myDpFit->SetParameter(8,2.5);//crystal ball n
	myDpFit->SetParLimits(8,1.00001,6.);


auto totalpullcan = new TCanvas("totalpullcan", "totalpullcan", 1000, 800);
 // gStyle->SetOptStat(11);
TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1.0);
TPad *pad2 = new TPad("pad2","pad2",0,0.0,1,0.25);
	pad1->Draw();
	pad2->Draw();



pad1->cd();
	pad1->SetBottomMargin(0);
	pad1->SetLeftMargin(0.15);
	pad1->SetLogy();//comment this line out to have a non-log plot




totalcuthist->Fit("myDpFit","RL");

Double_t nSignal  = myDpFit->GetParameter(0);
Double_t mu       = myDpFit->GetParameter(1);
Double_t rms      = myDpFit->GetParameter(2);
Double_t sigma1   = myDpFit->GetParameter(3);
Double_t f        = myDpFit->GetParameter(4);
//Double_t sigma2sq = (rms*rms - f*sigma1*sigma1)/(1-f);
//Double_t sigma2   = TMath::Sqrt(sigma2sq);
Double_t exp_int    = myDpFit->GetParameter(5);
Double_t exp_coef    = myDpFit->GetParameter(6);
//skip bin width because const
Double_t CB_alpha = myDpFit->GetParameter(7);
Double_t CB_n     = myDpFit->GetParameter(8);


signalfit->SetParameter(0,nSignal);//nSignal
	signalfit->SetParameter(1,mu);//mu
	signalfit->SetParameter(2,rms);//rms of double gaussian
	signalfit->SetParameter(3,sigma1);//sigma_1 of primary gaussian
	signalfit->SetParameter(4,f);//fraction of signal in primary gaussian
	signalfit->SetParameter(5,exp_int);
	signalfit->SetParameter(6,exp_coef);
	signalfit->SetParameter(7,CB_alpha);
	signalfit->SetParameter(8,CB_n);



backgroundfit->SetParameter(0,nSignal);
	backgroundfit->SetParameter(1,mu);
	backgroundfit->SetParameter(2,rms);
	backgroundfit->SetParameter(3,sigma1);
	backgroundfit->SetParameter(4,f);
	backgroundfit->SetParameter(5,exp_int);
	backgroundfit->SetParameter(6,exp_coef);
	backgroundfit->SetParameter(7,CB_alpha);
	backgroundfit->SetParameter(8,CB_n);


totalcuthist->Draw();
signalfit->Draw("same");
backgroundfit->Draw("same");


TString muStr;
	TString muStrpm;
	muStr.Form("%5.6f\n",mu);
	muStrpm.Form("%5.6f\n",myDpFit->GetParError(1));
TString nSignalStr;
	TString nSignalStrpm;
	nSignalStr.Form("%5.0f\n",nSignal);
	nSignalStrpm.Form("%5.0f\n",myDpFit->GetParError(0));


auto lt = new TLatex();
	lt->SetTextSize(0.03);
	lt->DrawLatexNDC(0.62, 0.55, "#mu = "+muStr+" #pm "+muStrpm+" MeV/c^{2}");//0.62 for y if not log
	lt->DrawLatexNDC(0.62, 0.50, "Signal Events = "+nSignalStr+" #pm "+nSignalStrpm);//0.57 for y if not log


auto fitlegend = new TLegend(0.7,0.7,0.9,0.9);
	fitlegend->AddEntry(myDpFit, "Total Fit", "l");
	fitlegend->AddEntry(signalfit, "Signal Fit", "l");
	fitlegend->AddEntry(backgroundfit, "Background Fit", "l");
	fitlegend->Draw();



pad2->cd();
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.4);
	pad2->SetLeftMargin(0.15);
	pad2->SetGridx();


 Double_t xVals[100];
 Double_t yVals[100];
 for (Int_t i=1;i<100;i++) {
 Double_t x = totalcuthist->GetBinCenter(i);
 Double_t val = myDpFit->Eval(totalcuthist->GetBinCenter(i));
 Double_t sigma = sqrt(val);
 Double_t pull = (totalcuthist->GetBinContent(i)-val)/sigma;
 totalcutpull->SetBinContent(i,pull);
   xVals[i]=x;
   yVals[i]=pull;
   }
totalcutpull->Draw();




	totalpullcan->cd();
	totalpullcan->SaveAs("image/dp_fit_makeSelector.png");
}

