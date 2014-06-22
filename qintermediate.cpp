#include "qintermediate.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QDebug>
#include "addfieldsdialog.h"

QIntermediate::QIntermediate(QWidget *parent) :
    QWidget(parent)
{
    keyWasSelected = false;
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

QList<QString> QIntermediate::requestInfo(QString filename)
{
    QList<QString> details;
    details.append(QString(masterBlock.getDataBaseName().c_str()));
    engine.readTableList(filename.toStdString(), masterBlock);
    return details;
}

void QIntermediate::addFieldDefinition(FieldDefinition &field)
{
    fieldsDef.append(field);
}

void QIntermediate::resetHandlerState()
{
    allowKeyFields();
    fieldsDef.clear();
    //reset table definition variables
}

void QIntermediate::changeTableName(QString tableName)
{
    qDebug() << "Sending string " << tableName;
    table.setName(tableName.toStdString());
}

void QIntermediate::createDataBaseFile(QString filename, QString dbName)
{
    masterBlock.setName(dbName.toStdString());
    engine.createNewFile(filename.toStdString(), masterBlock);
}

void QIntermediate::readDataBaseFile(QString filename)
{
    qDebug() << "Asking the Endgine to read the file";
    engine.readMasterBlock(filename.toStdString(), masterBlock);
}

bool QIntermediate::tableExists(QString tableName)
{
    return engine.doesTableExist(getActiveFile().toStdString(), tableName.toStdString(), masterBlock);
}

void QIntermediate::writeTableDefinition()
{
    engine.writeTableDefinition(getActiveFile().toStdString(), masterBlock, table);
}

void QIntermediate::writeFieldDefinitions()
{
    engine.writeFieldsDefinition(getActiveFile().toStdString(),masterBlock, fieldsDef.toStdList(), table);
}

void QIntermediate::updateCurrentTableBlock()
{
    engine.updateCurrentTableBlock(getActiveFile().toStdString(), masterBlock, table);
}

QList<QString> QIntermediate::getFields(QWidget *parent)
{
    QList<QString> fieldList;
    AddFieldsDialog dialog(parent);
    int result = dialog.exec();
    if(result == QDialog::Accepted){
        fieldList.append(QString::number(dialog.getType()));
        fieldList.append(QString::number(dialog.getSize()));
        fieldList.append(QString::number(dialog.getKey()));
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
