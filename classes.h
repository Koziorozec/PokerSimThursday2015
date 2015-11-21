#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED
//=============================================================================
#include <iostream>
#include<time.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <stddef.h>
#include <algorithm>
#include <utility>
using std::cout;
using std::cin;
using std::endl;
// Te enumy sa "obowiazkwe"
enum Wartosc {BlankW=0,Dwojka=2,Trojka,Czworka,Piatka,Szostka,Siodemka,Osemka,Dziewiatka,Dziesiatka,Walet,Dama,Krol,As}; // zapamietac dwojka jest oznaczona DWOJKA !


enum Kolor {BlankK=0,Trefl=1,Karo,Kier,Pik};
enum Odzywka{Pass=0,Raise,Call,Check};

enum Blad{ZaMaloPieniedzy=0,MusiszCoNajmniejWyrownac,NieMoznaZrobicCheckWTejLicytacji,Dyskwalifikacja,NieMaszDoscPieniedzy,NieMoznaZrobicPassWTejLicytacji};
      //Nie masz dosc pieniedzy oznacza ze zamiast rise, zostalo wykonane call. nie ma drugiej szansy w tej kolejce licytacji

//Te sa prywatne stolu, i nie sa wymagane dla innych
enum UkladyMS{Brak=0,Para,DwiePary,TrojkaU,Strit,KolorU,Full,Kareta,Poker}; // definiuje najpierw uklad, a potem jako zmienna sile ukladu

enum WynikMS{przegrana=0,remis,wygrana};

//------------

class Karta
{
    public:
    enum Wartosc m_w;
    enum Kolor m_k;

	Karta(Wartosc w = Wartosc::BlankW, Kolor k = Kolor::BlankK);
    void Set(Wartosc w,Kolor k);// bo set jest krotsze niz ustaw
    Wartosc ReadW();
    Kolor ReadK();
};


class Talia{
private:
    Karta m_TabTalia[52];
    int m_iLicznik;
public:
    Talia();
    Karta Draw();
};

class GraczKopia{
public:
    int m_iNumerGracza;
    int m_iIloscPieniedzy;
    int m_WlozonePieniadze;
    Karta m_KartyGracza[2];
};

class Gracz{
public:
    void virtual Wywolanie(int iNumerGracza, int iIloscGraczy, int Iloscpieniedzy, int SmallBlind); // numer gracza, to Twoj numer, to tez oznacza now¹ gre.
    std::string virtual PrzedstawSie();
    std::pair<Odzywka,int> virtual odOdzywka();  //jesli powiedziales ze podbijasz to zostaniesz zapytany o to o ile hajs w wielokrotnosci big blind

    void virtual BladOdzywki(Blad blad);// po bledzie zostanie wywolane zadanie odzywki po raz drugi. jezeli dalej wystepuje blad uznaje sie pass
    void virtual ZwyciestwoPartii(int ZarobionePieniadze);
    void virtual ZwyciestwoCalejGry();
    void virtual WszedlesSmallBlind();
    void virtual WszedlesBigBlind(); //
    void virtual PrzegranaCalejGry(int NrGraczaWygrywajacego); //-1 oznacza ze zostales z dyskwalifikowany
    void virtual PrzegranaPartii(int NrGraczaWygrywajacegoPartie);
    void virtual ZwrotPieniedzy(int iIlosc); // ilosc jest podana w liczbach bo nie musi byc wielokrotnoscia Big blind. teoretycznie chyab powinna byc ale nie chce mi sie tego dowodzic
    void virtual PodniesioneBigBlind();// zawsze podnoszone dwukrotnie
    void virtual GraczZlicytowal(int NrGraczaWypowiadajacego, Odzywka odzWypowiedz, int iIloscPieniedzyPodbitych); // ilosc pieniedzy jest rozna od zero kiedy podbija. inaczej jest bez znaczenia i JEST podana w ILOSCI HAJSU
    void virtual PokazKarty(int NrGr, Karta PierwszaKarta, Karta DrugaKarta);
    // Podaje pieniadze w postaci wielokrotnosci BigBlinD
	void virtual OdsloniecieKartyGracza(Karta nowaKarta);
	void virtual OdsloniecieKartyZeStolu(Karta KartaZeStolu);

};
///////////////////////////////////////////////////////////////////////////////
class UkladCaly
{
public:
    UkladyMS m_Uklad;
    Wartosc m_WolneOdNajwyzszej[5];
    Wartosc m_NajwyzszaZUkladu;
    Wartosc m_SlabszaPara; // oznacza tez pare, w ukladzie 3+2
    UkladCaly();
};

///////////////////////////////////////////////////////////////////////////////
class AllIn
{
public:
    AllIn();
    AllIn(int NrGr,int iPieniadze);

    int m_NrGraczaAllIn;
    int m_iPulaPieniedzyDlaGraczaAllIn;
};


//-------------funkcja
UkladCaly ZnajdzUklad(Karta k1,Karta k2,Karta k3,Karta k4,Karta k5);

///////////////////////////////////////////////////////////////////////////////
class Stol //graczy numeruje sie od 0
{
private:

    Talia m_Talia;
    std::string m_strNazwyGraczy[10];
    Gracz* m_TabGraczy[10];
    GraczKopia m_TabGraczyKopia[10];
    Karta m_KartyNaStole[5];
    AllIn m_TabelaAllIn[10];
    bool m_CzyGraczAktywny[10];
    bool m_CzyGraczWRundzie[10];
    bool m_CzyGraczAllIn[10];
    bool m_FlagKoniecGry;
    bool m_FlagKoniecRundy;
    bool m_FlagPartiaWToku; // w konstruktorze ustawic na false
    int m_iLicznikGraczyCalosc;
    int m_iLiczbaGraczyAktualnie;
    int m_iLiczbaGraczyWRundzie;
    int m_iNumerGraczaRoz;
    int m_iSmallBlind;
    int m_iBigBlind;
    int m_iPieniadzeStartowe;
    int m_iLicznikRund;
    int m_iPulaPieniedzyAktualnie;
    int m_iStawkaNaGraczaAkt;
    int m_NajwyzszyNaAllIn;// wskaznik na najzywsze miejsce w tabeli

public:
    Stol(int SmallBlind, int IloscPieniedzy);
    bool DodajGracza(Gracz* gracz);// GOTOWE zwraca false, jesli nie uda sie wykonac operacji,
    WynikMS PorownajUkladyGr(int iNumerGraczaA,int NumerGraczaB); // wygrana znaczy ze wygral pierwszy gracz. reszta sensownie
    void Graj();
    void IncrementujWPetli(int* iLicznik);
    bool CzyGraczGra(int nrGracza);
    bool CzyGraczGraR(int iNrGr);
    void Runda();
    void PierwszaLicytacja();
    void Licytacja();
    void AllInTabClear();
    void Wyrownaj(int NrGracza);
    void WyznanieGr(int NrGr, Odzywka Wyznanie, int iHajs);
    void IncrementujWPetliGr(int *NrGr); // wpetli graczy grajacych w ogole
    void IncrementujWPetliGrR(int *NrGr);// w petli graczyw rundzie
    void DecrementujWPetliGrR(int *NrGr);
    void DecrementujWPetliGr(int *NrGr);
    bool CzyGraczAllIn(int NrGr);
    int ZnajdzNrGrAllIn(int NrGr);
    void OdrzucLudziBezHajsu();
    void PokazWszystkieKarty();

};



























//=============================================================================
#endif // CLASSES_H_INCLUDED
