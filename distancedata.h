#ifndef DISTANCEDATA_H
#define DISTANCEDATA_H

#include <QVector>

#include "irisdata.h"

class DistanceData
{
public:
    DistanceData(const int& first_id, const int& second_id, const double& distance);

    bool checkIfIncludesId(const int& search_id) const;
    double getDistance() const;
    int getPairForId(const int& search_id) const;

    bool operator < (const DistanceData& other) const;

private:
    int first_id;
    int second_id;
    double distance;


};

#endif // DISTANCEDATA_H
