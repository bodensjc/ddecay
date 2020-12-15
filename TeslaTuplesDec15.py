##  an options file to make NTUPLEs from Turbo stream data processed by Tesla circa early July, 2015
##
##  tested in a local release of DaVinci_v36r7p4 created using "SetupProject DaVinci v36r7p4 --build-env"
##  executed using 
##     gaudirun.py TeslaTuplesJuly11C.py  >& (log file name) & 
##
##  The .mdst file used as input here was generated using the options file turbo_july11B.py
##  found in /afs/cern.ch/work/m/msokolof/public/July10_15.  A list of the Turbo lines
##  which should be instantiated in corresponding TES locations starts at line 20 of that file.
##
##   The input files are listed in the file 
##      NB_PassedMooreJuly11.py
##   also found in
##      /afs/cern.ch/work/m/msokolof/public/July10_15
##
##  The LFNs given in that file corresponds to 3.5M No-Bias events 
##  which passed L0-filtering corresponding to what we expect 
##  to use in August for the 25-ns running. Howver, not all were
##  processed by Moore when making the .raw file used as input to 
##  the Tesla job used to make the .mdst file.
##
##   added TupleToolTrackPosition to record x position in middle of T-stations
##   151215
##   Mike Sokoloff



from Configurables import DaVinci
from Configurables import DecayTreeTuple
from Configurables import TupleToolTrackPosition
from Configurables import GaudiSequencer, ChargedProtoANNPIDConf


#List of tools 
tools = [ 
        "TupleToolGeometry"
        , "TupleToolKinematic"
        , "TupleToolPropertime"
        , "TupleToolPrimaries"
        , "TupleToolPid"
        , "TupleToolEventInfo"
        , "TupleToolRecoStats"
        , "TupleToolL0Data"
        , "TupleToolTrigger"
        , "TupleToolTISTOS"
        , "TupleToolTrackPosition"
        ]

triggers =  [ 'L0HadronDecision', 'Hlt1TrackMVADecision', 'Hlt1TwoTrackMVADecision',
              'Hlt2Topo2BodyDecision',
              'Hlt2Topo3BodyDecision',
              'Hlt2Topo4BodyDecision',
              'Hlt2TopoMu2BodyDecision',
              'Hlt2TopoMu3BodyDecision',
              'Hlt2TopoMu4BodyDecision',
            ]

from Configurables import TupleToolDecay, TupleToolDecayTreeFitter, TupleToolTrigger, TupleToolTISTOS


## from Michel De Cian 151213
##  The positions of the T stations are (about):
##  7950mm
##  8630mm
##  9315mm
TupleToolTrackPosition = TupleToolTrackPosition('TupleToolTrackPosition')
TupleToolTrackPosition.Z = 8630.

##     ----------------  D*+ --> D0,pi+;  D0 --> K-,pi-,pi+,pi+  --------------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDstp2D0Pip_D02KmPimPipPipTurbo'
name = 'DstpD0ToK3Pi'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

DstpD02KPiPiPi = DecayTreeTuple("DstpD02KPiPiPiTuple")
DstpD02KPiPiPi.Decay = "[D*(2010)+ -> ^(D0 -> ^K- ^pi- ^pi+ ^pi+) ^pi+]CC"
DstpD02KPiPiPi.Branches = {
    "D0"          : "[D*(2010)+ -> ^(D0 -> K- pi- pi+ pi+) pi+]CC",
    "Kminus"      : "[D*(2010)+ -> (D0 -> ^K- pi- pi+ pi+) pi+]CC",
    "Piminus"     : "[D*(2010)+ -> (D0 -> K- ^pi- pi+ pi+) pi+]CC",
    "Piplus1"     : "[D*(2010)+ -> (D0 -> K- pi- ^pi+ pi+) pi+]CC",
    "Piplus2"     : "[D*(2010)+ -> (D0 -> K- pi- pi+ ^pi+) pi+]CC",
    "PromptPi"    : "[D*(2010)+ -> (D0 -> K- pi- pi+  pi+) ^pi+]CC",
    "Dstar"       : "[D*(2010)+ -> (D0 -> K- pi- pi+ pi+) pi+]CC"
}
DstpD02KPiPiPi.TupleName = "DstpD02KPiPiPi"
DstpD02KPiPiPi.WriteP2PVRelations = False
DstpD02KPiPiPi.InputPrimaryVertices = tesla_vertex_location
DstpD02KPiPiPi.Inputs = [ tesla_particle_location ]
DstpD02KPiPiPi.ToolList +=  tools

## added 151215
##     ----------------  D*+ --> D0,pi+;  D0 --> K-,K-,K+,pi+  --------------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDstp2D0Pip_D02KmKmKpPipTurbo'
name = 'DstpD0ToKKKPi'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

