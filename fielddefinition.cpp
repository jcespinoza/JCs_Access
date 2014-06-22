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
    fieldName = name;
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
}
