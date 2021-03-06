import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import patJetGenJetMatch, patJetPartonMatch
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import patJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi import patJets

from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *

from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akSoftDrop2PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop2PFJets"),
    matched = cms.InputTag("ak2HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.2
    )

akSoftDrop2PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop2HiSignalGenJets"),
    matched = cms.InputTag("ak2HiSignalGenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.2
    )

akSoftDrop2PFparton = patJetPartonMatch.clone(
    src = cms.InputTag("akSoftDrop2PFJets"),
    matched = cms.InputTag("hiSignalGenParticles"))

akSoftDrop2PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
    levels   = cms.vstring('L2Relative','L2L3Residual'),
    src = cms.InputTag("akSoftDrop2PFJets"),
    payload = "AK2PF"
    )

akSoftDrop2PFJetID = cms.EDProducer(
    'JetIDProducer',
    JetIDParams,
    src = cms.InputTag('akSoftDrop2CaloJets'))

# akSoftDrop2PFclean = heavyIonCleanedGenJets.clone(
#     src = cms.InputTag('ak2HiSignalGenJets'))

akSoftDrop2PFbTagger = bTaggers(
    "akSoftDrop2PF",
    0.2)

# create objects locally since they dont load properly otherwise
akSoftDrop2PFPatJetPartons = akSoftDrop2PFbTagger.PatJetPartons
akSoftDrop2PFJetTracksAssociatorAtVertex = akSoftDrop2PFbTagger.JetTracksAssociatorAtVertex
akSoftDrop2PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akSoftDrop2PFSimpleSecondaryVertexHighEffBJetTags = akSoftDrop2PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop2PFSimpleSecondaryVertexHighPurBJetTags = akSoftDrop2PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop2PFCombinedSecondaryVertexBJetTags = akSoftDrop2PFbTagger.CombinedSecondaryVertexBJetTags
akSoftDrop2PFCombinedSecondaryVertexV2BJetTags = akSoftDrop2PFbTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop2PFJetBProbabilityBJetTags = akSoftDrop2PFbTagger.JetBProbabilityBJetTags
akSoftDrop2PFSoftPFMuonByPtBJetTags = akSoftDrop2PFbTagger.SoftPFMuonByPtBJetTags
akSoftDrop2PFSoftPFMuonByIP3dBJetTags = akSoftDrop2PFbTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop2PFTrackCountingHighEffBJetTags = akSoftDrop2PFbTagger.TrackCountingHighEffBJetTags
akSoftDrop2PFTrackCountingHighPurBJetTags = akSoftDrop2PFbTagger.TrackCountingHighPurBJetTags

akSoftDrop2PFImpactParameterTagInfos = akSoftDrop2PFbTagger.ImpactParameterTagInfos
akSoftDrop2PFImpactParameterTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
akSoftDrop2PFJetProbabilityBJetTags = akSoftDrop2PFbTagger.JetProbabilityBJetTags

akSoftDrop2PFSecondaryVertexTagInfos = akSoftDrop2PFbTagger.SecondaryVertexTagInfos
akSoftDrop2PFSimpleSecondaryVertexHighEffBJetTags = akSoftDrop2PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop2PFSimpleSecondaryVertexHighPurBJetTags = akSoftDrop2PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop2PFCombinedSecondaryVertexBJetTags = akSoftDrop2PFbTagger.CombinedSecondaryVertexBJetTags
akSoftDrop2PFCombinedSecondaryVertexV2BJetTags = akSoftDrop2PFbTagger.CombinedSecondaryVertexV2BJetTags

akSoftDrop2PFSecondaryVertexNegativeTagInfos = akSoftDrop2PFbTagger.SecondaryVertexNegativeTagInfos
akSoftDrop2PFNegativeSimpleSecondaryVertexHighEffBJetTags = akSoftDrop2PFbTagger.NegativeSimpleSecondaryVertexHighEffBJetTags
akSoftDrop2PFNegativeSimpleSecondaryVertexHighPurBJetTags = akSoftDrop2PFbTagger.NegativeSimpleSecondaryVertexHighPurBJetTags
akSoftDrop2PFNegativeCombinedSecondaryVertexBJetTags = akSoftDrop2PFbTagger.NegativeCombinedSecondaryVertexBJetTags
akSoftDrop2PFPositiveCombinedSecondaryVertexBJetTags = akSoftDrop2PFbTagger.PositiveCombinedSecondaryVertexBJetTags
akSoftDrop2PFNegativeCombinedSecondaryVertexV2BJetTags = akSoftDrop2PFbTagger.NegativeCombinedSecondaryVertexV2BJetTags
akSoftDrop2PFPositiveCombinedSecondaryVertexV2BJetTags = akSoftDrop2PFbTagger.PositiveCombinedSecondaryVertexV2BJetTags

