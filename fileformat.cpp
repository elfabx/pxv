#include "fileformat.h"


FileFormat::FileFormat()
{
    // create a joint list of descriptions and file type id's
    // the first entry is the fallback format for unmatched files
    descr.clear(); ids.clear();
    descr.append(tr("XY files (*.xy *.xye)"));
    ids.append(PXV_XY_FILE);
    descr.append(tr("ARL text files (*.txt)"));
    ids.append(PXV_ARL_FILE);
    descr.append(tr("Tab/space separated files (*.txt *.tsv)"));
    ids.append(PXV_TSV_FILE);
    descr.append(tr("CSV files (*.csv)"));
    ids.append(PXV_CSV_FILE);

    // create filter string
    filter = descr.join(";;");
}

// return filter stting for use in QFileDialog
const QString & FileFormat::filterString()
{
    return(filter);
}

// Guess format from file name
FileFormatIDX FileFormat::guessFromName(const QString & fn)
{
    QString n(fn.toLower());
    if (n.endsWith(".xy") || n.endsWith(".xye")) return(PXV_XY_FILE);
    if (n.endsWith(".txt")) return(PXV_ARL_FILE);
    if (n.endsWith(".tsv")) return(PXV_TSV_FILE);
    if (n.endsWith(".csv")) return(PXV_CSV_FILE);
    return(ids[0]); // unrecognised, treated as first in constructor
}

// determine format from selected filter
FileFormatIDX FileFormat::guessFromFilter(const QString & s)
{
    for (int i=0; i < descr.size(); ++i)
    {
        if (s==descr[i]) return(ids[i]);
    }
    return(ids[0]);  //fallback (should never be reached)
}


FileFormatIDX FileFormat::guess(const QString &name, const QString &filter)
{
    if (filter.isEmpty()) return(guessFromName(name));
    return(guessFromFilter(filter));
}
