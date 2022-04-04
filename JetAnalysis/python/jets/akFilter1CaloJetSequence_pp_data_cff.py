

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akFilter1Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter1CaloJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

akFilter1CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akFilter1GenJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

akFilter1Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter1CaloJets")
                                                        )

akFilter1Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative','L2L3Residual'),
    src = cms.InputTag("akFilter1CaloJets"),
    payload = "AK4PF"
    )

akFilter1CaloJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akFilter1CaloJets'))

#akFilter1Caloclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak1GenJets'))

akFilter1CalobTagger = bTaggers("akFilter1Calo",0.1,True,True)

#create objects locally since they dont load properly otherwise
#akFilter1Calomatch = akFilter1CalobTagger.match
akFilter1Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akFilter1CaloJets"), matched = cms.InputTag("genParticles"))
akFilter1CaloPatJetFlavourAssociationLegacy = akFilter1CalobTagger.PatJetFlavourAssociationLegacy
akFilter1CaloPatJetPartons = akFilter1CalobTagger.PatJetPartons
akFilter1CaloJetTracksAssociatorAtVertex = akFilter1CalobTagger.JetTracksAssociatorAtVertex
akFilter1CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akFilter1CaloSimpleSecondaryVertexHighEffBJetTags = akFilter1CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter1CaloSimpleSecondaryVertexHighPurBJetTags = akFilter1CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter1CaloCombinedSecondaryVertexBJetTags = akFilter1CalobTagger.CombinedSecondaryVertexBJetTags
akFilter1CaloCombinedSecondaryVertexV2BJetTags = akFilter1CalobTagger.CombinedSecondaryVertexV2BJetTags
akFilter1CaloJetBProbabilityBJetTags = akFilter1CalobTagger.JetBProbabilityBJetTags
akFilter1CaloSoftPFMuonByPtBJetTags = akFilter1CalobTagger.SoftPFMuonByPtBJetTags
akFilter1CaloSoftPFMuonByIP3dBJetTags = akFilter1CalobTagger.SoftPFMuonByIP3dBJetTags
akFilter1CaloTrackCountingHighEffBJetTags = akFilter1CalobTagger.TrackCountingHighEffBJetTags
akFilter1CaloTrackCountingHighPurBJetTags = akFilter1CalobTagger.TrackCountingHighPurBJetTags
akFilter1CaloPatJetPartonAssociationLegacy = akFilter1CalobTagger.PatJetPartonAssociationLegacy

akFilter1CaloImpactParameterTagInfos = akFilter1CalobTagger.ImpactParameterTagInfos
akFilter1CaloPfImpactParameterTagInfos = akFilter1CalobTagger.PfImpactParameterTagInfos
akFilter1CaloJetProbabilityBJetTags = akFilter1CalobTagger.JetProbabilityBJetTags

akFilter1CaloSecondaryVertexTagInfos = akFilter1CalobTagger.SecondaryVertexTagInfos
akFilter1CaloSimpleSecondaryVertexHighEffBJetTags = akFilter1CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akFilter1CaloSimpleSecondaryVertexHighPurBJetTags = akFilter1CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akFilter1CaloCombinedSecondaryVertexBJetTags = akFilter1CalobTagger.CombinedSecondaryVertexBJetTags
akFilter1CaloCombinedSecondaryVertexV2BJetTags = akFilter1CalobTagger.CombinedSecondaryVertexV2BJetTags
akFilter1CaloPfInclusiveSecondaryVertexFinderTagInfos = akFilter1CalobTagger.PfInclusiveSecondaryVertexFinderTagInfos
akFilter1CaloPfDeepCSVTagInfos = akFilter1CalobTagger.PfDeepCSVTagInfos
akFilter1CaloPfDeepCSVJetTags = akFilter1CalobTagger.PfDeepCSVJetTags


