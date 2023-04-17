//
// Created by Ki MNO on 2023/4/11.
//

#ifndef SIMCORESIMULATOR_SCSPICE_H
#define SIMCORESIMULATOR_SCSPICE_H

#include <QObject>

class SCSpice : public QObject {
    Q_OBJECT

    explicit SCSpice(QObject *parent = nullptr);

};


#endif //SIMCORESIMULATOR_SCSPICE_H
