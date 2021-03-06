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
    ui->lwTablesList->clear();
    handler.clearWidget(ui->twFieldsDefinition);
    handler.readDataBaseFile(handler.getActiveFile());
    ui->stackedWidget->setCurrentWidget(ui->pgStatistics);
    ui->lbDataBaseName->setText(handler.getActiveDataBaseName());
    ui->lbDataBaseName_DataPage->setText(handler.getActiveDataBaseName());
    QList<QString> info = handler.requestInfo(handler.getActiveFile());
    ui->lbDataBaseName->setText(info.at(0));
    ui->lbNumberOfTables->setText(info.at(1));

    for(int i = 2; i < info.count(); i++){
        ui->lwTablesList->addItem(info.at(i));
    }
}

void MWindow::showDataPanel()
{
    handler.retrieveFieldDefinitionsFromDisk();
    handler.loadFieldDefinitionsIntoHeader(ui->twData);
    ui->lbTableName->setText(handler.getActiveTableName());
    ui->stackedWidget->setCurrentWidget(ui->pgData);
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
    handler.resetHandlerState();
    bool ok = true;
    QString filename = handler.getAFilename(this, "Elija el archivo de la base de datos", 0, ok);
    if(!ok || filename.isEmpty())
        return;
    handler.readDataBaseFile(filename);
    handler.setActiveFile(filename);
    showStatistics();
}

void MWindow::on_lwTablesList_itemDoubleClicked(QListWidgetItem *)
{
    on_pbAddRecords_clicked();
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
    }else{
        on_pbOpenDataBase_clicked();
    }
}

void MWindow::on_actionCerrar_Bade_de_Datos_triggered()
{
    handler.resetHandlerState();
    showWelcomeScreen();
}

void MWindow::on_action_Salir_triggered()
{
    QApplication::exit();
}

void MWindow::on_actionNueva_Tabla_triggered()
{
    if(handler.getActiveDataBaseName() == "invalid"
            || handler.getActiveFile().isEmpty()){
        QMessageBox::information(this, "Accion Invalida", "Debe abrir una base de datos antes de poder agregar un tabla");
        return;
    }
    on_pbAddTable_clicked();
}

void MWindow::on_actionAcerca_de_JC_s_Access_triggered()
{
    //code to show the developers info
}

void MWindow::on_pbAddTable_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pgNewTable);
}

void MWindow::on_pbAddField_clicked()
{
    QList<QString> fields = handler.getFields(this);
    if(fields.isEmpty()) return;
    FieldDefinition def( fields[0].toInt(), fields[1].toInt(), fields[2].toInt(), fields[3].toStdString());
    fields[2] = (def.isKey())?"Si":"No";
    fields[0] = (def.getFieldType()==0)?"Entero":"Caracteres";
    if(def.isKey() && !handler.canAcceptKeyFields()){
        QMessageBox::warning(this,"Multiple Llave no soportado", "Usted ya selecciono un campo llave",QMessageBox::Ok);
        return;
    }
    int row = ui->twFieldsDefinition->rowCount();
    ui->twFieldsDefinition->insertRow(row);
    for(int i = 0; i < fields.count(); i++){
        ui->twFieldsDefinition->setItem(row, i, new QTableWidgetItem(fields.at(i)));
    }
    handler.addFieldDefinition(def);
    if(def.isKey()) handler.dontAllowMoreKeyFields();
}

void MWindow::on_pbDiscardFieldDefinition_clicked()
{
    int result = QMessageBox::Yes;
    if(handler.getFieldDefinitions().count() > 0)
        result = QMessageBox::question(this, "Descartar Cambios?", "Seguro que desea descartar la definicion de la tabla?");
    if(result == QMessageBox::No) return;
    showStatistics();
}

void MWindow::on_pbAcceptFieldDefinition_clicked()
{
    int result = 0;
    if(handler.getFieldDefinitions().count() < 1)
        result = QMessageBox::warning(this, "Tabla sin Campos", "Esta intentando guardar una tabla sin campos. Desea descartar los cambios?", QMessageBox::Yes,QMessageBox::No);
    if(result == QMessageBox::Yes){
        showStatistics();
        return;
    }
    if(result == QMessageBox::No) return;

    QString tableName = handler.getAName(this, "Ingrese un nombre para esta tabla", "Nombre de Tabla");
    if(tableName.isEmpty()) return;
    //check if the table exists
    if(handler.tableExists(tableName)){
        QMessageBox::warning(this, "Nombre en Conflicto", "Ya existe una tabla con ese nombre");
        return;
    }
    handler.changeTableName(tableName);
    if(handler.writeTableDefinition() == 0){
        handler.writeFieldDefinitions();
        handler.updateCurrentTableBlock();
    }
    //write all definitions to a block and save to disk

    //increment the block count in the master properties
    //numberOfBlocks, numberOfTAbleBlocks and numberOffieldBlocks
    handler.resetHandlerState();
    showStatistics();
}

void MWindow::on_pbAddRecords_clicked()
{
    //code to get the selected index from the list of tables
    int selected = ui->lwTablesList->currentRow();
    qDebug() << "Selcted " << selected;
    if(selected == -1){
        QMessageBox::information(this, "Sin Selection", "Por favor seleccione una tabla de la lista");
        return;
    }
    handler.retrieveTableFromDisk(ui->lwTablesList->currentItem()->text());
    showDataPanel();
}

void MWindow::on_pbCerrarDB_clicked()
{
    on_actionCerrar_Bade_de_Datos_triggered();
}

void MWindow::on_actionHacer_Consultar_triggered()
{
    //Code to look by key here
}

void MWindow::on_pbQuery_clicked()
{
    on_actionHacer_Consultar_triggered();
}

void MWindow::on_actionCerrar_Tabla_triggered()
{
    //Ask to save changes
    showStatistics();
}

void MWindow::on_pbAddRow_clicked()
{
    if(ui->twData->rowCount() < 1){
        ui->twData->insertRow(ui->twData->rowCount());
    }else{
        if(handler.validateRow(ui->twData)){
            handler.disableRow(ui->twData);
            ui->twData->insertRow(ui->twData->rowCount());
        }else{
            QMessageBox::warning(this, "Datos Invalidos", "Al menos uno de los campos no cumple con la definicion. Por favor verifique los datos");
        }
    }
}

void MWindow::on_pbSaveRecords_clicked()
{
    if(ui->twData->rowCount() < 1)
        return;
    else{
        if(handler.validateRow(ui->twData)){
            handler.disableRow(ui->twData);
        }else{
            QMessageBox::warning(this, "Datos Invalidos", "Al menos uno de los campos no cumple con la definicion. Por favor verifique los datos");
            return;
        }
    }
    if(ui->twData->rowCount() > 0){
        handler.saveRecords(ui->twData);
    }
}

void MWindow::on_pbDiscardRecords_clicked()
{
    //Check whether there is at least one record
}
