#include "constants.hpp"
#include <cmath>

const float EARTH_RADIUS = 3963; // Earth's radius in miles
const float LOWEST_LAT = 37.999366; // Lowest latitude that I have in points
const float LOWEST_LONG = -87.910623; // Lowest longitude that I have in points
const float HIGHEST_LAT = 41.759907; // Highest latitude that I have in points
const float HIGHEST_LONG = -84.820157; // Highest longitude that I have in points
const double LONG_IN_1_MILE = 0.01834684915; // Longitude per mile at LOWEST_LAT
const double LAT_IN_1_MILE = 0.01445767838; // Latitude per mile
const int LATSIZE = ceil( (HIGHEST_LAT - LOWEST_LAT) / LAT_IN_1_MILE ); // Vertical size of points matrix
const int LONGSIZE = ceil( (HIGHEST_LONG - LOWEST_LONG) / LONG_IN_1_MILE ); // Horizontal size of points matrix