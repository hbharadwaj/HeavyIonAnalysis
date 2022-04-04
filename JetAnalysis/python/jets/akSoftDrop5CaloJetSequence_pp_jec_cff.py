

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

akSoftDrop5Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop5CaloJets"),
    matched = cms.InputTag("ak5GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.5
    )

akSoftDrop5CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("akSoftDrop5GenJets"),
    matched = cms.InputTag("ak5GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.5
    )

akSoftDrop5Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop5CaloJets")
                                                        )

akSoftDrop5Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("akSoftDrop5CaloJets"),
    payload = "AK4PF"
    )

akSoftDrop5CaloJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('akSoftDrop5CaloJets'))

#akSoftDrop5Caloclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak5GenJets'))

akSoftDrop5CalobTagger = bTaggers("akSoftDrop5Calo",0.5,True,True)

#create objects locally since they dont load properly otherwise
#akSoftDrop5Calomatch = akSoftDrop5CalobTagger.match
akSoftDrop5Caloparton = patJetPartonMatch.clone(src = cms.InputTag("akSoftDrop5CaloJets"), matched = cms.InputTag("genParticles"))
akSoftDrop5CaloPatJetFlavourAssociationLegacy = akSoftDrop5CalobTagger.PatJetFlavourAssociationLegacy
akSoftDrop5CaloPatJetPartons = akSoftDrop5CalobTagger.PatJetPartons
akSoftDrop5CaloJetTracksAssociatorAtVertex = akSoftDrop5CalobTagger.JetTracksAssociatorAtVertex
akSoftDrop5CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
akSoftDrop5CaloSimpleSecondaryVertexHighEffBJetTags = akSoftDrop5CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop5CaloSimpleSecondaryVertexHighPurBJetTags = akSoftDrop5CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop5CaloCombinedSecondaryVertexBJetTags = akSoftDrop5CalobTagger.CombinedSecondaryVertexBJetTags
akSoftDrop5CaloCombinedSecondaryVertexV2BJetTags = akSoftDrop5CalobTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop5CaloJetBProbabilityBJetTags = akSoftDrop5CalobTagger.JetBProbabilityBJetTags
akSoftDrop5CaloSoftPFMuonByPtBJetTags = akSoftDrop5CalobTagger.SoftPFMuonByPtBJetTags
akSoftDrop5CaloSoftPFMuonByIP3dBJetTags = akSoftDrop5CalobTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop5CaloTrackCountingHighEffBJetTags = akSoftDrop5CalobTagger.TrackCountingHighEffBJetTags
akSoftDrop5CaloTrackCountingHighPurBJetTags = akSoftDrop5CalobTagger.TrackCountingHighPurBJetTags
akSoftDrop5CaloPatJetPartonAssociationLegacy = akSoftDrop5CalobTagger.PatJetPartonAssociationLegacy

akSoftDrop5CaloImpactParameterTagInfos = akSoftDrop5CalobTagger.ImpactParameterTagInfos
akSoftDrop5CaloPfImpactParameterTagInfos = akSoftDrop5CalobTagger.PfImpactParameterTagInfos
akSoftDrop5CaloJetProbabilityBJetTags = akSoftDrop5CalobTagger.JetProbabilityBJetTags

akSoftDrop5CaloSecondaryVertexTagInfos = akSoftDrop5CalobTagger.SecondaryVertexTagInfos
akSoftDrop5CaloSimpleSecondaryVertexHighEffBJetTags = akSoftDrop5CalobTagger.SimpleSecondaryVertexHighEffBJetTags
akSoftDrop5CaloSimpleSecondaryVertexHighPurBJetTags = akSoftDrop5CalobTagger.SimpleSecondaryVertexHighPurBJetTags
akSoftDrop5CaloCombinedSecondaryVertexBJetTags = akSoftDrop5CalobTagger.CombinedSecondaryVertexBJetTags
akSoftDrop5CaloCombinedSecondaryVertexV2BJetTags = akSoftDrop5CalobTagger.CombinedSecondaryVertexV2BJetTags
akSoftDrop5CaloPfInclusiveSecondaryVertexFinderTagInfos = akSoftDrop5CalobTagger.PfInclusiveSecondaryVertexFinderTagInfos
akSoftDrop5CaloPfDeepCSVTagInfos = akSoftDrop5CalobTagger.PfDeepCSVTagInfos
akSoftDrop5CaloPfDeepCSVJetTags = akSoftDrop5CalobTagger.PfDeepCSVJetTags


