import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import patJetGenJetMatch, patJetPartonMatch
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import patJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi import patJets

from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *

from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak6Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak6CaloJets"),
    matched = cms.InputTag("ak6HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.6
    )

ak6CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak6HiSignalGenJets"),
    matched = cms.InputTag("ak6HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.6
    )

ak6Caloparton = patJetPartonMatch.clone(
    src = cms.InputTag("ak6CaloJets"),
    matched = cms.InputTag("hiSignalGenParticles"))

ak6Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("ak6CaloJets"),
    payload = "AK4PF"
    )

ak6CaloJetID = cms.EDProducer(
    'JetIDProducer',
    JetIDParams,
    src = cms.InputTag('ak6CaloJets'))

# ak6Caloclean = heavyIonCleanedGenJets.clone(
#     src = cms.InputTag('ak6HiSignalGenJets'))

ak6CalobTagger = bTaggers(
    "ak6Calo",
    0.6)

# create objects locally since they dont load properly otherwise
ak6CaloPatJetPartons = ak6CalobTagger.PatJetPartons
ak6CaloJetTracksAssociatorAtVertex = ak6CalobTagger.JetTracksAssociatorAtVertex
ak6CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
ak6CaloSimpleSecondaryVertexHighEffBJetTags = ak6CalobTagger.SimpleSecondaryVertexHighEffBJetTags
ak6CaloSimpleSecondaryVertexHighPurBJetTags = ak6CalobTagger.SimpleSecondaryVertexHighPurBJetTags
ak6CaloCombinedSecondaryVertexBJetTags = ak6CalobTagger.CombinedSecondaryVertexBJetTags
ak6CaloCombinedSecondaryVertexV2BJetTags = ak6CalobTagger.CombinedSecondaryVertexV2BJetTags
ak6CaloJetBProbabilityBJetTags = ak6CalobTagger.JetBProbabilityBJetTags
ak6CaloSoftPFMuonByPtBJetTags = ak6CalobTagger.SoftPFMuonByPtBJetTags
ak6CaloSoftPFMuonByIP3dBJetTags = ak6CalobTagger.SoftPFMuonByIP3dBJetTags
ak6CaloTrackCountingHighEffBJetTags = ak6CalobTagger.TrackCountingHighEffBJetTags
ak6CaloTrackCountingHighPurBJetTags = ak6CalobTagger.TrackCountingHighPurBJetTags

ak6CaloImpactParameterTagInfos = ak6CalobTagger.ImpactParameterTagInfos
ak6CaloImpactParameterTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
ak6CaloJetProbabilityBJetTags = ak6CalobTagger.JetProbabilityBJetTags

ak6CaloSecondaryVertexTagInfos = ak6CalobTagger.SecondaryVertexTagInfos
ak6CaloSimpleSecondaryVertexHighEffBJetTags = ak6CalobTagger.SimpleSecondaryVertexHighEffBJetTags
ak6CaloSimpleSecondaryVertexHighPurBJetTags = ak6CalobTagger.SimpleSecondaryVertexHighPurBJetTags
ak6CaloCombinedSecondaryVertexBJetTags = ak6CalobTagger.CombinedSecondaryVertexBJetTags
ak6CaloCombinedSecondaryVertexV2BJetTags = ak6CalobTagger.CombinedSecondaryVertexV2BJetTags

ak6CaloSecondaryVertexNegativeTagInfos = ak6CalobTagger.SecondaryVertexNegativeTagInfos
ak6CaloNegativeSimpleSecondaryVertexHighEffBJetTags = ak6CalobTagger.NegativeSimpleSecondaryVertexHighEffBJetTags
ak6CaloNegativeSimpleSecondaryVertexHighPurBJetTags = ak6CalobTagger.NegativeSimpleSecondaryVertexHighPurBJetTags
ak6CaloNegativeCombinedSecondaryVertexBJetTags = ak6CalobTagger.NegativeCombinedSecondaryVertexBJetTags
ak6CaloPositiveCombinedSecondaryVertexBJetTags = ak6CalobTagger.PositiveCombinedSecondaryVertexBJetTags
ak6CaloNegativeCombinedSecondaryVertexV2BJetTags = ak6CalobTagger.NegativeCombinedSecondaryVertexV2BJetTags
ak6CaloPositiveCombinedSecondaryVertexV2BJetTags = ak6CalobTagger.PositiveCombinedSecondaryVertexV2BJetTags

