{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();


//create rdataframe for dp magdown data
RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp2kkpi_magdown.root");

//get and print number of entries
/*
auto dpdf_count = dpdf.Count();
double dpdfEntries = *dpdf_count;
cout << "Dp MagDown Raw Entries: " << dpdfEntries << endl;
*/
//get and print column names
/*
auto colNames = dpdf.GetColumnNames();
for (auto &&colName : colNames) std::cout << colName << std::endl;
*/

const double phi_pm = 12;
const double phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 







auto inv_m_func = [](double px1, double py1, double pz1, double pe1, double px2, double py2, double pz2, double pe2) {return TLorentzVector(TLorentzVector(px1, py1, pz1, pe1)+TLorentzVector(px2, py2, pz2, pe2)).Mag2()/1000000 ;};
auto prob_func = [](double prob1, double prob2) {return TMath::Log(prob1) - TMath::Log(prob2) ;};


auto cut_ipchi2 = [](double x) {return x < 5 ;};
auto cut_fdchi2 = [](double x) {return x > 175 ;};
auto cut_phi = [phiupperbound, philowerbound](double x) {return ((x > philowerbound) && (x < phiupperbound)) ;};
auto cut_prob_5 = [] (double x) {return x>5 ;};
auto cut_prob_0 = [] (double x) {return x>5 ;};

auto signalregion = [](double x) {return ((x > 1855) && (x < 1885)) ;};
auto backgroundregion = [](double x) {return ((x>1810 && x < 1840) || (x > 1900 && x < 1930)) ;};


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




auto dp_sig_df = dpdf.Filter(signalregion, {"Dplus_MM"});
auto dp_bg_df = dpdf.Filter(backgroundregion, {"Dplus_MM"});


auto dpendvertexcan = new TCanvas("dpendvertexcan", "dpendvertexcan", 1200, 800);
	dpendvertexcan->cd();
	//TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
	//pad1->Draw();
	//pad1->cd();
	//pad1->SetLogy();



auto dpendvertexsighist = dp_sig_df.Fill<double>(TH1D("signalhist","D+ EndVertex Chi2",36, 0, 18), {"Dplus_ENDVERTEX_CHI2"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dpendvertexsighist->SetStats(0);
    dpendvertexsighist->SetTitleFont(43);
    dpendvertexsighist->SetTitleSize(35);
    dpendvertexsighist->GetYaxis()->SetTitle("events per 1mev");//Candidates/(1 MeV/c^{2})
    dpendvertexsighist->SetMinimum(100);//make minimum 1 so logy doesnt break, make 100 or better viewing
    dpendvertexsighist->GetYaxis()->SetTitleFont(43);
	dpendvertexsighist->GetYaxis()->SetTitleSize(30);
	dpendvertexsighist->GetYaxis()->CenterTitle(true);
    dpendvertexsighist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dpendvertexsighist->GetXaxis()->SetTitleFont(43);
	dpendvertexsighist->GetXaxis()->SetTitleSize(25);
	dpendvertexsighist->GetXaxis()->CenterTitle(true);
	dpendvertexsighist->GetXaxis()->SetTitleOffset(1.2);
	dpendvertexsighist->SetLineColor(kBlue);
auto dpendvertexsighistROOT = dpendvertexsighist->DrawCopy();

auto dpendvertexbghist = dp_bg_df.Fill<double>(TH1D("backgroundhist","D+ EndVertex Chi2",36, 0, 18), {"Dplus_ENDVERTEX_CHI2"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	dpendvertexbghist->SetStats(0);
    dpendvertexbghist->SetTitleFont(43);
    dpendvertexbghist->SetTitleSize(35);
    dpendvertexbghist->GetYaxis()->SetTitle("events per 1mev");//Candidates/(1 MeV/c^{2})
    dpendvertexbghist->SetMinimum(100);//make minimum 1 so logy doesnt break, make 100 or better viewing
    dpendvertexbghist->GetYaxis()->SetTitleFont(43);
	dpendvertexbghist->GetYaxis()->SetTitleSize(30);
	dpendvertexbghist->GetYaxis()->CenterTitle(true);
    dpendvertexbghist->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
    dpendvertexbghist->GetXaxis()->SetTitleFont(43);
	dpendvertexbghist->GetXaxis()->SetTitleSize(25);
	dpendvertexbghist->GetXaxis()->CenterTitle(true);
	dpendvertexbghist->GetXaxis()->SetTitleOffset(1.2);
	dpendvertexbghist->SetLineColor(kRed);

auto dpendvertexbghistROOT = dpendvertexbghist->DrawCopy();
dpendvertexbghistROOT->Add(dpendvertexbghistROOT, -0.5); //this is necessary since this is twice the mass region of the signal, so scale it down by 1/2 for a good comparison




auto endvertexlegend = new TLegend(0.7,0.8,0.9,0.9);
	endvertexlegend->AddEntry(dpendvertexsighist.GetPtr(), "Signal Region", "lp");
	endvertexlegend->AddEntry(dpendvertexbghist.GetPtr(), "Background Region", "lp");


dpendvertexsighist->Draw("e0 9");
dpendvertexbghist->Draw("e0 9 same");
endvertexlegend->Draw("same");
dpendvertexcan->SaveAs("image/dp_endvertex_sigbg.png");

}//end



