#include "addfieldsdialog.h"
#include "ui_addfieldsdialog.h"

AddFieldsDialog::AddFieldsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFieldsDialog)
{
    ui->setupUi(this);
}

AddFieldsDialog::~AddFieldsDialog()
{
    delete ui;
}

void AddFieldsDialog::on_buttonBox_accepted()
{
    if(ui->leFieldName->text().isEmpty() || ui->leFieldSize->text().isEmpty()
            || ui->leFieldSize->text().toInt() < 4)
        reject();
}

void AddFieldsDialog::on_cboFieldType_currentIndexChanged(int index)
{
    if(ui->cboFieldType->currentIndex() == 0){
        type = 0;
        ui->leFieldSize->setText("4");
        ui->leFieldSize->setEnabled(false);
    }else{
        type = 1;
        ui->leFieldSize->setEnabled(true);
    }
}

void AddFieldsDialog::on_leFieldSize_editingFinished()
{
    size = ui->leFieldSize->text().toInt();
}

void AddFieldsDialog::on_leFieldName_editingFinished()
{
    name = ui->leFieldName->text();
}
