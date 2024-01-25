#ifndef PLOT_H
#define PLOT_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
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
    void prepareAxesMarkingValues();
    void setXAxisMarkingValues(const QString& feature);
    void setYAxisMarkingValues(const QString& feature);
    void onSetSepalLength(const float& sepal_length);
    void onSetSepalWidth(const float& sepal_width);
    void onSetPetalLength(const float& petal_length);
    void onSetPetalWidth(const float& petal_width);

    void setDataset(const QVector<IrisData>& dataset);

public slots:
    void setPredictionPlotPointColor(const QColor& color);

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
    QGraphicsPolygonItem* x_axis_arrow;
    QGraphicsPolygonItem* y_axis_arrow;

    QGraphicsTextItem* setosa_legend_text;
    QGraphicsTextItem* versicolor_legend_text;
    QGraphicsTextItem* virginica_legend_text;
    QGraphicsRectItem* setosa_legend_rect;
    QGraphicsRectItem* versicolor_legend_rect;
    QGraphicsRectItem* virginica_legend_rect;

    QVector<QGraphicsLineItem*> sepal_length_x_axis_lines;
    QVector<QGraphicsLineItem*> sepal_width_x_axis_lines;
    QVector<QGraphicsLineItem*> petal_length_x_axis_lines;

    QVector<QGraphicsTextItem*> sepal_length_x_axis_texts;
    QVector<QGraphicsTextItem*> sepal_width_x_axis_texts;
    QVector<QGraphicsTextItem*> petal_length_x_axis_texts;

    QVector<QGraphicsLineItem*> sepal_width_y_axis_lines;
    QVector<QGraphicsLineItem*> petal_length_y_axis_lines;
    QVector<QGraphicsLineItem*> petal_width_y_axis_lines;

    QVector<QGraphicsTextItem*> sepal_width_y_axis_texts;
    QVector<QGraphicsTextItem*> petal_length_y_axis_texts;
    QVector<QGraphicsTextItem*> petal_width_y_axis_texts;

    QBrush main_rect_brush;
    QPen big_axis_pen;
    QPen small_axis_pen;
    QPen points_outline_pen;

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
    int plot_prediction_point_size = 12;

    float prediction_point_x = 0.0;
    float prediction_point_y = 0.0;

    float prediction_sepal_length = 0.0;
    float prediction_sepal_width = 0.0;
    float prediction_petal_length = 0.0;
    float prediction_petal_width = 0.0;

    float sepal_length_min = 4.0;
    float sepal_length_max = 8.0;
    float sepal_width_min = 1.5;
    float sepal_width_max = 5.0;
    float petal_length_min = 0.5;
    float petal_length_max = 7.0;
    float petal_width_min = 0.0;
    float petal_width_max = 3.5;

};

#endif // PLOT_H
