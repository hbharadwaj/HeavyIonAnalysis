

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akSoftDrop5PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop5PFJets"),
    matched = cms.InputTag("ak5GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.5
    )

akSoftDrop5PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop5GenJets"),
    matched = cms.InputTag("ak5GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.5
    )

akSoftDrop5PFparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop5PFJets")
                                                        )

akSoftDrop5PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akSoftDrop5PFJets"),
    payload = "AK5PF"
    )

akSoftDrop5PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akSoftDrop5CaloJets'))

#akSoftDrop5PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak5GenJets'))

akSoftDrop5PFbTagger = bTaggers("akSoftDrop5PF",0.5,True,True)

#create objects locally since they dont load properly otherwise
#akSoftDrop5PFmatch = akSoftDrop5PFbTagger.match
akSoftDrop5PFparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop5PFJets"), matched = cms.InputTag("genParticles"))
akSoftDrop5PFPatJetFlavourAssociationLegacy = akSoftDrop5PFbTagger.PatJetFlavourAssociationLegacy
akSoftDrop5PFPatJetPartons = akSoftDrop5PFbTagger.PatJetPartons
akSoftDrop5PFJetTracksAssociatorAtVertex = akSoftDrop5PFbTagger.JetTracksAssociatorAtVertex
akSoftDrop5PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akSoftDrop5PFSimpleSecondaryVertexHighEffBJetTags = akSoftDrop5PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop5PFSimpleSecondaryVertexHighPurBJetTags = akSoftDrop5PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop5PFCombinedSecondaryVertexBJetTags = akSoftDrop5PFbTagger.CombinedSecondaryVertexBJetTags
akSoftDrop5PFCombinedSecondaryVertexV2BJetTags = akSoftDrop5PFbTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop5PFJetBProbabilityBJetTags = akSoftDrop5PFbTagger.JetBProbabilityBJetTags
akSoftDrop5PFSoftPFMuonByPtBJetTags = akSoftDrop5PFbTagger.SoftPFMuonByPtBJetTags
akSoftDrop5PFSoftPFMuonByIP3dBJetTags = akSoftDrop5PFbTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop5PFTrackCountingHighEffBJetTags = akSoftDrop5PFbTagger.TrackCountingHighEffBJetTags
akSoftDrop5PFTrackCountingHighPurBJetTags = akSoftDrop5PFbTagger.TrackCountingHighPurBJetTags
akSoftDrop5PFPatJetPartonAssociationLegacy = akSoftDrop5PFbTagger.PatJetPartonAssociationLegacy

akSoftDrop5PFImpactParameterTagInfos = akSoftDrop5PFbTagger.ImpactParameterTagInfos
akSoftDrop5PFPfImpactParameterTagInfos = akSoftDrop5PFbTagger.PfImpactParameterTagInfos
akSoftDrop5PFJetProbabilityBJetTags = akSoftDrop5PFbTagger.JetProbabilityBJetTags

akSoftDrop5PFSecondaryVertexTagInfos = akSoftDrop5PFbTagger.SecondaryVertexTagInfos
akSoftDrop5PFSimpleSecondaryVertexHighEffBJetTags = akSoftDrop5PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop5PFSimpleSecondaryVertexHighPurBJetTags = akSoftDrop5PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop5PFCombinedSecondaryVertexBJetTags = akSoftDrop5PFbTagger.CombinedSecondaryVertexBJetTags
akSoftDrop5PFCombinedSecondaryVertexV2BJetTags = akSoftDrop5PFbTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop5PFPfInclusiveSecondaryVertexFinderTagInfos = akSoftDrop5PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
akSoftDrop5PFPfDeepCSVTagInfos = akSoftDrop5PFbTagger.PfDeepCSVTagInfos
akSoftDrop5PFPfDeepCSVJetTags = akSoftDrop5PFbTagger.PfDeepCSVJetTags


