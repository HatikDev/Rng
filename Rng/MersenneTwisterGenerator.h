#pragma once

#include "Generator.h"

class MersenneTwisterGenerator : public Generator
{
public:
    MersenneTwisterGenerator(uint64_t seed) : Generator(), m_seed{ seed } {}
    virtual ~MersenneTwisterGenerator() {}

    virtual void generateData(std::vector<uint8_t>& data, size_t size = 0) override;
    virtual void setSeed(const std::vector<uint8_t>& seed) override;

private:
    uint64_t m_seed;
};
