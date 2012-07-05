#include "mainwindow.h"

#include "enexport.h"
#include "settingsdialog.h"
#include "hellodialog.h"

#include "enview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mDialog(0),
    mWebView(0),
    mCurrentNoteIndex(0)
{
    loadSettings();
    checkExistenceTempImgDir();

    setWindowTitle(tr("Zoth Reader"));
    setWindowIcon(QIcon(":/images/green_book_zoth.png"));
    createCentralWidget();
    //showFullScreen();
    showMaximized();
    setContextMenuPolicy(Qt::NoContextMenu);
    mDialog = new SettingsDialog();

    connect(&mEnExport, SIGNAL(exported()), SLOT(notesReloaded()));
    connect(&mEnExport, SIGNAL(exported()), SLOT(displayNotes()));
    connect(&mEnExport, SIGNAL(exported()), SLOT(refreshNavigationLabel()));
    connect(mDialog, SIGNAL(accepted()), SLOT(saveDialogSettings()));

    if(isFirstRun){
        HelloDialog* helloDialog = new HelloDialog(this);
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(mBgColor));
        helloDialog->setPalette(palette);
        helloDialog->setBackgroundRole(QPalette::Window);
        helloDialog->activateWindow();
        helloDialog->show();
        connect(helloDialog, SIGNAL(tagAccepted(QString)), SLOT(setTagAndReload(QString)));
    }else{
        reloadNotes();
    }
}

MainWindow::~MainWindow(){
    saveSettings();
}

void MainWindow::createCentralWidget()
{
    mWebView = new EnView(this);
    mWebView->setContextMenuPolicy(Qt::NoContextMenu);
    if(isFirstRun)
        mWebView->setHtml(defaultPage(false));
    else
        mWebView->setHtml(defaultPage(true));

    connect(mWebView, SIGNAL(noteClicked(QString)), &mEnExport, SLOT(openNote(QString)));
    //connect(mWebView, SIGNAL(linkClicked(QUrl)), SLOT(openUrl(QUrl)));

    QPalette navigationPalette;
    navigationPalette.setColor(QPalette::Window, QColor(mBgColor));

    mToolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, mToolBar);
    mToolBar->setBackgroundRole(QPalette::Window);
    mToolBar->setAutoFillBackground(true);
    mToolBar->setPalette(navigationPalette);
    mToolBar->setMovable(false);
    mToolBar->setIconSize(QSize(30, 30));

    //mPageNumberLabel = new QLabel("4 / 7", this);
    //mPageNumberLabel->setFont(QFont("Times", 18));

    QAction* settingsAction = new QAction(QIcon(":/images/gear2.png"), tr("Settings"), mToolBar);
    QAction* prevAction = new QAction(QIcon(":/images/prev.png"), tr("Prev"), mToolBar);
    QAction* nextAction = new QAction(QIcon(":/images/next.png"), tr("Next"), mToolBar);

    mToolBar->addAction(settingsAction);
    mToolBar->addAction(prevAction);
    mToolBar->addAction(nextAction);

    mNavigationLabel = new QLabel(mToolBar);
    mNavigationLabel->setFont(QFont("Times", 18));
    mToolBar->addWidget(mNavigationLabel);

    connect(settingsAction, SIGNAL(triggered()), SLOT(loadDialogSettings()));
    //connect(settingsAction, SIGNAL(triggered()), mDialog, SLOT(show()));
    connect(prevAction, SIGNAL(triggered()), SLOT(prevNote()));
    connect(nextAction, SIGNAL(triggered()), SLOT(nextNote()));

    setCentralWidget(mWebView);
}

void MainWindow::saveDialogSettings(){
    const QString& dialogTag = mDialog->mTagEdit->text();
    const QString& dialogBgColor = mDialog->mBgColorDialog->currentColor().name();
    int dialogPageWidth = mDialog->mPageWidthEdit->text().toInt();

    if ( mTag == dialogTag && mBgColor == dialogBgColor && mPageWidth == dialogPageWidth){
        return;
    } else {
        if(dialogBgColor != mBgColor){
            QPalette navigationPalette;
            navigationPalette.setColor(QPalette::Window, QColor(dialogBgColor));
            mToolBar->setPalette(navigationPalette);
        }
        mTag = dialogTag;
        mBgColor = dialogBgColor;
        mPageWidth = dialogPageWidth;
        if(mPageWidth < 0)
            mPageWidth = 600;
        reloadNotes();
    }
}

