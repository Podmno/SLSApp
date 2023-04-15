#ifndef SGHEADERS_H
#define SGHEADERS_H

// Qt Header Files Summary
#include <QObject>
#include <QString>
#include <QList>
#include <QMouseEvent>
#include <QWidget>
#include <QPalette>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QPixmap>
#include <QTimer>
#include <QUuid>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <vector>

#define PI acos(-1)

struct SGFlagStruct {
    /// 开启调试模式
    bool boolDebugEnabled = true;
    
};

/// 调试旗子
static SGFlagStruct FlagData;

/// 最大的画布高度
static float Canvas_MaxHeight = 1000.0;
/// 最大的画布宽度
static float Canvas_MaxWidth = 1000.0;
/// 画布的背景颜色
static QColor Canvas_BackgroundColor = QColor(240, 240, 240);
/// 网格的颜色
static QColor Canvas_GridColor = QColor(222, 222, 222);
/// 网格的宽度
static int Canvas_GridWidth = 1;
/// 格子的最小宽度
static int Canvas_MinGap = 20;
/// 格子的的最大宽度
static int Canvas_MaxGap = 50;
/// 格子调整的宽度大小
static int Canvas_GapScaleSize = 5;
/// 画布移动的步长
static int Canvas_ScroolStep = 15;
/// 开启格子显示提示
static bool Canvas_ShowGridDisplay = false;
/// 开启顶点显示提示
static bool Canvas_ShowNodeDisplay = true;
/// 元器件绘制过程中的颜色
static QColor Canvas_ColorOnDraw = QColor(255,0,0);
/// 元器件选中时的颜色
static QColor Canvas_ColorOnSelect = QColor(0,127,220);
/// 元器件一般情况时的颜色
static QColor Canvas_ColorOnNormal = QColor(0,0,0);

/// 通知显示时间
static int Canvas_NoticeTimer = 3000;

/// 元器件选择灵敏度 越高越灵敏 默认为 0.07
static double Canvas_ModalSelectionTurning = 0.07;

/// 支持的元器件值类型
enum SGModalValueType {
    ModalValueTypeBool,
    ModalValueTypeInt,
    ModalValueTypeLong,
    ModalValueTypeFloat,
    ModalValueTypeDouble,
    ModalValueTypeString,
};

struct SGModalValueDescription {
    SGModalValueType valueType;
    QString description;
    
    SGModalValueDescription() {
        
    }
    
    SGModalValueDescription(SGModalValueType type, QString desp) {
        valueType = type;
        description = desp;
    }
};

/// 即将进行的操作判断
enum SGItemActionType {
    /// 不进行操作
    ItemActionNoAction,
    /// 编辑 Left 顶点
    ItemActionOnPointEditLeftAction,
    /// 编辑 Right 顶点
    ItemActionOnPointEditRightAction,
    /// 移动物品模式
    ItemActionOnItemMoveAction
};


/// Canvas 当前状况
struct SGCanvasViewInfo {
    /// 当前的间隔
    int gap;
    
    float centerX;
    float centerY;
    
    float originalX;
    float originalY;
    
};

/// 当前的元器件状态
enum SGItemStatus {
    /// 目前正在绘制状态
    ItemStatusOnDraw,
    /// 目前处于选中状态
    ItemStatusOnSelect,
    /// 默认状态
    ItemStatusOnNormal
};

/// 支持的元器件种类
enum SGItemType {
    /// 未知部件
    ItemTypeUnknown,
    /// 导线
    ItemTypeLine,
    /// 电压源
    ItemTypeSourceV,
    /// 电流源
    ItemTypeSourceA,
    /// 电阻
    ItemTypeResistance,
    /// 电流表
    ItemTypeMeterV,
    /// 电压表
    ItemTypeMeterA,
    /// 地
    ItemTypeGround,
    /// 电压源（老款样式）
    ItenTypeSourceV_Legacy,
    
};

/// 顶点位置描述
struct SGNode {
    int X;
    int Y;
    SGNode() {
        X = INT_MAX;
        Y = INT_MAX;
    }
    
    SGNode(int x,int y) {
        X = x;
        Y = y;
    }
};

/// 格子坐标描述
struct SGGrid {
    int X;
    int Y;
    
    SGGrid() {
        X = INT_MAX;
        Y = INT_MAX;
    }
    
    SGGrid(int x,int y) {
        X = x;
        Y = y;
    }
};

/// static 类 SGCanvas 换算工具
class SGCanvasUtil {
public:
    /// 将 SGNode 位置转换为 QPointF 绘图位置
    static QPointF nodeSGToPoint(SGNode, SGCanvasViewInfo);
    
    /// 将 QPointF 位置换算为 SGNode 位置
    static SGNode pointToSGNode(QPointF, SGCanvasViewInfo);

    /// 将 SGGrid 转换为 QPointF 位置
    static QPointF gridSGToPoint(SGGrid, SGCanvasViewInfo);

    /// 将 QPointF 转换为 SGGrid
    static SGGrid pointToSGGrid(QPointF, SGCanvasViewInfo);
    
    /// 角度计算函数 计算结果为度数
    static float calculateAngle(float x1, float y1, float x2, float y2);
    
};



#endif // SGHEADERS_H
