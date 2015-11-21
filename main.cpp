#include "stdafx.h"
#include <iostream>
#include<time.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <stddef.h>
#include "classes.h"
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;


#define DEBUG1
/*lista metod w kazdej z klas
odzywka
blad odzywki(u podac przyczyne, np. nie ma chech jesli ktos podbil etc)
zwyciestwo
przegrana celej patrii


TwojaKarta(Karta)
KartaZeStolu(Karta)
*/
/*
bool MojaFunkcjaSortujacaKarty(Karta a, Karta b)
{
    return (a.m_w>b.m_w);
}
*/


struct
{
    bool operator()(Karta a, Karta b)
    {
        return (a.m_w<b.m_w);
    }
}CustomSort;
struct
{
    bool operator()(Wartosc a, Wartosc b)
    {
        return (a>b);
    }
}CustomSortWartoscOdMaks;


//--------------------- Karta -------------------------------------------------

    Karta::Karta(Wartosc w,Kolor k)
    {
        m_w=w;
        m_k=k;
    }
    void Karta::Set(Wartosc w,Kolor k)// bo set jest krotsze niz ustaw
    {
        m_w=w;
        m_k=k;
    }
    Wartosc Karta::ReadW()
    {
        return m_w;
    }
    Kolor Karta::ReadK()
    {
        return m_k;
    }
    bool operator == (Karta KartaPierw, Karta KartaDr)
    {
        if(KartaPierw.m_w==KartaDr.m_w && KartaPierw.m_k==KartaDr.m_k)
            return true;
        else
            return false;
    }
    bool operator != (Karta KartaPierw, Karta KartaDr)
    {
        if(KartaPierw==KartaDr)
            return false;
        else
            return true;
    }
 /*   Karta& operator =(const Karta&  ObjektKar)
    {
        m_w=ObjektKar.m_W;
        m_k=ObjektKar.m_k;
        return *this;
    }

*/



//-------------------- Talia --------------------------------------------------

    Talia::Talia()
    {
        //------------ustaw talie------
        m_iLicznik=0;
        int iLicznikKart=0;
        Karta karStash(BlankW,BlankK);
        srand(time(NULL));
        for(int i=2;i<15;i++)//
        {
            for(int k=1;k<5;k++)
            {
                m_TabTalia[iLicznikKart].m_w=Wartosc(i);
                m_TabTalia[iLicznikKart].m_k=Kolor(k);
                iLicznikKart++;
                #ifdef DEBUG1
                cout<<"wartosc : "<< m_TabTalia[iLicznikKart-1].m_w<<" kolor : "<<m_TabTalia[iLicznikKart-1].m_k<<endl;
                #endif // DEBUG1
            }//end for(int k=1;k<5;k++)
        }//end for(int i=1;i<14;i++)



        //-------------potasuj---------
        int iPierwszy=0,iDrugi=0;
        for(int l=0;l<1000;l++)
        {
            iPierwszy=(rand()%52);
            iDrugi=(rand()%52);
            karStash=m_TabTalia[iPierwszy];
            m_TabTalia[iPierwszy]=m_TabTalia[iDrugi];
            m_TabTalia[iDrugi]=karStash;
        }
     #ifdef DEBUG1
     for(int i=0;i<52;i++)
        cout<<i<<"  -> "<<m_TabTalia[i].m_w<<"/"<<m_TabTalia[i].m_k<<endl;
     #endif // DEBUG1

    }
    Karta Talia::Draw()
    {
        Karta karStash=m_TabTalia[m_iLicznik];
        m_iLicznik++;
        return karStash;
    }

