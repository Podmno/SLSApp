#include "SGCanvasView.h"
#include "ui_SGCanvasView.h"


// TODO: BUG 在绘制元器件时元器件会有错误着色

SGCanvasView::SGCanvasView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SGCanvasView)
{
    ui->setupUi(this);
    ui->teDebugInfo->setVisible(false);

    drawBackground();
    minGap = Canvas_MinGap;
    maxGap = Canvas_MaxGap;
    
    showNodeOnCanvas = false;
    canvasStatus = SGCanvasViewStatus::CanvasStatusNormal;

    uiSetCursorShape(canvasStatus);
    
    viewInfo.gap = (minGap + maxGap) / 2;
    viewInfo.centerX = width() / 2;
    viewInfo.centerY = height() / 2;
    // 不再区分 lightPen 与 darkPen 的绘制
    
    lightPen = QPen(Canvas_GridColor);
    lightPen.setWidth(Canvas_GridWidth);
    darkPen = QPen(Canvas_GridColor);
    darkPen.setWidth(Canvas_GridWidth);
    
    currentGridRelevent.setX(INT_MAX);
    currentGridRelevent.setY(INT_MAX);

    viewInfo.originalX = viewInfo.centerX;
    viewInfo.originalY = viewInfo.centerY;
    
    //outputCanvasGridInfo();
    notification = new SGCanvasNotification(this);
    file = new SGFile(this);

    setCanvasCurrentStatus(SGCanvasViewStatus::CanvasStatusNormal);
    
}

void SGCanvasView::drawGridRectangle(int x, int y)
{
    // 绘制当前选中的格子
    
    if(x>=INT_MAX || y>= INT_MAX) {
        return;
    }
    QPen pen;
    pen.setColor(QColor(255,0,0,255));
    QBrush brush;
    brush.setColor(QColor(0,255,0,120));
    brush.setStyle(Qt::SolidPattern);
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(viewInfo.centerX+x*viewInfo.gap,viewInfo.centerY+y*viewInfo.gap,viewInfo.gap,viewInfo.gap);
}

void SGCanvasView::drawNodeAtPoint(QPoint node)
{
    if(node.x() >= INT_MAX || node.y() >= INT_MAX) {
        return;
    }
    
    float draw_grid_pos_x = (float)node.x() * viewInfo.gap + viewInfo.centerX - 5.0;
    float draw_grid_pos_y = (-(float)node.y() * viewInfo.gap) + viewInfo.centerY - 5.0;
    
    QPen pen;
    pen.setColor(QColor(0,127,220));
    QBrush brush;
    brush.setColor(QColor(0,127,220));
    brush.setStyle(Qt::SolidPattern);
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(draw_grid_pos_x,draw_grid_pos_y,10,10);
    
}

            
void SGCanvasView::sendCurrentMousePoint(QPointF p)
{
    currentGridRelevent = SGCanvasUtil::pointToSGGrid(p, viewInfo);
    currentNode = SGCanvasUtil::pointToSGNode(p, viewInfo);
    currentPoint = p;
    
}

void SGCanvasView::mouseMoveEvent(QMouseEvent* e)
{
    QPointF pos = e->position();
    
    sendCurrentMousePoint(mapTo(this, pos));
    
    if(canvasStatus == SGCanvasViewStatus::CanvasStatusViewing) {
        // 查看模式
        
        viewInfo.centerX = originalCenterPointX + currentPoint.x() - recordReleventPointX;
        viewInfo.centerY = originalCenterPointY + currentPoint.y() - recordReleventPointY;
        
    }
    
    update();
    repaint();
    // repaint()
}

void SGCanvasView::drawBackground()
{
    QPalette palette;
    palette.setColor(QPalette::Window, Canvas_BackgroundColor);
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}

