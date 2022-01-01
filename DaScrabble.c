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

//Deklarasi Modul Inisialisasi Permainan
void inisialisasiPapan();
void inisialisasiHuruf();

//Deklarasi Modul saat permainan
void printPapan();
int getPosisi(int *baris, int *kolom);
int getArah(int *arah);
int getKata(char *kata, int baris, int kolom, int arah);

//Deklarasi Modul validasi posisi kata pada papan
int cekPosisiKata(char *kata, int baris, int kolom, int arah);
void insertKePapan(char *temp, int baris, int kolom, int arah);

//Deklarasi Modul yang berhubungan dengan File
int cekKamus(char *kata);


typedef struct {
	char huruf;
	int nilaiHuruf;
	int jumlah;
} DataHuruf;

typedef struct {
	char isiHuruf;
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
IsiPapan Papan[15][15];
DataHuruf Huruf[27];
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
	int pilihMain;
	int result; // untuk parameter kondisi perulangan ketika input jawaban tidak valid
	int baris, kolom, arah; //baris kolom untuk input jawaban, arah untuk jawaban horizontal atau vertikal
	char kata[8];
	int giliran = -1; //-1 agar index dari 0
	int jumPass = 0; //counter berapa kali pemain memilih Pass
	bool isMenyerah = false; 
	bool isHabis = false; //kondisi jika huruf persediaan dan huruf pemain habis
	
	system("cls");
	level = registPemain();
	
	system("cls");
	inisialisasiHuruf(); //pengisian nilai huruf yang tersedia, huruf, poin, serta jumlahnya
	inisialisasiPapan(); //pengisian nilai awal papan
	
	do{
		giliran = (giliran + 1) % 2; //pergantian giliran pemain 0 dan 1
		//system("cls");
		switch(level){
			case 1 : printf("\n  Level : Easy");
				break;
			case 2 : printf("\n  Level : Medium");
				break;
			case 3 : printf("\n  Level : Hard");
				break;
		}
		
		printf("\n  %s vs. %s", Pemain[0].nama_pemain, Pemain[1].nama_pemain);
		printf("\n  Skor %s : %d \t\t Skor %s : %d\n\n", Pemain[0].nama_pemain, Pemain[0].score, Pemain[1].nama_pemain, Pemain[1].score);
		
		printPapan(); //menampilkan papan dan isinya
		
		printf("\n\n  Giliran: %s \t  Waktu: 01:23\t  Sisa Huruf: 84", Pemain[giliran].nama_pemain);
		printf("\n\n\t\tA B C D E F G H I");
		printf("\n\n\t\t1 2 3 4 5 6 7 8 9");
		
		restart:
		printf("\n\n  1. Jawab");
		printf("\n  2. Pass");
		printf("\n  3. Menyerah");
		printf("\n  Masukkan pilihan : ");
		scanf("%d", &pilihMain);
		fflush(stdin);
		if(pilihMain==1){
			// input baris kolom
			do{
				result = getPosisi(&baris, &kolom);
			}while(result == 0);
			if(result == -1){
				goto restart;
			}
				
			// input horizontal atau vertikal
			do{
				result = getArah(&arah);
			}while(result == 0);
			if(result == -1){
				goto restart;
			}
			
			// input kata
			inputkata:
			do{
				result = getKata(kata, baris, kolom, arah);
			}while(result == 0);
			if(result == -1){
				goto restart;
			}
			
			result = cekPosisiKata(kata, baris, kolom, arah);
			if(result == 0){
				goto inputkata;
			}
			
		}
		
		printf("\n  baris : %d",baris);
		printf("\n  kolom : %d",kolom);
		printf("\n  arah : %d",arah);
		printf("\n  kata : %s\n",kata);
	}while(jumPass < 2 && isMenyerah == false && isHabis == false);
	
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

void inisialisasiHuruf(){
	char huruf;
	int nilaiHuruf;
	int jumlah;
	int i = 0;
	
	FILE *in = fopen("datahuruf.txt", "r");
		while(!feof(in)){
			fscanf(in,"%c#%d#%d\n", &huruf, &nilaiHuruf, &jumlah);
			fflush(stdin);
			
			Huruf[i].huruf = huruf;
			Huruf[i].nilaiHuruf = nilaiHuruf;
			Huruf[i].jumlah = jumlah;
			
			i++;
		};
	fclose(in);
}

void inisialisasiPapan(){
	int i, j;
	
	for(i=0; i<15; i++){
		for(j=0; j<16; j++){
			Papan[i][j].isLetter2 = false;
            Papan[i][j].isLetter3 = false;
            Papan[i][j].isWord2 = false;
            Papan[i][j].isWord3 = false;
            Papan[i][j].isiHuruf = ' ';
            if ((i==0 || i==7 || i==14) && (j==0 || j==7 || j==14)){
            	if(i==7 && j==7){
            		Papan[i][j].isiHuruf= ' ';
				}
				else{
					Papan[i][j].isWord3= true;
				}
			}
            else if ((i==5 || i==9) && ((j-1)%4==0)){
            	Papan[i][j].isLetter3 = true;
			}
            else if ((j==5 || j==9) && ((i-1)%4==0)){
            	Papan[i][j].isLetter3 = true;
			}
            else if ((i==6 || i==8) && (j==2 || j==6 || j==8 || j==12)){
            	Papan[i][j].isLetter2 = true;
			}
            else if ((j==6 || j==8) && (i==2 || i==6 || i==8 || i==12)){
            	Papan[i][j].isLetter2 = true;
			}
            else if ((i==3 || i==11) && (j==0 || j==7 || j==14)){
            	Papan[i][j].isLetter2 = true;
			}
            else if ((j==3 || j==11) && (i==0 || i==7 || i==14)){
            	Papan[i][j].isLetter2 = true;
			}
            else if (i==j || i==(14-j)){
            	Papan[i][j].isWord2 = true;
			}
		}
	}
}

void printPapan(){
	int i, x, y;
	char temp;
	
	printf("  ");
	for(i=1;i<=15;i++){
		if(i>9){
			printf(" %d ",i);		// kolom 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		}
		else{
			printf(" %d  ",i);		// kolom 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		}
	}
			
	printf("\n \xda");
	for(i=1;i<=15-1;i++){
		printf("\xc4\xc4\xc4\xc2");
	}
	printf("\xc4\xc4\xc4\xbf");

	printf("\n");
	for(y = 0;y<15;y++){
		printf("%c\xb3",y+'a'); //baris a|
		for(x = 0;x<15;x++){
			if(Papan[y][x].isLetter2 && Papan[y][x].isiHuruf==' '){
				temp='2';
			}
			else if(Papan[y][x].isLetter3 && Papan[y][x].isiHuruf==' '){
				temp='3';
			}
			else if(Papan[y][x].isWord2 && Papan[y][x].isiHuruf==' '){
				temp='2';
			}
			else if(Papan[y][x].isWord3 && Papan[y][x].isiHuruf==' '){
				temp='3';
			}
			else{
				temp = Papan[y][x].isiHuruf;
			}
			printf(" %c \xb3",temp);				// X | O | X | O | X |
		}

		printf((y<15-1) ? "\n \xc3" : "\n \xc0");
		for(i=1;i<=15;i++){
			printf((i==15) ? ((y<15-1) ? "\xc4\xc4\xc4\xb4" : "\xc4\xc4\xc4\xd9") : ((y<15-1) ? "\xc4\xc4\xc4\xc5" : "\xc4\xc4\xc4\xc1"));
		}
		printf("\n");
	}
}

int getPosisi(int *baris, int *kolom){
	char row;
	int col;
	
	printf("\n  Masukkan posisi huruf pertama (contoh: H8) : ");
	scanf("%c%d", &row, &col);
	fflush(stdin);
	
	row &= 0x5F;
	
	*baris = row - 0x41;
	if(*baris < 0 || *baris > 14){
		printf("  Posisi tidak valid, coba lagi.\n");
		return 0;
	}
	
	*kolom = col - 1;
	if(*kolom < 0 || *kolom > 14){
		printf("  Posisi tidak valid, coba lagi.\n");
		return 0;
	}
	
	return 1;
}

int getArah(int *arah){
	char dir;
	
	printf("\n  Masukkan arah susuh Horizontal(H) atau Vertikal(V), (ENTER) untuk mengulang : ");
	scanf("%c", &dir);
	fflush(stdin);
	
	if(dir == 'H' || dir == 'h'){
		*arah = 0;
		return 1;
	}
	else if(dir == 'V' || dir == 'v'){
		*arah = 1;
		return 1;
	}
	else if(dir == '\n'){
		return -1;
	}
	else{
		printf("  Arah tidak valid, coba lagi.\n");
	}
		
	return 0;
}

int getKata(char *kata, int baris, int kolom, int arah){
	int length;
	int i=0;
	fflush(stdin);
	printf("\n  Masukkan kata sesuai huruf yang diberikan, atau (.) untuk mengulang : ");
	scanf("%s", kata);
	
	
	if(kata[0] == '.'){
		return -1;
	}
	length = strlen(kata);
	strupr(kata);
	while(i<length){
		if(kata[i] < 'A' || kata[i] > 'Z'){
			printf("\n  Kata tidak Valid, coba lagi, pastikan memasukkan huruf yang benar.");
			return 0;
		}
		
		i++;
	}
	
	if((length + ((arah) ? baris : kolom)) > 15){
		printf("Posisi kata terlalu panjang, coba lagi.");
		return 0;
	}
	
	return 1;
}

int cekPosisiKata(char *kata, int baris, int kolom, int arah){
	char temp[15];
	int i = baris;
	int j = kolom;
	int valid = 0;
	int k = 0;
	int c = 0;
	bool status = true;
	int length, l;
	
	while(k < 15 && status){
		if(i == 7 && j == 7){
			valid = 1;
		}
		
		if(Papan[i][j].isiHuruf != ' '){
			temp[k] = Papan[i][j].isiHuruf;
			valid = 1;
		}
		else if(kata[c] != '\0'){
			temp[k] = kata[c];
			c++;
		}
		
		if(arah == 0){
			j++;
		}
		else{
			i++;
		}
		
		k++;
	}
	
	if(valid == 0){
		printf("  Posisi tidak tepat, coba lagi.");
		return 0;
	}
	length = strlen(temp);
	if((length + ((arah) ? baris : kolom)) > 15){
		printf("  Posisi kata terlalu panjang, coba lagi.");
		return 0;
	}
	
	if(cekKamus(temp)){
		insertKePapan(temp, baris, kolom, arah);	
	}
	else{
		printf("  Kata tidak valid, coba lagi,");
		return 0;
	}
	
	return 1;
}

void insertKePapan(char *temp, int baris, int kolom, int arah){
	int length, k;
	int i = baris;
	int j = kolom;
	
	length = strlen(temp);
	
	for(k=0; k<length; k++){
		Papan[i][j].isiHuruf = temp[k];
		
		if(arah == 0){
			j++;
		}
		else{
			i++;
		}
	}
	
	printf("\n %s", temp);
}

int cekKamus(char *kata)
{
    char nama[100];
    kata = strlwr(kata);
	FILE *in=fopen("words2.txt","r");
        while(!feof(in)){
           fscanf(in,"%[^\n]\n", &nama);fflush(stdin);
           // %[^\n] artinya kita menyimpan bagian dari string dalam file \n atau newline
		   if(strcmp(nama, kata) == 0){
		   		return 1;
				break;
		   }
        }
	fclose(in);
	
	return 0;
}

