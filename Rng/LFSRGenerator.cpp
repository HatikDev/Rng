#include "LSFRGenerator.h"

#include <stdexcept>

void LSFRGenerator::generateData(std::vector<uint8_t>& data, size_t size)
{
    if (!size)
        size = data.size();

    uint32_t shiftRegister = static_cast<uint32_t>(m_seed & 0xFFFFFFFF);

    for (size_t i = 0; i < size / 4; ++i)
    {
        size_t index = 4 * i;
        data[index] = shiftRegister & 0x000000FF;
        data[index + 1] = (shiftRegister & 0x0000FF00) >> 8;
        data[index + 2] = (shiftRegister & 0x00FF0000) >> 16;
        data[index + 3] = (shiftRegister & 0xFF000000) >> 24;

        for (size_t j = 0; j < 32; ++j)
        {
            shiftRegister = (((((shiftRegister >> 31)
                              ^ (shiftRegister >> 6)
                              ^ (shiftRegister >> 4)
                              ^ (shiftRegister >> 2)
                              ^ (shiftRegister >> 1)
                              ^ shiftRegister))
                              & 1) << 31) | (shiftRegister >> 1);
        }
    }

    uint8_t byte;
    uint8_t result;
    for (size_t i = 0; i < size; ++i)
    {
        byte = data[i];
        result = 0;

        result |= (byte & 0x80) >> 7;
        result |= (byte & 0x40) >> 5;
        result |= (byte & 0x20) >> 3;
        result |= (byte & 0x10) >> 1;
        result |= (byte & 0x8) << 1;
        result |= (byte & 0x4) << 3;
        result |= (byte & 0x2) << 5;
        result |= (byte & 0x1) << 7;

        data[i] = result;
    }
}

void LSFRGenerator::setSeed(const std::vector<uint8_t>& seed)
{
    if (seed.size() != 8)
        throw std::logic_error("Seed size is invalid");

    for (size_t i = 0; i < 8; ++i)
        m_seed = (m_seed << 8) & seed[i];
}