//
//  LGDataModel.h
//  labGraphic
//
//  Created by Ki MNO on 2023/4/2.
//

#ifndef LGDataModel_h
#define LGDataModel_h

#include <QObject>
#include <QDebug>
#include <QFile>
#include "LGStyleCollection.h"

/// 支持的 DataModel 格式
enum LGModelType {
    DataModelUnknown,
    DataModelBar2D,
    DataModelLine2D,
    DataModelArea2D,
    DataModelPie2D,
    DataModelBar3D
};

class LGBaseModel {
public:
    LGBaseModel();
    
    /// 图表的数据类型
    LGModelType dataType;
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
class LG2DBarModel : public LGBaseModel {
   
public:
    LG2DBarModel();
    
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

class LG2DPointModel : public LGBaseModel {
public:
    
    LG2DPointModel();
    /// 点数据列表
    QList<LG2DPointSeries> seriesData;
    
    bool importFromCSV(QString filePath);
    
    QChart* getChart();
};

class LG3DBarModel : public LGBaseModel {
public:
    LG3DBarModel();
   
    QList<LGBarSeries> seriesData;
    
    bool importFromCSV(QString filePath);
    
    Q3DBars* get3DBars();
    
    
};

#endif /* LGDataModel_h */
