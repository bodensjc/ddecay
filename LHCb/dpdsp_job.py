j = Job(name='7-9:1 DpDsp_KKpi') #"mm-dd:run decay"
myApp = GaudiExec()
myApp.directory = "./DaVinciDev_v45r1 " #davinci version listed for charmcharged stream is v42r5 but this oen works
j.application = myApp
j.application.options = ['DpDsp_KKpi_options.py'] #ntuple options file
j.application.platform = 'x86_64-centos7-gcc8-opt' #gcc8 to match davinci version, gcc62 for v42r5
bkPath = '/LHCb/Collision17/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo04/94000000/CHARMCHARGED.MDST' #path to real data
data = BKQuery(bkPath, dqflag=['OK']).getDataset()
j.inputdata = data[0:100] #get first 100 data files (out of 4311)
j.backend = Dirac()
j.outputfiles = [
	DiracFile('DpDsp2KKpiMagDown.root')
]
j.splitter = SplitByFiles(filesPerJob=10) #should give 10 subjobs (100 files / 10 files per job)
j.submit()

