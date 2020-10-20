#define Dsp_Background_cxx
#include "Dsp_Background.h"
#include <TH2.h>
#include <TStyle.h>

//******************DEFINITION SECTION*********************
//~~~~~~~~~~~~~~~~~~~mass dsp~~~~~~~~~~~~~~~~~
//~~~~~~~~~mass Dp~~~~~~~~~~~
TH1 * mdspsig = NULL;
TH1 * mdspisb = NULL;
TH1 * mdsposb = NULL;
//~~~~~~~~~~~~~~~ phi 1020 ~~~~~~~~~~~~~~~~~~~~~
TH1 * phisighist = NULL;
TH1 * phiosbhist = NULL;
TH1 * phisubhist = NULL;
TH1 * phiratio = NULL;







TH1 * probsighist = NULL;
TH1 * probosbhist = NULL;
TH1 * probsubhist = NULL;
TH1 * probratio = NULL;



TH1 * fdchi2sighist = NULL;
TH1 * fdchi2osbhist = NULL;
TH1 * fdchi2subhist = NULL;
TH1 * fdchi2ratio = NULL;



TH1 * ipchi2sighist = NULL;
TH1 * ipchi2osbhist = NULL;
TH1 * ipchi2subhist = NULL;
TH1 * ipchi2ratio = NULL;



TH1 * kplusloghist = NULL;
TH1 * kminusloghist = NULL;
TH1 * piplusloghist = NULL;



void Dsp_Background::Begin(TTree * /*tree*/)
{

   TString option = GetOption();

 //*****************INITIALIZATION***************
//~~~~~~~~~~~~mass dsp~~~~~~~~~~~~~
   mdspsig = new TH1D("Signal Region","m(Ds+) with Background Regions",100,1919,2019);
 mdspsig->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
 mdspsig->GetYaxis()->SetTitle("events per MeV");
 //mdpsig->SetStats(0);
 mdspsig->SetFillColor(kBlue);
mdspisb = new TH1D("mdspisb","m(Ds+) inner side band",100,1919,2019);
 mdspisb->SetStats(0);
 mdspisb->SetFillColor(kYellow);
mdsposb = new TH1D("mdsposb","m(Ds+) outer side band",100,1919,2019);
 mdsposb->SetStats(0);
 mdsposb->SetFillColor(kRed);

 //~~~~~~~~~~~~~~~~~ phi 1020 ~~~~~~~~~~~~~~~~~~~~~
   phisighist = new TH1D("phisighist", "D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+}  cut on  #phi(1020)", 100, 1, 1.1);
   phisighist->GetXaxis()->SetTitle("m^{2}(K^{+}K^{-}) [GeV^{2}/c^{4}]");
   phisighist->GetYaxis()->SetTitle("Events per GeV^{2}/c^{4}");
   phisighist->SetStats(0);
   phisighist->SetLineColor(kBlue);

   phiosbhist = new TH1D("phiosbhist", "background events", 100, 1, 1.1);
   phiosbhist->SetStats(0);
   phiosbhist->SetLineColor(kRed);
   phisubhist = new TH1D("phisubhist", "background subtracted", 100, 1, 1.1);
   phisubhist->SetStats(0);
   phisubhist->SetLineColor(kGreen);





    probsighist = new TH1D("probsighist", "ProbNNk(K^{+})*ProbNNk(K^{-})*ProbNNpi(#pi^{+})", 100, 0, 1);
   probsighist->SetStats(0);
   probsighist->SetLineColor(kBlue);
   probsighist->GetXaxis()->SetTitle("Probability Product");
   probsighist->GetYaxis()->SetTitle("Events per 0.01 prob");

    probosbhist = new TH1D("probosbhist", "prob prod background", 100, 0, 1);
   probosbhist->SetStats(0);
   probosbhist->SetLineColor(kRed);
    probsubhist = new TH1D("probsubhist", "prob prod background subtracted", 100, 0, 1);
   probsubhist->SetStats(0);
   probsubhist->SetLineColor(kGreen);




    fdchi2sighist = new TH1D("fdchi2sighist", "D^{+}_{s}   Log(FD #chi^{2})", 100, 0, 20);
   fdchi2sighist->SetStats(0);
   fdchi2sighist->SetLineColor(kBlue);
   fdchi2sighist->GetXaxis()->SetTitle("unit of time/distance (?)");
   fdchi2sighist->GetYaxis()->SetTitle("Events per unit");
   //fdchi2sighist->SetMinimum(0);

    fdchi2osbhist = new TH1D("fdchi2osbhist", "fdchi2 background", 100, 0, 20);
   fdchi2osbhist->SetStats(0);
   fdchi2osbhist->SetLineColor(kRed);
    fdchi2subhist = new TH1D("fdchi2subhist", "fdchi2 background subtracted", 100, 0, 20);
   fdchi2subhist->SetStats(0);
   fdchi2subhist->SetLineColor(kGreen);




   ipchi2sighist = new TH1D("ipchi2sighist", "D^{+}_{s}   IP #chi^{2}", 100, 0, 20);
   ipchi2sighist->SetStats(0);
   ipchi2sighist->SetLineColor(kBlue);
   ipchi2sighist->GetXaxis()->SetTitle("unit of time/distance (?)");
   ipchi2sighist->GetYaxis()->SetTitle("Events per unit");
   //ipchi2sighist->SetMinimum(0);

   ipchi2osbhist = new TH1D("ipchi2osbhist", "ipchi2 background", 100, 0, 20);
   ipchi2osbhist->SetStats(0);
   ipchi2osbhist->SetLineColor(kRed);
   ipchi2subhist = new TH1D("ipchi2subhist", "ipchi2 background subtracted", 100, 0, 20);
   ipchi2subhist->SetStats(0);
   ipchi2subhist->SetLineColor(kGreen);





  kminusloghist = new TH1D("kminusloghist", "D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+},  #color[4]{K^{-}} (#color[2]{#pi^{+}}) log likelihood difference",80, -4, 12);
kminusloghist->GetXaxis()->SetTitle("log #frac{probNN#color[4]{k}(#color[2]{pi})}{probNN#color[4]{pi}(#color[2]{k})}");
kminusloghist->GetXaxis()->CenterTitle(true);
kminusloghist->GetXaxis()->SetTitleOffset(2);
kminusloghist->GetYaxis()->SetTitle("Events / 0.2 log difference");
kminusloghist->GetYaxis()->CenterTitle(true);
kminusloghist->SetStats(0);
kminusloghist->SetLineColor(kBlue);
kminusloghist->SetLineWidth(2);


   kplusloghist = new TH1D("kplusloghist", "K^{+} log(#frac{probNNk}{probNNpi})",80, -4, 12);
kplusloghist->SetStats(0);
kplusloghist->SetLineColor(kBlue);
kplusloghist->SetLineWidth(2);
kplusloghist->SetLineStyle(8);




   piplusloghist = new TH1D("piplusloghist", "D^{+} #rightarrow K^{+}K^{-}#pi^{+}, #pi^{+} log likelihood difference",80, -4, 12);
piplusloghist->GetXaxis()->SetTitle("log(#frac{probNNpi}{probNNk})");
piplusloghist->GetXaxis()->CenterTitle(true);
piplusloghist->GetXaxis()->SetTitleOffset(2);
piplusloghist->SetLineColor(kRed);
piplusloghist->SetLineWidth(2);
piplusloghist->SetStats(0);

}


