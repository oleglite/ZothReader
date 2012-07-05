#include <QtTest/QtTest>
#include "enexport.h"

//! Тест класса EnExport.
class Test_EnExport : public QObject
{
    Q_OBJECT
private slots:
    void loadNotes();
    void readExport();
};

void Test_EnExport::loadNotes(){
    EnExport exportTest;
    QVERIFY(exportTest.loadNotes("tag:test"));
    QVERIFY(exportTest.loadNotes("tag:test"));
    QVERIFY(exportTest.loadNotes("tag:test"));
}

void Test_EnExport::readExport(){

}


QTEST_MAIN(Test_EnExport)
#include "test_enexport.moc"

