

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akFilter4PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter4PFJets"),
    matched = cms.InputTag("ak4GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.4
    )

akFilter4PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter4GenJets"),
    matched = cms.InputTag("ak4GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.4
    )

akFilter4PFparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter4PFJets")
                                                        )

akFilter4PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akFilter4PFJets"),
    payload = "AK4PF"
    )

akFilter4PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akFilter4CaloJets'))

#akFilter4PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak4GenJets'))

akFilter4PFbTagger = bTaggers("akFilter4PF",0.4,True,True)

#create objects locally since they dont load properly otherwise
#akFilter4PFmatch = akFilter4PFbTagger.match
akFilter4PFparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter4PFJets"), matched = cms.InputTag("genParticles"))
akFilter4PFPatJetFlavourAssociationLegacy = akFilter4PFbTagger.PatJetFlavourAssociationLegacy
akFilter4PFPatJetPartons = akFilter4PFbTagger.PatJetPartons
akFilter4PFJetTracksAssociatorAtVertex = akFilter4PFbTagger.JetTracksAssociatorAtVertex
akFilter4PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akFilter4PFSimpleSecondaryVertexHighEffBJetTags = akFilter4PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter4PFSimpleSecondaryVertexHighPurBJetTags = akFilter4PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter4PFCombinedSecondaryVertexBJetTags = akFilter4PFbTagger.CombinedSecondaryVertexBJetTags
akFilter4PFCombinedSecondaryVertexV2BJetTags = akFilter4PFbTagger.CombinedSecondaryVertexV2BJetTags
akFilter4PFJetBProbabilityBJetTags = akFilter4PFbTagger.JetBProbabilityBJetTags
akFilter4PFSoftPFMuonByPtBJetTags = akFilter4PFbTagger.SoftPFMuonByPtBJetTags
akFilter4PFSoftPFMuonByIP3dBJetTags = akFilter4PFbTagger.SoftPFMuonByIP3dBJetTags
akFilter4PFTrackCountingHighEffBJetTags = akFilter4PFbTagger.TrackCountingHighEffBJetTags
akFilter4PFTrackCountingHighPurBJetTags = akFilter4PFbTagger.TrackCountingHighPurBJetTags
akFilter4PFPatJetPartonAssociationLegacy = akFilter4PFbTagger.PatJetPartonAssociationLegacy

akFilter4PFImpactParameterTagInfos = akFilter4PFbTagger.ImpactParameterTagInfos
akFilter4PFPfImpactParameterTagInfos = akFilter4PFbTagger.PfImpactParameterTagInfos
akFilter4PFJetProbabilityBJetTags = akFilter4PFbTagger.JetProbabilityBJetTags

akFilter4PFSecondaryVertexTagInfos = akFilter4PFbTagger.SecondaryVertexTagInfos
akFilter4PFSimpleSecondaryVertexHighEffBJetTags = akFilter4PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter4PFSimpleSecondaryVertexHighPurBJetTags = akFilter4PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter4PFCombinedSecondaryVertexBJetTags = akFilter4PFbTagger.CombinedSecondaryVertexBJetTags
akFilter4PFCombinedSecondaryVertexV2BJetTags = akFilter4PFbTagger.CombinedSecondaryVertexV2BJetTags
akFilter4PFPfInclusiveSecondaryVertexFinderTagInfos = akFilter4PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
akFilter4PFPfDeepCSVTagInfos = akFilter4PFbTagger.PfDeepCSVTagInfos
akFilter4PFPfDeepCSVJetTags = akFilter4PFbTagger.PfDeepCSVJetTags


