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
/*
"Kminus_ID", "Dplus_P", "Kplus_PE", "Kminus_X", "Dplus_DIRA_OWNPV", "Dplus_FDCHI2_OWNPV", "Kminus_PY", "Piplus_MC15TuneV1_ProbNNpi", "Dplus_PE", "Kplus_ID", "Piplus_PZ", "Dplus_PT", "Kminus_P", "Piplus_PT", "Piplus_isMuon", "Dplus_IPCHI2_OWNPV", "Kplus_IPCHI2_OWNPV", "Piplus_MC15TuneV1_ProbNNp", "Kminus_PZ", "Kplus_PT", "Kplus_Y", "Piplus_PY", "Piplus_X", "Dplus_TAU", "Kplus_M", "Kminus_PT", "Kminus_PX", "Kplus_MC15TuneV1_ProbNNk", "Kplus_PY", "Piplus_ID", "Kminus_M", "Dplus_PX", "Kminus_Y", "Piplus_Y", "Kminus_PE", "Dplus_M", "Dplus_PY", "Dplus_PZ", "Kplus_PZ", "Kplus_PX", "Kplus_X", "Piplus_PX", "Dplus_ENDVERTEX_CHI2", "Kminus_IPCHI2_OWNPV", "Kminus_MC15TuneV1_ProbNNk", "Kplus_isMuon", "Kplus_P", "Piplus_PE", "Piplus_P", "Piplus_M", "Kplus_PIDe", "Piplus_PIDe", "Piplus_IPCHI2_OWNPV", "Dplus_ID"
*/






//create rdataframe for dp data

//RDataFrame dpdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp_data_dec20/dpmagup01.root");//smaller file for tests
RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dpmagup_dec20.root","/share/lazy/D2KKpi/dpmagdown_dec20.root"});

auto cut_dp_fdchi2 = [](double x) {return x > 150 ;};
auto cut_dp_ipchi2 = [](double x) {return x < 15 ;};
auto cut_dp_dira = [](double x) {return x > 0.99 ;};
auto cut_dp_PZ = [](double x) {return x > 8000 ;};

auto cut_kkpi_P = [](double x) {return x > 2500 ;};
auto cut_kkpi_PT = [](double x) {return x > 250 ;};
auto cut_kkpi_ipchi2 = [](double x) {return x > 5 ;};
auto cut_kkpi_probNNsame = [](double x) {return x > 0.6 ;};
auto cut_kkpi_PIDe = [](double x) {return x < 0 ;};
auto cut_kkpi_isMuon = [](double x) {return !x ;};





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


				 








auto treeName = "DecayTree";


auto dpoutFileName = "/share/lazy/D2KKpi/dp_cut.root";
dp_standardized.Snapshot(treeName, dpoutFileName, {"particle_MM", "particle_TAU", "particle_PX", "particle_PY", "particle_PZ", "particle_PT", "isDp", "Polarity"});



}//end



