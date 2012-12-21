#include "appcastenclosure.h"
#include "appcastitem.h"


const char AppcastEnclosure::kXmlElementName[] = "enclosure";
const char AppcastEnclosure::kVersionXmlElementName[] = "version";
const char AppcastEnclosure::kUrlXmlElementName[] = "url";
const char AppcastEnclosure::kTypeXmlElementName[] = "type";

AppcastEnclosure::AppcastEnclosure(QObject *parent /* = 0 */)
    : QObject(parent),
      mDepth(0)
{
}

AppcastEnclosure::~AppcastEnclosure()
{
}

QString AppcastEnclosure::version() const
{
    return mVersion;
}

QUrl AppcastEnclosure::url() const
{
    return mUrl;
}

QString AppcastEnclosure::mimeType() const
{
    return mMimeType;
}

IXmlDeserializer* AppcastEnclosure::deserializeXmlStartElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(reader)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(name)
    Q_UNUSED(attributes)
    
    mDepth++;
    return this;
}

void AppcastEnclosure::deserializeXmlEndElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name)
{
    Q_UNUSED(reader)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(name)
    
    if (!mDepth) {
        emit parsed();
        return;
    }
    
    mDepth--;
}

void AppcastEnclosure::deserializeXmlAttributes(XmlReader* reader, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(reader)
    Q_UNUSED(attributes)
    
    mVersion = attributes.value(AppcastItem::kSparkleXmlNamespace, kVersionXmlElementName).toString();
    mUrl = QUrl(attributes.value("", kUrlXmlElementName).toString());
    mMimeType = attributes.value("", kTypeXmlElementName).toString();
}

void AppcastEnclosure::deserializeXmlCharacters(XmlReader* reader, const QStringRef & text)
{
    Q_UNUSED(reader)
    Q_UNUSED(text)
}
