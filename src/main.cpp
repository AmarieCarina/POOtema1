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
    Produs(const long int IDProdus_, const std::string& Denumire_, const long int Stoc_, const std::string& Furnizor_, const double Pret_)
        : IDProdus{IDProdus_}, Denumire{Denumire_}, Stoc{Stoc_}, Furnizor{Furnizor_}, Pret{Pret_} {
        //std::cout<<"Constructor cu parametri- Produs\n";
    }

    ///constructor de copiere, folosind lista de initializare
    Produs(const Produs& other)
        :IDProdus{other.IDProdus}, Denumire{other.Denumire}, Stoc{other.Stoc}, Furnizor{other.Furnizor}, Pret{other.Pret} {
        //std::cout<<"Constructor de copiere- Produs\n";
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
        os<<"Denumire produs: "<<p.Denumire<<"; ";
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
    Comanda(const long int IDComanda_, const std::string& NumeClient_, const std::string& MetodaPlata_, const std::vector<Produs>& Produse_, const std::vector<int>& Cantitati_, const bool StatusProcesare_=false, const double Total_=0.0)
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
        size_t indexCantitate=0;
        for (const Produs& produs : obj.Produse) {
            operator-(os, produs);
            os<<"Cantitate: "<<obj.Cantitati[indexCantitate]<<"\n";
            indexCantitate++;
        }
        os<<"Total comanda: "<<obj.Total<<"\n";
        return os;
    }

    ///functionalitati:
    double CalculeazaTotal() const; //prototip

    void setTotal() {
        this->Total=CalculeazaTotal();
    }
    double getTotal() const{
        return Total;
    }
    std::string getNumeClient() const {
        return NumeClient;
    }
    long int getID() const {
        return IDComanda;
    }
    bool getStatus() const {
        return this->StatusProcesare;
    }

    void AplicaReducere(int procent);

    void Proceseaza() {
        if (this->StatusProcesare == false) {
            this->StatusProcesare = true;
            std::cout<<"Succes!\n";
        }
        else
            std::cout<<"Comanda deja procesata!\n";
    }
    ~Comanda() = default;
};
double Comanda::CalculeazaTotal() const {
    double total=0;
    for (size_t i=0; i < Produse.size(); i++) {
        total+=Produse[i].getPret()*Cantitati[i];
    }
    return total;
}
void Comanda::AplicaReducere(int procent) {
    const double initial = CalculeazaTotal();
    Total = initial-initial*procent/100.0;
}

class Livrari {
    std::vector<Comanda>Comenzi;
        //vector continand obiecte de tip Comanda; conditie de apartenenta: campul statusProcesare == true
    std::vector<std::string>Adrese;
        //vector continand adresele la care trebuie facuta livrarea
    std::vector<std::string>NumeClienti;
        //vector continand numele clientilor
public:
    Livrari(const std::vector<Comanda>& Comenzi_, const std::vector<std::string>& Adrese_, const std::vector<std::string>& NumeClienti_)
        :Comenzi{Comenzi_}, Adrese{Adrese_}, NumeClienti {NumeClienti_} {}

    friend void IstoricClient(const Livrari& Livrare, const std::string& Nume) {
        for (const Comanda& c : Livrare.Comenzi) {
            if (c.getNumeClient()==Nume) {
                operator<<(std::cout,c);
            }
        }
    }
    friend double CalculeazaIncasari(const Livrari& livrare) {
        double total=0;
        for (const Comanda& c:livrare.Comenzi) {
            total+=c.getTotal();
        }
        return total;
    }

    friend void ComenziDeLivrat(const Livrari& livrare) {
        for (size_t index=0; index<livrare.Comenzi.size(); index++) {
            if (livrare.Comenzi[index].getStatus()==true) {
                std::cout<<livrare.Comenzi[index].getNumeClient()<<" | ";
                std::cout<<livrare.Adrese[index]<<std::endl;
            }
        }
    }

    friend void getNumeTotiClientii(const Livrari& livrare) {
        for (size_t index=0; index<livrare.Comenzi.size(); index++) {
            std::cout<<" * "<<livrare.Comenzi[index].getNumeClient()<<" -> "<<index<<"\n";
        }
        std::cout<<"\n";
    }
    friend std::string getNumeDupaCod(const Livrari& livrare, const int cod) {
        return livrare.Comenzi.at(cod).getNumeClient();
    }
    friend void AfiseazaToateComenzile(const Livrari& livrare) {
        for (size_t index=0; index<livrare.Comenzi.size(); index++) {
            operator<<(std::cout,livrare.Comenzi[index]);
        }
    }
    friend Comanda* getComandaDupaID(Livrari& livrare, const int ID) {
        for (size_t index=0; index<livrare.Comenzi.size(); index++) {
            if (livrare.Comenzi[index].getID()==ID) {
                return &livrare.Comenzi[index];
            }
        }
        return nullptr;
    }

};

