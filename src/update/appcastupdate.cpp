#include "appcastupdate.h"
#include "appcastitem.h"
#include "appcastenclosure.h"

QTX_BEGIN_NAMESPACE


AppcastUpdate::AppcastUpdate(AppcastItem *item, QObject *parent /* = 0 */)
  : Update(parent),
    mItem(item)
{
    mItem->setParent(this);
}

AppcastUpdate::~AppcastUpdate()
{
}

QString AppcastUpdate::name() const
{
    if (!mItem) {
        return "";
    }
    
    return mItem->title();
}

QString AppcastUpdate::version() const
{
    if (!mItem) {
        return "";
    }
    
    return mItem->version();
}

QUrl AppcastUpdate::linkUrl() const
{
    if (!mItem) {
        return QUrl();
    }
    
    return mItem->linkUrl();
}

QUrl AppcastUpdate::packageUrl() const
{
    if (!mItem) {
        return QUrl();
    }
    
    const AppcastEnclosure *enclosure = mItem->enclosure();
    if (!enclosure) {
        return QUrl();
    }
    return enclosure->url();
}

QString AppcastUpdate::mimeType() const
{
    if (!mItem) {
        return "";
    }
    
    const AppcastEnclosure *enclosure = mItem->enclosure();
    if (!enclosure) {
        return "";
    }
    return enclosure->mimeType();
}

QString AppcastUpdate::minSystemVersion() const
{
    if (!mItem) {
        return "";
    }
    
    return mItem->minSystemVersion();
}


QTX_END_NAMESPACE
