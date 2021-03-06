import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import patJetGenJetMatch, patJetPartonMatch
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import patJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi import patJets

from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *

from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak3PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak3PFJets"),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.3
    )

ak3PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak3HiSignalGenJets"),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.3
    )

ak3PFparton = patJetPartonMatch.clone(
    src = cms.InputTag("ak3PFJets"),
    matched = cms.InputTag("hiSignalGenParticles"))

ak3PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("ak3PFJets"),
    payload = "AK3PF"
    )

ak3PFJetID = cms.EDProducer(
    'JetIDProducer',
    JetIDParams,
    src = cms.InputTag('ak3CaloJets'))

# ak3PFclean = heavyIonCleanedGenJets.clone(
#     src = cms.InputTag('ak3HiSignalGenJets'))

ak3PFbTagger = bTaggers(
    "ak3PF",
    0.3)

# create objects locally since they dont load properly otherwise
ak3PFPatJetPartons = ak3PFbTagger.PatJetPartons
ak3PFJetTracksAssociatorAtVertex = ak3PFbTagger.JetTracksAssociatorAtVertex
ak3PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
ak3PFSimpleSecondaryVertexHighEffBJetTags = ak3PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak3PFSimpleSecondaryVertexHighPurBJetTags = ak3PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak3PFCombinedSecondaryVertexBJetTags = ak3PFbTagger.CombinedSecondaryVertexBJetTags
ak3PFCombinedSecondaryVertexV2BJetTags = ak3PFbTagger.CombinedSecondaryVertexV2BJetTags
ak3PFJetBProbabilityBJetTags = ak3PFbTagger.JetBProbabilityBJetTags
ak3PFSoftPFMuonByPtBJetTags = ak3PFbTagger.SoftPFMuonByPtBJetTags
ak3PFSoftPFMuonByIP3dBJetTags = ak3PFbTagger.SoftPFMuonByIP3dBJetTags
ak3PFTrackCountingHighEffBJetTags = ak3PFbTagger.TrackCountingHighEffBJetTags
ak3PFTrackCountingHighPurBJetTags = ak3PFbTagger.TrackCountingHighPurBJetTags

ak3PFImpactParameterTagInfos = ak3PFbTagger.ImpactParameterTagInfos
ak3PFImpactParameterTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
ak3PFJetProbabilityBJetTags = ak3PFbTagger.JetProbabilityBJetTags

ak3PFSecondaryVertexTagInfos = ak3PFbTagger.SecondaryVertexTagInfos
ak3PFSimpleSecondaryVertexHighEffBJetTags = ak3PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak3PFSimpleSecondaryVertexHighPurBJetTags = ak3PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak3PFCombinedSecondaryVertexBJetTags = ak3PFbTagger.CombinedSecondaryVertexBJetTags
ak3PFCombinedSecondaryVertexV2BJetTags = ak3PFbTagger.CombinedSecondaryVertexV2BJetTags

ak3PFSecondaryVertexNegativeTagInfos = ak3PFbTagger.SecondaryVertexNegativeTagInfos
ak3PFNegativeSimpleSecondaryVertexHighEffBJetTags = ak3PFbTagger.NegativeSimpleSecondaryVertexHighEffBJetTags
ak3PFNegativeSimpleSecondaryVertexHighPurBJetTags = ak3PFbTagger.NegativeSimpleSecondaryVertexHighPurBJetTags
ak3PFNegativeCombinedSecondaryVertexBJetTags = ak3PFbTagger.NegativeCombinedSecondaryVertexBJetTags
ak3PFPositiveCombinedSecondaryVertexBJetTags = ak3PFbTagger.PositiveCombinedSecondaryVertexBJetTags
ak3PFNegativeCombinedSecondaryVertexV2BJetTags = ak3PFbTagger.NegativeCombinedSecondaryVertexV2BJetTags
ak3PFPositiveCombinedSecondaryVertexV2BJetTags = ak3PFbTagger.PositiveCombinedSecondaryVertexV2BJetTags

