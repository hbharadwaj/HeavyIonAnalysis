

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akFilter5PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter5PFJets"),
    matched = cms.InputTag("ak5GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.5
    )

akFilter5PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter5GenJets"),
    matched = cms.InputTag("ak5GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.5
    )

akFilter5PFparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter5PFJets")
                                                        )

akFilter5PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative','L2L3Residual'),
    src = cms.InputTag("akFilter5PFJets"),
    payload = "AK5PF"
    )

akFilter5PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akFilter5CaloJets'))

#akFilter5PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak5GenJets'))

akFilter5PFbTagger = bTaggers("akFilter5PF",0.5,True,True)

#create objects locally since they dont load properly otherwise
#akFilter5PFmatch = akFilter5PFbTagger.match
akFilter5PFparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter5PFJets"), matched = cms.InputTag("genParticles"))
akFilter5PFPatJetFlavourAssociationLegacy = akFilter5PFbTagger.PatJetFlavourAssociationLegacy
akFilter5PFPatJetPartons = akFilter5PFbTagger.PatJetPartons
akFilter5PFJetTracksAssociatorAtVertex = akFilter5PFbTagger.JetTracksAssociatorAtVertex
akFilter5PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akFilter5PFSimpleSecondaryVertexHighEffBJetTags = akFilter5PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter5PFSimpleSecondaryVertexHighPurBJetTags = akFilter5PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter5PFCombinedSecondaryVertexBJetTags = akFilter5PFbTagger.CombinedSecondaryVertexBJetTags
akFilter5PFCombinedSecondaryVertexV2BJetTags = akFilter5PFbTagger.CombinedSecondaryVertexV2BJetTags
akFilter5PFJetBProbabilityBJetTags = akFilter5PFbTagger.JetBProbabilityBJetTags
akFilter5PFSoftPFMuonByPtBJetTags = akFilter5PFbTagger.SoftPFMuonByPtBJetTags
akFilter5PFSoftPFMuonByIP3dBJetTags = akFilter5PFbTagger.SoftPFMuonByIP3dBJetTags
akFilter5PFTrackCountingHighEffBJetTags = akFilter5PFbTagger.TrackCountingHighEffBJetTags
akFilter5PFTrackCountingHighPurBJetTags = akFilter5PFbTagger.TrackCountingHighPurBJetTags
akFilter5PFPatJetPartonAssociationLegacy = akFilter5PFbTagger.PatJetPartonAssociationLegacy

akFilter5PFImpactParameterTagInfos = akFilter5PFbTagger.ImpactParameterTagInfos
akFilter5PFPfImpactParameterTagInfos = akFilter5PFbTagger.PfImpactParameterTagInfos
akFilter5PFJetProbabilityBJetTags = akFilter5PFbTagger.JetProbabilityBJetTags

akFilter5PFSecondaryVertexTagInfos = akFilter5PFbTagger.SecondaryVertexTagInfos
akFilter5PFSimpleSecondaryVertexHighEffBJetTags = akFilter5PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter5PFSimpleSecondaryVertexHighPurBJetTags = akFilter5PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter5PFCombinedSecondaryVertexBJetTags = akFilter5PFbTagger.CombinedSecondaryVertexBJetTags
akFilter5PFCombinedSecondaryVertexV2BJetTags = akFilter5PFbTagger.CombinedSecondaryVertexV2BJetTags
akFilter5PFPfInclusiveSecondaryVertexFinderTagInfos = akFilter5PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
akFilter5PFPfDeepCSVTagInfos = akFilter5PFbTagger.PfDeepCSVTagInfos
akFilter5PFPfDeepCSVJetTags = akFilter5PFbTagger.PfDeepCSVJetTags


