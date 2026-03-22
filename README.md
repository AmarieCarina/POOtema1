## Tema 1 | Florarie
Student: Amarie Elena Carina
2026

### Descrierea claselor implementate
Presupunem existenta unei florarii care vinde buchete personalizate, trimise exclusiv prin livrare la adresa. Florile sunt reprezentate de obiecte din clasa `Produs`, avand specificate un identificator unic, denumirea florii, furnizorul, pretul si stocul disponibil. Clientul isi alege florile dorite si lanseaza o comanda, iar produsul final este un buchet cu toate aceste produse. O comanda poate avea un singur buchet; daca clientul isi doreste mai multe buchete, poate da mai multe comenzi. Comenzile sunt obiecte ale clasei `Comanda`, ce contine florile dorite, cantitatea dorita din fiecare produs, suma totala de platit, metoda de plata si statusul comenzii: procesat/neprocesat. Gestiunea comenzilor se face in functie de ziua in care a fost plasata comanda. Un obiect al clasei `Livrare` reprezinta totalul comenzilor plasate intr o zi, ce contine informatii utile pentru curier: comenzile destinate livrarii din ziua respectiva (depinzand de statusul comenzii), adresele de livrare corespunzatoare si numele clientilor. 

---

### Functionalitati
Functionalitatile proiectului depind de tipul utilizatorului. Astfel, pentru Client, Manager si Curier, sunt listate optiunile de functionare in cadrul unui meniu interactiv.
  - **Client**
     - istoricul comenzilor plasate, in functie de numele clientului
  - **Manager**
     - aplica reduceri anumitor comenzi, cu un procent dat (criteriile de acordare a reducerii sunt stabilite de promotia in curs a florariei)
     - calculeaza totalul de incasari pentru ziua curenta
  - **Curier**
     - comenzile gata de livrat, impreuna cu toate informatiile necesare

---

### Rulare
Datele de intrare sunt specificate in functia `int main()` a programului, acestea fiind: produsele de pe stoc (obiecte ale clasei `Produs`), cu atributele obligatorii specificate, comenzile lansate in ziua curenta (obiecte ale clasei `Comanda`), si o lista de livrari de efectuat (obiecte ale clasei `Livrare`), bazata pe comenzile procesate. La rulare, utilizatorul isi introduce optiunile, conform indicatiilor afisate.  

---

## Lista de cerinte
- [x] Nume proiect
- [x] Scurtă descriere a temei alese
- [x] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi; moștenirile nu se iau în considerare aici
- [x] constructori de inițializare cu parametri pentru fiecare clasă
- [x] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
- [x] `operator<<` pentru toate clasele pentru afișare (`std::ostream`) folosind compunere de apeluri cu `operator<<`
- [x] cât mai multe `const` (unde este cazul) și funcții `private`
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
- [x] scenariu de utilizare **cu sens** a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
- [ ] minim 52-60% din codul propriu să fie C++, `.gitattributes` configurat corect
- [ ] tag de `git`: de exemplu `v0.1`
- [ ] serviciu de integrare continuă (CI) cu **toate bifele**; exemplu: GitHub Actions
- [ ] code review #1 2 proiecte


## License
The project is licensed under [AGPLv3](LICENSE).
The [template repository](https://github.com/mcmarius/oop-template) itself is licensed under [Unlicense](LICENSE.template).
