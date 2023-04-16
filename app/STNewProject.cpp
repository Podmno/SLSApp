//
// Created by Ki MNO on 2023/4/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_STNewProject.h" resolved

#include "STNewProject.h"
#include "ui_STNewProject.h"


STNewProject::STNewProject(QWidget *parent) :
        QDialog(parent), ui(new Ui::STNewProject) {
    ui->setupUi(this);

    connect(ui->btnCancel, &QPushButton::clicked, this, [=](){
        this->close();
    });

    connect(ui->btnCreate, &QPushButton::clicked, this, [=](){
        QMessageBox msgBox;
        msgBox.setText("请输入项目名称                                                            ");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setInformativeText("项目名称不得多于 20 个字符，且需要创建于合法路径。");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    });
    addTemplateLists();
}

STNewProject::~STNewProject() {
    delete ui;
}

void STNewProject::addTemplateLists()
{
    QWidget* totalWidget = new QWidget(this);
    QVBoxLayout* totalLayout = new QVBoxLayout(this);
    totalLayout->setAlignment(Qt::AlignTop);

    QLabel* label = new QLabel(this);
    label->setFixedHeight(15);
    QFont font1 = label->font();
    font1.setBold(true);
    label->setFont(font1);
    label->setText("Lab Studio 项目");
    totalLayout->addWidget(label);

    QGridLayout* grid_lab_studio = new QGridLayout(this);
    QWidget* grid_lab_studio_widget = new QWidget(this);


    QToolButton* button_cursor = createTemplateButton("Formula\nPlayground",":/pic/Res/pro_calc.png");
    grid_lab_studio->addWidget(button_cursor,1,1,{Qt::AlignTop, Qt::AlignLeft});

    QToolButton* button_2 = createTemplateButton("2D Bar",":/pic/Res/pro_2d.png");
    grid_lab_studio->addWidget(button_2,1,2,{Qt::AlignTop, Qt::AlignLeft});

    QToolButton* button_3 = createTemplateButton("2D Line",":/pic/Res/pro_2d.png");
    grid_lab_studio->addWidget(button_3,1,3,{Qt::AlignTop, Qt::AlignLeft});

    QToolButton* button_4 = createTemplateButton("2D Pie",":/pic/Res/pro_2d.png");
    grid_lab_studio->addWidget(button_4,1,4,{Qt::AlignTop, Qt::AlignLeft});

    QToolButton* button_5 = createTemplateButton("3D Bar",":/pic/Res/pro_3d.png");
    grid_lab_studio->addWidget(button_5,2,1,{Qt::AlignTop, Qt::AlignLeft});


    grid_lab_studio_widget->setLayout(grid_lab_studio);
    totalLayout->addWidget(grid_lab_studio_widget);


    QLabel* label2 = new QLabel(this);
    QFont font2 = label2->font();
    font2.setBold(true);
    label2->setFont(font2);
    label2->setFixedHeight(15);
    label2->setText("Simulation Studio 项目");
    totalLayout->addWidget(label2);

    QGridLayout* grid_sim_studio = new QGridLayout(this);
    QWidget* grid_sim_studio_widget = new QWidget(this);

    QToolButton* button_6 = createTemplateButton("空电路",":/pic/Res/pro_sim.png");
    grid_sim_studio->addWidget(button_6,1,1,{Qt::AlignTop, Qt::AlignLeft});

    QToolButton* button_8 = createTemplateButton("欧姆定律",":/pic/Res/pro_sim.png");
    grid_sim_studio->addWidget(button_8,1,2,{Qt::AlignTop, Qt::AlignLeft});

    QToolButton* button_9 = createTemplateButton("电容器",":/pic/Res/pro_sim.png");
    grid_sim_studio->addWidget(button_9,1,3,{Qt::AlignTop, Qt::AlignLeft});

    QToolButton* button_10 = createTemplateButton("电感",":/pic/Res/pro_sim.png");
    grid_sim_studio->addWidget(button_10,1,4,{Qt::AlignTop, Qt::AlignLeft});

    grid_sim_studio_widget->setLayout(grid_sim_studio);
    totalLayout->addWidget(grid_sim_studio_widget);


    totalWidget->setLayout(totalLayout);
    ui->scrollArea->setWidget(totalWidget);
}

QToolButton* STNewProject::createTemplateButton(QString name,QString pic)
{
    QToolButton* button_cursor = new QToolButton(this);
    button_cursor->setIcon(QIcon(pic));
    button_cursor->setIconSize(QSize(60,60));
    button_cursor->setText(name);
    button_cursor->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    button_cursor->setFixedHeight(100);
    button_cursor->setFixedWidth(130);
    button_cursor->setStyleSheet("QToolBar\n"
    "{\n"
    "background-color: rgb(255, 255, 255);\n"
    "border-width: 1px;"
    "padding: 1px;\n"
    "border-color: rgb(200,200,200);\n"
    "}\n"
    "QToolButton{ border-radius:5px; border-width: 0px;font-size: 12px; }"
    "QToolButton:hover\n"
    "{\n"
    "background: rgb(210,210,210);\n"
    "border-radius:10px;\n"
    "}");
    return button_cursor;
}