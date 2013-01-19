TEMPLATE = app
TARGET = tst_appcastminsystemupdatefilter

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_appcastminsystemupdatefilter.h
SOURCES += tst_appcastminsystemupdatefilter.cpp
