#include "angle-conversions.hpp"
#include <cmath>
#include "constants.hpp"
#include <utility>
#define _USE_MATH_DEFINES

// C++ program to calculate Distance
// Between Two Points on Earth

long double calculateDistance(const std::pair<long double, long double>& coord1, const std::pair<long double, long double>& coord2)
{
	// Extract data
	auto [lat1, long1] = coord1;
	auto [lat2, long2] = coord2;

	// Convert the latitudes
	// and longitudes
	// from degree to radians.
	lat1 = toRadians(lat1);
	long1 = toRadians(long1);
	lat2 = toRadians(lat2);
	long2 = toRadians(long2);
	
	// Haversine Formula
	long double dlong = long2 - long1;
	long double dlat = lat2 - lat1;

	long double ans = pow(sin(dlat / 2), 2) +
						cos(lat1) * cos(lat2) *
						pow(sin(dlong / 2), 2);

	ans = 2 * asin(sqrt(ans));

	// Radius of Earth in
	// Miles, R = 3956
	long double R = EARTH_RADIUS;
	
	// Calculate the result
	ans = ans * R;

	return ans;
}

// This code is contributed
// by Aayush Chaturvedi
