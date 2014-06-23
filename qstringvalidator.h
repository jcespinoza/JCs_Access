#ifndef QSTRINGVALIDATOR_H
#define QSTRINGVALIDATOR_H

#include <QValidator>
#include <QString>

class QStringValidator : public QValidator {
   Q_OBJECT
public:
    explicit QStringValidator(QObject* parent = 0){
        maxLenght = 50;
    }

    int getMaxLenght()const{return maxLenght;}
    void setMaxLenght(int max){maxLenght = max;}

    QValidator::State validate(QString& str, int&max) const{
        if(str.length() <= max)
            return Acceptable;
        else
            return Invalid;
    }
private:
    int maxLenght;
};

#endif // QSTRINGVALIDATOR_H
