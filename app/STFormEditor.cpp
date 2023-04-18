#include "STFormEditor.h"
#include "ui_STFormEditor.h"

STFormEditor::STFormEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::STFormEditor)
{
    ui->setupUi(this);
    
    instantForm = false;
    rowCount = 0;
    colCount = 2;
    
    connect(ui->btnAdd, &QPushButton::clicked, this, [=](){
        rowCount++;
        
        ui->tableWidget->setRowCount(rowCount);
        ui->tableWidget->setItem(rowCount-1, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(rowCount-1, 1, new QTableWidgetItem(""));
        
    });
    
    connect(ui->btnMinus, &QPushButton::clicked, this, [=](){
        qDebug() << "Editor > Current Selected " << ui->tableWidget->currentIndex();
        if(ui->tableWidget->currentIndex().row() < 0) {
            return;
        }
        rowCount--;
        ui->tableWidget->removeRow(ui->tableWidget->currentItem()->row());
        
    });
    
    connect(ui->cboxDataType, &QComboBox::currentIndexChanged, this, [=](int index_num){
        
        if(index_num == 0) {
            ui->tableWidget->clear();
            QStringList header;
            header << "名称" << "Val1";
            colCount = 2;
            rowCount = 0;
            ui->tableWidget->setColumnCount(2);
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setHorizontalHeaderLabels(header);
            ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        }
        
        if(index_num == 1) {
            ui->tableWidget->clear();
            QStringList header;
            header << "名称" << "axisX1" << "axisY1";
            colCount = 3;
            rowCount = 0;
            ui->tableWidget->setColumnCount(3);
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setHorizontalHeaderLabels(header);
            ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        }

    });

    connect(ui->btnColAdd, &QPushButton::clicked, this, [=](){
        // 增加列
        if(ui->cboxDataType->currentIndex() == 0) {
            // 数组数据
            qDebug() << "Add single value";
            colCount++;
            QString title = "Val" + QString::number(colCount-1);
            ui->tableWidget->insertColumn(colCount-1);
            ui->tableWidget->setHorizontalHeaderItem(colCount-1,new QTableWidgetItem(title));
        }

        if(ui->cboxDataType->currentIndex() == 1) {
            // 点数据
            qDebug() << "Add point value";
            colCount += 2;
            QString title_x = "axisX" + QString::number((colCount)/2);
            QString title_y = "axisY" + QString::number((colCount)/2);
            ui->tableWidget->insertColumn(colCount-2);
            ui->tableWidget->setHorizontalHeaderItem(colCount-2,new QTableWidgetItem(title_x));
            ui->tableWidget->insertColumn(colCount-1);
            ui->tableWidget->setHorizontalHeaderItem(colCount-1, new QTableWidgetItem(title_y));
            

        }
    });

    connect(ui->btnColMinus, &QPushButton::clicked, this, [=](){
        // 减少列
        if(ui->cboxDataType->currentIndex() == 0) {
            // 数组数据
            if(colCount <= 2) {
                qDebug() << "已经达到最小表格要求，无法继续删除。";
                return;
            }

            ui->tableWidget->removeColumn(colCount-1);

            colCount -= 1;
        }

        if(ui->cboxDataType->currentIndex() == 1) {
            // 点数据
            if(colCount <= 3) {
                qDebug() << "已经达到最小表格要求，无法继续删除。";
                return;
            }


            ui->tableWidget->removeColumn(colCount-1);
            ui->tableWidget->removeColumn(colCount-2);

            colCount -= 2;
        }
    });

    connect(ui->btnOK, &QPushButton::clicked, this, [=](){
        
        parseTableWidgetData();
    });
    
    connect(ui->tableWidget, &QTableWidget::itemChanged, this, [=](){
        if(instantForm) {
            parseTableWidgetData();
        }
    });
    
    connect(ui->checkBox, &QCheckBox::stateChanged, this, [=](int status){
        if(status == Qt::Checked) {
            instantForm = true;
        } else {
            instantForm = false;
        }
    });
    
    
    QStringList header;
    header << "名称" << "Val1";
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    //ui->tableWidget->setItem(0, 0, new QTableWidgetItem(""));
    //ui->tableWidget->setItem(0, 1, new QTableWidgetItem(""));
    initForm();
}


void STFormEditor::initForm()
{
    qDebug() << "Initalizing Form Editor...";
    
    
}

void STFormEditor::parseTableWidgetData()
{
    qDebug() << "Editor > Send Form Contents : ";
    
    
    if(ui->cboxType->currentIndex() == 0 || ui->cboxType->currentIndex() == 3) {
        
        // TODO: 2DBar / 2DAera / 2DPie
        LG2DBarModel* model = new LG2DBarModel();
        if(ui->lineEditTitle->text() == "") {
            model->title = "图表";
        } else {
            model->title = ui->lineEditTitle->text();
        }
        
        for(int i=0; i<rowCount; i++) {
            // 按行进行处理
            LGBarSeries series;
            series.title = ui->tableWidget->item(i, 0)->text();
            QList<double> content_value;
            for(int k=1; k<colCount; k++) {
                if(ui->tableWidget->item(i, k) == nullptr) {
                    content_value.append(0);
                } else {
                    content_value.append(ui->tableWidget->item(i, k)->text().toDouble());
                }
                
                
            }
            series.barData = content_value;
            model->seriesData.append(series);
        }
        
        if(ui->cboxType->currentIndex() == 0) {
            model->dataType = LGModelType::DataModelBar2D;
        }

        
        if(ui->cboxType->currentIndex() == 3) {
            model->dataType = LGModelType::DataModelPie2D;
        }
        
        emit onDataFormFinished(model);
        
    }
    
    if(ui->cboxType->currentIndex() == 1 || ui->cboxType->currentIndex() == 2) {
        
        LG2DPointModel* model = new LG2DPointModel();
        if(ui->lineEditTitle->text() == "") {
            model->title = "图表";
        } else {
            model->title = ui->lineEditTitle->text();
        }
        
        
        for(int i=0; i<rowCount; i++) {
            // 按行进行处理
            LG2DPointSeries series;
            series.title = ui->tableWidget->item(i, 0)->text();
            
            
            for(int k=1; k<colCount-1; ) {
                double x_axis;
                double y_axis;
                if(ui->tableWidget->item(i, k) == nullptr) {
                    x_axis = 0.0;
                    
                } else {
                    x_axis = ui->tableWidget->item(i, k)->text().toDouble();
                }
                
                if(ui->tableWidget->item(i, k+1) == nullptr) {
                    y_axis = 0.0;
                } else {
                    y_axis = ui->tableWidget->item(i, k+1)->text().toDouble();
                }
                 
                
                LG2DPoint pt;
                pt.x = x_axis;
                pt.y = y_axis;
                series.pointData.append(pt);
                
                k += 2;
            }
            
            model->seriesData.append(series);
  
        }
        
        
        if(ui->cboxType->currentIndex() == 2) {
            model->dataType = LGModelType::DataModelArea2D;
        }
        
        if(ui->cboxType->currentIndex() == 1) {
            model->dataType = LGModelType::DataModelLine2D;
        }
        
        emit onDataFormFinished(model);
        
    }
    
    if(ui->cboxType->currentIndex() == 4) {
        
        LG3DBarModel* model = new LG3DBarModel();
        if(ui->lineEditTitle->text() == "") {
            model->title = "图表";
        } else {
            model->title = ui->lineEditTitle->text();
        }
        
        for(int i=0; i<rowCount; i++) {
            // 按行进行处理
            LGBarSeries series;
            series.title = ui->tableWidget->item(i, 0)->text();
            QList<double> content_value;
            for(int k=1; k<colCount; k++) {
                if(ui->tableWidget->item(i, k) == nullptr) {
                    content_value.append(0);
                } else {
                    content_value.append(ui->tableWidget->item(i, k)->text().toDouble());
                }
                
                
            }
            series.barData = content_value;
            model->seriesData.append(series);
        }
        
        if(ui->cboxType->currentIndex() == 4) {
            model->dataType = LGModelType::DataModelBar3D;
        }

        emit onDataFormFinished(model);
        
        
        
        
    }

}


STFormEditor::~STFormEditor()
{
    delete ui;
    
}
