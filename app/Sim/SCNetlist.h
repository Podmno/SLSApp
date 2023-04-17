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

/**
 Netlist 元件信息
 */

/// NodeData 的总结数据 包括标号 与此节点相连的其他元器件
struct SCNodeDataSummary {
    
    int nodeID;
    
    /// 与此节点连接的所有其他 BaseModel 的指针
    QList<SGModelBase*> nodeModelList;
    
};

/// Netlist 解析工具
class SCNetlist
{
public:
    SCNetlist();
    
    void resolveFromModelList(QList<SGModelBase*> modelList);
    
};

#endif /* SCNetlist_h */
