#ifndef ENNOTE_H
#define ENNOTE_H

#include <QStringList>
#include <QDebug>
#include "enresource.h"
#include "encontent.h"

class EnNote
{
public:
    EnNote();
    ~EnNote();

    void pushEmptyResource();
    void cutTitleFromContent();
    QString toString() const;

    void prepareContent();

    QString title;
    QString created;
    QString updated;
    QStringList tags;
    QString source;
    QString sourceUrl;
    QList<EnResource*> resources;
    EnContent* content;
};

#endif // ENNOTE_H
