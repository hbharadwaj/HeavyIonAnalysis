

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akFilter6Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter6CaloJets"),
    matched = cms.InputTag("ak6GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.6
    )

akFilter6CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter6GenJets"),
    matched = cms.InputTag("ak6GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.6
    )

akFilter6Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter6CaloJets")
                                                        )

akFilter6Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akFilter6CaloJets"),
    payload = "AK4PF"
    )

akFilter6CaloJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akFilter6CaloJets'))

#akFilter6Caloclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak6GenJets'))

akFilter6CalobTagger = bTaggers("akFilter6Calo",0.6,True,True)

#create objects locally since they dont load properly otherwise
#akFilter6Calomatch = akFilter6CalobTagger.match
akFilter6Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter6CaloJets"), matched = cms.InputTag("genParticles"))
akFilter6CaloPatJetFlavourAssociationLegacy = akFilter6CalobTagger.PatJetFlavourAssociationLegacy
akFilter6CaloPatJetPartons = akFilter6CalobTagger.PatJetPartons
akFilter6CaloJetTracksAssociatorAtVertex = akFilter6CalobTagger.JetTracksAssociatorAtVertex
akFilter6CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akFilter6CaloSimpleSecondaryVertexHighEffBJetTags = akFilter6CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter6CaloSimpleSecondaryVertexHighPurBJetTags = akFilter6CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter6CaloCombinedSecondaryVertexBJetTags = akFilter6CalobTagger.CombinedSecondaryVertexBJetTags
akFilter6CaloCombinedSecondaryVertexV2BJetTags = akFilter6CalobTagger.CombinedSecondaryVertexV2BJetTags
akFilter6CaloJetBProbabilityBJetTags = akFilter6CalobTagger.JetBProbabilityBJetTags
akFilter6CaloSoftPFMuonByPtBJetTags = akFilter6CalobTagger.SoftPFMuonByPtBJetTags
akFilter6CaloSoftPFMuonByIP3dBJetTags = akFilter6CalobTagger.SoftPFMuonByIP3dBJetTags
akFilter6CaloTrackCountingHighEffBJetTags = akFilter6CalobTagger.TrackCountingHighEffBJetTags
akFilter6CaloTrackCountingHighPurBJetTags = akFilter6CalobTagger.TrackCountingHighPurBJetTags
akFilter6CaloPatJetPartonAssociationLegacy = akFilter6CalobTagger.PatJetPartonAssociationLegacy

akFilter6CaloImpactParameterTagInfos = akFilter6CalobTagger.ImpactParameterTagInfos
akFilter6CaloPfImpactParameterTagInfos = akFilter6CalobTagger.PfImpactParameterTagInfos
akFilter6CaloJetProbabilityBJetTags = akFilter6CalobTagger.JetProbabilityBJetTags

akFilter6CaloSecondaryVertexTagInfos = akFilter6CalobTagger.SecondaryVertexTagInfos
akFilter6CaloSimpleSecondaryVertexHighEffBJetTags = akFilter6CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter6CaloSimpleSecondaryVertexHighPurBJetTags = akFilter6CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter6CaloCombinedSecondaryVertexBJetTags = akFilter6CalobTagger.CombinedSecondaryVertexBJetTags
akFilter6CaloCombinedSecondaryVertexV2BJetTags = akFilter6CalobTagger.CombinedSecondaryVertexV2BJetTags
akFilter6CaloPfInclusiveSecondaryVertexFinderTagInfos = akFilter6CalobTagger.PfInclusiveSecondaryVertexFinderTagInfos
akFilter6CaloPfDeepCSVTagInfos = akFilter6CalobTagger.PfDeepCSVTagInfos
akFilter6CaloPfDeepCSVJetTags = akFilter6CalobTagger.PfDeepCSVJetTags


