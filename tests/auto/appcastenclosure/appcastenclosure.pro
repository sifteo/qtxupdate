TEMPLATE = app
TARGET = tst_appcastenclosure

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_appcastenclosure.h
SOURCES += tst_appcastenclosure.cpp
