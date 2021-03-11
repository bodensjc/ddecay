{//begin
#include <TMath.h>
#include <math.h>
#include "scripts/fit1MeV_GaussianPlusCBWithExp_redo.C"

using namespace std;
using namespace ROOT;

EnableImplicitMT();



//need to make ntuples for the cut data
//one with D+ in overlap, one with Ds in overlap
//per the image "overlap_difference", use 1896 - 1944 as edges for overlap
//	ideally, could repeat this process at each MeV, i.e. using D+ up until 1896, 1897, 1898...


//this file creates snapshots of the cut d/ds data that can then be combined with hadd
//into one root file with general column labels and a variabel indicating if the observation
//originated from the d or ds data



//create rdataframe for dp, dsp magdown data

RDataFrame dpdf("D2KKpi/DecayTree", {"/share/lazy/D2KKpi/dpmagup_dec20.root","/share/lazy/D2KKpi/dpmagdown_dec20.root"});
RDataFrame dspdf("Dsp2KKpi/DecayTree", {"/share/lazy/D2KKpi/dspmagup_dec20.root","/share/lazy/D2KKpi/dspmagdown_dec20.root"});





const double phi_pm = 10;//12 for regular cut
const double phiupperbound = (1019.455+phi_pm)*(1019.455+phi_pm)/1000000; 
const double philowerbound = (1019.455-phi_pm)*(1019.455-phi_pm)/1000000; 
const int cc = 299792458;//speed of light in m/s



auto inv_m_func = [](double px1, double py1, double pz1, double pe1, double px2, double py2, double pz2, double pe2) {return TLorentzVector(TLorentzVector(px1, py1, pz1, pe1)+TLorentzVector(px2, py2, pz2, pe2)).Mag2()/1000000 ;};
auto prob_func = [](double prob1, double prob2) {return TMath::Log(prob1) - TMath::Log(prob2) ;};
auto probNNx_func = [](double prob1, double prob2, double prob3) {return prob1*prob2*prob3 ;};

auto rename_func = [](double varb) {return varb ;};//used to make columns with same name accross both dfs
auto isdp_func = [](double varb) {return 1;}; //this and below used to differentiate between dp/dsp
auto isdsp_func = [](double varb) {return 0;}; //1 meaning is dp, 0 meaning is dsp


auto cut_ipchi2 = [](double x) {return x < 4 ;};//5 for regular cut
auto cut_fdchi2 = [](double x) {return x > 225 ;};//175 for regular cut
auto cut_endvertexchi2 = [](double x) {return x < 9 ;};
auto cut_phi = [&phiupperbound, &philowerbound](double x) {return x > philowerbound && x < phiupperbound ;};
auto cut_prob_5 = [] (double x) {return x>5 ;};
auto cut_prob_0 = [] (double x) {return x>0 ;};
auto cut_probnnx = [] (double x) {return x >= 0.70 ;};
auto cut_pK_ambiguity = [] (double x) {return x> 10000 ;}; //10,000 MeV = 10GeV
auto cut_dira = [] (double x) {return x>0.99999 ;};




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




auto dp_standardized = dp_cut.Define("particle_MM", rename_func, {"Dplus_MM"})
							 .Define("particle_TAU", rename_func, {"Dplus_TAU"})
							 .Define("particle_PX", rename_func, {"Dplus_PX"})
							 .Define("particle_PY", rename_func, {"Dplus_PY"})
							 .Define("particle_PZ", rename_func, {"Dplus_PZ"})
							 .Define("particle_PT", rename_func, {"Dplus_PT"})
							 .Define("isDp", isdp_func, {"Dplus_MM"});


auto dsp_standardized = dsp_cut.Define("particle_MM", rename_func, {"Dsplus_MM"})
							 .Define("particle_TAU", rename_func, {"Dsplus_TAU"})
							 .Define("particle_PX", rename_func, {"Dsplus_PX"})
							 .Define("particle_PY", rename_func, {"Dsplus_PY"})
							 .Define("particle_PZ", rename_func, {"Dsplus_PZ"})
							 .Define("particle_PT", rename_func, {"Dsplus_PT"})
							 .Define("isDp", isdsp_func, {"Dsplus_MM"});




auto treeName = "DecayTree";

auto dpoutFileName = "/share/lazy/D2KKpi/dp_cut.root";
dp_standardized.Snapshot(treeName, dpoutFileName, {"particle_MM", "particle_TAU", "particle_PX", "particle_PY", "particle_PZ", "particle_PT", "isDp", "Polarity"});

auto dspoutFileName = "/share/lazy/D2KKpi/dsp_cut.root";
dsp_standardized.Snapshot(treeName, dspoutFileName, {"particle_MM", "particle_TAU", "particle_PX", "particle_PY", "particle_PZ", "particle_PT", "isDp", "Polarity"});






}//end



