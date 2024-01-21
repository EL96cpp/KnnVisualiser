#ifndef DISTANCEDATA_H
#define DISTANCEDATA_H

#include <QVector>

#include "irisdata.h"

//DistanceData object stores distance between IrisData inputed by user,
//and IrisData from dataset, iris_type value stores type of IrisData from dataset,
//so we'll be able to predict type of IrisData inputed by user

class DistanceData {

public:
    DistanceData(const double& distance, const IrisType& iris_type);

    double getDistance() const;
    IrisType getIrisType() const;

    bool operator < (const DistanceData& other) const;

private:
    double distance;
    IrisType iris_type;

};

#endif // DISTANCEDATA_H
