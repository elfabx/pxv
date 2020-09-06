#include <QtGui>
#include <qwt.h>
#include "curve.h"
#include "cselect.h"

CurveSelector::CurveSelector(const QList< Curve* > curves, QWidget* parent) : 
    QListView(parent)
{
    curveList = curves;
    QStringList curvenames;
    for (int i = 0; i < curves.size(); ++i)
        curvenames.append(curves[i]->title().text());
    
    QStringListModel *model = new QStringListModel(curvenames,this);
    setModel(model);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

QList< Curve* > CurveSelector::selected()
{
    QList<Curve*> list;
    
    QModelIndexList selection = selectionModel()->selectedIndexes();
    foreach (const QModelIndex & m, selection)
    {
       list.append(curveList[m.row()]);   
    }
    
    return list;
}
