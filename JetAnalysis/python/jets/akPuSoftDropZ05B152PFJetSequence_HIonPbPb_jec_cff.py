import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import patJetGenJetMatch, patJetPartonMatch
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import patJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi import patJets

from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *

from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akPuSoftDropZ05B152PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akPuSoftDropZ05B152PFJets"),
    matched = cms.InputTag("ak2HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.2
    )

akPuSoftDropZ05B152PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDropZ05B152HiSignalGenJets"),
    matched = cms.InputTag("ak2HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.2
    )

akPuSoftDropZ05B152PFparton = patJetPartonMatch.clone(
    src = cms.InputTag("akPuSoftDropZ05B152PFJets"),
    matched = cms.InputTag("hiSignalGenParticles"))

akPuSoftDropZ05B152PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akPuSoftDropZ05B152PFJets"),
    payload = "AKPu2PF_offline"
    )

akPuSoftDropZ05B152PFJetID = cms.EDProducer(
    'JetIDProducer',
    JetIDParams,
    src = cms.InputTag('akPuSoftDropZ05B152CaloJets'))

# akPuSoftDropZ05B152PFclean = heavyIonCleanedGenJets.clone(
#     src = cms.InputTag('ak2HiSignalGenJets'))

akPuSoftDropZ05B152PFbTagger = bTaggers(
    "akPuSoftDropZ05B152PF",
    0.2)

# create objects locally since they dont load properly otherwise
akPuSoftDropZ05B152PFPatJetFlavourAssociationLegacy = akPuSoftDropZ05B152PFbTagger.PatJetFlavourAssociationLegacy
akPuSoftDropZ05B152PFPatJetPartons = akPuSoftDropZ05B152PFbTagger.PatJetPartons
akPuSoftDropZ05B152PFJetTracksAssociatorAtVertex = akPuSoftDropZ05B152PFbTagger.JetTracksAssociatorAtVertex
akPuSoftDropZ05B152PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akPuSoftDropZ05B152PFSimpleSecondaryVertexHighEffBJetTags = akPuSoftDropZ05B152PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akPuSoftDropZ05B152PFSimpleSecondaryVertexHighPurBJetTags = akPuSoftDropZ05B152PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akPuSoftDropZ05B152PFCombinedSecondaryVertexBJetTags = akPuSoftDropZ05B152PFbTagger.CombinedSecondaryVertexBJetTags
akPuSoftDropZ05B152PFCombinedSecondaryVertexV2BJetTags = akPuSoftDropZ05B152PFbTagger.CombinedSecondaryVertexV2BJetTags
akPuSoftDropZ05B152PFJetBProbabilityBJetTags = akPuSoftDropZ05B152PFbTagger.JetBProbabilityBJetTags
akPuSoftDropZ05B152PFSoftPFMuonByPtBJetTags = akPuSoftDropZ05B152PFbTagger.SoftPFMuonByPtBJetTags
akPuSoftDropZ05B152PFSoftPFMuonByIP3dBJetTags = akPuSoftDropZ05B152PFbTagger.SoftPFMuonByIP3dBJetTags
akPuSoftDropZ05B152PFTrackCountingHighEffBJetTags = akPuSoftDropZ05B152PFbTagger.TrackCountingHighEffBJetTags
akPuSoftDropZ05B152PFTrackCountingHighPurBJetTags = akPuSoftDropZ05B152PFbTagger.TrackCountingHighPurBJetTags
akPuSoftDropZ05B152PFPatJetPartonAssociationLegacy = akPuSoftDropZ05B152PFbTagger.PatJetPartonAssociationLegacy
akPuSoftDropZ05B152PFPatJetPartonAssociationLegacy.partons = "signalPartons"

akPuSoftDropZ05B152PFImpactParameterTagInfos = akPuSoftDropZ05B152PFbTagger.ImpactParameterTagInfos
akPuSoftDropZ05B152PFImpactParameterTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
akPuSoftDropZ05B152PFJetProbabilityBJetTags = akPuSoftDropZ05B152PFbTagger.JetProbabilityBJetTags
akPuSoftDropZ05B152PFpfImpactParameterTagInfos = akPuSoftDropZ05B152PFbTagger.pfImpactParameterTagInfos

akPuSoftDropZ05B152PFSecondaryVertexTagInfos = akPuSoftDropZ05B152PFbTagger.SecondaryVertexTagInfos
akPuSoftDropZ05B152PFSimpleSecondaryVertexHighEffBJetTags = akPuSoftDropZ05B152PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akPuSoftDropZ05B152PFSimpleSecondaryVertexHighPurBJetTags = akPuSoftDropZ05B152PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akPuSoftDropZ05B152PFCombinedSecondaryVertexBJetTags = akPuSoftDropZ05B152PFbTagger.CombinedSecondaryVertexBJetTags
akPuSoftDropZ05B152PFCombinedSecondaryVertexV2BJetTags = akPuSoftDropZ05B152PFbTagger.CombinedSecondaryVertexV2BJetTags

