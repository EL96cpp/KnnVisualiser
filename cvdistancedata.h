#ifndef CVDISTANCEDATA_H
#define CVDISTANCEDATA_H

#include "irisdata.h"

class CVDistanceData {

public:
    CVDistanceData(const int& first_id, const int& second_id, const IrisType& first_type,
                   const IrisType& second_type, const double& distance);

    bool checkIfIncludesId(const int& id) const;
    int getPairId(const int& id) const;
    double getDistance() const;

    bool operator < (const CVDistanceData& other) const;

private:
    int first_id;
    int second_id;
    IrisType first_type;
    IrisType second_type;
    double distance;

};

#endif // CVDISTANCEDATA_H
