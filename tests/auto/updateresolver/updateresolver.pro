TEMPLATE = app
TARGET = tst_updateresolver

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_updateresolver.h \
           ../../mock/src/mockfailingupdatechecker.h \
           ../../mock/src/mockupdate.h \
           ../../mock/src/mockupdatechecker.h \
           ../../mock/src/versionlimitupdatefilter.h
SOURCES += tst_updateresolver.cpp \
           ../../mock/src/mockfailingupdatechecker.cpp \
           ../../mock/src/mockupdate.cpp \
           ../../mock/src/mockupdatechecker.cpp \
           ../../mock/src/versionlimitupdatefilter.cpp
