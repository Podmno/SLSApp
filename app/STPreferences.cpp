#include "STPreferences.h"
#include "ui_STPreferences.h"

STPreferences::STPreferences(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::STPreferences)
{
    ui->setupUi(this);
}

STPreferences::~STPreferences()
{
    delete ui;
}
