

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akSoftDrop3PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop3PFJets"),
    matched = cms.InputTag("ak3GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.3
    )

akSoftDrop3PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop3GenJets"),
    matched = cms.InputTag("ak3GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.3
    )

akSoftDrop3PFparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop3PFJets")
                                                        )

akSoftDrop3PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akSoftDrop3PFJets"),
    payload = "AK3PF"
    )

akSoftDrop3PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akSoftDrop3CaloJets'))

#akSoftDrop3PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak3GenJets'))

akSoftDrop3PFbTagger = bTaggers("akSoftDrop3PF",0.3,True,True)

#create objects locally since they dont load properly otherwise
#akSoftDrop3PFmatch = akSoftDrop3PFbTagger.match
akSoftDrop3PFparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop3PFJets"), matched = cms.InputTag("genParticles"))
akSoftDrop3PFPatJetFlavourAssociationLegacy = akSoftDrop3PFbTagger.PatJetFlavourAssociationLegacy
akSoftDrop3PFPatJetPartons = akSoftDrop3PFbTagger.PatJetPartons
akSoftDrop3PFJetTracksAssociatorAtVertex = akSoftDrop3PFbTagger.JetTracksAssociatorAtVertex
akSoftDrop3PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akSoftDrop3PFSimpleSecondaryVertexHighEffBJetTags = akSoftDrop3PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop3PFSimpleSecondaryVertexHighPurBJetTags = akSoftDrop3PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop3PFCombinedSecondaryVertexBJetTags = akSoftDrop3PFbTagger.CombinedSecondaryVertexBJetTags
akSoftDrop3PFCombinedSecondaryVertexV2BJetTags = akSoftDrop3PFbTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop3PFJetBProbabilityBJetTags = akSoftDrop3PFbTagger.JetBProbabilityBJetTags
akSoftDrop3PFSoftPFMuonByPtBJetTags = akSoftDrop3PFbTagger.SoftPFMuonByPtBJetTags
akSoftDrop3PFSoftPFMuonByIP3dBJetTags = akSoftDrop3PFbTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop3PFTrackCountingHighEffBJetTags = akSoftDrop3PFbTagger.TrackCountingHighEffBJetTags
akSoftDrop3PFTrackCountingHighPurBJetTags = akSoftDrop3PFbTagger.TrackCountingHighPurBJetTags
akSoftDrop3PFPatJetPartonAssociationLegacy = akSoftDrop3PFbTagger.PatJetPartonAssociationLegacy

akSoftDrop3PFImpactParameterTagInfos = akSoftDrop3PFbTagger.ImpactParameterTagInfos
akSoftDrop3PFPfImpactParameterTagInfos = akSoftDrop3PFbTagger.PfImpactParameterTagInfos
akSoftDrop3PFJetProbabilityBJetTags = akSoftDrop3PFbTagger.JetProbabilityBJetTags

akSoftDrop3PFSecondaryVertexTagInfos = akSoftDrop3PFbTagger.SecondaryVertexTagInfos
akSoftDrop3PFSimpleSecondaryVertexHighEffBJetTags = akSoftDrop3PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop3PFSimpleSecondaryVertexHighPurBJetTags = akSoftDrop3PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop3PFCombinedSecondaryVertexBJetTags = akSoftDrop3PFbTagger.CombinedSecondaryVertexBJetTags
akSoftDrop3PFCombinedSecondaryVertexV2BJetTags = akSoftDrop3PFbTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop3PFPfInclusiveSecondaryVertexFinderTagInfos = akSoftDrop3PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
akSoftDrop3PFPfDeepCSVTagInfos = akSoftDrop3PFbTagger.PfDeepCSVTagInfos
akSoftDrop3PFPfDeepCSVJetTags = akSoftDrop3PFbTagger.PfDeepCSVJetTags


