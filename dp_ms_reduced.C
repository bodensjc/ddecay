{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();



//this file is for making the reduced d+ ntuples
//split by polarity and run 
//used for the momentum scaling steps 1 and 2



//These are all of the variables that appear in the Step1 and Step2 Code:
//(I added polarity and runNumber)
/*
"Dplus_DIRA_OWNPV", "Dplus_ENDVERTEX_CHI2", "Dplus_FDCHI2_OWNPV", "Dplus_ID", "Dplus_IPCHI2_OWNPV", "Dplus_M", "Dplus_P", "Dplus_PE", "Dplus_PT", "Dplus_PX", "Dplus_PY", "Dplus_PZ", "Dplus_TAU", "Kminus_ID", "Kminus_IPCHI2_OWNPV", "Kminus_M", "Kminus_MC15TuneV1_ProbNNk", "Kminus_P", "Kminus_PE", "Kminus_PT", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_X", "Kminus_Y", "Kplus_ID", "Kplus_IPCHI2_OWNPV", "Kplus_M", "Kplus_MC15TuneV1_ProbNNk", "Kplus_P", "Kplus_PE", "Kplus_PIDe", "Kplus_PT", "Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_X", "Kplus_Y", "Kplus_isMuon", "Piplus_ID", "Piplus_IPCHI2_OWNPV", "Piplus_M", "Piplus_MC15TuneV1_ProbNNp", "Piplus_MC15TuneV1_ProbNNpi", "Piplus_P", "Piplus_PE", "Piplus_PIDe", "Piplus_PT", "Piplus_PX", "Piplus_PY", "Piplus_PZ", "Piplus_X", "Piplus_Y", "Piplus_isMuon", "Polarity", "runNumber"
*/





//create rdataframe for dp data
RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp_data_dec20/dpmagup01.root");//smaller file for tests
//RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dpmagup_dec20.root","/share/lazy/D2KKpi/dpmagdown_dec20.root"});



//main set of cuts, slightly relaxed from what is done in Step1
auto cut_dp_fdchi2 = [](double x) {return x > 150 ;};
auto cut_dp_ipchi2 = [](double x) {return x < 15 ;};
auto cut_dp_dira = [](double x) {return x > 0.99 ;};
auto cut_dp_PZ = [](double x) {return x > 8000 ;};
auto cut_kkpi_P = [](double x) {return x > 2500 ;};
auto cut_kkpi_PT = [](double x) {return x > 250 ;};
auto cut_kkpi_ipchi2 = [](double x) {return x > 5 ;};
auto cut_kkpi_probNNsame = [](double x) {return x > 0.6 ;};
auto cut_kkpi_PIDe = [](double x) {return x < 0 ;};
auto cut_kkpi_isMuon = [](bool x) {return !x ;};


auto dp_cut  =  dpdf.Filter(cut_dp_fdchi2, {"Dplus_FDCHI2_OWNPV"})
					.Filter(cut_dp_ipchi2, {"Dplus_IPCHI2_OWNPV"})
					.Filter(cut_dp_dira, {"Dplus_DIRA_OWNPV"})
					.Filter(cut_kkpi_P, {"Kminus_P"})
					.Filter(cut_kkpi_P, {"Kplus_P"})
					.Filter(cut_kkpi_P, {"Piplus_P"})
					.Filter(cut_kkpi_PT, {"Kminus_PT"})
					.Filter(cut_kkpi_PT, {"Kplus_PT"})
					.Filter(cut_kkpi_PT, {"Piplus_PT"})
					.Filter(cut_kkpi_ipchi2, {"Kminus_IPCHI2_OWNPV"})
					.Filter(cut_kkpi_ipchi2, {"Kplus_IPCHI2_OWNPV"})
					.Filter(cut_kkpi_ipchi2, {"Piplus_IPCHI2_OWNPV"})
					.Filter(cut_kkpi_probNNsame, {"Kminus_MC15TuneV1_ProbNNk"})
					.Filter(cut_kkpi_probNNsame, {"Kplus_MC15TuneV1_ProbNNk"})
					.Filter(cut_kkpi_probNNsame, {"Piplus_MC15TuneV1_ProbNNpi"})
					.Filter(cut_kkpi_PIDe, {"Kplus_PIDe"})
					.Filter(cut_kkpi_PIDe, {"Piplus_PIDe"})
					.Filter(cut_kkpi_isMuon, {"Kplus_isMuon"})
					.Filter(cut_kkpi_isMuon, {"Piplus_isMuon"});



auto cut_magup = [](double x) {return x == 1 ;};
auto cut_magdown = [](double x) {return x == -1 ;};

auto dp_magup = dp_cut.Filter(cut_magup, {"Polarity"});
auto dp_magdown = dp_cut.Filter(cut_magdown, {"Polarity"});












auto treeName = "DecayTree";
auto testOutFileName = "/share/lazy/D2KKpi/dp_reduced_test.root";

dp_cut.Snapshot(treeName, testOutFileName, {"Dplus_DIRA_OWNPV", "Dplus_ENDVERTEX_CHI2", "Dplus_FDCHI2_OWNPV", "Dplus_ID", "Dplus_IPCHI2_OWNPV", "Dplus_M", "Dplus_P", "Dplus_PE", "Dplus_PT", "Dplus_PX", "Dplus_PY", "Dplus_PZ", "Dplus_TAU", "Kminus_ID", "Kminus_IPCHI2_OWNPV", "Kminus_M", "Kminus_MC15TuneV1_ProbNNk", "Kminus_P", "Kminus_PE", "Kminus_PT", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_X", "Kminus_Y", "Kplus_ID", "Kplus_IPCHI2_OWNPV", "Kplus_M", "Kplus_MC15TuneV1_ProbNNk", "Kplus_P", "Kplus_PE", "Kplus_PIDe", "Kplus_PT", "Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_X", "Kplus_Y", "Kplus_isMuon", "Piplus_ID", "Piplus_IPCHI2_OWNPV", "Piplus_M", "Piplus_MC15TuneV1_ProbNNp", "Piplus_MC15TuneV1_ProbNNpi", "Piplus_P", "Piplus_PE", "Piplus_PIDe", "Piplus_PT", "Piplus_PX", "Piplus_PY", "Piplus_PZ", "Piplus_X", "Piplus_Y", "Piplus_isMuon", "Polarity", "runNumber"});



}//end



