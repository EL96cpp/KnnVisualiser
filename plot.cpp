#include "plot.h"

Plot::Plot(QObject *parent) : QObject{parent},
                              scene(new QGraphicsScene(this)),
                              main_rect(new QGraphicsRectItem(0, 0, 600, 600)),
                              x_axis(new QGraphicsLineItem(50, 50, 50, 550)),
                              y_axis(new QGraphicsLineItem(50, 550, 550, 550)),
                              main_rect_brush(QColor(255, 255, 255), Qt::SolidPattern),
                              big_axis_pen(QColor(0, 0, 0), 1.5, Qt::SolidLine),
                              small_axis_pen(QColor(0, 0, 0), 1.0, Qt::SolidLine) {

    main_rect->setBrush(main_rect_brush);

    x_axis->setPen(big_axis_pen);
    y_axis->setPen(big_axis_pen);

    scene->addItem(main_rect);
    scene->addItem(x_axis);
    scene->addItem(y_axis);

}

void Plot::setGraphicsScene(QGraphicsView *graphics_view) {

    graphics_view->setScene(scene);

}
