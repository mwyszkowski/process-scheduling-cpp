#include "rr.hpp"
#include <vector>
#include <iostream>
#include <fstream>
void findwTrr(int n, int tablica[][6], int q)
{
    int tempaT[n]; // tymczasowa tablica czasu przybycia
    int tempbT[n];// tymczasowa tablica czasu wykonywania
    int clock=0; // zegar
    bool check=1;// zmienna sprawdzenia czy wykonac ponowna runde
    for (int i=0; i<n; i++) // przypisanie wartosci do tymczasowych tablic
    {
        tempaT[i]=tablica[i][1];
        tempbT[i]=tablica[i][2];
    }
    while (true)
    {
        check=1;
        for (int i=0; i<n; i++)
        {
            if (tempaT[i]<=clock) //sprawdzenie czy proces zostal zaladowany do kolejki
            {
                if (tempaT[i]<=q) //sprawdzenie czy proces zostal zaladowany przed czasem kwantu
                {
                    if (tempbT[i]>0) // sprawdzenie czy proces musi sie jeszcze wykonac
                    {
                        check=0; // wymagane do ponownej rundy
                        if (tempbT[i]>q) // jesli proces nie wykona sie w przydzielonym czasie to zostaje ponownie dodany do kolejki
                        {
                            clock=clock+q; // zwiekszenie zegara o czas poswiecony procesowi
                            tempbT[i]=tempbT[i]-q; // zmiejszenie pozostalego czasu wymaganego do wykonania procesu
                            tempaT[i]=tempaT[i]+q; // zwiekszenie czasu przybycia, bo zakonczyl sie czas przydzielony procesowi
                        }
                        else // gdy proces sie wykona
                        {
                            clock=clock+tempbT[i]; // zwiekszenie zegara o pozostaly czas wykonywania procesu
                            tablica[i][5]=clock-tablica[i][1]; // obliczenie calkowitego czasu wykonywania procesu
                            tablica[i][3]=clock-tablica[i][2]-tablica[i][1]; // obliczenie czasu oczekiwania
                            tempbT[i]=0; // zerowanie tymczasowej wartosci bT by przy kolejnej rundzie nie wykonywac ponownie obliczen
                        }
                    }
                }
                else if (tempaT[i]>q) // jesli proces ma dluzszy czas przybycia niz czas kwantu to sprawdzenie czy jest proces o krotszym czasie przybycia
                {
                    for (int j=0; j<n; j++) //ponowne uruchomienie petli sprawdzajacej czasy przybycia
                    {
                        if (tempaT[j]<tempaT[i]) // jesli proces przybedzie szybciej od procesu poczatkowego to:
                        {
                            if (tempbT[j]>0) // jesli proces ma sie jeszcze wykonac
                            {
                                check=0; // wymagane do ponownej rundy
                                if (tempbT[j]>q) // jesli proces nie wykona sie w przydzielonym czasie to zostaje ponownie dodany do kolejki
                                {
                                    clock=clock+q;
                                    tempbT[j]=tempbT[j]-q;
                                    tempaT[j]=tempaT[j]+q;
                                }
                                else // gdy proces sie wykona
                                {
                                    clock=clock+tempbT[j];
                                    tablica[j][5]=clock-tablica[j][1];
                                    tablica[j][3]=clock-tablica[j][2]-tablica[j][1];
                                    tempbT[j]=0;
                                }
                            }
                        }
                    }
                    if (tempbT[i]>0) // jesli proces ma sie jeszcze wykonac
                    {
                        check=0; // wymagane do ponownej rundy
                        if (tempbT[i]>q) // jesli proces nie wykona sie w przydzielonym czasie to zostaje ponownie dodany do kolejki
                        {
                            clock=clock+q;
                            tempbT[i]=tempbT[i]-q;
                            tempaT[i]=tempaT[i]+q;
                        }
                        else // gdy proces sie wykona
                        {
                            clock=clock+tempbT[i];
                            tablica[i][5]=clock-tablica[i][1];
                            tablica[i][3]=clock-tablica[i][2]-tablica[i][1];
                            tempbT[i]=0;
                        }
                    }
                }
            }
            else if (tempaT[i]>clock) // jesli aT jest wieksze od czasu zegara to zegar zwieksza wartosc o 1, a iteracja zostaje powtorzona
            {
                clock++;
                i--;
            }
        }
        if (check==1) // zakonczenie petli jesli wszystkie procesy zostaly zrobione
        {
            break;
        }
    }
    for(int i=0; i<n; i++) // sortowanie w celu wyswietlenia procesow w kolejnosci ukonczenia
    {
        for(int j=1; j<n-i; j++)
        {
            if(tablica[j-1][5]>tablica[j][5])
            {
                swap(tablica[j-1], tablica[j]);
            }
        }
    }

}

void findtaTrr(int n, int tablica[][6]) // obliczanie czasu realizacji procesu
{
    for(int i=0; i<n; i++)
    {
        tablica[i][4]=tablica[i][2]+tablica[i][3];
    }
}

float wTsrrr(int n, int tablica[][6]) // liczenie sredniego czasu oczekiwania
{
    int wT=0;
    for(int i=0; i<n; i++)
    {
        wT=wT+tablica[i][3];
    }
    return wT*1.0/n;
}

float taTsrrr(int n, int tablica[][6]) // liczenie sredniego czasu realizacji
{
    int taT=0;
    for(int i=0; i<n; i++)
    {
        taT=taT+tablica[i][4];
    }
    return taT*1.0/n;
}

void rrShow(int n,int tablica[][6], int showTab, int saveTab) // wyswietlanie i wpisywanie do pliku
{
    cout << "------------------------------------------------" << endl;
    cout << "Algorytm Round Robin" << endl;
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
        wyniki.open("roundrobin.txt");
        wyniki << "------------------------------------------------" << endl;
        wyniki << "Algorytm Round Robin" << endl;
        wyniki << "------------------------------------------------" << endl;
        wyniki << "PID" << "\t" << "aT" << "\t"<< "bT" << "\t" << "wT" << "\t" << "taT" << "\t" << "cT" << endl;
        wyniki << "------------------------------------------------" << endl;

        for (int i=0; i<n; i++)
        {
            wyniki << tablica[i][0] << "\t" << tablica[i][1] << "\t"<< tablica[i][2] << "\t" << tablica[i][3] << "\t"<< tablica[i][4] << "\t" << tablica[i][5] << endl;
        }
        wyniki << "------------------------------------------------" << endl;
        wyniki << "Sredni czas czekania: " << wTsrrr(n, tablica) << endl;
        wyniki << "Sredni czas realizacji: " << taTsrrr(n, tablica) << endl;
        wyniki.close();
    }
    cout << "------------------------------------------------" << endl;
    cout << "Sredni czas czekania: " << wTsrrr(n, tablica) << endl;
    cout << "Sredni czas realizacji: " << taTsrrr(n, tablica) << endl;
}

void rrEnd(int n,int tablica[][6], int q, int showTab, int saveTab)
{
    findwTrr(n, tablica, q);
    findtaTrr(n, tablica);
    rrShow(n, tablica, showTab, saveTab);

}