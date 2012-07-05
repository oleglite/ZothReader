#ifndef ENEXPORT_H
#define ENEXPORT_H

#include <QtCore>
#include <QtXml>
#include <QtWebKit/QWebView>

class EnNote;

//! Класс, обеспечивающий работу с разметкой экспорта evernote.
class EnExport: public QThread
{
    Q_OBJECT
public:
    friend class Test_EnExport;

    //! Определяется путь к исплняемым файлам evernote.
    explicit EnExport(QObject* parent = 0);
    ~EnExport();

    void run();

    //! Отправляет запрос @p query в evernote. Возвращает true, если запрос отправлен, иначе false.
    bool loadNotes(const QString& query);
    void setNotesToView(QWebView*);
    QList<EnNote*> getNotes() const;

    void setQuery(const QString&);

    bool isExportAvaliable() const;

signals:
    //! Сигнал, посылается когда экспорт заметок завершён.
    void exported();

public slots:
    void openNote(const QString&);

private slots:
    //! Слот, обрабатывающий полученные от процесса mEnProcess данные.
    void readExport();

private:
    QTime mTimer;

    QString mEnScriptPath;
    QString mEvernotePath;
    QString mQuery;

    QProcess* mEnProcess;
    QList<EnNote*> mEnNotes;
};

#endif // ENEXPORT_H