//////////////////////////uklad
UkladCaly::UkladCaly()
{
    m_Uklad=UkladyMS::Brak;
    for(int i=0;i<5;i++)
    {
        m_WolneOdNajwyzszej[i]=Wartosc::BlankW;
    }
    m_NajwyzszaZUkladu=Wartosc::BlankW;
    m_SlabszaPara=Wartosc::BlankW;
}
WynikMS operator == (UkladCaly U1,UkladCaly U2) // porownaj uklady
{
    if(int(U1.m_Uklad)>int(U2.m_Uklad))
        return WynikMS::wygrana;
    if(int(U1.m_Uklad)<int(U2.m_Uklad))
        return WynikMS::przegrana;
    if(int(U1.m_Uklad)==int(U2.m_Uklad)) // poker nie moga istniec dwa takie same pokery
    {
        //-------------
        if(U1.m_Uklad==UkladyMS::Kareta)
        {
            if(U1.m_NajwyzszaZUkladu>U2.m_NajwyzszaZUkladu) // porownujesz sily ukladow(najwyzsza karte)
            {
               return WynikMS::wygrana;
            }
            if(U1.m_NajwyzszaZUkladu<U2.m_NajwyzszaZUkladu)
            {
               return WynikMS::przegrana;
            }
            if(U1.m_NajwyzszaZUkladu==U2.m_NajwyzszaZUkladu)// jezeli to sa uklady z takich samych kart porownujemy wolne
            {
                if(U1.m_WolneOdNajwyzszej[0]>U2.m_WolneOdNajwyzszej[0])
                    return WynikMS::wygrana;
                if(U1.m_WolneOdNajwyzszej[0]<U2.m_WolneOdNajwyzszej[0])
                    return WynikMS::przegrana;
                if(U1.m_WolneOdNajwyzszej[0]==U2.m_WolneOdNajwyzszej[0])
                    return WynikMS::remis;
            }

        }
        //----------------------
        if(U1.m_Uklad==UkladyMS::Full)
        {
             if(U1.m_NajwyzszaZUkladu>U2.m_NajwyzszaZUkladu) // porownujesz sily ukladow(najwyzsza karte)
            {
               return WynikMS::wygrana;
            }
            if(U1.m_NajwyzszaZUkladu<U2.m_NajwyzszaZUkladu)
            {
               return WynikMS::przegrana;
            }
            if(U1.m_NajwyzszaZUkladu==U2.m_NajwyzszaZUkladu)
            {
                if(U1.m_SlabszaPara>U2.m_SlabszaPara)
                    return WynikMS::wygrana;
                if(U1.m_SlabszaPara<U2.m_SlabszaPara)
                    return WynikMS::przegrana;
                if(U1.m_SlabszaPara==U2.m_SlabszaPara)
                    return WynikMS::remis;
            }
        }
        //------------------------
        if(U1.m_Uklad==UkladyMS::KolorU)   // z jakiegos powodu porownuje sie tylko najwyzsza z ukladu, a nie reszte kart. Takie przepisy
        {
            if(U1.m_NajwyzszaZUkladu>U2.m_NajwyzszaZUkladu) // porownujesz sily ukladow(najwyzsza karte)
            {
               return WynikMS::wygrana;
            }
            if(U1.m_NajwyzszaZUkladu<U2.m_NajwyzszaZUkladu)
            {
               return WynikMS::przegrana;
            }
            if(U1.m_NajwyzszaZUkladu==U2.m_NajwyzszaZUkladu)
                return WynikMS::remis;
        }
        //------------------
        if(U1.m_Uklad==UkladyMS::Strit)
        {
            if(U1.m_NajwyzszaZUkladu>U2.m_NajwyzszaZUkladu) // porownujesz sily ukladow(najwyzsza karte)
            {
               return WynikMS::wygrana;
            }
            if(U1.m_NajwyzszaZUkladu<U2.m_NajwyzszaZUkladu)
            {
               return WynikMS::przegrana;
            }
            if(U1.m_NajwyzszaZUkladu==U2.m_NajwyzszaZUkladu)
                return WynikMS::remis;
        }
        //-----------------------------------------------------
        if(U1.m_Uklad==UkladyMS::TrojkaU)
        {
             if(U1.m_NajwyzszaZUkladu>U2.m_NajwyzszaZUkladu) // porownujesz sily ukladow(najwyzsza karte)
            {
               return WynikMS::wygrana;
            }
            if(U1.m_NajwyzszaZUkladu<U2.m_NajwyzszaZUkladu)
            {
               return WynikMS::przegrana;
            }
            if(U1.m_NajwyzszaZUkladu==U2.m_NajwyzszaZUkladu)// mamy teraz 2 karty do poronwninia
            {
                if(U1.m_WolneOdNajwyzszej[0]>U2.m_WolneOdNajwyzszej[0])
                    return WynikMS::wygrana;
                if(U1.m_WolneOdNajwyzszej[0]<U2.m_WolneOdNajwyzszej[0])
                    return WynikMS::przegrana;
                if(U1.m_WolneOdNajwyzszej[0]==U2.m_WolneOdNajwyzszej[0])//jezeli to dalej nie da opdowiedzi
                {
                    if(U1.m_WolneOdNajwyzszej[1]>U2.m_WolneOdNajwyzszej[1])
                        return WynikMS::wygrana;
                    if(U1.m_WolneOdNajwyzszej[1]<U2.m_WolneOdNajwyzszej[1])
                        return WynikMS::przegrana;
                    if(U1.m_WolneOdNajwyzszej[1]==U2.m_WolneOdNajwyzszej[1])
                        return WynikMS::remis;
                }
            }
        }
        //-----------------
        if(U1.m_Uklad==UkladyMS::DwiePary)
        {
            if(U1.m_NajwyzszaZUkladu>U2.m_NajwyzszaZUkladu) // porownujesz sily ukladow(najwyzsza karte)
            {
               return WynikMS::wygrana;
            }
            if(U1.m_NajwyzszaZUkladu<U2.m_NajwyzszaZUkladu)
            {
               return WynikMS::przegrana;
            }
            if(U1.m_NajwyzszaZUkladu==U2.m_NajwyzszaZUkladu)
            {
                if(U1.m_SlabszaPara>U2.m_SlabszaPara)
                    return WynikMS::wygrana;
                if(U1.m_SlabszaPara<U2.m_SlabszaPara)
                    return WynikMS::przegrana;
                if(U1.m_SlabszaPara==U2.m_SlabszaPara) // porownujemy
                    {
                        if(U1.m_WolneOdNajwyzszej[0]>U2.m_WolneOdNajwyzszej[0])
                            return WynikMS::wygrana;
                        if(U1.m_WolneOdNajwyzszej[0]<U2.m_WolneOdNajwyzszej[0])
                            return WynikMS::przegrana;
                        if(U1.m_WolneOdNajwyzszej[0]==U2.m_WolneOdNajwyzszej[0])
                            return WynikMS::remis;
                    }
            }


        }
        //------------------------------------------------
        if(U1.m_Uklad==UkladyMS::Para)
        {
            if(U1.m_NajwyzszaZUkladu>U2.m_NajwyzszaZUkladu) // porownujesz sily ukladow(najwyzsza karte)
            {
               return WynikMS::wygrana;
            }
            if(U1.m_NajwyzszaZUkladu<U2.m_NajwyzszaZUkladu)
            {
               return WynikMS::przegrana;
            }
            if(U1.m_NajwyzszaZUkladu==U2.m_NajwyzszaZUkladu)// zostaly nam 3 karty
            {
                for(int i=2;i<4;i++) // idziemy po kolej od najwiekszych, jesli ktora kolwiek bedzie wieksza to mamy return;
                {
                    if(U1.m_WolneOdNajwyzszej[i]>U2.m_WolneOdNajwyzszej[i])
                        return WynikMS::wygrana;
                    if(U1.m_WolneOdNajwyzszej[i]<U2.m_WolneOdNajwyzszej[i])
                        return WynikMS::przegrana;
                }// jezeli jednak nic z tego to sprawdzamy ostatnia karte
                if(U1.m_WolneOdNajwyzszej[4]>U2.m_WolneOdNajwyzszej[4])
                    return WynikMS::wygrana;
                if(U1.m_WolneOdNajwyzszej[4]<U2.m_WolneOdNajwyzszej[4])
                    return WynikMS::przegrana;
                if(U1.m_WolneOdNajwyzszej[4]==U2.m_WolneOdNajwyzszej[4])
                    return WynikMS::remis;

            }
        }
        //---------------------------------------
        if(U1.m_Uklad==UkladyMS::Brak)
        {
            for(int i=0;i<4;i++) // jak wyzej
            {
                if(U1.m_WolneOdNajwyzszej[i]>U2.m_WolneOdNajwyzszej[i])
                    return WynikMS::wygrana;
                if(U1.m_WolneOdNajwyzszej[i]<U2.m_WolneOdNajwyzszej[i])
                    return WynikMS::przegrana;
            }// jezeli jednak nic z tego to sprawdzamy ostatnia karte
            if(U1.m_WolneOdNajwyzszej[4]>U2.m_WolneOdNajwyzszej[4])
                return WynikMS::wygrana;
            if(U1.m_WolneOdNajwyzszej[4]<U2.m_WolneOdNajwyzszej[4])
                return WynikMS::przegrana;
            if(U1.m_WolneOdNajwyzszej[4]==U2.m_WolneOdNajwyzszej[4])
                return WynikMS::remis;
        }
        //---------------------------------------


    }//end if(int(U1.m_Uklad)==int(U2.m_Uklad))
    return WynikMS::remis;
}


