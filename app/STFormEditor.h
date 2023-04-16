#ifndef STFORMEDITOR_H
#define STFORMEDITOR_H

#include <QWidget>

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
};

#endif // STFORMEDITOR_H
