#include "appcastenclosure.h"
#include "appcastitem.h"

QTX_BEGIN_NAMESPACE


const char AppcastEnclosure::kXmlElementName[] = "enclosure";
const char AppcastEnclosure::kVersionXmlElementName[] = "version";
const char AppcastEnclosure::kUrlXmlElementName[] = "url";
const char AppcastEnclosure::kTypeXmlElementName[] = "type";


QString AppcastEnclosure::xmlName()
{
    return kXmlElementName;
}

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

IXmlDeserializing *AppcastEnclosure::deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri,  const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(name)
    Q_UNUSED(attributes)
    
    mDepth++;
    return this;
}

void AppcastEnclosure::deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(name)
    
    if (!mDepth) {
        emit parsed();
        return;
    }
    
    mDepth--;
}

void AppcastEnclosure::deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(attributes)
    
    mVersion = attributes.value(AppcastItem::kSparkleXmlNamespace, kVersionXmlElementName).toString();
    mUrl = QUrl(attributes.value("", kUrlXmlElementName).toString());
    mMimeType = attributes.value("", kTypeXmlElementName).toString();
}

void AppcastEnclosure::deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(text)
}


QTX_END_NAMESPACE
