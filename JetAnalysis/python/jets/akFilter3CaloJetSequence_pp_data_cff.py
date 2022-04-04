

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akFilter3Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter3CaloJets"),
    matched = cms.InputTag("ak3GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.3
    )

akFilter3CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter3GenJets"),
    matched = cms.InputTag("ak3GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.3
    )

akFilter3Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter3CaloJets")
                                                        )

akFilter3Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative','L2L3Residual'),
    src = cms.InputTag("akFilter3CaloJets"),
    payload = "AK4PF"
    )

akFilter3CaloJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akFilter3CaloJets'))

#akFilter3Caloclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak3GenJets'))

akFilter3CalobTagger = bTaggers("akFilter3Calo",0.3,True,True)

#create objects locally since they dont load properly otherwise
#akFilter3Calomatch = akFilter3CalobTagger.match
akFilter3Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter3CaloJets"), matched = cms.InputTag("genParticles"))
akFilter3CaloPatJetFlavourAssociationLegacy = akFilter3CalobTagger.PatJetFlavourAssociationLegacy
akFilter3CaloPatJetPartons = akFilter3CalobTagger.PatJetPartons
akFilter3CaloJetTracksAssociatorAtVertex = akFilter3CalobTagger.JetTracksAssociatorAtVertex
akFilter3CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akFilter3CaloSimpleSecondaryVertexHighEffBJetTags = akFilter3CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter3CaloSimpleSecondaryVertexHighPurBJetTags = akFilter3CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter3CaloCombinedSecondaryVertexBJetTags = akFilter3CalobTagger.CombinedSecondaryVertexBJetTags
akFilter3CaloCombinedSecondaryVertexV2BJetTags = akFilter3CalobTagger.CombinedSecondaryVertexV2BJetTags
akFilter3CaloJetBProbabilityBJetTags = akFilter3CalobTagger.JetBProbabilityBJetTags
akFilter3CaloSoftPFMuonByPtBJetTags = akFilter3CalobTagger.SoftPFMuonByPtBJetTags
akFilter3CaloSoftPFMuonByIP3dBJetTags = akFilter3CalobTagger.SoftPFMuonByIP3dBJetTags
akFilter3CaloTrackCountingHighEffBJetTags = akFilter3CalobTagger.TrackCountingHighEffBJetTags
akFilter3CaloTrackCountingHighPurBJetTags = akFilter3CalobTagger.TrackCountingHighPurBJetTags
akFilter3CaloPatJetPartonAssociationLegacy = akFilter3CalobTagger.PatJetPartonAssociationLegacy

akFilter3CaloImpactParameterTagInfos = akFilter3CalobTagger.ImpactParameterTagInfos
akFilter3CaloPfImpactParameterTagInfos = akFilter3CalobTagger.PfImpactParameterTagInfos
akFilter3CaloJetProbabilityBJetTags = akFilter3CalobTagger.JetProbabilityBJetTags

akFilter3CaloSecondaryVertexTagInfos = akFilter3CalobTagger.SecondaryVertexTagInfos
akFilter3CaloSimpleSecondaryVertexHighEffBJetTags = akFilter3CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter3CaloSimpleSecondaryVertexHighPurBJetTags = akFilter3CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter3CaloCombinedSecondaryVertexBJetTags = akFilter3CalobTagger.CombinedSecondaryVertexBJetTags
akFilter3CaloCombinedSecondaryVertexV2BJetTags = akFilter3CalobTagger.CombinedSecondaryVertexV2BJetTags
akFilter3CaloPfInclusiveSecondaryVertexFinderTagInfos = akFilter3CalobTagger.PfInclusiveSecondaryVertexFinderTagInfos
akFilter3CaloPfDeepCSVTagInfos = akFilter3CalobTagger.PfDeepCSVTagInfos
akFilter3CaloPfDeepCSVJetTags = akFilter3CalobTagger.PfDeepCSVJetTags


