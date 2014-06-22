#include "tabledefinition.h"
#include <iostream>
#include <cstring>

using namespace std;

TableDefinition::TableDefinition()
{
    blockID = 1;
    tableID = 0;
    name = "invalid";
    nDataRecords = 0;
    nFields = 0;
    firstDataBlock = -1;
    firstFieldBlock = -1;
    activeDataBlock = -1;
    indexBlockID = -1;
}

string TableDefinition::getName() const{
    cout << "\nReturning " << name << " which should be equal to " << tableName;
    return name;
}

string TableDefinition::getTableName() const {
    cout << "\nTAbleName: " << tableName;
    cout << "\nREturn value: " << string(tableName);
    return string(tableName);
}

void TableDefinition::setBlockID(int i )
{
    blockID = i;
}

void TableDefinition::setTableID(int i)
{
    tableID = i;
}

void TableDefinition::setName(string na)
{
    name = na;
    if(!na.empty()){
        strncpy(tableName, na.c_str(),50);
    }else{
        string empty = "invalid";
        strncpy(tableName, empty.c_str(), 50);
    }
    cout << "\nValue set: " << tableName;
}

void TableDefinition::incrementNDataRecords()
{
    nDataRecords += 1;
}

void TableDefinition::setNDataRecords(int i)
{
    nDataRecords = i;
}

void TableDefinition::setFirstDataBlock(int i)
{
    firstDataBlock = i;
}

void TableDefinition::setFirstFieldBlock(int i)
{
    firstFieldBlock = i;
}

void TableDefinition::setIndexBlockID(int i)
{
    indexBlockID = i;
}

void TableDefinition::setActiveDataBlock(int i)
{
    activeDataBlock = i;
}

void TableDefinition::setNFields(int i)
{
    nFields = i;
}

int TableDefinition::getSize()
{
    return 6*sizeof(int)+50; //50 is the max lenght of any name;
}

void TableDefinition::toByteArray(char *dest, int buffSize)
{
    if(buffSize < 74){
        cout << "GOT OUT";
        return;
    }
    memcpy(dest, &nFields, 4);
    int temp = 0;
    memcpy(&temp, &dest[0], 4);
    cout << "\nWROTE FIELDS: " << temp;
    memcpy(&dest[4], &nDataRecords, 4);
    memcpy(&temp, &dest[4], 4);
    cout << "\nWROTE RECORDS: " << temp;
    memcpy(&dest[8], &firstFieldBlock, 4);
    memcpy(&temp, &dest[8], 4);
    cout << "\nWROTE FieldBLOCK: " << temp;
    memcpy(&dest[12], &indexBlockID, 4);
    memcpy(&temp, &dest[12], 4);
    cout << "\nWROTE INDEX: " << temp;
    memcpy(&dest[16], &firstDataBlock, 4);
    memcpy(&temp, &dest[16], 4);
    cout << "\nWROTE DATA: " << temp;
    memcpy(&dest[20], &activeDataBlock, 4);
    memcpy(&temp, &dest[20], 4);
    cout << "\nWROTE ACTIVE: " << temp;
    char n[50];
    strncpy(n, name.c_str(), strlen(name.c_str()));
    memcpy(&dest[24], tableName, 50);
    cout << "\nWROTE NAME: " << &dest[24];
}

void TableDefinition::fromByteArray(char *source, int buffSize)
{
    if(buffSize < 74)
        return;
    memcpy(&nFields, source, 4);
    memcpy(&nDataRecords, &source[4], 4);
    memcpy(&firstFieldBlock, &source[8], 4);
    memcpy(&indexBlockID, &source[12], 4);
    memcpy(&firstDataBlock, &source[16], 4);
    memcpy(&activeDataBlock, &source[20], 4);
    char n[50];
    cout << "\nPotential error about to occur here";
    memcpy(n, &source[24], 50);
    string sname = string(n);
    setName(sname);

    cout << "\nnFilds: "  << nFields;
    cout << "\nnDataRecords: "  << nDataRecords;
    cout << "\nfirstFieldBlock: "  << firstFieldBlock;
    cout << "\nindexBlockID: "  << indexBlockID;
    cout << "\nfirstDataBlock: "  << firstDataBlock;
    cout << "\nactiveDataBlock: "  << activeDataBlock;
    cout << "\nname: "  << sname;

}
