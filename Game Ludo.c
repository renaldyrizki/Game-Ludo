#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// TUGAS BESAR GAME LUDO //

/////////////////////Variabel Global/////////////////
typedef struct{ int posisi_baru;
				int posisi_lama;
				int finish;
				int start;
				}bidak;
			
bidak A[5][5];
char nama[11];
/* Variabel jika menggunakan map */
//char jalur_utama[53];
//char base[5][5];
//char jalur_sendiri[5][6];
/////////////////////////////////////////////////////

/************************************************************ Prorotype Modul **********************************************************************************/
/* Fungsi */
int kocokdadu(int player);																		//perintah mengacak nilai dadu
int pilih_bidak(int player, int dadu);															//peintah untuk memilih bidak yg akan dijalankan
int cek_valid(int player, int play, int posisi_bidak, int dadu);								//mengecek bidak yang sudah dipilih apakah bisa dijalankan
int pilih_bidak2(int player, int dadu);															//perintah greddy no left behind
int cek_jauh_bidak(int min, int max, int terkecil, int terbesar, int player);					//mengecek bidak yg paling jauh dari HOME
int cek_jalur_sendiri(int player,int play);														//mengecek apakah bidak sudah pada jalur hanya dimiliki olehnya
int cek_finish_bidak(int player,int play);														//mengecek apakah bidak sudah finish
int cek_sama(int player, int play);																//mengecek apakah ada bidak yg berhenti ditempat yg sama
int cek_gameover();																				//mengecek apakah player sudah finish
/* Prosedur */
void tampilan_awal();																			//peintah untuk menampilkan tampilan awal
void initial_state();																			//perintah initail state
void tampilan_posisi(char nama[], int player);													//perintah untuk menampilkan posisi masing bidak
void jalankan(int dadu, int player, int play, int *keluar_base);								//perintah untuk menjalankan bidak
void langkah_jalur_sendiri(int *dadu,int player,int play);										//perintah untuk menjalankan bidak pd jalur hanya dimiliki olehnya
void suit(int player, int play, int i, int j);													//perintah untuk melakukan suit jika ada bidak yang sama
void kembali_ke_base(int player, int play);														//perintah untuk bidak yg kalah dari suit, dan kembali ke base
void tampilan_pemenang(int player);																//perintah menamilkan siapa pemenangnya
/***************************************************************************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////// mainprogram /////////////////////////////////////////////////////////////////////////////////
int main(){
	
	/* Deklarasi */
	int player=1;																				
	int dadu;
	int play;
	int gameover=0;
	int keluar_base;																			//variabel jika ada bidak yg keluar dari base
	
	/* Proses */
	tampilan_awal();																			//memanggil tampilan awal

  system("cls");																				//menghaus layar
  printf("||===================================================||\n");
  printf("||===================================================||\n");
  printf("||===================================================||\n");
  printf("                  Masukan Nama Anda                    \n");
  printf("                                                       \n");
  printf("                  ");
  gets(nama);																					//membaca nama yg akan bermain
  sleep(0.8);
  printf("||===================================================||\n");
  sleep(0.8);
  printf("||===================================================||\n");  
  sleep(0.8);
  printf("||===================================================||\n");
  
  system("pause");																				//perintah pause dari seluruh proses
  	
	initial_state();																	
	
	while(gameover==0)																			//pengulangan sampai ada pemenang
	{
		keluar_base=0;
		tampilan_posisi(nama,player);
		dadu=kocokdadu(player);																	//mengacak nilai dadu
		
		if(dadu>0){
			play=pilih_bidak(player,dadu);														//memilih bidak yang akan dijalankan
			jalankan(dadu,player,play,&keluar_base);											//menjalankan bidak
			cek_sama(player,play);																//mengecek jika ada yg sama
		}
				
		gameover=cek_gameover(player);															//mengecek jika game over
		
		if(gameover==1){
			tampilan_pemenang(player);
		}
		
		if((dadu==6) && (keluar_base==0) && (gameover==0)){										//jika player mendapatkan nilai dadu 6 & mendapat giliran lagi
			if(player==1){
				printf("\nSELAMAT Anda mendapat 1 giliran lagi, karena mendapat nilai dadu 6\n");
				sleep(2);																				//menehan keseluruhan proses selama 2 dtk
			}else{
				printf("\nSELAMAT player ke-%d mendapat 1 giliran lagi, karena mendapat nilai dadu 6\n", player);
				sleep(2);
			}
		}else{
			player++;
		}
				
		if(player==5){
			player=1;
		}				
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*******************************************************************tampilan awal*******************************************************************************/
void tampilan_awal(){  
  
  printf("||===================================================||\n");
  printf("||                                                   ||\n");
  printf("||                                                   ||\n");
  printf("||                                                   ||\n");
  printf("||      ||         ||    ||  ||=====\\   (=====)      ||\n");
  printf("||      ||         ||    ||  ||     ||  (     )      ||\n");
  printf("||      ||         ||    ||  ||     ||  (     )      ||\n");
  printf("||      ||======   ||====||  ||=====//  (=====)      ||\n");
  printf("||                                                   ||\n");
  printf("||                                                   ||\n");  
  printf("||                                                   ||\n");
  printf("||                   WELCOME !!!                     ||\n");
  printf("||                                                   ||\n");
  printf("||                                                   ||\n");  
  printf("||===================================================||\n");
  
  system("pause");
}

/*******************************************************************initail state*******************************************************************************/
void initial_state(){
	
	int i,j;
	
	for(i=1; i<=4; i++){														//initail posisi dan finish
		for(j=1; j<=4; j++){
			A[i][j].posisi_baru=0;
			A[i][j].posisi_lama=0;
			A[i][j].finish=0;
		}
	}
	
	for(i=1; i<=4; i++){														//initail start
		for(j=1; j<=4; j++){
			switch(i){
				case 1 : A[i][j].start=15;
						 break;
				case 2 : A[i][j].start=28;
						 break;
				case 3 : A[i][j].start=41;
						 break;
				case 4 : A[i][j].start=2;
						 break;						 						 						 
			}	
		}
	}
	
	/*for(i=1; i<=52; i++){														//initial board
		jalur_utama[i]=' ';
	}
	
	for(i=1; i<=4; i++){														//initail board
		for(j=1; j<=6; j++){
			jalur_sendiri[i][j]=' ';
		}
	}
	
	for(i=1; j<=4; i++){
		for(j=1; j<=4; j++){		
		}
	}*/
}
/***************************************************************** tampilan posisi*******************************************************************************/
void tampilan_posisi(char nama[], int player){													
  
  system("cls");
  printf("||===================================================\n");
  printf("||===================================================\n");
  printf("||   %s                      \n", nama);
  printf("||Bidak nomor 1 : %d         \n", A[1][1].posisi_baru);
  printf("||Bidak nomor 2 : %d         \n", A[1][2].posisi_baru);
  printf("||Bidak nomor 3 : %d         \n", A[1][3].posisi_baru);
  printf("||Bidak nomor 4 : %d         \n", A[1][4].posisi_baru);
  printf("||                        player 2                \n", nama);
  printf("||                     Bidak nomor 1 : %d         \n", A[2][1].posisi_baru);
  printf("||                     Bidak nomor 2 : %d         \n", A[2][2].posisi_baru);
  printf("||                     Bidak nomor 3 : %d         \n", A[2][3].posisi_baru);
  printf("||                     Bidak nomor 4 : %d         \n", A[2][4].posisi_baru);
  printf("||  player 3                 \n");
  printf("||Bidak nomor 1 : %d         \n", A[3][1].posisi_baru);
  printf("||Bidak nomor 2 : %d         \n", A[3][2].posisi_baru);  
  printf("||Bidak nomor 3 : %d         \n", A[3][3].posisi_baru);
  printf("||Bidak nomor 4 : %d         \n", A[3][4].posisi_baru);
  printf("||                        player 4                \n", nama);
  printf("||                     Bidak nomor 1 : %d         \n", A[4][1].posisi_baru);
  printf("||                     Bidak nomor 2 : %d         \n", A[4][2].posisi_baru);
  printf("||                     Bidak nomor 3 : %d         \n", A[4][3].posisi_baru);
  printf("||                     Bidak nomor 4 : %d         \n", A[4][4].posisi_baru);
  printf("||===================================================\n");
  printf("||===================================================\n");
  printf("             ");
  
  if(player==1){
			printf("Giliran pasukan %s\n", nama);
		}else{
			printf("Giliran pasukan player ke%d\n", player);
		}		
  printf("                                                   \n");  
  printf("||===================================================||\n");
	
}
/********************************************************************kocokdadu***********************************************************************************/
int kocokdadu(int player){	
	
	int i,x;
	
	system("pause");
	
	if(player==1){
		srand(time(NULL));
		for(i=0; i<100; i++){
			system("cls");
			x=rand()%6+1;																	//me-random dadu
			tampilan_posisi(nama,player);
			printf("Hasil kocokan dadu kamu adalah %d\n\n", x);
		}		
	}else{
		srand(time(NULL));
		x=rand()%6+1;																		//me-random dadu
		printf("Hasil kocokan dadu player ke %d adalah %d\n\n", player,x);
	}
		
	if((A[player][1].posisi_baru==0) && (A[player][2].posisi_baru==0) && (A[player][3].posisi_baru==0) && (A[player][4].posisi_baru==0) && (x!=6)){
		x=0;																				//jika seluruh bidak ada di base dan nilai dadu tidak 6
	}
	system("pause");
	
	return x;
}

/********************************************************************** pilih bidak ****************************************************************************/
int pilih_bidak(int player, int dadu){
	
	int valid=0;																		//variabel utk mengecek jika bidak yg diinputkan benar
	int play;																			//variabel untuk bidak yg akan dijalankan

	
	while(valid==0){
		switch(player){
			case 1 : tampilan_posisi(nama,player); 
					 printf("Pilihlah nomor bidak yang akan dijalankan : ");
				 	 scanf("%d", &play);		
				 	 if((play>=1) && (play<=4)){																				
				 	 	valid=cek_valid(player,play,A[player][play].posisi_baru,dadu);
				 	 }else{	
				 	 	printf("\nBidak ke %d mah ga ada bray >:@\n", play);				//jika yg diinputkan salah
						  sleep(2);				
				 	 }
				 	 
				 	
				 	 if(valid==0){
				 	 printf("Bidak ke %d tidak bisa dijalankan\n", play);
				 	 sleep(2);
				 	 }				
				 	 break;
				 
			case 2 : srand(time(NULL));														
					 play=rand()%4+1;														//player 2 memilih bidak secara acak				
				 	 valid=cek_valid(player,play,A[player][play].posisi_baru,dadu);
				 	 break;
				 	
			case 3 : play=pilih_bidak2(player,dadu);										//player 3 memilih idak secara greedy no left behind
				 	 valid=cek_valid(player,play,A[player][play].posisi_baru,dadu);
				 	 break;
				 
			case 4 : play=pilih_bidak2(player,dadu);										//player 4 memilih bidak secara greedy no left behind
				 	 valid=cek_valid(player,play,A[player][play].posisi_baru,dadu);
				 	 break;
		}				
	}

	return play;
}
/*********************************************************************cek_valid**********************************************************************************/
int cek_valid(int player, int play, int posisi_bidak, int dadu){
	
	int find;
	
	if((A[player][play].posisi_baru==0) && (dadu!=6)){										//jika player memilih bidak yg ada di BASE tetapi nilai dadu tidak 6
		return 0;
	}else{
		if(A[player][play].finish==1){														//jika player memilih bidak yg sudah di HOME
			return 0;
		}else{
			return 1;																		//jika yg diinputkan benar
		}				
	}
}

/************************************************************** pilih_bidak2 *************************************************************************************/
int pilih_bidak2(int player, int dadu){
	
	int find=0;
	int min=1;
	int play;
	
	if(dadu==6){																		//jika nilai dadu 6, maka bidak yg ada di dalam BASE yg akan didahulukan
		play=1;
		while((play<=4) && (find==0)){			
			if((A[player][play].posisi_baru==0) && (find==0)){
				return play;															
			}
			play++;
		}
	}else{
		play=2;
		while(play<=4){																		//mendahulukan bidak yg paling jauh dari HOME
			if((A[player][min].posisi_baru!=0) && (A[player][play].posisi_baru!=0)){
				min=cek_jauh_bidak(min,play,A[player][min].posisi_baru,A[player][play].posisi_baru,player);
			}						
			play++;
		}
		
		return min;
	}	 
}

/********************************************************* cek jauh bidak *************************************************************************************/
int cek_jauh_bidak(int min, int max, int terkecil, int terbesar, int player){
	
	
	if((A[player][min].posisi_baru<A[player][min].start) || (A[player][min].posisi_baru>52)){				//jaraknya bidak disesuaikan dengan array jalur_utama
		terkecil=A[player][min].posisi_baru+52-A[player][min].start;
	}else{
		terkecil=A[player][min].posisi_baru-A[player][min].start;
	}
	
	if((A[player][max].posisi_baru<A[player][min].start) || (A[player][min].posisi_baru>52)){				//jaraknya bidak disesuaikan dengan array jalur_utama
		terbesar=A[player][max].posisi_baru+52-A[player][max].start;
	}else{
		terbesar=A[player][max].posisi_baru-A[player][max].start;
	}	
	
	
	if(terkecil<=terbesar){		
		return min;
	}else{
		return max;
	}
}

/*************************************************************************jalankan******************************************************************************/
void jalankan(int dadu, int player, int play, int *keluar_base){															//langkah bida
	
	/* Deklarasi */
	int belok;	
	
	/* Proses */
	if((A[player][play].posisi_baru==0) && (dadu==6)){							//bidak di dalam base di pastikan tidak bisa dipilih jika nilai dadu TIDAK 6
		dadu=0;
		A[player][play].posisi_baru=A[player][play].start;
		*keluar_base=1;
	}
	
	while(dadu>0){
		belok=cek_jalur_sendiri(player,play);
		
		if(belok==1){
			langkah_jalur_sendiri(&dadu,player,play);
		}else{
			if(A[player][play].posisi_baru==52){								//posisi disesuaikan dengan array jalur_utama
				A[player][play].posisi_baru=1;
				dadu--;
			}else{
				A[player][play].posisi_baru=A[player][play].posisi_baru+1;
				dadu--;
			}			
		}		
	}
		
	}

/****************************************************************cek_jalur_sendiri********************************************************************************/
int cek_jalur_sendiri(int player,int play){
	
	if(A[player][play].posisi_baru==player*13){									//mengecek belokan utk jalurnya sendiri disesuaikan dengan array jalur_utama
		A[player][play].posisi_baru=53;											//jika bidak sudah di jalurnya hanya miliknya posisi akan diisi >52
		return 1;
	}else{
		if(A[player][play].posisi_baru>52){
			return 1;
		}else{
			return 0;
		}
	}
}

/**********************************************************langkah_jalur_sendiri**********************************************************************************/
void langkah_jalur_sendiri(int *dadu,int player,int play){
	
	int selesai;
	
	do{
		selesai=cek_finish_bidak(player,play);
		
		if(selesai==0){
			A[player][play].posisi_baru=A[player][play].posisi_baru+1;
			*dadu=*dadu-1;
			
			selesai=cek_finish_bidak(player,play);
			if((selesai==1) && (*dadu==0)){
				A[player][play].finish=1;
			}			
		}else{
			while(*dadu>0){
					A[player][play].posisi_baru=A[player][play].posisi_baru-1;
					*dadu=*dadu-1;
			}
		}
	}while(*dadu>0);
}

/*******************************************************************cek_finish_bidak***************************************************************************/
int cek_finish_bidak(int player,int play){
	
	if(A[player][play].posisi_baru-53==6){
		return 1;
	}else{	
		return 0;
	}
}

/************************************************************************** cek sama ***************************************************************************/
int cek_sama(int player, int play){															//cek_sama
	int lawan,bidak_lawan;
	int find;
	
	/* Proses */
	lawan=1;
	find=0;
	while((lawan<=4) && (find==0)){
		bidak_lawan=1;
		while((bidak_lawan<=4) && (find==0)){
			if(player!=lawan){
				if((A[player][play].posisi_baru==A[lawan][bidak_lawan].posisi_baru) && (A[player][play].posisi_baru<53) && (A[player][play].posisi_baru>0)){
				find=1;
				suit(player,play,lawan,bidak_lawan);
				}
			}
			bidak_lawan++;
		}
		lawan++;
	}
	
}
/********************************************************************suit***************************************************************************************/
void suit(int player, int play, int lawan, int bidak_lawan){
	
	
	int pilihan1,pilihan2;
	int valid1=0,valid2,temp=0;
	
	if((player==1) || (lawan==1)){
		
		if(lawan==1){
			temp=player;
			player=lawan;
			lawan=temp;
			
			temp=play;
			play=bidak_lawan;
			bidak_lawan=temp;
		}
		printf("\nPosisi bidak anda sama dengan posisi bidak player ke %d", lawan);
		
		do{																											//Looping jika seri
			printf("\nLakukan SUIT!!, Inputkan :");
			printf("\n				1. Kertas");
			printf("\n				2. Gunting");
			printf("\n				3. Batu\n");
				
				valid2=0;															
				while(valid2==0){																					//Looping jika yang diputkan salah
					scanf("%d", &pilihan1);
					if((pilihan1==1) || (pilihan1==2) || (pilihan1==3)){
						valid2=1;
					}else{
						printf("\nInput yang anda masukan salah\n");
					}
				}
				
				srand(time(NULL));																					//Random com
				pilihan2=rand()%3+1;
			
				if(pilihan1==pilihan2){
					printf("\nAnda SERI!!!, Suit diulang");
				}else{
					valid1=1;
				}
				
				
		}while(valid1==0);
		
			switch(pilihan1){																						//Case menentukan menang kalah
				case 1 : 	if(pilihan2==2){
								printf("\nAnda KALAH!!!, bidak anda kembali ke BASE!!!");
								sleep(4);
								kembali_ke_base(player,play);
						 	}else{
						 		printf("\nAnda MENANG!!!, bidak player ke-%d kembali ke BASE!!!", lawan);
						 		sleep(4);
						 		kembali_ke_base(lawan,bidak_lawan);
						 	}
						 	break;
				
				case 2 : 	if(pilihan2==3){
								printf("\nAnda KALAH!!!, bidak anda kembali ke BASE!!!");
								sleep(4);
								kembali_ke_base(player,play);
						 	}else{
						 		printf("\nAnda MENANG!!!, bidak player ke-%d kembali ke BASE!!!", lawan);
						 		sleep(4);
						 		kembali_ke_base(lawan,bidak_lawan);
						 	}
						 	break;
						 	
				case 3 : 	if(pilihan2==1){
								printf("\nAnda KALAH!!!, bidak anda kembali ke BASE!!!");
								sleep(4);
								kembali_ke_base(player,play);
						 	}else{
						 		printf("\nAnda MENANG!!!, bidak player ke-%d kembali ke BASE!!!", lawan);
						 		sleep(4);
						 		kembali_ke_base(lawan,bidak_lawan);
						 	}
						 	break;
			}
		}else{
			
			printf("\nPosisi bidak player ke-%d sama dengan posisi bidak player ke-%d", player,lawan);
			sleep(4);
			
			do{
				srand(time(NULL));
				pilihan1=rand()%3+1;
			
				srand(time(NULL));
				pilihan2=rand()%3+1;
				
				if(pilihan1!=pilihan2){
					valid1=1;
				}
				
			}while(valid1==0);
			
			
			switch(pilihan1){																						//Case menentukan menang kalah
				case 1 : 	if(pilihan2==2){
								printf("\nplayer ke-%d MENANG!!!, bidak player ke-%d kembali ke BASE!!!", lawan,player);
								sleep(4);
								kembali_ke_base(player,play);								
						 	}else{
						 		printf("\nplayer ke-%d MENANG!!!, bidak player ke-%d kembali ke BASE!!!", player,lawan);
								sleep(4);
						 		kembali_ke_base(lawan,bidak_lawan);
						 	}
						 	break;
				
				case 2 : 	if(pilihan2==3){
								printf("\nplayer ke-%d MENANG!!!, bidak player ke-%d kembali ke BASE!!!", lawan,player);
								sleep(4);
								kembali_ke_base(player,play);
						 	}else{
						 		printf("\nplayer ke-%d MENANG!!!, bidak player ke-%d kembali ke BASE!!!", player,lawan);
								sleep(4);
						 		kembali_ke_base(lawan,bidak_lawan);
						 	}
						 	break;
						 	
				case 3 : 	if(pilihan2==1){
								printf("\nplayer ke-%d MENANG!!!, bidak player ke-%d kembali ke BASE!!!", lawan,player);
								sleep(4);
								kembali_ke_base(player,play);
						 	}else{
						 		printf("\nplayer ke-%d MENANG!!!, bidak player ke-%d kembali ke BASE!!!", player,lawan);
								sleep(4);
						 		kembali_ke_base(lawan,bidak_lawan);						 		
						 	}
						 	break;
			}
		}
		
	}
/******************************************************************** kembali ke base **************************************************************************/	
void kembali_ke_base(int player, int play){
	
	A[player][play].posisi_baru=0;
	//jalur_utama[A[player][play].posisi_lama]=' ';
	
}

/************************************************************* cek gameover ************************************************************************************/
int cek_gameover(int player){													//cek_finish
	
	int find=0;
	
	if((A[player][1].finish==1) && (A[player][2].finish==1) && (A[player][3].finish==1) && (A[player][4].finish==1)){
			find=1;
		}

	return find;
}

/**************************************************************** Tampilan Pemenang *****************************************************************************/
void tampilan_pemenang(int player){
	
	if(player!=1)																			//lose
		{
			for(player=1; player<=3; player++){
		system("cls");
		printf("   ***     ***  ***    ***    ***     ***        ***     ******  *******\n");
		sleep(0.8);
		printf("    ***   *** **   **  ***    ***     ***      **   **  **       *******\n");
		sleep(0.8);
		printf("     *** *** **     ** ***    ***     ***     **     ** **       **     \n");
		sleep(0.8);
		printf("      *****  **     ** ***    ***     ***     **     **  *****   ****   \n");
		sleep(0.8);
		printf("       ***   **     ** ***    ***     ***     **     **       ** **     \n");
		sleep(0.8);
		printf("       ***    **   **   ***  ***      *******  **   **        ** *******\n");
		sleep(0.8);
		printf("       ***      ***      ******       *******    ***     ******  *******\n");
		sleep(0.8);
		printf("player ke-%d yang memenangkan permainan", player);
		sleep(3);
			}
		}
	else																				//win
		{
			for(player=1; player<=3; player++){
		system("cls");
		printf("     ***     ***  ***    ***    ***     ***       *** *** ***   ***\n");
		sleep(0.8);
		printf("      ***   *** **   **  ***    ***     ***       *** *** ****  ***\n");
		sleep(0.8);
		printf("       *** *** **     ** ***    ***     ***       *** *** ***** ***\n");
		sleep(0.8);
		printf("        *****  **     ** ***    ***     *** ***** *** *** *********\n");
		sleep(0.8);
		printf("         ***   **     ** ***    ***     ****** ****** *** *** *****\n");
		sleep(0.8);
		printf("         ***    **   **   ***  ***      *****   ***** *** ***  ****\n");
		sleep(0.8);
		printf("         ***      ***      ******       ****     **** *** ***   ***\n");
		sleep(0.8);
		printf("SELAMAT %s, Anda memenangkan permainan", nama);
		sleep(3);
			}
	}
}
