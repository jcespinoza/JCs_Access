#include "mwindow.h"
#include "ui_mwindow.h"
#include <QDebug>
#include <QMessageBox>

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

void MWindow::showStatistics()
{
    ui->stackedWidget->setCurrentWidget(ui->pgStatistics);
    ui->lbDataBaseName->setText(handler.getActiveDataBaseName());
    QList<QString> info = handler.requestInfo(handler.getActiveFile());
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
    showStatistics();
}

void MWindow::on_pbOpenDataBase_clicked()
{
    bool ok = true;
    QString filename = handler.getAFilename(this, "Elija el archivo de la base de datos", 0, ok);
    if(!ok || filename.isEmpty())
        return;
    handler.readDataBaseFile(filename);
    handler.setActiveFile(filename);
    showStatistics();
}

void MWindow::on_lwTablesList_itemDoubleClicked(QListWidgetItem *item)
{
    //Code to open that table on another panel
}

void MWindow::on_action_Nuevo_triggered()
{
    //code to close current database here
    on_pbNewDataBase_clicked();
}

void MWindow::on_action_Abrir_triggered()
{
    if(handler.isWorking()){
        int res = QMessageBox::warning(this, "Precaucion", "Hay una base de datos abierta, desea cerrarla primero?", QMessageBox::Yes, QMessageBox::No);
        if(res == QMessageBox::Yes)
            on_pbOpenDataBase_clicked();
    }
}

void MWindow::on_actionCerrar_Bade_de_Datos_triggered()
{
    //code
    showWelcomeScreen();
}

void MWindow::on_action_Salir_triggered()
{
    //code to save changes first then close
}

void MWindow::on_actionNueva_Tabla_triggered()
{
    //Code to add a table to the current database
}

void MWindow::on_actionAcerca_de_JC_s_Access_triggered()
{
    //code to show the developers info
}
