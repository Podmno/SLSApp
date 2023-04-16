#include "SGModelLine.h"

SGModelLine::SGModelLine()
{
    itemType = SGItemType::ItemTypeLine;
    itemIdentifier = "SG.Line";
}

void SGModelLine::drawItem(QWidget *paintWidget, SGCanvasViewInfo viewInfo)
{
    if(itemLeftVertex.X == INT_MAX || itemLeftVertex.X == INT_MAX || itemRightVertex.X == INT_MAX || itemRightVertex.Y == INT_MAX){
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
}

