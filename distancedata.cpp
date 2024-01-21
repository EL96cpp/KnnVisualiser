#include "distancedata.h"

DistanceData::DistanceData(const double& distance,
                           const IrisType& iris_type) : distance(distance),
                                                        iris_type(iris_type) {}


double DistanceData::getDistance() const {

    return distance;

}

IrisType DistanceData::getIrisType() const {

    return iris_type;

}


bool DistanceData::operator <(const DistanceData &other) const {

    return distance < other.distance;

}

