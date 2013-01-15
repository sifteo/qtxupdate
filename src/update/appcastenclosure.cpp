#include "appcastenclosure.h"
#include "appcastitem.h"
#include "appcastxmlns.h"

QTX_BEGIN_NAMESPACE

using namespace __Appcast;


class AppcastEnclosurePrivate
{
public:
    QString version;
    QUrl url;
    QString type;
};



QString AppcastEnclosure::xmlName()
{
    return kRssEnclosureXmlName;
}

AppcastEnclosure::AppcastEnclosure(QObject *parent /* = 0 */)
    : QObject(parent),
      d_ptr(new AppcastEnclosurePrivate())
{
}

AppcastEnclosure::~AppcastEnclosure()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

QString AppcastEnclosure::version() const
{
    return d_ptr->version;
}

QUrl AppcastEnclosure::url() const
{
    return d_ptr->url;
}

QString AppcastEnclosure::mimeType() const
{
    return d_ptr->type;
}

void AppcastEnclosure::deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    
    d_ptr->version = attributes.value(kSparkleXmlNamespaceUri, kSparkleEnclosureVersionXmlAttr).toString();
    d_ptr->url = QUrl(attributes.value(kRssEnclosureUrlXmlAttr).toString());
    d_ptr->type = attributes.value(kRssEnclosureTypeXmlAttr).toString();
}


QTX_END_NAMESPACE