DstpD02KKKPi = DecayTreeTuple("DstpD02KKKPiTuple")
DstpD02KKKPi.Decay = "[D*(2010)+ -> ^(D0 -> ^K- ^K- ^K+ ^pi+) ^pi+]CC"
DstpD02KKKPi.Branches = {
    "D0"          : "[D*(2010)+ -> ^(D0 -> K- K- K+ pi+) pi+]CC",
    "Kminus1"     : "[D*(2010)+ -> (D0 -> ^K- K- K+ pi+) pi+]CC",
    "Kminus2"     : "[D*(2010)+ -> (D0 -> K- ^K- K+ pi+) pi+]CC",
    "Kplus"       : "[D*(2010)+ -> (D0 -> K- K- ^K+ pi+) pi+]CC",
    "Piplus"      : "[D*(2010)+ -> (D0 -> K- K- K+ ^pi+) pi+]CC",
    "PromptPi"    : "[D*(2010)+ -> (D0 -> K- K- K+  pi+) ^pi+]CC",
    "Dstar"       : "[D*(2010)+ -> (D0 -> K- K- K+ pi+) pi+]CC"
}
DstpD02KKKPi.TupleName = "DstpD02KKKPi"
DstpD02KKKPi.WriteP2PVRelations = False
DstpD02KKKPi.InputPrimaryVertices = tesla_vertex_location
DstpD02KKKPi.Inputs = [ tesla_particle_location ]
DstpD02KKKPi.ToolList +=  tools


## added 151215
##     ----------------  D*+ --> D0,pi+;  D0 --> K-,K+,pi-,pi+  --------------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDstp2D0Pip_D02KmKpPimPipTurbo'
name = 'DstpD0ToKKPiPi'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

DstpD02KKPiPi = DecayTreeTuple("DstpD02KKPiPiTuple")
DstpD02KKPiPi.Decay = "[D*(2010)+ -> ^(D0 -> ^K- ^K+ ^pi- ^pi+) ^pi+]CC"
DstpD02KKPiPi.Branches = {
    "D0"          : "[D*(2010)+ -> ^(D0 -> K- K+ pi- pi+) pi+]CC",
    "Kminus"      : "[D*(2010)+ -> (D0 -> ^K- K+ pi- pi+) pi+]CC",
    "Kplus"       : "[D*(2010)+ -> (D0 -> K- ^K+ pi- pi+) pi+]CC",
    "Piminus"     : "[D*(2010)+ -> (D0 -> K- K+ ^pi- pi+) pi+]CC",
    "Piplus"      : "[D*(2010)+ -> (D0 -> K- K+ pi- ^pi+) pi+]CC",
    "PromptPi"    : "[D*(2010)+ -> (D0 -> K- K+ pi-  pi+) ^pi+]CC",
    "Dstar"       : "[D*(2010)+ -> (D0 -> K- K+ pi- pi+) pi+]CC"
}
DstpD02KKPiPi.TupleName = "DstpD02KKPiPi"
DstpD02KKPiPi.WriteP2PVRelations = False
DstpD02KKPiPi.InputPrimaryVertices = tesla_vertex_location
DstpD02KKPiPi.Inputs = [ tesla_particle_location ]
DstpD02KKPiPi.ToolList +=  tools


## ------  Spectroscopy:  (D*+),pi-;  D*+ --> D0,pi+;  D0 --> K-,pi+  -------------------
#Locations of tesla
tesla_line = 'Hlt2CharmHadSpec_Dst_KPi_PiTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'Dst_D0ToKPi_Pi'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

DstpPim = DecayTreeTuple("DstpPim")
DstpPim.Decay = "[D*(2007)0 ->^(D*(2010)+ -> ^(D0 -> ^K- ^pi+) ^pi+) ^pi-]CC"
DstpPim.Branches = {
    "Dstar"       : "[D*(2007)0 ->^(D*(2010)+ -> (D0 -> K- pi+) pi+) pi-]CC",
    "D0"          : "[D*(2007)0 ->(D*(2010)+ -> ^(D0 -> K- pi+) pi+) pi-]CC",
    "DaughterK"   : "[D*(2007)0 ->(D*(2010)+ -> (D0 -> ^K- pi+) pi+) pi-]CC",
    "DaughterPi"  : "[D*(2007)0 ->(D*(2010)+ -> (D0 -> K- ^pi+) pi+) pi-]CC",
    "SlowPi"      : "[D*(2007)0 ->(D*(2010)+ -> (D0 -> K- pi+) ^pi+) pi-]CC",
    "PromptPi"    : "[D*(2007)0 ->(D*(2010)+ -> (D0 -> K- pi+) pi+) ^pi-]CC",
    "Dstarsq"     : "[D*(2007)0 ->(D*(2010)+ -> (D0 -> K- pi+) pi+) pi-]CC"
}
DstpPim.TupleName = "DstpPim"
DstpPim.WriteP2PVRelations = False
DstpPim.InputPrimaryVertices = tesla_vertex_location
DstpPim.Inputs = [ tesla_particle_location ]
DstpPim.ToolList +=  tools

