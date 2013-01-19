TEMPLATE = app
TARGET = tst_semversortupdatefilter

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_semversortupdatefilter.h \
           ../../mock/src/mockupdate.h
SOURCES += tst_semversortupdatefilter.cpp \
           ../../mock/src/mockupdate.cpp