akSoftDrop5PFSoftPFMuonsTagInfos = akSoftDrop5PFbTagger.SoftPFMuonsTagInfos
akSoftDrop5PFSoftPFMuonBJetTags = akSoftDrop5PFbTagger.SoftPFMuonBJetTags
akSoftDrop5PFSoftPFMuonByIP3dBJetTags = akSoftDrop5PFbTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop5PFSoftPFMuonByPtBJetTags = akSoftDrop5PFbTagger.SoftPFMuonByPtBJetTags
akSoftDrop5PFPatJetFlavourIdLegacy = cms.Sequence(akSoftDrop5PFPatJetPartonAssociationLegacy*akSoftDrop5PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akSoftDrop5PFPatJetFlavourAssociation = akSoftDrop5PFbTagger.PatJetFlavourAssociation
akSoftDrop5PFPatJetFlavourId = cms.Sequence(akSoftDrop5PFPatJetPartons*akSoftDrop5PFPatJetFlavourAssociation)

#adding the subjet taggers
akSoftDrop5PFSubjetImpactParameterTagInfos = akSoftDrop5PFbTagger.SubjetImpactParameterTagInfos
akSoftDrop5PFSubjetJetProbabilityBJetTags = akSoftDrop5PFbTagger.SubjetJetProbabilityBJetTags
akSoftDrop5PFSubjetSecondaryVertexTagInfos = akSoftDrop5PFbTagger.SubjetSecondaryVertexTagInfos
akSoftDrop5PFSubjetJetTracksAssociatorAtVertex = akSoftDrop5PFbTagger.SubjetJetTracksAssociatorAtVertex
akSoftDrop5PFCombinedSubjetSecondaryVertexBJetTags = akSoftDrop5PFbTagger.CombinedSubjetSecondaryVertexBJetTags
akSoftDrop5PFCombinedSubjetSecondaryVertexV2BJetTags = akSoftDrop5PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

akSoftDrop5PFJetBtaggingIP       = cms.Sequence(akSoftDrop5PFImpactParameterTagInfos *
            (akSoftDrop5PFTrackCountingHighEffBJetTags +
             akSoftDrop5PFTrackCountingHighPurBJetTags +
             akSoftDrop5PFJetProbabilityBJetTags +
             akSoftDrop5PFJetBProbabilityBJetTags 
            ) *
	     akSoftDrop5PFPfImpactParameterTagInfos 
            )

akSoftDrop5PFJetBtaggingSV = cms.Sequence(akSoftDrop5PFImpactParameterTagInfos
            *
            akSoftDrop5PFSecondaryVertexTagInfos
            * (akSoftDrop5PFSimpleSecondaryVertexHighEffBJetTags+
                akSoftDrop5PFSimpleSecondaryVertexHighPurBJetTags+
                akSoftDrop5PFCombinedSecondaryVertexBJetTags+
                akSoftDrop5PFCombinedSecondaryVertexV2BJetTags
              ) *
	    akSoftDrop5PFPfImpactParameterTagInfos *
	    akSoftDrop5PFPfInclusiveSecondaryVertexFinderTagInfos *
	    akSoftDrop5PFPfDeepCSVTagInfos *
	    akSoftDrop5PFPfDeepCSVJetTags  
            )



akSoftDrop5PFJetBtaggingMu = cms.Sequence(akSoftDrop5PFSoftPFMuonsTagInfos * (akSoftDrop5PFSoftPFMuonBJetTags
                +
                akSoftDrop5PFSoftPFMuonByIP3dBJetTags
                +
                akSoftDrop5PFSoftPFMuonByPtBJetTags               
              )
            )

akSoftDrop5PFJetBtagging = cms.Sequence(akSoftDrop5PFJetBtaggingIP
            *akSoftDrop5PFJetBtaggingSV
#            *akSoftDrop5PFJetBtaggingMu
            )

akSoftDrop5PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akSoftDrop5PFJets"),
        genJetMatch          = cms.InputTag("akSoftDrop5PFmatch"),
        genPartonMatch       = cms.InputTag("akSoftDrop5PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akSoftDrop5PFcorr")),
        #JetPartonMapSource   = cms.InputTag("akSoftDrop5PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akSoftDrop5PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akSoftDrop5PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akSoftDrop5PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akSoftDrop5PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akSoftDrop5PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akSoftDrop5PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akSoftDrop5PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akSoftDrop5PFJetBProbabilityBJetTags"),
            cms.InputTag("akSoftDrop5PFJetProbabilityBJetTags"),
            #cms.InputTag("akSoftDrop5PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akSoftDrop5PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akSoftDrop5PFTrackCountingHighEffBJetTags"),
            cms.InputTag("akSoftDrop5PFTrackCountingHighPurBJetTags"),
            cms.InputTag("akSoftDrop5PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akSoftDrop5PFJetID"),
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

