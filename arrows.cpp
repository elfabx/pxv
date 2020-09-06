#include <QtGui>
#include <qwt.h>
#include "arrows.h"

Arrows::Arrows(QWidget *parent): QWidget(parent)
{
    up = new QwtArrowButton(1,Qt::UpArrow);
    up->setFixedSize(24,24);
    down = new QwtArrowButton(1,Qt::DownArrow);
    down->setFixedSize(24,24);
    left = new QwtArrowButton(1,Qt::LeftArrow);
    left->setFixedSize(24,24);
    right = new QwtArrowButton(1,Qt::RightArrow);
    right->setFixedSize(24,24);
    
    connect(up, SIGNAL(clicked(bool)), this, SLOT(up_click()));
    connect(down, SIGNAL(clicked(bool)), this, SLOT(down_click()));
    connect(left, SIGNAL(clicked(bool)), this, SLOT(left_click()));
    connect(right, SIGNAL(clicked(bool)), this, SLOT(right_click()));
    
    QGridLayout *layout = new QGridLayout;
    setLayout(layout);
    
    layout->addWidget(up,0,1,1,1,Qt::AlignHCenter|Qt::AlignBottom);
    layout->addWidget(left,1,0,1,1,Qt::AlignVCenter|Qt::AlignRight);
    layout->addWidget(right,1,2,1,1,Qt::AlignVCenter|Qt::AlignLeft);
    layout->addWidget(down,2,1,1,1,Qt::AlignHCenter|Qt::AlignTop);
    layout->setColumnStretch(1,0);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(2,1);
    layout->setRowStretch(1,0);
    layout->setRowStretch(0,1);
    layout->setRowStretch(2,1);
    

//    connect(d_picker, SIGNAL(moved(const QPoint &)),
//            SLOT(moved(const QPoint &)));
//    connect(d_picker, SIGNAL(selected(const QwtPolygon &)),
//           SLOT(selected(const QwtPolygon &)));

}

void Arrows::up_click()
{
    emit clicked(Qt::UpArrow);
}

void Arrows::down_click()
{
    emit clicked(Qt::DownArrow);
}

void Arrows::left_click()
{
    emit clicked(Qt::LeftArrow);
}

void Arrows::right_click()
{
    emit clicked(Qt::RightArrow);
}

