# LHCb Research
Research measuring mass difference between D+ and Ds+ mesons. This repository includes all analysis files, including RDataFrames and the more standard MakeSelectors. Also included in the ```LHCb``` subdirectory are the Ganga scripts and DaVinci ntuple options used to collect the raw data.

Some relevant links: 
 * [Precision measurement of D meson mass differences](https://arxiv.org/pdf/1304.6865.pdf "d meson mass differences")
 * [D+ → K−K+π+](https://arxiv.org/pdf/hep-ex/0501075.pdf "D -> KKpi")
 * [LHCb StarterKit Lessons](https://lhcb.github.io/starterkit-lessons/ "lhcb starterkit")


## Data Collection
All of the necessary files for this and more are stored in the [`/LHCb/`](https://github.com/bodensjc/ddecay/tree/main/LHCb) subdirectory. This part of the tutorial assumes that you have a functioning grid certificate through CERN and are able to run Ganga jobs on DIRAC. This is covered in the LHCb StarterKit Lessons linked above. 
List of files in `/LHCb/` and their purpose:
 * [`dp_job.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/dp_job.py): Ganga job to get D+ -> KKpi data
   * [`dp_options.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/dp_options.py): Options file for D+ -> KKpi data. Tells what variables to collect.
 * [`dsp_job.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/dsp_job.py): Ganga job to get Ds+ -> KKpi data
   * [`dsp_options.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/dsp_options.py): Options file for Ds+ -> KKpi data. Tells what variables to collect.
* [`symbols.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/symbols.py): Prints out particle symbols as interpreted by Ganga with some additional info.
* [`jobstatus.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/jobstatus.py): Prints out status of subjobs of a running job
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
Done on UC computer (dot at end can be replaced with destination path, it's probably a good idea to put data in `share/lazy`):
```
$ rsync -ap username@lxplus.cern.ch:/path/to/chunk1.root .
```

## Data Analysis


