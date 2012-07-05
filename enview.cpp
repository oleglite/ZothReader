#include "enview.h"
#include <QDebug>

EnView::EnView(QWidget *parent) :
    QWebView(parent)
{
    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(this, SIGNAL(linkClicked(QUrl)), SLOT(openUrl(QUrl)));
}

void EnView::load(const QUrl &url){
    qDebug() << "EnView::load";
}

void EnView::openUrl(const QUrl& url){
    qDebug() << "openUrl";
    if(url.toString().startsWith("__zothreader__="))
        emit noteClicked(url.toString().mid(15));
    else
        QDesktopServices::openUrl(url);
}


/*
void EnView::setENML(const QString& src)
{
    QString page = substringBetween(src, "<en-note>", "</en-note>");
    changeStyles(page);
    //QString page = src;
    //page.replace("en-note", "body");

    setContent(QByteArray().append(page));
}

QString EnView::substringBetween(const QString& src, const QString& from, const QString& to)
{
    int fromPos = src.indexOf(from) + from.length();
    int number = src.indexOf(to) - fromPos;
    return src.mid(fromPos, number);
    return QString();
}

QString& EnView::deleteAttibute(QString& str, const QString& attr)
{
    int pos = 0;
    while(pos >= 0){
        pos = str.indexOf(attr + ':');
        str.remove(pos, str.indexOf(QString(';'), pos) - pos);
    }
    return str;
}

QString& EnView::changeStyles(QString& page)
{
    deleteAttibute(page, "background");
    deleteAttibute(page, "background-color");

    page = "<body bgcolor=\"#eeeeee\"><div style=\"margin-left:200px;margin-right:200px;background-color:#eeeeee;\">" +
            page +
            "</div></body>";

    page.replace("background-repeat: initial initial;", "");
    page.replace("margin-top:0px;", "");
    page.replace("margin-right:0px;", "");
    page.replace("margin-left:0px;", "");
    page.replace("margin-bottom:0px;", "");
    page.replace("padding-top:0px;", "");
    page.replace("padding-right:0px;", "");
    page.replace("padding-left:0px;", "");
    page.replace("padding-bottom:0px;", "");

    return page;
}
*/

