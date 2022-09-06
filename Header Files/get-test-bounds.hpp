#ifndef GET_TEST_BOUNDS_HPP
#define GET_TEST_BOUNDS_HPP

#include <utility>

std::pair<std::pair<int, int>, std::pair<int, int>> getTestIndexBounds(const std::pair<float, float>& stationCoordinate, const float radiusOfCircles);

#endif