#include "controller.h"
#include <QDebug>

Controller::Controller()
{
}

void Controller::wholeFileToDisk(string, int, MasterBlock &)
{

}

void Controller::updateMasterBlock(string, MasterBlock &)
{

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

void Controller::readTableList(string filename, MasterBlock &master)
{
    int currentIndex = master.getFirstDefTableBlock();
    if(currentIndex == -1)
        return;

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
    if(tableIndex == -1) return false;
    bool found = false;
    FILE* dbFile = fopen(filename.c_str(),"rb");
    while(tableIndex != -1){
        fseek(dbFile,0,SEEK_SET);
        fseek(dbFile,tableIndex*master.getBlockSize(),SEEK_SET);
        fread(block, 1, master.getBlockSize(), dbFile);
        int numberOfTables = 0;
        memcpy(&numberOfTables, block, 4);
        memcpy(&tableIndex, &block[4], 4);
        //next 4 bytes are the size of the tables it would be 8
        //TableDefinitionStrcture is
        //int int int int int int int char
        //that give 7*4=28bytes to skip until the name. That would be 8+28=36
        //so iteration will go block[36+74*i]
        char test[50];
        for(int i  = 0; i < numberOfTables; i++){
            memcpy(test, &block[36+74*i], 50);
            string tName(test);
            cout << "\nComparing " << tName << " with " << tableName;
            if(tName == tableName){
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
}

void Controller::writeTableDefinition(string filename, MasterBlock &master, TableDefinition &table)
{
    char* block = new char[master.getBlockSize()];
    int indexActiveTableBlock = master.getActiveDefTableBlock();
    FILE* dbFile = fopen(filename.c_str(), "wb+");
    if(indexActiveTableBlock == -1){//check for inexistence first
        cout << "\nThere's no tableDefBlock yet";

    }else{//else it exists, so let's see if there's room for one

    }
    //check if there is already one active
    //if there is, check if there is room
    //if there is room, calculate the relative index
    //if there isnt create one
    delete[] block;
}
