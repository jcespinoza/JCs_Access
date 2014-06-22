#include "controller.h"
#include <QDebug>
#include <iostream>
//using namespace std;

Controller::Controller()
{
}

void Controller::wholeFileToDisk(string, int, MasterBlock &)
{

}

void Controller::updateMasterBlock(string filename, MasterBlock &master)
{
    FILE* dbFile = fopen(filename.c_str(),"r+b");
    char* block = new char[master.getBlockSize()];
    master.toByteArray(block, master.getBlockSize());
    int res = fwrite(block, 1, master.DEFAULT_BLOCKSIZE, dbFile);
    fclose(dbFile);
    delete[] block;
}

void Controller::readMasterBlock(string filename, MasterBlock &master)
{
    FILE* dbFile = fopen(filename.c_str(),"rb");
    char* block = new char[MasterBlock::DEFAULT_BLOCKSIZE];
    int res = fread(block, 1, MasterBlock::DEFAULT_BLOCKSIZE, dbFile);
    master.fromByteArray(block, MasterBlock::DEFAULT_BLOCKSIZE);
    fclose(dbFile);
    delete[] block;
}

void Controller::createNewFile(string filename, MasterBlock& master, int blockSize)
{
    FILE* dbFile = fopen(filename.c_str(),"wb");
    char* block = new char[blockSize];
    master.toByteArray(block, blockSize);
    int res = fwrite(block, 1, master.DEFAULT_BLOCKSIZE, dbFile);
    fclose(dbFile);
    delete[] block;
}

list<TableDefinition> Controller::readTableList(string filename, MasterBlock &master)
{
    list<TableDefinition> tables;
    int currentIndex = master.getFirstDefTableBlock();

    FILE* dbFile = fopen(filename.c_str(), "rb");
    char* block = new char[master.getBlockSize()];
    char* tblock = new char[TableDefinition::getSize()];
    TableDefinition tempT;
    while(currentIndex != -1){
        fseek(dbFile, currentIndex*master.getBlockSize(), SEEK_SET);
        fread(block, 1, master.getBlockSize(), dbFile);
        int ntablas = 0;
        memcpy(&ntablas, block, 4);
        memcpy(&currentIndex, &block[4], 4);
        for(int i = 0; i < ntablas; i++){
            tempT.fromByteArray(&block[12+i*tempT.getSize()], tempT.getSize());
            qDebug() << "TAble Name: " << QString::fromStdString(tempT.getName());
            TableDefinition newOne = tempT;
            tables.push_back(newOne);
        }
    }
    return tables;
}

void Controller::readFieldList(string filename, MasterBlock &, TableDefinition&)
{

}

void Controller::readDataBlock(string filename, MasterBlock &master, int blockID, char* dest)
{
    FILE* dbFile = fopen(filename.c_str(), "rb");
    fread(dest, 1, master.getBlockSize(), dbFile);
    fclose(dbFile);
}

bool Controller::doesTableExist(string filename, string tableName, MasterBlock &master)
{
    char* block = new char[master.getBlockSize()];
    int tableIndex = master.getFirstDefTableBlock();
    cout << "\ntableIndex is " << tableIndex;
    qDebug() << "tableIndex is " << tableIndex;
    if(tableIndex == -1) return false;
    bool found = false;
    FILE* dbFile = fopen(filename.c_str(),"rb");
    while(tableIndex != -1){
        fseek(dbFile,0,SEEK_SET);
        fseek(dbFile,tableIndex*master.getBlockSize(),SEEK_SET);
        fread(block, 1, master.getBlockSize(), dbFile);
        int numberOfTables = 0;
        memcpy(&numberOfTables, block, 4);
        qDebug() << "Number of Tables is: " << numberOfTables;
        memcpy(&tableIndex, &block[4], 4);
        qDebug() << "tableIndex is: " << tableIndex;
        //next 4 bytes are the size of the tables it would be 8
        //TableDefinitionStrcture is
        //int int int int int int char
        //that give 7*4=28bytes to skip until the name. That would be 8+28=36
        //so iteration will go block[36+74*i]
        char test[50];
        for(int i  = 0; i < numberOfTables; i++){
            memcpy(test, &block[36+74*i], 50);
            int len1 = strlen(test);
            int len2 = strlen(tableName.c_str());
            int less = (len1 < len2)?len1:len2;
            if(strncmp(test, tableName.c_str(),less) == 0){
                found = true;
                break;
            }
            if(found) break;
        }
    }
    //read the given block index
    //read the nextIndex and store
    //read the number of tables and store it
    //read the corresponding 50 bytes in a cycle
    fclose(dbFile);
    delete[] block;
    qDebug() << "Was the table already stored? " << found;
    return found;
}

