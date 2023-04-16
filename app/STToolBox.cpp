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
    ui->layoutContentModel->setAlignment(Qt::AlignTop);
    
    QPushButton* btn9 = new QPushButton(this);
    btn9->setText("导线");
    connect(btn9, &QPushButton::clicked, this, [=](){
        emit ModelSelected(SGItemType::ItemTypeLine);
    });
    ui->layoutContentModel->addWidget(btn9);
    
    QPushButton* btn = new QPushButton(this);
    btn->setText("电阻器");
    connect(btn, &QPushButton::clicked, this, [=](){
        emit ModelSelected(SGItemType::ItemTypeResistance);
    });
    ui->layoutContentModel->addWidget(btn);
    
    QPushButton* btn2 = new QPushButton(this);
    btn2->setText("电压源");
    connect(btn2, &QPushButton::clicked, this, [=](){
        qDebug() << "Res";
        emit ModelSelected(SGItemType::ItemTypeSourceV);
    });
    ui->layoutContentModel->addWidget(btn2);
    
    QPushButton* btn3 = new QPushButton(this);
    btn3->setText("电流源");
    connect(btn3, &QPushButton::clicked, this, [=](){
        emit ModelSelected(SGItemType::ItemTypeSourceA);
    });
    ui->layoutContentModel->addWidget(btn3);
    
    QPushButton* btn4 = new QPushButton(this);
    btn4->setText("接地");
    connect(btn4, &QPushButton::clicked, this, [=](){
        emit ModelSelected(SGItemType::ItemTypeGround);
    });
    ui->layoutContentModel->addWidget(btn4);
}