UkladCaly ZnajdzUklad(Karta k1,Karta k2,Karta k3,Karta k4,Karta k5)
{
    Karta TabKart[5];
    UkladCaly OstWynik;
    UkladyMS enWynik=UkladyMS::Brak;
    //UkladyMS enStash=UkladyMS::Brak; // to sa enumy. wyzszy uklad to wyzsza wartosc
    TabKart[0]=k1;    TabKart[1]=k2;    TabKart[2]=k3;    TabKart[3]=k4;    TabKart[4]=k5;

    std::sort(TabKart,TabKart+5,CustomSort);// sortuje tabele rosnaca po wartosciach kart
    //Szukamy par
    for(int i=0;i<4;i++)
    {
        if(TabKart[i].m_w==TabKart[i+1].m_w) // jezeli znaleslimy pare
        {
            if(i<3)// jezeli wystepuje jeszcze jakas nastepna <nie jestesmy na ostatniej parze>
            {
                if(TabKart[i].m_w==TabKart[i+2].m_w) // sprawdzamy czy kolejna para za ta daje nam trojke
                {
                    if(i<2) // jezeli sie zmeisci jeszcze czwartka
                    {
                        if(TabKart[i].m_w==TabKart[i+3].m_w) // sprawdzamy czy czwarta opd rzad daje to samo
                        {
                            if(enWynik<UkladyMS::Kareta)
							{
								enWynik=UkladyMS::Kareta;
							} // mamy karete
                        }
                    }
                    if(0==i) // jezeli mamy jeszcze miejsce na pare
                    {
                        if(TabKart[3].m_w==TabKart[4].m_w)// jezeli pierwsze trzy daja trojke, anastepne dwie daja para mamy fulla
                            if(enWynik<UkladyMS::Full){enWynik=UkladyMS::Full;}
                    }
                    if(enWynik<UkladyMS::TrojkaU){enWynik=UkladyMS::TrojkaU;}
                }
                else// jezeli nie ma pary
                {
                    if(i<2) // sprawdzamy czy zmiesci sie druga para
                    {
                        for(int k=i+2;k<4;k++) // sprawdzamy czy wystepuje druga para
                        {
                            if(TabKart[k].m_w==TabKart[k+1].m_w)
                                if(enWynik<UkladyMS::DwiePary){enWynik=UkladyMS::DwiePary;} // mamy dwie pary
                        }
                    }
                    if(0==i)// jezeli to jest pierwsza para, sprawdzamy czy nie ma Fula
                    {
                        if(TabKart[2].m_w==TabKart[3].m_w && TabKart[3].m_w==TabKart[4].m_w) // czy nastepne 3 karty daja trojke
                        {
                            if(enWynik<UkladyMS::Full){enWynik=UkladyMS::Full;}
                        }
                    }
                }//end else od if(TabKart[i]==TabKart[i+2])
            }
            else // jezeli to juz 2 ostatnie  else od if(i<3)
            {
                if(enWynik<UkladyMS::Para){enWynik=UkladyMS::Para;}
            }//end if(i<3)
        if(enWynik<UkladyMS::Para){enWynik=UkladyMS::Para;}
        }//endif (TabKart[i]==TabKart[i+1])
    }
    //----------------------- teraz szukamy  strita i pokera

    if(
       ((int(TabKart[0].m_w)+1)==int(TabKart[1].m_w)) &&
       ((int(TabKart[1].m_w)+1)==int(TabKart[2].m_w)) &&
       ((int(TabKart[2].m_w)+1)==int(TabKart[3].m_w)) &&
       ((int(TabKart[3].m_w)+1)==int(TabKart[4].m_w))
      )
       // sprawdzamy czy kartty sa jedna po drugiej
    {// jezeli sa sprawdzamy czy s¹ w tym samym kolorze
        if(TabKart[0].m_k==TabKart[1].m_k && TabKart[0].m_k==TabKart[2].m_k && TabKart[0].m_k==TabKart[3].m_k && TabKart[0].m_k==TabKart[4].m_k)
        {// jezeli sa tego samego koloru
            if(enWynik<UkladyMS::Poker){enWynik=UkladyMS::Poker;}
        }
        else
        {
            if(enWynik<UkladyMS::Strit){enWynik=UkladyMS::Strit;}
        }

    }
    //----------------kulturalnie osobno sprawdzimy kolor
    if(TabKart[0].m_k==TabKart[1].m_k && TabKart[0].m_k==TabKart[2].m_k && TabKart[0].m_k==TabKart[3].m_k && TabKart[0].m_k==TabKart[4].m_k)
    {
        if(enWynik<UkladyMS::KolorU){enWynik=UkladyMS::KolorU;}
    }

    //Teraz trzeba dorobic warunki zeby dalo sie rozroznic zwyciezce zawsze----
    if(UkladyMS::Para==enWynik)
    {
        for(int i=0;i<4;i++)// szukasz pary
        {
            if(TabKart[i].m_w==TabKart[i+1].m_w) // jezeli juz ja znajdziesz to
            {
                OstWynik.m_NajwyzszaZUkladu=TabKart[i].m_w; // przypisz wartosc jako najwyzsza z ukladu
                for(int k=0;k<5;k++)
                {
                    if (k!=i&& k!=(i+1))  // jezeli t nie sa karty z pary
                       {
                           OstWynik.m_WolneOdNajwyzszej[k]=TabKart[k].m_w;
                       }
                }
                std::sort(OstWynik.m_WolneOdNajwyzszej,OstWynik.m_WolneOdNajwyzszej+5,CustomSortWartoscOdMaks);

            }//end if
        }//end for
    }//end if
    //to samo dla trojki

    if(UkladyMS::TrojkaU==enWynik)
    {
        for(int i=0;i<3;i++)
        {
            if(TabKart[i].m_w==TabKart[i+1].m_w&& TabKart[i].m_w==TabKart[i+2].m_w) // jezeli 3 sa rowne
            {
                OstWynik.m_NajwyzszaZUkladu=TabKart[i].m_w; // zapisz wartosc najwiekszej
                for(int k=0;k<5;k++)
                {
                    if (k!=i&& k!=(i+1)&& k!=(i+2))  // jezeli t nie sa karty z pary
                       {
                           OstWynik.m_WolneOdNajwyzszej[k]=TabKart[k].m_w;
                       }
                }
                std::sort(OstWynik.m_WolneOdNajwyzszej,OstWynik.m_WolneOdNajwyzszej+5,CustomSortWartoscOdMaks);
            }
        }
    }//end if(UkladyMS::TrojkaU==enWynik)

        //dla czworki
    if(UkladyMS::Kareta==enWynik)
    {
        if(TabKart[0].m_w==TabKart[1].m_w)// jezeli pierwsze 2 sa takie same, to ostatnia jest rozna
        {
            OstWynik.m_NajwyzszaZUkladu=TabKart[0].m_w;
            OstWynik.m_WolneOdNajwyzszej[0]=TabKart[4].m_w;
        }
        else //znaczy ze pierwsza jest inna od reszty tabela jest posortowana
        {
            OstWynik.m_NajwyzszaZUkladu=TabKart[2].m_w;
            OstWynik.m_WolneOdNajwyzszej[0]=TabKart[0].m_w;
        }
    }//endif(UkladyMS::Kareta==enWynik)

    // dla pokera


    if(UkladyMS::Poker==enWynik || UkladyMS::Strit==enWynik || UkladyMS::KolorU==enWynik)
    {
        OstWynik.m_NajwyzszaZUkladu=TabKart[4].m_w; // bo tablica posortowana
        // nie ma wlnych kart (nie w ukladzie)
    }//end if(UkladyMS::Poker==enWynik || UkladyMS::Strit==enWynik || kladyMS::Kolor==enWynik)
    //dla dwoch par
     if(UkladyMS::DwiePary==enWynik)
     {
         if(TabKart[0].m_w==TabKart[1].m_w) // jesli uklad jest YYxxx
         {
             if(TabKart[2].m_w==TabKart[3].m_w) // jesli jest uklad YYXXz X jest rozne od Y
             {
                 OstWynik.m_NajwyzszaZUkladu=TabKart[3].m_w; // YYX(X)z
                 OstWynik.m_WolneOdNajwyzszej[0]=TabKart[4].m_w;// YYXX(z)
             }
             else// jezeli uklad jest YYzXX
             {
                 OstWynik.m_NajwyzszaZUkladu=TabKart[3].m_w; // YYz(X)X
                 OstWynik.m_WolneOdNajwyzszej[0]=TabKart[2].m_w;// YY(z)XX
             }
             OstWynik.m_SlabszaPara=TabKart[1].m_w; // Y(Y)[X/z][x][x/z]
         }
         else// jezeli uklad jest zYYXX
         {
            OstWynik.m_NajwyzszaZUkladu=TabKart[4].m_w; // zYYX(X)
            OstWynik.m_WolneOdNajwyzszej[0]=TabKart[0].m_w;// (z)XXYY
            OstWynik.m_SlabszaPara=TabKart[1].m_w; //z(Y)YXX
         }

     }//end if(UkladyMS::DwiePary==enWynik)

    if(UkladyMS::Full==enWynik) // X jest rozne od Y
    {
        if(TabKart[1].m_w==TabKart[2].m_w) // jezeli wystepuje X(XX)YY
        {
            OstWynik.m_NajwyzszaZUkladu=TabKart[2].m_w; //XX(X)YY
            OstWynik.m_SlabszaPara=TabKart[4].m_w; // XXXY(Y)
        }
        else // Y(YX)XX
        {
            OstWynik.m_NajwyzszaZUkladu=TabKart[2].m_w; //XX(X)YY
            OstWynik.m_SlabszaPara=TabKart[0].m_w; // (Y)YXXX
        }
    }


    if(UkladyMS::Brak==enWynik)
    {
        for(int i=0;i<5;i++)
            OstWynik.m_WolneOdNajwyzszej[i]=TabKart[4-i].m_w;
    }







    // Tymczasowo:
    OstWynik.m_Uklad=enWynik;


    return OstWynik;




}





