#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent} {

    readDataFromCsv();

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

        qDebug() << dataset.size();

    }

}
