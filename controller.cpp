#include "controller.h"
#include <QDebug>

Controller::Controller()
{
}

void Controller::wholeFileToDisk(string filename, int position, MasterBlock &)
{

}

void Controller::updateMasterBlock(string filename, MasterBlock &)
{

}

void Controller::readMasterBlock(string filename, MasterBlock &master)
{
    FILE* dbFile = fopen(filename.c_str(),"rb");
    char* block = new char[MasterBlock::DEFAULT_BLOCKSIZE];
    int res = fread(block, 1, MasterBlock::DEFAULT_BLOCKSIZE, dbFile);
    master.fromByteArray(block, MasterBlock::DEFAULT_BLOCKSIZE);

    fclose(dbFile);
}

void Controller::createNewFile(string filename, string name, int blockSize)
{
    FILE* dbFile = fopen(filename.c_str(),"wb");
    char* block = new char[blockSize];
    MasterBlock master;
    master.setName(name);
    master.toByteArray(block, blockSize);
    int res = fwrite(block, 1, master.DEFAULT_BLOCKSIZE, dbFile);
    //qDebug() << res;
    fclose(dbFile);
}
