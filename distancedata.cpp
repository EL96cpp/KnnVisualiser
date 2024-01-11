#include "distancedata.h"

DistanceData::DistanceData(const int& first_id,
                           const int& second_id,
                           const double& distance) : first_id(first_id),
                                                     second_id(second_id),
                                                     distance(distance) {}

bool DistanceData::checkIfIncludesId(const int &search_id) const {

    return (search_id == first_id) || (search_id == second_id);

}

double DistanceData::getDistance() const {

    return distance;

}

int DistanceData::getPairForId(const int &search_id) const
{

}

bool DistanceData::operator <(const DistanceData &other) const {

    return distance < other.distance;

}

