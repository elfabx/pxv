#ifndef CLOSE_H
#define CLOSE_H

#include <QDialog>
#include <QListView>
#include "plot.h"

class Curve;
class CurveSelector;

class CloseDialog : public QDialog
{
    Q_OBJECT
public:
    CloseDialog(Plot* plot, QWidget *parent = nullptr);

private:
    CurveSelector *list;
    Plot *p;

private slots:
    void closefiles();
};

#endif // CLOSE_H
