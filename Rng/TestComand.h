#pragma once

#include "Comand.h"

class TestComand : public Comand
{
public:
    TestComand(const std::vector<std::string>& params) : Comand(params) {}
    virtual ~TestComand() {}

    virtual void execute() override;
};