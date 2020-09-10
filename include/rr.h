#ifndef RR_H_INCLUDED
#define RR_H_INCLUDED
using namespace std;
void findwTrr(int n, int q, int tablica[][6]); // liczenie wT, cT oraz przeprowadzenie samego algorytmu
void findtaTrr(int n, int tablica[][6]);// liczenie taT
float wTsrrr(int n, int tablica[][6]); // srednia wT
float taTsrrr(int n, int tablica[][6]); // srednia taT
void rrShow(int n,int tablica[][6]); // wyswietla
void rrEnd(int n,int tablica[][6], int q, int showTab, int saveTab);


#endif // RR_H_INCLUDED