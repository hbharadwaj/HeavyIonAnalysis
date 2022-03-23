import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import patJetGenJetMatch, patJetPartonMatch
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import patJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi import patJets

from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *

from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akCsSoftDrop3PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akCsSoftDrop3PFJets"),
    matched = cms.InputTag("ak3HiCleanedGenJets"),
    resolveByMatchQuality = cms.bool(True),
    maxDeltaR = 0.3
    )

akCsSoftDrop3PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop3HiGenJets"),
    matched = cms.InputTag("ak3HiCleanedGenJets"),
    resolveByMatchQuality = cms.bool(True),
    maxDeltaR = 0.3
    )

akCsSoftDrop3PFparton = patJetPartonMatch.clone(
    src = cms.InputTag("akCsSoftDrop3PFJets"),
    matched = cms.InputTag("cleanedPartons"))

akCsSoftDrop3PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akCsSoftDrop3PFJets"),
    payload = "AK3PF"
    )

akCsSoftDrop3PFJetID = cms.EDProducer(
    'JetIDProducer',
    JetIDParams,
    src = cms.InputTag('akCsSoftDrop3CaloJets'))

# akCsSoftDrop3PFclean = heavyIonCleanedGenJets.clone(
#     src = cms.InputTag('ak3HiCleanedGenJets'))

akCsSoftDrop3PFbTagger = bTaggers(
    "akCsSoftDrop3PF",
    0.3)

# create objects locally since they dont load properly otherwise
akCsSoftDrop3PFPatJetFlavourAssociationLegacy = akCsSoftDrop3PFbTagger.PatJetFlavourAssociationLegacy
akCsSoftDrop3PFPatJetPartons = akCsSoftDrop3PFbTagger.PatJetPartons
akCsSoftDrop3PFJetTracksAssociatorAtVertex = akCsSoftDrop3PFbTagger.JetTracksAssociatorAtVertex
akCsSoftDrop3PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akCsSoftDrop3PFSimpleSecondaryVertexHighEffBJetTags = akCsSoftDrop3PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akCsSoftDrop3PFSimpleSecondaryVertexHighPurBJetTags = akCsSoftDrop3PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akCsSoftDrop3PFCombinedSecondaryVertexBJetTags = akCsSoftDrop3PFbTagger.CombinedSecondaryVertexBJetTags
akCsSoftDrop3PFCombinedSecondaryVertexV2BJetTags = akCsSoftDrop3PFbTagger.CombinedSecondaryVertexV2BJetTags
akCsSoftDrop3PFJetBProbabilityBJetTags = akCsSoftDrop3PFbTagger.JetBProbabilityBJetTags
akCsSoftDrop3PFSoftPFMuonByPtBJetTags = akCsSoftDrop3PFbTagger.SoftPFMuonByPtBJetTags
akCsSoftDrop3PFSoftPFMuonByIP3dBJetTags = akCsSoftDrop3PFbTagger.SoftPFMuonByIP3dBJetTags
akCsSoftDrop3PFTrackCountingHighEffBJetTags = akCsSoftDrop3PFbTagger.TrackCountingHighEffBJetTags
akCsSoftDrop3PFTrackCountingHighPurBJetTags = akCsSoftDrop3PFbTagger.TrackCountingHighPurBJetTags
akCsSoftDrop3PFPatJetPartonAssociationLegacy = akCsSoftDrop3PFbTagger.PatJetPartonAssociationLegacy
akCsSoftDrop3PFPatJetPartonAssociationLegacy.partons = "myPartons"

akCsSoftDrop3PFImpactParameterTagInfos = akCsSoftDrop3PFbTagger.ImpactParameterTagInfos
akCsSoftDrop3PFImpactParameterTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
akCsSoftDrop3PFJetProbabilityBJetTags = akCsSoftDrop3PFbTagger.JetProbabilityBJetTags
akCsSoftDrop3PFpfImpactParameterTagInfos = akCsSoftDrop3PFbTagger.pfImpactParameterTagInfos

akCsSoftDrop3PFSecondaryVertexTagInfos = akCsSoftDrop3PFbTagger.SecondaryVertexTagInfos
akCsSoftDrop3PFSimpleSecondaryVertexHighEffBJetTags = akCsSoftDrop3PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akCsSoftDrop3PFSimpleSecondaryVertexHighPurBJetTags = akCsSoftDrop3PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akCsSoftDrop3PFCombinedSecondaryVertexBJetTags = akCsSoftDrop3PFbTagger.CombinedSecondaryVertexBJetTags
akCsSoftDrop3PFCombinedSecondaryVertexV2BJetTags = akCsSoftDrop3PFbTagger.CombinedSecondaryVertexV2BJetTags