AllIn::AllIn()
{
    m_NrGraczaAllIn=0;
    m_iPulaPieniedzyDlaGraczaAllIn=0;
}



//////////////////////////////// Stol ////////////////////////////////////////

bool Stol::DodajGracza(Gracz *NowyGracz)
{
    if(m_FlagPartiaWToku)
        return false;
    //jezeli jest flaszywa
    m_iLicznikGraczyCalosc++;
    m_iLiczbaGraczyAktualnie++;
    m_TabGraczy[m_iLicznikGraczyCalosc-1]=NowyGracz; // wsadzam wskaznik na gracza
    m_CzyGraczAktywny[m_iLicznikGraczyCalosc-1]=true;
    m_strNazwyGraczy[m_iLicznikGraczyCalosc-1]=NowyGracz->PrzedstawSie();
    return true;
}

WynikMS Stol::PorownajUkladyGr(int iNrGrA,int iNrGrB)
{

    Karta TabKartGrA[7];
    Karta TabKartPoOdrzuceniuGrA[5];
    Karta TabKartPoOdrzuceniuGrB[5];
    Karta TabKartGrB[7];
    UkladCaly UkGrA,UkGrAKopia,UkGrB,UkGrBKopia;
    int iLicznik=0;


    int m=0; // bo sie kompilator rzucal
    for(m=0; m<5;m++);
    {
        TabKartGrA[m]=m_KartyNaStole[m];
        TabKartGrB[m]=m_KartyNaStole[m];
    }
    TabKartGrA[5]=m_TabGraczyKopia[iNrGrA].m_KartyGracza[0];
    TabKartGrA[6]=m_TabGraczyKopia[iNrGrA].m_KartyGracza[1];
    TabKartGrB[5]=m_TabGraczyKopia[iNrGrA].m_KartyGracza[0]; //do sprawdzenia
    TabKartGrB[6]=m_TabGraczyKopia[iNrGrA].m_KartyGracza[1];
    iLicznik=0;
    for(int i=0;i<6;i++)// wyznaczam pierwsza karte nie brana pod uwage dla gracza A i B0
    {
        for(int k=i+1;k<7;k++) // druga karte nie barana pod uwage dla gracza A iB
        {
            iLicznik=0;
            for(int r=0;r<7;r++)
            {
                if(r!=i && r!=k) // jesli r nie nalezy do odrzuconych to przypisz go do tablicy kart
                {
                    TabKartPoOdrzuceniuGrB[iLicznik]=TabKartGrB[r];
                    TabKartPoOdrzuceniuGrA[iLicznik]=TabKartGrA[r];
                    iLicznik++;
                }
            }
        //kiedy mamy juz wyznaczone tablice graczy to lecimy
        UkGrAKopia=ZnajdzUklad(TabKartPoOdrzuceniuGrA[0],TabKartPoOdrzuceniuGrA[1],TabKartPoOdrzuceniuGrA[2],TabKartPoOdrzuceniuGrA[3],TabKartPoOdrzuceniuGrA[4]);
        UkGrBKopia=ZnajdzUklad(TabKartPoOdrzuceniuGrB[0],TabKartPoOdrzuceniuGrB[1],TabKartPoOdrzuceniuGrB[2],TabKartPoOdrzuceniuGrB[3],TabKartPoOdrzuceniuGrB[4]);
        if( ( UkGrAKopia==UkGrA )==WynikMS::wygrana )
        { // jesli znaleziony uklad wygra z zapisanym juz ukladem to
            UkGrA=UkGrAKopia;
        }
        if( ( UkGrBKopia==UkGrB )==WynikMS::wygrana )
        { // jesli znaleziony uklad wygra z zapisanym juz ukladem to
            UkGrB=UkGrBKopia;
        }



        }//end for(int k=i+1;k<7;k++)
    }//end for(int i=0,i<6;i++)
// teraz powinnysmy miec najsilniejszy uklad gracza A i Gracza B, wiec je poprostu porownujemy
return (UkGrA==UkGrB);
}//end Stol::PorownajUkladyGr(int iNrGrA,int iNrGrB)
//-------------------------------------

void Stol::IncrementujWPetli(int *iLicznik)
{
    if(*iLicznik >= (m_iLicznikGraczyCalosc-1) ) // jezeli Ilicznik jest na sktraju tablicy badz poza nia
        *iLicznik=0;
    else
        (*iLicznik)++;
}

void Stol::IncrementujWPetliGr(int *iNrGr)
{
        IncrementujWPetli(iNrGr);
    while(false==CzyGraczGra(*iNrGr))    // jezeli zaczynajacy nie gra to powtarzamy operacje
        {
            IncrementujWPetli(iNrGr);
        }
}
void Stol::DecrementujWPetliGr(int *NrGr)
{
    bool Flag=true;
    while(true==Flag)
    {
        (*NrGr)-=1;
        if(*NrGr<0)
            *NrGr=m_iLicznikGraczyCalosc-1;
        if(true==CzyGraczGra(*NrGr))
            Flag=false;

    }
}

void Stol::IncrementujWPetliGrR(int *iNrGr)
{
        IncrementujWPetli(iNrGr);
    while(false==CzyGraczGraR(*iNrGr))    // jezeli zaczynajacy nie gra to powtarzamy operacje
        {
            IncrementujWPetli(iNrGr);
        }
}
void Stol::DecrementujWPetliGrR(int *NrGr)
{
    bool Flag=true;
    while(true==Flag)
    {
        (*NrGr)-=1;
        if(*NrGr<0)
            *NrGr=m_iLicznikGraczyCalosc-1;
        if(true==CzyGraczGraR(*NrGr))
            Flag=false;

    }
}
bool Stol::CzyGraczGra(int nrGracza)
{
    if(true==m_CzyGraczAktywny[nrGracza])
        return true;
    else
        return false;
}
bool Stol::CzyGraczGraR(int nrGracza)
{
    if(true==m_CzyGraczWRundzie[nrGracza])
        return true;
    else
        return false;
}
void Stol::AllInTabClear()
{
    for(int i=0;i<10;i++)
    {
        m_CzyGraczAllIn[i]=false;
        m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn=0;
        m_TabelaAllIn[i].m_NrGraczaAllIn=-1;
    }
    m_NajwyzszyNaAllIn=-1;
}



