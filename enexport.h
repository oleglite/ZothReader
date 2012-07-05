#ifndef ENEXPORT_H
#define ENEXPORT_H

#include <QtCore>
#include <QtXml>
#include <QtWebKit/QWebView>

class EnNote;

//! �����, �������������� ������ � ��������� �������� evernote.
class EnExport: public QThread
{
    Q_OBJECT
public:
    friend class Test_EnExport;

    //! ������������ ���� � ���������� ������ evernote.
    explicit EnExport(QObject* parent = 0);
    ~EnExport();

    void run();

    //! ���������� ������ @p query � evernote. ���������� true, ���� ������ ���������, ����� false.
    bool loadNotes(const QString& query);
    void setNotesToView(QWebView*);
    QList<EnNote*> getNotes() const;

    void setQuery(const QString&);

    bool isExportAvaliable() const;

signals:
    //! ������, ���������� ����� ������� ������� ��������.
    void exported();

public slots:
    void openNote(const QString&);

private slots:
    //! ����, �������������� ���������� �� �������� mEnProcess ������.
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
