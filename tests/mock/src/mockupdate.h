#ifndef MOCK_MOCKUPDATE_H
#define MOCK_MOCKUPDATE_H

#include "update.h"
#include <QtCore>

QTX_USE_NAMESPACE


class MockUpdate : public Update
{
    Q_OBJECT

public:
    MockUpdate(const QString & version, QObject *parent = 0);
    ~MockUpdate();
    
    QString title() const;
    QString version() const;
    QUrl linkUrl() const;
    QUrl releaseNotesUrl() const;
    QUrl packageUrl() const;
    QString mimeType() const;
    
private:
    QString mVersion;
};

#endif // MOCK_MOCKUPDATE_H