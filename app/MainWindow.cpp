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
    simulationView = new STSimulation(this);
    netlistHelper = new SCNetlist();
    
    ui->tabWidget->addTab(widgetFileManager, "浏览");
    ui->tabWidget->addTab(simulationView, "模拟");

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
    
    connect(netlistHelper, &SCNetlist::signalResolveInformation, this, [=](QString msg){
        simulationView->addNewInformation(msg);
    });
    
    connect(simulationView, &STSimulation::startSimulation, this, [=](){
        qDebug() << "SLS > Start Simulation";
        
        netlistHelper->resolveFromModelList(canvasView->itemList);
        
        //netlist->resolveFromModelList(can)
        //netlist->resolveFromModelList(canvasView->item)
        
    });
    
    connect(canvasView, &SGCanvasView::onCurrentNodeChangedInfo, this, [=](QPoint currentPt){
        QString info = "当前坐标：" + QString::number(currentPt.x()) + "," + QString::number(currentPt.y());
        ui->statusbar->showMessage(info);
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
    button_copy->setEnabled(false);
    ui->toolBar->addWidget(button_copy);
    

    auto button_paste = createToolButton("粘贴",":/pic/Res/paste.png");
    button_paste->setEnabled(false);
    ui->toolBar->addWidget(button_paste);
    
    auto button_delete = createToolButton("删除",":/pic/Res/delete.png");
    button_delete->setEnabled(false);
    ui->toolBar->addWidget(button_delete);
    
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

    connect(ui->verticalScrollBar, &QScrollBar::valueChanged, canvasView, &SGCanvasView::onScroolVerticalChanged);
    connect(ui->horizontalScrollBar, &QScrollBar::valueChanged, canvasView, &SGCanvasView::onScroolHorizontalChanged);
    connect(ui->actionOpen_Project, &QAction::triggered, this, [=](){
        qDebug() << "SLS > Open Project";
        QString fileName = QFileDialog::getOpenFileName(this,"Select .sls file","/",tr("SLS File(*.sls)"));
        QFile file(fileName);
        if (fileName.isEmpty()) {
            return;
        } else {
            QString reply;
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                canvasView->showNotification("无法读取文件");
            }
            while(!file.atEnd())
            {
                QByteArray line = file.readLine();
                QString str(line);
                reply.append(str);
            }
            // 读取完成
            canvasView->loadCanvasFile(reply);
    }});
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
