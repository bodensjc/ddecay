j = Job(name='6-18:1 Dp_KKpi')
myApp = GaudiExec()
myApp.directory = "./DaVinci/v42r5"
j.application = myApp
j.application.options = ['Dp_KKpi_options.py'] #ntuple options file
j.application.platform = 'x86_64-centos7-gcc62-opt' #maybe gcc8
bkPath = '/LHCb/Collision17/94000000/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo04/CHARMCHARGED.MDST'
data = BKQuery(bkPath, dqflag=['OK']).getDataset()
j.inputdata = data[0:10] #get first 10 data files (out of 4311)
j.backend = Dirac()
j.splitter = SplitByFiles(filesPerJob=5) #should give 2 subjobs (10 files / 5 files per job)
j.outputfiles = [DiracFile('DVntuple.root')] #store on eos
j.submit()

