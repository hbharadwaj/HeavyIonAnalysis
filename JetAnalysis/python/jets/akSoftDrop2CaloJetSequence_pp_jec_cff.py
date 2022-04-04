

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akSoftDrop2Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop2CaloJets"),
    matched = cms.InputTag("ak2GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.2
    )

akSoftDrop2CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop2GenJets"),
    matched = cms.InputTag("ak2GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.2
    )

akSoftDrop2Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop2CaloJets")
                                                        )

akSoftDrop2Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akSoftDrop2CaloJets"),
    payload = "AK4PF"
    )

akSoftDrop2CaloJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akSoftDrop2CaloJets'))

#akSoftDrop2Caloclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak2GenJets'))

akSoftDrop2CalobTagger = bTaggers("akSoftDrop2Calo",0.2,True,True)

#create objects locally since they dont load properly otherwise
#akSoftDrop2Calomatch = akSoftDrop2CalobTagger.match
akSoftDrop2Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop2CaloJets"), matched = cms.InputTag("genParticles"))
akSoftDrop2CaloPatJetFlavourAssociationLegacy = akSoftDrop2CalobTagger.PatJetFlavourAssociationLegacy
akSoftDrop2CaloPatJetPartons = akSoftDrop2CalobTagger.PatJetPartons
akSoftDrop2CaloJetTracksAssociatorAtVertex = akSoftDrop2CalobTagger.JetTracksAssociatorAtVertex
akSoftDrop2CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akSoftDrop2CaloSimpleSecondaryVertexHighEffBJetTags = akSoftDrop2CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop2CaloSimpleSecondaryVertexHighPurBJetTags = akSoftDrop2CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop2CaloCombinedSecondaryVertexBJetTags = akSoftDrop2CalobTagger.CombinedSecondaryVertexBJetTags
akSoftDrop2CaloCombinedSecondaryVertexV2BJetTags = akSoftDrop2CalobTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop2CaloJetBProbabilityBJetTags = akSoftDrop2CalobTagger.JetBProbabilityBJetTags
akSoftDrop2CaloSoftPFMuonByPtBJetTags = akSoftDrop2CalobTagger.SoftPFMuonByPtBJetTags
akSoftDrop2CaloSoftPFMuonByIP3dBJetTags = akSoftDrop2CalobTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop2CaloTrackCountingHighEffBJetTags = akSoftDrop2CalobTagger.TrackCountingHighEffBJetTags
akSoftDrop2CaloTrackCountingHighPurBJetTags = akSoftDrop2CalobTagger.TrackCountingHighPurBJetTags
akSoftDrop2CaloPatJetPartonAssociationLegacy = akSoftDrop2CalobTagger.PatJetPartonAssociationLegacy

akSoftDrop2CaloImpactParameterTagInfos = akSoftDrop2CalobTagger.ImpactParameterTagInfos
akSoftDrop2CaloPfImpactParameterTagInfos = akSoftDrop2CalobTagger.PfImpactParameterTagInfos
akSoftDrop2CaloJetProbabilityBJetTags = akSoftDrop2CalobTagger.JetProbabilityBJetTags

akSoftDrop2CaloSecondaryVertexTagInfos = akSoftDrop2CalobTagger.SecondaryVertexTagInfos
akSoftDrop2CaloSimpleSecondaryVertexHighEffBJetTags = akSoftDrop2CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop2CaloSimpleSecondaryVertexHighPurBJetTags = akSoftDrop2CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop2CaloCombinedSecondaryVertexBJetTags = akSoftDrop2CalobTagger.CombinedSecondaryVertexBJetTags
akSoftDrop2CaloCombinedSecondaryVertexV2BJetTags = akSoftDrop2CalobTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop2CaloPfInclusiveSecondaryVertexFinderTagInfos = akSoftDrop2CalobTagger.PfInclusiveSecondaryVertexFinderTagInfos
akSoftDrop2CaloPfDeepCSVTagInfos = akSoftDrop2CalobTagger.PfDeepCSVTagInfos
akSoftDrop2CaloPfDeepCSVJetTags = akSoftDrop2CalobTagger.PfDeepCSVJetTags


