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

double IrisData::getFeatureValue(const FeatureType &feature_type) const {

    switch (feature_type) {

    case FeatureType::SEPAL_LENGTH:
        return sepal_length;

    case FeatureType::SEPAL_WIDTH:
        return sepal_width;

    case FeatureType::PETAL_LENGTH:
        return petal_length;

    case FeatureType::PETAL_WIDTH:
        return petal_width;

    }


}


IrisType IrisData::getType() const {

    return iris_type;

}
