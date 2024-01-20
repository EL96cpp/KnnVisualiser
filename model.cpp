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

void Model::startBuildingPlot() {

    emit setIsLearning(true);

    accuracy_results.clear();
    prepareCrossValidationData();
    setDistancesVector();

    QVector<double> first_group_accuracies = getCvGroupAccuracies(0);
    QVector<double> second_group_accuracies = getCvGroupAccuracies(1);
    QVector<double> third_group_accuracies = getCvGroupAccuracies(2);
    QVector<double> fourth_group_accuracies = getCvGroupAccuracies(3);
    QVector<double> fifth_group_accuracies = getCvGroupAccuracies(4);

    for (int i = 0; i < first_group_accuracies.size(); ++i) {

        accuracy_results.push_back((first_group_accuracies[i] + second_group_accuracies[i] +
                                    third_group_accuracies[i] + fourth_group_accuracies[i] +
                                    fifth_group_accuracies[i]) / 5.0);

    }

    for (int i = 0; i < accuracy_results.size(); ++i) {

        qDebug() << accuracy_results[i];

    }

    qDebug() << "===================";

    emit setIsLearning(false);

}

void Model::startPredicting() {



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

void Model::onSetFeatureIndexes(const int &first_feature_index, const int &second_feature_index) {

    this->first_feature_index = first_feature_index;
    this->second_feature_index = second_feature_index;

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
        int id = 1;

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

void Model::prepareCrossValidationData() {

    //In dataset first 50 values are Iris-setosa, next 50 - Iris-versicolor, last 50 - Iris-virginica
    //It means we can create vector of indexes, shuffle indexes in each group of 50 values
    //and consistently put 10 values from each of three groups in cross-validation vectors
    //to get 5 cross-validation vectors, 30 values in each

    QVector<int> cv_indexes;

    for (int i = 0; i < 150; ++i) {

        cv_indexes.push_back(i);

    }

    //std::time(0) - time in seconds since the Unix epoch
    std::srand(std::time(0));

    for (int i = 0; i <= 100; i += 50) {

        std::random_shuffle(cv_indexes.begin() + i, cv_indexes.begin() + (i + 50));

    }

    cv_data.clear();

    for (int i = 0; i < 5; ++i) {

        QVector<IrisData> cv_group;

        for (int j = 0; j < 10; ++j) {

            cv_group.push_back(dataset[cv_indexes[i*10 + j]]);
            cv_group.push_back(dataset[cv_indexes[i*10 + 50 + j]]);
            cv_group.push_back(dataset[cv_indexes[i*10 + 100 + j]]);

        }

        cv_data.push_back(cv_group);

    }

}

void Model::setDistancesVector() {

    distances.clear();

    for (int i = 0; i < dataset.size(); ++i) {

        for (int j = i+1; j < dataset.size(); ++j) {

            distances.pushBack(DistanceData(dataset[i].getId(), dataset[j].getId(), calculateDistance(dataset[i], dataset[j])));

        }

    }

}

double Model::calculateDistance(const IrisData &first, const IrisData &second) {

    double sum = std::pow(std::abs(first.getFeatureByIndex(first_feature_index) - second.getFeatureByIndex(first_feature_index)), minkowski_metric_param) +
                 std::pow(std::abs(first.getFeatureByIndex(second_feature_index) - second.getFeatureByIndex(second_feature_index)), minkowski_metric_param);
    return std::pow(sum, 1.f/minkowski_metric_param);

}

QVector<double> Model::getCvGroupAccuracies(const int &group_index) {

    QVector<int> cv_group_ids;

    for (int i = 0; i < cv_data[group_index].size(); ++i) {

        cv_group_ids.push_back(cv_data[group_index][i].getId());

    }

    QVector<QVector<bool>> prediction_results;

    for (int i = 0; i < cv_data[group_index].size(); ++i) {

        int current_id = cv_data[group_index][i].getId();
        IrisType current_type = cv_data[group_index][i].getType();
        QVector<DistanceData> current_distances = distances.getDecreasingSortedDistances(current_id, cv_group_ids);

        double first_type_score = 0.0, second_type_score = 0.0, third_type_score = 0.0;

        //Value with index i will store correctness of prediction for i+1 neighbours
        QVector<bool> current_predictions;

        for (int j = 0; j < number_of_neighbours; ++j) {

            int pair_id = current_distances[j].getPairForId(current_id);
            IrisType pair_type = dataset[pair_id-1].getType();

            switch(pair_type) {

            case IrisType::SETOSA:
                first_type_score += kernel(current_distances[j].getDistance()/window_width);
                break;

            case IrisType::VERSICOLOR:
                second_type_score += kernel(current_distances[j].getDistance()/window_width);
                break;

            case IrisType::VIRGINICA:
                third_type_score += kernel(current_distances[j].getDistance()/window_width);
                break;

            }

            IrisType predicted_type = predictType(first_type_score, second_type_score, third_type_score);

            current_predictions.push_back(current_type == predicted_type);

        }

        prediction_results.push_back(current_predictions);

    }

    QVector<double> cv_group_accuracies;

    for (int i = 0; i < number_of_neighbours; ++i) {

        double correct_predictions = 0.0;

        for (int j = 0; j < prediction_results.size(); ++j) {

            correct_predictions += prediction_results[j][i];

        }

        cv_group_accuracies.push_back(correct_predictions/prediction_results.size());

    }

    return cv_group_accuracies;

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
