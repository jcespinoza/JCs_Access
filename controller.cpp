#include "controller.h"
#include <QDebug>
#include <iostream>
using namespace std;

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
    cout << "\ntableIndex is " << tableIndex;
    qDebug() << "tableIndex is " << tableIndex;
    if(tableIndex == -1) return false;
    bool found = false;
    FILE* dbFile = fopen(filename.c_str(),"rb");
    int count = 1;
    while(tableIndex != -1){
        if(count >= 2)break;
        count++;
        fseek(dbFile,0,SEEK_SET);
        cout << "\nCurrent position in file: " << ftell(dbFile);
        cout << "\nJump will be " << tableIndex*master.getBlockSize();
        fseek(dbFile,tableIndex*master.getBlockSize(),SEEK_SET);
        cout << "\nCurrent position in file: " << ftell(dbFile);
        fread(block, 1, master.getBlockSize(), dbFile);
        cout << "\nCurrent position in file: " << ftell(dbFile);
        cout << "\nBLock: " << block;
        int numberOfTables = 0;
        memcpy(&numberOfTables, block, 4);
        qDebug() << "Number of Tables is: " << numberOfTables;
        memcpy(&tableIndex, &block[4], 4);
        qDebug() << "tableIndex is: " << tableIndex;
        //next 4 bytes are the size of the tables it would be 8
        int msd = 0;
        memcpy(&msd, &block[8],4);
        cout << "\nTableSize: " << msd;
        memcpy(&msd, &block[12],4);
        cout << "\nfields: " << msd;
        memcpy(&msd, &block[16],4);
        cout << "\nrecords: " << msd;
        memcpy(&msd, &block[20],4);
        cout << "\nfieldsBlock: " << msd;
        memcpy(&msd, &block[24],4);
        cout << "\nindex: " << msd;
        memcpy(&msd, &block[28],4);
        cout << "\ndatablock: " << msd;
        memcpy(&msd, &block[32],4);
        cout << "\nactiveBlock: " << msd;
        char algo[50];
        memcpy(algo, &block[36],50);
        cout << "\nName: " << algo;
        //TableDefinitionStrcture is
        //int int int int int int int char
        //that give 7*4=28bytes to skip until the name. That would be 12+28=40
        //so iteration will go block[36+74*i]
        char test[50];
        for(int i  = 0; i < numberOfTables; i++){
            memcpy(test, &block[36+74*i], 50);
            string tName(test);
            cout << "\nComparing " << test << " with " << tableName;
            qDebug() << "Comparing " << QString(tName.c_str()) << " with " << QString(tableName.c_str());
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
    int numberOfBlocks = master.getNumberOfBlocks()+1;
    bool updateNeeded = false;
    FILE* dbFile = fopen(filename.c_str(), "r+b");
    if(indexActiveTableBlock == -1){//check for inexistence first
        cout << "\nThere's no tableDefBlock yet";
        master.setFirstDefTableBlock(numberOfBlocks);
        master.setActiveDefTableBlock(numberOfBlocks);
        master.setNumberOfTableBlocks(1); //it's the first one
        master.incrementBlockCount();
        int nTables = 1;
        int nextOne = -1;
        int tSize = table.getSize();
        cout << "\nReported size: " << tSize;
        memcpy(block, &nTables, 4);
        memcpy(&block[4], &nextOne, 4);
        memcpy(&block[8], &tSize, 4);
        char *tab = new char[tSize];
        table.toByteArray(tab, tSize);
        memcpy(&block[12], tab ,tSize);
        cout << "\n block: " <<  block;
        fseek(dbFile, master.getBlockSize()*(numberOfBlocks),SEEK_SET);
        cout << "\nCurrent position: " << ftell(dbFile);
        fwrite(block, 1, master.getBlockSize(), dbFile);
        updateNeeded = true;
    }else{//else it exists, so let's see if there's room for one

    }
    //check if there is already one active
    //if there is, check if there is room
    //if there is room, calculate the relative index
    //if there isnt create one
    fclose(dbFile);
    delete[] block;

    if(updateNeeded)
        updateMasterBlock(filename, master);
}
