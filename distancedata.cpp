#include "distancedata.h"

DistanceData::DistanceData(const int& first_id,
                           const int& second_id,
                           const double& distance) : first_id(first_id),
                                                     second_id(second_id),
                                                     distance(distance) {}

bool DistanceData::checkIfIncludesId(const int &search_id) {

    return (search_id == first_id) || (search_id == second_id);

}

double DistanceData::getDistance() {

    return distance;

}
