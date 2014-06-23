#include "qintermediate.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QDebug>
#include "addfieldsdialog.h"
#include <QHeaderView>

QIntermediate::QIntermediate(QWidget *parent) :
    QWidget(parent)
{
    keyWasSelected = false;
    intVal = new QIntValidator(this);
    strVal = new QStringValidator(this);
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
    tables = QList<TableDefinition>::fromStdList(engine.readTableList(filename.toStdString(), masterBlock));
    details.append(QString::number(tables.count()));
    qDebug() << "Tables from FILe: " << tables.count();
    for(int i = 0; i < tables.count(); i++){
        details.append(QString::fromStdString(tables.at(i).getName()));
    }
    return details;
}

void QIntermediate::addFieldDefinition(FieldDefinition &field)
{
    fieldsDef.append(field);
}

void QIntermediate::retrieveFieldDefinitionsFromDisk()
{
    fieldsDef = QList<FieldDefinition>::fromStdList(engine.readFieldList(getActiveFile().toStdString(), masterBlock, table));
}

int QIntermediate::retrieveTableFromDisk(QString tName)
{
    return engine.readTableDefinition(getActiveFile().toStdString(), masterBlock, table, tName.toStdString());
}

void QIntermediate::setValidatorMaxLenght(int max)
{
    strVal->setMaxLenght(max);
}

void QIntermediate::resetHandlerState()
{
    allowKeyFields();
    fieldsDef.clear();
    table = TableDefinition();
    tables.clear();
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
    engine.readMasterBlock(filename.toStdString(), masterBlock);
}

bool QIntermediate::tableExists(QString tableName)
{
    return engine.doesTableExist(getActiveFile().toStdString(), tableName.toStdString(), masterBlock);
}

int QIntermediate::writeTableDefinition()
{
    return engine.writeTableDefinition(getActiveFile().toStdString(), masterBlock, table);
}

void QIntermediate::writeFieldDefinitions()
{
    engine.writeFieldsDefinition(getActiveFile().toStdString(),masterBlock, fieldsDef.toStdList(), table);
}

void QIntermediate::updateCurrentTableBlock()
{
    engine.updateCurrentTableBlock(getActiveFile().toStdString(), masterBlock, table);
}

void QIntermediate::saveRecords(QTableWidget *)
{

}

void QIntermediate::loadRecords(QTableWidget *)
{

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

void QIntermediate::clearWidget(QTableWidget *tw)
{
    while(tw->rowCount() > 0){
        tw->removeRow(tw->rowCount()-1);
    }
}

void QIntermediate::loadFieldDefinitionsIntoHeader(QTableWidget *tw)
{
    while(tw->rowCount() > 0)
        tw->removeRow(tw->rowCount()-1);
    tw->setRowCount(0);
    tw->setColumnCount(0);

    QStringList headerLabels;
    for(int i = 0; i < fieldsDef.count(); i++){
        QString h = QString::fromStdString(fieldsDef.at(i).getFieldName());
        h.append(" (").append(QString::number(fieldsDef.at(i).getFieldSize())).append(")");
        headerLabels.append(h);
        tw->insertColumn(i);
    }
    tw->setHorizontalHeaderLabels(headerLabels);
    tw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

bool QIntermediate::validateRow(QTableWidget *tw)
{
    int faults = 0;
    int row = tw->rowCount()-1;
    qDebug() << "rowCount is" << row+1;
    for(int col = 0; col < tw->columnCount(); col++){
        int maxLenght = fieldsDef.at(col).getFieldSize();
        QString text = tw->item(row,col)->text();
        if(fieldsDef.at(col).getFieldType() == 0){
            int pos(0);
            if(intVal->validate(text,pos)==QValidator::Invalid)
                faults++;
        }else{
            if(strVal->validate(text, maxLenght) == QValidator::Invalid)
                faults++;
        }
    }
    return faults == 0;
}

void QIntermediate::disableRow(QTableWidget *tw)
{
    int row = tw->rowCount()-1;
    for(int col = 0; col < tw->columnCount(); col++){
        tw->item(row,col)->setFlags(Qt::NoItemFlags);
    }
}

void QIntermediate::setActiveFile(QString filename)
{
    this->activeFile = filename;
}

QString QIntermediate::getActiveDataBaseName()
{
    return QString::fromStdString(masterBlock.getDataBaseName());
}

QString QIntermediate::getActiveTableName()
{
    return QString::fromStdString(table.getName());
}
