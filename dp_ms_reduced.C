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
//RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dp_data_dec20/dpmagup01.root", "/share/lazy/D2KKpi/dp_data_dec20/dpmagdown01.root"});//smaller file for tests
RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dpmagup_dec20.root","/share/lazy/D2KKpi/dpmagdown_dec20.root"});

//slight redundancy with merging magup and magdown here then cutting on them later. oops



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



//cut on magnet polarity
auto cut_magup = [](short x) {return x == 1 ;};
auto cut_magdown = [](short x) {return x == -1 ;};

auto dp_magup = dp_cut.Filter(cut_magup, {"Polarity"});
auto dp_magdown = dp_cut.Filter(cut_magdown, {"Polarity"});



//cut on run number groupings
auto cut_run_up1 = [](unsigned int x) {return 192000 < x && x < 196000 ;};
auto cut_run_up2 = [](unsigned int x) {return 196000 < x && x < 200000 ;};
auto cut_run_up3 = [](unsigned int x) {return 200000 < x && x < 204000 ;};

auto cut_run_down1 = [](unsigned int x) {return 194000 < x && x < 198000 ;};
auto cut_run_down2 = [](unsigned int x) {return 198000 < x && x < 202000 ;};


auto dp_magup_group1 = dp_magup.Filter(cut_run_up1, {"runNumber"});
auto dp_magup_group2 = dp_magup.Filter(cut_run_up2, {"runNumber"});
auto dp_magup_group3 = dp_magup.Filter(cut_run_up3, {"runNumber"});
auto dp_magdown_group1 = dp_magdown.Filter(cut_run_down1, {"runNumber"});
auto dp_magdown_group2 = dp_magdown.Filter(cut_run_down2, {"runNumber"});







auto treeName = "DecayTree";

auto testOutFileName = "/share/lazy/D2KKpi/dp_reduced_test.root";
//dp_cut.Snapshot(treeName, testOutFileName, {"Dplus_DIRA_OWNPV", "Dplus_ENDVERTEX_CHI2", "Dplus_FDCHI2_OWNPV", "Dplus_ID", "Dplus_IPCHI2_OWNPV", "Dplus_M", "Dplus_P", "Dplus_PE", "Dplus_PT", "Dplus_PX", "Dplus_PY", "Dplus_PZ", "Dplus_TAU", "Kminus_ID", "Kminus_IPCHI2_OWNPV", "Kminus_M", "Kminus_MC15TuneV1_ProbNNk", "Kminus_P", "Kminus_PE", "Kminus_PT", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_X", "Kminus_Y", "Kplus_ID", "Kplus_IPCHI2_OWNPV", "Kplus_M", "Kplus_MC15TuneV1_ProbNNk", "Kplus_P", "Kplus_PE", "Kplus_PIDe", "Kplus_PT", "Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_X", "Kplus_Y", "Kplus_isMuon", "Piplus_ID", "Piplus_IPCHI2_OWNPV", "Piplus_M", "Piplus_MC15TuneV1_ProbNNp", "Piplus_MC15TuneV1_ProbNNpi", "Piplus_P", "Piplus_PE", "Piplus_PIDe", "Piplus_PT", "Piplus_PX", "Piplus_PY", "Piplus_PZ", "Piplus_X", "Piplus_Y", "Piplus_isMuon", "Polarity", "runNumber"});



//save each grouping to an ntuple in /share/lazy/D2KKpi

