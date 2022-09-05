#include "points.hpp"
#include "constants.hpp"
#include <cmath>
#include <iostream>

//This convoluted line creates a 2d matrix of points of size LATSIZE by LONGSIZE
std::vector<std::vector<bool>> points(LATSIZE, std::vector<bool>(LONGSIZE, false));

std::pair<int, int> convertCoordToIndex(const std::pair<float, float>& coordinate)
{
    const auto [latitude, longitude] = coordinate; // Extract data

    // Calculate the coordinate's difference in miles from LOWEST_LAT and LOWEST_LONG
    const float latDifference = (latitude - LOWEST_LAT) / LAT_IN_1_MILE;
    const float longDifference = (longitude - LOWEST_LONG) / LONG_IN_1_MILE;

    // Round the difference so it's an integer
    int latIndex = round(latDifference); // Also why is round not constexpr aaaaa
    int longIndex = round(longDifference);

    return {latIndex, longIndex};
}

void fillPoints()
{
    // These are the coordinates of corners of rectangles that make up the points in Indiana
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
        // Extract data
        const float lowLat = rectangleCornerSet.first.first;
        const float highLat = rectangleCornerSet.second.first;
        const float lowLong = rectangleCornerSet.first.second;
        const float highLong = rectangleCornerSet.second.second;

        // Fill the points to be spaced less than 1 mile apart
        for (float i = lowLat; i <= highLat; i += LAT_IN_1_MILE)
        {
            for (float j = lowLong; j <= highLong; j += LONG_IN_1_MILE)
            {
                auto [latIndex, longIndex] = convertCoordToIndex({i, j});
                points[latIndex][longIndex] = true;
            }
        }
    }
}