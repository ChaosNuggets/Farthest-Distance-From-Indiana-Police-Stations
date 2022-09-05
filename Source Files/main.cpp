#include <iostream>
#include "station-coordinates.hpp"
#include "points.hpp"
#include "constants.hpp"

std::pair<std::pair<int, int>, std::pair<int, int>> getTestIndexBounds(const std::pair<float, float>& stationCoordinate, const float radiusOfCircles)
{
    auto& [stationLat, stationLong] = stationCoordinate;
    
}

int main()
{
    fillPoints();
    for (int i = LATSIZE - 1; i >= 0; i -= 2)
    {
        for (int j = 0; j < LONGSIZE; j += 2)
        {
            std::cout << points[i][j] ? '1' : ' ';
        }
        std::cout << '\n';
    }
    return 0;
}