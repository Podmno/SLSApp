#ifndef SGRESMODAL_H
#define SGRESMODAL_H

#include "SGModalBase.h"

class SGModalRes : public SGModalBase
{
public:
    SGModalRes();
    
    void drawItem(QWidget*, SGCanvasViewInfo) override;

};

/*
 *  modalDoubleValue[0]: 电阻的阻值 （单位：欧姆）
 */

#endif // SGRESMODAL_H
