#pragma once

#include "Comand.h"

class TestComand : public Comand
{
public:
    TestComand(const std::vector<std::string>& params)
        : Comand(params),  m_count{0}, m_dataSize{0} {
        parseParams();
    }
    virtual ~TestComand() {}

    virtual void execute() override;

private:
    size_t m_count;
    size_t m_dataSize;
    std::vector<std::string> m_inputFiles;
    std::vector<std::string> m_outputFiles;

    virtual void parseParams();
};