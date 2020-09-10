#include "cProcess.h"
#include <iostream>
#include <cstdlib>
cProcess::cProcess(int minaTu, int aTu, int minbTu, int bTu)
{
    PID=numer;
    aT=(rand()%(aTu-minaTu+1)+minaTu);
    bT=(rand()%(bTu-minbTu+1)+minbTu);
    numer++;
}

cProcess::cProcess(int PIDu, int aTu, int bTu)
{
    PID=PIDu;
    aT=aTu;
    bT=bTu;
    numer++;
}

cProcess::cProcess(int aTu)
{
    PID=numer;
    aT=aTu;
    bT=(rand()%10)+1;
    numer++;
}



cProcess::cProcess()
{
    PID=numer;
    aT=(rand()%(11));
    bT=(rand()%(10)+1);
    numer++;
}

void cProcess::wyswietl()
{
    cout << "PID: " << PID << endl;
    cout << "aT: " << aT << endl;
    cout << "bT: " << bT << endl;
}

int cProcess::sPID()
{
    return PID;
}

int cProcess::saT()
{
    return aT;
}

int cProcess::sbT()
{
    return bT;
}

cProcess::~cProcess()
{
    numer--;
}