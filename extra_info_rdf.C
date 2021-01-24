{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"
using namespace std;
using namespace ROOT;


EnableImplicitMT();


//create rdataframe for dp, dsp magdown data
/*
RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dpmagup_dec20.root","/share/lazy/D2KKpi/dpmagdown_dec20.root"});
RDataFrame dspdf("Dsp2KKpi/DecayTree", {"/share/lazy/D2KKpi/dspmagup_dec20.root","/share/lazy/D2KKpi/dspmagdown_dec20.root"});
*/

//smaller test sets
RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp_data_dec20/dpmagup01.root");
RDataFrame dspdf("Dsp2KKpi/DecayTree", "/share/lazy/D2KKpi/dsp_data_dec20/dspmagdown01.root");




//get and print number of entries
/*
auto dpdf_count = dpdf.Count();
double dpdfEntries = *dpdf_count;
cout << "Raw Entries: " << dpdfEntries << endl;
*/

//get and print column names
/*
auto colNames = dpdf.GetColumnNames();
for (auto &&colName : colNames) std::cout << colName << std::endl;
*/



auto dprunhist = dpdf.Fill<unsigned int>(TH1D("dprunhist","D+ run number", 8000, 194000, 202000), {"runNumber"});



double xVals[8000];
double runCount[8000];
for (int i=1;i<8000;i++) {
	int x = dprunhist->GetBinCenter(i);
	int val = dprunhist->GetBinContent(i);
    xVals[i]=x;
    runCount[i]=val;

	if (runCount[i] > 1) {
		cout << "runNumber " << xVals[i] << " has " << runCount[i] << " candidates." << endl;
	}
}


}//end



