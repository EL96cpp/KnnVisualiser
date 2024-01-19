#include "irisdata.h"

IrisData::IrisData(const int& id,
                   const double &sepal_length,
                   const double &sepal_width,
                   const double &petal_length,
                   const double &petal_width,
                   const IrisType &iris_type) : id(id), sepal_length(sepal_length), sepal_width(sepal_width),
                                           petal_length(petal_length), petal_width(petal_width),
                                           iris_type(iris_type) {}

int IrisData::getId() const {

    return id;

}

double IrisData::getFeatureByIndex(const int &feature_index) const {

    switch(feature_index) {

    case 0:
        return sepal_length;

    case 1:
        return sepal_width;

    case 2:
        return petal_length;

    case 3:
        return petal_width;

    }

}


IrisType IrisData::getType() const {

    return iris_type;

}
