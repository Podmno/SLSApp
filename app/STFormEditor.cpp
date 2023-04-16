#include "STFormEditor.h"
#include "ui_STFormEditor.h"

STFormEditor::STFormEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::STFormEditor)
{
    ui->setupUi(this);
    
    initForm();
}

STFormEditor::~STFormEditor()
{
    delete ui;
}


void STFormEditor::initForm()
{
    qDebug() << "Initalizing Form Editor...";
    
    
    
}
