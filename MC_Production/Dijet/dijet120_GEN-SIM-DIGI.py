
# Auto generated configuration file
# using: 
# Revision: 1.341 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/Pyquen_GammaJet_pt30_cfi.py -n 10 -s GEN:hiSignal,SIM,DIGI,L1,DIGI2RAW,HLT:HIon --conditions auto:starthi --scenario HeavyIons --geometry Extended --himix --datatier GEN-SIM-RAWDEBUG --eventcontent=RAWDEBUG --filein=input.root --processName HISIGNAL --no_exec

import FWCore.ParameterSet.VarParsing as VarParsing

ivars = VarParsing.VarParsing('python')

ivars.register ('randomNumber',
                1,
                ivars.multiplicity.singleton,
                ivars.varType.int,
                "Random Seed")

ivars.randomNumber = 1
ivars.inputFiles = "file:preMix_440_C_numEvent1.root"
ivars.outputFile = './mixed_440_B_01.root'

ivars.parseArguments()

import FWCore.ParameterSet.Config as cms

process = cms.Process('HISIGNAL')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.HiEventMixing_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic7TeV2011Collision_cfi')
process.load('SimGeneral.MixingModule.himixGEN_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.Sim_cff')
process.load('SimGeneral.MixingModule.himixSIMExtended_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('SimGeneral.MixingModule.himixDIGI_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
#process.load('HLTrigger.Configuration.HLT_HIon_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.RandomNumberGeneratorService.hiSignal.initialSeed = ivars.randomNumber
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(40)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
    ivars.inputFiles
    ),
                            inputCommands = cms.untracked.vstring('drop *', 
                                                                  'keep *_generator_*_*', 
                                                                  'keep *_g4SimHits_*_*'),
                            dropDescendantsOfDroppedBranches = cms.untracked.bool(False)
                            )

process.options = cms.untracked.PSet(

    )

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.5 $'),
    annotation = cms.untracked.string('PYQUEN quenched dijets (pt-hat > 30 GeV) at sqrt(s) = 2.76TeV'),
    name = cms.untracked.string('$Source: /cvs/CMSSW/UserCode/yinglu/MC_Production/Dijet/dijet120_GEN-SIM-DIGI.py,v $')
    )

# Output definition

process.RAWDEBUGoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWDEBUGEventContent.outputCommands,
    fileName = cms.untracked.string(ivars.outputFile),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RAWDEBUG')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'STARTHI44_V7::All'

# hiSignal??
process.load('Configuration.GenProduction.Pyquen_DiJet_Pt120_TuneZ2_Unquenched_2760GeV_cfi')

process.ProductionFilterSequence = cms.Sequence(process.hiSignal)

# Path and EndPath definitions
process.generation_step = cms.Path(process.hiSignal*process.pgen_himix)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWDEBUGoutput_step = cms.EndPath(process.RAWDEBUGoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
#process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.RAWDEBUGoutput_step])

from Configuration.GenProduction.customiseCaloDigisNZS import *
customiseHcalNZS(process)






