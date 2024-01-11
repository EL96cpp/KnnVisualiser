#include "distancesvector.h"

DistancesVector::DistancesVector() {}

void DistancesVector::pushBack(const DistanceData &distance_data) {

    distances.push_back(distance_data);

}

QVector<DistanceData> DistancesVector::getDecreasingSortedDistances(const int &search_id) {



}
