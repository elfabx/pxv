#include <QtGui>
#include <QApplication>
#include "appw.h"


int main(int argc, char *argv[])
{
// if we have a resource file: 	Q_INIT_RESOURCE(app)

    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QString("pxv_") + locale);

    QApplication app(argc, argv); // on return it is the filtered list
//    app.setOrganizationName("LF"); // needed for QSettings?
    app.setApplicationName("pxv"); // used by QSettings
    app.installTranslator(&translator);
    app.setWindowIcon(QIcon(":/pxv.svg"));

    AppWindow appw;

    if (argc > 0) 
    {
        for (int i = 1; i < argc; ++i)
        {
            appw.setDataFile(argv[i],"");
        }
    }

    appw.show();

    return app.exec();
}
