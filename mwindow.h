#ifndef MWINDOW_H
#define MWINDOW_H
#include "qintermediate.h"

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

private slots:
    void on_pbNewDataBase_clicked();

    void on_pbOpenDataBase_clicked();

private:
    Ui::MWindow *ui;
    QIntermediate handler;
};

#endif // MWINDOW_H
