{//begin
#include <iostream>
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"
using namespace ROOT;


EnableImplicitMT(); //run in parallel!


//create rdataframe for dp, dsp magdown data

RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dpmagup_dec20.root","/share/lazy/D2KKpi/dpmagdown_dec20.root"});
RDataFrame dspdf("Dsp2KKpi/DecayTree", {"/share/lazy/D2KKpi/dspmagup_dec20.root","/share/lazy/D2KKpi/dspmagdown_dec20.root"});


//smaller test sets
/*
RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp_data_dec20/dpmagup01.root");
RDataFrame dspdf("Dsp2KKpi/DecayTree", "/share/lazy/D2KKpi/dsp_data_dec20/dspmagdown01.root");
*/



//get and print number of entries
	
	auto dpdf_count = dspdf.Count();
	double dpdfEntries = *dpdf_count;
	cout << "Raw Entries: " << dpdfEntries << endl;
	


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


//information about OdinTCK - I believe the OdinTCK is the 

	auto odinTCK = dspdf.Fill<unsigned int>(TH1D("odinTCK","D+ odin tck", 1300000, 290300000, 291600000), {"OdinTCK"});
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





}//end



