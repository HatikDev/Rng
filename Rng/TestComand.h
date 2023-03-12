#pragma once

#include "Comand.h"

class TestComand : public Comand
{
public:
    TestComand(const std::vector<std::string>& params) : Comand(params), m_count{ 0 } {}
    virtual ~TestComand() {}

    virtual void execute() override;

private:
    size_t m_count;
    std::vector<std::string> m_inputFiles;
    std::vector<std::string> m_outputFiles;

    void parseParams();
    std::string prepareStringFromRegex(std::string regex, size_t iota); // TODO: think if we must remove this func from here
};