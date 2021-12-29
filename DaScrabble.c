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
	IsiPapan Papan;
	DataPemain Pemain;
	printf("DaScrabble");
	
	return 0;
}