akCsSoftDrop3PFSecondaryVertexNegativeTagInfos = akCsSoftDrop3PFbTagger.SecondaryVertexNegativeTagInfos
akCsSoftDrop3PFNegativeSimpleSecondaryVertexHighEffBJetTags = akCsSoftDrop3PFbTagger.NegativeSimpleSecondaryVertexHighEffBJetTags
akCsSoftDrop3PFNegativeSimpleSecondaryVertexHighPurBJetTags = akCsSoftDrop3PFbTagger.NegativeSimpleSecondaryVertexHighPurBJetTags
akCsSoftDrop3PFNegativeCombinedSecondaryVertexBJetTags = akCsSoftDrop3PFbTagger.NegativeCombinedSecondaryVertexBJetTags
akCsSoftDrop3PFPositiveCombinedSecondaryVertexBJetTags = akCsSoftDrop3PFbTagger.PositiveCombinedSecondaryVertexBJetTags
akCsSoftDrop3PFNegativeCombinedSecondaryVertexV2BJetTags = akCsSoftDrop3PFbTagger.NegativeCombinedSecondaryVertexV2BJetTags
akCsSoftDrop3PFPositiveCombinedSecondaryVertexV2BJetTags = akCsSoftDrop3PFbTagger.PositiveCombinedSecondaryVertexV2BJetTags

akCsSoftDrop3PFpfSecondaryVertexTagInfos = akCsSoftDrop3PFbTagger.pfSecondaryVertexTagInfos
akCsSoftDrop3PFpfDeepCSVTagInfos = akCsSoftDrop3PFbTagger.pfDeepCSVTagInfos
akCsSoftDrop3PFpfDeepCSVJetTags = akCsSoftDrop3PFbTagger.pfDeepCSVJetTags

akCsSoftDrop3PFSoftPFMuonsTagInfos = akCsSoftDrop3PFbTagger.SoftPFMuonsTagInfos
akCsSoftDrop3PFSoftPFMuonsTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
akCsSoftDrop3PFSoftPFMuonBJetTags = akCsSoftDrop3PFbTagger.SoftPFMuonBJetTags
akCsSoftDrop3PFSoftPFMuonByIP3dBJetTags = akCsSoftDrop3PFbTagger.SoftPFMuonByIP3dBJetTags
akCsSoftDrop3PFSoftPFMuonByPtBJetTags = akCsSoftDrop3PFbTagger.SoftPFMuonByPtBJetTags
akCsSoftDrop3PFNegativeSoftPFMuonByPtBJetTags = akCsSoftDrop3PFbTagger.NegativeSoftPFMuonByPtBJetTags
akCsSoftDrop3PFPositiveSoftPFMuonByPtBJetTags = akCsSoftDrop3PFbTagger.PositiveSoftPFMuonByPtBJetTags
akCsSoftDrop3PFPatJetFlavourIdLegacy = cms.Sequence(akCsSoftDrop3PFPatJetPartonAssociationLegacy*akCsSoftDrop3PFPatJetFlavourAssociationLegacy)
# Not working with our PU sub, but keep it here for reference
# akCsSoftDrop3PFPatJetFlavourAssociation = akCsSoftDrop3PFbTagger.PatJetFlavourAssociation
# akCsSoftDrop3PFPatJetFlavourId = cms.Sequence(akCsSoftDrop3PFPatJetPartons*akCsSoftDrop3PFPatJetFlavourAssociation)

akCsSoftDrop3PFJetBtaggingIP = cms.Sequence(
    akCsSoftDrop3PFImpactParameterTagInfos *
    akCsSoftDrop3PFTrackCountingHighEffBJetTags +
    akCsSoftDrop3PFTrackCountingHighPurBJetTags +
    akCsSoftDrop3PFJetProbabilityBJetTags +
    akCsSoftDrop3PFJetBProbabilityBJetTags
    )