akPuSoftDropZ05B152PFSecondaryVertexNegativeTagInfos = akPuSoftDropZ05B152PFbTagger.SecondaryVertexNegativeTagInfos
akPuSoftDropZ05B152PFNegativeSimpleSecondaryVertexHighEffBJetTags = akPuSoftDropZ05B152PFbTagger.NegativeSimpleSecondaryVertexHighEffBJetTags
akPuSoftDropZ05B152PFNegativeSimpleSecondaryVertexHighPurBJetTags = akPuSoftDropZ05B152PFbTagger.NegativeSimpleSecondaryVertexHighPurBJetTags
akPuSoftDropZ05B152PFNegativeCombinedSecondaryVertexBJetTags = akPuSoftDropZ05B152PFbTagger.NegativeCombinedSecondaryVertexBJetTags
akPuSoftDropZ05B152PFPositiveCombinedSecondaryVertexBJetTags = akPuSoftDropZ05B152PFbTagger.PositiveCombinedSecondaryVertexBJetTags
akPuSoftDropZ05B152PFNegativeCombinedSecondaryVertexV2BJetTags = akPuSoftDropZ05B152PFbTagger.NegativeCombinedSecondaryVertexV2BJetTags
akPuSoftDropZ05B152PFPositiveCombinedSecondaryVertexV2BJetTags = akPuSoftDropZ05B152PFbTagger.PositiveCombinedSecondaryVertexV2BJetTags

akPuSoftDropZ05B152PFpfSecondaryVertexTagInfos = akPuSoftDropZ05B152PFbTagger.pfSecondaryVertexTagInfos
akPuSoftDropZ05B152PFpfDeepCSVTagInfos = akPuSoftDropZ05B152PFbTagger.pfDeepCSVTagInfos
akPuSoftDropZ05B152PFpfDeepCSVJetTags = akPuSoftDropZ05B152PFbTagger.pfDeepCSVJetTags

akPuSoftDropZ05B152PFSoftPFMuonsTagInfos = akPuSoftDropZ05B152PFbTagger.SoftPFMuonsTagInfos
akPuSoftDropZ05B152PFSoftPFMuonsTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
akPuSoftDropZ05B152PFSoftPFMuonBJetTags = akPuSoftDropZ05B152PFbTagger.SoftPFMuonBJetTags
akPuSoftDropZ05B152PFSoftPFMuonByIP3dBJetTags = akPuSoftDropZ05B152PFbTagger.SoftPFMuonByIP3dBJetTags
akPuSoftDropZ05B152PFSoftPFMuonByPtBJetTags = akPuSoftDropZ05B152PFbTagger.SoftPFMuonByPtBJetTags
akPuSoftDropZ05B152PFNegativeSoftPFMuonByPtBJetTags = akPuSoftDropZ05B152PFbTagger.NegativeSoftPFMuonByPtBJetTags
akPuSoftDropZ05B152PFPositiveSoftPFMuonByPtBJetTags = akPuSoftDropZ05B152PFbTagger.PositiveSoftPFMuonByPtBJetTags
akPuSoftDropZ05B152PFPatJetFlavourIdLegacy = cms.Sequence(akPuSoftDropZ05B152PFPatJetPartonAssociationLegacy*akPuSoftDropZ05B152PFPatJetFlavourAssociationLegacy)
# Not working with our PU sub, but keep it here for reference
# akPuSoftDropZ05B152PFPatJetFlavourAssociation = akPuSoftDropZ05B152PFbTagger.PatJetFlavourAssociation
# akPuSoftDropZ05B152PFPatJetFlavourId = cms.Sequence(akPuSoftDropZ05B152PFPatJetPartons*akPuSoftDropZ05B152PFPatJetFlavourAssociation)

akPuSoftDropZ05B152PFJetBtaggingIP = cms.Sequence(
    akPuSoftDropZ05B152PFImpactParameterTagInfos *
    akPuSoftDropZ05B152PFTrackCountingHighEffBJetTags +
    akPuSoftDropZ05B152PFTrackCountingHighPurBJetTags +
    akPuSoftDropZ05B152PFJetProbabilityBJetTags +
    akPuSoftDropZ05B152PFJetBProbabilityBJetTags
    )

akPuSoftDropZ05B152PFJetBtaggingSV = cms.Sequence(
    akPuSoftDropZ05B152PFImpactParameterTagInfos *
    akPuSoftDropZ05B152PFSecondaryVertexTagInfos *
    akPuSoftDropZ05B152PFSimpleSecondaryVertexHighEffBJetTags +
    akPuSoftDropZ05B152PFSimpleSecondaryVertexHighPurBJetTags +
    akPuSoftDropZ05B152PFCombinedSecondaryVertexBJetTags +
    akPuSoftDropZ05B152PFCombinedSecondaryVertexV2BJetTags
    )

