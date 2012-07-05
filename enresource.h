#ifndef ENRESOURCE_H
#define ENRESOURCE_H

#include <QString>
#include <QCryptographicHash>
#include <QImage>
#include <QMimeData>
#include <QFile>

class EnResource
{
public:
    EnResource();
    EnResource(const QString& type, const QString& data, int width = 0, int height = 0);

    void setType(const QString& type);
    void setData(const QString& data);
    void setHash(const QString& hash);
    void setWidth(int width);
    void setHeight(int height);

    QString getType() const;
    QByteArray getData() const;
    QString getHash() const;
    int getWidth() const;
    int getHeight() const;

    QString getImageType() const;
    void saveImage() const;

private:
    QString mType;
    QByteArray mData;
    QString mHash;
    int mWidth;
    int mHeight;

    bool isImage;
};

#endif // ENRESOURCE_H
