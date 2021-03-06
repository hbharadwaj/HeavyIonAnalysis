import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import patJetGenJetMatch, patJetPartonMatch
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import patJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi import patJets

from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *

from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak1PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak1PFJets"),
    matched = cms.InputTag("ak1HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

ak1PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak1HiSignalGenJets"),
    matched = cms.InputTag("ak1HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

ak1PFparton = patJetPartonMatch.clone(
    src = cms.InputTag("ak1PFJets"),
    matched = cms.InputTag("hiSignalGenParticles"))

ak1PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("ak1PFJets"),
    payload = "AK1PF"
    )

ak1PFJetID = cms.EDProducer(
    'JetIDProducer',
    JetIDParams,
    src = cms.InputTag('ak1CaloJets'))

# ak1PFclean = heavyIonCleanedGenJets.clone(
#     src = cms.InputTag('ak1HiSignalGenJets'))

ak1PFbTagger = bTaggers(
    "ak1PF",
    0.1)

# create objects locally since they dont load properly otherwise
ak1PFPatJetPartons = ak1PFbTagger.PatJetPartons
ak1PFJetTracksAssociatorAtVertex = ak1PFbTagger.JetTracksAssociatorAtVertex
ak1PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
ak1PFSimpleSecondaryVertexHighEffBJetTags = ak1PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak1PFSimpleSecondaryVertexHighPurBJetTags = ak1PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak1PFCombinedSecondaryVertexBJetTags = ak1PFbTagger.CombinedSecondaryVertexBJetTags
ak1PFCombinedSecondaryVertexV2BJetTags = ak1PFbTagger.CombinedSecondaryVertexV2BJetTags
ak1PFJetBProbabilityBJetTags = ak1PFbTagger.JetBProbabilityBJetTags
ak1PFSoftPFMuonByPtBJetTags = ak1PFbTagger.SoftPFMuonByPtBJetTags
ak1PFSoftPFMuonByIP3dBJetTags = ak1PFbTagger.SoftPFMuonByIP3dBJetTags
ak1PFTrackCountingHighEffBJetTags = ak1PFbTagger.TrackCountingHighEffBJetTags
ak1PFTrackCountingHighPurBJetTags = ak1PFbTagger.TrackCountingHighPurBJetTags

ak1PFImpactParameterTagInfos = ak1PFbTagger.ImpactParameterTagInfos
ak1PFImpactParameterTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
ak1PFJetProbabilityBJetTags = ak1PFbTagger.JetProbabilityBJetTags

ak1PFSecondaryVertexTagInfos = ak1PFbTagger.SecondaryVertexTagInfos
ak1PFSimpleSecondaryVertexHighEffBJetTags = ak1PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak1PFSimpleSecondaryVertexHighPurBJetTags = ak1PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak1PFCombinedSecondaryVertexBJetTags = ak1PFbTagger.CombinedSecondaryVertexBJetTags
ak1PFCombinedSecondaryVertexV2BJetTags = ak1PFbTagger.CombinedSecondaryVertexV2BJetTags

ak1PFSecondaryVertexNegativeTagInfos = ak1PFbTagger.SecondaryVertexNegativeTagInfos
ak1PFNegativeSimpleSecondaryVertexHighEffBJetTags = ak1PFbTagger.NegativeSimpleSecondaryVertexHighEffBJetTags
ak1PFNegativeSimpleSecondaryVertexHighPurBJetTags = ak1PFbTagger.NegativeSimpleSecondaryVertexHighPurBJetTags
ak1PFNegativeCombinedSecondaryVertexBJetTags = ak1PFbTagger.NegativeCombinedSecondaryVertexBJetTags
ak1PFPositiveCombinedSecondaryVertexBJetTags = ak1PFbTagger.PositiveCombinedSecondaryVertexBJetTags
ak1PFNegativeCombinedSecondaryVertexV2BJetTags = ak1PFbTagger.NegativeCombinedSecondaryVertexV2BJetTags
ak1PFPositiveCombinedSecondaryVertexV2BJetTags = ak1PFbTagger.PositiveCombinedSecondaryVertexV2BJetTags

ak1PFSoftPFMuonsTagInfos = ak1PFbTagger.SoftPFMuonsTagInfos
ak1PFSoftPFMuonsTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
ak1PFSoftPFMuonBJetTags = ak1PFbTagger.SoftPFMuonBJetTags
ak1PFSoftPFMuonByIP3dBJetTags = ak1PFbTagger.SoftPFMuonByIP3dBJetTags
ak1PFSoftPFMuonByPtBJetTags = ak1PFbTagger.SoftPFMuonByPtBJetTags
ak1PFNegativeSoftPFMuonByPtBJetTags = ak1PFbTagger.NegativeSoftPFMuonByPtBJetTags
ak1PFPositiveSoftPFMuonByPtBJetTags = ak1PFbTagger.PositiveSoftPFMuonByPtBJetTags
ak1PFPatJetFlavourAssociation = ak1PFbTagger.PatJetFlavourAssociation
ak1PFPatJetFlavourId = cms.Sequence(ak1PFPatJetPartons*ak1PFPatJetFlavourAssociation)

ak1PFJetBtaggingIP = cms.Sequence(
    ak1PFImpactParameterTagInfos *
    ak1PFTrackCountingHighEffBJetTags +
    ak1PFTrackCountingHighPurBJetTags +
    ak1PFJetProbabilityBJetTags +
    ak1PFJetBProbabilityBJetTags
    )

ak1PFJetBtaggingSV = cms.Sequence(
    ak1PFImpactParameterTagInfos *
    ak1PFSecondaryVertexTagInfos *
    ak1PFSimpleSecondaryVertexHighEffBJetTags +
    ak1PFSimpleSecondaryVertexHighPurBJetTags +
    ak1PFCombinedSecondaryVertexBJetTags +
    ak1PFCombinedSecondaryVertexV2BJetTags
    )

ak1PFJetBtaggingNegSV = cms.Sequence(
    ak1PFImpactParameterTagInfos *
    ak1PFSecondaryVertexNegativeTagInfos *
    ak1PFNegativeSimpleSecondaryVertexHighEffBJetTags +
    ak1PFNegativeSimpleSecondaryVertexHighPurBJetTags +
    ak1PFNegativeCombinedSecondaryVertexBJetTags +
    ak1PFPositiveCombinedSecondaryVertexBJetTags +
    ak1PFNegativeCombinedSecondaryVertexV2BJetTags +
    ak1PFPositiveCombinedSecondaryVertexV2BJetTags
    )

ak1PFJetBtaggingMu = cms.Sequence(
    ak1PFSoftPFMuonsTagInfos *
    ak1PFSoftPFMuonBJetTags +
    ak1PFSoftPFMuonByIP3dBJetTags +
    ak1PFSoftPFMuonByPtBJetTags +
    ak1PFNegativeSoftPFMuonByPtBJetTags +
    ak1PFPositiveSoftPFMuonByPtBJetTags
    )

ak1PFJetBtagging = cms.Sequence(
    ak1PFJetBtaggingIP
    * ak1PFJetBtaggingSV
    # * ak1PFJetBtaggingNegSV
    # * ak1PFJetBtaggingMu
    )

ak1PFpatJetsWithBtagging = patJets.clone(
    jetSource = cms.InputTag("ak1PFJets"),
    genJetMatch            = cms.InputTag("ak1PFmatch"),
    genPartonMatch         = cms.InputTag("ak1PFparton"),
    jetCorrFactorsSource   = cms.VInputTag(cms.InputTag("ak1PFcorr")),
    JetPartonMapSource     = cms.InputTag("ak1PFPatJetFlavourAssociation"),
    JetFlavourInfoSource   = cms.InputTag("ak1PFPatJetFlavourAssociation"),
    trackAssociationSource = cms.InputTag("ak1PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour  = False,
    discriminatorSources   = cms.VInputTag(
        cms.InputTag("ak1PFSimpleSecondaryVertexHighEffBJetTags"),
        cms.InputTag("ak1PFSimpleSecondaryVertexHighPurBJetTags"),
        cms.InputTag("ak1PFCombinedSecondaryVertexBJetTags"),
        cms.InputTag("ak1PFCombinedSecondaryVertexV2BJetTags"),
        cms.InputTag("ak1PFJetBProbabilityBJetTags"),
        cms.InputTag("ak1PFJetProbabilityBJetTags"),
        # cms.InputTag("ak1PFSoftPFMuonByPtBJetTags"),
        # cms.InputTag("ak1PFSoftPFMuonByIP3dBJetTags"),
        cms.InputTag("ak1PFTrackCountingHighEffBJetTags"),
        cms.InputTag("ak1PFTrackCountingHighPurBJetTags"),
        ),
    tagInfoSources = cms.VInputTag(cms.InputTag("ak1PFImpactParameterTagInfos"),cms.InputTag("ak1PFSecondaryVertexTagInfos")),
    jetIDMap = cms.InputTag("ak1PFJetID"),
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

ak1PFNjettiness = Njettiness.clone(
    src = cms.InputTag("ak1PFJets"),
    R0  = cms.double(0.1)
    )

ak1PFpatJetsWithBtagging.userData.userFloats.src += [
    'ak1PFNjettiness:tau1',
    'ak1PFNjettiness:tau2',
    'ak1PFNjettiness:tau3']

ak1PFJetAnalyzer = inclusiveJetAnalyzer.clone(
    jetTag = cms.InputTag("ak1PFpatJetsWithBtagging"),
    genjetTag = 'ak1HiSignalGenJets',
    rParam = 0.1,
    matchJets = cms.untracked.bool(False),
    matchTag = 'patJetsWithBtagging',
    pfCandidateLabel = cms.untracked.InputTag('particleFlow'),
    trackTag = cms.InputTag("generalTracks"),
    fillGenJets = True,
    isMC = True,
    doSubEvent = True,
    useHepMC = cms.untracked.bool(False),
    genParticles = cms.untracked.InputTag("genParticles"),
    eventInfoTag = cms.InputTag("generator"),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    bTagJetName = cms.untracked.string("ak1PF"),
    jetName = cms.untracked.string("ak1PF"),
    genPtMin = cms.untracked.double(5),
    doTower = cms.untracked.bool(False),
    doSubJets = cms.untracked.bool(False),
    doGenSubJets = cms.untracked.bool(False),
    subjetGenTag = cms.untracked.InputTag("ak1GenJets"),
    doGenTaus = cms.untracked.bool(False),
    genTau1 = cms.InputTag("ak1HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak1HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak1HiGenNjettiness","tau3"),
    doGenSym = cms.untracked.bool(False),
    genSym = cms.InputTag("ak1GenJets","sym"),
    genDroppedBranches = cms.InputTag("ak1GenJets","droppedBranches")
    )

ak1PFJetSequence_mc = cms.Sequence(
    # ak1PFclean
    # *
    ak1PFmatch
    # *
    # ak1PFmatchGroomed
    *
    ak1PFparton
    *
    ak1PFcorr
    # *
    # ak1PFJetID
    *
     ak1PFPatJetFlavourId 
    *
    ak1PFJetTracksAssociatorAtVertex
    *
    ak1PFJetBtagging
    *
    # No constituents for calo jets in pp. Must be removed for pp calo jets but
    # I'm not sure how to do this transparently (Marta)
    ak1PFNjettiness
    *
    ak1PFpatJetsWithBtagging
    *
    ak1PFJetAnalyzer
    )

ak1PFJetSequence_data = cms.Sequence(
    ak1PFcorr
    *
    # ak1PFJetID
    # *
    ak1PFJetTracksAssociatorAtVertex
    *
    ak1PFJetBtagging
    *
    ak1PFNjettiness
    *
    ak1PFpatJetsWithBtagging
    *
    ak1PFJetAnalyzer
    )

ak1PFJetSequence_mb = cms.Sequence(
    ak1PFJetSequence_mc)
ak1PFJetSequence_jec = cms.Sequence(
    ak1PFJetSequence_mc)

ak1PFJetSequence = cms.Sequence(
    ak1PFJetSequence_jec)
ak1PFJetAnalyzer.genPtMin = cms.untracked.double(1)
ak1PFJetAnalyzer.jetPtMin = cms.double(1)
