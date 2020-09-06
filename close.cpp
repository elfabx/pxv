#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QDialogButtonBox>
#include "plot.h"
#include "curve.h"
#include "cselect.h"
#include "close.h"

CloseDialog::CloseDialog(Plot *plot, QWidget *parent) :
    QDialog (parent)
{
    p = plot;
    QList<Curve*> curves = plot->curveList();

    setWindowTitle(tr("Close pattern"));
    QVBoxLayout *vlayout = new QVBoxLayout(this);

    QLabel *sel = new QLabel(tr("Select patterns to close"),this);
    vlayout->addWidget(sel);

    list = new CurveSelector(curves,this);
    vlayout->addWidget(list);

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                     QDialogButtonBox::Cancel);
    connect(buttons,SIGNAL(accepted()),this,SLOT(closefiles()));
    connect(buttons,SIGNAL(rejected()),this,SLOT(close()));

    vlayout->addWidget(buttons);
}

void CloseDialog::closefiles()
{
    foreach(Curve* m, list->selected())
    {
        p->removeCurve(m);
    }
    this->close();
}
