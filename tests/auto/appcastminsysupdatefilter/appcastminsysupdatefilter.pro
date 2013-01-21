TEMPLATE = app
TARGET = tst_appcastminsysupdatefilter

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_appcastminsysupdatefilter.h
SOURCES += tst_appcastminsysupdatefilter.cpp
