#include <TMath.h>
#include <Math/ProbFuncMathCore.h>
#include <Math/PdfFuncMathCore.h> 


//new fitting functions for D+ Ds mass and mass difference measurements.

//with any luck, these functions will be more readable and usable then the 
// previously used "fit_spectrum.C"

//I am attempting to write these such that a few parameters can be adjusted
// in the analysis file to control the fitting function rather than write
// several variations of the same thing

//things to include:    binWidth variation
//                      single / double gaussians(common mean) at one or both peaks 
//                      same or difference CB params
//                      fit [m(D+) and m(Ds)] OR [m(D+) and m(D+ - Ds)]
//                      


Double_t customFit_Dplus_Ds(Double_t *v, Double_t *par)
{
//create a fitting function for a bimodal mass distributions usingan exponential
//  background plus a (single/double) Gaussian + (same/different) CB signal


//**************SETUP PARAMS**************
//should be FIXED parameters in fitting
//par[0] = binWidth
//par[1] = first peak gaussians (0-one, 1-two)
//par[2] = second peak gaussians (0-one, 1-two)
//par[3] = same CB params for both peak (0-FALSE, 1-TRUE)
//par[4] = fit option (0-both masses, 1-mass difference)

//**************first signal**************
//  par[5] = nSignal # of signal events
//  par[6] = common mean value
//  par[7] = rms width of combined "double Gaussian" part of signal
//  par[8] = sigma of Gaussian (modified for CB use, see: sigmaCB)
//  par[9] = fraction in Gaussian;  
//  par[10] = Crystal Ball "alpha" (function uses absolute value, so 
//         probably best to constrain to be very, very slightly above 0
//         in calling routine
//  par[11] = Crystal Ball "n";  must be greater than 1, so probably best
// to constrain it to be very, very slightly above 1 in calling routine

//**************second signal**************
//repeat of above for params 12-18

//**************exp background**************
//par[19] = intercept of exponential background at a nominal "endpoint"
//par[20] = co-efficient of the exponential background


//**************extra gaussians**************
//only need an extra fraction gaus and gaussian sigma for each
//par[21] = sigma of second first peak gaussian
//par[22] = fraction in second gaussian of first peak 
//par[23] = sigma of second second peak gaussian
//par[24] = fraction in second gaussian of second peak


      Double_t binWidth = par[0];
      Bool_t isFirstPeakDoubleGaus = par[1];
      Bool_t isSecondPeakDoubleGaus = par[2];
      Bool_t isSameCBParams = par[3];
      Bool_t isMassDiffFit = par[4];

      Double_t nSignalPeak1 = par[5];
      Double_t muPeak1 = par[6];
      Double_t rmsPeak1 = par[7];
      Double_t sigmaGaus1Peak1 = par[8];
      Double_t f1Peak1 = par[9];
      Double_t CB_alphaPeak1 = par[10];
      Double_t CB_nPeak1 = par[11];

      Double_t nSignalPeak2 = par[12];
      if (isMassDiffFit) {//change this parameter depending on if it is a mass difference fit
            Double_t massDiff = par[13];
            Double_t muPeak2 = muPeak1+massDiff;
      } else {
            Double_t muPeak2 = par[13];
      }
      Double_t rmsPeak2 = par[14];
      Double_t sigmaGaus1Peak2 = par[15];
      Double_t f1Peak2 = par[16];
      Double_t CB_alphaPeak2 = par[17];
      Double_t CB_nPeak2 = par[18];

      Double_t exp_int = par[19];
      Double_t exp_coef = par[20];

      Double_t sigmaGaus2Peak1 = par[21];
      Double_t f2Peak1 = par[22];
      Double_t sigmaGaus2Peak2 = par[23];
      Double_t f2Peak2 = par[23];


      if (isSameCBParams) {
            CB_alphaPeak2 = CB_alphaPeak1;
            CB_nPeak2 = CB_nPeak1;
      }




      if (isFirstPeakDoubleGaus) {//if there are two gaussians in first peak
            if (f1Peak1+f2Peak1 > 1) {//reassign gaus fracs if they add up to be > 1
                  f1Peak1 = f1Peak1 / (f1Peak1+f2Peak1);
                  f2Peak1 = f2Peak1 / (f1Peak1+f2Peak1);
            }

            Double_t sigmaCBPeak1sq = (rmsPeak1*rmsPeak1 - f1Peak1*sigmaGaus1Peak1*sigmaGaus1Peak1)/(1-f1Peak1-f2Peak1);
            Double_t sigmaCBPeak1 = TMath::Sqrt(sigmaCBPeak1sq);
            
            Double_t arg1 = 0;
            if (sigmaGaus1Peak1 != 0) arg1 = (v[0] - muPeak1)/sigmaGaus1Peak1;
            Double_t arg2 = 0;
            if (sigmaGaus2Peak1 != 0) arg2 = (v[0] - muPeak1)/sigmaGaus2Peak1;

            Double_t fitval = nSignalPeak1*binWidth*f1Peak1*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(TMath::TwoPi())*sigmaGaus1Peak1);//add gaus11            
            fitval = fitval + nSignalPeak1*binWidth*f2Peak1*TMath::Exp(-0.5*arg2*arg2)/(TMath::Sqrt(TMath::TwoPi())*sigmaGaus2Peak1);//add gaus12
            fitval = fitval + nSignalPeak1*binWidth*(1-f1Peak1-f2Peak1)*ROOT::Math::crystalball_pdf(v[0],CB_alphaPeak1,CB_nPeak1,sigmaCBPeak1,muPeak1);//add CB1

      } else {//if there is only one gaussian in first peak
            Double_t sigmaCBPeak1sq = (rmsPeak1*rmsPeak1 - f1Peak1*sigmaGaus1Peak1*sigmaGaus1Peak1)/(1-f1Peak1);
            Double_t sigmaCBPeak1 = TMath::Sqrt(sigmaCBPeak1sq);

            Double_t arg1 = 0;
            if (sigmaGaus1Peak1 != 0) arg1 = (v[0] - muPeak1)/sigmaGaus1Peak1;

            Double_t fitval = nSignalPeak1*binWidth*f1Peak1*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(TMath::TwoPi())*sigmaGaus1Peak1);//add gaus1
            fitval = fitval + nSignalPeak1*binWidth*(1-f1Peak1)*ROOT::Math::crystalball_pdf(v[0],CB_alphaPeak1,CB_nPeak1,sigmaCBPeak1,muPeak1);//add CB1
      }


      if (isSecondPeakDoubleGaus) {//if there are two gaussians in second peak
            if (f1Peak2+f2Peak2 > 1) {//reassign gaus fracs if they add up to be > 1
                  f1Peak2 = f1Peak2 / (f1Peak2+f2Peak2);
                  f2Peak2 = f2Peak2 / (f1Peak2+f2Peak2);
            }

            Double_t sigmaCBPeak2sq = (rmsPeak2*rmsPeak2 - f1Peak2*sigmaGaus1Peak2*sigmaGaus1Peak2)/(1-f1Peak2-f2Peak2);
            Double_t sigmaCBPeak2 = TMath::Sqrt(sigmaCBPeak2sq);
            
            Double_t arg1 = 0;
            if (sigmaGaus1Peak2 != 0) arg1 = (v[0] - muPeak2)/sigmaGaus1Peak2;
            Double_t arg2 = 0;
            if (sigmaGaus2Peak2 != 0) arg2 = (v[0] - muPeak2)/sigmaGaus2Peak2;

            fitval = fitval + nSignalPeak2*binWidth*f1Peak2*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(TMath::TwoPi())*sigmaGaus1Peak2);//add gaus21            
            fitval = fitval + nSignalPeak2*binWidth*f2Peak2*TMath::Exp(-0.5*arg2*arg2)/(TMath::Sqrt(TMath::TwoPi())*sigmaGaus2Peak2);//add gaus 22
            fitval = fitval + nSignalPeak2*binWidth*(1-f1Peak2-f2Peak2)*ROOT::Math::crystalball_pdf(v[0],CB_alphaPeak2,CB_nPeak2,sigmaCBPeak2,muPeak2);//add CB2

      } else {//if there is only one gaussian in first peak
            Double_t sigmaCBPeak2sq = (rmsPeak2*rmsPeak2 - f1Peak2*sigmaGaus1Peak2*sigmaGaus1Peak2)/(1-f1Peak2);
            Double_t sigmaCBPeak2 = TMath::Sqrt(sigmaCBPeak2sq);

            Double_t arg1 = 0;
            if (sigmaGaus1Peak2 != 0) arg1 = (v[0] - muPeak2)/sigmaGaus1Peak2;

            fitval = fitval + nSignalPeak2*binWidth*f1Peak2*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(TMath::TwoPi())*sigmaGaus1Peak2);//add gaus2
            fitval = fitval + nSignalPeak2*binWidth*(1-f1Peak2)*ROOT::Math::crystalball_pdf(v[0],CB_alphaPeak2,CB_nPeak2,sigmaCBPeak2,muPeak2);//add CB2
      }


      fitval = fitval + exp_int*TMath::Exp(exp_coef*(v[0]-1790.));//add exponential background 
      //1790 is a number just a bit before the "action" happens. not rigorous.

      return fitval;

}




