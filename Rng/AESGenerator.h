#pragma once

#include "Generator.h"

class AESGenerator : public Generator
{
public:
    AESGenerator() : Generator() {}
    virtual ~AESGenerator() {}

    virtual void generateData(std::vector<uint8_t>& data, size_t size = 0) override;
    virtual void setSeed(const std::vector<uint8_t>& seed) override;

private:
    std::vector<uint8_t> m_seed;
};
