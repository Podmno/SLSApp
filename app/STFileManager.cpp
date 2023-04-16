//
// Created by Ki MNO on 2023/4/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_STFileManager.h" resolved

#include "STFileManager.h"
#include "ui_STFileManager.h"


STFileManager::STFileManager(QWidget *parent) :
        QWidget(parent), ui(new Ui::STFileManager) {
    ui->setupUi(this);
    model = new QFileSystemModel;
    model->setRootPath(QDir::rootPath());
    ui->lineEdit->setText(QDir::homePath());
    ui->treeView->setModel(model);
    ui->treeView->header()->setVisible(false);
    ui->treeView->setColumnHidden(1, true);
    ui->treeView->setColumnHidden(2, true);
    ui->treeView->setColumnHidden(3, true);
    ui->treeView->setSortingEnabled(true);
    ui->treeView->setRootIndex(model->index(QDir::homePath()));

}

STFileManager::~STFileManager() {
    delete ui;
}
