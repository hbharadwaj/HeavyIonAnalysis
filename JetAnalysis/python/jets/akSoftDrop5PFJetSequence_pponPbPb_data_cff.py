import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import patJetGenJetMatch, patJetPartonMatch
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import patJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi import patJets

from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *

from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akSoftDrop5PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop5PFJets"),
    matched = cms.InputTag("ak5HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.5
    )

akSoftDrop5PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop5HiSignalGenJets"),
    matched = cms.InputTag("ak5HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.5
    )

akSoftDrop5PFparton = patJetPartonMatch.clone(
    src = cms.InputTag("akSoftDrop5PFJets"),
    matched = cms.InputTag("hiSignalGenParticles"))

akSoftDrop5PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
    levels   = cms.vstring('L2Relative','L2L3Residual'),
    src = cms.InputTag("akSoftDrop5PFJets"),
    payload = "AK5PF"
    )

akSoftDrop5PFJetID = cms.EDProducer(
    'JetIDProducer',
    JetIDParams,
    src = cms.InputTag('akSoftDrop5CaloJets'))

# akSoftDrop5PFclean = heavyIonCleanedGenJets.clone(
#     src = cms.InputTag('ak5HiSignalGenJets'))

akSoftDrop5PFbTagger = bTaggers(
    "akSoftDrop5PF",
    0.5)

# create objects locally since they dont load properly otherwise
akSoftDrop5PFPatJetPartons = akSoftDrop5PFbTagger.PatJetPartons
akSoftDrop5PFJetTracksAssociatorAtVertex = akSoftDrop5PFbTagger.JetTracksAssociatorAtVertex
akSoftDrop5PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akSoftDrop5PFSimpleSecondaryVertexHighEffBJetTags = akSoftDrop5PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop5PFSimpleSecondaryVertexHighPurBJetTags = akSoftDrop5PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop5PFCombinedSecondaryVertexBJetTags = akSoftDrop5PFbTagger.CombinedSecondaryVertexBJetTags
akSoftDrop5PFCombinedSecondaryVertexV2BJetTags = akSoftDrop5PFbTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop5PFJetBProbabilityBJetTags = akSoftDrop5PFbTagger.JetBProbabilityBJetTags
akSoftDrop5PFSoftPFMuonByPtBJetTags = akSoftDrop5PFbTagger.SoftPFMuonByPtBJetTags
akSoftDrop5PFSoftPFMuonByIP3dBJetTags = akSoftDrop5PFbTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop5PFTrackCountingHighEffBJetTags = akSoftDrop5PFbTagger.TrackCountingHighEffBJetTags
akSoftDrop5PFTrackCountingHighPurBJetTags = akSoftDrop5PFbTagger.TrackCountingHighPurBJetTags

akSoftDrop5PFImpactParameterTagInfos = akSoftDrop5PFbTagger.ImpactParameterTagInfos
akSoftDrop5PFImpactParameterTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
akSoftDrop5PFJetProbabilityBJetTags = akSoftDrop5PFbTagger.JetProbabilityBJetTags

akSoftDrop5PFSecondaryVertexTagInfos = akSoftDrop5PFbTagger.SecondaryVertexTagInfos
akSoftDrop5PFSimpleSecondaryVertexHighEffBJetTags = akSoftDrop5PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop5PFSimpleSecondaryVertexHighPurBJetTags = akSoftDrop5PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop5PFCombinedSecondaryVertexBJetTags = akSoftDrop5PFbTagger.CombinedSecondaryVertexBJetTags
akSoftDrop5PFCombinedSecondaryVertexV2BJetTags = akSoftDrop5PFbTagger.CombinedSecondaryVertexV2BJetTags

akSoftDrop5PFSecondaryVertexNegativeTagInfos = akSoftDrop5PFbTagger.SecondaryVertexNegativeTagInfos
akSoftDrop5PFNegativeSimpleSecondaryVertexHighEffBJetTags = akSoftDrop5PFbTagger.NegativeSimpleSecondaryVertexHighEffBJetTags
akSoftDrop5PFNegativeSimpleSecondaryVertexHighPurBJetTags = akSoftDrop5PFbTagger.NegativeSimpleSecondaryVertexHighPurBJetTags
akSoftDrop5PFNegativeCombinedSecondaryVertexBJetTags = akSoftDrop5PFbTagger.NegativeCombinedSecondaryVertexBJetTags
akSoftDrop5PFPositiveCombinedSecondaryVertexBJetTags = akSoftDrop5PFbTagger.PositiveCombinedSecondaryVertexBJetTags
akSoftDrop5PFNegativeCombinedSecondaryVertexV2BJetTags = akSoftDrop5PFbTagger.NegativeCombinedSecondaryVertexV2BJetTags
akSoftDrop5PFPositiveCombinedSecondaryVertexV2BJetTags = akSoftDrop5PFbTagger.PositiveCombinedSecondaryVertexV2BJetTags

