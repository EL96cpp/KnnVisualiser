#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new Model(this)) {

    ui->setupUi(this);
    setWindowTitle("KnnVisualiser");

    auto dv = new QDoubleValidator(0.0, 5.0, 2); // [0, 5] with 2 decimals of precision
    dv->setNotation(QDoubleValidator::StandardNotation);
    ui->windowWidthLineEdit->setValidator(dv);

    connect(this, &MainWindow::setKernelType, model, &Model::onSetKernelType);
    connect(this, &MainWindow::setMinkowskiMetric, model, &Model::onSetMinkowskiMetric);
    connect(this, &MainWindow::setWindowWidth, model, &Model::onSetWindowWidth);

}

MainWindow::~MainWindow() {

    delete ui;

}


void MainWindow::on_kernelComboBox_currentTextChanged(const QString &kernel_string) {

    if (kernel_string == "Прямоугольное") {

        emit setKernelType(KernelType::RECTANGULAR);

    } else if (kernel_string == "Треугольное") {

        emit setKernelType(KernelType::TRIANGLE);

    } else if (kernel_string == "Ядро Епанченкова") {

        emit setKernelType(KernelType::EPANCHENKOV);

    } else if (kernel_string == "Биквадратное") {

        emit setKernelType(KernelType::BIQUADRATIC);

    } else if (kernel_string == "Гауссовское") {

        emit setKernelType(KernelType::GAUSSIAN);

    }

}


void MainWindow::on_windowWidthLineEdit_textChanged(const QString &arg1) {

    QString copy = arg1;
    emit setWindowWidth(copy.replace(",", ".").toDouble());

}


void MainWindow::on_metricComboBox_currentTextChanged(const QString &arg1) {

    QString copy = arg1[0];
    emit setMinkowskiMetric(copy.toInt());

}

