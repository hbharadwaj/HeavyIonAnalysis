import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import patJetGenJetMatch, patJetPartonMatch
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import patJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi import patJets

from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *

from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak2Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak2CaloJets"),
    matched = cms.InputTag("ak2HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.2
    )

ak2CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak2HiSignalGenJets"),
    matched = cms.InputTag("ak2HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.2
    )

ak2Caloparton = patJetPartonMatch.clone(
    src = cms.InputTag("ak2CaloJets"),
    matched = cms.InputTag("hiSignalGenParticles"))

ak2Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("ak2CaloJets"),
    payload = "AK4PF"
    )

ak2CaloJetID = cms.EDProducer(
    'JetIDProducer',
    JetIDParams,
    src = cms.InputTag('ak2CaloJets'))

# ak2Caloclean = heavyIonCleanedGenJets.clone(
#     src = cms.InputTag('ak2HiSignalGenJets'))

ak2CalobTagger = bTaggers(
    "ak2Calo",
    0.2)

# create objects locally since they dont load properly otherwise
ak2CaloPatJetPartons = ak2CalobTagger.PatJetPartons
ak2CaloJetTracksAssociatorAtVertex = ak2CalobTagger.JetTracksAssociatorAtVertex
ak2CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
ak2CaloSimpleSecondaryVertexHighEffBJetTags = ak2CalobTagger.SimpleSecondaryVertexHighEffBJetTags
ak2CaloSimpleSecondaryVertexHighPurBJetTags = ak2CalobTagger.SimpleSecondaryVertexHighPurBJetTags
ak2CaloCombinedSecondaryVertexBJetTags = ak2CalobTagger.CombinedSecondaryVertexBJetTags
ak2CaloCombinedSecondaryVertexV2BJetTags = ak2CalobTagger.CombinedSecondaryVertexV2BJetTags
ak2CaloJetBProbabilityBJetTags = ak2CalobTagger.JetBProbabilityBJetTags
ak2CaloSoftPFMuonByPtBJetTags = ak2CalobTagger.SoftPFMuonByPtBJetTags
ak2CaloSoftPFMuonByIP3dBJetTags = ak2CalobTagger.SoftPFMuonByIP3dBJetTags
ak2CaloTrackCountingHighEffBJetTags = ak2CalobTagger.TrackCountingHighEffBJetTags
ak2CaloTrackCountingHighPurBJetTags = ak2CalobTagger.TrackCountingHighPurBJetTags

ak2CaloImpactParameterTagInfos = ak2CalobTagger.ImpactParameterTagInfos
ak2CaloImpactParameterTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
ak2CaloJetProbabilityBJetTags = ak2CalobTagger.JetProbabilityBJetTags

ak2CaloSecondaryVertexTagInfos = ak2CalobTagger.SecondaryVertexTagInfos
ak2CaloSimpleSecondaryVertexHighEffBJetTags = ak2CalobTagger.SimpleSecondaryVertexHighEffBJetTags
ak2CaloSimpleSecondaryVertexHighPurBJetTags = ak2CalobTagger.SimpleSecondaryVertexHighPurBJetTags
ak2CaloCombinedSecondaryVertexBJetTags = ak2CalobTagger.CombinedSecondaryVertexBJetTags
ak2CaloCombinedSecondaryVertexV2BJetTags = ak2CalobTagger.CombinedSecondaryVertexV2BJetTags

ak2CaloSecondaryVertexNegativeTagInfos = ak2CalobTagger.SecondaryVertexNegativeTagInfos
ak2CaloNegativeSimpleSecondaryVertexHighEffBJetTags = ak2CalobTagger.NegativeSimpleSecondaryVertexHighEffBJetTags
ak2CaloNegativeSimpleSecondaryVertexHighPurBJetTags = ak2CalobTagger.NegativeSimpleSecondaryVertexHighPurBJetTags
ak2CaloNegativeCombinedSecondaryVertexBJetTags = ak2CalobTagger.NegativeCombinedSecondaryVertexBJetTags
ak2CaloPositiveCombinedSecondaryVertexBJetTags = ak2CalobTagger.PositiveCombinedSecondaryVertexBJetTags
ak2CaloNegativeCombinedSecondaryVertexV2BJetTags = ak2CalobTagger.NegativeCombinedSecondaryVertexV2BJetTags
ak2CaloPositiveCombinedSecondaryVertexV2BJetTags = ak2CalobTagger.PositiveCombinedSecondaryVertexV2BJetTags

