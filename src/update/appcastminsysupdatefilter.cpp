#include "appcastminsysupdatefilter.h"
#include "appcastupdate.h"
#include <QtxVersion>

QTX_BEGIN_NAMESPACE


class AppcastMinSysUpdateFilterPrivate
{
public:
    static Version osVersion();
    
    Version sysVersion;
};


AppcastMinSysUpdateFilter::AppcastMinSysUpdateFilter(QObject *parent /* = 0 */)
    : AbstractUpdateFilter(parent),
      d_ptr(new AppcastMinSysUpdateFilterPrivate())
{
    d_ptr->sysVersion = AppcastMinSysUpdateFilterPrivate::osVersion();
}

AppcastMinSysUpdateFilter::AppcastMinSysUpdateFilter(const QString & version, QObject *parent /* = 0 */)
    : AbstractUpdateFilter(parent),
      d_ptr(new AppcastMinSysUpdateFilterPrivate())
{
    d_ptr->sysVersion = Version(version);
}

AppcastMinSysUpdateFilter::~AppcastMinSysUpdateFilter()
{
}

QList<Update *> AppcastMinSysUpdateFilter::filter(const QList<Update *> candidates)
{
    QList<Update *> filtered;
    foreach (Update *candidate, candidates) {
        AppcastUpdate *update = qobject_cast<AppcastUpdate *>(candidate);
        if (update) {
            Version systemVersion = d_ptr->sysVersion;
            Version minSystemVersion(update->minSysVersion());
            
            if (!systemVersion.isValid()) {
                // An unknown system is typically a newer version of the OS than
                // what was available at the time the application was built.
                // Assume compatiblity until proven otherwise.
                filtered.append(candidate);
                continue;
            }
            if (!minSystemVersion.isValid()) {
                // The minimum version was not specified, which means any
                // version is acceptable.
                filtered.append(candidate);
                continue;
            }
            
            if (systemVersion >= minSystemVersion) {
                filtered.append(candidate);
                continue;
            }
        } else {
            // This is not a type understood by this filter.  Let it through so
            // other filters in the chain get a chance to handle it.
            filtered.append(candidate);
            continue;
        }
    }
    
    return filtered;
}

Version AppcastMinSysUpdateFilterPrivate::osVersion()
{
#if defined Q_OS_WIN
    switch (QSysInfo::WindowsVersion) {
        case QSysInfo::WV_95: return Version("4.00.950");    // http://support.microsoft.com/kb/158238
        case QSysInfo::WV_98: return Version("4.10.1998");   // http://support.microsoft.com/kb/158238
        case QSysInfo::WV_Me: return Version("4.90.3000");   // http://support.microsoft.com/kb/158238
        case QSysInfo::WV_4_0: return Version("4.0");  // QSysInfo::WV_NT
        case QSysInfo::WV_5_0: return Version("5.0");  // QSysInfo::WV_2000
        case QSysInfo::WV_5_1: return Version("5.1");  // QSysInfo::WV_XP
        case QSysInfo::WV_5_2: return Version("5.2");  // QSysInfo::WV_2003
        case QSysInfo::WV_6_0: return Version("6.0");  // QSysInfo::WV_VISTA
        case QSysInfo::WV_6_1: return Version("6.1");  // QSysInfo::WV_WINDOWS7
#if QT_VERSION >= 0x050000
        case QSysInfo::WV_6_2: return Version("6.2");  // QSysInfo::WV_WINDOWS8
#endif
        default: return Version();
    }
#elif defined Q_OS_MAC
    switch (QSysInfo::MacintoshVersion) {
        case QSysInfo::MV_10_0: return Version("10.0");  // QSysInfo::MV_CHEETAH
        case QSysInfo::MV_10_1: return Version("10.1");  // QSysInfo::MV_PUMA
        case QSysInfo::MV_10_2: return Version("10.2");  // QSysInfo::MV_JAGUAR
        case QSysInfo::MV_10_3: return Version("10.3");  // QSysInfo::MV_PANTHER
        case QSysInfo::MV_10_4: return Version("10.4");  // QSysInfo::MV_TIGER
        case QSysInfo::MV_10_5: return Version("10.5");  // QSysInfo::MV_LEOPARD
        case QSysInfo::MV_10_6: return Version("10.6");  // QSysInfo::MV_SNOWLEOPARD
#if QT_VERSION >= 0x040800
        case QSysInfo::MV_10_7: return Version("10.7");  // QSysInfo::MV_LION
#endif
#if QT_VERSION >= 0x050000
        case QSysInfo::MV_10_8: return Version("10.8");  // QSysInfo::MV_MOUNTAINLION
#endif
        default: return Version();
    }
#endif
    
    return Version();
}


QTX_END_NAMESPACE