akCsSoftDrop3PFJetBtaggingSV = cms.Sequence(
    akCsSoftDrop3PFImpactParameterTagInfos *
    akCsSoftDrop3PFSecondaryVertexTagInfos *
    akCsSoftDrop3PFSimpleSecondaryVertexHighEffBJetTags +
    akCsSoftDrop3PFSimpleSecondaryVertexHighPurBJetTags +
    akCsSoftDrop3PFCombinedSecondaryVertexBJetTags +
    akCsSoftDrop3PFCombinedSecondaryVertexV2BJetTags
    )

akCsSoftDrop3PFJetBtaggingNegSV = cms.Sequence(
    akCsSoftDrop3PFImpactParameterTagInfos *
    akCsSoftDrop3PFSecondaryVertexNegativeTagInfos *
    akCsSoftDrop3PFNegativeSimpleSecondaryVertexHighEffBJetTags +
    akCsSoftDrop3PFNegativeSimpleSecondaryVertexHighPurBJetTags +
    akCsSoftDrop3PFNegativeCombinedSecondaryVertexBJetTags +
    akCsSoftDrop3PFPositiveCombinedSecondaryVertexBJetTags +
    akCsSoftDrop3PFNegativeCombinedSecondaryVertexV2BJetTags +
    akCsSoftDrop3PFPositiveCombinedSecondaryVertexV2BJetTags
    )

akCsSoftDrop3PFJetCandBtagging = cms.Sequence(akCsSoftDrop3PFpfImpactParameterTagInfos *
    akCsSoftDrop3PFpfSecondaryVertexTagInfos *
    akCsSoftDrop3PFpfDeepCSVTagInfos *
    akCsSoftDrop3PFpfDeepCSVJetTags
    )

akCsSoftDrop3PFJetBtaggingMu = cms.Sequence(
    akCsSoftDrop3PFSoftPFMuonsTagInfos *
    akCsSoftDrop3PFSoftPFMuonBJetTags +
    akCsSoftDrop3PFSoftPFMuonByIP3dBJetTags +
    akCsSoftDrop3PFSoftPFMuonByPtBJetTags +
    akCsSoftDrop3PFNegativeSoftPFMuonByPtBJetTags +
    akCsSoftDrop3PFPositiveSoftPFMuonByPtBJetTags
    )

akCsSoftDrop3PFJetBtagging = cms.Sequence(
    akCsSoftDrop3PFJetBtaggingIP
    * akCsSoftDrop3PFJetBtaggingSV
    # * akCsSoftDrop3PFJetBtaggingNegSV
    * akCsSoftDrop3PFJetCandBtagging
    # * akCsSoftDrop3PFJetBtaggingMu
    )