ak2CaloSoftPFMuonsTagInfos = ak2CalobTagger.SoftPFMuonsTagInfos
ak2CaloSoftPFMuonsTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
ak2CaloSoftPFMuonBJetTags = ak2CalobTagger.SoftPFMuonBJetTags
ak2CaloSoftPFMuonByIP3dBJetTags = ak2CalobTagger.SoftPFMuonByIP3dBJetTags
ak2CaloSoftPFMuonByPtBJetTags = ak2CalobTagger.SoftPFMuonByPtBJetTags
ak2CaloNegativeSoftPFMuonByPtBJetTags = ak2CalobTagger.NegativeSoftPFMuonByPtBJetTags
ak2CaloPositiveSoftPFMuonByPtBJetTags = ak2CalobTagger.PositiveSoftPFMuonByPtBJetTags
ak2CaloPatJetFlavourAssociation = ak2CalobTagger.PatJetFlavourAssociation
ak2CaloPatJetFlavourId = cms.Sequence(ak2CaloPatJetPartons*ak2CaloPatJetFlavourAssociation)

ak2CaloJetBtaggingIP = cms.Sequence(
    ak2CaloImpactParameterTagInfos *
    ak2CaloTrackCountingHighEffBJetTags +
    ak2CaloTrackCountingHighPurBJetTags +
    ak2CaloJetProbabilityBJetTags +
    ak2CaloJetBProbabilityBJetTags
    )

ak2CaloJetBtaggingSV = cms.Sequence(
    ak2CaloImpactParameterTagInfos *
    ak2CaloSecondaryVertexTagInfos *
    ak2CaloSimpleSecondaryVertexHighEffBJetTags +
    ak2CaloSimpleSecondaryVertexHighPurBJetTags +
    ak2CaloCombinedSecondaryVertexBJetTags +
    ak2CaloCombinedSecondaryVertexV2BJetTags
    )

ak2CaloJetBtaggingNegSV = cms.Sequence(
    ak2CaloImpactParameterTagInfos *
    ak2CaloSecondaryVertexNegativeTagInfos *
    ak2CaloNegativeSimpleSecondaryVertexHighEffBJetTags +
    ak2CaloNegativeSimpleSecondaryVertexHighPurBJetTags +
    ak2CaloNegativeCombinedSecondaryVertexBJetTags +
    ak2CaloPositiveCombinedSecondaryVertexBJetTags +
    ak2CaloNegativeCombinedSecondaryVertexV2BJetTags +
    ak2CaloPositiveCombinedSecondaryVertexV2BJetTags
    )

ak2CaloJetBtaggingMu = cms.Sequence(
    ak2CaloSoftPFMuonsTagInfos *
    ak2CaloSoftPFMuonBJetTags +
    ak2CaloSoftPFMuonByIP3dBJetTags +
    ak2CaloSoftPFMuonByPtBJetTags +
    ak2CaloNegativeSoftPFMuonByPtBJetTags +
    ak2CaloPositiveSoftPFMuonByPtBJetTags
    )

ak2CaloJetBtagging = cms.Sequence(
    ak2CaloJetBtaggingIP
    * ak2CaloJetBtaggingSV
    # * ak2CaloJetBtaggingNegSV
    # * ak2CaloJetBtaggingMu
    )

