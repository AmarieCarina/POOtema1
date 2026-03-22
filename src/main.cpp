#include <iostream>
#include <vector>
#include <string>
class Produs {
    //produse ale florariei: tipuri de flori
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

    ///operator<<, functie prieten
    friend std::ostream& operator<<(std::ostream& os, const Produs& p) {
        os<<"\nIDProdus: "<<p.IDProdus<<"\n";
        os<<"Denumire: "<<p.Denumire<<"\n";
        os<<"Stoc: "<<p.Stoc<<"\n";
        os<<"Furnizor: "<<p.Furnizor<<"\n";
        os<<"Pret: "<<p.Pret<<"\n";
        return os;
    }
    //operator-, definit special pentru afisarea denumirii unui produs, in cadrul afisarii clasei Comanda
    //am folosit operatorul - pentru a exersa supraincarcarea operatorilor
    //simbolul e folosit pentru a sugera "micsorarea" outputului de afisare a intregului obiect, comparativ cu op<<
    friend std::ostream& operator-(std::ostream& os, const Produs& p) {
        os<<"Denumire produs: "<<p.Denumire<<"; ";
        return os;
    }
    //getter Pret -> folosit la CalculeazaTotal()
    //pentru a accesa o data membra privata intr o functie externa
    double getPret() const {
        return this->Pret;
    }

    ///destructorul implicit
    ~Produs() {
        //std::cout<<"Destructor- Produs\n";
    }
};

class Comanda {
    //echivalentul unui buchet ce contine mai multe flori
    //am considerat redundant sa implementez o noua clasa Buchet, care nu ar fi adus beneficii in implementarea metodelor non-triviale

