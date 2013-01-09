include(features/qtx_testcase.prf)


QT += network

INCLUDEPATH += \
    ../../../src/update \
    ../../../../qtxxml/include

LIBS += \
    -L../../../lib \
    -L../../../../qtxxml/lib

LIBS += -lQtxUpdate -lQtxXml