Stol::Stol(int iSmallBlind, int iIloscPieniedzy) // stol gotow do gry
{
    m_iPulaPieniedzyAktualnie=0;
    m_FlagPartiaWToku=false;
    m_FlagKoniecGry=false;
    m_iLicznikGraczyCalosc=0;
    m_iLiczbaGraczyAktualnie=0;
    m_iNumerGraczaRoz=0;
    m_iBigBlind=(2*iSmallBlind);
    m_iSmallBlind=iSmallBlind;
    m_iPieniadzeStartowe=iIloscPieniedzy;
    m_iLicznikRund=0;
    m_iStawkaNaGraczaAkt=0;

    m_iLicznikRund=0;
    for(int i=0;i<10;i++)
    {
        m_CzyGraczAktywny[i]=false;
    }
    m_FlagPartiaWToku=false;
    AllInTabClear();
    for(int i=0;i<5;i++)
    {
        m_KartyNaStole[i]=Karta(Wartosc::BlankW,Kolor::BlankK);
    }
}
void Stol::Wyrownaj(int NrGr)
{
    int iRoznica=(m_iStawkaNaGraczaAkt-m_TabGraczyKopia[NrGr].m_WlozonePieniadze);

    if( iRoznica>0)
    {
        if( (m_TabGraczyKopia[NrGr].m_iIloscPieniedzy)>=iRoznica) // jezeli gracz ma dosc hajsu zeby wyrownac
        {
            m_TabGraczyKopia[NrGr].m_iIloscPieniedzy-=iRoznica;
            m_iPulaPieniedzyAktualnie+=iRoznica;
        }
        else // jezeli nie ma to yolo in
        {

            m_NajwyzszyNaAllIn++;
            m_TabelaAllIn[m_NajwyzszyNaAllIn].m_NrGraczaAllIn=NrGr;
            m_iPulaPieniedzyAktualnie+=m_TabGraczyKopia[NrGr].m_iIloscPieniedzy;
            m_TabelaAllIn[m_NajwyzszyNaAllIn].m_iPulaPieniedzyDlaGraczaAllIn=(m_iPulaPieniedzyAktualnie+ m_TabGraczyKopia[NrGr].m_iIloscPieniedzy); // pula to sie rowna aktualna pula + resztka hajsu
            m_TabGraczyKopia[NrGr].m_iIloscPieniedzy=0; // juz nie ma resztki hajsu
        }

    }

}
void Stol::WyznanieGr(int NrGr,Odzywka enWyznanie, int Hajs)
{
    for(int i=0; i<m_iLicznikGraczyCalosc;i++)
    {
        m_TabGraczy[i]->GraczZlicytowal( NrGr,  enWyznanie, Hajs);
    }
}
bool Stol::CzyGraczAllIn(int NrGr)
{
    for(int i=0;i<=m_NajwyzszyNaAllIn;i++)
    {
        if(NrGr==m_TabelaAllIn[i].m_NrGraczaAllIn) // jesli nasz grasz jest w ktoryms all in
            return true;
    }
    return false; // jesli go nie znalazl w tabelach all in to znaczy ze nie all in
}
int Stol::ZnajdzNrGrAllIn(int NrGr)
{
    for(int k=0;k<=m_NajwyzszyNaAllIn;k++)
    {
        if(false==CzyGraczAllIn(NrGr))
            return 9;
        if(m_TabelaAllIn[k].m_NrGraczaAllIn==NrGr)
        {
            return k;
        }
    }
    return 9;
}

void Stol::PierwszaLicytacja()
{
    int iNrGrAkt=m_iNumerGraczaRoz;
    Karta OdslonietaKarta;
    int iLiczbaGrCall=0;
    bool FlagLicytacjaTrwa=true;
    bool FlagDrugaSzansa=false;
    int iLicznikBezpieczenstwa=0;
    int iIleBigBlindPodbija=0;
    int iIlePodbija=0;
    Odzywka enWypowiedz=Odzywka::Pass;
    if(m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy>=m_iSmallBlind)
    {
        m_TabGraczy[iNrGrAkt]->WszedlesSmallBlind();
        m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy-=m_iSmallBlind;
        m_iPulaPieniedzyAktualnie+=m_iSmallBlind;
    }
    else // yolo in
    {
        m_TabGraczy[iNrGrAkt]->WszedlesSmallBlind();
        m_NajwyzszyNaAllIn++;
        m_TabelaAllIn[m_NajwyzszyNaAllIn].m_NrGraczaAllIn=iNrGrAkt;
        m_iPulaPieniedzyAktualnie+=m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy;
        m_TabelaAllIn[m_NajwyzszyNaAllIn].m_iPulaPieniedzyDlaGraczaAllIn=(m_iPulaPieniedzyAktualnie+ m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy); // pula to sie rowna aktualna pula + resztka hajsu
        m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy=0; // juz nie ma resztki hajsu
    }

    IncrementujWPetliGrR(&iNrGrAkt);

    if(m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy>=m_iBigBlind)
    {
        m_TabGraczy[iNrGrAkt]->WszedlesBigBlind();
        m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy-=m_iBigBlind;
        m_iPulaPieniedzyAktualnie+=m_iBigBlind;
    }
    else // yolo in
    {
        m_TabGraczy[iNrGrAkt]->WszedlesBigBlind();
        m_NajwyzszyNaAllIn++;
        m_TabelaAllIn[m_NajwyzszyNaAllIn].m_NrGraczaAllIn=iNrGrAkt;
        m_iPulaPieniedzyAktualnie+=m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy;
        m_TabelaAllIn[m_NajwyzszyNaAllIn].m_iPulaPieniedzyDlaGraczaAllIn=(m_iPulaPieniedzyAktualnie+ m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy); // pula to sie rowna aktualna pula + resztka hajsu
        m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy=0; // juz nie ma resztki hajsu
    }


    while(true==FlagLicytacjaTrwa&&iLicznikBezpieczenstwa<1000)
    {
        IncrementujWPetliGrR(&iNrGrAkt);
        if(CzyGraczAllIn(iNrGrAkt)) // czy ten koles all in
        {
            iLiczbaGrCall++;
        }
        else
        {
            enWypowiedz=m_TabGraczy[iNrGrAkt]->odOdzywka();
            if(Odzywka::Check==enWypowiedz)
            {
                m_TabGraczy[iNrGrAkt]->BladOdzywki(Blad::NieMoznaZrobicCheckWTejLicytacji);
                if(false==FlagDrugaSzansa)
                {
                    DecrementujWPetliGrR(&iNrGrAkt);
                    FlagDrugaSzansa=true;
                }
                else
                {
                    m_TabGraczy[iNrGrAkt]->BladOdzywki(Blad::Dyskwalifikacja);
                    m_TabGraczy[iNrGrAkt]->PrzegranaCalejGry( -1);
                    FlagDrugaSzansa=false;
                    m_CzyGraczAktywny[iNrGrAkt]=false;
                    m_iLiczbaGraczyAktualnie-=1;
                    m_iLiczbaGraczyWRundzie-=1;
                }




            }

            if(Odzywka::Pass==enWypowiedz)
            {
                m_CzyGraczWRundzie[iNrGrAkt]=false;
                m_iLiczbaGraczyWRundzie-=1;
                WyznanieGr(iNrGrAkt, Odzywka::Pass,0);
            }
            if(Odzywka::Call)
            {
                Wyrownaj(iNrGrAkt);
                iLiczbaGrCall++;
                WyznanieGr(iNrGrAkt, Odzywka::Call,0);
            }
            if(Odzywka::Raise==enWypowiedz)
            {
                iIleBigBlindPodbija=m_TabGraczy[iNrGrAkt]->IlePieniedzy();
                Wyrownaj(iNrGrAkt);
                if(false==CzyGraczAllIn(iNrGrAkt))
                {
                    if( m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy>= (iIleBigBlindPodbija*m_iBigBlind) )// jesli ma hajs
                    {
                        iIlePodbija=(iIleBigBlindPodbija*m_iBigBlind);
                        m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy-=iIlePodbija;
                        m_iPulaPieniedzyAktualnie+=iIlePodbija;
                        WyznanieGr(iNrGrAkt, Odzywka::Raise,iIleBigBlindPodbija);
                        iLiczbaGrCall=0;

                    }
                    else // jesli nie ma to allIn
                    {
                        m_TabGraczy[iNrGrAkt]->BladOdzywki(Blad::NieMaszDoscPieniedzy);
                        WyznanieGr(iNrGrAkt, Odzywka::Call,0);
                        iLiczbaGrCall++;
                    }

                }//end if(false==CzyGraczAllIn(iNrGrAkt))
                else
                {
                    WyznanieGr(iNrGrAkt, Odzywka::Call,0);
                }
            }
        }



        if(m_iLiczbaGraczyWRundzie<=iLiczbaGrCall)// jesli wszycy czekali to koniec licytacji
            FlagLicytacjaTrwa=false;
        if(1>=m_iLiczbaGraczyWRundzie) // wiekszy rowny na wszelki
        {
            FlagLicytacjaTrwa=false;
            m_FlagKoniecRundy=true;
        }
        iLicznikBezpieczenstwa++;
    }


    for(int k=0;k<3;k++)  // po licytacji odslaniamy 3 karty
    {
        OdslonietaKarta=m_Talia.Draw();
        for(int i=0;i<m_iLicznikGraczyCalosc;i++)
        {
            if(true==CzyGraczGra(i))
                m_TabGraczy[i]->OdsloniecieKartyZeStolu(OdslonietaKarta);
        }
        m_KartyNaStole[k]=OdslonietaKarta;
    }
}



