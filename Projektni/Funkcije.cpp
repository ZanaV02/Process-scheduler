#include "Funkcije.h"
#include <iomanip>
#include <queue>



void ispis(std::vector<Proces> niz)
{
    auto poredjenje = [](const Proces& a, const Proces& b)
        {
            return a.redniBrojUnosa < b.redniBrojUnosa;
        };
    std::sort(niz.begin(), niz.end(), poredjenje);
    std::cout << std::endl << "==============================================================" << std::endl;
    std::cout << " Naziv procesa      " << "Vrijeme kompletiranja      " << "Vrijeme cekanja      " << std::endl;

    std::cout << "==============================================================" << std::endl;

    // Ispisivanje podataka u tabeli
    for (int i = 0; i < niz.size(); i++)
    {
        std::cout << std::setw(7) << niz.at(i).nazivProcesa << std::setw(22) << niz.at(i).krajProcesa << std::setw(25) << niz.at(i).vrijemeCekanja << std::endl;
    }
    int suma1 = 0, suma2 = 0;
    for (int i = 0; i < niz.size(); i++)
    {
        suma1 += niz.at(i).krajProcesa;
        suma2 += niz.at(i).vrijemeCekanja;
    }
    std::cout << "==============================================================" << std::endl;
    std::cout << std::setw(17) << "Srednje vrijeme:" << YELLOW << std::setw(12) << std::fixed << std::setprecision(2) << static_cast<double> (suma1) / niz.size() << std::setw(25) << static_cast<double> (suma2) / niz.size() << RESET << std::endl;
}

void priority(std::vector<Proces> niz1)
{
    std::vector<Proces> niz = niz1;
    //sortiramo prvo po vremenu nailaska pa onda po prioritetu
    std::sort(niz.begin(), niz.end(), [](Proces& a, Proces& b) {
        if (a.vrijemeDolaska != b.vrijemeDolaska)
            return a.vrijemeDolaska < b.vrijemeDolaska;
        else
            return a.prioritet < b.prioritet;
        });
    int ukupnoVrijeme = 0;
    std::cout << YELLOW << "\nGantova karta:" << RESET << "\n |0| ";
    int zavrseniProcesi = 0;
    while (zavrseniProcesi != niz.size())
    {
        int trenutniProces = -1;
        bool check = false;
        for (int i = 0; i < niz.size(); i++)
        {
            //trazimo da li ima spremnih i koji ce postati trenutni
            if (!check && niz.at(i).vrijemeDolaska <= ukupnoVrijeme && niz.at(i).vrijemeTrajanja != 0)
            {
                check = true; //pronadjen je prvi spreman
                trenutniProces = i;
                continue;
            }
            //provjeravamo da li ima neki koji je takodje spreman i ima veci prioritet pa bi mogao zamijeniti prethodno pronadjen
            if (check && niz.at(i).vrijemeDolaska <= ukupnoVrijeme &&
                niz.at(i).prioritet < niz.at(trenutniProces).prioritet &&
                niz.at(i).vrijemeTrajanja != 0)
            {
                trenutniProces = i;
            }
        }
        if (trenutniProces == -1)
        {
            for (int i = 0; i < niz.size(); i++)
            {
                if (niz.at(i).vrijemeTrajanja != 0) //trazimo prvi naredni koji ce se obraditi
                {
                    std::cout << YELLOW << "X " << RESET;
                    ukupnoVrijeme += (niz.at(i).vrijemeDolaska - ukupnoVrijeme);
                    std::cout << "|" << ukupnoVrijeme << "| ";
                    break;
                }
            }
        }
        else
        {
            std::cout << YELLOW << niz.at(trenutniProces).nazivProcesa << " " << RESET;
            ukupnoVrijeme += niz.at(trenutniProces).vrijemeTrajanja;
            niz.at(trenutniProces).krajProcesa = ukupnoVrijeme - niz.at(trenutniProces).vrijemeDolaska;
            niz.at(trenutniProces).vrijemeCekanja = niz.at(trenutniProces).krajProcesa - niz.at(trenutniProces).vrijemeTrajanja;
            std::cout << "|" << ukupnoVrijeme << "| ";
            zavrseniProcesi++;
            niz.at(trenutniProces).vrijemeTrajanja = 0;
        }

    }
    ispis(niz);
}

