

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak6Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak6CaloJets"),
    matched = cms.InputTag("ak6GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.6
    )

ak6CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak6GenJets"),
    matched = cms.InputTag("ak6GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.6
    )

ak6Caloparton = patJetPartonMatch.clone(src = cms.InputTag("ak6CaloJets")
                                                        )

ak6Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("ak6CaloJets"),
    payload = "AK4PF"
    )

ak6CaloJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('ak6CaloJets'))

#ak6Caloclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak6GenJets'))

ak6CalobTagger = bTaggers("ak6Calo",0.6,True,False)

#create objects locally since they dont load properly otherwise
#ak6Calomatch = ak6CalobTagger.match
ak6Caloparton = patJetPartonMatch.clone(src = cms.InputTag("ak6CaloJets"), matched = cms.InputTag("genParticles"))
ak6CaloPatJetFlavourAssociationLegacy = ak6CalobTagger.PatJetFlavourAssociationLegacy
ak6CaloPatJetPartons = ak6CalobTagger.PatJetPartons
ak6CaloJetTracksAssociatorAtVertex = ak6CalobTagger.JetTracksAssociatorAtVertex
ak6CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
ak6CaloSimpleSecondaryVertexHighEffBJetTags = ak6CalobTagger.SimpleSecondaryVertexHighEffBJetTags
ak6CaloSimpleSecondaryVertexHighPurBJetTags = ak6CalobTagger.SimpleSecondaryVertexHighPurBJetTags
ak6CaloCombinedSecondaryVertexBJetTags = ak6CalobTagger.CombinedSecondaryVertexBJetTags
ak6CaloCombinedSecondaryVertexV2BJetTags = ak6CalobTagger.CombinedSecondaryVertexV2BJetTags
ak6CaloJetBProbabilityBJetTags = ak6CalobTagger.JetBProbabilityBJetTags
ak6CaloSoftPFMuonByPtBJetTags = ak6CalobTagger.SoftPFMuonByPtBJetTags
ak6CaloSoftPFMuonByIP3dBJetTags = ak6CalobTagger.SoftPFMuonByIP3dBJetTags
ak6CaloTrackCountingHighEffBJetTags = ak6CalobTagger.TrackCountingHighEffBJetTags
ak6CaloTrackCountingHighPurBJetTags = ak6CalobTagger.TrackCountingHighPurBJetTags
ak6CaloPatJetPartonAssociationLegacy = ak6CalobTagger.PatJetPartonAssociationLegacy

ak6CaloImpactParameterTagInfos = ak6CalobTagger.ImpactParameterTagInfos
ak6CaloPfImpactParameterTagInfos = ak6CalobTagger.PfImpactParameterTagInfos
ak6CaloJetProbabilityBJetTags = ak6CalobTagger.JetProbabilityBJetTags

ak6CaloSecondaryVertexTagInfos = ak6CalobTagger.SecondaryVertexTagInfos
ak6CaloSimpleSecondaryVertexHighEffBJetTags = ak6CalobTagger.SimpleSecondaryVertexHighEffBJetTags
ak6CaloSimpleSecondaryVertexHighPurBJetTags = ak6CalobTagger.SimpleSecondaryVertexHighPurBJetTags
ak6CaloCombinedSecondaryVertexBJetTags = ak6CalobTagger.CombinedSecondaryVertexBJetTags
ak6CaloCombinedSecondaryVertexV2BJetTags = ak6CalobTagger.CombinedSecondaryVertexV2BJetTags
ak6CaloPfInclusiveSecondaryVertexFinderTagInfos = ak6CalobTagger.PfInclusiveSecondaryVertexFinderTagInfos
ak6CaloPfDeepCSVTagInfos = ak6CalobTagger.PfDeepCSVTagInfos
ak6CaloPfDeepCSVJetTags = ak6CalobTagger.PfDeepCSVJetTags


