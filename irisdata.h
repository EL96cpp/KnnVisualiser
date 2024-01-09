#ifndef IRISDATA_H
#define IRISDATA_H


class IrisData {

public:
    IrisData(const double& sepal_length, const double& sepal_width,
             const double& petal_length, const double& petal_width,
             const int& iris_type);

    double getSepalLength();
    double getSepalWidth();
    double getPetalLength();
    double getPetalWidth();
    int getType();

private:
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    int iris_type;

};

#endif // IRISDATA_H
