#include "updatedialog.h"
#include "ui_updatedialog.h"


// 520x390

UpdateDialog::UpdateDialog(QWidget *parent /* = 0 */, Qt::WindowFlags f /* = 0 */)
    : QDialog(parent, f),
      mUi(0),
      mNotesNeedHide(false)
{
    mUi = new Ui::UpdateDialog();
    mUi->setupUi(this);
    connect(mUi->skipButton, SIGNAL(clicked(bool)), SLOT(onSkipClicked(bool)));
    
    QPixmap pixmap = qApp->windowIcon().pixmap(64);
    mUi->iconLabel->setPixmap(pixmap);
    
    mUi->buttonBox->button(QDialogButtonBox::Ok)->setFocus();
}

UpdateDialog::~UpdateDialog()
{
    qDebug() << "UpdateDialog::~UpdateDialog";
}

void UpdateDialog::setApplicationName(const QString & application)
{
    mApplication = application;
}

void UpdateDialog::setApplicationVersion(const QString & version)
{
    setCurrentVersion(version);
}

void UpdateDialog::setCurrentVersion(const QString & version)
{
    mCurrentVersion = version;
}

void UpdateDialog::setUpdateVersion(const QString & version)
{
    mUpdateVersion = version;
}

void UpdateDialog::setReleaseNotesUrl(const QUrl & url)
{
    mUi->webView->setUrl(url);
}

void UpdateDialog::hideReleaseNotes()
{
    mNotesNeedHide = true;
}

bool UpdateDialog::event(QEvent *event)
{
    if (QEvent::Polish == event->type()) {
        polishEvent(event);
    }
    
    return QDialog::event(event);
}

void UpdateDialog::polishEvent(QEvent *event)
{
    Q_UNUSED(event);
    
    if (mApplication.isEmpty()) {
        setApplicationName(qApp->applicationName());
    }
    if (mCurrentVersion.isEmpty()) {
        setApplicationVersion(qApp->applicationVersion());
    }
    
    QString title = QString("A new version of %1 is available!")
                      .arg(mApplication);
    QString description = QString("%1 %2 is now available (you have %3).  Would you like to install it now?")
                            .arg(mApplication)
                            .arg(mUpdateVersion)
                            .arg(mCurrentVersion);
                            
    mUi->titleLabel->setText(title);
    mUi->descriptionLabel->setText(description);
}

void UpdateDialog::showEvent(QShowEvent * event)
{
    if (!mNotesNeedHide) {
        return;
    }
    
    QSize size = this->size();
    QSize notesSize = mUi->frame->size();
    
    mUi->frame->hide();
    this->resize(size.width(), size.height() - notesSize.height());
    mNotesNeedHide = false;
    
    QDialog::showEvent(event);
}

void UpdateDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
}

void UpdateDialog::onSkipClicked(bool checked /* = false */)
{
    Q_UNUSED(checked)
     
    emit versionSkipped(mUpdateVersion);
    reject();
}