akSoftDrop5PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("akSoftDrop5PFJets"),
           	    R0  = cms.double( 0.5)
)
#ppDataDummy_akSoftDrop5PFpatJetsWithBtagging.userData.userFloats.src += ['akSoftDrop5PFNjettiness:tau1','akSoftDrop5PFNjettiness:tau2','akSoftDrop5PFNjettiness:tau3']

akSoftDrop5PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akSoftDrop5PFpatJetsWithBtagging"),
                                                             genjetTag = 'ak5GenJets',
                                                             rParam = 0.5,
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
                                                             bTagJetName = cms.untracked.string("akSoftDrop5PF"),
                                                             jetName = cms.untracked.string("akSoftDrop5PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(True),     
                                                             subjetGenTag = cms.untracked.InputTag("akSoftDrop5GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("akSoftDrop5PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akSoftDrop5PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akSoftDrop5PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

#ENABLE_PPCALO_akSoftDrop5PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_akSoftDrop5PFJetAnalyzer.doExtendedFlavorTagging = False

akSoftDrop5PFJetAnalyzer.trackSelection = akSoftDrop5PFSecondaryVertexTagInfos.trackSelection
akSoftDrop5PFJetAnalyzer.trackPairV0Filter = akSoftDrop5PFSecondaryVertexTagInfos.vertexCuts.v0Filter

akSoftDrop5PFJetSequence_mc = cms.Sequence(
                                                  #akSoftDrop5PFclean
                                                  #*
                                                  akSoftDrop5PFmatch
                                                  #*
                                                  #akSoftDrop5PFmatchGroomed
                                                  *
                                                  akSoftDrop5PFparton
                                                  *
                                                  akSoftDrop5PFcorr
                                                  *
                                                  #akSoftDrop5PFJetID
                                                  #*
                                                  #akSoftDrop5PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  akSoftDrop5PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
                                                  akSoftDrop5PFJetTracksAssociatorAtVertex
                                                  *
                                                  akSoftDrop5PFJetBtagging
                                                  *
                                                  akSoftDrop5PFNjettiness
                                                  *
                                                  akSoftDrop5PFpatJetsWithBtagging
                                                  *
                                                  akSoftDrop5PFJetAnalyzer
                                                  )

akSoftDrop5PFJetSequence_data = cms.Sequence(akSoftDrop5PFcorr
                                                    *
                                                    #akSoftDrop5PFJetID
                                                    #*
                                                    akSoftDrop5PFJetTracksAssociatorAtVertex
                                                    *
                                                    akSoftDrop5PFJetBtagging
                                                    *
                                                    akSoftDrop5PFNjettiness
                                                    *
                                                    akSoftDrop5PFpatJetsWithBtagging
                                                    *
                                                    akSoftDrop5PFJetAnalyzer
                                                    )

akSoftDrop5PFJetSequence_jec = cms.Sequence(akSoftDrop5PFJetSequence_mc)
akSoftDrop5PFJetSequence_mb = cms.Sequence(akSoftDrop5PFJetSequence_mc)

akSoftDrop5PFJetSequence = cms.Sequence(akSoftDrop5PFJetSequence_mc)
