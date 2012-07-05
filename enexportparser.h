#ifndef ENEXPORTPARSER_H
#define ENEXPORTPARSER_H

#include <QtXml>

class EnNote;

class EnExportParser : public QXmlDefaultHandler
{
public:
    friend class Test_EnExportParser;
    EnExportParser();

    //! ����������� ����� ����������� � ������� QIODevice ������.
    //! ����������� �� � ������ ������� (����� EnNote), ���������� �����������;
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

    //! ���������� ������ �������, ���������� � ������ �������.
    QList<EnNote*> getNotes() const;

private:
    //! ������ ��������� �������.
    QList<EnNote*> mEnNotes;

    //! �������� ������ true, ����� ��������� � ���� note.
    bool mIsInNote;

    //! �������� ������ true, ����� ��������� � ���� resource.
    bool mIsInResource;

    //! ����, �������� ���������� �����.
    QStack<QString> mTagContent;

    //! �������� ��� ������� �� ����������� ���� recognition
    static QString getResourceHash(const QString&);
};

#endif // ENEXPORTPARSER_H
