#ifndef READER_H
#define READER_H

#include <QtWebKit>
#include <QDesktopServices>

class EnView : public QWebView
{
    Q_OBJECT
public:
    explicit EnView(QWidget *parent = 0);

    void load(const QUrl &url);

signals:
    void noteClicked(const QString&);

public slots:
    void openUrl(const QUrl&);


/*
    void setENML(const QString&);
    void setENML(const QByteArray&);

private:
    static QString substringBetween(const QString& src, const QString& from, const QString& to);
    static QString& deleteAttibute(QString&, const QString&);
    static QString& changeStyles(QString&);*/
};

#endif // READER_H
