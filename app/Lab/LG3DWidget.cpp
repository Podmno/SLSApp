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
    
    if(dataModel == nullptr) {
        return;
    }
    
    if(dataModel->dataType == LGModelType::DataModelBar3D) {
        // 3DBar
       
        LG3DBarModel* bar_Model = (LG3DBarModel*) dataModel;
        Q3DBars* b = bar_Model->get3DBars();
        // TODO: 此处不应该为 show 窗口
        ui->gridLayout_2->addWidget(QWidget::createWindowContainer(b));
    }
    
}