ak6CaloSoftPFMuonsTagInfos = ak6CalobTagger.SoftPFMuonsTagInfos
ak6CaloSoftPFMuonsTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
ak6CaloSoftPFMuonBJetTags = ak6CalobTagger.SoftPFMuonBJetTags
ak6CaloSoftPFMuonByIP3dBJetTags = ak6CalobTagger.SoftPFMuonByIP3dBJetTags
ak6CaloSoftPFMuonByPtBJetTags = ak6CalobTagger.SoftPFMuonByPtBJetTags
ak6CaloNegativeSoftPFMuonByPtBJetTags = ak6CalobTagger.NegativeSoftPFMuonByPtBJetTags
ak6CaloPositiveSoftPFMuonByPtBJetTags = ak6CalobTagger.PositiveSoftPFMuonByPtBJetTags
ak6CaloPatJetFlavourAssociation = ak6CalobTagger.PatJetFlavourAssociation
ak6CaloPatJetFlavourId = cms.Sequence(ak6CaloPatJetPartons*ak6CaloPatJetFlavourAssociation)

ak6CaloJetBtaggingIP = cms.Sequence(
    ak6CaloImpactParameterTagInfos *
    ak6CaloTrackCountingHighEffBJetTags +
    ak6CaloTrackCountingHighPurBJetTags +
    ak6CaloJetProbabilityBJetTags +
    ak6CaloJetBProbabilityBJetTags
    )

ak6CaloJetBtaggingSV = cms.Sequence(
    ak6CaloImpactParameterTagInfos *
    ak6CaloSecondaryVertexTagInfos *
    ak6CaloSimpleSecondaryVertexHighEffBJetTags +
    ak6CaloSimpleSecondaryVertexHighPurBJetTags +
    ak6CaloCombinedSecondaryVertexBJetTags +
    ak6CaloCombinedSecondaryVertexV2BJetTags
    )

ak6CaloJetBtaggingNegSV = cms.Sequence(
    ak6CaloImpactParameterTagInfos *
    ak6CaloSecondaryVertexNegativeTagInfos *
    ak6CaloNegativeSimpleSecondaryVertexHighEffBJetTags +
    ak6CaloNegativeSimpleSecondaryVertexHighPurBJetTags +
    ak6CaloNegativeCombinedSecondaryVertexBJetTags +
    ak6CaloPositiveCombinedSecondaryVertexBJetTags +
    ak6CaloNegativeCombinedSecondaryVertexV2BJetTags +
    ak6CaloPositiveCombinedSecondaryVertexV2BJetTags
    )

ak6CaloJetBtaggingMu = cms.Sequence(
    ak6CaloSoftPFMuonsTagInfos *
    ak6CaloSoftPFMuonBJetTags +
    ak6CaloSoftPFMuonByIP3dBJetTags +
    ak6CaloSoftPFMuonByPtBJetTags +
    ak6CaloNegativeSoftPFMuonByPtBJetTags +
    ak6CaloPositiveSoftPFMuonByPtBJetTags
    )

ak6CaloJetBtagging = cms.Sequence(
    ak6CaloJetBtaggingIP
    * ak6CaloJetBtaggingSV
    # * ak6CaloJetBtaggingNegSV
    # * ak6CaloJetBtaggingMu
    )

