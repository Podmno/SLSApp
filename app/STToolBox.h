#ifndef STTOOLBOX_H
#define STTOOLBOX_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
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
};

#endif // STTOOLBOX_H
