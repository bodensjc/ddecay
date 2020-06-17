from Configurables import DaVinci
from GaudiConf import IOHelper

# Load algorithms
from Configurables import CombineParticles
from Configurables import DaVinci
from Configurables import DecayTreeTuple
from DecayTreeTuple.Configuration import *

# Load input particles
from StandardParticles import StdAllNoPIDsPions as Pions
from StandardParticles import StdNoPIDsKaons as Kaons
from StandardParticles import StdNoPIDsPions as Pions
# Load Selection objects
from PhysConf.Selections import CombineSelection, FilterSelection
from PhysConf.Selections import SelectionSequence, Hlt2TOSSelection

# Build the D+ from the kaons and pion
dp_daughters = {
    'K-': '(PT > 750*MeV) & (P > 4000*MeV) & (MIPCHI2DV(PRIMARY) > 4)',
    'K+': '(PT > 750*MeV) & (P > 4000*MeV) & (MIPCHI2DV(PRIMARY) > 4)',
    'pi+': '(PT > 750*MeV) & (P > 4000*MeV) & (MIPCHI2DV(PRIMARY) > 4)'
}
dp_comb = "(AMAXDOCA('') < 0.2*mm) & (ADAMASS('D+') < 100*MeV)"
# We can split long selections across multiple lines
dp_mother = (
    '(VFASPF(VCHI2/VDOF)< 9)'
    '& (BPVDIRA > 0.9997)'
    "& (ADMASS('D+') < 70*MeV)"
)

dp_sel = CombineSelection(
    'Sel_Dp',
    [Kaons, Pions],
    DecayDescriptor='[D+ -> K- K+ pi+]cc',
    DaughtersCuts=dp_daughters,
    CombinationCut=dp_comb,
    MotherCut=dp_mother,
)

dp_seq = SelectionSequence('Dp_Seq', TopSelection=dp_sel)

# Create an ntuple
dtt = DecayTreeTuple('Tuple_DpToKKpi')
dtt.Inputs = dp_seq.outputLocations()
dtt.Decay = '[D+ -> ^K- ^K+ ^pi+]CC'

DaVinci().UserAlgorithms += [dp_seq.sequence(), dtt]

# DaVinci configuration
DaVinci().InputType = 'MDST'
DaVinci().TupleFile = 'DVntuple.root'
DaVinci().PrintFreq = 1000
DaVinci().DataType = '2017'
DaVinci().Simulation = False
# Only ask for luminosity information when not using simulated data
DaVinci().Lumi = not DaVinci().Simulation
DaVinci().EvtMax = 1000

IOHelper().inputFiles([('root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/LHCb/Collision17/94000000/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo04/CHARMCHARGED.MDST')],
                      clear=True)
