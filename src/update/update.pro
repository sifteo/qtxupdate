include(../../modules/qtx_update.pri)
include(../../mkspecs/features/qtx_config.prf)
include(../../mkspecs/features/qtx_module.prf)


contains(QT.webkitwidgets.VERSION, ^5\\.[0-9]\\..*) {
    QT += widgets webkitwidgets
} else {
    QT += gui webkit
}

QT += network

INCLUDEPATH += \
    ../../../qtxversion/include \
    ../../../qtxxml/include \
    ../../../qtxnetwork/include

include(update.pri)

LIBS += \
    -L../../../qtxversion/lib \
    -L../../../qtxxml/lib \
    -L../../../qtxnetwork/lib

LIBS += -lQtxVersion -lQtxXml -lQtxNetwork
