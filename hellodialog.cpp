#include "hellodialog.h"
#include "tools.h"

HelloDialog::HelloDialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    /*QPixmap zothPixmap;
    if(zothPixmap.load(":/images/zoth.png")){
        QLabel* zothLabel = new QLabel(this);
        zothLabel->setPixmap(zothPixmap.scaled(QSize(200, 200), Qt::KeepAspectRatio));
        layout->addWidget(zothLabel, 0, Qt::AlignCenter);
    }*/

    QLabel* helloLabel = new QLabel(Tools::openTextFile(":/text/hello.txt"), this);
    helloLabel->setWordWrap(true);
    helloLabel->setFont(QFont("Times", 16, QFont::Light, true));
    layout->addWidget(helloLabel, 0, Qt::AlignLeft);

    mTagEdit = new QLineEdit;
    layout->addWidget(mTagEdit);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok /*| QDialogButtonBox::Cancel*/);
    connect(buttons, SIGNAL(accepted()), SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), SLOT(reject()));

    layout->addWidget(buttons);

    setLayout(layout);
    setModal(true);
    setWindowFlags(Qt::SplashScreen);
    setWindowTitle(tr("Hello, Reader!"));
    setWindowIcon(QIcon(":/images/green_book_zoth.png"));
}

void HelloDialog::accept(){
    QString tag = mTagEdit->text();
    if(!tag.isEmpty())
        emit tagAccepted(tag);
    QDialog::accept();
}
