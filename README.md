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
* [`TeslaTuplesDec15.py`](https://github.com/bodensjc/ddecay/blob/main/LHCb/TeslaTuplesDec15.py): File from Mike in 2015. I yoinked some code from here, specifically regarding the T stations. Excelent example of what a _good_ ntuple options file looks like.



### Run the Ganga scripts:
This is the first step of the analysis- collecting the data. The Ganga scripts used will save the data to EOS, a large area of disk space provided by CERN for users. 

### To get lfns from dirac:
1. in lxplus open a dirac sub-shell and proxy to lhcb
```
$ lb-dirac bash --norc 
$ lhcb-proxy-init
```
2. get a list of lfns older than d days, this will output "lhcb-user-u-username.lfns" into current directory ("u-username" in my case is j-jbodensc)
```
$ dirac-dms-user-lfns --Days=d
```
3. (optional) if you need to get rid of older data, run the above command isolating all data older than d days, then run the following command to remove these lfns. WARNING: they are not going to come back
```
$ dirac-dms-remove-files --File=lhcb-user-u-username.lfns
```
4. get the access URLs to the lfns, run the below command with your file containing the LFNs
```
$dirac-dms-lfn-accessURL --File=lhcb-user-u-username.lfns > somefilename.txt 
```
5. Now run the "somefilename.txt" through a parser, selesting the accessURLs. Then these can hadd'd on lxplus, then rsync'd to UC from CERN.


