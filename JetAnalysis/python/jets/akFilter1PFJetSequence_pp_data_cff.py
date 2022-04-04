

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akFilter1PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter1PFJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

akFilter1PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter1GenJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

akFilter1PFparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter1PFJets")
                                                        )

akFilter1PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative','L2L3Residual'),
    src = cms.InputTag("akFilter1PFJets"),
    payload = "AK1PF"
    )

akFilter1PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akFilter1CaloJets'))

#akFilter1PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak1GenJets'))

akFilter1PFbTagger = bTaggers("akFilter1PF",0.1,True,True)

#create objects locally since they dont load properly otherwise
#akFilter1PFmatch = akFilter1PFbTagger.match
akFilter1PFparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter1PFJets"), matched = cms.InputTag("genParticles"))
akFilter1PFPatJetFlavourAssociationLegacy = akFilter1PFbTagger.PatJetFlavourAssociationLegacy
akFilter1PFPatJetPartons = akFilter1PFbTagger.PatJetPartons
akFilter1PFJetTracksAssociatorAtVertex = akFilter1PFbTagger.JetTracksAssociatorAtVertex
akFilter1PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akFilter1PFSimpleSecondaryVertexHighEffBJetTags = akFilter1PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter1PFSimpleSecondaryVertexHighPurBJetTags = akFilter1PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter1PFCombinedSecondaryVertexBJetTags = akFilter1PFbTagger.CombinedSecondaryVertexBJetTags
akFilter1PFCombinedSecondaryVertexV2BJetTags = akFilter1PFbTagger.CombinedSecondaryVertexV2BJetTags
akFilter1PFJetBProbabilityBJetTags = akFilter1PFbTagger.JetBProbabilityBJetTags
akFilter1PFSoftPFMuonByPtBJetTags = akFilter1PFbTagger.SoftPFMuonByPtBJetTags
akFilter1PFSoftPFMuonByIP3dBJetTags = akFilter1PFbTagger.SoftPFMuonByIP3dBJetTags
akFilter1PFTrackCountingHighEffBJetTags = akFilter1PFbTagger.TrackCountingHighEffBJetTags
akFilter1PFTrackCountingHighPurBJetTags = akFilter1PFbTagger.TrackCountingHighPurBJetTags
akFilter1PFPatJetPartonAssociationLegacy = akFilter1PFbTagger.PatJetPartonAssociationLegacy

akFilter1PFImpactParameterTagInfos = akFilter1PFbTagger.ImpactParameterTagInfos
akFilter1PFPfImpactParameterTagInfos = akFilter1PFbTagger.PfImpactParameterTagInfos
akFilter1PFJetProbabilityBJetTags = akFilter1PFbTagger.JetProbabilityBJetTags

akFilter1PFSecondaryVertexTagInfos = akFilter1PFbTagger.SecondaryVertexTagInfos
akFilter1PFSimpleSecondaryVertexHighEffBJetTags = akFilter1PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter1PFSimpleSecondaryVertexHighPurBJetTags = akFilter1PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter1PFCombinedSecondaryVertexBJetTags = akFilter1PFbTagger.CombinedSecondaryVertexBJetTags
akFilter1PFCombinedSecondaryVertexV2BJetTags = akFilter1PFbTagger.CombinedSecondaryVertexV2BJetTags
akFilter1PFPfInclusiveSecondaryVertexFinderTagInfos = akFilter1PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
akFilter1PFPfDeepCSVTagInfos = akFilter1PFbTagger.PfDeepCSVTagInfos
akFilter1PFPfDeepCSVJetTags = akFilter1PFbTagger.PfDeepCSVJetTags