ak2CalopatJetsWithBtagging = patJets.clone(
    jetSource = cms.InputTag("ak2CaloJets"),
    genJetMatch            = cms.InputTag("ak2Calomatch"),
    genPartonMatch         = cms.InputTag("ak2Caloparton"),
    jetCorrFactorsSource   = cms.VInputTag(cms.InputTag("ak2Calocorr")),
    JetPartonMapSource     = cms.InputTag("ak2CaloPatJetFlavourAssociation"),
    JetFlavourInfoSource   = cms.InputTag("ak2CaloPatJetFlavourAssociation"),
    trackAssociationSource = cms.InputTag("ak2CaloJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour  = False,
    discriminatorSources   = cms.VInputTag(
        cms.InputTag("ak2CaloSimpleSecondaryVertexHighEffBJetTags"),
        cms.InputTag("ak2CaloSimpleSecondaryVertexHighPurBJetTags"),
        cms.InputTag("ak2CaloCombinedSecondaryVertexBJetTags"),
        cms.InputTag("ak2CaloCombinedSecondaryVertexV2BJetTags"),
        cms.InputTag("ak2CaloJetBProbabilityBJetTags"),
        cms.InputTag("ak2CaloJetProbabilityBJetTags"),
        # cms.InputTag("ak2CaloSoftPFMuonByPtBJetTags"),
        # cms.InputTag("ak2CaloSoftPFMuonByIP3dBJetTags"),
        cms.InputTag("ak2CaloTrackCountingHighEffBJetTags"),
        cms.InputTag("ak2CaloTrackCountingHighPurBJetTags"),
        ),
    tagInfoSources = cms.VInputTag(cms.InputTag("ak2CaloImpactParameterTagInfos"),cms.InputTag("ak2CaloSecondaryVertexTagInfos")),
    jetIDMap = cms.InputTag("ak2CaloJetID"),
    addBTagInfo = True,
    addTagInfos = True,
    addDiscriminators = True,
    addAssociatedTracks = True,
    addJetCharge = False,
    addJetID = False,
    getJetMCFlavour = False,
    addGenPartonMatch = False,
    addGenJetMatch = False,
    embedGenJetMatch = False,
    embedGenPartonMatch = False,
    # embedCaloTowers = False,
    # embedPFCandidates = True
    )

ak2CaloNjettiness = Njettiness.clone(
    src = cms.InputTag("ak2CaloJets"),
    R0  = cms.double(0.2)
    )

ak2CalopatJetsWithBtagging.userData.userFloats.src += [
    'ak2CaloNjettiness:tau1',
    'ak2CaloNjettiness:tau2',
    'ak2CaloNjettiness:tau3']

ak2CaloJetAnalyzer = inclusiveJetAnalyzer.clone(
    jetTag = cms.InputTag("ak2CalopatJetsWithBtagging"),
    genjetTag = 'ak2HiSignalGenJets',
    rParam = 0.2,
    matchJets = cms.untracked.bool(False),
    matchTag = 'patJetsWithBtagging',
    pfCandidateLabel = cms.untracked.InputTag('particleFlow'),
    trackTag = cms.InputTag("generalTracks"),
    fillGenJets = False,
    isMC = False,
    doSubEvent = False,
    useHepMC = cms.untracked.bool(False),
    genParticles = cms.untracked.InputTag("genParticles"),
    eventInfoTag = cms.InputTag("generator"),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    bTagJetName = cms.untracked.string("ak2Calo"),
    jetName = cms.untracked.string("ak2Calo"),
    genPtMin = cms.untracked.double(5),
    doTower = cms.untracked.bool(False),
    doSubJets = cms.untracked.bool(False),
    doGenSubJets = cms.untracked.bool(False),
    subjetGenTag = cms.untracked.InputTag("ak2GenJets"),
    doGenTaus = cms.untracked.bool(False),
    genTau1 = cms.InputTag("ak2HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak2HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak2HiGenNjettiness","tau3"),
    doGenSym = cms.untracked.bool(False),
    genSym = cms.InputTag("ak2GenJets","sym"),
    genDroppedBranches = cms.InputTag("ak2GenJets","droppedBranches")
    )

ak2CaloJetSequence_mc = cms.Sequence(
    # ak2Caloclean
    # *
    ak2Calomatch
    # *
    # ak2CalomatchGroomed
    *
    ak2Caloparton
    *
    ak2Calocorr
    # *
    # ak2CaloJetID
    *
     ak2CaloPatJetFlavourId 
    *
    ak2CaloJetTracksAssociatorAtVertex
    *
    ak2CaloJetBtagging
    *
    # No constituents for calo jets in pp. Must be removed for pp calo jets but
    # I'm not sure how to do this transparently (Marta)
    ak2CaloNjettiness
    *
    ak2CalopatJetsWithBtagging
    *
    ak2CaloJetAnalyzer
    )

ak2CaloJetSequence_data = cms.Sequence(
    ak2Calocorr
    *
    # ak2CaloJetID
    # *
    ak2CaloJetTracksAssociatorAtVertex
    *
    ak2CaloJetBtagging
    *
    ak2CaloNjettiness
    *
    ak2CalopatJetsWithBtagging
    *
    ak2CaloJetAnalyzer
    )

ak2CaloJetSequence_mb = cms.Sequence(
    ak2CaloJetSequence_mc)
ak2CaloJetSequence_jec = cms.Sequence(
    ak2CaloJetSequence_mc)

ak2CaloJetSequence = cms.Sequence(
    ak2CaloJetSequence_data)
