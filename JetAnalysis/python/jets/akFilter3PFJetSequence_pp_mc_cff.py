

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akFilter3PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter3PFJets"),
    matched = cms.InputTag("ak3GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.3
    )

akFilter3PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter3GenJets"),
    matched = cms.InputTag("ak3GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.3
    )

akFilter3PFparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter3PFJets")
                                                        )

akFilter3PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akFilter3PFJets"),
    payload = "AK3PF"
    )

akFilter3PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akFilter3CaloJets'))

#akFilter3PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak3GenJets'))

akFilter3PFbTagger = bTaggers("akFilter3PF",0.3,True,True)

#create objects locally since they dont load properly otherwise
#akFilter3PFmatch = akFilter3PFbTagger.match
akFilter3PFparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter3PFJets"), matched = cms.InputTag("genParticles"))
akFilter3PFPatJetFlavourAssociationLegacy = akFilter3PFbTagger.PatJetFlavourAssociationLegacy
akFilter3PFPatJetPartons = akFilter3PFbTagger.PatJetPartons
akFilter3PFJetTracksAssociatorAtVertex = akFilter3PFbTagger.JetTracksAssociatorAtVertex
akFilter3PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akFilter3PFSimpleSecondaryVertexHighEffBJetTags = akFilter3PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter3PFSimpleSecondaryVertexHighPurBJetTags = akFilter3PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter3PFCombinedSecondaryVertexBJetTags = akFilter3PFbTagger.CombinedSecondaryVertexBJetTags
akFilter3PFCombinedSecondaryVertexV2BJetTags = akFilter3PFbTagger.CombinedSecondaryVertexV2BJetTags
akFilter3PFJetBProbabilityBJetTags = akFilter3PFbTagger.JetBProbabilityBJetTags
akFilter3PFSoftPFMuonByPtBJetTags = akFilter3PFbTagger.SoftPFMuonByPtBJetTags
akFilter3PFSoftPFMuonByIP3dBJetTags = akFilter3PFbTagger.SoftPFMuonByIP3dBJetTags
akFilter3PFTrackCountingHighEffBJetTags = akFilter3PFbTagger.TrackCountingHighEffBJetTags
akFilter3PFTrackCountingHighPurBJetTags = akFilter3PFbTagger.TrackCountingHighPurBJetTags
akFilter3PFPatJetPartonAssociationLegacy = akFilter3PFbTagger.PatJetPartonAssociationLegacy

akFilter3PFImpactParameterTagInfos = akFilter3PFbTagger.ImpactParameterTagInfos
akFilter3PFPfImpactParameterTagInfos = akFilter3PFbTagger.PfImpactParameterTagInfos
akFilter3PFJetProbabilityBJetTags = akFilter3PFbTagger.JetProbabilityBJetTags

akFilter3PFSecondaryVertexTagInfos = akFilter3PFbTagger.SecondaryVertexTagInfos
akFilter3PFSimpleSecondaryVertexHighEffBJetTags = akFilter3PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter3PFSimpleSecondaryVertexHighPurBJetTags = akFilter3PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter3PFCombinedSecondaryVertexBJetTags = akFilter3PFbTagger.CombinedSecondaryVertexBJetTags
akFilter3PFCombinedSecondaryVertexV2BJetTags = akFilter3PFbTagger.CombinedSecondaryVertexV2BJetTags
akFilter3PFPfInclusiveSecondaryVertexFinderTagInfos = akFilter3PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
akFilter3PFPfDeepCSVTagInfos = akFilter3PFbTagger.PfDeepCSVTagInfos
akFilter3PFPfDeepCSVJetTags = akFilter3PFbTagger.PfDeepCSVJetTags