akPuSoftDropZ05B152PFJetBtaggingNegSV = cms.Sequence(
    akPuSoftDropZ05B152PFImpactParameterTagInfos *
    akPuSoftDropZ05B152PFSecondaryVertexNegativeTagInfos *
    akPuSoftDropZ05B152PFNegativeSimpleSecondaryVertexHighEffBJetTags +
    akPuSoftDropZ05B152PFNegativeSimpleSecondaryVertexHighPurBJetTags +
    akPuSoftDropZ05B152PFNegativeCombinedSecondaryVertexBJetTags +
    akPuSoftDropZ05B152PFPositiveCombinedSecondaryVertexBJetTags +
    akPuSoftDropZ05B152PFNegativeCombinedSecondaryVertexV2BJetTags +
    akPuSoftDropZ05B152PFPositiveCombinedSecondaryVertexV2BJetTags
    )

akPuSoftDropZ05B152PFJetCandBtagging = cms.Sequence(akPuSoftDropZ05B152PFpfImpactParameterTagInfos *
    akPuSoftDropZ05B152PFpfSecondaryVertexTagInfos *
    akPuSoftDropZ05B152PFpfDeepCSVTagInfos *
    akPuSoftDropZ05B152PFpfDeepCSVJetTags
    )

akPuSoftDropZ05B152PFJetBtaggingMu = cms.Sequence(
    akPuSoftDropZ05B152PFSoftPFMuonsTagInfos *
    akPuSoftDropZ05B152PFSoftPFMuonBJetTags +
    akPuSoftDropZ05B152PFSoftPFMuonByIP3dBJetTags +
    akPuSoftDropZ05B152PFSoftPFMuonByPtBJetTags +
    akPuSoftDropZ05B152PFNegativeSoftPFMuonByPtBJetTags +
    akPuSoftDropZ05B152PFPositiveSoftPFMuonByPtBJetTags
    )

akPuSoftDropZ05B152PFJetBtagging = cms.Sequence(
    akPuSoftDropZ05B152PFJetBtaggingIP
    * akPuSoftDropZ05B152PFJetBtaggingSV
    # * akPuSoftDropZ05B152PFJetBtaggingNegSV
    * akPuSoftDropZ05B152PFJetCandBtagging
    # * akPuSoftDropZ05B152PFJetBtaggingMu
    )

