#include "TestComand.h"

#include "Constants.h"
#include "FileIOSystem.h"

#include <bitset>
#include <fstream>
#include <map>
#include <memory>
#include <vector>

namespace
{
auto comparator = [](const std::string& s1, const std::string& s2)
{
    return s1.size() == s2.size() ?
            (strcmp(s1.c_str(), s2.c_str()) < 0 ? true : false )
            : s1.size() < s2.size();
};
using CompType = decltype(comparator);

void analysisTest(std::vector<uint8_t>& batch, std::map<std::string, size_t, CompType>& result, const std::string& pattern, std::string& str)
{
    str.reserve(str.length() + CHAR_BIT * batch.size());
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

void launchAnalysisTest(const std::string& inputFileName, const std::string& outputFileName)
{
    using result_type = std::map<std::string, size_t, CompType>;
    size_t count = 8;

    std::vector<uint8_t> batch;
    std::vector<result_type> allResults;

    auto ioSystem = std::make_unique<FileIOSystem>(inputFileName, outputFileName, "seed_" + outputFileName);
    for (size_t j = 0; j < count; ++j)
    {
        result_type result(comparator);

        const std::string pattern = std::bitset<3>(j).to_string();

        std::string str;
        for (size_t i = 0; i < kLength / kBatchLength; ++i)
        {
            ioSystem->readBinBatch(batch, i * kBatchLength, kBatchLength);
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
} // namespace

void TestComand::execute()
{
    for (size_t i = 0; i < m_inputFiles.size(); ++i)
        launchAnalysisTest(m_inputFiles[i], m_outputFiles[i]);
}

void TestComand::parseParams()
{
    for (size_t i = 0; i < m_params.size(); ++i)
    {
        if (m_params[i] == "-i")
        {
            ++i;
            while (m_params[i][0] != '-')
            {
                m_inputFiles.push_back(m_params[i++]);
            }
        }
        if (m_params[i] == "-o")
        {
            ++i;
            while (m_params[i][0] != '-')
            {
                m_outputFiles.push_back(m_params[i++]);
            }
        }
        if (m_params[i] == "-c")
        {
            m_count = std::atoi(m_params[i + 1].c_str());
        }
        if (m_params[i] == "-s")
        {
            m_dataSize = std::atoi(m_params[i + 1].c_str());
        }
    }
}
