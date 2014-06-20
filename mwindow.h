#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>

namespace Ui {
class MWindow;
}

class MWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWindow(QWidget *parent = 0);
    ~MWindow();

private:
    Ui::MWindow *ui;
};

#endif // MWINDOW_H
