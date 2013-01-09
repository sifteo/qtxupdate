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
}

IXmlDeserializing* tst_AppcastEnclosure::deserializeXmlStart(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes)
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
