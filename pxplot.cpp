#include <QtGui>
#include <qwt.h>
#include <qwt_legend.h>
#include <qwt_plot_layout.h>
#include "pxplot.h"
#include "curve.h"
#include "fileformat.h"
#include "xye.h"

static Qt::GlobalColor colorlist[10] = { Qt::red,
                                       Qt::green, Qt::blue, Qt::cyan,
                                       Qt::magenta, Qt::darkRed, Qt::darkGreen,
                                       Qt::darkBlue, Qt::darkCyan,
                                       Qt::darkMagenta
                                       };

PxPlot::PxPlot(QWidget *parent): QwtPlot(parent)
{
    setAutoReplot(false);

    setTitle(tr(" ")); // creates a wider top frame
    setCanvasBackground(QColor(Qt::white));
    plotLayout()->setLegendRatio(0.25);

    QwtLegend *legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    legend->setDefaultItemMode(QwtLegendData::Checkable);
    insertLegend(legend, QwtPlot::RightLegend);
    connect(legend,SIGNAL(checked(QVariant,bool,int)),this,
            SLOT(labelClick(QVariant,bool,int)));

    setAxisTitle(QwtPlot::xBottom, QString::fromUtf8("2Θ / °"));
    setAxisTitle(QwtPlot::yLeft, tr("Intensity"));

    curves.clear();

    setAutoReplot(true);
}

bool PxPlot::setData(const QString& name, const QString & filter)
{
    bool svReplot = autoReplot();
    setAutoReplot(false);

    int baselen = name.length()-name.lastIndexOf("/")-1;
    Qt::GlobalColor col = colorlist[curves.size() % 10];
    Curve* crv1;
    crv1 = new Curve(name.right(baselen));
    crv1->setRenderHint(QwtPlotItem::RenderAntialiased);
    crv1->setPen(col,2.0);
//    crv1->setYAxis(QwtPlot::yLeft);
    crv1->attach(this);
    curves.append(crv1);

    int ArraySize = 0;
    double* dx;
    double* dy;

    dx = new double[50000];
    dy = new double[50000];

    QByteArray ba = name.toLocal8Bit();

    FileFormat* ff = new FileFormat();
    FileFormatIDX fid = ff->guess(name, filter);
    delete ff;

    if (fid==PXV_XY_FILE)
        ArraySize = read_xye(ba.data(),dx,dy,0);
    else if (fid==PXV_ARL_FILE)
         ArraySize = read_xye(ba.data(),dx,dy,38);

    if (ArraySize > 0)
    {
        crv1->setSamples(dx,dy,ArraySize); // makes a copy, unlike setRawSamples
    } else
    {
        removeCurve(crv1);
    }

    delete [] dx;
    delete [] dy;

    setAutoReplot(svReplot);
    replot();

    return(ArraySize > 0);
}

QRectF PxPlot::boundingRect()
{
    QRectF bounds = QRectF(0,0,-1,-1);
    if (curves.isEmpty()) {
        return bounds;
    }

    bounds = curves[0]->boundingRect();
    for (int i = 1; i < curves.size(); ++i)
    {
        if (bounds.left() > curves[i]->minXValue())
        {
            bounds.setLeft(curves[i]->minXValue());
        }
        if (bounds.right() < curves[i]->maxXValue())
        {
            bounds.setRight(curves[i]->maxXValue());
        }
        if (bounds.top() > curves[i]->minYValue())
        {
            bounds.setTop(curves[i]->minYValue());
        }
        if (bounds.bottom() < curves[i]->maxYValue())
        {
            bounds.setBottom(curves[i]->maxYValue());
        }
    }

    return bounds;

}

void PxPlot::labelClick(QVariant qv, bool on, int index)
{
    QwtPlotItem *plotitem;

    if ( ! qv.canConvert<QwtPlotItem *>() ) return;

    plotitem = qvariant_cast<QwtPlotItem *>( qv );
    for (int i = 0; i < curves.size(); ++i)
    {
        if (curves[i] == plotitem)
        {
            if (on) plotitem->hide(); else plotitem->show();
        }
    }
}

QList<Curve*> PxPlot::curveList()
{
    return curves;
}

bool PxPlot::removeCurve(Curve *c)
{
    bool ok;
    c->detach();
    ok = curves.removeOne(c);
    if (ok) delete c;
    return(ok);
}
