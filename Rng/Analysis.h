#pragma once

#include <string>

#include "Analysis.h"
#include "Constants.h"
#include "IOSystem.h"

#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

namespace
{
auto comparator = [](const std::string& s1, const std::string& s2) { return s1.size() == s2.size() ? (strcmp(s1.c_str(), s2.c_str()) < 0 ? true : false ) : s1.size() < s2.size() ; };
using CompType = decltype(comparator);

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
} // namespace

template <size_t length>
void launchAnalysisTestAllSetsAuto(const std::string& inputFileName, const std::string& outputFileName)
{
    using result_type = std::map<std::string, size_t, CompType>;
    size_t count = static_cast<size_t>(pow(2, length));

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
