#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include <QIntValidator>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void setKernelType(const QString& kernel_type);
    void setWindowWidth(const double& window_width);
    void setMinkowskiMetric(const int& minkowski_metric);
    void setMaximumNumberOfNeighbours(const int& max_number_of_neighbours);
    void startLearning();

    void setPredictKernelType(const QString& kernel_type);
    void setPredictWindowWidth(const double& window_width);
    void setPredictMinkowskiMetric(const int& minkowski_metric);
    void setPredictMaximumNumberOfNeighbours(const int& max_number_of_neighbours);

    void setSepalLength(const double& sepal_length);
    void setSepalWidth(const double& sepal_width);
    void setPetalLength(const double& petal_length);
    void setPetalWidth(const double& petal_width);

    void startPrediction();

public slots:
    void onSetIsLearning(const bool& is_learning);

private slots:
    void on_kernelComboBox_currentTextChanged(const QString &arg1);
    void on_windowWidthLineEdit_textChanged(const QString &arg1);
    void on_metricComboBox_currentTextChanged(const QString &arg1);
    void on_startLearnButton_clicked();
    void on_maxNeighboursSpinBox_valueChanged(int arg1);

    void on_predictWindowWidthLineEdit_textChanged(const QString &arg1);
    void on_predictKernelComboBox_currentTextChanged(const QString &arg1);
    void on_predictMetricComboBox_currentTextChanged(const QString &arg1);
    void on_predictMaxNeighboursSpinBox_valueChanged(int arg1);
    void on_sepalLengthEdit_textChanged(const QString &arg1);
    void on_sepalWidthEdit_textChanged(const QString &arg1);
    void on_petalLengthEdit_textChanged(const QString &arg1);
    void on_petalWidthEdit_textChanged(const QString &arg1);
    void on_predictButton_clicked();


private:
    Ui::MainWindow *ui;
    Model* model;
};
#endif // MAINWINDOW_H