akSoftDrop3PFSoftPFMuonsTagInfos = akSoftDrop3PFbTagger.SoftPFMuonsTagInfos
akSoftDrop3PFSoftPFMuonBJetTags = akSoftDrop3PFbTagger.SoftPFMuonBJetTags
akSoftDrop3PFSoftPFMuonByIP3dBJetTags = akSoftDrop3PFbTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop3PFSoftPFMuonByPtBJetTags = akSoftDrop3PFbTagger.SoftPFMuonByPtBJetTags
akSoftDrop3PFPatJetFlavourIdLegacy = cms.Sequence(akSoftDrop3PFPatJetPartonAssociationLegacy*akSoftDrop3PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akSoftDrop3PFPatJetFlavourAssociation = akSoftDrop3PFbTagger.PatJetFlavourAssociation
akSoftDrop3PFPatJetFlavourId = cms.Sequence(akSoftDrop3PFPatJetPartons*akSoftDrop3PFPatJetFlavourAssociation)

#adding the subjet taggers
akSoftDrop3PFSubjetImpactParameterTagInfos = akSoftDrop3PFbTagger.SubjetImpactParameterTagInfos
akSoftDrop3PFSubjetJetProbabilityBJetTags = akSoftDrop3PFbTagger.SubjetJetProbabilityBJetTags
akSoftDrop3PFSubjetSecondaryVertexTagInfos = akSoftDrop3PFbTagger.SubjetSecondaryVertexTagInfos
akSoftDrop3PFSubjetJetTracksAssociatorAtVertex = akSoftDrop3PFbTagger.SubjetJetTracksAssociatorAtVertex
akSoftDrop3PFCombinedSubjetSecondaryVertexBJetTags = akSoftDrop3PFbTagger.CombinedSubjetSecondaryVertexBJetTags
akSoftDrop3PFCombinedSubjetSecondaryVertexV2BJetTags = akSoftDrop3PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

akSoftDrop3PFJetBtaggingIP       = cms.Sequence(akSoftDrop3PFImpactParameterTagInfos *
            (akSoftDrop3PFTrackCountingHighEffBJetTags +
             akSoftDrop3PFTrackCountingHighPurBJetTags +
             akSoftDrop3PFJetProbabilityBJetTags +
             akSoftDrop3PFJetBProbabilityBJetTags 
            ) *
	     akSoftDrop3PFPfImpactParameterTagInfos 
            )

akSoftDrop3PFJetBtaggingSV = cms.Sequence(akSoftDrop3PFImpactParameterTagInfos
            *
            akSoftDrop3PFSecondaryVertexTagInfos
            * (akSoftDrop3PFSimpleSecondaryVertexHighEffBJetTags+
                akSoftDrop3PFSimpleSecondaryVertexHighPurBJetTags+
                akSoftDrop3PFCombinedSecondaryVertexBJetTags+
                akSoftDrop3PFCombinedSecondaryVertexV2BJetTags
              ) *
	    akSoftDrop3PFPfImpactParameterTagInfos *
	    akSoftDrop3PFPfInclusiveSecondaryVertexFinderTagInfos *
	    akSoftDrop3PFPfDeepCSVTagInfos *
	    akSoftDrop3PFPfDeepCSVJetTags  
            )



akSoftDrop3PFJetBtaggingMu = cms.Sequence(akSoftDrop3PFSoftPFMuonsTagInfos * (akSoftDrop3PFSoftPFMuonBJetTags
                +
                akSoftDrop3PFSoftPFMuonByIP3dBJetTags
                +
                akSoftDrop3PFSoftPFMuonByPtBJetTags               
              )
            )

akSoftDrop3PFJetBtagging = cms.Sequence(akSoftDrop3PFJetBtaggingIP
            *akSoftDrop3PFJetBtaggingSV
#            *akSoftDrop3PFJetBtaggingMu
            )

akSoftDrop3PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akSoftDrop3PFJets"),
        genJetMatch          = cms.InputTag("akSoftDrop3PFmatch"),
        genPartonMatch       = cms.InputTag("akSoftDrop3PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akSoftDrop3PFcorr")),
        #JetPartonMapSource   = cms.InputTag("akSoftDrop3PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akSoftDrop3PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akSoftDrop3PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akSoftDrop3PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akSoftDrop3PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akSoftDrop3PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akSoftDrop3PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akSoftDrop3PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akSoftDrop3PFJetBProbabilityBJetTags"),
            cms.InputTag("akSoftDrop3PFJetProbabilityBJetTags"),
            #cms.InputTag("akSoftDrop3PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akSoftDrop3PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akSoftDrop3PFTrackCountingHighEffBJetTags"),
            cms.InputTag("akSoftDrop3PFTrackCountingHighPurBJetTags"),
            cms.InputTag("akSoftDrop3PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akSoftDrop3PFJetID"),
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

