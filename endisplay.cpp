#include "endisplay.h"

#include "ennote.h"

EnDisplay::EnDisplay(){
}

QString EnDisplay::display(const QList<EnNote*>& notes) const {
    QString str = "<body bgcolor=\"" + mBgColor + "\">";

    str += "<head><style type=\"text/css\">a{color: #333333;} </style></head>";

    for(int i = 0; i < notes.size(); i++){
        notes[i]->cutTitleFromContent();
        str += "<div style=\"color:black; font-family: serif; font-size: 14pt; width:" + QString::number(mWidth) + "; margin: 0 auto; margin-top:40px; margin-bottom:50px; background-color:" + mBgColor + ";\">" +
                "<a href=\"__zothreader__=" + notes[i]->title + "\" style=\"font-family: sans-serif; font-size: 20pt; font-style: italic; font-weight:bold;text-decoration:none; color: black;\">" +
                notes[i]->title +
                "</a>" +
                "<div style=\"border-top: 1px dashed #111111; padding: 20px; margin-top:16px;\">" +
                notes[i]->content->mNoteContent +
                "</div>" +
                "</div>";
    }
    str += "</body>";

    return str;
}

QString EnDisplay::display(EnNote* note, const QString& def) const {
    if(!note)
        return def;

    QList<EnNote*> notes;
    notes << note;
    return display(notes);
}

void EnDisplay::setBgColor(const QString& color){
    mBgColor = color;
}

void EnDisplay::setPageWidth(int width){
    mWidth = width;
}
