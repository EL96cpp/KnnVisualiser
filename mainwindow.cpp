#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new Model(this)) {

    ui->setupUi(this);
    setWindowTitle("KnnVisualiser");

    QDoubleValidator* dv = new QDoubleValidator(0.0, 5.0, 2); // [0, 5] with 2 decimals of precision
    dv->setNotation(QDoubleValidator::StandardNotation);
    ui->windowWidthLineEdit->setValidator(dv);
    ui->windowWidthLineEdit->insert("1,0");

    ui->neighboursSpinBox->setRange(1, 120);
    ui->neighboursSpinBox->setValue(1);


    connect(this, &MainWindow::setKernelType, model, &Model::onSetKernelType);
    connect(this, &MainWindow::setMinkowskiMetric, model, &Model::onSetMinkowskiMetric);
    connect(this, &MainWindow::setWindowWidth, model, &Model::onSetWindowWidth);
    connect(this, &MainWindow::setNumberOfNeighbours, model, &Model::onSetNumberOfNeighbours);
    connect(this, &MainWindow::startLearning, model, &Model::startLearning);
    connect(model, &Model::setIsLearning, this, &MainWindow::onSetIsLearning);

    //Send initial values from ui to model
    on_kernelComboBox_currentTextChanged(ui->kernelComboBox->currentText());
    on_windowWidthLineEdit_textChanged(ui->windowWidthLineEdit->text());
    on_metricComboBox_currentTextChanged(ui->metricComboBox->currentText());
    on_neighboursSpinBox_valueChanged(ui->neighboursSpinBox->value());

}

MainWindow::~MainWindow() {

    delete ui;

}

void MainWindow::onSetIsLearning(const bool &is_learning) {

    if (is_learning) {

        ui->windowWidthLineEdit->setDisabled(true);
        ui->kernelComboBox->setDisabled(true);
        ui->metricComboBox->setDisabled(true);

    } else {

        ui->windowWidthLineEdit->setEnabled(true);
        ui->kernelComboBox->setEnabled(true);
        ui->metricComboBox->setEnabled(true);

    }

}


void MainWindow::on_kernelComboBox_currentTextChanged(const QString &kernel_type) {

    emit setKernelType(kernel_type);

}


void MainWindow::on_windowWidthLineEdit_textChanged(const QString &arg1) {

    QString copy = arg1;
    emit setWindowWidth(copy.replace(",", ".").toDouble());

}


void MainWindow::on_metricComboBox_currentTextChanged(const QString &arg1) {

    QString copy = arg1[0];
    emit setMinkowskiMetric(copy.toInt());

}


void MainWindow::on_startLearnButton_clicked() {

    emit startLearning();

}


void MainWindow::on_neighboursSpinBox_valueChanged(int max_number_of_neighbours) {

    emit setNumberOfNeighbours(max_number_of_neighbours);

}

