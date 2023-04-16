#ifndef SGEDITORModel_H
#define SGEDITORModel_H

#include <QDialog>
#include "SGFile.h"

namespace Ui {
class SGEditorModel;
}

class SGEditorModel : public QDialog
{
    Q_OBJECT

public:
    explicit SGEditorModel(QWidget *parent = nullptr);
    ~SGEditorModel();
    

    void setModelPointer(SGModelBase*);
    void showEditor();
    
    QList<QWidget*> editingStack;
    
    QWidget* editingContentWidget;
    
private:
    Ui::SGEditorModel *ui;
    
    SGModelBase* Model;
};

#endif // SGEDITORModel_H
