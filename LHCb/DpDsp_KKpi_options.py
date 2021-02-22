from GaudiConf import IOHelper
from Configurables import DaVinci, DecayTreeTuple
from DecayTreeTuple.Configuration import *

stream = 'Charmcharged'
line0 = 'Hlt2CharmHadDpToKmKpPipTurbo'
line1 = 'Hlt2CharmHadDspToKmKpPip_LTUNBTurbo'

dtt0 = DecayTreeTuple('Dp2KKpi_Tuple')
dtt0.Inputs = ['{0}/Particles'.format(line0)] #/Event/{0}/Phys/{1}/Particles
dtt0.Decay = '[D+ -> ^K- ^K+ ^pi+]CC'
track_tool0 = dtt0.addTupleTool('TupleToolTrackInfo')
track_tool0.Verbose = True
dtt0.addTupleTool('TupleToolPrimaries')
dtt0.addBranches({
        'Dplus' : '([^D+ -> K- K+ pi+]CC)',
        'Kminus' : '([D+ -> ^K- K+ pi+]CC)',
        'Kplus' : '([D+ -> K- ^K+ pi+]CC)',
        'Piplus' : '([D+ -> K- K+ ^pi+]CC)'
})

dtt1 = DecayTreeTuple('Ds2KKpi_Tuple')
dtt1.Inputs = ['{0}/Particles'.format(line1)] #/Event/{0}/Phys/{1}/Particles
dtt1.Decay = '[D_s+ -> ^K- ^K+ ^pi+]CC'
track_tool1 = dtt1.addTupleTool('TupleToolTrackInfo')
track_tool1.Verbose = True
dtt1.addTupleTool('TupleToolPrimaries')
dtt1.addBranches({
        'Dsplus' : '([^D_s+ -> K- K+ pi+]CC)',
        'Kminus' : '([D_s+ -> ^K- K+ pi+]CC)',
        'Kplus' : '([D_s+ -> K- ^K+ pi+]CC)',
        'Piplus' : '([D_s+ -> K- K+ ^pi+]CC)'
})


DaVinci().UserAlgorithms += [dtt0, dtt1]

DaVinci().Turbo = True
DaVinci().RootInTES = '/Event/Charmcharged/Turbo'
DaVinci().InputType = 'MDST'
DaVinci().DDDBtag = 'dddb-20171030-3'
DaVinci().Simulation = False
DaVinci().TupleFile = 'DpDsp2KKpiMagDown.root'
DaVinci().PrintFreq = 5000
DaVinci().DataType = '2017'
DaVinci().Lumi = False
DaVinci().EvtMax = -1

#IOHelper().inputFiles([
#    'root://hake1.grid.surfsara.nl:1094/pnfs/grid.sara.nl/data/lhcb/LHCb/Collision17/CHARMCHARGED.MDST/00067727/0001/00067727_00012788_1.charmcharged.mdst'], clear=True)
