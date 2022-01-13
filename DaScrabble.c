/*
	Judul  	: DaScrabble
	Author 	: Kelompok A11
			  - Dafa Nurul Fauziansyah   (211524006)
			  - Salsabila Maharani Putri (211524026)
	Versi 1	: Desember 2021 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>

/* Modul Menu Utama */
void tampilMenu();
void mulaiPermainan();
void readHighscores();
void readHTPFile();
void tampilTentang();
void endProgram();

/* Modul Inisialisasi Pemain */
int  registPemain();
int  pilihPemain();
void inputNama(int pilihan);
int  pilihLevel();

/* Modul Inisialisasi Permainan */
void inisialisasiPapan();
void inisialisasiHuruf();
int  hitungSisa();
void randomHuruf(int sisa, int giliran, int kurang);
void showHuruf(int giliran);
void showPoin(int giliran);
void kurangiHuruf(char *string);

/* Modul Permainan */
void printPapan();
int  getPosisi(int *baris, int *kolom);
int  getArah(int *arah);
int  getKata(char *kata, int baris, int kolom, int arah);
void hitungScore(char *jawaban, int baris, int kolom, int arah, int giliran);
int  cekHuruf(char *kata, int giliran);
void susunHuruf(char *kata, int giliran); 
int  startTimer();
int  finishTimer();
int  timerCountdown(int *jumlahPass, int levelPermainan, int lastTime);
int  cekPosisiKata(char *kata, int baris, int kolom, int arah, int giliran, int level);
void insertKePapan(char *temp, int baris, int kolom, int arah);
int  cekKamus(char *kata, int level);
void writeHighscores(char namaBaru[100], int scoreBaru, int levelBaru);

/*Modul gotoxy untuk posisi*/
void gotoxy(int x, int y);

/* Tipe data bentukan */
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

typedef struct{
	char nama[100];
	int score;
	char level[10];
}highScore;

/*Kamus Data Variable Global*/
IsiPapan Papan[15][15];
DataHuruf Huruf[27];
DataPemain Pemain[2];

int main(){
	tampilMenu();
	
	return 0;
}

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void tampilMenu(){
	/*
		Author : Dafa 
		Prosedur menampilkan menu utama
	*/
	int pilihMenu;
	
	//Program
	do{
		main:
		system("cls");
		gotoxy(40,9); printf("DaScrabble");
		gotoxy(40,11); printf("1. Main");
		gotoxy(40,12); printf("2. Papan Peringkat");
		gotoxy(40,13); printf("3. Cara Bermain");
		gotoxy(40,14); printf("4. Tentang");
		gotoxy(40,15); printf("5. Keluar");
		gotoxy(40,17); printf("Masukkan nomor menu : ");
		scanf("%d", &pilihMenu);
		
		switch(pilihMenu){
			case 1 : mulaiPermainan(); 
				break;
			case 2 : readHighscores(); 
				break;
			case 3 : readHTPFile(); 
				break;
			case 4 : tampilTentang(); 
				break;
			case 5 : endProgram(); 
				break;
			default : system("cls"); gotoxy(47,15); printf("\a Menu tidak tersedia."); Sleep(2000);
		}
	} while(pilihMenu < 1 || pilihMenu > 5 );
}

void readHighscores(){
	/*
		Author : Dafa 
		Prosedur menampilkan data highscore
		referensi : https://www.mahirkoding.com/operasi-file-dalam-bahasa-c/
	*/
    char nama[100];
    int umur;
    char level[10];
	FILE *in=fopen("updatedHighscore.txt","r");//perintah untuk membuka file dengan mode r / read
        system("cls");
		printf("\n");
		while(!feof(in)){
           fscanf(in,"%[^#]#%d#%[^\n]\n", &nama, &umur, &level);fflush(stdin);   
           // %[^#] artinya kita menyimpan bagian dari string dalam file sampai tanda #. 
           // Kita tidak menggunnakan %s karena nama mengandung spasi
           printf("%s\t%d\t%s\n", nama, umur, level);
        }
	fclose(in);//perintah untuk menutup file yang tadi dibuka
	printf("\nTekan tombol apapun untuk kembali ke menu utama.....");
	getch(); 
	tampilMenu();
}

