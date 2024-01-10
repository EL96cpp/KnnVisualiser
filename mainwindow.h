#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>

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
    void setKernelType(const KernelType& kernel_type);
    void setWindowWidth(const double& window_width);
    void setMinkowskiMetric(const int& minkowski_metric);

private slots:
    void on_kernelComboBox_currentTextChanged(const QString &arg1);
    void on_windowWidthLineEdit_textChanged(const QString &arg1);

    void on_metricComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Model* model;
};
#endif // MAINWINDOW_H
