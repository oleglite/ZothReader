#ifndef ENDISPLAY_H
#define ENDISPLAY_H

#include <QtCore>
#include <QSettings>
#include <QColor>

class EnNote;

class EnDisplay
{
public:
    EnDisplay();

    QString display(const QList<EnNote*>&) const;
    QString display(EnNote*, const QString& def = QString()) const;

    void setBgColor(const QString&);
    void setPageWidth(int);

private:
    QString mBgColor;
    int mWidth;
};

#endif // ENDISPLAY_H
