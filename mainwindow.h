#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtWebKit/QWebView>

#include "enexport.h"
#include "endisplay.h"

class SettingsDialog;
class EnView;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createCentralWidget();

private slots:
    void saveDialogSettings();
    void loadDialogSettings();
    void displayNotes();
    void reloadNotes();
    void notesReloaded();

    void nextNote();
    void prevNote();

    void refreshNavigationLabel();
    void setTagAndReload(const QString&);

    void openUrl(const QUrl&);

private:
    EnView* mWebView;
    SettingsDialog* mDialog;
    QToolBar* mToolBar;
    QLabel* mNavigationLabel;

    QLabel* mPageNumberLabel;

    EnExport mEnExport;
    EnDisplay mEnDisplay;

    QList<EnNote*> mEnNotes;
    int mCurrentNoteIndex;

    // Settings
    QString mTag;
    QString mBgColor;
    int mPageWidth;

    bool isFirstRun;

private:

    //QString openFileAsString(const QString& mFileName);
    QByteArray openFileAsByteArray(const QString& fileName);
    QString defaultPage(bool putLabel = true) const;

    void loadSettings();
    void saveSettings();

    void checkFirstRun();

    void checkExistenceTempImgDir() const;

    //void setupDisplaySetttings();
};

#endif // MAINWINDOW_H
