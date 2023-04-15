#include "LG3DWidget.h"
#include "ui_LG3DWidget.h"

LG3DWidget::LG3DWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LG3DWidget)
{
    ui->setupUi(this);
}

LG3DWidget::~LG3DWidget()
{
    delete ui;
}


void LG3DWidget::update()
{
    
    if(dataModal == nullptr) {
        return;
    }
    
    if(dataModal->dataType == LGModalType::DataModalBar3D) {
        // 3DBar
       
        LG3DBarModal* bar_modal = (LG3DBarModal*) dataModal;
        Q3DBars* b = bar_modal->get3DBars();
        // TODO: 此处不应该为 show 窗口
        ui->gridLayout_2->addWidget(QWidget::createWindowContainer(b));
    }
    
}
