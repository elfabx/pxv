#include <QtGui>
#include <QtWidgets>
#include <QTextStream>
#include <QApplication>
#include "plot.h"
#include "appw.h"
#include "move.h"
#include "scale.h"
#include "close.h"
#include "curve.h"
#include "fileformat.h"

AppWindow::AppWindow()
{
    plot = new Plot;
    setCentralWidget(plot);
    addActions();
    addMenus();
// readSettings();
    setDataFile("","");
//    connect(textEdit->document(), SIGNAL(contentsChanged()), this,
//            SLOT(needsSave()));

    // set window size to 67% of desktop if enough to display all widgets
    // done this to avoid tiny window on high res laptop screen
    QSize swin = this->size(); // current size (fits widgets)
    QSize sdesk = qApp->primaryScreen()->availableSize()*2/3;
    if (swin.width() < sdesk.width()) swin.setWidth(sdesk.width());
    if (swin.height() < sdesk.height()) swin.setHeight(sdesk.height());
    this->resize(swin);
}

// to be called by changed signal of contents
/* void AppWindow::needsSave()
{
    // call QWidget.setWindowModified to update window change indicator
    setWindowModified(textEdit->document()->isModified());
} */

void AppWindow::quitEvent(QCloseEvent *event)
{
    if (checkSave())
    {
// saveSettings();
        event->accept();
    } else
    {
        event->ignore();
    }
}

void AppWindow::open()
{
    QString *filter = new QString(); // selected filter
    FileFormat* format = new FileFormat();

    QStringList fns = QFileDialog::getOpenFileNames(this,
                          tr("Open file"),QString(),
                          format->filterString(),filter);

    delete format;

    foreach(const QString & fn, fns)
    {
        if (!fn.isEmpty())
        {
            setDataFile(fn,*filter);
        }
    }

    delete filter;

}

void AppWindow::move()
{
    QList<Curve*> curves = plot->curveList();
    
    MoveDialog *dia = new MoveDialog(curves, this);
    dia->exec();
}

void AppWindow::scale()
{
    QList<Curve*> curves = plot->curveList();
    
    ScaleDialog *dia = new ScaleDialog(curves, this);
    dia->exec();
}

void AppWindow::fclose()
{
    CloseDialog *dia = new CloseDialog(plot, this);
    dia->exec();
}

void AppWindow::about()
{
    QMessageBox dia;
    dia.setText(tr("PXV - Powder X-ray Viewer"));
    dia.setInformativeText(tr("Copyright 2010-2020 Laszlo Fabian"));
    dia.exec();
}

void AppWindow::addActions()
{
    openAction = new QAction(tr("&Open..."),this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an XY data file"));
    openAction->setIcon(QIcon::fromTheme("document-open"));
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

    exportAction = new QAction(tr("&Export..."),this);
//    exportAction->setShortcuts(QKeySequence::Print);
    exportAction->setStatusTip(tr("Save the graph to an image file"));
    exportAction->setIcon(QIcon::fromTheme("document-export"));
    connect(exportAction,SIGNAL(triggered()),plot,SLOT(fexport()));
    
    printAction = new QAction(tr("&Print..."),this);
    printAction->setShortcuts(QKeySequence::Print);
    printAction->setStatusTip(tr("Print the graph"));
    printAction->setIcon(QIcon::fromTheme("document-print"));
    connect(printAction,SIGNAL(triggered()),plot,SLOT(print()));

    closeAction = new QAction(tr("&Close..."),this);
    closeAction->setShortcuts(QKeySequence::Close);
    closeAction->setStatusTip(tr("Close a data set"));
    closeAction->setIcon(QIcon::fromTheme("window-close"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(fclose()));

    quitAction = new QAction(tr("&Quit"),this);
    quitAction->setShortcuts(QKeySequence::Quit);
    quitAction->setStatusTip(tr("Quit the application"));
    quitAction->setIcon(QIcon::fromTheme("application-exit"));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(close()));
    
    moveAction = new QAction(tr("&Move pattern..."),this);
//    quitAction->setShortcuts(QKeySequence::Quit);
    moveAction->setStatusTip(tr("Shift a pattern in any direction"));
    moveAction->setIcon(QIcon::fromTheme("transform-move"))   ;
    connect(moveAction,SIGNAL(triggered()),this,SLOT(move()));
    
    scaleAction = new QAction(tr("&Scale pattern..."),this);
//    quitAction->setShortcuts(QKeySequence::Quit);
    scaleAction->setStatusTip(tr("Change the intensity scale"));
    scaleAction->setIcon(QIcon::fromTheme("transform-scale"))   ;
    connect(scaleAction,SIGNAL(triggered()),this,SLOT(scale()));

    zoomFitAction = new QAction(tr("Zoom to &Fit"),this);
    zoomFitAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Asterisk));
    zoomFitAction->setStatusTip(tr("Zoom to show all data"));
    zoomFitAction->setIcon(QIcon::fromTheme("zoom-fit-best"));
    connect(zoomFitAction,SIGNAL(triggered()),plot,SLOT(zoomToFit()));

    aboutAction = new QAction(tr("About &pxv..."),this);
    aboutAction->setStatusTip(tr("Information about the program"));
    aboutAction->setIcon(QIcon::fromTheme("help-about"));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt..."),this);
    aboutQtAction->setStatusTip(tr("Information about the Qt framework"));
    aboutQtAction->setIcon(QIcon::fromTheme("help-about"));
    connect(aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
}

void AppWindow::addMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(exportAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    fileMenu->addAction(quitAction);
    
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(moveAction);
    editMenu->addAction(scaleAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(zoomFitAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

bool AppWindow::checkSave()
{
    if (true)  // should check if a save is needed once implemented
    {
        QMessageBox::StandardButton re;
        re = QMessageBox::warning(this, tr("File modified"),
               tr("The document has been modified.\n"
                  "Do you want to save your changes?"),
              QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (re == QMessageBox::Save)
            return true;
        else if (re == QMessageBox::Cancel)
            return false;
    }
    return true;

}

void AppWindow::setDataFile(const QString &fn, const QString & format)
{
    dataFile = fn;
    // textEdit->document()->setModified(false);
    if (!dataFile.isEmpty())
    {
        // setWindowFilePath(dataFile);
        plot->addDataFile(dataFile, format);
    } else
    {
        // setWindowFilePath("untitled");
    }
}