akFilter3CaloSoftPFMuonsTagInfos = akFilter3CalobTagger.SoftPFMuonsTagInfos
akFilter3CaloSoftPFMuonBJetTags = akFilter3CalobTagger.SoftPFMuonBJetTags
akFilter3CaloSoftPFMuonByIP3dBJetTags = akFilter3CalobTagger.SoftPFMuonByIP3dBJetTags
akFilter3CaloSoftPFMuonByPtBJetTags = akFilter3CalobTagger.SoftPFMuonByPtBJetTags
akFilter3CaloPatJetFlavourIdLegacy = cms.Sequence(akFilter3CaloPatJetPartonAssociationLegacy*akFilter3CaloPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akFilter3CaloPatJetFlavourAssociation = akFilter3CalobTagger.PatJetFlavourAssociation
akFilter3CaloPatJetFlavourId = cms.Sequence(akFilter3CaloPatJetPartons*akFilter3CaloPatJetFlavourAssociation)

#adding the subjet taggers
akFilter3CaloSubjetImpactParameterTagInfos = akFilter3CalobTagger.SubjetImpactParameterTagInfos
akFilter3CaloSubjetJetProbabilityBJetTags = akFilter3CalobTagger.SubjetJetProbabilityBJetTags
akFilter3CaloSubjetSecondaryVertexTagInfos = akFilter3CalobTagger.SubjetSecondaryVertexTagInfos
akFilter3CaloSubjetJetTracksAssociatorAtVertex = akFilter3CalobTagger.SubjetJetTracksAssociatorAtVertex
akFilter3CaloCombinedSubjetSecondaryVertexBJetTags = akFilter3CalobTagger.CombinedSubjetSecondaryVertexBJetTags
akFilter3CaloCombinedSubjetSecondaryVertexV2BJetTags = akFilter3CalobTagger.CombinedSubjetSecondaryVertexV2BJetTags

akFilter3CaloJetBtaggingIP       = cms.Sequence(akFilter3CaloImpactParameterTagInfos *
            (akFilter3CaloTrackCountingHighEffBJetTags +
             akFilter3CaloTrackCountingHighPurBJetTags +
             akFilter3CaloJetProbabilityBJetTags +
             akFilter3CaloJetBProbabilityBJetTags 
            ) *
	     akFilter3CaloPfImpactParameterTagInfos 
            )

akFilter3CaloJetBtaggingSV = cms.Sequence(akFilter3CaloImpactParameterTagInfos
            *
            akFilter3CaloSecondaryVertexTagInfos
            * (akFilter3CaloSimpleSecondaryVertexHighEffBJetTags+
                akFilter3CaloSimpleSecondaryVertexHighPurBJetTags+
                akFilter3CaloCombinedSecondaryVertexBJetTags+
                akFilter3CaloCombinedSecondaryVertexV2BJetTags
              ) *
	    akFilter3CaloPfImpactParameterTagInfos *
	    akFilter3CaloPfInclusiveSecondaryVertexFinderTagInfos *
	    akFilter3CaloPfDeepCSVTagInfos *
	    akFilter3CaloPfDeepCSVJetTags  
            )



akFilter3CaloJetBtaggingMu = cms.Sequence(akFilter3CaloSoftPFMuonsTagInfos * (akFilter3CaloSoftPFMuonBJetTags
                +
                akFilter3CaloSoftPFMuonByIP3dBJetTags
                +
                akFilter3CaloSoftPFMuonByPtBJetTags               
              )
            )

akFilter3CaloJetBtagging = cms.Sequence(akFilter3CaloJetBtaggingIP
            *akFilter3CaloJetBtaggingSV
#            *akFilter3CaloJetBtaggingMu
            )

akFilter3CalopatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akFilter3CaloJets"),
        genJetMatch          = cms.InputTag("akFilter3Calomatch"),
        genPartonMatch       = cms.InputTag("akFilter3Caloparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akFilter3Calocorr")),
        #JetPartonMapSource   = cms.InputTag("akFilter3CaloPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akFilter3CaloPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akFilter3CaloPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akFilter3CaloJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akFilter3CaloSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akFilter3CaloSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akFilter3CaloCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akFilter3CaloCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akFilter3CaloJetBProbabilityBJetTags"),
            cms.InputTag("akFilter3CaloJetProbabilityBJetTags"),
            #cms.InputTag("akFilter3CaloSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akFilter3CaloSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akFilter3CaloTrackCountingHighEffBJetTags"),
            cms.InputTag("akFilter3CaloTrackCountingHighPurBJetTags"),
            cms.InputTag("akFilter3CaloPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akFilter3CaloJetID"),
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

