#define dp_CB_cxx
#include "dp_CB.h"
#include <TH2.h>
#include <TStyle.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp.C"
#include "scripts/fit1MeV_Gaussian.C"



TH1 * totalcuthist = NULL;
TH1 * totalcutpull = NULL;
TF1 * myDpFit = NULL;

double_t phiupperbound = 1.063899417;//bounds created by +-12MeV of phi mass 
double_t philowerbound = 1.014965577;//of 1019.455 then squared to match mkpkm


Double_t results[10];

  Double_t sigma;
  Double_t deltaSigma;
  Double_t mu;
  Double_t deltaMu;
  Double_t total;
  Double_t deltaTotal;
  Double_t frac;
  Double_t deltaFrac;
  Double_t sigma1;
  Double_t deltaSigma1;
  Double_t intercept;
  Double_t deltaIntercept;
  Double_t expSlope;
  Double_t deltaExpSlope;
  Double_t CB_n;
  Double_t delta_CB_n;
  Double_t CB_alpha;
  Double_t delta_CB_alpha;





void dp_CB::Begin(TTree * /*tree*/)
{
   TString option = GetOption();



   totalcuthist = new TH1D("D^{+} cuts","D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut on #phi(1020), log(probNN), and IP #chi^{2}", 100, 1819,1919);
   //totalcuthist->GetXaxis()->SetTitle("D^{+} Mass [MeV/c^{2}]");
   totalcuthist->SetTitleFont(43);
   totalcuthist->SetTitleSize(35);
   totalcuthist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");
   totalcuthist->SetMinimum(0);
   totalcuthist->GetYaxis()->SetTitleFont(43);
totalcuthist->GetYaxis()->SetTitleSize(30);
 totalcuthist->GetYaxis()->CenterTitle(true);




   totalcutpull = new TH1D("total cut pull plot", "Pull Plot", 100, 1819, 1919);
totalcutpull->SetStats(0);
 totalcutpull->GetYaxis()->SetTitle("Pull");
 totalcutpull->GetYaxis()->SetTitleSize(30);
 totalcutpull->GetYaxis()->SetTitleFont(43);
 totalcutpull->GetYaxis()->CenterTitle(true);
 totalcutpull->GetYaxis()->SetLabelSize(0.1);
   totalcutpull->GetXaxis()->SetTitle("D^{+} Mass [MeV/c^{2}]");
   totalcutpull->GetXaxis()->SetTitleSize(30);
   totalcutpull->GetXaxis()->SetTitleFont(43);
   totalcutpull->GetXaxis()->CenterTitle(true);
   totalcutpull->GetXaxis()->SetLabelSize(0.15);
   totalcutpull->GetXaxis()->SetTitleOffset(4);
 totalcutpull->SetFillColor(kBlue);
 totalcutpull->SetLineColor(kBlue);
totalcutpull->SetBit(TH1::kNoTitle);



   myDpFit = new TF1("myDpFit",fit1MeV_GaussianPlusCBWithExp, 1819, 1919, 9);
   myDpFit->SetParNames("nSignal", "mu", "rms_wdth", "sigma_1", "gaus_frac", "exp_int","exp_coef","CB_alpha","CB_n");
  myDpFit->SetLineColor(kRed+1);
  myDpFit->SetLineWidth(3);

  myDpFit->SetParameter(0,10000);//nSignal
  myDpFit->SetParameter(1,1869);//mu
  myDpFit->SetParameter(2,4.);//rms of double gaussian
  myDpFit->SetParLimits(2,0.,20.);
  myDpFit->SetParameter(3,7);//sigma_1 of primary gaussian
  myDpFit->SetParameter(4,0.85);//fraction of signal in primary gaussian
  myDpFit->SetParLimits(4,0.001,0.0999);
  myDpFit->SetParameter(5,15);
  myDpFit->SetParameter(6,-0.004);//coefficient background exponential
  myDpFit->SetParameter(7, 1.5);//crystal ball alpha
  myDpFit->SetParameter(8,2.5);//crystal ball n
  myDpFit->SetParLimits(8,1.00001,5.);

}

void dp_CB::SlaveBegin(TTree * /*tree*/) {}

Bool_t dp_CB::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);
   GetEntry(entry);

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
   Bool_t probcutpass = (kminuslog > 5 && kpluslog > 5 && pipluslog > 0);//5, 5, 0 comes from section 3 of the paper saved in slack
   Bool_t ipchi2cutpass = (*Dplus_IPCHI2_OWNPV < 5);//not sure what exactly IPchi2 is... 


   if (phicutpass && probcutpass && ipchi2cutpass) {
     totalcuthist->Fill(*Dplus_M);
   }




   return kTRUE;
}

void dp_CB::SlaveTerminate()
{
}

void dp_CB::Terminate()
{


auto totalpullcan = new TCanvas("totalpullcan", "totalpullcan", 1000, 800);
 // gStyle->SetOptStat(11);

TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1.0);
TPad *pad2 = new TPad("pad2","pad2",0,0.0,1,0.25);

pad1->SetBottomMargin(0);
 pad1->SetLeftMargin(0.15);
 pad1->SetGridx();
pad1->Draw();

pad2->SetTopMargin(0);
 pad2->SetBottomMargin(0.4);
 pad2->SetLeftMargin(0.15);
 pad2->SetGridx();
pad2->Draw();

pad1->cd();
 totalcuthist->Fit("myDpFit","RL");
totalcuthist->Draw();

pad2->cd();
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

 totalpullcan->SaveAs("image/dpCB_totalcut_pull.png");


  total = myDpFit->GetParameter(0);
  deltaTotal = myDpFit->GetParError(0);
  mu = myDpFit->GetParameter(1);
  deltaMu = myDpFit->GetParError(1);
  sigma = myDpFit->GetParameter(2);
  deltaSigma = myDpFit->GetParError(2);
  sigma1 = myDpFit->GetParameter(3);
  deltaSigma1 = myDpFit->GetParError(3);
  frac = myDpFit->GetParameter(4);
  deltaFrac = myDpFit->GetParError(4);
  intercept = myDpFit->GetParameter(5);
  deltaIntercept = myDpFit->GetParError(5);
  expSlope = myDpFit->GetParameter(6);
  deltaExpSlope = myDpFit->GetParError(6);
  CB_alpha = myDpFit->GetParameter(7);
  delta_CB_alpha = myDpFit->GetParError(7);
  CB_n = myDpFit->GetParameter(8);
  delta_CB_n = myDpFit->GetParError(8);

  results[0] = sigma;
  results[1] = deltaSigma;
  results[2] = mu;
  results[3] = deltaMu;
  results[4] = total;
  results[5] = deltaTotal;
  results[6] = sigma1;
  results[7] = deltaSigma1;
  results[8] = frac;
  results[9] = deltaFrac;

}
