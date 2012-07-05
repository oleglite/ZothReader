#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QTextCodec* codec = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);

    MainWindow w;
    w.show();

    return a.exec();
}

