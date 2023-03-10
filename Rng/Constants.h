#pragma once

constexpr size_t kLength = 10485760;
constexpr size_t kBatchLength = 2048;
constexpr size_t kResultCount = 200;

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
