#include "LG2DWidget.h"
#include "ui_LG2DWidget.h"


LG2DWidget::LG2DWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LG2DWidget)
{
    ui->setupUi(this);
    

    chartView = new QChartView();
    
    ui->gridLayout->addWidget(chartView);
    
}

void LG2DWidget::update()
{
    
    if(LGGRAPHIC_ANTIALIASING) {
        chartView->setRenderHint(QPainter::Antialiasing);
    }
    
    if(dataModel->dataType == LGModelType::DataModelBar2D || dataModel->dataType == LGModelType::DataModelPie2D) {
        LG2DBarModel* Model = (LG2DBarModel*) dataModel;
        chartView->setChart(Model->getChart());
    }
    
    if(dataModel->dataType == LGModelType::DataModelLine2D || dataModel->dataType == LGModelType::DataModelArea2D) {
        LG2DPointModel* Model = (LG2DPointModel*) dataModel;
        chartView->setChart(Model->getChart());
    }
  
     
}


LG2DWidget::~LG2DWidget()
{
    delete ui;
}
