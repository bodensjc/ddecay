j = Job(name='dp_up_12-16:all') #"mm-dd:run"
#only need below line if its first time running with DaVinci version
#myApp = prepareGaudiExec('DaVinci', 'v45r1', myPath='.')

myApp = GaudiExec()
myApp.directory = "./DaVinciDev_v45r1"

j.application = myApp
j.application.options = ['dp_options.py'] #ntuple options file
j.application.platform = 'x86_64-centos7-gcc8-opt' #gcc8 to match davinci version, gcc62 for v42r5
bkPath = '/LHCb/Collision17/Beam6500GeV-VeloClosed-MagUp/Real Data/Turbo04/94000000/CHARMCHARGED.MDST' #path to real data
data = BKQuery(bkPath, dqflag=['OK']).getDataset()
j.inputdata = data[0:4126] #get all data files (magup)
j.backend = Dirac()

#can use the below line to not run on russian servers if its going to be an issue again...
#j.backend.settings['BannedSites'] = ['LCG.Some.Site','LCG.SomeOther.Site'] 

j.splitter = SplitByFiles(filesPerJob=5) 
j.outputfiles = [DiracFile('Dp2KKpiMagUp.root')]
j.submit()

