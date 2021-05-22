// VeriYapilariOdev2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ogrenci.h"

// Ogrencilerin bulundugu ogrenci listesinden olusmus nesne
ogrenciListesi defter;

void menuyazdir()
{
    cout << endl << endl;
    cout << "Ogrenci Listesi Uygulamasi" << endl;
    cout << "Bir islem seciniz" << endl;
    cout << "A: Kayitlari Listele" << endl;
    cout << "E: Kesisim Bul" << endl;
    cout << "G: Kayit Ara" << endl;
    cout << "S: Ogrenci Sil" << endl;
    cout << "T: Ogrenciyi Dersten Sil" << endl;
    cout << "C: Cikis" << endl;
    cout << endl;
    cout << "Bir secenek giriniz {A, E, G, S, T, C} : ";
}

bool islemyap(char secim)
{
    char x = '*';
    string a, b;
    bool sonlandir = false;
    switch (secim)
    {
    case 'A':
    case 'a':
        defter.listele();
        break;
    case 'E':
    case 'e':
        defter.kesisimBul();
        break;
    case 'G':
    case 'g':
        defter.ogrenciAra();
        break;
    case 'S':
    case 's':
        defter.ogrenciSil();
        break;
    case 'T':
    case 't':
        defter.dersSil();
        break;
    case 'C':
    case 'c':
        cout << "Programi sonlandirmak istedi?inize emin misiniz? (E/H):";
        cin >> secim;
        if (secim == 'E' || secim == 'e')
            sonlandir = true;
        break;
    default:
        cout << "Hata: Yanlis giris yaptiniz" << endl;
        cout << "Tekrar deneyiniz {A, E, G, S, B, C} :";
        cin >> secim;
        sonlandir = islemyap(secim);
        break;
    }
    return sonlandir;
}

int main()
{
    defter.olustur();

    bool bitir = false;
    char secim;
    while (!bitir)
    {
        menuyazdir();
        cin >> secim;
        bitir = islemyap(secim);
    }
    
    defter.kapat();
}
