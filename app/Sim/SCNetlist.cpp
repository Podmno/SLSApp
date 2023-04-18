//
//  SCNetlist.cpp
//  simCoreSimulator
//
//  Created by Ki MNO on 2023/3/13.
//

#include "SCNetlist.h"

SCNetlist::SCNetlist(QObject* parent)
    : QObject {parent}
{

}

void SCNetlist::resolveFromModelList(QList<SGModelBase *> modelList)
{
    emit signalResolveInformation("Resolver > 正在检查线路连接情况");
    
    
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
            //return;
        }
        
    }


    
    QMultiMap<QString, SGModelBase*> nodeMap;
    
    for(SGModelBase* bs : modelList) {
        if(bs->itemType == SGItemType::ItemTypeLine) {
            continue;
        }
        QString point_string_left = QString::number(bs->simulationLeftVertex.x()) + "," + QString::number(bs->simulationLeftVertex.y());
        QString point_string_right = QString::number(bs->simulationRightVertex.x()) + "," + QString::number(bs->simulationRightVertex.y());
        
        qDebug() << "Model " << bs->itemUUID << " point info : " << point_string_left << " / " << point_string_right;
        nodeMap.insert(point_string_left, bs);
        nodeMap.insert(point_string_right, bs);
    }
    
    
    
    
    emit signalResolveInformation("Resolver > 正在处理节点");
    QList<SCNodeDataSummary> nodeSummary;
    int nodeIDCount = 0;
    
    for(QString key : nodeMap.keys()) {

            bool exists = false;
            for(SCNodeDataSummary summary : nodeSummary) {
                if(summary.nodeCanvasPlace == key) {
                    // 遍历重复 跳过
                    exists = true;
                    continue;
                }
            }
            
            if(exists) {
                continue;
            }
            
            // 导入一个 SCNodeDataSummary
            SCNodeDataSummary summary;
            summary.nodeID = nodeIDCount;
            summary.nodeCanvasPlace = key;
            nodeIDCount++;
            summary.nodeModelList.append(nodeMap.values(key));
            nodeSummary.append(summary);
        
    }
    

    
    emit signalResolveInformation("Resolver > 正在生成网表");
    // 收集完成节点列表
    
    SCSimulation* sim_core = new SCSimulation();
    int count_source = 0;
    for(SGModelBase* bs : modelList) {
        if(bs->itemType == SGItemType::ItemTypeSourceV) {
            count_source++;
        }
    }
    
    sim_core->createMatrix(int(nodeSummary.count()), count_source);
    int sourceCountNumber = 1;
    for(SGModelBase* bs : modelList) {
        
        QString itemUUID = bs->itemUUID;
        QString itemType = QString::number(bs->itemType);
        QString nodels = "";
        int n1 = -1;
        int n2 = -1;
        
        for(SCNodeDataSummary sum : nodeSummary) {
            
            for(SGModelBase* bs_in : sum.nodeModelList) {
                
                if(itemUUID == bs_in->itemUUID) {
                    
                    if(n1 != -1) {
                        n2 = sum.nodeID;
                    } else {
                        n1 = sum.nodeID;
                        continue;
                    }
                    nodels.append(QString::number(sum.nodeID));
                    nodels.append(" ");
                }
                
            }
            
        }
        
        if(bs->itemType == SGItemType::ItemTypeLine) {
            //sim_core->addResModal(n1, n2, 0.0);
        }
        if(bs->itemType == SGItemType::ItemTypeSourceV) {
            // TODO: SourceV 编号

            sim_core->addSourceVModal(n1, n2, sourceCountNumber, bs->ModelValue[0].toDouble());
            sourceCountNumber++;
        }
        if(bs->itemType == SGItemType::ItemTypeResistance) {
            sim_core->addResModal(n1, n2, bs->ModelValue[0].toDouble());
        }
        qDebug() << itemUUID << "/" << itemType << "/" << nodels;
        
    }
    // s
    
    sim_core->runSimulation();
    QString reply_matrix = QString::fromStdString(sim_core->outputVectorInfo());
    emit signalResolveInformation(reply_matrix);
    
    
}


