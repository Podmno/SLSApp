//
//  SGHeaders.cpp
//  simGraphicView
//
//  Created by Ki MNO on 2023/3/31.
//

#include "SGHeaders.h"

QPointF SGCanvasUtil::nodeSGToPoint(QPoint node, SGCanvasViewInfo viewInfo)
{
    float relevent_x = viewInfo.centerX + (float)(node.x()*viewInfo.gap);
    float relevent_y = viewInfo.centerY - (float)(node.y()*viewInfo.gap);

    return QPointF(relevent_x, relevent_y);
}

QPoint SGCanvasUtil::pointToSGNode(QPointF point, SGCanvasViewInfo viewInfo)
{
    QPoint repo;
    
    float relevent_x = point.x() - viewInfo.centerX;
    float relevent_y = point.y() - viewInfo.centerY;
    
    // 找到格子坐标
    int X_grid = floor(relevent_x/ viewInfo.gap );
    int Y_grid = floor(relevent_y/ viewInfo.gap );

    
    float grid_center_X = (float)X_grid * viewInfo.gap + viewInfo.gap/2;
    float grid_center_Y = (float)Y_grid * viewInfo.gap + viewInfo.gap/2;
    
    if(grid_center_X - relevent_x > 0) {
        repo.setX(X_grid);
    } else {
        repo.setX(X_grid + 1);
    }
    
    if(grid_center_Y - relevent_y > 0) {
        repo.setY(Y_grid);
    } else {
        repo.setY(Y_grid + 1);
    }
    repo.setY(-repo.y());
    
    return repo;
}

QPointF SGCanvasUtil::gridSGToPoint(QPoint grid, SGCanvasViewInfo viewInfo)
{
    QPointF f;
    f.setX(viewInfo.centerX + grid.x() * viewInfo.gap);
    f.setY(viewInfo.centerY - grid.y() * viewInfo.centerY);
    return f;
}

QPoint SGCanvasUtil::pointToSGGrid(QPointF point, SGCanvasViewInfo viewInfo)
{
    QPoint repo;
    
    float relevent_x = point.x() - viewInfo.centerX;
    float relevent_y = point.y() - viewInfo.centerY;

    repo.setX(floor(relevent_x/viewInfo.gap));
    repo.setY(floor(relevent_y/viewInfo.gap));
    repo.setY(-repo.y());
    
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