int main() {
    //
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

    Comanda c1(1, "Popescu", "Card", {p1,p6}, {7,3}, true);
    Comanda c2(2,"Ionescu", "Cash", {p3,p5,p10}, {5,4,3},true);
    Comanda c3(3,"Popescu","Card",{p4,p6,p9},{3,4,5},true);
    Comanda c4(4,"Munteanu", "Cash", {p7,p8,p3},{3,2,3});
    Comanda c5(5,"Anghel","Card", {p7,p6,p5},{4,5,3},true);
    Comanda c6(6,"Olteanu", "Card", {p1,p9,p10},{5,3,4});

    c1.setTotal();
    c2.setTotal();
    c3.setTotal();
    c4.setTotal();
    c5.setTotal();
    c6.setTotal();

    Livrari liv({c1,c2,c3,c4,c5, c6},
        {"Str. Lalelelor nr. 12, bl. A3, sc. 1, et. 2, ap. 15, Bucuresti, Sector 3",
            "Str. Baba Novac nr. 22, bl. M12, sc. 1, et. 3, ap. 21, Bucuresti, Sector 3",
            "Str. Drumul Taberei nr. 84, bl. T5, sc. 2, et. 7, ap. 63, Bucuresti, Sector 6",
            "Bd. Dimitrie Cantemir nr. 15, bl. C1, sc. A, et. 4, ap. 18, Bucuresti, Sector 4",
            "Sos. Colentina nr. 120, bl. K3, sc. 3, et. 6, ap. 54, Bucuresti, Sector 2",
            "Calea 13 Septembrie nr. 98, bl. P7, sc. 1, et. 2, ap. 9, Bucuresti, Sector 5"},
            {"Popescu", "Ionescu", "Popescu", "Munteanu", "Popescu", "Olteanu"});

    c6.Proceseaza();

    std::cout<<"Bine ati venit!\n Selectati tipul de utilizator:\n[Client -> 0 | Manager -> 1 | Curier -> 2]\n";
    char tipUtilizator;
    std::cin>>tipUtilizator;
    switch (tipUtilizator) {
        case '0': std::cout<<"\nBine ati venit, dle Client! \nCum va numiti?\n";
                getNumeTotiClientii(liv);
                int inputClient;
                std::cin>>inputClient;
                std::cout<<"D."<<getNumeDupaCod(liv,inputClient)<<",";
                std::cout<<"Selectati o optiune: [istoricClient() -> 0]\n";
                std::cin>>inputClient;
                switch (inputClient) {
                    //am ales switch, pentru a fi usor de adaugat functionalitati noi
                    case 0: std::cout<<"Ati selectat istoricClient():\n";
                        IstoricClient(liv,getNumeDupaCod(liv,inputClient));
                        break;
                    default: std::cout<<"Nu exista aceasta optiune."; break;
                }
                break;

        case '1': std::cout<<"\nBine ati venit, dle Manager! Selectati o optiune:\n [aplicaReducere() -> 0 | calculeazaIncasari() -> 1]";
                char inputManager;
                std::cin>>inputManager;

                switch (inputManager) {
                    case '0': {
                        std::cout<<"Ati selectat aplicaReducere(). Alegeti ID-ul comenzii careia i se va aplica reducerea:";
                        AfiseazaToateComenzile(liv);
                        int indexComanda;
                        //preluare indexul dorit
                        std::cin>>indexComanda;
                        int procent;
                        std::cout<<"Specificati procentul cu care sa fie redusa comanda aleasa: [type: int]";
                        std::cin>>procent;

                        Comanda* comandaDeModificat=getComandaDupaID(liv,indexComanda);
                        if (comandaDeModificat != nullptr) {
                            comandaDeModificat->AplicaReducere(procent);
                            std::cout<<*comandaDeModificat;
                        }
                        else {
                            std::cout<<"Nu exista aceasta comanda.";
                        }
                        break;
                    }
                    case '1':
                        std::cout<<"Ati selectat calculeazaIncasari(). Incasarile pentru ultima livrare inregistrata sunt:\n";
                        std::cout<<CalculeazaIncasari(liv)<<" RON";
                        break;

                    default:
                        std::cout<<"Nu exista aceasta optiune."; break;
                }
                break;

        case '2': std::cout<<"\nBine ati venit, dle Curier! \nSelectati o optiune: [comenziDeLivrat() -> 0]\n";
                char inputLivrator;
                std::cin>>inputLivrator;

                switch (inputLivrator) {
                    case '0':
                        std::cout<<"Ati selectat comenziDeLivrat(). Adresele si clientii dvs de astazi sunt:\n";
                        ComenziDeLivrat(liv);
                        break;
                    default: std::cout<<"Nu exista aceasta optiune."; break;
                }
                break;

        default: std::cout<<"\nNu exista aceasta optiune.";break;
    }
    std::cout<<"\nVa uram o zi placuta!";
    return 0;
}