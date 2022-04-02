# pxv - Powder X-ray Viewer

This is a very simple program to view 2&theta; - intensity data sets saved in
text formats (such as .xy, .xye, .csv, .tsv). It was written to make comparisons,
phase identification and recognition of multi-phase mixtures easier. Multiple data
sets can be loaded, moved around, scaled and their visibility switched on/off.
The plots can be exported as pdf, svg, png files and in other image formats.

### Mouse buttons:
- Left: show coordinates & zoom in (drag area)
- Middle: pan
- Right: step back in zoom history

Clicking on the legend toggles the visibility of the corresponding pattern.

## Compilation

You need Qt5 (>=5.12) or Qt6 and Qwt (>=6.1.4) installed and configured
to compile the code.

`mkdir build && cd build`

`qmake ..` (or "`qmake-qt5 ..`" or "`qmake-qt6 ..`")

`make`

and (optionally) `make install`

should work on recent linux distributions with Qwt installed. If you compile Qwt manually, qmake may be unable to find your qwt installation. This can often be
fixed by replacing the

`CONFIG += qwt`

line in the pxv.pro file by

`include ( /full/path/to/qwt.pri )` 

