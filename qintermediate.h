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
    QString getActiveFile(){return activeFile;}
    QString getAName(QWidget *parent,QString message, QString title);
    QList<QString> requestInfo(QString);
    void createDataBaseFile(QString, QString);
    void readDataBaseFile(QString);
    QList<QString> getFields(QWidget *parent);
    void setActiveFile(QString);
    QString getActiveDataBaseName();
    bool isWorking(){return !activeFile.isEmpty();}

private:
    Controller engine;
    QString activeFile;
    MasterBlock masterBlock;

signals:

public slots:

};

#endif // QINTERMEDIATE_H
