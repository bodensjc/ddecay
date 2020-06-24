from GaudiConf import IOHelper
from Configurables import DaVinci, DecayTreeTuple
from DecayTreeTuple.Configuration import *

stream = 'Charmcharged'
line = 'Hlt2CharmHadDspToKmKpPip_LTUNBTurbo'

dtt = DecayTreeTuple('D2KKpi_Tuple')
dtt.Inputs = ['{0}/Particles'.format(line)] #/Event/{0}/Phys/{1}/Particles
dtt.Decay = '[Ds+ -> ^K- ^K+ ^pi+]CC'
track_tool = dtt.addTupleTool('TupleToolTrackInfo')
track_tool.Verbose = True
dtt.addTupleTool('TupleToolPrimaries')

dtt.addBranches({
        'Dsplus' : '([^Ds+ -> K- K+ pi+]CC)',
        'Kminus' : '([Ds+ -> ^K- K+ pi+]CC)',
        'Kplus' : '([Ds+ -> K- ^K+ pi+]CC)',
        'Piplus' : '([Ds+ -> K- K+ ^pi+]CC)'
})

DaVinci().UserAlgorithms += [dtt]

DaVinci().Turbo = True
DaVinci().RootInTES = '/Event/Charmcharged/Turbo'
DaVinci().InputType = 'MDST'
DaVinci().DDDBtag = 'dddb-20171030-3'
DaVinci().Simulation = False
DaVinci().TupleFile = 'Dsp2KKpiMagDown.root'
DaVinci().PrintFreq = 5000
DaVinci().DataType = '2017'
DaVinci().Lumi = False
DaVinci().EvtMax = -1

#IOHelper().inputFiles([
#    'root://hake1.grid.surfsara.nl:1094/pnfs/grid.sara.nl/data/lhcb/LHCb/Collision17/CHARMCHARGED.MDST/00067727/0001/00067727_00012788_1.charmcharged.mdst'], clear=True)
