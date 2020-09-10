#include"fcfs.h"
#include <vector>
#include <iostream>
#include <fstream>
void sortaTfcfs(int n, int tablica[][6]) // sortowanie procesow na podstawie czasu przybycia
{
    for(int i=0; i<n; i++)
    {
        for(int j=1; j<n-i; j++)
        {
            if(tablica[j-1][1]>tablica[j][1])
            {
                swap(tablica[j-1], tablica[j]);
            }
        }
    }
}

void findwTfcfs(int n, int tablica[][6])
{
    int clock=0;
    tablica[0][3]=0; // poczatkowy czas oczekiwania dla 1 procesu wynosi 0
    for (int i=1; i<n; i++)
    {
        clock=clock+tablica[i-1][2]; // zwiekszenie czasu zegara o czas wykonania procesu
        tablica[i][3]=clock-tablica[i][1]; // wpisanie czasu oczekiwania dla danego procesu
        if (tablica[i][3]<0) // jesli czas oczekiwania jest < 0 to wynosi 0, bo nie moze byc ujemny
            tablica[i][3]=0;
    }
}

void findtaTfcfs(int n, int tablica[][6]) // obliczanie czasu realizacji procesu
{
    for(int i=0; i<n; i++)
    {
        tablica[i][4]=tablica[i][2]+tablica[i][3];
    }
}

float wTsrfcfs(int n, int tablica[][6]) // liczenie sredniego czas oczekiwania
{
    int wT=0;
    for(int i=0; i<n; i++)
    {
        wT=wT+tablica[i][3];
    }
    return wT*1.0/n;
}

float taTsrfcfs(int n, int tablica[][6]) // liczenie sredniego czasu realizacji
{
    int taT=0;
    for(int i=0; i<n; i++)
    {
        taT=taT+tablica[i][4];
    }
    return taT*1.0/n;
}

void countcTfcfs(int n, int tablica[][6])
{
    for(int i=0; i<n; i++)
    {
        tablica[i][5]=tablica[i][4]+tablica[i][1];
    }
}

void fcfsShow(int n,int tablica[][6], int showTab, int saveTab)
{
    cout << "------------------------------------------------" << endl;
    cout << "Algorytm First Come First Served" << endl;
    cout << "------------------------------------------------" << endl;
    if (showTab==1)
    {
        cout << "PID" << "\t" << "aT" << "\t"<< "bT" << "\t" << "wT" << "\t" << "taT" << "\t" << "cT" << endl;
        cout << "------------------------------------------------" << endl;

        for (int i=0; i<n; i++)
        {
            cout << tablica[i][0] << "\t" << tablica[i][1] << "\t"<< tablica[i][2] << "\t" << tablica[i][3] << "\t"<< tablica[i][4] << "\t" << tablica[i][5] << endl;
        }
    }
        if (saveTab==1)
    {
        ofstream wyniki;
        wyniki.open("fcfs.txt");
        wyniki << "------------------------------------------------" << endl;
        wyniki << "Algorytm First Come First Served" << endl;
        wyniki << "------------------------------------------------" << endl;
        wyniki << "PID" << "\t" << "aT" << "\t"<< "bT" << "\t" << "wT" << "\t" << "taT" << "\t" << "cT" << endl;
        wyniki << "------------------------------------------------" << endl;

        for (int i=0; i<n; i++)
        {
            wyniki << tablica[i][0] << "\t" << tablica[i][1] << "\t"<< tablica[i][2] << "\t" << tablica[i][3] << "\t"<< tablica[i][4] << "\t" << tablica[i][5] << endl;
        }
                wyniki << "------------------------------------------------" << endl;
        wyniki << "Sredni czas czekania: " << wTsrfcfs(n, tablica) << endl;
        wyniki << "Sredni czas realizacji: " << taTsrfcfs(n, tablica) << endl;
        wyniki.close();
    }
    cout << "Sredni czas czekania: " << wTsrfcfs(n, tablica) << endl;
    cout << "Sredni czas realizacji: " << taTsrfcfs(n, tablica) << endl;
}

void fcfsEnd(int n,int tablica[][6], int showTab, int saveTab)
{
    sortaTfcfs(n, tablica);
    findwTfcfs(n, tablica);
    findtaTfcfs(n, tablica);
    countcTfcfs(n, tablica);
    fcfsShow(n, tablica, showTab, saveTab);

}