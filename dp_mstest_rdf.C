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


auto signalregion = [](double x) {return ((x > 1855) && (x < 1885)) ;};
auto backgroundregion = [](double x) {return ((x>1810 && x < 1840) || (x > 1900 && x < 1930)) ;};
auto rightbackgroundregion = [](double x) {return (x > 1900 && x < 1950) ;};
auto leftbackgroundregion = [](double x) {return (x > 1790 && x < 1840) ;};


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




auto dp_sig_df = dp_cut.Filter(signalregion, {"Dplus_MM"});
auto dp_bgd_df = dp_cut.Filter(backgroundregion, {"Dplus_MM"});
auto dp_left = dp_cut.Filter(leftbackgroundregion, {"Dplus_MM"});
auto dp_right = dp_cut.Filter(rightbackgroundregion, {"Dplus_MM"});


//Tau tests
/*

const double taubinmin = 0;
const double taubinmax = 0.005;
const int nbins = 100;


auto dptaucan = new TCanvas("dptaucan", "dptaucan", 1200, 800);
	dptaucan->cd();
auto dptausighist = dp_sig_df.Fill<double>(TH1D("dptausighist","D+ #tau, uncut",nbins, taubinmin, taubinmax), {"Dplus_TAU"});
	dptausighist->SetStats(0);
	dptausighist->SetTitleFont(43);
	dptausighist->SetTitleSize(35);
	dptausighist->GetYaxis()->SetTitle("events per bin");
	dptausighist->GetYaxis()->SetTitleFont(43);
	dptausighist->GetYaxis()->SetTitleSize(30);
	dptausighist->GetYaxis()->CenterTitle(true);
	dptausighist->GetXaxis()->SetTitle("decay time (ns)");
	dptausighist->GetXaxis()->SetTitleFont(43);
	dptausighist->GetXaxis()->SetTitleSize(25);
	dptausighist->GetXaxis()->CenterTitle(true);
	dptausighist->GetXaxis()->SetTitleOffset(1.2);
	dptausighist->SetLineColor(kRed);
	dptausighist->SetLineWidth(3);

//total background, not split by left or right
//
//auto dptaubgdhist = dp_bgd_df.Fill<double>(TH1D("bgdhist","D+ #tau, uncut",nbins, taubinmin, taubinmax), {"Dplus_TAU"});
//	dptaubgdhist->SetStats(0);
//	dptaubgdhist->SetLineColor(kBlue);
//	dptaubgdhist->SetLineWidth(3);


auto dptaulefthist = dp_left.Fill<double>(TH1D("dptaulefthist","D+ #tau, uncut",nbins, taubinmin, taubinmax), {"Dplus_TAU"});
	dptaulefthist->SetStats(0);
	dptaulefthist->SetLineColor(kBlue);
	dptaulefthist->SetLineWidth(3);

auto dptaurighthist = dp_right.Fill<double>(TH1D("dptaurighthist","D+ #tau uncut",nbins, taubinmin, taubinmax), {"Dplus_TAU"});
	dptaurighthist->SetStats(0);
	dptaurighthist->SetLineColor(kGreen + 2);
	dptaurighthist->SetLineWidth(3);

auto taulegend = new TLegend(0.7,0.8,0.9,0.9);
	taulegend->AddEntry(dptausighist.GetPtr(), "Signal Region", "lp");
	//taulegend->AddEntry(dptaubgdhist.GetPtr(), "Background Region", "lp");
	taulegend->AddEntry(dptaulefthist.GetPtr(), "Left Background", "lp");
	taulegend->AddEntry(dptaurighthist.GetPtr(), "Right Background", "lp");

dptausighist->Draw("");
dptaulefthist->Draw("same");
dptaurighthist->Draw("same");
taulegend->Draw("same");
dptaucan->SaveAs("image/dp_tau_uncut.png");
*/






//particle_x, particle_y

/*
auto pip_pos = dp_cut.Fill<double, double>(TH2D("pip_pos", "#pi^{+} _X, _Y cut",300,-3000,3000,300,-3000,3000), {"Piplus_X","Piplus_Y"});
	pip_pos->SetStats(0);
	pip_pos->GetXaxis()->SetTitle("Piplus_X");
	pip_pos->GetYaxis()->SetTitle("Piplus_Y");
pip_pos_can = new TCanvas("pip_pos_can", "pip_pos_can", 1000, 800);
	pip_pos_can->SetRightMargin(0.15);
	pip_pos_can->SetLeftMargin(0.15);
	pip_pos_can->cd();
pip_pos->Draw("colz");
pip_pos_can->SaveAs("image/dp_XY_cut_pip.png");


auto kp_pos = dp_cut.Fill<double, double>(TH2D("kp_pos", "K^{+} _X, _Y cut",300,-3000,3000,300,-3000,3000), {"Kplus_X","Kplus_Y"});
	kp_pos->SetStats(0);
	kp_pos->GetXaxis()->SetTitle("Kplus_X");
	kp_pos->GetYaxis()->SetTitle("Kplus_Y");
kp_pos_can = new TCanvas("kp_pos_can", "kp_pos_can", 1000, 800);
	kp_pos_can->SetRightMargin(0.15);
	kp_pos_can->SetLeftMargin(0.15);
	kp_pos_can->cd();
kp_pos->Draw("colz");
kp_pos_can->SaveAs("image/dp_XY_cut_kp.png");


auto km_pos = dp_cut.Fill<double, double>(TH2D("km_pos", "K^{-} _X, _Y cut",300,-3000,3000,300,-3000,3000), {"Kminus_X","Kminus_Y"});
	km_pos->SetStats(0);
	km_pos->GetXaxis()->SetTitle("Kminus_X");
	km_pos->GetYaxis()->SetTitle("Kminus_Y");
km_pos_can = new TCanvas("km_pos_can", "km_pos_can", 1000, 800);
	km_pos_can->SetRightMargin(0.15);
	km_pos_can->SetLeftMargin(0.15);
	km_pos_can->cd();
km_pos->Draw("colz");
km_pos_can->SaveAs("image/dp_XY_cut_km.png");
*/










}//end



