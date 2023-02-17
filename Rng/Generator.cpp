#include "Generator.h"

#include "dll.h"
#include "cryptlib.h"
#include "rng.h"
#include "osrng.h"
#include "AES_RNG.h"

#include <random>

namespace
{
std::vector<uint8_t> generateRandRNG(size_t size)
{
    std::vector<uint8_t> block;
    block.reserve(size);

    for (size_t i = 0; i < size; ++i)
        block.push_back(rand() % 0x100);

    return block;
}

std::vector<uint8_t> generateLinear(size_t size)
{
    std::vector<uint8_t> block;
    block.reserve(size);

    const uint64_t a = 6364136223846793005;
    const uint64_t b = 1442695040888963407;
    const uint64_t m = 0x8000000000000000;// (1 << 62);
    uint64_t x = 0x54326457245; // seed

    for (size_t i = 0; i < size / 8; ++i)
    {
        x = (a * x + b) % m;

        block.emplace_back((x & 0xFF00000000000000) >> 52);
        block.emplace_back((x & 0x00FF000000000000) >> 48);
        block.emplace_back((x & 0x0000FF0000000000) >> 40);
        block.emplace_back((x & 0x000000FF00000000) >> 32);
        block.emplace_back((x & 0x00000000FF000000) >> 24);
        block.emplace_back((x & 0x0000000000FF0000) >> 16);
        block.emplace_back((x & 0x000000000000FF00) >> 8);
        block.emplace_back(x &  0x00000000000000FF);
    }

    return block;
}

std::vector<uint8_t> generateX917RNG(size_t size)
{
    std::vector<uint8_t> block;
    block.reserve(size);

    using namespace CryptoPP;

    SecByteBlock scratch(size);

    SecByteBlock key(AES::DEFAULT_KEYLENGTH), seed(AES::BLOCKSIZE);
    OS_GenerateRandomBlock(false, key, key.size());
    OS_GenerateRandomBlock(false, seed, seed.size());
    X917RNG rng(new AES::Encryption(key, AES::DEFAULT_KEYLENGTH), seed, NULLPTR);

    std::ofstream seedFile("X917seed.bin", std::ios::out | std::ios::binary);
    for (auto byte : seed)
        seedFile << static_cast<char>(byte);
    seedFile.close();

    rng.GenerateBlock(scratch, scratch.size());
    block.assign(scratch.begin(), scratch.end());

    return block;
}

std::vector<uint8_t> generateMidSquareRNG(size_t size)
{
    std::vector<uint8_t> block;
    block.reserve(size);

    uint32_t seed = rand();// 0xA3A80;

    for (size_t i = 0; i < size / 2; ++i)
    {
        seed = seed * seed;
        seed &= 0x00FFFF00;
        seed >>= 8;
        block.push_back((seed & 0xFF00) >> 8);
        block.push_back(seed & 0xFF);
    }
    return block;
}

std::vector<uint8_t> generateAESRNG(size_t size)
{
    std::vector<uint8_t> block(size, 0);

    using namespace CryptoPP;

    SecByteBlock seed(32);
    OS_GenerateRandomBlock(false, seed, seed.size());

    std::ofstream seedFile("AESRNGseed.bin", std::ios::out | std::ios::binary);
    for (auto byte : seed)
        seedFile << static_cast<char>(byte);
    seedFile.close();

    AES_RNG prng(seed.data(), seed.size());
    prng.GenerateBlock(block.data(), block.size());

    return block;
}

std::vector<uint8_t> generateMersenneTwister(size_t size)
{
    std::vector<uint8_t> block;
    std::mt19937_64 gen64;
    gen64.seed(348336Ui64);

    uint64_t value;
    for (size_t i = 0; i < size / 8; ++i)
    {
        value = gen64();
        block.emplace_back((value & 0xFF00000000000000) >> 56);
        block.emplace_back((value & 0x00FF000000000000) >> 48);
        block.emplace_back((value & 0x0000FF0000000000) >> 40);
        block.emplace_back((value & 0x000000FF00000000) >> 32);
        block.emplace_back((value & 0x00000000FF000000) >> 24);
        block.emplace_back((value & 0x0000000000FF0000) >> 16);
        block.emplace_back((value & 0x000000000000FF00) >> 8);
        block.emplace_back(value &  0x00000000000000FF);
    }

    return block;
}

std::vector<uint8_t> generateKnuthanRNG(size_t size)
{
    std::vector<uint8_t> block;
    const uint32_t a1 = 271828183;
    const uint32_t a2 = 314159269;
    const uint32_t m = 0xFFFFFFFF;

    const uint64_t seed = 0x345987234098a;
    const uint32_t x0 = (seed & 0xFFFFFFFF00000000) >> 32;
    const uint32_t x1 = seed & 0xFFFFFFFF;

    block.push_back((x0 & 0xFF000000) >> 24);
    block.push_back((x0 & 0x00FF0000) >> 16);
    block.push_back((x0 & 0x0000FF00) >> 8);
    block.push_back(x0 & 0x000000FF);

    block.push_back((x1 & 0xFF000000) >> 24);
    block.push_back((x1 & 0x00FF0000) >> 16);
    block.push_back((x1 & 0x0000FF00) >> 8);
    block.push_back(x1 & 0x000000FF);

    uint64_t xn;
    uint64_t xn_1 = x1;
    uint64_t xn_2 = x0;
    for (size_t i = 0; i < size / 4 - 2; ++i)
    {
        xn = (a1 * xn_1 + a2 * xn_2) % m;
        xn_2 = xn_1;
        xn_1 = xn;

        block.push_back((xn & 0xFF000000) >> 24);
        block.push_back((xn & 0x00FF0000) >> 16);
        block.push_back((xn & 0x0000FF00) >> 8);
        block.push_back(xn & 0x000000FF);
    }

    return block;
}

std::vector<uint8_t> generateLFSRSimple(size_t size)
{
    uint32_t shiftRegister = 0x345987234098a; // seed
    std::vector<uint8_t> block;

    for (size_t i = 0; i < size / 4; ++i)
    {
        block.push_back(shiftRegister & 0x000000FF);
        block.push_back((shiftRegister & 0x0000FF00) >> 8);
        block.push_back((shiftRegister & 0x00FF0000) >> 16);
        block.push_back((shiftRegister & 0xFF000000) >> 24);

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
    for (size_t i = 0; i < block.size(); ++i)
    {
        byte = block[i];
        result = 0;

        result |= (byte & 0x80) >> 7;
        result |= (byte & 0x40) >> 5;
        result |= (byte & 0x20) >> 3;
        result |= (byte & 0x10) >> 1;
        result |= (byte & 0x8) << 1;
        result |= (byte & 0x4) << 3;
        result |= (byte & 0x2) << 5;
        result |= (byte & 0x1) << 7;

        block[i] = result;
    }

    return block;
}
}

std::vector<uint8_t> getRandomBlockFromGenerator(SupportedGenerators generator, size_t size)
{
    if (generator == SupportedGenerators::X917RNG)
        return generateX917RNG(size);

    switch (generator)
    {
    case SupportedGenerators::SystemGenerator:
        return generateRandRNG(size);
    case SupportedGenerators::Linear:
        return generateLinear(size);
    case SupportedGenerators::X917RNG:
        return generateX917RNG(size);
    case SupportedGenerators::MidSquare:
        return generateMidSquareRNG(size);
    case SupportedGenerators::AESRNG:
        return generateAESRNG(size);
    case SupportedGenerators::MersenneTwister:
        return generateMersenneTwister(size);
    case SupportedGenerators::Knuthan:
        return generateKnuthanRNG(size);
    case SupportedGenerators::LFSRSimple:
        return generateLFSRSimple(size);
    }

    return {};
}