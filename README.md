# LHCb Research
Research measuring mass difference between D+ and Ds+ mesons. This repository includes all analysis files, including RDataFrames and the more standard MakeSelectors. Also included is the `LHCb` subdirectory, containing the Ganga scripts and DaVinci ntuple options used to collect the raw data.

Some relevant links: 
 * [Precision measurement of D meson mass differences](https://arxiv.org/pdf/1304.6865.pdf "d meson mass differences")
 * [D+ → K−K+π+](https://arxiv.org/pdf/hep-ex/0501075.pdf "D -> KKpi")
 * [LHCb StarterKit Lessons](https://lhcb.github.io/starterkit-lessons/ "lhcb starterkit")


## Data Collection
All of the necessary files for this and more are stored in the [`/LHCb/`](https://github.com/bodensjc/ddecay/tree/main/LHCb) subdirectory. This part of the tutorial assumes that you have a functioning grid certificate through CERN and are able to run Ganga jobs on DIRAC. This is covered in the LHCb StarterKit Lessons linked above. 
List of files in `/LHCb/` and their purpose:
 * [`dp_job.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/dp_job.py): Ganga job to get D+ -> KKpi data.
   * [`dp_options.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/dp_options.py): Options file for D+ -> KKpi data. Tells what variables to collect.
 * [`dsp_job.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/dsp_job.py): Ganga job to get Ds+ -> KKpi data.
   * [`dsp_options.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/dsp_options.py): Options file for Ds+ -> KKpi data. Tells what variables to collect.
* [`symbols.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/symbols.py): Prints out particle symbols as interpreted by Ganga with some additional info.
* [`jobstatus.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/jobstatus.py): Prints out status of subjobs of a running job.
* [`ListLFNs.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/ListLFNs.py): Saves the LFNs (output file locations) of a Ganga job to a .txt file.
* [`lfn_parse.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/lfn_parse.py): File that is fairly unique to this decay and will almost certainly need to be revised if used again. It looks at the file produced by `ListLFNs.py` and extracts the important information and "chunks" it for data transfer purposes.
* [`getEvents.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/getEvents.py): Not used in this analysis, but can collect some dms files.
* [`TeslaTuplesDec15.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/TeslaTuplesDec15.py): File from Mike in 2015. I borrowed some code from here, specifically regarding the T stations. Great example of what a _good_ ntuple options file looks like.



### Run the Ganga scripts:
This is the first step of the analysis- collecting the data. The ntuple options / Ganga scripts used will save the data to EOS, a large area of disk space provided by CERN for users. 
1. Start by `ssh`-ing into CERN computers, proxying into lhcb, and navigating to the directory in which you have saved your job and options files.
```
$ ssh username@lxplus.cern.ch
$ lhcb-proxy-init
$ cd ddecay/
```
2. Enter Ganga and run the jobs. For the files I have created this will need to be done **four** times. Twice for each decay (D+ and Ds+) and again for each magnet polarity. As they are, the `job` and `options` files are set up to already discriminate between D+ and Ds+ (As indicated by their names). To change between MagUp and MagDown data, lines 1, 11, 15, and 22 in the `job` scripts needs to be adjusted. Line 46 (`TupleFile`) in the `options` scripts should also be changed to match the output file name (line 22) in the `job` scripts.
```
$ ganga
$ ganga dp_job.py
```
after that is done setting up:
```
$ ganga
$ ganga dsp_job.py
```
After both of these are done, make the polarity changes and repeat.


### Monitor your jobs
Monitoring running jobs can be done on [DIRAC](https://lhcb-portal-dirac.cern.ch/DIRAC/). You will need your certificates functioning in your browser to properly access this site. The process to get this up and running is well documented on CERN wikis and forums. Using the "Job Monitor" tool on DIRAC you can change some parameters to monitor recently scheduled jobs. You can also reschedule jobs that happen to fail. More information about DIRAC including some useful guides can be found [here](http://diracgrid.org/).


### Get the data:
1. In lxplus open a dirac sub-shell and proxy to lhcb.
```
$ lb-dirac bash --norc 
$ lhcb-proxy-init
```
2. Get a list of all lfns older than d days (probably fine to set d=0), this will output the file "lhcb-user-u-username.lfns" into current directory ("u-username" in my case is j-jbodensc)
```
$ dirac-dms-user-lfns --Days=d
```
3. (optional) if you need to get rid of older files, run the above command isolating all data older than d' days (d' > d, such that you only select files _older_ than what you are interested in), then run the following command to remove these lfns. WARNING: they are not going to come back! (Note: There is probably a cleaner way of doing this without [risking] removing older data. Just something to consdier.)
```
$ dirac-dms-remove-files --File=lhcb-user-u-username.lfns
```
4. Get the access URLs to the lfns by running the below command with your file containing the LFNs:
```
$dirac-dms-lfn-accessURL --File=lhcb-user-u-username.lfns > somefilename.txt 
```
5. Now run the "somefilename.txt" through a parser, selesting the accessURLs. Then these can `hadd`'d on lxplus, then `rsync`'d to UC from CERN. I have created an `lfn_parse.py` script that does this for my lfns and can be modified to parse through your lfns also. I collect and move the data in chunks from CERN computers to UC computers so as to not exceed storage limits. This is also safer in the event that something "breaks"- only a small chunkneeds to be redone.
```
$ hadd chunk1.root smallfile1.root smallfile2.root ... smallfilen.root
```
The following line can be done on either lxplus or UC computers, but I prefer to do it on UC computers so I can have only one session of lxplus up where I am `hadd`ing chunks together. Done on lxplus:
```
$ rsync -ap chunk1.root username@sleepy.geop.uc.edu:/share/lazy/yourfolder
```
Alternatively on UC computers (dot at end can be replaced with destination path, it's probably a good idea to put data in `/share/lazy`):
```
$ rsync -ap username@lxplus.cern.ch:/path/to/chunk1.root .
```

## Data Analysis
This is the crux of the research. Here we study the many variables of the decays, generating a great number of plots from which we can extract useful information regarding the signals and background.  The `/image/` and `/finalImages/` subdirectories are where I store any plots I create, more important (final) plots going into the `/finalImages/` folder. The subdirectories `/old_C/` and `/old_dsp/` are, as labeled, _old_. They contain my first attempts at analysis from Summer 2020. The methods used are sometimes similar to more recent code, but in general these are just saved for a rare reference to past work and will certainly **not** work on existing datasets. The `/scripts/` subdirectory contains all fitting functions used. The most improtant file in this folder is `new_fit_spectrum.C`. It was created to make various fitting techniques "easier" in the Analysis stage, this will be seen later on. The "loose" files in the main `ddecay/` directory are what I used for analysis. 
### Cut the data
Due to the size of the data for this analysis some more "modern" ROOT techniques are applied, namely, `RDataFrames`. RDataFrames (RDFs) are fairly new to ROOT, as such they arenn't documented incredibly well and are not yet as powerful as their predecessor `MakeSelector`. The [official documentation](https://root.cern/doc/master/classROOT_1_1RDataFrame.html) provides a helpful cheat sheet on the functions that can be used with RDFs. In my case, I use RDFs to make my first analysis cuts on the larger data set. I make special use of the `Snapshot()` function to create smaller, more efficient data sets that include only necessary variables (for fitting, momentum scaling, etc.). I was not able to figure out if it was possible to do fitting in RDFs, so I do all fitting in a `MakeSelector`. You _can_ make regular plots and histograms in RDFs, but I found the process to have some tedious additional steps- so I generally stuck to the aforementioned method of snapshots. Here is a list of my RDF files and analysis files as well as their purpose:

RDataFrame Files:
 * **Useful**
   * [`dp_dalitz_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/dp_dalitz_rdf.C): Dalitz plots of the D+ decay.
   * [`dp_dsp_cut_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/dp_dsp_cut_rdf.C): The big one! This file contains the final cuts and "standardizes" the data so that I can make ONE ntuple containing both D+ and Ds data.
   * [`dp_ms_reduced_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/dp_ms_reduced_rdf.C): Used in conjunction with `quick.py`, makes reduced ntuples that are cut and include only variables necessary for momentum scaling steps.
   * [`extra_info_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/extra_info_rdf.C): Commented below the preamble are some helpful functions for getting properties of the ntuple/data (column names, number of entries, ...). Also used to investigate OdinTCKs and the overlap region (see `notes.txt`).
 * **Old**
   * [`dp_cuts_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/dp_cuts_rdf.C): Old D+ cuts with some attempts at fitting.
   * [`dsp_cuts_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/dsp_cuts_rdf.C): Old Ds cuts with some attempts at fitting.
   * [`dp_dsp_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/dp_dsp_rdf.C): Simple plots of the two decays with some cuts.
   * [`dp_fit_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/dp_fit_rdf.C): Failed attempts at fitting.
   * [`dp_mstest_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/dp_mstest_rdf.C): Old file used to make plots of the T-Stations for momentum scaling.
   * [`dp_probtests_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/dp_probtests_rdf.C): Looking at ProbNNx in different regions.
   * [`dp_tests_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/dp_tests_rdf.C): Looking at endvertex cuts.
   * [`lifetime_rdf.C`](https://github.com/bodensjc/ddecay/blob/main/lifetime_rdf.C): Trying to manually calculate lifetime before eventually remaking ntuples to include the `_TAU` variable.

Analysis files:
 * **Useful**
   * 
 * **Old**
   * 






Here are brief descriptions of other files used:
 * [`differences.xlsx`](https://github.com/bodensjc/ddecay/blob/main/differences.xlsx): Quick excel sheet to find Δm(Ds-D+) for momentum regions.
 * [`quick.py`](https://github.com/bodensjc/ddecay/blob/main/quick.py): Quickply made python parser used to find what variables are used in Momentum Scaling code.
 * [`notes.txt`](https://github.com/bodensjc/ddecay/blob/main/notes.txt): Notes file used when searching for ~~missing~~(ended up none missing) TCKs. Also used to look at the "overlap region".
 * `README.md`: Documentation.
