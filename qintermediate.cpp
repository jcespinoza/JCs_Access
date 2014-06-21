#include "qintermediate.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QDebug>
#include "addfieldsdialog.h"

QIntermediate::QIntermediate(QWidget *parent) :
    QWidget(parent)
{
}

QString QIntermediate::getAFilename(QWidget*parent, QString message, int type, bool &ok)
{
    int OPEN = 0;
    int SAVE = 1;
    QString ans;

    if(type == SAVE)
        ans = QFileDialog::getSaveFileName(parent, message, QString(), "DataBase File (*.accdb)",0,0);
    else if(type == OPEN)
        ans = QFileDialog::getOpenFileName(parent, message, QString(), "DataBase File (*.accdb)",0,0);
    ok != ans.isNull();

    return ans;
}

QString QIntermediate::getAName(QWidget *parent,QString message, QString title)
{
    QString ans = QInputDialog::getText(parent, title, message);
    return ans;
}

void QIntermediate::createDataBaseFile(QString filename, QString dbName)
{
    engine.createNewFile(filename.toStdString(), dbName.toStdString());
}

void QIntermediate::readDataBaseFile(QString filename)
{
    engine.readMasterBlock(filename.toStdString(), masterBlock);
}

QList<QString> QIntermediate::getFields(QWidget *parent)
{
    QList<QString> fieldList;
    AddFieldsDialog dialog(parent);
    int result = dialog.exec();
    if(result == QDialog::Accepted){
        fieldList.append(QString::number(dialog.getType()));
        fieldList.append(QString::number(dialog.getSize()));
        fieldList.append(dialog.getName());
    }
    return fieldList;
}

void QIntermediate::setActiveFile(QString filename)
{
    this->activeFile = filename;
}

QString QIntermediate::getActiveDataBaseName()
{
    return QString::fromStdString(masterBlock.getDataBaseName());
}