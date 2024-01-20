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
    connect(this, &MainWindow::setPlotBuildingFeatures, model, &Model::onSetPlotBuildingFeatures);
    connect(this, &MainWindow::startBuildingPlot, model, &Model::startBuildingPlot);

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

    if (ui->windowWidthLineEdit->text().isEmpty()) {

        QMessageBox::warning(this, "Plot building error!", "Для обучения модели заполните все необходимые поля!");

    } else {

        emit startBuildingPlot();

    }

}


void MainWindow::on_neighboursSpinBox_valueChanged(int number_of_neighbours) {

    emit setNumberOfNeighbours(number_of_neighbours);

}


void MainWindow::on_sepalLengthLineEdit_textChanged(const QString &sepal_length) {

    QString copy = sepal_length;
    emit setSepalLength(copy.replace(",", ".").toDouble());

    if (ui->sepalLengthLineEdit->text().isEmpty()) {

        ui->sepalLengthCheckBox->setCheckState(Qt::Unchecked);

    } else {

        ui->sepalLengthCheckBox->setCheckState(Qt::Checked);

    }

}


void MainWindow::on_sepalWidthLineEdit_textChanged(const QString &sepal_width) {

    QString copy = sepal_width;
    emit setSepalWidth(copy.replace(",", ".").toDouble());

    if (ui->sepalWidthLineEdit->text().isEmpty()) {

        ui->sepalWidthCheckBox->setCheckState(Qt::Unchecked);

    } else {

        ui->sepalWidthCheckBox->setCheckState(Qt::Checked);

    }

}


void MainWindow::on_petalLengthLineEdit_textChanged(const QString &petal_length) {

    QString copy = petal_length;
    emit setPetalLength(copy.replace(",", ".").toDouble());

    if (ui->petalLengthLineEdit->text().isEmpty()) {

        ui->petalLengthCheckBox->setCheckState(Qt::Unchecked);

    } else {

        ui->petalLengthCheckBox->setCheckState(Qt::Checked);

    }

}


void MainWindow::on_petalWidthLineEdit_textChanged(const QString &petal_width) {

    QString copy = petal_width;
    emit setPetalWidth(copy.replace(",", ".").toDouble());

    if (ui->petalWidthLineEdit->text().isEmpty()) {

        ui->petalWidthCheckBox->setCheckState(Qt::Unchecked);

    } else {

        ui->petalWidthCheckBox->setCheckState(Qt::Checked);

    }

}


void MainWindow::on_predictButton_clicked() {

    if ((ui->sepalLengthLineEdit->text().isEmpty() && ui->sepalLengthCheckBox->checkState() == Qt::Checked)||
        (ui->sepalWidthLineEdit->text().isEmpty() && ui->sepalWidthCheckBox->checkState() == Qt::Checked)||
        (ui->petalLengthLineEdit->text().isEmpty() && ui->petalLengthCheckBox->checkState() == Qt::Checked)||
        (ui->petalWidthLineEdit->text().isEmpty() && ui->petalWidthCheckBox->checkState() == Qt::Checked)||
        (ui->sepalLengthCheckBox->checkState() == Qt::Unchecked && ui->sepalWidthCheckBox->checkState() == Qt::Unchecked &&
        ui->petalLengthCheckBox->checkState() == Qt::Unchecked && ui->petalWidthCheckBox->checkState() == Qt::Unchecked) ||
        ui->windowWidthLineEdit->text().isEmpty()) {

        QMessageBox::warning(this, "Prediction error!", "Для обучения модели заполните все необходимые поля!");


    } else {




    }


}


void MainWindow::on_featuresComboBox_currentTextChanged(const QString &features) {

    if (features == "Sepal length - Sepal width") {

        emit setPlotBuildingFeatures(FeatureType::SEPAL_LENGTH, FeatureType::SEPAL_WIDTH);

    } else if (features == "Sepal length - Petal length") {

        emit setPlotBuildingFeatures(FeatureType::SEPAL_LENGTH, FeatureType::PETAL_LENGTH);

    } else if (features == "Sepal length - Petal width") {

        emit setPlotBuildingFeatures(FeatureType::SEPAL_LENGTH, FeatureType::PETAL_WIDTH);

    } else if (features == "Sepal width - Petal length") {

        emit setPlotBuildingFeatures(FeatureType::SEPAL_WIDTH, FeatureType::PETAL_LENGTH);

    } else if (features == "Sepal width - Petal width") {

        emit setPlotBuildingFeatures(FeatureType::SEPAL_WIDTH, FeatureType::PETAL_WIDTH);

    } else if (features == "Petal length - Petal width") {

        emit setPlotBuildingFeatures(FeatureType::PETAL_LENGTH, FeatureType::PETAL_WIDTH);

    }

}
