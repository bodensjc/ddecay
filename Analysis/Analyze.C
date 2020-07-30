#define Analyze_cxx
#include "Analyze.h"
#include <TH2.h>
#include <TStyle.h>
#include <vector>

//**************** Definition Section **************
//~~~~~~~~~mass Dp~~~~~~~~~~~
TH1 * mdpsig = NULL;
TH1 * mdpisb = NULL;
TH1 * mdposb = NULL;

//~~~~~~~~~~~~~~~~~~~minPT~~~~~~~~~~~~~~~
TH1 * bsubhist = NULL;
TH1 * sighist = NULL;
TH1 * usbhist = NULL;
TH1 * lsbhist = NULL;
TH1 * esthist = NULL;

//~~~~~~~~~~~FDchi2~~~~~~~~~~~~~~~~~~~
TH1 * fdsig = NULL;
TH1 * fdusb = NULL;
TH1 * fdlsb = NULL;
TH1 * fdest = NULL;
TH1 * fdsub = NULL;

//~~~~~~~~~~~~~~~~~~NN probs~~~~~~~~~~~~~~~~~~
TH1 * piprobhist = NULL;
TH1 * pisigpi = NULL;
TH1 * piusbpi = NULL;
TH1 * pilsbpi = NULL;
TH1 * piestpi = NULL;
TH1 * pisubpi = NULL;



void Analyze::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

//************** Initialization Section ************

//~~~~~~~~~~~~mass dp~~~~~~~~~~~~~
   mdpsig = new TH1D("Signal Region","m(D+) with Background Regions",100,1819,1919);
 mdpsig->GetXaxis()->SetTitle("Mass [MeV/c^2]");
 mdpsig->GetYaxis()->SetTitle("events per MeV");
 //mdpsig->SetStats(0);
 mdpsig->SetFillColor(kBlue);
mdpisb = new TH1D("mdpisb","m(D+) inner side band",100,1819,1919);
 mdpisb->SetStats(0);
 mdpisb->SetFillColor(kYellow);
mdposb = new TH1D("mdposb","m(D+) outer side band",100,1819,1919);
 mdposb->SetStats(0);
 mdposb->SetFillColor(kRed);


//~~~~~~~~~~~~~~~~~minPT~~~~~~~~~~~~~~~~~~~~~~~~~~~
 sighist = new TH1D("sighist","D+ -> KKpi Signal Region min PT",100,0,2500);//goes up to about 4750 but cutting at 2500
 sighist->GetXaxis()->SetTitle("PT [MeV]");
 sighist->GetYaxis()->SetTitle("events per 25 MeV");
 sighist->SetLineColor(kBlue);
 sighist->SetStats(0);

 usbhist = new TH1D("usbhist", "Upper Side Band", 100, 0, 2500);
 lsbhist = new TH1D("lsbhist", "Lower Side Band", 100, 0, 2500);
 esthist = new TH1D("esthist","Estimated Signal Error Bar Graph",100,0,2500);
 esthist->SetLineColor(kRed);
 esthist->SetStats(0);

 bsubhist = new TH1D("bsubhist","Subtracted Error Bar Graph",100,0,2500);
 bsubhist->SetLineColor(kGreen);
 bsubhist->SetStats(0);


 //~~~~~~~~~~~~~~~FD chi2~~~~~~~~~~~~~~~~~~

 fdsig = new TH1D("Signal Region FD_Chi2", "D+ -> KKpi  FDChi2", 100, 0, 5000);
 fdsig->GetXaxis()->SetTitle("unit of time or distance(?)");
 fdsig->GetYaxis()->SetTitle("events");
 fdsig->SetLineColor(kBlue);

fdusb = new TH1D("fdusb", "upper side band", 100, 0, 5000);
fdlsb = new TH1D("fdlsb", "lower side band", 100, 0, 5000);
fdest = new TH1D("fdest", "estimate background", 100, 0, 5000);
 fdest->SetLineColor(kRed);

fdsub = new TH1D("fdsub", "background subtracted", 100, 0, 5000);
 fdsub->SetLineColor(kGreen);


 //~~~~~~~~~~~~~~~~NN probs~~~~~~~~~~~~~~~~~~~~~~
 piprobhist = new TH2F("piprobhist","Pi probNN pi v. K",20,0,1,20,0,1);
  piprobhist->GetXaxis()->SetTitle("ProbNNpi");
  piprobhist->GetYaxis()->SetTitle("ProbNNk");
  piprobhist->SetStats(0);


  pisigpi = new TH1D("pisigpi", "D+ -> KKpi Pi+ Signal Region ProbNNpi",50,0,1);
  pisigpi->GetXaxis()->SetTitle("prob");
  pisigpi->GetYaxis()->SetTitle("events");
  pisigpi->SetStats(0);
  pisigpi->SetLineColor(kBlue);

piusbpi = new TH1D("piusbpi", "Upper side band",50,0,1);
pilsbpi = new TH1D("pilsbpi", "Lower side band",50,0,1);
 piestpi = new TH1D("piestpi", "estimated error",50,0,1);
 piestpi->SetStats(0);
 piestpi->SetLineColor(kRed);

 pisubpi = new TH1D("pisubpi","background subtracted",50,0,1);
 pisubpi->SetStats(0);
 pisubpi->SetLineColor(kGreen);


}

void Analyze::SlaveBegin(TTree * ) {}

