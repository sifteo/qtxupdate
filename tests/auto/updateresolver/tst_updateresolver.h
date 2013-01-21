#ifndef TST_UPDATERESOLVER_H
#define TST_UPDATERESOLVER_H

#include "updateresolver.h"
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_UpdateResolver : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void updateFromTest();
    void updateFromWithNoUpdatesTest();
    void updateFromInvalidVersionTest();
    
private:
    UpdateResolver *mResolver;
};

#endif // TST_UPDATERESOLVER_H
