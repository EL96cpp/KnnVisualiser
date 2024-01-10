#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <algorithm>

#include "irisdata.h"

enum class KernelType {

    RECTANGULAR,
    TRIANGLE,
    EPANCHENKOV,
    BIQUADRATIC,
    GAUSSIAN

};

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    //void startLearning();
    void onSetKernelType(const KernelType& kernel_type);


signals:
    void openCsvFileError();

private:
    void readDataFromCsv();
    void prepareCrossValidationData();


private:
    QVector<IrisData> dataset;
    QVector<QVector<IrisData>> cv_data;
    int minkowski_metric;
    KernelType kernel_type;

};

#endif // MODEL_H
