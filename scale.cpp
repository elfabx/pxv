#include <QtGui>
#include <QtWidgets>
#include "scale.h"
#include "plot.h"
#include "arrows.h"
#include "curve.h"
#include "cselect.h"

ScaleDialog::ScaleDialog(const QList<Curve*> curves, QWidget *parent):
    QDialog(parent)
{
    setWindowTitle(tr("Scale pattern"));
    QGridLayout *layout = new QGridLayout(this);

    QLabel *sel = new QLabel(tr("Select patterns to scale"),this);
    layout->addWidget(sel,0,0,1,-1);
    
    list = new CurveSelector(curves,this);
    layout->addWidget(list,1,0,1,-1);
    
    QLabel *normLabel = new QLabel(tr("Normalise to:"),this);
    normEdit = new QLineEdit(tr("1000"),this);
    normEdit->selectAll();
    // FIXME: Add QValidator
    
    QPushButton *normButton = new QPushButton(tr("Normalise"),this);
    connect(normButton,SIGNAL(clicked(bool)),this,SLOT(normalise()));
    
    layout->addWidget(normLabel,2,0,1,1);
    layout->addWidget(normEdit,2,1,1,1);
    layout->addWidget(normButton,2,2,1,1);
    
    QLabel *scaleLabel = new QLabel(tr("Multiply by:"),this);
    scaleEdit = new QLineEdit(tr("1"),this);
    // FIXME: Add QValidator
    
    QPushButton *scaleButton = new QPushButton(tr("Multiply"),this);
    connect(scaleButton,SIGNAL(clicked(bool)),this,SLOT(scale()));
    
    layout->addWidget(scaleLabel,3,0,1,1);
    layout->addWidget(scaleEdit,3,1,1,1);
    layout->addWidget(scaleButton,3,2,1,1);
        
    // add spacing
    layout->setRowMinimumHeight(4,scaleButton->height());
    
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    QPushButton *closeButton = buttons->addButton(QDialogButtonBox::Close);
    layout->addWidget(buttons,5,0,1,-1);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
}

void ScaleDialog::scale()
{
    double s = scaleEdit->text().toDouble();
    foreach (Curve* m, list->selected())
    {
        m->multiply(s);
    }
}

void ScaleDialog::normalise()
{
    double s = normEdit->text().toDouble();
    foreach (Curve* m, list->selected())
    {
        m->normalise(s);
    }
}
