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

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    //void startLearning();


signals:
    void openCsvFileError();

private:
    void readDataFromCsv();
    void prepareCrossValidationData();


private:
    QVector<IrisData> dataset;
    QVector<QVector<IrisData>> cv_data;

};

#endif // MODEL_H
