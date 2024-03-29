#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QMessageBox>

#include "model.h"
#include "plot.h"

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
    void setNumberOfNeighbours(const int& number_of_neighbours);
    void setPlotBuildingFeatures(const FeatureType& first_feature, const FeatureType& second_feature);
    void addPredictionFeature(const FeatureType& feature);
    void removePredictionFeature(const FeatureType& feature);


    void setSepalLength(const double& sepal_length);
    void setSepalWidth(const double& sepal_width);
    void setPetalLength(const double& petal_length);
    void setPetalWidth(const double& petal_width);

    void startPrediction();

public slots:
    void onSetIsLearning(const bool& is_learning);
    void onSetPredictedIrisType(const IrisType& predicted_type);
    void onSetModelAccuracy(const double& model_accuracy);

private slots:
    void on_kernelComboBox_currentTextChanged(const QString &arg1);
    void on_windowWidthLineEdit_textChanged(const QString &arg1);
    void on_metricComboBox_currentTextChanged(const QString &arg1);
    void on_neighboursSpinBox_valueChanged(int number_of_neighbours);
    void on_featuresComboBox_currentTextChanged(const QString &features);

    void on_sepalLengthLineEdit_textChanged(const QString &sepal_length);
    void on_sepalWidthLineEdit_textChanged(const QString &sepal_width);
    void on_petalLengthLineEdit_textChanged(const QString &petal_length);
    void on_petalWidthLineEdit_textChanged(const QString &petal_width);

    void on_predictButton_clicked();

    void on_sepalLengthCheckBox_stateChanged(int arg1);
    void on_sepalWidthCheckBox_stateChanged(int arg1);
    void on_petalLengthCheckBox_stateChanged(int arg1);
    void on_petalWidthCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Model* model;
    Plot* plot;

};
#endif // MAINWINDOW_H
