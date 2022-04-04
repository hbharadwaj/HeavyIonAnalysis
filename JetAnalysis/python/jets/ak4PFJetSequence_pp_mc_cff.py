

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak4PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak4PFJets"),
    matched = cms.InputTag("ak4GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.4
    )

ak4PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak4GenJets"),
    matched = cms.InputTag("ak4GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.4
    )

ak4PFparton = patJetPartonMatch.clone(src = cms.InputTag("ak4PFJets")
                                                        )

ak4PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("ak4PFJets"),
    payload = "AK4PF"
    )

ak4PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('ak4CaloJets'))

#ak4PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak4GenJets'))

ak4PFbTagger = bTaggers("ak4PF",0.4,True,False)

#create objects locally since they dont load properly otherwise
#ak4PFmatch = ak4PFbTagger.match
ak4PFparton = patJetPartonMatch.clone(src = cms.InputTag("ak4PFJets"), matched = cms.InputTag("genParticles"))
ak4PFPatJetFlavourAssociationLegacy = ak4PFbTagger.PatJetFlavourAssociationLegacy
ak4PFPatJetPartons = ak4PFbTagger.PatJetPartons
ak4PFJetTracksAssociatorAtVertex = ak4PFbTagger.JetTracksAssociatorAtVertex
ak4PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
ak4PFSimpleSecondaryVertexHighEffBJetTags = ak4PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak4PFSimpleSecondaryVertexHighPurBJetTags = ak4PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak4PFCombinedSecondaryVertexBJetTags = ak4PFbTagger.CombinedSecondaryVertexBJetTags
ak4PFCombinedSecondaryVertexV2BJetTags = ak4PFbTagger.CombinedSecondaryVertexV2BJetTags
ak4PFJetBProbabilityBJetTags = ak4PFbTagger.JetBProbabilityBJetTags
ak4PFSoftPFMuonByPtBJetTags = ak4PFbTagger.SoftPFMuonByPtBJetTags
ak4PFSoftPFMuonByIP3dBJetTags = ak4PFbTagger.SoftPFMuonByIP3dBJetTags
ak4PFTrackCountingHighEffBJetTags = ak4PFbTagger.TrackCountingHighEffBJetTags
ak4PFTrackCountingHighPurBJetTags = ak4PFbTagger.TrackCountingHighPurBJetTags
ak4PFPatJetPartonAssociationLegacy = ak4PFbTagger.PatJetPartonAssociationLegacy

ak4PFImpactParameterTagInfos = ak4PFbTagger.ImpactParameterTagInfos
ak4PFPfImpactParameterTagInfos = ak4PFbTagger.PfImpactParameterTagInfos
ak4PFJetProbabilityBJetTags = ak4PFbTagger.JetProbabilityBJetTags

ak4PFSecondaryVertexTagInfos = ak4PFbTagger.SecondaryVertexTagInfos
ak4PFSimpleSecondaryVertexHighEffBJetTags = ak4PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak4PFSimpleSecondaryVertexHighPurBJetTags = ak4PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak4PFCombinedSecondaryVertexBJetTags = ak4PFbTagger.CombinedSecondaryVertexBJetTags
ak4PFCombinedSecondaryVertexV2BJetTags = ak4PFbTagger.CombinedSecondaryVertexV2BJetTags
ak4PFPfInclusiveSecondaryVertexFinderTagInfos = ak4PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
ak4PFPfDeepCSVTagInfos = ak4PFbTagger.PfDeepCSVTagInfos
ak4PFPfDeepCSVJetTags = ak4PFbTagger.PfDeepCSVJetTags


