#ifndef PLOT_H
#define PLOT_H

#include <QGridLayout>
#include <QWidget>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_renderer.h>

// This class defines the complete plot area with attached controls

class QwtPlotZoomer;
class QLabel;
// class QwtPlotPicker;
// class QwtPlotPanner;
class PxPlot; // the actual graph
class Curve;

class Plot : public QWidget
{
    Q_OBJECT

public:
    Plot(QWidget *parent = nullptr);
    bool addDataFile(const QString & name, const QString & format);
    QList<Curve*> curveList();
    bool removeCurve(Curve* c);
    

public slots:
//    void moved(const QPoint &);
    void fexport();
    void print();
//    void exportSVG();
//    void enableZoomMode(bool);
    void zoomToFit();

private:
    PxPlot *px;

    QwtPlotZoomer *zoomer;
    QLabel *label;
//    QwtPlotPicker *picker;
    QwtPlotPanner *panner;

};

#endif

