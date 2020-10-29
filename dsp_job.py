j = Job(name='dsp_10-29') #"mm-dd:run"
myApp = GaudiExec()
myApp.directory = "./DaVinciDev_v45r1 " #davinci version listed for charmcharged stream is v42r5 but this oen works
j.application = myApp
j.application.options = ['dsp_options.py'] #ntuple options file
j.application.platform = 'x86_64-centos7-gcc8-opt' #gcc8 to match davinci version, gcc62 for v42r5
bkPath = '/LHCb/Collision17/Beam6500GeV-VeloClosed-MagUp/Real Data/Turbo04/94000000/CHARMSPEC.MDST' #path to real data
data = BKQuery(bkPath, dqflag=['OK']).getDataset()
j.inputdata = data[0:12693] #get first 5 data files
j.backend = Dirac()

#can use the below line to not run on russian servers if its going to be an issue again...
#j.backend.settings['BannedSites'] = ['LCG.Some.Site','LCG.SomeOther.Site'] 

j.outputfiles = [
	DiracFile('Dsp2KKpiMagUp.root')
]
j.splitter = SplitByFiles(filesPerJob=5) 
j.submit()