akSoftDrop2CaloSoftPFMuonsTagInfos = akSoftDrop2CalobTagger.SoftPFMuonsTagInfos
akSoftDrop2CaloSoftPFMuonBJetTags = akSoftDrop2CalobTagger.SoftPFMuonBJetTags
akSoftDrop2CaloSoftPFMuonByIP3dBJetTags = akSoftDrop2CalobTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop2CaloSoftPFMuonByPtBJetTags = akSoftDrop2CalobTagger.SoftPFMuonByPtBJetTags
akSoftDrop2CaloPatJetFlavourIdLegacy = cms.Sequence(akSoftDrop2CaloPatJetPartonAssociationLegacy*akSoftDrop2CaloPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akSoftDrop2CaloPatJetFlavourAssociation = akSoftDrop2CalobTagger.PatJetFlavourAssociation
akSoftDrop2CaloPatJetFlavourId = cms.Sequence(akSoftDrop2CaloPatJetPartons*akSoftDrop2CaloPatJetFlavourAssociation)

#adding the subjet taggers
akSoftDrop2CaloSubjetImpactParameterTagInfos = akSoftDrop2CalobTagger.SubjetImpactParameterTagInfos
akSoftDrop2CaloSubjetJetProbabilityBJetTags = akSoftDrop2CalobTagger.SubjetJetProbabilityBJetTags
akSoftDrop2CaloSubjetSecondaryVertexTagInfos = akSoftDrop2CalobTagger.SubjetSecondaryVertexTagInfos
akSoftDrop2CaloSubjetJetTracksAssociatorAtVertex = akSoftDrop2CalobTagger.SubjetJetTracksAssociatorAtVertex
akSoftDrop2CaloCombinedSubjetSecondaryVertexBJetTags = akSoftDrop2CalobTagger.CombinedSubjetSecondaryVertexBJetTags
akSoftDrop2CaloCombinedSubjetSecondaryVertexV2BJetTags = akSoftDrop2CalobTagger.CombinedSubjetSecondaryVertexV2BJetTags

akSoftDrop2CaloJetBtaggingIP       = cms.Sequence(akSoftDrop2CaloImpactParameterTagInfos *
            (akSoftDrop2CaloTrackCountingHighEffBJetTags +
             akSoftDrop2CaloTrackCountingHighPurBJetTags +
             akSoftDrop2CaloJetProbabilityBJetTags +
             akSoftDrop2CaloJetBProbabilityBJetTags 
            ) *
	     akSoftDrop2CaloPfImpactParameterTagInfos 
            )

akSoftDrop2CaloJetBtaggingSV = cms.Sequence(akSoftDrop2CaloImpactParameterTagInfos
            *
            akSoftDrop2CaloSecondaryVertexTagInfos
            * (akSoftDrop2CaloSimpleSecondaryVertexHighEffBJetTags+
                akSoftDrop2CaloSimpleSecondaryVertexHighPurBJetTags+
                akSoftDrop2CaloCombinedSecondaryVertexBJetTags+
                akSoftDrop2CaloCombinedSecondaryVertexV2BJetTags
              ) *
	    akSoftDrop2CaloPfImpactParameterTagInfos *
	    akSoftDrop2CaloPfInclusiveSecondaryVertexFinderTagInfos *
	    akSoftDrop2CaloPfDeepCSVTagInfos *
	    akSoftDrop2CaloPfDeepCSVJetTags  
            )



akSoftDrop2CaloJetBtaggingMu = cms.Sequence(akSoftDrop2CaloSoftPFMuonsTagInfos * (akSoftDrop2CaloSoftPFMuonBJetTags
                +
                akSoftDrop2CaloSoftPFMuonByIP3dBJetTags
                +
                akSoftDrop2CaloSoftPFMuonByPtBJetTags               
              )
            )

akSoftDrop2CaloJetBtagging = cms.Sequence(akSoftDrop2CaloJetBtaggingIP
            *akSoftDrop2CaloJetBtaggingSV
#            *akSoftDrop2CaloJetBtaggingMu
            )

akSoftDrop2CalopatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akSoftDrop2CaloJets"),
        genJetMatch          = cms.InputTag("akSoftDrop2Calomatch"),
        genPartonMatch       = cms.InputTag("akSoftDrop2Caloparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akSoftDrop2Calocorr")),
        #JetPartonMapSource   = cms.InputTag("akSoftDrop2CaloPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akSoftDrop2CaloPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akSoftDrop2CaloPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akSoftDrop2CaloJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akSoftDrop2CaloSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akSoftDrop2CaloSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akSoftDrop2CaloCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akSoftDrop2CaloCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akSoftDrop2CaloJetBProbabilityBJetTags"),
            cms.InputTag("akSoftDrop2CaloJetProbabilityBJetTags"),
            #cms.InputTag("akSoftDrop2CaloSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akSoftDrop2CaloSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akSoftDrop2CaloTrackCountingHighEffBJetTags"),
            cms.InputTag("akSoftDrop2CaloTrackCountingHighPurBJetTags"),
            cms.InputTag("akSoftDrop2CaloPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akSoftDrop2CaloJetID"),
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