void readHTPFile(){
	/*
		Author : Dafa 
		Prosedur menampilkan cara bermain
	*/
    char rules[255];
	FILE *in=fopen("htp.txt","r");//perintah untuk membuka file dengan mode r / read
	system("cls");
	printf("\n");
    while(!feof(in)){
        fscanf(in,"%[^\n]\n", &rules);fflush(stdin);   
        // %[^\n] artinya kita menyimpan bagian dari string dalam file sampai tanda \n atau newline. 
        // Kita tidak menggunnakan %s karena aturan mengandung spasi
        printf("%s\n", rules);
    }
	fclose(in);//perintah untuk menutup file yang tadi dibuka
	printf("\nTekan tombol apapun untuk kembali ke menu utama.....");
	getch();
	tampilMenu();
}

void tampilTentang(){
	/*
		Author : Dafa 
		Prosedur menampilkan tentang aplikasi
	*/
	char rules[255];
	FILE *in=fopen("tentang.txt","r");//perintah untuk membuka file dengan mode r / read
	system("cls");
	printf("\n");
    while(!feof(in)){
        fscanf(in,"%[^\n]\n", &rules);fflush(stdin);   
        // %[^\n] artinya kita menyimpan bagian dari string dalam file sampai tanda \n atau newline. 
        // Kita tidak menggunnakan %s karena aturan mengandung spasi
        printf("%s\n", rules);
    }
	fclose(in);//perintah untuk menutup file yang tadi dibuka
	printf("\nTekan tombol apapun untuk kembali ke menu utama.....");
	getch();
	tampilMenu();
}

void endProgram(){
	/*
		Author : Dafa 
		Prosedur untuk mengakhiri program
	*/
	char pilihanKeluar;
	gotoxy(40,19); printf("Apakah anda yakin ingin keluar ? [Y/N] ");fflush(stdin);scanf("%c", &pilihanKeluar);
	if(pilihanKeluar == 'Y' || pilihanKeluar == 'y'){
		printf("Terima kasih sudah bermain DaScrabble");
	}
	else if(pilihanKeluar == 'N' || pilihanKeluar == 'n'){
		system("cls");
		tampilMenu();
	}
	else{
		gotoxy(40,21); printf("\aMohon maaf kode yang anda inputkan");
		gotoxy(40,22); printf("\atidak valid pastikan mengisi dengan Y / N");
		Sleep(3000);
		system("cls");
		tampilMenu();
	}
}

