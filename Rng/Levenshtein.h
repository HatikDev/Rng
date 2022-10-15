#pragma once

#include <algorithm>
#include <string>
#include <vector>

size_t levenshteinDistance(const std::string& source, const std::string& target);

size_t levenshteinTest1(const std::vector<uint8_t>& sequence1, const std::vector<uint8_t>& sequence2);

size_t levenshteinTest2(const std::vector<uint8_t>& sequence1, const std::vector<uint8_t>& sequence2);