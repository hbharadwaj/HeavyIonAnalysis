

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akFilter4Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter4CaloJets"),
    matched = cms.InputTag("ak4GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.4
    )

akFilter4CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter4GenJets"),
    matched = cms.InputTag("ak4GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.4
    )

akFilter4Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter4CaloJets")
                                                        )

akFilter4Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative','L2L3Residual'),
    src = cms.InputTag("akFilter4CaloJets"),
    payload = "AK4PF"
    )

akFilter4CaloJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akFilter4CaloJets'))

#akFilter4Caloclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak4GenJets'))

akFilter4CalobTagger = bTaggers("akFilter4Calo",0.4,True,True)

#create objects locally since they dont load properly otherwise
#akFilter4Calomatch = akFilter4CalobTagger.match
akFilter4Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter4CaloJets"), matched = cms.InputTag("genParticles"))
akFilter4CaloPatJetFlavourAssociationLegacy = akFilter4CalobTagger.PatJetFlavourAssociationLegacy
akFilter4CaloPatJetPartons = akFilter4CalobTagger.PatJetPartons
akFilter4CaloJetTracksAssociatorAtVertex = akFilter4CalobTagger.JetTracksAssociatorAtVertex
akFilter4CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akFilter4CaloSimpleSecondaryVertexHighEffBJetTags = akFilter4CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter4CaloSimpleSecondaryVertexHighPurBJetTags = akFilter4CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter4CaloCombinedSecondaryVertexBJetTags = akFilter4CalobTagger.CombinedSecondaryVertexBJetTags
akFilter4CaloCombinedSecondaryVertexV2BJetTags = akFilter4CalobTagger.CombinedSecondaryVertexV2BJetTags
akFilter4CaloJetBProbabilityBJetTags = akFilter4CalobTagger.JetBProbabilityBJetTags
akFilter4CaloSoftPFMuonByPtBJetTags = akFilter4CalobTagger.SoftPFMuonByPtBJetTags
akFilter4CaloSoftPFMuonByIP3dBJetTags = akFilter4CalobTagger.SoftPFMuonByIP3dBJetTags
akFilter4CaloTrackCountingHighEffBJetTags = akFilter4CalobTagger.TrackCountingHighEffBJetTags
akFilter4CaloTrackCountingHighPurBJetTags = akFilter4CalobTagger.TrackCountingHighPurBJetTags
akFilter4CaloPatJetPartonAssociationLegacy = akFilter4CalobTagger.PatJetPartonAssociationLegacy

akFilter4CaloImpactParameterTagInfos = akFilter4CalobTagger.ImpactParameterTagInfos
akFilter4CaloPfImpactParameterTagInfos = akFilter4CalobTagger.PfImpactParameterTagInfos
akFilter4CaloJetProbabilityBJetTags = akFilter4CalobTagger.JetProbabilityBJetTags

akFilter4CaloSecondaryVertexTagInfos = akFilter4CalobTagger.SecondaryVertexTagInfos
akFilter4CaloSimpleSecondaryVertexHighEffBJetTags = akFilter4CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter4CaloSimpleSecondaryVertexHighPurBJetTags = akFilter4CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter4CaloCombinedSecondaryVertexBJetTags = akFilter4CalobTagger.CombinedSecondaryVertexBJetTags
akFilter4CaloCombinedSecondaryVertexV2BJetTags = akFilter4CalobTagger.CombinedSecondaryVertexV2BJetTags
akFilter4CaloPfInclusiveSecondaryVertexFinderTagInfos = akFilter4CalobTagger.PfInclusiveSecondaryVertexFinderTagInfos
akFilter4CaloPfDeepCSVTagInfos = akFilter4CalobTagger.PfDeepCSVTagInfos
akFilter4CaloPfDeepCSVJetTags = akFilter4CalobTagger.PfDeepCSVJetTags


