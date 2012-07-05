#include "enexportparser.h"
#include "ennote.h"

EnExportParser::EnExportParser() :
    mIsInNote(false),
    mIsInResource(false)
{
}

QList<EnNote*> EnExportParser::readFromIO(QIODevice* sourceDevice){
    if(sourceDevice->isReadable()){
        QXmlInputSource source(sourceDevice);
        EnExportParser handler;

        QXmlSimpleReader reader;
        reader.setContentHandler(&handler);
        reader.parse(source);
        foreach(EnNote* note, handler.getNotes()){
            note->prepareContent();
        }

        qDebug() << "closing device";
        sourceDevice->close();
        return handler.getNotes();
    }
    return QList<EnNote*>();
}

bool EnExportParser::startElement(const QString &,
                                  const QString &,
                                  const QString &qName,
                                  const QXmlAttributes &attrs){
    // для каждого новог тега помещаем в стек строку, в которую будем записывать его содержимое
    mTagContent.push(QString());

    if(qName == "note"){
        Q_ASSERT_X(!mIsInNote, "EnExportParser::startElement", "starting new note inside note");

        // создаём новую заметку
        mEnNotes << new EnNote;
        mIsInNote = true;
    }else if(qName == "resource"){
        Q_ASSERT_X(!mIsInResource, "EnExportParser::startElement", "starting new note inside note");

        // добавляем в заметку пустой ресурс
        mEnNotes.last()->pushEmptyResource();
        mIsInResource = true;
    }
    return true;
}

bool EnExportParser::characters(const QString& characters){
    // прибавляем к последенму элементу стека прочитанные символы
    mTagContent.last() += characters;
    return true;
}

bool EnExportParser::endElement(const QString&, const QString&, const QString& qName){
    //qDebug() << qName;
    if(qName == "note"){
        Q_ASSERT_X(mIsInNote, "EnExportParser::endElement", "ending note outside note");
        mIsInNote = false;
    }else if(mIsInNote){
        // заполняем свойства заметки
        if(qName == "title"){
            mEnNotes.last()->title = mTagContent.last();
        }else if(qName == "content"){
            mEnNotes.last()->content = new EnContent(mTagContent.last());
        }else if(qName == "created"){
            mEnNotes.last()->created = mTagContent.last();
        }else if(qName == "updated"){
            mEnNotes.last()->updated = mTagContent.last();
        }else if(qName == "tag"){
            mEnNotes.last()->tags << mTagContent.last();
        }else if(qName == "source"){
            mEnNotes.last()->source = mTagContent.last();
        }else if(qName == "source-url"){
            mEnNotes.last()->sourceUrl = mTagContent.last();
        }else if(qName == "resource"){
            mIsInResource = false;
            //qDebug() << mTagContent.last();
        }else if(mIsInResource){
            // заполняем свойства ресурса
            if(qName == "data"){
                mEnNotes.last()->resources.last()->setData(mTagContent.last());
            }else if(qName == "mime"){
                mEnNotes.last()->resources.last()->setType(mTagContent.last());
            }else if(qName == "width"){
                mEnNotes.last()->resources.last()->setWidth(mTagContent.last().toInt());
            }else if(qName == "height"){
                mEnNotes.last()->resources.last()->setHeight(mTagContent.last().toInt());
            }/*else if(qName == "recognition"){
                mEnNotes.last()->resources.last()->setHash(getResourceHash(mTagContent.last()));
            }*/
        }
    }
    if(!mTagContent.isEmpty())
        mTagContent.pop();
    return true;
}

bool EnExportParser::fatalError(const QXmlParseException& exception){
    qDebug() << "Line:"      << exception.lineNumber()
             << ", Column:"  << exception.columnNumber()
             << ", Message:" << exception.message();
    return false;
}

QList<EnNote*> EnExportParser::getNotes() const{
    return mEnNotes;
}

QString EnExportParser::getResourceHash(const QString& str){
    //qDebug() << str;
    int from = str.indexOf("objID=\"");
    from += 7;
    int to = str.indexOf('"', from);
    return str.mid(from, to - from);
}
