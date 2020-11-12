{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();


//create rdataframe for dp magdown data
RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp2kkpi_magdown.root");
RDataFrame dspdf("Dsp2KKpi/DecayTree", "/share/lazy/D2KKpi/dsp2kkpi_magdown.root");


const double phi_pm = 10;
const double phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 

const int binmin = 1790;//1790 absolute minimum for dp
const int binmax = 2050;//max value for dsp is 2050
const int nbins = 100;


auto inv_m_func = [](double px1, double py1, double pz1, double pe1, double px2, double py2, double pz2, double pe2) {return TLorentzVector(TLorentzVector(px1, py1, pz1, pe1)+TLorentzVector(px2, py2, pz2, pe2)).Mag2()/1000000 ;};
auto prob_func = [](double prob1, double prob2) {return TMath::Log(prob1) - TMath::Log(prob2) ;};
auto probNNx_func = [](double prob1, double prob2, double prob3) {return prob1*prob2*prob3 ;};

auto cut_ipchi2 = [](double x) {return x < 4 ;};
auto cut_fdchi2 = [](double x) {return x > 200 ;};
auto cut_endvertexchi2 = [](double x) {return x < 3 ;};
auto cut_phi = [phiupperbound, philowerbound](double x) {return x > philowerbound && x < phiupperbound ;};
auto cut_prob_5 = [] (double x) {return x>5 ;};
auto cut_prob_0 = [] (double x) {return x>5 ;};

auto cut_probnn1 = [] (double x) {return x < 0.25 ;};
auto cut_probnn2 = [] (double x) {return (x >= 0.25 && x < 0.5) ;};
auto cut_probnn3 = [] (double x) {return (x >= 0.50 && x < 0.75) ;};
auto cut_probnn4 = [] (double x) {return x >= 0.75 ;};



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
				   .Filter(cut_phi, {"mkpkm"})
			   	   .Define("ProbNNx", probNNx_func, {"Kminus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNk", "Piplus_MC15TuneV1_ProbNNpi"});


auto dsp_cut = dspdf.Filter(cut_ipchi2, {"Dsplus_IPCHI2_OWNPV"})
				   .Filter(cut_fdchi2, {"Dsplus_FDCHI2_OWNPV"})
				   .Filter(cut_endvertexchi2, {"Dsplus_ENDVERTEX_CHI2"})
				   .Define("kminuslog", prob_func, {"Kminus_MC15TuneV1_ProbNNk", "Kminus_MC15TuneV1_ProbNNpi"})
				   .Define("kpluslog", prob_func, {"Kplus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNpi"})
				   .Define("pipluslog", prob_func, {"Piplus_MC15TuneV1_ProbNNpi", "Piplus_MC15TuneV1_ProbNNk"})
				   .Filter(cut_prob_5, {"kminuslog"})
				   .Filter(cut_prob_5, {"kpluslog"})
				   .Filter(cut_prob_0, {"pipluslog"})
				   .Define("mkpkm", inv_m_func, {"Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_PE", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_PE"})
				   .Filter(cut_phi, {"mkpkm"})
			   	   .Define("ProbNNx", probNNx_func, {"Kminus_MC15TuneV1_ProbNNk", "Kplus_MC15TuneV1_ProbNNk", "Piplus_MC15TuneV1_ProbNNpi"});




auto dp_probnn1 = dp_cut.Filter(cut_probnn1, {"ProbNNx"});
auto dp_probnn2 = dp_cut.Filter(cut_probnn2, {"ProbNNx"});
auto dp_probnn3 = dp_cut.Filter(cut_probnn3, {"ProbNNx"});
auto dp_probnn4 = dp_cut.Filter(cut_probnn4, {"ProbNNx"});

auto dsp_probnn1 = dsp_cut.Filter(cut_probnn1, {"ProbNNx"});
auto dsp_probnn2 = dsp_cut.Filter(cut_probnn2, {"ProbNNx"});
auto dsp_probnn3 = dsp_cut.Filter(cut_probnn3, {"ProbNNx"});
auto dsp_probnn4 = dsp_cut.Filter(cut_probnn4, {"ProbNNx"});



/* This block is used to produce the distribution of ProbNnx for all dp
auto probNNxhist = dp_cut.Fill<double>(TH1D("probNNxhist","ProbNNx after all cuts",20, 0, 1), {"ProbNNx"});
	probNNxhist->SetStats(0);
    probNNxhist->SetTitleFont(43);
    probNNxhist->SetTitleSize(35);
    probNNxhist->GetYaxis()->SetTitle("events per 0.05");//Candidates/(1 MeV/c^{2})
    probNNxhist->GetYaxis()->SetTitleFont(43);
	probNNxhist->GetYaxis()->SetTitleSize(30);
	probNNxhist->GetYaxis()->CenterTitle(true);
    probNNxhist->GetXaxis()->SetTitle("events per 0.05");//Candidates/(1 MeV/c^{2})
    probNNxhist->GetXaxis()->SetTitleFont(43);
	probNNxhist->GetXaxis()->SetTitleSize(30);
	probNNxhist->GetXaxis()->SetTitleOffset(1.2);
	probNNxhist->GetXaxis()->CenterTitle(true);

auto probNNxhistROOT = probNNxhist->DrawCopy();//converts Rhist into ROOThist

auto probNNxcan = new TCanvas("probNNxcan", "probNNxcan", 1200, 800);
	probNNxcan->cd();
	probNNxhistROOT->Draw();
probNNxcan->SaveAs("image/dp_probnnx.png");
*/



auto dpprobnn1hist = dp_probnn1.Fill<double>(TH1D("dpprobnn1hist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dplus_MM"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dpprobnn1hist->SetStats(0);
    dpprobnn1hist->SetTitleFont(43);
    dpprobnn1hist->SetTitleSize(33);
    dpprobnn1hist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");//Candidates/(1 MeV/c^{2})
    dpprobnn1hist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 or better viewing
    dpprobnn1hist->GetYaxis()->SetTitleFont(43);
	dpprobnn1hist->GetYaxis()->SetTitleSize(30);
	dpprobnn1hist->GetYaxis()->CenterTitle(true);
    dpprobnn1hist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dpprobnn1hist->GetXaxis()->SetTitleFont(43);
	dpprobnn1hist->GetXaxis()->SetTitleSize(25);
	dpprobnn1hist->GetXaxis()->CenterTitle(true);
	dpprobnn1hist->GetXaxis()->SetTitleOffset(1.2);
	dpprobnn1hist->SetLineColor(kRed);

auto dspprobnn1hist = dsp_probnn1.Fill<double>(TH1D("dspprobnn1hist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dsplus_MM"});//D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dspprobnn1hist->SetStats(0);
    dspprobnn1hist->SetTitleFont(43);
    dspprobnn1hist->SetTitleSize(33);
    dspprobnn1hist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");//Candidates/(1 MeV/c^{2})
    dspprobnn1hist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 or better viewing
    dspprobnn1hist->GetYaxis()->SetTitleFont(43);
	dspprobnn1hist->GetYaxis()->SetTitleSize(30);
	dspprobnn1hist->GetYaxis()->CenterTitle(true);
    dspprobnn1hist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dspprobnn1hist->GetXaxis()->SetTitleFont(43);
	dspprobnn1hist->GetXaxis()->SetTitleSize(30);
	dspprobnn1hist->GetXaxis()->CenterTitle(true);
	dspprobnn1hist->GetXaxis()->SetTitleOffset(1.2);
	dspprobnn1hist->SetLineColor(kRed);





auto dpprobnn2hist = dp_probnn2.Fill<double>(TH1D("dpprobnn2hist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dplus_MM"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dpprobnn2hist->SetStats(0);
    dpprobnn2hist->SetTitleFont(43);
    dpprobnn2hist->SetTitleSize(33);
    dpprobnn2hist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");//Candidates/(1 MeV/c^{2})
    dpprobnn2hist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 or better viewing
    dpprobnn2hist->GetYaxis()->SetTitleFont(43);
	dpprobnn2hist->GetYaxis()->SetTitleSize(30);
	dpprobnn2hist->GetYaxis()->CenterTitle(true);
    dpprobnn2hist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dpprobnn2hist->GetXaxis()->SetTitleFont(43);
	dpprobnn2hist->GetXaxis()->SetTitleSize(25);
	dpprobnn2hist->GetXaxis()->CenterTitle(true);
	dpprobnn2hist->GetXaxis()->SetTitleOffset(1.2);
	dpprobnn2hist->SetLineColor(kBlue);

auto dspprobnn2hist = dsp_probnn2.Fill<double>(TH1D("dspprobnn2hist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dsplus_MM"});//D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dspprobnn2hist->SetStats(0);
    dspprobnn2hist->SetTitleFont(43);
    dspprobnn2hist->SetTitleSize(33);
    dspprobnn2hist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");//Candidates/(1 MeV/c^{2})
    dspprobnn2hist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 or better viewing
    dspprobnn2hist->GetYaxis()->SetTitleFont(43);
	dspprobnn2hist->GetYaxis()->SetTitleSize(30);
	dspprobnn2hist->GetYaxis()->CenterTitle(true);
    dspprobnn2hist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dspprobnn2hist->GetXaxis()->SetTitleFont(43);
	dspprobnn2hist->GetXaxis()->SetTitleSize(30);
	dspprobnn2hist->GetXaxis()->CenterTitle(true);
	dspprobnn2hist->GetXaxis()->SetTitleOffset(1.2);
	dspprobnn2hist->SetLineColor(kBlue);






auto dpprobnn3hist = dp_probnn3.Fill<double>(TH1D("dpprobnn3hist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dplus_MM"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dpprobnn3hist->SetStats(0);
    dpprobnn3hist->SetTitleFont(43);
    dpprobnn3hist->SetTitleSize(33);
    dpprobnn3hist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");//Candidates/(1 MeV/c^{2})
    dpprobnn3hist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 or better viewing
    dpprobnn3hist->GetYaxis()->SetTitleFont(43);
	dpprobnn3hist->GetYaxis()->SetTitleSize(30);
	dpprobnn3hist->GetYaxis()->CenterTitle(true);
    dpprobnn3hist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dpprobnn3hist->GetXaxis()->SetTitleFont(43);
	dpprobnn3hist->GetXaxis()->SetTitleSize(25);
	dpprobnn3hist->GetXaxis()->CenterTitle(true);
	dpprobnn3hist->GetXaxis()->SetTitleOffset(1.2);
	dpprobnn3hist->SetLineColor(kGreen+2);

auto dspprobnn3hist = dsp_probnn3.Fill<double>(TH1D("dspprobnn3hist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dsplus_MM"});//D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dspprobnn3hist->SetStats(0);
    dspprobnn3hist->SetTitleFont(43);
    dspprobnn3hist->SetTitleSize(33);
    dspprobnn3hist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");//Candidates/(1 MeV/c^{2})
    dspprobnn3hist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 or better viewing
    dspprobnn3hist->GetYaxis()->SetTitleFont(43);
	dspprobnn3hist->GetYaxis()->SetTitleSize(30);
	dspprobnn3hist->GetYaxis()->CenterTitle(true);
    dspprobnn3hist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dspprobnn3hist->GetXaxis()->SetTitleFont(43);
	dspprobnn3hist->GetXaxis()->SetTitleSize(30);
	dspprobnn3hist->GetXaxis()->CenterTitle(true);
	dspprobnn3hist->GetXaxis()->SetTitleOffset(1.2);
	dspprobnn3hist->SetLineColor(kGreen+2);




auto dpprobnn4hist = dp_probnn4.Fill<double>(TH1D("dpprobnn4hist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dplus_MM"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dpprobnn4hist->SetStats(0);
    dpprobnn4hist->SetTitleFont(43);
    dpprobnn4hist->SetTitleSize(33);
    dpprobnn4hist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");//Candidates/(1 MeV/c^{2})
    dpprobnn4hist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 or better viewing
    dpprobnn4hist->GetYaxis()->SetTitleFont(43);
	dpprobnn4hist->GetYaxis()->SetTitleSize(30);
	dpprobnn4hist->GetYaxis()->CenterTitle(true);
    dpprobnn4hist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dpprobnn4hist->GetXaxis()->SetTitleFont(43);
	dpprobnn4hist->GetXaxis()->SetTitleSize(25);
	dpprobnn4hist->GetXaxis()->CenterTitle(true);
	dpprobnn4hist->GetXaxis()->SetTitleOffset(1.2);
	dpprobnn4hist->SetLineColor(kBlack);

auto dspprobnn4hist = dsp_probnn4.Fill<double>(TH1D("dspprobnn4hist","D^{+}_{(s)} #rightarrow K^{+}K^{-}#pi^{+}",nbins, binmin, binmax), {"Dsplus_MM"});//D^{+}_{s} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dspprobnn4hist->SetStats(0);
    dspprobnn4hist->SetTitleFont(43);
    dspprobnn4hist->SetTitleSize(33);
    dspprobnn4hist->GetYaxis()->SetTitle("Candidates/(1 MeV/c^{2})");//Candidates/(1 MeV/c^{2})
    dspprobnn4hist->SetMinimum(100);//make minimum 100 so logy doesnt break, make 100 or better viewing
    dspprobnn4hist->GetYaxis()->SetTitleFont(43);
	dspprobnn4hist->GetYaxis()->SetTitleSize(30);
	dspprobnn4hist->GetYaxis()->CenterTitle(true);
    dspprobnn4hist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dspprobnn4hist->GetXaxis()->SetTitleFont(43);
	dspprobnn4hist->GetXaxis()->SetTitleSize(30);
	dspprobnn4hist->GetXaxis()->CenterTitle(true);
	dspprobnn4hist->GetXaxis()->SetTitleOffset(1.2);
	dspprobnn4hist->SetLineColor(kBlack);



auto dpdspprobnnlegend = new TLegend(0.65,0.8,0.9,0.9);
	dpdspprobnnlegend->AddEntry(dpprobnn1hist.GetPtr(), "0 <= ProbNNx < 0.25", "l");
	dpdspprobnnlegend->AddEntry(dpprobnn2hist.GetPtr(), "0.25 <= ProbNNx < 0.5", "l");
	dpdspprobnnlegend->AddEntry(dpprobnn3hist.GetPtr(), "0.5 <= ProbNNx < 0.75", "l");
	dpdspprobnnlegend->AddEntry(dpprobnn4hist.GetPtr(), "0.75 <= ProbNNx < 1", "l");



auto logyprobnncan = new TCanvas("logyprobnncan", "logyprobnncan", 1600, 1200);
	logyprobnncan->cd();
		TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
		pad1->Draw();
		pad1->cd();
		pad1->SetLogy();
	dspprobnn4hist->Draw();//draw this one first bc it is tallest
	dpprobnn1hist->Draw("same");
	dspprobnn1hist->Draw("same");
	dpprobnn2hist->Draw("same");
	dspprobnn2hist->Draw("same");
	dpprobnn3hist->Draw("same");
	dspprobnn3hist->Draw("same");
	dpprobnn4hist->Draw("same");

	
	dpdspprobnnlegend->Draw("same");


logyprobnncan->SaveAs("image/dp_dsp_ProbNN_tightcuts.png");













}//end



