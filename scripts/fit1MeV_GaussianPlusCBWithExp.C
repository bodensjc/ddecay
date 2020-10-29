where the external fit parameters are the common mean value, the rms width
//  of the two, and the fraction associated with the "first" Gaussian
//  the nominal units are MeV with a 2 MeV bin width

//  par[0] = nSignal # of signal events
//  par[1] = common mean value
//  par[2] = rms width of combined "double Gaussian" part of signal
//  par[3] = sigma of Gaussian
//  par[4] = fraction in Gaussian;  
    //  the user should constrain par[4] to lie in the range (0.55 - 0.99999)
//  par[5] = intercept of exponential background at a nominal "endpoint"
   //  we want the fit value to be positive, so should constrain the fitting
   //  range where this is called;  but it must be done very carefully
   // so that the fits will converge properly
//  par[6] = co-efficient of the exponential backbground
//  par[7] = Crystal Ball "alpha" (function uses absolute value, so 
  //         probably best to constrain to be very, very slightly above 0
  //         in calling routine
//  par[8] = Crystal Ball "n";  must be greater than 1, so probably best
  // to constrain it to be very, very slightly above 1 in calling routine
      Double_t nSignal = par[0];
      Double_t mu = par[1];
      Double_t rms = par[2];
      Double_t sigma1 = par[3];
      Double_t f = par[4];
      Double_t sigma2sq = (rms*rms - f *sigma1*sigma1) / (1-f);
      Double_t sigma2 = TMath::Sqrt(sigma2sq);
      Double_t binWidth = 1.;
      Double_t CB_alpha = par[7];
      Double_t CB_n = par[8];

      Double_t arg1 = 0;
      if (sigma1 != 0) arg1 = (v[0] - mu)/sigma1;

      Double_t arg2 = 0;
      if (sigma2 != 0) arg2 = (v[0] - mu)/sigma2;

//  create a double Gaussian with widths sigma1 & sigma 2 and common mean mu
      Double_t fitval = nSignal*(binWidth*f*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(TMath::TwoPi())*sigma1) + binWidth*(1-f)*ROOT::Math::crystalball_pdf(v[0],CB_alpha,CB_n,sigma2,mu));

//  add an exponential background
      fitval = fitval + par[5]*TMath::Exp(par[6]*(v[0]-1919.));

//  we're done
      return fitval;
   }






Double_t  primaryGaussian (Double_t *v, Double_t *par) 
{

       Double_t nSignal = par[0];
      Double_t mu = par[1];
      Double_t rms = par[2];
      Double_t sigma1 = par[3];
      Double_t f = par[4];
      Double_t sigma2sq = (rms*rms - f *sigma1*sigma1) / (1-f);
      Double_t sigma2 = TMath::Sqrt(sigma2sq);
      Double_t binWidth = 1.;
      Double_t CB_alpha = par[7];
      Double_t CB_n = par[8];

      Double_t arg1 = (v[0] - mu)/sigma1;

      Double_t arg2  = (v[0] - mu)/sigma2;

//  create a double Gaussian with widths sigma1 & sigma 2 and common mean mu
      Double_t fitval = nSignal*(binWidth*f*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(TMath::TwoPi())*sigma1) + binWidth*(1-f)*ROOT::Math::crystalball_pdf(v[0],CB_alpha,CB_n,sigma2,mu));


      return fitval;
}





Double_t  backgroundCB (Double_t *v, Double_t *par) {


//  add an exponential background
      Double_t fitval =  par[5]*TMath::Exp(par[6]*(v[0]-1919.));

      return fitval;
}








