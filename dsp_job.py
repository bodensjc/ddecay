j = Job(name='dsp_up_12-30:0') #"mm-dd:run"
#only need below line if its first time running with DaVinci version
#myApp = prepareGaudiExec('DaVinci', 'v45r1', myPath='.')

myApp = GaudiExec()
myApp.directory = "./DaVinciDev_v45r1" 

j.application = myApp
j.application.options = ['dsp_options.py'] #ntuple options file
j.application.platform = 'x86_64-centos7-gcc8-opt' #gcc8 to match davinci version, gcc62 for v42r5
bkPath = '/LHCb/Collision17/Beam6500GeV-VeloClosed-MagUp/Real Data/Turbo04/94000000/CHARMSPEC.MDST' #path to real data
#magdown path'/LHCb/Collision17/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo04/94000000/CHARMCHARGED.MDST'
data = BKQuery(bkPath, dqflag=['OK']).getDataset()
j.inputdata = data[0:13551] #get all data files (magup - 13551) (magdown - 12693)
j.backend = Dirac()

#can use the below line to not run on russian servers if its going to be an issue again...
#j.backend.settings['BannedSites'] = ['LCG.Some.Site','LCG.SomeOther.Site'] 

j.splitter = SplitByFiles(filesPerJob=5) 
j.outputfiles = [DiracFile('Dsp2KKpiMagUp.root')]
j.submit()

