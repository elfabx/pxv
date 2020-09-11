#ifndef XYE_H
#define XYE_H
#include <QString>
#include <QVector>

//! Read data from text files containing x y coordinates
/** Reads data from a text file that contains x and y coordinates of data
 * points as the first and second white-space separated columns
 *
 * \param fn name of file to open
 * \param sep separator between columns (' ' means any whitespace)
 * \param x, y arrays for data
 * \param skip number of header lines to ignore
 * \return number of successfully read data point
 */
int readXYE(const QString &fn, QChar sep, QVector<double> &x,
            QVector<double> &y, int skip=0);

#endif
