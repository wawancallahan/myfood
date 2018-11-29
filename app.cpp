#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iomanip>
 
using namespace std;


int i;
bool found;
 
struct Antrian {
	int no;
	string nama;
 	struct Makanan *makananNext;
 	struct Antrian *antrianNext;
} *AntrianListHead,
  *AntrianListTail;
 
struct Makanan {
	int no;
 	string nama;
 	string tipe;
 	int jumlah;
 	int harga;
 	struct Makanan *makananNext;
} *MakananListHead,
  *MakananListTail;
 
void clearScreen();
void initialize();
void makananSeed();
void garisData(int max);

int MakananEmpty();
int MakananCount();
int MakananNomor();
struct Makanan *cariMakanan(int no);
void MakananView(bool denganNomor = false);
struct Makanan *saveMakanan(int noMakanan, int jumlahPesan);
void lihatMakanan(Makanan *MakananList);
int TotalHargaMakanan(Makanan *MakananList);
void MakananAdd();
void MakananRemove(int no);

struct Antrian *cariAntrian(int no);
void AntrianMakananView(int no);
int AntrianEmpty();
int AntrianCount();
int AntrianNomor();
void AntrianView();
void AntrianRemove(int no);
struct Antrian *AntrianAdd(string input);

int isNumber(std::string input)
{
	bool isNumeric = true;
	
	for (int i = 0; i < input.length(); i++) {
		if ( ! isdigit(input.at(i))) {
			isNumeric = false;
			break;
		}
	}
	
	return isNumeric;
}
  
