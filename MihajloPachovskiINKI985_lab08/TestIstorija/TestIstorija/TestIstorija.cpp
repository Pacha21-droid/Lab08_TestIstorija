//MIHAJLO PACHOVSKI INKI985
#include <iostream>
#include<fstream>
#include<string>
#include <chrono>
#include <ctime>
using namespace std;
//Definiran student
struct student {
    string ime, prezime, indeks;
};
//Funkcija za dobivanje na vreme
string get_current_time() {
    auto now = chrono::system_clock::now();
    time_t now_C = chrono::system_clock::to_time_t(now);
    return ctime(&now_C);
}
//Vnesuvanje na podatoci za studentot
void vnesNaStudent(student&Student){
    cout<< "Vnesi ime: ";      cin>> Student.ime;
    cout<< "Vnesi prezime: ";  cin>>Student.prezime;
    do { cout << "Vnesi indeks: "; cin >> Student.indeks; } while (Student.indeks.size() != 3);
}
//Vnesuvanje na studenti vo spisok
void dodaj_student_vo_spisok(student& student,int poeni, int ocenka) {
    static int n = 1;
    string pochetok = get_current_time();
    string kraj = get_current_time();
    ofstream out("Studenti", ios::app);
    if (out.is_open()) {
        out << "Ime: " << student.ime << "\n";
        out << "Prezime: " << student.prezime << "\n";
        out << "Indeks: " << student.indeks << "\n";
        out << "Vreme na start: " << pochetok;
        out << "Vreme na kraj: " << kraj;
        out << "Poeni: " << poeni << "\n";
        out << "Ocenka: " << ocenka << "\n\n";
        out.close();
        n++;
    }
    else {
        cout << "Greshka \n";
    }
}
//Definiranje na odgovorite vo 4ki
char odgovoriPrvi[4] = {'A','C','B','A'};
char odgovoriVtori[4] = { 'B','B','B','A' };
char odgovoriTreti[4] = { 'A','C','C','A' };
//Zapishuvanje na odgovori
void zapishiOdgovori(fstream &file,char odg,int broj) {
    file << broj << "- " << odg << " " << endl;
}
//Proverka na odgovorite
float proveriOdgovori(char odg, int brojP) {
        if (brojP <= 4) {
        if (odg == odgovoriPrvi[brojP - 1]) {return 7;}}
        else if (brojP > 4 && brojP <= 8) {
        if (odg == odgovoriVtori[brojP - 5]) {return 8;}}
        else if (brojP > 8 && brojP <= 12) {
         if (odg == odgovoriTreti[brojP - 9]) { return 10;}}}
//Funkcija za proverka na vnes i zapishuvanje na odgovorite
float proveriVnes(int brojP, fstream& file) {
    char odg = ' ';
    if (brojP <= 12) {
        do {
            cout << "Vashiot odgovor: ";
            cin >> odg;
        } while (odg != 'A'&& odg != 'B'&& odg != 'C');
        zapishiOdgovori(file, odg, brojP);
    }
 return proveriOdgovori(odg,brojP);}
//Funkcija za bodiranje
int bodiranje(float poeni) {
    int ocenka = 0;
    if (poeni >= 0 && poeni <= 50)
       ocenka= 5;
    else if (poeni >= 51 && poeni <= 60)
        ocenka = 6;
    else if (poeni >= 61 && poeni <= 70)
        ocenka = 7;
    else if (poeni >= 71 && poeni <= 80)
        ocenka = 8;
    else if (poeni >= 81 && poeni <= 90)
        ocenka = 9;
    else if (poeni >= 91 && poeni <= 100)
        ocenka = 10;
    return ocenka;
}
//Funkcija za pechatenje na odgovori
void answersTable() {
    cout << "Tocni odgovori na prasanjata se:" << endl;
    for (int i = 1; i <= 12; i++) {
        if (i <= 4)
            cout << i << ". " << odgovoriPrvi[i - 1] << endl;
        else if (i > 4 && i <= 8)
            cout << i << ". " << odgovoriVtori[i - 5] << endl;
        else if (i > 8 && i <= 12)
            cout << i << ". " << odgovoriTreti[i - 9]<<endl;
    }
}
//Da se proveri dali polagal
inline bool dali_studentot_polagal(const string& name)
{
    bool polagal;
    ifstream file(name);
    if (!file)
        polagal = true;
    else polagal = false;
    return polagal;
}
bool proveriStudent(student& Student,const string filename) {
    
    ifstream in(filename);
    if (in) {
        cout << "Vekje si polagal! \n";
        return false;
    }
    return true;
}
int main()
{
    fstream file, test;
    student lice;
    string prasanje;
    int brojnaprasanje = 1;
    float poeni = 0;
    int ocenka = bodiranje(poeni);
    vnesNaStudent(lice);
    // Kreiranje na datotekata so ime i prezime na studentot 
    const string filename = lice.ime + lice.prezime + "INKI" + lice.indeks;
    if (proveriStudent(lice, filename)) {
        ;
        file.open(filename.c_str(), ios::out);
        file.close();
    }
    else { return 0; }
    // Otvoranje na datotekata so prasanja i prevzemanje na soodvetnoto prasanje i negovite odgovori
    test.open("Prashanja.txt", ios::in);
    while (getline(test, prasanje)) {
        for (int i = 0; i < prasanje.size(); i++) {
            if (prasanje[i] == ';') {
                cout << endl;
                i++;}
            else
                cout << prasanje[i];}
        cout << endl;
        file.open(filename.c_str(), ios::app);
        poeni += proveriVnes(brojnaprasanje, file);
        file.close();
        brojnaprasanje++;}
    test.close();
    dodaj_student_vo_spisok(lice, poeni, ocenka);
    answersTable();
    return 0;
}