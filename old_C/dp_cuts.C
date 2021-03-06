#define dp_cuts_cxx
#include "dp_cuts.h"
#include <TH2.h>
#include <TStyle.h>
//#include "scripts/fit1MeV_Gaussian.C"
//#include "scripts/fit1MeV_GaussianPlusCBWithExp.C"
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"
//using namespace ROOT;


//	root -l /share/lazy/D2KKpi/Dp2KKpi.root
//      ROOT::EnableImplicitMT();
//	root [1] _file0->cd("D2KKpi_Tuple");
//	root [2] DecayTree->Process("dp_cuts.C");



//**************** Definition Section **************
TH1 * phicuthist = NULL;
TH1 * phicutbadhist = NULL;

TH1 * totalcuthist = NULL;
TH1 * totalcutrejects = NULL;

TH1 * totalcutpull = NULL;


TH1 * myDpFitHist = NULL;
TF1 * myDpFit = NULL;



const double_t phi_pm = 12;
const double_t phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double_t philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 

const double_t kstar_pm = 50;
const double_t kstar_upperbound = (895.55+kstar_pm)*(895.55+kstar_pm)/1000000;
const double_t kstar_lowerbound = (895.55-kstar_pm)*(895.55-kstar_pm)/1000000;


TH1 * probprodhist = NULL;
TF1 * signalfit = NULL;
TF1 * backgroundfit = NULL;



void dp_cuts::Begin(TTree * /*tree*/)
{


   TString option = GetOption();

//************** Initialization Section ************
phicuthist = new TH1D("phi cut","D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut on #phi(1020)", 100,1819,1919);
   phicuthist->GetXaxis()->SetTitle("D^{+} Mass [MeV/c^{2}]");
   phicuthist->GetYaxis()->SetTitle("Events per MeV");
   // phicuthist->SetMinimum(0);

   phicutbadhist = new TH1D("phi cut rejects","D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut on #phi(1020) REJECTS", 100,1819,1919);
   phicutbadhist->GetXaxis()->SetTitle("D^{+} Mass [MeV/c^{2}]");
   phicutbadhist->GetYaxis()->SetTitle("Events per MeV");
   phicutbadhist->SetMinimum(0);


   /*
   myDpFit = new TF1("myDpFit",fit1MeV_Gaussian, 1819, 1919, 5);
   myDpFit->SetParNames("p0", "mean", "width", "lin_b", "lin_m");
    myDpFit->SetParameter(0,100000.);
    myDpFit->SetParameter(1,1869);
    myDpFit->SetParameter(2,4.);
    myDpFit->SetParLimits(2,0.,20.);
    myDpFit->SetParameter(3,1000);
    myDpFit->SetParameter(4,0.);
   */


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



//    probprodhist = new TH1D("probprodhist", "ProbNN k,k,pi Product for K^{+} K^{-} #pi^{+}", 100, 0, 1);



totalcuthist = new TH1D("D^{+} cuts","D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit",100,1819,1919);
   //totalcuthist->GetXaxis()->SetTitle("D^{+} Mass [MeV/c^{2}]");
totalcuthist->SetStats(0);
   totalcuthist->SetTitleFont(43);
   totalcuthist->SetTitleSize(35);
   totalcuthist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");
   totalcuthist->SetMinimum(100);//make minimum 1 so logy doesnt break
   totalcuthist->GetYaxis()->SetTitleFont(43);
totalcuthist->GetYaxis()->SetTitleSize(30);
 totalcuthist->GetYaxis()->CenterTitle(true);

totalcutrejects = new TH1D("D^{+} cut rejects","D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut on #phi(1020), log(probNN), and IP #chi^{2} - REJECTS",100,1819,1919);
   totalcutrejects->GetXaxis()->SetTitle("D^{+} Mass [MeV/c^{2}]");
   totalcutrejects->GetYaxis()->SetTitle("Events per MeV/c^{2}");
   totalcutrejects->SetMinimum(0);



   totalcutpull = new TH1D("total cut pull plot", "Pull Plot", 100,1819,1919);
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



void dp_cuts::SlaveBegin(TTree * /*tree*/) {}



Bool_t dp_cuts::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);
   GetEntry(entry);
//*************** Loop Section ********************
   //filling the actual Lorentz Vectors
   TLorentzVector kpLV(*Kplus_PX, *Kplus_PY, *Kplus_PZ, *Kplus_PE);
   TLorentzVector kmLV(*Kminus_PX, *Kminus_PY, *Kminus_PZ, *Kminus_PE);
   TLorentzVector piLV(*Piplus_PX, *Piplus_PY, *Piplus_PZ, *Piplus_PE);
   //initializing the Lorentz Vectors for pairing
   TLorentzVector kpkmLV(kpLV + kmLV);
   TLorentzVector kppiLV(kpLV + piLV);
   TLorentzVector kmpiLV(kmLV + piLV);
   //calculating invariant mass pairs
   double_t mkpkm = kpkmLV.Mag2()/1000000;
   double_t mkppi = kppiLV.Mag2()/1000000;
   double_t mkmpi = kmpiLV.Mag2()/1000000;


