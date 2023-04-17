//
//  SCNetlist.h
//  simCoreSimulator
//
//  Created by Ki MNO on 2023/3/13.
//

#ifndef SCNetlist_h
#define SCNetlist_h

#include <QObject>
#include "SCHeader.h"
#include "SGFile.h"
#include "SCSimulation.h"

/**
 Netlist 元件信息
 */

/// NodeData 的总结数据 包括标号 与此节点相连的其他元器件
struct SCNodeDataSummary {
    
    int nodeID;
    
    QString nodeCanvasPlace;
    
    /// 与此节点连接的所有其他 BaseModel 的指针
    QList<SGModelBase*> nodeModelList;
    
};

/// Netlist 解析工具
class SCNetlist : public QObject
{
    Q_OBJECT
public:
    explicit SCNetlist(QObject *parent = nullptr);
    
    void resolveFromModelList(QList<SGModelBase*> modelList);
    
signals:
    void signalResolveInformation(QString);
};

#endif /* SCNetlist_h */
