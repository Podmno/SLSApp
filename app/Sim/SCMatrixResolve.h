//
//  SCMatrixResolve.h
//  simCoreSimulator
//
//  Created by Ki MNO on 2023/3/18.
//

#ifndef SCMatrixResolve_h
#define SCMatrixResolve_h

#include <QObject>
#include "SCHeader.h"

using namespace Eigen;

class SCMatrixResolve
{
public:
    SCMatrixResolve();
    
    VectorXd MNAResolve(MatrixXd matrixA, VectorXd vectorZ);
    

};

#endif /* SCMatrixResolve_h */
