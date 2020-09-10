#ifndef SJFP_H_INCLUDED
#define SJFP_H_INCLUDED
using namespace std;
void findwTsjfp(int n, int tablica[][6]); // liczenie wT, cT oraz przeprowadzenie samego algorytmu
void findtaTsjfp(int n, int tablica[][6]);// liczenie taT
float wTsrsjfp(int n, int tablica[][6]); // srednia wT
float taTsrsjfp(int n, int tablica[][6]); // srednia taT
void sjfpShow(int n,int tablica[][6]); // wyswietla
void sjfpEnd(int n,int tablica[][6], int showTab, int saveTab);


#endif // SJFP_H_INCLUDED