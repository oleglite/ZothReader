#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#include <QDialog>
#include <QtGui>

class HelloDialog : public QDialog
{
    Q_OBJECT
public:
    explicit HelloDialog(QWidget *parent = 0);

    QLineEdit* mTagEdit;

signals:
    void tagAccepted(const QString&);

private slots:
    void accept();
};

#endif // HELLODIALOG_H
