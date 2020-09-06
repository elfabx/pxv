#include <QPointF>
#include <qwt_plot_curve.h>
#include "curve.h"

Curve::Curve(const QString& title): QwtPlotCurve(title)
{
    ;
}

void Curve::move(double dx, double dy)
{
    size_t n = dataSize();
    double *x = new double[n];
    double *y = new double[n];
    
    QPointF p;
        for (size_t i = 0; i < n; i++)
    {
        p = data()->sample(i);
        x[i] = p.x()+dx;
        y[i] = p.y()+dy;     
    }
    
    setSamples(x,y,n);
    
    delete [] x;
    delete [] y;
}

void Curve::normalise(double scale)
{
    size_t n = dataSize();
    double ymin,ymax,multiplier;
    double *x = new double[n];
    double *y = new double[n];
    
    ymin = minYValue();
    ymax = maxYValue();
    
    if (qFuzzyCompare(ymin,ymax))
    {
        delete [] x; delete [] y;
        return; 
    }
    
    multiplier = scale/(ymax-ymin);
    
    QPointF p;
        for (size_t i = 0; i < n; i++)
    {
        p = data()->sample(i);
        x[i] = p.x();
        y[i] = (p.y()-ymin)*multiplier+ymin;     
    }
    
    setSamples(x,y,n);
    
    delete [] x;
    delete [] y;
}

void Curve::multiply(double multiplier)
{
    size_t n = dataSize();
    double *x = new double[n];
    double *y = new double[n];
        
    QPointF p;
        for (size_t i = 0; i < n; i++)
    {
        p = data()->sample(i);
        x[i] = p.x();
        y[i] = p.y()*multiplier;     
    }
    
    setSamples(x,y,n);
    
    delete [] x;
    delete [] y;
}
