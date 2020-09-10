#include "sjfp.h"
#include <vector>
#include <iostream>
#include <fstream>
void findwTsjfp(int n, int tablica[][6])
{
    int tempbT[n]; // tymczasowa tablica czasu przybycia
    int tempcT[n];// tymczasowa tablica czasu wykonywania
    int clock=0; // zegar
    bool check=1;// zmienna sprawdzenia czy wykonac ponowna runde
    int temp, x;
    for (int i=0; i<n; i++) // przypisanie wartosci do tymczasowych tablic
    {
        tempbT[i]=tablica[i][2];
    }
    while (true)
    {
        check=1;
        for (int i=0; i<n; i++)
        {
            if (tempbT[i]>0)
            {
                if (tablica[i][1]<=clock) //sprawdzenie czy proces zostal zaladowany do kolejki
                {
                    temp=tempbT[i];
                    x=i;
                    for (int j=0; j<n; j++)
                    {
                        if (clock>=tablica[j][1] && temp>=tempbT[j] && tempbT[j]>0) // sprawdzenie czy istnieje proces o mniejszym czasie wykonywania
                        {
                            temp=tempbT[j];
                            x=j;
                        }
                    }
                    clock++;
                    tempbT[x]--;
                    swap(tablica[i], tablica[x]);
                    swap(tempbT[i], tempbT[x]);
                    if (tempbT[i]<=0)
                    {
                        tempbT[i]=0;
                        tablica[i][5]=clock;
                        tablica[i][4]=tablica[i][5]-tablica[i][1]; // obliczanie czasu trwania procesu
                        tablica[i][3]=tablica[i][4]-tablica[i][2]; // obliczenie czasu oczekiwania
                    }
                    else
                        i--;


                }
                else if (tablica[i][1]>clock) // jesli aT jest wieksze od czasu zegara to zegar zwieksza wartosc o 1, a iteracja zostaje powtorzona
                {
                    clock++;
                    i--;
                }
            }
        }
        for (int i=0; i<n; i++)
        {
            if (tempbT[i]>0)
                check=0;
        }
        if (check==1) // zakonczenie petli jesli wszystkie procesy zostaly zrobione
        {
            break;
        }
    }
}

float wTsrsjfp(int n, int tablica[][6]) // liczenie sredniego czasu oczekiwania
{
    int wT=0;
    for(int i=0; i<n; i++)
    {
        wT=wT+tablica[i][3];
    }
    return wT*1.0/n;
}

float taTsrsjfp(int n, int tablica[][6]) // liczenie sredniego czasu realizacji
{
    int taT=0;
    for(int i=0; i<n; i++)
    {
        taT=taT+tablica[i][4];
    }
    return taT*1.0/n;
}

void sjfpShow(int n,int tablica[][6], int showTab, int saveTab)
{
    cout << "------------------------------------------------" << endl;
    cout << "Algorytm Shortest Job First Wywlaszczajacy" << endl;
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
        wyniki.open("sjfp.txt");
        wyniki << "------------------------------------------------" << endl;
        wyniki << "Algorytm Shortest Job First Wywlaszczajacy" << endl;
        wyniki << "------------------------------------------------" << endl;
        wyniki << "PID" << "\t" << "aT" << "\t"<< "bT" << "\t" << "wT" << "\t" << "taT" << "\t" << "cT" << endl;
        wyniki << "------------------------------------------------" << endl;

        for (int i=0; i<n; i++)
        {
            wyniki << tablica[i][0] << "\t" << tablica[i][1] << "\t"<< tablica[i][2] << "\t" << tablica[i][3] << "\t"<< tablica[i][4] << "\t" << tablica[i][5] << endl;
        }
        wyniki << "------------------------------------------------" << endl;
        wyniki << "Sredni czas czekania: " << wTsrsjfp(n, tablica) << endl;
        wyniki << "Sredni czas realizacji: " << taTsrsjfp(n, tablica) << endl;
        wyniki.close();
    }
    cout << "Sredni czas czekania: " << wTsrsjfp(n, tablica) << endl;
    cout << "Sredni czas realizacji: " << taTsrsjfp(n, tablica) << endl;
}

void sjfpEnd(int n,int tablica[][6], int showTab, int saveTab)
{
    findwTsjfp(n, tablica);
    sjfpShow(n, tablica, showTab, saveTab);

}