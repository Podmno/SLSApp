#include "SGModelBase.h"

SGModelBase::SGModelBase()
{

    itemType = SGItemType::ItemTypeUnknown;
    itemLeftVertex.setX(INT_MAX);
    itemRightVertex.setX(INT_MAX);
    itemLeftVertex.setY(INT_MAX);
    itemRightVertex.setY(INT_MAX);
    simulationLeftVertex.setX(INT_MAX);
    simulationRightVertex.setX(INT_MAX);
    itemStatus = SGItemStatus::ItemStatusOnNormal;
    itemUUID = generateUUID();
    itemIdentifier = "SG.Base";
}

QColor SGModelBase::getDrawColor()
{
    QColor drawColor;
    switch (itemStatus) {
    case ItemStatusOnNormal:
        drawColor = Canvas_ColorOnNormal;
        break;
    case ItemStatusOnSelect:
        drawColor = Canvas_ColorOnSelect;
        break;
    case ItemStatusOnDraw:
        drawColor = Canvas_ColorOnDraw;
        break;
    default:
        drawColor = Canvas_ColorOnNormal;
        break;
    }
    
    return drawColor;
}

QString SGModelBase::generateUUID() {

    QUuid id = QUuid::createUuid();
    return id.toString();
}

SGItemActionType SGModelBase::onPlaceItemAction(QPointF itemPlace, SGCanvasViewInfo viewInfo)
{
    // 快速优化判断 如果离得太远太离谱就直接 bu zai
    QPoint mouseNode = SGCanvasUtil::pointToSGNode(itemPlace, viewInfo);
    if(mouseNode.x() < itemLeftVertex.x() && mouseNode.x() < itemRightVertex.x()) {
        return SGItemActionType::ItemActionNoAction;
    }
    if(mouseNode.y() < itemLeftVertex.y() && mouseNode.y() < itemRightVertex.y()) {
        return SGItemActionType::ItemActionNoAction;
    }
    if(mouseNode.x() > itemLeftVertex.x() && mouseNode.x() > itemRightVertex.x()) {
        return SGItemActionType::ItemActionNoAction;
    }
    if(mouseNode.y() > itemLeftVertex.y() && mouseNode.y() > itemRightVertex.y()) {
        return SGItemActionType::ItemActionNoAction;
    }

    // 鼠标定位的 SGNode 会自动寻找最近的顶点进行解析， 所以不需要 canvasInfo 也可以正确判断指向位置
    if(mouseNode.x() == itemLeftVertex.x() && mouseNode.y() == itemLeftVertex.y()) {
        // 鼠标指向左顶点
        return SGItemActionType::ItemActionOnPointEditLeftAction;
    }
    if(mouseNode.x() == itemRightVertex.x() && mouseNode.y() == itemRightVertex.y()) {
        // 鼠标指向右顶点
        return SGItemActionType::ItemActionOnPointEditRightAction;
    }
    
    if(itemLeftVertex.x() == itemRightVertex.x()) {
        if(mouseNode.y() > std::min(itemLeftVertex.y(), itemRightVertex.y()) && mouseNode.y() < std::max(itemLeftVertex.y(), itemRightVertex.y())) {
            return SGItemActionType::ItemActionOnItemMoveAction;
        }
    }
    
    if(itemLeftVertex.y() == itemRightVertex.y()) {
        if(mouseNode.x() > std::min(itemLeftVertex.x(), itemRightVertex.x()) && mouseNode.x() < std::max(itemLeftVertex.x(), itemRightVertex.x())) {
            return SGItemActionType::ItemActionOnItemMoveAction;
        }
    }

    // 判断鼠标是否在顶点处
    QPointF itemLeftPoint = SGCanvasUtil::nodeSGToPoint(itemLeftVertex, viewInfo);
    QPointF itemRightPoint = SGCanvasUtil::nodeSGToPoint(itemRightVertex, viewInfo);

    // 距离判断问题
    
    double revValue = (itemPlace.x() - itemLeftPoint.x())/(itemRightPoint.x() - itemLeftPoint.x()) - (itemPlace.y()- itemLeftPoint.y())/(itemRightPoint.y()-itemLeftPoint.y());
    revValue = abs(revValue);
    if(revValue < 0.05){
        return SGItemActionType::ItemActionOnItemMoveAction;
    }
            


    return SGItemActionType::ItemActionNoAction;
}

QJsonObject SGModelBase::convertToJson()
{
    QJsonObject contentJson;
    
    contentJson.insert("identifier", itemIdentifier);
    contentJson.insert("type", itemType);
    contentJson.insert("uuid", itemUUID);
    contentJson.insert("leftX", itemLeftVertex.x());
    contentJson.insert("leftY", itemLeftVertex.y());
    contentJson.insert("rightX", itemRightVertex.x());
    contentJson.insert("rightY", itemRightVertex.y());
    QJsonArray jsonArray;
    for(QString value : ModelValue) {
        jsonArray.append(value);
    }
    contentJson.insert("ModelValue", jsonArray);
    
    //return QString(QJsonDocument(contentJson).toJson());
    return contentJson;
}

void SGModelBase::loadFromJson(QJsonObject jsonObject)
{

    itemIdentifier = jsonObject.value("identifier").toString();
    itemType = (SGItemType)jsonObject.value("type").toInt();
    itemUUID = jsonObject.value("uuid").toString();
    itemLeftVertex.setX(jsonObject.value("leftX").toInt());
    itemRightVertex.setX(jsonObject.value("rightX").toInt());
    itemLeftVertex.setY(jsonObject.value("leftY").toInt());
    itemRightVertex.setY(jsonObject.value("rightY").toInt());
    QJsonArray array = jsonObject.value("ModelValue").toArray();
    for(QJsonValue v : array) {
        ModelValue.append(v.toString());
    }
    
}

void SGModelBase::drawItem(QWidget *paintWidget, SGCanvasViewInfo viewInfo)
{

}

/*
 * 去除 BaseItem 的绘图能力
 *
void SGModelBase::drawItem(QWidget* paintWidget,SGCanvasViewInfo info)
{
    // placeX 物体的 X 坐标 / Y 坐标 绘图位置

    QPixmap image_null(":/img/simGraphicView/xmark.circle.fill@2x.png");

    image_null = image_null.scaled(info.gap,info.gap,Qt::KeepAspectRatio);
    QRect image_rect(0,0,info.gap,info.gap);
    QPainter painter(paintWidget);
    painter.drawPixmap(SGCanvasUtil::nodeSGToPoint(SGNode(itemPlace.X, itemPlace.Y), info) , image_null, image_rect);
}

*/
