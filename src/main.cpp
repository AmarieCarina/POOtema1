#include <iostream>
#include <vector>
#include <string>
class Produs {
    long int IDProdus; ///cod identificare
    std::string Denumire;
    long int Stoc; ///nr de produse disponibile
    std::string Furnizor;
    double Pret; ///nr real reprezentand costul
public:
    Produs() { ///constructor de initializare, fara parametri
        this->Denumire="";
        this->IDProdus = 0;
        this->Stoc = 0;
        this->Furnizor="";
        this->Pret=0.0;
        std::cout<<"Constructor de initializare- Produs\n";
    }
    ///constructor cu parametri, folosind lista de initializare
    Produs(const long int IDProdus_, const std::string Denumire_, const long int Stoc_, const std::string Furnizor_, const double Pret_)
        : IDProdus{IDProdus_}, Denumire{Denumire_}, Stoc{Stoc_}, Furnizor{Furnizor_}, Pret{Pret_} {
        //std::cout<<"Constructor cu parametri- Produs\n";
    }

    ///constructor de copiere, folosind lista de initializare
    Produs(const Produs& other)
        :IDProdus{other.IDProdus}, Denumire{other.Denumire}, Stoc{other.Stoc}, Furnizor{other.Furnizor}, Pret{other.Pret} {
        //std::cout<<"Constructor de copiere- Produs\n";
    }

    ///////////////////////////////////getter?
    std::string getDenumire() const {
        return Denumire;
    }

    ///operator= de copiere
    Produs& operator=(const Produs& other) {
        if (this == &other)
                {return *this;}
        IDProdus=other.IDProdus;
        Denumire=other.Denumire;
        Stoc=other.Stoc;
        Furnizor=other.Furnizor;
        Pret=other.Pret;
        //std::cout<<"Operator= copiere- Produs\n";
        return *this;
    }

    ///operator<< folosind functie prieten
    friend std::ostream& operator<<(std::ostream& os, const Produs& p) {
        os<<"\nIDProdus: "<<p.IDProdus<<"\n";
        os<<"Denumire: "<<p.Denumire<<"\n";
        os<<"Stoc: "<<p.Stoc<<"\n";
        os<<"Furnizor: "<<p.Furnizor<<"\n";
        os<<"Pret: "<<p.Pret<<"\n";
        return os;
    }
    //operator-, definit special pentru afisarea denumirii unui produs, in cadrul afisarii clasei Comanda
    friend std::ostream& operator-(std::ostream& os, const Produs& p) {
        os<<"\nDenumire produs: "<<p.Denumire<<"\n";
        return os;
    }
    double getPret() const {
        return this->Pret;
    }

    ///destructor
    ~Produs() {
        //std::cout<<"Destructor- Produs\n";
    }
};

class Comanda {
    long int IDComanda; //pentru identificare unica a comenzii
    std::string NumeClient; //cine a facut comanda
    std::string MetodaPlata; //plata la livrare sau online
    bool StatusProcesare; //procesat-> 1; neprocesat-> 0
    std::vector<Produs> Produse; //produsele corespunzatoare comenzii
    std::vector<int> Cantitati;
    //vector de intregi cu cantitati- un buchet nu poate avea decat un numar intreg de flori
    double Total;
public:
    ///constuctor de initializare, fara parametri
    Comanda() {
        this->IDComanda = 0;
        this->NumeClient = "";
        this->Produse.clear();
        this->Cantitati.clear();
        this->MetodaPlata = "";
        this->StatusProcesare = false;
        this->Total = 0;
    }

