#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <algorithm>
#include <math.h>
#include <functional>

#include "irisdata.h"
#include "distancedata.h"
#include "distancesvector.h"


class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void startLearning();
    void onSetKernelType(const QString& kernel_type);
    void onSetWindowWidth(const double &window_width);
    void onSetMinkowskiMetric(const int& minkowski_metric_param);
    void onSetNumberOfNeighbours(const int& number_of_neighbours);

    void onSetSepalLength(const double& sepal_length);
    void onSetSepalWidth(const double& sepal_width);
    void onSetPetalLength(const double& petal_length);
    void onSetPetalWidth(const double& petal_width);

signals:
    void openCsvFileError();
    void setIsLearning(const bool& is_learning); //Emits, when model starts/stops learning process

private:
    void readDataFromCsv();
    void prepareCrossValidationData();
    void setDistancesVector();
    double calculateDistance(const IrisData& first, const IrisData& second);
    QVector<double> getCvGroupAccuracies(const int& group_index);
    int predictType(const double& first_type_score, const double& second_type_score, const double& third_type_score);


private:
    QVector<IrisData> dataset;
    QVector<QVector<IrisData>> cv_data;
    std::function<double(const double&)> kernel;
    int minkowski_metric_param;
    double window_width;
    bool is_learning;
    DistancesVector distances;
    QVector<double> accuracy_results;
    int number_of_neighbours;

    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;

};

#endif // MODEL_H
