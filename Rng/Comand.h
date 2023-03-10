#pragma once

#include <string>
#include <vector>

class Comand
{
public:
    Comand(const std::vector<std::string>& params) 
        : m_params{ params } {}
    virtual ~Comand() {}

    virtual void execute() = 0;

protected:
    std::vector<std::string> m_params;
};