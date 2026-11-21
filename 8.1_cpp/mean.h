#ifndef MEAN_H
#define MEAN_H

#include <vector>
#include <optional>

std::optional<double> meanLength(const std::vector<double>& lengths);
int countGreaterOrEqual(const std::vector<double>& lengths, double threshold);

#endif