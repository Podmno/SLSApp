#include "SGEditorModel.h"
#include "ui_SGEditorModel.h"

SGEditorModel::SGEditorModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SGEditorModel)
{
    ui->setupUi(this);
    
    setWindowTitle("元器件参数编辑");
    
    //ui->verticalLayout_2->setDirection(QBoxLayout::TopToBottom);
    
    connect(ui->btnCancel, &QPushButton::clicked, this, [=](){
        this->close();
    });
    
    connect(ui->btnSave, &QPushButton::clicked, this, [=](){
        
        for(int k=0; k<editingStack.count(); k++) {
            
            if(Model->ModelValueDescription[k].valueType == SGModelValueType::ModelValueTypeDouble) {
                QLineEdit* editor = (QLineEdit*)editingStack[k];
                Model->ModelValue[k] = editor->text();
            }
            
            if(Model->ModelValueDescription[k].valueType == SGModelValueType::ModelValueTypeFloat) {
                QLineEdit* editor = (QLineEdit*)editingStack[k];
                Model->ModelValue[k] = editor->text();
            }
        }
        
        close();
    });
}

void SGEditorModel::setModelPointer(SGModelBase * Model)
{
    
    
    this->Model = Model;
    if(Model->ModelValue.count() == 0) {
        QLabel* lb = new QLabel(this);
        lb->setText("无参数可编辑");
        lb->setAlignment(Qt::AlignCenter);
        ui->scrollArea->setWidget(lb);
        return;
    }
    
    
    // TODO: 完成 ScroolArea 适配工作
    QWidget* widget_content = new QWidget();
    QVBoxLayout* p_widget_content = new QVBoxLayout();
    p_widget_content->setDirection(QBoxLayout::TopToBottom);
    p_widget_content->setAlignment(Qt::AlignTop);
    p_widget_content->setContentsMargins(5, 5, 5, 5);
    

    
    for(int i=0; i<Model->ModelValue.count(); i++) {
        
        SGModelValueDescription desp = Model->ModelValueDescription[i];
        QLabel* lb = new QLabel(this);
        lb->setText(desp.description);
        lb->setFixedHeight(30);
        lb->setContentsMargins(5, 5, 5, 5);
        p_widget_content->addWidget(lb);
        
        if(desp.valueType == SGModelValueType::ModelValueTypeDouble) {
            //ui->verticalLayout_2->addWidget(lb);
            QLineEdit* lineEdit = new QLineEdit(this);
            lineEdit->setText(Model->ModelValue[0]);
            lineEdit->setFixedHeight(50);
            lineEdit->setContentsMargins(10, 10, 10, 10);
            editingStack.append(lineEdit);
            
            p_widget_content->addWidget(lineEdit);
        }
        
        if(desp.valueType == SGModelValueType::ModelValueTypeFloat) {
            QLineEdit* lineEdit = new QLineEdit(this);
            lineEdit->setText(Model->ModelValue[0]);
            lineEdit->setFixedHeight(50);
            lineEdit->setContentsMargins(10, 10, 10, 10);
            editingStack.append(lineEdit);
            
            p_widget_content->addWidget(lineEdit);
        }
        
    }
    
    widget_content->setLayout(p_widget_content);
    ui->scrollArea->setWidget(widget_content);
}

void SGEditorModel::showEditor()
{
    this->exec();
}

SGEditorModel::~SGEditorModel()
{
    delete ui;
}
