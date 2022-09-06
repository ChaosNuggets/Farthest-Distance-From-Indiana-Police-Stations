#define _USE_MATH_DEFINES
#include "points.hpp"
#include <cmath>
#include "constants.hpp"
#include "angle-conversions.hpp"
#include "get-test-bounds.hpp"

static float calcCoordLong(const std::pair<float, float>& coordinate, const float distance)
{
    auto [latitude, longitude] = coordinate; // Extract latitude and longitude from coordinate

    //Convert coordinates to radians
    latitude = toRadians(latitude);
    longitude = toRadians(longitude);
    
    // Stupid formula
    float difference = acos( (cos(distance / 3963) - pow(sin(latitude), 2)) / pow(cos(latitude), 2) );
    
    // Make difference negative if distance is negative
    if (distance < 0) difference *= -1;

    return toDegrees(longitude + difference);
}

static constexpr float calcCoordLat(const std::pair<float, float>& coordinate, const float distance)
{
    const float latitude = coordinate.first; // Extract latitude from coordinate
    const float difference = distance * LAT_IN_1_MILE; // Not stupid formula
    return latitude + difference;
}

static std::pair<std::pair<float, float>, std::pair<float, float>> getTestCoordinateBounds(const std::pair<float, float>& stationCoordinate, const float radiusOfCircles)
{
    const float highLat = calcCoordLat(stationCoordinate, radiusOfCircles);
    const float lowLat = calcCoordLat(stationCoordinate, -radiusOfCircles);
    const float highLong = calcCoordLong(stationCoordinate, radiusOfCircles);
    const float lowLong = calcCoordLong(stationCoordinate, -radiusOfCircles);
    return {{lowLat, lowLong}, {highLat, highLong}};
}

// The corners of the rectangles of the indexes you should test
std::pair<std::pair<int, int>, std::pair<int, int>> getTestIndexBounds(const std::pair<float, float>& stationCoordinate, const float radiusOfCircles)
{
    //Extract the corners from the coordinate bounds
    const auto [lowCorner, highCorner] = getTestCoordinateBounds(stationCoordinate, radiusOfCircles);

    //Calculate the index bounds
    auto [lowLat, lowLong] = coordToIndex(lowCorner);
    auto [highLat, highLong] = coordToIndex(highCorner);
    
    // Make the range a little bigger than it has to be to correct for rounding errors, it's just safer
    return {{lowLat - 1, lowLong - 1}, {highLat + 1, highLong + 1}};
}