#include <iostream>
#include <vector>

#include "Analysis.h"
#include "Constants.h"
#include "Generator.h"
#include "Levenshtein.h"

#include "Comand.h"
#include "GenerateComand.h"
#include "TestComand.h"

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

std::vector<std::string> getParams(size_t argc, char* argv[], size_t startIndex)
{
    if (argc - startIndex <= 0)
        throw std::logic_error("Invalid comand params");

    std::vector<std::string> params;
    params.reserve(argc - startIndex);
    for (size_t i = startIndex; i < argc; ++i)
        params.emplace_back(argv[i]);

    return params;
}

void launchComand(int argc, char* argv[])
{
    std::unique_ptr<Comand> comand;
    if (std::string(argv[1]) == "generate")
        comand = std::make_unique<GenerateComand>(getParams(argc, argv, 2));
    else if (std::string(argv[1]) == "test")
        comand = std::make_unique<TestComand>(getParams(argc, argv, 2));
    else
        throw std::logic_error("Invalid comand");

    comand->execute();
}

int main(int argc, char* argv[])
{
    launchComand(argc, argv);

    return 0;
}