Bool_t Analyze::Process(Long64_t entry)
{
  fReader.SetLocalEntry(entry);//do NOT delete this line, otherwise the program will crash

//*************** Loop Section ********************
  GetEntry(entry);
  //do the fancy stuff here

  //~~~~~~~~~~~~~minPT and others~~~~~~~~~~~~
  vector<double> ptv{*Kminus_PT, *Kplus_PT, *Piplus_PT};//init vec of pts
  double_t ptmin = *min_element(ptv.begin(), ptv.end());//find min of ptv

  if (*Dplus_M > 1858 && *Dplus_M < 1880) {
    sighist->Fill(ptmin);//filling signal bars
    pisigpi->Fill(*Piplus_ProbNNpi);
    mdpsig->Fill(*Dplus_M);
    fdsig->Fill(*Dplus_FDCHI2_OWNPV);
  };

  if (*Dplus_M < 1840 && *Dplus_M > 1818) {
    lsbhist->Fill(ptmin);//filling lower side band bars
    pilsbpi->Fill(*Piplus_ProbNNpi);
    mdposb->Fill(*Dplus_M);
    fdlsb->Fill(*Dplus_FDCHI2_OWNPV);
  };

  if (*Dplus_M < 1920 && *Dplus_M > 1898) {
    usbhist->Fill(ptmin);//filling upper side band bars
    piusbpi->Fill(*Piplus_ProbNNpi);
    mdposb->Fill(*Dplus_M);
    fdusb->Fill(*Dplus_FDCHI2_OWNPV);
  };

  if ((*Dplus_M < 1859 && *Dplus_M > 1839) || (*Dplus_M > 1879 && *Dplus_M < 1899)) {
    mdpisb->Fill(*Dplus_M);//inner side band
  };


  //~~~~~~~~~~~~~~NN probs~~~~~~~~~~~~~~~~~~~~~
  piprobhist->Fill(*Piplus_ProbNNpi, *Piplus_ProbNNk);




  return kTRUE; //also need this line otherwise (error: control reaches end of non-void function)
}

void Analyze::SlaveTerminate() {}

void Analyze::Terminate()
{
 //**************** Wrap-up Section ****************
  //~~~~~~~~~~~~mdp~~~~~~~~~~~~~~~~~~~~~~
   auto c0 = new TCanvas("c0","c0",1600,1200);
auto mdplegend = new TLegend(0.15,0.7,0.38,0.9);

 mdpsig->Draw();
 mdposb->Draw("same");
 mdpisb->Draw("same");

 mdplegend->SetHeader("Regions","C"); // "c" centers header
   mdplegend->AddEntry(mdpsig,"Signal Region","f");
   mdplegend->AddEntry(mdpisb,"Inner Sideband","f");
   mdplegend->AddEntry(mdposb,"Outer Sideband","f");
  mdplegend->Draw();
  c0->SaveAs("image/dp_mdp.png");

 //~~~~~~~~~~~~~~~~~~~minPT~~~~~~~~~~~~~~~~~~
auto c1 = new TCanvas("c1","c1",1600,1200);
auto legend = new TLegend(0.55,0.7,0.9,0.9); 

esthist->Add(usbhist,lsbhist,0.5,0.5);//creating esthist by adding equal parts usb and lsb
  
  bsubhist->Add(sighist);
  bsubhist->Add(esthist,-1);//creating background bars by subbing est from sig

  sighist->Draw("e0");
  esthist->Draw("e0same");
  bsubhist->Draw("e0same");

 legend->SetHeader("Distributions","C"); // "c" centers header
   legend->AddEntry(sighist,"Signal min PT","l");
   legend->AddEntry(esthist,"Background min PT","l");
   legend->AddEntry(bsubhist,"Background Subtracted min PT","l");
  legend->Draw();

  c1->SaveAs("image/dp_minPT.png");

  //~~~~~~~~~~~~~~~FD chi2~~~~~~~~~~~~~~~~~~~
  auto fdc = new TCanvas("fdc","fdc",1600,1200);
  auto flegend = new TLegend(0.35,0.7,0.65,0.9);

  fdest->Add(fdlsb,fdusb,0.5,0.5);

  fdsub->Add(fdsig);
  fdsub->Add(fdest,-1);

  fdsig->Draw("e0");
  fdest->Draw("e0same");
  fdsub->Draw("e0same");

  flegend->SetHeader("Distributions","C");
  flegend->AddEntry(fdsig, "Signal FD", "l");
  flegend->AddEntry(fdest, "Background FD", "l");
  flegend->AddEntry(fdsub, "Background Subtracted FD", "l");
  flegend->Draw();

  fdc->SaveAs("image/dp_fdchi2.png");

  //~~~~~~~~~~~~~~~~NN probs~~~~~~~~~~~~~~~~~~~~
  auto c2 = new TCanvas("c2","c2",1600,1200);
auto legendpipi = new TLegend(0.1,0.7,0.48,0.9);
  //c2->Divide(1,2);//two graphs, one for pi and one for k
  //c2->cd(1);//pi first
  piestpi->Add(piusbpi,pilsbpi,0.5,0.5);
  pisubpi->Add(pisigpi);
  pisubpi->Add(piestpi,-1);

  pisigpi->Draw("e0");
  piestpi->Draw("e0same");
  pisubpi->Draw("e0same");

 legendpipi->SetHeader("Distributions","C"); // "c" centers header
   legendpipi->AddEntry(pisigpi,"Signal ProbNNpi","l");
   legendpipi->AddEntry(piestpi,"Background ProbNNpi","l");
   legendpipi->AddEntry(pisubpi,"Background Subtracted ProbNNpi","l");
  legendpipi->Draw();

  //piprobhist->Draw("colz");
  c2->SaveAs("image/dp_piprobNNpi.png");

}
