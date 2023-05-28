#include "Constants.h"
#include "FileIOSystem.h"

#include <fstream>

void FileIOSystem::readBinBatch(std::vector<uint8_t>& data, size_t offset, size_t size)
{
    data.resize(kBatchLength);

    std::ifstream file(m_inputFile, std::ios::binary);
    file.seekg(offset);

    file.read((char*)&data[0], kBatchLength);
    file.close();
}

void FileIOSystem::writeBinBatch(const std::vector<uint8_t>& data, bool rewrite)
{
    std::ofstream file(m_outputFile, std::ios::out | std::ios::binary);

    for (auto byte : data)
        file << static_cast<char>(byte);

    file.close();
}

void FileIOSystem::logSeed(const std::vector<uint8_t>& seed)
{
    std::ofstream file(m_seedFile, std::ios::out | std::ios::binary);

    for (auto byte : seed)
        file << static_cast<char>(byte);

    file.close();
}

void FileIOSystem::writeResult(std::map<std::string, size_t>& result, bool rewrite)
{
    std::ofstream file(m_outputFile, std::ios::app);

    auto begin = result.begin();
    auto end = result.begin();
    std::advance(end, kResultCount);

    for (auto iter = begin; iter != end; ++iter)
        file << "'" << (*iter).first << "'" << "," << (*iter).second << std::endl;

    file.close();
}

void FileIOSystem::setInputFile(const std::string& filename)
{
    m_inputFile = filename;
}

void FileIOSystem::setOutputFile(const std::string& filename)
{
    m_outputFile = filename;
}

std::string FileIOSystem::getInputFile() const
{
    return m_inputFile;
}

std::string FileIOSystem::getOutputFile() const
{
    return m_outputFile;
}