//That should do it for fitting the whole spectrum.
//the below functions are used to plot the contributing functions separately
//these are meant to be use AFTER the data is fit using the above function, then
//taking those parameters and directly inputting them into these functions




Double_t Gaussian (Double_t *v, Double_t *par)
{
      //this is used for both peaks single or double gaussians

	Double_t binWidth = par[0];
      Double_t nSignal = par[1];
      Double_t mu = par[2];
      Double_t rms = par[3];
      Double_t sigma = par[4];
      Double_t f = par[5];

      Double_t arg1 = (v[0] - mu)/sigma;
      Double_t fitval = nSignal*binWidth*f*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(TMath::TwoPi())*sigma);

      return fitval;
}



Double_t CB (Double_t *v, Double_t *par)
{
      //used to draw the CB part of the fit for both peaks
      //if there are two gaussians, report "f" as "f1+f2"

      Double_t binWidth = par[0];
      Double_t nSignal = par[1];
      Double_t mu = par[2];
      Double_t rms = par[3];
      Double_t sigma = par[4];
      Double_t f = par[5];
      Double_t sigma2sq = (rms*rms - f *sigma*sigma) / (1-f);
      Double_t sigma2 = TMath::Sqrt(sigma2sq);
      Double_t CB_alpha = par[6];
      Double_t CB_n = par[7];

      Double_t fitval = nSignal*binWidth*(1-f)*ROOT::Math::crystalball_pdf(v[0],CB_alpha,CB_n,sigma2,mu);

      return fitval;
}



Double_t  backgroundExp (Double_t *v, Double_t *par) 
{
      //used to draw the exponential background
      //heuristic 1790 also lives here, change as needed

      Double_t exp_int = par[0];
      Double_t exp_coef = par[1];

      Double_t fitval =  exp_int*TMath::Exp(exp_coef*(v[0]-1790.));

      return fitval;
}



//and that's all!