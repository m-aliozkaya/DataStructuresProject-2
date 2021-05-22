#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Her ogrencide bulunan ders yapisi
struct ders
{
	char derskodu[10];
	char dersadi[50];
	ders* sonraki;
};

struct ogrenci
{
	char ogrno[15];
	char ad[30];
	char soyad[30];
	ders* dersdugumu;
	ogrenci* sonraki;
};

// Ogrencilerin baglantili listesi
struct ogrenciListesi
{
	ogrenci* baslangic;
	int dugumSayisi;
	void olustur();
	char* dosyaadi;
	FILE* ogrenciler;
	void dosyadan_oku(string path);
	void ekle(ogrenci*);
	void listele();
	void dosyaya_yaz();
	void kesisimBul();
	void listebosalt();
	void kapat();
	void ara(string pattern, int type);
	void ogrenciAra();
	void ogrenciSil();
};

// Kendisine verilen ogrenciyi ekrana yazdiran algoritma
void yazdir(ogrenci* ogr) {
	ders* drs;

	cout << ogr->ad << " " << ogr->soyad << " " << ogr->ogrno << " ";
	drs = ogr->dersdugumu;
	while (drs)
	{
		cout << " " << drs->derskodu << " " << drs->dersadi;
		drs = drs->sonraki;
	}
	cout << endl;
}

// OgrenciListesini ilgili dosyalardan okuyup olusturur.
void ogrenciListesi::olustur()
{
	baslangic = NULL;
	dugumSayisi = 0;

	dosyadan_oku("eng101.txt");
	dosyadan_oku("fiz101.txt");
	dosyadan_oku("mat101.txt");
}

// Dosyalardan okuyan algoritma
void ogrenciListesi::dosyadan_oku(string path)
{
	string satir = "", ad, soyad, numara, dersAdi, dersKodu;
	int sayac = 0;

	ifstream dosyaOku(path);

	//Dosyadan verileri okuyup numara, ad ve soyad þeklinde bölüyoruz.
	if (dosyaOku.is_open())
	{
		while (getline(dosyaOku, satir))
		{
			if (sayac == 0)
			{
				sayac += 1;
				int x = satir.find(" ");
				dersKodu = satir.substr(0, x);
				dersAdi = satir.substr(x + 1);
			}
			else
			{
				int x = satir.find("\t");
				int x2 = satir.find_last_of(" ");
				numara = satir.substr(0, x);
				ad = satir.substr(x + 1, x2 - x);
				soyad = satir.substr(x2 + 1);

				ogrenci* ogr = new ogrenci;
				strcpy_s(ogr->ad, ad.c_str());
				strcpy_s(ogr->soyad, soyad.c_str());
				strcpy_s(ogr->ogrno, numara.c_str());

				ders* drs = new ders;
				strcpy_s(drs->dersadi, dersAdi.c_str());
				strcpy_s(drs->derskodu, dersKodu.c_str());

				ogr->dersdugumu = drs;
				ekle(ogr);
			}
		}
		dosyaOku.close();
	}
}

// Okunan ogrenciyi ogrenci listesine ekleyen algoritma
void ogrenciListesi::ekle(ogrenci* eklenecek)
{
	ogrenci* tara, * arka{};
	ogrenci* yeni;
	tara = baslangic;
	yeni = new ogrenci;
	*yeni = *eklenecek;
	yeni->sonraki = NULL;
	yeni->dersdugumu->sonraki = NULL;

	if (baslangic == NULL)
	{
		baslangic = yeni;
		dugumSayisi++;
		return;
	}

	if (strcmp(yeni->ogrno, baslangic->ogrno) < 0)
	{
		yeni->sonraki = baslangic;
		baslangic = yeni;
		dugumSayisi++;
		return;
	}

	while (tara && (strcmp(yeni->ogrno, tara->ogrno) > 0))
	{
		arka = tara;
		tara = tara->sonraki;
	}

	if (tara && strcmp(yeni->ogrno, tara->ogrno) == 0)
	{
		ders* d = tara->dersdugumu;

		while (d)
		{
			if (!d->sonraki)
			{
				d->sonraki = yeni->dersdugumu;
				delete yeni;
				break;
			}
			d = d->sonraki;
		}
		return;
	}

	if (tara)
	{
		yeni->sonraki = tara;
		arka->sonraki = yeni;
	}
	else
	{
		arka->sonraki = yeni;
	}
	dugumSayisi++;
}

// Ogrenci listesindeki tum ogrencileri konsola yazdýrýr
void ogrenciListesi::listele() {
	ogrenci* tara;
	tara = baslangic;

	while (tara)
	{
		yazdir(tara);

		tara = tara->sonraki;
	}
}

