import FWCore.ParameterSet.Config as cms

from HeavyIonsAnalysis.JetAnalysis.rerecoRho_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoJets_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoTracks_cff import *
from HeavyIonsAnalysis.JetAnalysis.akSubstrPFJets_cfi import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu3CaloJetSequence_pponPbPb_data_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu3PFJetSequence_pponPbPb_data_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs3PFJetSequence_pponPbPb_data_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akFlowPuCs3PFJetSequence_pponPbPb_data_cff import *

from HeavyIonsAnalysis.JetAnalysis.jets.akPu2CaloJetSequence_pponPbPb_data_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu2PFJetSequence_pponPbPb_data_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs2PFJetSequence_pponPbPb_data_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akFlowPuCs2PFJetSequence_pponPbPb_data_cff import *

jetSequence = cms.Sequence(
    rhoSequence +

    highPurityTracks +



    akCs2PFJets +



    akCs2PFJetSequence +

    akCs3PFJets +



    akCs3PFJetSequence 

)