## ------  Spectroscopy:  (D0 --> K-,pi+),pi+
#Locations of tesla
tesla_line = 'Hlt2CharmHadSpec_D0ToKPi_PiTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"

D0ToKPi_Pip = DecayTreeTuple("D0ToKPi_Pip")
D0ToKPi_Pip.Decay = "[D*(2010)+ -> ^(D0 -> ^K- ^pi+) ^pi+ ]CC"
D0ToKPi_Pip.Branches = {
    "D0"          : "[D*(2010)+ -> ^(D0 -> K- pi+) pi+]CC",
    "Kminus"      : "[D*(2010)+ -> (D0 -> ^K- pi+) pi+]CC",
    "Piplus"      : "[D*(2010)+ -> (D0 -> K- ^pi+) pi+]CC",
    "BachelorPi"  : "[D*(2010)+ -> (D0 -> K- pi+) ^pi+]CC",
    "Dstar"       : "[D*(2010)+ -> (D0 -> K- pi+) pi+]CC",
}
D0ToKPi_Pip.TupleName = "DecayTree"
D0ToKPi_Pip.WriteP2PVRelations = False
D0ToKPi_Pip.InputPrimaryVertices = tesla_vertex_location
D0ToKPi_Pip.Inputs = [ tesla_particle_location ]
D0ToKPi_Pip.ToolList +=  tools

## ------  Spectroscopy:  (D0 --> K-,pi+),pi-
#Locations of tesla
tesla_line = 'Hlt2CharmHadSpec_D0ToKPi_PiTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"

D0ToKPi_Pim = DecayTreeTuple("D0ToKPi_Pim")
D0ToKPi_Pim.Decay = "[D*(2010)- -> ^(D0 -> ^K- ^pi+) ^pi- ]CC"
D0ToKPi_Pim.Branches = {
    "D0"          : "[D*(2010)- -> ^(D0 -> K- pi+) pi-]CC",
    "Kminus"      : "[D*(2010)- -> (D0 -> ^K- pi+) pi-]CC",
    "Piplus"      : "[D*(2010)- -> (D0 -> K- ^pi+) pi-]CC",
    "BachelorPi"  : "[D*(2010)- -> (D0 -> K- pi+) ^pi-]CC",
    "Dstar"       : "[D*(2010)- -> (D0 -> K- pi+) pi-]CC",
}
D0ToKPi_Pim.TupleName = "DecayTree"
D0ToKPi_Pim.WriteP2PVRelations = False
D0ToKPi_Pim.InputPrimaryVertices = tesla_vertex_location
D0ToKPi_Pim.Inputs = [ tesla_particle_location ]
D0ToKPi_Pim.ToolList +=  tools


##  -----------  D*+ --> D0,pi+;  D0 --> K-,pi+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDstp2D0Pip_D02KmPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'Dstp_D0ToKPi'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

DstpD02KPi = DecayTreeTuple("DstpD02KPi")
DstpD02KPi.Decay = "[D*(2010)+ -> ^(D0 -> ^K- ^pi+) ^pi+]CC"
DstpD02KPi.Branches = {
    "D0"          : "[D*(2010)+ -> ^(D0 -> K- pi+) pi+]CC",
    "DaughterK"   : "[D*(2010)+ -> (D0 -> ^K- pi+) pi+]CC",
    "DaughterPi"  : "[D*(2010)+ -> (D0 -> K- ^pi+) pi+]CC",
    "SlowPi"      : "[D*(2010)+ -> (D0 -> K- pi+) ^pi+]CC",
    "Dstar"       : "[D*(2010)+ -> (D0 -> K- pi+) pi+]CC",
}
DstpD02KPi.TupleName = "DstpD02KPi"
DstpD02KPi.WriteP2PVRelations = False
DstpD02KPi.InputPrimaryVertices = tesla_vertex_location
DstpD02KPi.Inputs = [ tesla_particle_location ]
DstpD02KPi.ToolList +=  tools
DstpD02KPi.addTool(TupleToolTrackPosition)


##  added 151215  mds
##  -----------  D*+ --> D0,pi+;  D0 --> K-,K+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDstp2D0Pip_D02KmKpTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'Dstp_D0ToKK'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

DstpD02KK = DecayTreeTuple("DstpD02KK")
DstpD02KK.Decay = "[D*(2010)+ -> ^(D0 -> ^K- ^K+) ^pi+]CC"
DstpD02KK.Branches = {
    "D0"          : "[D*(2010)+ -> ^(D0 -> K- K+) pi+]CC",
    "DaughterK"   : "[D*(2010)+ -> (D0 -> ^K- K+) pi+]CC",
    "DaughterPi"  : "[D*(2010)+ -> (D0 -> K- ^K+) pi+]CC",
    "SlowPi"      : "[D*(2010)+ -> (D0 -> K- K+) ^pi+]CC",
    "Dstar"       : "[D*(2010)+ -> (D0 -> K- K+) pi+]CC",
}
DstpD02KK.TupleName = "DstpD02KK"
DstpD02KK.WriteP2PVRelations = False
DstpD02KK.InputPrimaryVertices = tesla_vertex_location
DstpD02KK.Inputs = [ tesla_particle_location ]
DstpD02KK.ToolList +=  tools
DstpD02KK.addTool(TupleToolTrackPosition)

