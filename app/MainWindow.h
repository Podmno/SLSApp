#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include <QPushButton>
#include <QPalette>

#include "STNewProject.h"
#include "STFileManager.h"
#include "STPreferences.h"
#include "STToolBox.h"
#include "STFormEditor.h"
#include "STSimulation.h"


#include "Sim/SGCanvasView.h"
#include "Sim/SCNetlist.h"

#include "Lab/LGDataModel.h"
#include "Lab/LGStyleCollection.h"
#include "Lab/LG2DWidget.h"
#include "Lab/LG3DWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QToolBar* toolBar;
    STFileManager* widgetFileManager;
    STPreferences* preferencesManager;
    STToolBox* toolBox;
    STFormEditor* formEditor;
    SGCanvasView* canvasView;
    STSimulation* simulationView;
    SCNetlist* netlistHelper;
    
    QWidget* window1;
    QWidget* window2;
    QWidget* window3;
    
    void initMenuBar();
    void removeDockWidgetTitleBar();
    QToolButton* createToolButton(QString, QString);
};
#endif // MAINWINDOW_H
