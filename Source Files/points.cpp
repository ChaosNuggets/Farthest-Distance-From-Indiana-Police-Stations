#include "points.hpp"
#include "constants.hpp"
#include <cmath>
#include <functional>
#include <iostream>

//This convoluted line creates a 2d matrix of coordinates where all the coordinates are {999, 999} (there's no null in c++ sadly)
std::vector<std::vector<bool>> points(LATSIZE, std::vector<bool>(LONGSIZE, false));

std::pair<int, int> convertCoordToIndex(const std::pair<float, float>& coordinate, std::function<int(float)> roundFunc)
{
    const auto& [latitude, longitude] = coordinate;
    const float latDifference = (latitude - LOWESTLAT) / LATIN1MILE;
    const float longDifference = (longitude - LOWESTLONG) / LONGIN1MILE;
    int latIndex = roundFunc(latDifference);
    int longIndex = roundFunc(longDifference);
    return {latIndex, longIndex};
}

void fillPoints()
{
    // These are the coordinates of corners of rectangles that are in Indiana
    const std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> rectangleCorners =
    {
        {{39.105480, -87.523661}, {41.759907, -84.820157}},
        {{39.056190, -87.571926}, {39.105480, -84.897566}},
        {{38.792125, -87.495200}, {39.056190, -84.897566}},
        {{38.468242, -87.495200}, {38.792125, -85.498866}},
        {{38.288894, -87.730132}, {38.468242, -85.697890}},
        {{38.198666, -87.834796}, {38.288894, -85.885433}},
        {{37.999366, -87.910623}, {38.198666, -86.525765}},
        {{38.016023, -86.190050}, {38.198666, -85.932822}}
    };
    for (auto& rectangleCornerSet : rectangleCorners)
    {
        const float lowLat = rectangleCornerSet.first.first;
        const float highLat = rectangleCornerSet.second.first;
        const float lowLong = rectangleCornerSet.first.second;
        const float highLong = rectangleCornerSet.second.second;

        // Fill the points to be spaced less than 1 mile apart
        for (float i = lowLat; i <= highLat; i += LATIN1MILE)
        {
            for (float j = lowLong; j <= highLong; j += LONGIN1MILE)
            {
                auto [latIndex, longIndex] = convertCoordToIndex({i, j}, roundf);
                points[latIndex][longIndex] = true;
            }
        }
    }
}