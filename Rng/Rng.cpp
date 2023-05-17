#include <iostream>
#include <vector>

#include "Analysis.h"
#include "Constants.h"
#include "Generator.h"
#include "Levenshtein.h"

template <size_t length>
void launchAnalysisTestAllSetsAuto1(const std::string& inputFileName, const std::string& outputFileName)
{
    using result_type = std::map<std::string, size_t, CompType>;
    size_t count = pow(2, length);

    std::vector<uint8_t> batch;
    std::vector<result_type> allResults;
    for (size_t j = 0; j < count; ++j)
    {
        result_type result(comparator);

        const std::string pattern = std::bitset<3/*length*/>(j).to_string();

        std::string str;
        for (size_t i = 0; i < kLength / kBatchLength; ++i)
        {
            readBatch(inputFileName, i * kBatchLength, batch);
            analysisTest(batch, result, pattern, str);
        }

        auto begin = result.begin();
        auto end = result.begin();
        std::advance(end, result.size() > kResultCount ? kResultCount : result.size());
        allResults.push_back(result_type(begin, end, comparator));
    }

    std::vector<result_type::iterator> iterators;
    std::vector<result_type::iterator> endIterators;
    iterators.reserve(allResults.size());
    endIterators.reserve(allResults.size());
    for (auto& res : allResults)
    {
        iterators.emplace_back(res.begin());
        endIterators.emplace_back(res.end());
    }

    std::ofstream file(outputFileName, std::ios::app);
    for (size_t i = 0; i < kResultCount; ++i)
    {
        for (size_t i = 0; i < iterators.size(); ++i)
        {
            auto& iter = iterators[i];
            if (iter == endIterators[i])
                continue;

            file << "'" << (*iter).first << "'" << "," << (*iter).second << ",";
            ++iter;
        }

        file << std::endl;
    }
    file.close();
}

uint64_t sysrand()
{
    return rand();
}

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

    //for (size_t i = 0; i < 10; ++i)
        getAllLevenshteinTestsResult("levenshtein.txt");

    //srand(time(NULL));
    //for (size_t j = 41; j <= 60; ++j)
    //{
    //    std::string folderNumber = std::to_string(j);
    //    //std::vector<std::string> inputFileNames = { };/*"1/inputSystem.bin", folderNumber + "/inputLFSRSimple.bin", folderNumber + "/inputKnuthan.bin"/*, folderNumber + "/inputAESRNG.bin", folderNumber + "/inputMersenne.bin"*/// };
    //    std::vector<std::string> outputFileNames = { folderNumber + "/outMersenne.csv", folderNumber + "/outKnuthan.csv", folderNumber + "/LFSR.csv" };
    //    //std::vector<SupportedGenerators> generators = { /*SupportedGenerators::SystemGenerator,*/ SupportedGenerators::Linear,
    //                                                    /*SupportedGenerators::X917RNG,*/ /*SupportedGenerators::AESRNG,*/ /*SupportedGenerators::MersenneTwister };*/
    //    //std::vector<SupportedGenerators> generators = { SupportedGenerators::MersenneTwister, 
    //    //                                                SupportedGenerators::Knuthan,
    //    //                                                SupportedGenerators::LFSRSimple,
    //    //                                                /*SupportedGenerators::X917RNG*/ };
    //    ////std::vector<std::string> inputFileNames = { "inputMersenneTwister.bin", "inputKnuthan.bin", "inputLFSRSimple.bin" };
    //    std::vector<std::string> inputFileNames = { folderNumber + "/inMersenne.bin", folderNumber + "/inKnuthan.bin", folderNumber + "/inLFSR.bin",
    //                                                /*folderNumber + "/inX917.bin"*/ };
    //    //for (size_t i = 0; i < inputFileNames.size(); ++i)
    //    //{
    //    //    uint64_t seed;
    //    //    seed = (sysrand() << 56) | (sysrand() << 48) | (sysrand() << 40) | (sysrand() << 32) |
    //    //            (sysrand() << 24) | (sysrand() << 16) | (sysrand() << 8) | sysrand();
    //    //    generateData(inputFileNames[i], generators[i], kLength, seed);
    //    //}
    ////}

    //    for (size_t i = 0; i < inputFileNames.size(); ++i)
    //    {
    //        launchAnalysisTestAllSetsAuto<3>(inputFileNames[i], outputFileNames[i]);
    //    }
    //}

    //launchAnalysisTestAllSetsAuto<3>("1/inputLinear.bin", "1/outputLinearTest.csv");

    //auto result = getRandomBlockFromGenerator(SupportedGenerators::LFSRSimple, 1024);

    return 0;
}
