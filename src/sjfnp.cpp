#include "sjfnp.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
void sortaTsjfnp(int n, int tablica[][6]) // sertowanie w celu znalezienia najnizszej wartosci aT i bT w przypadku gdy wiecej niz 1 proces ma najnizsza wartosc aT
{
    int x=1;
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
    for (int i=1; i<n; i++)
    {
        if (tablica[0][1]==tablica[i][1])
            x++;
    }
    if (x>1)
    {
        for(int i=0; i<x; i++)
        {
            for(int j=1; j<n-i; j++)
            {
                if(tablica[j-1][2]>tablica[j][2])
                {
                    swap(tablica[j-1], tablica[j]);
                }
            }
        }
    }
}

void findwTsjfnp(int n, int tablica[][6])
{
    int clock=0;
    int temp, x;
    for (int i=0; i<n; i++)
    {
        temp=tablica[i][2];
        if (tablica[i][1]<=clock) // sprawdzenie czy proces jest zaladowany
        {
            for (int j=i; j<n; j++)
            {
                if (clock>=tablica[j][1] && temp>=tablica[j][2]) // sprawdzenie czy istnieje proces o mniejszym czasie wykonywania
                {
                    temp=tablica[j][2];
                    x=j;
                }
            }
            swap(tablica[i], tablica[x]);

            tablica[i][5]=clock+tablica[i][2]; // obliczenie calkowitego czasu wykonywania procesu
            clock=clock+tablica[i][2]; // zwiekszenie zegara o czas wykonywania procesu
            tablica[i][3]=clock-tablica[i][2]-tablica[i][1]; // obliczenie czasu oczekiwania
            tablica[i][4]=tablica[i][5]-tablica[i][1]; // obliczanie czasu trwania procesu
        }
        else
        {
            clock++;
            i--;
        }
    }
}

float wTsrsjfnp(int n, int tablica[][6]) // liczenie sredniego czasu oczekiwania
{
    int wT=0;
    for(int i=0; i<n; i++)
    {
        wT=wT+tablica[i][3];
    }
    return wT*1.0/n;
}

float taTsrsjfnp(int n, int tablica[][6]) // liczenie sredniego czasu realizacji
{
    int taT=0;
    for(int i=0; i<n; i++)
    {
        taT=taT+tablica[i][4];
    }
    return taT*1.0/n;
}

void sjfnpShow(int n,int tablica[][6], int showTab, int saveTab)
{
    cout << "------------------------------------------------" << endl;
    cout << "Algorytm Shortest Job First Nie Wywlaszczajacy" << endl;
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
        wyniki.open("sjfnp.txt");
        wyniki << "------------------------------------------------" << endl;
        wyniki << "Algorytm Shortest Job First Nie Wywlaszczajacy" << endl;
        wyniki << "------------------------------------------------" << endl;
        wyniki << "PID" << "\t" << "aT" << "\t"<< "bT" << "\t" << "wT" << "\t" << "taT" << "\t" << "cT" << endl;
        wyniki << "------------------------------------------------" << endl;

        for (int i=0; i<n; i++)
        {
            wyniki << tablica[i][0] << "\t" << tablica[i][1] << "\t"<< tablica[i][2] << "\t" << tablica[i][3] << "\t"<< tablica[i][4] << "\t" << tablica[i][5] << endl;
        }
        wyniki << "------------------------------------------------" << endl;
        wyniki << "Sredni czas czekania: " << wTsrsjfnp(n, tablica) << endl;
        wyniki << "Sredni czas realizacji: " << taTsrsjfnp(n, tablica) << endl;
        wyniki.close();
    }
    cout << "Sredni czas czekania: " << wTsrsjfnp(n, tablica) << endl;
    cout << "Sredni czas realizacji: " << taTsrsjfnp(n, tablica) << endl;
}

void sjfnpEnd(int n,int tablica[][6], int showTab, int saveTab)
{
    sortaTsjfnp(n, tablica);
    findwTsjfnp(n, tablica);
    sjfnpShow(n, tablica, showTab, saveTab);

}