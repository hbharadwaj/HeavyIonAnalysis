

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akSoftDrop1PFmatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop1PFJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

akSoftDrop1PFmatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop1GenJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

akSoftDrop1PFparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop1PFJets")
                                                        )

akSoftDrop1PFcorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akSoftDrop1PFJets"),
    payload = "AK1PF"
    )

akSoftDrop1PFJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akSoftDrop1CaloJets'))

#akSoftDrop1PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak1GenJets'))

akSoftDrop1PFbTagger = bTaggers("akSoftDrop1PF",0.1,True,True)

#create objects locally since they dont load properly otherwise
#akSoftDrop1PFmatch = akSoftDrop1PFbTagger.match
akSoftDrop1PFparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop1PFJets"), matched = cms.InputTag("genParticles"))
akSoftDrop1PFPatJetFlavourAssociationLegacy = akSoftDrop1PFbTagger.PatJetFlavourAssociationLegacy
akSoftDrop1PFPatJetPartons = akSoftDrop1PFbTagger.PatJetPartons
akSoftDrop1PFJetTracksAssociatorAtVertex = akSoftDrop1PFbTagger.JetTracksAssociatorAtVertex
akSoftDrop1PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akSoftDrop1PFSimpleSecondaryVertexHighEffBJetTags = akSoftDrop1PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop1PFSimpleSecondaryVertexHighPurBJetTags = akSoftDrop1PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop1PFCombinedSecondaryVertexBJetTags = akSoftDrop1PFbTagger.CombinedSecondaryVertexBJetTags
akSoftDrop1PFCombinedSecondaryVertexV2BJetTags = akSoftDrop1PFbTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop1PFJetBProbabilityBJetTags = akSoftDrop1PFbTagger.JetBProbabilityBJetTags
akSoftDrop1PFSoftPFMuonByPtBJetTags = akSoftDrop1PFbTagger.SoftPFMuonByPtBJetTags
akSoftDrop1PFSoftPFMuonByIP3dBJetTags = akSoftDrop1PFbTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop1PFTrackCountingHighEffBJetTags = akSoftDrop1PFbTagger.TrackCountingHighEffBJetTags
akSoftDrop1PFTrackCountingHighPurBJetTags = akSoftDrop1PFbTagger.TrackCountingHighPurBJetTags
akSoftDrop1PFPatJetPartonAssociationLegacy = akSoftDrop1PFbTagger.PatJetPartonAssociationLegacy

akSoftDrop1PFImpactParameterTagInfos = akSoftDrop1PFbTagger.ImpactParameterTagInfos
akSoftDrop1PFPfImpactParameterTagInfos = akSoftDrop1PFbTagger.PfImpactParameterTagInfos
akSoftDrop1PFJetProbabilityBJetTags = akSoftDrop1PFbTagger.JetProbabilityBJetTags

akSoftDrop1PFSecondaryVertexTagInfos = akSoftDrop1PFbTagger.SecondaryVertexTagInfos
akSoftDrop1PFSimpleSecondaryVertexHighEffBJetTags = akSoftDrop1PFbTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop1PFSimpleSecondaryVertexHighPurBJetTags = akSoftDrop1PFbTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop1PFCombinedSecondaryVertexBJetTags = akSoftDrop1PFbTagger.CombinedSecondaryVertexBJetTags
akSoftDrop1PFCombinedSecondaryVertexV2BJetTags = akSoftDrop1PFbTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop1PFPfInclusiveSecondaryVertexFinderTagInfos = akSoftDrop1PFbTagger.PfInclusiveSecondaryVertexFinderTagInfos
akSoftDrop1PFPfDeepCSVTagInfos = akSoftDrop1PFbTagger.PfDeepCSVTagInfos
akSoftDrop1PFPfDeepCSVJetTags = akSoftDrop1PFbTagger.PfDeepCSVJetTags


