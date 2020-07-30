#define dsp_cuts_cxx
#include "dsp_cuts.h"
#include <TH2.h>
#include <TStyle.h>
#include "scripts/fit1MeV_Gaussian.C"
#include "scripts/fit1MeV_GaussianPlusCBWithExp.C"


//	root -l /share/lazy/D2KKpi/Dsp2KKpi.root
//	root [1] _file0->cd("Ds2KKpi_Tuple");
//	root [2] DecayTree->Process("dp_cuts.C");


//**************Definition Section**************
TH1 * phicuthist = NULL;
TH1 * phicutbadhist = NULL;

TH1 * myDspFitHist = NULL;
TF1 * myDspFit = NULL;


TH1 * totalcuthist = NULL;
TH1 * totalcutrejects = NULL;
TH1 * totalcutpull = NULL;

double_t phi_pm = 20;
double_t phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
double_t philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 

double_t kstar_pm = 50;
double_t kstar_upperbound = (895.55+kstar_pm)*(895.55+kstar_pm)/1000000;
double_t kstar_lowerbound = (895.55-kstar_pm)*(895.55-kstar_pm)/1000000;



void dsp_cuts::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
//**************Initialization Section***************
   phicuthist = new TH1D("phi cut","D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+} Cut on #phi(1020)", 100, 1919,2019);
   phicuthist->GetXaxis()->SetTitle("D^{+}_{s} Mass [MeV/c^{2}]");
   phicuthist->GetYaxis()->SetTitle("Events per MeV");
   phicuthist->SetMinimum(0);

   phicutbadhist = new TH1D("phi cut rejects","D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+} Cut on #phi(1020) REJECTS", 100, 1919,2019);
   phicutbadhist->GetXaxis()->SetTitle("D^{+}_{s} Mass [MeV/c^{2}]");
   phicutbadhist->GetYaxis()->SetTitle("Events per MeV");
   phicutbadhist->SetMinimum(0);

/*
   myDspFit = new TF1("myDspFit",fit1MeV_Gaussian, 1919, 2019, 5);
   myDspFit->SetParNames("p0", "mean", "width", "lin_b", "lin_m");
    myDspFit->SetParameter(0,100000.);
    myDspFit->SetParameter(1,1969);
    myDspFit->SetParameter(2,4.);
    myDspFit->SetParLimits(2,0.,20.);
    myDspFit->SetParameter(3,1000);
    myDspFit->SetParameter(4,0.);
*/

   myDspFit = new TF1("myDspFit",fit1MeV_GaussianPlusCBWithExp, 1919, 2019, 9);
   myDspFit->SetParNames("nSignal", "mu", "rms_wdth", "sigma_1", "gaus_frac", "exp_int","exp_coef","CB_alpha","CB_n");
  myDspFit->SetLineColor(kRed+1);
  myDspFit->SetLineWidth(3);

  myDspFit->SetParameter(0,10000);//nSignal
  myDspFit->SetParameter(1,1969);//mu
  myDspFit->SetParameter(2,4.);//rms of double gaussian
  myDspFit->SetParLimits(2,0.,20.);
  myDspFit->SetParameter(3,7);//sigma_1 of primary gaussian
  myDspFit->SetParameter(4,0.85);//fraction of signal in primary gaussian
  myDspFit->SetParLimits(4,0.001,0.0999);
  myDspFit->SetParameter(5,15);
  myDspFit->SetParameter(6,-0.004);//coefficient background exponential
  myDspFit->SetParameter(7, 1.5);//crystal ball alpha
  myDspFit->SetParameter(8,2.5);//crystal ball n
  myDspFit->SetParLimits(8,1.00001,5.);




   totalcuthist = new TH1D("D^{+}_{s} cuts","D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+} Cut on #phi(1020), log(probNN), and IP #chi^{2}", 100, 1919,2019);
   //totalcuthist->GetXaxis()->SetTitle("D^{+}_{s} Mass [MeV/c^{2}]");
totalcuthist->SetStats(0);
   totalcuthist->SetTitleFont(43);
   totalcuthist->SetTitleSize(35);
   totalcuthist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");
   totalcuthist->SetMinimum(0);
   totalcuthist->GetYaxis()->SetTitleFont(43);
totalcuthist->GetYaxis()->SetTitleSize(30);
 totalcuthist->GetYaxis()->CenterTitle(true);

   totalcutrejects = new TH1D("D^{+}_{s} cut rejects","D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+} Cut on #phi(1020), log(probNN), and IP #chi^{2} - REJECTS", 100, 1919,2019);
   totalcutrejects->GetXaxis()->SetTitle("D^{+}_{s} Mass [MeV/c^{2}]");
   totalcutrejects->GetYaxis()->SetTitle("Events per MeV/c^{2}");
   totalcutrejects->SetMinimum(0);

   totalcutpull = new TH1D("total cut pull plot", "Pull Plot", 100, 1919, 2019);