auto dp_up1_OutName = "/share/lazy/D2KKpi/dp_reduced_magup1.root";
dp_magup_group1.Snapshot(treeName, dp_up1_OutName, {"Dplus_DIRA_OWNPV", "Dplus_ENDVERTEX_CHI2", "Dplus_FDCHI2_OWNPV", "Dplus_ID", "Dplus_IPCHI2_OWNPV", "Dplus_M", "Dplus_P", "Dplus_PE", "Dplus_PT", "Dplus_PX", "Dplus_PY", "Dplus_PZ", "Dplus_TAU", "Kminus_ID", "Kminus_IPCHI2_OWNPV", "Kminus_M", "Kminus_MC15TuneV1_ProbNNk", "Kminus_P", "Kminus_PE", "Kminus_PT", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_X", "Kminus_Y", "Kplus_ID", "Kplus_IPCHI2_OWNPV", "Kplus_M", "Kplus_MC15TuneV1_ProbNNk", "Kplus_P", "Kplus_PE", "Kplus_PIDe", "Kplus_PT", "Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_X", "Kplus_Y", "Kplus_isMuon", "Piplus_ID", "Piplus_IPCHI2_OWNPV", "Piplus_M", "Piplus_MC15TuneV1_ProbNNp", "Piplus_MC15TuneV1_ProbNNpi", "Piplus_P", "Piplus_PE", "Piplus_PIDe", "Piplus_PT", "Piplus_PX", "Piplus_PY", "Piplus_PZ", "Piplus_X", "Piplus_Y", "Piplus_isMuon", "Polarity", "runNumber"});

auto dp_up2_OutName = "/share/lazy/D2KKpi/dp_reduced_magup2.root";
dp_magup_group2.Snapshot(treeName, dp_up2_OutName, {"Dplus_DIRA_OWNPV", "Dplus_ENDVERTEX_CHI2", "Dplus_FDCHI2_OWNPV", "Dplus_ID", "Dplus_IPCHI2_OWNPV", "Dplus_M", "Dplus_P", "Dplus_PE", "Dplus_PT", "Dplus_PX", "Dplus_PY", "Dplus_PZ", "Dplus_TAU", "Kminus_ID", "Kminus_IPCHI2_OWNPV", "Kminus_M", "Kminus_MC15TuneV1_ProbNNk", "Kminus_P", "Kminus_PE", "Kminus_PT", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_X", "Kminus_Y", "Kplus_ID", "Kplus_IPCHI2_OWNPV", "Kplus_M", "Kplus_MC15TuneV1_ProbNNk", "Kplus_P", "Kplus_PE", "Kplus_PIDe", "Kplus_PT", "Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_X", "Kplus_Y", "Kplus_isMuon", "Piplus_ID", "Piplus_IPCHI2_OWNPV", "Piplus_M", "Piplus_MC15TuneV1_ProbNNp", "Piplus_MC15TuneV1_ProbNNpi", "Piplus_P", "Piplus_PE", "Piplus_PIDe", "Piplus_PT", "Piplus_PX", "Piplus_PY", "Piplus_PZ", "Piplus_X", "Piplus_Y", "Piplus_isMuon", "Polarity", "runNumber"});

auto dp_up3_OutName = "/share/lazy/D2KKpi/dp_reduced_magup3.root";
dp_magup_group3.Snapshot(treeName, dp_up3_OutName, {"Dplus_DIRA_OWNPV", "Dplus_ENDVERTEX_CHI2", "Dplus_FDCHI2_OWNPV", "Dplus_ID", "Dplus_IPCHI2_OWNPV", "Dplus_M", "Dplus_P", "Dplus_PE", "Dplus_PT", "Dplus_PX", "Dplus_PY", "Dplus_PZ", "Dplus_TAU", "Kminus_ID", "Kminus_IPCHI2_OWNPV", "Kminus_M", "Kminus_MC15TuneV1_ProbNNk", "Kminus_P", "Kminus_PE", "Kminus_PT", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_X", "Kminus_Y", "Kplus_ID", "Kplus_IPCHI2_OWNPV", "Kplus_M", "Kplus_MC15TuneV1_ProbNNk", "Kplus_P", "Kplus_PE", "Kplus_PIDe", "Kplus_PT", "Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_X", "Kplus_Y", "Kplus_isMuon", "Piplus_ID", "Piplus_IPCHI2_OWNPV", "Piplus_M", "Piplus_MC15TuneV1_ProbNNp", "Piplus_MC15TuneV1_ProbNNpi", "Piplus_P", "Piplus_PE", "Piplus_PIDe", "Piplus_PT", "Piplus_PX", "Piplus_PY", "Piplus_PZ", "Piplus_X", "Piplus_Y", "Piplus_isMuon", "Polarity", "runNumber"});

auto dp_down1_OutName = "/share/lazy/D2KKpi/dp_reduced_magdown1.root";
dp_magdown_group1.Snapshot(treeName, dp_down1_OutName, {"Dplus_DIRA_OWNPV", "Dplus_ENDVERTEX_CHI2", "Dplus_FDCHI2_OWNPV", "Dplus_ID", "Dplus_IPCHI2_OWNPV", "Dplus_M", "Dplus_P", "Dplus_PE", "Dplus_PT", "Dplus_PX", "Dplus_PY", "Dplus_PZ", "Dplus_TAU", "Kminus_ID", "Kminus_IPCHI2_OWNPV", "Kminus_M", "Kminus_MC15TuneV1_ProbNNk", "Kminus_P", "Kminus_PE", "Kminus_PT", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_X", "Kminus_Y", "Kplus_ID", "Kplus_IPCHI2_OWNPV", "Kplus_M", "Kplus_MC15TuneV1_ProbNNk", "Kplus_P", "Kplus_PE", "Kplus_PIDe", "Kplus_PT", "Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_X", "Kplus_Y", "Kplus_isMuon", "Piplus_ID", "Piplus_IPCHI2_OWNPV", "Piplus_M", "Piplus_MC15TuneV1_ProbNNp", "Piplus_MC15TuneV1_ProbNNpi", "Piplus_P", "Piplus_PE", "Piplus_PIDe", "Piplus_PT", "Piplus_PX", "Piplus_PY", "Piplus_PZ", "Piplus_X", "Piplus_Y", "Piplus_isMuon", "Polarity", "runNumber"});

auto dp_down2_OutName = "/share/lazy/D2KKpi/dp_reduced_magdown2.root";
dp_magdown_group2.Snapshot(treeName, dp_down2_OutName, {"Dplus_DIRA_OWNPV", "Dplus_ENDVERTEX_CHI2", "Dplus_FDCHI2_OWNPV", "Dplus_ID", "Dplus_IPCHI2_OWNPV", "Dplus_M", "Dplus_P", "Dplus_PE", "Dplus_PT", "Dplus_PX", "Dplus_PY", "Dplus_PZ", "Dplus_TAU", "Kminus_ID", "Kminus_IPCHI2_OWNPV", "Kminus_M", "Kminus_MC15TuneV1_ProbNNk", "Kminus_P", "Kminus_PE", "Kminus_PT", "Kminus_PX", "Kminus_PY", "Kminus_PZ", "Kminus_X", "Kminus_Y", "Kplus_ID", "Kplus_IPCHI2_OWNPV", "Kplus_M", "Kplus_MC15TuneV1_ProbNNk", "Kplus_P", "Kplus_PE", "Kplus_PIDe", "Kplus_PT", "Kplus_PX", "Kplus_PY", "Kplus_PZ", "Kplus_X", "Kplus_Y", "Kplus_isMuon", "Piplus_ID", "Piplus_IPCHI2_OWNPV", "Piplus_M", "Piplus_MC15TuneV1_ProbNNp", "Piplus_MC15TuneV1_ProbNNpi", "Piplus_P", "Piplus_PE", "Piplus_PIDe", "Piplus_PT", "Piplus_PX", "Piplus_PY", "Piplus_PZ", "Piplus_X", "Piplus_Y", "Piplus_isMuon", "Polarity", "runNumber"});



}//end



