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

    //const std::string pattern = "0101";
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

//void cryptoPPTest()
//{
//    using namespace CryptoPP;
//
//    const unsigned int BLOCKSIZE = 1024;
//    SecByteBlock scratch(BLOCKSIZE);
//
//    CryptoPP::AutoSeededX917RNG<CryptoPP::DES_EDE3> rng(false, false);
//    SecByteBlock seed(32);
//
//    OS_GenerateRandomBlock(false, seed, seed.size()); // It's entropy
//    rng.IncorporateEntropy(seed, seed.size());
//
//    rng.GenerateBlock(scratch, scratch.size());
//    scratch.BytePtr();
//}

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

void getAllLevenshteinTestsResult()
{
    std::vector<SupportedGenerators> generators = { SupportedGenerators::SystemGenerator,
                                                    SupportedGenerators::X917RNG,
                                                    //SupportedGenerators::MidSquare,
                                                    SupportedGenerators::AESRNG };

    for (auto generator : generators)
    {
        auto seq1 = getRandomBlockFromGenerator(generator, 2048);
        auto seq2 = getRandomBlockFromGenerator(generator, 2048);

        std::cout << "generator " << static_cast<int>(generator) << " test 1: " << levenshteinTest1(seq1, seq2) << std::endl;
        std::cout << "generator " << static_cast<int>(generator) << " test 2: " << levenshteinTest2(seq1, seq2) << std::endl;
    }
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

    return 0;
}
