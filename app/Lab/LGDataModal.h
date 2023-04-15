//
//  LGDataModal.h
//  labGraphic
//
//  Created by Ki MNO on 2023/4/2.
//

#ifndef LGDataModal_h
#define LGDataModal_h

#include <QObject>
#include <QDebug>
#include <QFile>
#include "LGStyleCollection.h"

/// 支持的 DataModal 格式
enum LGModalType {
    DataModalUnknown,
    DataModalBar2D,
    DataModalLine2D,
    DataModalArea2D,
    DataModalPie2D,
    DataModalBar3D
};

class LGBaseModal {
public:
    LGBaseModal();
    
    /// 图表的数据类型
    LGModalType dataType;
    /// 图表名称
    QString title;
    
    /// 读取 CSV 功能
    QStringList csvReader(QString filePath);
    
    /// 为图表设定动画选项
    void setAnimationOptions(QChart* chart);
    
    
};

/// 单个 2D 系列数据
struct LGBarSeries {
  
    /// 单个系列的名称
    QString title;
    /// Double 类型数据
    QList<double> barData;
    
};

/// 单个 2D 图表数据
class LG2DBarModal : public LGBaseModal {
   
public:
    LG2DBarModal();
    
    /// 系列集合
    QList<LGBarSeries> seriesData;
    
    /// 从 CSV 文件解析
    bool importFromCSV(QString filePath);
   
    QChart* getChart();
    
};

/// Point 数据
struct LG2DPoint {
    double x;
    double y;
    
};

struct LG2DPointSeries {
  
    QString title;
    
    QList<LG2DPoint> pointData;
};

class LG2DPointModal : public LGBaseModal {
public:
    
    LG2DPointModal();
    /// 点数据列表
    QList<LG2DPointSeries> seriesData;
    
    bool importFromCSV(QString filePath);
    
    QChart* getChart();
};

class LG3DBarModal : public LGBaseModal {
public:
    LG3DBarModal();
   
    QList<LGBarSeries> seriesData;
    
    bool importFromCSV(QString filePath);
    
    Q3DBars* get3DBars();
    
    
};

#endif /* LGDataModal_h */
