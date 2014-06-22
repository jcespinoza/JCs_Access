#ifndef FIELDDEFINITION_H
#define FIELDDEFINITION_H
#include <string>
#include <cstring>
using namespace std;

class FieldDefinition
{
public:
    FieldDefinition();
    FieldDefinition(int,int,int,string);

    void setFieldType(int);
    void setFieldSize(int);
    void setAsKey();
    void setFieldName(string);

    int getFieldType()const{return fieldType;}
    int getFieldSize()const{return fieldSize;}
    bool isKey(){return is_Key==1;}
    string getFieldName()const{return fieldName;}

private:
    int fieldType;
    int is_Key;
    int fieldSize;
    string fieldName;
};

#endif // FIELDDEFINITION_H