akFilter3PFSoftPFMuonsTagInfos = akFilter3PFbTagger.SoftPFMuonsTagInfos
akFilter3PFSoftPFMuonBJetTags = akFilter3PFbTagger.SoftPFMuonBJetTags
akFilter3PFSoftPFMuonByIP3dBJetTags = akFilter3PFbTagger.SoftPFMuonByIP3dBJetTags
akFilter3PFSoftPFMuonByPtBJetTags = akFilter3PFbTagger.SoftPFMuonByPtBJetTags
akFilter3PFPatJetFlavourIdLegacy = cms.Sequence(akFilter3PFPatJetPartonAssociationLegacy*akFilter3PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akFilter3PFPatJetFlavourAssociation = akFilter3PFbTagger.PatJetFlavourAssociation
akFilter3PFPatJetFlavourId = cms.Sequence(akFilter3PFPatJetPartons*akFilter3PFPatJetFlavourAssociation)

#adding the subjet taggers
akFilter3PFSubjetImpactParameterTagInfos = akFilter3PFbTagger.SubjetImpactParameterTagInfos
akFilter3PFSubjetJetProbabilityBJetTags = akFilter3PFbTagger.SubjetJetProbabilityBJetTags
akFilter3PFSubjetSecondaryVertexTagInfos = akFilter3PFbTagger.SubjetSecondaryVertexTagInfos
akFilter3PFSubjetJetTracksAssociatorAtVertex = akFilter3PFbTagger.SubjetJetTracksAssociatorAtVertex
akFilter3PFCombinedSubjetSecondaryVertexBJetTags = akFilter3PFbTagger.CombinedSubjetSecondaryVertexBJetTags
akFilter3PFCombinedSubjetSecondaryVertexV2BJetTags = akFilter3PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

akFilter3PFJetBtaggingIP       = cms.Sequence(akFilter3PFImpactParameterTagInfos *
            (akFilter3PFTrackCountingHighEffBJetTags +
             akFilter3PFTrackCountingHighPurBJetTags +
             akFilter3PFJetProbabilityBJetTags +
             akFilter3PFJetBProbabilityBJetTags 
            ) *
	     akFilter3PFPfImpactParameterTagInfos 
            )

akFilter3PFJetBtaggingSV = cms.Sequence(akFilter3PFImpactParameterTagInfos
            *
            akFilter3PFSecondaryVertexTagInfos
            * (akFilter3PFSimpleSecondaryVertexHighEffBJetTags+
                akFilter3PFSimpleSecondaryVertexHighPurBJetTags+
                akFilter3PFCombinedSecondaryVertexBJetTags+
                akFilter3PFCombinedSecondaryVertexV2BJetTags
              ) *
	    akFilter3PFPfImpactParameterTagInfos *
	    akFilter3PFPfInclusiveSecondaryVertexFinderTagInfos *
	    akFilter3PFPfDeepCSVTagInfos *
	    akFilter3PFPfDeepCSVJetTags  
            )



akFilter3PFJetBtaggingMu = cms.Sequence(akFilter3PFSoftPFMuonsTagInfos * (akFilter3PFSoftPFMuonBJetTags
                +
                akFilter3PFSoftPFMuonByIP3dBJetTags
                +
                akFilter3PFSoftPFMuonByPtBJetTags               
              )
            )

akFilter3PFJetBtagging = cms.Sequence(akFilter3PFJetBtaggingIP
            *akFilter3PFJetBtaggingSV
#            *akFilter3PFJetBtaggingMu
            )

akFilter3PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akFilter3PFJets"),
        genJetMatch          = cms.InputTag("akFilter3PFmatch"),
        genPartonMatch       = cms.InputTag("akFilter3PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akFilter3PFcorr")),
        #JetPartonMapSource   = cms.InputTag("akFilter3PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akFilter3PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akFilter3PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akFilter3PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akFilter3PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akFilter3PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akFilter3PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akFilter3PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akFilter3PFJetBProbabilityBJetTags"),
            cms.InputTag("akFilter3PFJetProbabilityBJetTags"),
            #cms.InputTag("akFilter3PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akFilter3PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akFilter3PFTrackCountingHighEffBJetTags"),
            cms.InputTag("akFilter3PFTrackCountingHighPurBJetTags"),
            cms.InputTag("akFilter3PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akFilter3PFJetID"),
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

akFilter3PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("akFilter3PFJets"),
           	    R0  = cms.double( 0.3)
)
#ppDataDummy_akFilter3PFpatJetsWithBtagging.userData.userFloats.src += ['akFilter3PFNjettiness:tau1','akFilter3PFNjettiness:tau2','akFilter3PFNjettiness:tau3']

akFilter3PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akFilter3PFpatJetsWithBtagging"),
                                                             genjetTag = 'ak3GenJets',
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
                                                             bTagJetName = cms.untracked.string("akFilter3PF"),
                                                             jetName = cms.untracked.string("akFilter3PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akFilter3GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("akFilter3PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akFilter3PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akFilter3PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

#ENABLE_PPCALO_akFilter3PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_akFilter3PFJetAnalyzer.doExtendedFlavorTagging = False

akFilter3PFJetAnalyzer.trackSelection = akFilter3PFSecondaryVertexTagInfos.trackSelection
akFilter3PFJetAnalyzer.trackPairV0Filter = akFilter3PFSecondaryVertexTagInfos.vertexCuts.v0Filter

akFilter3PFJetSequence_mc = cms.Sequence(
                                                  #akFilter3PFclean
                                                  #*
                                                  akFilter3PFmatch
                                                  #*
                                                  #akFilter3PFmatchGroomed
                                                  *
                                                  akFilter3PFparton
                                                  *
                                                  akFilter3PFcorr
                                                  *
                                                  #akFilter3PFJetID
                                                  #*
                                                  #akFilter3PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  akFilter3PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
                                                  akFilter3PFJetTracksAssociatorAtVertex
                                                  *
                                                  akFilter3PFJetBtagging
                                                  *
                                                  akFilter3PFNjettiness
                                                  *
                                                  akFilter3PFpatJetsWithBtagging
                                                  *
                                                  akFilter3PFJetAnalyzer
                                                  )

akFilter3PFJetSequence_data = cms.Sequence(akFilter3PFcorr
                                                    *
                                                    #akFilter3PFJetID
                                                    #*
                                                    akFilter3PFJetTracksAssociatorAtVertex
                                                    *
                                                    akFilter3PFJetBtagging
                                                    *
                                                    akFilter3PFNjettiness
                                                    *
                                                    akFilter3PFpatJetsWithBtagging
                                                    *
                                                    akFilter3PFJetAnalyzer
                                                    )

akFilter3PFJetSequence_jec = cms.Sequence(akFilter3PFJetSequence_mc)
akFilter3PFJetSequence_mb = cms.Sequence(akFilter3PFJetSequence_mc)

akFilter3PFJetSequence = cms.Sequence(akFilter3PFJetSequence_mc)
