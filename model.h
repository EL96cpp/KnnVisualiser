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

signals:
    void openCsvFileError();
    void setIsLearning(const bool& is_learning); //Sends, when model starts/stops learning process

private:
    void readDataFromCsv();
    void prepareCrossValidationData();
    double calculateDistance(const IrisData& first, const IrisData& second);


private:
    QVector<IrisData> dataset;
    QVector<QVector<IrisData>> cv_data;
    std::function<double(const double&)> kernel;
    int minkowski_metric_param;
    double window_width;
    bool is_learning;

};

#endif // MODEL_H
