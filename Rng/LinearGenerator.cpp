#include "LinearGenerator.h"

#include <stdexcept>

void LinearGenerator::generateData(std::vector<uint8_t>& data, size_t size)
{
    const uint64_t a = 6364136223846793005;
    const uint64_t b = 1442695040888963407;
    const uint64_t m = 0x8000000000000000;

    for (size_t i = 0; i < size / 8; ++i)
    {
        m_seed = (a * m_seed + b) % m;

        data.emplace_back((m_seed & 0xFF00000000000000) >> 52);
        data.emplace_back((m_seed & 0x00FF000000000000) >> 48);
        data.emplace_back((m_seed & 0x0000FF0000000000) >> 40);
        data.emplace_back((m_seed & 0x000000FF00000000) >> 32);
        data.emplace_back((m_seed & 0x00000000FF000000) >> 24);
        data.emplace_back((m_seed & 0x0000000000FF0000) >> 16);
        data.emplace_back((m_seed & 0x000000000000FF00) >> 8);
        data.emplace_back(m_seed &  0x00000000000000FF);
    }
}

void LinearGenerator::setSeed(const std::vector<uint8_t>& seed)
{
    if (seed.size() != 8)
        throw std::logic_error("Seed size is invalid");

    for (size_t i = 0; i < 8; ++i)
        m_seed = (m_seed << 8) & seed[i];
}
