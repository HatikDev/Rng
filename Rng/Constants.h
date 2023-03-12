#pragma once

#include <map> // TODO: remove this
#include <string>

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

auto comparator = [](const std::string& s1, const std::string& s2)
{
    return s1.size() == s2.size() ?
            (strcmp(s1.c_str(), s2.c_str()) < 0 ? true : false )
            : s1.size() < s2.size();
};
using CompType = decltype(comparator);
using result_type = std::map<std::string, size_t, CompType>; // TODO: move into types