int Controller::writeTableDefinition(string filename, MasterBlock &master, TableDefinition &table)
{
    char* block = new char[master.getBlockSize()];
    int indexActiveTableBlock = master.getActiveDefTableBlock();
    int numberOfBlocks = master.getNumberOfBlocks()+1;
    bool updateNeeded = false;
    FILE* dbFile = fopen(filename.c_str(), "r+b");
    if(indexActiveTableBlock == -1){//check for inexistence first
        table.setBlockID(numberOfBlocks);
        table.setTableID(0);
        master.setFirstDefTableBlock(numberOfBlocks);
        master.setActiveDefTableBlock(numberOfBlocks);
        master.setNumberOfTableBlocks(1); //it's the first one
        master.incrementBlockCount();
        int nTables = 1;
        int nextOne = -1;
        int tSize = table.getSize();

        memcpy(block, &nTables, 4);
        memcpy(&block[4], &nextOne, 4);
        memcpy(&block[8], &tSize, 4);
        char *tab = new char[tSize];
        table.toByteArray(tab, tSize);
        memcpy(&block[12], tab ,tSize);
        delete[] tab;

        fseek(dbFile, master.getBlockSize()*(numberOfBlocks),SEEK_SET);

        fwrite(block, 1, master.getBlockSize(), dbFile);
        updateNeeded = true;
    }else{//else it exists, so let's see if there's room for one
         char* tBlock = new char[master.getBlockSize()];
         fseek(dbFile, master.getActiveDefTableBlock()*master.getBlockSize(), SEEK_SET);
         fread(tBlock, 1, master.getBlockSize(), dbFile);

         int nTables = 0;
         memcpy(&nTables, tBlock, 4);

         //goven the number of tables, check if there is room
         //compare with the max
         int header = 12;
         int maxTables = (master.getBlockSize()-header)/TableDefinition::getSize();
         if(nTables <= maxTables){
             table.setTableID(nTables);
             table.setBlockID(master.getActiveDefTableBlock());
             int nextOne = 0;
             memcpy(&nextOne, &tBlock[4], 4);
             int tSize = 0;
             memcpy(&tSize, &tBlock[8], 4);
             char* tab = new char[tSize];

             table.toByteArray(tab, tSize);


             fseek(dbFile, master.getActiveDefTableBlock()*master.getBlockSize()+header+nTables*tSize, SEEK_SET);
             qDebug() << "\nPosition in file " << ftell(dbFile);
             fwrite(tab, 1, tSize, dbFile);
             nTables++;
             fseek(dbFile, master.getActiveDefTableBlock()*master.getBlockSize(), SEEK_SET);
             qDebug() << "\nPosition in file2 " << ftell(dbFile);
             fwrite(&nTables, 1, 4, dbFile);
         }else{
             cout << "\nCANT ADD MORE TABLES FROM NOW. PLEASE CONTACT THE DEVELOPER\n"
                     << "ERROR: MAXIMUM NUMBER OF TABLES EXCEDED. ABORTING";
             return 2;
         }
    }
    //check if there is already one active
    //if there is, check if there is room
    //if there is room, calculate the relative index
    //if there isnt create one
    fclose(dbFile);
    delete[] block;

    if(updateNeeded)
        updateMasterBlock(filename, master);
    return 0;
}

void Controller::writeFieldsDefinition(string filename, MasterBlock &master, list<FieldDefinition> list, TableDefinition& table)
{
    //check masterblock
    //store the nextavailable space using the blockCount
    char* block = new char[master.getBlockSize()];

    int numberOfBlocks = master.getNumberOfBlocks()+1;
    qDebug() << "There currrently " << numberOfBlocks-1 << "blocks right withoung counting master";
    bool updateNeeded = false;

    int nFields = list.size();
    table.setNFields(nFields);
    //If there was a table with too much field definitios (66) there would be the need to make another a block
    int nextField = -1;
    int fSize = FieldDefinition::getSize();
    memcpy(block, &nFields, 4);
    memcpy(&block[4], &nextField, 4);
    memcpy(&block[8], &fSize, 4);
    int i = 0;
    std::list< FieldDefinition > ::iterator it;
    for(it = list.begin(); it != list.end(); ++it, i++){
        char *temp = new char[fSize];
        (*it).toByteArray(temp, fSize);
        memcpy(&block[12+i*fSize], temp, fSize);
        for(int i = 0; i < fSize; i++){
            qDebug() << temp[i];
        }
    }

    FILE* dbFile = fopen(filename.c_str(), "r+b");
    fseek(dbFile, numberOfBlocks*master.getBlockSize(), SEEK_SET);
    fwrite(block, 1, master.getBlockSize(), dbFile);

    master.incrementBlockCount();
    master.setNumberOfFieldBlocks(master.getNumberOfFieldBlocks()+1);
    updateNeeded = true;
    if(table.getFirstFieldBlock() == -1){
        table.setFirstFieldBlock(numberOfBlocks);
        qDebug() << "Updated firstFieldBlock to" << table.getFirstFieldBlock();
    }

    fclose(dbFile);
    delete[] block;

    if(updateNeeded)
        updateMasterBlock(filename, master);
}

void Controller::updateCurrentTableBlock(string filename, MasterBlock &master, TableDefinition &table)
{
    char *block = new char[TableDefinition::getSize()];
    table.toByteArray(block, TableDefinition::getSize());
    int blockID = table.getBlockID();
    int tableID = table.getTableID();
    FILE* dbFile = fopen(filename.c_str(), "r+b");
    int headerSize = 12;
    fseek(dbFile, blockID*master.getBlockSize()+ headerSize + tableID*TableDefinition::getSize(), SEEK_SET);
    cout << "\nCurrent Position in file " << ftell(dbFile);
    fwrite(block, 1, TableDefinition::getSize(), dbFile);
    fclose(dbFile);
    delete[] block;
}
