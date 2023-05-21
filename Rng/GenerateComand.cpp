#include "AESGenerator.h"
#include "GenerateComand.h"
#include "Generator.h"
#include "FileIOSystem.h"
#include "KnuthanGenerator.h"
#include "MersenneTwisterGenerator.h"
#include "LSFRGenerator.h"
#include "LinearGenerator.h"
#include "SystemGenerator.h"
#include "X917Generator.h"

#include <memory>
#include <stdexcept>
#include <unordered_map>

namespace
{
std::unordered_map<std::string, SupportedGenerators> generatorsFromNameToConst = {
    { "linear", SupportedGenerators::Linear },
    { "knuthan", SupportedGenerators::Knuthan },
    { "aes", SupportedGenerators::AESRNG },
    { "x917", SupportedGenerators::X917RNG },
    { "mersenne", SupportedGenerators::MersenneTwister },
    { "lfsr", SupportedGenerators::LFSRSimple },
    { "system", SupportedGenerators::SystemGenerator },
};

std::unordered_map<SupportedGenerators, std::string> generatorsFromConstToName = {
    { SupportedGenerators::Linear , "linear" },
    { SupportedGenerators::Knuthan, "knuthan" },
    { SupportedGenerators::AESRNG, "aes" },
    { SupportedGenerators::X917RNG, "x917" },
    { SupportedGenerators::MersenneTwister , "mersenne" },
    { SupportedGenerators::LFSRSimple, "lfsr" },
    { SupportedGenerators::SystemGenerator, "system" },
};

SupportedGenerators getGeneratorByString(const std::string& generatorName)
{
    if (generatorsFromNameToConst.count(generatorName) == 0)
        throw std::logic_error("Invalid generator constant");

    return generatorsFromNameToConst[generatorName];
}

std::string getGeneratorName(SupportedGenerators generator)
{
    if (generatorsFromConstToName.count(generator) == 0)
        throw std::logic_error("Invalid generator name");

    return generatorsFromConstToName[generator];
}

std::unique_ptr<Generator> getGeneratorObject(SupportedGenerators generator)
{
    switch (generator)
    {
    case SupportedGenerators::AESRNG:
        return std::make_unique<AESGenerator>();
    case SupportedGenerators::Knuthan:
        return std::make_unique<KnuthanGenerator>(0);
    case SupportedGenerators::Linear:
        return std::make_unique<LinearGenerator>();
    case SupportedGenerators::X917RNG:
        return std::make_unique<X917Generator>();
    case SupportedGenerators::LFSRSimple:
        return std::make_unique<LSFRGenerator>(0);
    case SupportedGenerators::MersenneTwister:
        return std::make_unique<MersenneTwisterGenerator>(0);
    case SupportedGenerators::SystemGenerator:
        return std::make_unique<SystemGenerator>(0);
    default:
        throw std::logic_error("Invalid generator name");
    }
}
}

void GenerateComand::execute()
{
    std::unique_ptr<Generator> generator;
    std::unique_ptr<IOSystem> ioSystem;
    std::vector<uint8_t> data(m_dataSize, 0);
    
    const size_t outputFileCount = m_outputFiles.size();
    for (size_t k = 1; k <= m_count; ++k)
    {
        for (size_t i = 0; i < m_generators.size(); ++i)
        {
            std::string outputFilename = prepareStringFromRegex(m_outputFiles[i % outputFileCount], k, m_generators[i]);

            generator = getGeneratorObject(m_generators[i]);
            //generator->setSeed(); // TODO: we HAVE TO set seed
            generator->generateData(data);

            ioSystem = std::make_unique<FileIOSystem>(outputFilename);
            ioSystem->writeBinBatch(data, true);
        }
    }
}

void GenerateComand::parseParams()
{
    for (size_t i = 0; i < m_params.size(); ++i)
    {
        if (m_params[i] == "-g")
        {
            ++i;
            while (m_params[i][0] != '-')
            {
                m_generators.push_back(getGeneratorByString(m_params[i++]));
            }
        }
        if (m_params[i] == "-o")
        {
            ++i;
            while (m_params[i][0] != '-')
            {
                m_outputFiles.push_back(m_params[i++]);
            }
        }
        if (m_params[i] == "-c")
        {
            m_count = std::atoi(m_params[i + 1].c_str());
        }
        if (m_params[i] == "-s")
        {
            m_dataSize = std::atoi(m_params[i + 1].c_str());
        }
    }
}

std::string GenerateComand::prepareStringFromRegex(std::string regex, size_t iota, SupportedGenerators generator)
{
    size_t count = std::count(regex.begin(), regex.end(), '%');
    if (count > 0)
    {
        size_t index = 0;
        while (index != std::string::npos)
        {
            index = regex.find('%', index);
            if (regex[index + 1] == 'd')
            {
                auto startPos = regex.begin() + index;
                auto endPos = regex.begin() + index + 2;
                regex.replace(startPos, endPos, std::to_string(iota));
            }
            else if (regex[index + 1] == 's')
            {
                auto startPos = regex.begin() + index;
                auto endPos = regex.begin() + index + 2;
                regex.replace(startPos, endPos, getGeneratorName(generator));
            }
        }
    }
    return regex;
}