int main()
{
	initialize();
	
	int cinMenu,
		pilihDaftarPesan,
		jumlahPesan,
		pesanan = 0,
		noAntrian = 0,
		noMakanan = 0,
		inputBayar,
		total = 0;
		
	Antrian *newAntrian = NULL;
	Makanan *newMakanan = NULL;
	Makanan *tempMakanan = NULL;
	Makanan *getMakanan = NULL;
	Makanan *getTempMakanan = NULL;
		
	string input,
		   inputMenu;
	
	labelMenu:
	
	cout << "Restoran Wik Wik Wik" << endl;
	cout << "1. Antri Untuk Memesan" << endl;
	cout << "2. Lihat Daftar Menu" << endl;
	cout << "3. Lihat Antrian" << endl; 
	cout << "4. Keluar" << endl;
	cout << ">> ";
	getline(cin, inputMenu);
		
	if (inputMenu.length() == 0 || ! isNumber(inputMenu)) {
		cout << "Tolong cek kembali inputan anda";
		
		getch();
		clearScreen();
		
		goto labelMenu;	
	}
	
	cinMenu = atoi(inputMenu.c_str());
	
	switch (cinMenu) {
		case 1:
			
			if (MakananCount() <= 0) {
				cout << "Tambahkan Makanan terlebih Dahulu";
				
				getch();
				clearScreen();
				goto labelMenu;
			}
			
			clearScreen();
			
			labelAntrianBaru:
			
			cout << "Antrian. " << AntrianNomor() << endl;
			
			cout << "Nama : ";
			getline(cin, input);
			
			newAntrian = AntrianAdd(input);
			
			labelAntrianPesanan:
			
			cout << endl << "Silahkan Pesan" << endl;
			MakananView(true);
			
			cout << ">> ";
			getline(cin, inputMenu);
		
			if (inputMenu.length() == 0 || ! isNumber(inputMenu)) {
				cout << "Tolong cek kembali inputan anda";
				
				getch();
				clearScreen();
				
				cout << "Antrian. " << newAntrian->no << endl;
			
				cout << "Nama : " << newAntrian->nama << endl;
				
				goto labelAntrianPesanan;	
			}
			
			pilihDaftarPesan = atoi(inputMenu.c_str());
			
			if (pilihDaftarPesan <= 0 || pilihDaftarPesan > MakananCount()) {
				cout << "Data pesanan tidak ditemukan ";
				getch();
				
				clearScreen();
				
				cout << "Antrian. " << newAntrian->no << endl;
			
				cout << "Nama : " << newAntrian->nama << endl;
				
				goto labelAntrianPesanan;
			}
			
			// Masukkan pesanan
			
			labelJumlahMakanan:
			
			cout << "Jumlah : ";
			getline(cin, inputMenu);
		
			if (inputMenu.length() == 0 || ! isNumber(inputMenu)) {
				cout << "Tolong cek kembali inputan anda" << endl;
				
				goto labelJumlahMakanan;	
			}
			
			jumlahPesan = atoi(inputMenu.c_str());
			
			newMakanan = NULL;
			newMakanan = saveMakanan(pilihDaftarPesan, jumlahPesan);
			
			found = false;
			
			if (newAntrian->makananNext == NULL) {
				newAntrian->makananNext = newMakanan;
			} else {
				getMakanan = newAntrian->makananNext;
				
				while (getMakanan != NULL) {
					
					if (getMakanan->no == newMakanan->no) {
						getMakanan->jumlah += newMakanan->jumlah;
						
						found = true;
						
						break;
					}
					
					getMakanan = getMakanan->makananNext;
				}
				
				if (found == false) {
					newMakanan->makananNext = newAntrian->makananNext;
					newAntrian->makananNext = newMakanan;	
				}
			}
			
			pesanan++;
			
			cout << "Pesanan berhasil ditambah ";
			getch();
			clearScreen();
			
			labelMenuAntrian:
				
			cout << "Antrian. " << newAntrian->no << endl;
		
			cout << "Nama : " << newAntrian->nama << endl;
			
			cout << "1. Pesan lagi" << endl;
			cout << "2. Lihat Pesanan" << endl;
			cout << "3. Hapus Pesanan" << endl;
			cout << "4. Bayar Pesanan" << endl;
			cout << "5. Batalkan" << endl;
			cout << ">> ";
			getline(cin, inputMenu);
		
			if (inputMenu.length() == 0 || ! isNumber(inputMenu)) {
				cout << "Tolong cek kembali inputan anda";
				
				getch();
				clearScreen();
				
				goto labelMenuAntrian;	
			}
			
			pilihDaftarPesan = atoi(inputMenu.c_str());
			
			switch (pilihDaftarPesan) {
				case 1:
					clearScreen();
					goto labelAntrianPesanan;
					break;
				case 2:
					lihatMakanan(newAntrian->makananNext);
					break;
				case 3:
					
					if (pesanan == 0) {
						cout << "Pesanan kosong" << endl;
						
						getch();
						clearScreen();
						
						cout << "Antrian. " << newAntrian->no << endl;
						cout << "Nama : " << newAntrian->nama << endl;
						
						goto labelMenuAntrian;
					}
					
					labelHapusPesanan:
					
					lihatMakanan(newAntrian->makananNext);
					
					cout << ">> ";
					getline(cin, inputMenu);
		
					if (inputMenu.length() == 0 || ! isNumber(inputMenu)) {
						cout << "Tolong cek kembali inputan anda";
						
						getch();
						clearScreen();
						
						goto labelHapusPesanan;	
					}
					
					pilihDaftarPesan = atoi(inputMenu.c_str());
					
					if (pilihDaftarPesan <= 0 || pilihDaftarPesan > pesanan) {
						cout << "Pesanan tidak ditemukan" << endl;
						
						getch();
						clearScreen();
						goto labelHapusPesanan;
					}
					
					i = 0;
					
					getMakanan = newAntrian->makananNext;
					getTempMakanan = NULL;
					
					while (getMakanan != NULL) {
						
						i++;
						
						if (i == pilihDaftarPesan) {
							
							if (getTempMakanan == NULL) {
								newAntrian->makananNext = getMakanan->makananNext;
							} else {
								getTempMakanan->makananNext = getMakanan->makananNext;
							}
							
							break;
						}
						
						getTempMakanan = getMakanan;
						getMakanan = getMakanan->makananNext;
					}
					
					pesanan--;
					
					cout << "Pesanan dihapus" << endl;
					break;
				case 4:
					
					if (pesanan == 0) {
						cout << "Pesanan kosong" << endl;
						
						getch();
						clearScreen();
						
						cout << "Antrian. " << newAntrian->no << endl;
						cout << "Nama : " << newAntrian->nama << endl;
						
						goto labelMenuAntrian;
					}
					
					lihatMakanan(newAntrian->makananNext);
					
					cout << endl;
					
					
					total = TotalHargaMakanan(newAntrian->makananNext);
					
					cout << "Total : " << total  << endl;
					
					labelBayar:
					
					cout << "Bayar : ";
					getline(cin, inputMenu);
		
					if (inputMenu.length() == 0 || ! isNumber(inputMenu)) {
						cout << "Tolong cek kembali inputan anda" << endl;
					
						goto labelBayar;	
					}
					
					inputBayar = atoi(inputMenu.c_str());
					
					if (total > inputBayar) {
						
						cout << "Pembayaran Kurang" << endl;
						
						goto labelBayar;
					}
					
					cout << "Silahkan Tunggu Pesanan Anda ";
					
					if ( AntrianListHead == NULL ) {
						AntrianListHead = newAntrian;
						AntrianListTail = newAntrian;
					} else {
						AntrianListTail->antrianNext = newAntrian;
						AntrianListTail = newAntrian;
					}
					
					getch();
					clearScreen();
					
					goto labelMenu;
					break;
				case 5:
					
					cout << "Pesanan dibatalkan" << endl;
					
					getch();
					clearScreen();
					
					goto labelMenu;
					
					break;
				default:
					cout << "Tolong cek kembali inputan anda";
			} 
			
			if (cinMenu != 5) {
				getch();
				clearScreen();
				goto labelMenuAntrian;
			}
			
			break;
		case 2:
			if (MakananEmpty()) {
				cout << "Makanan belum tersedia" << endl;
			} else {
				
				clearScreen();
				
				labelMakanan:
				
				MakananView(true);
				
				cout << "1. Tambah Makanan" << endl;
				cout << "2. Hapus Makanan" << endl;
				cout << "3. Kembali" << endl;
				cout << ">> ";
				getline(cin, inputMenu);
		
				if (inputMenu.length() == 0 || ! isNumber(inputMenu)) {
					cout << "Tolong cek kembali inputan anda";
					
					getch();
					clearScreen();
					
					goto labelMakanan;	
				}
				
				pilihDaftarPesan = atoi(inputMenu.c_str());
				
				switch (pilihDaftarPesan) {
					case 1:
						MakananAdd();
						
						cout << "Makanan berhasil ditambah";
						break;
					case 2:
						
						labelNoMakanan:
						
						cout << "No : ";
						getline(cin, inputMenu);
		
						if (inputMenu.length() == 0 || ! isNumber(inputMenu)) {
							cout << "Tolong cek kembali inputan anda" << endl;
							
							goto labelNoMakanan;	
						}
						
						noMakanan = atoi(inputMenu.c_str());
						
						if (noMakanan <= 0 || noMakanan > MakananCount()) {
							cout << "Makanan tidak ditemukan";
							
							getch();
							clearScreen();
							goto labelMakanan;
						}
							
						MakananRemove(noMakanan);
						
						cout << "Makanan berhasil dihapus";
						
						break;
					case 3:
						clearScreen();
				
						goto labelMenu;
						break;
					default:
						cout << "Tolong cek kembali inputan anda";
						break;
				}
				
				getch();
				clearScreen();
				
				goto labelMakanan;
			}
			
			break;
		case 3:
			
			if (AntrianEmpty()) {
				cout << "Tidak ada yang mengantri untuk saat ini" << endl;
			} else {
				
				clearScreen();
				
				labelAntrian:
				
				AntrianView();
				
				cout << "1. Panggil Antrian" << endl;
				cout << "2. Kembali" << endl;
				cout << ">> ";
				getline(cin, inputMenu);
		
				if (inputMenu.length() == 0 || ! isNumber(inputMenu)) {
					cout << "Tolong cek kembali inputan anda";
					
					getch();
					clearScreen();
					
					goto labelAntrian;	
				}
				
				pilihDaftarPesan = atoi(inputMenu.c_str());
				
				switch (pilihDaftarPesan) {
					case 1:
						
						labelNoAntrian:
						
						cout << "No : ";
						getline(cin, inputMenu);
		
						if (inputMenu.length() == 0 || ! isNumber(inputMenu)) {
							cout << "Tolong cek kembali inputan anda" << endl;
							
							goto labelNoAntrian;	
						}
						
						noAntrian = atoi(inputMenu.c_str());
						
						if (noAntrian <= 0 || noAntrian > AntrianCount()) {
							cout << "Antrian tidak ditemukan";
							
							getch();
							clearScreen();
							goto labelAntrian;
						}
						
						AntrianMakananView(noAntrian);
							
						cout << "No Antrian Segera Dipanggil" << endl;
							
						AntrianRemove(noAntrian);
						
						break;
					case 2:
						clearScreen();
						
						goto labelMenu;
						
						break;
					default:
						cout << "Tolong cek kembali inputan anda";
						break;
				}
				
				getch();
				clearScreen();
				
				goto labelAntrian;
			}
			
			break;
		case 4:
			cout << "Terima Kasih" << endl;
			
			break;
		default:
			cout << "Tolong cek kembali inputan anda";
	} 
	
	if (cinMenu != 4) {
		getch();
		clearScreen();
		goto labelMenu;
	}
	
	return 1;
}
 