totalcutpull->SetStats(0);
 totalcutpull->GetYaxis()->SetTitle("Pull");
 totalcutpull->GetYaxis()->SetTitleSize(30);
 totalcutpull->GetYaxis()->SetTitleFont(43);
 totalcutpull->GetYaxis()->CenterTitle(true);
 totalcutpull->GetYaxis()->SetLabelSize(0.1);
   totalcutpull->GetXaxis()->SetTitle("D^{+}_{s} mass [MeV/c^{2}]");
   totalcutpull->GetXaxis()->SetTitleSize(30);
   totalcutpull->GetXaxis()->SetTitleFont(43);
   totalcutpull->GetXaxis()->CenterTitle(true);
   totalcutpull->GetXaxis()->SetLabelSize(0.15);
   totalcutpull->GetXaxis()->SetTitleOffset(4);
 totalcutpull->SetFillColor(kBlue);
 totalcutpull->SetLineColor(kBlue);
totalcutpull->SetBit(TH1::kNoTitle);


}

void dsp_cuts::SlaveBegin(TTree * /*tree*/) {}

Bool_t dsp_cuts::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);
   GetEntry(entry);
   //******************Loop Section****************
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


   Bool_t phicutpass = (mkpkm > philowerbound && mkpkm < phiupperbound);
   Bool_t probcutpass = (kminuslog > 5 && kpluslog > 5 && pipluslog > 0);//5, 5, 0 comes from section 3 of the paper saved in slack
Bool_t kstarcutpass = (mkmpi > kstar_lowerbound && mkmpi < kstar_upperbound);//k-pi+ invariant mass cut on k*892 resonance
   Bool_t ipchi2cutpass = (*D_splus_IPCHI2_OWNPV < 5);
Bool_t momentumcutpass = (*D_splus_P > 1000 && *D_splus_PT > 100 && *Kplus_P > 1000 && *Kplus_PT > 100 && *Kminus_P > 1000 && *Kminus_PT > 100 && *Piplus_P >1000 && *Piplus_PT > 100);//this cut has NO EFFECT
Bool_t fdchi2cutpass = (TMath::Log(*D_splus_FDCHI2_OWNPV) > 5 && TMath::Log(*D_splus_FDCHI2_OWNPV) < 11);



   if (mkpkm > philowerbound && mkpkm < phiupperbound) {
     phicuthist->Fill(*D_splus_M);
   } else {
     phicutbadhist->Fill(*D_splus_M);
   }


Bool_t resonancecutpass = (phicutpass || kstarcutpass);


   if (resonancecutpass && probcutpass && ipchi2cutpass && momentumcutpass) {
     totalcuthist->Fill(*D_splus_M);
   } else {
     totalcutrejects->Fill(*D_splus_M);
   }







   return kTRUE;
}

void dsp_cuts::SlaveTerminate() {}

void dsp_cuts::Terminate()
{
  //*******************Wrap-Up Section********************
/*
auto phican = new TCanvas("phican","phican",1600,800);

 phican->Divide(2,1);
 phican->cd(1);
 phicuthist->Fit("myDspFit");
 phicuthist->Draw();
 phican->cd(2);
 phicutbadhist->Fit("myDspFit");
 phicutbadhist->Draw();
 phican->SaveAs("image/dsp_phicut.png");

*/

/*
 auto totalcan = new TCanvas("totalcan", "totalcan", 1600, 800);
 totalcan->Divide(2,1);
 totalcan->cd(1);
 totalcan->SetLeftMargin(0.5);
 totalcuthist->Fit("myDspFit");
 totalcuthist->Draw();
 totalcan->cd(2);
 totalcutrejects->Draw();
 totalcan->SaveAs("image/dsp_totalcut.png");
*/






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
 totalcuthist->Fit("myDspFit","RL");
totalcuthist->Draw();

pad2->cd();
 Double_t xVals[100];
 Double_t yVals[100];
 for (Int_t i=1;i<100;i++) {
 Double_t x = totalcuthist->GetBinCenter(i);
 Double_t val = myDspFit->Eval(totalcuthist->GetBinCenter(i));
 Double_t sigma = sqrt(val);
 Double_t pull = (totalcuthist->GetBinContent(i)-val)/sigma;
 totalcutpull->SetBinContent(i,pull);
   xVals[i]=x;
   yVals[i]=pull;
   }
totalcutpull->Draw();


 totalpullcan->cd();
 totalpullcan->SaveAs("image/dsp_totalcut_pull.png");
}
