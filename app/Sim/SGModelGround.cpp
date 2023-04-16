//
//  SGModelGround.cpp
//  simGraphicView
//
//  Created by Ki MNO on 2023/4/8.
//

#include "SGModelGround.h"

SGModelGround::SGModelGround()
{
    itemType = SGItemType::ItemTypeGround;
    itemIdentifier = "SG.Ground";
}

void SGModelGround::drawItem(QWidget* paintWidget, SGCanvasViewInfo viewInfo)
{
    // 绘制一条线
    QPen pen;
    pen.setWidth(4);
    pen.setColor(getDrawColor());
    QBrush brush;
    brush.setColor(getDrawColor());
    brush.setStyle(Qt::SolidPattern);
    
    QPainter painter(paintWidget);
    painter.setPen(pen);
    painter.setBrush(brush);
    
    // 绘制起始点与终点连线
    QPointF pointStart = SGCanvasUtil::nodeSGToPoint(itemLeftVertex, viewInfo);
    QPointF pointEnd = SGCanvasUtil::nodeSGToPoint(itemRightVertex, viewInfo);
    painter.drawLine(pointStart, pointEnd);
    
    float centerPoint_x = (pointStart.x() + pointEnd.x())/2;
    float centerPoint_y = (pointStart.y() + pointEnd.y())/2;

    float pointSpaceX = abs(centerPoint_x - pointStart.x());
    float pointSpaceY = abs(centerPoint_y - pointStart.y());
    float space = sqrt(pointSpaceX*pointSpaceX + pointSpaceY*pointSpaceY);
    
    QPointF pointRect(centerPoint_x,centerPoint_y);
    QBrush backgroundBrush;
    backgroundBrush.setColor(Canvas_BackgroundColor);
    backgroundBrush.setStyle(Qt::SolidPattern);
    QPen backgroundPen;
    backgroundPen.setColor(Canvas_BackgroundColor);
    
    // 计算倾斜角度
    int roateAngle = (int)SGCanvasUtil::calculateAngle(pointStart.x(), pointStart.y(), pointEnd.x(), pointEnd.y());
    painter.translate(pointRect);
    painter.rotate(roateAngle);
    
    
    // 绘制背景
    painter.setPen(backgroundPen);
    painter.setBrush(backgroundBrush);
    painter.drawRect(space-10,-15,10,30);
    painter.setBrush(brush);
    
    // 绘制元器件
    painter.setPen(pen);
    painter.drawLine(space-10,15,space-10,-15);
    painter.drawLine(space-5,10,space-5,-10);
    painter.drawLine(space,5,space,-5);
    
}
