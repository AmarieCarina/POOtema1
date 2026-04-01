#include <iostream>
#include <cstring>
class Produs {
    //produse ale florariei: tipuri de flori
    long int IDProdus; ///cod identificare
    char* Denumire;
    long int Stoc; ///nr de produse disponibile
    char* Furnizor;
    double Pret; ///nr real reprezentand costul
public:
    ///constructor de initializare, fara parametri
    Produs() : IDProdus{0}, Stoc{0}, Pret{0.0}{
        this->Denumire=new char[1];
        Denumire[0]='\0';

        this->Furnizor=new char[1];
        Furnizor[0]='\0';

        //std::cout<<"Constructor de initializare- Produs\n";
    }
    ///constructor cu parametri, folosind lista de initializare
    Produs(long int IDProdus_, const char* Denumire_, long Stoc_, const char* Furnizor_, double Pret_)
        : IDProdus{IDProdus_}, Stoc{Stoc_}, Pret{Pret_} {

        Denumire=new char[strlen(Denumire_)+1];
        strcpy(Denumire,Denumire_);

        Furnizor=new char[strlen(Furnizor_)+1];
        strcpy(Furnizor,Furnizor_);

        //std::cout<<"Constructor cu parametri- Produs\n";
    }

    ///constructor de copiere, folosind lista de initializare
    Produs(const Produs& other)
        :IDProdus{other.IDProdus}, Stoc{other.Stoc}, Pret{other.Pret} {
        Denumire = new char[strlen(other.Denumire)+1];
        strcpy(Denumire,other.Denumire);

        Furnizor = new char[strlen(other.Furnizor)+1];
        strcpy(Furnizor,other.Furnizor);
        //std::cout<<"Constructor de copiere- Produs\n";
    }

    ///operator= de copiere
    Produs& operator=(const Produs& other) {
        if (this != &other) {
            delete[] Denumire;
            delete[] Furnizor;

            IDProdus=other.IDProdus;
            Stoc=other.Stoc;
            Pret=other.Pret;

            //alocal memorie noua si copiem sirul de caractere
            if (other.Denumire!=nullptr) {
                Denumire=new char[strlen(other.Denumire)+1];
                strcpy(Denumire,other.Denumire);
            }
            else {
                Denumire=new char[1];
                Denumire[0]='\0';
            }

            if (other.Furnizor!=nullptr) {
                Furnizor=new char[strlen(other.Furnizor)+1];
                strcpy(Furnizor,other.Furnizor);
            }
            else {
                Furnizor=new char[1];
                Furnizor[0]='\0';
            }
        }
        //std::cout<<"Operator= copiere- Produs\n";
        return *this;
    }
    void ModificaStoc(int cantitate) {
        if (this->Stoc >= cantitate) {
            this->Stoc-=cantitate;
        }
        else {
            this->Stoc=0;
            std::cout<<"Atentie! Stoc insuficient pentru produsul "<<Denumire<<"!\n";
        }
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
    inline friend std::ostream& operator-(std::ostream& os, const Produs& p) {
        os<<"Denumire produs: "<<p.Denumire<<"; ";
        return os;
    }
    //getter Pret -> folosit la CalculeazaTotal()
    //pentru a accesa o data membra privata
    double getPret() const {
        return this->Pret;
    }

    ///destructorul
    ~Produs() {
        delete[] Denumire;
        delete[] Furnizor;
        //std::cout<<"Destructor- Produs\n";
    }
};

class Comanda {
    //echivalentul unui buchet ce contine mai multe flori
    //am considerat redundant sa implementez o noua clasa Buchet, care nu ar fi adus beneficii in implementarea metodelor non-triviale

    long int IDComanda; //pentru identificare unica a comenzii
    char* NumeClient; //cine a facut comanda; util in identificare in IstoricClient()
    char* MetodaPlata; //plata la livrare sau online
    bool StatusProcesare; //procesat-> 1; neprocesat-> 0
    Produs* Produse; //produsele corespunzatoare comenzii
    int* Cantitati;
    int NrProduse; //al comenzii
    double Total; //actualizat separat prin metoda CalculeazaTotal()
    static double PragTransportGratuit; //variabila comuna intregii clase, ce determina daca se mai adauga costurile de transport la calcul sumei de platit
public:
    //constructor de initializare, fara parametri
    Comanda(): IDComanda{0}, NumeClient{nullptr}, MetodaPlata{nullptr}, StatusProcesare{false}, Produse{nullptr}, Cantitati{nullptr}, NrProduse{0}, Total{0.0} {}

