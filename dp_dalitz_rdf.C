{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();


//create rdataframe for dp magdown data
RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp2kkpi_magdown.root");


const double phi_pm = 12;
const double phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 



auto inv_m_func = [](double px1, double py1, double pz1, double pe1, double px2, double py2, double pz2, double pe2) {return TLorentzVector(TLorentzVector(px1, py1, pz1, pe1)+TLorentzVector(px2, py2, pz2, pe2)).Mag2()/1000000 ;};
auto prob_func = [](double prob1, double prob2) {return TMath::Log(prob1) - TMath::Log(prob2) ;};


auto cut_ipchi2 = [](double x) {return x < 5 ;};
auto cut_fdchi2 = [](double x) {return x > 175 ;};
auto cut_endvertexchi2 = [](double x) {return x < 3 ;};
auto cut_phi = [phiupperbound, philowerbound](double x) {return x > philowerbound && x < phiupperbound ;};
auto cut_prob_5 = [] (double x) {return x>5 ;};
auto cut_prob_0 = [] (double x) {return x>5 ;};


auto dp_og = dpdf.Define("mkpkm", inv_m_func, {"Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_PE", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_PE"})
					.Define("mkmpi", inv_m_func, {"Piplus_PX", "Piplus_PY", "Piplus_PZ", "Piplus_PE", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_PE"});


auto dp_cut = dp_og.Filter(cut_ipchi2, {"Dplus_IPCHI2_OWNPV"})
				   .Filter(cut_fdchi2, {"Dplus_FDCHI2_OWNPV"})
				   .Filter(cut_endvertexchi2, {"Dplus_ENDVERTEX_CHI2"})
				   .Define("kminuslog", prob_func, {"Kminus_MC15TuneV1_ProbNNk", "Kminus_MC15TuneV1_ProbNNpi"})
				   .Define("kpluslog", prob_func, {"Kplus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNpi"})
				   .Define("pipluslog", prob_func, {"Piplus_MC15TuneV1_ProbNNpi", "Piplus_MC15TuneV1_ProbNNk"})
				   .Filter(cut_prob_5, {"kminuslog"})
				   .Filter(cut_prob_5, {"kpluslog"})
				   .Filter(cut_prob_0, {"pipluslog"});



auto dp_phicut = dp_cut.Filter(cut_phi, {"mkpkm"});



gStyle->SetPalette(55, 0);



auto dalitz_og = dp_og.Fill<double, double>(TH2D("dalitz_og", "D^{+} #rightarrow  K^{+}K^{-}#pi^{+} Dalitz Plot (no cuts)",200,0.8,3.3,200,0.1,2.3), {"mkpkm", "mkmpi"});
	dalitz_og->SetStats(0);
    dalitz_og->GetXaxis()->SetTitle("m^{2}(K^{+}K^{-}) [GeV/c^{2}]^{2}");
    dalitz_og->GetYaxis()->SetTitle("m^{2}(K^{-}#pi^{+}) [GeV/c^{2}]^{2}");
auto dalitz_og_ROOT = dalitz_og->DrawCopy();//converts Rhist into ROOThist
auto dalitz_og_can = new TCanvas("dalitz_og_can", "dalitz_og_can", 1000, 800);
	dalitz_og_can->SetRightMargin(0.15);
	dalitz_og_can->cd();
	dalitz_og_ROOT->Draw("colz");
dalitz_og_can->SaveAs("image/dp_dalitz_nocuts.png");


auto dalitz_cut = dp_cut.Fill<double, double>(TH2D("dalitz_cut", "D^{+} #rightarrow  K^{+}K^{-}#pi^{+} Dalitz Plot (cut not on phi)",200,0.8,3.3,200,0.1,2.3), {"mkpkm", "mkmpi"});
	dalitz_cut->SetStats(0);
    dalitz_cut->GetXaxis()->SetTitle("m^{2}(K^{+}K^{-}) [GeV/c^{2}]^{2}");
    dalitz_cut->GetYaxis()->SetTitle("m^{2}(K^{-}#pi^{+}) [GeV/c^{2}]^{2}");
auto dalitz_cut_ROOT = dalitz_cut->DrawCopy();//converts Rhist into ROOThist
auto dalitz_cut_can = new TCanvas("dalitz_cut_can", "dalitz_cut_can", 1000, 800);
	dalitz_cut_can->SetRightMargin(0.15);
	dalitz_cut_can->cd();
	dalitz_cut_ROOT->Draw("colz");
dalitz_cut_can->SaveAs("image/dp_dalitz_somecuts.png");



auto dalitz_phicut = dp_phicut.Fill<double, double>(TH2D("dalitz_phicut", "D^{+} #rightarrow  K^{+}K^{-}#pi^{+} Dalitz Plot (cut on phi)",200,0.8,3.3,200,0.1,2.3), {"mkpkm", "mkmpi"});
	dalitz_phicut->SetStats(0);
    dalitz_phicut->GetXaxis()->SetTitle("m^{2}(K^{+}K^{-}) [GeV/c^{2}]^{2}");
    dalitz_phicut->GetYaxis()->SetTitle("m^{2}(K^{-}#pi^{+}) [GeV/c^{2}]^{2}");
auto dalitz_phicut_ROOT = dalitz_phicut->DrawCopy();//converts Rhist into ROOThist
auto dalitz_phicut_can = new TCanvas("dalitz_phicut_can", "dalitz_phicut_can", 1000, 800);
	dalitz_phicut_can->SetRightMargin(0.15);
	dalitz_phicut_can->cd();
	dalitz_phicut_ROOT->Draw("colz");
dalitz_phicut_can->SaveAs("image/dp_dalitz_phicut.png");



}//end



