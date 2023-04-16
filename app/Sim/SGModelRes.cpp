#include "SGModelRes.h"

SGModelRes::SGModelRes()
{
    itemType = SGItemType::ItemTypeResistance;
    itemIdentifier = "SG.Resistance";

    ModelValue.append("10.0");
    ModelValueDescription.append(SGModelValueDescription(SGModelValueType::ModelValueTypeDouble, "电阻的阻值（欧姆）"));
}

void SGModelRes::drawItem(QWidget *paintWidget, SGCanvasViewInfo viewInfo)
{
    
    if(itemLeftVertex.X == INT_MAX || itemLeftVertex.X == INT_MAX || itemRightVertex.X == INT_MAX || itemRightVertex.Y == INT_MAX) {
        return;
    }

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
    
    QPointF pointStart = SGCanvasUtil::nodeSGToPoint(itemLeftVertex, viewInfo);
    QPointF pointEnd = SGCanvasUtil::nodeSGToPoint(itemRightVertex, viewInfo);
    painter.drawLine(pointStart, pointEnd);
    
    // TODO: 电阻的位置偏了需要修正
    float centerPoint_x = pointStart.x() - (pointStart.x() - pointEnd.x())/2;
    float centerPoint_y = pointStart.y() - (pointStart.y() - pointEnd.y())/2;
    
    
    QBrush brush2;
    brush2.setColor(Canvas_BackgroundColor);
    brush2.setStyle(Qt::SolidPattern);

    QPointF pointRect(centerPoint_x,centerPoint_y);
    painter.translate(centerPoint_x, centerPoint_y);
    // 角度计算：Passed
    int roateAngle = (int)SGCanvasUtil::calculateAngle(pointStart.x(), pointStart.y(), pointEnd.x(), pointEnd.y());
    painter.rotate(roateAngle);
    painter.setBrush(brush2);
    painter.drawRect(-17,-7,34,14);
    
}