akSoftDrop2CaloNjettiness = Njettiness.clone(
		    src = cms.InputTag("akSoftDrop2CaloJets"),
           	    R0  = cms.double( 0.2)
)
#ppDataDummy_akSoftDrop2CalopatJetsWithBtagging.userData.userFloats.src += ['akSoftDrop2CaloNjettiness:tau1','akSoftDrop2CaloNjettiness:tau2','akSoftDrop2CaloNjettiness:tau3']

akSoftDrop2CaloJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akSoftDrop2CalopatJetsWithBtagging"),
                                                             genjetTag = 'ak2GenJets',
                                                             rParam = 0.2,
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
                                                             bTagJetName = cms.untracked.string("akSoftDrop2Calo"),
                                                             jetName = cms.untracked.string("akSoftDrop2Calo"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akSoftDrop2GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("akSoftDrop2CaloPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akSoftDrop2CaloPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akSoftDrop2CaloJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

akSoftDrop2CalopatJetsWithBtagging.getJetMCFlavour = False
akSoftDrop2CaloJetAnalyzer.doExtendedFlavorTagging = False

akSoftDrop2CaloJetAnalyzer.trackSelection = akSoftDrop2CaloSecondaryVertexTagInfos.trackSelection
akSoftDrop2CaloJetAnalyzer.trackPairV0Filter = akSoftDrop2CaloSecondaryVertexTagInfos.vertexCuts.v0Filter

akSoftDrop2CaloJetSequence_mc = cms.Sequence(
                                                  #akSoftDrop2Caloclean
                                                  #*
                                                  akSoftDrop2Calomatch
                                                  #*
                                                  #akSoftDrop2CalomatchGroomed
                                                  *
                                                  akSoftDrop2Caloparton
                                                  *
                                                  akSoftDrop2Calocorr
                                                  *
                                                  #akSoftDrop2CaloJetID
                                                  #*
                                                  #akSoftDrop2CaloPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  #DISABLE_PPCALO_akSoftDrop2CaloPatJetFlavourId  # doesn't work for PbPb yet
                                                  #DISABLE_PPCALO_*
                                                  akSoftDrop2CaloJetTracksAssociatorAtVertex
                                                  *
                                                  akSoftDrop2CaloJetBtagging
                                                  *
                                                  #DISABLE_PPCALO_akSoftDrop2CaloNjettiness
                                                  #DISABLE_PPCALO_*
                                                  akSoftDrop2CalopatJetsWithBtagging
                                                  *
                                                  akSoftDrop2CaloJetAnalyzer
                                                  )

akSoftDrop2CaloJetSequence_data = cms.Sequence(akSoftDrop2Calocorr
                                                    *
                                                    #akSoftDrop2CaloJetID
                                                    #*
                                                    akSoftDrop2CaloJetTracksAssociatorAtVertex
                                                    *
                                                    akSoftDrop2CaloJetBtagging
                                                    *
                                                    #DISABLE_PPCALO_akSoftDrop2CaloNjettiness
                                                    #DISABLE_PPCALO_*
                                                    akSoftDrop2CalopatJetsWithBtagging
                                                    *
                                                    akSoftDrop2CaloJetAnalyzer
                                                    )

akSoftDrop2CaloJetSequence_jec = cms.Sequence(akSoftDrop2CaloJetSequence_mc)
akSoftDrop2CaloJetSequence_mb = cms.Sequence(akSoftDrop2CaloJetSequence_mc)

akSoftDrop2CaloJetSequence = cms.Sequence(akSoftDrop2CaloJetSequence_jec)
akSoftDrop2CaloJetAnalyzer.genPtMin = cms.untracked.double(1)
akSoftDrop2CaloJetAnalyzer.jetPtMin = cms.double(1)
akSoftDrop2CaloJetAnalyzer.doSubEvent = True
