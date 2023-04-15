#ifndef SGEDITORMODAL_H
#define SGEDITORMODAL_H

#include <QDialog>
#include "SGFile.h"

namespace Ui {
class SGEditorModal;
}

class SGEditorModal : public QDialog
{
    Q_OBJECT

public:
    explicit SGEditorModal(QWidget *parent = nullptr);
    ~SGEditorModal();
    

    void setModalPointer(SGModalBase*);
    void showEditor();
    
    QList<QWidget*> editingStack;
    
    QWidget* editingContentWidget;
    
private:
    Ui::SGEditorModal *ui;
    
    SGModalBase* modal;
};

#endif // SGEDITORMODAL_H