akFilter5PFSoftPFMuonsTagInfos = akFilter5PFbTagger.SoftPFMuonsTagInfos
akFilter5PFSoftPFMuonBJetTags = akFilter5PFbTagger.SoftPFMuonBJetTags
akFilter5PFSoftPFMuonByIP3dBJetTags = akFilter5PFbTagger.SoftPFMuonByIP3dBJetTags
akFilter5PFSoftPFMuonByPtBJetTags = akFilter5PFbTagger.SoftPFMuonByPtBJetTags
akFilter5PFPatJetFlavourIdLegacy = cms.Sequence(akFilter5PFPatJetPartonAssociationLegacy*akFilter5PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akFilter5PFPatJetFlavourAssociation = akFilter5PFbTagger.PatJetFlavourAssociation
akFilter5PFPatJetFlavourId = cms.Sequence(akFilter5PFPatJetPartons*akFilter5PFPatJetFlavourAssociation)

#adding the subjet taggers
akFilter5PFSubjetImpactParameterTagInfos = akFilter5PFbTagger.SubjetImpactParameterTagInfos
akFilter5PFSubjetJetProbabilityBJetTags = akFilter5PFbTagger.SubjetJetProbabilityBJetTags
akFilter5PFSubjetSecondaryVertexTagInfos = akFilter5PFbTagger.SubjetSecondaryVertexTagInfos
akFilter5PFSubjetJetTracksAssociatorAtVertex = akFilter5PFbTagger.SubjetJetTracksAssociatorAtVertex
akFilter5PFCombinedSubjetSecondaryVertexBJetTags = akFilter5PFbTagger.CombinedSubjetSecondaryVertexBJetTags
akFilter5PFCombinedSubjetSecondaryVertexV2BJetTags = akFilter5PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

akFilter5PFJetBtaggingIP       = cms.Sequence(akFilter5PFImpactParameterTagInfos *
            (akFilter5PFTrackCountingHighEffBJetTags +
             akFilter5PFTrackCountingHighPurBJetTags +
             akFilter5PFJetProbabilityBJetTags +
             akFilter5PFJetBProbabilityBJetTags 
            ) *
	     akFilter5PFPfImpactParameterTagInfos 
            )

akFilter5PFJetBtaggingSV = cms.Sequence(akFilter5PFImpactParameterTagInfos
            *
            akFilter5PFSecondaryVertexTagInfos
            * (akFilter5PFSimpleSecondaryVertexHighEffBJetTags+
                akFilter5PFSimpleSecondaryVertexHighPurBJetTags+
                akFilter5PFCombinedSecondaryVertexBJetTags+
                akFilter5PFCombinedSecondaryVertexV2BJetTags
              ) *
	    akFilter5PFPfImpactParameterTagInfos *
	    akFilter5PFPfInclusiveSecondaryVertexFinderTagInfos *
	    akFilter5PFPfDeepCSVTagInfos *
	    akFilter5PFPfDeepCSVJetTags  
            )



akFilter5PFJetBtaggingMu = cms.Sequence(akFilter5PFSoftPFMuonsTagInfos * (akFilter5PFSoftPFMuonBJetTags
                +
                akFilter5PFSoftPFMuonByIP3dBJetTags
                +
                akFilter5PFSoftPFMuonByPtBJetTags               
              )
            )

akFilter5PFJetBtagging = cms.Sequence(akFilter5PFJetBtaggingIP
            *akFilter5PFJetBtaggingSV
#            *akFilter5PFJetBtaggingMu
            )

akFilter5PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akFilter5PFJets"),
        genJetMatch          = cms.InputTag("akFilter5PFmatch"),
        genPartonMatch       = cms.InputTag("akFilter5PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akFilter5PFcorr")),
        #JetPartonMapSource   = cms.InputTag("akFilter5PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akFilter5PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akFilter5PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akFilter5PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akFilter5PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akFilter5PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akFilter5PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akFilter5PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akFilter5PFJetBProbabilityBJetTags"),
            cms.InputTag("akFilter5PFJetProbabilityBJetTags"),
            #cms.InputTag("akFilter5PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akFilter5PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akFilter5PFTrackCountingHighEffBJetTags"),
            cms.InputTag("akFilter5PFTrackCountingHighPurBJetTags"),
            cms.InputTag("akFilter5PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akFilter5PFJetID"),
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

akFilter5PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("akFilter5PFJets"),
           	    R0  = cms.double( 0.5)
)
#ppDataDummy_akFilter5PFpatJetsWithBtagging.userData.userFloats.src += ['akFilter5PFNjettiness:tau1','akFilter5PFNjettiness:tau2','akFilter5PFNjettiness:tau3']

akFilter5PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akFilter5PFpatJetsWithBtagging"),
                                                             genjetTag = 'ak5GenJets',
                                                             rParam = 0.5,
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
                                                             bTagJetName = cms.untracked.string("akFilter5PF"),
                                                             jetName = cms.untracked.string("akFilter5PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akFilter5GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(False),
							     jetFlavourInfos = cms.InputTag("akFilter5PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akFilter5PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akFilter5PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = False
                                                            )

#ENABLE_PPCALO_akFilter5PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_akFilter5PFJetAnalyzer.doExtendedFlavorTagging = False

akFilter5PFJetAnalyzer.trackSelection = akFilter5PFSecondaryVertexTagInfos.trackSelection
akFilter5PFJetAnalyzer.trackPairV0Filter = akFilter5PFSecondaryVertexTagInfos.vertexCuts.v0Filter

akFilter5PFJetSequence_mc = cms.Sequence(
                                                  #akFilter5PFclean
                                                  #*
                                                  akFilter5PFmatch
                                                  #*
                                                  #akFilter5PFmatchGroomed
                                                  *
                                                  akFilter5PFparton
                                                  *
                                                  akFilter5PFcorr
                                                  *
                                                  #akFilter5PFJetID
                                                  #*
                                                  #akFilter5PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  akFilter5PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
                                                  akFilter5PFJetTracksAssociatorAtVertex
                                                  *
                                                  akFilter5PFJetBtagging
                                                  *
                                                  akFilter5PFNjettiness
                                                  *
                                                  akFilter5PFpatJetsWithBtagging
                                                  *
                                                  akFilter5PFJetAnalyzer
                                                  )

akFilter5PFJetSequence_data = cms.Sequence(akFilter5PFcorr
                                                    *
                                                    #akFilter5PFJetID
                                                    #*
                                                    akFilter5PFJetTracksAssociatorAtVertex
                                                    *
                                                    akFilter5PFJetBtagging
                                                    *
                                                    akFilter5PFNjettiness
                                                    *
                                                    akFilter5PFpatJetsWithBtagging
                                                    *
                                                    akFilter5PFJetAnalyzer
                                                    )

akFilter5PFJetSequence_jec = cms.Sequence(akFilter5PFJetSequence_mc)
akFilter5PFJetSequence_mb = cms.Sequence(akFilter5PFJetSequence_mc)

akFilter5PFJetSequence = cms.Sequence(akFilter5PFJetSequence_data)
