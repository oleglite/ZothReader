#ifndef ENEXPORTPARSER_H
#define ENEXPORTPARSER_H

#include <QtXml>

class EnNote;

class EnExportParser : public QXmlDefaultHandler
{
public:
    friend class Test_EnExportParser;
    EnExportParser();

    //! Статический метод считывающий с объекта QIODevice данные.
    //! Преобразует их в список заметок (класс EnNote), выделенных динамически;
    static QList<EnNote*> readFromIO(QIODevice*);

    bool startElement(const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName,
                      const QXmlAttributes &atts);

    bool characters(const QString &);

    bool endElement(const QString &namespaceURI,
                    const QString &localName,
                    const QString &qName);

    bool fatalError(const QXmlParseException &exception);

    //! Возвращает список заметок, хранящихся в данном объекте.
    QList<EnNote*> getNotes() const;

private:
    //! Список считанных заметок.
    QList<EnNote*> mEnNotes;

    //! Параметр равный true, когда находимся в теге note.
    bool mIsInNote;

    //! Параметр равный true, когда находимся в теге resource.
    bool mIsInResource;

    //! Стек, хранящий содержимое тегов.
    QStack<QString> mTagContent;

    //! Получает хеш ресурса из содержимого тега recognition
    static QString getResourceHash(const QString&);
};

#endif // ENEXPORTPARSER_H
