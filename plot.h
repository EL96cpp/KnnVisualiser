#ifndef PLOT_H
#define PLOT_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include <QColor>

#include "irisdata.h"

class Plot : public QObject {

    Q_OBJECT
public:
    Plot(QObject *parent = nullptr);

    void setGraphicsScene(QGraphicsView* graphics_view);
    void setAxesTexts(const QString& x_axis_text, const QString& y_axis_text);
    void setPredictionPointValues(const float& x_value, const float& y_value);
    void setPredictionPointX(const float& x_value);
    void setPredictionPointY(const float& y_value);

    void setDataset(const QVector<IrisData>& dataset);

private:
    void updateDatasetPlot();

private:
    QVector<IrisData> dataset;
    QVector<QGraphicsEllipseItem*> dataset_plot_points;
    QGraphicsEllipseItem* prediction_plot_point;
    QGraphicsScene* scene;
    QGraphicsRectItem* main_rect;
    QGraphicsLineItem* x_axis;
    QGraphicsLineItem* y_axis;
    QGraphicsTextItem* x_axis_text;
    QGraphicsTextItem* y_axis_text;
    QBrush main_rect_brush;
    QPen big_axis_pen;
    QPen small_axis_pen;

    bool added_dataset_points;

    int sepal_length_cell_size;
    int sepal_width_cell_size;
    int petal_length_cell_size;
    int petal_width_cell_size;

    int x_axis_cell_size;
    int y_axis_cell_size;
    float x_axis_min;
    float x_axis_max;
    float y_axis_min;
    float y_axis_max;

    int plot_point_size = 8;

    float prediction_point_x;
    float prediction_point_y;

    float sepal_length_min = 4.0;
    float sepal_length_max = 8.0;
    float sepal_width_min = 1.9;
    float sepal_width_max = 5.0;
    float petal_length_min = 0.5;
    float petal_length_max = 7.0;
    float petal_width_min = 0.0;
    float petal_width_max = 3.1;

};

#endif // PLOT_H
