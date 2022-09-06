#include <iostream>
#include <iomanip>
#include <cstring>
#include "station-coordinates.hpp"
#include "points.hpp"
#include "get-test-bounds.hpp"
#include "calculate-distance.hpp"
#include "constants.hpp"

long double convertSpeedToCircleRadius(long double speed)
{
    return speed * (MAX_TIME / MINUTES_IN_1_HOUR);
}

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

static float calculateCoverage()
{
    long double pointsNotCovered = 0;
    for (int i = 0; i < LATSIZE; i++)
    {
        for (int j = 0; j < LONGSIZE; j++)
        {
            if (points[i][j])
            {
                pointsNotCovered++;
            }
        }
    }
    const long double notCoverage = pointsNotCovered / totalPoints;
    return 1 - notCoverage;
}

int main()
{
    
    std::cout << std::setprecision(15);
    std::cout << "Percent coverage with " << MAX_TIME << " min of flight time starting from 0mph and incrementing by 5mph:\n";
    for (double speed = 0; speed <= 210; speed+=5)
    {
        long double circleRadius = convertSpeedToCircleRadius(speed); // The circleRadius the user enters in miles
        fillPoints();
        testAllStations(circleRadius);
        const long double percentCovered = calculateCoverage() * 100;
        std::cout << percentCovered << "%\n";
    }
    std::cin.ignore();
    return 0;
}