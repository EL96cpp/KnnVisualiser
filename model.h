#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QStringList>
#include <QTextStream>

#include <typeinfo>

#include "irisdata.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

signals:
    void openCsvFileError();

private:
    void readDataFromCsv();


private:
    QVector<IrisData> dataset;
    QVector<IrisData> train_data;
    QVector<IrisData> test_data;

};

#endif // MODEL_H
