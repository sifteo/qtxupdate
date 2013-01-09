TEMPLATE = app
TARGET = tst_appcastitem

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_appcastitem.h
SOURCES += tst_appcastitem.cpp
