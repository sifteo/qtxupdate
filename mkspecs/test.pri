include(features/qtx_testcase.prf)


INCLUDEPATH += \
    ../../../src/update \
    ../../../../qtxxml/include

LIBS += \
    -L../../../lib \
    -L../../../../qtxxml/lib

LIBS += -lQtxUpdate -lQtxXml