void SGCanvasView::drawRowLines(QPainter* p)
{
    //int lineCount = 0;
    float biggerY = viewInfo.centerY;
    float smallerY = viewInfo.centerY;
    
    p->setPen(this->lightPen);

    while (true) {
        p->drawLine(QPointF(0.0, biggerY), QPointF(Canvas_MaxWidth, biggerY));
        p->drawLine(QPointF(0.0, smallerY), QPointF(Canvas_MaxWidth, smallerY));
            
        biggerY += viewInfo.gap;
        smallerY -= viewInfo.gap;
        if (smallerY <= 0 && biggerY >= Canvas_MaxHeight) {
            break;
        }

    }
}

void SGCanvasView::drawColLines(QPainter* p)
{
    int lineCount = 0;
    float biggerX = viewInfo.centerX;
    float smallerX = viewInfo.centerX;

    p->setPen(this->lightPen);

    while (true) {
        p->drawLine(QPointF(biggerX, 0.0), QPointF(biggerX, Canvas_MaxHeight));
        p->drawLine(QPointF(smallerX, 0.0), QPointF(smallerX, Canvas_MaxHeight));

        biggerX += viewInfo.gap;
        smallerX -= viewInfo.gap;
        if (smallerX <= 0 && biggerX >= Canvas_MaxWidth) {
            break;
        }
    }
}

void SGCanvasView::drawItems()
{
    for(int k = 0; k<itemList.size() ; k++) {
        SGModelBase *i = itemList.at(k);
        drawItemOnCanvas(i);
    }
}

// 元器件类型判断与注册中心
void SGCanvasView::drawItemOnCanvas(SGModelBase* item)
{
    
    if(item == nullptr) {
        qDebug() << "item == nullptr, skip";
        
        return;
    }

    if(item->itemLeftVertex.x() == INT_MAX ||
        item->itemLeftVertex.y() == INT_MAX ||
        item->itemRightVertex.x() == INT_MAX ||
        item->itemRightVertex.y() == INT_MAX) {
        return;
    }
    
    if(item->itemType == SGItemType::ItemTypeUnknown) {
        // item->drawItem(this, viewInfo);
        // 现在 Unknown Type 不会绘制
    }

    item->drawItem(this, viewInfo);

}

void SGCanvasView::setItemPrepareToDraw(SGItemType type)
{
    
    currentItemOnDraw = SGFile::createModelBase(type);

}

void SGCanvasView::addCurrentItemToList(SGModelBase* item)
{
    // TODO: 加入物件的上限设置
    if(item == nullptr) {
        qDebug() << "[ERR] Unrecognized item.";
    }
    
    currentItemOnDraw->simulationLeftVertex = currentItemOnDraw->itemLeftVertex;
    currentItemOnDraw->simulationRightVertex = currentItemOnDraw->itemRightVertex;
    
    itemList.append(currentItemOnDraw);
    calcSimulationNode();
    
    // 可以在此设计阻止接连绘画的逻辑
    setItemPrepareToDraw(item->itemType);
    
}

void SGCanvasView::outputCanvasGridInfo()
{
    qDebug() << "center X: " << viewInfo.centerX;
    qDebug() << "center Y: " << viewInfo.centerY;
    
    qDebug() << "minGap: " << minGap;
    qDebug() << "maxGap: " << maxGap;
    
    qDebug() << "Single Grip Gap: " << viewInfo.gap;
    
    QPoint centerNode;
    centerNode.setX(0);
    centerNode.setY(0);
    qDebug() << "Grid(0,0) X: " << SGCanvasUtil::gridSGToPoint(centerNode, viewInfo).x();
    qDebug() << "Grid(0,0) Y: " << SGCanvasUtil::gridSGToPoint(centerNode, viewInfo).y();

    
}

