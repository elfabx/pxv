#ifndef PXPLOT_H
#define PXPLOT_H

#include <QWidget>
#include <QRectF>
#include <QVariant>
#include <qwt_plot.h>

class Curve;

class PxPlot: public QwtPlot
{
    Q_OBJECT

public:
    PxPlot(QWidget *parent=nullptr);
    QRectF boundingRect();
    QList<Curve*> curveList();
    bool removeCurve(Curve *c);

public slots:
    bool setData(const QString& name, const QString & filter);
    void labelClick(QVariant qv, bool on, int index);

private:
    QList<Curve*> curves;
};

#endif

