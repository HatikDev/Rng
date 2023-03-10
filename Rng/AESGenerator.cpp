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
    SecByteBlock seed(32);
    OS_GenerateRandomBlock(false, seed, seed.size());
    seedByteBlock = seed;

    AES_RNG prng(seed.data(), seed.size());
    prng.GenerateBlock(data.data(), data.size());
}

void AESGenerator::setSeed(const std::vector<uint8_t>& seed)
{

}