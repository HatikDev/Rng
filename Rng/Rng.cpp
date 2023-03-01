#include <iostream>
#include <vector>

#include "Constants.h"
#include "Generator.h"
#include "Levenshtein.h"

int main()
{
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

    for (size_t i = 0; i < 10; ++i)
        getAllLevenshteinTestsResult();

    /*for (size_t j = 7; j <= 10; ++j)
    {
        std::string folderNumber = std::to_string(j);
        //std::vector<std::string> inputFileNames = { /*"1/inputSystem.bin", folderNumber + "/inputLFSRSimple.bin", folderNumber + "/inputKnuthan.bin"/*, folderNumber + "/inputAESRNG.bin", folderNumber + "/inputMersenne.bin"*/// };
        //std::vector<std::string> outpuFileNames = { /*"1/outputSystem.csv",*/ folderNumber + "/outputLFSRSimple.csv", folderNumber + "/outputKnuthan.csv"/*, folderNumber + "/outputAESRNG.csv", folderNumber + "/outputMersenne.csv"*/ };
        //std::vector<SupportedGenerators> generators = { /*SupportedGenerators::SystemGenerator,*/ SupportedGenerators::Linear,
        //                                                /*SupportedGenerators::X917RNG,*/ /*SupportedGenerators::AESRNG,*/ /*SupportedGenerators::MersenneTwister*/ };
        //std::vector<SupportedGenerators> generators = { SupportedGenerators::Knuthan, SupportedGenerators::LFSRSimple };
        //std::vector<std::string> inputFileNames = { "inputKnuthan.bin", "inputLFSRSimple.bin" };
        //for (size_t i = 0; i < inputFileNames.size(); ++i)
        //{
        //    generateFromGenerator(inputFileNames[i], generators[i], kLength);
        //}

        /*for (size_t i = 0; i < inputFileNames.size(); ++i)
        {
            launchAnalysisTestAllSetsAuto<3>(inputFileNames[i], outpuFileNames[i]);
        }
    }*/

    //launchAnalysisTestAllSetsAuto<3>("1/inputLinear.bin", "1/outputLinearTest.csv");

    //auto result = getRandomBlockFromGenerator(SupportedGenerators::LFSRSimple, 1024);

    return 0;
}
