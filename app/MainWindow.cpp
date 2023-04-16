#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widgetFileManager = new STFileManager(this);
    toolBox = new STToolBox(this);
    canvasView = new SGCanvasView(this);
    formEditor = new STFormEditor(this);
    ui->tabWidget->addTab(widgetFileManager, "浏览");

    connect(ui->actionNew_Simulation_Project, &QAction::triggered, this, [=](){
        qDebug() << "Open New Simulation Project";
        auto project_new = new STNewProject(this);

        project_new->open();
    });

    connect(ui->actionQt_Version, &QAction::triggered, this, [=](){
        QApplication::aboutQt();
    });
    
    connect(ui->actionPreferences, &QAction::triggered, this, [=](){
        STPreferences* pref = new STPreferences();
        pref->show();
    });


    initMenuBar();
    removeDockWidgetTitleBar();
    

    
    ui->dockWidget_2->setWidget(toolBox);
    ui->dockWidget_3->setWidget(formEditor);
    
    ui->gridLayout_2->addWidget(canvasView);
    
    
    
    
    connect(toolBox, &STToolBox::ModelSelected, this, [=](SGItemType type){
        qDebug() << type;
        canvasView->setFocus();
        
        canvasView->setCanvasCurrentStatus(SGCanvasViewStatus::CanvasStatusEditing);
        canvasView->setItemPrepareToDraw(type);
    });
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenuBar()
{


    qDebug() << "Init Menubar on MainWindow...";

    //QPushButton* button_cursor = new QPushButton(this);
    //button_cursor->setFixedWidth(25);

    //button_cursor->setIcon(QIcon(":/pic/Res/cursor.png"));
    //button_cursor->setText("光标");

    auto button_cursor = createToolButton("光标",":/pic/Res/cursor.png");
    ui->toolBar->addWidget(button_cursor);
    connect(button_cursor, &QPushButton::clicked, this, [=](){
        canvasView->setCanvasCurrentStatus(SGCanvasViewStatus::CanvasStatusNormal);
    });



    auto button_select = createToolButton("选择",":/pic/Res/select.png");
    ui->toolBar->addWidget(button_select);
    connect(button_select, &QPushButton::clicked, this, [=](){
        canvasView->setCanvasCurrentStatus(SGCanvasViewStatus::CanvasStatusSelecting);
    });
    
    auto button_view = createToolButton("查看",":/pic/Res/hand.png");
    ui->toolBar->addWidget(button_view);
    connect(button_view, &QPushButton::clicked, this, [=](){
        canvasView->setCanvasCurrentStatus(SGCanvasViewStatus::CanvasStatusViewing);
    });
    
    ui->toolBar->addSeparator();
    
    
    
    auto button_copy = createToolButton("复制",":/pic/Res/copy.png");
    ui->toolBar->addWidget(button_copy);
    

    auto button_paste = createToolButton("粘贴",":/pic/Res/paste.png");
    ui->toolBar->addWidget(button_paste);
    
    ui->toolBar->addSeparator();
    
    auto button_zoomin = createToolButton("放大",":/pic/Res/zoom_add.png");
    connect(button_zoomin, &QPushButton::clicked, this, [=](){
        
        canvasView->onZoomIncreaseClicked();
    });
    ui->toolBar->addWidget(button_zoomin);
    
    auto button_zoomout = createToolButton("缩小",":/pic/Res/zoom_minus.png");
    ui->toolBar->addWidget(button_zoomout);
    connect(button_zoomout, &QPushButton::clicked, this, [=](){
        canvasView->onZoomDecreaseClicked();
    });
    
    ui->toolBar->setIconSize(QSize(25,25));

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setColor(QColor(171,171,171));
    //shadowEffect->setBlurRadius(40);
    shadowEffect->setOffset(0,0.5);
    ui->toolBar->setGraphicsEffect(shadowEffect);
    
    
    QGraphicsDropShadowEffect* shadowEffect2 = new QGraphicsDropShadowEffect(this);
    shadowEffect2->setColor(QColor(171,171,171));
    //shadowEffect->setBlurRadius(40);
    shadowEffect2->setOffset(0,-0.5);
    ui->statusbar->setGraphicsEffect(shadowEffect2);
    
    
    //this->setStyleSheet("QDockWidget#"+ui->dockWidget_2->objectName()+"::title {background-color: white; }");
    
    QPalette pal;

    pal.setColor(QPalette::Window, Qt::white);
    ui->dockWidget_2->setAutoFillBackground(true);
    ui->dockWidget_2->setPalette(pal);

    ui->dockWidget_3->setAutoFillBackground(true);
    ui->dockWidget_3->setPalette(pal);
    


}

void MainWindow::removeDockWidgetTitleBar()
{
    QWidget* lTitleBar = ui->dockWidget->titleBarWidget();
    QWidget* lEmptyWidget = new QWidget();
    ui->dockWidget->setTitleBarWidget(lEmptyWidget);
    delete lTitleBar;

    // MacEdit
    setUnifiedTitleAndToolBarOnMac(true);

}

QToolButton* MainWindow::createToolButton(QString name, QString iconp)
{
    QToolButton* button_cursor = new QToolButton(this);
    button_cursor->setIcon(QIcon(iconp));
    button_cursor->setIconSize(QSize(10,10));
    button_cursor->setText(name);
    button_cursor->setToolButtonStyle(Qt::ToolButtonIconOnly);
    button_cursor->setFixedHeight(30);
    button_cursor->setFixedWidth(35);
    return button_cursor;
}
