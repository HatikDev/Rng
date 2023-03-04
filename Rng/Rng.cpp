#include <iostream>
#include <string>
#include <vector>

#include "Analysis.h"
#include "Constants.h"
#include "Generator.h"
#include "Levenshtein.h"

void generateDataSequencesGlobal1()
{
    std::vector<SupportedGenerators> generators = { SupportedGenerators::Linear,
                                                    //SupportedGenerators::X917RNG,
                                                    //SupportedGenerators::AESRNG,
                                                    SupportedGenerators::MersenneTwister,
                                                    SupportedGenerators::Knuthan,
                                                    SupportedGenerators::LFSRSimple };
    std::vector<std::string> fileNames;
    std::vector<std::string> inputGeneratorNames = { "inLinear.bin", "inMersenneTwister.bin", "inKnuthan.bin", "inLFSRSimple.bin", };
    constexpr size_t kCount = 20;

    for (size_t i = 1; i <= kCount; ++i)
    {
        auto tempCopy = inputGeneratorNames;
        for (auto& copy : tempCopy)
            copy = std::to_string(i) + "/" + copy;
        generateDataSequences(tempCopy, generators, kLength, rand());
    }
}

void generateDataSequencesGlobal2()
{
    std::vector<SupportedGenerators> generators = { SupportedGenerators::X917RNG,
                                                    SupportedGenerators::AESRNG,
    };
    std::vector<std::string> fileNames;
    std::vector<std::string> inputGeneratorNames = { "X917RNG.bin", "AESRNG.bin", };
    constexpr size_t kCount = 20;

    std::vector<uint8_t> seed(32, 0);
    for (size_t i = 1; i <= kCount; ++i)
    {
        auto tempCopy = inputGeneratorNames;
        for (auto& copy : tempCopy)
            copy = std::to_string(i) + "/" + copy;

        
        generateDataSequences(tempCopy, generators, kLength);
    }
}

int main()
{
    //srand(time(NULL));
    //std::vector<uint8_t> batch;
    //std::map<std::string, size_t, CompType> result(comparator);

    //std::string str;
    //for (size_t i = 0; i < kLength / kBatchLength; ++i)
    //{
    //    readBatch("input.bin", i * kBatchLength, batch);
    //    analysisTest(batch, result, str);
    //}
    //writeResult("output.csv", result);

    //getRandomBlockFromGenerator(SupportedGenerators::AESRNG, 1024);

    //launchAnalysisTestAllSets<4>();

    //srand(time(NULL));
    //auto seq1 = getRandomBlockFromGenerator(SupportedGenerators::AESRNG, 1024);
    //auto seq2 = getRandomBlockFromGenerator(SupportedGenerators::AESRNG, 1024);
    //levenshteinTest2(seq1, seq2);

    //for (size_t i = 0; i < 10; ++i)
    //    getAllLevenshteinTestsResult();

    //for (size_t j = 1; j <= 20; ++j)
    //{
    //    std::string folderNumber = std::to_string(j);
    //    std::vector<std::string> inputFileNames = { /*"1/inputSystem.bin", folderNumber + "/inputLFSRSimple.bin", folderNumber + "/inputKnuthan.bin"/*, folderNumber + "/inputAESRNG.bin", folderNumber + "/inputMersenne.bin"*/// };
    //    std::vector<std::string> outputFileNames = { /*"1/outputSystem.csv",*/ folderNumber + "/outputLFSRSimple.csv", folderNumber + "/outputKnuthan.csv"/*, folderNumber + "/outputAESRNG.csv", folderNumber + "/outputMersenne.csv"*/ };
    //    std::vector<SupportedGenerators> generators = { /*SupportedGenerators::SystemGenerator,*/ SupportedGenerators::Linear,
    //                                                    /*SupportedGenerators::X917RNG,*/ /*SupportedGenerators::AESRNG,*/ /*SupportedGenerators::MersenneTwister*/ };
    //    std::vector<SupportedGenerators> generators = { SupportedGenerators::Knuthan, SupportedGenerators::LFSRSimple };
    //    std::vector<std::string> inputFileNames = { "inputKnuthan.bin", "inputLFSRSimple.bin" };
    //    for (size_t i = 0; i < inputFileNames.size(); ++i)
    //    {
    //        generateData(inputFileNames[i], generators[i], kLength);
    //    }

    //    /*for (size_t i = 0; i < inputFileNames.size(); ++i)
    //    {
    //        launchAnalysisTestAllSetsAuto<3>(inputFileNames[i], outpuFileNames[i]);
    //    }*/
    //}

    //launchAnalysisTestAllSetsAuto<3>("1/inputLinear.bin", "1/outputLinearTest.csv");

    //auto result = getRandomBlockFromGenerator(SupportedGenerators::LFSRSimple, 1024);

    //generateDataSequencesGlobal1();
    generateDataSequencesGlobal2();

    //std::vector<std::string> inputFileNames = { /*"inLinear.bin", */"inMersenneTwister.bin", "inKnuthan.bin", "inLFSRSimple.bin", };
    //std::vector<std::string> outputFileNames = { /*"outLinear.csv", */"outMersenneTwister.csv", "outKnuthan.csv", "outLFSRSimple.csv", };
    //for (size_t i = 1; i <= 1; ++i)
    //{
    //    for (size_t j = 0; j < inputFileNames.size(); ++j)
    //    {
    //        auto inFilename = std::to_string(i) + "/" + inputFileNames[j];
    //        auto outFilename = std::to_string(i) + "/" + outputFileNames[j];
    //        launchAnalysisTestAllSetsAuto<3>(inFilename, outFilename);
    //    }
    //}

    return 0;
}
