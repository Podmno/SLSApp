#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include <QPushButton>
#include <QPalette>
#include "STNewProject.h"
#include "STFileManager.h"
#include "Sim/SGCanvasView.h"
#include "STPreferences.h"
#include "STToolBox.h"
#include "STFormEditor.h"

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
    
    void initMenuBar();
    void removeDockWidgetTitleBar();
    QToolButton* createToolButton(QString, QString);
};
#endif // MAINWINDOW_H
