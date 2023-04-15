//
//  SGCanvas.h
//  simGraphicView
//
//  Created by Ki MNO on 2023/2/11.
//

#ifndef SGCanvas_h
#define SGCanvas_h

#include <QObject>

#include "SGModalLine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SGCanvas; }
QT_END_NAMESPACE

class SGCanvas : public QObject
{
    Q_OBJECT
public:
    explicit SGCanvas(QObject *parent = nullptr);
    
    
    
    
signals:

};

#endif /* SGCanvas_h */
