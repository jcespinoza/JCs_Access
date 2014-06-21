#ifndef MASTERBLOCK_H
#define MASTERBLOCK_H
#include <string>
#include <iostream>
using namespace std;

class MasterBlock
{
public:
    static int const DEFAULT_BLOCKSIZE = 4096;

    MasterBlock();

    void setName(string);
    void incrementBlockCount();
    void changeFirstDefTableBlock(int);
    void changeActiveDefTableBlock(int);
    int toByteArray(char*dest, int buffSize);
    int fromByteArray(char* source, int buffSize);

    int getNumberOfBlocks() const {return numberOfBlocks;}
    int getBlockSize() const{return blockSize;}
    int getFirstDefTableBlock() const {return firstDefTableBlock;}
    int getActiveDefTableBlock() const{return activeDefTableBlock;}
    string getDataBaseName() const {cout << "\n " << databaseName << " \n"; return string(databaseName);}

private:
    int numberOfBlocks;
    int blockSize;
    int firstDefTableBlock;
    int activeDefTableBlock;
    char databaseName[50];
};

#endif // MASTERBLOCK_H
