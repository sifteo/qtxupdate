#ifndef QTXUPDATE_UPDATEDIALOG_H
#define QTXUPDATE_UPDATEDIALOG_H

#ifdef QT_WIDGETS_LIB
#include <QtWidgets>
#else
#include <QtGui>
#endif


namespace Ui {
    class UpdateDialog;
}

class UpdateDialog : public QDialog
{
    Q_OBJECT
    
public:
    UpdateDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~UpdateDialog();
    
    void setApplicationName(const QString & application);
    void setApplicationVersion(const QString & version);
    void setCurrentVersion(const QString & version);
    void setUpdateVersion(const QString & version);
    void setReleaseNotesUrl(const QUrl & url);
    
    void hideReleaseNotes();
    
signals:
    void versionSkipped(const QString & version);
    
protected:
    bool event(QEvent *event);
    void polishEvent(QEvent *event);
    void showEvent(QShowEvent * event);
    void resizeEvent(QResizeEvent *event);
    
private slots:
    void onSkipClicked(bool checked = false);
    
private:
    Ui::UpdateDialog *mUi;
    bool mNotesNeedHide;
    
    QString mApplication;
    QString mCurrentVersion;
    QString mUpdateVersion;
};

#endif // QTXUPDATE_UPDATEDIALOG_H
