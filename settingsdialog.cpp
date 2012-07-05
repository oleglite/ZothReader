#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    QGridLayout* layout = new QGridLayout;
    layout->setColumnStretch(1, 0);
    layout->addWidget(new QLabel(tr("Tag")), 0, 0, Qt::AlignRight);
    layout->addWidget(new QLabel(tr("Page width")), 1, 0, Qt::AlignRight);
    layout->addWidget(new QLabel(tr("Background color")), 2, 0, Qt::AlignRight);
    //layout->addWidget(new QLabel(tr("Text font")), 3, 0, Qt::AlignRight);
    //layout->addWidget(new QLabel(tr("Text color")), 4, 0, Qt::AlignRight);

    mTagEdit = new QLineEdit;
    mPageWidthEdit = new QLineEdit;
    mPageWidthEdit->setValidator(new QIntValidator);
    mBgColorBotton = new QPushButton;
    mBgColorBotton->setFlat(true);

    layout->addWidget(mTagEdit, 0, 1);
    layout->addWidget(mPageWidthEdit, 1, 1);
    layout->addWidget(mBgColorBotton, 2, 1);

    mButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(mButtons, SIGNAL(accepted()), SLOT(accept()));
    connect(mButtons, SIGNAL(rejected()), SLOT(reject()));

    layout->addWidget(mButtons, 4, 1);

    mBgColorDialog = new QColorDialog();
    mBgColorDialog->setModal(true);

    setLayout(layout);
    setModal(true);
    setWindowFlags(Qt::Tool);
    setWindowTitle(tr("Settings"));

    connect(mBgColorBotton, SIGNAL(clicked()), mBgColorDialog, SLOT(show()));
    connect(mBgColorDialog, SIGNAL(accepted()), SLOT(refresh()));
}

void SettingsDialog::show(){
    refresh();
    activateWindow();
    QDialog::show();
}

void SettingsDialog::refresh(){
    QPixmap pixMap(40, 20);
    QPainter painter(&pixMap);
    painter.setBrush(QBrush(QColor(mBgColorDialog->currentColor())));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(0, 0, 40, 20);
    mBgColorBotton->setIcon(QIcon(pixMap));
    mBgColorBotton->setIconSize(QSize(40, 20));
}
