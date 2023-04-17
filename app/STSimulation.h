#ifndef STSIMULATION_H
#define STSIMULATION_H

#include <QWidget>

namespace Ui {
class STSimulation;
}

class STSimulation : public QWidget
{
    Q_OBJECT

public:
    explicit STSimulation(QWidget *parent = nullptr);
    ~STSimulation();
    
signals:
    void startSimulation();
    
private:
    Ui::STSimulation *ui;
};

#endif // STSIMULATION_H
