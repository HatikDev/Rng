#pragma once

#include <map>
#include <string>
#include <vector>

void readBatch(std::string inputFile, size_t position, std::vector<uint8_t>& batch);

template <typename Result>
void writeResult(std::string outputFile, const Result& result);
