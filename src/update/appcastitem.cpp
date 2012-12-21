#include "appcastitem.h"
#include "appcastenclosure.h"


const char AppcastItem::kSparkleXmlNamespace[] = "http://www.andymatuschak.org/xml-namespaces/sparkle";
const char AppcastItem::kXmlElementName[] = "item";
const char AppcastItem::kTitleXmlElementName[] = "title";
const char AppcastItem::kLinkXmlElementName[] = "link";
const char AppcastItem::kMinimumSystemVersionXmlElementName[] = "minimumSystemVersion";

AppcastItem::AppcastItem(QObject *parent /* = 0 */)
    : QObject(parent),
      mParsingEnclosure(0),
      mDepth(0)
{
}

AppcastItem::~AppcastItem()
{
}

QString AppcastItem::title() const
{
    return mTitle;
}

QString AppcastItem::version() const
{
    return mVersion;
}

QUrl AppcastItem::linkUrl() const
{
    return mLinkUrl;
}

const AppcastEnclosure *AppcastItem::enclosure() const
{
    if (mEnclosures.isEmpty()) {
        return 0;
    }
    
    return mEnclosures.at(0);
}

QString AppcastItem::minSystemVersion() const
{
    return mMinSystemVersion;
}

void AppcastItem::onEnclosureParsed()
{
    mParsingEnclosure->disconnect(this);
    
    mEnclosures.append(mParsingEnclosure);
    if (mEnclosures.size() == 1) {
        // Sparkle's RSS extension is rather poorly specified.  The version is
        // logically associated with the item, but is indicated as an attribute
        // of the enclosure (of which there can be many, in the case of
        // per-platform enclosures).  The version of the first enclosure will be
        // treated as the item's version.  For consistency, it is recommended
        // that any item containing multiple enclosures indicates an identical
        // version for each.
        mVersion = mParsingEnclosure->version();
    }
    
    mParsingEnclosure = 0;
}

IXmlDeserializer* AppcastItem::deserializeXmlStartElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(reader)
    Q_UNUSED(namespaceUri)
    Q_UNUSED(name)
    Q_UNUSED(attributes)
    
    if (AppcastEnclosure::kXmlElementName == name) {
        mParsingEnclosure = new AppcastEnclosure(this);
        connect(mParsingEnclosure, SIGNAL(parsed()), SLOT(onEnclosureParsed()));
        return mParsingEnclosure;
    }
    
    mDepth++;
    return this;
}

void AppcastItem::deserializeXmlEndElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name)
{
    Q_UNUSED(reader)
    
    if (!mDepth) {
        emit parsed();
        return;
    }
    
    if (kTitleXmlElementName == name) {
        mTitle = mCharacters.trimmed();
    } else if (kLinkXmlElementName == name) {
        mLinkUrl = QUrl(mCharacters.trimmed());
    } else if (namespaceUri == kSparkleXmlNamespace && kMinimumSystemVersionXmlElementName == name) {
        mMinSystemVersion = mCharacters.trimmed();
    }
    
    mDepth--;
    mCharacters.clear();
}

void AppcastItem::deserializeXmlAttributes(XmlReader* reader, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(reader)
    Q_UNUSED(attributes)
}

void AppcastItem::deserializeXmlCharacters(XmlReader* reader, const QStringRef & text)
{
    Q_UNUSED(reader)
    
    mCharacters.append(text);
}