akSoftDrop1PFSoftPFMuonsTagInfos = akSoftDrop1PFbTagger.SoftPFMuonsTagInfos
akSoftDrop1PFSoftPFMuonBJetTags = akSoftDrop1PFbTagger.SoftPFMuonBJetTags
akSoftDrop1PFSoftPFMuonByIP3dBJetTags = akSoftDrop1PFbTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop1PFSoftPFMuonByPtBJetTags = akSoftDrop1PFbTagger.SoftPFMuonByPtBJetTags
akSoftDrop1PFPatJetFlavourIdLegacy = cms.Sequence(akSoftDrop1PFPatJetPartonAssociationLegacy*akSoftDrop1PFPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akSoftDrop1PFPatJetFlavourAssociation = akSoftDrop1PFbTagger.PatJetFlavourAssociation
akSoftDrop1PFPatJetFlavourId = cms.Sequence(akSoftDrop1PFPatJetPartons*akSoftDrop1PFPatJetFlavourAssociation)

#adding the subjet taggers
akSoftDrop1PFSubjetImpactParameterTagInfos = akSoftDrop1PFbTagger.SubjetImpactParameterTagInfos
akSoftDrop1PFSubjetJetProbabilityBJetTags = akSoftDrop1PFbTagger.SubjetJetProbabilityBJetTags
akSoftDrop1PFSubjetSecondaryVertexTagInfos = akSoftDrop1PFbTagger.SubjetSecondaryVertexTagInfos
akSoftDrop1PFSubjetJetTracksAssociatorAtVertex = akSoftDrop1PFbTagger.SubjetJetTracksAssociatorAtVertex
akSoftDrop1PFCombinedSubjetSecondaryVertexBJetTags = akSoftDrop1PFbTagger.CombinedSubjetSecondaryVertexBJetTags
akSoftDrop1PFCombinedSubjetSecondaryVertexV2BJetTags = akSoftDrop1PFbTagger.CombinedSubjetSecondaryVertexV2BJetTags

akSoftDrop1PFJetBtaggingIP       = cms.Sequence(akSoftDrop1PFImpactParameterTagInfos *
            (akSoftDrop1PFTrackCountingHighEffBJetTags +
             akSoftDrop1PFTrackCountingHighPurBJetTags +
             akSoftDrop1PFJetProbabilityBJetTags +
             akSoftDrop1PFJetBProbabilityBJetTags 
            ) *
	     akSoftDrop1PFPfImpactParameterTagInfos 
            )

akSoftDrop1PFJetBtaggingSV = cms.Sequence(akSoftDrop1PFImpactParameterTagInfos
            *
            akSoftDrop1PFSecondaryVertexTagInfos
            * (akSoftDrop1PFSimpleSecondaryVertexHighEffBJetTags+
                akSoftDrop1PFSimpleSecondaryVertexHighPurBJetTags+
                akSoftDrop1PFCombinedSecondaryVertexBJetTags+
                akSoftDrop1PFCombinedSecondaryVertexV2BJetTags
              ) *
	    akSoftDrop1PFPfImpactParameterTagInfos *
	    akSoftDrop1PFPfInclusiveSecondaryVertexFinderTagInfos *
	    akSoftDrop1PFPfDeepCSVTagInfos *
	    akSoftDrop1PFPfDeepCSVJetTags  
            )



akSoftDrop1PFJetBtaggingMu = cms.Sequence(akSoftDrop1PFSoftPFMuonsTagInfos * (akSoftDrop1PFSoftPFMuonBJetTags
                +
                akSoftDrop1PFSoftPFMuonByIP3dBJetTags
                +
                akSoftDrop1PFSoftPFMuonByPtBJetTags               
              )
            )

akSoftDrop1PFJetBtagging = cms.Sequence(akSoftDrop1PFJetBtaggingIP
            *akSoftDrop1PFJetBtaggingSV
#            *akSoftDrop1PFJetBtaggingMu
            )

akSoftDrop1PFpatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akSoftDrop1PFJets"),
        genJetMatch          = cms.InputTag("akSoftDrop1PFmatch"),
        genPartonMatch       = cms.InputTag("akSoftDrop1PFparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akSoftDrop1PFcorr")),
        #JetPartonMapSource   = cms.InputTag("akSoftDrop1PFPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akSoftDrop1PFPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akSoftDrop1PFPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akSoftDrop1PFJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akSoftDrop1PFSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akSoftDrop1PFSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akSoftDrop1PFCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akSoftDrop1PFCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akSoftDrop1PFJetBProbabilityBJetTags"),
            cms.InputTag("akSoftDrop1PFJetProbabilityBJetTags"),
            #cms.InputTag("akSoftDrop1PFSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akSoftDrop1PFSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akSoftDrop1PFTrackCountingHighEffBJetTags"),
            cms.InputTag("akSoftDrop1PFTrackCountingHighPurBJetTags"),
            cms.InputTag("akSoftDrop1PFPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akSoftDrop1PFJetID"),
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

