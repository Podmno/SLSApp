#ifndef SGLINEMODAL_H
#define SGLINEMODAL_H

#include "SGModalBase.h"

class SGModalLine : public SGModalBase
{
public:
    SGModalLine();
    
    void drawItem(QWidget*, SGCanvasViewInfo) override;

};

#endif // SGLINEMODAL_H