akFilter4PFSoftPFMuonsTagInfos = akFilter4PFbTagger.SoftPFMuonsTagInfos
akFilter4PFSoftPFMuonBJetTags = akFilter4PFbTagger.SoftPFMuonBJetTags
akFilter4PFSoftPFMuonByIP3dBJetTags = akFilter4PFbTagger.SoftPFMuonByIP3dBJetTags
akFilter4PFSoftPFMuonByPtBJetTags = akFilter4PFbTagger.SoftPFMuonByPtBJetTags
akFilter4PFPatJetFlavourIdLegacy = cms.Sequence(akFilter4PFPatJetPartonAssociationLegacy*akFilter4PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akFilter4PFPatJetFlavourAssociation = akFilter4PFbTagger.PatJetFlavourAssociation
akFilter4PFPatJetFlavourId = cms.Sequence(akFilter4PFPatJetPartons*akFilter4PFPatJetFlavourAssociation)

#adding the subjet taggers
akFilter4PFSubjetImpactParameterTagInfos = akFilter4PFbTagger.SubjetImpactParameterTagInfos
akFilter4PFSubjetJetProbabilityBJetTags = akFilter4PFbTagger.SubjetJetProbabilityBJetTags
akFilter4PFSubjetSecondaryVertexTagInfos = akFilter4PFbTagger.SubjetSecondaryVertexTagInfos
akFilter4PFSubjetJetTracksAssociatorAtVertex = akFilter4PFbTagger.SubjetJetTracksAssociatorAtVertex
akFilter4PFCombinedSubjetSecondaryVertexBJetTags = akFilter4PFbTagger.CombinedSubjetSecondaryVertexBJetTags
akFilter4PFCombinedSubjetSecondaryVertexV2BJetTags = akFilter4PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

akFilter4PFJetBtaggingIP       = cms.Sequence(akFilter4PFImpactParameterTagInfos *
            (akFilter4PFTrackCountingHighEffBJetTags +
             akFilter4PFTrackCountingHighPurBJetTags +
             akFilter4PFJetProbabilityBJetTags +
             akFilter4PFJetBProbabilityBJetTags 
            ) *
	     akFilter4PFPfImpactParameterTagInfos 
            )

akFilter4PFJetBtaggingSV = cms.Sequence(akFilter4PFImpactParameterTagInfos
            *
            akFilter4PFSecondaryVertexTagInfos
            * (akFilter4PFSimpleSecondaryVertexHighEffBJetTags+
                akFilter4PFSimpleSecondaryVertexHighPurBJetTags+
                akFilter4PFCombinedSecondaryVertexBJetTags+
                akFilter4PFCombinedSecondaryVertexV2BJetTags
              ) *
	    akFilter4PFPfImpactParameterTagInfos *
	    akFilter4PFPfInclusiveSecondaryVertexFinderTagInfos *
	    akFilter4PFPfDeepCSVTagInfos *
	    akFilter4PFPfDeepCSVJetTags  
            )



akFilter4PFJetBtaggingMu = cms.Sequence(akFilter4PFSoftPFMuonsTagInfos * (akFilter4PFSoftPFMuonBJetTags
                +
                akFilter4PFSoftPFMuonByIP3dBJetTags
                +
                akFilter4PFSoftPFMuonByPtBJetTags               
              )
            )

akFilter4PFJetBtagging = cms.Sequence(akFilter4PFJetBtaggingIP
            *akFilter4PFJetBtaggingSV
#            *akFilter4PFJetBtaggingMu
            )

akFilter4PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akFilter4PFJets"),
        genJetMatch          = cms.InputTag("akFilter4PFmatch"),
        genPartonMatch       = cms.InputTag("akFilter4PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akFilter4PFcorr")),
        #JetPartonMapSource   = cms.InputTag("akFilter4PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akFilter4PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akFilter4PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akFilter4PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akFilter4PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akFilter4PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akFilter4PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akFilter4PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akFilter4PFJetBProbabilityBJetTags"),
            cms.InputTag("akFilter4PFJetProbabilityBJetTags"),
            #cms.InputTag("akFilter4PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akFilter4PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akFilter4PFTrackCountingHighEffBJetTags"),
            cms.InputTag("akFilter4PFTrackCountingHighPurBJetTags"),
            cms.InputTag("akFilter4PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akFilter4PFJetID"),
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

akFilter4PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("akFilter4PFJets"),
           	    R0  = cms.double( 0.4)
)
#ppDataDummy_akFilter4PFpatJetsWithBtagging.userData.userFloats.src += ['akFilter4PFNjettiness:tau1','akFilter4PFNjettiness:tau2','akFilter4PFNjettiness:tau3']

akFilter4PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akFilter4PFpatJetsWithBtagging"),
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
                                                             bTagJetName = cms.untracked.string("akFilter4PF"),
                                                             jetName = cms.untracked.string("akFilter4PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akFilter4GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("akFilter4PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akFilter4PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akFilter4PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

#ENABLE_PPCALO_akFilter4PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_akFilter4PFJetAnalyzer.doExtendedFlavorTagging = False

akFilter4PFJetAnalyzer.trackSelection = akFilter4PFSecondaryVertexTagInfos.trackSelection
akFilter4PFJetAnalyzer.trackPairV0Filter = akFilter4PFSecondaryVertexTagInfos.vertexCuts.v0Filter

akFilter4PFJetSequence_mc = cms.Sequence(
                                                  #akFilter4PFclean
                                                  #*
                                                  akFilter4PFmatch
                                                  #*
                                                  #akFilter4PFmatchGroomed
                                                  *
                                                  akFilter4PFparton
                                                  *
                                                  akFilter4PFcorr
                                                  *
                                                  #akFilter4PFJetID
                                                  #*
                                                  #akFilter4PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  akFilter4PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
                                                  akFilter4PFJetTracksAssociatorAtVertex
                                                  *
                                                  akFilter4PFJetBtagging
                                                  *
                                                  akFilter4PFNjettiness
                                                  *
                                                  akFilter4PFpatJetsWithBtagging
                                                  *
                                                  akFilter4PFJetAnalyzer
                                                  )

akFilter4PFJetSequence_data = cms.Sequence(akFilter4PFcorr
                                                    *
                                                    #akFilter4PFJetID
                                                    #*
                                                    akFilter4PFJetTracksAssociatorAtVertex
                                                    *
                                                    akFilter4PFJetBtagging
                                                    *
                                                    akFilter4PFNjettiness
                                                    *
                                                    akFilter4PFpatJetsWithBtagging
                                                    *
                                                    akFilter4PFJetAnalyzer
                                                    )

akFilter4PFJetSequence_jec = cms.Sequence(akFilter4PFJetSequence_mc)
akFilter4PFJetSequence_mb = cms.Sequence(akFilter4PFJetSequence_mc)

akFilter4PFJetSequence = cms.Sequence(akFilter4PFJetSequence_jec)
akFilter4PFJetAnalyzer.genPtMin = cms.untracked.double(1)
akFilter4PFJetAnalyzer.jetPtMin = cms.double(1)
akFilter4PFJetAnalyzer.doSubEvent = True
