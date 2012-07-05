#include "tools.h"

Tools::Tools()
{
}

QString Tools::openTextFile(const QString &filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        qWarning() << "WARNING: file not opened \"" + filename + "\"";
        return QString();
    }
    QTextStream out(&file);
    return out.readAll();
}
/*
QByteArray MainWindow::openFileAsByteArray(const QString& fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, "Unable to open file", file.errorString());
        return "";
    }
    QByteArray content, chunk;
    QTextStream out(&file);
    do {
        out >> chunk;
        content.append(chunk);
    } while (!chunk.isEmpty());

    //qDebug() << content;
    return content;
    return QByteArray();
}*/
