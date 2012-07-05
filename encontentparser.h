#ifndef ENCONTENTPARSER_H
#define ENCONTENTPARSER_H

#include <QXmlDefaultHandler>
#include <QStack>

class Tag{
public:
    QString name;
    QXmlAttributes attributes;
    QString content;
};

class EnContentParser : public QXmlDefaultHandler
{
public:
    EnContentParser();

    bool startElement(const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName,
                      const QXmlAttributes &atts);

    bool characters(const QString &);

    bool endElement(const QString &namespaceURI,
                    const QString &localName,
                    const QString &qName);

    bool fatalError(const QXmlParseException &exception);

    QString getAttributeValue(const QXmlAttributes& attrs, const QString& attr);

    QStack<QString> mTagContent;
    QString accepted;
};

#endif // ENCONTENTPARSER_H