void SGCanvasView::calcSimulationNode()
{
    if(currentItemOnDraw->itemType != SGItemType::ItemTypeLine) {
        return;
    }

    for(SGModelBase* ms : itemList) {
        

            for(SGModelBase* md_edit : itemList) {
                
                if(md_edit->itemType == SGItemType::ItemTypeLine) {
                    continue;
                }
                
                if(md_edit->itemUUID == ms->itemUUID) {
                    // 重复过滤
                    continue;
                }
                
                if(ms->itemIdentifier == "0") {
                    continue;
                }
                
                if(md_edit->simulationLeftVertex == ms->itemLeftVertex) {
                    md_edit->simulationLeftVertex = ms->itemRightVertex;
                    ms->itemIdentifier = "0";
                    qDebug() << "EditedR1 : " << md_edit->itemType << ":" << md_edit->simulationLeftVertex << "," << md_edit->simulationRightVertex;
                    continue;
                }
                
                if(md_edit->simulationRightVertex == ms->itemLeftVertex) {
                    md_edit->simulationRightVertex = ms->itemRightVertex;
                    ms->itemIdentifier = "0";
                    qDebug() << "EditedR2 : " << md_edit->itemType << ":"<< md_edit->simulationLeftVertex << "," << md_edit->simulationRightVertex;
                    continue;
                }
                
                if(md_edit->simulationLeftVertex == ms->itemRightVertex) {
                    md_edit->simulationLeftVertex = ms->itemLeftVertex;
                    ms->itemIdentifier = "0";
                    qDebug() << "EditedR3 : " << md_edit->itemType << ":"<< md_edit->simulationLeftVertex << "," << md_edit->simulationRightVertex;
                    continue;
                }
                
    
                if(md_edit->simulationRightVertex == ms->itemRightVertex) {
                    md_edit->simulationRightVertex = ms->itemLeftVertex;
                    ms->itemIdentifier = "0";
                    qDebug() << "EditedR4 : " << md_edit->itemType << ":"<< md_edit->simulationLeftVertex << "," << md_edit->simulationRightVertex;
                    continue;
 
                }
                
            }
            
        
    }
}


void SGCanvasView::uiSetCursorShape(SGCanvasViewStatus status)
{
    QCursor cursor;
    switch (status) {
        case SGCanvasViewStatus::CanvasStatusNormal:
            cursor.setShape(Qt::ArrowCursor);
            break;
        case SGCanvasViewStatus::CanvasStatusViewing:
            cursor.setShape(Qt::OpenHandCursor);
            break;
        case SGCanvasViewStatus::CanvasStatusEditing:
            cursor.setShape(Qt::CrossCursor);
            break;
        default:
            cursor.setShape(Qt::ArrowCursor);
            break;
    }
    
    setCursor(cursor);
}


void SGCanvasView::paintEvent(QPaintEvent *event)
{
    // 绘图事件会始终重复
    QWidget::paintEvent(event);
    
    QPainter painter(this);

    this->drawColLines(&painter);
    this->drawRowLines(&painter);
    
    if(Canvas_ShowGridDisplay) {
        this->drawGridRectangle(currentGridRelevent.x(), currentGridRelevent.y());
    }
    
    if(Canvas_ShowNodeDisplay) {
        if(showNodeOnCanvas) {
            if(canvasStatus == SGCanvasViewStatus::CanvasStatusEditing) {
                this->drawNodeAtPoint(currentNode);
                this->drawNodeAtPoint(mousePressNodeStart);
                this->drawNodeAtPoint(mousePressNodeEnd);
                currentItemOnDraw->itemRightVertex.setX(currentNode.x());
                currentItemOnDraw->itemRightVertex.setY(currentNode.y());
            }
            
            if(canvasStatus == SGCanvasViewStatus::CanvasStatusNormal) {

            }
            
 
            
        }
        
    }
    
    this->drawItems();
    
}