void initialize()
{
 	AntrianListHead = NULL;
	AntrianListTail = NULL;
 	MakananListHead = NULL;
	MakananListTail = NULL;
	 	
 	makananSeed();
}

void makananSeed()
{	
	string makananArray[10] = {
		"Makanan I",
		"Makanan II",
		"Makanan III",
		"Makanan IV",
		"Makanan V",
		"Makanan VI",
		"Makanan VII",
		"Makanan VIII",
		"Makanan IX",
		"Makanan X"
	};
	
	string makananTipeArray[10] = {
		"Ikan",
		"Udang",
		"Sapi",
		"Betina",
		"Laki Laki",
		"Perempuan",
		"Pria",
		"Kambing",
		"Kodok",
		"Katak"
	};
	
	int makananHargaArray[10] = {
		10000,
		15000,
		25000,
		30000,
		12000,
		15000,
		18000,
		21000,
		23000,
		11000
	};
	
	
	for (i = 0; i < 10; i++) {
		Makanan *newMakanan = new Makanan;
		newMakanan->no = i + 1;
		newMakanan->nama = makananArray[i];
		newMakanan->tipe = makananTipeArray[i];
		newMakanan->jumlah = 0;
		newMakanan->harga = makananHargaArray[i];
		newMakanan->makananNext = NULL;
		
		if (MakananListHead == NULL) {
			MakananListHead = newMakanan;
			MakananListTail = newMakanan;
		} else {
			MakananListTail->makananNext = newMakanan;
			MakananListTail = newMakanan;
		}	
	}
}

