#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new Model(this)) {

    ui->setupUi(this);
    setWindowTitle("KnnVisualiser");

    QDoubleValidator* window_validator = new QDoubleValidator(0.00, 5.00, 2); // [0, 5] with 2 decimals of precision
    window_validator->setNotation(QDoubleValidator::StandardNotation);
    ui->windowWidthLineEdit->setValidator(window_validator);
    ui->windowWidthLineEdit->insert("1,0");

    QDoubleValidator* iris_validator = new QDoubleValidator(0.1, 9.9, 1);
    iris_validator->setNotation(QDoubleValidator::StandardNotation);
    ui->sepalLengthLineEdit->setValidator(iris_validator);
    ui->sepalWidthLineEdit->setValidator(iris_validator);
    ui->petalLengthLineEdit->setValidator(iris_validator);
    ui->petalWidthLineEdit->setValidator(iris_validator);


    ui->neighboursSpinBox->setRange(1, 120);
    ui->neighboursSpinBox->setValue(1);


    connect(this, &MainWindow::setKernelType, model, &Model::onSetKernelType);
    connect(this, &MainWindow::setMinkowskiMetric, model, &Model::onSetMinkowskiMetric);
    connect(this, &MainWindow::setWindowWidth, model, &Model::onSetWindowWidth);
    connect(this, &MainWindow::setNumberOfNeighbours, model, &Model::onSetNumberOfNeighbours);
    connect(this, &MainWindow::setFeatureIndexes, model, &Model::onSetFeatureIndexes);
    connect(this, &MainWindow::startLearning, model, &Model::startLearning);

    connect(this, &MainWindow::setSepalLength, model, &Model::onSetSepalLength);
    connect(this, &MainWindow::setSepalWidth, model, &Model::onSetSepalWidth);
    connect(this, &MainWindow::setPetalLength, model, &Model::onSetPetalLength);
    connect(this, &MainWindow::setPetalWidth, model, &Model::onSetPetalWidth);

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


void MainWindow::on_neighboursSpinBox_valueChanged(int number_of_neighbours) {

    emit setNumberOfNeighbours(number_of_neighbours);

}


void MainWindow::on_sepalLengthLineEdit_textChanged(const QString &sepal_length) {

    QString copy = sepal_length;
    emit setSepalLength(copy.replace(",", ".").toDouble());

}


void MainWindow::on_sepalWidthLineEdit_textChanged(const QString &sepal_width) {

    QString copy = sepal_width;
    emit setSepalWidth(copy.replace(",", ".").toDouble());

}


void MainWindow::on_petalLengthLineEdit_textChanged(const QString &petal_length) {

    QString copy = petal_length;
    emit setPetalLength(copy.replace(",", ".").toDouble());

}


void MainWindow::on_petalWidthLineEdit_textChanged(const QString &petal_width) {

    QString copy = petal_width;
    emit setPetalWidth(copy.replace(",", ".").toDouble());

}


void MainWindow::on_predictButton_clicked() {

    if (ui->sepalLengthLineEdit->text().isEmpty() || ui->sepalWidthLineEdit->text().isEmpty() ||
        ui->petalLengthLineEdit->text().isEmpty() || ui->petalWidthLineEdit->text().isEmpty() ||
        ui->windowWidthLineEdit->text().isEmpty()) {

        QMessageBox::warning(this, "Prediction error!", "Для обучения модели заполните все необходимые поля!");


    } else {




    }


}


void MainWindow::on_featuresComboBox_currentTextChanged(const QString &features) {

    if (features == "Sepal length - Sepal width") {

        emit setFeatureIndexes(0, 1);

    } else if (features == "Sepal length - Petal length") {

        emit setFeatureIndexes(0, 2);

    } else if (features == "Sepal length - Petal width") {

        emit setFeatureIndexes(0, 3);

    } else if (features == "Sepal width - Petal length") {

        emit setFeatureIndexes(1, 2);

    } else if (features == "Sepal width - Petal width") {

        emit setFeatureIndexes(1, 3);

    } else if (features == "Petal length - Petal width") {

        emit setFeatureIndexes(2, 3);

    }

}
