#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QDialogButtonBox>
#include "move.h"
#include "arrows.h"
#include "plot.h"
#include "curve.h"
#include "cselect.h"

MoveDialog::MoveDialog(const QList<Curve*> curves, QWidget *parent):
    QDialog(parent)
{
    setWindowTitle(tr("Shift pattern"));
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    
    QLabel *sel = new QLabel(tr("Select patterns to shift"),this);
    vlayout->addWidget(sel);
    
    list = new CurveSelector(curves,this);
    vlayout->addWidget(list);
    
    QHBoxLayout *hlayout = new QHBoxLayout();
    vlayout->addLayout(hlayout);
    QLabel *label = new QLabel(tr("Move by:"),this);
    edit = new QLineEdit(tr("0"),this);
    edit->selectAll();
    // FIXME: Add QValidator
    hlayout->addWidget(label);
    hlayout->addWidget(edit);
    
    Arrows *arrows = new Arrows(this);
    vlayout->addWidget(arrows);
    connect(arrows,SIGNAL(clicked(Qt::ArrowType)),this,
            SLOT(arrow_click(Qt::ArrowType)));    
    
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    QPushButton *closeButton = buttons->addButton(QDialogButtonBox::Close);
    vlayout->addWidget(buttons);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
}

void MoveDialog::arrow_click(Qt::ArrowType t)
{
    double s = edit->text().toDouble();
    foreach (Curve* m, list->selected())
    {
        switch (t)
        {
            case Qt::UpArrow:
                m->move(0.0,s);
                break;
                
            case Qt::DownArrow:
                m->move(0.0,-1.0*s);
                break;
                
            case Qt::LeftArrow:
                m->move(-1.0*s,0.0);
                break;
                
            case Qt::RightArrow:
                m->move(s,0.0);
                break;
                
            default:
                ;
        }
    }
}
