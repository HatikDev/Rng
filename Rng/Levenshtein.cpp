#include "Levenshtein.h"

#include <algorithm>
#include <bitset>
#include <vector>

size_t levenshteinDistance(const std::string& source, const std::string& target)
{
    if (source.size() > target.size())
        return levenshteinDistance(target, source);

    const size_t min_size = source.size(), max_size = target.size();
    std::vector<size_t> lev_dist(min_size + 1);

    for (size_t i = 0; i <= min_size; ++i)
        lev_dist[i] = i;

    for (size_t j = 1; j <= max_size; ++j)
    {
        size_t previous_diagonal = lev_dist[0], previous_diagonal_save;
        ++lev_dist[0];

        for (size_t i = 1; i <= min_size; ++i)
        {
            previous_diagonal_save = lev_dist[i];
            if (source[i - 1] == target[j - 1])
                lev_dist[i] = previous_diagonal;
            else
                lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;

            previous_diagonal = previous_diagonal_save;
        }
    }

    return lev_dist[min_size];
}

size_t levenshteinTest1(const std::vector<uint8_t>& sequence1, const std::vector<uint8_t>& sequence2)
{
    std::string string1;
    std::string string2;

    for (auto byte : sequence1)
        string1 += std::bitset<8>(byte).to_string();
    for (auto byte : sequence2)
        string2 += std::bitset<8>(byte).to_string();

    return levenshteinDistance(string1, string2);
}

size_t levenshteinTest2(const std::vector<uint8_t>& sequence1, const std::vector<uint8_t>& sequence2)
{
    std::string string1;
    std::string string2;

    for (auto byte : sequence1)
        string1 += (char)byte;
    for (auto byte : sequence2)
        string2 += (char)byte;

    return levenshteinDistance(string1, string2);
}