akFilter6CaloSoftPFMuonsTagInfos = akFilter6CalobTagger.SoftPFMuonsTagInfos
akFilter6CaloSoftPFMuonBJetTags = akFilter6CalobTagger.SoftPFMuonBJetTags
akFilter6CaloSoftPFMuonByIP3dBJetTags = akFilter6CalobTagger.SoftPFMuonByIP3dBJetTags
akFilter6CaloSoftPFMuonByPtBJetTags = akFilter6CalobTagger.SoftPFMuonByPtBJetTags
akFilter6CaloPatJetFlavourIdLegacy = cms.Sequence(akFilter6CaloPatJetPartonAssociationLegacy*akFilter6CaloPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akFilter6CaloPatJetFlavourAssociation = akFilter6CalobTagger.PatJetFlavourAssociation
akFilter6CaloPatJetFlavourId = cms.Sequence(akFilter6CaloPatJetPartons*akFilter6CaloPatJetFlavourAssociation)

#adding the subjet taggers
akFilter6CaloSubjetImpactParameterTagInfos = akFilter6CalobTagger.SubjetImpactParameterTagInfos
akFilter6CaloSubjetJetProbabilityBJetTags = akFilter6CalobTagger.SubjetJetProbabilityBJetTags
akFilter6CaloSubjetSecondaryVertexTagInfos = akFilter6CalobTagger.SubjetSecondaryVertexTagInfos
akFilter6CaloSubjetJetTracksAssociatorAtVertex = akFilter6CalobTagger.SubjetJetTracksAssociatorAtVertex
akFilter6CaloCombinedSubjetSecondaryVertexBJetTags = akFilter6CalobTagger.CombinedSubjetSecondaryVertexBJetTags
akFilter6CaloCombinedSubjetSecondaryVertexV2BJetTags = akFilter6CalobTagger.CombinedSubjetSecondaryVertexV2BJetTags

akFilter6CaloJetBtaggingIP       = cms.Sequence(akFilter6CaloImpactParameterTagInfos *
            (akFilter6CaloTrackCountingHighEffBJetTags +
             akFilter6CaloTrackCountingHighPurBJetTags +
             akFilter6CaloJetProbabilityBJetTags +
             akFilter6CaloJetBProbabilityBJetTags 
            ) *
	     akFilter6CaloPfImpactParameterTagInfos 
            )

akFilter6CaloJetBtaggingSV = cms.Sequence(akFilter6CaloImpactParameterTagInfos
            *
            akFilter6CaloSecondaryVertexTagInfos
            * (akFilter6CaloSimpleSecondaryVertexHighEffBJetTags+
                akFilter6CaloSimpleSecondaryVertexHighPurBJetTags+
                akFilter6CaloCombinedSecondaryVertexBJetTags+
                akFilter6CaloCombinedSecondaryVertexV2BJetTags
              ) *
	    akFilter6CaloPfImpactParameterTagInfos *
	    akFilter6CaloPfInclusiveSecondaryVertexFinderTagInfos *
	    akFilter6CaloPfDeepCSVTagInfos *
	    akFilter6CaloPfDeepCSVJetTags  
            )



akFilter6CaloJetBtaggingMu = cms.Sequence(akFilter6CaloSoftPFMuonsTagInfos * (akFilter6CaloSoftPFMuonBJetTags
                +
                akFilter6CaloSoftPFMuonByIP3dBJetTags
                +
                akFilter6CaloSoftPFMuonByPtBJetTags               
              )
            )

akFilter6CaloJetBtagging = cms.Sequence(akFilter6CaloJetBtaggingIP
            *akFilter6CaloJetBtaggingSV
#            *akFilter6CaloJetBtaggingMu
            )

akFilter6CalopatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akFilter6CaloJets"),
        genJetMatch          = cms.InputTag("akFilter6Calomatch"),
        genPartonMatch       = cms.InputTag("akFilter6Caloparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akFilter6Calocorr")),
        #JetPartonMapSource   = cms.InputTag("akFilter6CaloPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akFilter6CaloPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akFilter6CaloPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akFilter6CaloJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akFilter6CaloSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akFilter6CaloSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akFilter6CaloCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akFilter6CaloCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akFilter6CaloJetBProbabilityBJetTags"),
            cms.InputTag("akFilter6CaloJetProbabilityBJetTags"),
            #cms.InputTag("akFilter6CaloSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akFilter6CaloSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akFilter6CaloTrackCountingHighEffBJetTags"),
            cms.InputTag("akFilter6CaloTrackCountingHighPurBJetTags"),
            cms.InputTag("akFilter6CaloPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akFilter6CaloJetID"),
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

akFilter6CaloNjettiness = Njettiness.clone(
		    src = cms.InputTag("akFilter6CaloJets"),
           	    R0  = cms.double( 0.6)
)
#ppDataDummy_akFilter6CalopatJetsWithBtagging.userData.userFloats.src += ['akFilter6CaloNjettiness:tau1','akFilter6CaloNjettiness:tau2','akFilter6CaloNjettiness:tau3']

akFilter6CaloJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akFilter6CalopatJetsWithBtagging"),
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
                                                             bTagJetName = cms.untracked.string("akFilter6Calo"),
                                                             jetName = cms.untracked.string("akFilter6Calo"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akFilter6GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("akFilter6CaloPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akFilter6CaloPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akFilter6CaloJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

akFilter6CalopatJetsWithBtagging.getJetMCFlavour = False
akFilter6CaloJetAnalyzer.doExtendedFlavorTagging = False

akFilter6CaloJetAnalyzer.trackSelection = akFilter6CaloSecondaryVertexTagInfos.trackSelection
akFilter6CaloJetAnalyzer.trackPairV0Filter = akFilter6CaloSecondaryVertexTagInfos.vertexCuts.v0Filter

akFilter6CaloJetSequence_mc = cms.Sequence(
                                                  #akFilter6Caloclean
                                                  #*
                                                  akFilter6Calomatch
                                                  #*
                                                  #akFilter6CalomatchGroomed
                                                  *
                                                  akFilter6Caloparton
                                                  *
                                                  akFilter6Calocorr
                                                  *
                                                  #akFilter6CaloJetID
                                                  #*
                                                  #akFilter6CaloPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  #DISABLE_PPCALO_akFilter6CaloPatJetFlavourId  # doesn't work for PbPb yet
                                                  #DISABLE_PPCALO_*
                                                  akFilter6CaloJetTracksAssociatorAtVertex
                                                  *
                                                  akFilter6CaloJetBtagging
                                                  *
                                                  #DISABLE_PPCALO_akFilter6CaloNjettiness
                                                  #DISABLE_PPCALO_*
                                                  akFilter6CalopatJetsWithBtagging
                                                  *
                                                  akFilter6CaloJetAnalyzer
                                                  )

akFilter6CaloJetSequence_data = cms.Sequence(akFilter6Calocorr
                                                    *
                                                    #akFilter6CaloJetID
                                                    #*
                                                    akFilter6CaloJetTracksAssociatorAtVertex
                                                    *
                                                    akFilter6CaloJetBtagging
                                                    *
                                                    #DISABLE_PPCALO_akFilter6CaloNjettiness
                                                    #DISABLE_PPCALO_*
                                                    akFilter6CalopatJetsWithBtagging
                                                    *
                                                    akFilter6CaloJetAnalyzer
                                                    )

akFilter6CaloJetSequence_jec = cms.Sequence(akFilter6CaloJetSequence_mc)
akFilter6CaloJetSequence_mb = cms.Sequence(akFilter6CaloJetSequence_mc)

akFilter6CaloJetSequence = cms.Sequence(akFilter6CaloJetSequence_mc)