##  -----------  D+ --> K-,pi+,pi+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDpToKmPipPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'DplusToKPiPi'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

Dp2KmPipPip = DecayTreeTuple("DpToKmPipPip")
Dp2KmPipPip.Decay = "[D+ -> ^K- ^pi+ ^pi+]CC"
Dp2KmPipPip.Branches = {
    "Kminus"    : "[D+ -> ^K- pi+ pi+]CC",
    "Piplus1"   : "[D+ -> K- ^pi+ pi+]CC",
    "Piplus2"   : "[D+ -> K- pi+ ^pi+]CC",
    "Dplus"     : "[D+ -> K- pi+ pi+]CC",
}
Dp2KmPipPip.TupleName = "DpToKmPipPip"
Dp2KmPipPip.WriteP2PVRelations = False
Dp2KmPipPip.InputPrimaryVertices = tesla_vertex_location
Dp2KmPipPip.Inputs = [ tesla_particle_location ]
Dp2KmPipPip.ToolList +=  tools
Dp2KmPipPip.addTool(TupleToolTrackPosition)

##  -----------  D+ --> pi-,pi+,pi+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDpToPimPipPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'DplusToPiPiPi'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

Dp2PimPipPip = DecayTreeTuple("DpToPimPipPip")
Dp2PimPipPip.Decay = "[D+ -> ^pi- ^pi+ ^pi+]CC"
Dp2PimPipPip.Branches = {
    "Piminus"    : "[D+ -> ^pi- pi+ pi+]CC",
    "Piplus1"   : "[D+ -> pi- ^pi+ pi+]CC",
    "Piplus2"   : "[D+ -> pi- pi+ ^pi+]CC",
    "Dplus"     : "[D+ -> pi- pi+ pi+]CC",
}
Dp2PimPipPip.TupleName = "DpToPimPipPip"
Dp2PimPipPip.WriteP2PVRelations = False
Dp2PimPipPip.InputPrimaryVertices = tesla_vertex_location
Dp2PimPipPip.Inputs = [ tesla_particle_location ]
Dp2PimPipPip.ToolList +=  tools

##  -----------  D+ --> K-,K+,pi+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDpToKmKpPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'DplusToKKPi'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

Dp2KmKpPip = DecayTreeTuple("DpToKmKpPip")
Dp2KmKpPip.Decay = "[D+ -> ^K- ^K+ ^pi+]CC"
Dp2KmKpPip.Branches = {
    "Kminus"    : "[D+ -> ^K- K+ pi+]CC",
    "Kplus"     : "[D+ -> K- ^K+ pi+]CC",
    "Piplus"    : "[D+ -> K- K+ ^pi+]CC",
    "Dplus"     : "[D+ -> K- K+ pi+]CC",
}
Dp2KmKpPip.TupleName = "DpToKmKpPip"
Dp2KmKpPip.WriteP2PVRelations = False
Dp2KmKpPip.InputPrimaryVertices = tesla_vertex_location
Dp2KmKpPip.Inputs = [ tesla_particle_location ]
Dp2KmKpPip.ToolList +=  tools

##  -----------  D+ --> K-,pi-,pi+,pi+,pi+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDp2KmPimPipPipPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'DplusToKPiPiPiPi'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

Dp2KmPimPipPipPip = DecayTreeTuple("DpToKmPimPipPipPip")
Dp2KmPimPipPipPip.Decay = "[D+ -> ^K- ^pi- ^pi+ ^pi+ ^pi+]CC"
Dp2KmPimPipPipPip.Branches = {
    "Kminus"    : "[D+ -> ^K- pi- pi+ pi+ pi+]CC",
    "Piminus"   : "[D+ -> K- ^pi- pi+ pi+ pi+]CC",
    "Piplus1"   : "[D+ -> K- pi- ^pi+ pi+ pi+]CC",
    "Piplus2"   : "[D+ -> K- pi- pi+ ^pi+ pi+]CC",
    "Piplus3"   : "[D+ -> K- pi- pi+ pi+ ^pi+]CC",
    "Dplus"     : "[D+ -> K- pi- pi+ pi+ pi+]CC",
}
Dp2KmPimPipPipPip.TupleName = "DecayTree"
Dp2KmPimPipPipPip.WriteP2PVRelations = False
Dp2KmPimPipPipPip.InputPrimaryVertices = tesla_vertex_location
Dp2KmPimPipPipPip.Inputs = [ tesla_particle_location ]
Dp2KmPimPipPipPip.ToolList +=  tools

##  -----------  Ds --> K-,K+,pi-,pi+,pi+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDsp2KmKpPimPipPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'DsToKKPiPiPi'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