ak3PFSoftPFMuonsTagInfos = ak3PFbTagger.SoftPFMuonsTagInfos
ak3PFSoftPFMuonsTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
ak3PFSoftPFMuonBJetTags = ak3PFbTagger.SoftPFMuonBJetTags
ak3PFSoftPFMuonByIP3dBJetTags = ak3PFbTagger.SoftPFMuonByIP3dBJetTags
ak3PFSoftPFMuonByPtBJetTags = ak3PFbTagger.SoftPFMuonByPtBJetTags
ak3PFNegativeSoftPFMuonByPtBJetTags = ak3PFbTagger.NegativeSoftPFMuonByPtBJetTags
ak3PFPositiveSoftPFMuonByPtBJetTags = ak3PFbTagger.PositiveSoftPFMuonByPtBJetTags
ak3PFPatJetFlavourAssociation = ak3PFbTagger.PatJetFlavourAssociation
ak3PFPatJetFlavourId = cms.Sequence(ak3PFPatJetPartons*ak3PFPatJetFlavourAssociation)

ak3PFJetBtaggingIP = cms.Sequence(
    ak3PFImpactParameterTagInfos *
    ak3PFTrackCountingHighEffBJetTags +
    ak3PFTrackCountingHighPurBJetTags +
    ak3PFJetProbabilityBJetTags +
    ak3PFJetBProbabilityBJetTags
    )

ak3PFJetBtaggingSV = cms.Sequence(
    ak3PFImpactParameterTagInfos *
    ak3PFSecondaryVertexTagInfos *
    ak3PFSimpleSecondaryVertexHighEffBJetTags +
    ak3PFSimpleSecondaryVertexHighPurBJetTags +
    ak3PFCombinedSecondaryVertexBJetTags +
    ak3PFCombinedSecondaryVertexV2BJetTags
    )

ak3PFJetBtaggingNegSV = cms.Sequence(
    ak3PFImpactParameterTagInfos *
    ak3PFSecondaryVertexNegativeTagInfos *
    ak3PFNegativeSimpleSecondaryVertexHighEffBJetTags +
    ak3PFNegativeSimpleSecondaryVertexHighPurBJetTags +
    ak3PFNegativeCombinedSecondaryVertexBJetTags +
    ak3PFPositiveCombinedSecondaryVertexBJetTags +
    ak3PFNegativeCombinedSecondaryVertexV2BJetTags +
    ak3PFPositiveCombinedSecondaryVertexV2BJetTags
    )

ak3PFJetBtaggingMu = cms.Sequence(
    ak3PFSoftPFMuonsTagInfos *
    ak3PFSoftPFMuonBJetTags +
    ak3PFSoftPFMuonByIP3dBJetTags +
    ak3PFSoftPFMuonByPtBJetTags +
    ak3PFNegativeSoftPFMuonByPtBJetTags +
    ak3PFPositiveSoftPFMuonByPtBJetTags
    )

ak3PFJetBtagging = cms.Sequence(
    ak3PFJetBtaggingIP
    * ak3PFJetBtaggingSV
    # * ak3PFJetBtaggingNegSV
    # * ak3PFJetBtaggingMu
    )

