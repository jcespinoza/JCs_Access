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

void MasterBlock::changeFirstDefTableBlock(int index)
{
    if( index >= 1)
        firstDefTableBlock = index;
}

void MasterBlock::changeActiveDefTableBlock(int index)
{
    if(index >= 1)
        activeDefTableBlock = index;
}

int MasterBlock::toByteArray(char *dest, int buffSize)
{
    if(buffSize < 50)
        return -1;
    memcpy(dest, &numberOfBlocks, 4);
    memcpy(&dest[4], &blockSize, 4);
    memcpy(&dest[8],&firstDefTableBlock, 4);
    memcpy(&dest[12], &activeDefTableBlock, 4);
    memcpy(&dest[16], databaseName, 50);
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
    memcpy(databaseName, &source[16], 50);
    return 0;
}
