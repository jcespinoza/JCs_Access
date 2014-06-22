#ifndef FIELDDEFINITION_H
#define FIELDDEFINITION_H
#include <string>
#include <cstring>
#include <iostream>
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
    string getFieldName()const;
    void toByteArray(char* dest, int buffSize);
    void fromByteArray(char* source, int buffSize);
    static int getSize();

private:
    int fieldType;
    int is_Key;
    int fieldSize;
    string fieldName;
    char name[50];
};

#endif // FIELDDEFINITION_H
