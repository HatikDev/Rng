#pragma once

#include "Generator.h"

class SystemGenerator : public Generator
{
public:
    SystemGenerator(uint32_t seed) : Generator(), m_seed{ seed } {}
    virtual ~SystemGenerator() {}

    virtual void generateData(std::vector<uint8_t>& data, size_t size = 0) override;
    virtual void setSeed(const std::vector<uint8_t>& seed) override;

private:
    uint32_t m_seed;
};