void Stol::Licytacja()
{
    int iNrGrAkt=m_iNumerGraczaRoz;
    Karta OdslonietaKarta;
    int iLiczbaGrCheck=0;
    bool FlagDrugaSzansa=false;
    int iLicznikBezpieczenstwa=0;
    int iIleBigBlindPodbija=0;
    int iIlePodbija=0;
    Odzywka enWypowiedz=Odzywka::Pass;
    bool FlagLicytacjaTrwa=true;
    while(true==FlagLicytacjaTrwa&&iLicznikBezpieczenstwa<1000)
    {
        IncrementujWPetliGrR(&iNrGrAkt);
        if(CzyGraczAllIn(iNrGrAkt)) // czy ten koles all in
        {
            iLiczbaGrCheck++;
        }
        else
        {
            enWypowiedz=m_TabGraczy[iNrGrAkt]->odOdzywka();
            if(Odzywka::Check==enWypowiedz)
            {
                if(m_TabGraczyKopia[iNrGrAkt].m_WlozonePieniadze>=m_iStawkaNaGraczaAkt)
                {
                    WyznanieGr(iNrGrAkt, Odzywka::Check,0);
                    iLiczbaGrCheck++;
                    FlagDrugaSzansa=false;
                }
                else // jezeli nie wyrownal to
                {
                    m_TabGraczy[iNrGrAkt]->BladOdzywki(Blad::MusiszCoNajmniejWyrownac);
                    if(false==FlagDrugaSzansa)
                    {
                        DecrementujWPetliGrR(&iNrGrAkt);
                        FlagDrugaSzansa=true;
                    }
                    else
                    {
                        m_TabGraczy[iNrGrAkt]->BladOdzywki(Blad::MusiszCoNajmniejWyrownac);
                        m_TabGraczy[iNrGrAkt]->BladOdzywki(Blad::Dyskwalifikacja);
                        m_TabGraczy[iNrGrAkt]->PrzegranaCalejGry( -1);
                        FlagDrugaSzansa=false;
                        m_CzyGraczAktywny[iNrGrAkt]=false;
                        m_iLiczbaGraczyAktualnie-=1;
                        m_iLiczbaGraczyWRundzie-=1;
                    }
                }




            }

            if(Odzywka::Pass==enWypowiedz)
            {
                m_TabGraczy[iNrGrAkt]->BladOdzywki(Blad::NieMoznaZrobicPassWTejLicytacji);
                if(false==FlagDrugaSzansa)
                {
                    DecrementujWPetliGrR(&iNrGrAkt);
                    FlagDrugaSzansa=true;
                }
                else
                {
                    m_TabGraczy[iNrGrAkt]->BladOdzywki(Blad::NieMoznaZrobicPassWTejLicytacji);
                    m_TabGraczy[iNrGrAkt]->BladOdzywki(Blad::Dyskwalifikacja);
                    m_TabGraczy[iNrGrAkt]->PrzegranaCalejGry( -1);
                    FlagDrugaSzansa=false;
                    m_CzyGraczAktywny[iNrGrAkt]=false;
                    m_iLiczbaGraczyAktualnie-=1;
                    m_iLiczbaGraczyWRundzie-=1;
                }
            }
            if(Odzywka::Call==enWypowiedz)
            {
                FlagDrugaSzansa=false;
                Wyrownaj(iNrGrAkt);
                iLiczbaGrCheck=0;
                WyznanieGr(iNrGrAkt, Odzywka::Call,0);
            }
            if(Odzywka::Raise==enWypowiedz)
            {
                FlagDrugaSzansa=false;
                iIleBigBlindPodbija=m_TabGraczy[iNrGrAkt]->IlePieniedzy();
                Wyrownaj(iNrGrAkt);
                if(false==CzyGraczAllIn(iNrGrAkt))
                {
                    if( m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy>= (iIleBigBlindPodbija*m_iBigBlind) )// jesli ma hajs
                    {
                        iIlePodbija=(iIleBigBlindPodbija*m_iBigBlind);
                        m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy-=iIlePodbija;
                        m_iPulaPieniedzyAktualnie+=iIlePodbija;
                        WyznanieGr(iNrGrAkt, Odzywka::Raise,iIleBigBlindPodbija);
                        iLiczbaGrCheck=0;

                    }
                    else                     {
                        m_TabGraczy[iNrGrAkt]->BladOdzywki(Blad::NieMaszDoscPieniedzy);
                        WyznanieGr(iNrGrAkt, Odzywka::Call,0);
                        iLiczbaGrCheck++;
                    }//end if( m_TabGraczyKopia[iNrGrAkt].m_iIloscPieniedzy>= (iIleBigBlindPodbija*m_BigBlind) )

                }//end if(false==CzyGraczAllIn(iNrGrAkt))
                else
                {
                    WyznanieGr(iNrGrAkt, Odzywka::Call,0);
                    iLiczbaGrCheck++;
                }
            }
        }



        if(m_iLiczbaGraczyWRundzie<=iLiczbaGrCheck)// jesli wszycy czekali to koniec licytacji
            FlagLicytacjaTrwa=false;
        if(1>=m_iLiczbaGraczyWRundzie) // wiekszy rowny na wszelki
        {
            FlagLicytacjaTrwa=false;
            m_FlagKoniecRundy=true;
        }
        iLicznikBezpieczenstwa++;
    }


    OdslonietaKarta=m_Talia.Draw();
    if(m_KartyNaStole[3]==Karta(Wartosc::BlankW,Kolor::BlankK)) // jesli czwartej karty nie ma to ja zapisz
        m_KartyNaStole[3]=OdslonietaKarta;
    else
        m_KartyNaStole[4]=OdslonietaKarta; // jesli jest czwarta to zapisz piata
    for(int i=0;i<m_iLicznikGraczyCalosc;i++)
    {
        if(true==CzyGraczGra(i))
            m_TabGraczy[i]->OdsloniecieKartyZeStolu(OdslonietaKarta);
    }

}

void Stol::PokazWszystkieKarty()
{
    Karta Karty[2];
    for(int i=0; i<m_iLicznikGraczyCalosc;i++)
    {
        Karty[0]=m_TabGraczyKopia[i].m_KartyGracza[0];
        Karty[1]=m_TabGraczyKopia[i].m_KartyGracza[1];
        for(int k=0;k<m_iLicznikGraczyCalosc;k++)
        {
            m_TabGraczy[k]->PokazKarty(i, Karty[0], Karty[1]); // pokazuje wszystkim karty gracza i.
        }
    }
}