akFilter4CaloSoftPFMuonsTagInfos = akFilter4CalobTagger.SoftPFMuonsTagInfos
akFilter4CaloSoftPFMuonBJetTags = akFilter4CalobTagger.SoftPFMuonBJetTags
akFilter4CaloSoftPFMuonByIP3dBJetTags = akFilter4CalobTagger.SoftPFMuonByIP3dBJetTags
akFilter4CaloSoftPFMuonByPtBJetTags = akFilter4CalobTagger.SoftPFMuonByPtBJetTags
akFilter4CaloPatJetFlavourIdLegacy = cms.Sequence(akFilter4CaloPatJetPartonAssociationLegacy*akFilter4CaloPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akFilter4CaloPatJetFlavourAssociation = akFilter4CalobTagger.PatJetFlavourAssociation
akFilter4CaloPatJetFlavourId = cms.Sequence(akFilter4CaloPatJetPartons*akFilter4CaloPatJetFlavourAssociation)

#adding the subjet taggers
akFilter4CaloSubjetImpactParameterTagInfos = akFilter4CalobTagger.SubjetImpactParameterTagInfos
akFilter4CaloSubjetJetProbabilityBJetTags = akFilter4CalobTagger.SubjetJetProbabilityBJetTags
akFilter4CaloSubjetSecondaryVertexTagInfos = akFilter4CalobTagger.SubjetSecondaryVertexTagInfos
akFilter4CaloSubjetJetTracksAssociatorAtVertex = akFilter4CalobTagger.SubjetJetTracksAssociatorAtVertex
akFilter4CaloCombinedSubjetSecondaryVertexBJetTags = akFilter4CalobTagger.CombinedSubjetSecondaryVertexBJetTags
akFilter4CaloCombinedSubjetSecondaryVertexV2BJetTags = akFilter4CalobTagger.CombinedSubjetSecondaryVertexV2BJetTags

akFilter4CaloJetBtaggingIP       = cms.Sequence(akFilter4CaloImpactParameterTagInfos *
            (akFilter4CaloTrackCountingHighEffBJetTags +
             akFilter4CaloTrackCountingHighPurBJetTags +
             akFilter4CaloJetProbabilityBJetTags +
             akFilter4CaloJetBProbabilityBJetTags 
            ) *
	     akFilter4CaloPfImpactParameterTagInfos 
            )

akFilter4CaloJetBtaggingSV = cms.Sequence(akFilter4CaloImpactParameterTagInfos
            *
            akFilter4CaloSecondaryVertexTagInfos
            * (akFilter4CaloSimpleSecondaryVertexHighEffBJetTags+
                akFilter4CaloSimpleSecondaryVertexHighPurBJetTags+
                akFilter4CaloCombinedSecondaryVertexBJetTags+
                akFilter4CaloCombinedSecondaryVertexV2BJetTags
              ) *
	    akFilter4CaloPfImpactParameterTagInfos *
	    akFilter4CaloPfInclusiveSecondaryVertexFinderTagInfos *
	    akFilter4CaloPfDeepCSVTagInfos *
	    akFilter4CaloPfDeepCSVJetTags  
            )



akFilter4CaloJetBtaggingMu = cms.Sequence(akFilter4CaloSoftPFMuonsTagInfos * (akFilter4CaloSoftPFMuonBJetTags
                +
                akFilter4CaloSoftPFMuonByIP3dBJetTags
                +
                akFilter4CaloSoftPFMuonByPtBJetTags               
              )
            )

akFilter4CaloJetBtagging = cms.Sequence(akFilter4CaloJetBtaggingIP
            *akFilter4CaloJetBtaggingSV
#            *akFilter4CaloJetBtaggingMu
            )

akFilter4CalopatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akFilter4CaloJets"),
        genJetMatch          = cms.InputTag("akFilter4Calomatch"),
        genPartonMatch       = cms.InputTag("akFilter4Caloparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akFilter4Calocorr")),
        #JetPartonMapSource   = cms.InputTag("akFilter4CaloPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akFilter4CaloPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akFilter4CaloPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akFilter4CaloJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akFilter4CaloSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akFilter4CaloSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akFilter4CaloCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akFilter4CaloCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akFilter4CaloJetBProbabilityBJetTags"),
            cms.InputTag("akFilter4CaloJetProbabilityBJetTags"),
            #cms.InputTag("akFilter4CaloSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akFilter4CaloSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akFilter4CaloTrackCountingHighEffBJetTags"),
            cms.InputTag("akFilter4CaloTrackCountingHighPurBJetTags"),
            cms.InputTag("akFilter4CaloPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akFilter4CaloJetID"),
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

