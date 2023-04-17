//
//  SCMatrixResolve.cpp
//  simCoreSimulator
//
//  Created by Ki MNO on 2023/3/18.
//

#include "SCMatrixResolve.h"

SCMatrixResolve::SCMatrixResolve()
{
    

}

VectorXd SCMatrixResolve::MNAResolve(MatrixXd matrixA, VectorXd vectorZ)
{
    
    //VectorXd vectorX = matrixA.inverse() * vectorZ;
    VectorXd vectorX = matrixA.lu().solve(vectorZ);
    return vectorX;
}
