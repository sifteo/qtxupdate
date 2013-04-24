#include "tst_appcastenclosure.h"


void tst_AppcastEnclosure::init()
{
    mDeserializer = new XmlDeserializer();
    mDeserializer->setDelegate(this);
    
    mEnclosure = 0;
}

void tst_AppcastEnclosure::cleanup()
{
    if (mEnclosure) {
        delete mEnclosure;
        mEnclosure = 0;
    }

    if (mDeserializer) {
        delete mDeserializer;
        mDeserializer = 0;
    }
}

void tst_AppcastEnclosure::readElement()
{
    QFile file("data/element.xml");
    file.open(QIODevice::ReadOnly);
    
    mDeserializer->addData(file.readAll());
    mDeserializer->parse();

    QVERIFY(mEnclosure);
    QCOMPARE(mEnclosure->version(), QString("2.0"));
    QCOMPARE(mEnclosure->url(), QUrl("http://you.com/app/Your Great App 2.0.zip"));
    QCOMPARE(mEnclosure->mimeType(), QString("application/octet-stream"));
    QCOMPARE(mEnclosure->md5Sum(), QString(""));
}

void tst_AppcastEnclosure::readElementWithMd5Sum()
{
    QFile file("data/md5Sum.xml");
    file.open(QIODevice::ReadOnly);
    
    mDeserializer->addData(file.readAll());
    mDeserializer->parse();

    QVERIFY(mEnclosure);
    QCOMPARE(mEnclosure->version(), QString("1.3.10"));
    QCOMPARE(mEnclosure->url(), QUrl("http://adiumx.cachefly.net/Adium_1.3.10.dmg"));
    QCOMPARE(mEnclosure->mimeType(), QString("application/octet-stream"));
    QCOMPARE(mEnclosure->md5Sum(), QString("16309a78add9dc7695ccc14079baae10"));
}

IXmlDeserializing* tst_AppcastEnclosure::deserializeXmlStart(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(attributes)

    if (name == AppcastEnclosure::xmlName()) {
        mEnclosure = new AppcastEnclosure();
        return mEnclosure;
    }
    
    return 0;
}

void tst_AppcastEnclosure::deserializeXmlEnd(XmlDeserializer *deserializer)
{
    Q_UNUSED(deserializer)
}

void tst_AppcastEnclosure::deserializeXmlError(XmlDeserializer *deserializer, const QXmlStreamReader::Error error, const QString & errorString)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(error)
    Q_UNUSED(errorString)
}


QTEST_APPLESS_MAIN(tst_AppcastEnclosure)