DspToKmKpPimPipPip = DecayTreeTuple("DspToKmKpPimPipPip")
DspToKmKpPimPipPip.Decay = "[D_s+ -> ^K- ^K+ ^pi- ^pi+ ^pi+]CC"
DspToKmKpPimPipPip.Branches = {
    "Kminus"    : "[D_s+ -> ^K- K+ pi- pi+ pi+]CC",
    "Kplus"     : "[D_s+ -> K- ^K+ pi- pi+ pi+]CC",
    "Piminus"   : "[D_s+ -> K- K+ ^pi- pi+ pi+]CC",
    "Piplus1"   : "[D_s+ -> K- K+ pi- ^pi+ pi+]CC",
    "Piplus2"   : "[D_s+ -> K- K+ pi- pi+ ^pi+]CC",
    "Ds"        : "[D_s+ -> K- K+ pi- pi+ pi+]CC",
}
DspToKmKpPimPipPip.TupleName = "DecayTree"
DspToKmKpPimPipPip.WriteP2PVRelations = False
DspToKmKpPimPipPip.InputPrimaryVertices = tesla_vertex_location
DspToKmKpPimPipPip.Inputs = [ tesla_particle_location ]
DspToKmKpPimPipPip.ToolList +=  tools

## added 151215  mds
##  -----------  Dp --> K-,K+,pi-,pi+,pi+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDp2KmKpPimPipPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'DpToKKPiPiPi'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

DpToKmKpPimPipPip = DecayTreeTuple("DpToKmKpPimPipPip")
DpToKmKpPimPipPip.Decay = "[D+ -> ^K- ^K+ ^pi- ^pi+ ^pi+]CC"
DpToKmKpPimPipPip.Branches = {
    "Kminus"    : "[D+ -> ^K- K+ pi- pi+ pi+]CC",
    "Kplus"     : "[D+ -> K- ^K+ pi- pi+ pi+]CC",
    "Piminus"   : "[D+ -> K- K+ ^pi- pi+ pi+]CC",
    "Piplus1"   : "[D+ -> K- K+ pi- ^pi+ pi+]CC",
    "Piplus2"   : "[D+ -> K- K+ pi- pi+ ^pi+]CC",
    "Dplus"     : "[D+ -> K- K+ pi- pi+ pi+]CC",
}
DpToKmKpPimPipPip.TupleName = "DecayTree"
DpToKmKpPimPipPip.WriteP2PVRelations = False
DpToKmKpPimPipPip.InputPrimaryVertices = tesla_vertex_location
DpToKmKpPimPipPip.Inputs = [ tesla_particle_location ]
DpToKmKpPimPipPip.ToolList +=  tools

## added 151215  mds
##  -----------  Dp --> K-,K-,K+,pi+,pi+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDp2KmKmKpPipPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'DpToKKKPiPi'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

DpToKmKmKpPipPip = DecayTreeTuple("DpToKmKmKpPipPip")
DpToKmKmKpPipPip.Decay = "[D+ -> ^K- ^K- ^K+ ^pi+ ^pi+]CC"
DpToKmKmKpPipPip.Branches = {
    "Kminus1"   : "[D+ -> ^K- K- K+ pi+ pi+]CC",
    "Kminus2"   : "[D+ -> K- ^K- K+ pi+ pi+]CC",
    "Kplus"     : "[D+ -> K- K- ^K+ pi+ pi+]CC",
    "Piplus1"   : "[D+ -> K- K- K+ ^pi+ pi+]CC",
    "Piplus2"   : "[D+ -> K- K- K+ pi+ ^pi+]CC",
    "Dplus"     : "[D+ -> K- K- K+ pi+ pi+]CC",
}
DpToKmKmKpPipPip.TupleName = "DecayTree"
DpToKmKmKpPipPip.WriteP2PVRelations = False
DpToKmKmKpPipPip.InputPrimaryVertices = tesla_vertex_location
DpToKmKmKpPipPip.Inputs = [ tesla_particle_location ]
DpToKmKmKpPipPip.ToolList +=  tools

##  -----------  Lambda_C --> p,K-,K+,pi-,pi+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadLcpToPpKmKpPimPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"

LcpToPpKmKpPimPip = DecayTreeTuple("LcpToPpKmKpPimPip")
LcpToPpKmKpPimPip.Decay = "[Lambda_c+ -> p+ K- K+ pi- pi+]CC"
LcpToPpKmKpPimPip.Branches = {
    "Proton"   : "[Lambda_c+ -> ^p+ K- K+ pi- pi+]CC",
    "Kminus"   : "[Lambda_c+ -> p+ ^K- K+ pi- pi+]CC",
    "Kplus"    : "[Lambda_c+ -> p+ K- ^K+ pi- pi+]CC",
    "Piminus"  : "[Lambda_c+ -> p+ K- K+ ^pi- pi+]CC",
    "Piplus"   : "[Lambda_c+ -> p+ K- K+ pi- ^pi+]CC",
    "LambdaC"  : "[Lambda_c+ -> p+ K- K+ pi- pi+]CC",
}
LcpToPpKmKpPimPip.TupleName = "DecayTree"
LcpToPpKmKpPimPip.WriteP2PVRelations = False
LcpToPpKmKpPimPip.InputPrimaryVertices = tesla_vertex_location
LcpToPpKmKpPimPip.Inputs = [ tesla_particle_location ]
LcpToPpKmKpPimPip.ToolList +=  tools

