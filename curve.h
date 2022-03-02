#ifndef CURVE_H
#define CURVE_H

#include <qwt_plot_curve.h>

class Curve : public QwtPlotCurve
{

public:
    explicit Curve(const QString& title = QString());
    void move(double dx, double dy);
    void normalise(double scale);  // set max-min intensity to scale
    void multiply(double multiplier); // multiply by value (incl. background)
    
};

#endif // CURVE_H
