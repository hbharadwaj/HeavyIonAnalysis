

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akSoftDrop1Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop1CaloJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

akSoftDrop1CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop1GenJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

akSoftDrop1Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop1CaloJets")
                                                        )

akSoftDrop1Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative','L2L3Residual'),
    src = cms.InputTag("akSoftDrop1CaloJets"),
    payload = "AK4PF"
    )

akSoftDrop1CaloJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akSoftDrop1CaloJets'))

#akSoftDrop1Caloclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak1GenJets'))

akSoftDrop1CalobTagger = bTaggers("akSoftDrop1Calo",0.1,True,True)

#create objects locally since they dont load properly otherwise
#akSoftDrop1Calomatch = akSoftDrop1CalobTagger.match
akSoftDrop1Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop1CaloJets"), matched = cms.InputTag("genParticles"))
akSoftDrop1CaloPatJetFlavourAssociationLegacy = akSoftDrop1CalobTagger.PatJetFlavourAssociationLegacy
akSoftDrop1CaloPatJetPartons = akSoftDrop1CalobTagger.PatJetPartons
akSoftDrop1CaloJetTracksAssociatorAtVertex = akSoftDrop1CalobTagger.JetTracksAssociatorAtVertex
akSoftDrop1CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akSoftDrop1CaloSimpleSecondaryVertexHighEffBJetTags = akSoftDrop1CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop1CaloSimpleSecondaryVertexHighPurBJetTags = akSoftDrop1CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop1CaloCombinedSecondaryVertexBJetTags = akSoftDrop1CalobTagger.CombinedSecondaryVertexBJetTags
akSoftDrop1CaloCombinedSecondaryVertexV2BJetTags = akSoftDrop1CalobTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop1CaloJetBProbabilityBJetTags = akSoftDrop1CalobTagger.JetBProbabilityBJetTags
akSoftDrop1CaloSoftPFMuonByPtBJetTags = akSoftDrop1CalobTagger.SoftPFMuonByPtBJetTags
akSoftDrop1CaloSoftPFMuonByIP3dBJetTags = akSoftDrop1CalobTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop1CaloTrackCountingHighEffBJetTags = akSoftDrop1CalobTagger.TrackCountingHighEffBJetTags
akSoftDrop1CaloTrackCountingHighPurBJetTags = akSoftDrop1CalobTagger.TrackCountingHighPurBJetTags
akSoftDrop1CaloPatJetPartonAssociationLegacy = akSoftDrop1CalobTagger.PatJetPartonAssociationLegacy

akSoftDrop1CaloImpactParameterTagInfos = akSoftDrop1CalobTagger.ImpactParameterTagInfos
akSoftDrop1CaloPfImpactParameterTagInfos = akSoftDrop1CalobTagger.PfImpactParameterTagInfos
akSoftDrop1CaloJetProbabilityBJetTags = akSoftDrop1CalobTagger.JetProbabilityBJetTags

akSoftDrop1CaloSecondaryVertexTagInfos = akSoftDrop1CalobTagger.SecondaryVertexTagInfos
akSoftDrop1CaloSimpleSecondaryVertexHighEffBJetTags = akSoftDrop1CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop1CaloSimpleSecondaryVertexHighPurBJetTags = akSoftDrop1CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop1CaloCombinedSecondaryVertexBJetTags = akSoftDrop1CalobTagger.CombinedSecondaryVertexBJetTags
akSoftDrop1CaloCombinedSecondaryVertexV2BJetTags = akSoftDrop1CalobTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop1CaloPfInclusiveSecondaryVertexFinderTagInfos = akSoftDrop1CalobTagger.PfInclusiveSecondaryVertexFinderTagInfos
akSoftDrop1CaloPfDeepCSVTagInfos = akSoftDrop1CalobTagger.PfDeepCSVTagInfos
akSoftDrop1CaloPfDeepCSVJetTags = akSoftDrop1CalobTagger.PfDeepCSVJetTags


