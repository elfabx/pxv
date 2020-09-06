#ifndef CSELECT_H
#define CSELECT_H

#include <QWidget>
#include <QListView>
#include "curve.h"


class CurveSelector : public QListView
{
    Q_OBJECT

public:
    CurveSelector(const QList<Curve*> curves, QWidget *parent = nullptr);
        
    QList<Curve*> selected(); // list of selected curves
       
private:
    QList<Curve*> curveList;

};

#endif
