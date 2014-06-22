#include "masterblock.h"
#include <iostream>

using namespace std;

MasterBlock::MasterBlock()
{
    blockSize = DEFAULT_BLOCKSIZE;
    numberOfBlocks = 0;
    firstDefTableBlock = -1;
    activeDefTableBlock = -1;
    setName("invalid");
    numberOfDataBlocks = 0;
    numberOfFieldBlocks = 0;
    numberOfIndexBlocks = 0;
    numberOfTableBlocks = 0;
}

void MasterBlock::setName(string na)
{
    if(!na.empty())
        strncpy(databaseName, na.c_str(),50);
    else{
        string empty = "invalid";
        strncpy(databaseName, empty.c_str(), 50);
    }
}

void MasterBlock::incrementBlockCount()
{
    numberOfBlocks++;
}

void MasterBlock::setFirstDefTableBlock(int index)
{
    if( index >= 1)
        firstDefTableBlock = index;
}

void MasterBlock::setActiveDefTableBlock(int index)
{
    if(index >= 1)
        activeDefTableBlock = index;
}

void MasterBlock::setNumberOfDataBlocks(int index)
{
    if(index >= 1)
        numberOfDataBlocks = index;
}

void MasterBlock::setNumberOfFieldBlocks(int index)
{
    if(index >= 1)
        numberOfFieldBlocks = index;
}

void MasterBlock::setNumberOfIndexBlocks(int index)
{
    if(index >= 1)
        numberOfIndexBlocks = index;
}

void MasterBlock::setNumberOfTableBlocks(int index)
{
    if(index >= 1)
        numberOfTableBlocks = index;
}

int MasterBlock::toByteArray(char *dest, int buffSize)
{
    if(buffSize < 50)
        return -1;
    memcpy(dest, &numberOfBlocks, 4);
    memcpy(&dest[4], &blockSize, 4);
    memcpy(&dest[8],&firstDefTableBlock, 4);
    memcpy(&dest[12], &activeDefTableBlock, 4);
    memcpy(&dest[16], &numberOfTableBlocks, 4);
    memcpy(&dest[20], &numberOfFieldBlocks, 4);
    memcpy(&dest[24], &numberOfDataBlocks, 4);
    memcpy(&dest[28], &numberOfIndexBlocks, 4);
    memcpy(&dest[32], databaseName, 50);
    /*
    cout << "WRITTEN DATA:";
    cout << "\nNBlocks: " << numberOfBlocks;
    cout << "\nblockSize: " << blockSize;
    cout << "\nfirstDefTable: " << firstDefTableBlock;
    cout << "\nactiveDefTable: " << activeDefTableBlock;
    cout << "\nnumberOfTableBlocks: " << numberOfTableBlocks;
    cout << "\nnumberOfFieldBlocks: " << numberOfFieldBlocks;
    cout << "\nnumberOfDataBlocks: " << numberOfDataBlocks;
    cout << "\nnumberOfIndexBlocks: " << numberOfIndexBlocks;
    cout << "\ndatabaseName: " << databaseName;
    */
    return 0;
}

int MasterBlock::fromByteArray(char *source, int buffSize)
{
    if(buffSize < 50)
        return -1;
    memcpy(&numberOfBlocks, source, 4);
    memcpy(&blockSize, &source[4], 4);
    memcpy(&firstDefTableBlock, &source[8], 4);
    memcpy(&activeDefTableBlock, &source[12], 4);
    memcpy(&numberOfTableBlocks, &source[16], 4);
    memcpy(&numberOfFieldBlocks, &source[20], 4);
    memcpy(&numberOfDataBlocks, &source[24], 4);
    memcpy(&numberOfIndexBlocks, &source[28], 4);
    memcpy(databaseName, &source[32], 50);

    cout << "\nREAD DATA:";
    cout << "\nNBlocks: " << numberOfBlocks;
    cout << "\nblockSize: " << blockSize;
    cout << "\nfirstDefTable: " << firstDefTableBlock;
    cout << "\nactiveDefTable: " << activeDefTableBlock;
    cout << "\nnumberOfTableBlocks: " << numberOfTableBlocks;
    cout << "\nnumberOfFieldBlocks: " << numberOfFieldBlocks;
    cout << "\nnumberOfDataBlocks: " << numberOfDataBlocks;
    cout << "\nnumberOfIndexBlocks: " << numberOfIndexBlocks;
    cout << "\ndatabaseName: " << databaseName;

    return 0;
}
