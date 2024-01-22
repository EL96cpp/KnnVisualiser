#include "plot.h"

Plot::Plot(QObject *parent) : QObject{parent},
                              scene(new QGraphicsScene(this)),
                              //dataset_plot_points(150, new QGraphicsEllipseItem()),
                              main_rect(new QGraphicsRectItem(0, 0, 600, 600)),
                              x_axis(new QGraphicsLineItem(50, 50, 50, 550)),
                              y_axis(new QGraphicsLineItem(50, 550, 550, 550)),
                              x_axis_text(new QGraphicsTextItem),
                              y_axis_text(new QGraphicsTextItem),
                              main_rect_brush(QColor(255, 255, 255, 120), Qt::SolidPattern),
                              big_axis_pen(QColor(0, 0, 0), 1.5, Qt::SolidLine),
                              small_axis_pen(QColor(0, 0, 0), 1.0, Qt::SolidLine) {

    main_rect->setBrush(main_rect_brush);

    x_axis->setPen(big_axis_pen);
    y_axis->setPen(big_axis_pen);

    x_axis_text->setPos(300, 555);
    y_axis_text->setPos(20, 300);
    y_axis_text->setRotation(-90);

    scene->addItem(main_rect);
    scene->addItem(x_axis);
    scene->addItem(y_axis);
    scene->addItem(x_axis_text);
    scene->addItem(y_axis_text);

    for (int i = 0; i < 150; ++i) {

        dataset_plot_points.push_back(new QGraphicsEllipseItem());

    }

    sepal_length_cell_size = 500 / (sepal_length_max - sepal_length_min);
    sepal_width_cell_size = 500 / (sepal_width_max - sepal_width_min);
    petal_length_cell_size = 500 / (petal_length_max - petal_length_min);
    petal_width_cell_size = 500 / (petal_width_max - petal_width_min);

    qDebug() << "cell sizes " << sepal_length_cell_size << " " << sepal_width_cell_size << " " << petal_length_cell_size << " " << petal_width_cell_size;

}

void Plot::setGraphicsScene(QGraphicsView *graphics_view) {

    graphics_view->setScene(scene);

}


void Plot::setAxesTexts(const QString &x_axis_text, const QString &y_axis_text) {

    this->x_axis_text->setPlainText(x_axis_text);
    this->y_axis_text->setPlainText(y_axis_text);
    this->x_axis_text->setPos(300 - this->x_axis_text->boundingRect().width()/2, 555);
    this->y_axis_text->setPos(20, 300 + this->y_axis_text->boundingRect().width()/2);

    updateDatasetPlot();

}

void Plot::setDataset(const QVector<IrisData> &dataset) {

    this->dataset = dataset;

}

void Plot::updateDatasetPlot() {

    for (int i = 0; i < dataset_plot_points.size(); ++i) {

        double x_value = dataset[i].getFeatureValue(x_axis_text->toPlainText());
        double y_value = dataset[i].getFeatureValue(y_axis_text->toPlainText());
        IrisType iris_type = dataset[i].getType();

        if (x_axis_text->toPlainText() == "Sepal length") {


            if (y_axis_text->toPlainText() == "Sepal width") {

                dataset_plot_points[i]->setRect(50 + (x_value - sepal_length_min)*sepal_length_cell_size + plot_point_size/2,
                                                550 - (y_value - sepal_width_min)*sepal_width_cell_size - plot_point_size/2,
                                                plot_point_size, plot_point_size);
                dataset_plot_points[i]->setPen(big_axis_pen);

            } else if (y_axis_text->toPlainText() == "Petal length") {

                dataset_plot_points[i]->setRect(50 + (x_value - sepal_length_min)*sepal_length_cell_size + plot_point_size/2,
                                                550 - (y_value - petal_length_min)*petal_length_cell_size - plot_point_size/2,
                                                plot_point_size, plot_point_size);
                dataset_plot_points[i]->setPen(big_axis_pen);

            } else if (y_axis_text->toPlainText() == "Petal width") {

                dataset_plot_points[i]->setRect(50 + (x_value - sepal_length_min)*sepal_length_cell_size + plot_point_size/2,
                                                550 - (y_value - petal_width_min)*petal_width_cell_size - plot_point_size/2,
                                                plot_point_size, plot_point_size);
                dataset_plot_points[i]->setPen(big_axis_pen);

            }


        } else if (x_axis_text->toPlainText() == "Sepal width") {


            if (y_axis_text->toPlainText() == "Petal length") {

                dataset_plot_points[i]->setRect(50 + (x_value - sepal_width_min)*sepal_width_cell_size + plot_point_size/2,
                                                550 - (y_value - petal_length_min)*petal_length_cell_size - plot_point_size/2,
                                                plot_point_size, plot_point_size);
                dataset_plot_points[i]->setPen(big_axis_pen);

            } else if (y_axis_text->toPlainText() == "Petal width") {

                dataset_plot_points[i]->setRect(50 + (x_value - sepal_width_min)*sepal_width_cell_size + plot_point_size/2,
                                                550 - (y_value - petal_width_min)*petal_width_cell_size - plot_point_size/2,
                                                plot_point_size, plot_point_size);
                dataset_plot_points[i]->setPen(big_axis_pen);

            }


        } else if (x_axis_text->toPlainText() == "Petal length") {


            if (y_axis_text->toPlainText() == "Petal width") {

                dataset_plot_points[i]->setRect(50 + (x_value - petal_length_min)*petal_length_cell_size + plot_point_size/2,
                                                550 - (y_value - petal_width_min)*petal_width_cell_size - plot_point_size/2,
                                                plot_point_size, plot_point_size);
                dataset_plot_points[i]->setPen(big_axis_pen);

            }


        }

        if (iris_type == IrisType::SETOSA) {

            dataset_plot_points[i]->setBrush(QColor(239, 28, 28));

        } else if (iris_type == IrisType::VERSICOLOR) {

            dataset_plot_points[i]->setBrush(QColor(85, 234, 0));

        } else if (iris_type == IrisType::VIRGINICA) {

            dataset_plot_points[i]->setBrush(QColor(0, 92, 255));

        }

        scene->addItem(dataset_plot_points[i]);

    }

}