void mulaiPermainan(){
	/*
		Author : Salsabila
		Prosedur dimulainya rangkaian permainan
	*/
	int i, kurang;
	int level; 
	int pilihMain;
	int result; // untuk parameter kondisi perulangan ketika input jawaban tidak valid
	int baris, kolom, arah; //baris kolom untuk input jawaban, arah untuk jawaban horizontal atau vertikal
	char kata[8];
	int giliran = -1; //-1 agar index dari 0
	int jumPass = 0; //counter berapa kali pemain memilih Pass
	bool isMenyerah = false; 
	bool isHabis = false; //kondisi jika huruf persediaan dan huruf pemain habis
	int panjang;
	int lamaMain = 0;
	int mulaiMain;
	int menit, detik = 0;
	int sisahuruf = 0;
	
	system("cls");
	level = registPemain();
	
	system("cls");
	inisialisasiHuruf(); 
	inisialisasiPapan(); 
	
	do{
		nexturn:
		giliran = (giliran + 1) % 2; //pergantian giliran pemain 0 dan 1
		system("cls");
		mulaiMain = startTimer();
		restart:
		system("cls");
		switch(level){
			case 1 : printf("\n  Level : Easy");
					 menit = 7;
				break;
			case 2 : printf("\n  Level : Medium");
					 menit = 5;
				break;
			case 3 : printf("\n  Level : Hard");
					 menit = 3;
					 detik = 30;
				break;
		}
		
		printf("\n  %s vs. %s", Pemain[0].nama_pemain, Pemain[1].nama_pemain);
		printf("\n  Skor %s : %d \t\t Skor %s : %d\n\n", Pemain[0].nama_pemain, Pemain[0].score, Pemain[1].nama_pemain, Pemain[1].score);
		
		printPapan(); 
		
		panjang = strlen(Pemain[giliran].huruf);
		kurang = 7 - panjang;
		
		if(hitungSisa() >= kurang){
			randomHuruf(hitungSisa(), giliran, kurang);	
		}
		else{
			randomHuruf(hitungSisa(), giliran, hitungSisa());	
		}
		printf("\n\n  Giliran: %s \t  \tSisa Huruf: %d", Pemain[giliran].nama_pemain, hitungSisa());
		
		printf("\n\n\t\t");
		showHuruf(giliran);
		printf("\n\n\t\t");
		showPoin(giliran);
		printf("\n\n  Ingat waktu giliran adalah %d menit %d detik.", menit, detik);
		
		printf("\n\n  1. Jawab");
		printf("\n  2. Pass");
		printf("\n  3. Menyerah");
		printf("\n  Masukkan pilihan : ");
		scanf("%d", &pilihMain);
		fflush(stdin);
		
		lamaMain = finishTimer() - mulaiMain;
		if(timerCountdown(&jumPass, level, lamaMain)){
			if(pilihMain==1){
				//reset jumlah pass
				jumPass = 0;
				// input baris kolom
				lamaMain = finishTimer() - mulaiMain;
				if(timerCountdown(&jumPass, level, lamaMain)){
					do{
					result = getPosisi(&baris, &kolom);
					}while(result == 0);
					if(result == -1){
						goto restart;
					}
				}
				else{
					goto nexturn;
				}
					
				// input horizontal atau vertikal
				lamaMain = finishTimer() - mulaiMain;
				if(timerCountdown(&jumPass, level, lamaMain)){
					do{
						result = getArah(&arah);
					}while(result == 0);
					if(result == -1){
						goto restart;
					}
				}
				else{
					goto nexturn;
				}
				
				// input kata
				inputkata:
				lamaMain = finishTimer() - mulaiMain;
				if(timerCountdown(&jumPass, level, lamaMain)){
					do{
						result = getKata(kata, baris, kolom, arah);
					}while(result == 0);
					if(result == -1){
						goto restart;
					}
				}
				else{
					goto nexturn;
				}
				
				lamaMain = finishTimer() - mulaiMain;
				if(timerCountdown(&jumPass, level, lamaMain)){
					result = cekPosisiKata(kata, baris, kolom, arah, giliran, level);
					if(result == 0){
						goto inputkata;
					}
				}
				else{
					goto nexturn;
				}
				
			}
			else if(pilihMain == 2){
				jumPass = jumPass + 1;
			}
			else if(pilihMain == 3){
				isMenyerah = true;
				Pemain[giliran].score = 0;
			}
			else{
				printf("\a  Input kurang tepat harap masukan kode yang tersedia");
				Sleep(2000);
				system("cls");
				goto restart;
			}
		}
		else{
			goto nexturn;
		}
		
		sisahuruf = strlen(Pemain[giliran].huruf);
		if(sisahuruf == 0){
			isHabis = true;
		}
	}	while(jumPass < 2 && isMenyerah == false && isHabis == false);
	system("cls");
	if(isMenyerah){
		gotoxy(10,10); printf("%s menyerah.", Pemain[giliran].nama_pemain);
		giliran = (giliran + 1) % 2;
		gotoxy(10,12); printf("Selamat kepada %s telah memenangkan permainan ini dengan score %d", Pemain[giliran].nama_pemain, Pemain[giliran].score);
		gotoxy(10,15); writeHighscores(Pemain[giliran].nama_pemain, Pemain[giliran].score, level);
	}
	if (Pemain[0].score > Pemain[1].score){
		gotoxy(10,10); printf("Selamat kepada %s telah memenangkan permainan ini dengan score %d", Pemain[0].nama_pemain, Pemain[0].score);
		gotoxy(10,13);writeHighscores(Pemain[0].nama_pemain, Pemain[0].score, level);
	}
	else if(Pemain[0].score < Pemain[1].score){
		gotoxy(10,10); printf("Selamat kepada %s telah memenangkan permainan ini dengan score %d", Pemain[1].nama_pemain, Pemain[1].score);
		writeHighscores(Pemain[1].nama_pemain, Pemain[1].score, level);
		gotoxy(10,13); 
	}
	else{
		gotoxy(10,10); printf("Akhir permainan seri dengan skor %s %d dan %s %d", Pemain[0].nama_pemain, Pemain[0].score, Pemain[1].nama_pemain, Pemain[1].score);
		gotoxy(10,13); printf("Tekan enter untuk melanjutkan......");
		getch();
		tampilMenu();
	}
}