akSoftDrop1PFNjettiness = Njettiness.clone(
		    src = cms.InputTag("akSoftDrop1PFJets"),
           	    R0  = cms.double( 0.1)
)
#ppDataDummy_akSoftDrop1PFpatJetsWithBtagging.userData.userFloats.src += ['akSoftDrop1PFNjettiness:tau1','akSoftDrop1PFNjettiness:tau2','akSoftDrop1PFNjettiness:tau3']

akSoftDrop1PFJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akSoftDrop1PFpatJetsWithBtagging"),
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
                                                             bTagJetName = cms.untracked.string("akSoftDrop1PF"),
                                                             jetName = cms.untracked.string("akSoftDrop1PF"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akSoftDrop1GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("akSoftDrop1PFPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akSoftDrop1PFPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akSoftDrop1PFJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

#ENABLE_PPCALO_akSoftDrop1PFpatJetsWithBtagging.getJetMCFlavour = False
#ENABLE_PPCALO_akSoftDrop1PFJetAnalyzer.doExtendedFlavorTagging = False

akSoftDrop1PFJetAnalyzer.trackSelection = akSoftDrop1PFSecondaryVertexTagInfos.trackSelection
akSoftDrop1PFJetAnalyzer.trackPairV0Filter = akSoftDrop1PFSecondaryVertexTagInfos.vertexCuts.v0Filter

akSoftDrop1PFJetSequence_mc = cms.Sequence(
                                                  #akSoftDrop1PFclean
                                                  #*
                                                  akSoftDrop1PFmatch
                                                  #*
                                                  #akSoftDrop1PFmatchGroomed
                                                  *
                                                  akSoftDrop1PFparton
                                                  *
                                                  akSoftDrop1PFcorr
                                                  *
                                                  #akSoftDrop1PFJetID
                                                  #*
                                                  #akSoftDrop1PFPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  akSoftDrop1PFPatJetFlavourId  # doesn't work for PbPb yet
                                                  *
                                                  akSoftDrop1PFJetTracksAssociatorAtVertex
                                                  *
                                                  akSoftDrop1PFJetBtagging
                                                  *
                                                  akSoftDrop1PFNjettiness
                                                  *
                                                  akSoftDrop1PFpatJetsWithBtagging
                                                  *
                                                  akSoftDrop1PFJetAnalyzer
                                                  )

akSoftDrop1PFJetSequence_data = cms.Sequence(akSoftDrop1PFcorr
                                                    *
                                                    #akSoftDrop1PFJetID
                                                    #*
                                                    akSoftDrop1PFJetTracksAssociatorAtVertex
                                                    *
                                                    akSoftDrop1PFJetBtagging
                                                    *
                                                    akSoftDrop1PFNjettiness
                                                    *
                                                    akSoftDrop1PFpatJetsWithBtagging
                                                    *
                                                    akSoftDrop1PFJetAnalyzer
                                                    )

akSoftDrop1PFJetSequence_jec = cms.Sequence(akSoftDrop1PFJetSequence_mc)
akSoftDrop1PFJetSequence_mb = cms.Sequence(akSoftDrop1PFJetSequence_mc)

akSoftDrop1PFJetSequence = cms.Sequence(akSoftDrop1PFJetSequence_jec)
akSoftDrop1PFJetAnalyzer.genPtMin = cms.untracked.double(1)
akSoftDrop1PFJetAnalyzer.jetPtMin = cms.double(1)
akSoftDrop1PFJetAnalyzer.doSubEvent = True
