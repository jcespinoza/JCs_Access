#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>
#include <cstdio>
#include "masterblock.h"
#include <iostream>
#include "fielddefinition.h"
#include "tabledefinition.h"
#include <list>


using namespace std;

class Controller
{
public:
    Controller();

    void updateMasterBlock(string filename, MasterBlock&);
    void readMasterBlock(string filename, MasterBlock&);
    void createNewFile(string filename, MasterBlock &master, int blockSize = 4096);
    list<TableDefinition> readTableList(string filename, MasterBlock&);
    list<FieldDefinition> readFieldList(string filename, MasterBlock&, TableDefinition &);
    int readTableDefinition(string filename, MasterBlock&, TableDefinition&table, string tName);
    void readDataBlock(string filename, MasterBlock& master, int blockID, char *dest);
    bool doesTableExist(string filename, string tableName, MasterBlock& master);
    int writeTableDefinition(string filename, MasterBlock& master, TableDefinition& table);
    void writeFieldsDefinition(string filename, MasterBlock &, list<FieldDefinition>, TableDefinition &);
    void writeRecords(string filename, MasterBlock&, TableDefinition&, list<FieldDefinition>, list<list<string> >&, int);
    void loadRecords(string filename,MasterBlock&, TableDefinition&, list<FieldDefinition>, list<list<string> >&, int);
    void updateCurrentTableBlock(string filename, MasterBlock&, TableDefinition&);

private:
    MasterBlock master;
};


#endif // CONTROLLER_H
