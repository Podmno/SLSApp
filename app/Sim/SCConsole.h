#ifndef SCCONSOLE_H
#define SCCONSOLE_H

#include <QObject>

#include "SCHeader.h"
class SCConsole : public QObject
{
    Q_OBJECT
public:
    explicit SCConsole(QObject *parent = nullptr);
    
    /// 打印 Console 信息
    void printConsoleInfo();
    

signals:

};

#endif // SCCONSOLE_H
