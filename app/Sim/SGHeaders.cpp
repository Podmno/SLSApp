//
//  SGHeaders.cpp
//  simGraphicView
//
//  Created by Ki MNO on 2023/3/31.
//

#include "SGHeaders.h"

QPointF SGCanvasUtil::nodeSGToPoint(SGNode node, SGCanvasViewInfo viewInfo)
{
    float relevent_x = viewInfo.centerX + (float)(node.X*viewInfo.gap);
    float relevent_y = viewInfo.centerY - (float)(node.Y*viewInfo.gap);

    return QPointF(relevent_x, relevent_y);
}

SGNode SGCanvasUtil::pointToSGNode(QPointF point, SGCanvasViewInfo viewInfo)
{
    SGNode repo;
    
    float relevent_x = point.x() - viewInfo.centerX;
    float relevent_y = point.y() - viewInfo.centerY;
    
    // 找到格子坐标
    int X_grid = floor(relevent_x/ viewInfo.gap );
    int Y_grid = floor(relevent_y/ viewInfo.gap );

    
    float grid_center_X = (float)X_grid * viewInfo.gap + viewInfo.gap/2;
    float grid_center_Y = (float)Y_grid * viewInfo.gap + viewInfo.gap/2;
    
    if(grid_center_X - relevent_x > 0) {
        repo.X = X_grid;
    } else {
        repo.X = X_grid + 1;
    }
    
    if(grid_center_Y - relevent_y > 0) {
        repo.Y = Y_grid;
    } else {
        repo.Y = Y_grid + 1;
    }
    repo.Y = -repo.Y;
    
    return repo;
}

QPointF SGCanvasUtil::gridSGToPoint(SGGrid grid, SGCanvasViewInfo viewInfo)
{
    QPointF f;
    f.setX(viewInfo.centerX + grid.X * viewInfo.gap);
    f.setY(viewInfo.centerY - grid.Y * viewInfo.centerY);
    return f;
}

SGGrid SGCanvasUtil::pointToSGGrid(QPointF point, SGCanvasViewInfo viewInfo)
{
    SGGrid repo;
    
    float relevent_x = point.x() - viewInfo.centerX;
    float relevent_y = point.y() - viewInfo.centerY;

    repo.X = floor(relevent_x/viewInfo.gap);
    repo.Y = floor(relevent_y/viewInfo.gap);
    repo.Y = -repo.Y;
    
    return repo;
}

float SGCanvasUtil::calculateAngle(float x1, float y1, float x2, float y2)
{
    //
    double angle;
    if (x1 == x2 && y1 < y2)
        return 90.0;
    if (x1 == x2 && y1 > y2)
        return 270.0;
    if (y1 == y2 && x1 < x2)
        return 0.0;
    if (y1 == y2 && x1 > x2)
        return 180.0;
    angle = atan((y1 - y2) / (x1 - x2))  *  (180.0 / PI);
    if (x1 < x2 && y1 < y2)
        return angle;
    if (x1 > x2)
        return 180.0 + angle;
    if (x1 < x2 && y1 > y2)
        return 360.0 + angle;
    return 0.0;
}
