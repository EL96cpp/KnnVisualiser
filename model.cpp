#include "model.h"

# define PI 3.14159265358979323846

#include <math.h>

// Kernel functions

double Rectangular(const double& x) {

    return 0.5 * (std::abs(x) <= 1);

}

double Triangle(const double& x) {

    return (1 - std::abs(x)) * (std::abs(x) <= 1);

}

double Epanchenkov(const double& x) {

    return 0.75 * (1 - std::pow(x, 2)) * (std::abs(x) <= 1);

}

double Biquadratic(const double& x) {

    return 0.9375 * std::pow(1 - std::pow(x, 2), 2) * (std::abs(x) <= 1);

}

double Gaussian(const double& x) {

    return (1/std::sqrt(2 * PI)) * std::exp(-2 * std::pow(x, 2));

}

Model::Model(QObject *parent)
    : QObject{parent}, is_learning(false) {

    readDataFromCsv();

}

QVector<IrisData> Model::getDataset() {

    return dataset;

}


void Model::onStartPrediction() {

    emit setIsLearning(true);

    setTrainTestDatasets();

    QVector<DistanceData> distances;
    IrisData prediction_iris_data(sepal_length, sepal_width, petal_length, petal_width);

    for (int i = 0; i < dataset.size(); ++i) {

        distances.push_back(DistanceData(calculateDistance(prediction_iris_data, dataset[i]), dataset[i].getType()));

    }

    std::sort(distances.begin(), distances.end());

    double setosa_score = 0.0, versicolor_score = 0.0, virginica_score = 0.0;

    for (int i = 0; i < number_of_neighbours; ++i) {

        if (distances[i].getIrisType() == IrisType::SETOSA) {

            setosa_score += kernel(distances[i].getDistance()/window_width);

        } else if (distances[i].getIrisType() == IrisType::VERSICOLOR) {

            versicolor_score += kernel(distances[i].getDistance()/window_width);

        } else if (distances[i].getIrisType() == IrisType::VIRGINICA) {

            virginica_score += kernel(distances[i].getDistance()/window_width);

        }

    }

    IrisType predicted_type = predictType(setosa_score, versicolor_score, virginica_score);

    //Debug
    switch (predicted_type) {

    case IrisType::SETOSA:
        qDebug() << "setosa predicted!";
        break;

    case IrisType::VERSICOLOR:
        qDebug() << "versicolor predicted!";
        break;

    case IrisType::VIRGINICA:
        qDebug() << "virginica predicted!";
        break;

    }


    double model_accuracy = calculateModelAccuracy();
    qDebug() << "Model accuracy " << model_accuracy;


    emit setPredictedIrisType(predicted_type);
    emit setIsLearning(false);

}

void Model::onSetKernelType(const QString &kernel_type) {

    if (kernel_type == "Прямоугольное") {

        kernel = Rectangular;

    } else if (kernel_type == "Треугольное") {

        kernel = Triangle;

    } else if (kernel_type == "Ядро Епанченкова") {

        kernel = Epanchenkov;

    } else if (kernel_type == "Биквадратное") {

        kernel = Biquadratic;

    } else if (kernel_type == "Гауссовское") {

        kernel = Gaussian;

    }

}

void Model::onSetWindowWidth(const double &window_width) {

    this->window_width = window_width;

}

void Model::onSetMinkowskiMetric(const int &minkowski_metric_param) {

    this->minkowski_metric_param = minkowski_metric_param;

}

void Model::onSetNumberOfNeighbours(const int &number_of_neighbours) {

    this->number_of_neighbours = number_of_neighbours;

}

void Model::onSetPlotBuildingFeatures(const FeatureType &first_feature, const FeatureType &second_feature) {

    plot_building_features.clear();
    plot_building_features.push_back(first_feature);
    plot_building_features.push_back(second_feature);

}

void Model::onAddPredictionFeature(const FeatureType &feature) {

    qDebug() << "Added feature ";
    prediction_featrues.push_back(feature);

}

void Model::onRemovePredictionFeature(const FeatureType &feature) {

    qDebug() << "trying remove feature ";
    qDebug() << "removed feature " << prediction_featrues.removeIf([feature](const FeatureType& f){ return f == feature; });

}

void Model::onSetSepalLength(const double &sepal_length) {

    this->sepal_length = sepal_length;

}

void Model::onSetSepalWidth(const double &sepal_width) {

    this->sepal_width = sepal_width;

}

void Model::onSetPetalLength(const double &petal_length) {

    this->petal_length = petal_length;

}

void Model::onSetPetalWidth(const double &petal_width) {

    this->petal_width = petal_width;

}