    ///constructor parametrizat, folosind lista de initializare
    ///StatusProcesare - valoare implicita false
    ///Total - valoare implicita 0.0
    ///astfel, unui obiect nou i se seteaza automat totalul si statusul
    Comanda(long int IDComanda_, const char* NumeClient_, const char* MetodaPlata_, Produs* Produse_, int NrProduse_, const int* Cantitati_)
        :IDComanda{IDComanda_},StatusProcesare{false}, Produse{Produse_}, NrProduse{NrProduse_}, Total{0.0}{
        NumeClient = new char[strlen(NumeClient_)+1];
        strcpy(NumeClient,NumeClient_);

        MetodaPlata = new char[strlen(MetodaPlata_)+1];
        strcpy(MetodaPlata,MetodaPlata_);

        Produse = new Produs[NrProduse];
        Cantitati=new int[NrProduse];

        for (int i=0; i<NrProduse; i++) {
            Produse[i] = Produse_[i];
            Cantitati[i] = Cantitati_[i];
        }
        //std::cout<<"Constructor cu parametri- Comanda\n";
    }
    //constructor de copiere, cu lista de initializare
    Comanda(const Comanda& other)
        :IDComanda{other.IDComanda}, StatusProcesare{other.StatusProcesare}, NrProduse{other.NrProduse}, Total{other.Total}{
        NumeClient = new char[strlen(other.NumeClient)+1];
        strcpy(NumeClient,other.NumeClient);

        MetodaPlata = new char[strlen(other.MetodaPlata)+1];
        strcpy(MetodaPlata, other.MetodaPlata);

        Produse = new Produs[other.NrProduse];
        Cantitati = new int[other.NrProduse];

        for (int i=0; i<other.NrProduse; i++) {
            Produse[i] = other.Produse[i];
            Cantitati[i] = other.Cantitati[i];
        }
        //std::cout<<"Constructor de copiere- Comanda\n";
    }
    //operator= de copiere
    Comanda& operator=(const Comanda& other) {
        if (this != &other) { //trateaza cazul in care se incearca sa se copieze un obiect in el insusi
            delete[] NumeClient;
            delete[] MetodaPlata;
            delete[] Produse;
            delete[] Cantitati;

            IDComanda=other.IDComanda;
            StatusProcesare=other.StatusProcesare;
            NrProduse=other.NrProduse;
            Total=other.Total;

            //deep copy pentru NumeClient
            if (other.NumeClient) {
                NumeClient=new char[strlen(other.NumeClient)+1];
                strcpy(NumeClient,other.NumeClient);
            }
            else {
                NumeClient=nullptr;
            }

            if (other.MetodaPlata) {
                MetodaPlata=new char[strlen(other.MetodaPlata)+1];
                strcpy(MetodaPlata,other.MetodaPlata);
            }
            else {
                MetodaPlata=nullptr;
            }

            //deep copy pentru vectorul de Produse
            if (other.Produse) {
                Produse=new Produs[other.NrProduse];
                for (int i=0;i<other.NrProduse;i++) {
                    Produse[i] = other.Produse[i];
                }
            }
            else Produse=nullptr;

            //deep copy pentru vectorul de cantitati
            if (other.Cantitati) {
                Cantitati=new int[other.NrProduse];
                for (int i=0;i<other.NrProduse;i++) {
                    Cantitati[i] = other.Cantitati[i];
                }
            }
            else Cantitati=nullptr;
        }
        return *this;
    }
    ///reprezentare obiecte ca strings:
    ///operator<< pentru afisare, cu apel catre operatorul- pentru afisarea denumirii produsului, in loc de toate datele produsului
    friend std::ostream& operator<<(std::ostream& os, const Comanda& obj){
        os<<"\nIDComanda: "<<obj.IDComanda<<"\n";
        os<<"NumeClient: "<<obj.NumeClient<<"\n";
        os<<"MetodaPlata: "<<obj.MetodaPlata<<"\n";
        os<<"StatusProcesare: "<<obj.StatusProcesare<<"\n";
        for (int i=0;i<obj.NrProduse;i++) {
            operator-(os, obj.Produse[i]);
            os<<"Cantitate: "<<obj.Cantitati[i]<<"\n";
        }
        os<<"Total comanda: "<<obj.Total<<" RON \n";
        return os;
    }

    ///functionalitati:
    //setter, folosit pentru modificarea datelor membre din clasa dupa apelul CalculeazaTotal()
    void setTotal() { this->Total=CalculeazaTotal();}

    //getter, folosit pentur acces la datele private in cadrul apelilui CalculeazaIncasari()
    double getTotal() const{ return Total;}

