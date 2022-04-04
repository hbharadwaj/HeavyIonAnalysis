

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akSoftDrop6Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop6CaloJets"),
    matched = cms.InputTag("ak6GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.6
    )

akSoftDrop6CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop6GenJets"),
    matched = cms.InputTag("ak6GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.6
    )

akSoftDrop6Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop6CaloJets")
                                                        )

akSoftDrop6Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akSoftDrop6CaloJets"),
    payload = "AK4PF"
    )

akSoftDrop6CaloJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akSoftDrop6CaloJets'))

#akSoftDrop6Caloclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak6GenJets'))

akSoftDrop6CalobTagger = bTaggers("akSoftDrop6Calo",0.6,True,True)

#create objects locally since they dont load properly otherwise
#akSoftDrop6Calomatch = akSoftDrop6CalobTagger.match
akSoftDrop6Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop6CaloJets"), matched = cms.InputTag("genParticles"))
akSoftDrop6CaloPatJetFlavourAssociationLegacy = akSoftDrop6CalobTagger.PatJetFlavourAssociationLegacy
akSoftDrop6CaloPatJetPartons = akSoftDrop6CalobTagger.PatJetPartons
akSoftDrop6CaloJetTracksAssociatorAtVertex = akSoftDrop6CalobTagger.JetTracksAssociatorAtVertex
akSoftDrop6CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akSoftDrop6CaloSimpleSecondaryVertexHighEffBJetTags = akSoftDrop6CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop6CaloSimpleSecondaryVertexHighPurBJetTags = akSoftDrop6CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop6CaloCombinedSecondaryVertexBJetTags = akSoftDrop6CalobTagger.CombinedSecondaryVertexBJetTags
akSoftDrop6CaloCombinedSecondaryVertexV2BJetTags = akSoftDrop6CalobTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop6CaloJetBProbabilityBJetTags = akSoftDrop6CalobTagger.JetBProbabilityBJetTags
akSoftDrop6CaloSoftPFMuonByPtBJetTags = akSoftDrop6CalobTagger.SoftPFMuonByPtBJetTags
akSoftDrop6CaloSoftPFMuonByIP3dBJetTags = akSoftDrop6CalobTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop6CaloTrackCountingHighEffBJetTags = akSoftDrop6CalobTagger.TrackCountingHighEffBJetTags
akSoftDrop6CaloTrackCountingHighPurBJetTags = akSoftDrop6CalobTagger.TrackCountingHighPurBJetTags
akSoftDrop6CaloPatJetPartonAssociationLegacy = akSoftDrop6CalobTagger.PatJetPartonAssociationLegacy

akSoftDrop6CaloImpactParameterTagInfos = akSoftDrop6CalobTagger.ImpactParameterTagInfos
akSoftDrop6CaloPfImpactParameterTagInfos = akSoftDrop6CalobTagger.PfImpactParameterTagInfos
akSoftDrop6CaloJetProbabilityBJetTags = akSoftDrop6CalobTagger.JetProbabilityBJetTags

akSoftDrop6CaloSecondaryVertexTagInfos = akSoftDrop6CalobTagger.SecondaryVertexTagInfos
akSoftDrop6CaloSimpleSecondaryVertexHighEffBJetTags = akSoftDrop6CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop6CaloSimpleSecondaryVertexHighPurBJetTags = akSoftDrop6CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop6CaloCombinedSecondaryVertexBJetTags = akSoftDrop6CalobTagger.CombinedSecondaryVertexBJetTags
akSoftDrop6CaloCombinedSecondaryVertexV2BJetTags = akSoftDrop6CalobTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop6CaloPfInclusiveSecondaryVertexFinderTagInfos = akSoftDrop6CalobTagger.PfInclusiveSecondaryVertexFinderTagInfos
akSoftDrop6CaloPfDeepCSVTagInfos = akSoftDrop6CalobTagger.PfDeepCSVTagInfos
akSoftDrop6CaloPfDeepCSVJetTags = akSoftDrop6CalobTagger.PfDeepCSVJetTags


