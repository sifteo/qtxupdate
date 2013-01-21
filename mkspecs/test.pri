include(features/qtx_testcase.prf)


QT += network

INCLUDEPATH += \
    ../../../src/update \
    ../../../../qtxversion/include \
    ../../../../qtxxml/include \
    ../../../../qtxmocknetwork/include

LIBS += \
    -L../../../lib \
    -L../../../../qtxversion/lib \
    -L../../../../qtxxml/lib \
    -L../../../../qtxmocknetwork/lib

LIBS += -lQtxUpdate -lQtxVersion -lQtxXml -lQtxMockNetwork
