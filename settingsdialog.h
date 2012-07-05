#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QtGui>

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);

    QLineEdit* mTagEdit;
    QLineEdit* mPageWidthEdit;
    QColorDialog* mBgColorDialog;

public slots:
    void show();
    void refresh();

private:
    QDialogButtonBox* mButtons;
    QPushButton* mBgColorBotton;
};

#endif // ADDDIALOG_H
