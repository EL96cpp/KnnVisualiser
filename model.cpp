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

void Model::startLearning() {

    emit setIsLearning(true);

    accuracy_results.clear();
    prepareCrossValidationData();
    setDistancesVector();

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
            int iris_type;

            if (iris_type_string.compare("Iris-setosa") == 0) {

                iris_type = 1;

            } else if (iris_type_string.compare("Iris-versicolor") == 0) {

                iris_type = 2;

            } else if (iris_type_string.compare("Iris-virginica") == 0) {

                iris_type = 3;

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

    double sum = std::pow(std::abs(first.getSepalLength() - second.getSepalLength()), minkowski_metric_param) +
                 std::pow(std::abs(first.getSepalWidth() - second.getSepalWidth()), minkowski_metric_param) +
                 std::pow(std::abs(first.getPetalLength() - second.getPetalLength()), minkowski_metric_param) +
                 std::pow(std::abs(first.getPetalWidth() - second.getPetalWidth()), minkowski_metric_param);

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
        int current_type = cv_data[group_index][i].getType();
        QVector<DistanceData> current_distances = distances.getDecreasingSortedDistances(current_id, cv_group_ids);

        double first_type_score = 0.0, second_type_score = 0.0, third_type_score = 0.0;

        //Value with index i will store correctness of prediction for i+1 neighbours
        QVector<bool> current_predictions;

        for (int j = 0; j < max_number_of_neighbours; ++j) {

            int pair_id = current_distances[j].getPairForId(current_id);
            int pair_type = dataset[pair_id-1].getType();

            switch(pair_type) {

            case 1:
                first_type_score += kernel(current_distances[j].getDistance()/window_width);
                break;

            case 2:
                second_type_score += kernel(current_distances[j].getDistance()/window_width);
                break;

            case 3:
                third_type_score += kernel(current_distances[j].getDistance()/window_width);
                break;

            }

            int predicted_type = predictType(first_type_score, second_type_score, third_type_score);

            current_predictions.push_back(current_type == predicted_type);

        }

        prediction_results.push_back(current_predictions);

    }

    QVector<double> cv_group_accuracies;

    for (int i = 0; i < max_number_of_neighbours; ++i) {

        double correct_predictions = 0.0;

        for (int j = 0; j < prediction_results.size(); ++j) {

            correct_predictions += prediction_results[j][i];

        }

        cv_group_accuracies.push_back(correct_predictions/prediction_results.size());

    }

    return cv_group_accuracies;

}


int Model::predictType(const double &first_type_score, const double &second_type_score, const double &third_type_score) {

    if (first_type_score > second_type_score) {

        if (first_type_score > third_type_score) {

            return 1;

        } else {

            return 3;

        }

    } else {

        if (second_type_score > third_type_score) {

            return 2;

        } else {

            return 3;

        }

    }

}
