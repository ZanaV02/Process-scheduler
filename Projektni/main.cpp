#include <iostream>
#include "Funkcije.h"
#include <vector>
#include <sstream>

bool isInteger(const std::string& s)
{
    std::stringstream iss(s);
    int n;
    iss >> std::noskipws >> n;
    return iss.eof() && !iss.fail();
}


int main()
{
    std::string unos;
    do
    {
        std::cout << "Unesite broj procesa, ime fajla ili QUIT za izlaz iz programa: \n";
        std::getline(std::cin, unos);
        if (isInteger(unos))
        {
            int brojProcesa = std::stoi(unos);

            std::string pomNaziv;
            int pomVrijemeTrajanja;
            int pomVrijemeDolaska;
            int pomPrioritet;

            std::vector<Proces> nizProcesa;
            for (int i = 1; i <= brojProcesa; i++)
            {
                Proces pom;
                std::cout << "Unesite naziv " << i << ". procesa: ";
                std::cin >> pomNaziv;
                pom.nazivProcesa = pomNaziv;

                std::cout << "  Unesite vrijeme trajanja " << i << ". procesa: ";
                std::cin >> pomVrijemeTrajanja;
                pom.vrijemeTrajanja = pomVrijemeTrajanja;

                std::cout << "    Unesite vrijeme dolaska " << i << ". procesa: ";
                std::cin >> pomVrijemeDolaska;
                pom.vrijemeDolaska = pomVrijemeDolaska;

                std::cout << "      Unesite prioritet " << i << ". procesa: ";
                std::cin >> pomPrioritet;
                pom.prioritet = pomPrioritet;

                std::cout << "_______________________________________________\n";
                pom.redniBrojUnosa = i;

                nizProcesa.push_back(pom);
            }
            if (nizProcesa.size() > 0)
            {
                std::string ime;
                do
                {
                    std::cout << "\nUnesite naziv algoritma ili KRAJ1 za izlaz na prethodni meni\n";
                    std::cin >> ime;
                    if (ime == "PRIORITY" || ime == "priority")
                        priority(nizProcesa);
                    else if (ime == "FCFS" || ime == "fcfs")
                        fcfs(nizProcesa);
                    else if (ime == "SJF" || ime == "sjf")
                        sjf(nizProcesa);
                    else if (ime == "RR" || ime == "rr")
                    {
                        int q;
                        std::cout << "Unesite vrijednost quantuma: ";
                        std::cin >> q;
                        rr(nizProcesa, q);
                    }
                    else if (ime == "SRTF" || ime == "srtf")
                        srtf(nizProcesa);
                } while (ime != "KRAJ1");
            }
        }
        else if (unos != "QUIT")
        {
            std::ifstream inputFile(unos + ".txt");
            std::vector<Proces> nizProcesa;
            if (inputFile.is_open())
            {
                Proces pom;
                int number;
                inputFile >> number;

                for (int i = 0; i < number; i++)
                {
                    std::string line;
                    int trajanje, dolazak, prioritet;
                    inputFile >> line >> trajanje >> dolazak >> prioritet;
                    pom.nazivProcesa = line;
                    pom.vrijemeTrajanja = trajanje;
                    pom.vrijemeDolaska = dolazak;
                    pom.prioritet = prioritet;
                    pom.redniBrojUnosa = i + 1;
                    nizProcesa.push_back(pom);
                }
                inputFile.close();
            }
            if (nizProcesa.size() > 0)
            {
                std::string ime;
                do
                {

                    std::cout << "\nUnesite naziv algoritma ili KRAJ2 za izlaz na prethodni meni\n";
                    std::cin >> ime;
                    if (ime == "PRIORITY" || ime == "priority")
                        priority(nizProcesa);
                    else if (ime == "FCFS" || ime == "fcfs")
                        fcfs(nizProcesa);
                    else if (ime == "SJF" || ime == "sjf")
                        sjf(nizProcesa);
                    else if (ime == "RR" || ime == "rr")
                    {
                        int q;
                        std::cout << "Unesite vrijednost quantuma: ";
                        std::cin >> q;
                        rr(nizProcesa, q);
                    }
                    else if (ime == "SRTF" || ime == "srtf")
                        srtf(nizProcesa);
                } while (ime != "KRAJ2");
            }
        }
    } while (unos != "QUIT");
}

