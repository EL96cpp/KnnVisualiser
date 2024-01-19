#ifndef IRISDATA_H
#define IRISDATA_H

enum class IrisType {

    SETOSA,
    VERSICOLOR,
    VIRGINICA

};

class IrisData {

public:
    IrisData(const int& id, const double& sepal_length, const double& sepal_width,
             const double& petal_length, const double& petal_width, const IrisType& iris_type);

    int getId() const;
    double getFeatureByIndex(const int& feature_index) const;
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