akFilter1CaloSoftPFMuonsTagInfos = akFilter1CalobTagger.SoftPFMuonsTagInfos
akFilter1CaloSoftPFMuonBJetTags = akFilter1CalobTagger.SoftPFMuonBJetTags
akFilter1CaloSoftPFMuonByIP3dBJetTags = akFilter1CalobTagger.SoftPFMuonByIP3dBJetTags
akFilter1CaloSoftPFMuonByPtBJetTags = akFilter1CalobTagger.SoftPFMuonByPtBJetTags
akFilter1CaloPatJetFlavourIdLegacy = cms.Sequence(akFilter1CaloPatJetPartonAssociationLegacy*akFilter1CaloPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akFilter1CaloPatJetFlavourAssociation = akFilter1CalobTagger.PatJetFlavourAssociation
akFilter1CaloPatJetFlavourId = cms.Sequence(akFilter1CaloPatJetPartons*akFilter1CaloPatJetFlavourAssociation)

#adding the subjet taggers
akFilter1CaloSubjetImpactParameterTagInfos = akFilter1CalobTagger.SubjetImpactParameterTagInfos
akFilter1CaloSubjetJetProbabilityBJetTags = akFilter1CalobTagger.SubjetJetProbabilityBJetTags
akFilter1CaloSubjetSecondaryVertexTagInfos = akFilter1CalobTagger.SubjetSecondaryVertexTagInfos
akFilter1CaloSubjetJetTracksAssociatorAtVertex = akFilter1CalobTagger.SubjetJetTracksAssociatorAtVertex
akFilter1CaloCombinedSubjetSecondaryVertexBJetTags = akFilter1CalobTagger.CombinedSubjetSecondaryVertexBJetTags
akFilter1CaloCombinedSubjetSecondaryVertexV2BJetTags = akFilter1CalobTagger.CombinedSubjetSecondaryVertexV2BJetTags

akFilter1CaloJetBtaggingIP       = cms.Sequence(akFilter1CaloImpactParameterTagInfos *
            (akFilter1CaloTrackCountingHighEffBJetTags +
             akFilter1CaloTrackCountingHighPurBJetTags +
             akFilter1CaloJetProbabilityBJetTags +
             akFilter1CaloJetBProbabilityBJetTags 
            ) *
	     akFilter1CaloPfImpactParameterTagInfos 
            )

akFilter1CaloJetBtaggingSV = cms.Sequence(akFilter1CaloImpactParameterTagInfos
            *
            akFilter1CaloSecondaryVertexTagInfos
            * (akFilter1CaloSimpleSecondaryVertexHighEffBJetTags+
                akFilter1CaloSimpleSecondaryVertexHighPurBJetTags+
                akFilter1CaloCombinedSecondaryVertexBJetTags+
                akFilter1CaloCombinedSecondaryVertexV2BJetTags
              ) *
	    akFilter1CaloPfImpactParameterTagInfos *
	    akFilter1CaloPfInclusiveSecondaryVertexFinderTagInfos *
	    akFilter1CaloPfDeepCSVTagInfos *
	    akFilter1CaloPfDeepCSVJetTags  
            )



akFilter1CaloJetBtaggingMu = cms.Sequence(akFilter1CaloSoftPFMuonsTagInfos * (akFilter1CaloSoftPFMuonBJetTags
                +
                akFilter1CaloSoftPFMuonByIP3dBJetTags
                +
                akFilter1CaloSoftPFMuonByPtBJetTags               
              )
            )

akFilter1CaloJetBtagging = cms.Sequence(akFilter1CaloJetBtaggingIP
            *akFilter1CaloJetBtaggingSV
#            *akFilter1CaloJetBtaggingMu
            )

akFilter1CalopatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akFilter1CaloJets"),
        genJetMatch          = cms.InputTag("akFilter1Calomatch"),
        genPartonMatch       = cms.InputTag("akFilter1Caloparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akFilter1Calocorr")),
        #JetPartonMapSource   = cms.InputTag("akFilter1CaloPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akFilter1CaloPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akFilter1CaloPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akFilter1CaloJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akFilter1CaloSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akFilter1CaloSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akFilter1CaloCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akFilter1CaloCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akFilter1CaloJetBProbabilityBJetTags"),
            cms.InputTag("akFilter1CaloJetProbabilityBJetTags"),
            #cms.InputTag("akFilter1CaloSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akFilter1CaloSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akFilter1CaloTrackCountingHighEffBJetTags"),
            cms.InputTag("akFilter1CaloTrackCountingHighPurBJetTags"),
            cms.InputTag("akFilter1CaloPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akFilter1CaloJetID"),
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

