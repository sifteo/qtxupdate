#include "appcastupdatechecker.h"
#include "appcastupdate.h"
#include "appcastitem.h"
#include <QtxNetwork>


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
    
    mXmlReader = new XmlReader();
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

IXmlDeserializer* AppcastUpdateChecker::rootXmlDeserializer(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(reader)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(name)
    Q_UNUSED(attributes)
    
    return this;
}

void AppcastUpdateChecker::xmlReadComplete(XmlReader* reader)
{
    //qDebug() << "AppcastUpdateChecker::xmlReadComplete()";
    
    Q_UNUSED(reader)
    
    emit finished();
}

void AppcastUpdateChecker::xmlReadError(XmlReader* reader, const QXmlStreamReader::Error err, const QString & errorString)
{
    Q_UNUSED(reader)
    Q_UNUSED(err)
    Q_UNUSED(errorString)
    
    setErrorString("invalid appcast XML");
    emit error(-1);
}

IXmlDeserializer* AppcastUpdateChecker::deserializeXmlStartElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(reader)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(attributes)
    
    if (kChannelXmlElementName == reader->parentName() && AppcastItem::kXmlElementName == name) {
        mParsingItem = new AppcastItem(this);
        connect(mParsingItem, SIGNAL(parsed()), SLOT(onItemParsed()));
        return mParsingItem;
    }
    
    return this;
}

void AppcastUpdateChecker::deserializeXmlEndElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name)
{
    Q_UNUSED(reader)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(name)
}

void AppcastUpdateChecker::deserializeXmlAttributes(XmlReader* reader, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(reader)
    Q_UNUSED(attributes)
}

void AppcastUpdateChecker::deserializeXmlCharacters(XmlReader* reader, const QStringRef & text)
{
    Q_UNUSED(reader)
    Q_UNUSED(text)
}
