#include "constants.hpp"
#include <cmath>

const float LONGIN1MILE = 0.01834684915;
const float LATIN1MILE = 0.01445767838;
const float LOWESTLAT = 37.999366;
const float LOWESTLONG = -87.910623;
const float HIGHESTLAT = 41.759907;
const float HIGHESTLONG = -84.820157;
const int LATSIZE = ceil( (HIGHESTLAT - LOWESTLAT) / LATIN1MILE );
const int LONGSIZE = ceil( (HIGHESTLONG - LOWESTLONG) / LONGIN1MILE );