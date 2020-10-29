# LHCb Research
## Data collection repository
Research measuring mass difference between D+ and Ds+ mesons. This repository includes relevant ntuple options, ganga jobs, and root files.
Some relevant links: https://arxiv.org/pdf/hep-ex/0501075.pdf, https://journals.aps.org/prd/pdf/10.1103/PhysRevD.98.056021, http://hyperphysics.phy-astr.gsu.edu/hbase/Particles/dmeson.html






### To get lfns from dirac:
1. in lxplus open a dirac sub-shell and proxy to lhcb
```
$ lb-dirac bash --norc 
$ lhcb-proxy-init
```

2. get a list of lfns older than d days, this will output "filename.lfns" into current directory
```
$ dirac-dms-user-lfns --Days=d
```

3. (optional) if you need to get rid of older data, run the above command isolating all data older than d days, then run the following ocmmand to remove these lfns. WARNING: they are not going to come back
```
$ dirac-dms-remove-files --File=filename.lfns
```

4. get the access URLs to the lfns, this can then be put through the parder then scrdp'd into ntubles that can be rsync'd from uc to cern
```
$dirac-dms-lfn-accessURL --File-filename.lfns > siomefile.txt 
```

