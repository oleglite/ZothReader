#include "encontent.h"
#include "encontentparser.h"

#include <QDebug>

EnContent::EnContent(const QString& content){
    mNoteContent = content;
    cutTag(mNoteContent, "en-note");
}

QString& EnContent::cutTag(QString& src, const QString& tag){
    int indexBegin = src.indexOf('<' + tag);
    indexBegin = src.indexOf('>', indexBegin);
    int indexEnd = src.lastIndexOf("</" + tag + ">");
    if(indexBegin >= 0 && indexEnd >= 0 && indexBegin < indexEnd){
        src.remove(indexEnd, src.length() - indexEnd);
        src.remove(0, indexBegin + 1);
    }else{
        qWarning("EnNoteContent::cutBetween: wrong string or params");
    }
    //qDebug() << src;
    return src;
}
/*
void EnContent::processMedias(){
    EnContentParser handler;

    QXmlInputSource source;
    source.setData(mNoteContent);

    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.parse(source);
}
*/

void EnContent::processMedias(){
    // ������� ���� en-media
    int mediaIndex = mNoteContent.indexOf("<en-media");

    // ��������� ��� ������� ���� en-media
    while(mediaIndex > 0){

        // ������� ����� ������������ ����
        int mediaIndexEnd = mNoteContent.indexOf('>', mediaIndex);

        // �������� ��� � ��� ��������
        QString hash = getAttributeValueFromTag(mNoteContent, mediaIndex, mediaIndexEnd, "hash");
        QString type = getAttributeValueFromTag(mNoteContent, mediaIndex, mediaIndexEnd, "type");

        // ���� ��� - �����������
        if(type.startsWith("image") && !hash.isEmpty()){

            // ��������� ��������� �� ���, ���� ��� �� ������ ����������� ���
            if(mNoteContent[mediaIndexEnd - 1] != '/'){
                int mediaCloseTagIndex = mNoteContent.indexOf("</en-media>", mediaIndexEnd);
                mNoteContent.replace(mediaCloseTagIndex, 11, "</img>");
            }

            // ������ �������� ������������ ����
            mNoteContent.replace(mediaIndex, 9, "<img src=\"c:/TEMP/zothReader/img/" + hash + '.' + type.mid(6) + '"' );
        }

        mediaIndex =  mNoteContent.indexOf("<en-media", mediaIndexEnd);
    }
    //qDebug() << mNoteContent;
}

QString EnContent::getAttributeValueFromTag(const QString& src,
                                                int tagBegin,
                                                int tagEnd,
                                                const QString& attribute)
{
    int begin = src.indexOf(attribute, tagBegin) + attribute.length();
    if(begin > tagEnd)
        return QString();

    begin = 1 + src.indexOf('"', begin);
    int end = src.indexOf('"', begin);
    return src.mid(begin, end - begin);
}

