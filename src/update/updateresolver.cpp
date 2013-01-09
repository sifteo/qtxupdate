#include "updateresolver.h"
#include "abstractupdatechecker.h"
#include "abstractupdatefilter.h"
#include "abstractversioncomparator.h"
#include "semverversioncomparator.h"
#include "update.h"

QTX_BEGIN_NAMESPACE


UpdateResolver::UpdateResolver(QObject *parent /* = 0 */)
  : QObject(parent),
    mChecker(0),
    mComparator(0)
{
}

UpdateResolver::~UpdateResolver()
{
}

void UpdateResolver::resolve()
{
    QCoreApplication *app = QCoreApplication::instance();
    if (app) {
        resolve(app->applicationVersion());
    }
}

void UpdateResolver::resolve(const QString & version)
{
    if (!mChecker) {
        emit error(InvalidCheckerError);
        return;
    }
    
    mVersion = version;
    mChecker->check();
}

Update *UpdateResolver::updateFrom(const QString & version)
{
    /*
     * If for some reason, we have failed to retrieve a proper version string
     * for the entity we're considering updating, decline the update.
     *
     * This change was specifically introduced to avoid prompting for an update
     * of the launcher or base firmware on Windows, in which we're currently
     * subject to a Qt bug in QProcess preventing us from capturing info
     * about the base from swiss.
     */

    if (version.isEmpty()) {
        return 0;
    }

    if (!mChecker) { return 0; }
    if (!mComparator) {
        mComparator = new SemVerVersionComparator(this);
    }
    
    // The checker is expected to build a list of available updates.  The
    // server that is queried for updates may filter this list based on
    // compatiblity information ascertained from the request (for example,
    // by inspecting a `User-Agent` header).
    QList<Update *> candidates = mChecker->updates();
    
    // Filter the list of candidates.  Filters are typically used to inspect
    // candidates, ensuring they satisfy minimum system requirements and
    // runtime compatibility.  If the server applied its own filtering, these
    // filters further refine the list of candidates based on information known
    // only by the client system.
    foreach (AbstractUpdateFilter *filter, mFilters) {
        candidates = filter->filter(candidates);
    }
    
    if (candidates.isEmpty()) {
        return 0;
    }
    
    // Candidates are assumed to be sorted in priority order.  Take the first
    // candidate (ie, the highest priority candidate) and check if it is more
    // recent than the given version.  If so, and update is available;
    // otherwise, no update is available.
    Update *update = candidates.at(0);
    int rv = mComparator->compare(update->version(), version);
    if (rv == 1) {
        return update;
    }
    return 0;
}

void UpdateResolver::setChecker(AbstractUpdateChecker *checker)
{
    if (mChecker) {
        mChecker->disconnect(this);
        mChecker->deleteLater();
    }
    
    checker->setParent(this);
    mChecker = checker;
    connect(mChecker, SIGNAL(finished()), SLOT(onCheckerFinished()));
    connect(mChecker, SIGNAL(error(qint32)), SLOT(onCheckerError(qint32)));
}

void UpdateResolver::setComparator(AbstractVersionComparator *comparator)
{
    if (mComparator) {
        mComparator->deleteLater();
    }
    
    comparator->setParent(this);
    mComparator = comparator;
}

void UpdateResolver::addFilter(AbstractUpdateFilter *filter)
{
    filter->setParent(this);
    mFilters.append(filter);
}

void UpdateResolver::onCheckerFinished()
{
    qDebug() << "UpdateResolver::onCheckerFinished";
    
    Update *update = updateFrom(mVersion);
    if (update) {
        emit updateAvailable(update);
    } else {
        emit noUpdateAvailable();
    }
}

void UpdateResolver::onCheckerError(qint32 code)
{
    qDebug() << "UpdateResolver::onCheckerError";
    qDebug() << "  code: " << code;
}


QTX_END_NAMESPACE