akCsSoftDrop3PFpatJetsWithBtagging = patJets.clone(
    jetSource = cms.InputTag("akCsSoftDrop3PFJets"),
    genJetMatch            = cms.InputTag("akCsSoftDrop3PFmatch"),
    genPartonMatch         = cms.InputTag("akCsSoftDrop3PFparton"),
    jetCorrFactorsSource   = cms.VInputTag(cms.InputTag("akCsSoftDrop3PFcorr")),
    JetPartonMapSource     = cms.InputTag("akCsSoftDrop3PFPatJetFlavourAssociationLegacy"),
    JetFlavourInfoSource   = cms.InputTag("akCsSoftDrop3PFPatJetFlavourAssociation"),
    trackAssociationSource = cms.InputTag("akCsSoftDrop3PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour  = True,
    discriminatorSources   = cms.VInputTag(
        cms.InputTag("akCsSoftDrop3PFSimpleSecondaryVertexHighEffBJetTags"),
        cms.InputTag("akCsSoftDrop3PFSimpleSecondaryVertexHighPurBJetTags"),
        cms.InputTag("akCsSoftDrop3PFCombinedSecondaryVertexBJetTags"),
        cms.InputTag("akCsSoftDrop3PFCombinedSecondaryVertexV2BJetTags"),
        cms.InputTag("akCsSoftDrop3PFJetBProbabilityBJetTags"),
        cms.InputTag("akCsSoftDrop3PFJetProbabilityBJetTags"),
        # cms.InputTag("akCsSoftDrop3PFSoftPFMuonByPtBJetTags"),
        # cms.InputTag("akCsSoftDrop3PFSoftPFMuonByIP3dBJetTags"),
        cms.InputTag("akCsSoftDrop3PFTrackCountingHighEffBJetTags"),
        cms.InputTag("akCsSoftDrop3PFTrackCountingHighPurBJetTags"),
        cms.InputTag("akCsSoftDrop3PFpfDeepCSVJetTags:probb"),
        cms.InputTag("akCsSoftDrop3PFpfDeepCSVJetTags:probc"),
        cms.InputTag("akCsSoftDrop3PFpfDeepCSVJetTags:probudsg"),
        cms.InputTag("akCsSoftDrop3PFpfDeepCSVJetTags:probbb"),
        ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akCsSoftDrop3PFImpactParameterTagInfos"),cms.InputTag("akCsSoftDrop3PFSecondaryVertexTagInfos")),
    jetIDMap = cms.InputTag("akCsSoftDrop3PFJetID"),
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

akCsSoftDrop3PFNjettiness = Njettiness.clone(
    src = cms.InputTag("akCsSoftDrop3PFJets"),
    R0  = cms.double(0.3)
    )

akCsSoftDrop3PFpatJetsWithBtagging.userData.userFloats.src += [
    'akCsSoftDrop3PFNjettiness:tau1',
    'akCsSoftDrop3PFNjettiness:tau2',
    'akCsSoftDrop3PFNjettiness:tau3']

akCsSoftDrop3PFJetAnalyzer = inclusiveJetAnalyzer.clone(
    jetTag = cms.InputTag("akCsSoftDrop3PFpatJetsWithBtagging"),
    genjetTag = 'ak3HiGenJets',
    rParam = 0.3,
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
    doLifeTimeCandidateTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    bTagJetName = cms.untracked.string("akCsSoftDrop3PF"),
    jetName = cms.untracked.string("akCsSoftDrop3PF"),
    genPtMin = cms.untracked.double(5),
    hltTrgResults = cms.untracked.string('TriggerResults::'+'HISIGNAL'),
    doTower = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(True),
    doGenSubJets = cms.untracked.bool(False),
    subjetGenTag = cms.untracked.InputTag("akSoftDrop3GenJets"),
    doGenTaus = cms.untracked.bool(False),
    genTau1 = cms.InputTag("akSoftDrop3HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("akSoftDrop3HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("akSoftDrop3HiGenNjettiness","tau3"),
    doGenSym = cms.untracked.bool(False),
    genSym = cms.InputTag("akSoftDrop3GenJets","sym"),
    genDroppedBranches = cms.InputTag("akSoftDrop3GenJets","droppedBranches")
    )

akCsSoftDrop3PFJetSequence_mc = cms.Sequence(
    # akCsSoftDrop3PFclean
    # *
    akCsSoftDrop3PFmatch
    # *
    # akCsSoftDrop3PFmatchGroomed
    *
    akCsSoftDrop3PFparton
    *
    akCsSoftDrop3PFcorr
    # *
    # akCsSoftDrop3PFJetID
    *
    akCsSoftDrop3PFPatJetFlavourIdLegacy
    # *
    # akCsSoftDrop3PFPatJetFlavourId # Use legacy algo till PU implemented
    *
    akCsSoftDrop3PFJetTracksAssociatorAtVertex
    *
    akCsSoftDrop3PFJetBtagging
    *
    # No constituents for calo jets in pp. Must be removed for pp calo jets but
    # I'm not sure how to do this transparently (Marta)
    akCsSoftDrop3PFNjettiness
    *
    akCsSoftDrop3PFpatJetsWithBtagging
    *
    akCsSoftDrop3PFJetAnalyzer
    )

akCsSoftDrop3PFJetSequence_data = cms.Sequence(
    akCsSoftDrop3PFcorr
    *
    # akCsSoftDrop3PFJetID
    # *
    akCsSoftDrop3PFJetTracksAssociatorAtVertex
    *
    akCsSoftDrop3PFJetBtagging
    *
    akCsSoftDrop3PFNjettiness
    *
    akCsSoftDrop3PFpatJetsWithBtagging
    *
    akCsSoftDrop3PFJetAnalyzer
    )

akCsSoftDrop3PFJetSequence_mb = cms.Sequence(
    akCsSoftDrop3PFJetSequence_mc)
akCsSoftDrop3PFJetSequence_jec = cms.Sequence(
    akCsSoftDrop3PFJetSequence_mc)

akCsSoftDrop3PFJetSequence = cms.Sequence(
    akCsSoftDrop3PFJetSequence_mb)
akCsSoftDrop3PFpatJetsWithBtagging.userData.userFloats.src += ['akCsSoftDrop3PFJets:sym']
akCsSoftDrop3PFpatJetsWithBtagging.userData.userInts.src += ['akCsSoftDrop3PFJets:droppedBranches']