void SGCanvasView::mousePressEvent(QMouseEvent* event)
{
    
    // 加入此防止鼠标信息无法获取
    sendCurrentMousePoint(event->position());
    
    
    if(event->button() == Qt::LeftButton) {
        switch (canvasStatus) {
            case SGCanvasViewStatus::CanvasStatusEditing:
                showNodeOnCanvas = true;
                //mousePressNodeStart.X
                
                mousePressNodeStart.setX(currentNode.x());
                mousePressNodeStart.setY(currentNode.y());
                
                qDebug() << "mousePressNodeStart: " << mousePressNodeStart.x() << "," << mousePressNodeStart.y();
                
                // FIXME: 此处注意可能会访问到空指针
                currentItemOnDraw->itemLeftVertex.setX(mousePressNodeStart.x());
                currentItemOnDraw->itemLeftVertex.setY(mousePressNodeStart.y());
                currentItemOnDraw->itemRightVertex.setX(INT_MAX);
                currentItemOnDraw->itemRightVertex.setY(INT_MAX);
                
                // 返回普通模式
                // canvasStatus = SGCanvasViewStatus::Normal;
                


            case SGCanvasViewStatus::CanvasStatusNormal:
                
                if(currentItemOnSelection == nullptr) {
                    
                    for(SGModelBase* bs : itemList) {
                        SGItemActionType type = bs->onPlaceItemAction(currentPoint, viewInfo);
                        
                        if(type == SGItemActionType::ItemActionNoAction) {
                            continue;
                        } else {
                            currentItemOnSelectionAction = type;
                            currentItemOnSelection = bs;
                            bs->itemStatus = SGItemStatus::ItemStatusOnSelect;
                            recordNodeSelection = currentNode;
                            break;
                        }
                    }
                    
                } else {
                    
                }
                
                break;
                
            case SGCanvasViewStatus::CanvasStatusViewing:
                // 鼠标拖拽中
                

                
                originalCenterPointX = viewInfo.centerX;
                originalCenterPointY = viewInfo.centerY;
                
                recordReleventPointX = currentPoint.x();
                recordReleventPointY = currentPoint.y();
                
                
                break;
            
            default:
                break;
        }
        
        
        update();
    }
}

void SGCanvasView::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {

        switch (canvasStatus) {
            case SGCanvasViewStatus::CanvasStatusEditing:
            
                
                showNodeOnCanvas = false;
                mousePressNodeEnd.setX(currentNode.x());
                mousePressNodeEnd.setY(currentNode.y());
                recordNodeStart = mousePressNodeStart;
                recordNodeEnd = mousePressNodeEnd;
                

                currentItemOnDraw->itemRightVertex.setX(recordNodeEnd.x());
                currentItemOnDraw->itemRightVertex.setY(recordNodeEnd.y());
                
                
                addCurrentItemToList(currentItemOnDraw);
                
                
                qDebug() << "Start " << recordNodeStart.x() << ", " << recordNodeStart.y();
                qDebug() << "End " << recordNodeEnd.x() << ", " << recordNodeEnd.y();
                
                break;
                
            case SGCanvasViewStatus::CanvasStatusNormal:
                if(currentItemOnSelection == nullptr) {
                    return;
                }
                
                if(currentItemOnSelectionAction == SGItemActionType::ItemActionOnPointEditLeftAction) {
                    currentItemOnSelection->itemLeftVertex = currentNode;
                    break;
                }
                
                if(currentItemOnSelectionAction == SGItemActionType::ItemActionOnPointEditRightAction) {
                    currentItemOnSelection->itemRightVertex = currentNode;
                    break;
                }
                
                if(currentItemOnSelectionAction == SGItemActionType::ItemActionOnItemMoveAction) {
                    
                    int relevent_x = currentNode.x() - recordNodeSelection.x();
                    int relevent_y = currentNode.y() - recordNodeSelection.y();
                    
                    currentItemOnSelection->itemLeftVertex.setX(currentItemOnSelection->itemLeftVertex.x() + relevent_x);
                    currentItemOnSelection->itemLeftVertex.setY(currentItemOnSelection->itemLeftVertex.y() + relevent_y);
                    currentItemOnSelection->itemRightVertex.setX(currentItemOnSelection->itemRightVertex.x() + relevent_x);
                    currentItemOnSelection->itemRightVertex.setY(currentItemOnSelection->itemRightVertex.y() + relevent_y);
                    
                    
                }
                
                
                break;
                
            case SGCanvasViewStatus::CanvasStatusViewing:

                recordReleventPointX = 0;
                recordReleventPointY = 0;
                
                break;
                
            default:
                break;
        }
        
        // 重置
        for(SGModelBase* base : itemList) {
            base->itemStatus = SGItemStatus::ItemStatusOnNormal;
        }
        

        mousePressNodeStart.setX(INT_MAX);
        mousePressNodeEnd.setX(INT_MAX);
        mousePressNodeStart.setY(INT_MAX);
        mousePressNodeEnd.setY(INT_MAX);
        recordNodeSelection.setX(INT_MAX);
        recordNodeSelection.setY(INT_MAX);
        currentItemOnSelection = nullptr;
        // currentItemOnDraw = nullptr;

        update();
    }
}

