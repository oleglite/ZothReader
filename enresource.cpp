#include "enresource.h"
#include <QDebug>

EnResource::EnResource(){
}

EnResource::EnResource(const QString& type, const QString& data, int width, int height){
    setType(type);
    setData(data);
    setWidth(width);
    setHeight(height);
}

void EnResource::setType(const QString& type){
    mType = type;
    isImage = mType.startsWith("image", Qt::CaseInsensitive);
}

void EnResource::setData(const QString& data){
    mData = QByteArray::fromBase64(QByteArray().append(data));
    mHash = QCryptographicHash::hash(QByteArray().append(mData), QCryptographicHash::Md5).toHex();
}

void EnResource::setHash(const QString& hash){
    mHash = hash;
}

void EnResource::setWidth(int width){
    mWidth = width;
}

void EnResource::setHeight(int height){
    mHeight = height;
}

QString EnResource::getType() const{
    return mType;
}

QByteArray EnResource::getData() const{
    return mData;
}

QString EnResource::getHash() const{
    return mHash;
}

int EnResource::getWidth() const{
    return mWidth;
}

int EnResource::getHeight() const{
    return mHeight;
}

QString EnResource::getImageType() const{
    if(isImage){
        return mType.mid(6);
    }
    return QString();
}

void EnResource::saveImage() const{
    if(isImage){
        QString filename = "c:/TEMP/zothReader/img/" + mHash + "." + getImageType();
        QFile file(filename);
        if(file.exists()){
            qDebug() << "hashed";
            return;
        }else{
            QImage img;
            img.loadFromData(mData);

            if(img.save(filename))
                qDebug() << "image saved";
            else
                qDebug() << "error: " + filename;
        }
    }
}
