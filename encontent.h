#ifndef ENNOTECONTENT_H
#define ENNOTECONTENT_H

#include <QString>

class EnContent
{
public:
    EnContent(const QString& content);

    void processMedias();

    QString mNoteContent;

private:
    static QString& cutTag(QString& src, const QString& tag);

    static QString getAttributeValueFromTag(const QString& src, int tagBegin, int tagEnd, const QString& attribute);

};

#endif // ENNOTECONTENT_H