akSoftDrop5PFSoftPFMuonsTagInfos = akSoftDrop5PFbTagger.SoftPFMuonsTagInfos
akSoftDrop5PFSoftPFMuonsTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
akSoftDrop5PFSoftPFMuonBJetTags = akSoftDrop5PFbTagger.SoftPFMuonBJetTags
akSoftDrop5PFSoftPFMuonByIP3dBJetTags = akSoftDrop5PFbTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop5PFSoftPFMuonByPtBJetTags = akSoftDrop5PFbTagger.SoftPFMuonByPtBJetTags
akSoftDrop5PFNegativeSoftPFMuonByPtBJetTags = akSoftDrop5PFbTagger.NegativeSoftPFMuonByPtBJetTags
akSoftDrop5PFPositiveSoftPFMuonByPtBJetTags = akSoftDrop5PFbTagger.PositiveSoftPFMuonByPtBJetTags
akSoftDrop5PFPatJetFlavourAssociation = akSoftDrop5PFbTagger.PatJetFlavourAssociation
akSoftDrop5PFPatJetFlavourId = cms.Sequence(akSoftDrop5PFPatJetPartons*akSoftDrop5PFPatJetFlavourAssociation)

akSoftDrop5PFJetBtaggingIP = cms.Sequence(
    akSoftDrop5PFImpactParameterTagInfos *
    akSoftDrop5PFTrackCountingHighEffBJetTags +
    akSoftDrop5PFTrackCountingHighPurBJetTags +
    akSoftDrop5PFJetProbabilityBJetTags +
    akSoftDrop5PFJetBProbabilityBJetTags
    )

akSoftDrop5PFJetBtaggingSV = cms.Sequence(
    akSoftDrop5PFImpactParameterTagInfos *
    akSoftDrop5PFSecondaryVertexTagInfos *
    akSoftDrop5PFSimpleSecondaryVertexHighEffBJetTags +
    akSoftDrop5PFSimpleSecondaryVertexHighPurBJetTags +
    akSoftDrop5PFCombinedSecondaryVertexBJetTags +
    akSoftDrop5PFCombinedSecondaryVertexV2BJetTags
    )

akSoftDrop5PFJetBtaggingNegSV = cms.Sequence(
    akSoftDrop5PFImpactParameterTagInfos *
    akSoftDrop5PFSecondaryVertexNegativeTagInfos *
    akSoftDrop5PFNegativeSimpleSecondaryVertexHighEffBJetTags +
    akSoftDrop5PFNegativeSimpleSecondaryVertexHighPurBJetTags +
    akSoftDrop5PFNegativeCombinedSecondaryVertexBJetTags +
    akSoftDrop5PFPositiveCombinedSecondaryVertexBJetTags +
    akSoftDrop5PFNegativeCombinedSecondaryVertexV2BJetTags +
    akSoftDrop5PFPositiveCombinedSecondaryVertexV2BJetTags
    )

akSoftDrop5PFJetBtaggingMu = cms.Sequence(
    akSoftDrop5PFSoftPFMuonsTagInfos *
    akSoftDrop5PFSoftPFMuonBJetTags +
    akSoftDrop5PFSoftPFMuonByIP3dBJetTags +
    akSoftDrop5PFSoftPFMuonByPtBJetTags +
    akSoftDrop5PFNegativeSoftPFMuonByPtBJetTags +
    akSoftDrop5PFPositiveSoftPFMuonByPtBJetTags
    )

akSoftDrop5PFJetBtagging = cms.Sequence(
    akSoftDrop5PFJetBtaggingIP
    * akSoftDrop5PFJetBtaggingSV
    # * akSoftDrop5PFJetBtaggingNegSV
    # * akSoftDrop5PFJetBtaggingMu
    )

