//Dinaminiai dvigubai susieti sąrašai
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

string pavard; //pavarde;
string rungt; //rungtis
int vieta;//vieta
string pratimas; //pratimo pavadinimas
int trukm; //pratimo trukme

class ROD2
{
public:
    string pratimas; //pratimo pavadinimas
    int trukm; //pratimo trukme
    ROD2* p2Next; //is eiles (rodyklė i sekanti pratimu sarašo elementa)
    ROD2* pPrevious;
public:
    //-------------------------------------------------------------
    ROD2(string spratimas, int strukm) : //konstruktorius
        pratimas(spratimas), trukm(strukm), p2Next(NULL), pPrevious(NULL)
    { }
    //-------------------------------------------------------------
    void RodytiElementa() //sąrašo elemento išvedimas
    {
        cout << left << setw(14) << pratimas << "|" << trukm << " min" << endl;
    }
    //-------------------------------------------------------------
}; //klasės ROD2 pabaiga


class ROD1
{
public:
    string pavard; //sportininko pavarde
    string rung; //rungtis
    int vieta; //sportininko vieta sarase
    ROD1* pPrevious;//prieš tai einančio elemento rodyklė sąraše
    ROD1* pNext; //Sportininku sarasas

    ROD1* ppPrevious;//prieš tai einančio elemento rodyklė sąraše
    ROD1* ppNext; //Sportininku sarasas

    ROD2* p2Next; //surūšiuotas pagal trukme;
    ROD2* p2First; // rodyklė į pirmą elementa;

public:
    //-------------------------------------------------------------
    ROD1(string spavard, string srungt, int svieta) : //konstruktorius
        pavard(spavard), rung(srungt), vieta(svieta), pNext(NULL), p2Next(NULL), p2First(NULL), pPrevious(NULL), ppNext(NULL), ppPrevious(NULL)
    { }
    //-------------------------------------------------------------
    void RodytiElementa() //sąrašo elemento išvedimas
    {
        cout << left << setw(12) << pavard << "|" << setw(12) << rung << "|" << setw(5) << vieta << endl;
    }
    bool changeTime(string pratimas, int trukm)
    {
        ROD2* pCurrent = p2First;
        while (true) //ieškoma tol kol randamas nurodytas elementas,
        {
            if (pCurrent->pratimas == pratimas)
            {
                pCurrent->trukm = trukm;
                return true;
                break;
            }
            pCurrent = pCurrent->p2Next; //pereinama prie kito sąrašo elemento
            if (pCurrent == NULL)
            {
                return false; //jeigu perinko visą sąrašą ir nieko nerado, gražina false reikšmę ir baigia vykdyti funkcijos komandas
                break;
            }
        }
    }


    bool addExercise(string pratimas, int trukm)
    {
        ROD2* pNewLink = new ROD2(pratimas, trukm);
        ROD2* pPrevious = NULL;
        ROD2* pCurrent = p2First;
        while (pCurrent != NULL && trukm > pCurrent->trukm)
        {
            pPrevious = pCurrent;
            pCurrent = pCurrent->p2Next;
        }
        if (pPrevious == NULL)
            p2First = pNewLink;
        else
            pPrevious->p2Next = pNewLink;
        pNewLink->p2Next = pCurrent;
        return true;
    }
    void displayPratimai()
    {

        ROD2* pCurrent = p2First; //pradėti nuo pradžių
        while (pCurrent != NULL) //kol nepasiekiama sąrašo pabaiga,
        {
            pCurrent->RodytiElementa(); //rodyti duomenis
            pCurrent = pCurrent->p2Next; //pereiti prie sekančio sąrašo elemento
        }
        if (p2First == NULL)
            cout << "Pratimu nera" << endl;
        cout << endl;
    }
    void deletePratimai()
    {
        ROD2* pCurrent = p2First; //pradeda nuo pradžios
        while (pCurrent != NULL) //kol pasiekiama sąrašo pabaiga,
        {
            ROD2* pOldCur = pCurrent; //atsimenamas šalinamas sąrašo elementas
            pCurrent = pCurrent->p2Next; //pereinama prie kito sąrašo elemento
            delete pOldCur; //ištrinamas prieš tai atsimintas elementas iš kompiuterio atminties
        }
    }
};
////////////////////////////////////////////////////////////////