ak6CaloSoftPFMuonsTagInfos = ak6CalobTagger.SoftPFMuonsTagInfos
ak6CaloSoftPFMuonBJetTags = ak6CalobTagger.SoftPFMuonBJetTags
ak6CaloSoftPFMuonByIP3dBJetTags = ak6CalobTagger.SoftPFMuonByIP3dBJetTags
ak6CaloSoftPFMuonByPtBJetTags = ak6CalobTagger.SoftPFMuonByPtBJetTags
ak6CaloPatJetFlavourIdLegacy = cms.Sequence(ak6CaloPatJetPartonAssociationLegacy*ak6CaloPatJetFlavourAssociationLegacy)
#Not working with our PU sub
ak6CaloPatJetFlavourAssociation = ak6CalobTagger.PatJetFlavourAssociation
ak6CaloPatJetFlavourId = cms.Sequence(ak6CaloPatJetPartons*ak6CaloPatJetFlavourAssociation)

#adding the subjet taggers
#SUBJETDUMMY_ak6CaloSubjetImpactParameterTagInfos = ak6CalobTagger.SubjetImpactParameterTagInfos
#SUBJETDUMMY_ak6CaloSubjetJetProbabilityBJetTags = ak6CalobTagger.SubjetJetProbabilityBJetTags
#SUBJETDUMMY_ak6CaloSubjetSecondaryVertexTagInfos = ak6CalobTagger.SubjetSecondaryVertexTagInfos
#SUBJETDUMMY_ak6CaloSubjetJetTracksAssociatorAtVertex = ak6CalobTagger.SubjetJetTracksAssociatorAtVertex
#SUBJETDUMMY_ak6CaloCombinedSubjetSecondaryVertexBJetTags = ak6CalobTagger.CombinedSubjetSecondaryVertexBJetTags
#SUBJETDUMMY_ak6CaloCombinedSubjetSecondaryVertexV2BJetTags = ak6CalobTagger.CombinedSubjetSecondaryVertexV2BJetTags

ak6CaloJetBtaggingIP       = cms.Sequence(ak6CaloImpactParameterTagInfos *
            (ak6CaloTrackCountingHighEffBJetTags +
             ak6CaloTrackCountingHighPurBJetTags +
             ak6CaloJetProbabilityBJetTags +
             ak6CaloJetBProbabilityBJetTags 
            ) *
	     ak6CaloPfImpactParameterTagInfos 
            )

ak6CaloJetBtaggingSV = cms.Sequence(ak6CaloImpactParameterTagInfos
            *
            ak6CaloSecondaryVertexTagInfos
            * (ak6CaloSimpleSecondaryVertexHighEffBJetTags+
                ak6CaloSimpleSecondaryVertexHighPurBJetTags+
                ak6CaloCombinedSecondaryVertexBJetTags+
                ak6CaloCombinedSecondaryVertexV2BJetTags
              ) *
	    ak6CaloPfImpactParameterTagInfos *
	    ak6CaloPfInclusiveSecondaryVertexFinderTagInfos *
	    ak6CaloPfDeepCSVTagInfos *
	    ak6CaloPfDeepCSVJetTags  
            )



ak6CaloJetBtaggingMu = cms.Sequence(ak6CaloSoftPFMuonsTagInfos * (ak6CaloSoftPFMuonBJetTags
                +
                ak6CaloSoftPFMuonByIP3dBJetTags
                +
                ak6CaloSoftPFMuonByPtBJetTags               
              )
            )

ak6CaloJetBtagging = cms.Sequence(ak6CaloJetBtaggingIP
            *ak6CaloJetBtaggingSV
#            *ak6CaloJetBtaggingMu
            )

