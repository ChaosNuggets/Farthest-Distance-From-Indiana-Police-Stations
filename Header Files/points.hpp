#ifndef POINTS_HPP
#define POINTS_HPP

#include <utility>
#include <vector>

extern std::vector<std::vector<bool>> points;
extern long double totalPoints;
void fillPoints();
std::pair<int, int> coordToIndex(const std::pair<float, float>& coordinate);
std::pair<float, float> indexToCoord(const std::pair<int, int>& index);

#endif