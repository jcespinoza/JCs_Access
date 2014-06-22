#include "fielddefinition.h"

FieldDefinition::FieldDefinition()
{
    fieldType = 0;
    is_Key = 0;
    fieldSize = 4;
    fieldName = "ID";
}

FieldDefinition::FieldDefinition(int type, int size, int key, string name)
{
    fieldType = (type == 0 || type == 1)?type:0;
    fieldSize = (type == 1)?size:4;
    is_Key = key;
    setFieldName(name);
}

void FieldDefinition::setFieldType(int type)
{
    fieldType = (type == 0 || type == 1)?type:0;
}

void FieldDefinition::setFieldSize(int size)
{
    fieldSize = (fieldType == 1)?size:4;
}

void FieldDefinition::setAsKey()
{
    is_Key = 1;
}

void FieldDefinition::setFieldName(string name)
{
    fieldName = name;
    if(!name.empty())
        strncpy(this->name, name.c_str(),50);
    else{
        string empty = "invalid";
        strncpy(this->name, empty.c_str(), 50);
    }
}

string FieldDefinition::getFieldName() const{
    return string(name);
}

void FieldDefinition::toByteArray(char *dest, int buffSize)
{
    if(buffSize < 16) return;

    memcpy(dest, &fieldType, 4);
    memcpy(&dest[4], &fieldSize, 4);
    memcpy(&dest[8], &is_Key, 4);
    memcpy(&dest[12], name, 50);
}

void FieldDefinition::fromByteArray(char *source, int buffSize)
{
    if(buffSize < 62) return;

    memcpy(&fieldType, source, 4);
    memcpy(&fieldSize, &source[4], 4);
    memcpy(&is_Key, &source[8], 4);
    memcpy(name, &source[12], 50);

    cout << "\nF-Type: " << fieldType;
    cout << "\nF-Size: " << fieldSize;
    cout << "\nF-Key: " << is_Key;
    cout << "\nF-name: " << getFieldName();

}

int FieldDefinition::getSize()
{
    return 3*sizeof(int) + 50; //50 is the name
}
