//
//  SGModalGround.h
//  simGraphicView
//
//  Created by Ki MNO on 2023/4/8.
//

#ifndef SGGroundModal_h
#define SGGroundModal_h

#include <QObject>
#include "SGModalBase.h"

class SGModalGround : public SGModalBase
{
public:
    SGModalGround();
    
    void drawItem(QWidget*, SGCanvasViewInfo) override;

};

#endif /* SGGroundModal_h */
