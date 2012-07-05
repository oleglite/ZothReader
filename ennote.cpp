#include "ennote.h"

EnNote::EnNote() :
    content(0)
{}

EnNote::~EnNote(){
    if(content)
        delete content;
    foreach(EnResource* res, resources){
        delete res;
    }
}

void EnNote::pushEmptyResource(){
    resources << new EnResource();
}

void EnNote::cutTitleFromContent(){
    int index = content->mNoteContent.indexOf(title, 0, Qt::CaseInsensitive);
    if(index > 0 && index < content->mNoteContent.length() * 0.3)
        content->mNoteContent.remove(index, title.length());
}

QString EnNote::toString() const{
    return "EnNote:" + title + " created:" + created + " tags:" + tags.join(", ");
}

void EnNote::prepareContent(){
    foreach(EnResource* res, resources){
        res->saveImage();
    }
    content->processMedias();
}