##  -----------  Lambda_c --> p K- pi+  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadLcpToPpKmPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"

LcpToPpKmPip = DecayTreeTuple("LcpToPpKmPip")
LcpToPpKmPip.Decay = "[Lambda_c+ -> ^K- ^p+ ^pi+]CC"
LcpToPpKmPip.Branches = {
    "Proton"    : "[Lambda_c+ -> K- ^p+ pi+]CC",
    "Kminus"    : "[Lambda_c+ -> ^K- p+ pi+]CC",
    "Piplus"    : "[Lambda_c+ -> K- p+ ^pi+]CC",
    "LambdaC"   : "[Lambda_c+ -> K- p+ pi+]CC",
}
LcpToPpKmPip.TupleName = "LcpToPpKmPip"
LcpToPpKmPip.WriteP2PVRelations = False
LcpToPpKmPip.InputPrimaryVertices = tesla_vertex_location
LcpToPpKmPip.Inputs = [ tesla_particle_location ]
LcpToPpKmPip.ToolList +=  tools


##  -----------  Lambda_c --> Lambda0 pi+  --------
##  start with the Lambda_LL sample
#Locations of tesla
tesla_line = 'Hlt2CharmHadLcp2LamPip_LamLLTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'Lcp2LamPip_LamLL'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

Lcp2LamPip_LamLL = DecayTreeTuple("Lcp2LamPip_LamLL")
Lcp2LamPip_LamLL.Decay = "[Lambda_c+ -> ^pi+ ^(Lambda0 -> ^p+ ^pi-)]CC"
Lcp2LamPip_LamLL.Branches = {
    "Lambda0"     : "[Lambda_c+ -> pi+ ^(Lambda0 -> p+ pi-)]CC",
    "LambdaPr"    : "[Lambda_c+ -> pi+ (Lambda0 -> ^p+ pi-)]CC",
    "LambdaPi"    : "[Lambda_c+ -> pi+ (Lambda0 -> p+ ^pi-)]CC",
    "BachelorPi"  : "[Lambda_c+ -> ^pi+ (Lambda0 -> p+ pi-)]CC",
    "LambdaC"     : "[Lambda_c+ -> pi+ (Lambda0 -> p+ pi-)]CC",
}
Lcp2LamPip_LamLL.TupleName = "Lcp2LamPip_LamLL"
Lcp2LamPip_LamLL.WriteP2PVRelations = False
Lcp2LamPip_LamLL.InputPrimaryVertices = tesla_vertex_location
Lcp2LamPip_LamLL.Inputs = [ tesla_particle_location ]
Lcp2LamPip_LamLL.ToolList +=  tools


##  -----------  Lambda_c --> Lambda0 pi+  --------
##  next, the Lambda_DD sample
#Locations of tesla
tesla_line = 'Hlt2CharmHadLcp2LamPip_LamDDTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'Lcp2LamPip_LamDD'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

Lcp2LamPip_LamDD = DecayTreeTuple("Lcp2LamPip_LamDD")
Lcp2LamPip_LamDD.Decay = "[Lambda_c+ -> ^pi+ ^(Lambda0 -> ^p+ ^pi-)]CC"
Lcp2LamPip_LamDD.Branches = {
    "Lambda0"     : "[Lambda_c+ -> pi+ ^(Lambda0 -> p+ pi-)]CC",
    "LambdaPr"    : "[Lambda_c+ -> pi+ (Lambda0 -> ^p+ pi-)]CC",
    "LambdaPi"    : "[Lambda_c+ -> pi+ (Lambda0 -> p+ ^pi-)]CC",
    "BachelorPi"  : "[Lambda_c+ -> ^pi+ (Lambda0 -> p+ pi-)]CC",
    "LambdaC"     : "[Lambda_c+ -> pi+ (Lambda0 -> p+ pi-)]CC",
}
Lcp2LamPip_LamDD.TupleName = "Lcp2LamPip_LamDD"
Lcp2LamPip_LamDD.WriteP2PVRelations = False
Lcp2LamPip_LamDD.InputPrimaryVertices = tesla_vertex_location
Lcp2LamPip_LamDD.Inputs = [ tesla_particle_location ]
Lcp2LamPip_LamDD.ToolList +=  tools


##  -----------  Pentaquark --> phi,p,pi  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadPentaToPhiPpPimTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'Penta'

