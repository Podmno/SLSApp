#ifndef SGBASEITEM_H
#define SGBASEITEM_H

#include "SGHeaders.h"

/// Canvas 绘制元器件的基础类

class SGModalBase
{
public:
    SGModalBase();
    
    /// Item 的 Paint 方法 需要 override
    virtual void drawItem(QWidget* paintWidget, SGCanvasViewInfo);

    /// 确定元件是否在指定 Node 位置 用于选中、移动等操作
    SGItemActionType onPlaceItemAction(QPointF, SGCanvasViewInfo);

    /// 转换为 String 保存
    QJsonObject convertToJson();

    /// 从 String 加载
    void loadFromJson(QJsonObject);
    
    /// 指示物件的类别
    SGItemType itemType;

    /// 当前的物件状态信息
    SGItemStatus itemStatus;
    
    /// 左侧顶点位置
    SGNode itemLeftVertex;
    /// 右侧顶点位置
    SGNode itemRightVertex;
    
    /// 物件的 UUID 号码
    QString itemUUID;

    /// 物件的识别码
    QString itemIdentifier;

    /// 对于多顶点元器件的追加
    QList<SGNode> itemOtherVertex;

    /// 用于内部根据当前状态获取画笔颜色
    QColor getDrawColor();

    /// 生成 UUID 方法
    QString generateUUID();

    /// Modal 提供的值存储数组 对应的数组处的值的意义需要参照具体元件
    QList<QString> modalValue;
    
    /// 对 modalDoubleValue 的值意义解释
    QList<SGModalValueDescription> modalValueDescription;
    

};

#endif // SGBASEITEM_H
