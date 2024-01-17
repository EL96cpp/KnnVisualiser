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

    ui->maxNeighboursSpinBox->setRange(10, 100);
    ui->maxNeighboursSpinBox->setValue(30);

    ui->predictWindowWidthLineEdit->setValidator(dv);
    ui->predictWindowWidthLineEdit->insert("1,0");

    ui->predictMaxNeighboursSpinBox->setRange(1, 150);
    ui->predictMaxNeighboursSpinBox->setValue(1);

    QDoubleValidator* iris_validator = new QDoubleValidator(0.1, 10.0, 2);
    iris_validator->setNotation(QDoubleValidator::StandardNotation);

    ui->sepalLengthEdit->setValidator(iris_validator);
    ui->sepalWidthEdit->setValidator(iris_validator);
    ui->petalLengthEdit->setValidator(iris_validator);
    ui->petalWidthEdit->setValidator(iris_validator);

    ui->sepalLengthEdit->insert("1,0");
    ui->sepalWidthEdit->insert("1,0");
    ui->petalLengthEdit->insert("1,0");
    ui->petalWidthEdit->insert("1,0");


    connect(this, &MainWindow::setKernelType, model, &Model::onSetKernelType);
    connect(this, &MainWindow::setMinkowskiMetric, model, &Model::onSetMinkowskiMetric);
    connect(this, &MainWindow::setWindowWidth, model, &Model::onSetWindowWidth);
    connect(this, &MainWindow::setMaximumNumberOfNeighbours, model, &Model::onSetMaximumNumberOfNeighbours);
    connect(this, &MainWindow::startLearning, model, &Model::startLearning);
    connect(model, &Model::setIsLearning, this, &MainWindow::onSetIsLearning);

    connect(this, &MainWindow::setPredictKernelType, model, &Model::onSetPredictionKernelType);
    connect(this, &MainWindow::setPredictMinkowskiMetric, model, &Model::onSetPredictionMinkowskiMetric);
    connect(this, &MainWindow::setPredictWindowWidth, model, &Model::onSetPredictionWindowWidth);
    connect(this, &MainWindow::setPredictMaximumNumberOfNeighbours, model, &Model::onSetPredictionMaximumNumberOfNeighbours);
    connect(this, &MainWindow::startPrediction, model, &Model::startPrediction);

    connect(this, &MainWindow::setSepalLength, model, &Model::onSetSepalLength);
    connect(this, &MainWindow::setSepalWidth, model, &Model::onSetSepalWidth);
    connect(this, &MainWindow::setPetalLength, model, &Model::onSetPetalLength);
    connect(this, &MainWindow::setPetalWidth, model, &Model::onSetPetalWidth);

    //Send initial values from ui to model
    on_kernelComboBox_currentTextChanged(ui->kernelComboBox->currentText());
    on_windowWidthLineEdit_textChanged(ui->windowWidthLineEdit->text());
    on_metricComboBox_currentTextChanged(ui->metricComboBox->currentText());
    on_maxNeighboursSpinBox_valueChanged(ui->maxNeighboursSpinBox->value());

    on_predictKernelComboBox_currentTextChanged(ui->predictKernelComboBox->currentText());
    on_predictWindowWidthLineEdit_textChanged(ui->predictWindowWidthLineEdit->text());
    on_predictMetricComboBox_currentTextChanged(ui->predictMetricComboBox->currentText());
    on_predictMaxNeighboursSpinBox_valueChanged(ui->predictMaxNeighboursSpinBox->value());


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


void MainWindow::on_windowWidthLineEdit_textChanged(const QString &window_width) {

    QString copy = window_width;
    emit setWindowWidth(copy.replace(",", ".").toDouble());

}


void MainWindow::on_metricComboBox_currentTextChanged(const QString &arg1) {

    QString copy = arg1[0];
    emit setMinkowskiMetric(copy.toInt());

}


void MainWindow::on_startLearnButton_clicked() {

    emit startLearning();

}


void MainWindow::on_maxNeighboursSpinBox_valueChanged(int max_number_of_neighbours) {

    emit setMaximumNumberOfNeighbours(max_number_of_neighbours);

}


void MainWindow::on_predictWindowWidthLineEdit_textChanged(const QString &window_width) {

    QString copy = window_width;
    emit setPredictWindowWidth(copy.replace(",", ".").toDouble());

}


void MainWindow::on_predictKernelComboBox_currentTextChanged(const QString &kernel_type) {

    emit setPredictKernelType(kernel_type);

}


void MainWindow::on_predictMetricComboBox_currentTextChanged(const QString &minkowski_metric_parameter) {

    QString val = minkowski_metric_parameter[0];
    emit setPredictMinkowskiMetric(val.toInt());

}


void MainWindow::on_predictMaxNeighboursSpinBox_valueChanged(int arg1) {

    emit setPredictMaximumNumberOfNeighbours(arg1);

}


void MainWindow::on_sepalLengthEdit_textChanged(const QString &sepal_length) {

    emit setSepalLength(sepal_length.toDouble());

}


void MainWindow::on_sepalWidthEdit_textChanged(const QString &sepal_width) {

    emit setSepalWidth(sepal_width.toDouble());

}


void MainWindow::on_petalLengthEdit_textChanged(const QString &petal_length) {

    emit setPetalLength(petal_length.toDouble());

}


void MainWindow::on_petalWidthEdit_textChanged(const QString &petal_width) {

    emit setPetalWidth(petal_width.toDouble());

}


void MainWindow::on_predictButton_clicked() {

    emit startPrediction();

}


