//
//  SGModelSource.cpp
//  simGraphicView
//
//  Created by Ki MNO on 2023/3/19.
//

#include "SGModelSource.h"

SGModelSource::SGModelSource(SGModelSourceType type)
{
    // 默认设置类型 sourceV
    setModelSourceType(type);

}

void SGModelSource::setModelSourceType(SGModelSourceType type)
{
    ModelValue.empty();
    ModelValueDescription.empty();
    
    if(type == SGModelSourceType::SourceTypeV) {
        ModelValue.append("5.0");
        ModelValueDescription.append(SGModelValueDescription(SGModelValueType::ModelValueTypeDouble, "AC 电压源的电压 / 伏特"));
        itemType = SGItemType::ItemTypeSourceV;
        itemIdentifier = "SG.SourceV";
    }
    if(type == SGModelSourceType::SourceTypeA) {
        ModelValue.append("5.0");
        ModelValueDescription.append(SGModelValueDescription(SGModelValueType::ModelValueTypeDouble, "电流源的电流 / 安培"));
        itemType = SGItemType::ItemTypeSourceA;
        itemIdentifier = "SG.SourceA";
    }

}

void SGModelSource::drawItem(QWidget *paintWidget, SGCanvasViewInfo viewInfo)
{
    if(itemType == SGItemType::ItemTypeSourceV) {
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

        //float pointSpaceX = abs(centerPoint_x - pointStart.x());
        //float pointSpaceY = abs(centerPoint_y - pointStart.y());
        //float space = sqrt(pointSpaceX*pointSpaceX + pointSpaceY*pointSpaceY);
        // SPACE 横向长度计算
        
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
        
        // 此种方法绘制：会导致顶点处的略微偏移
        // 为元器件加入背景，优化显示效果
        // V2 版绘制方法 可以使用 SVG 自定义图片
        // 导线仍然使用顶点进行绘制，但是元器件使用一层背景进行绘制（把背景的导线盖住）
        
        // 绘制背景
        painter.setPen(backgroundPen);
        painter.setBrush(backgroundBrush);
        painter.drawRect(-5,-15,10,30);
        painter.setBrush(brush);
        
        // 绘制元器件
        painter.setPen(pen);
        painter.drawLine(-5,-5,-5,5);
        painter.drawLine(5,-15,5,15);
    }
    
    if(itemType == SGItemType::ItemTypeSourceA) {
        // 电流源绘制
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

        //float pointSpaceX = abs(centerPoint_x - pointStart.x());
        //float pointSpaceY = abs(centerPoint_y - pointStart.y());
        //float space = sqrt(pointSpaceX*pointSpaceX + pointSpaceY*pointSpaceY);
        // SPACE 横向长度计算
        
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
        
        // 此种方法绘制：会导致顶点处的略微偏移
        // 为元器件加入背景，优化显示效果
        // V2 版绘制方法 可以使用 SVG 自定义图片
        // 导线仍然使用顶点进行绘制，但是元器件使用一层背景进行绘制（把背景的导线盖住）
        
        // 绘制背景
        painter.setPen(backgroundPen);
        painter.setBrush(backgroundBrush);
        painter.drawRect(-16,-16,32,32);
        painter.setBrush(brush);
        
        // 绘制元器件
        painter.setPen(pen);
        painter.drawArc(-16, -16, 32, 32, 0, 360*16);
        painter.drawLine(0, 16, 0, -16);
    }

}