akSoftDrop6CaloSoftPFMuonsTagInfos = akSoftDrop6CalobTagger.SoftPFMuonsTagInfos
akSoftDrop6CaloSoftPFMuonBJetTags = akSoftDrop6CalobTagger.SoftPFMuonBJetTags
akSoftDrop6CaloSoftPFMuonByIP3dBJetTags = akSoftDrop6CalobTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop6CaloSoftPFMuonByPtBJetTags = akSoftDrop6CalobTagger.SoftPFMuonByPtBJetTags
akSoftDrop6CaloPatJetFlavourIdLegacy = cms.Sequence(akSoftDrop6CaloPatJetPartonAssociationLegacy*akSoftDrop6CaloPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akSoftDrop6CaloPatJetFlavourAssociation = akSoftDrop6CalobTagger.PatJetFlavourAssociation
akSoftDrop6CaloPatJetFlavourId = cms.Sequence(akSoftDrop6CaloPatJetPartons*akSoftDrop6CaloPatJetFlavourAssociation)

#adding the subjet taggers
akSoftDrop6CaloSubjetImpactParameterTagInfos = akSoftDrop6CalobTagger.SubjetImpactParameterTagInfos
akSoftDrop6CaloSubjetJetProbabilityBJetTags = akSoftDrop6CalobTagger.SubjetJetProbabilityBJetTags
akSoftDrop6CaloSubjetSecondaryVertexTagInfos = akSoftDrop6CalobTagger.SubjetSecondaryVertexTagInfos
akSoftDrop6CaloSubjetJetTracksAssociatorAtVertex = akSoftDrop6CalobTagger.SubjetJetTracksAssociatorAtVertex
akSoftDrop6CaloCombinedSubjetSecondaryVertexBJetTags = akSoftDrop6CalobTagger.CombinedSubjetSecondaryVertexBJetTags
akSoftDrop6CaloCombinedSubjetSecondaryVertexV2BJetTags = akSoftDrop6CalobTagger.CombinedSubjetSecondaryVertexV2BJetTags

akSoftDrop6CaloJetBtaggingIP       = cms.Sequence(akSoftDrop6CaloImpactParameterTagInfos *
            (akSoftDrop6CaloTrackCountingHighEffBJetTags +
             akSoftDrop6CaloTrackCountingHighPurBJetTags +
             akSoftDrop6CaloJetProbabilityBJetTags +
             akSoftDrop6CaloJetBProbabilityBJetTags 
            ) *
	     akSoftDrop6CaloPfImpactParameterTagInfos 
            )

akSoftDrop6CaloJetBtaggingSV = cms.Sequence(akSoftDrop6CaloImpactParameterTagInfos
            *
            akSoftDrop6CaloSecondaryVertexTagInfos
            * (akSoftDrop6CaloSimpleSecondaryVertexHighEffBJetTags+
                akSoftDrop6CaloSimpleSecondaryVertexHighPurBJetTags+
                akSoftDrop6CaloCombinedSecondaryVertexBJetTags+
                akSoftDrop6CaloCombinedSecondaryVertexV2BJetTags
              ) *
	    akSoftDrop6CaloPfImpactParameterTagInfos *
	    akSoftDrop6CaloPfInclusiveSecondaryVertexFinderTagInfos *
	    akSoftDrop6CaloPfDeepCSVTagInfos *
	    akSoftDrop6CaloPfDeepCSVJetTags  
            )



akSoftDrop6CaloJetBtaggingMu = cms.Sequence(akSoftDrop6CaloSoftPFMuonsTagInfos * (akSoftDrop6CaloSoftPFMuonBJetTags
                +
                akSoftDrop6CaloSoftPFMuonByIP3dBJetTags
                +
                akSoftDrop6CaloSoftPFMuonByPtBJetTags               
              )
            )

akSoftDrop6CaloJetBtagging = cms.Sequence(akSoftDrop6CaloJetBtaggingIP
            *akSoftDrop6CaloJetBtaggingSV
#            *akSoftDrop6CaloJetBtaggingMu
            )

akSoftDrop6CalopatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akSoftDrop6CaloJets"),
        genJetMatch          = cms.InputTag("akSoftDrop6Calomatch"),
        genPartonMatch       = cms.InputTag("akSoftDrop6Caloparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akSoftDrop6Calocorr")),
        #JetPartonMapSource   = cms.InputTag("akSoftDrop6CaloPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akSoftDrop6CaloPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akSoftDrop6CaloPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akSoftDrop6CaloJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akSoftDrop6CaloSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akSoftDrop6CaloSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akSoftDrop6CaloCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akSoftDrop6CaloCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akSoftDrop6CaloJetBProbabilityBJetTags"),
            cms.InputTag("akSoftDrop6CaloJetProbabilityBJetTags"),
            #cms.InputTag("akSoftDrop6CaloSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akSoftDrop6CaloSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akSoftDrop6CaloTrackCountingHighEffBJetTags"),
            cms.InputTag("akSoftDrop6CaloTrackCountingHighPurBJetTags"),
            cms.InputTag("akSoftDrop6CaloPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akSoftDrop6CaloJetID"),
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

