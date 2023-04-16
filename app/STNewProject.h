//
// Created by Ki MNO on 2023/4/15.
//

#ifndef SLS_STNEWPROJECT_H
#define SLS_STNEWPROJECT_H

#include <QDialog>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QToolButton>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class STNewProject; }
QT_END_NAMESPACE

/// 新建项目的列表
struct STNewProjectList {
    
    
    
};


class STNewProject : public QDialog {
Q_OBJECT

public:
    explicit STNewProject(QWidget *parent = nullptr);

    ~STNewProject() override;

private:
    Ui::STNewProject *ui;

    void addTemplateLists();

    QToolButton* createTemplateButton(QString name, QString pic);
};


#endif //SLS_STNEWPROJECT_H
