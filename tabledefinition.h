#ifndef TABLEDEFINITION_H
#define TABLEDEFINITION_H
#include <string>

using namespace std;

class TableDefinition
{
public:
    TableDefinition();

    int getBlockID()const{return blockID;}
    int getTableID()const{return tableID;}
    string getName()const{return name;}
    int getNDataRecords()const{return nDataRecords;}
    int getFirstDataBlock()const{return firstDataBlock;}
    int getFirstFieldBlock()const{return firstFieldBlock;}
    int getIndexBlockID()const{return indexBlockID;}
    int getActiveDataBlock()const{return activeDataBlock;}

    void setBlockID(int);
    void setTableID(int);
    void setName(string);
    void incrementNDataRecords();
    void setNDataRecords(int);
    void setFirstDataBlock(int);
    void setFirstFieldBlock(int);
    void setIndexBlockID(int);
    void setActiveDataBlock(int);

private:
    int blockID;
    int tableID;
    string name;
    int nDataRecords;
    int nFields;
    int firstFieldBlock;
    int indexBlockID;
    int firstDataBlock;
    int activeDataBlock;
};

#endif // TABLEDEFINITION_H
