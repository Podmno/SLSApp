#ifndef SGFILE_H
#define SGFILE_H

#include <QObject>
#include "SGModelBase.h"
#include "SGModelRes.h"
#include "SGModelLine.h"
#include "SGModelSource.h"
#include "SGModelGround.h"
#include "SGCanvasNotification.h"


class SGFile : public QObject
{
    Q_OBJECT
public:
    explicit SGFile(QObject *parent = nullptr);

    QString saveFile(QList<SGModelBase*>);
    QList<SGModelBase*> loadFile(QString);
    
    static SGModelBase* createModelBase(SGItemType);
    
signals:

};

#endif // SGFILE_H
