#pragma once

#include <map>
#include <string>
#include <vector>

void readBatch(std::string inputFile, size_t position, std::vector<uint8_t>& batch);

template <typename Result>
void writeResult(std::string outputFile, const Result& result);

class IOSystem
{
public:
    IOSystem() {}
    virtual ~IOSystem() {}

    virtual void readBinBatch(std::vector<uint8_t>& data, size_t offset, size_t size = 0) = 0;
    virtual void writeBinBatch(const std::vector<uint8_t>& data, bool rewrite = false) = 0;

    virtual void logSeed(const std::vector<uint8_t>& seed) = 0;
    virtual void writeResult(std::map<std::string, size_t>& result, bool rewrite = false) = 0; // TODO: improve architechture
};
