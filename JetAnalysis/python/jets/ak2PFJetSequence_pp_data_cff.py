

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak2PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak2PFJets"),
    matched = cms.InputTag("ak2GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.2
    )

ak2PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak2GenJets"),
    matched = cms.InputTag("ak2GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.2
    )

ak2PFparton = patJetPartonMatch.clone(src = cms.InputTag("ak2PFJets")
                                                        )

ak2PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative','L2L3Residual'),
    src = cms.InputTag("ak2PFJets"),
    payload = "AK2PF"
    )

ak2PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('ak2CaloJets'))

#ak2PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak2GenJets'))

ak2PFbTagger = bTaggers("ak2PF",0.2,True,False)

#create objects locally since they dont load properly otherwise
#ak2PFmatch = ak2PFbTagger.match
ak2PFparton = patJetPartonMatch.clone(src = cms.InputTag("ak2PFJets"), matched = cms.InputTag("genParticles"))
ak2PFPatJetFlavourAssociationLegacy = ak2PFbTagger.PatJetFlavourAssociationLegacy
ak2PFPatJetPartons = ak2PFbTagger.PatJetPartons
ak2PFJetTracksAssociatorAtVertex = ak2PFbTagger.JetTracksAssociatorAtVertex
ak2PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
ak2PFSimpleSecondaryVertexHighEffBJetTags = ak2PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak2PFSimpleSecondaryVertexHighPurBJetTags = ak2PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak2PFCombinedSecondaryVertexBJetTags = ak2PFbTagger.CombinedSecondaryVertexBJetTags
ak2PFCombinedSecondaryVertexV2BJetTags = ak2PFbTagger.CombinedSecondaryVertexV2BJetTags
ak2PFJetBProbabilityBJetTags = ak2PFbTagger.JetBProbabilityBJetTags
ak2PFSoftPFMuonByPtBJetTags = ak2PFbTagger.SoftPFMuonByPtBJetTags
ak2PFSoftPFMuonByIP3dBJetTags = ak2PFbTagger.SoftPFMuonByIP3dBJetTags
ak2PFTrackCountingHighEffBJetTags = ak2PFbTagger.TrackCountingHighEffBJetTags
ak2PFTrackCountingHighPurBJetTags = ak2PFbTagger.TrackCountingHighPurBJetTags
ak2PFPatJetPartonAssociationLegacy = ak2PFbTagger.PatJetPartonAssociationLegacy

ak2PFImpactParameterTagInfos = ak2PFbTagger.ImpactParameterTagInfos
ak2PFPfImpactParameterTagInfos = ak2PFbTagger.PfImpactParameterTagInfos
ak2PFJetProbabilityBJetTags = ak2PFbTagger.JetProbabilityBJetTags

ak2PFSecondaryVertexTagInfos = ak2PFbTagger.SecondaryVertexTagInfos
ak2PFSimpleSecondaryVertexHighEffBJetTags = ak2PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak2PFSimpleSecondaryVertexHighPurBJetTags = ak2PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak2PFCombinedSecondaryVertexBJetTags = ak2PFbTagger.CombinedSecondaryVertexBJetTags
ak2PFCombinedSecondaryVertexV2BJetTags = ak2PFbTagger.CombinedSecondaryVertexV2BJetTags
ak2PFPfInclusiveSecondaryVertexFinderTagInfos = ak2PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
ak2PFPfDeepCSVTagInfos = ak2PFbTagger.PfDeepCSVTagInfos
ak2PFPfDeepCSVJetTags = ak2PFbTagger.PfDeepCSVJetTags