akFilter3CaloNjettiness = Njettiness.clone(
		    src = cms.InputTag("akFilter3CaloJets"),
           	    R0  = cms.double( 0.3)
)
#ppDataDummy_akFilter3CalopatJetsWithBtagging.userData.userFloats.src += ['akFilter3CaloNjettiness:tau1','akFilter3CaloNjettiness:tau2','akFilter3CaloNjettiness:tau3']

akFilter3CaloJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akFilter3CalopatJetsWithBtagging"),
                                                             genjetTag = 'ak3GenJets',
                                                             rParam = 0.3,
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
                                                             bTagJetName = cms.untracked.string("akFilter3Calo"),
                                                             jetName = cms.untracked.string("akFilter3Calo"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akFilter3GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(False),
							     jetFlavourInfos = cms.InputTag("akFilter3CaloPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akFilter3CaloPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akFilter3CaloJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = False
                                                            )

akFilter3CalopatJetsWithBtagging.getJetMCFlavour = False
akFilter3CaloJetAnalyzer.doExtendedFlavorTagging = False

akFilter3CaloJetAnalyzer.trackSelection = akFilter3CaloSecondaryVertexTagInfos.trackSelection
akFilter3CaloJetAnalyzer.trackPairV0Filter = akFilter3CaloSecondaryVertexTagInfos.vertexCuts.v0Filter

akFilter3CaloJetSequence_mc = cms.Sequence(
                                                  #akFilter3Caloclean
                                                  #*
                                                  akFilter3Calomatch
                                                  #*
                                                  #akFilter3CalomatchGroomed
                                                  *
                                                  akFilter3Caloparton
                                                  *
                                                  akFilter3Calocorr
                                                  *
                                                  #akFilter3CaloJetID
                                                  #*
                                                  #akFilter3CaloPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  #DISABLE_PPCALO_akFilter3CaloPatJetFlavourId  # doesn't work for PbPb yet
                                                  #DISABLE_PPCALO_*
                                                  akFilter3CaloJetTracksAssociatorAtVertex
                                                  *
                                                  akFilter3CaloJetBtagging
                                                  *
                                                  #DISABLE_PPCALO_akFilter3CaloNjettiness
                                                  #DISABLE_PPCALO_*
                                                  akFilter3CalopatJetsWithBtagging
                                                  *
                                                  akFilter3CaloJetAnalyzer
                                                  )

akFilter3CaloJetSequence_data = cms.Sequence(akFilter3Calocorr
                                                    *
                                                    #akFilter3CaloJetID
                                                    #*
                                                    akFilter3CaloJetTracksAssociatorAtVertex
                                                    *
                                                    akFilter3CaloJetBtagging
                                                    *
                                                    #DISABLE_PPCALO_akFilter3CaloNjettiness
                                                    #DISABLE_PPCALO_*
                                                    akFilter3CalopatJetsWithBtagging
                                                    *
                                                    akFilter3CaloJetAnalyzer
                                                    )

akFilter3CaloJetSequence_jec = cms.Sequence(akFilter3CaloJetSequence_mc)
akFilter3CaloJetSequence_mb = cms.Sequence(akFilter3CaloJetSequence_mc)

akFilter3CaloJetSequence = cms.Sequence(akFilter3CaloJetSequence_data)