akSoftDrop2PFSoftPFMuonsTagInfos = akSoftDrop2PFbTagger.SoftPFMuonsTagInfos
akSoftDrop2PFSoftPFMuonsTagInfos.primaryVertex = cms.InputTag("offlinePrimaryVertices")
akSoftDrop2PFSoftPFMuonBJetTags = akSoftDrop2PFbTagger.SoftPFMuonBJetTags
akSoftDrop2PFSoftPFMuonByIP3dBJetTags = akSoftDrop2PFbTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop2PFSoftPFMuonByPtBJetTags = akSoftDrop2PFbTagger.SoftPFMuonByPtBJetTags
akSoftDrop2PFNegativeSoftPFMuonByPtBJetTags = akSoftDrop2PFbTagger.NegativeSoftPFMuonByPtBJetTags
akSoftDrop2PFPositiveSoftPFMuonByPtBJetTags = akSoftDrop2PFbTagger.PositiveSoftPFMuonByPtBJetTags
akSoftDrop2PFPatJetFlavourAssociation = akSoftDrop2PFbTagger.PatJetFlavourAssociation
akSoftDrop2PFPatJetFlavourId = cms.Sequence(akSoftDrop2PFPatJetPartons*akSoftDrop2PFPatJetFlavourAssociation)

akSoftDrop2PFJetBtaggingIP = cms.Sequence(
    akSoftDrop2PFImpactParameterTagInfos *
    akSoftDrop2PFTrackCountingHighEffBJetTags +
    akSoftDrop2PFTrackCountingHighPurBJetTags +
    akSoftDrop2PFJetProbabilityBJetTags +
    akSoftDrop2PFJetBProbabilityBJetTags
    )

akSoftDrop2PFJetBtaggingSV = cms.Sequence(
    akSoftDrop2PFImpactParameterTagInfos *
    akSoftDrop2PFSecondaryVertexTagInfos *
    akSoftDrop2PFSimpleSecondaryVertexHighEffBJetTags +
    akSoftDrop2PFSimpleSecondaryVertexHighPurBJetTags +
    akSoftDrop2PFCombinedSecondaryVertexBJetTags +
    akSoftDrop2PFCombinedSecondaryVertexV2BJetTags
    )

akSoftDrop2PFJetBtaggingNegSV = cms.Sequence(
    akSoftDrop2PFImpactParameterTagInfos *
    akSoftDrop2PFSecondaryVertexNegativeTagInfos *
    akSoftDrop2PFNegativeSimpleSecondaryVertexHighEffBJetTags +
    akSoftDrop2PFNegativeSimpleSecondaryVertexHighPurBJetTags +
    akSoftDrop2PFNegativeCombinedSecondaryVertexBJetTags +
    akSoftDrop2PFPositiveCombinedSecondaryVertexBJetTags +
    akSoftDrop2PFNegativeCombinedSecondaryVertexV2BJetTags +
    akSoftDrop2PFPositiveCombinedSecondaryVertexV2BJetTags
    )

akSoftDrop2PFJetBtaggingMu = cms.Sequence(
    akSoftDrop2PFSoftPFMuonsTagInfos *
    akSoftDrop2PFSoftPFMuonBJetTags +
    akSoftDrop2PFSoftPFMuonByIP3dBJetTags +
    akSoftDrop2PFSoftPFMuonByPtBJetTags +
    akSoftDrop2PFNegativeSoftPFMuonByPtBJetTags +
    akSoftDrop2PFPositiveSoftPFMuonByPtBJetTags
    )

akSoftDrop2PFJetBtagging = cms.Sequence(
    akSoftDrop2PFJetBtaggingIP
    * akSoftDrop2PFJetBtaggingSV
    # * akSoftDrop2PFJetBtaggingNegSV
    # * akSoftDrop2PFJetBtaggingMu
    )

