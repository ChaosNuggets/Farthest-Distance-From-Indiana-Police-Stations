#include <iostream>
#include <iomanip>
#include "station-coordinates.hpp"
#include "points.hpp"
#include "get-test-bounds.hpp"
#include "calculate-distance.hpp"
#include "constants.hpp"

std::pair<float, float> remainingPoint;

static void testAllStations(float circleRadius)
{
    for (const auto& stationCoord : stationCoordinates)
    {
        // Extract data
        const auto [lowCorner, highCorner] = getTestIndexBounds(stationCoord, circleRadius);
        auto [lowLatIndex, lowLongIndex] = lowCorner;
        auto [highLatIndex, highLongIndex] = highCorner;

        // Don't test indexes that are out of bounds of the points matrix
        if (lowLatIndex < 0) lowLatIndex = 0;
        if (lowLongIndex < 0) lowLongIndex = 0;
        if (highLatIndex >= LATSIZE) highLatIndex = LATSIZE - 1;
        if (highLongIndex >= LONGSIZE) highLongIndex = LONGSIZE - 1;

        for (int i = lowLatIndex; i <= highLatIndex; i++)
        {
            for (int j = lowLongIndex; j <= highLongIndex; j++)
            {
                const std::pair<float, float> pointCoord = indexToCoord({i, j});
                const float distance = calculateDistance(pointCoord, stationCoord);
                if (distance <= circleRadius)
                {
                    points[i][j] = false;
                }
            }
        }
    }
}

static bool anyRemainingPoints()
{
    for (int i = 0; i < LATSIZE; i++)
    {
        for (int j = 0; j < LONGSIZE; j++)
        {
            if (points[i][j])
            {
                remainingPoint = indexToCoord({i, j});
                return true;
            }
        }
    }
    return false;
}

int main()
{
    long double radiusAdd = 25; // Add or subtract this number from circleRadius
    long double circleRadius = 50; // Start circleRadius at 50 miles
    std::cout << std::setprecision(15);
    while (radiusAdd > 0)
    {
        fillPoints();
        testAllStations(circleRadius);
        if (anyRemainingPoints())
        {
            std::cout << "circle radius " << circleRadius << " is too small, point remaining at ";
            std::cout << remainingPoint.first << ", " << remainingPoint.second << '\n';
            circleRadius += radiusAdd;
            radiusAdd /= 2;
        } else
        {
            std::cout << "circle radius " << circleRadius << " is too big\n";
            circleRadius -= radiusAdd;
            radiusAdd /= 2;
        }
    }
    std::cin.ignore();
    return 0;
}