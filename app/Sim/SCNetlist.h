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

/**
 Netlist 元件信息
 */
struct SCNetlistItem {
    
};

/**
    SCNetlist Netlist 解析
 */
class SCNetlist
{
public:
    SCNetlist();
    
    /**
    解析 Netlist 网表
    @param QString 需要解析的 Netlist 网表字符串
    @returns 网表结构体
     */
    void resolve(QString);
    
    void resolveComponent(QString);
    
    void resolvePower(QString);

    void resolveNetlist(QString content);
    
    void countNode();
    
};

#endif /* SCNetlist_h */
