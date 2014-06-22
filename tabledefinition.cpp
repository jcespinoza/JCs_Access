#include "tabledefinition.h"

TableDefinition::TableDefinition()
{
    blockID = 1;
    tableID = 0;
    name = "";
    nDataRecords = 0;
    nFields = 0;
    firstDataBlock = -1;
    firstFieldBlock = -1;
    indexBlockID = -1;
}

void TableDefinition::setBlockID(int i )
{
    blockID = i;
}

void TableDefinition::setTableID(int i)
{
    tableID = i;
}

void TableDefinition::setName(string i)
{
    name = i;
}

void TableDefinition::incrementNDataRecords()
{
    nDataRecords += 1;
}

void TableDefinition::setNDataRecords(int i)
{
    nDataRecords = i;
}

void TableDefinition::setFirstDataBlock(int i)
{
    firstDataBlock = i;
}

void TableDefinition::setFirstFieldBlock(int i)
{
    firstFieldBlock = i;
}

void TableDefinition::setIndexBlockID(int i)
{
    indexBlockID = i;
}

void TableDefinition::setActiveDataBlock(int i)
{
    activeDataBlock = i;
}
