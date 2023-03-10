#pragma once

#include "Constants.h"
#include "Comand.h"

class GenerateComand : public Comand
{
public:
    GenerateComand(const std::vector<std::string>& params) : Comand(params)
    {
        parseParams();
    }
    virtual ~GenerateComand() {}

    virtual void execute() override;

protected:
    std::vector<SupportedGenerators> m_generators;
    std::vector<std::string> m_outputFiles;
    size_t m_count;
    size_t m_dataSize; // in bytes

    virtual void parseParams();

    virtual std::string prepareStringFromRegex(std::string regex, size_t iota, SupportedGenerators generator);
};