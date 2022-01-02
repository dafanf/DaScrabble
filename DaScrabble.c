#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

//Deklarasi Modul Menu
void tampilMenu();
void mulaiPermainan();
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
int hitungSisa();
void randomHuruf(int sisa, int giliran, int kurang);
void showHuruf(int giliran);
void showPoin(int giliran);
void kurangiHuruf(char *string);

//Deklarasi Modul saat permainan
void printPapan();
int getPosisi(int *baris, int *kolom);
int getArah(int *arah);
int getKata(char *kata, int baris, int kolom, int arah);
void hitungScore(char *jawaban, int baris, int kolom, int arah, int giliran);
int cekHuruf(char *kata, int giliran);
void susunHuruf(char *kata, int giliran); //untuk mengurangi huruf yang dimiliki pemain yang telah disubmit ke papan

//Deklarasi Modul validasi posisi kata pada papan
int cekPosisiKata(char *kata, int baris, int kolom, int arah, int giliran);
void insertKePapan(char *temp, int baris, int kolom, int arah);

//Deklarasi Modul yang berhubungan dengan File
int cekKamus(char *kata);
void readHighscores();
void writeHighscores(char namaBaru[100], int scoreBaru, char levelBaru[10]);
void readHTPFile();

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
//Kamus Data Global
IsiPapan Papan[15][15];
DataHuruf Huruf[27];
DataPemain Pemain[2];

int main(){
	tampilMenu();
	
	return 0;
}

void tampilMenu(){
	int pilihMenu;
	
	//Program
	do{
		main:
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
			case 2 : readHighscores(); 
				break;
			case 3 : readHTPFile(); 
				break;
			case 4 : tampilTentang(); 
				break;
			case 5 : endProgram(); 
				break;
			default : printf("Menu tidak tersedia.");
		}
	} while(pilihMenu < 1 || pilihMenu > 5 );
}

void readHighscores(){
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
	getchar(); 
	tampilMenu();
}

void readHTPFile(){
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
	getchar();
	tampilMenu();
}

void tampilTentang(){
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
	getchar();
	tampilMenu();
}

void endProgram(){
	system("cls");
	printf("Terima kasih sudah bermain DaScrabble");
}

void mulaiPermainan(){
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
		
		
		panjang = strlen(Pemain[giliran].huruf);
		kurang = 7 - panjang;
		
		randomHuruf(hitungSisa(), giliran, kurang);
		printf("\n\n  Giliran: %s \t  Waktu: 01:23\t  Sisa Huruf: %d", Pemain[giliran].nama_pemain, hitungSisa());
		
		printf("\n\n\t\t");
		showHuruf(giliran);
		printf("\n\n\t\t");
		showPoin(giliran);
		
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
			
			result = cekPosisiKata(kata, baris, kolom, arah, giliran);
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

int registPemain(){
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

int cekHuruf(char *kata, int giliran){
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

int cekPosisiKata(char *kata, int baris, int kolom, int arah, int giliran){
	char temp[15] = " ";
	int i = baris;
	int j = kolom;
	int valid;
	int k = 0;
	int c = 0;
	bool status = true;
	int length, l;
	bool ada = true;
	
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
		printf("  Posisi tidak tepat, coba lagi.");
		return 0;
	}
	else{
		if(cekHuruf(kata, giliran)){
			if(cekKamus(temp)){
				hitungScore(temp, baris, kolom, arah, giliran);
				insertKePapan(temp, baris, kolom, arah);
				susunHuruf(kata, giliran);
			}
			else{
				printf("  Kata tidak valid, coba lagi,");
				printf("  %s", temp);
				return 0;
			}
		}
		else{
			printf("Masukkan huruf yang sesuai");
			return 0;
		}
		
	}
	
	length = strlen(temp);
	if((length + ((arah) ? baris : kolom)) > 15){
		printf("  Posisi kata terlalu panjang, coba lagi.");
		return 0;
	}
	
	return 1;
}

void susunHuruf(char *kata, int giliran){
	char tempHuruf[7] = " ";
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

int cekKamus(char *kata){
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

void hitungScore(char *jawaban, int baris, int kolom, int arah, int giliran){
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
	int i;
	int sisa=0;
	
	for(i=0; i<27; i++){
    	sisa += Huruf[i].jumlah;
	}
	
	return sisa;
}

void randomHuruf(int sisa, int giliran, int kurang){
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
    srand(time(0));
        for(i=0;i<kurang;i++){
        string[i]=huruf[rand() % sisa];
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
	int i, length;
	
	length = strlen(Pemain[giliran].huruf);
	for(i=0; i<length; i++){
		printf("%c ", Pemain[giliran].huruf[i]);
	}
}

void kurangiHuruf(char *string){
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

void writeHighscores(char namaBaru[100], int scoreBaru, char levelBaru[10]){
	highScore testHighscore[6];
    bool isMengisi = false;
    int i = 0;
	FILE *in=fopen("updatedHighscore.txt","r+");//perintah untuk membuka file dengan mode r / read
    while(!feof(in)){
        fscanf(in,"%[^#]#%d#%[^\n]\n", &testHighscore[i].nama, &testHighscore[i].score, &testHighscore[i].level);fflush(stdin);
        i++;
    }
	printf("Sebelum diedit\n");    
    for(i = 0; i < 6;i++){
        printf("%s\t%d\t%s\n", testHighscore[i].nama, testHighscore[i].score, testHighscore[i].level);
	}
	fclose(in);//perintah untuk menutup file yang tadi dibuka
	FILE *out=fopen("updatedHighscore.txt","w");
	for(i = 0; i < 6;i++){
        if(scoreBaru >= testHighscore[i].score && isMengisi==false){
        	fprintf(out,"%s#%d#%s\n", namaBaru, scoreBaru, levelBaru);
        	isMengisi = true;
		}
		else{
			fprintf(out,"%s#%d#%s\n", testHighscore[i].nama, testHighscore[i].score, testHighscore[i].level);
		}
	}
	fclose(out);
	getchar();
}


