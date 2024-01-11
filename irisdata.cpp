#include "irisdata.h"

IrisData::IrisData(const double &sepal_length, const double &sepal_width,
                   const double &petal_length, const double &petal_width,
                   const int &iris_type) : sepal_length(sepal_length), sepal_width(sepal_width),
                                           petal_length(petal_length), petal_width(petal_width),
                                           iris_type(iris_type) {}

double IrisData::getSepalLength() const {

    return sepal_length;

}

double IrisData::getSepalWidth() const {

    return sepal_width;

}

double IrisData::getPetalLength() const {

    return petal_length;

}

double IrisData::getPetalWidth() const {

    return petal_width;

}

int IrisData::getType() const {

    return iris_type;

}
