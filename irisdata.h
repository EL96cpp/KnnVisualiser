#ifndef IRISDATA_H
#define IRISDATA_H


class IrisData {

public:
    IrisData(const int& id, const double& sepal_length, const double& sepal_width,
             const double& petal_length, const double& petal_width, const int& iris_type);

    int getId() const;
    double getSepalLength() const;
    double getSepalWidth() const;
    double getPetalLength() const;
    double getPetalWidth() const;
    int getType() const;

private:
    int id;
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    int iris_type;

};

#endif // IRISDATA_H
