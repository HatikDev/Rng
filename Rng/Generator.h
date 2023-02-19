#pragma once

#include <vector>

enum class SupportedGenerators // we also need rsa rng
{
    SystemGenerator,
    Linear,
    X917RNG,
    MidSquare,
    AESRNG,
    MersenneTwister,
    Knuthan,
    LFSRSimple,
};

std::vector<uint8_t> getRandomBlockFromGenerator(SupportedGenerators generator, size_t size, uint64_t seed);