ak3PFpatJetsWithBtagging = patJets.clone(
    jetSource = cms.InputTag("ak3PFJets"),
    genJetMatch            = cms.InputTag("ak3PFmatch"),
    genPartonMatch         = cms.InputTag("ak3PFparton"),
    jetCorrFactorsSource   = cms.VInputTag(cms.InputTag("ak3PFcorr")),
    JetPartonMapSource     = cms.InputTag("ak3PFPatJetFlavourAssociation"),
    JetFlavourInfoSource   = cms.InputTag("ak3PFPatJetFlavourAssociation"),
    trackAssociationSource = cms.InputTag("ak3PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour  = False,
    discriminatorSources   = cms.VInputTag(
        cms.InputTag("ak3PFSimpleSecondaryVertexHighEffBJetTags"),
        cms.InputTag("ak3PFSimpleSecondaryVertexHighPurBJetTags"),
        cms.InputTag("ak3PFCombinedSecondaryVertexBJetTags"),
        cms.InputTag("ak3PFCombinedSecondaryVertexV2BJetTags"),
        cms.InputTag("ak3PFJetBProbabilityBJetTags"),
        cms.InputTag("ak3PFJetProbabilityBJetTags"),
        # cms.InputTag("ak3PFSoftPFMuonByPtBJetTags"),
        # cms.InputTag("ak3PFSoftPFMuonByIP3dBJetTags"),
        cms.InputTag("ak3PFTrackCountingHighEffBJetTags"),
        cms.InputTag("ak3PFTrackCountingHighPurBJetTags"),
        ),
    tagInfoSources = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"),cms.InputTag("ak3PFSecondaryVertexTagInfos")),
    jetIDMap = cms.InputTag("ak3PFJetID"),
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

ak3PFNjettiness = Njettiness.clone(
    src = cms.InputTag("ak3PFJets"),
    R0  = cms.double(0.3)
    )

ak3PFpatJetsWithBtagging.userData.userFloats.src += [
    'ak3PFNjettiness:tau1',
    'ak3PFNjettiness:tau2',
    'ak3PFNjettiness:tau3']

ak3PFJetAnalyzer = inclusiveJetAnalyzer.clone(
    jetTag = cms.InputTag("ak3PFpatJetsWithBtagging"),
    genjetTag = 'ak3HiSignalGenJets',
    rParam = 0.3,
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
    bTagJetName = cms.untracked.string("ak3PF"),
    jetName = cms.untracked.string("ak3PF"),
    genPtMin = cms.untracked.double(5),
    doTower = cms.untracked.bool(False),
    doSubJets = cms.untracked.bool(False),
    doGenSubJets = cms.untracked.bool(False),
    subjetGenTag = cms.untracked.InputTag("ak3GenJets"),
    doGenTaus = cms.untracked.bool(False),
    genTau1 = cms.InputTag("ak3HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak3HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak3HiGenNjettiness","tau3"),
    doGenSym = cms.untracked.bool(False),
    genSym = cms.InputTag("ak3GenJets","sym"),
    genDroppedBranches = cms.InputTag("ak3GenJets","droppedBranches")
    )

ak3PFJetSequence_mc = cms.Sequence(
    # ak3PFclean
    # *
    ak3PFmatch
    # *
    # ak3PFmatchGroomed
    *
    ak3PFparton
    *
    ak3PFcorr
    # *
    # ak3PFJetID
    *
     ak3PFPatJetFlavourId 
    *
    ak3PFJetTracksAssociatorAtVertex
    *
    ak3PFJetBtagging
    *
    # No constituents for calo jets in pp. Must be removed for pp calo jets but
    # I'm not sure how to do this transparently (Marta)
    ak3PFNjettiness
    *
    ak3PFpatJetsWithBtagging
    *
    ak3PFJetAnalyzer
    )

ak3PFJetSequence_data = cms.Sequence(
    ak3PFcorr
    *
    # ak3PFJetID
    # *
    ak3PFJetTracksAssociatorAtVertex
    *
    ak3PFJetBtagging
    *
    ak3PFNjettiness
    *
    ak3PFpatJetsWithBtagging
    *
    ak3PFJetAnalyzer
    )

ak3PFJetSequence_mb = cms.Sequence(
    ak3PFJetSequence_mc)
ak3PFJetSequence_jec = cms.Sequence(
    ak3PFJetSequence_mc)

ak3PFJetSequence = cms.Sequence(
    ak3PFJetSequence_jec)
ak3PFJetAnalyzer.genPtMin = cms.untracked.double(1)
ak3PFJetAnalyzer.jetPtMin = cms.double(1)
