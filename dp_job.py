j = Job(name='6-19:3 Dp_KKpi') #"mm-dd:run decay"
myApp = GaudiExec()
myApp.directory = "./DaVinciDev_v42r5" #davinci version listed for charmcharged stream
j.application = myApp
j.application.options = ['Dp_KKpi_options.py'] #ntuple options file
j.application.platform = 'x86_64-centos7-gcc62-opt' #gcc62 to match davinci version, usually gcc8
bkPath = '/LHCb/Collision17/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo04/94000000/CHARMCHARGED.MDST' #path to real data
data = BKQuery(bkPath, dqflag=['OK']).getDataset()
j.inputdata = data[0:2] #get first 2 data files (out of 4311)
j.backend = Dirac()
j.splitter = SplitByFiles(filesPerJob=1) #should give 2 subjobs (2 files / 1 files per job)
j.outputfiles = [DiracFile('D2KKpi_Tuple.root')] #store on eos
j.submit()

