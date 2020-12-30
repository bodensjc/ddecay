{//begin
#include <TMath.h>
#include <math.h>

using namespace std;
using namespace ROOT;

EnableImplicitMT();


//put rdataframe file here, can use multiple in second arg as {,,,}

//RDataFrame rdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dpmagup_dec20.root");//dpmagup dec_20
//RDataFrame rdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp2kkpi_magup.root");//dpmagup old_20

RDataFrame rdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dpmagdown_dec20.root");//dpmagdown dec_20
//RDataFrame rdf("D2KKpi/DecayTree", "/share/lazy/D2KKpi/dp2kkpi_magdown.root");//dpmagdown old_20



//get and print number of entries

auto rdf_count = rdf.Count();
double rdfEntries = *rdf_count;
cout << "ntuple Raw Entries: " << rdfEntries << endl;



//get and print column names
/*
auto colNames = rdf.GetColumnNames();
for (auto &&colName : colNames) std::cout << colName << std::endl;
*/



























//end
}
