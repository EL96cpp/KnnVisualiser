#include "plot.h"

Plot::Plot(QObject *parent) : QObject{parent},
                              scene(new QGraphicsScene(this)),
                              added_dataset_points(false),
                              main_rect(new QGraphicsRectItem(0, 0, 600, 600)),
                              prediction_plot_point(new QGraphicsEllipseItem),
                              x_axis(new QGraphicsLineItem(50, 50, 50, 550)),
                              y_axis(new QGraphicsLineItem(50, 550, 550, 550)),
                              x_axis_text(new QGraphicsTextItem),
                              y_axis_text(new QGraphicsTextItem),
                              main_rect_brush(QColor(188, 255, 255), Qt::SolidPattern),
                              big_axis_pen(QColor(0, 0, 0), 1.5, Qt::SolidLine),
                              small_axis_pen(QColor(0, 0, 0), 1.0, Qt::SolidLine),
                              points_outline_pen(QColor(0, 63, 65)) {

    main_rect->setBrush(main_rect_brush);
    main_rect->setPen(Qt::NoPen);

    points_outline_pen.setWidth(2);

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

}

void Plot::setGraphicsScene(QGraphicsView *graphics_view) {

    graphics_view->setScene(scene);

}


void Plot::setAxesTexts(const QString &x_axis_text, const QString &y_axis_text) {

    this->x_axis_text->setPlainText(x_axis_text);
    this->y_axis_text->setPlainText(y_axis_text);
    this->x_axis_text->setPos(300 - this->x_axis_text->boundingRect().width()/2, 555);
    this->y_axis_text->setPos(20, 300 + this->y_axis_text->boundingRect().width()/2);

    if (x_axis_text == "Sepal length") {

        x_axis_cell_size = sepal_length_cell_size;
        x_axis_min = sepal_length_min;
        x_axis_max = sepal_length_max;
        x_axis_min = sepal_length_min;

        prediction_point_x = prediction_sepal_length;

    } else if (x_axis_text == "Sepal width") {

        x_axis_cell_size = sepal_width_cell_size;
        x_axis_min = sepal_width_min;
        x_axis_max = sepal_width_max;
        x_axis_min = sepal_width_min;

        prediction_point_x = prediction_sepal_width;

    } else if (x_axis_text == "Petal length") {

        x_axis_cell_size = petal_length_cell_size;
        x_axis_min = petal_length_min;
        x_axis_max = petal_length_max;
        x_axis_min = petal_length_min;

        prediction_point_x = prediction_petal_length;

    }

    if (y_axis_text == "Sepal width") {

        y_axis_cell_size = sepal_width_cell_size;
        y_axis_min = sepal_width_min;
        y_axis_max = sepal_width_max;
        y_axis_min = sepal_width_min;

        prediction_point_y = prediction_sepal_width;

    } else if (y_axis_text == "Petal length") {

        y_axis_cell_size = petal_length_cell_size;
        y_axis_min = petal_length_min;
        y_axis_max = petal_length_max;
        y_axis_min = petal_length_min;

        prediction_point_y = prediction_petal_length;

    } else if (y_axis_text == "Petal width") {

        y_axis_cell_size = petal_width_cell_size;
        y_axis_min = petal_width_min;
        y_axis_max = petal_width_max;
        y_axis_min = petal_width_min;

        prediction_point_y = prediction_petal_width;

    }

    updateDatasetPlot();

}

void Plot::onSetSepalLength(const float &sepal_length) {

    prediction_sepal_length = sepal_length;

    if (x_axis_text->toPlainText() == "Sepal length") {

        prediction_point_x = prediction_sepal_length;
        updateDatasetPlot();

    } else if (y_axis_text->toPlainText() == "Sepal length") {

        prediction_point_y = prediction_sepal_length;
        updateDatasetPlot();

    }

}

void Plot::onSetSepalWidth(const float &sepal_width) {

    prediction_sepal_width = sepal_width;

    if (x_axis_text->toPlainText() == "Sepal width") {

        prediction_point_x = prediction_sepal_width;
        updateDatasetPlot();

    } else if (y_axis_text->toPlainText() == "Sepal width") {

        prediction_point_y = prediction_sepal_width;
        updateDatasetPlot();

    }

}

void Plot::onSetPetalLength(const float &petal_length) {

    prediction_petal_length = petal_length;

    if (x_axis_text->toPlainText() == "Petal length") {

        prediction_point_x = prediction_petal_length;
        updateDatasetPlot();

    } else if (y_axis_text->toPlainText() == "Petal length") {

        prediction_point_y = prediction_petal_length;
        updateDatasetPlot();

    }

}

void Plot::onSetPetalWidth(const float &petal_width) {

    prediction_petal_width = petal_width;

    if (x_axis_text->toPlainText() == "Petal width") {

        prediction_point_x = prediction_petal_width;
        updateDatasetPlot();

    } else if (y_axis_text->toPlainText() == "Petal width") {

        prediction_point_y = prediction_petal_width;
        updateDatasetPlot();

    }

}


void Plot::setDataset(const QVector<IrisData> &dataset) {

    this->dataset = dataset;

}

void Plot::setPredictionPlotPointColor(const QColor &color) {

    prediction_plot_point->setBrush(color);

}

void Plot::updateDatasetPlot() {

    for (int i = 0; i < dataset_plot_points.size(); ++i) {

        double x_value = dataset[i].getFeatureValue(x_axis_text->toPlainText());
        double y_value = dataset[i].getFeatureValue(y_axis_text->toPlainText());
        IrisType iris_type = dataset[i].getType();

        dataset_plot_points[i]->setRect(50 + (x_value - x_axis_min)*x_axis_cell_size + plot_point_size/2,
                                        550 - (y_value - y_axis_min)*y_axis_cell_size - plot_point_size/2,
                                        plot_point_size, plot_point_size);
        dataset_plot_points[i]->setPen(big_axis_pen);

        if (iris_type == IrisType::SETOSA) {

            dataset_plot_points[i]->setBrush(QColor(239, 28, 28));

        } else if (iris_type == IrisType::VERSICOLOR) {

            dataset_plot_points[i]->setBrush(QColor(85, 234, 0));

        } else if (iris_type == IrisType::VIRGINICA) {

            dataset_plot_points[i]->setBrush(QColor(0, 92, 255));

        }

        dataset_plot_points[i]->setPen(points_outline_pen);

    }

    if (!added_dataset_points) {

        for (int i = 0; i < dataset_plot_points.size(); ++i) {

            scene->addItem(dataset_plot_points[i]);

        }

        scene->addItem(prediction_plot_point);

        added_dataset_points = true;

    }

    if (!(prediction_point_x <= x_axis_min || prediction_point_x >= x_axis_max ||
          prediction_point_y <= y_axis_min || prediction_point_y >= y_axis_max)) {

        prediction_plot_point->setVisible(true);

        prediction_plot_point->setBrush(QColor(255, 234, 43));
        prediction_plot_point->setPen(points_outline_pen);
        prediction_plot_point->setRect(50 + (prediction_point_x - x_axis_min)*x_axis_cell_size + plot_point_size/2,
                                       550 - (prediction_point_y - y_axis_min)*y_axis_cell_size - plot_point_size/2,
                                       plot_point_size, plot_point_size);

        qDebug() << "set point visible";

    } else {

        prediction_plot_point->setVisible(false);
        qDebug() << "set point invisible";

    }

}
