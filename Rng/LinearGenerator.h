#pragma once

#include "Generator.h"

class LinearGenerator : public Generator
{
public:
    LinearGenerator() : Generator() {}
    virtual ~LinearGenerator() {}

    virtual void generateData(std::vector<uint8_t>& data, size_t size = 0) override;
    virtual void setSeed(const std::vector<uint8_t>& seed) override;

private:
    uint64_t m_seed;
};
