

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak3PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak3PFJets"),
    matched = cms.InputTag("ak3GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.3
    )

ak3PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak3GenJets"),
    matched = cms.InputTag("ak3GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.3
    )

ak3PFparton = patJetPartonMatch.clone(src = cms.InputTag("ak3PFJets")
                                                        )

ak3PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative','L2L3Residual'),
    src = cms.InputTag("ak3PFJets"),
    payload = "AK3PF"
    )

ak3PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('ak3CaloJets'))

#ak3PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak3GenJets'))

ak3PFbTagger = bTaggers("ak3PF",0.3,True,False)

#create objects locally since they dont load properly otherwise
#ak3PFmatch = ak3PFbTagger.match
ak3PFparton = patJetPartonMatch.clone(src = cms.InputTag("ak3PFJets"), matched = cms.InputTag("genParticles"))
ak3PFPatJetFlavourAssociationLegacy = ak3PFbTagger.PatJetFlavourAssociationLegacy
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
ak3PFPatJetPartonAssociationLegacy = ak3PFbTagger.PatJetPartonAssociationLegacy

ak3PFImpactParameterTagInfos = ak3PFbTagger.ImpactParameterTagInfos
ak3PFPfImpactParameterTagInfos = ak3PFbTagger.PfImpactParameterTagInfos
ak3PFJetProbabilityBJetTags = ak3PFbTagger.JetProbabilityBJetTags

ak3PFSecondaryVertexTagInfos = ak3PFbTagger.SecondaryVertexTagInfos
ak3PFSimpleSecondaryVertexHighEffBJetTags = ak3PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak3PFSimpleSecondaryVertexHighPurBJetTags = ak3PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak3PFCombinedSecondaryVertexBJetTags = ak3PFbTagger.CombinedSecondaryVertexBJetTags
ak3PFCombinedSecondaryVertexV2BJetTags = ak3PFbTagger.CombinedSecondaryVertexV2BJetTags
ak3PFPfInclusiveSecondaryVertexFinderTagInfos = ak3PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
ak3PFPfDeepCSVTagInfos = ak3PFbTagger.PfDeepCSVTagInfos
ak3PFPfDeepCSVJetTags = ak3PFbTagger.PfDeepCSVJetTags