    ///constructor parametrizat, folosind lista de initializare
    ///StatusProcesare - valoare implicita false
    ///Total - valoare implicita 0.0
    Comanda(const long int IDComanda_, const std::string& NumeClient_, const std::string& MetodaPlata_, const std::vector<Produs>& Produse_, const std::vector<int>& Cantitati_, const double Total_=0.0, const bool StatusProcesare_=false)
        :IDComanda{IDComanda_},NumeClient{NumeClient_},MetodaPlata{MetodaPlata_},StatusProcesare{StatusProcesare_}, Produse{Produse_},Cantitati {Cantitati_}, Total{Total_}{
        //std::cout<<"Constructor cu parametri- Comanda\n";
    }
    Comanda(const Comanda& other)
        :IDComanda{other.IDComanda}, NumeClient{other.NumeClient}, MetodaPlata{other.MetodaPlata}, StatusProcesare{other.StatusProcesare}, Produse{other.Produse}, Cantitati{other.Cantitati}, Total{other.Total}{
        //std::cout<<"Constructor de copiere- Comanda\n";
    }
    Comanda& operator=(const Comanda& other) {
        if (this == &other) {
            return *this;
        }
        IDComanda=other.IDComanda;
        NumeClient=other.NumeClient;
        MetodaPlata=other.MetodaPlata;
        StatusProcesare=other.StatusProcesare;
        Produse=other.Produse;
        Cantitati=other.Cantitati;
        Total=other.Total;
        return *this;
    }
    ///reprezentare obiecte ca strings
    ///operator<< pentru afisare
    friend std::ostream& operator<<(std::ostream& os, const Comanda& obj){
        os<<"\nIDComanda: "<<obj.IDComanda<<"\n";
        os<<"NumeClient: "<<obj.NumeClient<<"\n";
        os<<"MetodaPlata: "<<obj.MetodaPlata<<"\n";
        os<<"StatusProcesare: "<<obj.StatusProcesare<<"\n";
        int indexCantitate=0;
        for (const Produs& Produs : obj.Produse) {
            operator-(os, Produs);
            os<<"Cantitate: "<<obj.Cantitati[indexCantitate]<<"\n";
            indexCantitate++;
        }
        os<<"\nTotal comanda: "<<obj.Total<<"\n";
        return os;
    }
    friend double CalculeazaTotal(const Comanda& c) {
        double total=0;
        for (int i=0;i<c.Produse.size();i++) {
            total+=c.Produse[i].getPret()*c.Cantitati[i];
        }
        return total;
    }
    ~Comanda() {
        //std::cout<<"Destructor- Comanda\n";
    }
};


int main() {
    Produs p1(1,"Trandafir",1000,"Florar SRL",10);
    Produs p2(2,"Lalea",2000, "Flori SRL", 7);
    Produs p3(3,"Orhidee",800,"Exotic SRL",40);
    Produs p4(4,"Crin",1000,"Natura SRL",20);
    Produs p5(5,"Gerbera",1800,"Bloom SRL",9);
    Produs p6(6,"Frezie",1400,"Bloom SRL",8);
    Produs p7(7,"Bujor",900,"Garden SRL",18);
    Produs p8(8,"Hortensie",700,"Garden SRL",30);
    Produs p9(9,"Crizantema",2000,"Expert SRL",6);
    Produs p10(10,"Alstroemeria",1200,"Exotic SRL",10);
    Comanda c1(1, "Popescu", "Card", {p1,p6}, {7,3});
    Comanda c2(2,"Ionescu", "Cash", {p3,p5,p10}, {5,4,3});
    Comanda c3(3,"Popescu","Card",{p4,p6,p9},{3,4,5});
    Comanda c4(4,"Munteanu", "Cash", {p7,p8,p3},{3,2,3});
    Comanda c5(5,"Popescu","Card", {p7,p6,p5},{4,5,3});
    Comanda c6(6,"Olteanu", "Card", {p1,p9,p10},{5,3,4});
    //std::cout<<p0.getDenumire()<<"\n";
    //operator<<(std::cout,c1);
    std::cout<<CalculeazaTotal(c1);

    //e.push_back(elem) to add at the end;
    //e.pop_back(elem) to remove from the end;
    //e.size() for size; e.empty() (1 pentru empty)
    // for (int produs : produse) {
    //     cout << produs << "\n";
    // }
    return 0;
}