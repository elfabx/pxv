# Adjust to local installation

CONFIG += debug
CONFIG += qwt

win32-g++: QMAKE_LFLAGS_RELEASE += -static-libgcc -static-libstdc++
win32: RC_ICONS = pxv.ico

QT += printsupport

TARGET = pxv
HEADERS = appw.h arrows.h cselect.h curve.h move.h plot.h pxplot.h scale.h \
          xye.h close.h fileformat.h
SOURCES = main.cpp appw.cpp arrows.cpp cselect.cpp curve.cpp move.cpp \
          plot.cpp pxplot.cpp scale.cpp xye.cpp close.cpp fileformat.cpp

# TRANSLATIONS = pxv_hu.ts

# Use syntax like 'qmake PREFIX=/opt' to set install location on unix
unix {
  isEmpty(PREFIX) {
    PREFIX = /usr/local
  }

  # To make PREFIX known to programs:
  # DEFINES += PREFIX=$${PREFIX}

  isEmpty(BINDIR) {
    BINDIR = $${PREFIX}/bin
  }

  target.path = $$BINDIR
  INSTALLS += target

  # To define extra installed files use freetext categories (eg. documentation)
  # documentation.files = docs/*
  # documentation.path = $${DOCDIR}
  # INSTALLS += documentation
}

RESOURCES += pxv.qrc

