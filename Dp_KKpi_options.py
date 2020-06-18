from GaudiConf import IOHelper
from Configurables import DaVinci, DecayTreeTuple
from DecayTreeTuple.Configuration import *
​
stream = 'Charmcharged'
line = 'Hlt2CharmHadDpToKmKpPipTurbo'
​
dtt = DecayTreeTuple('D2KKpi_Tuple')
dtt.Inputs = ['/Event/{0}/Phys/{1}/Particles'.format(stream, line)] #added /ev - {1 
dtt.Decay = '[D+ -> ^K- ^K+ ^pi+]CC'
track_tool = dtt.addTupleTool('TupleToolTrackInfo')
track_tool.Verbose = True
dtt.addTupleTool('TupleToolPrimaries')
​
dtt.addBranches({
        'Dplus' : '([^D+ -> K- K+ pi+]CC)',
        'Kminus' : '([D+ -> ^K- K+ pi+]CC)',
        'Kplus' : '([D+ -> K- ^K+ pi+]CC)',
        'Piplus' : '([D+ -> K- K+ ^pi+]CC)'
})
​
DaVinci().UserAlgorithms += [dtt]
​
DaVinci().Turbo = True
DaVinci().RootInTES = '/Event/Charmcharged/Turbo'
DaVinci().InputType = 'MDST'
DaVinci().DDDBtag = 'dddb-20171030-3'
DaVinci().Simulation = False
DaVinci().TupleFile = 'Dp2KKpiMagDown.root'
DaVinci().PrintFreq = 5000
DaVinci().DataType = '2017'
DaVinci().Lumi = False
DaVinci().EvtMax = -1
​
#IOHelper().inputFiles([
#    'root://hake1.grid.surfsara.nl:1094/pnfs/grid.sara.nl/data/lhcb/LHCb/Collision17/CHARMCHARGED.MDST/00067727/0001/00067727_00012788_1.charmcharged.mdst'], clear=True)
