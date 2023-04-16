#ifndef STTOOLBOX_H
#define STTOOLBOX_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "Sim/SGHeaders.h"
namespace Ui {
class STToolBox;
}
///
///     元器件工具箱
///
class STToolBox : public QWidget
{
    Q_OBJECT

public:
    explicit STToolBox(QWidget *parent = nullptr);
    ~STToolBox();

private:
    Ui::STToolBox *ui;
    
    void initToolBox();
    
signals:
    
    /// 选择的元器件响应
    void ModelSelected(SGItemType);
};

#endif // STTOOLBOX_H
