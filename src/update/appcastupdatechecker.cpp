#include "appcastupdatechecker.h"
#include "appcastupdate.h"
#include "appcastitem.h"
#include <QtxNetwork>

QTX_BEGIN_NAMESPACE


class AppcastUpdateCheckerPrivate
{
public:
    AppcastUpdateCheckerPrivate(AppcastUpdateChecker *q);
    virtual ~AppcastUpdateCheckerPrivate();

    void check();

public:
    AppcastUpdateChecker *q_ptr;
    Q_DECLARE_PUBLIC(AppcastUpdateChecker);
    
    QNetworkAccessManager *netAccessManager;
    QNetworkRequest request;
    NetworkExchange *exchange;
    XmlDeserializer *xmlDeserializer;
    
    QList<Update *> updates;
    AppcastItem *parsingItem;
};


AppcastUpdateChecker::AppcastUpdateChecker(QObject *parent /* = 0 */)
    : AbstractUpdateChecker(parent),
      d_ptr(new AppcastUpdateCheckerPrivate(this))
{
}

AppcastUpdateChecker::~AppcastUpdateChecker()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

void AppcastUpdateChecker::check()
{
    Q_D(AppcastUpdateChecker);
    d->check();
}

QList<Update *> AppcastUpdateChecker::updates()
{
    Q_D(AppcastUpdateChecker);
    return d->updates;
}

void AppcastUpdateChecker::setUrl(const QUrl & url)
{
    Q_D(AppcastUpdateChecker);
    d->request.setUrl(url);
}

void AppcastUpdateChecker::setRequest(const QNetworkRequest & request)
{
    Q_D(AppcastUpdateChecker);
    d->request = request;
}

void AppcastUpdateChecker::setNetworkAccessManager(QNetworkAccessManager *manager)
{
    Q_D(AppcastUpdateChecker);
    d->netAccessManager = manager;
}

void AppcastUpdateChecker::onReplyReceived()
{
    Q_D(AppcastUpdateChecker);

    if (d->xmlDeserializer) {
        d->xmlDeserializer->setDelegate(0);
        d->xmlDeserializer->deleteLater();
    }
    
    d->xmlDeserializer = new XmlDeserializer(this);
    d->xmlDeserializer->setDelegate(this);
}

void AppcastUpdateChecker::onReadyRead()
{
    Q_D(AppcastUpdateChecker);

    QByteArray data = d->exchange->readAll();
    d->xmlDeserializer->addData(data);
    d->xmlDeserializer->parse();
}

void AppcastUpdateChecker::onFinished()
{
    Q_D(AppcastUpdateChecker);

    if (d->xmlDeserializer) {
        d->xmlDeserializer->setDelegate(0);
        d->xmlDeserializer->deleteLater();
    }

    d->exchange->disconnect(this);
    d->exchange->deleteLater();
    d->exchange = 0;
}

// TODO: Switch to using qint32 codes (or QNetworkReply::NetworkError, in this case)
void AppcastUpdateChecker::onError(quint32 code)
{
    Q_UNUSED(code)
    
    Q_D(AppcastUpdateChecker);
 
    setErrorString(d->exchange->errorString());
    emit error(-1);
}

IXmlDeserializing *AppcastUpdateChecker::deserializeXmlStart(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(name)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(attributes)
    
    return this;
}

void AppcastUpdateChecker::deserializeXmlEnd(XmlDeserializer *deserializer)
{
    Q_UNUSED(deserializer)
    
    emit finished();
}

void AppcastUpdateChecker::deserializeXmlError(XmlDeserializer *deserializer, const QXmlStreamReader::Error err, const QString & errorString)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(err)
    Q_UNUSED(errorString)
    
    setErrorString("invalid appcast XML");
    emit error(-1);
}

IXmlDeserializing *AppcastUpdateChecker::deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri,  const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(attributes)
    
    Q_D(AppcastUpdateChecker);
    
    if (AppcastItem::xmlName() == name) {
        d->parsingItem = new AppcastItem(this);
        return d->parsingItem;
    }
    
    return this;
}

void AppcastUpdateChecker::deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(name)
    Q_UNUSED(namespaceUri)
    
    Q_D(AppcastUpdateChecker);
    
    if (AppcastItem::xmlName() == name) {
        AppcastUpdate *update = new AppcastUpdate(d->parsingItem, this);
        d->updates.append(update);
        d->parsingItem = 0;
    }
}

void AppcastUpdateChecker::deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(attributes)
}

void AppcastUpdateChecker::deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(text)
}


AppcastUpdateCheckerPrivate::AppcastUpdateCheckerPrivate(AppcastUpdateChecker *q)
    : q_ptr(q),
      exchange(0),
      xmlDeserializer(0),
      parsingItem(0),
      netAccessManager(0)
{
}

AppcastUpdateCheckerPrivate::~AppcastUpdateCheckerPrivate()
{
}

void AppcastUpdateCheckerPrivate::check()
{
    Q_Q(AppcastUpdateChecker);
    
    if (!netAccessManager) {
        netAccessManager = new QNetworkAccessManager(q);
    }
    
    request.setRawHeader("Accept", "application/rss+xml");
    exchange = new NetworkExchange(request, q);
    exchange->setNetworkAccessManager(netAccessManager);
    
    q->connect(exchange, SIGNAL(replyReceived()), SLOT(onReplyReceived()));
    q->connect(exchange, SIGNAL(readyRead()), SLOT(onReadyRead()));
    q->connect(exchange, SIGNAL(finished()), SLOT(onFinished()));
    q->connect(exchange, SIGNAL(error(quint32)), SLOT(onError(quint32)));
    
    exchange->get();
}


QTX_END_NAMESPACE
