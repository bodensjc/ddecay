//root macro to make plot comparing D+ - Ds+ mass difference measurements
//data taken from pdg 4/12/2021

//to use, load up root then:
// root [0]   .L dp_mcomp.C
// root [1]   masscomp()  //or other



void masscomp() {


//gStyle->SetPadTickX(0);
//gStyle->SetPadTickY(0);


auto dpcan = new TCanvas("dpcan","dpcan",800,600);
dpcan->SetLeftMargin(0.15);
dpcan->DrawFrame(1868, 0, 1871.5, 6);
 
char *TECN[5] = { "BABR 2002", "CDF2 2003", "LHCB 2013", "#color[4]{LHCB 2021}", "PDG Avg"};
auto labels = new TH1F("labels", "m(D^{s}) - m(D_{+}) Measurements", 5, 0.5, 5.5);
for (int i=1;i<=5;i++) labels->GetXaxis()->SetBinLabel(i,TECN[i-1]);

labels->SetStats(0);
labels->SetMinimum(98);
labels->SetMaximum(100);
labels->GetYaxis()->SetTitle("Mass Difference [MeV/c^{2}]");
labels->GetYaxis()->SetTitleOffset(1.3);
labels->GetYaxis()->CenterTitle(1);
labels->Draw("hbars");

double statzero[4] = {0,0,0,0};
	double statmass[4] = {98.4, 99.41, 98.68, 98.69};  //CLEO, BABR, LHCB, AVG
	double staty[4] = {1,2,3,5};
	double stat[4] = {0.1, 0.38, 0.03, 0.05}; 
double syszero[2] = {0,0};
	double sysmass[3] = {98.4, 99.41, 98.68};
	double sysy[3] = {1,2,3};  //{"BABR", "CDF2", "LHCB"};
	double sys[3]  = {0.3+0.1, 0.21+0.38, 0.04+0.03};
double uczero[1] = {0};
	double ucmass[1] = {98.89};
	double ucy[1] = {4};
	double ucstat[1] = {0.005};

auto statdp = new TGraphErrors(4, statmass, staty, stat, statzero);
statdp->SetMarkerStyle(20);
statdp->Draw("P");
auto sysdp = new TGraphErrors(2, sysmass, sysy, sys, syszero);
sysdp->Draw("[]");
auto UCgraph = new TGraphErrors(1, ucmass, ucy, ucstat, uczero);
UCgraph->SetMarkerStyle(20);
UCgraph->SetMarkerColor(kBlue);
UCgraph->Draw("P");



float pdgMin = 98.64;
float pdgMax = 98.74;
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
lt->DrawLatexNDC(0.44, 0.811, "98.69 #pm 0.05 MeV");//PDG
lt->DrawLatexNDC(0.50, 0.651, "#color[4]{98.89 #pm 0.005 #pm x.xxx MeV}");//UC
lt->DrawLatexNDC(0.44, 0.491, "98.68 #pm 0.03 #pm 0.04 MeV");//LHCB
lt->DrawLatexNDC(0.605, 0.36, "99.41 #pm 0.38 #pm 0.21 MeV");//CDF2
lt->DrawLatexNDC(0.24, 0.20, "98.4 #pm 0.1 #pm 0.3 MeV");//BABR



dpcan->SaveAs("finalImages/dp_mass_comparison.png");
}
