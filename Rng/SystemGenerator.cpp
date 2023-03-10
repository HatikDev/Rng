#include "SystemGenerator.h"

void SystemGenerator::generateData(std::vector<uint8_t>& data, size_t size)
{
    if (!size)
        size = data.size();

    srand(m_seed);

    for (size_t i = 0; i < size; ++i)
        data[i] = rand() % 0x100;
}

void SystemGenerator::setSeed(const std::vector<uint8_t>& seed)
{

}