TLorentzVector kpkmpiLV(kpkmLV + piLV);
double_t mkpkmpi = TMath::Sqrt(kpkmpiLV.Mag2());


   //probability stuff
   double_t kminusprobk = *Kminus_MC15TuneV1_ProbNNk;
   double_t kplusprobk = *Kplus_MC15TuneV1_ProbNNk;
   double_t piplusprobpi = *Piplus_MC15TuneV1_ProbNNpi;
   double_t probprod = kminusprobk*kplusprobk*piplusprobpi;
   double_t kminusprobpi = *Kminus_MC15TuneV1_ProbNNpi;
   double_t kplusprobpi = *Kplus_MC15TuneV1_ProbNNpi;
   double_t piplusprobk = *Piplus_MC15TuneV1_ProbNNk;
   //calculating the logdifs (needs to be larger than 5)
   double_t kminuslog = TMath::Log(kminusprobk) - TMath::Log(kminusprobpi);
   double_t kpluslog = TMath::Log(kplusprobk) - TMath::Log(kplusprobpi);
   double_t pipluslog = TMath::Log(piplusprobpi) - TMath::Log(piplusprobk);


   Bool_t phicutpass = (mkpkm > philowerbound && mkpkm < phiupperbound);//KK invariant mass pair ut on phi1020 resonance
Bool_t kstarcutpass = (mkmpi > kstar_lowerbound && mkmpi < kstar_upperbound);//k-pi+ invariant mass cut on k*892 resonance
   Bool_t probcutpass = (kminuslog > 5 && kpluslog > 5 && pipluslog > 0);//5, 5, 0 comes from section 3 of the paper saved in slack
   Bool_t ipchi2cutpass = (*Dplus_IPCHI2_OWNPV < 5);//not sure what exactly IPchi2 is... 
Bool_t momentumcutpass = (*Dplus_P > 1000 && *Dplus_PT > 100 && *Kplus_P > 1000 && *Kplus_PT > 100 && *Kminus_P > 1000 && *Kminus_PT > 100 && *Piplus_P >1000 && *Piplus_PT > 100);//this cut has NO EFFECT
 Bool_t fdchi2cutpass = (*Dplus_FDCHI2_OWNPV > 175);
//Bool_t ipchi2cutpass = (*Dplus_IPCHI2_OWNPV < 5 && *Kplus_IPCHI2_OWNPV > 9 && *Kminus_IPCHI2_OWNPV > 9 && *Piplus_IPCHI2_OWNPV > 9);


   if (mkpkm > philowerbound && mkpkm < phiupperbound) {
     phicuthist->Fill(*Dplus_M);
   }
   if (mkpkm <= philowerbound || mkpkm >= phiupperbound) {
     phicutbadhist->Fill(*Dplus_M);
   }


Bool_t resonancecutpass = (phicutpass || kstarcutpass);//dont cut on k*



   if (phicutpass && probcutpass && ipchi2cutpass && momentumcutpass && fdchi2cutpass) {
     totalcuthist->Fill(*Dplus_M);//*Dplus_M or mkpkmpi
   } else {
     totalcutrejects->Fill(*Dplus_M);
   }




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

  myDpFit->SetParameter(0,nSignalGuess);//nSignal
  myDpFit->SetParLimits(0,2500000,3500000);//this is a yikes... need to address
  myDpFit->SetParameter(1,1869);//mu
  myDpFit->SetParameter(2,4.);//rms of double gaussian
  myDpFit->SetParLimits(2,0.,20.);
  myDpFit->SetParameter(3,7);//sigma_1 of primary gaussian
  myDpFit->SetParameter(4,0.85);//fraction of signal in primary gaussian
  myDpFit->SetParLimits(4,0.001,0.09999999);
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
 lt->DrawLatexNDC(0.60, 0.35, "#mu = "+muStr+" #pm "+muStrpm+" MeV/c^{2}");//0.62 for y if not log
 lt->DrawLatexNDC(0.60, 0.30, "Signal Events = "+nSignalStr+" #pm "+nSignalStrpm);//0.57 for y if not log


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


 totalpullcan->SaveAs("image/dp_totalcut_pull_logy_magdown.png");

/*
auto sigcan = new TCanvas("sigcan", "sigcan", 1000, 800);
signalfit->Draw("RL");
backgroundfit->Draw("RLsame");
*/
}

