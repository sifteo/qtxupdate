#include "versionlimitupdatefilter.h"
#include "update.h"
#include <QtxVersion>

QTX_BEGIN_NAMESPACE


class VersionLimitUpdateFilterPrivate
{
public:
    Version version;
};


VersionLimitUpdateFilter::VersionLimitUpdateFilter(const QString & version, QObject *parent /* = 0 */)
    : AbstractUpdateFilter(parent),
      d_ptr(new VersionLimitUpdateFilterPrivate())
{
    d_ptr->version = Version(version);
}

VersionLimitUpdateFilter::~VersionLimitUpdateFilter()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

QList<Update *> VersionLimitUpdateFilter::filter(const QList<Update *> candidates)
{
    QList<Update *> filtered;
    
    foreach (Update *candidate, candidates) {
        Version v(candidate->version());
        if (v < d_ptr->version) {
            filtered.append(candidate);
        }
    }
    
    return filtered;
}


QTX_END_NAMESPACE
