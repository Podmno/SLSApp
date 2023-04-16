#include "SGCanvasView.h"
#include "ui_SGCanvasView.h"


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
    
    currentGridRelevent.X = INT_MAX;
    currentGridRelevent.Y = INT_MAX;

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

void SGCanvasView::drawNodeAtPoint(SGNode node)
{
    if(node.X >= INT_MAX || node.Y >= INT_MAX) {
        return;
    }
    
    float draw_grid_pos_x = (float)node.X * viewInfo.gap + viewInfo.centerX - 5.0;
    float draw_grid_pos_y = (-(float)node.Y * viewInfo.gap) + viewInfo.centerY - 5.0;
    
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
    update();
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
        SGModalBase *i = itemList.at(k);
        drawItemOnCanvas(i);
    }
}

// 元器件类型判断与注册中心
void SGCanvasView::drawItemOnCanvas(SGModalBase* item)
{
    
    if(item == nullptr) {
        qDebug() << "item == nullptr, skip";
        
        return;
    }

    if(item->itemLeftVertex.X == INT_MAX ||
        item->itemLeftVertex.Y == INT_MAX ||
        item->itemRightVertex.X == INT_MAX ||
        item->itemRightVertex.Y == INT_MAX) {
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
    
    currentItemOnDraw = SGFile::createModalBase(type);

}

void SGCanvasView::addCurrentItemToList(SGModalBase* item)
{
    // TODO: 加入物件的上限设置
    if(item == nullptr) {
        qDebug() << "[ERR] Unrecognized item.";
    }
    
    itemList.append(currentItemOnDraw);
    
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
    
    SGGrid centerNode;
    centerNode.X = 0;
    centerNode.Y = 0;
    qDebug() << "Grid(0,0) X: " << SGCanvasUtil::gridSGToPoint(centerNode, viewInfo).x();
    qDebug() << "Grid(0,0) Y: " << SGCanvasUtil::gridSGToPoint(centerNode, viewInfo).y();

    
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
        this->drawGridRectangle(currentGridRelevent.X, currentGridRelevent.Y);
    }
    
    if(Canvas_ShowNodeDisplay) {
        if(showNodeOnCanvas) {
            if(canvasStatus == SGCanvasViewStatus::CanvasStatusEditing) {
                this->drawNodeAtPoint(currentNode);
                this->drawNodeAtPoint(mousePressNodeStart);
                this->drawNodeAtPoint(mousePressNodeEnd);
                currentItemOnDraw->itemRightVertex.X = currentNode.X;
                currentItemOnDraw->itemRightVertex.Y = currentNode.Y;
            }
            
            if(canvasStatus == SGCanvasViewStatus::CanvasStatusNormal) {
                // TODO: 绘图时显示顶点功能待实现
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
                
                mousePressNodeStart.X = currentNode.X;
                mousePressNodeStart.Y = currentNode.Y;
                
                qDebug() << "mousePressNodeStart: " << mousePressNodeStart.X << "," << mousePressNodeStart.Y;
                
                // FIXME: 此处注意可能会访问到空指针
                currentItemOnDraw->itemLeftVertex.X = mousePressNodeStart.X;
                currentItemOnDraw->itemLeftVertex.Y = mousePressNodeStart.Y;
                currentItemOnDraw->itemRightVertex.X = INT_MAX;
                currentItemOnDraw->itemRightVertex.Y = INT_MAX;
                
                // 返回普通模式
                // canvasStatus = SGCanvasViewStatus::Normal;
                
            case SGCanvasViewStatus::CanvasStatusViewing:
                // 鼠标拖拽中
                
                break;

            case SGCanvasViewStatus::CanvasStatusNormal:
                
                if(currentItemOnSelection == nullptr) {
                    
                    for(SGModalBase* bs : itemList) {
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
                mousePressNodeEnd.X = currentNode.X;
                mousePressNodeEnd.Y = currentNode.Y;
                recordNodeStart = mousePressNodeStart;
                recordNodeEnd = mousePressNodeEnd;
                

                currentItemOnDraw->itemRightVertex.X = recordNodeEnd.X;
                currentItemOnDraw->itemRightVertex.Y = recordNodeEnd.Y;
                
                
                addCurrentItemToList(currentItemOnDraw);
                
                
                qDebug() << "Start " << recordNodeStart.X << ", " << recordNodeStart.Y;
                qDebug() << "End " << recordNodeEnd.X << ", " << recordNodeEnd.Y;
                
                break;
            case SGCanvasViewStatus::CanvasStatusViewing:
                
                // 鼠标拖拽事件结束
                
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
                    
                    int relevent_x = currentNode.X - recordNodeSelection.X;
                    int relevent_y = currentNode.Y - recordNodeSelection.Y;
                    
                    currentItemOnSelection->itemLeftVertex.X += relevent_x;
                    currentItemOnSelection->itemLeftVertex.Y += relevent_y;
                    currentItemOnSelection->itemRightVertex.X += relevent_x;
                    currentItemOnSelection->itemRightVertex.Y += relevent_y;
                    
                    
                }
                
                
                break;
            default:
                break;
        }
        
        // 重置
        for(SGModalBase* base : itemList) {
            base->itemStatus = SGItemStatus::ItemStatusOnNormal;
        }
        mousePressNodeStart.X = INT_MAX;
        mousePressNodeEnd.X = INT_MAX;
        mousePressNodeStart.Y = INT_MAX;
        mousePressNodeEnd.Y = INT_MAX;
        recordNodeSelection.X = INT_MAX;
        recordNodeSelection.Y = INT_MAX;
        currentItemOnSelection = nullptr;
        // currentItemOnDraw = nullptr;

        update();
    }
}

void SGCanvasView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {
        
        if(canvasStatus == SGCanvasViewStatus::CanvasStatusNormal) {
            for(SGModalBase* base : itemList) {
                if(base->onPlaceItemAction(currentPoint, viewInfo) != SGItemActionType::ItemActionNoAction) {
                    base->itemStatus = SGItemStatus::ItemStatusOnSelect;
                    currentItemOnSelection = base;
                    SGEditorModal* md = new SGEditorModal();
                    md->setModalPointer(base);
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
    
    for(SGModalBase* modal : itemList) {
        delete modal;
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
    qDebug() << "onZoomIncreaseClicked";
    qDebug() << Canvas_GapScaleSize;
    qDebug() << viewInfo.gap << " < " << maxGap;
    if(viewInfo.gap < maxGap) {
        viewInfo.gap = viewInfo.gap + Canvas_GapScaleSize;
    }
    qDebug() << viewInfo.gap << " < " << maxGap;
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


