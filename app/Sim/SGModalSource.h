//
//  SGModalSource.h
//  simGraphicView
//
//  Created by Ki MNO on 2023/3/19.
//

#ifndef SGSourceModal_h
#define SGSourceModal_h


#include "SGModalBase.h"

enum SGModalSourceType {
    SourceTypeV,
    SourceTypeA,
};

class SGModalSource : public SGModalBase
{
public:
    SGModalSource(SGModalSourceType);

    void setModalSourceType(SGModalSourceType);
    void drawItem(QWidget*, SGCanvasViewInfo) override;



};

/*
 *  modalDoubleValue[0]: 电流源的电流 / 电压源的电压
 */

#endif /* SGSourceModal_h */
