#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include "cProcess.hpp"
#include "fcfs.hpp"
#include "rr.hpp"
#include "sjfnp.hpp"
#include "sjfp.hpp"
using namespace std;
int cProcess::numer=1; // zmienna statyczna uzywana do numeracji procesow w klasie

int main()
{
    srand(time(0)); // rozpoczecie pracy generatora liczb pseudolosowych
    int n=0; // ilosc procesow w programie
    int a; // uzywana do obslugi switch
    int aTu=-1; // aT podawany przez uzytkownika
    int minaTu=-1; // minimalna wartosc aT do generowania procesow
    int bTu=-1; // bT podawany przez uzytkownika
    int minbTu=-1; // minimalna wartosc bT do generowania procesow
    int PIDu=-1; // PID podawany przez uzytkownika
    int q=0; // quantum podawany przez uzytkowanika
    ifstream baza; // przechowanie danych z pliku z procesami
    string inplik; // zmienna na nazwe pliku z procesami
    bool checkinplik=0; // zmienna do poprawy blednej nazwy pliku z procesami
    int showTab=-1; // czy wyswietlic tabele
    int saveTab=-1; // czy zapisac tabele do pliku
    vector<cProcess*> mProcess; // vector przechowujacy procesy
    cout << "1. Losowe parametry procesow." << endl;
    cout << "2. Losowe parametry procesow w danym zakresie." << endl;
    cout << "3. Podaj stala wartosc aT." << endl;
    cout << "4. Podaj wszystkie dane recznie." << endl;
    cout << "5. Wczytaj dane z pliku." << endl;
    cout << "Wybierz sposob dzialania programu: ";
    cin >> a;
    switch (a) //funkcja pozwala wybrac opcje dzialania programu
    {
    case 1: // Dla procesow z losowym aT i bT
    {

        while (n<=0)
        {
            cout << "Ile chcesz stworzyc procesow: ";
            cin >> n;
        }
        while (q<=0)
        {
            cout << "Podaj kwant dla round robin: ";
            cin >> q;
        }
        for (int i=0; i<n; i++)
        {
            mProcess.push_back(new cProcess);
        }
        break;
    }
    case 2: // Dla procesow z losowym aT i bT w zakresie ustwionym przez uzytkownika
    {

        while (n<=0)
        {
            cout << "Ile chcesz stworzyc procesow: ";
            cin >> n;
        }
        while (q<=0)
        {
            cout << "Podaj kwant dla round robin: ";
            cin >> q;
        }
        while (aTu<0 | minaTu<0 | minaTu>aTu)
        {
            cout << "Jaka minimalna wartosc aT: ";
            cin >> minaTu;
            cout << "Jaka maksymalna wartosc aT: ";
            cin >> aTu;
        }
        while (bTu<0 | minbTu<=0 | minbTu>bTu)
        {
            cout << "Jaka minimalna wartosc bT: ";
            cin >> minbTu;
            cout << "Jaka maksymalna wartosc bT: ";
            cin >> bTu;
        }
        for (int i=0; i<n; i++)
        {
            mProcess.push_back(new cProcess(minaTu, aTu, minbTu, bTu));
        }
        break;
    }
    case 3: // Dla procesow ze stala wartoscia aT
    {
        while (n<=0)
        {
            cout << "Ile chcesz stworzyc procesow: ";
            cin >> n;
        }
        while (q<=0)
        {
            cout << "Podaj kwant dla round robin: ";
            cin >> q;
        }
        while (aTu<0)
        {
            cout << "Jaka wartosc aT: ";
            cin >> aTu;
            for (int i=0; i<n; i++)
            {
                mProcess.push_back(new cProcess(aTu));
            }
        }
        break;
    }
    case 4: // Reczne tworzenie procesow
    {
        while (n<=0)
        {
            cout << "Ile chcesz stworzyc procesow: ";
            cin >> n;
        }

        while (q<=0)
        {
            cout << "Podaj kwant dla round robin: ";
            cin >> q;
        }
        for (int i=0; i<n; i++)
        {
            while(PIDu<0)
            {
                cout << "Jaka wartosc PID dla " << i+1 << "procesu: ";
                cin >> PIDu;
            }
            while(aTu<0)
            {
                cout << "Jaka wartosc aT dla " << i+1 << "procesu: ";
                cin >> aTu;
            }
            while(bTu<0)
            {
                cout << "Jaka wartosc bT dla " << i+1 << "procesu: ";
                cin >> bTu;
            }
            mProcess.push_back(new cProcess(PIDu, aTu, bTu));
            PIDu=-1;
            aTu=-1;
            bTu=-1;
        }

        break;
    }
    case 5: // wczytywanie procesow z pliku
    {
        while(checkinplik==0) //petla pozwala wpisac ponownie nazwe pliku jesli uzytkownik sie pomylil
        {
            cout << "Podaj nazwe pliku z baza (plik .txt, podaj nazwe bez rozszerzenia): ";
            cin >> inplik;
            inplik=inplik+".txt";
            baza.open(inplik); // otworzenie pliku z baza procesow
            if ( baza.good())
            {
                while (true)
                {
                    int a, b, c;
                    baza >> a >> b >> c;
                    if (!baza.fail())
                    {
                        if (a==0)
                        {
                            n=b;
                            q=c;
                        }
                        else
                        {
                            mProcess.push_back(new cProcess(a, b, c));
                        }
                    }
                    else
                    {
                        checkinplik=1;
                        break;
                    }

                }
            }
            else
                cout << "Nie otworzono pliku!" << endl;
        }
        baza.close();
        break;
    }
    }
    while(showTab!=0 && showTab!=1)
    {
        cout << "Czy wyswietlic tabele procesow (1 tak, 0 nie): ";
        cin >> showTab;
    }
    while(saveTab!=0 && saveTab!=1)
    {
        cout << "Czy zapisac tabele procesow do pliku (1 tak, 0 nie): ";
        cin >> saveTab;
    }


    int tablica[n][6]; // 0 - PID, 1 - aT, 2 - bT, 3 - wT, 4 - taT, 5 - cT
    for (int i=0; i<n; i++) // przepisanie procesow do tablicy uzywanej w algorytmach
    {
        tablica[i][0]=mProcess[i]->sPID();
        tablica[i][1]=mProcess[i]->saT();
        tablica[i][2]=mProcess[i]->sbT();
        tablica[i][3]=0;
        tablica[i][5]=0;
        tablica[i][4]=0;
    }
    fcfsEnd(n, tablica, showTab, saveTab); // wykonanie algorytmu First Come, First Served
    rrEnd(n, tablica, q, showTab, saveTab);
    sjfnpEnd(n, tablica, showTab, saveTab);
    sjfpEnd(n, tablica, showTab, saveTab);
    return 0;
}