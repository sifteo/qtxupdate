#include "mockupdate.h"


MockUpdate::MockUpdate(const QString & version, QObject *parent /* = 0 */)
    : Update(parent),
      mVersion(version)
{
}

MockUpdate::~MockUpdate()
{
}

QString MockUpdate::title() const
{
    return "";
}

QString MockUpdate::version() const
{
    return mVersion;
}

QUrl MockUpdate::linkUrl() const
{
    return QUrl();
}

QUrl MockUpdate::releaseNotesUrl() const
{
    return QUrl();
}

QUrl MockUpdate::packageUrl() const
{
    return QUrl();
}

QString MockUpdate::mimeType() const
{
    return "";
}
