#include "SGEditorModal.h"
#include "ui_SGEditorModal.h"

SGEditorModal::SGEditorModal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SGEditorModal)
{
    ui->setupUi(this);
    
    setWindowTitle("元器件参数编辑");
    
    //ui->verticalLayout_2->setDirection(QBoxLayout::TopToBottom);
    
    connect(ui->btnCancel, &QPushButton::clicked, this, [=](){
        this->close();
    });
    
    connect(ui->btnSave, &QPushButton::clicked, this, [=](){
        
        for(int k=0; k<editingStack.count(); k++) {
            
            if(modal->modalValueDescription[k].valueType == SGModalValueType::ModalValueTypeDouble) {
                QLineEdit* editor = (QLineEdit*)editingStack[k];
                modal->modalValue[k] = editor->text();
            }
            
            if(modal->modalValueDescription[k].valueType == SGModalValueType::ModalValueTypeFloat) {
                QLineEdit* editor = (QLineEdit*)editingStack[k];
                modal->modalValue[k] = editor->text();
            }
        }
        
        close();
    });
}

void SGEditorModal::setModalPointer(SGModalBase * modal)
{
    
    
    this->modal = modal;
    if(modal->modalValue.count() == 0) {
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
    

    
    for(int i=0; i<modal->modalValue.count(); i++) {
        
        SGModalValueDescription desp = modal->modalValueDescription[i];
        QLabel* lb = new QLabel(this);
        lb->setText(desp.description);
        lb->setFixedHeight(30);
        lb->setContentsMargins(5, 5, 5, 5);
        p_widget_content->addWidget(lb);
        
        if(desp.valueType == SGModalValueType::ModalValueTypeDouble) {
            //ui->verticalLayout_2->addWidget(lb);
            QLineEdit* lineEdit = new QLineEdit(this);
            lineEdit->setText(modal->modalValue[0]);
            lineEdit->setFixedHeight(50);
            lineEdit->setContentsMargins(10, 10, 10, 10);
            editingStack.append(lineEdit);
            
            p_widget_content->addWidget(lineEdit);
        }
        
        if(desp.valueType == SGModalValueType::ModalValueTypeFloat) {
            QLineEdit* lineEdit = new QLineEdit(this);
            lineEdit->setText(modal->modalValue[0]);
            lineEdit->setFixedHeight(50);
            lineEdit->setContentsMargins(10, 10, 10, 10);
            editingStack.append(lineEdit);
            
            p_widget_content->addWidget(lineEdit);
        }
        
    }
    
    widget_content->setLayout(p_widget_content);
    ui->scrollArea->setWidget(widget_content);
}

void SGEditorModal::showEditor()
{
    this->exec();
}

SGEditorModal::~SGEditorModal()
{
    delete ui;
}