ak2PFSoftPFMuonsTagInfos = ak2PFbTagger.SoftPFMuonsTagInfos
ak2PFSoftPFMuonBJetTags = ak2PFbTagger.SoftPFMuonBJetTags
ak2PFSoftPFMuonByIP3dBJetTags = ak2PFbTagger.SoftPFMuonByIP3dBJetTags
ak2PFSoftPFMuonByPtBJetTags = ak2PFbTagger.SoftPFMuonByPtBJetTags
ak2PFPatJetFlavourIdLegacy = cms.Sequence(ak2PFPatJetPartonAssociationLegacy*ak2PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
ak2PFPatJetFlavourAssociation = ak2PFbTagger.PatJetFlavourAssociation
ak2PFPatJetFlavourId = cms.Sequence(ak2PFPatJetPartons*ak2PFPatJetFlavourAssociation)

#adding the subjet taggers
#SUBJETDUMMY_ak2PFSubjetImpactParameterTagInfos = ak2PFbTagger.SubjetImpactParameterTagInfos
#SUBJETDUMMY_ak2PFSubjetJetProbabilityBJetTags = ak2PFbTagger.SubjetJetProbabilityBJetTags
#SUBJETDUMMY_ak2PFSubjetSecondaryVertexTagInfos = ak2PFbTagger.SubjetSecondaryVertexTagInfos
#SUBJETDUMMY_ak2PFSubjetJetTracksAssociatorAtVertex = ak2PFbTagger.SubjetJetTracksAssociatorAtVertex
#SUBJETDUMMY_ak2PFCombinedSubjetSecondaryVertexBJetTags = ak2PFbTagger.CombinedSubjetSecondaryVertexBJetTags
#SUBJETDUMMY_ak2PFCombinedSubjetSecondaryVertexV2BJetTags = ak2PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

ak2PFJetBtaggingIP       = cms.Sequence(ak2PFImpactParameterTagInfos *
            (ak2PFTrackCountingHighEffBJetTags +
             ak2PFTrackCountingHighPurBJetTags +
             ak2PFJetProbabilityBJetTags +
             ak2PFJetBProbabilityBJetTags 
            ) *
	     ak2PFPfImpactParameterTagInfos 
            )

ak2PFJetBtaggingSV = cms.Sequence(ak2PFImpactParameterTagInfos
            *
            ak2PFSecondaryVertexTagInfos
            * (ak2PFSimpleSecondaryVertexHighEffBJetTags+
                ak2PFSimpleSecondaryVertexHighPurBJetTags+
                ak2PFCombinedSecondaryVertexBJetTags+
                ak2PFCombinedSecondaryVertexV2BJetTags
              ) *
	    ak2PFPfImpactParameterTagInfos *
	    ak2PFPfInclusiveSecondaryVertexFinderTagInfos *
	    ak2PFPfDeepCSVTagInfos *
	    ak2PFPfDeepCSVJetTags  
            )



ak2PFJetBtaggingMu = cms.Sequence(ak2PFSoftPFMuonsTagInfos * (ak2PFSoftPFMuonBJetTags
                +
                ak2PFSoftPFMuonByIP3dBJetTags
                +
                ak2PFSoftPFMuonByPtBJetTags               
              )
            )

ak2PFJetBtagging = cms.Sequence(ak2PFJetBtaggingIP
            *ak2PFJetBtaggingSV
#            *ak2PFJetBtaggingMu
            )

ak2PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("ak2PFJets"),
        genJetMatch          = cms.InputTag("ak2PFmatch"),
        genPartonMatch       = cms.InputTag("ak2PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak2PFcorr")),
        #JetPartonMapSource   = cms.InputTag("ak2PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("ak2PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("ak2PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("ak2PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("ak2PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("ak2PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("ak2PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("ak2PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("ak2PFJetBProbabilityBJetTags"),
            cms.InputTag("ak2PFJetProbabilityBJetTags"),
            #cms.InputTag("ak2PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("ak2PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("ak2PFTrackCountingHighEffBJetTags"),
            cms.InputTag("ak2PFTrackCountingHighPurBJetTags"),
            cms.InputTag("ak2PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("ak2PFJetID"),
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

ak2PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("ak2PFJets"),
           	    R0  = cms.double( 0.2)
)
#ppDataDummy_ak2PFpatJetsWithBtagging.userData.userFloats.src += ['ak2PFNjettiness:tau1','ak2PFNjettiness:tau2','ak2PFNjettiness:tau3']

ak2PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("ak2PFpatJetsWithBtagging"),
                                                             genjetTag = 'ak2GenJets',
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
                                                             bTagJetName = cms.untracked.string("ak2PF"),
                                                             jetName = cms.untracked.string("ak2PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(False),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("ak2GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(False),
							     jetFlavourInfos = cms.InputTag("ak2PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("ak2PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("ak2PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = False
                                                            )

#ENABLE_PPCALO_ak2PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_ak2PFJetAnalyzer.doExtendedFlavorTagging = False

ak2PFJetAnalyzer.trackSelection = ak2PFSecondaryVertexTagInfos.trackSelection
ak2PFJetAnalyzer.trackPairV0Filter = ak2PFSecondaryVertexTagInfos.vertexCuts.v0Filter

ak2PFJetSequence_mc = cms.Sequence(
                                                  #ak2PFclean
                                                  #*
                                                  ak2PFmatch
                                                  #*
                                                  #ak2PFmatchGroomed
                                                  *
                                                  ak2PFparton
                                                  *
                                                  ak2PFcorr
                                                  *
                                                  #ak2PFJetID
                                                  #*
                                                  #ak2PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  ak2PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
                                                  ak2PFJetTracksAssociatorAtVertex
                                                  *
                                                  ak2PFJetBtagging
                                                  *
                                                  ak2PFNjettiness
                                                  *
                                                  ak2PFpatJetsWithBtagging
                                                  *
                                                  ak2PFJetAnalyzer
                                                  )

ak2PFJetSequence_data = cms.Sequence(ak2PFcorr
                                                    *
                                                    #ak2PFJetID
                                                    #*
                                                    ak2PFJetTracksAssociatorAtVertex
                                                    *
                                                    ak2PFJetBtagging
                                                    *
                                                    ak2PFNjettiness
                                                    *
                                                    ak2PFpatJetsWithBtagging
                                                    *
                                                    ak2PFJetAnalyzer
                                                    )

ak2PFJetSequence_jec = cms.Sequence(ak2PFJetSequence_mc)
ak2PFJetSequence_mb = cms.Sequence(ak2PFJetSequence_mc)

ak2PFJetSequence = cms.Sequence(ak2PFJetSequence_data)