Penta = DecayTreeTuple("Penta")
Penta.Decay = "[Xi_c0 -> ^K- ^K+  ^p+ ^pi-]CC"
Penta.Branches = {
    "Kminus"     : "[Xi_c0 -> ^K- K+  p+ pi-]CC",
    "Kplus"      : "[Xi_c0 -> K- ^K+  p+ pi-]CC",
    "Proton"     : "[Xi_c0 -> K- K+  ^p+ pi-]CC",
    "Piminus"    : "[Xi_c0 -> K- K+  p+ ^pi-]CC",
    "Penta"      : "[Xi_c0 -> K- K+  p+ pi-]CC",
}
Penta.TupleName = "DecayTree"
Penta.WriteP2PVRelations = False
Penta.InputPrimaryVertices = tesla_vertex_location
Penta.Inputs = [ tesla_particle_location ]
Penta.ToolList +=  tools


##  -----------  Pentaquark --> phi,p,pi  --------
#Locations of tesla
tesla_line = 'Hlt2CharmHadDp2KmPimPipPipPipTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'DpToK4Pi"'

DpToK4Pi = DecayTreeTuple("DpToK4Pi")
DpToK4Pi.Decay = "[D+ -> ^K- ^pi- ^pi+ ^pi+ ^pi+]CC"
DpToK4Pi.Branches = {
    "Kminus"     : "[D+ -> ^K- pi- pi+ pi+ pi+]CC",
    "Piminus"    : "[D+ -> K- ^pi- pi+ pi+ pi+]CC",
    "Piplus1"    : "[D+ -> K- pi- ^pi+ pi+ pi+]CC",
    "Piplus2"    : "[D+ -> K- pi- pi+ ^pi+ pi+]CC",
    "Piplus3"    : "[D+ -> K- pi- pi+ pi+ ^pi+]CC",
    "Dplus"      : "[D+ -> K- pi- pi+ pi+ pi+]CC",
}
DpToK4Pi.TupleName = "DecayTree"
DpToK4Pi.WriteP2PVRelations = False
DpToK4Pi.InputPrimaryVertices = tesla_vertex_location
DpToK4Pi.Inputs = [ tesla_particle_location ]
DpToK4Pi.ToolList +=  tools



##  -----------  (D+,Lambda)$ (D-,Lambda) "spectroscopy"  --------
##  next, the Lambda_DD sample
#Locations of tesla
tesla_line = 'Hlt2CharmHadSpec_DpLambdaTurbo'
tesla_particle_location = "/Event/Turbo/"+tesla_line+"/Particles"
tesla_vertex_location = "/Event/Turbo/Primary"
name = 'Spec_DpLambda'
gaudiSequence = GaudiSequencer ( name + "ProbNNSeq" )

Spec_DpLambda = DecayTreeTuple("Spec_DpLambda")
Spec_DpLambda.Decay = "[D*(2010)+ -> ^(D+ -> ^K- ^pi+ ^pi+)  ^(Lambda0 -> ^p+ ^pi-) ]CC"
Spec_DpLambda.Branches = {
    "Dplus"       : "[D*(2010)+ -> ^(D+ -> K- pi+ pi+)  (Lambda0 -> p+ pi-) ]CC",
    "Kminus"      : "[D*(2010)+ -> (D+ -> ^K- pi+ pi+)  (Lambda0 -> p+ pi-) ]CC",
    "Piplus1"     : "[D*(2010)+ -> (D+ -> K- ^pi+ pi+)  (Lambda0 -> p+ pi-) ]CC",
    "Piplus2"     : "[D*(2010)+ -> (D+ -> K- pi+ ^pi+)  (Lambda0 -> p+ pi-) ]CC",
    "Lambda0"     : "[D*(2010)+ -> (D+ -> K- pi+ pi+)  ^(Lambda0 -> p+ pi-) ]CC",
    "LambdaPr"    : "[D*(2010)+ -> (D+ -> K- pi+ pi+)  (Lambda0 -> ^p+ pi-) ]CC",
    "LambdaPi"    : "[D*(2010)+ -> (D+ -> K- pi+ pi+)  (Lambda0 -> p+ ^pi-) ]CC",
    "DLambda"     : "[D*(2010)+ -> (D+ -> K- pi+ pi+)  (Lambda0 -> p+ pi-) ]CC",
}
Spec_DpLambda.TupleName = "Spec_DpLambda"
Spec_DpLambda.WriteP2PVRelations = False
Spec_DpLambda.InputPrimaryVertices = tesla_vertex_location
Spec_DpLambda.Inputs = [ tesla_particle_location ]
Spec_DpLambda.ToolList +=  tools

     ##  reading from the same TES bank, look at Dm,Lambda
     ##  as of July 26, 2015 the corresponding trigger line had a mistake
     ##  with the decay descriptor (D_s- rather than D-) so there
     ##  should be no entries