void Stol::Runda()
{
    m_FlagKoniecRundy=false;
    m_iStawkaNaGraczaAkt=0;
    m_iLiczbaGraczyWRundzie=m_iLiczbaGraczyAktualnie;
    m_iPulaPieniedzyAktualnie=0;
    int r=0;//bokompilator sie sypie
    int iPulaDoPodzialu=0;
    int iNadwyzka=0;
    int iStash=0;
    int TabRemisow[10];
    int iLicznikRemisow; // to jest licznik do najwyzszej pozycji w tabeli
    int iCzescRozdana=0;
    iLicznikRemisow=-1;
    for (int i=0;i<10;i++)
        TabRemisow[i]=0;

    bool bCzyCosPrzegral=false;
    bool bCzyZremisowal=false;
    bool FlagKtosWygral=false;

    for(int i=0;i<m_iLicznikGraczyCalosc;i++) // ustaw graczy na aktywnych
    {
        if(true==m_CzyGraczAktywny[i])
        {
            m_CzyGraczWRundzie[i]=true;
        }
    }
    Karta KartyStash[2];
    KartyStash[0]=Karta(Wartosc::BlankW,Kolor::BlankK);
    KartyStash[1]=Karta(Wartosc::BlankW,Kolor::BlankK);
    for(int i=0;i<m_iLicznikGraczyCalosc;i++) // przydziel karty, przydziel hajs
    {
        if(true==CzyGraczGra(i))
        {
            KartyStash[0]=m_Talia.Draw();
            KartyStash[1]=m_Talia.Draw();
            m_TabGraczy[i]->OdsloniecieKartyGracza(KartyStash[0]);
            m_TabGraczy[i]->OdsloniecieKartyGracza(KartyStash[1]);
            m_TabGraczyKopia[i].m_KartyGracza[0]=KartyStash[0];
            m_TabGraczyKopia[i].m_KartyGracza[1]=KartyStash[1];
        }
    }
    AllInTabClear();
    PierwszaLicytacja();
    if(false==m_FlagKoniecRundy)
        Licytacja();
    if(false==m_FlagKoniecRundy)
        Licytacja();
//-------------------------------------------------- jesli odpadli wszyscy oprocz jednego
    if(true==m_FlagKoniecRundy)
    {
        for(int i=0;i<m_iLicznikGraczyCalosc;i++)
        {
            if(true==CzyGraczGraR(i))
            {
                if(false==CzyGraczAllIn(i))
                {
                    m_TabGraczy[i]->ZwyciestwoPartii(m_iPulaPieniedzyAktualnie);
                    for(int k=0;k<m_iLicznikGraczyCalosc;k++) // reszcie wysylamy ze sa frajerami i przegrali
                    {
                        if(k!=i)
                            m_TabGraczy[k]->PrzegranaPartii(i);
                    }
                }
            }
            else
            {
                for(int k=0;k<=m_NajwyzszyNaAllIn;k++)
                {
                    if(m_TabelaAllIn[k].m_NrGraczaAllIn==i)
                    {
                        iStash=k; // to jest numer wygrywajacego gracza w tabeli all in
                    }
                }
                m_TabGraczy[i]->ZwyciestwoPartii(m_TabelaAllIn[iStash].m_iPulaPieniedzyDlaGraczaAllIn);
                iPulaDoPodzialu=m_iPulaPieniedzyAktualnie-m_TabelaAllIn[iStash].m_iPulaPieniedzyDlaGraczaAllIn; // ile jest w pulach bonusowych
                for(int l=0;l<m_iLicznikGraczyCalosc;l++)// dla wszystkich graczy
                {
                    if(CzyGraczAllIn(l))// czy jest all In
                    {
                        if(ZnajdzNrGrAllIn(l)>iStash) // jesli zostal zmuszony do wejscia yoloin po naszym zwyciescy to ma prawo do zwrotu czesci hajsow,
                            //chyba ze musial wejsc allin ebz zadnych hajsow po zwyciescy
                        {
                            iNadwyzka=(m_TabelaAllIn[l].m_iPulaPieniedzyDlaGraczaAllIn-m_TabelaAllIn[iStash].m_iPulaPieniedzyDlaGraczaAllIn);
                            if(iNadwyzka>0)
                            {
                                m_TabGraczy[l]->ZwrotPieniedzy(iNadwyzka);
                            }
                        }
                    }
                    else // jeslie nie yolo in
                    {
                        iNadwyzka=(m_TabGraczyKopia[l].m_WlozonePieniadze-m_TabelaAllIn[iStash].m_iPulaPieniedzyDlaGraczaAllIn);
                    }

                }//end for(int l=0;l<m_iLicznikGraczyCalosc;l++)



            }

        }//end for(int i=0;i<m_iLicznikGraczyCalosc;i++)

        PokazWszystkieKarty();
        m_iLicznikRund++;
        OdrzucLudziBezHajsu();
        IncrementujWPetliGr(&m_iNumerGraczaRoz);
        if(m_iLiczbaGraczyAktualnie<=1)
        m_FlagKoniecGry=true;
        return;
    }//endif(true==m_FlagKoniecRundy)

    // jesli jednak licytacja skonczyla sie normalnie
    iStash=0;
    iPulaDoPodzialu=m_iPulaPieniedzyAktualnie;
    //No to teraz jak licytacja sie skonczy
    for(int i=0;i<=m_NajwyzszyNaAllIn;i++)// lecimy od gosci na All in od tych z najmniejszym hajsem // i JEST NUMER ALL IN
    {
        iLicznikRemisow=-1; // zerowanie zmiennych
        for (int i=0;i<10;i++)
        TabRemisow[i]=0;




        for(int k=0;k<m_iLicznikGraczyCalosc;k++) // koles musi wygrac wszystko zeby zgarnac hajsy/
        {
            if(true==CzyGraczGraR(k)&&(k!=m_TabelaAllIn[i].m_NrGraczaAllIn && (ZnajdzNrGrAllIn(k)>i || false== CzyGraczAllIn(k)) )) // czy wylosowany gracz gra w tej rundzie, i czy nie walczylbym z samym soba
            { // sprawdzamy czy gracz k gra, czy jest rozny od gracza ktory jest w all in jako i, sprawzdamy czy jest gracz k tez all in to ma byc wyzej w hierarchi all in, inaczej nei walcza ze soba
                if(WynikMS::przegrana==PorownajUkladyGr(m_TabelaAllIn[i].m_NrGraczaAllIn,k)) // jesli przegral z kimkolwiek to znaczy ze traci caly hajs i wypad z giereczki
                {
                    bCzyCosPrzegral=true;
                }

                if(WynikMS::remis==PorownajUkladyGr(m_TabelaAllIn[i].m_NrGraczaAllIn,k))
                {
                   bCzyZremisowal=true;
                   iLicznikRemisow++;
                   TabRemisow[iLicznikRemisow]=k; // zapisujemy z kim zremisowalismy

                }
            }//endif(true==CzyGraczGraR(k)&&(k!=ZnajdzNrGrAllIn(i) )


        }

        if(false==bCzyCosPrzegral && false==bCzyZremisowal)
        {
           if(false==FlagKtosWygral)
           {
                iPulaDoPodzialu-= (m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn-iCzescRozdana);
                m_TabGraczy[m_TabelaAllIn[i].m_NrGraczaAllIn]->ZwyciestwoPartii(m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn- iCzescRozdana);
                iCzescRozdana+=(m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn-iCzescRozdana);
                FlagKtosWygral=true;
           }
           else
           {
                iPulaDoPodzialu-= (m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn-iCzescRozdana);
                m_TabGraczy[m_TabelaAllIn[i].m_NrGraczaAllIn]->ZwrotPieniedzy(m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn- iCzescRozdana);
                iCzescRozdana+=(m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn-iCzescRozdana);

           }
        }
        if(false==bCzyCosPrzegral && true==bCzyZremisowal)
        {
            iPulaDoPodzialu-= (m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn-iCzescRozdana);
            m_TabGraczy[ZnajdzNrGrAllIn(i)]->ZwrotPieniedzy(int((m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn - iCzescRozdana) /(iLicznikRemisow+2))); // jeden remis da nam zerowy licznik remisow <bedzie wskazywac na zerowa pozycje w tabeli>
            // bierzemy to co zostalo z puli dla tego gracza i rozdajemy remisujacym
            for(r=0;r<=iLicznikRemisow;r++)
                m_TabGraczy[TabRemisow[r]]->ZwrotPieniedzy(int((m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn-iCzescRozdana) /(iLicznikRemisow+2)));
            iCzescRozdana+=(m_TabelaAllIn[i].m_iPulaPieniedzyDlaGraczaAllIn-iCzescRozdana);
        }

    }//endfor (int i=0;i<=m_NajwyzszyNaAllIn;i++)

    //------------------------------------------- Po all inn


    iLicznikRemisow=-1;
    for (int i=0;i<10;i++)
        TabRemisow[i]=0;







    for(int i=0;i<m_iLicznikGraczyCalosc;i++)
    {
        bool bCzyCosPrzegral=false;
        bool bCzyZremisowal=false;

        if(false==CzyGraczAllIn(i)&&true==CzyGraczGra(i)&&true==CzyGraczGraR(i))
            for(int k=0;k<m_iLicznikGraczyCalosc;k++)
                if((false==CzyGraczAllIn(k))&&(true==CzyGraczGra(k))&&(true==CzyGraczGraR(k))&&(k!=i))// jesli to pelno prawni gracze ezs katkerino
                {
                    if(WynikMS::przegrana==PorownajUkladyGr(i,k))
                    {
                        bCzyCosPrzegral=true;
                    }
                    if(WynikMS::remis==PorownajUkladyGr(i,k))
                    {
                        bCzyZremisowal=true;
                        iLicznikRemisow++;
                        TabRemisow[iLicznikRemisow]=k;
                    }
                }
        if((false==bCzyCosPrzegral)&&(false==bCzyZremisowal))
        {
            if(false==FlagKtosWygral)
                m_TabGraczy[i]->ZwyciestwoPartii(iPulaDoPodzialu);
            else
                m_TabGraczy[i]->ZwrotPieniedzy(iPulaDoPodzialu);
        }
        if((false==bCzyCosPrzegral)&&(true==bCzyZremisowal))
        {
            m_TabGraczy[i]->ZwrotPieniedzy(iPulaDoPodzialu/(iLicznikRemisow+2));
            for(int r=0;r<=iLicznikRemisow;r++)
                {
                    m_TabGraczy[TabRemisow[r]]->ZwrotPieniedzy(iPulaDoPodzialu/(iLicznikRemisow+2));
                }

        }
    }//end for(int i=0;i<m_iLicznikGraczyCalosc;i++)







    PokazWszystkieKarty();
    m_iLicznikRund++;
    OdrzucLudziBezHajsu();
    if(m_iLiczbaGraczyAktualnie<=1)
        m_FlagKoniecGry=true;
    IncrementujWPetliGr(&m_iNumerGraczaRoz);



}



