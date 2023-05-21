#include "X917Generator.h"

#include "dll.h"
#include "cryptlib.h"
#include "rng.h"
#include "osrng.h"

void X917Generator::generateData(std::vector<uint8_t>& data, size_t size)
{
    if (!size)
        size = data.size();

    data.reserve(size);

    using namespace CryptoPP;

    SecByteBlock scratch(size);

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    OS_GenerateRandomBlock(false, key, key.size());
    X917RNG rng(new AES::Encryption(key, AES::DEFAULT_KEYLENGTH), m_seed.data(), NULLPTR);

    rng.GenerateBlock(scratch, scratch.size());
    data.assign(scratch.begin(), scratch.end());
}

void X917Generator::setSeed(const std::vector<uint8_t>& seed)
{
    if (seed.size() != 16)
        throw std::logic_error("Seed size is invalid");

    m_seed = seed;
}