void fcfs(std::vector<Proces> niz1)
{
    std::vector<Proces> niz = niz1;
    std::sort(niz.begin(), niz.end(), [](Proces& a, Proces& b) {
        if (a.vrijemeDolaska != b.vrijemeDolaska)
            return a.vrijemeDolaska < b.vrijemeDolaska;
        else
            return a.redniBrojUnosa < b.redniBrojUnosa;
        });
    int ukupnoVrijeme = 0;
    std::cout << YELLOW << "\nGantova karta:" << RESET << "\n |0| ";
    for (int i = 0; i < niz.size(); i++) //trazimo spremne procese
    {
        //ako nije nijedan, trazimo onaj koji sljedeci na redu po vremenu nailaska a posto je prvi put obradjen u tu svrhu
        //vracamo iterator unazad da bi bio ispisan na karti
        if (ukupnoVrijeme < niz.at(i).vrijemeDolaska)
        {
            std::cout << YELLOW << "X " << RESET;
            ukupnoVrijeme += (niz.at(i).vrijemeDolaska - ukupnoVrijeme);
            std::cout << "|" << ukupnoVrijeme << "| ";
            i--;
        }
        else
        {
            std::cout << YELLOW << niz.at(i).nazivProcesa << " " << RESET;
            ukupnoVrijeme += niz.at(i).vrijemeTrajanja;
            niz.at(i).krajProcesa = ukupnoVrijeme - niz.at(i).vrijemeDolaska;
            niz.at(i).vrijemeCekanja = niz.at(i).krajProcesa - niz.at(i).vrijemeTrajanja;
            std::cout << "|" << ukupnoVrijeme << "| ";
        }
    }
    ispis(niz);
}
void sjf(std::vector<Proces> niz1)
{
    std::vector<Proces> niz = niz1;
    auto poredjenje = [](const Proces& a, const Proces& b)
        {
            return a.vrijemeTrajanja < b.vrijemeTrajanja;
        };
    std::sort(niz.begin(), niz.end(), poredjenje);
    int ukupnoVrijeme = 0;
    int zavrseniProcesi = 0;
    std::cout << YELLOW << "\nGantova karta:" << RESET << "\n |0| ";
    while (zavrseniProcesi != niz.size())
    {
        int trenutniProces = -1;
        for (int i = 0; i < niz.size(); i++)//pronalazenje prvog dostupnog procesa
        {
            if (niz.at(i).vrijemeTrajanja != 0 && niz.at(i).vrijemeDolaska <= ukupnoVrijeme)
            {
                trenutniProces = i;
                break;
            }
        }
        if (trenutniProces != -1)
        {
            std::cout << YELLOW << niz.at(trenutniProces).nazivProcesa << " " << RESET;
            ukupnoVrijeme += niz.at(trenutniProces).vrijemeTrajanja;
            niz.at(trenutniProces).krajProcesa = ukupnoVrijeme - niz.at(trenutniProces).vrijemeDolaska;
            niz.at(trenutniProces).vrijemeCekanja = niz.at(trenutniProces).krajProcesa - niz.at(trenutniProces).vrijemeTrajanja;
            std::cout << "|" << ukupnoVrijeme << "| ";
            zavrseniProcesi++;
            niz.at(trenutniProces).vrijemeTrajanja = 0;
        }
        else //ako ne postoji spreman proces
        {
            bool check = false;
            int sljedeci = -1;
            for (int i = 0; i < niz.size(); i++)
            {
                if (!check && niz.at(i).vrijemeTrajanja != 0) //prvi sa najkracim vremenom u nizu
                {
                    sljedeci = i;
                    check = true;
                    continue;
                }
                //poredimo da li je neki od procesa poslije njega prije bio spreman
                if (check && niz.at(i).vrijemeTrajanja != 0 && niz.at(i).vrijemeDolaska < niz.at(sljedeci).vrijemeDolaska)
                {
                    sljedeci = i;
                }
            }
            std::cout << YELLOW << "X " << RESET;
            ukupnoVrijeme += (niz.at(sljedeci).vrijemeDolaska - ukupnoVrijeme);
            std::cout << "|" << ukupnoVrijeme << "| ";
        }
    }
    ispis(niz);
}

