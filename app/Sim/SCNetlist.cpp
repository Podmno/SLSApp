//
//  SCNetlist.cpp
//  simCoreSimulator
//
//  Created by Ki MNO on 2023/3/13.
//

#include "SCNetlist.h"

SCNetlist::SCNetlist()
{

}

void SCNetlist::resolveFromModelList(QList<SGModelBase *> modelList)
{
    qDebug() << "Resolver > Pre : 正在检查线路连接情况";
    
    for(SGModelBase* md : modelList) {
        
        bool check_passed_left = false;
        bool check_passed_right = false;
        
        for(SGModelBase* check_md : modelList) {
            
            if(md->itemLeftVertex.x() == check_md->itemLeftVertex.x() && md->itemLeftVertex.y() == check_md->itemLeftVertex.y() && md->itemRightVertex.x() == check_md->itemRightVertex.x() && md->itemRightVertex.y() == check_md->itemRightVertex.y()) {
                continue;
            }
            
            if(md->itemLeftVertex.x() == check_md->itemLeftVertex.x() && md->itemLeftVertex.y() == check_md->itemLeftVertex.y() && check_passed_left == false) {
                check_passed_left = true;
            }
            
            if(md->itemLeftVertex.x() == check_md->itemRightVertex.x() && md->itemLeftVertex.y() == check_md->itemRightVertex.y() && check_passed_left == false) {
                check_passed_left = true;
            }
            
            if(md->itemRightVertex.x() == check_md->itemLeftVertex.x() && md->itemRightVertex.y() == check_md->itemLeftVertex.y() && check_passed_right == false) {
                check_passed_right = true;
            }
            
            if(md->itemRightVertex.x() == check_md->itemRightVertex.x() && md->itemRightVertex.y() == check_md->itemRightVertex.y() && check_passed_right == false) {
                check_passed_right = true;
            }
        }
        
        if(check_passed_left != true || check_passed_right != true) {
            qDebug() << "Resolver > Error Code 1 : 线路未连通";
            return;
        }
        
    }
    
    qDebug() << "Resolver > Pre : 正在处理节点";
    /*
    QMultiMap<SGNode, SGModelBase*> nodeMap;
    
    for(SGModelBase* bs : modelList) {
        
        nodeMap.insert(bs->itemLeftVertex, bs);
        nodeMap.insert(bs->itemRightVertex, bs);
        
    }
     */
    
    


}
