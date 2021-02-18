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

auto cut_run = [] (unsigned int x) {return x != 193695 ;};





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


auto dp_runcut = dp_cut.Filter(cut_run, {"runNumber"});
auto dsp_runcut = dsp_cut.Filter(cut_run, {"runNumber"});





//get and print number of entries
/*
	std::cout << std::dec << std::fixed << std::cout.precision(0);
	
	auto dpdf_count = dpdf.Count();
	double dpdfEntries = *dpdf_count;
	cout << "Dplus Raw Entries: " << dpdfEntries << endl;
	auto dspdf_count = dspdf.Count();
	double dspdfEntries = *dspdf_count;
	cout << "Dsplus Raw Entries: " << dspdfEntries << endl;

	auto dpdf_cut_count = dp_cut.Count();
	double dpdf_cutEntries = *dpdf_cut_count;
	cout << "Dplus Cut Entries: " << dpdf_cutEntries << endl;
	auto dspdf_cut_count = dsp_cut.Count();
	double dspdf_cutEntries = *dspdf_cut_count;
	cout << "Dsplus Cut Entries: " << dspdf_cutEntries << endl;

	auto dpdf_runcut_count = dp_runcut.Count();
	double dpdf_runcutEntries = *dpdf_runcut_count;
	cout << "Dplus Run Cut Entries: " << dpdf_runcutEntries << endl;
	auto dspdf_runcut_count = dsp_runcut.Count();
	double dspdf_runcutEntries = *dspdf_runcut_count;
	cout << "Dsplus Run Cut Entries: " << dspdf_runcutEntries << endl;
*/


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
/*
	auto dpmasshist = dp_cut.Fill<double>(TH1D("dpmasshist","d -> kkpi",nbins, binmin, binmax), {"Dplus_MM"});
	auto dspmasshist = dsp_cut.Fill<double>(TH1D("dspmasshist","ds -> kkpi",nbins, binmin, binmax), {"Dsplus_MM"});
	int dpVals[nbins];
	int dspVals[nbins];
	int diff;
		std::cout << "Events per MeV:" << endl;
		std::cout << "Bin\tD\tDs" << endl;
	for (int i=1; i<nbins; i++) {
		int massbin = dpmasshist->GetBinCenter(i);
		int dpm = dpmasshist->GetBinContent(i);
		int dspm = dspmasshist->GetBinContent(i);
		MeV[i] = massbin;
		dpVals[i] = dpm;
		dspVals[i] = dspm;
		std::cout << x << '\t' << dpm << '\t' << dspm << endl;
	}
*/
//these values are the overlap region as produced above
/*
	int MeV[81] = {1878, 1879, 1880, 1881, 1882, 1883, 1884, 1885, 1886, 1887, 1888, 1889, 1890, 1891, 1892, 1893, 1894, 1895, 1896, 1897, 1898, 1899, 1900, 1901, 1902, 1903, 1904, 1905, 1906, 1907, 1908, 1909, 1910, 1911, 1912, 1913, 1914, 1915, 1916, 1917, 1918, 1919, 1920, 1921, 1922, 1923, 1924, 1925, 1926, 1927, 1928, 1929, 1930, 1931, 1932, 1933, 1934, 1935, 1936, 1937, 1938, 1939, 1940, 1941, 1942, 1943, 1944, 1945, 1946, 1947, 1948, 1949, 1950, 1951, 1952, 1953, 1954, 1955, 1956, 1957, 1958};
	int nD[81] = {86014, 65453, 49013, 36850, 27061, 19801, 14523, 10895, 8124, 6395, 4969, 3993, 3278, 2618, 2267, 1936, 1769, 1605, 1491, 1447, 1335, 1338, 1264, 1254, 1139, 1118, 1146, 1142, 1132, 1145, 1112, 1148, 1122, 1161, 1165, 1147, 1180, 1205, 1255, 1309, 1338, 1328, 1290, 1344, 1420, 1473, 1486, 1524, 1548, 1614, 1636, 1709, 1811, 1829, 1917, 2030, 2128, 2170, 2288, 2477, 2646, 2695, 2929, 3319, 3470, 4051, 4140, 4843, 5523, 6116, 5797, 1627, 271, 91, 44, 23, 15, 5, 5, 3, 0};
	int nDs[81] = {0, 3, 7, 8, 5, 16, 34, 41, 82, 231, 933, 2781, 2946, 2489, 2213, 1900, 1759, 1602, 1485, 1450, 1339, 1341, 1267, 1255, 1142, 1123, 1156, 1155, 1133, 1147, 1114, 1152, 1126, 1165, 1170, 1156, 1188, 1206, 1257, 1315, 1344, 1335, 1294, 1356, 1428, 1478, 1487, 1534, 1560, 1621, 1642, 1719, 1813, 1835, 1930, 2036, 2140, 2180, 2301, 2498, 2656, 2715, 2951, 3348, 3490, 4076, 4189, 4943, 5682, 6573, 7874, 9806, 11853, 15115, 19459, 25523, 33764, 44958, 59800, 79143, 104298};
	int pm[81];
	auto diffhist = new TH1D("diffhist", "n(Ds - D) in overlap region)", 81, MeV[0], MeV[80]);
		diffhist->SetStats(0);
		diffhist->SetTitleFont(43);
		diffhist->SetTitleSize(35);
		diffhist->GetYaxis()->SetTitle("n(Ds - D) /(1 MeV/c^{2})");
		//diffhist->SetMinimum(10);//for logy, but might not be a good idea since +/- values
		diffhist->GetYaxis()->SetTitleFont(43);
		diffhist->GetYaxis()->SetTitleSize(30);
		diffhist->GetYaxis()->CenterTitle(true);
	for (int i=0; i<81; i++) {
		int diff = nDs[i] - nD[i];
		if (diff > 0) {
			pm[i]=1;		
		}
		if (diff < 0) {
			pm[i]=-1;		
		}
		if (diff > 0) {
			pm[i]=0;		
		}
		diffhist->SetBinContent(i+1, diff);

	}
	auto can = new TCanvas("can", "can", 1600, 1200);
		can->cd();
		//can->SetLeftMargin(0.15);
		//can->SetRightMargin(0.09);
		//can->SetBottomMargin(0.15);
		TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
		pad1->Draw();
		pad1->cd();
		pad1->SetLogy();
	diffhist->Draw();
	can->SaveAs("image/aaa_overlap_difference.png");
*/



