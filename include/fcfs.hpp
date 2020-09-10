#ifndef FCFS_H_INCLUDED
#define FCFS_H_INCLUDED
using namespace std;

void findwTfcfs(int n, int tablica[][6]); // liczenie wT
void findtaTfcfs(int n, int tablica[][6]); // liczenie taT
float wTsrfcfs(int n, int tablica[][6]); // liczenie lacznego wT
float taTsrfcfs(int n, int tablica[][6]); // liczenie lacznego taT
void countcTfcfs(int n, int tablica[][6]); // liczenie cT
void fcfsShow(int n, int tablica[][6]); // wypisanie tabeli oraz danych
void fcfsEnd(int n,int tablica[][6], int showTab, int saveTab); // obsluga algorytmu

#endif // FCFS_H_INCLUDED