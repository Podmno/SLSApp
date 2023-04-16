#include "STToolBox.h"
#include "ui_STToolBox.h"

STToolBox::STToolBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::STToolBox)
{
    ui->setupUi(this);
    
    initToolBox();
}

STToolBox::~STToolBox()
{
    delete ui;
}

void STToolBox::initToolBox()
{
    qDebug() << "Initializing Tool Box...";
    
    QPushButton* btn = new QPushButton(this);
    ui->layoutContentModal->addWidget(btn);
}