Spec_DmLambda = DecayTreeTuple("Spec_DmLambda")
Spec_DmLambda.Decay = "[D*(2010)- -> ^(D- -> ^K+ ^pi- ^pi-)  ^(Lambda0 -> ^p+ ^pi-) ]CC"
Spec_DmLambda.Branches = {
    "Dminus"     : "[D*(2010)- -> ^(D- -> K+ pi- pi-)  (Lambda0 -> p+ pi-) ]CC",
    "Kplus"      : "[D*(2010)- -> (D- -> ^K+ pi- pi-)  (Lambda0 -> p+ pi-) ]CC",
    "Piminus1"   : "[D*(2010)- -> (D- -> K+ ^pi- pi-)  (Lambda0 -> p+ pi-) ]CC",
    "Piminus2"   : "[D*(2010)- -> (D- -> K+ pi- ^pi-)  (Lambda0 -> p+ pi-) ]CC",
    "Lambda0"    : "[D*(2010)- -> (D- -> K+ pi- pi-)  ^(Lambda0 -> p+ pi-) ]CC",
    "LambdaPr"   : "[D*(2010)- -> (D- -> K+ pi- pi-)  (Lambda0 -> ^p+ pi-) ]CC",
    "LambdaPi"   : "[D*(2010)- -> (D- -> K+ pi- pi-)  (Lambda0 -> p+ ^pi-) ]CC",
    "DmLambda"   : "[D*(2010)- -> (D- -> K+ pi- pi-)  (Lambda0 -> p+ pi-) ]CC",
}   
Spec_DmLambda.TupleName = "Spec_DmLambda"
Spec_DmLambda.WriteP2PVRelations = False
Spec_DmLambda.InputPrimaryVertices = tesla_vertex_location
Spec_DmLambda.Inputs = [ tesla_particle_location ]
Spec_DmLambda.ToolList +=  tools

##   ------------- a tuple of tuple names  ----------

tuples = [ DstpPim, DstpD02KPi, DstpD02KPiPiPi, DstpD02KKKPi,
           DstpD02KKPiPi,
           Dp2KmPipPip, Dp2PimPipPip, Dp2KmKpPip,
           LcpToPpKmPip, Lcp2LamPip_LamLL, Lcp2LamPip_LamDD,
           Spec_DpLambda, Spec_DmLambda,
           Dp2KmPimPipPipPip, DspToKmKpPimPipPip, DpToKmKpPimPipPip,
           DpToKmKmKpPipPip, Penta, LcpToPpKmKpPimPip,
           D0ToKPi_Pip, D0ToKPi_Pim ]

for tuple in tuples:
  tuple.WriteP2PVRelations = False
  tuple.InputPrimaryVertices = "/Event/Turbo/Primary"
  tuple.ToolList += tools
  tuple.addTool(TupleToolDecay, name="Dstar")
  tuple.Dstar.ToolList += [ "TupleToolDecayTreeFitter/DTF" ]
  tuple.Dstar.addTool(TupleToolDecayTreeFitter("DTF"))
  tuple.Dstar.DTF.Verbose = True
  tuple.Dstar.DTF.constrainToOriginVertex = True
  tuple.Dstar.DTF.UpdateDaughters = True
  tuple.addTool(TupleToolTrigger())
  tuple.TupleToolTrigger.TriggerList = triggers
  tuple.TupleToolTrigger.VerboseL0 = True
  tuple.TupleToolTrigger.VerboseHlt1 = True
  tuple.addTool(TupleToolTISTOS())
  tuple.TupleToolTISTOS.TriggerList = triggers
  tuple.TupleToolTISTOS.Verbose = True
  tuple.TupleToolTISTOS.VerboseL0 = True
  tuple.TupleToolTISTOS.VerboseHlt1 = True
  tuple.TupleToolTISTOS.VerboseHlt2 = True

# Necessary DaVinci parameters #################
DaVinci().Simulation   = False
DaVinci().SkipEvents = 0
DaVinci().EvtMax = -1
##DaVinci().EvtMax = 20000
DaVinci().Lumi = True
DaVinci().TupleFile = 'TeslaTuples_Dec15A.root'
DaVinci().PrintFreq = 1000
DaVinci().DataType      = '2015'
DaVinci().UserAlgorithms = [] 
## orig DaVinci().UserAlgorithms += [tuple] 
DaVinci().UserAlgorithms += tuples 
DaVinci().InputType = 'MDST'

from Gaudi.Configuration import *
from GaudiConf import IOHelper

from GaudiConf.IOHelper import IOHelper
##ioh = IOHelper()
##ioh.setupServices()
## mds ioh.inputFiles([
## mds     "/afs/cern.ch/user/m/msokolof/cmtuser/DaVinci_v36r7p4/July10_Turbo_July11B.mdst"
##])
## mdsIOHelper().inputFiles( [
## mds   "root://eoslhcb.cern.ch//eos/lhcb/user/m/msokolof/TeslaFiles/July23_Turbo_July25.mdst"
## mds   ] )
IOHelper().inputFiles( [
   "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/validation/Collision15/TURBO.MDST/00047111/0000//00047111_00000007_1.turbo.mdst"
   ] )
