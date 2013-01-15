#include "tst_appcastitem.h"


void tst_AppcastItem::init()
{
    mDeserializer = new XmlDeserializer();
    mDeserializer->setDelegate(this);
    
    mItem = 0;
}

void tst_AppcastItem::cleanup()
{
    if (mItem) {
        delete mItem;
        mItem = 0;
    }

    if (mDeserializer) {
        delete mDeserializer;
        mDeserializer = 0;
    }
}

void tst_AppcastItem::readElement()
{
    QFile file("data/element.xml");
    file.open(QIODevice::ReadOnly);
    
    mDeserializer->addData(file.readAll());
    mDeserializer->parse();

    QVERIFY(mItem);
    QCOMPARE(mItem->title(), QString("Version 2.0 (2 bugs fixed; 3 new features)"));
    QCOMPARE(mItem->version(), QString("2.0"));
    QCOMPARE(mItem->linkUrl(), QUrl("http://you.com/app/index.html"));
    QCOMPARE(mItem->minSystemVersion(), QString(""));
    
    QVERIFY(mItem->enclosure());
}

void tst_AppcastItem::readMinimumSystemVersion()
{
    QFile file("data/minimumSystemVersion.xml");
    file.open(QIODevice::ReadOnly);
    
    mDeserializer->addData(file.readAll());
    mDeserializer->parse();

    QVERIFY(mItem);
    QCOMPARE(mItem->title(), QString("Version 2.0 (2 bugs fixed; 3 new features)"));
    QCOMPARE(mItem->version(), QString("2.0"));
    QCOMPARE(mItem->linkUrl(), QUrl("http://you.com/app/index.html"));
    QCOMPARE(mItem->minSystemVersion(), QString("10.6.0"));
    
    QVERIFY(mItem->enclosure());
}

IXmlDeserializing* tst_AppcastItem::deserializeXmlStart(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(attributes)

    if (name == AppcastItem::xmlName()) {
        mItem = new AppcastItem();
        return mItem;
    }
    
    return 0;
}

void tst_AppcastItem::deserializeXmlEnd(XmlDeserializer *deserializer)
{
    Q_UNUSED(deserializer)
}

void tst_AppcastItem::deserializeXmlError(XmlDeserializer *deserializer, const QXmlStreamReader::Error error, const QString & errorString)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(error)
    Q_UNUSED(errorString)
}


QTEST_APPLESS_MAIN(tst_AppcastItem)
