#include "Generator.h"

#include "dll.h"
#include "cryptlib.h"
#include "rng.h"
#include "osrng.h"
#include "AES_RNG.h"

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

    AES_RNG prng(seed.data(), seed.size());
    prng.GenerateBlock(block.data(), block.size());

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
    case SupportedGenerators::X917RNG:
        return generateX917RNG(size);
    case SupportedGenerators::MidSquare:
        return generateMidSquareRNG(size);
    case SupportedGenerators::AESRNG:
        return generateAESRNG(size);
    }

    return {};
}