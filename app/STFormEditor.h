#ifndef STFORMEDITOR_H
#define STFORMEDITOR_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

namespace Ui {
class STFormEditor;
}

class STFormEditor : public QWidget
{
    Q_OBJECT

public:
    explicit STFormEditor(QWidget *parent = nullptr);
    ~STFormEditor();

private:
    Ui::STFormEditor *ui;
    
    void initForm();
};

#endif // STFORMEDITOR_H