akPuSoftDropZ05B152PFpatJetsWithBtagging = patJets.clone(
    jetSource = cms.InputTag("akPuSoftDropZ05B152PFJets"),
    genJetMatch            = cms.InputTag("akPuSoftDropZ05B152PFmatch"),
    genPartonMatch         = cms.InputTag("akPuSoftDropZ05B152PFparton"),
    jetCorrFactorsSource   = cms.VInputTag(cms.InputTag("akPuSoftDropZ05B152PFcorr")),
    JetPartonMapSource     = cms.InputTag("akPuSoftDropZ05B152PFPatJetFlavourAssociationLegacy"),
    JetFlavourInfoSource   = cms.InputTag("akPuSoftDropZ05B152PFPatJetFlavourAssociation"),
    trackAssociationSource = cms.InputTag("akPuSoftDropZ05B152PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour  = True,
    discriminatorSources   = cms.VInputTag(
        cms.InputTag("akPuSoftDropZ05B152PFSimpleSecondaryVertexHighEffBJetTags"),
        cms.InputTag("akPuSoftDropZ05B152PFSimpleSecondaryVertexHighPurBJetTags"),
        cms.InputTag("akPuSoftDropZ05B152PFCombinedSecondaryVertexBJetTags"),
        cms.InputTag("akPuSoftDropZ05B152PFCombinedSecondaryVertexV2BJetTags"),
        cms.InputTag("akPuSoftDropZ05B152PFJetBProbabilityBJetTags"),
        cms.InputTag("akPuSoftDropZ05B152PFJetProbabilityBJetTags"),
        # cms.InputTag("akPuSoftDropZ05B152PFSoftPFMuonByPtBJetTags"),
        # cms.InputTag("akPuSoftDropZ05B152PFSoftPFMuonByIP3dBJetTags"),
        cms.InputTag("akPuSoftDropZ05B152PFTrackCountingHighEffBJetTags"),
        cms.InputTag("akPuSoftDropZ05B152PFTrackCountingHighPurBJetTags"),
        cms.InputTag("akPuSoftDropZ05B152PFpfDeepCSVJetTags:probb"),
        cms.InputTag("akPuSoftDropZ05B152PFpfDeepCSVJetTags:probc"),
        cms.InputTag("akPuSoftDropZ05B152PFpfDeepCSVJetTags:probudsg"),
        cms.InputTag("akPuSoftDropZ05B152PFpfDeepCSVJetTags:probbb"),
        ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akPuSoftDropZ05B152PFImpactParameterTagInfos"),cms.InputTag("akPuSoftDropZ05B152PFSecondaryVertexTagInfos")),
    jetIDMap = cms.InputTag("akPuSoftDropZ05B152PFJetID"),
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

akPuSoftDropZ05B152PFNjettiness = Njettiness.clone(
    src = cms.InputTag("akPuSoftDropZ05B152PFJets"),
    R0  = cms.double(0.2)
    )

akPuSoftDropZ05B152PFpatJetsWithBtagging.userData.userFloats.src += [
    'akPuSoftDropZ05B152PFNjettiness:tau1',
    'akPuSoftDropZ05B152PFNjettiness:tau2',
    'akPuSoftDropZ05B152PFNjettiness:tau3']

akPuSoftDropZ05B152PFJetAnalyzer = inclusiveJetAnalyzer.clone(
    jetTag = cms.InputTag("akPuSoftDropZ05B152PFpatJetsWithBtagging"),
    genjetTag = 'ak2HiSignalGenJets',
    rParam = 0.2,
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
    bTagJetName = cms.untracked.string("akPuSoftDropZ05B152PF"),
    jetName = cms.untracked.string("akPuSoftDropZ05B152PF"),
    genPtMin = cms.untracked.double(5),
    hltTrgResults = cms.untracked.string('TriggerResults::'+'HISIGNAL'),
    doTower = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(True),
    doGenSubJets = cms.untracked.bool(False),
    subjetGenTag = cms.untracked.InputTag("akSoftDropZ05B152GenJets"),
    doGenTaus = cms.untracked.bool(False),
    genTau1 = cms.InputTag("akSoftDropZ05B152HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("akSoftDropZ05B152HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("akSoftDropZ05B152HiGenNjettiness","tau3"),
    doGenSym = cms.untracked.bool(False),
    genSym = cms.InputTag("akSoftDropZ05B152GenJets","sym"),
    genDroppedBranches = cms.InputTag("akSoftDropZ05B152GenJets","droppedBranches")
    )

akPuSoftDropZ05B152PFJetSequence_mc = cms.Sequence(
    # akPuSoftDropZ05B152PFclean
    # *
    akPuSoftDropZ05B152PFmatch
    # *
    # akPuSoftDropZ05B152PFmatchGroomed
    *
    akPuSoftDropZ05B152PFparton
    *
    akPuSoftDropZ05B152PFcorr
    # *
    # akPuSoftDropZ05B152PFJetID
    *
    akPuSoftDropZ05B152PFPatJetFlavourIdLegacy
    # *
    # akPuSoftDropZ05B152PFPatJetFlavourId # Use legacy algo till PU implemented
    *
    akPuSoftDropZ05B152PFJetTracksAssociatorAtVertex
    *
    akPuSoftDropZ05B152PFJetBtagging
    *
    # No constituents for calo jets in pp. Must be removed for pp calo jets but
    # I'm not sure how to do this transparently (Marta)
    akPuSoftDropZ05B152PFNjettiness
    *
    akPuSoftDropZ05B152PFpatJetsWithBtagging
    *
    akPuSoftDropZ05B152PFJetAnalyzer
    )

akPuSoftDropZ05B152PFJetSequence_data = cms.Sequence(
    akPuSoftDropZ05B152PFcorr
    *
    # akPuSoftDropZ05B152PFJetID
    # *
    akPuSoftDropZ05B152PFJetTracksAssociatorAtVertex
    *
    akPuSoftDropZ05B152PFJetBtagging
    *
    akPuSoftDropZ05B152PFNjettiness
    *
    akPuSoftDropZ05B152PFpatJetsWithBtagging
    *
    akPuSoftDropZ05B152PFJetAnalyzer
    )

akPuSoftDropZ05B152PFJetSequence_mb = cms.Sequence(
    akPuSoftDropZ05B152PFJetSequence_mc)
akPuSoftDropZ05B152PFJetSequence_jec = cms.Sequence(
    akPuSoftDropZ05B152PFJetSequence_mc)

akPuSoftDropZ05B152PFJetSequence = cms.Sequence(
    akPuSoftDropZ05B152PFJetSequence_jec)
akPuSoftDropZ05B152PFJetAnalyzer.genPtMin = cms.untracked.double(1)
akPuSoftDropZ05B152PFJetAnalyzer.jetPtMin = cms.double(1)
akPuSoftDropZ05B152PFpatJetsWithBtagging.userData.userFloats.src += ['akPuSoftDropZ05B152PFJets:sym']
akPuSoftDropZ05B152PFpatJetsWithBtagging.userData.userInts.src += ['akPuSoftDropZ05B152PFJets:droppedBranches']
