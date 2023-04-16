#ifndef SGRESModel_H
#define SGRESModel_H

#include "SGModelBase.h"

class SGModelRes : public SGModelBase
{
public:
    SGModelRes();
    
    void drawItem(QWidget*, SGCanvasViewInfo) override;

};

/*
 *  ModelDoubleValue[0]: 电阻的阻值 （单位：欧姆）
 */

#endif // SGRESModel_H
