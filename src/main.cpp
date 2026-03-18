#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include "../include/produs.h"
class Produs {
    long int IDProdus;
    std::string Denumire;
    long int Stoc;
    std::string Furnizor;
    double Pret;
public:
    Produs() {
        this->Denumire="";
        this->IDProdus = 0;
        this->Stoc = 0;
        this->Furnizor="";
        this->Pret=0.0;
        std::cout<<"Constructor de initializare- Produs\n";
    }
    Produs(const long int IDProdus_, const char* Denumire_, const long int Stoc_, const char* Furnizor_, const double Pret_)
        : IDProdus{IDProdus_}, Denumire{Denumire_}, Stoc{Stoc_}, Furnizor{Furnizor_}, Pret{Pret_} {
        std::cout<<"Constructor cu parametri- Produs\n";
    }
    Produs(const Produs& other)
        :IDProdus{other.IDProdus}, Denumire{other.Denumire}, Stoc{other.Stoc}, Furnizor{other.Furnizor}, Pret{other.Pret} {
        std::cout<<"Constructor de copiere- Produs\n";
    }
    const std::string getDenumire() const {
        return Denumire;
    }
    Produs& operator=(const Produs& other) {
        if (this == &other)
                {return *this;}
        IDProdus=other.IDProdus;
        Denumire=other.Denumire;
        Stoc=other.Stoc;
        Furnizor=other.Furnizor;
        Pret=other.Pret;
        std::cout<<"Operator= copiere- Produs\n";
        return *this;
    }
    ~Produs() {
        std::cout<<"Destructor- Produs\n";
    }
};
// class Comanda {
//     long int IDComanda;
//     char* NumeClient;
//     char* MetodaPlata;
//     std::vector<Produs> Produse[];
//     // std::vector<int> Cantitati [];
//     double Total;
// public:
//     Comanda() {
//         this->IDComanda = 0;
//         this->NumeClient = nullptr;
//         this->Produse={};
//         this->Cantitati={};
//         this->MetodaPlata = nullptr;
//         this->Total = 0;
//     }
//     Comanda(const long int IDComanda, const char* NumeClient, const char* MetodaPlata, std::vector<int> Produse, std::vector<int> Cantitati, const double Total) {
//         this->IDComanda = IDComanda;
//         this->NumeClient = new char[strlen(NumeClient)+1];
//         strcpy(this->NumeClient, NumeClient);
//         // for (int i=0; i<Produse.size(); i++) {
//         //     this->Produse[i]=Produse[i];
//         // }
//         this->MetodaPlata = new char[strlen(MetodaPlata)+1];
//         strcpy(this->MetodaPlata, MetodaPlata);
//         this->Total=Total;
//     }
//     Comanda(Comanda& c) {
//         this->IDComanda = c.IDComanda;
//         if (this->NumeClient) {
//             this->NumeClient = new char[strlen(this->NumeClient)+1];
//             strcpy(this->NumeClient, c.NumeClient);
//         }
//         else {
//             this->NumeClient = nullptr;
//         }
//         if (this->MetodaPlata) {
//             this->MetodaPlata = new char[strlen (this->MetodaPlata)+1];
//             strcpy(this->MetodaPlata, c.MetodaPlata);
//         }else {
//             this->MetodaPlata = nullptr;
//         }
//         ////////////////Produse si Cantitati///////////////////////////////////////////////
//         this->Total = c.Total;
//     }
//     ~Comanda() {
//         delete[] NumeClient;
//         delete[] MetodaPlata;
//     }
// };
int main() {
    Produs p0;
    Produs p1(1,"Lalea",10,"Firma1",5);
    p0 = p1;
    std::cout<<p0.getDenumire()<<"\n";


    //Produse.push_back(elem) to add at the end;
    //Produse.pop_back(elem) to remove from the end;
    //Produse.size() for size; Produse.empty() (1 pentru empty)
    // for (int produs : produse) {
    //     cout << produs << "\n";
    // }
    return 0;
}