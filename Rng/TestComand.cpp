//#include "Constants.h"
#include "TestComand.h"

void TestComand::execute()
{
    if (m_params[0] == "analysis")
    {
        parseParams();

        std::string inFile;
        std::string outFile;
        for (size_t i = 0; i < m_count; ++i)
        {
            inFile = prepareStringFromRegex(m_inputFiles[i], i + 1);
            outFile = prepareStringFromRegex(m_inputFiles[i], i + 1);

    // ----------------------

            
    

    // ----------------
        }
    }
}

void TestComand::parseParams()
{
    for (size_t i = 1; i < m_params.size(); ++i)
    {
        if (m_params[i] == "-i") // TODO: refactor it
        {
            while (++i < m_params.size() && m_params[++i][0] != '-')
            {
                m_inputFiles.push_back(m_params[i]);
            }
        }
        if (m_params[i] == "-o")
        {
            while (++i < m_params.size() && m_params[i][0] != '-')
            {
                m_outputFiles.push_back(m_params[i]);
            }
        }
        if (m_params[i] == "-c")
        {
            m_count = std::atoi(m_params[++i].c_str());
        }
    }
}

std::string TestComand::prepareStringFromRegex(std::string regex, size_t iota)
{
    size_t count = std::count(regex.begin(), regex.end(), '%');
    if (count > 0)
    {
        size_t index = 0;
        while (index != std::string::npos)
        {
            index = regex.find('%', index);
            if (regex[index + 1] == 'd') // TODO: maybe we can replace it by std::string.replace
            {
                auto startPos = regex.begin() + index;
                auto endPos = regex.begin() + index + 2;
                regex.replace(startPos, endPos, std::to_string(iota));
            }
        }
    }
    return regex;
}
