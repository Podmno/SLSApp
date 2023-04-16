#ifndef STPREFERENCES_H
#define STPREFERENCES_H

#include <QMainWindow>

namespace Ui {
class STPreferences;
}

class STPreferences : public QMainWindow
{
    Q_OBJECT

public:
    explicit STPreferences(QWidget *parent = nullptr);
    ~STPreferences();

private:
    Ui::STPreferences *ui;
};

#endif // STPREFERENCES_H
