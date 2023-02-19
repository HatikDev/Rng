#include <bitset>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>

#include "dll.h"
#include "cryptlib.h"
#include "sha.h"
#include "files.h"
#include "rng.h"
#include "osrng.h"

#include "Generator.h"
#include "Levenshtein.h"

//constexpr size_t kLength = 4194304;
constexpr size_t kLength = 10485760;
//constexpr size_t kBatchLength = 4096;
constexpr size_t kBatchLength = 16384;

auto comparator = [](const std::string& s1, const std::string& s2) { return s1.size() == s2.size() ? (strcmp(s1.c_str(), s2.c_str()) < 0 ? true : false ) : s1.size() < s2.size() ; };
using CompType = decltype(comparator);

void generate(std::string outputFile)
{
    srand(time(NULL));

    std::ofstream file(outputFile, std::ios::out | std::ios::binary);

    for (size_t i = 0; i < kLength; ++i)
        file << static_cast<char>(rand() % 0x100);

    file.close();
}

void generateFromGenerator(std::string outputFile, SupportedGenerators generator, size_t size) // add seed
{
    std::ofstream file(outputFile, std::ios::out | std::ios::binary);

    auto data = getRandomBlockFromGenerator(generator, size);
    //for (size_t i = 0; i < kLength; ++i)
    //    file << static_cast<char>(rand() % 0x100);

    for (auto byte : data)
        file << static_cast<char>(byte);

    file.close();
}

void readBatch(std::string inputFile, size_t position, std::vector<uint8_t>& batch)
{
    batch.resize(kBatchLength);

    std::ifstream file(inputFile, std::ios::binary);
    file.seekg(position);

    file.read((char*)&batch[0], kBatchLength);
    file.close();
}

void analysisTest(std::vector<uint8_t>& batch, std::map<std::string, size_t, CompType>& result, const std::string& pattern, std::string& str)
{
    for (size_t i = 0; i < batch.size(); ++i)
        str += std::bitset<8>(batch[i]).to_string();

    size_t position = -1 * pattern.length();
    size_t newPosition;
    std::string key;

    for (size_t i = 0; i < batch.size(); ++i)
    {
        newPosition = str.find(pattern, position + pattern.length());
        if (newPosition == std::string::npos)
        {
            size_t count = str.length() - position - pattern.length();
            str = str.substr(position + pattern.length(), count);

            return;
        }
        else
        {
            size_t count = newPosition - position - pattern.length();
            key = str.substr(position + pattern.length(), newPosition - position - pattern.length());
        }

        if (result.find(key) == result.end())
            result[key] = 1;
        else
            result[key] += 1;
        position = newPosition;
    }
}

void writeResult(std::string outputFile, std::map<std::string, size_t, CompType> result)
{
    std::ofstream file(outputFile, std::ios::app);

    //for (auto& [key, value] : result)
    //    file << "'" << key << "'" << "," << value << std::endl;

    auto begin = result.begin();
    auto end = result.begin();
    std::advance(end, 200); // just first 200 results

    for (auto iter = begin; iter != end; ++iter)
        file << "'" << (*iter).first << "'" << "," << (*iter).second << std::endl;

    file.close();
}

template <size_t length>
void launchAnalysisTestAllSets()
{
    size_t count = pow(2, length);

    std::vector<uint8_t> batch;
    for (size_t j = 0; j < count; ++j)
    {
        std::map<std::string, size_t, CompType> result(comparator);

        const std::string pattern = std::bitset<length>(j).to_string();

        std::string str;
        for (size_t i = 0; i < kLength / kBatchLength; ++i)
        {
            readBatch("10mb/input.bin", i * kBatchLength, batch);
            analysisTest(batch, result, pattern, str);
        }
        writeResult("10mb/len4_cut/output_" + pattern + ".csv", result);
    }
}

template <size_t length>
void launchAnalysisTestAllSetsAuto(std::string inputFileName, std::string outputFileName)
{
    using result_type = std::map<std::string, size_t, CompType>;
    size_t count = pow(2, length);

    std::vector<uint8_t> batch;
    std::vector<result_type> allResults;
    for (size_t j = 0; j < count; ++j)
    {
        result_type result(comparator);

        const std::string pattern = std::bitset<length>(j).to_string();

        std::string str;
        for (size_t i = 0; i < kLength / kBatchLength; ++i)
        {
            readBatch(inputFileName, i * kBatchLength, batch);
            analysisTest(batch, result, pattern, str);
        }

        auto begin = result.begin();
        auto end = result.begin();
        std::advance(end, result.size() > 200 ? 200 : result.size());
        allResults.push_back(result_type(begin, end, comparator));
    }

    std::vector<result_type::iterator> iterators;
    std::vector<result_type::iterator> endIterators;
    iterators.reserve(allResults.size());
    for (auto& res : allResults)
    {
        iterators.emplace_back(res.begin());
        endIterators.emplace_back(res.end());
    }

    std::ofstream file(outputFileName, std::ios::app);
    for (size_t i = 0; i < 200; ++i) // what with 200?
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

void getAllLevenshteinTestsResult()
{
    std::vector<SupportedGenerators> generators = { SupportedGenerators::SystemGenerator,
                                                    SupportedGenerators::X917RNG,
                                                    //SupportedGenerators::MidSquare,
                                                    SupportedGenerators::AESRNG,
                                                    /*SupportedGenerators::MersenneTwister,
                                                    SupportedGenerators::Linear,
                                                    SupportedGenerators::Knuthan,
                                                    SupportedGenerators::LFSRSimple*/ };

    for (auto generator : generators)
    {
        for (size_t i = 0; i < 25; ++i)
        {
            auto seq1 = getRandomBlockFromGenerator(generator, 2048);
            auto seq2 = getRandomBlockFromGenerator(generator, 2048);

            std::cout << "generator " << static_cast<int>(generator) << " test 1: " << levenshteinTest1(seq1, seq2) << std::endl;
            std::cout << "generator " << static_cast<int>(generator) << " test 2: " << levenshteinTest2(seq1, seq2) << std::endl;
        }
    }

    return;
}

int main()
{
    //generate("output.bin");
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

    //const std::string src = "котик";
    //const std::string dst = "скотина";
    //const std::string::size_type distance = levenshteinDistance(src, dst);

    //srand(time(NULL));
    //auto seq1 = getRandomBlockFromGenerator(SupportedGenerators::AESRNG, 1024);
    //auto seq2 = getRandomBlockFromGenerator(SupportedGenerators::AESRNG, 1024);
    //levenshteinTest2(seq1, seq2);

    for (size_t i = 0; i < 10; ++i)
        getAllLevenshteinTestsResult();

    //generate("10mb/output.bin");

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