int registPemain(){
	/*
		Author : Salsabila
		Fungsi pemanggilan rangkaian inisialisasi pemain
		mengembalikan hasil pilihan level 
	*/
	int pilihanPemain;
	int pilihanLevel;
	
	pilihanPemain = pilihPemain();
	inputNama(pilihanPemain);
	pilihanLevel = pilihLevel();
	Pemain[0].score = 0;
	Pemain[1].score = 0;
	
	return pilihanLevel;
}

int  pilihPemain(){
	/*
		Author : Salsabila
		Fungsi memilih lawan dalam permainan
	*/
	int pilih;
	int pemain;
	
	do{
		pilihMode:
		system("cls");
		gotoxy(40,9); printf("Pilih Pemain");
		gotoxy(40,11); printf("1. manusia vs manusia");
		gotoxy(40,12); printf("2. manusia vs komputer");
		gotoxy(40,14); printf("Masukkan nomor pilihan : ");
		scanf("%d", &pilih);
		
		switch(pilih){
			case 1 : 
				pemain = 2;
				break;
			case 2 : 
				pemain = 1;
				system("cls");
				gotoxy(38,9); printf("\a Maaf pilihan mode bermain masih dalam tahap ");
				gotoxy(38,10); printf("\a pengembangan harap coba menu lain terlebih dahulu");
				Sleep(4000);
				goto pilihMode;
				break;
			default : 
				system("cls");
				gotoxy(38,14); printf("\a Maaf pilihan mode bermain tidak tersedia");
				Sleep(2000);
				break;
		}
	} while(pilih > 2 || pilih < 1);
	
	return pemain;
}

void inputNama(int pilihan){
	/*
		Author : Salsabila 
		Prosedur pengisian nama pemain
	*/
	system("cls");
	gotoxy(20,8); printf("Pastikan mengisi nama dengan benar, karena hanya 1 kali kesempatan.");
	if(pilihan == 2){
		gotoxy(20,11); printf("Nama Pemain 1 (maks. 30 karakter): ");
		scanf("%s", Pemain[0].nama_pemain);
		gotoxy(20,13); printf("Nama Pemain 2 (maks. 30 karakter): ");
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

int pilihLevel(){
	/*
		Author : Salsabila 
		Fungsi pemilihan level bermain
	*/
	int pilih;
	int level;
	
	do{
		pilihlevel:
		system("cls");
		gotoxy(40,8); printf("Pilih level");
		gotoxy(40,10); printf("1. Easy");
		gotoxy(40,11); printf("2. Medium");
		gotoxy(40,12); printf("3. Hard");
		gotoxy(40,14); printf("Masukkan pilihan level : ");
		scanf("%d", &pilih);
		
		switch(pilih){
			case 1 : level = 1;
				break;
			case 2 : level = 2;
				break;
			case 3 : level = 3;
				break;
			default : 
				system("cls");
				gotoxy(38,14); printf("\a Maaf pilihan level bermain tidak tersedia");
				Sleep(2000);
				goto pilihlevel;
				break;
		}
		
	} while(pilih < 1 || pilih > 3);
	
	return level;
}

void inisialisasiHuruf(){
	/* 	
		Author : Dafa 
		Prosedur pengisian data huruf untuk permainan
		hurufnya apa, poin si hurufnya berapa, jumlah hurufnya berapa 
	*/
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
	/*
		Author : Salsabila 
		Prosedur pengisian data awal kotak-kotak pada papan
		memberi nilai jika di kotak tersebut ada poin bonus atau tidak
	*/
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
	/*
		Author : Salsabila
		Prosedur menampilkan papan permainan
	*/
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
			printf(" %c \xb3",toupper(temp));				// A | B | C | D | E | isi kotak
		}

		printf((y<15-1) ? "\n \xc3" : "\n \xc0");
		for(i=1;i<=15;i++){
			printf((i==15) ? ((y<15-1) ? "\xc4\xc4\xc4\xb4" : "\xc4\xc4\xc4\xd9") : ((y<15-1) ? "\xc4\xc4\xc4\xc5" : "\xc4\xc4\xc4\xc1"));
		}
		printf("\n");
	}
}