akSoftDrop6CaloNjettiness = Njettiness.clone(
		    src = cms.InputTag("akSoftDrop6CaloJets"),
           	    R0  = cms.double( 0.6)
)
#ppDataDummy_akSoftDrop6CalopatJetsWithBtagging.userData.userFloats.src += ['akSoftDrop6CaloNjettiness:tau1','akSoftDrop6CaloNjettiness:tau2','akSoftDrop6CaloNjettiness:tau3']

akSoftDrop6CaloJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akSoftDrop6CalopatJetsWithBtagging"),
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
                                                             bTagJetName = cms.untracked.string("akSoftDrop6Calo"),
                                                             jetName = cms.untracked.string("akSoftDrop6Calo"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(True),     
                                                             subjetGenTag = cms.untracked.InputTag("akSoftDrop6GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("akSoftDrop6CaloPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akSoftDrop6CaloPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akSoftDrop6CaloJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

akSoftDrop6CalopatJetsWithBtagging.getJetMCFlavour = False
akSoftDrop6CaloJetAnalyzer.doExtendedFlavorTagging = False

akSoftDrop6CaloJetAnalyzer.trackSelection = akSoftDrop6CaloSecondaryVertexTagInfos.trackSelection
akSoftDrop6CaloJetAnalyzer.trackPairV0Filter = akSoftDrop6CaloSecondaryVertexTagInfos.vertexCuts.v0Filter

akSoftDrop6CaloJetSequence_mc = cms.Sequence(
                                                  #akSoftDrop6Caloclean
                                                  #*
                                                  akSoftDrop6Calomatch
                                                  #*
                                                  #akSoftDrop6CalomatchGroomed
                                                  *
                                                  akSoftDrop6Caloparton
                                                  *
                                                  akSoftDrop6Calocorr
                                                  *
                                                  #akSoftDrop6CaloJetID
                                                  #*
                                                  #akSoftDrop6CaloPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  #DISABLE_PPCALO_akSoftDrop6CaloPatJetFlavourId  # doesn't work for PbPb yet
                                                  #DISABLE_PPCALO_*
                                                  akSoftDrop6CaloJetTracksAssociatorAtVertex
                                                  *
                                                  akSoftDrop6CaloJetBtagging
                                                  *
                                                  #DISABLE_PPCALO_akSoftDrop6CaloNjettiness
                                                  #DISABLE_PPCALO_*
                                                  akSoftDrop6CalopatJetsWithBtagging
                                                  *
                                                  akSoftDrop6CaloJetAnalyzer
                                                  )

akSoftDrop6CaloJetSequence_data = cms.Sequence(akSoftDrop6Calocorr
                                                    *
                                                    #akSoftDrop6CaloJetID
                                                    #*
                                                    akSoftDrop6CaloJetTracksAssociatorAtVertex
                                                    *
                                                    akSoftDrop6CaloJetBtagging
                                                    *
                                                    #DISABLE_PPCALO_akSoftDrop6CaloNjettiness
                                                    #DISABLE_PPCALO_*
                                                    akSoftDrop6CalopatJetsWithBtagging
                                                    *
                                                    akSoftDrop6CaloJetAnalyzer
                                                    )

akSoftDrop6CaloJetSequence_jec = cms.Sequence(akSoftDrop6CaloJetSequence_mc)
akSoftDrop6CaloJetSequence_mb = cms.Sequence(akSoftDrop6CaloJetSequence_mc)

akSoftDrop6CaloJetSequence = cms.Sequence(akSoftDrop6CaloJetSequence_mc)