    long int IDComanda; //pentru identificare unica a comenzii
    std::string NumeClient; //cine a facut comanda; util in identificare in IstoricClient()
    std::string MetodaPlata; //plata la livrare sau online
    bool StatusProcesare; //procesat-> 1; neprocesat-> 0
    std::vector<Produs> Produse; //produsele corespunzatoare comenzii
    std::vector<int> Cantitati;
    //vector de intregi cu cantitati- un buchet nu poate avea decat un numar intreg de flori
    double Total; //actualizat separat prin metoda CalculeazaTotal()
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
    ///astfel, unui obiect nou i se seteaza automat totalul si statusul
    Comanda(const long int IDComanda_, const std::string& NumeClient_, const std::string& MetodaPlata_, const std::vector<Produs>& Produse_, const std::vector<int>& Cantitati_, const bool StatusProcesare_=false, const double Total_=0.0)
        :IDComanda{IDComanda_},NumeClient{NumeClient_},MetodaPlata{MetodaPlata_},StatusProcesare{StatusProcesare_}, Produse{Produse_},Cantitati {Cantitati_}, Total{Total_}{
        //std::cout<<"Constructor cu parametri- Comanda\n";
    }
    //constructor de copiere, cu lista de initializare
    Comanda(const Comanda& other)
        :IDComanda{other.IDComanda}, NumeClient{other.NumeClient}, MetodaPlata{other.MetodaPlata}, StatusProcesare{other.StatusProcesare}, Produse{other.Produse}, Cantitati{other.Cantitati}, Total{other.Total}{
        //std::cout<<"Constructor de copiere- Comanda\n";
    }
    //operator= de copiere
    Comanda& operator=(const Comanda& other) {
        if (this == &other) { //trateaza cazul in care se incearca sa se copieze un obiect in el insusi
            return *this; //se ignora
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
    ///reprezentare obiecte ca strings:
    ///operator<< pentru afisare, cu apel catre operatorul- pentru afisarea denumirii produsului, in loc de toate datele produsului
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
    double CalculeazaTotal() const; //prototipul functiei externe

    //setter, folosit pentru modificarea datelor membre din clasa dupa apelul CalculeazaTotal()
    void setTotal() {
        this->Total=CalculeazaTotal();
    }

    //getter, folosit pentur acces la datele private in cadrul apelilui CalculeazaIncasari()
    double getTotal() const{
        return Total;
    }

    //getter, folosit pentru preluare a datelor private in apelul metodelor/functiilor:
    //IstoricClient(), ComenziDeLivrat(), getNumeTotiClientii(), getNumeDupaCod()
    const std::string& getNumeClient() const {
        return NumeClient;
    }

    //getter, folosit la getComandaDupaID()
    long int getID() const {
        return IDComanda;
    }

    //getter, folosit la ComenziDeLivrat()
    bool getStatus() const {
        return this->StatusProcesare;
    }

    void AplicaReducere(int procent); //prototip al unei functii externe

    //metoda pentru schimbare a statusului de procesare, cu modificare in obiect
    void Proceseaza() {
        if (this->StatusProcesare == false) {
            this->StatusProcesare = true;
            //std::cout<<"Succes!\n";
        }
        //else
            //std::cout<<"Comanda deja procesata!\n";
    }

    //destructorul implicit
    ~Comanda() = default;

};
//metoda pentru actualizare a totalului de plata
double Comanda::CalculeazaTotal() const {
    double total=0;
    for (size_t i=0; i < Produse.size(); i++) { //pentru fiecare produs din comanda
        total+=Produse[i].getPret()*Cantitati[i]; //calcul al totalului
    }
    return total;
}

//metoda utilizata de Manager, dupa criterii proprii, avand ca utilitate modificarea totalului unei comenzi
void Comanda::AplicaReducere(int procent) {
    const double initial = CalculeazaTotal();
    Total = initial-initial*procent/100.0;
}

class Livrari {
    //comenzile acumulate in ziua curenta, continand date utile curierului
    std::vector<Comanda>Comenzi;
        //vector continand obiecte de tip Comanda; conditie de apartenenta: campul statusProcesare == true
    std::vector<std::string>Adrese;
        //vector continand adresele la care trebuie facuta livrarea
    std::vector<std::string>NumeClienti;
        //vector continand numele clientilor
public:
    //constructor parametrizat, cu lista de initializare
    Livrari(const std::vector<Comanda>& Comenzi_, const std::vector<std::string>& Adrese_, const std::vector<std::string>& NumeClienti_)
        :Comenzi{Comenzi_}, Adrese{Adrese_}, NumeClienti {NumeClienti_} {}

    //functie prieten, desemnata Clientului, ce apeleaza operatorul<< de afisare
    friend void IstoricClient(const Livrari& Livrare, const std::string& Nume) {
        for (const Comanda& c : Livrare.Comenzi) {
            if (c.getNumeClient()==Nume) {
                operator<<(std::cout,c);
            }
        }
    }
    //functie prieten, desemnata Managerului, pentru analiza incasarilor zilnice
    friend double CalculeazaIncasari(const Livrari& livrare) {
        double total=0;
        for (const Comanda& c:livrare.Comenzi) {
            total+=c.getTotal();
        }
        return total;
    }

    //functie prieten, desemnata Curierului, pentru a configurarea traseului zilnic
    friend void ComenziDeLivrat(const Livrari& livrare) {
        for (size_t index=0; index<livrare.Comenzi.size(); index++) {
            if (livrare.Comenzi[index].getStatus()==true) {
                std::cout<<livrare.Comenzi[index].getNumeClient()<<" | ";
                std::cout<<livrare.Adrese[index]<<std::endl;
            }
        }
    }

    //functie pentru afisarea optiunilor
    //faciliteaza meniul interactiv
    friend void getNumeTotiClientii(const Livrari& livrare) {
        for (size_t index=0; index<livrare.Comenzi.size(); index++) {
            std::cout<<" * "<<livrare.Comenzi[index].getNumeClient()<<" -> "<<index<<"\n";
        }
        std::cout<<"\n";
    }

    //functie pentru identificare NumeClient, in functie de inputul minimalist al utilizatorului
    friend std::string getNumeDupaCod(const Livrari& livrare, const int cod) {
        return livrare.Comenzi.at(cod).getNumeClient();
    }

    //functie pentru afisarea optiunilor
    //faciliteaza meniul interactiv
    friend void AfiseazaToateComenzile(const Livrari& livrare) {
        for (size_t index=0; index<livrare.Comenzi.size(); index++) {
            operator<<(std::cout,livrare.Comenzi[index]);
        }
    }
    //functie pentru identificare Comanda, in functie de inputul minimalist al utilizatorului
    //returneaza pointer catre un obiect de tip comanda, pentru a trata cazul in care inputul utilizatorului este invalid
    friend Comanda* getComandaDupaID(Livrari& livrare, const int ID) {
        for (size_t index=0; index<livrare.Comenzi.size(); index++) {
            if (livrare.Comenzi[index].getID()==ID) {
                return &livrare.Comenzi[index]; //returneaza adresa obiectului Comanda
            }
        }
        return nullptr; //daca nu s a gasit ID-ul
        //implementat pentru corectitudinea definirii functiei
        //tratarea cazului se face in main, cu mesaj corespunzator
    }

};

int main() {
    //datele membre:
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

    //actualizeaza totalul pentru comenzile curente:
    c1.setTotal();
    c2.setTotal();
    c3.setTotal();
    c4.setTotal();
    c5.setTotal();
    c6.setTotal();

    //comenzile pentru ziua curenta
    Livrari liv({c1,c2,c3,c4,c5, c6},
        {"Str. Lalelelor nr. 12, bl. A3, sc. 1, et. 2, ap. 15, Bucuresti, Sector 3",
            "Str. Baba Novac nr. 22, bl. M12, sc. 1, et. 3, ap. 21, Bucuresti, Sector 3",
            "Str. Drumul Taberei nr. 84, bl. T5, sc. 2, et. 7, ap. 63, Bucuresti, Sector 6",
            "Bd. Dimitrie Cantemir nr. 15, bl. C1, sc. A, et. 4, ap. 18, Bucuresti, Sector 4",
            "Sos. Colentina nr. 120, bl. K3, sc. 3, et. 6, ap. 54, Bucuresti, Sector 2",
            "Calea 13 Septembrie nr. 98, bl. P7, sc. 1, et. 2, ap. 9, Bucuresti, Sector 5"},
            {"Popescu", "Ionescu", "Popescu", "Munteanu", "Popescu", "Olteanu"});

    //schimbare StatusProcesare al unei comenzi
    c6.Proceseaza();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////  M E N I U    I N T E R A C T I V  //////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout<<"Bine ati venit!\n Selectati tipul de utilizator:\n[Client -> 0 | Manager -> 1 | Curier -> 2]\n";
    //input optiunea utilizatorului
    char tipUtilizator;
    std::cin>>tipUtilizator;

    //pentru toate variantele de input:
    switch (tipUtilizator) {
        //cazul Client
        case '0': std::cout<<"Bine ati venit, dle Client! \nCum va numiti?\n";
                //afisare toate numele de clienti disponibile, pentru a fi mai usor utilizatorului sa aleaga
                getNumeTotiClientii(liv);

                //input optiunea utilizatorului
                int inputClient;
                std::cin>>inputClient;

                //afisare corespunzatoare
                std::cout<<"D."<<getNumeDupaCod(liv,inputClient)<<",";
                //urmatoarea optiune
                std::cout<<"selectati o optiune: [istoricClient() -> 0]\n";

                //input optiunea utilizatorului
                std::cin>>inputClient;

                //tratare toate cazurile de input
                //am ales switch, pentru a fi usor de adaugat functionalitati noi
                switch (inputClient) {
                    //cazul primei functii
                    case 0: std::cout<<"Ati selectat istoricClient():\n";
                        IstoricClient(liv,getNumeDupaCod(liv,inputClient));
                        break;
                    //orice alt caz
                    default: std::cout<<"Nu exista aceasta optiune."; break;
                }
                break;

        //cazul Manager
        case '1': std::cout<<"Bine ati venit, dle Manager! Selectati o optiune:\n [aplicaReducere() -> 0 | calculeazaIncasari() -> 1]";
                //preluare input utilizator - optiunea dorita
                char inputManager;
                std::cin>>inputManager;

                //pentru toate cazurile de input
                switch (inputManager) {
                    //cazul primei functii
                    case '0': {
                        std::cout<<"Ati selectat aplicaReducere(). Alegeti ID-ul comenzii careia i se va aplica reducerea:";

                        //afisare toate comenzile curente, pentru a alege mai usor
                        AfiseazaToateComenzile(liv);

                        //preluare indexul dorit
                        int indexComanda;
                        std::cin>>indexComanda;

                        //preluare procentul dorit
                        int procent;
                        std::cout<<"Specificati procentul cu care sa fie redusa comanda aleasa: [type: int]";
                        std::cin>>procent;

                        //gasire comanda corespunzatoare indexului dat
                        Comanda* comandaDeModificat=getComandaDupaID(liv,indexComanda);

                        //tratarea cazului in care indexul comenzii nu exista
                        if (comandaDeModificat != nullptr) {
                            //comanda este trimisa mai departe catre metoda definita
                            comandaDeModificat->AplicaReducere(procent);
                            //afisare corespunzatoare
                            std::cout<<*comandaDeModificat;
                        }
                        else {
                            std::cout<<"Nu exista aceasta comanda.";
                        }
                        break;
                    }
                    //cazul pentru a doua functie implementata
                    case '1':
                        std::cout<<"Ati selectat calculeazaIncasari(). Incasarile totale pentru ultima livrare inregistrata sunt:\n";
                        //apelul functiei, cu mesaj corespunzator
                        std::cout<<CalculeazaIncasari(liv)<<" RON";
                        break;

                    //pentru orice alt input
                    default:
                        std::cout<<"Nu exista aceasta optiune."; break;
                }
                break;

        //cazul Curier
        case '2': std::cout<<"Bine ati venit, dle Curier! \nSelectati o optiune: [comenziDeLivrat() -> 0]\n";

                //preluare optiune dorita
                char inputLivrator;
                std::cin>>inputLivrator;

                //pentru toate cazurile de input
                switch (inputLivrator) {
                    //cazul primei functii
                    case '0':
                        std::cout<<"Ati selectat comenziDeLivrat(). Adresele si clientii dvs de astazi sunt:\n";
                        ComenziDeLivrat(liv);
                        break;
                    //pentru orice alt input
                    default: std::cout<<"Nu exista aceasta optiune."; break;
                }
                break;

            //pentru orice alt input
        default: std::cout<<"\nNu exista aceasta optiune.";break;
    }
    std::cout<<"\nVa uram o zi placuta!"; //mesaj de incheiere
    return 0;
}