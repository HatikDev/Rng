#include "AnalysisTest.h"

#include <bitset>
#include <iostream>
#include <string>

void AnalysisTest::executeTest(const std::vector<uint8_t>& inputBuffer, result_type& outputBuffer)
{
    size_t count = pow(2, m_length);

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