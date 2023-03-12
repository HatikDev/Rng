#pragma once

#include "Constants.h"

#include <vector>

class Test
{
public:
    Test() {}
    virtual ~Test() {}

    virtual void executeTest(const std::vector<uint8_t>& inputBuffer, result_type& outputBuffer) = 0;
};
