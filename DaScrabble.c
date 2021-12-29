#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//Deklarasi Modul Menu
void mulaiPermainan();
void tampilLeaderboard();
void tampilHTP();
void tampilTentang();
void endProgram();

//Deklarasi Modul Pengisian Data Pemain
int  registPemain();
int  pilihPemain();
void inputNama(int pilihan);
int  pilihLevel();


typedef struct {
	char huruf;
	int nilaiHuruf;
	int jumlah;
} DataHuruf;

typedef struct {
	DataHuruf isiHuruf;
	bool isLetter2;
	bool isLetter3;
	bool isWord2;
	bool isWord3;
} IsiPapan;

typedef struct{
   char nama_pemain[30];
   int score;
   char huruf[7];
   bool iskomputer;
}DataPemain;

//Kamus Data Global
IsiPapan Papan;
DataPemain Pemain[2];

int main(){
	//Kamus Data
	int pilihMenu;
	
	//Program
	do{
		system("cls");
		printf("DaScrabble\n\n");
		printf("1. Main\n");
		printf("2. Papan Peringkat\n");
		printf("3. Cara Bermain\n");
		printf("4. Tentang\n");
		printf("5. Keluar\n");
		printf("\nMasukkan nomor menu : ");
		scanf("%d", &pilihMenu);
		
		switch(pilihMenu){
			case 1 : mulaiPermainan(); 
				break;
			case 2 : tampilLeaderboard(); 
				break;
			case 3 : tampilHTP(); 
				break;
			case 4 : tampilTentang(); 
				break;
			case 5 : endProgram(); 
				break;
			default : printf("Menu tidak tersedia.");
		}
	} while(pilihMenu < 1 || pilihMenu > 5);
	
	return 0;
}

void mulaiPermainan(){
	int level;
	
	system("cls");
	level = registPemain();
	system("cls");
	printf("Pemain 1 : %s", Pemain[0].nama_pemain);
	printf("\nPemain 2 : %s", Pemain[1].nama_pemain);
	
	switch(level){
		case 1 : printf("\nLevel : Easy");
			break;
		case 2 : printf("\nLevel : Medium");
			break;
		case 3 : printf("\nLevel : Hard");
			break;
	}
}

void tampilLeaderboard(){
	system("cls");
	printf("Leaderboard");
}

void tampilHTP(){
	system("cls");
	printf("Cara Bermain");
}

void tampilTentang(){
	system("cls");
	printf("Tentang Aplikasi");
}

void endProgram(){
	system("cls");
	printf("Terima kasih sudah bermain DaScrabble");
}

int registPemain(){
	int pilihanPemain;
	int pilihanLevel;
	
	pilihanPemain = pilihPemain();
	inputNama(pilihanPemain);
	pilihanLevel = pilihLevel();
	
	return pilihanLevel;
}

int  pilihPemain(){
	int pilih;
	int pemain;
	
	do{
		system("cls");
		printf("Pilih Pemain\n");
		printf("1. manusia vs manusia\n");
		printf("2. manusia vs komputer\n\n");
		printf("Masukkan nomor pilihan : ");
		scanf("%d", &pilih);
		
		switch(pilih){
			case 1 : pemain = 2;
				break;
			case 2 : pemain = 1;
				break;
			default : printf("Pilihan tidak tersedia.");
		}
	} while(pilih > 2 || pilih < 1);
	
	return pemain;
}
void inputNama(int pilihan){
	system("cls");
	printf("Pastikan mengisi nama dengan benar, karena hanya 1 kali kesempatan.\n\n");
	if(pilihan == 2){
		printf("Nama Pemain 1 (maks. 30 karakter): ");
		scanf("%s", Pemain[0].nama_pemain);
		printf("\nNama Pemain 2 (maks. 30 karakter): ");
		scanf("%s", Pemain[1].nama_pemain);
	}
	else{
		printf("Nama Pemain 1 (maks. 30 karakter): ");
		scanf("%s", Pemain[0].nama_pemain);
		Pemain[1].nama_pemain[0] = 'D';
		Pemain[1].nama_pemain[1] = 'a';
		Pemain[1].nama_pemain[2] = 's';
		Pemain[1].nama_pemain[3] = 'c';
		Pemain[1].nama_pemain[4] = 'o';
		Pemain[1].nama_pemain[5] = 'm';
	}
}

int  pilihLevel(){
	int pilih;
	int level;
	
	do{
		system("cls");
		printf("Pilih level\n");
		printf("1. Easy\n");
		printf("2. Medium\n");
		printf("3. Hard\n\n");
		printf("Masukkan pilihan level : ");
		scanf("%d", &pilih);
		
		switch(pilih){
			case 1 : level = 1;
				break;
			case 2 : level = 2;
				break;
			case 3 : level = 3;
				break;
			default : printf("Level tidak tersedia.");
		}
		
	} while(pilih < 1 || pilih > 3);
	
	return level;
}