ak4PFSoftPFMuonsTagInfos = ak4PFbTagger.SoftPFMuonsTagInfos
ak4PFSoftPFMuonBJetTags = ak4PFbTagger.SoftPFMuonBJetTags
ak4PFSoftPFMuonByIP3dBJetTags = ak4PFbTagger.SoftPFMuonByIP3dBJetTags
ak4PFSoftPFMuonByPtBJetTags = ak4PFbTagger.SoftPFMuonByPtBJetTags
ak4PFPatJetFlavourIdLegacy = cms.Sequence(ak4PFPatJetPartonAssociationLegacy*ak4PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
ak4PFPatJetFlavourAssociation = ak4PFbTagger.PatJetFlavourAssociation
ak4PFPatJetFlavourId = cms.Sequence(ak4PFPatJetPartons*ak4PFPatJetFlavourAssociation)

#adding the subjet taggers
#SUBJETDUMMY_ak4PFSubjetImpactParameterTagInfos = ak4PFbTagger.SubjetImpactParameterTagInfos
#SUBJETDUMMY_ak4PFSubjetJetProbabilityBJetTags = ak4PFbTagger.SubjetJetProbabilityBJetTags
#SUBJETDUMMY_ak4PFSubjetSecondaryVertexTagInfos = ak4PFbTagger.SubjetSecondaryVertexTagInfos
#SUBJETDUMMY_ak4PFSubjetJetTracksAssociatorAtVertex = ak4PFbTagger.SubjetJetTracksAssociatorAtVertex
#SUBJETDUMMY_ak4PFCombinedSubjetSecondaryVertexBJetTags = ak4PFbTagger.CombinedSubjetSecondaryVertexBJetTags
#SUBJETDUMMY_ak4PFCombinedSubjetSecondaryVertexV2BJetTags = ak4PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

ak4PFJetBtaggingIP       = cms.Sequence(ak4PFImpactParameterTagInfos *
            (ak4PFTrackCountingHighEffBJetTags +
             ak4PFTrackCountingHighPurBJetTags +
             ak4PFJetProbabilityBJetTags +
             ak4PFJetBProbabilityBJetTags 
            ) *
	     ak4PFPfImpactParameterTagInfos 
            )

ak4PFJetBtaggingSV = cms.Sequence(ak4PFImpactParameterTagInfos
            *
            ak4PFSecondaryVertexTagInfos
            * (ak4PFSimpleSecondaryVertexHighEffBJetTags+
                ak4PFSimpleSecondaryVertexHighPurBJetTags+
                ak4PFCombinedSecondaryVertexBJetTags+
                ak4PFCombinedSecondaryVertexV2BJetTags
              ) *
	    ak4PFPfImpactParameterTagInfos *
	    ak4PFPfInclusiveSecondaryVertexFinderTagInfos *
	    ak4PFPfDeepCSVTagInfos *
	    ak4PFPfDeepCSVJetTags  
            )



ak4PFJetBtaggingMu = cms.Sequence(ak4PFSoftPFMuonsTagInfos * (ak4PFSoftPFMuonBJetTags
                +
                ak4PFSoftPFMuonByIP3dBJetTags
                +
                ak4PFSoftPFMuonByPtBJetTags               
              )
            )

ak4PFJetBtagging = cms.Sequence(ak4PFJetBtaggingIP
            *ak4PFJetBtaggingSV
#            *ak4PFJetBtaggingMu
            )

ak4PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("ak4PFJets"),
        genJetMatch          = cms.InputTag("ak4PFmatch"),
        genPartonMatch       = cms.InputTag("ak4PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak4PFcorr")),
        #JetPartonMapSource   = cms.InputTag("ak4PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("ak4PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("ak4PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("ak4PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("ak4PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("ak4PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("ak4PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("ak4PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("ak4PFJetBProbabilityBJetTags"),
            cms.InputTag("ak4PFJetProbabilityBJetTags"),
            #cms.InputTag("ak4PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("ak4PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("ak4PFTrackCountingHighEffBJetTags"),
            cms.InputTag("ak4PFTrackCountingHighPurBJetTags"),
            cms.InputTag("ak4PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("ak4PFJetID"),
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

ak4PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("ak4PFJets"),
           	    R0  = cms.double( 0.4)
)
#ppDataDummy_ak4PFpatJetsWithBtagging.userData.userFloats.src += ['ak4PFNjettiness:tau1','ak4PFNjettiness:tau2','ak4PFNjettiness:tau3']

ak4PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("ak4PFpatJetsWithBtagging"),
                                                             genjetTag = 'ak4GenJets',
                                                             rParam = 0.4,
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
                                                             bTagJetName = cms.untracked.string("ak4PF"),
                                                             jetName = cms.untracked.string("ak4PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(False),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("ak4GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("ak4PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("ak4PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("ak4PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

#ENABLE_PPCALO_ak4PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_ak4PFJetAnalyzer.doExtendedFlavorTagging = False

ak4PFJetAnalyzer.trackSelection = ak4PFSecondaryVertexTagInfos.trackSelection
ak4PFJetAnalyzer.trackPairV0Filter = ak4PFSecondaryVertexTagInfos.vertexCuts.v0Filter

ak4PFJetSequence_mc = cms.Sequence(
                                                  #ak4PFclean
                                                  #*
                                                  ak4PFmatch
                                                  #*
                                                  #ak4PFmatchGroomed
                                                  *
                                                  ak4PFparton
                                                  *
                                                  ak4PFcorr
                                                  *
                                                  #ak4PFJetID
                                                  #*
                                                  #ak4PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  ak4PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
                                                  ak4PFJetTracksAssociatorAtVertex
                                                  *
                                                  ak4PFJetBtagging
                                                  *
                                                  ak4PFNjettiness
                                                  *
                                                  ak4PFpatJetsWithBtagging
                                                  *
                                                  ak4PFJetAnalyzer
                                                  )

ak4PFJetSequence_data = cms.Sequence(ak4PFcorr
                                                    *
                                                    #ak4PFJetID
                                                    #*
                                                    ak4PFJetTracksAssociatorAtVertex
                                                    *
                                                    ak4PFJetBtagging
                                                    *
                                                    ak4PFNjettiness
                                                    *
                                                    ak4PFpatJetsWithBtagging
                                                    *
                                                    ak4PFJetAnalyzer
                                                    )

ak4PFJetSequence_jec = cms.Sequence(ak4PFJetSequence_mc)
ak4PFJetSequence_mb = cms.Sequence(ak4PFJetSequence_mc)

ak4PFJetSequence = cms.Sequence(ak4PFJetSequence_mc)
