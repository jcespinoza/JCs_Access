#ifndef MWINDOW_H
#define MWINDOW_H
#include "qintermediate.h"
#include <QListWidgetItem>

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
    void showWelcomeScreen();
    void showStatistics();
    void on_pbNewDataBase_clicked();
    void on_pbOpenDataBase_clicked();

    void on_lwTablesList_itemDoubleClicked(QListWidgetItem *item);

    void on_action_Nuevo_triggered();

    void on_action_Abrir_triggered();

    void on_actionCerrar_Bade_de_Datos_triggered();

    void on_action_Salir_triggered();

    void on_actionNueva_Tabla_triggered();

    void on_actionAcerca_de_JC_s_Access_triggered();

    void on_pbAddTable_clicked();

    void on_pbAddField_clicked();

    void on_pbDiscardFieldDefinition_clicked();

    void on_pbAcceptFieldDefinition_clicked();

    void on_pbAddRecords_clicked();

    void on_pbCerrarDB_clicked();

private:
    Ui::MWindow *ui;
    QIntermediate handler;
};

#endif // MWINDOW_H
