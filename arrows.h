#ifndef ARROWS_H
#define ARROWS_H

#include <QWidget>
#include <QGridLayout>
#include "qwt_arrow_button.h"

class Arrows : public QWidget
{
    Q_OBJECT

public:
    Arrows(QWidget *parent = nullptr);
    
signals:
    void clicked(Qt::ArrowType);   

private:
    QwtArrowButton *up;
    QwtArrowButton *down;
    QwtArrowButton *left;
    QwtArrowButton *right;

private slots:
    void up_click();
    void down_click();
    void left_click();
    void right_click();    
};

#endif