void Stol::OdrzucLudziBezHajsu()
{
    for(int i=0;i<m_iLicznikGraczyCalosc;i++)
    {
        if(true==CzyGraczGra(i))
        {
            if(m_TabGraczyKopia[i].m_iIloscPieniedzy<=0)
            {
                m_CzyGraczAktywny[i]=false;
                m_iLiczbaGraczyAktualnie-=1;
            }
        }
    }
}













void Stol::Graj()
{
    int iLicznikBezpieczenstwa=0;

    m_FlagPartiaWToku=true;
    for(int i=0;i<m_iLicznikGraczyCalosc;i++) // przydziel karty, przydziel hajs
    {
        m_CzyGraczAktywny[i]=true;

        m_TabGraczy[i]->Wywolanie(i,m_iLiczbaGraczyAktualnie,m_iPieniadzeStartowe,m_iSmallBlind);
        m_TabGraczyKopia[i].m_iNumerGracza=i;
        m_TabGraczyKopia[i].m_iIloscPieniedzy=m_iPieniadzeStartowe;
        m_TabGraczyKopia[i].m_WlozonePieniadze=0;
    }

    while (false==m_FlagKoniecGry && iLicznikBezpieczenstwa<100)
    {
        Runda();
        iLicznikBezpieczenstwa++;
    }//end while


    if(iLicznikBezpieczenstwa<100)

    {
        for(int i=0;m_iLicznikGraczyCalosc;i++)
        {
            if(true==m_CzyGraczAktywny[i]) // jak znajdziesz aktywnego gracza jedynego aka zwyciesce
            {
                m_TabGraczy[i]->ZwyciestwoCalejGry(); // jemu daj sie cieszyc
                for(int k=0;k<m_iLicznikGraczyCalosc;k++)
                {
                    if(false==m_CzyGraczAktywny[k])
                        m_TabGraczy[k]->PrzegranaCalejGry(i); // reszcie powiedz kto wygral
                }
            }
        }
    }



}






/////////////////--------------------------------------------------------------
int main()
{
    Karta testk(Wartosc::Dziesiatka,Kolor::Kier);
    Karta testk2(Wartosc::Walet,Kolor::Kier);
    Karta testk3(Wartosc::As,Kolor::Kier);
    Karta testk4(Wartosc::Dwojka,Kolor::Kier);
    Karta testk5(Wartosc::Krol,Kolor::Trefl);

    Karta testb(Wartosc::As,Kolor::Pik);
    Karta testb2(Wartosc::Dziesiatka,Kolor::Trefl);
    Karta testb3(Wartosc::Walet,Kolor::Pik);
    Karta testb4(Wartosc::Dwojka,Kolor::Pik);
    Karta testb5(Wartosc::Dama,Kolor::Pik);
    Karta TabKart[5]={testk5,testk4,testk3,testk2,testk};
    Stol TestStol(100,10000);
    Talia Tal;
    Karta karStash(Wartosc::BlankW,Kolor::BlankK);
    //cout << Wartosc(testk.m_w) << endl;
    /*
    std::sort(TabKart,TabKart+5,CustomSort);
    for(int i=0;i<5;i++)
    {
        cout<<i<<" : "<<TabKart[i].m_w<<"/"<<TabKart[i].m_k<<endl;
    }
    */
    /*
    UkladCaly a;
    UkladCaly b;
    a=ZnajdzUklad(testk5,testk4,testk3,testk2,testk);
    b=ZnajdzUklad(testb5,testb4,testb3,testb2,testb);
    cout<<"uklad A: "<<a.m_Uklad<<" || B: "<<b.m_Uklad<<endl;
    for(int i=0;i<5;i++)
    {
        cout<<"WOlne od najwyzszej A: "<<a.m_WolneOdNajwyzszej[i]<<" || B: "<<b.m_WolneOdNajwyzszej[i]<<endl;

    }
    cout<<"b==a : "<< WynikMS(b==a)<<endl;
    cout<<"a==b : "<< WynikMS(a==b)<<endl;
    */


    for(int i=0;i<10;i++)
    {
        karStash=Tal.Draw();
        cout<<Wartosc(karStash.m_w)<<"  |  "<<Kolor(karStash.m_k)<<endl;
    }




    return 0;
}
