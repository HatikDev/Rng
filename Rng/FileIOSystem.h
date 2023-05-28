#pragma once

#include "IOSystem.h"

class FileIOSystem : public IOSystem
{
public:
    FileIOSystem(const std::string& inputFile, const std::string& outputFile, const std::string& seedFile)
        : IOSystem(), m_inputFile{ inputFile }, m_outputFile{ outputFile }, m_seedFile{ seedFile }
    {}
    virtual ~FileIOSystem() {}

    virtual void readBinBatch(std::vector<uint8_t>& data, size_t offset, size_t size = 0) override;
    virtual void writeBinBatch(const std::vector<uint8_t>& data, bool rewrite = false) override;

    virtual void logSeed(const std::vector<uint8_t>& seed) override;
    virtual void writeResult(std::map<std::string, size_t>& result, bool rewrite = false) override;

    void setInputFile(const std::string& filename);
    void setOutputFile(const std::string& filename);

    std::string getInputFile() const;
    std::string getOutputFile() const;

private:
    std::string m_inputFile;
    std::string m_outputFile;
    std::string m_seedFile;
};