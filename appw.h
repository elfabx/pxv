#ifndef APPW_H
#define APPW_H

#include <QMainWindow>

class QAction;
class QMenu;
class Plot;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppWindow();
    void setDataFile(const QString & name,const QString & format);

protected:
    void quitEvent(QCloseEvent *event);

private slots:
    void open();
    void move();
    void scale();
    void fclose();
    void about();
//    void needsSave();

private:
    QString dataFile;

    void addActions();
    void addMenus();
//    void addStatusBar();
//    void addToolBar();

    Plot *plot;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QAction *openAction;
    QAction *exportAction;
    QAction *printAction;
    QAction *closeAction;
    QAction *quitAction;
    QAction *moveAction;
    QAction *scaleAction;
    QAction *zoomFitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

    bool checkSave();
};

#endif

