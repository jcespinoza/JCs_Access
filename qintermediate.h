#ifndef QINTERMEDIATE_H
#define QINTERMEDIATE_H
#include "controller.h"
#include "qstringvalidator.h"
#include <QList>
#include <QTableWidget>
#include <QWidget>

class QIntermediate : public QWidget
{
    Q_OBJECT
public:
    explicit QIntermediate(QWidget *parent = 0);

    QString getAFilename(QWidget*parent, QString message, int type, bool &ok);
    QString getAName(QWidget *parent,QString message, QString title);
    QList<QString> getFields(QWidget *parent);
    void clearWidget(QTableWidget*);
    void loadFieldDefinitionsIntoHeader(QTableWidget*);
    bool validateRow(QTableWidget*);
    void disableRow(QTableWidget*);

    QString getActiveFile(){return activeFile;}
    void setActiveFile(QString);
    QString getActiveDataBaseName();
    QString getActiveTableName();
    bool isWorking(){return !activeFile.isEmpty();}
    void addFieldDefinition(FieldDefinition&);
    QList<FieldDefinition> getFieldDefinitions(){return fieldsDef;}
    void retrieveFieldDefinitionsFromDisk();
    int retrieveTableFromDisk(QString tName);
    void dontAllowMoreKeyFields(){keyWasSelected = true;}
    void allowKeyFields(){keyWasSelected = false;}
    bool canAcceptKeyFields()const{return !keyWasSelected;}
    void setValidatorMaxLenght(int max);
    void resetHandlerState();
    void changeTableName(QString);

    QList<QString> requestInfo(QString);
    void createDataBaseFile(QString, QString);
    void readDataBaseFile(QString);
    bool tableExists(QString);
    int writeTableDefinition();
    void writeFieldDefinitions();
    void updateCurrentTableBlock();
    void saveRecords(QTableWidget*);
    void loadRecords(QTableWidget*);

private:
    Controller engine;
    QString activeFile;
    MasterBlock masterBlock;
    QList<TableDefinition> tables;
    TableDefinition table;
    QList<FieldDefinition> fieldsDef;
    bool keyWasSelected;
    QIntValidator* intVal;
    QStringValidator* strVal;

signals:

public slots:

};

#endif // QINTERMEDIATE_H