akSoftDrop2PFpatJetsWithBtagging = patJets.clone(
    jetSource = cms.InputTag("akSoftDrop2PFJets"),
    genJetMatch            = cms.InputTag("akSoftDrop2PFmatch"),
    genPartonMatch         = cms.InputTag("akSoftDrop2PFparton"),
    jetCorrFactorsSource   = cms.VInputTag(cms.InputTag("akSoftDrop2PFcorr")),
    JetPartonMapSource     = cms.InputTag("akSoftDrop2PFPatJetFlavourAssociation"),
    JetFlavourInfoSource   = cms.InputTag("akSoftDrop2PFPatJetFlavourAssociation"),
    trackAssociationSource = cms.InputTag("akSoftDrop2PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour  = False,
    discriminatorSources   = cms.VInputTag(
        cms.InputTag("akSoftDrop2PFSimpleSecondaryVertexHighEffBJetTags"),
        cms.InputTag("akSoftDrop2PFSimpleSecondaryVertexHighPurBJetTags"),
        cms.InputTag("akSoftDrop2PFCombinedSecondaryVertexBJetTags"),
        cms.InputTag("akSoftDrop2PFCombinedSecondaryVertexV2BJetTags"),
        cms.InputTag("akSoftDrop2PFJetBProbabilityBJetTags"),
        cms.InputTag("akSoftDrop2PFJetProbabilityBJetTags"),
        # cms.InputTag("akSoftDrop2PFSoftPFMuonByPtBJetTags"),
        # cms.InputTag("akSoftDrop2PFSoftPFMuonByIP3dBJetTags"),
        cms.InputTag("akSoftDrop2PFTrackCountingHighEffBJetTags"),
        cms.InputTag("akSoftDrop2PFTrackCountingHighPurBJetTags"),
        ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akSoftDrop2PFImpactParameterTagInfos"),cms.InputTag("akSoftDrop2PFSecondaryVertexTagInfos")),
    jetIDMap = cms.InputTag("akSoftDrop2PFJetID"),
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

akSoftDrop2PFNjettiness = Njettiness.clone(
    src = cms.InputTag("akSoftDrop2PFJets"),
    R0  = cms.double(0.2)
    )

akSoftDrop2PFpatJetsWithBtagging.userData.userFloats.src += [
    'akSoftDrop2PFNjettiness:tau1',
    'akSoftDrop2PFNjettiness:tau2',
    'akSoftDrop2PFNjettiness:tau3']

akSoftDrop2PFJetAnalyzer = inclusiveJetAnalyzer.clone(
    jetTag = cms.InputTag("akSoftDrop2PFpatJetsWithBtagging"),
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
    bTagJetName = cms.untracked.string("akSoftDrop2PF"),
    jetName = cms.untracked.string("akSoftDrop2PF"),
    genPtMin = cms.untracked.double(5),
    doTower = cms.untracked.bool(False),
    doSubJets = cms.untracked.bool(True),
    doGenSubJets = cms.untracked.bool(False),
    subjetGenTag = cms.untracked.InputTag("akSoftDrop2GenJets"),
    doGenTaus = cms.untracked.bool(False),
    genTau1 = cms.InputTag("akSoftDrop2HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("akSoftDrop2HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("akSoftDrop2HiGenNjettiness","tau3"),
    doGenSym = cms.untracked.bool(False),
    genSym = cms.InputTag("akSoftDrop2GenJets","sym"),
    genDroppedBranches = cms.InputTag("akSoftDrop2GenJets","droppedBranches")
    )

akSoftDrop2PFJetSequence_mc = cms.Sequence(
    # akSoftDrop2PFclean
    # *
    akSoftDrop2PFmatch
    # *
    # akSoftDrop2PFmatchGroomed
    *
    akSoftDrop2PFparton
    *
    akSoftDrop2PFcorr
    # *
    # akSoftDrop2PFJetID
    *
     akSoftDrop2PFPatJetFlavourId 
    *
    akSoftDrop2PFJetTracksAssociatorAtVertex
    *
    akSoftDrop2PFJetBtagging
    *
    # No constituents for calo jets in pp. Must be removed for pp calo jets but
    # I'm not sure how to do this transparently (Marta)
    akSoftDrop2PFNjettiness
    *
    akSoftDrop2PFpatJetsWithBtagging
    *
    akSoftDrop2PFJetAnalyzer
    )

akSoftDrop2PFJetSequence_data = cms.Sequence(
    akSoftDrop2PFcorr
    *
    # akSoftDrop2PFJetID
    # *
    akSoftDrop2PFJetTracksAssociatorAtVertex
    *
    akSoftDrop2PFJetBtagging
    *
    akSoftDrop2PFNjettiness
    *
    akSoftDrop2PFpatJetsWithBtagging
    *
    akSoftDrop2PFJetAnalyzer
    )

akSoftDrop2PFJetSequence_mb = cms.Sequence(
    akSoftDrop2PFJetSequence_mc)
akSoftDrop2PFJetSequence_jec = cms.Sequence(
    akSoftDrop2PFJetSequence_mc)

akSoftDrop2PFJetSequence = cms.Sequence(
    akSoftDrop2PFJetSequence_data)
akSoftDrop2PFpatJetsWithBtagging.userData.userFloats.src += ['akSoftDrop2PFJets:sym']
akSoftDrop2PFpatJetsWithBtagging.userData.userInts.src += ['akSoftDrop2PFJets:droppedBranches']
