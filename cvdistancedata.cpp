#include "cvdistancedata.h"

CVDistanceData::CVDistanceData(const int &first_id,
                               const int &second_id,
                               const IrisType &first_type,
                               const IrisType &second_type,
                               const double &distance) : first_id(first_id), second_id(second_id),
                                                         first_type(first_type), second_type(second_type),
                                                         distance(distance) {}

bool CVDistanceData::checkIfIncludesId(const int &id) const {

    return (first_id == id || second_id == id);

}

int CVDistanceData::getPairId(const int &id) const {

    if (first_id == id) {

        return second_id;

    } else if (second_id == id) {

        return first_id;

    } else {

        return -1;

    }

}

double CVDistanceData::getDistance() const {

    return distance;

}

bool CVDistanceData::operator < (const CVDistanceData &other) const {

    return distance < other.distance;

}
