

import FWCore.ParameterSet.Config as cms
from HeavyIonsAnalysis.JetAnalysis.patHeavyIonSequences_cff import patJetGenJetMatch, patJetPartonMatch, patJetCorrFactors, patJets
from HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff import *
from HeavyIonsAnalysis.JetAnalysis.bTaggers_cff import *
from RecoJets.JetProducers.JetIDParams_cfi import *
from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness

ak1Calomatch = patJetGenJetMatch.clone(
    src = cms.InputTag("ak1CaloJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

ak1CalomatchGroomed = patJetGenJetMatch.clone(
    src = cms.InputTag("ak1GenJets"),
    matched = cms.InputTag("ak1GenJets"),
    resolveByMatchQuality = cms.bool(False),
    maxDeltaR = 0.1
    )

ak1Caloparton = patJetPartonMatch.clone(src = cms.InputTag("ak1CaloJets")
                                                        )

ak1Calocorr = patJetCorrFactors.clone(
    useNPV = cms.bool(False),
    useRho = cms.bool(False),
#    primaryVertices = cms.InputTag("hiSelectedVertex"),
    levels   = cms.vstring('L2Relative'),
    src = cms.InputTag("ak1CaloJets"),
    payload = "AK4PF"
    )

ak1CaloJetID= cms.EDProducer('JetIDProducer', JetIDParams, src = cms.InputTag('ak1CaloJets'))

#ak1Caloclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak1GenJets'))

ak1CalobTagger = bTaggers("ak1Calo",0.1,True,False)

#create objects locally since they dont load properly otherwise
#ak1Calomatch = ak1CalobTagger.match
ak1Caloparton = patJetPartonMatch.clone(src = cms.InputTag("ak1CaloJets"), matched = cms.InputTag("genParticles"))
ak1CaloPatJetFlavourAssociationLegacy = ak1CalobTagger.PatJetFlavourAssociationLegacy
ak1CaloPatJetPartons = ak1CalobTagger.PatJetPartons
ak1CaloJetTracksAssociatorAtVertex = ak1CalobTagger.JetTracksAssociatorAtVertex
ak1CaloJetTracksAssociatorAtVertex.tracks = cms.InputTag("highPurityTracks")
ak1CaloSimpleSecondaryVertexHighEffBJetTags = ak1CalobTagger.SimpleSecondaryVertexHighEffBJetTags
ak1CaloSimpleSecondaryVertexHighPurBJetTags = ak1CalobTagger.SimpleSecondaryVertexHighPurBJetTags
ak1CaloCombinedSecondaryVertexBJetTags = ak1CalobTagger.CombinedSecondaryVertexBJetTags
ak1CaloCombinedSecondaryVertexV2BJetTags = ak1CalobTagger.CombinedSecondaryVertexV2BJetTags
ak1CaloJetBProbabilityBJetTags = ak1CalobTagger.JetBProbabilityBJetTags
ak1CaloSoftPFMuonByPtBJetTags = ak1CalobTagger.SoftPFMuonByPtBJetTags
ak1CaloSoftPFMuonByIP3dBJetTags = ak1CalobTagger.SoftPFMuonByIP3dBJetTags
ak1CaloTrackCountingHighEffBJetTags = ak1CalobTagger.TrackCountingHighEffBJetTags
ak1CaloTrackCountingHighPurBJetTags = ak1CalobTagger.TrackCountingHighPurBJetTags
ak1CaloPatJetPartonAssociationLegacy = ak1CalobTagger.PatJetPartonAssociationLegacy

ak1CaloImpactParameterTagInfos = ak1CalobTagger.ImpactParameterTagInfos
ak1CaloPfImpactParameterTagInfos = ak1CalobTagger.PfImpactParameterTagInfos
ak1CaloJetProbabilityBJetTags = ak1CalobTagger.JetProbabilityBJetTags

ak1CaloSecondaryVertexTagInfos = ak1CalobTagger.SecondaryVertexTagInfos
ak1CaloSimpleSecondaryVertexHighEffBJetTags = ak1CalobTagger.SimpleSecondaryVertexHighEffBJetTags
ak1CaloSimpleSecondaryVertexHighPurBJetTags = ak1CalobTagger.SimpleSecondaryVertexHighPurBJetTags
ak1CaloCombinedSecondaryVertexBJetTags = ak1CalobTagger.CombinedSecondaryVertexBJetTags
ak1CaloCombinedSecondaryVertexV2BJetTags = ak1CalobTagger.CombinedSecondaryVertexV2BJetTags
ak1CaloPfInclusiveSecondaryVertexFinderTagInfos = ak1CalobTagger.PfInclusiveSecondaryVertexFinderTagInfos
ak1CaloPfDeepCSVTagInfos = ak1CalobTagger.PfDeepCSVTagInfos
ak1CaloPfDeepCSVJetTags = ak1CalobTagger.PfDeepCSVJetTags


ak1CaloSoftPFMuonsTagInfos = ak1CalobTagger.SoftPFMuonsTagInfos
ak1CaloSoftPFMuonBJetTags = ak1CalobTagger.SoftPFMuonBJetTags
ak1CaloSoftPFMuonByIP3dBJetTags = ak1CalobTagger.SoftPFMuonByIP3dBJetTags
ak1CaloSoftPFMuonByPtBJetTags = ak1CalobTagger.SoftPFMuonByPtBJetTags
ak1CaloPatJetFlavourIdLegacy = cms.Sequence(ak1CaloPatJetPartonAssociationLegacy*ak1CaloPatJetFlavourAssociationLegacy)
#Not working with our PU sub
ak1CaloPatJetFlavourAssociation = ak1CalobTagger.PatJetFlavourAssociation
ak1CaloPatJetFlavourId = cms.Sequence(ak1CaloPatJetPartons*ak1CaloPatJetFlavourAssociation)

#adding the subjet taggers
#SUBJETDUMMY_ak1CaloSubjetImpactParameterTagInfos = ak1CalobTagger.SubjetImpactParameterTagInfos
#SUBJETDUMMY_ak1CaloSubjetJetProbabilityBJetTags = ak1CalobTagger.SubjetJetProbabilityBJetTags
#SUBJETDUMMY_ak1CaloSubjetSecondaryVertexTagInfos = ak1CalobTagger.SubjetSecondaryVertexTagInfos
#SUBJETDUMMY_ak1CaloSubjetJetTracksAssociatorAtVertex = ak1CalobTagger.SubjetJetTracksAssociatorAtVertex
#SUBJETDUMMY_ak1CaloCombinedSubjetSecondaryVertexBJetTags = ak1CalobTagger.CombinedSubjetSecondaryVertexBJetTags
#SUBJETDUMMY_ak1CaloCombinedSubjetSecondaryVertexV2BJetTags = ak1CalobTagger.CombinedSubjetSecondaryVertexV2BJetTags

ak1CaloJetBtaggingIP       = cms.Sequence(ak1CaloImpactParameterTagInfos *
            (ak1CaloTrackCountingHighEffBJetTags +
             ak1CaloTrackCountingHighPurBJetTags +
             ak1CaloJetProbabilityBJetTags +
             ak1CaloJetBProbabilityBJetTags 
            ) *
	     ak1CaloPfImpactParameterTagInfos 
            )

ak1CaloJetBtaggingSV = cms.Sequence(ak1CaloImpactParameterTagInfos
            *
            ak1CaloSecondaryVertexTagInfos
            * (ak1CaloSimpleSecondaryVertexHighEffBJetTags+
                ak1CaloSimpleSecondaryVertexHighPurBJetTags+
                ak1CaloCombinedSecondaryVertexBJetTags+
                ak1CaloCombinedSecondaryVertexV2BJetTags
              ) *
	    ak1CaloPfImpactParameterTagInfos *
	    ak1CaloPfInclusiveSecondaryVertexFinderTagInfos *
	    ak1CaloPfDeepCSVTagInfos *
	    ak1CaloPfDeepCSVJetTags  
            )



ak1CaloJetBtaggingMu = cms.Sequence(ak1CaloSoftPFMuonsTagInfos * (ak1CaloSoftPFMuonBJetTags
                +
                ak1CaloSoftPFMuonByIP3dBJetTags
                +
                ak1CaloSoftPFMuonByPtBJetTags               
              )
            )

ak1CaloJetBtagging = cms.Sequence(ak1CaloJetBtaggingIP
            *ak1CaloJetBtaggingSV
#            *ak1CaloJetBtaggingMu
            )

ak1CalopatJetsWithBtagging = patJets.clone(jetSource = cms.InputTag("ak1CaloJets"),
        genJetMatch          = cms.InputTag("ak1Calomatch"),
        genPartonMatch       = cms.InputTag("ak1Caloparton"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak1Calocorr")),
        #JetPartonMapSource   = cms.InputTag("ak1CaloPatJetFlavourAssociationLegacy"),
        JetPartonMapSource   = cms.InputTag("ak1CaloPatJetFlavourAssociation"),
	JetFlavourInfoSource   = cms.InputTag("ak1CaloPatJetFlavourAssociation"),
        trackAssociationSource = cms.InputTag("ak1CaloJetTracksAssociatorAtVertex"),
	useLegacyJetMCFlavour = False,
        discriminatorSources = cms.VInputTag(cms.InputTag("ak1CaloSimpleSecondaryVertexHighEffBJetTags"),
            cms.InputTag("ak1CaloSimpleSecondaryVertexHighPurBJetTags"),
            cms.InputTag("ak1CaloCombinedSecondaryVertexBJetTags"),
            cms.InputTag("ak1CaloCombinedSecondaryVertexV2BJetTags"),
            cms.InputTag("ak1CaloJetBProbabilityBJetTags"),
            cms.InputTag("ak1CaloJetProbabilityBJetTags"),
            #cms.InputTag("ak1CaloSoftPFMuonByPtBJetTags"),
            #cms.InputTag("ak1CaloSoftPFMuonByIP3dBJetTags"),
            cms.InputTag("ak1CaloTrackCountingHighEffBJetTags"),
            cms.InputTag("ak1CaloTrackCountingHighPurBJetTags"),
            cms.InputTag("ak1CaloPfDeepCSVJetTags:probb")

            ),
        jetIDMap = cms.InputTag("ak1CaloJetID"),
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

ak1CaloNjettiness = Njettiness.clone(
		    src = cms.InputTag("ak1CaloJets"),
           	    R0  = cms.double( 0.1)
)
#ppDataDummy_ak1CalopatJetsWithBtagging.userData.userFloats.src += ['ak1CaloNjettiness:tau1','ak1CaloNjettiness:tau2','ak1CaloNjettiness:tau3']

ak1CaloJetAnalyzer = inclusiveJetAnalyzer.clone(jetTag = cms.InputTag("ak1CalopatJetsWithBtagging"),
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
                                                             bTagJetName = cms.untracked.string("ak1Calo"),
                                                             jetName = cms.untracked.string("ak1Calo"),
                                                             genPtMin = cms.untracked.double(5),
							     doTower = cms.untracked.bool(False),
							     doSubJets = cms.untracked.bool(False),
                                                             doGenSubJets = cms.untracked.bool(False),     
                                                             subjetGenTag = cms.untracked.InputTag("ak1GenJets"),
							     doExtendedFlavorTagging = cms.untracked.bool(True),
							     jetFlavourInfos = cms.InputTag("ak1CaloPatJetFlavourAssociation"),
							     subjetFlavourInfos = cms.InputTag("ak1CaloPatJetFlavourAssociation","SubJets"),
							     groomedJets = cms.InputTag("ak1CaloJets"),
							     isPythia6 = cms.untracked.bool(False),
                                                             doGenTaus = True
                                                            )

ak1CalopatJetsWithBtagging.getJetMCFlavour = False
ak1CaloJetAnalyzer.doExtendedFlavorTagging = False

ak1CaloJetAnalyzer.trackSelection = ak1CaloSecondaryVertexTagInfos.trackSelection
ak1CaloJetAnalyzer.trackPairV0Filter = ak1CaloSecondaryVertexTagInfos.vertexCuts.v0Filter

ak1CaloJetSequence_mc = cms.Sequence(
                                                  #ak1Caloclean
                                                  #*
                                                  ak1Calomatch
                                                  #*
                                                  #ak1CalomatchGroomed
                                                  *
                                                  ak1Caloparton
                                                  *
                                                  ak1Calocorr
                                                  *
                                                  #ak1CaloJetID
                                                  #*
                                                  #ak1CaloPatJetFlavourIdLegacy  # works for PbPb
                                                  #*
                                                  #DISABLE_PPCALO_ak1CaloPatJetFlavourId  # doesn't work for PbPb yet
                                                  #DISABLE_PPCALO_*
                                                  ak1CaloJetTracksAssociatorAtVertex
                                                  *
                                                  ak1CaloJetBtagging
                                                  *
                                                  #DISABLE_PPCALO_ak1CaloNjettiness
                                                  #DISABLE_PPCALO_*
                                                  ak1CalopatJetsWithBtagging
                                                  *
                                                  ak1CaloJetAnalyzer
                                                  )

ak1CaloJetSequence_data = cms.Sequence(ak1Calocorr
                                                    *
                                                    #ak1CaloJetID
                                                    #*
                                                    ak1CaloJetTracksAssociatorAtVertex
                                                    *
                                                    ak1CaloJetBtagging
                                                    *
                                                    #DISABLE_PPCALO_ak1CaloNjettiness
                                                    #DISABLE_PPCALO_*
                                                    ak1CalopatJetsWithBtagging
                                                    *
                                                    ak1CaloJetAnalyzer
                                                    )

ak1CaloJetSequence_jec = cms.Sequence(ak1CaloJetSequence_mc)
ak1CaloJetSequence_mb = cms.Sequence(ak1CaloJetSequence_mc)

ak1CaloJetSequence = cms.Sequence(ak1CaloJetSequence_mc)
