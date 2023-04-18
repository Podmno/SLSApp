#ifndef STGRAPHICCONTAINER_H
#define STGRAPHICCONTAINER_H

#include <QWidget>

namespace Ui {
class STGraphicContainer;
}

class STGraphicContainer : public QWidget
{
    Q_OBJECT

public:
    explicit STGraphicContainer(QWidget *parent = nullptr);
    ~STGraphicContainer();

private:
    Ui::STGraphicContainer *ui;
};

#endif // STGRAPHICCONTAINER_H
