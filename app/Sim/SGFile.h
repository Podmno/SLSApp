#ifndef SGFILE_H
#define SGFILE_H

#include <QObject>
#include "SGModalBase.h"
#include "SGModalRes.h"
#include "SGModalLine.h"
#include "SGModalSource.h"
#include "SGModalGround.h"
#include "SGCanvasNotification.h"


class SGFile : public QObject
{
    Q_OBJECT
public:
    explicit SGFile(QObject *parent = nullptr);

    QString saveFile(QList<SGModalBase*>);
    QList<SGModalBase*> loadFile(QString);
    
    static SGModalBase* createModalBase(SGItemType);
    
signals:

};

#endif // SGFILE_H
