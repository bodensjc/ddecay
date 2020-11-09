{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();


//create rdataframe for dp, dsp magdown data
RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp2kkpi_magdown.root");
RDataFrame dspdf("Dsp2KKpi/DecayTree", "/share/lazy/D2KKpi/dsp2kkpi_magdown.root");



const double phi_pm = 10;//12 for regular cut
const double phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 

const int binmin = 1790;//1790 absolute minimum for dp
const int binmax = 2050;//max value for dsp is 2050
const int nbins = 100;





auto inv_m_func = [](double px1, double py1, double pz1, double pe1, double px2, double py2, double pz2, double pe2) {return TLorentzVector(TLorentzVector(px1, py1, pz1, pe1)+TLorentzVector(px2, py2, pz2, pe2)).Mag2()/1000000 ;};
auto prob_func = [](double prob1, double prob2) {return TMath::Log(prob1) - TMath::Log(prob2) ;};


auto cut_ipchi2 = [](double x) {return x < 3 ;};//5 for regular cut
auto cut_fdchi2 = [](double x) {return x > 200 ;};//175 for regular cut
auto cut_phi = [phiupperbound, philowerbound](double x) {return x > philowerbound && x < phiupperbound ;};
auto cut_prob_5 = [] (double x) {return x>5 ;};
auto cut_prob_0 = [] (double x) {return x>0 ;};



auto dp_cut = dpdf.Filter(cut_ipchi2, {"Dplus_IPCHI2_OWNPV"})
				   .Filter(cut_fdchi2, {"Dplus_FDCHI2_OWNPV"})
				   .Define("kminuslog", prob_func, {"Kminus_MC15TuneV1_ProbNNk", "Kminus_MC15TuneV1_ProbNNpi"})
				   .Define("kpluslog", prob_func, {"Kplus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNpi"})
				   .Define("pipluslog", prob_func, {"Piplus_MC15TuneV1_ProbNNpi", "Piplus_MC15TuneV1_ProbNNk"})
				   .Filter(cut_prob_5, {"kminuslog"})
				   .Filter(cut_prob_5, {"kpluslog"})
				   .Filter(cut_prob_0, {"pipluslog"})
				   .Define("mkpkm", inv_m_func, {"Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_PE", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_PE"})
				   .Filter(cut_phi, {"mkpkm"});

auto dsp_cut = dspdf.Filter(cut_ipchi2, {"Dsplus_IPCHI2_OWNPV"})
				   .Filter(cut_fdchi2, {"Dsplus_FDCHI2_OWNPV"})
				   .Define("kminuslog", prob_func, {"Kminus_MC15TuneV1_ProbNNk", "Kminus_MC15TuneV1_ProbNNpi"})
				   .Define("kpluslog", prob_func, {"Kplus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNpi"})
				   .Define("pipluslog", prob_func, {"Piplus_MC15TuneV1_ProbNNpi", "Piplus_MC15TuneV1_ProbNNk"})
				   .Filter(cut_prob_5, {"kminuslog"})
				   .Filter(cut_prob_5, {"kpluslog"})
				   .Filter(cut_prob_0, {"pipluslog"})
				   .Define("mkpkm", inv_m_func, {"Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_PE", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_PE"})
				   .Filter(cut_phi, {"mkpkm"});







auto dptotalcuthist = dp_cut.Fill<double>(TH1D("dptotalcuthist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dplus_MM"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dptotalcuthist->SetStats(0);
    dptotalcuthist->SetTitleFont(43);
    dptotalcuthist->SetTitleSize(33);
    dptotalcuthist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");//Candidates/(1 MeV/c^{2})
    dptotalcuthist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 or better viewing
    dptotalcuthist->GetYaxis()->SetTitleFont(43);
	dptotalcuthist->GetYaxis()->SetTitleSize(30);
	dptotalcuthist->GetYaxis()->CenterTitle(true);
    dptotalcuthist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dptotalcuthist->GetXaxis()->SetTitleFont(43);
	dptotalcuthist->GetXaxis()->SetTitleSize(25);
	dptotalcuthist->GetXaxis()->CenterTitle(true);
	dptotalcuthist->GetXaxis()->SetTitleOffset(1.2);
	dptotalcuthist->SetLineColor(kRed);

auto dsptotalcuthist = dsp_cut.Fill<double>(TH1D("dsptotalcuthist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dsplus_MM"});//D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dsptotalcuthist->SetStats(0);
    dsptotalcuthist->SetTitleFont(43);
    dsptotalcuthist->SetTitleSize(33);
    dsptotalcuthist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");//Candidates/(1 MeV/c^{2})
    dsptotalcuthist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 or better viewing
    dsptotalcuthist->GetYaxis()->SetTitleFont(43);
	dsptotalcuthist->GetYaxis()->SetTitleSize(30);
	dsptotalcuthist->GetYaxis()->CenterTitle(true);
    dsptotalcuthist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dsptotalcuthist->GetXaxis()->SetTitleFont(43);
	dsptotalcuthist->GetXaxis()->SetTitleSize(30);
	dsptotalcuthist->GetXaxis()->CenterTitle(true);
	dsptotalcuthist->GetXaxis()->SetTitleOffset(1.2);
	dsptotalcuthist->SetLineColor(kBlue);




auto dpdsplegend = new TLegend(0.8,0.8,0.9,0.9);
	dpdsplegend->AddEntry(dptotalcuthist.GetPtr(), "D^{+}  Data ", "l");
	dpdsplegend->AddEntry(dsptotalcuthist.GetPtr(), "D^{+}_{s}  Data", "l");



auto linytotalpullcan = new TCanvas("linytotalpullcan", "linytotalpullcan", 1600, 1200);
	linytotalpullcan->cd();
	dsptotalcuthist->Draw();
	dptotalcuthist->Draw("same");
	dpdsplegend->Draw("same");
linytotalpullcan->SaveAs("image/dp_dsp_continuous_liny_tightercuts.png");

auto logytotalpullcan = new TCanvas("logytotalpullcan", "logytotalpullcan", 1600, 1200);
	logytotalpullcan->cd();
		TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
		pad1->Draw();
		pad1->cd();
		pad1->SetLogy();
	dsptotalcuthist->Draw();
	dptotalcuthist->Draw("same");
	dpdsplegend->Draw("same");
logytotalpullcan->SaveAs("image/dp_dsp_continuous_logy_tightercuts.png");

}//end



