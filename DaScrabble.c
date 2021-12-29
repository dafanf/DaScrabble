#include<stdio.h>
#include<string.h>
#include<stdbool.h>

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

int main(){
	//Kamus Data
	IsiPapan Papan;
	DataPemain Pemain;
	int pilih;
	printf("DaScrabble\n\n");
	printf("1. Main\n");
	printf("2. Papan Peringkat\n");
	printf("3. Cara Bermain\n");
	printf("4. Tentang\n");
	printf("5. Keluar\n");
	printf("\nInput nomor menu: ");
	scanf("%d", &pilih);
	
	switch(pilih){
		case 1 : printf("Main"); break;
		case 2 : printf("Papan Peringkat"); break;
		case 3 : printf("Cara Bermain"); break;
		case 4 : printf("Tentang"); break;
		case 5 : printf("Keluar"); break;
		default : printf("Ulang");
	}
	
	return 0;
}
