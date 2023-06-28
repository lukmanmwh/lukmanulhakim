/*
================================
NAMA  : LUKMANUL HAKIM
NIM   : 22040037
KELAS : 2B
TEMA  : KASIR APOTEK
================================
*/



#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <iomanip>

using namespace std;

void cls() {
    system("cls");
}

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Produk {
    string nama;
    int harga;
    string kode;
};

void tambahProduk(Produk dataProduk[], int& jumlahProduk) {
    Produk barang;

    gotoXY(3, 1);
    cout << "Masukkan nama obat: ";
    cin.ignore();
    getline(cin, barang.nama);

    gotoXY(3, 2);
    cout << "Masukkan harga obat: ";
    cin >> barang.harga;

    cin.ignore(); // Membersihkan karakter newline sebelum mengambil input kode obat

    gotoXY(3, 3);
    cout << "Masukkan kode obat: ";
    getline(cin, barang.kode);

    // Find the appropriate position to insert the new product
    int insertPos = 0;
    while (insertPos < jumlahProduk && barang.harga > dataProduk[insertPos].harga) {
        insertPos++;
    }

    // Shift the existing products to make room for the new product
    for (int i = jumlahProduk; i > insertPos; i--) {
        dataProduk[i] = dataProduk[i - 1];
    }

    // Insert the new product at the appropriate position
    dataProduk[insertPos] = barang;
    jumlahProduk++;

    gotoXY(3, 5);
    cout << "Produk obat berhasil ditambahkan!" << endl;
    gotoXY(3, 7);
    system("pause");
}


void tampilkanDaftarObat(Produk dataProduk[], int jumlahProduk) {
    
    gotoXY(2, 1);cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    gotoXY(2, 2);cout << "| No |       Nama       |     Harga    |   Kode obat   |" << endl;
    gotoXY(2, 3);cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    for (int i = 0; i < jumlahProduk; i++) {
        gotoXY(2, 4 + i);
        cout << "| " << i + 1 << "  | ";
        cout << setw(16) << left << dataProduk[i].nama << " | ";
        cout << setw(12) << right << dataProduk[i].harga << " | ";
        cout << setw(13) << right << dataProduk[i].kode << " |" << endl;
    }
    gotoXY(2, 10);cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

bool compareProduk(const Produk& a, const Produk& b) {
    return a.harga < b.harga;
}

void bubbleSortProduk(Produk dataProduk[], int jumlahProduk) {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (dataProduk[j].harga > dataProduk[j + 1].harga) {
                swap(dataProduk[j], dataProduk[j + 1]);
            }
        }
    }

    gotoXY(2, 12);
    cout << "Produk berhasil diurutkan berdasarkan harga!" << endl;
}

void cariProduk(Produk dataProduk[], int jumlahProduk, const string& keyword) {
    bool found = false;

    gotoXY(3, 7);
    cout << "Hasil Pencarian untuk keyword '" << keyword << "':" << endl;

    for (int i = 0; i < jumlahProduk; i++) {
        if (dataProduk[i].nama.find(keyword) != string::npos) {
            gotoXY(3, 8 + i);
            cout << "Nama: " << dataProduk[i].nama << ", Harga: " << dataProduk[i].harga << ", Kode: " << dataProduk[i].kode << endl;
            found = true;
        }
    }

    if (!found) {
        gotoXY(3, 10);
        cout << "Produk tidak ditemukan." << endl;
    }

    gotoXY(3, 15);
    system("pause");
}

void prosesTransaksi(Produk dataProduk[], int jumlahProduk) {
    int nomorProduk;
    int jumlahBeli;
    char lagi;

    do {
        cls();

        gotoXY(3, 1);
        cout << "=== Proses Transaksi ===" << endl;
		gotoXY(3, 2);
        tampilkanDaftarObat(dataProduk, jumlahProduk);

        gotoXY(3, 12);
        cout << "Pilih nomor produk yang akan dibeli: ";
        cin >> nomorProduk;

        if (nomorProduk >= 1 && nomorProduk <= jumlahProduk) {
            gotoXY(3, 13);
            cout << "Masukkan jumlah yang akan dibeli: ";
            cin >> jumlahBeli;

            if (jumlahBeli > 0) {
                int totalHarga = dataProduk[nomorProduk - 1].harga * jumlahBeli;
                gotoXY(3, 15);
                cout << "Total Harga: " << totalHarga << endl;

                // Tambahkan ke resume transaksi
                Produk barang = dataProduk[nomorProduk - 1];
                for (int i = 0; i < jumlahBeli; i++) {
                    dataProduk[jumlahProduk] = barang;
                    jumlahProduk++;
                }
            } else {
                gotoXY(3, 15);
                cout << "Jumlah beli harus lebih dari 0!" << endl;
            }
        } else {
            gotoXY(3, 13);
            cout << "Nomor produk tidak valid!" << endl;
        }

        gotoXY(3, 17);
        cout << "Apakah ingin membeli lagi? (Y/N): ";
        cin >> lagi;

    } while (toupper(lagi) == 'Y');

    cls();
    gotoXY(3, 1);
    cout << "Transaksi selesai!" << endl;
    gotoXY(3, 3);
    system("pause");
}


