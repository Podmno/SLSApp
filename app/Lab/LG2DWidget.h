#ifndef LG2DWidget_H
#define LG2DWidget_H

#include <QWidget>


#include "LGStyleCollection.h"
#include "LGDataModel.h"

namespace Ui {
class LG2DWidget;
}

class LG2DWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LG2DWidget(QWidget *parent = nullptr);
    ~LG2DWidget();
   
    QChartView* getChartView();

    void update();
    
    LGBaseModel* dataModel;
    
private:
    Ui::LG2DWidget *ui;
    QChartView* chartView;
};

#endif // LG2DWidget_H
