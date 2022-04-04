

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak6PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak6PFJets"),
    matched = cms.InputTag("ak6GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.6
    )

ak6PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak6GenJets"),
    matched = cms.InputTag("ak6GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.6
    )

ak6PFparton = patJetPartonMatch.clone(src = cms.InputTag("ak6PFJets")
                                                        )

ak6PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("ak6PFJets"),
    payload = "AK6PF"
    )

ak6PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('ak6CaloJets'))

#ak6PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak6GenJets'))

ak6PFbTagger = bTaggers("ak6PF",0.6,True,False)

#create objects locally since they dont load properly otherwise
#ak6PFmatch = ak6PFbTagger.match
ak6PFparton = patJetPartonMatch.clone(src = cms.InputTag("ak6PFJets"), matched = cms.InputTag("genParticles"))
ak6PFPatJetFlavourAssociationLegacy = ak6PFbTagger.PatJetFlavourAssociationLegacy
ak6PFPatJetPartons = ak6PFbTagger.PatJetPartons
ak6PFJetTracksAssociatorAtVertex = ak6PFbTagger.JetTracksAssociatorAtVertex
ak6PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
ak6PFSimpleSecondaryVertexHighEffBJetTags = ak6PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak6PFSimpleSecondaryVertexHighPurBJetTags = ak6PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak6PFCombinedSecondaryVertexBJetTags = ak6PFbTagger.CombinedSecondaryVertexBJetTags
ak6PFCombinedSecondaryVertexV2BJetTags = ak6PFbTagger.CombinedSecondaryVertexV2BJetTags
ak6PFJetBProbabilityBJetTags = ak6PFbTagger.JetBProbabilityBJetTags
ak6PFSoftPFMuonByPtBJetTags = ak6PFbTagger.SoftPFMuonByPtBJetTags
ak6PFSoftPFMuonByIP3dBJetTags = ak6PFbTagger.SoftPFMuonByIP3dBJetTags
ak6PFTrackCountingHighEffBJetTags = ak6PFbTagger.TrackCountingHighEffBJetTags
ak6PFTrackCountingHighPurBJetTags = ak6PFbTagger.TrackCountingHighPurBJetTags
ak6PFPatJetPartonAssociationLegacy = ak6PFbTagger.PatJetPartonAssociationLegacy

ak6PFImpactParameterTagInfos = ak6PFbTagger.ImpactParameterTagInfos
ak6PFPfImpactParameterTagInfos = ak6PFbTagger.PfImpactParameterTagInfos
ak6PFJetProbabilityBJetTags = ak6PFbTagger.JetProbabilityBJetTags

ak6PFSecondaryVertexTagInfos = ak6PFbTagger.SecondaryVertexTagInfos
ak6PFSimpleSecondaryVertexHighEffBJetTags = ak6PFbTagger.SimpleSecondaryVertexHighEffBJetTags
ak6PFSimpleSecondaryVertexHighPurBJetTags = ak6PFbTagger.SimpleSecondaryVertexHighPurBJetTags
ak6PFCombinedSecondaryVertexBJetTags = ak6PFbTagger.CombinedSecondaryVertexBJetTags
ak6PFCombinedSecondaryVertexV2BJetTags = ak6PFbTagger.CombinedSecondaryVertexV2BJetTags
ak6PFPfInclusiveSecondaryVertexFinderTagInfos = ak6PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
ak6PFPfDeepCSVTagInfos = ak6PFbTagger.PfDeepCSVTagInfos
ak6PFPfDeepCSVJetTags = ak6PFbTagger.PfDeepCSVJetTags


