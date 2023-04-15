#include <QPropertyAnimation>
#include "SGCanvasNotification.h"
#include "ui_SGCanvasNotification.h"

SGCanvasNotification::SGCanvasNotification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SGCanvasNotification)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    m_animation = new QPropertyAnimation();
    //m_animation->setTargetObject(ui->label);
    m_animation->setEasingCurve(QEasingCurve::Linear);

    connect(timer, &QTimer::timeout, this, [=](){
        this->setVisible(false);
    });
}

void SGCanvasNotification::setNotificationContent(QString content)
{
    this->setVisible(true);
    QGraphicsOpacityEffect * m_pGraphicsOpacityEffect;
    QPropertyAnimation * m_pOpacityAnimation;

    m_pGraphicsOpacityEffect = new QGraphicsOpacityEffect(ui->label);
    m_pGraphicsOpacityEffect->setOpacity(1.0);
    ui->label->setGraphicsEffect(m_pGraphicsOpacityEffect);

    m_pOpacityAnimation = new QPropertyAnimation(m_pGraphicsOpacityEffect,"opacity",this);
    m_pOpacityAnimation->setDuration(2000);

    m_pOpacityAnimation->setKeyValueAt(0.0,1);
    m_pOpacityAnimation->setKeyValueAt(0.8,1);
    m_pOpacityAnimation->setKeyValueAt(1.0,0);
    m_pOpacityAnimation->start();
    ui->label->setGraphicsEffect(m_pGraphicsOpacityEffect);

    timer->start(Canvas_NoticeTimer);
    ui->label->setText(content);
}

SGCanvasNotification::~SGCanvasNotification()
{
    delete ui;
}
