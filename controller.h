#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>
#include <cstdio>
#include "masterblock.h"
#include <iostream>

using namespace std;

class Controller
{
public:
    Controller();

    void wholeFileToDisk(string filename, int position, MasterBlock&);
    void updateMasterBlock(string filename, MasterBlock&);
    void readMasterBlock(string filename, MasterBlock&);
    void createNewFile(string filename, string name, int blockSize = 4096);
    void readTableList(string filename, MasterBlock&);
    void read

private:
    MasterBlock master;
};


#endif // CONTROLLER_H
