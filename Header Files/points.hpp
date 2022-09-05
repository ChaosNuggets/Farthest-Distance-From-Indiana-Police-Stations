#ifndef POINTS_HPP
#define POINTS_HPP

#include <utility>
#include <vector>

extern std::vector<std::vector<bool>> points;
std::pair<int, int> convertCoordToIndex(const std::pair<float, float>&);
void fillPoints();

#endif