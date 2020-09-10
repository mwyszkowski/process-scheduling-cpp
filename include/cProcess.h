#ifndef CPROCESS_H
#define CPROCESS_H
using namespace std;

class cProcess
{
private:
    int PID; // process ID
    int aT; // arrival time
    int bT; // burst time
    static int numer;
public:
    cProcess(int minaTu, int aTu, int minbTu, int bTu); // konstruktor
    cProcess(int PIDu, int aTu, int bTu); // konstruktor
    cProcess(int aTu); // konstruktor
    cProcess(); // konstruktor
    int sPID(); // dostep do PID
    int saT(); // dostep do aT
    int sbT(); // dostep do bT
    void wyswietl(); // wyswietlanie danych poszczegolnego procesu
    virtual ~cProcess();

};

#endif // CPROCESS_H