akFilter1CaloNjettiness = Njettiness.clone(
		    src = cms.InputTag("akFilter1CaloJets"),
           	    R0  = cms.double( 0.1)
)
#ppDataDummy_akFilter1CalopatJetsWithBtagging.userData.userFloats.src += ['akFilter1CaloNjettiness:tau1','akFilter1CaloNjettiness:tau2','akFilter1CaloNjettiness:tau3']

akFilter1CaloJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akFilter1CalopatJetsWithBtagging"),
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
                                                             bTagJetName = cms.untracked.string("akFilter1Calo"),
                                                             jetName = cms.untracked.string("akFilter1Calo"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akFilter1GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(False),
							     jetFlavourInfos = cms.InputTag("akFilter1CaloPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akFilter1CaloPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akFilter1CaloJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = False
                                                            )

akFilter1CalopatJetsWithBtagging.getJetMCFlavour = False
akFilter1CaloJetAnalyzer.doExtendedFlavorTagging = False

akFilter1CaloJetAnalyzer.trackSelection = akFilter1CaloSecondaryVertexTagInfos.trackSelection
akFilter1CaloJetAnalyzer.trackPairV0Filter = akFilter1CaloSecondaryVertexTagInfos.vertexCuts.v0Filter

akFilter1CaloJetSequence_mc = cms.Sequence(
                                                  #akFilter1Caloclean
                                                  #*
                                                  akFilter1Calomatch
                                                  #*
                                                  #akFilter1CalomatchGroomed
                                                  *
                                                  akFilter1Caloparton
                                                  *
                                                  akFilter1Calocorr
                                                  *
                                                  #akFilter1CaloJetID
                                                  #*
                                                  #akFilter1CaloPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  #DISABLE_PPCALO_akFilter1CaloPatJetFlavourId  # doesn't work for PbPb yet
                                                  #DISABLE_PPCALO_*
                                                  akFilter1CaloJetTracksAssociatorAtVertex
                                                  *
                                                  akFilter1CaloJetBtagging
                                                  *
                                                  #DISABLE_PPCALO_akFilter1CaloNjettiness
                                                  #DISABLE_PPCALO_*
                                                  akFilter1CalopatJetsWithBtagging
                                                  *
                                                  akFilter1CaloJetAnalyzer
                                                  )

akFilter1CaloJetSequence_data = cms.Sequence(akFilter1Calocorr
                                                    *
                                                    #akFilter1CaloJetID
                                                    #*
                                                    akFilter1CaloJetTracksAssociatorAtVertex
                                                    *
                                                    akFilter1CaloJetBtagging
                                                    *
                                                    #DISABLE_PPCALO_akFilter1CaloNjettiness
                                                    #DISABLE_PPCALO_*
                                                    akFilter1CalopatJetsWithBtagging
                                                    *
                                                    akFilter1CaloJetAnalyzer
                                                    )

akFilter1CaloJetSequence_jec = cms.Sequence(akFilter1CaloJetSequence_mc)
akFilter1CaloJetSequence_mb = cms.Sequence(akFilter1CaloJetSequence_mc)

akFilter1CaloJetSequence = cms.Sequence(akFilter1CaloJetSequence_data)