void Dsp_Background::SlaveBegin(TTree * ) {}


Bool_t Dsp_Background::Process(Long64_t entry)
{
 fReader.SetLocalEntry(entry);//do NOT delete this line, otherwise the program will crash
  GetEntry(entry);
  //********************LOOP SECTION***************


   TLorentzVector kpLV(*Kplus_PX, *Kplus_PY, *Kplus_PZ, *Kplus_PE);
   TLorentzVector kmLV(*Kminus_PX, *Kminus_PY, *Kminus_PZ, *Kminus_PE);
   //initializing the Lorentz Vector for pairing
   TLorentzVector kpkmLV(kpLV + kmLV);
   //calculating invariant mass pair
   double_t mkpkm = kpkmLV.Mag2()/1000000;



   double_t kminusprobk = *Kminus_MC15TuneV1_ProbNNk;
   double_t kplusprobk = *Kplus_MC15TuneV1_ProbNNk;
   double_t piplusprobpi = *Piplus_MC15TuneV1_ProbNNpi;
   double_t probprod = kminusprobk*kplusprobk*piplusprobpi;
   double_t kminusprobpi = *Kminus_MC15TuneV1_ProbNNpi;
   double_t kplusprobpi = *Kplus_MC15TuneV1_ProbNNpi;
   double_t piplusprobk = *Piplus_MC15TuneV1_ProbNNk;

   double_t kminuslog = TMath::Log(kminusprobk) - TMath::Log(kminusprobpi);
   double_t kpluslog = TMath::Log(kplusprobk) - TMath::Log(kplusprobpi);
   double_t pipluslog = TMath::Log(piplusprobpi) - TMath::Log(piplusprobk);



  //fill signal bars
  if (*D_splus_M > 1958 && *D_splus_M < 1980) {
    phisighist->Fill(mkpkm);
   probsighist->Fill(probprod);
   fdchi2sighist->Fill(TMath::Log(*D_splus_FDCHI2_OWNPV));
   ipchi2sighist->Fill(*D_splus_IPCHI2_OWNPV);
   mdspsig->Fill(*D_splus_M);
  }
  //fill (outer) background bars
  if ((*D_splus_M < 1940 && *D_splus_M > 1918) || (*D_splus_M < 2020 && *D_splus_M > 1998)) {
    phiosbhist->Fill(mkpkm);
    probosbhist->Fill(probprod);
    fdchi2osbhist->Fill(TMath::Log(*D_splus_FDCHI2_OWNPV));
    ipchi2osbhist->Fill(*D_splus_IPCHI2_OWNPV);
    mdsposb->Fill(*D_splus_M);
  }

//inner side band
  if ((*D_splus_M < 1959 && *D_splus_M > 1939) || (*D_splus_M > 1979 && *D_splus_M < 1999)) {
    mdspisb->Fill(*D_splus_M);
  };


  //fill the log prob bars
  kminusloghist->Fill(kminuslog);
  kplusloghist->Fill(kpluslog);
  piplusloghist->Fill(pipluslog);


   return kTRUE;
}

