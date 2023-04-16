//
// Created by Ki MNO on 2023/4/15.
//

#ifndef SLS_STFILEMANAGER_H
#define SLS_STFILEMANAGER_H

#include <QWidget>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class STFileManager; }
QT_END_NAMESPACE

class STFileManager : public QWidget {
Q_OBJECT

public:
    explicit STFileManager(QWidget *parent = nullptr);

    ~STFileManager() override;

private:
    Ui::STFileManager *ui;

    QFileSystemModel* model;
};


#endif //SLS_STFILEMANAGER_H
