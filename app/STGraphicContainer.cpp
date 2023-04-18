#include "STGraphicContainer.h"
#include "ui_STGraphicContainer.h"

STGraphicContainer::STGraphicContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::STGraphicContainer)
{
    ui->setupUi(this);
}

STGraphicContainer::~STGraphicContainer()
{
    delete ui;
}