akFilter1PFSoftPFMuonsTagInfos = akFilter1PFbTagger.SoftPFMuonsTagInfos
akFilter1PFSoftPFMuonBJetTags = akFilter1PFbTagger.SoftPFMuonBJetTags
akFilter1PFSoftPFMuonByIP3dBJetTags = akFilter1PFbTagger.SoftPFMuonByIP3dBJetTags
akFilter1PFSoftPFMuonByPtBJetTags = akFilter1PFbTagger.SoftPFMuonByPtBJetTags
akFilter1PFPatJetFlavourIdLegacy = cms.Sequence(akFilter1PFPatJetPartonAssociationLegacy*akFilter1PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akFilter1PFPatJetFlavourAssociation = akFilter1PFbTagger.PatJetFlavourAssociation
akFilter1PFPatJetFlavourId = cms.Sequence(akFilter1PFPatJetPartons*akFilter1PFPatJetFlavourAssociation)

#adding the subjet taggers
akFilter1PFSubjetImpactParameterTagInfos = akFilter1PFbTagger.SubjetImpactParameterTagInfos
akFilter1PFSubjetJetProbabilityBJetTags = akFilter1PFbTagger.SubjetJetProbabilityBJetTags
akFilter1PFSubjetSecondaryVertexTagInfos = akFilter1PFbTagger.SubjetSecondaryVertexTagInfos
akFilter1PFSubjetJetTracksAssociatorAtVertex = akFilter1PFbTagger.SubjetJetTracksAssociatorAtVertex
akFilter1PFCombinedSubjetSecondaryVertexBJetTags = akFilter1PFbTagger.CombinedSubjetSecondaryVertexBJetTags
akFilter1PFCombinedSubjetSecondaryVertexV2BJetTags = akFilter1PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

akFilter1PFJetBtaggingIP       = cms.Sequence(akFilter1PFImpactParameterTagInfos *
            (akFilter1PFTrackCountingHighEffBJetTags +
             akFilter1PFTrackCountingHighPurBJetTags +
             akFilter1PFJetProbabilityBJetTags +
             akFilter1PFJetBProbabilityBJetTags 
            ) *
	     akFilter1PFPfImpactParameterTagInfos 
            )

akFilter1PFJetBtaggingSV = cms.Sequence(akFilter1PFImpactParameterTagInfos
            *
            akFilter1PFSecondaryVertexTagInfos
            * (akFilter1PFSimpleSecondaryVertexHighEffBJetTags+
                akFilter1PFSimpleSecondaryVertexHighPurBJetTags+
                akFilter1PFCombinedSecondaryVertexBJetTags+
                akFilter1PFCombinedSecondaryVertexV2BJetTags
              ) *
	    akFilter1PFPfImpactParameterTagInfos *
	    akFilter1PFPfInclusiveSecondaryVertexFinderTagInfos *
	    akFilter1PFPfDeepCSVTagInfos *
	    akFilter1PFPfDeepCSVJetTags  
            )



akFilter1PFJetBtaggingMu = cms.Sequence(akFilter1PFSoftPFMuonsTagInfos * (akFilter1PFSoftPFMuonBJetTags
                +
                akFilter1PFSoftPFMuonByIP3dBJetTags
                +
                akFilter1PFSoftPFMuonByPtBJetTags               
              )
            )

akFilter1PFJetBtagging = cms.Sequence(akFilter1PFJetBtaggingIP
            *akFilter1PFJetBtaggingSV
#            *akFilter1PFJetBtaggingMu
            )

akFilter1PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akFilter1PFJets"),
        genJetMatch          = cms.InputTag("akFilter1PFmatch"),
        genPartonMatch       = cms.InputTag("akFilter1PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akFilter1PFcorr")),
        #JetPartonMapSource   = cms.InputTag("akFilter1PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akFilter1PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akFilter1PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akFilter1PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akFilter1PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akFilter1PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akFilter1PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akFilter1PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akFilter1PFJetBProbabilityBJetTags"),
            cms.InputTag("akFilter1PFJetProbabilityBJetTags"),
            #cms.InputTag("akFilter1PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akFilter1PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akFilter1PFTrackCountingHighEffBJetTags"),
            cms.InputTag("akFilter1PFTrackCountingHighPurBJetTags"),
            cms.InputTag("akFilter1PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akFilter1PFJetID"),
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

akFilter1PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("akFilter1PFJets"),
           	    R0  = cms.double( 0.1)
)
#ppDataDummy_akFilter1PFpatJetsWithBtagging.userData.userFloats.src += ['akFilter1PFNjettiness:tau1','akFilter1PFNjettiness:tau2','akFilter1PFNjettiness:tau3']

akFilter1PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akFilter1PFpatJetsWithBtagging"),
                                                             genjetTag = 'ak1GenJets',
                                                             rParam = 0.1,
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
                                                             bTagJetName = cms.untracked.string("akFilter1PF"),
                                                             jetName = cms.untracked.string("akFilter1PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akFilter1GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(False),
							     jetFlavourInfos = cms.InputTag("akFilter1PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akFilter1PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akFilter1PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = False
                                                            )

#ENABLE_PPCALO_akFilter1PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_akFilter1PFJetAnalyzer.doExtendedFlavorTagging = False

akFilter1PFJetAnalyzer.trackSelection = akFilter1PFSecondaryVertexTagInfos.trackSelection
akFilter1PFJetAnalyzer.trackPairV0Filter = akFilter1PFSecondaryVertexTagInfos.vertexCuts.v0Filter

akFilter1PFJetSequence_mc = cms.Sequence(
                                                  #akFilter1PFclean
                                                  #*
                                                  akFilter1PFmatch
                                                  #*
                                                  #akFilter1PFmatchGroomed
                                                  *
                                                  akFilter1PFparton
                                                  *
                                                  akFilter1PFcorr
                                                  *
                                                  #akFilter1PFJetID
                                                  #*
                                                  #akFilter1PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  akFilter1PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
                                                  akFilter1PFJetTracksAssociatorAtVertex
                                                  *
                                                  akFilter1PFJetBtagging
                                                  *
                                                  akFilter1PFNjettiness
                                                  *
                                                  akFilter1PFpatJetsWithBtagging
                                                  *
                                                  akFilter1PFJetAnalyzer
                                                  )

akFilter1PFJetSequence_data = cms.Sequence(akFilter1PFcorr
                                                    *
                                                    #akFilter1PFJetID
                                                    #*
                                                    akFilter1PFJetTracksAssociatorAtVertex
                                                    *
                                                    akFilter1PFJetBtagging
                                                    *
                                                    akFilter1PFNjettiness
                                                    *
                                                    akFilter1PFpatJetsWithBtagging
                                                    *
                                                    akFilter1PFJetAnalyzer
                                                    )

akFilter1PFJetSequence_jec = cms.Sequence(akFilter1PFJetSequence_mc)
akFilter1PFJetSequence_mb = cms.Sequence(akFilter1PFJetSequence_mc)

akFilter1PFJetSequence = cms.Sequence(akFilter1PFJetSequence_data)
