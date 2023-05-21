#include "KnuthanGenerator.h"

void KnuthanGenerator::generateData(std::vector<uint8_t>& data, size_t size)
{
    if (!size)
        size = data.size();

    const uint32_t a1 = 271828183;
    const uint32_t a2 = 314159269;
    const uint32_t m = 0xFFFFFFFF;

    const uint32_t x0 = (m_seed & 0xFFFFFFFF00000000) >> 32;
    const uint32_t x1 = m_seed & 0xFFFFFFFF;

    data[0] = (x0 & 0xFF000000) >> 24;
    data[1] = (x0 & 0x00FF0000) >> 16;
    data[2] = (x0 & 0x0000FF00) >> 8;
    data[3] = x0 & 0x000000FF;

    data[4] = (x1 & 0xFF000000) >> 24;
    data[5] = (x1 & 0x00FF0000) >> 16;
    data[6] = (x1 & 0x0000FF00) >> 8;
    data[7] = x1 & 0x000000FF;

    uint64_t xn;
    uint64_t xn_1 = x1;
    uint64_t xn_2 = x0;
    for (size_t i = 0; i < size / 4 - 2; ++i)
    {
        xn = (a1 * xn_1 + a2 * xn_2) % m;
        xn_2 = xn_1;
        xn_1 = xn;

        size_t index = 4 * i + 8;
        data[index] = (xn & 0xFF000000) >> 24;
        data[index + 1] = (xn & 0x00FF0000) >> 16;
        data[index + 2] = (xn & 0x0000FF00) >> 8;
        data[index + 3] = xn & 0x000000FF;
    }
}

void KnuthanGenerator::setSeed(const std::vector<uint8_t>& seed)
{
    m_seed = (seed[0] << 56) + (seed[1] << 48) + (seed[2] << 40) + (seed[3] << 32)
             + (seed[4] << 24) + (seed[5] << 16) + (seed[6] << 8) + seed[7];
}