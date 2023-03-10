#pragma once

#include "IOSystem.h"
#include "FileIOSystem.h"

class FileIOSystem : public IOSystem
{
public:
    FileIOSystem(const std::string& outputFile)
        : IOSystem(), m_outputFile{ outputFile }
    {}
    virtual ~FileIOSystem() {}

    virtual void readBinBatch(std::vector<uint8_t>& data, size_t offset, size_t size = 0) override;
    virtual void writeBinBatch(const std::vector<uint8_t>& data, bool rewrite = false) override;

    virtual void logSeed(const std::vector<uint8_t>& seed) override;
    virtual void writeResult(std::map<std::string, size_t>& result, bool rewrite = false) override;

private:
    std::string m_outputFile;
};