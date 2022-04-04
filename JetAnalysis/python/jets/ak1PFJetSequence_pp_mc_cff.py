

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak1PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak1PFJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

ak1PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak1GenJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

ak1PFparton = patJetPartonMatch.clone(src = cms.InputTag("ak1PFJets")
                                                        )

ak1PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("ak1PFJets"),
    payload = "AK1PF"
    )

ak1PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('ak1CaloJets'))

#ak1PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak1GenJets'))

ak1PFbTagger = bTaggers("ak1PF",0.1,True,False)

#create objects locally since they dont load properly otherwise
#ak1PFmatch = ak1PFbTagger.match
ak1PFparton = patJetPartonMatch.clone(src = cms.InputTag("ak1PFJets"), matched = cms.InputTag("genParticles"))
ak1PFPatJetFlavourAssociationLegacy = ak1PFbTagger.PatJetFlavourAssociationLegacy
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
ak1PFPatJetPartonAssociationLegacy = ak1PFbTagger.PatJetPartonAssociationLegacy

ak1PFImpactParameterTagInfos = ak1PFbTagger.ImpactParameterTagInfos
ak1PFPfImpactParameterTagInfos = ak1PFbTagger.PfImpactParameterTagInfos
ak1PFJetProbabilityBJetTags = ak1PFbTagger.JetProbabilityBJetTags

ak1PFSecondaryVertexTagInfos = ak1PFbTagger.SecondaryVertexTagInfos
ak1PFSimpleSecondaryVertexHighEffBJetTags = ak1PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak1PFSimpleSecondaryVertexHighPurBJetTags = ak1PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak1PFCombinedSecondaryVertexBJetTags = ak1PFbTagger.CombinedSecondaryVertexBJetTags
ak1PFCombinedSecondaryVertexV2BJetTags = ak1PFbTagger.CombinedSecondaryVertexV2BJetTags
ak1PFPfInclusiveSecondaryVertexFinderTagInfos = ak1PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
ak1PFPfDeepCSVTagInfos = ak1PFbTagger.PfDeepCSVTagInfos
ak1PFPfDeepCSVJetTags = ak1PFbTagger.PfDeepCSVJetTags


