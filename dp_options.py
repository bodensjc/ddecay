from GaudiConf import IOHelper
from Configurables import DaVinci, DecayTreeTuple,TupleToolTrackPosition
from DecayTreeTuple.Configuration import *

stream = 'Charmcharged'#Charmspec doesnt work
line = 'Hlt2CharmHadDpToKmKpPipTurbo'

dtt = DecayTreeTuple('D2KKpi')
dtt.Inputs = ['{0}/Particles'.format(line)] #/Event/{0}/Phys/{1}/Particles
dtt.Decay = '[D+ -> ^K- ^K+ ^pi+]CC'
track_tool = dtt.addTupleTool('TupleToolTrackInfo')
track_tool.Verbose = True
dtt.addTupleTool('TupleToolPrimaries')

#I believe these five are included in Primaries
#dtt.addTupleTool('TupleToolGeometry')
#dtt.addTupleTool('TupleToolKinematic')
#dtt.addTupleTool('TupleToolPid')
#dtt.addTupleTool('TupleToolANNPid')
#dtt.addTupleTool('TupleToolEventInfo')

## from Michel De Cian 151213
##  The positions of the T stations are (about):
##  7950mm
##  8630mm
##  9315mm
#TupleToolTrackPosition = TupleToolTrackPosition('TupleToolTrackPosition')
#TupleToolTrackPosition.Z = 8630
#dtt.addTupleTool('TupleToolTrackPosition')

#another method
track_position_tool = dtt.addTupleTool('TupleToolTrackPosition')
track_position_tool.Z = 8630

dtt.addBranches({
        'Dplus' : '([D+ -> K- K+ pi+]CC)',
        'Kminus' : '([D+ -> ^K- K+ pi+]CC)',
        'Kplus' : '([D+ -> K- ^K+ pi+]CC)',
        'Piplus' : '([D+ -> K- K+ ^pi+]CC)'
})

dtt.Dplus.addTupleTool('TupleToolPropertime')

DaVinci().UserAlgorithms += [dtt]

DaVinci().Turbo = True
DaVinci().RootInTES = '/Event/Charmcharged/Turbo'#Charmspec doesnt work
DaVinci().InputType = 'MDST'
#DaVinci().DDDBtag = 'dddb-20171030-3'
DaVinci().Simulation = False
DaVinci().TupleFile = 'Dp2KKpiMagDown.root'
DaVinci().PrintFreq = 50000
DaVinci().DataType = '2017'
DaVinci().Lumi = False
DaVinci().EvtMax = -1

#IOHelper().inputFiles([
#    'root://hake1.grid.surfsara.nl:1094/pnfs/grid.sara.nl/data/lhcb/LHCb/Collision17/CHARMCHARGED.MDST/00067727/0001/00067727_00012788_1.charmcharged.mdst'], clear=True)
