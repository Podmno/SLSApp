#ifndef LG3DWIDGET_H
#define LG3DWIDGET_H

#include <QWidget>
#include "LGDataModel.h"

namespace Ui {
class LG3DWidget;
}

class LG3DWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LG3DWidget(QWidget *parent = nullptr);
    ~LG3DWidget();
    
    void update();

    LGBaseModel* dataModel;
    
private:
    Ui::LG3DWidget *ui;
};

#endif // LG3DWIDGET_H
