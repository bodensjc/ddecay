{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();


//create rdataframe for dp magdown data
//RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp2kkpi_magdown.root");

RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/magdowndata/dp1.root");

/*get and print number of entries
auto dpdf_count = dpdf.Count();
double dpdfEntries = *dpdf_count;
cout << "Dp MagDown Raw Entries: " << dpdfEntries << endl;
*/
/*get and print column names
auto colNames = dpdf.GetColumnNames();
for (auto &&colName : colNames) std::cout << colName << std::endl;
*/


const double phi_pm = 12;
const double phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 

const int binmin = 1790;//1790 absolute minimum for dp
const int binmax = 1950;//1950 absolute minimum for dp
const int nbins = (binmax-binmin)/5;






auto inv_m_func = [](double px1, double py1, double pz1, double pe1, double px2, double py2, double pz2, double pe2) {return TLorentzVector(TLorentzVector(px1, py1, pz1, pe1)+TLorentzVector(px2, py2, pz2, pe2)).Mag2()/1000000 ;};
auto prob_func = [](double prob1, double prob2) {return TMath::Log(prob1) - TMath::Log(prob2) ;};
auto probNNx_func = [](double prob1, double prob2, double prob3) {return prob1*prob2*prob3 ;};


auto cut_ipchi2 = [](double x) {return x < 5 ;};
auto cut_fdchi2 = [](double x) {return x > 175 ;};
auto cut_endvertexchi2 = [](double x) {return x < 3 ;};
auto cut_phi = [phiupperbound, philowerbound](double x) {return x > philowerbound && x < phiupperbound ;};
auto cut_prob_5 = [] (double x) {return x>5 ;};
auto cut_prob_0 = [] (double x) {return x>5 ;};
auto cut_probnnx = [] (double x) {return x >= 0.70 ;};
auto cut_pK_ambiguity = [] (double x) {return x> 10000 ;}; //10,000 MeV = 10GeV
auto cut_dira = [] (double x) {return  x > 0.99999;};



auto dp_cut = dpdf.Filter(cut_ipchi2, {"Dplus_IPCHI2_OWNPV"})
				   .Filter(cut_fdchi2, {"Dplus_FDCHI2_OWNPV"})
				   .Filter(cut_endvertexchi2, {"Dplus_ENDVERTEX_CHI2"})
				   .Define("kminuslog", prob_func, {"Kminus_MC15TuneV1_ProbNNk", "Kminus_MC15TuneV1_ProbNNpi"})
				   .Define("kpluslog", prob_func, {"Kplus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNpi"})
				   .Define("pipluslog", prob_func, {"Piplus_MC15TuneV1_ProbNNpi", "Piplus_MC15TuneV1_ProbNNk"})
				   .Filter(cut_prob_5, {"kminuslog"})
				   .Filter(cut_prob_5, {"kpluslog"})
				   .Filter(cut_prob_0, {"pipluslog"})
				   .Define("mkpkm", inv_m_func, {"Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_PE", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_PE"})
				   .Filter(cut_phi, {"mkpkm"});



auto dp_cut_new = dpdf.Filter(cut_ipchi2, {"Dplus_IPCHI2_OWNPV"})
				   .Filter(cut_fdchi2, {"Dplus_FDCHI2_OWNPV"})
				   .Filter(cut_endvertexchi2, {"Dplus_ENDVERTEX_CHI2"})
				   .Define("kminuslog", prob_func, {"Kminus_MC15TuneV1_ProbNNk", "Kminus_MC15TuneV1_ProbNNpi"})
				   .Define("kpluslog", prob_func, {"Kplus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNpi"})
				   .Define("pipluslog", prob_func, {"Piplus_MC15TuneV1_ProbNNpi", "Piplus_MC15TuneV1_ProbNNk"})
				   .Filter(cut_prob_5, {"kminuslog"})
				   .Filter(cut_prob_5, {"kpluslog"})
				   .Filter(cut_prob_0, {"pipluslog"})
				   .Define("mkpkm", inv_m_func, {"Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_PE", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_PE"})
				   .Filter(cut_phi, {"mkpkm"})
				   .Filter(cut_dira, {"Dplus_DIRA_OWNPV"});





auto totalcuthist = dp_cut.Fill<double>(TH1D("totalcuthist","D+",nbins, binmin, binmax), {"Dplus_MM"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	totalcuthist->SetStats(0);
    totalcuthist->SetTitleFont(43);
    totalcuthist->SetTitleSize(35);
    totalcuthist->GetYaxis()->SetTitle("events per 1mev");//Candidates/(1 MeV/c^{2})
    totalcuthist->SetMinimum(1);//make minimum 1 so logy doesnt break, make 100 or better viewing
    totalcuthist->GetYaxis()->SetTitleFont(43);
	totalcuthist->GetYaxis()->SetTitleSize(30);
	totalcuthist->GetYaxis()->CenterTitle(true);
	totalcuthist->SetLineColor(kBlue+2);
auto totalcuthistROOT = totalcuthist->DrawCopy();//converts Rhist into ROOThist



auto totalcuthistnew = dp_cut_new.Fill<double>(TH1D("totalcuthistnew","D+",nbins, binmin, binmax), {"Dplus_MM"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	totalcuthistnew->SetStats(0);
    totalcuthistnew->SetTitleFont(43);
    totalcuthistnew->SetTitleSize(35);
    totalcuthistnew->GetYaxis()->SetTitle("events per 1mev");//Candidates/(1 MeV/c^{2})
    totalcuthistnew->SetMinimum(1);//make minimum 1 so logy doesnt break, make 100 or better viewing
    totalcuthistnew->GetYaxis()->SetTitleFont(43);
	totalcuthistnew->GetYaxis()->SetTitleSize(30);
	totalcuthistnew->GetYaxis()->CenterTitle(true);
	totalcuthistnew->SetLineColor(kRed+2);
auto totalcuthistnewROOT = totalcuthistnew->DrawCopy();//converts Rhist into ROOThist





auto logytotalpullcan = new TCanvas("logytotalpullcan", "logytotalpullcan", 1600, 1200);
	logytotalpullcan->cd();
		TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
		pad1->Draw();
		pad1->cd();
		pad1->SetLogy();
	totalcuthist->Draw();
	totalcuthistnew->Draw("same");
logytotalpullcan->SaveAs("image/aaaaaaadp.png");





/*
auto myDpFit = new TF1("myDpFit",fit1MeV_GaussianPlusCBWithExp_redo,binmin, binmax, 9);
	myDpFit->SetParNames("nSignal", "mu", "rms_wdth", "sigma_1", "gaus_frac", "exp_int","exp_coef","CB_alpha","CB_n");
	myDpFit->SetLineColor(kRed+1);
	myDpFit->SetLineWidth(2);
		double maxbin = totalcuthistROOT->GetBinContent(totalcuthistROOT->GetMaximumBin());
		double firstbin = totalcuthistROOT->GetBinContent(1);//used for intercept guess
		double lastbin = totalcuthistROOT->GetBinContent(nbins-1);//used for slope guess
		double nSignalGuess = (maxbin-firstbin)*15;
		double expCoefGuess = (lastbin-firstbin)/nbins;
	myDpFit->SetParameter(0,nSignalGuess);//nSignal
	//myDpFit->SetParLimits(0,2500000,3500000);//try not to use this if possible
	myDpFit->SetParameter(1,1869);//mu
	myDpFit->SetParameter(2,4.);//rms of double gaussian	
	myDpFit->SetParLimits(2,0.,20.);
	myDpFit->SetParameter(3,7);//sigma_1 of primary gaussian
	myDpFit->SetParameter(4,0.85);//fraction of signal in primary gaussian
	myDpFit->SetParLimits(4,0.8,0.9999999);
	myDpFit->SetParameter(5,firstbin);//exp intercept
	myDpFit->SetParameter(6,expCoefGuess);//coefficient background exponential
	myDpFit->SetParameter(7, 1.5);//crystal ball alpha
	myDpFit->SetParameter(8,2.5);//crystal ball n
	myDpFit->SetParLimits(8,1.00001,6.);
*/




/*
pad2->cd();
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.4);
	pad2->SetLeftMargin(0.15);
	pad2->SetGridx();


totalcutpull = new TH1D("total cut pull plot", "Pull Plot", nbins, binmin, binmax);
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


auto dp_pull = dp_cut.Define("pull", 

 Double_t xVals[nbins];
 Double_t yVals[nbins];
 for (Int_t i=1;i<nbins;i++) {
 Double_t x = totalcuthist->GetBinCenter(i);
 Double_t val = myDpFit->Eval(totalcuthist->GetBinCenter(i));
 Double_t sigma = sqrt(val);
 Double_t pull = (totalcuthist->GetBinContent(i)-val)/sigma;
 totalcutpull->SetBinContent(i,pull);
   xVals[i]=x;
   yVals[i]=pull;
   }

*/

/*
auto totalpullcanliny = new TCanvas("totalpullcanliny", "totalpullcanliny", 1000, 800);
	TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1.0);
	TPad *pad2 = new TPad("pad2","pad2",0,0.0,1,0.25);
		pad1->Draw();
		pad2->Draw();
	pad1->cd();
		pad1->SetBottomMargin(0);
		pad1->SetLeftMargin(0.15);
		//pad1->SetLogy();
			totalcuthistROOT->Fit("myDpFit","RL");
			totalcuthistROOT->Draw();
	pad2->cd();
		pad2->SetTopMargin(0);
		pad2->SetBottomMargin(0.4);
		pad2->SetLeftMargin(0.15);
		pad2->SetGridx();
			//totalcutpull->Draw();
totalpullcanliny->SaveAs("image/dp_cut_fit_pull_rdf_liny.png");



auto totalpullcanlogy = new TCanvas("totalpullcanlogy", "totalpullcanlogy", 1000, 800);
	TPad *pad11 = new TPad("pad11","pad11",0,0.25,1,1.0);
	TPad *pad22 = new TPad("pad22","pad22",0,0.0,1,0.25);
		pad11->Draw();
		pad22->Draw();
	pad11->cd();
		pad11->SetBottomMargin(0);
		pad11->SetLeftMargin(0.15);
		pad11->SetLogy();
			totalcuthistROOT->Fit("myDpFit","RL");
			totalcuthistROOT->Draw();
	pad22->cd();
		pad22->SetTopMargin(0);
		pad22->SetBottomMargin(0.4);
		pad22->SetLeftMargin(0.15);
		pad22->SetGridx();
			//totalcutpull->Draw();
totalpullcanlogy->SaveAs("image/dp_cut_fit_pull_rdf_logy.png");


*/

}//end



