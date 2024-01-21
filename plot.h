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

    void setDataset(const QVector<IrisData>& dataset);

private:
    void updateDatasetPlot();

private:
    QVector<IrisData> dataset;
    QVector<QGraphicsEllipseItem*> dataset_plot_points;
    QGraphicsScene* scene;
    QGraphicsRectItem* main_rect;
    QGraphicsLineItem* x_axis;
    QGraphicsLineItem* y_axis;
    QGraphicsTextItem* x_axis_text;
    QGraphicsTextItem* y_axis_text;
    QBrush main_rect_brush;
    QPen big_axis_pen;
    QPen small_axis_pen;

};

#endif // PLOT_H
