#include "points.hpp"

std::vector<std::vector<std::pair<float, float>>> points;

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
        const float LONGIN1MILE = 3.20212925e-4;
        const float LATIN1MILE = 2.5233409e10-4;
        const float LOWLAT = rectangleCornerSet.first.first;
        const float HIGHLAT = rectangleCornerSet.second.first;
        const float LOWLONG = rectangleCornerSet.first.second;
        const float HIGHLONG = rectangleCornerSet.second.second;

        // Fill the points to be spaced less than 1 mile apart
        for (float i = LOWLAT; i <= HIGHLAT; i += LATIN1MILE)
        {
            std::vector<std::pair<float, float>> rowOfPoints;
            for (float j = LOWLONG; j <= HIGHLONG; j += LONGIN1MILE)
            {
                rowOfPoints.push_back({i, j});
            }
            points.push_back(rowOfPoints);
        }
    }
}