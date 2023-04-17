//
//  SCSimulation.cpp
//  simCoreSimulator
//
//  Created by Ki MNO on 2023/4/9.
//

#include "SCSimulation.h"

SCSimulation::SCSimulation()
{

}

void SCSimulation::createMatrix(int N, int M)
{
    matrixA = MatrixXd(N+M , N+M);
    matrixA.fill(0);

    vectorX = VectorXd(N+M);
    vectorX.fill(0);
    
    vectorZ = VectorXd(N+M);
    vectorZ.fill(0);
    
    lengthN = N;
    lengthM = M;
}

void SCSimulation::runSimulation()
{
    // 求解 vectorX
    // TODO: Matrix 求解功能整合入 SCSimulation
    vectorX = matrixResolve.MNAResolve(matrixA, vectorZ);
    
}

void SCSimulation::addResModal(int nodeID_L, int nodeID_R, double r_val)
{
    if(nodeID_L <=0 || nodeID_R <=0) {
        // 0 号节点：接地
        if(nodeID_L > 0) {
            matrixA(nodeID_L-1, nodeID_L-1) += 1/r_val;
        }
        if(nodeID_R > 0) {
            matrixA(nodeID_R-1, nodeID_R-1) += 1/r_val;
        }
    } else {
        matrixA(nodeID_L-1, nodeID_R-1) += -1/r_val;
        matrixA(nodeID_R-1, nodeID_L-1) += -1/r_val;
        matrixA(nodeID_L-1, nodeID_L-1) += 1/r_val;
        matrixA(nodeID_R-1, nodeID_R-1) += 1/r_val;
    }
}

void SCSimulation::addSourceVModal(int nodeID_L, int nodeID_R, int sourceID ,double v_val)
{
    if(nodeID_L <=0 || nodeID_R <= 0) {
        // 存在接地节点
        if(nodeID_L > 0) {
            matrixA(nodeID_L - 1, sourceID - 1 + lengthN) = 1;
            matrixA(sourceID - 1 + lengthN, nodeID_L - 1) = 1;
            vectorZ[lengthN -1 + sourceID] = v_val;
        }
        if(nodeID_R > 0) {
            matrixA(nodeID_R - 1, sourceID - 1 + lengthN) = 1;
            matrixA(sourceID - 1 + lengthN, nodeID_R - 1) = 1;
            vectorZ[lengthN -1 + sourceID] = v_val;
        }
    } else {
        // 两端都有连接
        matrixA(nodeID_L - 1, sourceID - 1 + lengthN) = 1;
        matrixA(sourceID - 1 + lengthN, nodeID_L - 1) = 1;
        matrixA(nodeID_R - 1, sourceID - 1 + lengthN) = -1;
        matrixA(sourceID - 1 + lengthN, nodeID_R - 1) = -1;
        vectorZ[lengthN -1 + sourceID] = v_val;

    }
}

void SCSimulation::addSourceAModal(int nodeID_L , int nodeID_R, double a_val)
{
    // A 仅操作 X 向量
    vectorZ[nodeID_L - 1] += a_val;
}

void SCSimulation::outputVectorInfo()
{
    std::cout << "A:" << std::endl;
    std::cout << matrixA << std::endl;
    std::cout << "Z:" << std::endl;
    std::cout << vectorZ << std::endl;
    std::cout << "X:" << std::endl;
    std::cout << vectorX << std::endl;
}
