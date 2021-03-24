#include <TMath.h>
#include <Math/ProbFuncMathCore.h>
#include <Math/PdfFuncMathCore.h> 
//comes from share/lazy/Nov17Code/lhcb_correction/Trigger_DTF_10Feb/fit0p5MeV_GaussianPlusCBWithExp.c


   Double_t fit1MeVspectrum_Gaussian_CB_ExpBG(Double_t *v, Double_t *par)
   {

//  create a fitting function for an exponential background plus a Gaussian + CB signal
//  where the external fit parameters are the common mean value, the rms width
//  of the two, and the fraction associated with the Gaussian and CB
//  the nominal units are MeV with a 1 MeV bin width

//all of the above times 2 for both mass peaks
//using all the same parameters but with a 2 appended to denote second signal peak


//  par[0] = nSignal # of signal events
//  par[1] = common mean value
//  par[2] = rms width of combined "double Gaussian" part of signal
//  par[3] = sigma of Gaussian
//  par[4] = fraction in Gaussian;  
//  the user should constrain par[4] to lie in the range (0.55 - 0.99999)
//  par[5] = Crystal Ball "alpha" (function uses absolute value, so 
//         probably best to constrain to be very, very slightly above 0
//         in calling routine
//  par[6] = Crystal Ball "n";  must be greater than 1, so probably best
// to constrain it to be very, very slightly above 1 in calling routine


//repeat of above for params 7-13 for second signal


//  par[14] = intercept of exponential background at a nominal "endpoint"
//  we want the fit value to be positive, so should constrain the fitting
//  range where this is called;  but it must be done very carefully
// so that the fits will converge properly
//  par[15] = co-efficient of the exponential backbground




      Double_t nSignal = par[0];
      Double_t mu = par[1];
      Double_t rms = par[2];
      Double_t sigma1 = par[3];
      Double_t f = par[4];
      Double_t sigma2sq = (rms*rms - f *sigma1*sigma1) / (1-f);
      Double_t sigma2 = TMath::Sqrt(sigma2sq);
      Double_t binWidth = 1.;
      Double_t CB_alpha = par[5];
      Double_t CB_n = par[6];

      Double_t arg1 = 0;
      if (sigma1 != 0) arg1 = (v[0] - mu)/sigma1;

      Double_t arg2 = 0;
      if (sigma2 != 0) arg2 = (v[0] - mu)/sigma2;

//  create a single Gaussian with CB
      Double_t fitval = nSignal*(binWidth*f*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(TMath::TwoPi())*sigma1) + binWidth*(1-f)*ROOT::Math::crystalball_pdf(v[0],CB_alpha,CB_n,sigma2,mu));


//repeat above for second signal
      Double_t nSignal2 = par[7];
      Double_t mu2 = par[8];
      Double_t rms2 = par[9];
      Double_t sigma12 = par[10];
      Double_t f2 = par[11];
      Double_t sigma22sq = (rms2*rms2 - f2 *sigma12*sigma12) / (1-f2);
      Double_t sigma22 = TMath::Sqrt(sigma22sq);
      Double_t CB_alpha2 = par[12];
      Double_t CB_n2 = par[13];

      Double_t arg12 = 0;
      if (sigma12 != 0) arg12 = (v[0] - mu2)/sigma12;


	fitval = fitval + nSignal2*(binWidth*f2*TMath::Exp(-0.5*arg12*arg12)/(TMath::Sqrt(TMath::TwoPi())*sigma12) + binWidth*(1-f2)*ROOT::Math::crystalball_pdf(v[0],CB_alpha2,CB_n2,sigma22,mu2));



//  add an exponential background
      fitval = fitval + par[14]*TMath::Exp(par[15]*(v[0]-1790.));

//  we're done
      return fitval;
   }










