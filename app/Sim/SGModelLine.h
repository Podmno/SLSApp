#ifndef SGLINEModel_H
#define SGLINEModel_H

#include "SGModelBase.h"

class SGModelLine : public SGModelBase
{
public:
    SGModelLine();
    
    void drawItem(QWidget*, SGCanvasViewInfo) override;

};

#endif // SGLINEModel_H
