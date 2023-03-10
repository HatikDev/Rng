#pragma once

#include "Constants.h"

#include <string>
#include <vector>

std::vector<uint8_t> getRandomBlock(SupportedGenerators generator, size_t size, uint64_t seed);

void generateData(std::string outputFile, SupportedGenerators generator, size_t size, uint64_t seed);

class Generator
{
public:
    Generator() {}
    virtual ~Generator() {}

    virtual void generateData(std::vector<uint8_t>& data, size_t size = 0) = 0;
    virtual void setSeed(const std::vector<uint8_t>& seed) = 0;
};