//gaussian part of signal
Double_t Gaussian (Double_t *v, Double_t *par)
{
	Double_t nSignal = par[0];
      Double_t mu = par[1];
      Double_t rms = par[2];
      Double_t sigma1 = par[3];
      Double_t f = par[4];
      Double_t sigma2sq = (rms*rms - f *sigma1*sigma1) / (1-f);
      Double_t sigma2 = TMath::Sqrt(sigma2sq);
      Double_t binWidth = 1.;
/*    
	  Double_t CB_alpha = par[5];
      Double_t CB_n = par[6];
*/
      Double_t arg1 = (v[0] - mu)/sigma1;
      Double_t fitval = nSignal*(binWidth*f*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(TMath::TwoPi())*sigma1));

      return fitval;
}




//CB part of signal
Double_t CB (Double_t *v, Double_t *par)
{
      Double_t nSignal = par[0];
      Double_t mu = par[1];
      Double_t rms = par[2];
      Double_t sigma1 = par[3];
      Double_t f = par[4];
      Double_t sigma2sq = (rms*rms - f *sigma1*sigma1) / (1-f);
      Double_t sigma2 = TMath::Sqrt(sigma2sq);
      Double_t binWidth = 1.;
      Double_t CB_alpha = par[5];
      Double_t CB_n = par[6];

      Double_t fitval = nSignal*(binWidth*(1-f)*ROOT::Math::crystalball_pdf(v[0],CB_alpha,CB_n,sigma2,mu));

      return fitval;
}



//isolate the exponential background
Double_t  backgroundExp (Double_t *v, Double_t *par) 
{
      Double_t fitval =  par[0]*TMath::Exp(par[1]*(v[0]-1790.));

      return fitval;
}










//mass difference fitting
//should produce the same results as fit1MeVspectrum_Gaussian_CB_ExpBG but gives us the error of mass difference

Double_t fit1MeVdifference_Gaussian_CB_ExpBG(Double_t *v, Double_t *par) {

      Double_t nSignal = par[0];
      Double_t mu = par[1];
      Double_t rms = par[2];
      Double_t sigma1 = par[3];
      Double_t f = par[4];
      Double_t sigma2sq = (rms*rms - f *sigma1*sigma1) / (1-f);
      Double_t sigma2 = TMath::Sqrt(sigma2sq);
      Double_t binWidth = 1.;
      Double_t CB_alpha = par[5];
      Double_t CB_n = par[6];

      Double_t arg1 = 0;
      if (sigma1 != 0) arg1 = (v[0] - mu)/sigma1;

      Double_t arg2 = 0;
      if (sigma2 != 0) arg2 = (v[0] - mu)/sigma2;

//  create a single Gaussian with CB
      Double_t fitval = nSignal*(binWidth*f*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(TMath::TwoPi())*sigma1) + binWidth*(1-f)*ROOT::Math::crystalball_pdf(v[0],CB_alpha,CB_n,sigma2,mu));


//repeat above for second signal
      Double_t nSignal2 = par[7];
      Double_t massDiff = par[8];
		Double_t mu2 = mu + massDiff;
      Double_t rms2 = par[9];
      Double_t sigma12 = par[10];
      Double_t f2 = par[11];
      Double_t sigma22sq = (rms2*rms2 - f2 *sigma12*sigma12) / (1-f2);
      Double_t sigma22 = TMath::Sqrt(sigma22sq);
      Double_t CB_alpha2 = par[12];
      Double_t CB_n2 = par[13];

      Double_t arg12 = 0;
      if (sigma12 != 0) arg12 = (v[0] - mu2)/sigma12;


	fitval = fitval + nSignal2*(binWidth*f2*TMath::Exp(-0.5*arg12*arg12)/(TMath::Sqrt(TMath::TwoPi())*sigma12) + binWidth*(1-f2)*ROOT::Math::crystalball_pdf(v[0],CB_alpha2,CB_n2,sigma22,mu2));



//  add an exponential background
      fitval = fitval + par[14]*TMath::Exp(par[15]*(v[0]-1790.));

//  we're done
      return fitval;
























}