class DoublyLinkedList
{
private:
    ROD1* pFirst; //rodyklė į pirmą elementą
    ROD1* pLast; //rodyklė į paskutinį elementą
    ROD1* ppFirst; //rodyklė į pirmą elementą
    ROD1* ppLast; //rodyklė į paskutinį elementą
public:
    //-------------------------------------------------------------
    DoublyLinkedList() : //constructor
        pFirst(NULL), pLast(NULL), ppFirst(NULL), ppLast(NULL)
    { }
    //-------------------------------------------------------------
    ~DoublyLinkedList() //destruktorius (išvalo sąrašą)
    {
        ROD1* pCurrent = pFirst; //pradeda nuo pradžios
        while (pCurrent != NULL) //kol pasiekiama sąrašo pabaiga,
        {
            pCurrent->deletePratimai();
            ROD1* pOldCur = pCurrent; //atsimenamas šalinamas sąrašo elementas
            pCurrent = pCurrent->pNext; //pereinama prie kito sąrašo elemento
            delete pOldCur; //ištrinamas prieš tai atsimintas elementas iš kompiuterio atminties
        }
    }
    //-------------------------------------------------------------
    bool insert1(string pav, string rung, int viet)
    {
        ROD1* pNewLink = new ROD1(pav, rung, viet);
        ROD1* pPrevious = NULL;
        ROD1* pCurrent = pFirst;
        while (pCurrent != NULL && pav > pCurrent->pavard)
        {
            //
            pPrevious = pCurrent;
            pCurrent = pCurrent->pNext;
        }
        if (pPrevious == NULL)
            pFirst = pNewLink;
        else
            pPrevious->pNext = pNewLink;
        pNewLink->pNext = pCurrent;

        ROD1* ppPrevious = NULL;
        ROD1* ppCurrent = ppFirst;
        while (ppCurrent != NULL && viet > ppCurrent->vieta)
        {
            ppPrevious = ppCurrent;
            ppCurrent = ppCurrent->ppNext;
        }
        if (ppPrevious == NULL)
            ppFirst = pNewLink;
        else
            ppPrevious->ppNext = pNewLink;
        pNewLink->ppNext = ppCurrent;

        return true;
    }

    bool findMemberAndChangeTime(string pavard)
    {

        ROD1* pCurrent = pFirst;
        while (true) //ieškoma tol kol randamas nurodytas elementas,
        {
            if (pCurrent->pavard == pavard)
            {
                cout << "Sportininkas " << pCurrent->pavard << " rastas" << endl;
                cout << "Jo pratimai:" << endl;
                findMemberAnddisplayPratimai(pavard);
                cout << "Iveskite pratima kurio laika norite keisti" << endl;
                cin >> pratimas;
                cout << "Iveskite nauja trukme" << endl;
                cin >> trukm;
                pCurrent->changeTime(pratimas, trukm);
                return true;
                break;
            }
            pCurrent = pCurrent->pNext; //pereinama prie kito sąrašo elemento
            if (pCurrent == NULL)
            {
                cout << "Sportininkas " << pavard << " nerastas" << endl;
                return false; //jeigu perinko visą sąrašą ir nieko nerado, gražina false reikšmę ir baigia vykdyti funkcijos komandas
                break;
            }
        }
    }

    bool findMemberAndAddExercise()
    {

        ROD1* pCurrent = pFirst;
        while (true) //ieškoma tol kol randamas nurodytas elementas,
        {
            if (pCurrent->pavard == pavard)
            {
                cout << "Sportininkas " << pCurrent->pavard << " rastas" << endl;
                cout << "Iveskite pratimo pavadinima: ";
                cin >> pratimas;
                cout << endl;
                cout << "Iveskite pratimo trukme: ";
                cin >> trukm;
                cout << endl;
                pCurrent->addExercise(pratimas, trukm); //pCurrent->pNext->addExercise(pratimas, trukm);
                return true;
                break;
            }
            pCurrent = pCurrent->pNext; //pereinama prie kito sąrašo elemento
            if (pCurrent == NULL)
            {
                cout << "Sportininkas " << pavard << " nerastas" << endl;
                return false; //jeigu perinko visą sąrašą ir nieko nerado, gražina false reikšmę ir baigia vykdyti funkcijos komandas
                break;
            }
        }
    }

    bool findMemberAnddisplayPratimai(string pavard)
    {
        ROD1* pCurrent = pFirst;
        while (true) //ieškoma tol kol randamas nurodytas elementas,
        {
            if (pCurrent->pavard == pavard)
            {
                pCurrent->displayPratimai();
                return true;
                break;
            }
            pCurrent = pCurrent->pNext; //pereinama prie kito sąrašo elemento
            if (pCurrent == NULL)
            {
                cout << "Sportininkas " << pavard << " nerastas" << endl;
                return false; //jeigu perinko visą sąrašą ir nieko nerado, gražina false reikšmę ir baigia vykdyti funkcijos komandas
                break;
            }
        }
    }

    bool remove(string pav)
    {
        ROD1* pPrevious = pFirst;
        ROD1* pCurrent = pFirst;
        while (pCurrent->pavard != pav)
        {
            pPrevious = pCurrent;
            pCurrent = pCurrent->pNext;
            if (pCurrent == NULL)
                return false;
        }
        if (pCurrent == pFirst)
            pFirst = pCurrent->pNext;
        else if (pCurrent == pLast)
            pLast = pPrevious;
        else
            pPrevious->pNext = pCurrent->pNext;


        ROD1* ppPrevious = ppFirst;
        ROD1* ppCurrent = ppFirst;

        while (ppCurrent != pCurrent)
        {
            ppPrevious = ppCurrent;
            ppCurrent = ppCurrent->ppNext;
            if (ppCurrent == NULL)
                return false;
        }
        if (ppCurrent == ppFirst)
            ppFirst = ppCurrent->ppNext;
        else if (ppCurrent == ppLast)
            ppLast = ppPrevious;
        else
            ppPrevious->ppNext = ppCurrent->ppNext;

        pCurrent->deletePratimai();
        delete pCurrent;
        return true; //pranešama, kad tyrnimas įvykdytas sėkmingai, gražinama reikšmė true
    }

