#ifndef MOVE_H
#define MOVE_H

#include <QDialog>
#include <QLineEdit>
#include <QListView>
#include "plot.h"

class Curve;
class CurveSelector;

class MoveDialog : public QDialog
{
    Q_OBJECT

public:
    MoveDialog(const QList<Curve*> curves, QWidget *parent = nullptr);
    
private:
    QLineEdit *edit;
    CurveSelector *list;

private slots:
    void arrow_click(Qt::ArrowType t);

};

#endif
