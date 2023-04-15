#ifndef SGCANVASNOTIFICATION_H
#define SGCANVASNOTIFICATION_H

#include <QWidget>
#include "SGFile.h"

namespace Ui {
class SGCanvasNotification;
}

class SGCanvasNotification : public QWidget
{
    Q_OBJECT

public:
    explicit SGCanvasNotification(QWidget *parent = nullptr);
    ~SGCanvasNotification();
    
    /// 设定通知显示的内容
    void setNotificationContent(QString);


    
private:
    Ui::SGCanvasNotification *ui;
    QPropertyAnimation* m_animation;
    QTimer* timer;
};

#endif // SGCANVASNOTIFICATION_H
