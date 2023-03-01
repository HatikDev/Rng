#include "Constants.h"
#include "IOSystem.h"

#include <fstream>

void readBatch(std::string inputFile, size_t position, std::vector<uint8_t>& batch)
{
    batch.resize(kBatchLength);

    std::ifstream file(inputFile, std::ios::binary);
    file.seekg(position);

    file.read((char*)&batch[0], kBatchLength);
    file.close();
}

template <typename Result>
void writeResult(std::string outputFile, const Result& result)
{
    std::ofstream file(outputFile, std::ios::app);

    auto begin = result.begin();
    auto end = result.begin();
    std::advance(end, kResultCount);

    for (auto iter = begin; iter != end; ++iter)
        file << "'" << (*iter).first << "'" << "," << (*iter).second << std::endl;

    file.close();
}