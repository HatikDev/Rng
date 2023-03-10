#pragma once

#include "Generator.h"

class X917Generator : public Generator
{
public:
    X917Generator() : Generator() {}
    virtual ~X917Generator() {}

    virtual void generateData(std::vector<uint8_t>& data, size_t size = 0) override;
    virtual void setSeed(const std::vector<uint8_t>& seed) override;
};
