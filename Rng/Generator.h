#pragma once

#include <vector>

enum class SupportedGenerators // we also need rsa rng
{
    SystemGenerator,
    X917RNG,
    MidSquare,
    AESRNG
};

std::vector<uint8_t> getRandomBlockFromGenerator(SupportedGenerators generator, size_t size);
