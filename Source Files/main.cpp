#define _USE_MATH_DEFINES

#include <iostream>
#include "station-coordinates.hpp"
#include "points.hpp"
#include "constants.hpp"
#include <cmath>

constexpr long double toRadians(const long double degrees)
{
	long double one_deg = M_PI / 180;
	return (one_deg * degrees);
}

constexpr long double toDegrees(const long double radians)
{
    long double one_rad = 180 / M_PI;
    return (one_rad * radians);
}

constexpr float calcCoordLong(const std::pair<float, float>& coordinate, const float distance)
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

constexpr float calcCoordLat(const std::pair<float, float>& coordinate, const float distance)
{
    const float latitude = coordinate.first; // Extract latitude from coordinate
    const float difference = distance * LAT_IN_1_MILE; // Not stupid formula
    return latitude + difference;
}

constexpr std::pair<std::pair<float, float>, std::pair<float, float>> getTestCoordinateBounds(const std::pair<float, float>& stationCoordinate, const float radiusOfCircles)
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
    auto [lowLat, lowLong] = convertCoordToIndex(lowCorner);
    auto [highLat, highLong] = convertCoordToIndex(highCorner);
    
    // Make the range a little bigger than it has to be to correct for rounding errors, it's just safer
    return {{lowLat - 1, lowLong - 1}, {highLat + 1, highLong + 1}};
}

int main()
{
    fillPoints();
    const auto [lowCorner, highCorner] = getTestIndexBounds({40.570342, -86.053295}, 30);
    const auto [lowLat, lowLong] = lowCorner;
    const auto [highLat, highLong] = highCorner;
    std::cout << lowLat << ' ' << lowLong << '\n';
    std::cout << highLat << ' ' << highLong << '\n';
    std::cin.ignore();
    return 0;
}