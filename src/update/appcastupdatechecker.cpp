#include "appcastupdatechecker.h"
#include "appcastupdate.h"
#include "appcastitem.h"
#include <QtxNetwork>

QTX_BEGIN_NAMESPACE


const char AppcastUpdateChecker::kChannelXmlElementName[] = "channel";

AppcastUpdateChecker::AppcastUpdateChecker(QObject *parent /* = 0 */)
  : AbstractUpdateChecker(parent),
    mExchange(0),
    mXmlReader(0),
    mParsingItem(0),
    mAccessManager(0)
{
}

AppcastUpdateChecker::~AppcastUpdateChecker()
{
}

void AppcastUpdateChecker::check()
{
    qDebug() << "AppcastUpdateChecker::check()";
    
    if (!mAccessManager) {
        mAccessManager = new QNetworkAccessManager(this);
    }
    
    QNetworkRequest request;
    
    if (!mRequest.url().isEmpty()) {
        request = mRequest;
    } else {
        request = QNetworkRequest(mUrl);
    }
    request.setRawHeader("Accept", "application/rss+xml");
    
    mExchange = new NetworkExchange(request, this);
    mExchange->setNetworkAccessManager(mAccessManager);
    
    connect(mExchange, SIGNAL(replyReceived()), SLOT(onReplyReceived()));
    connect(mExchange, SIGNAL(readyRead()), SLOT(onReadyRead()));
    connect(mExchange, SIGNAL(finished()), SLOT(onFinished()));
    connect(mExchange, SIGNAL(error(quint32)), SLOT(onError(quint32)));
    
    mExchange->get();
}

QList<Update *> AppcastUpdateChecker::updates()
{
    // NOTE: Does not apply version sorting.  Expects it to be implied by the order
    //       of items in the feed.
    
    return mUpdates;
}

void AppcastUpdateChecker::setUrl(const QUrl & url)
{
    mUrl = url;
}

void AppcastUpdateChecker::setRequest(const QNetworkRequest & request)
{
    mRequest = request;
}

void AppcastUpdateChecker::setNetworkAccessManager(QNetworkAccessManager *manager)
{
    mAccessManager = manager;
}

void AppcastUpdateChecker::onReplyReceived()
{
    if (mXmlReader) {
        mXmlReader->setDelegate(0);
        mXmlReader->deleteLater();
    }
    
    mXmlReader = new XmlDeserializer();
    mXmlReader->setDelegate(this);
}

void AppcastUpdateChecker::onReadyRead()
{
    QByteArray data = mExchange->readAll();
    qDebug() << "  data: " << data.data();
    
    mXmlReader->addData(data);
    mXmlReader->parse();
}

void AppcastUpdateChecker::onFinished()
{
    mExchange->disconnect(this);
    mExchange->deleteLater();
    mExchange = 0;
}

void AppcastUpdateChecker::onError(quint32 code)
{
    Q_UNUSED(code)
 
    //qDebug() << "AppcastUpdateChecker::onError";
    //qDebug() << "   error: " << code;
    //qDebug() << "   string: " << mExchange->errorString();
    
    setErrorString(mExchange->errorString());
    emit error(-1);
}

void AppcastUpdateChecker::onItemParsed()
{
    mParsingItem->disconnect(this);
    
    AppcastUpdate *update = new AppcastUpdate(mParsingItem, this);
    mUpdates.append(update);
    mParsingItem = 0;
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
    //qDebug() << "AppcastUpdateChecker::xmlReadComplete()";
    
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
    
    if (/*kChannelXmlElementName == deserializer->parentName() &&*/ AppcastItem::kXmlElementName == name) {
        mParsingItem = new AppcastItem(this);
        connect(mParsingItem, SIGNAL(parsed()), SLOT(onItemParsed()));
        return mParsingItem;
    }
    
    return this;
}

void AppcastUpdateChecker::deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(name)
    Q_UNUSED(namespaceUri)
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


QTX_END_NAMESPACE