    //getter, folosit pentru preluare a datelor private in apelul metodelor/functiilor:
    //IstoricClient(), ComenziDeLivrat(), getNumeTotiClientii(), getNumeDupaCod()
    const char* getNumeClient() const { return NumeClient; }

    //getter, folosit la getComandaDupaID()
    long int getID() const { return IDComanda;}

    //getter, folosit la ComenziDeLivrat()
    bool getStatus() const { return this->StatusProcesare;}

    static double getPragTransport(){ return PragTransportGratuit;}

    static void setPragtransport(double PragNou) {PragTransportGratuit=PragNou;}

    //metoda utilizata de Manager, dupa criterii proprii, avand ca utilitate modificarea totalului unei comenzi
    void AplicaReducere(int procent) {
        if (procent < 0 || procent > 100) return; // Validare minimă

        double initial = CalculeazaTotal();
        // calculam reducerea folosind double, ca să nu pierdem precizia
        double valoareReducere = (initial * (double)procent) / 100.0;

        this->Total = initial - valoareReducere;
    }

    //metoda pentru schimbare a statusului de procesare, cu modificare in obiect
    void Proceseaza() {
        if (this->StatusProcesare == false) {
            for (int i = 0; i < this->NrProduse; i++) {
                Produse[i].ModificaStoc(Cantitati[i]);
            }
            this->StatusProcesare = true;
            //std::cout<<"Succes!\n";
        }
        //else
            //std::cout<<"Comanda deja procesata!\n";
    }
    //metoda pentru actualizare a totalului de plata
    double CalculeazaTotal() const {
        double total=0;
        for (int i=0; i < NrProduse; i++) { //pentru fiecare produs din comanda
            total+=Produse[i].getPret()*Cantitati[i]; //calcul al totalului
        }
        int taxaTransport = 15;
        return total+taxaTransport;
    }
    static void AfiseazaPoliticaTransport() {
        std::cout<<"\n--Politica Florariei--\n";
        std::cout<<"Transportul este GRATUIT pentru comenzi de peste "<<PragTransportGratuit<<" RON.\n";
        std::cout<<"Taxa de transport este de 15 RON.\n";
    }


    //destructorul implicit
    ~Comanda() {
        delete[] NumeClient;
        delete[] MetodaPlata;
        delete[] Produse;
        delete[] Cantitati;
    }

};
//inafara clasei Comanda, initializam variabila statica
double Comanda::PragTransportGratuit=150.0;

class Livrari {
    //comenzile acumulate in ziua curenta, continand date utile curierului
    Comanda* Comenzi; //obiecte de tip Comanda;
    //conditie de apartenenta: campul statusProcesare == true
    char** Adrese; //adresele la care trebuie facuta livrarea
        //corespondenta indicilor cu *Comenzi este asigurata, pentru asociere directa
    int NrComenzi; //dintr o livrare neverificata de ComenziDeLivrat()
    char** NumeClienti; //numele clientilor
public:
    //constructor parametrizat, cu lista de initializare
    Livrari(const Comanda* Comenzi_, const char** Adrese_, const char** NumeClienti_, int NrComenzi_)
        :NrComenzi {NrComenzi_} {
        Comenzi = new Comanda[NrComenzi_];
        Adrese = new char*[NrComenzi_];
        NumeClienti = new char*[NrComenzi_];

        for (int i=0;i<NrComenzi;i++) {
            Comenzi[i] = Comenzi_[i];
            Adrese[i] = new char[strlen(Adrese_[i])+1];
            strcpy(Adrese[i], Adrese_[i]);
            NumeClienti[i] = new char[strlen(NumeClienti_[i])+1];
            strcpy(NumeClienti[i], NumeClienti_[i]);
        }
    }

    Livrari& operator=(const Livrari& other) {
        if (this!=&other) {
            for (int index = 0; index < NrComenzi; index++) {
                delete[] Adrese[index];
                delete[] NumeClienti[index];
            }
            delete[] Comenzi;
            delete[] Adrese;
            delete[] NumeClienti;

            //valoare primitiva
            NrComenzi=other.NrComenzi;

            //alocam memorie noua
            this->Comenzi=new Comanda[other.NrComenzi];
            this->Adrese=new char*[other.NrComenzi];
            this->NumeClienti=new char*[other.NrComenzi];

            //deep copy pentru fiecare element
            if (other.NumeClienti) {
                for (int i=0;i<other.NrComenzi;i++) {
                    Comenzi[i] = other.Comenzi[i];

                    Adrese[i]=new char[strlen(other.Adrese[i])+1];
                    strcpy(Adrese[i], other.Adrese[i]);

                    NumeClienti[i]=new char[strlen(other.NumeClienti[i])+1];
                    strcpy(NumeClienti[i], other.NumeClienti[i]);
                }
            }
            else NumeClienti=nullptr;
        }
        return *this;
    }

