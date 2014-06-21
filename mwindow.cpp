#include "mwindow.h"
#include "ui_mwindow.h"
#include <QDebug>

MWindow::MWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWindow)
{
    ui->setupUi(this);
    showWelcomeScreen();
}

MWindow::~MWindow()
{
    delete ui;
}

void MWindow::showWelcomeScreen()
{
    ui->stackedWidget->setCurrentWidget(ui->pgWelcome);
}

void MWindow::on_pbNewDataBase_clicked()
{
    bool ok = true;
    QString filename = handler.getAFilename(this, "Elija el nombre para el archivo de la base de datos", 1, ok);
    if(!ok || filename.isEmpty()){
        qDebug() << "Something went wrong!" << filename;
        return;
    }
    QString name = handler.getAName(this, "Introduzca un nombre para la base de datos.", "Nombre de Base de Datos");
    if(!name.isEmpty()){
        handler.createDataBaseFile(filename, name);
        handler.setActiveFile(filename);
    }
}

void MWindow::on_pbOpenDataBase_clicked()
{
    bool ok = true;
    QString filename = handler.getAFilename(this, "Elija el archivo de la base de datos", 0, ok);
    if(!ok)
        return;
    handler.readDataBaseFile(filename);
    handler.setActiveFile(filename);
    qDebug() << "Opened the database " << handler.getActiveDataBaseName();
}