int getPosisi(int *baris, int *kolom){
	/*
		Author : Dafa
		Fungsi untuk get inputan posisi dari pemain
		di return hasil valid atau tidaknya
	*/
	char row;
	int col;
	
	printf("\n  Masukkan posisi huruf pertama (contoh: H8) : ");
	scanf("%c%d", &row, &col);
	fflush(stdin);
	
	row &= 0x5F;
	
	*baris = row - 0x41;
	if(*baris < 0 || *baris > 14){
		printf("\a  Posisi tidak valid, coba lagi.\n");
		Sleep(2000);
		return 0;
	}
	
	*kolom = col - 1;
	if(*kolom < 0 || *kolom > 14){
		printf("\a  Posisi tidak valid, coba lagi.\n");
		Sleep(2000);
		return 0;
	}
	
	return 1;
}

int getArah(int *arah){
	/*
		Author : Dafa
		Fungsi untuk get inputan arah horizontal/vertikal dari pemain
		di return hasil valid atau tidaknya
	*/
	char dir;
	pilihArah:
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
		printf("\a  Arah tidak valid, coba lagi.\n");
		Sleep(2000);
		goto pilihArah;
	}
		
	return 0;
}

int getKata(char *kata, int baris, int kolom, int arah){
	/*
		Author : Dafa
		Fungsi untuk get inputan susunan huruf/kata dari pemain
		di return hasil valid atau tidaknya
	*/
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
			printf("\n\a  Kata tidak Valid, coba lagi, pastikan memasukkan huruf yang benar.");
			Sleep(3000);
			return 0;
		}
		
		i++;
	}
	
	if((length + ((arah) ? baris : kolom)) > 15){
		printf("\a  Posisi kata terlalu panjang, coba lagi.");
		Sleep(2000);
		return 0;
	}
	
	return 1;
}

int cekHuruf(char *kata, int giliran){
	/*
		Author : Salsabila
		Fungsi untuk mengecek huruf yang diinput pemain
		huruf arus sesuai dengan yang diberikan saat giliran
		di return hasil valid atau tidaknya
	*/
	int i, j;
	int c = 0;
	int length, panjang;
	bool beda;
	
	length = strlen(kata);
	panjang = strlen(Pemain[giliran].huruf);
	
	for(i=0; i<length; i++){
		beda = true;
		j = 0;
		while(beda && j<panjang){
			if(kata[i] == Pemain[giliran].huruf[j] || Pemain[giliran].huruf[j] == '_'){
				beda = false;
			}
			j++;
		}
		
		if(beda){
			c++;
		}
	}
	
	if(c > 0){
		return 0;
	}
	
	return 1;
}