akSoftDrop1CaloSoftPFMuonsTagInfos = akSoftDrop1CalobTagger.SoftPFMuonsTagInfos
akSoftDrop1CaloSoftPFMuonBJetTags = akSoftDrop1CalobTagger.SoftPFMuonBJetTags
akSoftDrop1CaloSoftPFMuonByIP3dBJetTags = akSoftDrop1CalobTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop1CaloSoftPFMuonByPtBJetTags = akSoftDrop1CalobTagger.SoftPFMuonByPtBJetTags
akSoftDrop1CaloPatJetFlavourIdLegacy = cms.Sequence(akSoftDrop1CaloPatJetPartonAssociationLegacy*akSoftDrop1CaloPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akSoftDrop1CaloPatJetFlavourAssociation = akSoftDrop1CalobTagger.PatJetFlavourAssociation
akSoftDrop1CaloPatJetFlavourId = cms.Sequence(akSoftDrop1CaloPatJetPartons*akSoftDrop1CaloPatJetFlavourAssociation)

#adding the subjet taggers
akSoftDrop1CaloSubjetImpactParameterTagInfos = akSoftDrop1CalobTagger.SubjetImpactParameterTagInfos
akSoftDrop1CaloSubjetJetProbabilityBJetTags = akSoftDrop1CalobTagger.SubjetJetProbabilityBJetTags
akSoftDrop1CaloSubjetSecondaryVertexTagInfos = akSoftDrop1CalobTagger.SubjetSecondaryVertexTagInfos
akSoftDrop1CaloSubjetJetTracksAssociatorAtVertex = akSoftDrop1CalobTagger.SubjetJetTracksAssociatorAtVertex
akSoftDrop1CaloCombinedSubjetSecondaryVertexBJetTags = akSoftDrop1CalobTagger.CombinedSubjetSecondaryVertexBJetTags
akSoftDrop1CaloCombinedSubjetSecondaryVertexV2BJetTags = akSoftDrop1CalobTagger.CombinedSubjetSecondaryVertexV2BJetTags

akSoftDrop1CaloJetBtaggingIP       = cms.Sequence(akSoftDrop1CaloImpactParameterTagInfos *
            (akSoftDrop1CaloTrackCountingHighEffBJetTags +
             akSoftDrop1CaloTrackCountingHighPurBJetTags +
             akSoftDrop1CaloJetProbabilityBJetTags +
             akSoftDrop1CaloJetBProbabilityBJetTags 
            ) *
	     akSoftDrop1CaloPfImpactParameterTagInfos 
            )

akSoftDrop1CaloJetBtaggingSV = cms.Sequence(akSoftDrop1CaloImpactParameterTagInfos
            *
            akSoftDrop1CaloSecondaryVertexTagInfos
            * (akSoftDrop1CaloSimpleSecondaryVertexHighEffBJetTags+
                akSoftDrop1CaloSimpleSecondaryVertexHighPurBJetTags+
                akSoftDrop1CaloCombinedSecondaryVertexBJetTags+
                akSoftDrop1CaloCombinedSecondaryVertexV2BJetTags
              ) *
	    akSoftDrop1CaloPfImpactParameterTagInfos *
	    akSoftDrop1CaloPfInclusiveSecondaryVertexFinderTagInfos *
	    akSoftDrop1CaloPfDeepCSVTagInfos *
	    akSoftDrop1CaloPfDeepCSVJetTags  
            )



akSoftDrop1CaloJetBtaggingMu = cms.Sequence(akSoftDrop1CaloSoftPFMuonsTagInfos * (akSoftDrop1CaloSoftPFMuonBJetTags
                +
                akSoftDrop1CaloSoftPFMuonByIP3dBJetTags
                +
                akSoftDrop1CaloSoftPFMuonByPtBJetTags               
              )
            )

akSoftDrop1CaloJetBtagging = cms.Sequence(akSoftDrop1CaloJetBtaggingIP
            *akSoftDrop1CaloJetBtaggingSV
#            *akSoftDrop1CaloJetBtaggingMu
            )

akSoftDrop1CalopatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akSoftDrop1CaloJets"),
        genJetMatch          = cms.InputTag("akSoftDrop1Calomatch"),
        genPartonMatch       = cms.InputTag("akSoftDrop1Caloparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akSoftDrop1Calocorr")),
        #JetPartonMapSource   = cms.InputTag("akSoftDrop1CaloPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akSoftDrop1CaloPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akSoftDrop1CaloPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akSoftDrop1CaloJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akSoftDrop1CaloSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akSoftDrop1CaloSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akSoftDrop1CaloCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akSoftDrop1CaloCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akSoftDrop1CaloJetBProbabilityBJetTags"),
            cms.InputTag("akSoftDrop1CaloJetProbabilityBJetTags"),
            #cms.InputTag("akSoftDrop1CaloSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akSoftDrop1CaloSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akSoftDrop1CaloTrackCountingHighEffBJetTags"),
            cms.InputTag("akSoftDrop1CaloTrackCountingHighPurBJetTags"),
            cms.InputTag("akSoftDrop1CaloPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akSoftDrop1CaloJetID"),
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