    //functie desemnata Clientului, ce apeleaza operatorul<< de afisare
    static void IstoricClient(const Livrari& Livrare, const char* Nume) {
        for (int i=0;i<Livrare.NrComenzi; i++) {
            if (strcmp(Livrare.Comenzi[i].getNumeClient(), Nume)==0) {
                operator<<(std::cout,Livrare.Comenzi[i]);
            }
        }
    }
    //functie prieten, desemnata Managerului, pentru analiza incasarilor zilnice
    static double CalculeazaIncasari(const Livrari& Livrare) {
        double total=0;
        for (int i=0; i < Livrare.NrComenzi; i++) {
            total+=Livrare.Comenzi[i].getTotal();
        }
        return total;
    }

    //functie prieten, desemnata Curierului, pentru a configurarea traseului zilnic
    static void ComenziDeLivrat(const Livrari& Livrare) {
        for (int index=0; index<Livrare.NrComenzi; index++) {
            if (Livrare.Comenzi[index].getStatus()==true) {
                std::cout<<Livrare.Comenzi[index].getNumeClient()<<" | ";
                std::cout<<Livrare.Adrese[index]<<std::endl;
                //nu s a folosit supraincarcarea operatorului<< pentru ca am fi avut nevoie de un al treilea parametru: indexul comenzii
            }
        }
    }

    //functie prieten pentru afisarea optiunilor
    //faciliteaza meniul interactiv
    friend void getNumeTotiClientii(const Livrari& livrare) {
        for (int index=0; index<livrare.NrComenzi; index++) {
            std::cout<<" * "<<livrare.Comenzi[index].getNumeClient()<<" -> "<<index<<"\n";
        }
        std::cout<<"\n";
    }

    //functie pentru identificare NumeClient, in functie de inputul minimalist al utilizatorului
    friend const char* getNumeDupaCod(const Livrari& livrare, int cod) {
        if (cod>=0 && cod<livrare.NrComenzi) {
            return livrare.Comenzi[cod].getNumeClient();
        }
        return "Necunoscut";
    }