int cekPosisiKata(char *kata, int baris, int kolom, int arah, int giliran, int level){
	/*
		Author : Salsabila
		Fungsi untuk mengecek kata yang disusun, poisinya valid atau tidak
		pemain pertama harus mengenai kotak tengah atau h8, kemudian
		penyusunan selanjutnya harus berdempetan dengan huruf yang sudah ada di papan
		di return hasil valid atau tidaknya
	*/
	char temp[15] = " ";
	int i = baris;
	int j = kolom;
	int valid;
	int k = 0;
	int c = 0;
	bool status = true;
	int length, l;
	bool ada = true;
	
	//Mengecek apakah ada huruf di kotak sebelum posisi yang dipilih pemain
	while(ada){
		if(arah==0){
			if(Papan[i][j-1].isiHuruf != ' '){
				j = j-1;
			}
			else{
				ada = false;
			}
		}
		else if(arah==1){
			if(Papan[i-1][j].isiHuruf != ' '){
				i = i-1;
			}
			else{
				ada = false;
			}
		}
	}
	
	baris = i;
	kolom = j;
	valid = 0;
	l = strlen(kata);
	
	//Mengambil huruf yang sudah ada di papan untuk disatukan dengan inputan pemain, sehingga menyusun satu kata
	while(status && c<l){
		if(Papan[7][7].isiHuruf == ' '){
			if(i == 7 && j == 7){
				valid = 1;
			}
			if(Papan[i][j].isiHuruf != ' '){
				temp[k] = Papan[i][j].isiHuruf;
			}
			else if(kata[c] >= 'A' || kata[c] <= 'Z'){
				temp[k] = kata[c];
				c++;
			}
			else{
				status = false;
			}
		}
		else{
			if(Papan[i][j].isiHuruf != ' '){
				temp[k] = Papan[i][j].isiHuruf;
				valid = 1;
			}
			else if(kata[c] >= 'A' || kata[c] <= 'Z'){
				temp[k] = kata[c];
				c++;
			}
			else{
				status = false;
			}
		}
		
		if(arah == 0){
			j++;
		}
		else{
			i++;
		}
		
		k++;
	}
	
	if(Papan[i][j].isiHuruf != ' '){
		temp[k] = Papan[i][j].isiHuruf;
		valid = 1;
	}
	
	if(valid == 0){
		printf("\a  Posisi tidak tepat, coba lagi.");
		Sleep(1000);
		return 0;
	}
	else{
		if(cekHuruf(kata, giliran)){
			if(cekKamus(temp, level)){
				hitungScore(temp, baris, kolom, arah, giliran);
				insertKePapan(temp, baris, kolom, arah);
				susunHuruf(kata, giliran);
			}
			else{
				printf("\a  Kata tidak valid, coba lagi.");
				Sleep(1000);
				return 0;
			}
		}
		else{
			printf("\a  Masukkan huruf yang sesuai");
			Sleep(1000);
			return 0;
		}
		
	}
	
	length = strlen(temp);
	if((length + ((arah) ? baris : kolom)) > 15){
		printf("\a  Posisi kata terlalu panjang, coba lagi.");
		Sleep(1000);
		return 0;
	}
	
	return 1;
}

void susunHuruf(char *kata, int giliran){
	/*
		Author : Salsabila
		Prosedur untuk menyusun ulang huruf yang dipegang oleh pemain,
		ketika pemain sudah menginputkan jawaban dan valid, 
		maka huruf yang dipegang oleh pemain tadi akan dihapus di sini
	*/
	char tempHuruf[] = {[7]='\0'};
	int length, panjang;
	int counter1, counter2, counter3;
	bool status;
	int i;
	
	status = false;
	counter1 = 0;
	counter3 = 0;
	
	length = strlen(Pemain[giliran].huruf);
	panjang = strlen(kata);
	
	if(length != 0){
		while(counter1 < length){
			counter2 = 0;
			do{
				if(Pemain[giliran].huruf[counter1] != kata[counter2]){
					status = false;
				}
				else{
					status = true;
					kata[counter2] = '\0';
				}
				if(Pemain[giliran].huruf[counter1] == '_'){
					status = true;
					kata[counter2] = '\0';
				}
				counter2++;
			}while(status == false && counter2 < panjang);
			
			if(status == false){
				tempHuruf[counter3] = Pemain[giliran].huruf[counter1];
				counter3++;
			}
			counter1++;
		}
	}
	
	for(i=0; i<7; i++){
		Pemain[giliran].huruf[i] = '\0';
	}
	length = strlen(tempHuruf);
	for(i=0; i<length; i++){
		Pemain[giliran].huruf[i] = tempHuruf[i];
	}
}

void insertKePapan(char *temp, int baris, int kolom, int arah){
	/*
		Author : Salsabila
		Prosedur menambahkan huruf yang berhasil disusun pemain ke papan
	*/
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
	
	printf("\n  %s", temp);
}

