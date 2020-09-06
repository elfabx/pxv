#ifndef SCALE_H
#define SCALE_H

#include <QDialog>
#include <QLineEdit>
#include <QListView>
#include "plot.h"

class Curve;
class CurveSelector;

class ScaleDialog : public QDialog
{
    Q_OBJECT

public:
    ScaleDialog(const QList<Curve*> curves, QWidget *parent = nullptr);
    
private:
    QLineEdit *scaleEdit;
    QLineEdit *normEdit;
    CurveSelector *list;

private slots:
    void scale();
    void normalise();

};

#endif
