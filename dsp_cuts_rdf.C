{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();


//create rdataframe for dp magdown data
RDataFrame dspdf("Dsp2KKpi/DecayTree", "/share/lazy/D2KKpi/magdowndata/dsp01.root");

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

const int binmin = 1880;//1790 absolute minimum for dp
const int binmax = 2050;//1950 absolute minimum for dp
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
				   .Filter(cut_phi, {"mkpkm"});


auto dsp_cut_new = dspdf.Filter(cut_ipchi2, {"Dsplus_IPCHI2_OWNPV"})
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
				   .Filter(cut_dira, {"Dsplus_DIRA_OWNPV"});




auto totalcuthist = dsp_cut.Fill<double>(TH1D("totalcuthist","Ds+",nbins, binmin, binmax), {"Dsplus_MM"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
	totalcuthist->SetStats(0);
    totalcuthist->SetTitleFont(43);
    totalcuthist->SetTitleSize(35);
    totalcuthist->GetYaxis()->SetTitle("events per 1mev");//Candidates/(1 MeV/c^{2})
    totalcuthist->SetMinimum(1);//make minimum 1 so logy doesnt break, make 100 or better viewing
    totalcuthist->GetYaxis()->SetTitleFont(43);
	totalcuthist->GetYaxis()->SetTitleSize(30);
	totalcuthist->GetYaxis()->CenterTitle(true);
	totalcuthist->SetLineColor(kBlue +2);
auto totalcuthistROOT = totalcuthist->DrawCopy();//converts Rhist into ROOThist


auto totalcuthistnew = dsp_cut_new.Fill<double>(TH1D("totalcuthistnew","Ds+",nbins, binmin, binmax), {"Dsplus_MM"});//D^{+} #rightarrow K^{+}K^{-}#pi^{+} Cut and Fit
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
logytotalpullcan->SaveAs("image/aaaaaaa.png");

}//end



