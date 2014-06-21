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

    QString getAFilename(QString message, QString Title);
    QString getAName(QString message);
    QList<QString> getFields(QWidget *parent);

private:
    Controller engine;
signals:

public slots:

};

#endif // QINTERMEDIATE_H
