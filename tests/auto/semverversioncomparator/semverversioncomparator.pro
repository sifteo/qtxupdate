TEMPLATE = app
TARGET = tst_semverversioncomparator

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_semverversioncomparator.h
SOURCES += tst_semverversioncomparator.cpp