struct Makanan *cariMakanan(int no)
{
	Makanan *MakananList = MakananListHead;
	
	Makanan *MakananPilih = NULL;
	
	while (MakananList != NULL) {
		
		if (MakananList->no == no) {
			MakananPilih = MakananList;
			break;
		}
	
		MakananList = MakananList->makananNext;
	}	
	
	return MakananPilih;
}

int MakananEmpty()
{
	return MakananListHead == NULL;
}

int MakananCount()
{
	if (MakananListTail == NULL) {
		return 0;
	} else {
		return MakananListTail->no;
	}
}

int MakananNomor()
{
	if (MakananListTail == NULL) {
		return 1;
	} else {
		return MakananListTail->no + 1;
	}
}

struct Makanan *saveMakanan(int noMakanan, int jumlahPesan) {
	Makanan *getMakanan = cariMakanan(noMakanan);
	Makanan *newMakanan = new Makanan;
	
	newMakanan->no = getMakanan->no;
	newMakanan->nama = getMakanan->nama;
	newMakanan->tipe = getMakanan->tipe;
	newMakanan->jumlah = jumlahPesan;
	newMakanan->harga = getMakanan->harga;
	newMakanan->makananNext = NULL;
	
	return newMakanan;
			
}

void MakananView(bool denganNomor)
{
	Makanan *MakananList = MakananListHead;
				
	cout << setiosflags(ios::fixed);
	
	if (denganNomor) {
		garisData(86);
	} else {
		garisData(82);	
	}
	
	cout << endl;
	
	if (denganNomor) {
		cout.width(4);
		cout << left << "No";
	}
	
	cout.width(2);
	cout << left << "|";
	cout.width(25);
	cout << left << "Nama";
	cout.width(2);
	cout << left << "|";
	cout.width(25);
	cout << left << "Tipe";
	cout.width(2);
	cout << left << "|";
	cout.width(25);
	cout << left << "Harga";
	cout.width(2);
	cout << left << "|" << endl;
		
	if (denganNomor) {
		garisData(86);
	} else {
		garisData(82);	
	}
	
	cout << endl;
	
	i = 1;
		
	while (MakananList != NULL) {
		
		if (denganNomor) {
			cout.width(4);
			cout << left << i++;
		}
		
		cout.width(2);
		cout << left << "|";
		cout.width(25);
		cout << left << MakananList->nama;
		cout.width(2);
		cout << left << "|";
		cout.width(25);
		cout << left << MakananList->tipe;
		cout.width(2);
		cout << left << "|";
		cout.width(25);
		cout << left << MakananList->harga;
		cout.width(2);
		cout << left << "|" << endl;
	
		MakananList = MakananList->makananNext;
	}	
	
	if (denganNomor) {
		garisData(86);
	} else {
		garisData(82);	
	}
	
	
	cout << endl;
}

