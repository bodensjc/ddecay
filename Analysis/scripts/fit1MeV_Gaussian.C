Double_t fit1MeV_Gaussian(Double_t *v, Double_t *par) {

	Double_t &x = v[0];
	Double_t &par0 = par[0];
	Double_t &mean = par[1];
	Double_t &width = par[2];
	Double_t &lin_b = par[3];
	Double_t &lin_m = par[4];

	Double_t arg = width  == 0 ? 0 : (x - mean)/width;

	Double_t fitval = par0*TMath::Exp(-0.5*arg*arg);

	fitval = (fitval*1.00)/(TMath::Sqrt(TMath::TwoPi())*width);

	fitval = fitval + lin_b + x*lin_m;

	return fitval;
}
