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
    //void startLearning();
    void onSetKernelType(const QString& kernel_type);
    void onSetWindowWidth(const double &window_width);
    void onSetMinkowskiMetric(const int& minkowski_metric);

signals:
    void openCsvFileError();

private:
    void readDataFromCsv();
    void prepareCrossValidationData();


private:
    QVector<IrisData> dataset;
    QVector<QVector<IrisData>> cv_data;
    std::function<double(const double&)> kernel;
    int minkowski_metric;
    double window_width;

};

#endif // MODEL_H
