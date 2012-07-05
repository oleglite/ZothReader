#include "enexport.h"
#include "enexportparser.h"

#include "ennote.h"
#include "endisplay.h"

EnExport::EnExport(QObject* parent) :
    QThread(parent),
    mEnProcess(0)
{
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths", QSettings::NativeFormat);
    mEnScriptPath =  settings.value("ENScript.exe/Default", "").toString();
    mEvernotePath =  settings.value("Evernote.exe/Default", "").toString();

    Q_ASSERT(mEnScriptPath != "" && mEvernotePath != "");

    mEnProcess = new QProcess;
    //connect(mEnProcess, SIGNAL(finished(int)), SLOT(readExport()));
}

EnExport::~EnExport(){
    delete mEnProcess;
    foreach(EnNote* note, mEnNotes){
        delete note;
    }
}

void EnExport::run(){
    loadNotes(mQuery);
}

bool EnExport::loadNotes(const QString& query){
    mTimer.start();

    if(query.isEmpty())
        return false;

    // проверяем запущен ли процесс
    if(mEnProcess->isOpen()){
        mEnProcess->close();
        qDebug() << "forced closing";
        return false;
    }

    // аргументы для запуска процесса
    QStringList arguments;
    arguments << "exportNotes" << "/q" << query;

    mEnProcess->start(mEnScriptPath, arguments);
    mEnProcess->waitForFinished();
    readExport();
    return true;
}

void EnExport::readExport(){
    foreach(EnNote* note, mEnNotes){
        delete note;
    }
    mEnNotes = EnExportParser::readFromIO(mEnProcess);
    emit exported();
    foreach(EnNote* note, mEnNotes){
        //qDebug() << note->toString();
    }
    qDebug() << "total " + QString::number(mEnNotes.count());
    qDebug("timer: export %d ms", mTimer.elapsed());
}

void EnExport::setNotesToView(QWebView* view){
    EnDisplay disp;
    view->setHtml(disp.display(mEnNotes));
}

QList<EnNote*> EnExport::getNotes() const{
    return mEnNotes;
}

void EnExport::setQuery(const QString& query){
    mQuery = query;
}

bool EnExport::isExportAvaliable() const{
    return mEnScriptPath != ""/* && mEvernotePath != ""*/;
}

void EnExport::openNote(const QString& title){
    // аргументы для запуска процесса
    QStringList arguments;
    arguments << "showNotes" << "/q" << '"' + title + '"';

    mEnProcess->start(mEnScriptPath, arguments);
}
