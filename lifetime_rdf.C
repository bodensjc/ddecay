{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();


//create rdataframe for dp magdown data
//RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/magdowndata/dp1.root");
//RDataFrame dspdf("Dsp2KKpi/DecayTree", "/share/lazy/D2KKpi/magdowndata/dsp01.root");

RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dp2kkpi_magdown.root","/share/lazy/D2KKpi/dp2kkpi_magup.root"});
RDataFrame dspdf("Dsp2KKpi/DecayTree", {"/share/lazy/D2KKpi/dsp2kkpi_magdown.root","/share/lazy/D2KKpi/dsp2kkpi_magup.root"});


const double phi_pm = 12;
const double phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 

const int binmin = 1880;//1790 absolute minimum for dp
const int binmax = 2050;//1950 absolute minimum for dp
//const int nbins = (binmax-binmin)/5;
const int nbins = 100;

const int cc = 299792458;//speed of light in m/s





auto inv_m_func = [](double px1, double py1, double pz1, double pe1, double px2, double py2, double pz2, double pe2) {return TLorentzVector(TLorentzVector(px1, py1, pz1, pe1)+TLorentzVector(px2, py2, pz2, pe2)).Mag2()/1000000 ;};
auto prob_func = [](double prob1, double prob2) {return TMath::Log(prob1) - TMath::Log(prob2) ;};
auto probNNx_func = [](double prob1, double prob2, double prob3) {return prob1*prob2*prob3 ;};
auto lifetime_func = [cc](double fd, double m, double p) {return (fd*m)/(p*cc*(10^3)) ;};


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
				   .Filter(cut_pK_ambiguity, {"Kplus_P"})
				   .Filter(cut_pK_ambiguity, {"Kminus_P"})
				   .Define("kminuslog", prob_func, {"Kminus_MC15TuneV1_ProbNNk", "Kminus_MC15TuneV1_ProbNNpi"})
				   .Define("kpluslog", prob_func, {"Kplus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNpi"})
				   .Define("pipluslog", prob_func, {"Piplus_MC15TuneV1_ProbNNpi", "Piplus_MC15TuneV1_ProbNNk"})
				   .Filter(cut_prob_5, {"kminuslog"})
				   .Filter(cut_prob_5, {"kpluslog"})
				   .Filter(cut_prob_0, {"pipluslog"})
				   .Define("ProbNNx", probNNx_func, {"Kminus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNk", "Piplus_MC15TuneV1_ProbNNpi"})
				   .Filter(cut_probnnx, {"ProbNNx"})
				   .Define("mkpkm", inv_m_func, {"Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_PE", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_PE"})
				   .Filter(cut_phi, {"mkpkm"})
				   .Filter(cut_dira, {"Dplus_DIRA_OWNPV"})
				   .Define("dp_lifetime", lifetime_func, {"Dplus_FD_OWNPV", "Dplus_MM", "Dplus_P"});




auto dsp_cut = dspdf.Filter(cut_ipchi2, {"Dsplus_IPCHI2_OWNPV"})
				   .Filter(cut_fdchi2, {"Dsplus_FDCHI2_OWNPV"})
				   .Filter(cut_endvertexchi2, {"Dsplus_ENDVERTEX_CHI2"})
				   .Filter(cut_pK_ambiguity, {"Kplus_P"})
				   .Filter(cut_pK_ambiguity, {"Kminus_P"})
				   .Define("kminuslog", prob_func, {"Kminus_MC15TuneV1_ProbNNk", "Kminus_MC15TuneV1_ProbNNpi"})
				   .Define("kpluslog", prob_func, {"Kplus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNpi"})
				   .Define("pipluslog", prob_func, {"Piplus_MC15TuneV1_ProbNNpi", "Piplus_MC15TuneV1_ProbNNk"})
				   .Filter(cut_prob_5, {"kminuslog"})
				   .Filter(cut_prob_5, {"kpluslog"})
				   .Filter(cut_prob_0, {"pipluslog"})
				   .Define("ProbNNx", probNNx_func, {"Kminus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNk", "Piplus_MC15TuneV1_ProbNNpi"})
				   .Filter(cut_probnnx, {"ProbNNx"})
				   .Define("mkpkm", inv_m_func, {"Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_PE", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_PE"})
				   .Filter(cut_phi, {"mkpkm"})
				   .Filter(cut_dira, {"Dsplus_DIRA_OWNPV"})
				   .Define("dsp_lifetime", lifetime_func, {"Dsplus_FD_OWNPV", "Dsplus_MM", "Dsplus_P"});



/*
auto dp_raw = dpdf.Define("dp_lifetime", lifetime_func, {"Dplus_FD_OWNPV", "Dplus_MM", "Dplus_P"});

auto dsp_raw = dspdf.Define("dsp_lifetime", lifetime_func, {"Dsplus_FD_OWNPV", "Dsplus_MM", "Dsplus_P"});
*/




auto dplifetimehist = dp_cut.Fill<double>(TH1D("dplifetimehist","D^{+}, D^{+}_{s} lifetime",nbins, 0, 0.0000000005), {"dp_lifetime"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dplifetimehist->SetStats(0); 
	dplifetimehist->SetTitleFont(43);
	dplifetimehist->SetTitleSize(35);
	dplifetimehist->GetYaxis()->SetTitle("events per bin");//Candidates/(1 MeV/c^{2})
	dplifetimehist->SetMinimum(1);//make minimum 1 so logy doesnt break, make 100 or better viewing
	dplifetimehist->GetYaxis()->SetTitleFont(43);
	dplifetimehist->GetYaxis()->SetTitleSize(30);
	dplifetimehist->GetYaxis()->CenterTitle(true);
	dplifetimehist->SetLineColor(kBlue);
	dplifetimehist->SetLineWidth(3);



auto dsplifetimehist = dsp_cut.Fill<double>(TH1D("dsplifetimehist","D^{+}, D^{+}_{s} lifetime",nbins, 0, 0.0000000005), {"dsp_lifetime"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dsplifetimehist->SetStats(0); 
	dsplifetimehist->SetTitleFont(43);
	dsplifetimehist->SetTitleSize(35);
	dsplifetimehist->GetYaxis()->SetTitle("events per bin");//Candidates/(1 MeV/c^{2})
	dsplifetimehist->SetMinimum(1);//make minimum 1 so logy doesnt break, make 100 or better viewing
	dsplifetimehist->GetYaxis()->SetTitleFont(43);
	dsplifetimehist->GetYaxis()->SetTitleSize(30);
	dsplifetimehist->GetYaxis()->CenterTitle(true);
	dsplifetimehist->SetLineColor(kRed);
	dsplifetimehist->SetLineWidth(3);




auto dpdsplegend = new TLegend(0.7,0.75,0.9,0.9);
	dpdsplegend->AddEntry(dplifetimehist.GetPtr(), "D^{+}  Data ", "l");
	dpdsplegend->AddEntry(dsplifetimehist.GetPtr(), "D^{+}_{s}  Data", "l");



auto dsplifetimecan = new TCanvas("dsplifetimecan", "dsplifetimecan", 1600, 1200);
	dsplifetimecan->cd();
		TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
		pad1->Draw();
		pad1->cd();
		pad1->SetLogy();
	dsplifetimehist->Draw();
	dplifetimehist->Draw("same");
	dpdsplegend->Draw("same");
dsplifetimecan->SaveAs("image/lifetime_dp_dsp_cut_logy.png");





}//end