akFilter4CaloNjettiness = Njettiness.clone(
		    src = cms.InputTag("akFilter4CaloJets"),
           	    R0  = cms.double( 0.4)
)
#ppDataDummy_akFilter4CalopatJetsWithBtagging.userData.userFloats.src += ['akFilter4CaloNjettiness:tau1','akFilter4CaloNjettiness:tau2','akFilter4CaloNjettiness:tau3']

akFilter4CaloJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akFilter4CalopatJetsWithBtagging"),
                                                             genjetTag = 'ak4GenJets',
                                                             rParam = 0.4,
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
                                                             bTagJetName = cms.untracked.string("akFilter4Calo"),
                                                             jetName = cms.untracked.string("akFilter4Calo"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akFilter4GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(False),
							     jetFlavourInfos = cms.InputTag("akFilter4CaloPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akFilter4CaloPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akFilter4CaloJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = False
                                                            )

akFilter4CalopatJetsWithBtagging.getJetMCFlavour = False
akFilter4CaloJetAnalyzer.doExtendedFlavorTagging = False

akFilter4CaloJetAnalyzer.trackSelection = akFilter4CaloSecondaryVertexTagInfos.trackSelection
akFilter4CaloJetAnalyzer.trackPairV0Filter = akFilter4CaloSecondaryVertexTagInfos.vertexCuts.v0Filter

akFilter4CaloJetSequence_mc = cms.Sequence(
                                                  #akFilter4Caloclean
                                                  #*
                                                  akFilter4Calomatch
                                                  #*
                                                  #akFilter4CalomatchGroomed
                                                  *
                                                  akFilter4Caloparton
                                                  *
                                                  akFilter4Calocorr
                                                  *
                                                  #akFilter4CaloJetID
                                                  #*
                                                  #akFilter4CaloPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  #DISABLE_PPCALO_akFilter4CaloPatJetFlavourId  # doesn't work for PbPb yet
                                                  #DISABLE_PPCALO_*
                                                  akFilter4CaloJetTracksAssociatorAtVertex
                                                  *
                                                  akFilter4CaloJetBtagging
                                                  *
                                                  #DISABLE_PPCALO_akFilter4CaloNjettiness
                                                  #DISABLE_PPCALO_*
                                                  akFilter4CalopatJetsWithBtagging
                                                  *
                                                  akFilter4CaloJetAnalyzer
                                                  )

akFilter4CaloJetSequence_data = cms.Sequence(akFilter4Calocorr
                                                    *
                                                    #akFilter4CaloJetID
                                                    #*
                                                    akFilter4CaloJetTracksAssociatorAtVertex
                                                    *
                                                    akFilter4CaloJetBtagging
                                                    *
                                                    #DISABLE_PPCALO_akFilter4CaloNjettiness
                                                    #DISABLE_PPCALO_*
                                                    akFilter4CalopatJetsWithBtagging
                                                    *
                                                    akFilter4CaloJetAnalyzer
                                                    )

akFilter4CaloJetSequence_jec = cms.Sequence(akFilter4CaloJetSequence_mc)
akFilter4CaloJetSequence_mb = cms.Sequence(akFilter4CaloJetSequence_mc)

akFilter4CaloJetSequence = cms.Sequence(akFilter4CaloJetSequence_data)
