import FWCore.ParameterSet.Config as cms

from HeavyIonsAnalysis.JetAnalysis.rerecoGen_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoRho_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoJets_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoTracks_cff import *
from HeavyIonsAnalysis.JetAnalysis.akSubstrPFJets_cfi import *
from HeavyIonsAnalysis.JetAnalysis.akGenJets_cfi import *

from HeavyIonsAnalysis.JetAnalysis.jets.akPu3CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.ak3PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu3PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs3PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akFlowPuCs3PFJetSequence_pponPbPb_mc_cff import *

from HeavyIonsAnalysis.JetAnalysis.jets.akPu4CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.ak4PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu4PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs4PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs2PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akFlowPuCs4PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCsSoftDrop4PFJetSequence_pponPbPb_mc_cff import *
genSignalSequence = cms.Sequence(
    genParticlesForJets +

    hiSignalGenParticles +
    genParticlesForJetsSignal +

    ak2HiGenJets +
    ak3HiGenJets +
    ak4HiGenJets +
    
    signalPartons +

    ak2HiSignalGenJets +
    ak3HiSignalGenJets +
    ak4HiSignalGenJets +


    ak2HiGenNjettiness +
    ak3HiGenNjettiness +
    ak4HiGenNjettiness
)

genCleanedSequence = cms.Sequence(
    genParticlesForJets +

    ak2HiGenJets +
    ak3HiGenJets +
    ak4HiGenJets +

    myPartons +
    cleanedPartons +

    ak2HiCleanedGenJets +
    ak3HiCleanedGenJets +
    ak4HiCleanedGenJets
)

jetSequence = cms.Sequence(
    rhoSequence +
    highPurityTracks +
    akCs2PFJets +
    akCs2PFJetSequence +
    
    akCs3PFJets +
    akCs3PFJetSequence +

    akCs4PFJets +
    akCs4PFJetSequence  

)
