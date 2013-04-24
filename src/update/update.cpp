#include "update.h"

QTX_BEGIN_NAMESPACE


Update::Update(QObject *parent /* = 0 */)
  : QObject(parent)
{
}

Update::~Update()
{
}

QString Update::title() const
{
    return "";
}

QUrl Update::linkUrl() const
{
    return QUrl();
}

QUrl Update::releaseNotesUrl() const
{
    return QUrl();
}

QString Update::mimeType() const
{
    return "application/octet-stream";
}

QString Update::md5Sum() const
{
    return "";
}

QTX_END_NAMESPACE
