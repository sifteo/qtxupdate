#include "appcastupdate.h"
#include "appcastitem.h"
#include "appcastenclosure.h"

QTX_BEGIN_NAMESPACE


class AppcastUpdatePrivate
{
public:
    AppcastUpdatePrivate();
    ~AppcastUpdatePrivate();
    
    AppcastItem *item;
};


AppcastUpdate::AppcastUpdate(AppcastItem *item, QObject *parent /* = 0 */)
    : Update(parent),
      d_ptr(new AppcastUpdatePrivate())
{
    item->setParent(this);
    d_ptr->item = item;
}

AppcastUpdate::~AppcastUpdate()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

QString AppcastUpdate::title() const
{
    if (!d_ptr->item) {
        return "";
    }
    
    return d_ptr->item->title();
}

QString AppcastUpdate::version() const
{
    if (!d_ptr->item) {
        return "";
    }
    
    return d_ptr->item->version();
}

QUrl AppcastUpdate::linkUrl() const
{
    if (!d_ptr->item) {
        return QUrl();
    }
    
    return d_ptr->item->linkUrl();
}

QUrl AppcastUpdate::releaseNotesUrl() const
{
    if (!d_ptr->item) {
        return QUrl();
    }
    
    return d_ptr->item->releaseNotesUrl();
}

QUrl AppcastUpdate::packageUrl() const
{
    if (!d_ptr->item) {
        return QUrl();
    }
    
    const AppcastEnclosure *enclosure = d_ptr->item->enclosure();
    if (!enclosure) {
        return QUrl();
    }
    return enclosure->url();
}

QString AppcastUpdate::mimeType() const
{
    if (!d_ptr->item) {
        return "";
    }
    
    const AppcastEnclosure *enclosure = d_ptr->item->enclosure();
    if (!enclosure) {
        return "";
    }
    return enclosure->mimeType();
}

QString AppcastUpdate::minSysVersion() const
{
    if (!d_ptr->item) {
        return "";
    }
    
    return d_ptr->item->minSysVersion();
}


AppcastUpdatePrivate::AppcastUpdatePrivate()
    : item(0)
{
}

AppcastUpdatePrivate::~AppcastUpdatePrivate()
{
}


QTX_END_NAMESPACE
