{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();


//create rdataframe for dp, dsp magdown data

RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dpmagup_dec20.root","/share/lazy/D2KKpi/dpmagdown_dec20.root"});
RDataFrame dspdf("Dsp2KKpi/DecayTree", {"/share/lazy/D2KKpi/dspmagup_dec20.root","/share/lazy/D2KKpi/dspmagdown_dec20.root"});


//smaller test sets
/*
RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp_data_dec20/dpmagup01.root");
RDataFrame dspdf("Dsp2KKpi/DecayTree", "/share/lazy/D2KKpi/dsp_data_dec20/dspmagdown01.root");
*/



const double phi_pm = 10;//12 for regular cut
const double phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 
const int cc = 299792458;//speed of light in m/s

const int binmin = 1790;//1790 absolute minimum for dp
const int binmax = 2050;//max value for dsp is 2050
const int nbins = binmax-binmin;//to get events / MeV, should be 260 bins

cout << "there are " << nbins << " bins" << endl;





auto inv_m_func = [](double px1, double py1, double pz1, double pe1, double px2, double py2, double pz2, double pe2) {return TLorentzVector(TLorentzVector(px1, py1, pz1, pe1)+TLorentzVector(px2, py2, pz2, pe2)).Mag2()/1000000 ;};
auto prob_func = [](double prob1, double prob2) {return TMath::Log(prob1) - TMath::Log(prob2) ;};
auto probNNx_func = [](double prob1, double prob2, double prob3) {return prob1*prob2*prob3 ;};
auto lifetime_func = [&cc](double fd, double m, double p) {return (fd*m)/(p*cc*(10^3)) ;};


auto cut_ipchi2 = [](double x) {return x < 4 ;};//5 for regular cut
auto cut_fdchi2 = [](double x) {return x > 225 ;};//175 for regular cut
auto cut_endvertexchi2 = [](double x) {return x < 9 ;};
auto cut_phi = [&phiupperbound, &philowerbound](double x) {return x > philowerbound && x < phiupperbound ;};
auto cut_prob_5 = [] (double x) {return x>5 ;};
auto cut_prob_0 = [] (double x) {return x>0 ;};
auto cut_probnnx = [] (double x) {return x >= 0.70 ;};
auto cut_pK_ambiguity = [] (double x) {return x> 10000 ;}; //10,000 MeV = 10GeV
auto cut_dira = [] (double x) {return x>0.99999 ;};
auto cut_tau = [] (double x) {return x > 0.0000000001 ;};//mikes suggestion : 1e-10, ds+ takeover : 2.3e-10



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
//				   .Define("dp_lifetime", lifetime_func, {"Dplus_FD_OWNPV", "Dplus_MM", "Dplus_P"})
//				   .Filter(cut_tau, {"dp_lifetime"});


auto dsp_cut = dspdf.Filter(cut_ipchi2, {"Dsplus_IPCHI2_OWNPV"})
				   .Filter(cut_fdchi2, {"Dsplus_FDCHI2_OWNPV"})
				   .Filter(cut_endvertexchi2, {"Dsplus_ENDVERTEX_CHI2"})
				   .Filter(cut_pK_ambiguity, {"Kplus_P"})
				   .Filter(cut_pK_ambiguity, {"Kminus_P"})
				   .Filter(cut_dira, {"Dsplus_DIRA_OWNPV"})
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
//				   .Define("dsp_lifetime", lifetime_func, {"Dsplus_FD_OWNPV", "Dsplus_MM", "Dsplus_P"})
//			   	   .Filter(cut_tau, {"dsp_lifetime"});









auto dptotalcuthist = dp_cut.Fill<double>(TH1D("dptotalcuthist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dplus_MM"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dptotalcuthist->SetStats(0);
    dptotalcuthist->SetTitleFont(43);
    dptotalcuthist->SetTitleSize(33);
    dptotalcuthist->GetYaxis()->SetTitle("Events / 1 MeV");//Candidates/(1 MeV/c^{2})
    dptotalcuthist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 for better viewing
    dptotalcuthist->GetYaxis()->SetTitleFont(43);
	dptotalcuthist->GetYaxis()->SetTitleSize(35);
	dptotalcuthist->GetYaxis()->CenterTitle(true);
	//dptotalcuthist->GetYaxis()->SetTitleOffset(1.3);
    dptotalcuthist->GetXaxis()->SetTitle("m(K^{+}K^{-}#pi^{+}) [MeV]");//"m(K^{+}K^{-}#pi^{+}) [MeV]"
    dptotalcuthist->GetXaxis()->SetTitleFont(43);
	dptotalcuthist->GetXaxis()->SetTitleSize(30);
	dptotalcuthist->GetXaxis()->CenterTitle(true);
	//dptotalcuthist->GetXaxis()->SetTitleOffset(1.4);
	dptotalcuthist->SetLineColor(kRed);
	dptotalcuthist->SetLineWidth(3);
/*nsf plot stuff
	//dptotalcuthist->SetTitle("");
	dptotalcuthist->GetXaxis()->SetLabelSize(50);
	dptotalcuthist->GetXaxis()->SetLabelFont(43);
	dptotalcuthist->GetYaxis()->SetLabelSize(50);
	dptotalcuthist->GetYaxis()->SetLabelFont(43);
*/

auto dsptotalcuthist = dsp_cut.Fill<double>(TH1D("dsptotalcuthist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dsplus_MM"});//D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dsptotalcuthist->SetStats(0);
    dsptotalcuthist->SetTitleFont(43);
    dsptotalcuthist->SetTitleSize(33);
    dsptotalcuthist->GetYaxis()->SetTitle("Events / 1 MeV");//Candidates/(1 MeV/c^{2})
    dsptotalcuthist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 for better viewing
    dsptotalcuthist->GetYaxis()->SetTitleFont(43);
	dsptotalcuthist->GetYaxis()->SetTitleSize(35);
	dsptotalcuthist->GetYaxis()->CenterTitle(true);
	//dsptotalcuthist->GetYaxis()->SetTitleOffset(1.4);
    dsptotalcuthist->GetXaxis()->SetTitle("m(K^{+}K^{-}#pi^{+}) [MeV]");
    dsptotalcuthist->GetXaxis()->SetTitleFont(43);
	dsptotalcuthist->GetXaxis()->SetTitleSize(30);
	dsptotalcuthist->GetXaxis()->CenterTitle(true);
	dsptotalcuthist->GetXaxis()->SetTitleOffset(1.3);
	dsptotalcuthist->SetLineColor(kBlue);
	dsptotalcuthist->SetLineWidth(3);
/*nsf plot stuff
	dsptotalcuthist->SetTitle("");
	dsptotalcuthist->GetXaxis()->SetLabelSize(50);
	dsptotalcuthist->GetXaxis()->SetLabelFont(43);
	dsptotalcuthist->GetYaxis()->SetLabelSize(50);
	dsptotalcuthist->GetYaxis()->SetLabelFont(43);
*/


auto dpdsplegendlogy = new TLegend(0.7,0.75,0.9,0.9);;
	dpdsplegendlogy->AddEntry(dptotalcuthist.GetPtr(), "D^{+}  Data ", "l");
	dpdsplegendlogy->AddEntry(dsptotalcuthist.GetPtr(), "D^{+}_{s}  Data", "l");


auto dpdsplegendliny = new TLegend(0.25,0.7,0.46,0.85);
	dpdsplegendliny->AddEntry(dptotalcuthist.GetPtr(), "D^{+}  Data ", "l");
	dpdsplegendliny->AddEntry(dsptotalcuthist.GetPtr(), "D^{+}_{s}  Data", "l");


auto linytotalpullcan = new TCanvas("linytotalpullcan", "linytotalpullcan", 1600, 1200);
	linytotalpullcan->cd();
	linytotalpullcan->SetLeftMargin(0.15);
	linytotalpullcan->SetRightMargin(0.09);
	linytotalpullcan->SetBottomMargin(0.15);
	dsptotalcuthist->Draw();
	dptotalcuthist->Draw("same");
	dpdsplegendliny->Draw("same");

linytotalpullcan->Update();

linytotalpullcan->SaveAs("image/dp_dsp_liny.png");

auto logytotalpullcan = new TCanvas("logytotalpullcan", "logytotalpullcan", 1600, 1200);
	logytotalpullcan->cd();
		TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
		pad1->Draw();
		pad1->cd();
		pad1->SetLogy();
	dsptotalcuthist->Draw();
	dptotalcuthist->Draw("same");
	dpdsplegendlogy->Draw("same");
logytotalpullcan->SaveAs("image/dp_dsp_logy.png");




}//end