ak3PFSoftPFMuonsTagInfos = ak3PFbTagger.SoftPFMuonsTagInfos
ak3PFSoftPFMuonBJetTags = ak3PFbTagger.SoftPFMuonBJetTags
ak3PFSoftPFMuonByIP3dBJetTags = ak3PFbTagger.SoftPFMuonByIP3dBJetTags
ak3PFSoftPFMuonByPtBJetTags = ak3PFbTagger.SoftPFMuonByPtBJetTags
ak3PFPatJetFlavourIdLegacy = cms.Sequence(ak3PFPatJetPartonAssociationLegacy*ak3PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
ak3PFPatJetFlavourAssociation = ak3PFbTagger.PatJetFlavourAssociation
ak3PFPatJetFlavourId = cms.Sequence(ak3PFPatJetPartons*ak3PFPatJetFlavourAssociation)

#adding the subjet taggers
#SUBJETDUMMY_ak3PFSubjetImpactParameterTagInfos = ak3PFbTagger.SubjetImpactParameterTagInfos
#SUBJETDUMMY_ak3PFSubjetJetProbabilityBJetTags = ak3PFbTagger.SubjetJetProbabilityBJetTags
#SUBJETDUMMY_ak3PFSubjetSecondaryVertexTagInfos = ak3PFbTagger.SubjetSecondaryVertexTagInfos
#SUBJETDUMMY_ak3PFSubjetJetTracksAssociatorAtVertex = ak3PFbTagger.SubjetJetTracksAssociatorAtVertex
#SUBJETDUMMY_ak3PFCombinedSubjetSecondaryVertexBJetTags = ak3PFbTagger.CombinedSubjetSecondaryVertexBJetTags
#SUBJETDUMMY_ak3PFCombinedSubjetSecondaryVertexV2BJetTags = ak3PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

ak3PFJetBtaggingIP       = cms.Sequence(ak3PFImpactParameterTagInfos *
            (ak3PFTrackCountingHighEffBJetTags +
             ak3PFTrackCountingHighPurBJetTags +
             ak3PFJetProbabilityBJetTags +
             ak3PFJetBProbabilityBJetTags 
            ) *
	     ak3PFPfImpactParameterTagInfos 
            )

ak3PFJetBtaggingSV = cms.Sequence(ak3PFImpactParameterTagInfos
            *
            ak3PFSecondaryVertexTagInfos
            * (ak3PFSimpleSecondaryVertexHighEffBJetTags+
                ak3PFSimpleSecondaryVertexHighPurBJetTags+
                ak3PFCombinedSecondaryVertexBJetTags+
                ak3PFCombinedSecondaryVertexV2BJetTags
              ) *
	    ak3PFPfImpactParameterTagInfos *
	    ak3PFPfInclusiveSecondaryVertexFinderTagInfos *
	    ak3PFPfDeepCSVTagInfos *
	    ak3PFPfDeepCSVJetTags  
            )



ak3PFJetBtaggingMu = cms.Sequence(ak3PFSoftPFMuonsTagInfos * (ak3PFSoftPFMuonBJetTags
                +
                ak3PFSoftPFMuonByIP3dBJetTags
                +
                ak3PFSoftPFMuonByPtBJetTags               
              )
            )

ak3PFJetBtagging = cms.Sequence(ak3PFJetBtaggingIP
            *ak3PFJetBtaggingSV
#            *ak3PFJetBtaggingMu
            )

ak3PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("ak3PFJets"),
        genJetMatch          = cms.InputTag("ak3PFmatch"),
        genPartonMatch       = cms.InputTag("ak3PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak3PFcorr")),
        #JetPartonMapSource   = cms.InputTag("ak3PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("ak3PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("ak3PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("ak3PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("ak3PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("ak3PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("ak3PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("ak3PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("ak3PFJetBProbabilityBJetTags"),
            cms.InputTag("ak3PFJetProbabilityBJetTags"),
            #cms.InputTag("ak3PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("ak3PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("ak3PFTrackCountingHighEffBJetTags"),
            cms.InputTag("ak3PFTrackCountingHighPurBJetTags"),
            cms.InputTag("ak3PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("ak3PFJetID"),
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

ak3PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("ak3PFJets"),
           	    R0  = cms.double( 0.3)
)
#ppDataDummy_ak3PFpatJetsWithBtagging.userData.userFloats.src += ['ak3PFNjettiness:tau1','ak3PFNjettiness:tau2','ak3PFNjettiness:tau3']

ak3PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("ak3PFpatJetsWithBtagging"),
                                                             genjetTag = 'ak3GenJets',
                                                             rParam = 0.3,
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
                                                             bTagJetName = cms.untracked.string("ak3PF"),
                                                             jetName = cms.untracked.string("ak3PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(False),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("ak3GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(False),
							     jetFlavourInfos = cms.InputTag("ak3PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("ak3PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("ak3PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = False
                                                            )

#ENABLE_PPCALO_ak3PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_ak3PFJetAnalyzer.doExtendedFlavorTagging = False

ak3PFJetAnalyzer.trackSelection = ak3PFSecondaryVertexTagInfos.trackSelection
ak3PFJetAnalyzer.trackPairV0Filter = ak3PFSecondaryVertexTagInfos.vertexCuts.v0Filter

ak3PFJetSequence_mc = cms.Sequence(
                                                  #ak3PFclean
                                                  #*
                                                  ak3PFmatch
                                                  #*
                                                  #ak3PFmatchGroomed
                                                  *
                                                  ak3PFparton
                                                  *
                                                  ak3PFcorr
                                                  *
                                                  #ak3PFJetID
                                                  #*
                                                  #ak3PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  ak3PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
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

ak3PFJetSequence_data = cms.Sequence(ak3PFcorr
                                                    *
                                                    #ak3PFJetID
                                                    #*
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

ak3PFJetSequence_jec = cms.Sequence(ak3PFJetSequence_mc)
ak3PFJetSequence_mb = cms.Sequence(ak3PFJetSequence_mc)

ak3PFJetSequence = cms.Sequence(ak3PFJetSequence_data)
