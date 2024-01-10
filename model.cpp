#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent} {

    readDataFromCsv();
    prepareCrossValidationData();

}

void Model::onSetKernelType(const KernelType &kernel_type) {

    this->kernel_type = kernel_type;

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

            dataset.emplaceBack(string_list[0].toDouble(), string_list[1].toDouble(),
                                string_list[2].toDouble(), string_list[3].toDouble(), iris_type);

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