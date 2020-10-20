//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 15 12:43:29 2020 by ROOT version 6.18/00
// from TTree DecayTree/DecayTree
// found on file: /share/lazy/D2KKpi/dsp2kkpi.root
//////////////////////////////////////////////////////////

#ifndef dsp_background_h
#define dsp_background_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class dsp_background : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> Dsplus_ENDVERTEX_X = {fReader, "Dsplus_ENDVERTEX_X"};
   TTreeReaderValue<Double_t> Dsplus_ENDVERTEX_Y = {fReader, "Dsplus_ENDVERTEX_Y"};
   TTreeReaderValue<Double_t> Dsplus_ENDVERTEX_Z = {fReader, "Dsplus_ENDVERTEX_Z"};
   TTreeReaderValue<Double_t> Dsplus_ENDVERTEX_XERR = {fReader, "Dsplus_ENDVERTEX_XERR"};
   TTreeReaderValue<Double_t> Dsplus_ENDVERTEX_YERR = {fReader, "Dsplus_ENDVERTEX_YERR"};
   TTreeReaderValue<Double_t> Dsplus_ENDVERTEX_ZERR = {fReader, "Dsplus_ENDVERTEX_ZERR"};
   TTreeReaderValue<Double_t> Dsplus_ENDVERTEX_CHI2 = {fReader, "Dsplus_ENDVERTEX_CHI2"};
   TTreeReaderValue<Int_t> Dsplus_ENDVERTEX_NDOF = {fReader, "Dsplus_ENDVERTEX_NDOF"};
   TTreeReaderValue<Double_t> Dsplus_OWNPV_X = {fReader, "Dsplus_OWNPV_X"};
   TTreeReaderValue<Double_t> Dsplus_OWNPV_Y = {fReader, "Dsplus_OWNPV_Y"};
   TTreeReaderValue<Double_t> Dsplus_OWNPV_Z = {fReader, "Dsplus_OWNPV_Z"};
   TTreeReaderValue<Double_t> Dsplus_OWNPV_XERR = {fReader, "Dsplus_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Dsplus_OWNPV_YERR = {fReader, "Dsplus_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Dsplus_OWNPV_ZERR = {fReader, "Dsplus_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Dsplus_OWNPV_CHI2 = {fReader, "Dsplus_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Dsplus_OWNPV_NDOF = {fReader, "Dsplus_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Dsplus_IP_OWNPV = {fReader, "Dsplus_IP_OWNPV"};
   TTreeReaderValue<Double_t> Dsplus_IPCHI2_OWNPV = {fReader, "Dsplus_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Dsplus_FD_OWNPV = {fReader, "Dsplus_FD_OWNPV"};
   TTreeReaderValue<Double_t> Dsplus_FDCHI2_OWNPV = {fReader, "Dsplus_FDCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Dsplus_DIRA_OWNPV = {fReader, "Dsplus_DIRA_OWNPV"};
   TTreeReaderValue<Double_t> Dsplus_P = {fReader, "Dsplus_P"};
   TTreeReaderValue<Double_t> Dsplus_PT = {fReader, "Dsplus_PT"};
   TTreeReaderValue<Double_t> Dsplus_PE = {fReader, "Dsplus_PE"};
   TTreeReaderValue<Double_t> Dsplus_PX = {fReader, "Dsplus_PX"};
   TTreeReaderValue<Double_t> Dsplus_PY = {fReader, "Dsplus_PY"};
   TTreeReaderValue<Double_t> Dsplus_PZ = {fReader, "Dsplus_PZ"};
   TTreeReaderValue<Double_t> Dsplus_MM = {fReader, "Dsplus_MM"};
   TTreeReaderValue<Double_t> Dsplus_MMERR = {fReader, "Dsplus_MMERR"};
   TTreeReaderValue<Double_t> Dsplus_M = {fReader, "Dsplus_M"};
   TTreeReaderValue<Int_t> Dsplus_ID = {fReader, "Dsplus_ID"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV2_ProbNNe = {fReader, "Kminus_MC12TuneV2_ProbNNe"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV2_ProbNNmu = {fReader, "Kminus_MC12TuneV2_ProbNNmu"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV2_ProbNNpi = {fReader, "Kminus_MC12TuneV2_ProbNNpi"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV2_ProbNNk = {fReader, "Kminus_MC12TuneV2_ProbNNk"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV2_ProbNNp = {fReader, "Kminus_MC12TuneV2_ProbNNp"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV2_ProbNNghost = {fReader, "Kminus_MC12TuneV2_ProbNNghost"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV3_ProbNNe = {fReader, "Kminus_MC12TuneV3_ProbNNe"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV3_ProbNNmu = {fReader, "Kminus_MC12TuneV3_ProbNNmu"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV3_ProbNNpi = {fReader, "Kminus_MC12TuneV3_ProbNNpi"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV3_ProbNNk = {fReader, "Kminus_MC12TuneV3_ProbNNk"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV3_ProbNNp = {fReader, "Kminus_MC12TuneV3_ProbNNp"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV3_ProbNNghost = {fReader, "Kminus_MC12TuneV3_ProbNNghost"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV4_ProbNNe = {fReader, "Kminus_MC12TuneV4_ProbNNe"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV4_ProbNNmu = {fReader, "Kminus_MC12TuneV4_ProbNNmu"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV4_ProbNNpi = {fReader, "Kminus_MC12TuneV4_ProbNNpi"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV4_ProbNNk = {fReader, "Kminus_MC12TuneV4_ProbNNk"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV4_ProbNNp = {fReader, "Kminus_MC12TuneV4_ProbNNp"};
   TTreeReaderValue<Double_t> Kminus_MC12TuneV4_ProbNNghost = {fReader, "Kminus_MC12TuneV4_ProbNNghost"};
   TTreeReaderValue<Double_t> Kminus_MC15TuneV1_ProbNNe = {fReader, "Kminus_MC15TuneV1_ProbNNe"};
   TTreeReaderValue<Double_t> Kminus_MC15TuneV1_ProbNNmu = {fReader, "Kminus_MC15TuneV1_ProbNNmu"};
   TTreeReaderValue<Double_t> Kminus_MC15TuneV1_ProbNNpi = {fReader, "Kminus_MC15TuneV1_ProbNNpi"};
   TTreeReaderValue<Double_t> Kminus_MC15TuneV1_ProbNNk = {fReader, "Kminus_MC15TuneV1_ProbNNk"};
   TTreeReaderValue<Double_t> Kminus_MC15TuneV1_ProbNNp = {fReader, "Kminus_MC15TuneV1_ProbNNp"};
   TTreeReaderValue<Double_t> Kminus_MC15TuneV1_ProbNNghost = {fReader, "Kminus_MC15TuneV1_ProbNNghost"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_X = {fReader, "Kminus_OWNPV_X"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_Y = {fReader, "Kminus_OWNPV_Y"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_Z = {fReader, "Kminus_OWNPV_Z"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_XERR = {fReader, "Kminus_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_YERR = {fReader, "Kminus_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_ZERR = {fReader, "Kminus_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_CHI2 = {fReader, "Kminus_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Kminus_OWNPV_NDOF = {fReader, "Kminus_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Kminus_IP_OWNPV = {fReader, "Kminus_IP_OWNPV"};
   TTreeReaderValue<Double_t> Kminus_IPCHI2_OWNPV = {fReader, "Kminus_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_X = {fReader, "Kminus_ORIVX_X"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_Y = {fReader, "Kminus_ORIVX_Y"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_Z = {fReader, "Kminus_ORIVX_Z"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_XERR = {fReader, "Kminus_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_YERR = {fReader, "Kminus_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_ZERR = {fReader, "Kminus_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_CHI2 = {fReader, "Kminus_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Kminus_ORIVX_NDOF = {fReader, "Kminus_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Kminus_P = {fReader, "Kminus_P"};
   TTreeReaderValue<Double_t> Kminus_PT = {fReader, "Kminus_PT"};
   TTreeReaderValue<Double_t> Kminus_PE = {fReader, "Kminus_PE"};
   TTreeReaderValue<Double_t> Kminus_PX = {fReader, "Kminus_PX"};
   TTreeReaderValue<Double_t> Kminus_PY = {fReader, "Kminus_PY"};
   TTreeReaderValue<Double_t> Kminus_PZ = {fReader, "Kminus_PZ"};
   TTreeReaderValue<Double_t> Kminus_M = {fReader, "Kminus_M"};
   TTreeReaderValue<Int_t> Kminus_ID = {fReader, "Kminus_ID"};
   TTreeReaderValue<Double_t> Kminus_PIDe = {fReader, "Kminus_PIDe"};
   TTreeReaderValue<Double_t> Kminus_PIDmu = {fReader, "Kminus_PIDmu"};
   TTreeReaderValue<Double_t> Kminus_PIDK = {fReader, "Kminus_PIDK"};
   TTreeReaderValue<Double_t> Kminus_PIDp = {fReader, "Kminus_PIDp"};
   TTreeReaderValue<Double_t> Kminus_PIDd = {fReader, "Kminus_PIDd"};
   TTreeReaderValue<Double_t> Kminus_ProbNNe = {fReader, "Kminus_ProbNNe"};
   TTreeReaderValue<Double_t> Kminus_ProbNNk = {fReader, "Kminus_ProbNNk"};
   TTreeReaderValue<Double_t> Kminus_ProbNNp = {fReader, "Kminus_ProbNNp"};
   TTreeReaderValue<Double_t> Kminus_ProbNNpi = {fReader, "Kminus_ProbNNpi"};
   TTreeReaderValue<Double_t> Kminus_ProbNNmu = {fReader, "Kminus_ProbNNmu"};
   TTreeReaderValue<Double_t> Kminus_ProbNNd = {fReader, "Kminus_ProbNNd"};
   TTreeReaderValue<Double_t> Kminus_ProbNNghost = {fReader, "Kminus_ProbNNghost"};
   TTreeReaderValue<Bool_t> Kminus_hasMuon = {fReader, "Kminus_hasMuon"};
   TTreeReaderValue<Bool_t> Kminus_isMuon = {fReader, "Kminus_isMuon"};
   TTreeReaderValue<Bool_t> Kminus_hasRich = {fReader, "Kminus_hasRich"};
   TTreeReaderValue<Bool_t> Kminus_UsedRichAerogel = {fReader, "Kminus_UsedRichAerogel"};
   TTreeReaderValue<Bool_t> Kminus_UsedRich1Gas = {fReader, "Kminus_UsedRich1Gas"};
   TTreeReaderValue<Bool_t> Kminus_UsedRich2Gas = {fReader, "Kminus_UsedRich2Gas"};
   TTreeReaderValue<Bool_t> Kminus_RichAboveElThres = {fReader, "Kminus_RichAboveElThres"};
   TTreeReaderValue<Bool_t> Kminus_RichAboveMuThres = {fReader, "Kminus_RichAboveMuThres"};
   TTreeReaderValue<Bool_t> Kminus_RichAbovePiThres = {fReader, "Kminus_RichAbovePiThres"};
   TTreeReaderValue<Bool_t> Kminus_RichAboveKaThres = {fReader, "Kminus_RichAboveKaThres"};
   TTreeReaderValue<Bool_t> Kminus_RichAbovePrThres = {fReader, "Kminus_RichAbovePrThres"};
   TTreeReaderValue<Bool_t> Kminus_hasCalo = {fReader, "Kminus_hasCalo"};
   TTreeReaderValue<Int_t> Kminus_TRACK_Type = {fReader, "Kminus_TRACK_Type"};
   TTreeReaderValue<Int_t> Kminus_TRACK_Key = {fReader, "Kminus_TRACK_Key"};
   TTreeReaderValue<Double_t> Kminus_TRACK_CHI2 = {fReader, "Kminus_TRACK_CHI2"};
   TTreeReaderValue<Int_t> Kminus_TRACK_NDOF = {fReader, "Kminus_TRACK_NDOF"};
   TTreeReaderValue<Double_t> Kminus_TRACK_CHI2NDOF = {fReader, "Kminus_TRACK_CHI2NDOF"};
   TTreeReaderValue<Double_t> Kminus_TRACK_PCHI2 = {fReader, "Kminus_TRACK_PCHI2"};
   TTreeReaderValue<Double_t> Kminus_TRACK_VeloCHI2NDOF = {fReader, "Kminus_TRACK_VeloCHI2NDOF"};
   TTreeReaderValue<Double_t> Kminus_TRACK_TCHI2NDOF = {fReader, "Kminus_TRACK_TCHI2NDOF"};
   TTreeReaderValue<Double_t> Kminus_TRACK_VELO_UTID = {fReader, "Kminus_TRACK_VELO_UTID"};
   TTreeReaderValue<Double_t> Kminus_TRACK_TT_UTID = {fReader, "Kminus_TRACK_TT_UTID"};
   TTreeReaderValue<Double_t> Kminus_TRACK_IT_UTID = {fReader, "Kminus_TRACK_IT_UTID"};
   TTreeReaderValue<Double_t> Kminus_TRACK_OT_UTID = {fReader, "Kminus_TRACK_OT_UTID"};
   TTreeReaderValue<Double_t> Kminus_TRACK_VP_UTID = {fReader, "Kminus_TRACK_VP_UTID"};
   TTreeReaderValue<Double_t> Kminus_TRACK_UT_UTID = {fReader, "Kminus_TRACK_UT_UTID"};
   TTreeReaderValue<Double_t> Kminus_TRACK_FT_UTID = {fReader, "Kminus_TRACK_FT_UTID"};
   TTreeReaderValue<Int_t> Kminus_TRACK_nVeloHits = {fReader, "Kminus_TRACK_nVeloHits"};
   TTreeReaderValue<Int_t> Kminus_TRACK_nVeloRHits = {fReader, "Kminus_TRACK_nVeloRHits"};
   TTreeReaderValue<Int_t> Kminus_TRACK_nVeloPhiHits = {fReader, "Kminus_TRACK_nVeloPhiHits"};
   TTreeReaderValue<Int_t> Kminus_TRACK_nVeloPileUpHits = {fReader, "Kminus_TRACK_nVeloPileUpHits"};
   TTreeReaderValue<Int_t> Kminus_TRACK_nTTHits = {fReader, "Kminus_TRACK_nTTHits"};
   TTreeReaderValue<Int_t> Kminus_TRACK_nITHits = {fReader, "Kminus_TRACK_nITHits"};
   TTreeReaderValue<Int_t> Kminus_TRACK_nOTHits = {fReader, "Kminus_TRACK_nOTHits"};
   TTreeReaderValue<Int_t> Kminus_TRACK_nVPHits = {fReader, "Kminus_TRACK_nVPHits"};
   TTreeReaderValue<Int_t> Kminus_TRACK_nUTHits = {fReader, "Kminus_TRACK_nUTHits"};
   TTreeReaderValue<Int_t> Kminus_TRACK_nFTHits = {fReader, "Kminus_TRACK_nFTHits"};
   TTreeReaderValue<Int_t> Kminus_TRACK_History = {fReader, "Kminus_TRACK_History"};
   TTreeReaderValue<Double_t> Kminus_TRACK_FirstMeasurementX = {fReader, "Kminus_TRACK_FirstMeasurementX"};
   TTreeReaderValue<Double_t> Kminus_TRACK_FirstMeasurementY = {fReader, "Kminus_TRACK_FirstMeasurementY"};
   TTreeReaderValue<Double_t> Kminus_TRACK_FirstMeasurementZ = {fReader, "Kminus_TRACK_FirstMeasurementZ"};
   TTreeReaderValue<Double_t> Kminus_TRACK_FirstMeasurementQOverP = {fReader, "Kminus_TRACK_FirstMeasurementQOverP"};
   TTreeReaderValue<Double_t> Kminus_TRACK_FirstMeasurementTx = {fReader, "Kminus_TRACK_FirstMeasurementTx"};
   TTreeReaderValue<Double_t> Kminus_TRACK_FirstMeasurementTy = {fReader, "Kminus_TRACK_FirstMeasurementTy"};
   TTreeReaderValue<Double_t> Kminus_TRACK_MatchCHI2 = {fReader, "Kminus_TRACK_MatchCHI2"};
   TTreeReaderValue<Double_t> Kminus_TRACK_GhostProb = {fReader, "Kminus_TRACK_GhostProb"};
   TTreeReaderValue<Double_t> Kminus_TRACK_CloneDist = {fReader, "Kminus_TRACK_CloneDist"};
   TTreeReaderValue<Double_t> Kminus_TRACK_Likelihood = {fReader, "Kminus_TRACK_Likelihood"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV2_ProbNNe = {fReader, "Kplus_MC12TuneV2_ProbNNe"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV2_ProbNNmu = {fReader, "Kplus_MC12TuneV2_ProbNNmu"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV2_ProbNNpi = {fReader, "Kplus_MC12TuneV2_ProbNNpi"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV2_ProbNNk = {fReader, "Kplus_MC12TuneV2_ProbNNk"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV2_ProbNNp = {fReader, "Kplus_MC12TuneV2_ProbNNp"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV2_ProbNNghost = {fReader, "Kplus_MC12TuneV2_ProbNNghost"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV3_ProbNNe = {fReader, "Kplus_MC12TuneV3_ProbNNe"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV3_ProbNNmu = {fReader, "Kplus_MC12TuneV3_ProbNNmu"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV3_ProbNNpi = {fReader, "Kplus_MC12TuneV3_ProbNNpi"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV3_ProbNNk = {fReader, "Kplus_MC12TuneV3_ProbNNk"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV3_ProbNNp = {fReader, "Kplus_MC12TuneV3_ProbNNp"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV3_ProbNNghost = {fReader, "Kplus_MC12TuneV3_ProbNNghost"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV4_ProbNNe = {fReader, "Kplus_MC12TuneV4_ProbNNe"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV4_ProbNNmu = {fReader, "Kplus_MC12TuneV4_ProbNNmu"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV4_ProbNNpi = {fReader, "Kplus_MC12TuneV4_ProbNNpi"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV4_ProbNNk = {fReader, "Kplus_MC12TuneV4_ProbNNk"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV4_ProbNNp = {fReader, "Kplus_MC12TuneV4_ProbNNp"};
   TTreeReaderValue<Double_t> Kplus_MC12TuneV4_ProbNNghost = {fReader, "Kplus_MC12TuneV4_ProbNNghost"};
   TTreeReaderValue<Double_t> Kplus_MC15TuneV1_ProbNNe = {fReader, "Kplus_MC15TuneV1_ProbNNe"};
   TTreeReaderValue<Double_t> Kplus_MC15TuneV1_ProbNNmu = {fReader, "Kplus_MC15TuneV1_ProbNNmu"};
   TTreeReaderValue<Double_t> Kplus_MC15TuneV1_ProbNNpi = {fReader, "Kplus_MC15TuneV1_ProbNNpi"};
   TTreeReaderValue<Double_t> Kplus_MC15TuneV1_ProbNNk = {fReader, "Kplus_MC15TuneV1_ProbNNk"};
   TTreeReaderValue<Double_t> Kplus_MC15TuneV1_ProbNNp = {fReader, "Kplus_MC15TuneV1_ProbNNp"};
   TTreeReaderValue<Double_t> Kplus_MC15TuneV1_ProbNNghost = {fReader, "Kplus_MC15TuneV1_ProbNNghost"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_X = {fReader, "Kplus_OWNPV_X"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_Y = {fReader, "Kplus_OWNPV_Y"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_Z = {fReader, "Kplus_OWNPV_Z"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_XERR = {fReader, "Kplus_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_YERR = {fReader, "Kplus_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_ZERR = {fReader, "Kplus_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_CHI2 = {fReader, "Kplus_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Kplus_OWNPV_NDOF = {fReader, "Kplus_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Kplus_IP_OWNPV = {fReader, "Kplus_IP_OWNPV"};
   TTreeReaderValue<Double_t> Kplus_IPCHI2_OWNPV = {fReader, "Kplus_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_X = {fReader, "Kplus_ORIVX_X"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_Y = {fReader, "Kplus_ORIVX_Y"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_Z = {fReader, "Kplus_ORIVX_Z"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_XERR = {fReader, "Kplus_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_YERR = {fReader, "Kplus_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_ZERR = {fReader, "Kplus_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_CHI2 = {fReader, "Kplus_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Kplus_ORIVX_NDOF = {fReader, "Kplus_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Kplus_P = {fReader, "Kplus_P"};
   TTreeReaderValue<Double_t> Kplus_PT = {fReader, "Kplus_PT"};
   TTreeReaderValue<Double_t> Kplus_PE = {fReader, "Kplus_PE"};
   TTreeReaderValue<Double_t> Kplus_PX = {fReader, "Kplus_PX"};
   TTreeReaderValue<Double_t> Kplus_PY = {fReader, "Kplus_PY"};
   TTreeReaderValue<Double_t> Kplus_PZ = {fReader, "Kplus_PZ"};
   TTreeReaderValue<Double_t> Kplus_M = {fReader, "Kplus_M"};
   TTreeReaderValue<Int_t> Kplus_ID = {fReader, "Kplus_ID"};
   TTreeReaderValue<Double_t> Kplus_PIDe = {fReader, "Kplus_PIDe"};
   TTreeReaderValue<Double_t> Kplus_PIDmu = {fReader, "Kplus_PIDmu"};
   TTreeReaderValue<Double_t> Kplus_PIDK = {fReader, "Kplus_PIDK"};
   TTreeReaderValue<Double_t> Kplus_PIDp = {fReader, "Kplus_PIDp"};
   TTreeReaderValue<Double_t> Kplus_PIDd = {fReader, "Kplus_PIDd"};
   TTreeReaderValue<Double_t> Kplus_ProbNNe = {fReader, "Kplus_ProbNNe"};
   TTreeReaderValue<Double_t> Kplus_ProbNNk = {fReader, "Kplus_ProbNNk"};
   TTreeReaderValue<Double_t> Kplus_ProbNNp = {fReader, "Kplus_ProbNNp"};
   TTreeReaderValue<Double_t> Kplus_ProbNNpi = {fReader, "Kplus_ProbNNpi"};
   TTreeReaderValue<Double_t> Kplus_ProbNNmu = {fReader, "Kplus_ProbNNmu"};
   TTreeReaderValue<Double_t> Kplus_ProbNNd = {fReader, "Kplus_ProbNNd"};
   TTreeReaderValue<Double_t> Kplus_ProbNNghost = {fReader, "Kplus_ProbNNghost"};
   TTreeReaderValue<Bool_t> Kplus_hasMuon = {fReader, "Kplus_hasMuon"};
   TTreeReaderValue<Bool_t> Kplus_isMuon = {fReader, "Kplus_isMuon"};
   TTreeReaderValue<Bool_t> Kplus_hasRich = {fReader, "Kplus_hasRich"};
   TTreeReaderValue<Bool_t> Kplus_UsedRichAerogel = {fReader, "Kplus_UsedRichAerogel"};
   TTreeReaderValue<Bool_t> Kplus_UsedRich1Gas = {fReader, "Kplus_UsedRich1Gas"};
   TTreeReaderValue<Bool_t> Kplus_UsedRich2Gas = {fReader, "Kplus_UsedRich2Gas"};
   TTreeReaderValue<Bool_t> Kplus_RichAboveElThres = {fReader, "Kplus_RichAboveElThres"};
   TTreeReaderValue<Bool_t> Kplus_RichAboveMuThres = {fReader, "Kplus_RichAboveMuThres"};
   TTreeReaderValue<Bool_t> Kplus_RichAbovePiThres = {fReader, "Kplus_RichAbovePiThres"};
   TTreeReaderValue<Bool_t> Kplus_RichAboveKaThres = {fReader, "Kplus_RichAboveKaThres"};
   TTreeReaderValue<Bool_t> Kplus_RichAbovePrThres = {fReader, "Kplus_RichAbovePrThres"};
   TTreeReaderValue<Bool_t> Kplus_hasCalo = {fReader, "Kplus_hasCalo"};
   TTreeReaderValue<Int_t> Kplus_TRACK_Type = {fReader, "Kplus_TRACK_Type"};
   TTreeReaderValue<Int_t> Kplus_TRACK_Key = {fReader, "Kplus_TRACK_Key"};
   TTreeReaderValue<Double_t> Kplus_TRACK_CHI2 = {fReader, "Kplus_TRACK_CHI2"};
   TTreeReaderValue<Int_t> Kplus_TRACK_NDOF = {fReader, "Kplus_TRACK_NDOF"};
   TTreeReaderValue<Double_t> Kplus_TRACK_CHI2NDOF = {fReader, "Kplus_TRACK_CHI2NDOF"};
   TTreeReaderValue<Double_t> Kplus_TRACK_PCHI2 = {fReader, "Kplus_TRACK_PCHI2"};
   TTreeReaderValue<Double_t> Kplus_TRACK_VeloCHI2NDOF = {fReader, "Kplus_TRACK_VeloCHI2NDOF"};
   TTreeReaderValue<Double_t> Kplus_TRACK_TCHI2NDOF = {fReader, "Kplus_TRACK_TCHI2NDOF"};
   TTreeReaderValue<Double_t> Kplus_TRACK_VELO_UTID = {fReader, "Kplus_TRACK_VELO_UTID"};
   TTreeReaderValue<Double_t> Kplus_TRACK_TT_UTID = {fReader, "Kplus_TRACK_TT_UTID"};
   TTreeReaderValue<Double_t> Kplus_TRACK_IT_UTID = {fReader, "Kplus_TRACK_IT_UTID"};
   TTreeReaderValue<Double_t> Kplus_TRACK_OT_UTID = {fReader, "Kplus_TRACK_OT_UTID"};
   TTreeReaderValue<Double_t> Kplus_TRACK_VP_UTID = {fReader, "Kplus_TRACK_VP_UTID"};
   TTreeReaderValue<Double_t> Kplus_TRACK_UT_UTID = {fReader, "Kplus_TRACK_UT_UTID"};
   TTreeReaderValue<Double_t> Kplus_TRACK_FT_UTID = {fReader, "Kplus_TRACK_FT_UTID"};
   TTreeReaderValue<Int_t> Kplus_TRACK_nVeloHits = {fReader, "Kplus_TRACK_nVeloHits"};
   TTreeReaderValue<Int_t> Kplus_TRACK_nVeloRHits = {fReader, "Kplus_TRACK_nVeloRHits"};
   TTreeReaderValue<Int_t> Kplus_TRACK_nVeloPhiHits = {fReader, "Kplus_TRACK_nVeloPhiHits"};
   TTreeReaderValue<Int_t> Kplus_TRACK_nVeloPileUpHits = {fReader, "Kplus_TRACK_nVeloPileUpHits"};
   TTreeReaderValue<Int_t> Kplus_TRACK_nTTHits = {fReader, "Kplus_TRACK_nTTHits"};
   TTreeReaderValue<Int_t> Kplus_TRACK_nITHits = {fReader, "Kplus_TRACK_nITHits"};
   TTreeReaderValue<Int_t> Kplus_TRACK_nOTHits = {fReader, "Kplus_TRACK_nOTHits"};
   TTreeReaderValue<Int_t> Kplus_TRACK_nVPHits = {fReader, "Kplus_TRACK_nVPHits"};
   TTreeReaderValue<Int_t> Kplus_TRACK_nUTHits = {fReader, "Kplus_TRACK_nUTHits"};
   TTreeReaderValue<Int_t> Kplus_TRACK_nFTHits = {fReader, "Kplus_TRACK_nFTHits"};
   TTreeReaderValue<Int_t> Kplus_TRACK_History = {fReader, "Kplus_TRACK_History"};
   TTreeReaderValue<Double_t> Kplus_TRACK_FirstMeasurementX = {fReader, "Kplus_TRACK_FirstMeasurementX"};
   TTreeReaderValue<Double_t> Kplus_TRACK_FirstMeasurementY = {fReader, "Kplus_TRACK_FirstMeasurementY"};
   TTreeReaderValue<Double_t> Kplus_TRACK_FirstMeasurementZ = {fReader, "Kplus_TRACK_FirstMeasurementZ"};
   TTreeReaderValue<Double_t> Kplus_TRACK_FirstMeasurementQOverP = {fReader, "Kplus_TRACK_FirstMeasurementQOverP"};
   TTreeReaderValue<Double_t> Kplus_TRACK_FirstMeasurementTx = {fReader, "Kplus_TRACK_FirstMeasurementTx"};
   TTreeReaderValue<Double_t> Kplus_TRACK_FirstMeasurementTy = {fReader, "Kplus_TRACK_FirstMeasurementTy"};
   TTreeReaderValue<Double_t> Kplus_TRACK_MatchCHI2 = {fReader, "Kplus_TRACK_MatchCHI2"};
   TTreeReaderValue<Double_t> Kplus_TRACK_GhostProb = {fReader, "Kplus_TRACK_GhostProb"};
   TTreeReaderValue<Double_t> Kplus_TRACK_CloneDist = {fReader, "Kplus_TRACK_CloneDist"};
   TTreeReaderValue<Double_t> Kplus_TRACK_Likelihood = {fReader, "Kplus_TRACK_Likelihood"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV2_ProbNNe = {fReader, "Piplus_MC12TuneV2_ProbNNe"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV2_ProbNNmu = {fReader, "Piplus_MC12TuneV2_ProbNNmu"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV2_ProbNNpi = {fReader, "Piplus_MC12TuneV2_ProbNNpi"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV2_ProbNNk = {fReader, "Piplus_MC12TuneV2_ProbNNk"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV2_ProbNNp = {fReader, "Piplus_MC12TuneV2_ProbNNp"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV2_ProbNNghost = {fReader, "Piplus_MC12TuneV2_ProbNNghost"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV3_ProbNNe = {fReader, "Piplus_MC12TuneV3_ProbNNe"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV3_ProbNNmu = {fReader, "Piplus_MC12TuneV3_ProbNNmu"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV3_ProbNNpi = {fReader, "Piplus_MC12TuneV3_ProbNNpi"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV3_ProbNNk = {fReader, "Piplus_MC12TuneV3_ProbNNk"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV3_ProbNNp = {fReader, "Piplus_MC12TuneV3_ProbNNp"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV3_ProbNNghost = {fReader, "Piplus_MC12TuneV3_ProbNNghost"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV4_ProbNNe = {fReader, "Piplus_MC12TuneV4_ProbNNe"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV4_ProbNNmu = {fReader, "Piplus_MC12TuneV4_ProbNNmu"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV4_ProbNNpi = {fReader, "Piplus_MC12TuneV4_ProbNNpi"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV4_ProbNNk = {fReader, "Piplus_MC12TuneV4_ProbNNk"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV4_ProbNNp = {fReader, "Piplus_MC12TuneV4_ProbNNp"};
   TTreeReaderValue<Double_t> Piplus_MC12TuneV4_ProbNNghost = {fReader, "Piplus_MC12TuneV4_ProbNNghost"};
   TTreeReaderValue<Double_t> Piplus_MC15TuneV1_ProbNNe = {fReader, "Piplus_MC15TuneV1_ProbNNe"};
   TTreeReaderValue<Double_t> Piplus_MC15TuneV1_ProbNNmu = {fReader, "Piplus_MC15TuneV1_ProbNNmu"};
   TTreeReaderValue<Double_t> Piplus_MC15TuneV1_ProbNNpi = {fReader, "Piplus_MC15TuneV1_ProbNNpi"};
   TTreeReaderValue<Double_t> Piplus_MC15TuneV1_ProbNNk = {fReader, "Piplus_MC15TuneV1_ProbNNk"};
   TTreeReaderValue<Double_t> Piplus_MC15TuneV1_ProbNNp = {fReader, "Piplus_MC15TuneV1_ProbNNp"};
   TTreeReaderValue<Double_t> Piplus_MC15TuneV1_ProbNNghost = {fReader, "Piplus_MC15TuneV1_ProbNNghost"};
   TTreeReaderValue<Double_t> Piplus_OWNPV_X = {fReader, "Piplus_OWNPV_X"};
   TTreeReaderValue<Double_t> Piplus_OWNPV_Y = {fReader, "Piplus_OWNPV_Y"};
   TTreeReaderValue<Double_t> Piplus_OWNPV_Z = {fReader, "Piplus_OWNPV_Z"};
   TTreeReaderValue<Double_t> Piplus_OWNPV_XERR = {fReader, "Piplus_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Piplus_OWNPV_YERR = {fReader, "Piplus_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Piplus_OWNPV_ZERR = {fReader, "Piplus_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Piplus_OWNPV_CHI2 = {fReader, "Piplus_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Piplus_OWNPV_NDOF = {fReader, "Piplus_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Piplus_IP_OWNPV = {fReader, "Piplus_IP_OWNPV"};
   TTreeReaderValue<Double_t> Piplus_IPCHI2_OWNPV = {fReader, "Piplus_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Piplus_ORIVX_X = {fReader, "Piplus_ORIVX_X"};
   TTreeReaderValue<Double_t> Piplus_ORIVX_Y = {fReader, "Piplus_ORIVX_Y"};
   TTreeReaderValue<Double_t> Piplus_ORIVX_Z = {fReader, "Piplus_ORIVX_Z"};
   TTreeReaderValue<Double_t> Piplus_ORIVX_XERR = {fReader, "Piplus_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Piplus_ORIVX_YERR = {fReader, "Piplus_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Piplus_ORIVX_ZERR = {fReader, "Piplus_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Piplus_ORIVX_CHI2 = {fReader, "Piplus_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Piplus_ORIVX_NDOF = {fReader, "Piplus_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Piplus_P = {fReader, "Piplus_P"};
   TTreeReaderValue<Double_t> Piplus_PT = {fReader, "Piplus_PT"};
   TTreeReaderValue<Double_t> Piplus_PE = {fReader, "Piplus_PE"};
   TTreeReaderValue<Double_t> Piplus_PX = {fReader, "Piplus_PX"};
   TTreeReaderValue<Double_t> Piplus_PY = {fReader, "Piplus_PY"};
   TTreeReaderValue<Double_t> Piplus_PZ = {fReader, "Piplus_PZ"};
   TTreeReaderValue<Double_t> Piplus_M = {fReader, "Piplus_M"};
   TTreeReaderValue<Int_t> Piplus_ID = {fReader, "Piplus_ID"};
   TTreeReaderValue<Double_t> Piplus_PIDe = {fReader, "Piplus_PIDe"};
   TTreeReaderValue<Double_t> Piplus_PIDmu = {fReader, "Piplus_PIDmu"};
   TTreeReaderValue<Double_t> Piplus_PIDK = {fReader, "Piplus_PIDK"};
   TTreeReaderValue<Double_t> Piplus_PIDp = {fReader, "Piplus_PIDp"};
   TTreeReaderValue<Double_t> Piplus_PIDd = {fReader, "Piplus_PIDd"};
   TTreeReaderValue<Double_t> Piplus_ProbNNe = {fReader, "Piplus_ProbNNe"};
   TTreeReaderValue<Double_t> Piplus_ProbNNk = {fReader, "Piplus_ProbNNk"};
   TTreeReaderValue<Double_t> Piplus_ProbNNp = {fReader, "Piplus_ProbNNp"};
   TTreeReaderValue<Double_t> Piplus_ProbNNpi = {fReader, "Piplus_ProbNNpi"};
   TTreeReaderValue<Double_t> Piplus_ProbNNmu = {fReader, "Piplus_ProbNNmu"};
   TTreeReaderValue<Double_t> Piplus_ProbNNd = {fReader, "Piplus_ProbNNd"};
   TTreeReaderValue<Double_t> Piplus_ProbNNghost = {fReader, "Piplus_ProbNNghost"};
   TTreeReaderValue<Bool_t> Piplus_hasMuon = {fReader, "Piplus_hasMuon"};
   TTreeReaderValue<Bool_t> Piplus_isMuon = {fReader, "Piplus_isMuon"};
   TTreeReaderValue<Bool_t> Piplus_hasRich = {fReader, "Piplus_hasRich"};
   TTreeReaderValue<Bool_t> Piplus_UsedRichAerogel = {fReader, "Piplus_UsedRichAerogel"};
   TTreeReaderValue<Bool_t> Piplus_UsedRich1Gas = {fReader, "Piplus_UsedRich1Gas"};
   TTreeReaderValue<Bool_t> Piplus_UsedRich2Gas = {fReader, "Piplus_UsedRich2Gas"};
   TTreeReaderValue<Bool_t> Piplus_RichAboveElThres = {fReader, "Piplus_RichAboveElThres"};
   TTreeReaderValue<Bool_t> Piplus_RichAboveMuThres = {fReader, "Piplus_RichAboveMuThres"};
   TTreeReaderValue<Bool_t> Piplus_RichAbovePiThres = {fReader, "Piplus_RichAbovePiThres"};
   TTreeReaderValue<Bool_t> Piplus_RichAboveKaThres = {fReader, "Piplus_RichAboveKaThres"};
   TTreeReaderValue<Bool_t> Piplus_RichAbovePrThres = {fReader, "Piplus_RichAbovePrThres"};
   TTreeReaderValue<Bool_t> Piplus_hasCalo = {fReader, "Piplus_hasCalo"};
   TTreeReaderValue<Int_t> Piplus_TRACK_Type = {fReader, "Piplus_TRACK_Type"};
   TTreeReaderValue<Int_t> Piplus_TRACK_Key = {fReader, "Piplus_TRACK_Key"};
   TTreeReaderValue<Double_t> Piplus_TRACK_CHI2 = {fReader, "Piplus_TRACK_CHI2"};
   TTreeReaderValue<Int_t> Piplus_TRACK_NDOF = {fReader, "Piplus_TRACK_NDOF"};
   TTreeReaderValue<Double_t> Piplus_TRACK_CHI2NDOF = {fReader, "Piplus_TRACK_CHI2NDOF"};
   TTreeReaderValue<Double_t> Piplus_TRACK_PCHI2 = {fReader, "Piplus_TRACK_PCHI2"};
   TTreeReaderValue<Double_t> Piplus_TRACK_VeloCHI2NDOF = {fReader, "Piplus_TRACK_VeloCHI2NDOF"};
   TTreeReaderValue<Double_t> Piplus_TRACK_TCHI2NDOF = {fReader, "Piplus_TRACK_TCHI2NDOF"};
   TTreeReaderValue<Double_t> Piplus_TRACK_VELO_UTID = {fReader, "Piplus_TRACK_VELO_UTID"};
   TTreeReaderValue<Double_t> Piplus_TRACK_TT_UTID = {fReader, "Piplus_TRACK_TT_UTID"};
   TTreeReaderValue<Double_t> Piplus_TRACK_IT_UTID = {fReader, "Piplus_TRACK_IT_UTID"};
   TTreeReaderValue<Double_t> Piplus_TRACK_OT_UTID = {fReader, "Piplus_TRACK_OT_UTID"};
   TTreeReaderValue<Double_t> Piplus_TRACK_VP_UTID = {fReader, "Piplus_TRACK_VP_UTID"};
   TTreeReaderValue<Double_t> Piplus_TRACK_UT_UTID = {fReader, "Piplus_TRACK_UT_UTID"};
   TTreeReaderValue<Double_t> Piplus_TRACK_FT_UTID = {fReader, "Piplus_TRACK_FT_UTID"};
   TTreeReaderValue<Int_t> Piplus_TRACK_nVeloHits = {fReader, "Piplus_TRACK_nVeloHits"};
   TTreeReaderValue<Int_t> Piplus_TRACK_nVeloRHits = {fReader, "Piplus_TRACK_nVeloRHits"};
   TTreeReaderValue<Int_t> Piplus_TRACK_nVeloPhiHits = {fReader, "Piplus_TRACK_nVeloPhiHits"};
   TTreeReaderValue<Int_t> Piplus_TRACK_nVeloPileUpHits = {fReader, "Piplus_TRACK_nVeloPileUpHits"};
   TTreeReaderValue<Int_t> Piplus_TRACK_nTTHits = {fReader, "Piplus_TRACK_nTTHits"};
   TTreeReaderValue<Int_t> Piplus_TRACK_nITHits = {fReader, "Piplus_TRACK_nITHits"};
   TTreeReaderValue<Int_t> Piplus_TRACK_nOTHits = {fReader, "Piplus_TRACK_nOTHits"};
   TTreeReaderValue<Int_t> Piplus_TRACK_nVPHits = {fReader, "Piplus_TRACK_nVPHits"};
   TTreeReaderValue<Int_t> Piplus_TRACK_nUTHits = {fReader, "Piplus_TRACK_nUTHits"};
   TTreeReaderValue<Int_t> Piplus_TRACK_nFTHits = {fReader, "Piplus_TRACK_nFTHits"};
   TTreeReaderValue<Int_t> Piplus_TRACK_History = {fReader, "Piplus_TRACK_History"};
   TTreeReaderValue<Double_t> Piplus_TRACK_FirstMeasurementX = {fReader, "Piplus_TRACK_FirstMeasurementX"};
   TTreeReaderValue<Double_t> Piplus_TRACK_FirstMeasurementY = {fReader, "Piplus_TRACK_FirstMeasurementY"};
   TTreeReaderValue<Double_t> Piplus_TRACK_FirstMeasurementZ = {fReader, "Piplus_TRACK_FirstMeasurementZ"};
   TTreeReaderValue<Double_t> Piplus_TRACK_FirstMeasurementQOverP = {fReader, "Piplus_TRACK_FirstMeasurementQOverP"};
   TTreeReaderValue<Double_t> Piplus_TRACK_FirstMeasurementTx = {fReader, "Piplus_TRACK_FirstMeasurementTx"};
   TTreeReaderValue<Double_t> Piplus_TRACK_FirstMeasurementTy = {fReader, "Piplus_TRACK_FirstMeasurementTy"};
   TTreeReaderValue<Double_t> Piplus_TRACK_MatchCHI2 = {fReader, "Piplus_TRACK_MatchCHI2"};
   TTreeReaderValue<Double_t> Piplus_TRACK_GhostProb = {fReader, "Piplus_TRACK_GhostProb"};
   TTreeReaderValue<Double_t> Piplus_TRACK_CloneDist = {fReader, "Piplus_TRACK_CloneDist"};
   TTreeReaderValue<Double_t> Piplus_TRACK_Likelihood = {fReader, "Piplus_TRACK_Likelihood"};
   TTreeReaderValue<UInt_t> nCandidate = {fReader, "nCandidate"};
   TTreeReaderValue<ULong64_t> totCandidates = {fReader, "totCandidates"};
   TTreeReaderValue<ULong64_t> EventInSequence = {fReader, "EventInSequence"};
   TTreeReaderValue<UInt_t> runNumber = {fReader, "runNumber"};
   TTreeReaderValue<ULong64_t> eventNumber = {fReader, "eventNumber"};
   TTreeReaderValue<UInt_t> BCID = {fReader, "BCID"};
   TTreeReaderValue<Int_t> BCType = {fReader, "BCType"};
   TTreeReaderValue<UInt_t> OdinTCK = {fReader, "OdinTCK"};
   TTreeReaderValue<UInt_t> L0DUTCK = {fReader, "L0DUTCK"};
   TTreeReaderValue<UInt_t> HLT1TCK = {fReader, "HLT1TCK"};
   TTreeReaderValue<UInt_t> HLT2TCK = {fReader, "HLT2TCK"};
   TTreeReaderValue<ULong64_t> GpsTime = {fReader, "GpsTime"};
   TTreeReaderValue<Short_t> Polarity = {fReader, "Polarity"};
   TTreeReaderValue<Int_t> nPV = {fReader, "nPV"};
   TTreeReaderArray<Float_t> PVX = {fReader, "PVX"};
   TTreeReaderArray<Float_t> PVY = {fReader, "PVY"};
   TTreeReaderArray<Float_t> PVZ = {fReader, "PVZ"};
   TTreeReaderArray<Float_t> PVXERR = {fReader, "PVXERR"};
   TTreeReaderArray<Float_t> PVYERR = {fReader, "PVYERR"};
   TTreeReaderArray<Float_t> PVZERR = {fReader, "PVZERR"};
   TTreeReaderArray<Float_t> PVCHI2 = {fReader, "PVCHI2"};
   TTreeReaderArray<Float_t> PVNDOF = {fReader, "PVNDOF"};
   TTreeReaderArray<Float_t> PVNTRACKS = {fReader, "PVNTRACKS"};


   dsp_background(TTree * /*tree*/ =0) { }
   virtual ~dsp_background() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(dsp_background,0);

};

#endif

#ifdef dsp_background_cxx
void dsp_background::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t dsp_background::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef dsp_background_cxx
