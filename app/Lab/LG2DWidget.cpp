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
    
    if(dataModal->dataType == LGModalType::DataModalBar2D || dataModal->dataType == LGModalType::DataModalPie2D) {
        LG2DBarModal* modal = (LG2DBarModal*) dataModal;
        chartView->setChart(modal->getChart());
    }
    
    if(dataModal->dataType == LGModalType::DataModalLine2D || dataModal->dataType == LGModalType::DataModalArea2D) {
        LG2DPointModal* modal = (LG2DPointModal*) dataModal;
        chartView->setChart(modal->getChart());
    }
  
     
}


LG2DWidget::~LG2DWidget()
{
    delete ui;
}
