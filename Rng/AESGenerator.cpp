#include "AESGenerator.h"

#include "dll.h"
#include "cryptlib.h"
#include "rng.h"
#include "osrng.h"
#include "AES_RNG.h"

void AESGenerator::generateData(std::vector<uint8_t>& data, size_t size)
{
    using namespace CryptoPP;

    SecByteBlock seedByteBlock(32);
    seedByteBlock.Assign(m_seed.data(), m_seed.size());

    AES_RNG prng(m_seed.data(), m_seed.size());
    prng.GenerateBlock(data.data(), data.size());
}

void AESGenerator::setSeed(const std::vector<uint8_t>& seed)
{
    if (seed.size() != 32)
        throw std::logic_error("Seed size is invalid");

    m_seed = seed;
}