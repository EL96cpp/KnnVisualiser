#include "distancesvector.h"

DistancesVector::DistancesVector() {}

void DistancesVector::pushBack(const DistanceData &distance_data) {

    distances.push_back(distance_data);

}

void DistancesVector::clear() {

    distances.clear();

}

QVector<DistanceData> DistancesVector::getDecreasingSortedDistances(const int &search_id, const QVector<int>& cv_indexes) {

    QVector<DistanceData> result;

    for (int i = 0; i < distances.size(); ++i) {

        if (distances[i].checkIfIncludesId(search_id)) {

            //If cv_indexes vector contains pair_id, we don't need this distance value!
            //(It means this is the distance between two test, but not train points!)

            int pair_id = distances[i].getPairForId(search_id);

            if (pair_id != -1 && !cv_indexes.contains(pair_id)) {

                result.push_back(distances[i]);

            }

        }

    }

    std::sort(result.begin(), result.end());
    std::reverse(result.begin(), result.end());
    return result;

}
