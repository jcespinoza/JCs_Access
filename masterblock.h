#ifndef MASTERBLOCK_H
#define MASTERBLOCK_H
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

class MasterBlock
{
public:
    static int const DEFAULT_BLOCKSIZE = 4096;

    MasterBlock();

    void setName(string);
    void incrementBlockCount();
    void setFirstDefTableBlock(int);
    void setActiveDefTableBlock(int);
    void setNumberOfDataBlocks(int);
    void setNumberOfFieldBlocks(int);
    void setNumberOfIndexBlocks(int);
    void setNumberOfTableBlocks(int);

    int toByteArray(char*dest, int buffSize);
    int fromByteArray(char* source, int buffSize);

    int getNumberOfBlocks() const {return numberOfBlocks;}
    int getBlockSize() const{return blockSize;}
    int getFirstDefTableBlock() const {return firstDefTableBlock;}
    int getActiveDefTableBlock() const{return activeDefTableBlock;}
    int getNumberOfDataBlocks() const{return numberOfDataBlocks;}
    int getNumberOfTableBlocks() const{return numberOfTableBlocks;}
    int getNumberOfFieldBlocks()const{return numberOfFieldBlocks;}
    int getNumberOfIndexBlocks()const{return numberOfIndexBlocks;}
    string getDataBaseName() const { return string(databaseName);}

private:
    int numberOfBlocks;
    int numberOfTableBlocks;
    int numberOfFieldBlocks;
    int numberOfDataBlocks;
    int numberOfIndexBlocks;
    int blockSize;
    int firstDefTableBlock;
    int activeDefTableBlock;
    char databaseName[50];
};

#endif // MASTERBLOCK_H
