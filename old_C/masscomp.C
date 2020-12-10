//root macro to make plot comparing D+ and Ds+ mass measurements
//to use, load up root then:
// root [0]   .L dp_mcomp.C
// root [1]   masscomp()  //or other



void dpmasscomp() {


//gStyle->SetPadTickX(0);
//gStyle->SetPadTickY(0);


auto dpcan = new TCanvas("dpcan","dpcan",800,600);
dpcan->SetLeftMargin(0.15);
dpcan->DrawFrame(1868, 0, 1871.5, 6);
 
char *TECN[5] = {"RVUE 1981", "ACCMOR 1990", "KEDR 2010", "#color[4]{UC 2020}", "PDG Avg"};
auto labels = new TH1F("labels", "D^{+} Mass Measurements", 5, 0.5, 5.5);
for (int i=1;i<=5;i++) labels->GetXaxis()->SetBinLabel(i,TECN[i-1]);

labels->SetStats(0);
labels->SetMinimum(1868);
labels->SetMaximum(1871.5);
labels->GetYaxis()->SetTitle("D^{+} mass [MeV/c^{2}]");
labels->GetYaxis()->SetTitleOffset(1.3);
labels->GetYaxis()->CenterTitle(1);
labels->Draw("hbars");

double statzero[4] = {0,0,0,0};
	double statmass[4] = {1869.4, 1870, 1869.53, 1869.5};  //RVUE, ACCMOR, KEDR, PDG
	double staty[4] = {1,2,3,5};
	double stat[4] = {0.6, 0.5, 0.49, 0.4}; 
double syszero[2] = {0,0};
	double sysmass[2] = {1870, 1869.53};
	double sysy[2] = {2,3};  //{"ACCMOR", "KEDR"};
	double sys[2]  = {1.0, 0.2};
double uczero[1] = {0};
	double ucmass[1] = {1869.80};
	double ucy[1] = {4};
	double ucstat[1] = {0.02};

auto statdp = new TGraphErrors(4, statmass, staty, stat, statzero);
statdp->SetMarkerStyle(20);
statdp->Draw("P");
auto sysdp = new TGraphErrors(2, sysmass, sysy, sys, syszero);
sysdp->Draw("[]");
auto UCgraph = new TGraphErrors(1, ucmass, ucy, ucstat, uczero);
UCgraph->SetMarkerStyle(20);
UCgraph->SetMarkerColor(kBlue);
UCgraph->Draw("P");



float pdgMin = 1869.1;
float pdgMax = 1869.9;
auto minLine = new TLine(pdgMin, 0.6, pdgMin, 5.4);
minLine->SetLineColor(kRed);
minLine->SetLineWidth(3);
minLine->Draw();
auto maxLine = new TLine(pdgMax, 0.6, pdgMax, 5.4);
maxLine->SetLineColor(kRed);
maxLine->SetLineWidth(3);
maxLine->Draw();


auto lt = new TLatex();
lt->SetTextSize(0.025);
lt->DrawLatexNDC(0.42, 0.84, "1869.5 #pm 0.4");//PDG
lt->DrawLatexNDC(0.41, 0.68, "#color[4]{1869.80 #pm 0.02}");//UC
lt->DrawLatexNDC(0.395, 0.52, "1869.53 #pm 0.49 #pm 0.2");//KEDR
lt->DrawLatexNDC(0.58, 0.36, "1870 #pm 0.5 #pm 1.0");//ACCMOR
lt->DrawLatexNDC(0.40, 0.20, "1869.4 #pm 0.6");//RVUE


dpcan->SaveAs("image/dp_mass_comparison.png");
}









void dspmasscomp() {


//gStyle->SetPadTickX(0);
//gStyle->SetPadTickY(0);


auto dspcan = new TCanvas("dspcan","dspcan",800,600);
dspcan->SetLeftMargin(0.15);
dspcan->DrawFrame(1964, 0, 1976.5, 7);
 
char *TECN[6] = {"CLEO 1983", "MARK-III 1987", "ARGUS 1988", "ACCMOR 1990", "#color[4]{UC 2020}", "PDG Avg"};
auto labels = new TH1F("labels", "D^{+}_{s} Mass Measurements", 6, 0.5, 6.5);
for (int i=1;i<=6;i++) labels->GetXaxis()->SetBinLabel(i,TECN[i-1]);

labels->SetStats(0);
labels->SetMinimum(1964);
labels->SetMaximum(1976.5);
labels->GetYaxis()->SetTitle("D^{+}_{s} mass [MeV/c^{2}]");
labels->GetYaxis()->SetTitleOffset(1.3);
labels->GetYaxis()->CenterTitle(1);
labels->Draw("hbars");

double statzero[5] = {0,0,0,0,0};
	double statmass[5] = {1970, 1972.4, 1969.3, 1967.0, 1969.0};  //CLEO,  MK3, ARGUS, ACCMOR, PDG
	double staty[5] = {1,2,3,4,6};
	double stat[5] = {5, 3.7, 1.4, 1.0, 1.4}; 
double syszero[4] = {0,0,0,0};
	double sysmass[4] = {1970, 1972.4, 1969.3, 1967.0};
	double sysy[4] = {1,2,3,4};  //CLEO, MK3, ARGUS, ACCMOR
	double sys[4]  = {5, 3.7, 1.4, 1.0};
double uczero[1] = {0};
	double ucmass[1] = {1968.77};
	double ucy[1] = {5};
	double ucstat[1] = {0.08};

auto statdp = new TGraphErrors(5, statmass, staty, stat, statzero);
statdp->SetMarkerStyle(20);
statdp->Draw("P");
auto sysdp = new TGraphErrors(4, sysmass, sysy, sys, syszero);
sysdp->Draw("[]");
auto UCgraph = new TGraphErrors(1, ucmass, ucy, ucstat, uczero);
UCgraph->SetMarkerStyle(20);
UCgraph->SetMarkerColor(kBlue);
UCgraph->Draw("P");



float pdgMin = 1967.6;
float pdgMax = 1970.4;
auto minLine = new TLine(pdgMin, 0.6, pdgMin, 6.4);
minLine->SetLineColor(kRed);
minLine->SetLineWidth(3);
minLine->Draw();
auto maxLine = new TLine(pdgMax, 0.6, pdgMax, 6.4);
maxLine->SetLineColor(kRed);
maxLine->SetLineWidth(3);
maxLine->Draw();


auto lt = new TLatex();
lt->SetTextSize(0.025);
lt->DrawLatexNDC(0.395, 0.85, "1969.0 #pm 1.4");//PDG
lt->DrawLatexNDC(0.38, 0.72, "#color[4]{1968.77 #pm 0.08}");//UC
lt->DrawLatexNDC(0.22, 0.58, "1967.0 #pm 1.0 #pm 1.0");//ACCMOR
lt->DrawLatexNDC(0.385, 0.45, "1969.3 #pm 1.4 #pm 1.4");//ARGUS
lt->DrawLatexNDC(0.575, 0.316, "1972.4 #pm 3.7 #pm 3.7");//MK3
lt->DrawLatexNDC(0.415, 0.184, "1970 #pm 5 #pm 5");//CLEO


dspcan->SaveAs("image/dsp_mass_comparison.png");
}




void lines() {
  auto c1 = new TCanvas("c1");
  auto h = new TH1F("h","test",100,-4,4);
  h->FillRandom("gaus",10000);
  h->Draw();
  float ymax = h->GetMaximum();
  auto line = new TLine(-3,ymax,3,ymax);
  line->SetLineColor(kRed);
  line->Draw();
}


