#ifndef SGCANVASVIEW_H
#define SGCANVASVIEW_H

#include "SGModalBase.h"
#include "SGModalRes.h"
#include "SGModalLine.h"
#include "SGModalSource.h"
#include "SGModalGround.h"
#include "SGCanvasNotification.h"
#include "SGEditorModal.h"
#include "SGFile.h"
namespace Ui {
class SGCanvasView;
}

enum SGCanvasViewStatus {
    CanvasStatusNormal,
    CanvasStatusEditing,
    CanvasStatusViewing,
    CanvasStatusSelecting,
    CanvasStatusMultiSelecting
};

class SGCanvasView : public QWidget
{
    Q_OBJECT

public:
    explicit SGCanvasView(QWidget *parent = nullptr);
    ~SGCanvasView();
    

// MARK: 外部公开 API 函数
    
    /// 设定当前的 Canvas 状态
    void setCanvasCurrentStatus(SGCanvasViewStatus);
    
    /// 设定当前将要绘制的元器件种类
    void setItemPrepareToDraw(SGItemType);
    
    /// 视图放大操作
    void onZoomIncreaseClicked();
    
    /// 视图缩小操作
    void onZoomDecreaseClicked();
    
    /// 在绘图页面展示通知信息
    void showNotification(QString);
    
    /// 保存 Canvas 文件
    QString saveCanvasFile();
    
    /// 读取 Canvas 文件
    void loadCanvasFile(QString);
    
public slots:
    // MARK: - 外部信号槽

    void onScroolHorizontalChanged(int value);
    void onScroolVerticalChanged(int value);
        
    
private:
// MARK: - 背景坐标绘制函数
    void drawBackground();
    void drawRowLines(QPainter*);
    void drawColLines(QPainter*);
    /// 绘制各种元器件的核心函数
    void drawItems();

    /// 获取当前的指针坐标信息
    void sendCurrentMousePoint(QPointF);
    
    /// 在指定格子处绘制长方形
    void drawGridRectangle(int,int);
    
    /// 在指定点绘制顶点功能
    void drawNodeAtPoint(SGNode);
    
    /// 设定鼠标指针状态
    void uiSetCursorShape(SGCanvasViewStatus);

    Ui::SGCanvasView *ui;
    
    /// 物品元器件列表
    QList<SGModalBase*> itemList;
    /// 通知显示栈
    QList<SGCanvasNotification> notificationList;
    
    /// 当前的 Canvas 状态
    SGCanvasViewStatus canvasStatus;
    
    int minGap;
    int maxGap;
    
    /// 当前的视图坐标数据 用于计算窗口的坐标位置
    SGCanvasViewInfo viewInfo;
    
    /// 实时：当前光标所在的 Grid 坐标
    SGGrid currentGridRelevent;
    /// 实时：当前光标指向的 Node 坐标
    SGNode currentNode;
    /// 实时：当前光标的具体坐标
    QPointF currentPoint;
    
    QPen lightPen;
    QPen darkPen;

    // 其中保存的是电路图信息
    // SGCanvas* canvas;
        
    // 输出 Canvas 的基本 Grid 信息
    void outputCanvasGridInfo();
    
    /// 通知组件
    SGCanvasNotification* notification;
    
    /// 文件组件
    SGFile* file;
    

// MARK: - 元器件绘图函数

    /// 目前正在绘制的元器件指针
    SGModalBase* currentItemOnDraw;
    
    /// 目前正在选取的元器件指针
    SGModalBase* currentItemOnSelection;
    
    SGItemActionType currentItemOnSelectionAction;
    
    /// 验证绘制的元器件是否合法并添加到 Canvas 绘图列表
    void addCurrentItemToList(SGModalBase*);
    
    /// 在 Canvas 绘制元器件的创建函数
    void drawItemOnCanvas(SGModalBase*);
    
// MARK: - Node 信息记录
    
    // 只有在按下鼠标左键时显示顶点
    bool showNodeOnCanvas;
    
    // 鼠标的起始位置
    SGNode mousePressNodeStart;
    // 鼠标的结束位置
    SGNode mousePressNodeEnd;
    
    // 记录的起始点
    SGNode recordNodeStart;
    // 记录的结束点
    SGNode recordNodeEnd;
    
    // 记录移动元器件时的初始位置记录
    SGNode recordNodeSelection;
    

protected:
// MARK: - 鼠标事件监听
    void mouseMoveEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;

};



#endif // SGCANVASVIEW_H
