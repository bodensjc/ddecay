from GaudiConf import IOHelper
from Configurables import DaVinci, DecayTreeTuple,TupleToolTrackPosition
from DecayTreeTuple.Configuration import *

stream = 'Charmspec'#Charmcharged doesnt work
line = 'Hlt2CharmHadDspToKmKpPipTurbo'

dtt = DecayTreeTuple('Dsp2KKpi')
dtt.Inputs = ['{0}/Particles'.format(line)] #/Event/{0}/Phys/{1}/Particles
dtt.Decay = '[D_s+ -> ^K- ^K+ ^pi+]CC'
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
track_position_tool = dtt.addTupleTool('TupleToolTrackPosition')
track_position_tool.Z = 8630

dtt.addBranches({
        'Dsplus' : '([D_s+ -> K- K+ pi+]CC)',
        'Kminus' : '([D_s+ -> ^K- K+ pi+]CC)',
        'Kplus' : '([D_s+ -> K- ^K+ pi+]CC)',
        'Piplus' : '([D_s+ -> K- K+ ^pi+]CC)'
})

dtt.Dsplus.addTupleTool('TupleToolPropertime')

DaVinci().UserAlgorithms += [dtt]

DaVinci().Turbo = True
DaVinci().RootInTES = '/Event/Charmspec/Turbo'#Charmcharged does not work
DaVinci().InputType = 'MDST'
#DaVinci().DDDBtag = 'dddb-20171030-3'
DaVinci().Simulation = False
DaVinci().TupleFile = 'Dsp2KKpiMagDown1.root'#change to magdown/magup
DaVinci().PrintFreq = 50000
DaVinci().DataType = '2017'
DaVinci().Lumi = False
DaVinci().EvtMax = -1