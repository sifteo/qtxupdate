#ifndef TST_APPCASTITEM_H
#define TST_APPCASTITEM_H

#include "appcastitem.h"
#include <QtxXml>
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_AppcastItem : public QObject,
                        public IXmlDeserializerDelegate
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    
    void readElement();
    
protected:
    virtual IXmlDeserializing* deserializeXmlStart(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes);
    virtual void deserializeXmlEnd(XmlDeserializer *deserializer);
    virtual void deserializeXmlError(XmlDeserializer *deserializer, const QXmlStreamReader::Error error, const QString & errorString);
    
private:
    XmlDeserializer *mDeserializer;
    AppcastItem *mItem;
};

#endif // TST_APPCASTITEM_H
