#include <QtGui>
#include <QLabel>
#include <QGridLayout>
#include <QPrintDialog>
#include <QPrinter>
#include <qwt.h>
#include <qwt_scale_engine.h>
#include "pxplot.h"
#include "plot.h"
#include "curve.h"

Plot::Plot(QWidget *parent): QWidget(parent)
{
    px = new PxPlot();

    zoomer = new QwtPlotZoomer(QwtPlot::xBottom, QwtPlot::yLeft, px->canvas());
    zoomer->setRubberBand(QwtPicker::RectRubberBand);
//    zoomer->setSelectionFlags(
//                QwtPicker::DragSelection | QwtPicker::CornerToCorner);

//      zoomer->setTrackerMode(QwtPicker::AlwaysOn);
//    zoomer->setTrackerMode(QwtPicker::ActiveOnly);
//    zoomer->setRubberBandPen(QColor(Qt::green));
//    zoomer->setTrackerPen(QColor(Qt::white));

    // RightButton: previous zoom
    // Ctrl+RightButton: reset zoom

    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
                            Qt::RightButton, Qt::ControlModifier);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
                            Qt::RightButton);
    zoomer->setEnabled(true);
//    zoomer->zoom(0);

    panner = new QwtPlotPanner(px->canvas());
    panner->setMouseButton(Qt::MidButton);

//    d_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
//        QwtPicker::PointSelection | QwtPicker::DragSelection,
//        QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
//        d_plot->canvas());
//    d_picker->setRubberBandPen(QColor(Qt::green));
//    d_picker->setRubberBand(QwtPicker::CrossRubberBand);
//    d_picker->setTrackerPen(QColor(Qt::white));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(px,0,0,1,-1);
    label = new QLabel(tr("LF"));
    layout->addWidget(label,1,1);

    setLayout(layout);



//    connect(d_picker, SIGNAL(moved(const QPoint &)),
//            SLOT(moved(const QPoint &)));
//    connect(d_picker, SIGNAL(selected(const QwtPolygon &)),
//           SLOT(selected(const QwtPolygon &)));

}

bool Plot::addDataFile(const QString& name, const QString & format)
{
    bool ok;
    ok = px->setData(name,format);
    if (ok) {
        zoomer->setZoomBase();
    }
    return(ok);
}

bool Plot::removeCurve(Curve *c)
{
    bool ok;
    ok = px->removeCurve(c);
    return(ok);
}

QList<Curve*> Plot::curveList()
{
    return(px->curveList());
}

void Plot::fexport()
{
    // change from gui theme colours to black axes / labels
    QPalette pgui, pfile;
    pgui = this->palette();
    pfile = pgui;
    pfile.setColor(QPalette::Text,QColor(Qt::black));
    pfile.setColor(QPalette::WindowText,QColor(Qt::black));
    this->setPalette(pfile);

    QwtPlotRenderer rx;
    rx.setDiscardFlag(QwtPlotRenderer::DiscardBackground);
    rx.setDiscardFlag(QwtPlotRenderer::DiscardCanvasFrame);

    // FIXME: set default filename more intelligently
    QString fn = "";
//    fn += px->title().text(); this is set to space; use last filename
    if (fn.isEmpty())
    {
        fn = "pxv";
    }


    // FIXME: set size, resolution as params of exportTo, from options
    // this is roughly half of an A4; RSC double width
    rx.exportTo(this->px,fn,QSizeF(170,113),300);

    // restore colours
    this->setPalette(pgui);
}


void Plot::print()
{
    QPrinter printer;

    QPrintDialog dia(&printer);
    if (dia.exec())
    {
        QwtPlotRenderer pf;
        pf.setDiscardFlag(QwtPlotRenderer::DiscardNone,true);
        if (printer.colorMode() == QPrinter::GrayScale)
        {
            pf.setDiscardFlag(QwtPlotRenderer::DiscardBackground,true);
        }
        pf.renderTo(px,printer);
    }
}

void Plot::zoomToFit()
{
    QRectF bounds = px->boundingRect();
    if (bounds.isValid())
    {
        QwtLinearScaleEngine scaler;
        double x1, x2, step;
        x1 = bounds.left();
        x2 = bounds.right();
        scaler.autoScale(20,x1,x2,step);
        bounds.setLeft(x1);
        bounds.setRight(x2);
        x1 = bounds.top();
        x2 = bounds.bottom();
        scaler.autoScale(20,x1,x2,step);
        bounds.setTop(x1);
        bounds.setBottom(x2);
        zoomer->zoom(bounds);
    }
}
