#ifndef IRISDATA_H
#define IRISDATA_H

enum class IrisType {

    SETOSA,
    VERSICOLOR,
    VIRGINICA

};

enum class FeatureType {

    SEPAL_LENGTH,
    SEPAL_WIDTH,
    PETAL_LENGTH,
    PETAL_WIDTH

};

class IrisData {

public:
    IrisData(const int& id, const double& sepal_length, const double& sepal_width,
             const double& petal_length, const double& petal_width, const IrisType& iris_type);

    int getId() const;
    double getSepalLength() const;
    double getSepalWidth() const;
    double getPetalLength() const;
    double getPetalWidth() const;
    double getFeatureValue(const FeatureType& feature_type) const;
    IrisType getType() const;

private:
    int id;
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    IrisType iris_type;

};

#endif // IRISDATA_H
