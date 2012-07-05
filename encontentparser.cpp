#include "encontentparser.h"
#include <QDebug>

EnContentParser::EnContentParser()
{
}

bool EnContentParser::startElement(const QString &,
                                  const QString &,
                                  const QString &qName,
                                  const QXmlAttributes &attrs){
    mTagContent.push(QString());

    if(qName == "en-media" && getAttributeValue(attrs, "type").startsWith("image")){
        accepted += "\n<" + qName;
        for(int i = 0; i < attrs.count(); i++){
            accepted += ' ' + attrs.qName(i) + "=\"" + attrs.value(i) + '"';
        }
        accepted += ">\n";
    }

    accepted += "\n<" + qName;
    for(int i = 0; i < attrs.count(); i++){
        accepted += ' ' + attrs.qName(i) + "=\"" + attrs.value(i) + '"';
    }
    accepted += ">\n";
    //qDebug() << /*QString('\t', level) + */qName + " (" + attrString + " )";
    return true;
}

bool EnContentParser::characters(const QString& characters){
    mTagContent.last() += characters;
    return true;
}

bool EnContentParser::endElement(const QString&, const QString&, const QString& qName){
    accepted += "\n</" + qName + ">\n";
    mTagContent.pop();
    return true;
}

bool EnContentParser::fatalError(const QXmlParseException& exception){
    qDebug() << "Line:"      << exception.lineNumber()
             << ", Column:"  << exception.columnNumber()
             << ", Message:" << exception.message();
    return false;
}

QString EnContentParser::getAttributeValue(const QXmlAttributes& attrs, const QString& attr){
    for(int i = 0; i < attrs.count(); i++)
        if(attrs.qName(i) == attr)
            return attrs.value(i);
    return QString();
}
