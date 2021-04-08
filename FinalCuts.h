//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr  7 20:47:51 2021 by ROOT version 6.22/00
// from TTree DecayTree/DecayTree
// found on file: /share/lazy/D2KKpi/combined_cut.root
//////////////////////////////////////////////////////////

#ifndef FinalCuts_h
#define FinalCuts_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class FinalCuts : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> particle_MM = {fReader, "particle_MM"};
   TTreeReaderValue<Double_t> particle_TAU = {fReader, "particle_TAU"};
   TTreeReaderValue<Double_t> particle_PX = {fReader, "particle_PX"};
   TTreeReaderValue<Double_t> particle_PY = {fReader, "particle_PY"};
   TTreeReaderValue<Double_t> particle_PZ = {fReader, "particle_PZ"};
   TTreeReaderValue<Double_t> particle_PT = {fReader, "particle_PT"};
   TTreeReaderValue<Int_t> isDp = {fReader, "isDp"};
   TTreeReaderValue<Short_t> Polarity = {fReader, "Polarity"};


   FinalCuts(TTree * /*tree*/ =0) { }
   virtual ~FinalCuts() { }
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

   ClassDef(FinalCuts,0);

};

#endif

#ifdef FinalCuts_cxx
void FinalCuts::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t FinalCuts::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef FinalCuts_cxx