void SGCanvasView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {
        
        if(canvasStatus == SGCanvasViewStatus::CanvasStatusNormal) {
            for(SGModelBase* base : itemList) {
                if(base->onPlaceItemAction(currentPoint, viewInfo) != SGItemActionType::ItemActionNoAction) {
                    base->itemStatus = SGItemStatus::ItemStatusOnSelect;
                    currentItemOnSelection = base;
                    SGEditorModel* md = new SGEditorModel();
                    md->setModelPointer(base);
                    md->showEditor();
                    base->itemStatus = SGItemStatus::ItemStatusOnNormal;
                    currentItemOnSelection = nullptr;
                    break;
                }
            }
        }
    }
}

void SGCanvasView::showNotification(QString content)
{
    notification->setNotificationContent(content);

    notification->setAttribute(Qt::WA_TransparentForMouseEvents);
    notification->setAttribute(Qt::WA_DeleteOnClose);
    notification->setGeometry(10, 10, notification->geometry().width(), notification->geometry().height());

}

QString SGCanvasView::saveCanvasFile()
{
    return file->saveFile(itemList);
}

void SGCanvasView::loadCanvasFile(QString fileContent)
{
    
    for(SGModelBase* Model : itemList) {
        delete Model;
    }
    
    itemList.empty();
    
    itemList.append(file->loadFile(fileContent));
    
    update();
}



void SGCanvasView::setCanvasCurrentStatus(SGCanvasViewStatus s)
{

    switch (s) {
        case SGCanvasViewStatus::CanvasStatusNormal:
            showNotification("标准模式");
            break;
        case SGCanvasViewStatus::CanvasStatusEditing:
            showNotification("编辑模式");
            break;
        case SGCanvasViewStatus::CanvasStatusViewing:
            showNotification("查看模式");
            break;
        case SGCanvasViewStatus::CanvasStatusSelecting:
            showNotification("选择模式");
            break;
        case SGCanvasViewStatus::CanvasStatusMultiSelecting:
            showNotification("多选模式");
            break;
        default:
            break;
    }
    
    // TODO: 加入元器件多选模式
    // TODO: 加入右键菜单： 复制、剪切、删除

    this->canvasStatus = s;
    
    uiSetCursorShape(s);
    
}


SGCanvasView::~SGCanvasView()
{
    delete ui;
}

void SGCanvasView::onZoomIncreaseClicked()
{

    if(viewInfo.gap < maxGap) {
        viewInfo.gap = viewInfo.gap + Canvas_GapScaleSize;
    }
    update();
}


void SGCanvasView::onZoomDecreaseClicked()
{
    if(viewInfo.gap > minGap) {
        viewInfo.gap = viewInfo.gap - Canvas_GapScaleSize;
    }
    
    update();
}


void SGCanvasView::onScroolVerticalChanged(int value)
{
    viewInfo.centerY = viewInfo.originalY - (value - 50) * Canvas_ScroolStep;
    update();
    
}

void SGCanvasView::onScroolHorizontalChanged(int value)
{
    // 横向的滚动条较长所以需要矫正 1.2 倍的参数
    viewInfo.centerX = viewInfo.originalX - (value - 50) * Canvas_ScroolStep * 1.2;
    update();
}


