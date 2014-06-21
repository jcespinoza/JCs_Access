#include "qintermediate.h"
#include <QFileDialog>
#include <QInputDialog>
#include "addfieldsdialog.h"

QIntermediate::QIntermediate(QWidget *parent) :
    QWidget(parent)
{
}

QString QIntermediate::getAFilename(QWidget*parent, QString message, int type, bool &ok)
{
    int OPEN = 0;
    int SAVE = 1;
    int DIR = 2;
    QString ans;
    if(type == SAVE)
        ans = QFileDialog::getSaveFileName(parent, message,QString(), "DataBase File (*.accdb)",0,0);
    else if(type == OPEN)
        ans QFileDialog::getOpenFileName(parent, message, QString(), "DataBase File (*.accdb)",0,0);
    return ans;
}

QString QIntermediate::getAName(QWidget *parent,QString message, QString title)
{
    QString ans = QInputDialog::getText(parent, title, message);
    return ans;
}

QList<QString> QIntermediate::getFields(QWidget *parent)
{
    QList<QString> returnList;
    AddFieldsDialog dialog(parent);
    int result = dialog.show();


}
