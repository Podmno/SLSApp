#ifndef STFORMEDITOR_H
#define STFORMEDITOR_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

#include "Lab/LGDataModel.h"

namespace Ui {
class STFormEditor;
}

class STFormEditor : public QWidget
{
    Q_OBJECT

public:
    explicit STFormEditor(QWidget *parent = nullptr);
    ~STFormEditor();

    int rowCount;
    int colCount;
signals:
    void onDataFormFinished(LGBaseModel*);
    
private:
    Ui::STFormEditor *ui;
    void parseTableWidgetData();
    void initForm();
    
    bool instantForm;
};

#endif // STFORMEDITOR_H
