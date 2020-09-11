#ifndef FILEFORMAT_H
#define FILEFORMAT_H
#include <QtCore>


// File formats as
typedef enum { PXV_XY_FILE,
               PXV_ARL_FILE,
               PXV_TSV_FILE,
               PXV_CSV_FILE } FileFormatIDX;

class FileFormat : private QObject
{
    Q_OBJECT // we use QObject only to inherit tr()

public:
    FileFormat();
    // Guess format from name
    FileFormatIDX guessFromName(const QString & fn);
    // Create filter stting for QFileDialog
    const QString & filterString();
    // format from selected filter
    FileFormatIDX guessFromFilter(const QString & s);
    // Guess from filter if available, from filename if not
    FileFormatIDX guess(const QString & name, const QString & filter);
private:
    int index(FileFormatIDX j); // index of file type
    QStringList descr;
    QList<FileFormatIDX> ids;
    QString filter;
};

#endif // FILEFORMAT_H
