//
//  SCSimulation.h
//  simCoreSimulator
//
//  Created by Ki MNO on 2023/4/9.
//

#ifndef SCSimulation_h
#define SCSimulation_h

#include <QObject>
#include "SCHeader.h"
#include "SCMatrixResolve.h"

using namespace Eigen;

class SCSimulation
{
public:
    SCSimulation();
    
    /*
     注意：此矩阵相对应地节点访问，节点是从 1 开始标记而矩阵对应的是 0 号位置
     */
    
    /// 输入的 MNA A 矩阵
    MatrixXd matrixA;
    /// 输入的 MNA Z 矩阵
    VectorXd vectorZ;
    /// 求解的结果 X 矩阵
    VectorXd vectorX;
    
    /// N: 节点的总个数
    int lengthN;
    /// M: 独立电压源的个数
    int lengthM;
    
    /// 建立节点矩阵
    /// - Parameters:
    ///   - N: 节点的总个数
    ///   - M: 独立电压源的个数
    void createMatrix(int N, int M);
    
    /// 计算仿真结果
    void runSimulation();
    
    /// 为矩阵添加阻抗的贡献
    void addResModal(int nodeID_L, int nodeID_R, double r_val);
    
    /// 为矩阵添加电压源的贡献 nodeID_L 为正 nodeID_R 为负
    void addSourceVModal(int nodeID_L, int nodeID_R, int sourceID, double v_val);
    
    /// 为矩阵添加电流源的贡献 nodeID_L 为正 nodeID_R 为负
    void addSourceAModal(int nodeID_L, int nodeID_R, double a_val);
    
    void outputVectorInfo();
    
    
private:
    
    SCMatrixResolve matrixResolve = SCMatrixResolve();
    
};

#endif /* SCSimulation_h */
