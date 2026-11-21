#include "mean.h"
#include <numeric>

std::optional<double> meanLength(const std::vector<double>& lengths) {
    if (lengths.empty()) {
        return std::nullopt;
    }
    double sum = std::accumulate(lengths.begin(), lengths.end(), 0.0);
    return sum / lengths.size();
}

int countGreaterOrEqual(const std::vector<double>& lengths, double threshold) {
    int count = 0;
    for (double len : lengths) {
        if (len >= threshold) {
            count++;
        }
    }
    return count;
}