void rr(std::vector<Proces> niz1, int quantum)
{
    std::queue<int> q;
    std::vector<Proces> niz = niz1;
    std::sort(niz.begin(), niz.end(), [](Proces& a, Proces& b) {
        return a.vrijemeDolaska < b.vrijemeDolaska;
        });
    std::vector<int> trajanja;
    for (int i = 0; i < niz.size(); i++)
    {
        int a;
        a = niz.at(i).vrijemeTrajanja;
        trajanja.push_back(a);
    }
    int ukupnoVrijeme = 0;
    int zavrseniProcesi = 0;
    int ponovoDodaj = -1;
    std::cout << YELLOW << "\nGantova karta:" << RESET << "\n |0| ";
    while (zavrseniProcesi != niz.size())
    {
        for (int i = 0; i < niz.size(); i++) //dodavanje procesa koji su spremni i nisu vec dodani u red
        {
            if (niz.at(i).vrijemeDolaska <= ukupnoVrijeme && trajanja.at(i) != 0 && !inQueue(q, i) && ponovoDodaj != i)
            {
                q.push(i);
            }
        }
        if (ponovoDodaj != -1) //procesi koji se trebaju opet obraditi
        {
            q.push(ponovoDodaj);
        }
        int current = -1;
        if (!q.empty())
        {
            current = q.front();
            q.pop();
        }
        if (current == -1) //red je prazan i trazimo prvi neizvrseni proces
        {
            for (int i = 0; i < niz.size(); i++)
            {
                if (trajanja.at(i) > 0)
                {
                    ukupnoVrijeme = niz.at(i).vrijemeDolaska;
                    ponovoDodaj = -1;
                    break;
                }
            }
            std::cout << YELLOW << "X " << RESET;
            std::cout << "|" << ukupnoVrijeme << "| ";
        }
        else
        {
            if (trajanja.at(current) >= quantum)
            {
                trajanja.at(current) -= quantum;
                ukupnoVrijeme += quantum;
            }
            else
            {
                ukupnoVrijeme += trajanja.at(current);
                trajanja.at(current) = 0;
            }
            if (trajanja.at(current) == 0) //proces je zavrsen
            {
                niz.at(current).krajProcesa = ukupnoVrijeme - niz.at(current).vrijemeDolaska;
                niz.at(current).vrijemeCekanja = niz.at(current).krajProcesa - niz.at(current).vrijemeTrajanja;
                ponovoDodaj = -1;
                zavrseniProcesi++;
            }
            else //proces je potrebno opet obraditi
            {
                ponovoDodaj = current;
            }
            std::cout << YELLOW << niz.at(current).nazivProcesa << " " << RESET;
            std::cout << "|" << ukupnoVrijeme << "| ";
        }
    }
    ispis(niz);
}

bool inQueue(std::queue<int> q, int index)
{
    while (!q.empty())
    {
        if (q.front() == index)
        {
            return true;
        }
        q.pop();
    }
    return false;
}

