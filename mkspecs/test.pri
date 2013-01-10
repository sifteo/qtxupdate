include(features/qtx_testcase.prf)


QT += network

INCLUDEPATH += \
    ../../../src/update \
    ../../../../qtxxml/include \
    ../../../../qtxmocknetwork/include

LIBS += \
    -L../../../lib \
    -L../../../../qtxxml/lib \
    -L../../../../qtxmocknetwork/lib

LIBS += -lQtxUpdate -lQtxXml -lQtxMockNetwork