akSoftDrop5PFpatJetsWithBtagging = patJets.clone(
    jetSource = cms.InputTag("akSoftDrop5PFJets"),
    genJetMatch            = cms.InputTag("akSoftDrop5PFmatch"),
    genPartonMatch         = cms.InputTag("akSoftDrop5PFparton"),
    jetCorrFactorsSource   = cms.VInputTag(cms.InputTag("akSoftDrop5PFcorr")),
    JetPartonMapSource     = cms.InputTag("akSoftDrop5PFPatJetFlavourAssociation"),
    JetFlavourInfoSource   = cms.InputTag("akSoftDrop5PFPatJetFlavourAssociation"),
    trackAssociationSource = cms.InputTag("akSoftDrop5PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour  = False,
    discriminatorSources   = cms.VInputTag(
        cms.InputTag("akSoftDrop5PFSimpleSecondaryVertexHighEffBJetTags"),
        cms.InputTag("akSoftDrop5PFSimpleSecondaryVertexHighPurBJetTags"),
        cms.InputTag("akSoftDrop5PFCombinedSecondaryVertexBJetTags"),
        cms.InputTag("akSoftDrop5PFCombinedSecondaryVertexV2BJetTags"),
        cms.InputTag("akSoftDrop5PFJetBProbabilityBJetTags"),
        cms.InputTag("akSoftDrop5PFJetProbabilityBJetTags"),
        # cms.InputTag("akSoftDrop5PFSoftPFMuonByPtBJetTags"),
        # cms.InputTag("akSoftDrop5PFSoftPFMuonByIP3dBJetTags"),
        cms.InputTag("akSoftDrop5PFTrackCountingHighEffBJetTags"),
        cms.InputTag("akSoftDrop5PFTrackCountingHighPurBJetTags"),
        ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akSoftDrop5PFImpactParameterTagInfos"),cms.InputTag("akSoftDrop5PFSecondaryVertexTagInfos")),
    jetIDMap = cms.InputTag("akSoftDrop5PFJetID"),
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

akSoftDrop5PFNjettiness = Njettiness.clone(
    src = cms.InputTag("akSoftDrop5PFJets"),
    R0  = cms.double(0.5)
    )

akSoftDrop5PFpatJetsWithBtagging.userData.userFloats.src += [
    'akSoftDrop5PFNjettiness:tau1',
    'akSoftDrop5PFNjettiness:tau2',
    'akSoftDrop5PFNjettiness:tau3']

akSoftDrop5PFJetAnalyzer = inclusiveJetAnalyzer.clone(
    jetTag = cms.InputTag("akSoftDrop5PFpatJetsWithBtagging"),
    genjetTag = 'ak5HiSignalGenJets',
    rParam = 0.5,
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
    bTagJetName = cms.untracked.string("akSoftDrop5PF"),
    jetName = cms.untracked.string("akSoftDrop5PF"),
    genPtMin = cms.untracked.double(5),
    doTower = cms.untracked.bool(False),
    doSubJets = cms.untracked.bool(True),
    doGenSubJets = cms.untracked.bool(False),
    subjetGenTag = cms.untracked.InputTag("akSoftDrop5GenJets"),
    doGenTaus = cms.untracked.bool(False),
    genTau1 = cms.InputTag("akSoftDrop5HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("akSoftDrop5HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("akSoftDrop5HiGenNjettiness","tau3"),
    doGenSym = cms.untracked.bool(False),
    genSym = cms.InputTag("akSoftDrop5GenJets","sym"),
    genDroppedBranches = cms.InputTag("akSoftDrop5GenJets","droppedBranches")
    )

akSoftDrop5PFJetSequence_mc = cms.Sequence(
    # akSoftDrop5PFclean
    # *
    akSoftDrop5PFmatch
    # *
    # akSoftDrop5PFmatchGroomed
    *
    akSoftDrop5PFparton
    *
    akSoftDrop5PFcorr
    # *
    # akSoftDrop5PFJetID
    *
     akSoftDrop5PFPatJetFlavourId 
    *
    akSoftDrop5PFJetTracksAssociatorAtVertex
    *
    akSoftDrop5PFJetBtagging
    *
    # No constituents for calo jets in pp. Must be removed for pp calo jets but
    # I'm not sure how to do this transparently (Marta)
    akSoftDrop5PFNjettiness
    *
    akSoftDrop5PFpatJetsWithBtagging
    *
    akSoftDrop5PFJetAnalyzer
    )

akSoftDrop5PFJetSequence_data = cms.Sequence(
    akSoftDrop5PFcorr
    *
    # akSoftDrop5PFJetID
    # *
    akSoftDrop5PFJetTracksAssociatorAtVertex
    *
    akSoftDrop5PFJetBtagging
    *
    akSoftDrop5PFNjettiness
    *
    akSoftDrop5PFpatJetsWithBtagging
    *
    akSoftDrop5PFJetAnalyzer
    )

akSoftDrop5PFJetSequence_mb = cms.Sequence(
    akSoftDrop5PFJetSequence_mc)
akSoftDrop5PFJetSequence_jec = cms.Sequence(
    akSoftDrop5PFJetSequence_mc)

akSoftDrop5PFJetSequence = cms.Sequence(
    akSoftDrop5PFJetSequence_data)
akSoftDrop5PFpatJetsWithBtagging.userData.userFloats.src += ['akSoftDrop5PFJets:sym']
akSoftDrop5PFpatJetsWithBtagging.userData.userInts.src += ['akSoftDrop5PFJets:droppedBranches']
