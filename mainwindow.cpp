#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new Model(this))
    , plot(new Plot(this)) {

    ui->setupUi(this);
    setWindowTitle("KnnVisualiser");
    plot->setGraphicsScene(ui->graphicsView);
    plot->setDataset(model->getDataset());

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

    connect(this, &MainWindow::addPredictionFeature, model, &Model::onAddPredictionFeature);
    connect(this, &MainWindow::removePredictionFeature, model, &Model::onRemovePredictionFeature);

    connect(this, &MainWindow::setSepalLength, model, &Model::onSetSepalLength);
    connect(this, &MainWindow::setSepalWidth, model, &Model::onSetSepalWidth);
    connect(this, &MainWindow::setPetalLength, model, &Model::onSetPetalLength);
    connect(this, &MainWindow::setPetalWidth, model, &Model::onSetPetalWidth);

    connect(this, &MainWindow::startPrediction, model, &Model::onStartPrediction);
    connect(model, &Model::setIsLearning, this, &MainWindow::onSetIsLearning);
    connect(model, &Model::setPredictedIrisType, this, &MainWindow::onSetPredictedIrisType);

    //Send initial values from ui to model
    on_kernelComboBox_currentTextChanged(ui->kernelComboBox->currentText());
    on_windowWidthLineEdit_textChanged(ui->windowWidthLineEdit->text());
    on_metricComboBox_currentTextChanged(ui->metricComboBox->currentText());
    on_neighboursSpinBox_valueChanged(ui->neighboursSpinBox->value());
    on_featuresComboBox_currentTextChanged(ui->featuresComboBox->currentText());

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

void MainWindow::onSetPredictedIrisType(const IrisType &predicted_type) {

    switch (predicted_type) {

    case IrisType::SETOSA:
        ui->predictionValueLabel->setText("Iris-setosa");
        break;

    case IrisType::VERSICOLOR:
        ui->predictionValueLabel->setText("Iris-versicolor");
        break;

    case IrisType::VIRGINICA:
        ui->predictionValueLabel->setText("Iris-virginica");
        break;

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


void MainWindow::on_neighboursSpinBox_valueChanged(int number_of_neighbours) {

    emit setNumberOfNeighbours(number_of_neighbours);

}


void MainWindow::on_sepalLengthLineEdit_textChanged(const QString &sepal_length) {

    QString copy = sepal_length;
    emit setSepalLength(copy.replace(",", ".").toDouble());

    if (ui->sepalLengthCheckBox->isEnabled()) {

        if (ui->sepalLengthLineEdit->text().isEmpty()) {

            ui->sepalLengthCheckBox->setCheckState(Qt::Unchecked);

        } else {

            ui->sepalLengthCheckBox->setCheckState(Qt::Checked);

        }

    }

    if (x_axis_plot_feature == FeatureType::SEPAL_LENGTH) {

        plot->setPredictionPointX(copy.replace(",", ".").toDouble());

    } else if (y_axis_plot_feature == FeatureType::SEPAL_LENGTH) {

        plot->setPredictionPointY(copy.replace(",", ".").toDouble());

    }

}


void MainWindow::on_sepalWidthLineEdit_textChanged(const QString &sepal_width) {

    QString copy = sepal_width;
    emit setSepalWidth(copy.replace(",", ".").toDouble());

    if (ui->sepalWidthCheckBox->isEnabled()) {

        if (ui->sepalWidthLineEdit->text().isEmpty()) {

            ui->sepalWidthCheckBox->setCheckState(Qt::Unchecked);

        } else {

            ui->sepalWidthCheckBox->setCheckState(Qt::Checked);

        }

    }

    if (x_axis_plot_feature == FeatureType::SEPAL_WIDTH) {

        plot->setPredictionPointX(copy.replace(",", ".").toDouble());

    } else if (y_axis_plot_feature == FeatureType::SEPAL_WIDTH) {

        plot->setPredictionPointY(copy.replace(",", ".").toDouble());

    }

}


void MainWindow::on_petalLengthLineEdit_textChanged(const QString &petal_length) {

    QString copy = petal_length;
    emit setPetalLength(copy.replace(",", ".").toDouble());

    if (ui->petalLengthCheckBox->isEnabled()) {

        if (ui->petalLengthLineEdit->text().isEmpty()) {

            ui->petalLengthCheckBox->setCheckState(Qt::Unchecked);

        } else {

            ui->petalLengthCheckBox->setCheckState(Qt::Checked);

        }

    }

    if (x_axis_plot_feature == FeatureType::PETAL_LENGTH) {

        plot->setPredictionPointX(copy.replace(",", ".").toDouble());

    } else if (y_axis_plot_feature == FeatureType::PETAL_LENGTH) {

        plot->setPredictionPointY(copy.replace(",", ".").toDouble());

    }

}


void MainWindow::on_petalWidthLineEdit_textChanged(const QString &petal_width) {

    QString copy = petal_width;
    emit setPetalWidth(copy.replace(",", ".").toDouble());

    if (ui->petalWidthCheckBox->isEnabled()) {

        if (ui->petalWidthLineEdit->text().isEmpty()) {

            ui->petalWidthCheckBox->setCheckState(Qt::Unchecked);

        } else {

            ui->petalWidthCheckBox->setCheckState(Qt::Checked);

        }

    }

    if (x_axis_plot_feature == FeatureType::PETAL_WIDTH) {

        plot->setPredictionPointX(copy.replace(",", ".").toDouble());

    } else if (y_axis_plot_feature == FeatureType::PETAL_WIDTH) {

        plot->setPredictionPointY(copy.replace(",", ".").toDouble());

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

        emit startPrediction();

    }


}


void MainWindow::on_featuresComboBox_currentTextChanged(const QString &features) {

    //This function disables checkBoxes for features, selected in featuresComboBox, in
    //checked state, so user won't be able to start algorythm
    //without providing features, necessary for building plot

    //We make all CheckBoxes active, in case some of them were
    //previously disabled by this function
    ui->sepalLengthCheckBox->setEnabled(true);
    ui->sepalWidthCheckBox->setEnabled(true);
    ui->petalLengthCheckBox->setEnabled(true);
    ui->petalWidthCheckBox->setEnabled(true);

    if (features == "Sepal length - Sepal width") {

        emit setPlotBuildingFeatures(FeatureType::SEPAL_LENGTH, FeatureType::SEPAL_WIDTH);
        ui->sepalLengthCheckBox->setCheckState(Qt::Checked);
        ui->sepalWidthCheckBox->setCheckState(Qt::Checked);
        ui->sepalLengthCheckBox->setEnabled(false);
        ui->sepalWidthCheckBox->setEnabled(false);
        x_axis_plot_feature = FeatureType::SEPAL_LENGTH;
        y_axis_plot_feature = FeatureType::SEPAL_WIDTH;
        plot->setAxesTexts(QStringLiteral("Sepal length"), QStringLiteral("Sepal width"));
        plot->setPredictionPointValues(ui->sepalLengthLineEdit->text().toFloat(), ui->sepalWidthLineEdit->text().toFloat());

    } else if (features == "Sepal length - Petal length") {

        emit setPlotBuildingFeatures(FeatureType::SEPAL_LENGTH, FeatureType::PETAL_LENGTH);
        ui->sepalLengthCheckBox->setCheckState(Qt::Checked);
        ui->petalLengthCheckBox->setCheckState(Qt::Checked);
        ui->sepalLengthCheckBox->setEnabled(false);
        ui->petalLengthCheckBox->setEnabled(false);
        x_axis_plot_feature = FeatureType::SEPAL_LENGTH;
        y_axis_plot_feature = FeatureType::PETAL_LENGTH;
        plot->setAxesTexts(QStringLiteral("Sepal length"), QStringLiteral("Petal length"));
        plot->setPredictionPointValues(ui->sepalLengthLineEdit->text().toFloat(), ui->petalLengthLineEdit->text().toFloat());

    } else if (features == "Sepal length - Petal width") {

        emit setPlotBuildingFeatures(FeatureType::SEPAL_LENGTH, FeatureType::PETAL_WIDTH);
        ui->sepalLengthCheckBox->setCheckState(Qt::Checked);
        ui->petalWidthCheckBox->setCheckState(Qt::Checked);
        ui->sepalLengthCheckBox->setEnabled(false);
        ui->petalWidthCheckBox->setEnabled(false);
        x_axis_plot_feature = FeatureType::SEPAL_LENGTH;
        y_axis_plot_feature = FeatureType::PETAL_WIDTH;
        plot->setAxesTexts(QStringLiteral("Sepal length"), QStringLiteral("Petal width"));
        plot->setPredictionPointValues(ui->sepalLengthLineEdit->text().toFloat(), ui->petalWidthLineEdit->text().toFloat());

    } else if (features == "Sepal width - Petal length") {

        emit setPlotBuildingFeatures(FeatureType::SEPAL_WIDTH, FeatureType::PETAL_LENGTH);
        ui->sepalWidthCheckBox->setCheckState(Qt::Checked);
        ui->petalLengthCheckBox->setCheckState(Qt::Checked);
        ui->sepalWidthCheckBox->setEnabled(false);
        ui->petalLengthCheckBox->setEnabled(false);
        x_axis_plot_feature = FeatureType::SEPAL_WIDTH;
        y_axis_plot_feature = FeatureType::PETAL_LENGTH;
        plot->setAxesTexts(QStringLiteral("Sepal width"), QStringLiteral("Petal length"));
        plot->setPredictionPointValues(ui->sepalWidthLineEdit->text().toFloat(), ui->petalLengthLineEdit->text().toFloat());

    } else if (features == "Sepal width - Petal width") {

        emit setPlotBuildingFeatures(FeatureType::SEPAL_WIDTH, FeatureType::PETAL_WIDTH);
        ui->sepalWidthCheckBox->setCheckState(Qt::Checked);
        ui->petalWidthCheckBox->setCheckState(Qt::Checked);
        ui->sepalWidthCheckBox->setEnabled(false);
        ui->petalWidthCheckBox->setEnabled(false);
        x_axis_plot_feature = FeatureType::SEPAL_WIDTH;
        y_axis_plot_feature = FeatureType::PETAL_WIDTH;
        plot->setAxesTexts(QStringLiteral("Sepal width"), QStringLiteral("Petal width"));
        plot->setPredictionPointValues(ui->sepalWidthLineEdit->text().toFloat(), ui->petalWidthLineEdit->text().toFloat());

    } else if (features == "Petal length - Petal width") {

        emit setPlotBuildingFeatures(FeatureType::PETAL_LENGTH, FeatureType::PETAL_WIDTH);
        ui->petalLengthCheckBox->setCheckState(Qt::Checked);
        ui->petalWidthCheckBox->setCheckState(Qt::Checked);
        ui->petalLengthCheckBox->setEnabled(false);
        ui->petalWidthCheckBox->setEnabled(false);
        x_axis_plot_feature = FeatureType::PETAL_LENGTH;
        y_axis_plot_feature = FeatureType::PETAL_WIDTH;
        plot->setAxesTexts(QStringLiteral("Petal length"), QStringLiteral("Petal width"));
        plot->setPredictionPointValues(ui->petalLengthLineEdit->text().toFloat(), ui->petalWidthLineEdit->text().toFloat());

    }

}

void MainWindow::on_sepalLengthCheckBox_stateChanged(int arg1) {

    if (arg1 == 0) {

        emit removePredictionFeature(FeatureType::SEPAL_LENGTH);

    } else if (arg1 == 2) {

        emit addPredictionFeature(FeatureType::SEPAL_LENGTH);

    }

}


void MainWindow::on_sepalWidthCheckBox_stateChanged(int arg1) {

    if (arg1 == 0) {

        emit removePredictionFeature(FeatureType::SEPAL_WIDTH);

    } else if (arg1 == 2) {

        emit addPredictionFeature(FeatureType::SEPAL_WIDTH);

    }

}


void MainWindow::on_petalLengthCheckBox_stateChanged(int arg1) {

    if (arg1 == 0) {

        emit removePredictionFeature(FeatureType::PETAL_LENGTH);

    } else if (arg1 == 2) {

        emit addPredictionFeature(FeatureType::PETAL_LENGTH);

    }

}


void MainWindow::on_petalWidthCheckBox_stateChanged(int arg1) {

    if (arg1 == 0) {

        emit removePredictionFeature(FeatureType::PETAL_WIDTH);

    } else if (arg1 == 2) {

        emit addPredictionFeature(FeatureType::PETAL_WIDTH);

    }

}