ak6CalopatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("ak6CaloJets"),
        genJetMatch          = cms.InputTag("ak6Calomatch"),
        genPartonMatch       = cms.InputTag("ak6Caloparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak6Calocorr")),
        #JetPartonMapSource   = cms.InputTag("ak6CaloPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("ak6CaloPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("ak6CaloPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("ak6CaloJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("ak6CaloSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("ak6CaloSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("ak6CaloCombinedSecondaryVertexBJetTags"),
            cms.InputTag("ak6CaloCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("ak6CaloJetBProbabilityBJetTags"),
            cms.InputTag("ak6CaloJetProbabilityBJetTags"),
            #cms.InputTag("ak6CaloSoftPFMuonByPtBJetTags"),
            #cms.InputTag("ak6CaloSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("ak6CaloTrackCountingHighEffBJetTags"),
            cms.InputTag("ak6CaloTrackCountingHighPurBJetTags"),
            cms.InputTag("ak6CaloPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("ak6CaloJetID"),
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

ak6CaloNjettiness = Njettiness.clone(
		    src = cms.InputTag("ak6CaloJets"),
           	    R0  = cms.double( 0.6)
)
#ppDataDummy_ak6CalopatJetsWithBtagging.userData.userFloats.src += ['ak6CaloNjettiness:tau1','ak6CaloNjettiness:tau2','ak6CaloNjettiness:tau3']

ak6CaloJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("ak6CalopatJetsWithBtagging"),
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
                                                             bTagJetName = cms.untracked.string("ak6Calo"),
                                                             jetName = cms.untracked.string("ak6Calo"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(False),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("ak6GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("ak6CaloPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("ak6CaloPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("ak6CaloJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

ak6CalopatJetsWithBtagging.getJetMCFlavour = False
ak6CaloJetAnalyzer.doExtendedFlavorTagging = False

ak6CaloJetAnalyzer.trackSelection = ak6CaloSecondaryVertexTagInfos.trackSelection
ak6CaloJetAnalyzer.trackPairV0Filter = ak6CaloSecondaryVertexTagInfos.vertexCuts.v0Filter

ak6CaloJetSequence_mc = cms.Sequence(
                                                  #ak6Caloclean
                                                  #*
                                                  ak6Calomatch
                                                  #*
                                                  #ak6CalomatchGroomed
                                                  *
                                                  ak6Caloparton
                                                  *
                                                  ak6Calocorr
                                                  *
                                                  #ak6CaloJetID
                                                  #*
                                                  #ak6CaloPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  #DISABLE_PPCALO_ak6CaloPatJetFlavourId  # doesn't work for PbPb yet
                                                  #DISABLE_PPCALO_*
                                                  ak6CaloJetTracksAssociatorAtVertex
                                                  *
                                                  ak6CaloJetBtagging
                                                  *
                                                  #DISABLE_PPCALO_ak6CaloNjettiness
                                                  #DISABLE_PPCALO_*
                                                  ak6CalopatJetsWithBtagging
                                                  *
                                                  ak6CaloJetAnalyzer
                                                  )

ak6CaloJetSequence_data = cms.Sequence(ak6Calocorr
                                                    *
                                                    #ak6CaloJetID
                                                    #*
                                                    ak6CaloJetTracksAssociatorAtVertex
                                                    *
                                                    ak6CaloJetBtagging
                                                    *
                                                    #DISABLE_PPCALO_ak6CaloNjettiness
                                                    #DISABLE_PPCALO_*
                                                    ak6CalopatJetsWithBtagging
                                                    *
                                                    ak6CaloJetAnalyzer
                                                    )

ak6CaloJetSequence_jec = cms.Sequence(ak6CaloJetSequence_mc)
ak6CaloJetSequence_mb = cms.Sequence(ak6CaloJetSequence_mc)

ak6CaloJetSequence = cms.Sequence(ak6CaloJetSequence_jec)
ak6CaloJetAnalyzer.genPtMin = cms.untracked.double(1)
ak6CaloJetAnalyzer.jetPtMin = cms.double(1)
ak6CaloJetAnalyzer.doSubEvent = True
