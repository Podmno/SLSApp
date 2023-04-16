//
//  SGModelSource.h
//  simGraphicView
//
//  Created by Ki MNO on 2023/3/19.
//

#ifndef SGSourceModel_h
#define SGSourceModel_h


#include "SGModelBase.h"

enum SGModelSourceType {
    SourceTypeV,
    SourceTypeA,
};

class SGModelSource : public SGModelBase
{
public:
    SGModelSource(SGModelSourceType);

    void setModelSourceType(SGModelSourceType);
    void drawItem(QWidget*, SGCanvasViewInfo) override;



};

/*
 *  ModelDoubleValue[0]: 电流源的电流 / 电压源的电压
 */

#endif /* SGSourceModel_h */