int cekKamus(char *kata, int level){
	/*
		Author : Dafa 
		Fungsi untuk mengecek jawaban pemain ke kamus
	*/
    char nama[100];
    kata = strlwr(kata);
    if(level == 1){
    	FILE *in=fopen("wordseasy.txt","r");
	        while(!feof(in)){
	           fscanf(in,"%[^\n]\n", &nama);fflush(stdin);
	           // %[^\n] artinya kita menyimpan bagian dari string dalam file \n atau newline
			   if(strcmp(nama, kata) == 0){
			   		return 1;
					break;
			   }
	        }
		fclose(in);
	}
	else if(level == 2){
		FILE *in=fopen("wordsmedium.txt","r");
	        while(!feof(in)){
	           fscanf(in,"%[^\n]\n", &nama);fflush(stdin);
	           // %[^\n] artinya kita menyimpan bagian dari string dalam file \n atau newline
			   if(strcmp(nama, kata) == 0){
			   		return 1;
					break;
			   }
	        }
		fclose(in);
	}
	else{
		FILE *in=fopen("wordshard.txt","r");
	        while(!feof(in)){
	           fscanf(in,"%[^\n]\n", &nama);fflush(stdin);
	           // %[^\n] artinya kita menyimpan bagian dari string dalam file \n atau newline
			   if(strcmp(nama, kata) == 0){
			   		return 1;
					break;
			   }
	        }
		fclose(in);
	}
	
	
	return 0;
}

void hitungScore(char *jawaban, int baris, int kolom, int arah, int giliran){
	/*
		Author : Salsabila
		Prosedur menghitung score yang diperoleh pemain
	*/
	int score = 0;
	int multiplier = 0;
	int i, j;
	int length;
	int r = baris;
	int c = kolom;
	bool status;
	
	length = strlen(jawaban);
	
	for(i=0; i<length; i++){
		j = 0;
		status = false;
		while(j<27 && status == false){
			if(jawaban[i] == tolower(Huruf[j].huruf)){
				if(Papan[r][c].isLetter2){
					score = score + (Huruf[j].nilaiHuruf*2);
					Papan[r][c].isLetter2 = false;
				}
				else if(Papan[r][c].isLetter3){
					score = score + (Huruf[j].nilaiHuruf*3);
					Papan[r][c].isLetter3 = false;
				}
				else if(Papan[r][c].isWord2){
					multiplier = multiplier + 2;
					Papan[r][c].isWord2 = false;
				}
				else if(Papan[r][c].isWord3){
					multiplier = multiplier + 3;
					Papan[r][c].isWord3 = false;
				}
				else {
					score = score + Huruf[j].nilaiHuruf;
				}
				status = true;
			}
			j++;
		}
		if(arah == 0){
			c++;
		}
		else{
			r++;
		}
	}
	
	if(multiplier > 0){
		score = score * multiplier;
	}
	
	if(Pemain[0].score == 0 && Pemain[1].score == 0){
		score = score * 2;
	}
	
	Pemain[giliran].score += score;
	
	printf("\n  Score yang didapat +%d", score);
	
}

int hitungSisa(){
	/*
		Author : Salsabila
		Fungsi untuk menghitung jumlah sisa huruf 
		yang disediakan untuk satu permainan
		nilai awalnya adalah 100
	*/
	int i;
	int sisa=0;
	
	for(i=0; i<27; i++){
    	sisa += Huruf[i].jumlah;
	}
	
	return sisa;
}

void randomHuruf(int sisa, int giliran, int kurang){
	/*
		Author : Dafa /ditambah modifikasi oleh Salsabila
		Prosedur untuk mengacak huruf yang akan diberikan
		kepada pemain di setiap gilirannya
	*/
	int i, j, k=0;
	int length;
    char string[]={[7]='\0'};
    char huruf[100];
    
    for (i=0; i<27; i++){
    	j=0;
    	while(j<Huruf[i].jumlah && k<sisa){
    		huruf[k] = Huruf[i].huruf;
    		j++;
    		k++;
		}
	}
	length = strlen(huruf);
	if(length > 7){
		srand(time(0));
        for(i=0;i<kurang;i++){
        	string[i]=huruf[rand() % sisa];
    	}
	}
	else{
		for(i=0; i<length; i++){
			string[i] = huruf[i];
		}
	}
    
    i = 0;
    j = 7 - kurang;
	while(i < kurang && j < 7){
		Pemain[giliran].huruf[j] = string[i];
		i++;
		j++;
	}
	
	kurangiHuruf(string);
}

void showPoin(int giliran){
	/*
		Author : Salsabila
		Prosedur untuk menampilkan poin
		dari huruf acak yang diberikan
	*/
	int i, j;
	
	for(i=0; i<7; i++){
		for(j=0; j<27; j++){
			if(Pemain[giliran].huruf[i] == Huruf[j].huruf){
				printf("%d ", Huruf[j].nilaiHuruf);
			}
		}
	}
}

