#pragma once

#include <string>
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

std::vector<uint8_t> getRandomBlock(SupportedGenerators generator, size_t size, uint64_t seed);

void generateData(std::string outputFile, SupportedGenerators generator, size_t size, uint64_t seed);
