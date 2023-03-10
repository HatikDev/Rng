#pragma once

#include "Generator.h"

class KnuthanGenerator : public Generator
{
public:
    KnuthanGenerator(uint64_t seed = 12345678901234567890) : Generator(), m_seed{ seed } {} // TODO: remove default value
    virtual ~KnuthanGenerator() {}

    virtual void generateData(std::vector<uint8_t>& data, size_t size = 0) override;
    virtual void setSeed(const std::vector<uint8_t>& seed) override;

private:
    uint64_t m_seed;
};