void Model::readDataFromCsv() {

    QFile dataset_file("../Data/iris_csv.csv");
    if (!dataset_file.open(QIODevice::ReadOnly)) {

        qDebug() << "Csv file error!";
        emit openCsvFileError();

    } else {

        QTextStream in(&dataset_file);

        //Read first line with headers, so we can work with actual data in while loop
        in.readLine();

        //Id value for IrisData objects
        int id = 0;

        while (!in.atEnd()) {

            QString line = in.readLine();
            QStringList string_list = line.split(",");
            QString iris_type_string = string_list[4];
            IrisType iris_type;

            if (iris_type_string.compare("Iris-setosa") == 0) {

                iris_type = IrisType::SETOSA;

            } else if (iris_type_string.compare("Iris-versicolor") == 0) {

                iris_type = IrisType::VERSICOLOR;

            } else if (iris_type_string.compare("Iris-virginica") == 0) {

                iris_type = IrisType::VIRGINICA;

            }

            dataset.emplaceBack(id, string_list[0].toDouble(), string_list[1].toDouble(),
                                string_list[2].toDouble(), string_list[3].toDouble(), iris_type);

            ++id;
            line.clear();
            string_list.clear();

        }

    }

}

void Model::setTrainTestDatasets() {

    QVector<int> dataset_ids;

    for (int i = 0; i < dataset.size(); ++i) {

        dataset_ids.push_back(i);

    }

    std::srand(std::time(0));

    std::random_shuffle(dataset_ids.begin(), dataset_ids.begin() + 50);
    std::random_shuffle(dataset_ids.begin() + 50, dataset_ids.begin() + 100);
    std::random_shuffle(dataset_ids.begin() + 100, dataset_ids.end());

    for (int i = 0; i < 10; ++i) {

        train_dataset.push_back(dataset[dataset_ids[i]]);
        train_dataset.push_back(dataset[dataset_ids[50 + i]]);
        train_dataset.push_back(dataset[dataset_ids[100 + i]]);

    }

    for (int i = 10; i < 50; ++i) {

        test_dataset.push_back(dataset[dataset_ids[i]]);
        test_dataset.push_back(dataset[dataset_ids[50 + i]]);
        test_dataset.push_back(dataset[dataset_ids[100 + i]]);

    }

}


double Model::calculateModelAccuracy() {

    QVector<int> test_dataset_ids;

    for (int i = 0; i < test_dataset_ids.size(); ++i) {

        test_dataset_ids.push_back(test_dataset[i].getId());

    }

    float correct_predictions_counter = 0.0;

    for (int i = 0; i < test_dataset.size(); ++i) {

        QVector<DistanceData> current_distances;

        for (int j = 0; j < train_dataset.size(); ++j) {

            current_distances.push_back(DistanceData(calculateDistance(test_dataset[i], train_dataset[j]), train_dataset[j].getType()));

        }

        std::sort(current_distances.begin(), current_distances.end());

        double setosa_score = 0.0, versicolor_score = 0.0, virginica_score = 0.0;

        for (int k = 0; k < number_of_neighbours; ++k) {

            if (current_distances[k].getIrisType() == IrisType::SETOSA) {

                setosa_score += kernel(current_distances[k].getDistance()/window_width);

            } else if (current_distances[k].getIrisType() == IrisType::VERSICOLOR) {

                versicolor_score += kernel(current_distances[k].getDistance()/window_width);

            } else if (current_distances[k].getIrisType() == IrisType::VIRGINICA) {

                virginica_score += kernel(current_distances[k].getDistance()/window_width);

            }

        }

        if (predictType(setosa_score, versicolor_score, virginica_score) == test_dataset[i].getType()) {

            correct_predictions_counter += 1.0;

        }

    }

    return correct_predictions_counter/test_dataset.size();

}


double Model::calculateDistance(const IrisData& prediction_iris_data, const IrisData& dataset_iris_data) {

    double sum = 0.0;

    for (auto& feature : prediction_featrues) {

        //qDebug() << "inside calculate distance " << prediction_iris_data.getId() << " " << dataset_iris_data.getId();
        sum += std::pow(std::abs(prediction_iris_data.getFeatureValue(feature) - dataset_iris_data.getFeatureValue(feature)), minkowski_metric_param);

    }

    return std::pow(sum, 1.0/minkowski_metric_param);

}


IrisType Model::predictType(const double &setosa_score, const double &versicolor_score, const double &virginica_score) {

    if (setosa_score > versicolor_score) {

        if (setosa_score > virginica_score) {

            return IrisType::SETOSA;

        } else {

            return IrisType::VIRGINICA;

        }

    } else {

        if (versicolor_score > virginica_score) {

            return IrisType::VERSICOLOR;

        } else {

            return IrisType::VIRGINICA;

        }

    }

}
