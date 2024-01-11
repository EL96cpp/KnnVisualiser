#include "distancesvector.h"

DistancesVector::DistancesVector() {}

void DistancesVector::pushBack(const DistanceData &distance_data) {

    distances.push_back(distance_data);

}

void DistancesVector::clear() {

    distances.clear();

}

QVector<DistanceData> DistancesVector::getDecreasingSortedDistances(const int &search_id) {

    QVector<DistanceData> result;

    for (int i = 0; i < distances.size(); ++i) {

        if (distances[i].checkIfIncludesId(search_id)) {

            result.push_back(distances[i]);

        }

    }

    std::sort(result.begin(), result.end());
    std::reverse(result.begin(), result.end());
    return result;

}