ak6CalopatJetsWithBtagging = patJets.clone(
    jetSource = cms.InputTag("ak6CaloJets"),
    genJetMatch            = cms.InputTag("ak6Calomatch"),
    genPartonMatch         = cms.InputTag("ak6Caloparton"),
    jetCorrFactorsSource   = cms.VInputTag(cms.InputTag("ak6Calocorr")),
    JetPartonMapSource     = cms.InputTag("ak6CaloPatJetFlavourAssociation"),
    JetFlavourInfoSource   = cms.InputTag("ak6CaloPatJetFlavourAssociation"),
    trackAssociationSource = cms.InputTag("ak6CaloJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour  = False,
    discriminatorSources   = cms.VInputTag(
        cms.InputTag("ak6CaloSimpleSecondaryVertexHighEffBJetTags"),
        cms.InputTag("ak6CaloSimpleSecondaryVertexHighPurBJetTags"),
        cms.InputTag("ak6CaloCombinedSecondaryVertexBJetTags"),
        cms.InputTag("ak6CaloCombinedSecondaryVertexV2BJetTags"),
        cms.InputTag("ak6CaloJetBProbabilityBJetTags"),
        cms.InputTag("ak6CaloJetProbabilityBJetTags"),
        # cms.InputTag("ak6CaloSoftPFMuonByPtBJetTags"),
        # cms.InputTag("ak6CaloSoftPFMuonByIP3dBJetTags"),
        cms.InputTag("ak6CaloTrackCountingHighEffBJetTags"),
        cms.InputTag("ak6CaloTrackCountingHighPurBJetTags"),
        ),
    tagInfoSources = cms.VInputTag(cms.InputTag("ak6CaloImpactParameterTagInfos"),cms.InputTag("ak6CaloSecondaryVertexTagInfos")),
    jetIDMap = cms.InputTag("ak6CaloJetID"),
    addBTagInfo = True,
    addTagInfos = True,
    addDiscriminators = True,
    addAssociatedTracks = True,
    addJetCharge = False,
    addJetID = False,
    getJetMCFlavour = True,
    addGenPartonMatch = True,
    addGenJetMatch = True,
    embedGenJetMatch = True,
    embedGenPartonMatch = True,
    # embedCaloTowers = False,
    # embedPFCandidates = True
    )

ak6CaloNjettiness = Njettiness.clone(
    src = cms.InputTag("ak6CaloJets"),
    R0  = cms.double(0.6)
    )

ak6CalopatJetsWithBtagging.userData.userFloats.src += [
    'ak6CaloNjettiness:tau1',
    'ak6CaloNjettiness:tau2',
    'ak6CaloNjettiness:tau3']

ak6CaloJetAnalyzer = inclusiveJetAnalyzer.clone(
    jetTag = cms.InputTag("ak6CalopatJetsWithBtagging"),
    genjetTag = 'ak6HiSignalGenJets',
    rParam = 0.6,
    matchJets = cms.untracked.bool(False),
    matchTag = 'patJetsWithBtagging',
    pfCandidateLabel = cms.untracked.InputTag('particleFlowTmp'),
    trackTag = cms.InputTag("hiGeneralTracks"),
    fillGenJets = True,
    isMC = True,
    doSubEvent = True,
    useHepMC = cms.untracked.bool(False),
    genParticles = cms.untracked.InputTag("genParticles"),
    eventInfoTag = cms.InputTag("generator"),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    bTagJetName = cms.untracked.string("ak6Calo"),
    jetName = cms.untracked.string("ak6Calo"),
    genPtMin = cms.untracked.double(5),
    doTower = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doGenSubJets = cms.untracked.bool(False),
    subjetGenTag = cms.untracked.InputTag("ak6GenJets"),
    doGenTaus = cms.untracked.bool(False),
    genTau1 = cms.InputTag("ak6HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak6HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak6HiGenNjettiness","tau3"),
    doGenSym = cms.untracked.bool(False),
    genSym = cms.InputTag("ak6GenJets","sym"),
    genDroppedBranches = cms.InputTag("ak6GenJets","droppedBranches")
    )

ak6CaloJetSequence_mc = cms.Sequence(
    # ak6Caloclean
    # *
    ak6Calomatch
    # *
    # ak6CalomatchGroomed
    *
    ak6Caloparton
    *
    ak6Calocorr
    # *
    # ak6CaloJetID
    *
     ak6CaloPatJetFlavourId 
    *
    ak6CaloJetTracksAssociatorAtVertex
    *
    ak6CaloJetBtagging
    *
    # No constituents for calo jets in pp. Must be removed for pp calo jets but
    # I'm not sure how to do this transparently (Marta)
    ak6CaloNjettiness
    *
    ak6CalopatJetsWithBtagging
    *
    ak6CaloJetAnalyzer
    )

ak6CaloJetSequence_data = cms.Sequence(
    ak6Calocorr
    *
    # ak6CaloJetID
    # *
    ak6CaloJetTracksAssociatorAtVertex
    *
    ak6CaloJetBtagging
    *
    ak6CaloNjettiness
    *
    ak6CalopatJetsWithBtagging
    *
    ak6CaloJetAnalyzer
    )

ak6CaloJetSequence_mb = cms.Sequence(
    ak6CaloJetSequence_mc)
ak6CaloJetSequence_jec = cms.Sequence(
    ak6CaloJetSequence_mc)

ak6CaloJetSequence = cms.Sequence(
    ak6CaloJetSequence_mc)
