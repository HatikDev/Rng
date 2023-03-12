#pragma once

#include "Test.h"

class AnalysisTest : public Test
{
public:
    AnalysisTest(size_t length) : Test(), m_length{ length } {}
    virtual ~AnalysisTest() {}

    virtual void executeTest(const std::vector<uint8_t>& inputBuffer, result_type& outputBuffer) override;

private:
    size_t m_length;
};