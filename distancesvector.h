#ifndef DISTANCESVECTOR_H
#define DISTANCESVECTOR_H

#include <QVector>
#include <QDebug>
#include <algorithm>

#include "distancedata.h"

class DistancesVector
{
public:
    DistancesVector();

    void pushBack(const DistanceData& distance_data);
    void clear();
    QVector<DistanceData> getDecreasingSortedDistances(const int& search_id);

private:
    QVector<DistanceData> distances;

};

#endif // DISTANCESVECTOR_H
