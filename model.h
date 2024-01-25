#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QColor>
#include <algorithm>
#include <math.h>
#include <functional>

#include "irisdata.h"
#include "distancedata.h"


class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    QVector<IrisData> getDataset();

public slots:
    void onStartPrediction();
    void onSetKernelType(const QString& kernel_type);
    void onSetWindowWidth(const double &window_width);
    void onSetMinkowskiMetric(const int& minkowski_metric_param);
    void onSetNumberOfNeighbours(const int& number_of_neighbours);
    void onSetPlotBuildingFeatures(const FeatureType& first_feature, const FeatureType& second_feature);
    void onAddPredictionFeature(const FeatureType& feature);
    void onRemovePredictionFeature(const FeatureType& feature);

    void onSetSepalLength(const double& sepal_length);
    void onSetSepalWidth(const double& sepal_width);
    void onSetPetalLength(const double& petal_length);
    void onSetPetalWidth(const double& petal_width);

signals:
    void openCsvFileError();
    void setIsLearning(const bool& is_learning); //Emits, when model starts/stops learning process
    void setPredictedIrisType(const IrisType& predicted_type);
    void setModelAccuracy(const double& model_accuracy);

private:
    void readDataFromCsv();
    void setTrainTestDatasets();
    double calculateModelAccuracy();
    double calculateDistance(const IrisData& prediction_iris_data, const IrisData& dataset_iris_data);
    IrisType predictType(const double& setosa_score, const double& versicolor_score, const double& virginica_score);

private:
    QVector<IrisData> dataset;
    QVector<IrisData> train_dataset;
    QVector<IrisData> test_dataset;

    std::function<double(const double&)> kernel;
    int minkowski_metric_param;
    double window_width;
    bool is_learning;
    int number_of_neighbours;

    QVector<FeatureType> plot_building_features;
    QVector<FeatureType> prediction_featrues;

    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;

};

#endif // MODEL_H
