{//begin
#include <iostream>
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"
using namespace ROOT;


EnableImplicitMT(); //run in parallel!

const double phi_pm = 10;//12 for regular cut
const double phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 

const int binmin = 1790;//1790 absolute minimum for dp
const int binmax = 2050;//max value for dsp is 2050
const int nbins = binmax - binmin;

auto inv_m_func = [](double px1, double py1, double pz1, double pe1, double px2, double py2, double pz2, double pe2) {return TLorentzVector(TLorentzVector(px1, py1, pz1, pe1)+TLorentzVector(px2, py2, pz2, pe2)).Mag2()/1000000 ;};
auto prob_func = [](double prob1, double prob2) {return TMath::Log(prob1) - TMath::Log(prob2) ;};
auto probNNx_func = [](double prob1, double prob2, double prob3) {return prob1*prob2*prob3 ;};

auto cut_ipchi2 = [](double x) {return x < 4 ;};
auto cut_fdchi2 = [](double x) {return x > 225 ;};
auto cut_endvertexchi2 = [](double x) {return x < 9 ;};
auto cut_phi = [&phiupperbound, &philowerbound](double x) {return x > philowerbound && x < phiupperbound ;};
auto cut_prob_5 = [] (double x) {return x>5 ;};
auto cut_prob_0 = [] (double x) {return x>0 ;};
auto cut_probnnx = [] (double x) {return x >= 0.70 ;};
auto cut_pK_ambiguity = [] (double x) {return x> 10000 ;};
auto cut_dira = [] (double x) {return x>0.99999 ;};
auto cut_tau = [] (double x) {return x > 0.0000000001 ;};






//create rdataframe for dp, dsp magdown data

RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dpmagup_dec20.root","/share/lazy/D2KKpi/dpmagdown_dec20.root"});
RDataFrame dspdf("Dsp2KKpi/DecayTree", {"/share/lazy/D2KKpi/dspmagup_dec20.root","/share/lazy/D2KKpi/dspmagdown_dec20.root"});


//smaller test sets
/*
RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp_data_dec20/dpmagup01.root");
RDataFrame dspdf("Dsp2KKpi/DecayTree", "/share/lazy/D2KKpi/dsp_data_dec20/dspmagdown01.root");
*/


//cut the data

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


//get and print number of entries
	
	auto dpdf_count = dp_cut.Count();
	double dpdfEntries = *dpdf_count;
	cout << "Dplus Entries: " << dpdfEntries << endl;
	auto dspdf_count = dsp_cut.Count();
	double dspdfEntries = *dspdf_count;
	cout << "Dsplus Entries: " << dspdfEntries << endl;
	


//get and print column names
	/*
	auto colNames = dpdf.GetColumnNames();
	for (auto &&colName : colNames) std::cout << colName << std::endl;
	*/


//information about runNumber
	/*
	auto dprunhist = dpdf.Fill<unsigned int>(TH1D("dprunhist","D+ run number", 8000, 194000, 202000), {"runNumber"});
	int xVals[8000];
	int runCount[8000];
	for (int i=1;i<8000;i++) {
		int x = dprunhist->GetBinCenter(i);
		int val = dprunhist->GetBinContent(i);
		xVals[i]=x;
		runCount[i]=val;

		if (runCount[i] > 1) {
			std::cout << "runNumber " << xVals[i] << " has " << runCount[i] << " candidates." << std::endl;
		}
	}
	*/


//information about OdinTCK
	/*
	auto odinTCK = dpdf.Fill<unsigned int>(TH1D("odinTCK","D+ odin tck", 1300000, 290300000, 291600000), {"OdinTCK"});
	int xVals[1300000];
	int tck[1300000];
	int temp = 0;
	for (int i=1; i<1300000; i++) {
		int x = odinTCK->GetBinCenter(i);
		int val = odinTCK->GetBinContent(i);
		xVals[i] = x;
		tck[i] = val;

		if (tck[i] > 0) {
			std::cout << std::hex << "OdinTCK " << xVals[i];
			std::cout << std::dec << std::fixed << std::cout.precision(0) << " has " << tck[i] << " entries." << endl;
			temp += tck[i];
		}
	}
	cout << "Total TCK counted entries: " << temp << endl;
	*/


//information about events per bin in the "overlap region" (1880 - 1960 MeV)

	auto dpmasshist = dp_cut.Fill<double>(TH1D("dpmasshist","d -> kkpi",nbins, binmin, binmax), {"Dplus_MM"});
	auto dspmasshist = dsp_cut.Fill<double>(TH1D("dspmasshist","ds -> kkpi",nbins, binmin, binmax), {"Dsplus_MM"});
	int xVals[nbins];
	int dpVals[nbins];
	int dspVals[nbins];
		std::cout << "Events per MeV:" << endl;
		std::cout << "Bin\tD\tDs" << endl;
	for (int i=1; i<nbins; i++) {
		int x = dpmasshist->GetBinCenter(i);
		int dpm = dpmasshist->GetBinContent(i);
		int dspm = dspmasshist->GetBinContent(i);
		xVals[i] = x;
		dpVals[i] = dpm;
		dspVals[i] = dspm;
		std::cout << x << '\t' << dpm << '\t' << dspm << endl;
	}








}//end