    //functie pentru afisarea optiunilor
    //faciliteaza meniul interactiv
    friend void AfiseazaToateComenzile(const Livrari& livrare) {
        for (int index=0; index<livrare.NrComenzi; index++) {
            operator<<(std::cout,livrare.Comenzi[index]);
        }
    }
    //functie pentru identificare Comanda, in functie de inputul minimalist al utilizatorului
    //returneaza pointer catre un obiect de tip comanda, pentru a trata cazul in care inputul utilizatorului este invalid
    friend Comanda* getComandaDupaID(Livrari& livrare, const int ID) {
        for (int index=0; index<livrare.NrComenzi; index++) {
            if (livrare.Comenzi[index].getID()==ID) {
                return &livrare.Comenzi[index]; //returneaza adresa obiectului Comanda
            }
        }
        return nullptr; //daca nu s a gasit ID-ul
        //implementat pentru corectitudinea definirii functiei
        //tratarea cazului se face in main, cu mesaj corespunzator
    }
    ~Livrari() {
        for (int index=0; index<NrComenzi; index++) {
            delete[] Adrese[index];
            delete[] NumeClienti[index];
        }
        delete[] Adrese;
        delete[] NumeClienti;
        delete[] Comenzi;
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

    Produs pr1[]={p1,p6}; int ct1[]={7,3};
    Comanda c1(1, "Popescu", "Card", pr1, 2, ct1);

    Produs pr2[]={p3,p5,p10}; int ct2[]={5,4,3};
    Comanda c2(2,"Ionescu", "Cash", pr2, 3, ct2);

    Produs pr3[]={p4,p6,p9}; int ct3[]={3,4,5};
    Comanda c3(3,"Popescu","Card",pr3,3,ct3);

    Produs pr4[]={p7,p8,p3}; int ct4[]={3,2,3};
    Comanda c4(4,"Munteanu", "Cash", pr4,3, ct4);

    Produs pr5[]={p7,p6,p5}; int ct5[]={4,5,3};
    Comanda c5(5,"Anghel","Card", pr5,3,ct5);

    Produs pr6[]={p1,p9,p10}; int ct6[]={5,3,4};
    Comanda c6(6,"Olteanu", "Card", pr6,3,ct6);

    //actualizeaza totalul pentru comenzile curente:
    c1.setTotal();  c2.setTotal();
    c3.setTotal();  c4.setTotal();
    c5.setTotal();  c6.setTotal();

    //schimbare StatusProcesare al unei comenzi
    c6.Proceseaza();
    c5.Proceseaza();
    c3.Proceseaza();


    //comenzile pentru ziua curenta
    Comanda Comenzi_zi[]={c1,c2,c3,c4,c5,c6};
    const char* Adrese[]={
        "Str. Lalelelor nr. 12, bl. A3, sc. 1, et. 2, ap. 15, Bucuresti, Sector 3",
        "Str. Baba Novac nr. 22, bl. M12, sc. 1, et. 3, ap. 21, Bucuresti, Sector 3",
        "Str. Drumul Taberei nr. 84, bl. T5, sc. 2, et. 7, ap. 63, Bucuresti, Sector 6",
        "Bd. Dimitrie Cantemir nr. 15, bl. C1, sc. A, et. 4, ap. 18, Bucuresti, Sector 4",
        "Sos. Colentina nr. 120, bl. K3, sc. 3, et. 6, ap. 54, Bucuresti, Sector 2",
        "Calea 13 Septembrie nr. 98, bl. P7, sc. 1, et. 2, ap. 9, Bucuresti, Sector 5"
    };
    const char* Clienti[]={"Popescu", "Ionescu", "Popescu", "Munteanu", "Popescu", "Olteanu"};
    Livrari liv(Comenzi_zi, Adrese, Clienti,6);



    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////  M E N I U    I N T E R A C T I V  //////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout<<"--Bine ati venit!--\n";
    Comanda::AfiseazaPoliticaTransport();
    std::cout<<"\nSelectati tipul de utilizator:\n[Client -> 0 | Manager -> 1 | Curier -> 2]\n\n";
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
                int inputClient; std::cin>>inputClient;

                //afisare corespunzatoare
                std::cout<<"D."<<getNumeDupaCod(liv,inputClient)<<",";
                //urmatoarea optiune
                std::cout<<"selectati o optiune: [istoricClient() -> 0]\n";

                //input optiunea utilizatorului
                int optiuneClient; std::cin>>optiuneClient;

                //tratare toate cazurile de input
                //am ales switch, pentru a fi usor de adaugat functionalitati noi
                switch (optiuneClient) {
                    //cazul primei functii
                    case 0: std::cout<<"Ati selectat istoricClient():\n";
                        Livrari::IstoricClient(liv,getNumeDupaCod(liv,inputClient));
                        break;
                    //orice alt caz
                    default: std::cout<<"Nu exista aceasta optiune."; break;
                }
                break;

        //cazul Manager
        case '1': std::cout<<"Bine ati venit, dle Manager! Selectati o optiune:\n [aplicaReducere() -> 0 | calculeazaIncasari() -> 1 | setPragTransport() -> 2]\n\n";
                //preluare input utilizator - optiunea dorita
                char inputManager; std::cin>>inputManager;

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
                        std::cout<<"Specificati procentul cu care sa fie redusa comanda aleasa: [type: int]\n\n";
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
                        std::cout<<"-----"<<Livrari::CalculeazaIncasari(liv)<<" RON\n";
                        break;
                    case '2':
                        std::cout<<"Ati selectat setPragTransport(). Pragul actual este "<<Comanda::getPragTransport()<<" RON.\n";
                        std::cout<<"Introduceti noul prag:\n ";
                        double PragNou;
                        std::cin>>PragNou;
                        Comanda::setPragtransport(PragNou);
                        std::cout<<"Pragul actual este "<<Comanda::getPragTransport()<<".\n";
                        break;

                    //pentru orice alt input
                    default:
                        std::cout<<"Nu exista aceasta optiune."; break;
                }
                break;

        //cazul Curier
        case '2': std::cout<<"Bine ati venit, dle Curier! \nSelectati o optiune: [comenziDeLivrat() -> 0]\n";

                //preluare optiune dorita
                char inputLivrator; std::cin>>inputLivrator;

                //pentru toate cazurile de input
                switch (inputLivrator) {
                    //cazul primei functii
                    case '0':
                        std::cout<<"Ati selectat comenziDeLivrat(). Adresele si clientii dvs de astazi sunt:\n";
                        Livrari::ComenziDeLivrat(liv);
                        break;
                    //pentru orice alt input
                    default: std::cout<<"Nu exista aceasta optiune."; break;
                }
                break;

            //pentru orice alt input
        default: std::cout<<"\nNu exista aceasta optiune.";break;
    }
    std::cout<<"\nVa uram o zi placuta!\nPentru alte functionalitati, va rugam sa rulati din nou programul."; //mesaj de incheiere
    return 0;
}