void MainWindow::loadDialogSettings(){
    mDialog->mTagEdit->setText(mTag);
    mDialog->mBgColorDialog->setCurrentColor(QColor(mBgColor));
    mDialog->mPageWidthEdit->setText(QString::number(mPageWidth));
    mDialog->show();
}

void MainWindow::displayNotes(){
    qDebug() << "displayNotes";

    mEnDisplay.setBgColor(mBgColor);
    mEnDisplay.setPageWidth(mPageWidth);

    QTime time;
    time.start();

    const QString& page = mEnDisplay.display(mEnNotes.value(mCurrentNoteIndex, 0), defaultPage());
    qDebug("timer: mEnDisplay.display() %d ms", time.elapsed());

    time.start();

    mWebView->setHtml(page);
    qDebug("timer: mWebView->setHtml %d ms", time.elapsed());

    refreshNavigationLabel();
}

void MainWindow::loadSettings(){
    checkFirstRun();
    QSettings settings("Lite Soft", "EnReader");
    settings.beginGroup("EnDisplay");

    mTag = settings.value("tag", QString("read")).toString();
    mBgColor = settings.value("bgColor", QString("#efefef")).toString();
    mPageWidth = settings.value("pageWidth", 600).toInt();

    settings.endGroup();
}

void MainWindow::saveSettings(){
    QSettings settings("Lite Soft", "EnReader");
    settings.beginGroup("EnDisplay");

    settings.setValue("tag", mTag);
    settings.setValue("bgColor", mBgColor);
    settings.setValue("pageWidth", mPageWidth);

    settings.endGroup();
}

void MainWindow::reloadNotes(){
    if(mTag.isEmpty()){
        mEnNotes.clear();
        displayNotes();
        return;
    }

    QString query = "tag:" + mTag;
    qDebug() << query;

    mNavigationLabel->setText("loading...");
    mEnExport.setQuery(query);
    mEnExport.start();
}

void MainWindow::notesReloaded(){
    mEnNotes = mEnExport.getNotes();
}

void MainWindow::nextNote(){
    if(mCurrentNoteIndex + 1 < mEnNotes.count())
        mCurrentNoteIndex++;
    displayNotes();

    /*
    if(mCurrentNoteIndex + 1 == mEnNotes.count())
        mNextButton->setVisible(false);
    if(mCurrentNoteIndex == 1)
        mPrevButton->setVisible(true);*/
}

void MainWindow::prevNote(){
    if(mCurrentNoteIndex > 0)
        mCurrentNoteIndex--;
    displayNotes();
    /*
    if(mCurrentNoteIndex + 2 == mEnNotes.count())
        mNextButton->setVisible(true);
    if(mCurrentNoteIndex == 0)
        mPrevButton->setVisible(false);*/
}

void MainWindow::refreshNavigationLabel(){
    if(mEnNotes.count() == 0)
        mNavigationLabel->setText(tr("empty"));
    else
        mNavigationLabel->setText(" " + QString::number(mCurrentNoteIndex + 1) + " / " + QString::number(mEnNotes.count()));
}

QString MainWindow::defaultPage(bool putLabel) const{
    if(!putLabel)
        return "<body bgcolor=\"" + mBgColor + "\"></body>";
    else
        return "<body bgcolor=\"" + mBgColor + "\"><div style=\"margin-top:120px;\"align=\"center\"><img src=\"d:/Development/Qt/EvernoteReader/images/zoth.png\" /></div></body>";
}

void MainWindow::checkFirstRun(){
    QSettings settings("Lite Soft", "EnReader");
    settings.beginGroup("EnDisplay");

    isFirstRun = settings.value("isFirstRun", QVariant(true)).toBool();
    if(isFirstRun)
        settings.setValue("isFirstRun", QVariant(false));

    settings.endGroup();
}

void MainWindow::setTagAndReload(const QString& newTag){
    mTag = newTag;
    mWebView->setHtml(defaultPage());
    reloadNotes();
}

void MainWindow::checkExistenceTempImgDir() const{
    if (!QDir("c:/TEMP/zothReader").exists()){
        QDir().mkdir("c:/TEMP/zothReader");
    }
    if (!QDir("c:/TEMP/zothReader/img").exists()){
        QDir().mkdir("c:/TEMP/zothReader/img");
    }
}

void MainWindow::openUrl(const QUrl& url){
    qDebug() << "MainWindow::openUrl";
    QDesktopServices::openUrl(url);
}