akSoftDrop3PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("akSoftDrop3PFJets"),
           	    R0  = cms.double( 0.3)
)
#ppDataDummy_akSoftDrop3PFpatJetsWithBtagging.userData.userFloats.src += ['akSoftDrop3PFNjettiness:tau1','akSoftDrop3PFNjettiness:tau2','akSoftDrop3PFNjettiness:tau3']

akSoftDrop3PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akSoftDrop3PFpatJetsWithBtagging"),
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
                                                             bTagJetName = cms.untracked.string("akSoftDrop3PF"),
                                                             jetName = cms.untracked.string("akSoftDrop3PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akSoftDrop3GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("akSoftDrop3PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akSoftDrop3PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akSoftDrop3PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

#ENABLE_PPCALO_akSoftDrop3PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_akSoftDrop3PFJetAnalyzer.doExtendedFlavorTagging = False

akSoftDrop3PFJetAnalyzer.trackSelection = akSoftDrop3PFSecondaryVertexTagInfos.trackSelection
akSoftDrop3PFJetAnalyzer.trackPairV0Filter = akSoftDrop3PFSecondaryVertexTagInfos.vertexCuts.v0Filter

akSoftDrop3PFJetSequence_mc = cms.Sequence(
                                                  #akSoftDrop3PFclean
                                                  #*
                                                  akSoftDrop3PFmatch
                                                  #*
                                                  #akSoftDrop3PFmatchGroomed
                                                  *
                                                  akSoftDrop3PFparton
                                                  *
                                                  akSoftDrop3PFcorr
                                                  *
                                                  #akSoftDrop3PFJetID
                                                  #*
                                                  #akSoftDrop3PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  akSoftDrop3PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
                                                  akSoftDrop3PFJetTracksAssociatorAtVertex
                                                  *
                                                  akSoftDrop3PFJetBtagging
                                                  *
                                                  akSoftDrop3PFNjettiness
                                                  *
                                                  akSoftDrop3PFpatJetsWithBtagging
                                                  *
                                                  akSoftDrop3PFJetAnalyzer
                                                  )

akSoftDrop3PFJetSequence_data = cms.Sequence(akSoftDrop3PFcorr
                                                    *
                                                    #akSoftDrop3PFJetID
                                                    #*
                                                    akSoftDrop3PFJetTracksAssociatorAtVertex
                                                    *
                                                    akSoftDrop3PFJetBtagging
                                                    *
                                                    akSoftDrop3PFNjettiness
                                                    *
                                                    akSoftDrop3PFpatJetsWithBtagging
                                                    *
                                                    akSoftDrop3PFJetAnalyzer
                                                    )

akSoftDrop3PFJetSequence_jec = cms.Sequence(akSoftDrop3PFJetSequence_mc)
akSoftDrop3PFJetSequence_mb = cms.Sequence(akSoftDrop3PFJetSequence_mc)

akSoftDrop3PFJetSequence = cms.Sequence(akSoftDrop3PFJetSequence_jec)
akSoftDrop3PFJetAnalyzer.genPtMin = cms.untracked.double(1)
akSoftDrop3PFJetAnalyzer.jetPtMin = cms.double(1)
akSoftDrop3PFJetAnalyzer.doSubEvent = True
