#include "FileIOSystem.h"

#include <fstream>

void FileIOSystem::readBinBatch(std::vector<uint8_t>& data, size_t offset, size_t size)
{

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

}

void FileIOSystem::writeResult(std::map<std::string, size_t>& result, bool rewrite)
{

}