// Ogrenci listesindeki ogrencileri "ogrenciler.txt" adýndaki dosyaya yazar
void ogrenciListesi::dosyaya_yaz()
{
	ogrenci* tara = baslangic;
	ders* ders;
	string satir = "";
	ofstream dosyaYaz("ogrenciler.txt");
	if (dosyaYaz.is_open())
	{
		while (tara)
		{
			dosyaYaz << tara->ogrno << " " << tara->ad << " " << tara->soyad;
			ders = tara->dersdugumu;
			while (ders)
			{
				dosyaYaz << " " << ders->derskodu << " " << ders->dersadi;
				ders = ders->sonraki;
			}
			dosyaYaz << "\n";
			tara = tara->sonraki;
		}
		dosyaYaz.close();
	}
}

// Kodu verilen iki derse ayný anda giren ogrencileri bulur
void ogrenciListesi::kesisimBul()
{
	string kod1, kod2;
	cout << "Kesisimini bulmak istediginiz derslerin kodlarini giriniz" << endl;
	cout << "Kod 1 :>";
	cin >> kod1;
	cout << "Kod 2 :>";
	cin >> kod2;

	ogrenci* baslangicPtr = baslangic;

	while (baslangicPtr)
	{
		int sayac = 0;
		ders* dersPtr = baslangicPtr->dersdugumu;
		while (dersPtr)
		{

			if (strcmp(dersPtr->derskodu, kod1.c_str()) == 0)
			{
				sayac++;
			}
			else if (strcmp(dersPtr->derskodu, kod2.c_str()) == 0)
			{
				sayac++;
			}
			if (sayac == 2)
			{
				yazdir(baslangicPtr);
			}
			dersPtr = dersPtr->sonraki;

		}

		baslangicPtr = baslangicPtr->sonraki;
	}
}

// Liste icin bellekten ayrilan yeri bosaltan algoritma
void ogrenciListesi::listebosalt()
{
	ogrenci* p;
	while (baslangic)
	{
		p = baslangic;
		baslangic = baslangic->sonraki;
		delete p;
	}
	dugumSayisi = 0;
}

// Ogrencilistesini kapatir, bellekteki yerini temizler
void ogrenciListesi::kapat()
{
	dosyaya_yaz();
	listebosalt();
}

// Kendisine verilen ogrenciyi pattern ve tipine gore (numara ya da soyad) bulur
void ogrenciListesi::ara(string pattern, int type)
{
	ogrenci* tara;
	tara = baslangic;
	string aranacak;

	while (tara)
	{
		if (type == 1)
		{
			aranacak = tara->ogrno;
		}
		else
		{
			aranacak = tara->soyad;
		}

		if (strncmp(aranacak.c_str(), pattern.c_str(), strlen(pattern.c_str())) == 0)
		{
			yazdir(tara);
		}

		tara = tara->sonraki;
	}

}

// Kullanicidan aramak istedigi kelimeyi alir ve istedigi aramayi yaptirir
void ogrenciListesi::ogrenciAra() {
	char secenek;
	string pattern;
	cout << "Bir islem seciniz" << endl;
	cout << "N: Numaraya Gore Bul" << endl;
	cout << "S: Soyada Gore Bul" << endl;
	cin >> secenek;

	switch (secenek)
	{
	case 'N':
	case 'n':
		cout << "Numarasini giriniz" << endl;
		cin >> pattern;
		ara(pattern, 1);
		break;
	case 'S':
	case 's':
		cout << "Soyadini giriniz" << endl;
		cin >> pattern;
		ara(pattern, 2);
		break;
	default:
		cout << "Lütfen doðru bir seçeneði iþaretleyiniz";
		break;
	}
}

void ogrenciListesi::ogrenciSil() {

	string ogrenciNo;

	cout << "Ogrenci No Giriniz :>" << endl;
	cin >> ogrenciNo;

	ogrenci* tara, * arka{};
	tara = baslangic;

	while (tara && (strcmp(tara->ogrno, ogrenciNo.c_str()) != 0))
	{
		arka = tara;
		tara = tara->sonraki;
	}

	if (tara && strcmp(tara->ogrno, ogrenciNo.c_str()) == 0)
	{
		if (arka != NULL)
		{
			arka->sonraki = tara->sonraki;
		}
		else {
			baslangic = baslangic->sonraki;
		}

		delete tara->dersdugumu;
		delete tara;
		dugumSayisi--;
		cout << "Ogrenci basariyla silindi" << endl;
		return;	
	}
}