akSoftDrop1CaloNjettiness = Njettiness.clone(
		    src = cms.InputTag("akSoftDrop1CaloJets"),
           	    R0  = cms.double( 0.1)
)
#ppDataDummy_akSoftDrop1CalopatJetsWithBtagging.userData.userFloats.src += ['akSoftDrop1CaloNjettiness:tau1','akSoftDrop1CaloNjettiness:tau2','akSoftDrop1CaloNjettiness:tau3']

akSoftDrop1CaloJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akSoftDrop1CalopatJetsWithBtagging"),
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
                                                             bTagJetName = cms.untracked.string("akSoftDrop1Calo"),
                                                             jetName = cms.untracked.string("akSoftDrop1Calo"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akSoftDrop1GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(False),
							     jetFlavourInfos = cms.InputTag("akSoftDrop1CaloPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akSoftDrop1CaloPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akSoftDrop1CaloJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = False
                                                            )

akSoftDrop1CalopatJetsWithBtagging.getJetMCFlavour = False
akSoftDrop1CaloJetAnalyzer.doExtendedFlavorTagging = False

akSoftDrop1CaloJetAnalyzer.trackSelection = akSoftDrop1CaloSecondaryVertexTagInfos.trackSelection
akSoftDrop1CaloJetAnalyzer.trackPairV0Filter = akSoftDrop1CaloSecondaryVertexTagInfos.vertexCuts.v0Filter

akSoftDrop1CaloJetSequence_mc = cms.Sequence(
                                                  #akSoftDrop1Caloclean
                                                  #*
                                                  akSoftDrop1Calomatch
                                                  #*
                                                  #akSoftDrop1CalomatchGroomed
                                                  *
                                                  akSoftDrop1Caloparton
                                                  *
                                                  akSoftDrop1Calocorr
                                                  *
                                                  #akSoftDrop1CaloJetID
                                                  #*
                                                  #akSoftDrop1CaloPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  #DISABLE_PPCALO_akSoftDrop1CaloPatJetFlavourId  # doesn't work for PbPb yet
                                                  #DISABLE_PPCALO_*
                                                  akSoftDrop1CaloJetTracksAssociatorAtVertex
                                                  *
                                                  akSoftDrop1CaloJetBtagging
                                                  *
                                                  #DISABLE_PPCALO_akSoftDrop1CaloNjettiness
                                                  #DISABLE_PPCALO_*
                                                  akSoftDrop1CalopatJetsWithBtagging
                                                  *
                                                  akSoftDrop1CaloJetAnalyzer
                                                  )

akSoftDrop1CaloJetSequence_data = cms.Sequence(akSoftDrop1Calocorr
                                                    *
                                                    #akSoftDrop1CaloJetID
                                                    #*
                                                    akSoftDrop1CaloJetTracksAssociatorAtVertex
                                                    *
                                                    akSoftDrop1CaloJetBtagging
                                                    *
                                                    #DISABLE_PPCALO_akSoftDrop1CaloNjettiness
                                                    #DISABLE_PPCALO_*
                                                    akSoftDrop1CalopatJetsWithBtagging
                                                    *
                                                    akSoftDrop1CaloJetAnalyzer
                                                    )

akSoftDrop1CaloJetSequence_jec = cms.Sequence(akSoftDrop1CaloJetSequence_mc)
akSoftDrop1CaloJetSequence_mb = cms.Sequence(akSoftDrop1CaloJetSequence_mc)

akSoftDrop1CaloJetSequence = cms.Sequence(akSoftDrop1CaloJetSequence_data)