void tampilkanResumeTransaksi(Produk dataProduk[], int jumlahProduk) {
    int subtotal = 0;
    int total = 0;

    gotoXY(3, 2);
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    gotoXY(3, 3);
    cout << "| No |       Nama       | 	Harga 	|" << endl;
    gotoXY(3, 4);
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    for (int i = 0; i < jumlahProduk; i++) {
        gotoXY(3, 5 + i);
        cout << "| " << i + 1 << "  | ";
        cout << setw(16) << left << dataProduk[i].nama << " | ";
        cout << setw(10) << right << dataProduk[i].harga << " |" << endl;

        subtotal += dataProduk[i].harga;
    }
    gotoXY(3, 11);
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;

    total = subtotal;

    gotoXY(3, 16 + jumlahProduk);
    gotoXY(3, 17);
    cout << "Subtotal: " << subtotal << endl;
    gotoXY(3, 18 + jumlahProduk);
    gotoXY(3, 19);
    cout << "Total   : " << total << endl;

    gotoXY(3, 22);
    system("pause");
}


int main() {
    const int MAX_PRODUK = 100;
    Produk dataProduk[MAX_PRODUK];
    int jumlahProduk = 0;
    int pilihan;
    int transaksi;
    int resumeTransaksi;
    string nama, kelas;
    int nim;
    
    gotoXY(0, 0);
    cout<<"harap login terlebih dahulu";
    gotoXY(0, 2);
    cout << "Masukkan NIM: ";
    cin >> nim;
    cin.ignore();
    gotoXY(0, 3);
    cout << "Masukkan Nama: ";
    getline(cin, nama);
    gotoXY(0, 4);
    cout << "Masukkan Kelas: ";
    getline(cin, kelas);
    
    cls();

    gotoXY(17, 1);cout << "=========================[ PROGRAM KASIR APOTEK  ]=====================\n";
    gotoXY(17, 2);cout << "|         NIM        |            NAMA            |        KELAS      |\n";
    gotoXY(17, 3);cout << "=======================================================================\n";
    gotoXY(17, 4);cout << "|      " << nim << "      |       " << nama << "       |        " << kelas << "	       |\n";
    gotoXY(17, 5);cout << "=======================================================================\n\n";
	gotoXY(17, 10);system("pause");

    do {
        cls();

        gotoXY(3, 1);
        cout << "=== Program kasir apotek ===" << endl;
        gotoXY(3, 2);
        cout << "1. Tambah obat" << endl;
        gotoXY(3, 3);
        cout << "2. Tampilkan obat" << endl;
        gotoXY(3, 4);
        cout << "3. Urutkan obat berdasarkan harga (Bubble Sort)" << endl;
        gotoXY(3, 5);
        cout << "4. Cari obat" << endl;
        gotoXY(3, 6);
        cout << "5. Proses Transaksi" << endl;
        gotoXY(3, 7);
        cout << "6. Tampilkan resume transaksi" << endl;
        gotoXY(3, 8);
        cout << "7. Keluar" << endl;
        gotoXY(3, 10);
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cls();

        switch (pilihan) {
            case 1:
                tambahProduk(dataProduk, jumlahProduk);
                break;
            case 2:
                tampilkanDaftarObat(dataProduk, jumlahProduk);
                gotoXY(3, 12);
                system("pause");
                break;
            case 3:
                bubbleSortProduk(dataProduk, jumlahProduk);
                tampilkanDaftarObat(dataProduk, jumlahProduk);
                gotoXY(3, 12);
                system("pause");
                break;
            case 4: {
                cin.ignore(); // Clear the input buffer
                gotoXY(3, 1);
                cout << "Masukkan keyword pencarian: ";
                string keyword;
                getline(cin, keyword);
                cariProduk(dataProduk, jumlahProduk, keyword);
                break;
            }
            case 5:
                prosesTransaksi(dataProduk, jumlahProduk);
                break;
            case 6:
                tampilkanResumeTransaksi(dataProduk, jumlahProduk);
                break;
            case 7:
                gotoXY(3, 1);
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                gotoXY(3, 3);
                system("pause");
                break;
            default:
                gotoXY(3, 1);
                cout << "Pilihan tidak valid!" << endl;
                gotoXY(3, 3);
                system("pause");
                break;
        }
    } while (pilihan != 7);
    
    system("cls");
    gotoXY(17, 1);cout << "=========================[ PROGRAM KASIR TOKO OBAT ]===================\n";
    gotoXY(17, 2);cout << "|         NIM        |            NAMA            |        KELAS      |\n";
    gotoXY(17, 3);cout << "=======================================================================\n";
    gotoXY(17, 4);cout << "|      " << nim << "      |       " << nama << "       |    " << kelas << "	   |\n";
    gotoXY(17, 5);cout << "=======================================================================\n\n";
	gotoXY(17, 10);system("pause");

    return 0;
}