ak1PFSoftPFMuonsTagInfos = ak1PFbTagger.SoftPFMuonsTagInfos
ak1PFSoftPFMuonBJetTags = ak1PFbTagger.SoftPFMuonBJetTags
ak1PFSoftPFMuonByIP3dBJetTags = ak1PFbTagger.SoftPFMuonByIP3dBJetTags
ak1PFSoftPFMuonByPtBJetTags = ak1PFbTagger.SoftPFMuonByPtBJetTags
ak1PFPatJetFlavourIdLegacy = cms.Sequence(ak1PFPatJetPartonAssociationLegacy*ak1PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
ak1PFPatJetFlavourAssociation = ak1PFbTagger.PatJetFlavourAssociation
ak1PFPatJetFlavourId = cms.Sequence(ak1PFPatJetPartons*ak1PFPatJetFlavourAssociation)

#adding the subjet taggers
#SUBJETDUMMY_ak1PFSubjetImpactParameterTagInfos = ak1PFbTagger.SubjetImpactParameterTagInfos
#SUBJETDUMMY_ak1PFSubjetJetProbabilityBJetTags = ak1PFbTagger.SubjetJetProbabilityBJetTags
#SUBJETDUMMY_ak1PFSubjetSecondaryVertexTagInfos = ak1PFbTagger.SubjetSecondaryVertexTagInfos
#SUBJETDUMMY_ak1PFSubjetJetTracksAssociatorAtVertex = ak1PFbTagger.SubjetJetTracksAssociatorAtVertex
#SUBJETDUMMY_ak1PFCombinedSubjetSecondaryVertexBJetTags = ak1PFbTagger.CombinedSubjetSecondaryVertexBJetTags
#SUBJETDUMMY_ak1PFCombinedSubjetSecondaryVertexV2BJetTags = ak1PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

ak1PFJetBtaggingIP       = cms.Sequence(ak1PFImpactParameterTagInfos *
            (ak1PFTrackCountingHighEffBJetTags +
             ak1PFTrackCountingHighPurBJetTags +
             ak1PFJetProbabilityBJetTags +
             ak1PFJetBProbabilityBJetTags 
            ) *
	     ak1PFPfImpactParameterTagInfos 
            )

ak1PFJetBtaggingSV = cms.Sequence(ak1PFImpactParameterTagInfos
            *
            ak1PFSecondaryVertexTagInfos
            * (ak1PFSimpleSecondaryVertexHighEffBJetTags+
                ak1PFSimpleSecondaryVertexHighPurBJetTags+
                ak1PFCombinedSecondaryVertexBJetTags+
                ak1PFCombinedSecondaryVertexV2BJetTags
              ) *
	    ak1PFPfImpactParameterTagInfos *
	    ak1PFPfInclusiveSecondaryVertexFinderTagInfos *
	    ak1PFPfDeepCSVTagInfos *
	    ak1PFPfDeepCSVJetTags  
            )



ak1PFJetBtaggingMu = cms.Sequence(ak1PFSoftPFMuonsTagInfos * (ak1PFSoftPFMuonBJetTags
                +
                ak1PFSoftPFMuonByIP3dBJetTags
                +
                ak1PFSoftPFMuonByPtBJetTags               
              )
            )

ak1PFJetBtagging = cms.Sequence(ak1PFJetBtaggingIP
            *ak1PFJetBtaggingSV
#            *ak1PFJetBtaggingMu
            )

ak1PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("ak1PFJets"),
        genJetMatch          = cms.InputTag("ak1PFmatch"),
        genPartonMatch       = cms.InputTag("ak1PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak1PFcorr")),
        #JetPartonMapSource   = cms.InputTag("ak1PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("ak1PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("ak1PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("ak1PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("ak1PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("ak1PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("ak1PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("ak1PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("ak1PFJetBProbabilityBJetTags"),
            cms.InputTag("ak1PFJetProbabilityBJetTags"),
            #cms.InputTag("ak1PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("ak1PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("ak1PFTrackCountingHighEffBJetTags"),
            cms.InputTag("ak1PFTrackCountingHighPurBJetTags"),
            cms.InputTag("ak1PFPfDeepCSVJetTags:probb")

            ),
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
           	    R0  = cms.double( 0.1)
)
#ppDataDummy_ak1PFpatJetsWithBtagging.userData.userFloats.src += ['ak1PFNjettiness:tau1','ak1PFNjettiness:tau2','ak1PFNjettiness:tau3']

ak1PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("ak1PFpatJetsWithBtagging"),
                                                             genjetTag = 'ak1GenJets',
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
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("ak1PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("ak1PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("ak1PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

#ENABLE_PPCALO_ak1PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_ak1PFJetAnalyzer.doExtendedFlavorTagging = False

ak1PFJetAnalyzer.trackSelection = ak1PFSecondaryVertexTagInfos.trackSelection
ak1PFJetAnalyzer.trackPairV0Filter = ak1PFSecondaryVertexTagInfos.vertexCuts.v0Filter

ak1PFJetSequence_mc = cms.Sequence(
                                                  #ak1PFclean
                                                  #*
                                                  ak1PFmatch
                                                  #*
                                                  #ak1PFmatchGroomed
                                                  *
                                                  ak1PFparton
                                                  *
                                                  ak1PFcorr
                                                  *
                                                  #ak1PFJetID
                                                  #*
                                                  #ak1PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  ak1PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
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

ak1PFJetSequence_data = cms.Sequence(ak1PFcorr
                                                    *
                                                    #ak1PFJetID
                                                    #*
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

ak1PFJetSequence_jec = cms.Sequence(ak1PFJetSequence_mc)
ak1PFJetSequence_mb = cms.Sequence(ak1PFJetSequence_mc)

ak1PFJetSequence = cms.Sequence(ak1PFJetSequence_mc)
