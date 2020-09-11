#include "xye.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QMessageBox>

int readXYE(const QString &fn, QChar sep, QVector<double> &x,
            QVector<double> &y, int skip)
{
    int n = 0; // number of points read

    QFile xyfile(fn);
    if (!xyfile.open(QFile::ReadOnly|QFile::Text))
    {
        return n;
    }

    QTextStream inp(&xyfile);
    QString line;

    if (skip > 0)
    {
        for (int i=0; i < skip; ++i)
        {
            line = inp.readLine();
        }
    }

    while (inp.readLineInto(&line))
    {
        bool a, b;
        line = line.simplified(); // simplify whitespace for parsing
        QStringList fields = line.split(sep);
        if (fields.size()>1)
        {
            x.append(fields.at(0).simplified().toDouble(&a));
            y.append(fields.at(1).simplified().toDouble(&b));
            if (!(a && b)) return(n); // unsuccessful conversion
            ++n;
        } else
        {
            // accept single value at start to allow optional lambda in xye,
            // finish reading otherwise (no longer x y format)
            if (n > 0) return(n);
        }
    }

    return(n);

}
