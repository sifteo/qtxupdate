#include "appcastitem.h"
#include "appcastenclosure.h"
#include "appcastxmlns.h"

QTX_BEGIN_NAMESPACE

using namespace __Appcast;


class AppcastItemPrivate
{
public:
    void addEnclosure(AppcastEnclosure *enclosure);

    QString title;
    QUrl link;
    QList<AppcastEnclosure *> enclosures;
    QString minSysVersion;
    
    QString characters;
};


QString AppcastItem::xmlName()
{
    return kRssItemXmlName;
}

AppcastItem::AppcastItem(QObject *parent /* = 0 */)
    : QObject(parent),
      d_ptr(new AppcastItemPrivate())
{
}

AppcastItem::~AppcastItem()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

QString AppcastItem::title() const
{
    return d_ptr->title;
}

QString AppcastItem::version() const
{
    // Sparkle's RSS extension is rather poorly specified.  The version is
    // logically associated with the item, but is indicated as an attribute
    // of the enclosure (of which there can be many, in the case of
    // per-platform enclosures).  The version of the first enclosure will be
    // treated as the item's version.  For consistency, it is recommended
    // that any item containing multiple enclosures indicates an identical
    // version for each.

    const AppcastEnclosure *e = enclosure();
    if (e) {
        return e->version();
    }

    return "";
}

QUrl AppcastItem::linkUrl() const
{
    return d_ptr->link;
}

const AppcastEnclosure *AppcastItem::enclosure() const
{
    if (d_ptr->enclosures.isEmpty()) {
        return 0;
    }
    
    return d_ptr->enclosures.at(0);
}

QString AppcastItem::minSysVersion() const
{
    return d_ptr->minSysVersion;
}

IXmlDeserializing *AppcastItem::deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(attributes)
    
    if (AppcastEnclosure::xmlName() == name) {
        AppcastEnclosure *enclosure = new AppcastEnclosure(this);
        d_ptr->addEnclosure(enclosure);
        return enclosure;
    }
    
    return this;
}

void AppcastItem::deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name)
{
    Q_UNUSED(deserializer)
    
    if (kRssTitleXmlName == name) {
        d_ptr->title = d_ptr->characters.trimmed();
    } else if (kRssLinkXmlName == name) {
        d_ptr->link = QUrl(d_ptr->characters.trimmed());
    } else if (kSparkleXmlNamespaceUri == namespaceUri && kSparkleMinimumSystemVersionXmlName == name) {
        d_ptr->minSysVersion = d_ptr->characters.trimmed();
    }
    
    d_ptr->characters.clear();
}

void AppcastItem::deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text)
{
    Q_UNUSED(deserializer)
    
    d_ptr->characters.append(text);
}


void AppcastItemPrivate::addEnclosure(AppcastEnclosure *enclosure)
{
    enclosures.append(enclosure);
}


QTX_END_NAMESPACE
