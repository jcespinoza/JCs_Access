#include "mwindow.h"
#include "ui_mwindow.h"

MWindow::MWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWindow)
{
    ui->setupUi(this);
}

MWindow::~MWindow()
{
    delete ui;
}

void MWindow::on_pbNewDataBase_clicked()
{

}

void MWindow::on_pbOpenDataBase_clicked()
{

}