void showHuruf(int giliran){
	/*
		Author : Salsabila
		Prosedur untuk menampilkan huruf
		apa saja yang diberikan untuk pemain
	*/
	int i, length;
	
	length = strlen(Pemain[giliran].huruf);
	for(i=0; i<length; i++){
		printf("%c ", Pemain[giliran].huruf[i]);
	}
}

void kurangiHuruf(char *string){
	/*
		Author : Salsabila
		Prosedur untuk mengurangi jumlah huruf
		di persediaan ketika huruf tersebut telah diberikan kepada pemain
	*/
	int i, j;
	int length;
	
	length = strlen(string);
	for(i=0; i<length; i++){
		for(j=0; j<27; j++){
			if(string[i] == Huruf[j].huruf){
				Huruf[j].jumlah -= 1;
			}
		}
	}
}

void writeHighscores(char namaBaru[100], int scoreBaru, int levelBaru){
	/*
		Author : Dafa
		Prosedur untuk mencatat highscore.
		Highscore yang dicatat hanya 6, 
		sehingga akan selalu dilakukan pengecekan apakah score 
		pemenang yang baru melebihi score yang sudah tercatat
		jika iya maka score tersebut akan dicatat dan yang lebih kecil akan terhapus
	*/
	highScore testHighscore[6];
    bool isMengisi = false;
    int i = 0;
    char stringLevel[10];
    if (levelBaru == 1){
    	strcpy(stringLevel, "Easy");
	}
	else if (levelBaru == 2){
    	strcpy(stringLevel, "Medium");
	}
	else{
    	strcpy(stringLevel, "Hard");
	}
	//perintah untuk membuka file dengan mode r+ / read lalu akan dilakukan lagi proses write
	FILE *in=fopen("updatedHighscore.txt","r+");
    while(!feof(in)){
        fscanf(in,"%[^#]#%d#%[^\n]\n", &testHighscore[i].nama, &testHighscore[i].score, &testHighscore[i].level);fflush(stdin);
        i++;
    }
    //perintah untuk menutup file yang tadi dibuka
	fclose(in);
	//perintah untuk membuka file dengan mode w / write
	FILE *out=fopen("updatedHighscore.txt","w");
	for(i = 0; i < 6;i++){
        if(scoreBaru >= testHighscore[i].score && isMengisi==false){
        	fprintf(out,"%s#%d#%s\n", namaBaru, scoreBaru, stringLevel);
        	isMengisi = true;
		}
		else{
			fprintf(out,"%s#%d#%s\n", testHighscore[i].nama, testHighscore[i].score, testHighscore[i].level);
		}
	}
	//perintah untuk menutup file yang tadi dibuka
	fclose(out);
	printf("Tekan enter untuk melanjutkan......");
	getch();
	tampilMenu();
}

/*Referensi module timer dibawah : Scrabble milik kelompok A9*/
int startTimer(){
	/*
		Author : Dafa
		Fungsi untuk mengambil waktu ketika giliran pemain dimulai
	*/
    clock_t timeStart;
    timeStart = clock();
    return timeStart;
}

int finishTimer(){
	/*
		Author : Dafa
		Fungsi untuk mengambil waktu ketika pemain selesai menginput
	*/
    clock_t timeEnd;
    timeEnd = clock();
    return timeEnd;
}

int timerCountdown(int *jumPass, int levelPermainan, int lastTime){
	/*
		Author : Dafa
		Fungsi untuk mengecek apakah waktu yang digunakan oleh pemain
		melebihi batasnya atau tidak
	*/
	int timeLimit;
	double time_in_sec = 0.0;
	time_in_sec = ((double)lastTime)/CLOCKS_PER_SEC;
	if(levelPermainan == 1){
		timeLimit = 420;
	}
	else if(levelPermainan == 2){
		timeLimit = 300;
	}
	else{
		timeLimit = 210;
	}
	//periksa waktu
	if(time_in_sec > timeLimit){
        printf("\n  waktu habis %.2f\n", time_in_sec);
        Sleep(1000);
        *jumPass += 1;
        return 0;
    }
    else{
        return 1;
    }
}
