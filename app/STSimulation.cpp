#include "STSimulation.h"
#include "ui_STSimulation.h"

STSimulation::STSimulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::STSimulation)
{
    ui->setupUi(this);
    
    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        emit startSimulation();
    });
}

STSimulation::~STSimulation()
{
    delete ui;
}
