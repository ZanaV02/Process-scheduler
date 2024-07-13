#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <limits>
#include <cmath>

#define RESET   "\033[0m"
#define YELLOW  "\033[33m"


class Proces
{
public:
    std::string nazivProcesa;
    int vrijemeTrajanja;
    int vrijemeDolaska;
    int prioritet;
    int redniBrojUnosa;
    int krajProcesa;
    int vrijemeCekanja;
};


void ispis(std::vector<Proces> niz);
void fcfs(std::vector<Proces> niz1);
void priority(std::vector<Proces> niz1);
void sjf(std::vector<Proces> niz1);
void rr(std::vector<Proces> niz1, int quantum);
bool inQueue(std::queue<int> q, int index);
void srtf(std::vector<Proces> niz1);