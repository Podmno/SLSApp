#include "STSimulation.h"
#include "ui_STSimulation.h"

STSimulation::STSimulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::STSimulation)
{
    ui->setupUi(this);
    textStorage = "";
    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        emit startSimulation();
    });
}

STSimulation::~STSimulation()
{
    delete ui;
}

void STSimulation::addNewInformation(QString info)
{
    textStorage += info;
    textStorage += "\n";
    ui->plainTextEdit->setPlainText(textStorage);
    
}
