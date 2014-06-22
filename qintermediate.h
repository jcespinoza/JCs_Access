#ifndef QINTERMEDIATE_H
#define QINTERMEDIATE_H
#include "controller.h"
#include <QList>

#include <QWidget>

class QIntermediate : public QWidget
{
    Q_OBJECT
public:
    explicit QIntermediate(QWidget *parent = 0);

    QString getAFilename(QWidget*parent, QString message, int type, bool &ok);
    QString getAName(QWidget *parent,QString message, QString title);
    QList<QString> getFields(QWidget *parent);

    QString getActiveFile(){return activeFile;}
    void setActiveFile(QString);
    QString getActiveDataBaseName();
    bool isWorking(){return !activeFile.isEmpty();}
    void addFieldDefinition(FieldDefinition&);
    QList<FieldDefinition> getFieldDefinitions(){return fieldsDef;}
    void dontAllowMoreKeyFields(){keyWasSelected = true;}
    void allowKeyFields(){keyWasSelected = false;}
    bool canAcceptKeyFields()const{return !keyWasSelected;}
    void resetHandlerState();
    void changeTableName(QString);

    QList<QString> requestInfo(QString);
    void createDataBaseFile(QString, QString);
    void readDataBaseFile(QString);
    bool tableExists(QString);
    void writeTableDefinition();
    void writeFieldDefinitions();
    void updateCurrentTableBlock();

private:
    Controller engine;
    QString activeFile;
    MasterBlock masterBlock;
    TableDefinition table;
    QList<FieldDefinition> fieldsDef;
    bool keyWasSelected;

signals:

public slots:

};

#endif // QINTERMEDIATE_H
