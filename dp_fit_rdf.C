{//begin
#include <TMath.h>
#include <math.h>


#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();


//create rdataframe for dp data
//RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dpmagdown_dec20.root","/share/lazy/D2KKpi/dpmagup_dec20.root"});

//smaller set of data for quicker, experimental runs
//done by taking the smalles magdown and magup subfiles
RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dp_data_dec20/dpmagup14-2.root", "/share/lazy/D2KKpi/dp_data_dec20/dpmagdown15-2.root"});


/*
auto test_min = dpdf.Min("Dplus_MM");
auto test_max = dpdf.Max("Dplus_MM");
cout << "minimum dp mass is " << *test_min << endl;
cout << "maximum dp mass is " << *test_max << endl;

auto test_summary = dpdf.Stats("Dplus_MM");
test_summary->Print();
*/



const double phi_pm = 10;//12 for regular cut
const double phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 


auto inv_m_func = [](double px1, double py1, double pz1, double pe1, double px2, double py2, double pz2, double pe2) {return TLorentzVector(TLorentzVector(px1, py1, pz1, pe1)+TLorentzVector(px2, py2, pz2, pe2)).Mag2()/1000000 ;};
auto prob_func = [](double prob1, double prob2) {return TMath::Log(prob1) - TMath::Log(prob2) ;};
auto probNNx_func = [](double prob1, double prob2, double prob3) {return prob1*prob2*prob3 ;};


auto cut_ipchi2 = [](double x) {return x < 4 ;};//5 for regular cut
auto cut_fdchi2 = [](double x) {return x > 225 ;};//175 for regular cut
auto cut_endvertexchi2 = [](double x) {return x < 9 ;};
auto cut_phi = [&phiupperbound, &philowerbound](double x) {return x > philowerbound && x < phiupperbound ;};
auto cut_prob_5 = [] (double x) {return x>5 ;};
auto cut_prob_0 = [] (double x) {return x>0 ;};
auto cut_probnnx = [] (double x) {return x >= 0.70 ;};
auto cut_pK_ambiguity = [] (double x) {return x> 10000 ;}; //10,000 MeV = 10GeV
auto cut_dira = [] (double x) {return x>0.99999 ;};
//auto cut_tau = [] (double x) {return x > 0.0000000001 ;};//mikes suggestion : 1e-10, ds+ takeover : 2.3e-10


auto dp_cut = dpdf.Filter(cut_ipchi2, {"Dplus_IPCHI2_OWNPV"})
				   .Filter(cut_fdchi2, {"Dplus_FDCHI2_OWNPV"})
				   .Filter(cut_endvertexchi2, {"Dplus_ENDVERTEX_CHI2"})
				   .Filter(cut_pK_ambiguity, {"Kplus_P"})
				   .Filter(cut_pK_ambiguity, {"Kminus_P"})
				   .Filter(cut_dira, {"Dplus_DIRA_OWNPV"})
				   .Define("kminuslog", prob_func, {"Kminus_MC15TuneV1_ProbNNk", "Kminus_MC15TuneV1_ProbNNpi"})
				   .Define("kpluslog", prob_func, {"Kplus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNpi"})
				   .Define("pipluslog", prob_func, {"Piplus_MC15TuneV1_ProbNNpi", "Piplus_MC15TuneV1_ProbNNk"})
				   .Filter(cut_prob_5, {"kminuslog"})
				   .Filter(cut_prob_5, {"kpluslog"})
				   .Filter(cut_prob_0, {"pipluslog"})
				   .Define("ProbNNx", probNNx_func, {"Kminus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNk", "Piplus_MC15TuneV1_ProbNNpi"})
				   .Filter(cut_probnnx, {"ProbNNx"})
				   .Define("mkpkm", inv_m_func, {"Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_PE", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_PE"})
				   .Filter(cut_phi, {"mkpkm"});





//original histogram method

const int binmin = 1790;//min value for dp is 1790
const int binmax = 1950;//max value for dp is 1950
const int nbins = binmax-binmin; // to get 1MeV per bin


auto dptotalcuthist = dp_cut.Fill<double>(TH1D("dptotalcuthist","D^{+} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dplus_MM"});
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

	dptotalcuthist->SetMaximum(8000);//not a good idea to have this, just for testing purposes
//nsf plot stuff
//	dptotalcuthist->GetYaxis()->SetTitleOffset(1.3);
//	dptotalcuthist->SetTitle("");
//	dptotalcuthist->GetXaxis()->SetLabelSize(50);
//	dptotalcuthist->GetXaxis()->SetLabelFont(43);
//	dptotalcuthist->GetYaxis()->SetLabelSize(50);
//	dptotalcuthist->GetYaxis()->SetLabelFont(43);



TF1 *myDpFit = new TF1("myDpFit",fit1MeV_GaussianPlusCBWithExp_redo,binmin+0.00001,binmax-0.00001, 9);
   myDpFit->SetParNames("nSignal", "mu", "rms_wdth", "sigma_1", "gaus_frac", "exp_int","exp_coef","CB_alpha","CB_n");
  myDpFit->SetLineColor(kBlack);
  myDpFit->SetLineWidth(2);

  double maxbin = dptotalcuthist->GetBinContent(dptotalcuthist->GetMaximumBin());
  double firstbin = dptotalcuthist->GetBinContent(1);//used for intercept guess
  double lastbin = dptotalcuthist->GetBinContent(99);//used for slope guess

  double nSignalGuess = (maxbin-firstbin)*15;
  double expCoefGuess = (lastbin-firstbin)/100;

cout << "nSignal guess is " << nSignalGuess << endl;
cout << "first bin is " << firstbin << endl;
cout << "last bin is " << lastbin << endl;

  myDpFit->SetParameter(0,nSignalGuess);//nSignal
  //myDpFit->SetParLimits(0,2500000,3500000);
  myDpFit->SetParameter(1,1869);//mu
  myDpFit->SetParameter(2,4.);//rms of double gaussian
  myDpFit->SetParLimits(2,0.,20.);
  myDpFit->SetParameter(3,7);//sigma_1 of primary gaussian
  myDpFit->SetParameter(4,0.85);//fraction of signal in primary gaussian
  //myDpFit->SetParLimits(4,0.001,0.09999999);
  myDpFit->SetParameter(5,firstbin);//exp intercept
  myDpFit->SetParameter(6,expCoefGuess);//coefficient background exponential
  myDpFit->SetParameter(7, 1.5);//crystal ball alpha
  myDpFit->SetParameter(8,2.5);//crystal ball n
  myDpFit->SetParLimits(8,1.00001,6.);







auto dplegendliny = new TLegend(0.7,0.75,0.91,0.9);
	dplegendliny->AddEntry(dptotalcuthist.GetPtr(), "D^{+}  Data ", "l");
	dplegendliny->AddEntry(myDpFit, "Signal Fit", "l");

auto linytotalpullcan = new TCanvas("linytotalpullcan", "linytotalpullcan", 1600, 1200);
	linytotalpullcan->cd();
	linytotalpullcan->SetLeftMargin(0.15);
	linytotalpullcan->SetRightMargin(0.09);
	linytotalpullcan->SetBottomMargin(0.15);
	dptotalcuthist->Fit(myDpFit,"R");
	dptotalcuthist->Draw();
	dplegendliny->Draw("same");

linytotalpullcan->Update();
linytotalpullcan->SaveAs("image/dp_fit_rdf.png");







//snapshot method
/*
auto outFileName = "dp_sample_cut.root";
auto treeName = "DecayTree";

dp_cut.Snapshot(treeName, outFileName, {"Dplus_MM"});



TFile f1(outFileName);
auto t = f1.Get<TTree>(treeName);
std::cout << "These are the columns Dplus_MM and Dplus_TAU:" << std::endl;
for (auto branch : *t->GetListOfBranches()) {
    std::cout << "Branch: " << branch->GetName() << std::endl;
}
f1.Close();
*/









}//end