akSoftDrop5CaloSoftPFMuonsTagInfos = akSoftDrop5CalobTagger.SoftPFMuonsTagInfos
akSoftDrop5CaloSoftPFMuonBJetTags = akSoftDrop5CalobTagger.SoftPFMuonBJetTags
akSoftDrop5CaloSoftPFMuonByIP3dBJetTags = akSoftDrop5CalobTagger.SoftPFMuonByIP3dBJetTags
akSoftDrop5CaloSoftPFMuonByPtBJetTags = akSoftDrop5CalobTagger.SoftPFMuonByPtBJetTags
akSoftDrop5CaloPatJetFlavourIdLegacy = cms.Sequence(akSoftDrop5CaloPatJetPartonAssociationLegacy*akSoftDrop5CaloPatJetFlavourAssociationLegacy)
#Not working with our PU sub
akSoftDrop5CaloPatJetFlavourAssociation = akSoftDrop5CalobTagger.PatJetFlavourAssociation
akSoftDrop5CaloPatJetFlavourId = cms.Sequence(akSoftDrop5CaloPatJetPartons*akSoftDrop5CaloPatJetFlavourAssociation)

#adding the subjet taggers
akSoftDrop5CaloSubjetImpactParameterTagInfos = akSoftDrop5CalobTagger.SubjetImpactParameterTagInfos
akSoftDrop5CaloSubjetJetProbabilityBJetTags = akSoftDrop5CalobTagger.SubjetJetProbabilityBJetTags
akSoftDrop5CaloSubjetSecondaryVertexTagInfos = akSoftDrop5CalobTagger.SubjetSecondaryVertexTagInfos
akSoftDrop5CaloSubjetJetTracksAssociatorAtVertex = akSoftDrop5CalobTagger.SubjetJetTracksAssociatorAtVertex
akSoftDrop5CaloCombinedSubjetSecondaryVertexBJetTags = akSoftDrop5CalobTagger.CombinedSubjetSecondaryVertexBJetTags
akSoftDrop5CaloCombinedSubjetSecondaryVertexV2BJetTags = akSoftDrop5CalobTagger.CombinedSubjetSecondaryVertexV2BJetTags

akSoftDrop5CaloJetBtaggingIP       = cms.Sequence(akSoftDrop5CaloImpactParameterTagInfos *
            (akSoftDrop5CaloTrackCountingHighEffBJetTags +
             akSoftDrop5CaloTrackCountingHighPurBJetTags +
             akSoftDrop5CaloJetProbabilityBJetTags +
             akSoftDrop5CaloJetBProbabilityBJetTags 
            ) *
	     akSoftDrop5CaloPfImpactParameterTagInfos 
            )

akSoftDrop5CaloJetBtaggingSV = cms.Sequence(akSoftDrop5CaloImpactParameterTagInfos
            *
            akSoftDrop5CaloSecondaryVertexTagInfos
            * (akSoftDrop5CaloSimpleSecondaryVertexHighEffBJetTags+
                akSoftDrop5CaloSimpleSecondaryVertexHighPurBJetTags+
                akSoftDrop5CaloCombinedSecondaryVertexBJetTags+
                akSoftDrop5CaloCombinedSecondaryVertexV2BJetTags
              ) *
	    akSoftDrop5CaloPfImpactParameterTagInfos *
	    akSoftDrop5CaloPfInclusiveSecondaryVertexFinderTagInfos *
	    akSoftDrop5CaloPfDeepCSVTagInfos *
	    akSoftDrop5CaloPfDeepCSVJetTags  
            )



akSoftDrop5CaloJetBtaggingMu = cms.Sequence(akSoftDrop5CaloSoftPFMuonsTagInfos * (akSoftDrop5CaloSoftPFMuonBJetTags
                +
                akSoftDrop5CaloSoftPFMuonByIP3dBJetTags
                +
                akSoftDrop5CaloSoftPFMuonByPtBJetTags               
              )
            )

akSoftDrop5CaloJetBtagging = cms.Sequence(akSoftDrop5CaloJetBtaggingIP
            *akSoftDrop5CaloJetBtaggingSV
#            *akSoftDrop5CaloJetBtaggingMu
            )

