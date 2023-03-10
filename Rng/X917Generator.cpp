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
    SecByteBlock seed(AES::BLOCKSIZE);
    OS_GenerateRandomBlock(false, key, key.size());
    OS_GenerateRandomBlock(false, seed, seed.size()); // TODO: remove generating seed from here
    X917RNG rng(new AES::Encryption(key, AES::DEFAULT_KEYLENGTH), seed, NULLPTR);

    rng.GenerateBlock(scratch, scratch.size());
    data.assign(scratch.begin(), scratch.end());
}

void X917Generator::setSeed(const std::vector<uint8_t>& seed)
{

}