void lihatMakanan(Makanan *MakananList)
{
	Makanan *getMakanan = MakananList;
	
	cout << setiosflags(ios::fixed);
	garisData(96);
	
	cout << endl;
	
	cout.width(2);
	cout << left << "|";
	cout.width(5);
	cout << left << "No";
	cout.width(2);
	cout << left << "|";
	cout.width(25);
	cout << left << "Pesanan";
	cout.width(2);
	cout << left << "|";
	cout.width(5);
	cout << left << "Qty";
	cout.width(2);
	cout << left << "|";
	cout.width(25);
	cout << left << "Harga";
	cout.width(2);
	cout << left << "|";
	cout.width(25);
	cout << left << "Total";
	cout.width(2);
	cout << left << "|" << endl;
	
	garisData(96);
	
	cout << endl;
		
	i = 1;
	int total = 0;
	
	while (getMakanan != NULL) {
		cout.width(2);
		cout << left << "|";
		cout.width(5);
		cout << left << i++;
		cout.width(2);
		cout << left << "|";
		cout.width(25);
		cout << left << getMakanan->nama;
		cout.width(2);
		cout << left << "|";
		cout.width(5);
		cout << left << getMakanan->jumlah;
		cout.width(2);
		cout << left << "|";
		cout.width(25);
		cout << left << getMakanan->harga;
		cout.width(2);
		cout << left << "|";
		cout.width(25);
		cout << left << getMakanan->harga * getMakanan->jumlah;
		cout.width(2);
		cout << left << "|" << endl;
		
		total += getMakanan->harga * getMakanan->jumlah;
		
		getMakanan = getMakanan->makananNext;	
	}
	
	garisData(96);
	
	cout << endl;
	
	cout.width(68);
	cout << left << "|";
	cout.width(2);
	cout << left << "|";
	cout.width(25);
	cout << left << total;
	cout.width(2);
	cout << left << "|" << endl;
	
	garisData(96);
	
	cout << endl;	
}

int TotalHargaMakanan(Makanan *MakananList)
{
	Makanan *getMakanan = MakananList;
	
	int total = 0;
	
	while (getMakanan != NULL) {
		total += getMakanan->harga * getMakanan->jumlah;
		getMakanan = getMakanan->makananNext;	
	}
	
	return total;
}

void MakananAdd()
{
	string nama, tipe, inputHarga;
	
	int harga;
	
	cout << "Nama : ";
	getline(cin, nama);
	
	cout << "Tipe : ";
	getline(cin, tipe);
	
	labelMakananHarga:
	
	cout << "Harga :";
	
	getline(cin, inputHarga);
		
	if (inputHarga.length() == 0 || ! isNumber(inputHarga)) {
		cout << "Harga harus berupa angka" << endl;
		
		goto labelMakananHarga;	
	}
	
	harga = atoi(inputHarga.c_str());
	
	Makanan *newMakanan = new Makanan;
	newMakanan->no = MakananNomor();
	newMakanan->nama = nama;
	newMakanan->tipe = tipe;
	newMakanan->jumlah = 0;
	newMakanan->harga = harga;
	newMakanan->makananNext = NULL;
	
	if (MakananListHead == NULL) {
		MakananListHead = newMakanan;
		MakananListTail = newMakanan;
	} else {
		MakananListTail->makananNext = newMakanan;
		MakananListTail = newMakanan;
	}	
}

void MakananRemove(int no)
{
	Makanan *MakananList = MakananListHead,
			*oldMakananList,
			*MakananPilih;
	
	if (MakananList != NULL) {
		
		if (MakananListHead->no == no) {
			MakananListHead = MakananListHead->makananNext;
			
			if (MakananListHead == NULL) {
				MakananListTail = NULL;
			}
		} else {
			if (MakananList->makananNext != NULL) {
				oldMakananList = MakananList->makananNext;
				
				while (oldMakananList != NULL) {
					if (oldMakananList->no == no) {
						MakananList->makananNext = oldMakananList->makananNext;
						break;
					}
					
					MakananList = oldMakananList;
					oldMakananList = oldMakananList->makananNext;
				}
			}
		}
		
		Makanan *MakananCurrent = MakananListHead;
			
		if (MakananCurrent != NULL) {
			int noMakanan = 1;
			
			while (MakananCurrent != NULL) {
				
				MakananCurrent->no = noMakanan++;
				
				MakananCurrent = MakananCurrent->makananNext;
			}
		}	
	}
}

