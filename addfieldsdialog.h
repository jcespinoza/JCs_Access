#ifndef ADDFIELDSDIALOG_H
#define ADDFIELDSDIALOG_H

#include <QDialog>

namespace Ui {
class AddFieldsDialog;
}

class AddFieldsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFieldsDialog(QWidget *parent = 0);
    ~AddFieldsDialog();
    int getType(){return type;}
    int getSize(){return size;}
    int getKey(){return key;}
    QString getName(){return name;}

private slots:
    void on_buttonBox_accepted();
    void on_cboFieldType_currentIndexChanged(int index);
    void on_leFieldSize_editingFinished();
    void on_leFieldName_editingFinished();

    void on_rbKeyYes_toggled(bool checked);

private:
    Ui::AddFieldsDialog *ui;
    int type;
    int size;
    int key;
    QString name;
};

#endif // ADDFIELDSDIALOG_H
