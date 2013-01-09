TEMPLATE = app
TARGET = tst_appcastupdatechecker

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_appcastupdatechecker.h
SOURCES += tst_appcastupdatechecker.cpp
