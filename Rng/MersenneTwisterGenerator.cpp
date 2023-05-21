#include "MersenneTwisterGenerator.h"

#include <stdexcept>
#include <random>

void MersenneTwisterGenerator::generateData(std::vector<uint8_t>& data, size_t size)
{
    if (!size)
        size = data.size();

    std::mt19937_64 gen64;
    gen64.seed(m_seed);

    uint64_t value;
    for (size_t i = 0; i < size / 8; ++i)
    {
        value = gen64();

        size_t index = 8 * i;
        data[index] = (value & 0xFF00000000000000) >> 56;
        data[index + 1] = (value & 0x00FF000000000000) >> 48;
        data[index + 2] = (value & 0x0000FF0000000000) >> 40;
        data[index + 3] = (value & 0x000000FF00000000) >> 32;
        data[index + 4] = (value & 0x00000000FF000000) >> 24;
        data[index + 5] = (value & 0x0000000000FF0000) >> 16;
        data[index + 6] = (value & 0x000000000000FF00) >> 8;
        data[index + 7] = value &  0x00000000000000FF;
    }
}

void MersenneTwisterGenerator::setSeed(const std::vector<uint8_t>& seed)
{
    if (seed.size() != 8)
        throw std::logic_error("Seed size is invalid");

    for (size_t i = 0; i < 8; ++i)
        m_seed = (m_seed << 8) & seed[i];
}