akSoftDrop5CalopatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("akSoftDrop5CaloJets"),
        genJetMatch          = cms.InputTag("akSoftDrop5Calomatch"),
        genPartonMatch       = cms.InputTag("akSoftDrop5Caloparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akSoftDrop5Calocorr")),
        #JetPartonMapSource   = cms.InputTag("akSoftDrop5CaloPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("akSoftDrop5CaloPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("akSoftDrop5CaloPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("akSoftDrop5CaloJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("akSoftDrop5CaloSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("akSoftDrop5CaloSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("akSoftDrop5CaloCombinedSecondaryVertexBJetTags"),
            cms.InputTag("akSoftDrop5CaloCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("akSoftDrop5CaloJetBProbabilityBJetTags"),
            cms.InputTag("akSoftDrop5CaloJetProbabilityBJetTags"),
            #cms.InputTag("akSoftDrop5CaloSoftPFMuonByPtBJetTags"),
            #cms.InputTag("akSoftDrop5CaloSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("akSoftDrop5CaloTrackCountingHighEffBJetTags"),
            cms.InputTag("akSoftDrop5CaloTrackCountingHighPurBJetTags"),
            cms.InputTag("akSoftDrop5CaloPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("akSoftDrop5CaloJetID"),
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

akSoftDrop5CaloNjettiness = Njettiness.clone(
		    src = cms.InputTag("akSoftDrop5CaloJets"),
           	    R0  = cms.double( 0.5)
)
#ppDataDummy_akSoftDrop5CalopatJetsWithBtagging.userData.userFloats.src += ['akSoftDrop5CaloNjettiness:tau1','akSoftDrop5CaloNjettiness:tau2','akSoftDrop5CaloNjettiness:tau3']

akSoftDrop5CaloJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("akSoftDrop5CalopatJetsWithBtagging"),
                                                             genjetTag = 'ak5GenJets',
                                                             rParam = 0.5,
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
                                                             bTagJetName = cms.untracked.string("akSoftDrop5Calo"),
                                                             jetName = cms.untracked.string("akSoftDrop5Calo"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(True),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("akSoftDrop5GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("akSoftDrop5CaloPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("akSoftDrop5CaloPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("akSoftDrop5CaloJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

akSoftDrop5CalopatJetsWithBtagging.getJetMCFlavour = False
akSoftDrop5CaloJetAnalyzer.doExtendedFlavorTagging = False

akSoftDrop5CaloJetAnalyzer.trackSelection = akSoftDrop5CaloSecondaryVertexTagInfos.trackSelection
akSoftDrop5CaloJetAnalyzer.trackPairV0Filter = akSoftDrop5CaloSecondaryVertexTagInfos.vertexCuts.v0Filter

akSoftDrop5CaloJetSequence_mc = cms.Sequence(
                                                  #akSoftDrop5Caloclean
                                                  #*
                                                  akSoftDrop5Calomatch
                                                  #*
                                                  #akSoftDrop5CalomatchGroomed
                                                  *
                                                  akSoftDrop5Caloparton
                                                  *
                                                  akSoftDrop5Calocorr
                                                  *
                                                  #akSoftDrop5CaloJetID
                                                  #*
                                                  #akSoftDrop5CaloPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  #DISABLE_PPCALO_akSoftDrop5CaloPatJetFlavourId  # doesn't work for PbPb yet
                                                  #DISABLE_PPCALO_*
                                                  akSoftDrop5CaloJetTracksAssociatorAtVertex
                                                  *
                                                  akSoftDrop5CaloJetBtagging
                                                  *
                                                  #DISABLE_PPCALO_akSoftDrop5CaloNjettiness
                                                  #DISABLE_PPCALO_*
                                                  akSoftDrop5CalopatJetsWithBtagging
                                                  *
                                                  akSoftDrop5CaloJetAnalyzer
                                                  )

akSoftDrop5CaloJetSequence_data = cms.Sequence(akSoftDrop5Calocorr
                                                    *
                                                    #akSoftDrop5CaloJetID
                                                    #*
                                                    akSoftDrop5CaloJetTracksAssociatorAtVertex
                                                    *
                                                    akSoftDrop5CaloJetBtagging
                                                    *
                                                    #DISABLE_PPCALO_akSoftDrop5CaloNjettiness
                                                    #DISABLE_PPCALO_*
                                                    akSoftDrop5CalopatJetsWithBtagging
                                                    *
                                                    akSoftDrop5CaloJetAnalyzer
                                                    )

akSoftDrop5CaloJetSequence_jec = cms.Sequence(akSoftDrop5CaloJetSequence_mc)
akSoftDrop5CaloJetSequence_mb = cms.Sequence(akSoftDrop5CaloJetSequence_mc)

akSoftDrop5CaloJetSequence = cms.Sequence(akSoftDrop5CaloJetSequence_jec)
akSoftDrop5CaloJetAnalyzer.genPtMin = cms.untracked.double(1)
akSoftDrop5CaloJetAnalyzer.jetPtMin = cms.double(1)
akSoftDrop5CaloJetAnalyzer.doSubEvent = True
