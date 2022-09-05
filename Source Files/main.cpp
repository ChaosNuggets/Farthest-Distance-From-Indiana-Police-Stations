#include <iostream>
#include "station-coordinates.hpp"
#include "points.hpp"
#include "constants.hpp"

// The corners of the rectangles of the indexes you should test
std::pair<std::pair<int, int>, std::pair<int, int>> getTestIndexBounds(const std::pair<float, float>& stationCoordinate, const float radiusOfCircles)
{
    auto& [stationLat, stationLong] = stationCoordinate;
    
}

int main()
{
    fillPoints();
    for (int i = LATSIZE - 1; i >= 0; i -= 1)
    {
        for (int j = 0; j < LONGSIZE; j += 1)
        {
            std::cout << (points[i][j] ? 'O' : ' ');
        }
        std::cout << '\n';
    }
    std::cin.ignore();
    return 0;
}