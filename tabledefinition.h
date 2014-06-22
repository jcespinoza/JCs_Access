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
    string getName()const;
    int getNDataRecords()const{return nDataRecords;}
    int getNFields() const{return nFields;}
    int getFirstDataBlock()const{return firstDataBlock;}
    int getFirstFieldBlock()const{return firstFieldBlock;}
    int getIndexBlockID()const{return indexBlockID;}
    int getActiveDataBlock()const{return activeDataBlock;}
    string getTableName() const;

    void setBlockID(int);
    void setTableID(int);
    void setName(string);
    void incrementNDataRecords();
    void setNDataRecords(int);
    void setFirstDataBlock(int);
    void setFirstFieldBlock(int);
    void setIndexBlockID(int);
    void setActiveDataBlock(int);
    void setNFields(int);
    static int getSize();

    void toByteArray(char*dest, int buffSize);
    void fromByteArray(char* source, int buffSize);

private:
    int blockID;
    int tableID;
    string name;
    char tableName[50];
    int nDataRecords;
    int nFields;
    int firstFieldBlock;
    int indexBlockID;
    int firstDataBlock;
    int activeDataBlock;
};

#endif // TABLEDEFINITION_H