ak6PFSoftPFMuonsTagInfos = ak6PFbTagger.SoftPFMuonsTagInfos
ak6PFSoftPFMuonBJetTags = ak6PFbTagger.SoftPFMuonBJetTags
ak6PFSoftPFMuonByIP3dBJetTags = ak6PFbTagger.SoftPFMuonByIP3dBJetTags
ak6PFSoftPFMuonByPtBJetTags = ak6PFbTagger.SoftPFMuonByPtBJetTags
ak6PFPatJetFlavourIdLegacy = cms.Sequence(ak6PFPatJetPartonAssociationLegacy*ak6PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
ak6PFPatJetFlavourAssociation = ak6PFbTagger.PatJetFlavourAssociation
ak6PFPatJetFlavourId = cms.Sequence(ak6PFPatJetPartons*ak6PFPatJetFlavourAssociation)

#adding the subjet taggers
#SUBJETDUMMY_ak6PFSubjetImpactParameterTagInfos = ak6PFbTagger.SubjetImpactParameterTagInfos
#SUBJETDUMMY_ak6PFSubjetJetProbabilityBJetTags = ak6PFbTagger.SubjetJetProbabilityBJetTags
#SUBJETDUMMY_ak6PFSubjetSecondaryVertexTagInfos = ak6PFbTagger.SubjetSecondaryVertexTagInfos
#SUBJETDUMMY_ak6PFSubjetJetTracksAssociatorAtVertex = ak6PFbTagger.SubjetJetTracksAssociatorAtVertex
#SUBJETDUMMY_ak6PFCombinedSubjetSecondaryVertexBJetTags = ak6PFbTagger.CombinedSubjetSecondaryVertexBJetTags
#SUBJETDUMMY_ak6PFCombinedSubjetSecondaryVertexV2BJetTags = ak6PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

ak6PFJetBtaggingIP       = cms.Sequence(ak6PFImpactParameterTagInfos *
            (ak6PFTrackCountingHighEffBJetTags +
             ak6PFTrackCountingHighPurBJetTags +
             ak6PFJetProbabilityBJetTags +
             ak6PFJetBProbabilityBJetTags 
            ) *
	     ak6PFPfImpactParameterTagInfos 
            )

ak6PFJetBtaggingSV = cms.Sequence(ak6PFImpactParameterTagInfos
            *
            ak6PFSecondaryVertexTagInfos
            * (ak6PFSimpleSecondaryVertexHighEffBJetTags+
                ak6PFSimpleSecondaryVertexHighPurBJetTags+
                ak6PFCombinedSecondaryVertexBJetTags+
                ak6PFCombinedSecondaryVertexV2BJetTags
              ) *
	    ak6PFPfImpactParameterTagInfos *
	    ak6PFPfInclusiveSecondaryVertexFinderTagInfos *
	    ak6PFPfDeepCSVTagInfos *
	    ak6PFPfDeepCSVJetTags  
            )



ak6PFJetBtaggingMu = cms.Sequence(ak6PFSoftPFMuonsTagInfos * (ak6PFSoftPFMuonBJetTags
                +
                ak6PFSoftPFMuonByIP3dBJetTags
                +
                ak6PFSoftPFMuonByPtBJetTags               
              )
            )

ak6PFJetBtagging = cms.Sequence(ak6PFJetBtaggingIP
            *ak6PFJetBtaggingSV
#            *ak6PFJetBtaggingMu
            )

ak6PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("ak6PFJets"),
        genJetMatch          = cms.InputTag("ak6PFmatch"),
        genPartonMatch       = cms.InputTag("ak6PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak6PFcorr")),
        #JetPartonMapSource   = cms.InputTag("ak6PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("ak6PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("ak6PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("ak6PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("ak6PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("ak6PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("ak6PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("ak6PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("ak6PFJetBProbabilityBJetTags"),
            cms.InputTag("ak6PFJetProbabilityBJetTags"),
            #cms.InputTag("ak6PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("ak6PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("ak6PFTrackCountingHighEffBJetTags"),
            cms.InputTag("ak6PFTrackCountingHighPurBJetTags"),
            cms.InputTag("ak6PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("ak6PFJetID"),
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

ak6PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("ak6PFJets"),
           	    R0  = cms.double( 0.6)
)
#ppDataDummy_ak6PFpatJetsWithBtagging.userData.userFloats.src += ['ak6PFNjettiness:tau1','ak6PFNjettiness:tau2','ak6PFNjettiness:tau3']

ak6PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("ak6PFpatJetsWithBtagging"),
                                                             genjetTag = 'ak6GenJets',
                                                             rParam = 0.6,
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
                                                             bTagJetName = cms.untracked.string("ak6PF"),
                                                             jetName = cms.untracked.string("ak6PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(False),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("ak6GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("ak6PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("ak6PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("ak6PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

#ENABLE_PPCALO_ak6PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_ak6PFJetAnalyzer.doExtendedFlavorTagging = False

ak6PFJetAnalyzer.trackSelection = ak6PFSecondaryVertexTagInfos.trackSelection
ak6PFJetAnalyzer.trackPairV0Filter = ak6PFSecondaryVertexTagInfos.vertexCuts.v0Filter

ak6PFJetSequence_mc = cms.Sequence(
                                                  #ak6PFclean
                                                  #*
                                                  ak6PFmatch
                                                  #*
                                                  #ak6PFmatchGroomed
                                                  *
                                                  ak6PFparton
                                                  *
                                                  ak6PFcorr
                                                  *
                                                  #ak6PFJetID
                                                  #*
                                                  #ak6PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  ak6PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
                                                  ak6PFJetTracksAssociatorAtVertex
                                                  *
                                                  ak6PFJetBtagging
                                                  *
                                                  ak6PFNjettiness
                                                  *
                                                  ak6PFpatJetsWithBtagging
                                                  *
                                                  ak6PFJetAnalyzer
                                                  )

ak6PFJetSequence_data = cms.Sequence(ak6PFcorr
                                                    *
                                                    #ak6PFJetID
                                                    #*
                                                    ak6PFJetTracksAssociatorAtVertex
                                                    *
                                                    ak6PFJetBtagging
                                                    *
                                                    ak6PFNjettiness
                                                    *
                                                    ak6PFpatJetsWithBtagging
                                                    *
                                                    ak6PFJetAnalyzer
                                                    )

ak6PFJetSequence_jec = cms.Sequence(ak6PFJetSequence_mc)
ak6PFJetSequence_mb = cms.Sequence(ak6PFJetSequence_mc)

ak6PFJetSequence = cms.Sequence(ak6PFJetSequence_jec)
ak6PFJetAnalyzer.genPtMin = cms.untracked.double(1)
ak6PFJetAnalyzer.jetPtMin = cms.double(1)
ak6PFJetAnalyzer.doSubEvent = True