    void displaySportininkai()
    {
        ROD1* pCurrent = pFirst; //pradėti nuo pradžių
        while (pCurrent != NULL) //kol nepasiekiama sąrašo pabaiga,
        {
            pCurrent->RodytiElementa(); //rodyti duomenis
            pCurrent = pCurrent->pNext; //pereiti prie sekančio sąrašo elemento
        }
        cout << endl;
    }
    void displaySportininkai2()
    {
        ROD1* ppCurrent = ppFirst; //pradėti nuo pradžių
        while (ppCurrent != NULL) //kol nepasiekiama sąrašo pabaiga,
        {
            ppCurrent->RodytiElementa(); //rodyti duomenis
            ppCurrent = ppCurrent->ppNext; //pereiti prie sekančio sąrašo elemento
        }
        cout << endl;
    }

}; //klasės DoublyLinkedList pabaiga
////////////////////////////////////////////////////////////////
void Meniu(int& b)
{
    //char a;
    cout << "[1] - Naujas sportininkas" << endl;
    cout << "[2] - Pakeisti pratimo trukme " << endl;
    cout << "[3] - Papildyti pratimu sarasa" << endl;
    cout << "[4] - Isvesti sportininku sarasa" << endl;
    cout << "[5] - Isvesti pratimu sarasa" << endl;
    cout << "[6] - Pasalinti sportininka" << endl;
    cout << "[7] - Duomenu suvedimas is failo" << endl;
    cout << "[9] - Isjungti programa" << endl;
    cin >> b;
}


void sportininko_duomenys()
{
    cout << "Iveskite sportininko pavarde: ";
    cin >> pavard;
    cout << endl;
    cout << "Iveskite rungti: ";
    cin >> rungt;
    cout << endl;
    cout << "Iveskite sportininko vieta: ";
    cin >> vieta;
    cout << endl;
}



int main()
{
    DoublyLinkedList sar;
    ifstream in("in.txt");
    ofstream out("out.txt");
    streambuf* cinbuf = cin.rdbuf();
    streambuf* coutbuf = cout.rdbuf();
    int pas;
    do
    {
        Meniu(pas);
        switch (pas)
        {
        case 1:
        {
            sportininko_duomenys();
            sar.insert1(pavard, rungt, vieta);
            cout << "Sportininkas sekmingai pridetas" << endl;
            break;
        }
        case 2:
        {
            sar.displaySportininkai();
            cout << "Iveskite sportininko pavarde is saraso virsuje" << endl;
            cin >> pavard;
            sar.findMemberAndChangeTime(pavard);
            break;
        }
        case 3:
        {
            cout << "Iveskite sportininko pavarde" << endl;
            cin >> pavard;
            sar.findMemberAndAddExercise();
            break;
        }
        case 4:
        {
            cout << "Sarasas pagal pavarde: " << endl;
            sar.displaySportininkai();
            cout << "Sarasas pagal nr: " << endl;
            sar.displaySportininkai2();
            break;
        }
        case 5:
        {
            sar.displaySportininkai();
            cout << "Iveskite sportininko pavarde is saraso virsuje" << endl;
            cin >> pavard;
            sar.findMemberAnddisplayPratimai(pavard);
            break;
        }
        case 6:
        {
            sar.displaySportininkai();
            cout << "Iveskite sportininko pavarde is saraso virsuje" << endl;
            cin >> pavard;
            if (sar.remove(pavard))cout << "Sportininkas " << pavard << " sekmingai pasalintas" << endl;
            else cout << "Sportininkas " << pavard << " nerastas" << endl;
            break;
        }
        case 7:
        {
            cin.rdbuf(in.rdbuf());
            cout.rdbuf(out.rdbuf());
            break;
        }
        case 8:
        {
            cin.rdbuf(cinbuf);
            cout.rdbuf(coutbuf);
            out.close();
            remove("out.txt");//istrinu sukurta faila, jo paskirtis neuztersti konsoles lango ivedant is failo
            cout << "Duomenys sekmingai suvesti" << endl;
            break;
        }

        case 9:
        {
            sar.~DoublyLinkedList();
            cout << "Duomenys istrinti" << endl;
            cout << "Programa isjungiama" << endl;
            return 0;
            break;
        }

        default:
        {
            cout << "Tokio pasirinkimo nera ..." << endl;
            break;
        }

        }
    } while (pas != 9);

    in.close();
    return 0;
}