void srtf(std::vector<Proces> niz1)
{
    std::vector<Proces> niz = niz1;
    auto poredjenje = [](const Proces& a, const Proces& b)
        {
            return a.vrijemeTrajanja < b.vrijemeTrajanja;
        };
    std::sort(niz.begin(), niz.end(), poredjenje);
    std::vector<int> trajanja;//pomocni niz vremena trajanja da se ne bi mijenjao originalni prilikom azuriranja podataka procesa
    for (int i = 0; i < niz.size(); i++)
    {
        int a;
        a = niz.at(i).vrijemeTrajanja;
        trajanja.push_back(a);
    }
    int ukupnoVrijeme = 0;
    int zavrseniProcesi = 0;

    std::cout << YELLOW << "\nGantova karta:" << RESET << "\n |0| ";
    while (zavrseniProcesi != niz.size())
    {
        int trenutni = -1;
        int prekid = -1;
        double najkraci = std::numeric_limits<double>::infinity();//varijabla za proces sa najkracim preostalim vremenom
        double najblizi = std::numeric_limits<double>::infinity();//ako nema spremnog procesa, trazimo najblizi po vremenu dolaska
        for (int i = 0; i < niz.size(); i++) //trazimo prvi koji nije izvrsen a spreman je
        {
            if (niz.at(i).vrijemeDolaska <= ukupnoVrijeme && trajanja.at(i) != 0 && trajanja.at(i) <= najkraci)
            {
                trenutni = i;
                najkraci = trajanja.at(i);
            }
        }
        if (trenutni == -1) //ako nije pronadjen trazimo proces koji ce najprije biti spreman i ukupno vrijeme setujemo na vrijeme dolaska tog procesa
        {
            for (int i = 0; i < niz.size(); i++)
            {
                if (trajanja.at(i) > 0 && niz.at(i).vrijemeDolaska < najblizi)
                {
                    najblizi = niz.at(i).vrijemeDolaska;
                }
            }
            ukupnoVrijeme = najblizi;
            std::cout << YELLOW << "X " << RESET;
            std::cout << "|" << ukupnoVrijeme << "| ";
        }
        else //ako je pronadjen racunamo sta kad dodamo njegovo vrijeme na ukupno, da li postoji neki koji ce ga prekinuti jer ima manje vrijeme
        {
            int pom = ukupnoVrijeme + trajanja.at(trenutni);
            //posto su sortirani po vremenu trajanja, petlja ide do trenutnog jer su svi poslije njega sa vecim trajanjem i nisu kandidati za prekid
            for (int i = 0; i < trenutni; i++)
            {
                //proces ne smije biti zavrsen, mora doci prije vremena zavrsetka prethodnog procesa, dosao je prije najblizeg 
                if (trajanja.at(i) > 0 && niz.at(i).vrijemeDolaska < pom && niz.at(i).vrijemeDolaska < najblizi &&
                    trajanja.at(i) < trajanja.at(trenutni) - (niz.at(i).vrijemeDolaska - ukupnoVrijeme) && trajanja.at(i) < trajanja.at(trenutni))
                {
                    najblizi = niz.at(i).vrijemeDolaska;
                    prekid = i;
                }
            }
            if (prekid != -1) //nadjen proces koji ce prekinuti prethodno nadjeni
            {
                trajanja.at(trenutni) -= niz.at(prekid).vrijemeDolaska - ukupnoVrijeme;//azuriranje vremena trajanja procesa
                ukupnoVrijeme = niz.at(prekid).vrijemeDolaska;
            }
            else
            {
                ukupnoVrijeme += trajanja.at(trenutni);
                trajanja.at(trenutni) = 0;
                niz.at(trenutni).krajProcesa = ukupnoVrijeme - niz.at(trenutni).vrijemeDolaska;
                niz.at(trenutni).vrijemeCekanja = niz.at(trenutni).krajProcesa - niz.at(trenutni).vrijemeTrajanja;
                zavrseniProcesi++;
            }
            std::cout << YELLOW << niz.at(trenutni).nazivProcesa << " " << RESET;
            std::cout << "|" << ukupnoVrijeme << "| ";
        }
    }
    ispis(niz);
}