void Dsp_Background::SlaveTerminate() {}

void Dsp_Background::Terminate()
{
  //*******************WRAP UP******************
/*


  //~~~~~~~~~~~~mdp~~~~~~~~~~~~~~~~~~~~~~
   auto c0 = new TCanvas("c0","c0",1600,1200);
auto mdsplegend = new TLegend(0.15,0.7,0.38,0.9);

mdspsig->Draw();
 mdsposb->Draw("same");
 mdspisb->Draw("same");

 mdsplegend->SetHeader("Regions","C"); // "c" centers header
   mdsplegend->AddEntry(mdspsig,"Signal Region","f");
   mdsplegend->AddEntry(mdspisb,"Inner Sideband","f");
   mdsplegend->AddEntry(mdsposb,"Outer Sideband","f");
   mdsplegend->Draw();
  c0->SaveAs("image/dsp_mdsp.png");




  //~~~~~~~~~~~~~~~~~ phi 1020 ~~~~~~~~~~~~~~~~
auto phican = new TCanvas("phican","phican",1700,1200);
auto philegend = new TLegend(0.55,0.7,0.85,0.9);


 phiosbhist->Add(phiosbhist, -0.5);
 phisubhist->Add(phisighist, phiosbhist, 1, -1);
 phisighist->Draw("e0 9");
 phiosbhist->Draw("e0same 9");
 phisubhist->Draw("e0same 9");
 phican->Update();
 phiratio = (TH1D*)phisighist->Clone();
 phiratio->SetName("phiratio");
   phiratio->SetStats(0);
   phiratio->SetLineColor(kViolet);
 phiratio->Divide(phiosbhist);
 float_t rightmax = 1.1*phiratio->GetMaximum();
 float_t scale = gPad->GetUymax()/rightmax;
 phiratio->Scale(scale);
 phiratio->Draw("hist L 9 same");


  philegend->SetHeader("Distributions","C");
  philegend->AddEntry(phisighist, "Signal m^{2}(K^{+}K^{-})", "l");
  philegend->AddEntry(phiosbhist, "Background m^{2}(K^{+}K^{-})", "l");
  philegend->AddEntry(phisubhist, "Background Subtracted m^{2}(K^{+}K^{-}) ", "l");
  philegend->AddEntry(phiratio, "Signal/Background Ratio", "l");
  philegend->Draw();


  auto axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), 
			   gPad->GetUxmax(),gPad->GetUymax(),
			   0, rightmax, 510, "+L");
  axis->SetLineColor(kViolet);
  axis->SetLabelColor(kViolet);
  axis->Draw();

  phican->SaveAs("image/dsp_phicut_bsub.png");






auto probcan = new TCanvas("probcan","probcan",1600,1200);
auto problegend = new TLegend(0.55,0.7,0.75,0.9);

 probosbhist->Add(probosbhist, -0.5);
 probsubhist->Add(probsighist, probosbhist, 1, -1);
 probsighist->Draw("e0");
 probosbhist->Draw("e0same");
 probsubhist->Draw("e0same");


 probcan->Update();
 probratio = (TH1D*)probsighist->Clone();
 probratio->SetName("probratio");
   probratio->SetStats(0);
   probratio->SetLineColor(kViolet);
 probratio->Divide(probosbhist);
 float_t probrightmax = 1.1*probratio->GetMaximum();
 float_t probscale = gPad->GetUymax()/probrightmax;
 probratio->Scale(probscale);
 probratio->Draw("hist L 9 same");



  problegend->SetHeader("Distributions","C");
  problegend->AddEntry(probsighist, "Signal Prob Prod", "l");
  problegend->AddEntry(probosbhist, "Background Prob Prod", "l");
  problegend->AddEntry(probsubhist, "Background Subtracted Prob Prod ", "l");
  problegend->AddEntry(probratio, "Signal/Background Ratio", "l");
  problegend->Draw();

  auto probaxis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), 
			   gPad->GetUxmax(),gPad->GetUymax(),
			   0, probrightmax, 510, "+L");
  probaxis->SetLineColor(kViolet);
  probaxis->SetLabelColor(kViolet);
  probaxis->Draw();

  probcan->SaveAs("image/dsp_probprodcut_bsub.png");






auto fdchi2can = new TCanvas("fdchi2can","fdchi2can",1600,1200);
auto fdchi2legend = new TLegend(0.55,0.7,0.75,0.9);

 fdchi2osbhist->Add(fdchi2osbhist, -0.5);
 fdchi2subhist->Add(fdchi2sighist, fdchi2osbhist, 1, -1);
 fdchi2sighist->Draw("e0");
 fdchi2osbhist->Draw("e0same");
 fdchi2subhist->Draw("e0same");


 fdchi2can->Update();
 fdchi2ratio = (TH1D*)fdchi2sighist->Clone();
 fdchi2ratio->SetName("fdchi2ratio");
   fdchi2ratio->SetStats(0);
   fdchi2ratio->SetLineColor(kViolet);
 fdchi2ratio->Divide(fdchi2osbhist);
 float_t fdchi2rightmax = 1.1*fdchi2ratio->GetMaximum();
 float_t fdchi2scale = gPad->GetUymax()/fdchi2rightmax;
 fdchi2ratio->Scale(fdchi2scale);
 fdchi2ratio->Draw("hist L 9 same");


  fdchi2legend->SetHeader("Distributions","C");
  fdchi2legend->AddEntry(fdchi2sighist, "Signal FD #chi^{2}", "l");
  fdchi2legend->AddEntry(fdchi2osbhist, "Background FD #chi^{2}", "l");
  fdchi2legend->AddEntry(fdchi2subhist, "Background Subtracted FD #chi^{2} ", "l");
  fdchi2legend->AddEntry(fdchi2ratio, "Signal/Background Ratio", "l");
  fdchi2legend->Draw();

  auto fdchi2axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), 
			   gPad->GetUxmax(),gPad->GetUymax(),
			   0, fdchi2rightmax, 510, "+L");
  fdchi2axis->SetLineColor(kViolet);
  fdchi2axis->SetLabelColor(kViolet);
  fdchi2axis->Draw();

  fdchi2can->SaveAs("image/dsp_fdchi2cut_bsub.png");




auto ipchi2can = new TCanvas("ipchi2can","ipchi2can",1600,1200);
auto ipchi2legend = new TLegend(0.55,0.7,0.75,0.9);

 ipchi2osbhist->Add(ipchi2osbhist, -0.5);
 ipchi2subhist->Add(ipchi2sighist, ipchi2osbhist, 1, -1);
 ipchi2sighist->Draw("e0");
 ipchi2osbhist->Draw("e0same");
 ipchi2subhist->Draw("e0same");


 ipchi2can->Update();
 ipchi2ratio = (TH1D*)ipchi2sighist->Clone();
 ipchi2ratio->SetName("ipchi2ratio");
   ipchi2ratio->SetStats(0);
   ipchi2ratio->SetLineColor(kViolet);
 ipchi2ratio->Divide(ipchi2osbhist);
 float_t ipchi2rightmax = 1.1*ipchi2ratio->GetMaximum();
 float_t ipchi2scale = gPad->GetUymax()/ipchi2rightmax;
 ipchi2ratio->Scale(ipchi2scale);
 ipchi2ratio->Draw("hist L 9 same");


  ipchi2legend->SetHeader("Distributions","C");
  ipchi2legend->AddEntry(ipchi2sighist, "Signal IP #chi^{2}", "l");
  ipchi2legend->AddEntry(ipchi2osbhist, "Background IP #chi^{2}", "l");
  ipchi2legend->AddEntry(ipchi2subhist, "Background Subtracted IP #chi^{2} ", "l");
  ipchi2legend->AddEntry(ipchi2ratio, "Signal/Background Ratio", "l");
  ipchi2legend->Draw();

  auto ipchi2axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), 
			   gPad->GetUxmax(),gPad->GetUymax(),
			   0, ipchi2rightmax, 510, "+L");
  ipchi2axis->SetLineColor(kViolet);
  ipchi2axis->SetLabelColor(kViolet);
  ipchi2axis->Draw();

  ipchi2can->SaveAs("image/dsp_ipchi2cut_bsub.png");




*/



  auto logcan = new TCanvas("logcan", "logcan", 600, 600);
logcan->SetTopMargin(0.11);
logcan->SetRightMargin(0.09);
logcan->SetLeftMargin(0.15);
logcan->SetBottomMargin(0.18);
  kminusloghist->Draw();
//kplusloghist->Draw("same");
  piplusloghist->Draw("same");
  logcan->SaveAs("image/dsp_kkpilogs.png");



}