//looking at entries per run number to see why Ds seems to have more data than D+
	//both cut and uncut, d+ and ds, had a range of (19228, 202897)
/*
auto dpMin = dp_cut.Min("runNumber");
auto dpMax = dp_cut.Max("runNumber");
int dpMinRunN = *dpMin;
int dpMaxRunN = *dpMax;
cout << "Dplus min run number: " << dpMinRunN << "\nDplus max run number: " << dpMaxRunN << endl;
auto dspMin = dsp_cut.Min("runNumber");
auto dspMax = dsp_cut.Max("runNumber");
int dspMinRunN = *dspMin;
int dspMaxRunN = *dspMax;
cout << "Ds min run number: " << dspMinRunN << "\nDs max run number: " << dspMaxRunN << endl;
*/     
	//getting the counts per run entry and printing. only one with 0 d+ is 0193695
/*
auto dpRunNumberHist = dpdf.Fill<unsigned int>(TH1D("dpRunNumberHist"," ", 11000, 192000, 203000), {"runNumber"});
auto dspRunNumberHist = dspdf.Fill<unsigned int>(TH1D("dspRunNumberHist"," ", 11000, 192000, 203000), {"runNumber"});

auto dpRunNumberHistcut = dp_cut.Fill<unsigned int>(TH1D("dpRunNumberHistcut"," ", 11000, 192000, 203000), {"runNumber"});
auto dspRunNumberHistcut = dsp_cut.Fill<unsigned int>(TH1D("dspRunNumberHistcut"," ", 11000, 192000, 203000), {"runNumber"});

std::cout << "runN\tuc(D+)\tuc(Ds)\tc(D+)\tc(Ds)" << endl;
int runN[11000];
int dpCount[11000];
int dspCount[11000];
int dpCountcut[11000];
int dspCountcut[11000];

for (int i=1; i<11000; i++) {
	int runNi = dspRunNumberHist->GetBinCenter(i);
	int dpCounti = dpRunNumberHist->GetBinContent(i);
	int dspCounti = dspRunNumberHist->GetBinContent(i);
	int dpCountcuti = dpRunNumberHistcut->GetBinContent(i);
	int dspCountcuti = dspRunNumberHistcut->GetBinContent(i);
	runN[i] = runNi;
	dpCount[i] = dpCounti;
	dspCount[i] = dspCounti;
	dpCountcut[i] = dpCountcuti;
	dspCountcut[i] = dspCountcuti;

	if (dpCounti > 0 || dspCounti > 0) {
	std::cout << std::dec << std::fixed << std::cout.precision(0);
	std::cout << runNi << "\t" << dpCounti << "\t" << dspCounti << "\t" << dpCountcuti << "\t" << dspCountcuti << endl;
	}
}
*/



//second look at overlap region after cutting excess run from ds

	auto dpmasshist = dp_cut.Fill<double>(TH1D("dpmasshist","d -> kkpi",nbins, binmin, binmax), {"Dplus_MM"});
	auto dspmasshist = dsp_cut.Fill<double>(TH1D("dspmasshist","ds -> kkpi",nbins, binmin, binmax), {"Dsplus_MM"});
	auto diffhist = new TH1D("diffhist", "n(Ds - D) in overlap region)", nbins, binmin, binmax);
		diffhist->SetStats(0);
		diffhist->SetTitleFont(43);
		diffhist->SetTitleSize(35);
		diffhist->GetYaxis()->SetTitle("n(Ds - D) /(1 MeV/c^{2})");
		//diffhist->SetMinimum(10);//for logy, but might not be a good idea since +/- values
		diffhist->GetYaxis()->SetTitleFont(43);
		diffhist->GetYaxis()->SetTitleSize(30);
		diffhist->GetYaxis()->CenterTitle(true);
		diffhist->SetLineWidth(3);
		diffhist->SetLineColor(kRed);
		diffhist->GetXaxis()->SetRangeUser(1890, 1948);

	for (int i=0; i<nbins; i++) {
		int massbin = dpmasshist->GetBinCenter(i);
		int dpm = dpmasshist->GetBinContent(i);
		int dspm = dspmasshist->GetBinContent(i);
		int diff = dspm - dpm;
		diffhist->SetBinContent(i, diff);
	}

	auto can = new TCanvas("can", "can", 1600, 1200);
		can->cd();
		//can->SetLeftMargin(0.15);
		//can->SetRightMargin(0.09);
		//can->SetBottomMargin(0.15);
		TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
		pad1->Draw();
		pad1->cd();
		//pad1->SetLogy();
	diffhist->Draw();
	diffhist->Draw("TEXT same");
	can->SaveAs("image/overlap_difference.png");





}//end



