//
//  SGModelGround.h
//  simGraphicView
//
//  Created by Ki MNO on 2023/4/8.
//

#ifndef SGGroundModel_h
#define SGGroundModel_h

#include <QObject>
#include "SGModelBase.h"

class SGModelGround : public SGModelBase
{
public:
    SGModelGround();
    
    void drawItem(QWidget*, SGCanvasViewInfo) override;

};

#endif /* SGGroundModel_h */