void AntrianMakananView(int no)
{
	Antrian *AntrianSelected = cariAntrian(no);
	
	lihatMakanan(AntrianSelected->makananNext);
}

struct Antrian *cariAntrian(int no)
{
	Antrian *AntrianList = AntrianListHead;
	
	Antrian *AntrianPilih = NULL;
	
	while (AntrianList != NULL) {
		
		if (AntrianList->no == no) {
			AntrianPilih = AntrianList;
			break;
		}
	
		AntrianList = AntrianList->antrianNext;
	}	
	
	return AntrianPilih;
}

int AntrianEmpty()
{
	return AntrianListHead == NULL;	
}

int AntrianCount()
{
	if (AntrianListTail == NULL) {
		return 0;
	} else {
		return AntrianListTail->no;
	}
}

int AntrianNomor()
{
	if (AntrianListTail == NULL) {
		return 1;
	} else {
		return AntrianListTail->no + 1;
	}
}

void AntrianView()
{
	Antrian *AntrianList = AntrianListHead;
	Makanan *MakananList = NULL;
				
	cout << setiosflags(ios::fixed);
	garisData(82);
	
	cout << endl;
	
	cout.width(2);
	cout << left << "|";
	cout.width(25);
	cout << left << "No";
	cout.width(2);
	cout << left << "|";
	cout.width(25);
	cout << left << "Nama";
	cout.width(2);
	cout << left << "|";
	cout.width(25);
	cout << left << "Pesanan - Qty";
	cout.width(2);
	cout << left << "|" << endl;
		
	garisData(82);
	
	cout << endl;
		
	while (AntrianList != NULL) {
		
		cout.width(2);
		cout << left << "|";
		cout.width(25);
		cout << left << AntrianList->no;
		cout.width(2);
		cout << left << "|";
		cout.width(25);
		cout << left << AntrianList->nama;
		cout.width(2);
		cout << left << "|";
		cout.width(25);
		cout << left << "";
		cout.width(2);
		cout << left << "|" << endl;
		
		MakananList = AntrianList->makananNext;
		
		while (MakananList != NULL) {
			
			cout.width(2);
			cout << left << "|";
			cout.width(25);
			cout << left << "";
			cout.width(2);
			cout << left << "|";
			cout.width(25);
			cout << left << "-";
			cout.width(2);
			cout << left << "|";
			cout.width(17);
			cout << left << MakananList->nama;
			cout.width(3);
			cout << left << " - ";
			cout.width(5);
			cout << left << MakananList->jumlah;
			cout.width(2);
			cout << left << "|" << endl;
			
			MakananList = MakananList->makananNext;
		}
		
		garisData(82);
		
		cout << endl;
	
		AntrianList = AntrianList->antrianNext;
	}	
	
}

void AntrianRemove(int no)
{
	Antrian *AntrianList = AntrianListHead;
	
	if (AntrianList != NULL) {
		AntrianListHead = AntrianListHead->antrianNext;
		
		if (AntrianListHead == NULL) {
			AntrianListTail = NULL;
		}
		
		delete AntrianList;
		
		
		Antrian *AntrianCurrent = AntrianListHead;
			
		if (AntrianCurrent != NULL) {
			int noAntrian = 1;
			
			while (AntrianCurrent != NULL) {
				
				AntrianCurrent->no = noAntrian++;
				
				AntrianCurrent = AntrianCurrent->antrianNext;
			}
		}	
	}	
}

struct Antrian *AntrianAdd(string input)
{
	// Tambah Antrian Baru
	Antrian *newAntrian = new Antrian;
	newAntrian->no = AntrianNomor();
	newAntrian->nama = input;
	newAntrian->antrianNext = NULL;
	newAntrian->makananNext = NULL;
	
	return newAntrian;
}

void garisData(int max = 1)
{
	for (i = 0; i < max; i++) {
		cout << "-";
	}
}
 
void clearScreen()
{
 	system("cls");
}
