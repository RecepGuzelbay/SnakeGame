#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define formatBool(b) ((b) ? "Acik" : "Kapali")

int en = 40, boy = 40;
char hiz = '4';
long sure = 90000000;
int puan;
int yilanBoy;
bool son;
bool duvar, icindenGec, geriDon;
char isim[30];
char kod[20] = "AliAkurgal";

enum yonelim
{
    sag = 1,
    sol,
    yukari,
    asagi
} yon;

typedef struct
{
    int x;
    int y;
} konum;

konum *knm;
konum yem;

typedef struct {
	char isim[10];
	int skor;
	char tarih[10];
	char saat[14];
	int en;
	int boy;
	int hiz;
} skorBilgi;

time_t t;
struct tm *zaman;

int hile()
{
	char secim;
	system ("cls");
	printf ("****************************** Hile Menusu ******************************\n\n");
	printf ("Hileyi acmak icin basindaki numarayi giriniz\nNot : Geri donme hilesi acildiginda icinden geme hilesi otomatik olarak acilir\n");
	printf ("1) Duvar Hilesi : %s\n2) Icinden Gecme Hilesi : %s\n3) Geri Donme Hilesi : %s\n4) Oyunu Baslat\n", formatBool(duvar), formatBool(icindenGec), formatBool(geriDon));
	
	do {
		printf ("\n1 ile 4 arasinda bir deger giriniz... ");
        secim = getch();
    } while(secim < '1' || secim > '4');
    
    switch (secim) {
    	case '1': duvar = !duvar; break;
    	case '2': icindenGec = !icindenGec; break;
    	case '3': geriDon = !geriDon; break;
    	case '4': return 0;
	}
	
	if (geriDon == 1)
		icindenGec = 1;
	
	hile();
}

int giris()
{
	char secim;
	char alan;
		
	printf ("Kullanici adinizi giriniz : ");
	scanf ("%s", &isim);
	
	printf ("1) Klasik Mod \n2) Ozel Mod\n");
	
	do {
		printf ("\n1 ile 2 arasinda bir deger giriniz... ");
        secim = getche();
    } while(secim < '1' || secim > '2');
	
	if (secim == '2') {
		printf ("\n\nAlan boyutunu seciniz... \n1) Kucuk Boy (25*25)\n2) Orta Boy (35*35) \n3) Buyuk Boy (45*45) \n4) Ozel Boy");
		
		do {
			printf ("\n1 ile 4 arasinda bir deger giriniz... ");
        	alan = getche();
    	} while(alan < '1' || alan > '4');
    	
    	switch (alan) {
    		case '1': boy = 25, en = 25; break;
    		case '2': boy = 35, en = 35; break;
    		case '3': boy = 45, en = 45; break;
    		case '4':
    			printf ("\nEn ve boy degerlerini giriniz : ");
    			scanf ("%d %d", &en, &boy);
    			break;
		}
		
		printf ("\n\nOyun hizini seciniz... \n1 ile 9 arasinda bir deger giriniz (1 : En Yavas, 9 : En Hizli)... \n");
		
		do {
			printf ("\n1 ile 9 arasinda bir deger giriniz... ");
        	hiz = getche();
    	} while(hiz < '1' || hiz > '9');
    	
    	switch (hiz) {
    		case '1': sure = 150000000; break;
    		case '2': sure = 125000000; break;
    		case '3': sure = 100000000; break;
    		case '4': sure = 90000000; break;
    		case '5': sure = 75000000; break;
    		case '6': sure = 60000000; break;
    		case '7': sure = 45000000; break;
    		case '8': sure = 35000000; break;
    		case '9': sure = 25000000; break;
		}
	}
	
	printf ("\n\nEn : %d Boy : %d Hiz : %c", en, boy, hiz);
	getch();
	
	if (!strcmp(isim, kod))
		hile();
}

void kayit ()
{
	FILE *fptr;
	
	fptr = fopen("oyuncular.txt", "a");
	
	fprintf (fptr, "%s\t %d\t %d\t %d\t %c\t", isim, puan, en, boy, hiz);
	
	time(&t);
	zaman=localtime(&t);
    if(zaman->tm_year>99) zaman->tm_year-=100;
    
	fprintf(fptr, "%d/%d/%d\t", zaman->tm_mday, zaman->tm_mon+1, zaman->tm_year);
	fprintf(fptr, "%d:%d:%d\n", zaman->tm_hour, zaman->tm_min, zaman->tm_sec);

	fclose(fptr);
}

void kurulum()
{
    knm = (konum *) malloc (sizeof(konum)*2);
    son = true;

    knm[0].y = boy / 2;
    knm[0].x = en / 2;

    srand(time(NULL));
	
	atla:
    yem.y = rand() % boy;
    yem.x = rand() % en;

    if (yem.y <= 1 || yem.x <= 1 || yem.y >= boy-1 || yem.x >= en-1)
            goto atla;

    puan = 0;
    yilanBoy = 1;
}

bool govde(int x, int y)
{
    for (int i = 0; i < yilanBoy; i++)
    {
        if (y == knm[i].y && x == knm[i].x)
            return 1;
    }

    return 0;
}

void ciz()
{
    system("cls");

    for (int i = 0; i < boy; i++)
    {
        for (int j = 0; j < en; j++)
        {
            if (i == 0 || i == boy - 1 || j == 0 || j == en - 1)
                printf("#");

            else if (i == knm[0].y && j == knm[0].x)
                printf("0");

            else if (i == yem.y && j == yem.x)
                printf("*");

            else if (govde(j,i))
                printf("+");

            else
                printf(" ");
        }

        printf("\n");
    }

    printf("Cikis yapmak icin x'e basiniz!\nPuan = %d", puan);

    printf("\n");
}

void bekle()
{
    for (int i = 0; i < sure; i++)
    {
    }
}

void degis()
{
    int yedek1y = knm[0].y;
    int yedek1x = knm[0].x;
    int yedek2x, yedek2y;

    for (int i = 1; i < yilanBoy; i++)
    {
        yedek2y = knm[i].y;
        yedek2x = knm[i].x;
        knm[i].x = yedek1x;
        knm[i].y = yedek1y;
        yedek1x = yedek2x;
        yedek1y = yedek2y;
    }
}

void tus()
{
    if (kbhit())
    {
    	char bas = getch();

        if (((bas == 'd' || bas == '6') && (geriDon == true || yon != 2)) || ((bas == 'a' || bas == '4') && (geriDon == true || yon != 1)) || ((bas == 's' || bas == '8') && (geriDon == true || yon != 3)) || (( bas == 'w' || bas == '2') && (geriDon == true || yon != 4)) || bas == 'x')
        {
            switch (bas)
            {
            case 'd':
            case '6':
                yon = sag;
                break;

            case 'a':
            case '4':
                yon = sol;
                break;

            case 'w':
            case '2':
                yon = yukari;
                break;

            case 's':
            case '8':
                yon = asagi;
                break;

            case 'x':
                son = false;
                break;
            }
        }
    }
}

void olum()
{
	if (duvar == false) {
        if (knm[0].y < 1 || knm[0].y > boy - 2 || knm[0].x < 1 || knm[0].x > en - 2)
            son = false;
    }

    else {
        if (knm[0].x >= en - 1)
            knm[0].x = 1;
        else if (knm[0].x <= 1)
            knm[0].x = en - 1;

        if (knm[0].y >= boy - 1)
            knm[0].y = 1;
        else if (knm[0].y <= 1)
            knm[0].y = boy - 1;
    }

    if (icindenGec == false) {
        for (int i = 1; i < yilanBoy; i++)
        {
            if (knm[0].y == knm[i].y && knm[0].x == knm[i].x)
            {
                son = false;
                break;
            }
        }
    }
}

void islem()
{
    degis();

    bekle();

    switch (yon)
    {
    case 1:
        knm[0].x++;
        break;

    case 2:
        knm[0].x--;
        break;

    case 3:
        knm[0].y--;
        break;

    case 4:
        knm[0].y++;
        break;

    default:
        break;
    }
    
    olum();

    if (knm[0].y == yem.y && knm[0].x == yem.x)
    {
        knm = (konum *) realloc (knm, sizeof(konum)*(yilanBoy+1));
        atla:
        yem.y = rand() % boy;
        yem.x = rand() % en;

        if (yem.y <= 1 || yem.x <= 1 || yem.y >= boy-1 || yem.x >= en-1)
            goto atla;

        for (int i = 0; i < yilanBoy; i++)
            if (yem.y == knm[i].y && yem.x == knm[i].x)
                goto atla;

        puan += 10;
        yilanBoy++;
    }
}

void siralama()
{
	FILE *fptr;
	
	fptr = fopen("oyuncular.txt", "r");
	
	skorBilgi *oyuncu = (skorBilgi *) malloc (sizeof(skorBilgi));
	int okunan = 0;
	
	if (fptr == NULL)
		printf ("Islem Gerceklestirilemiyor!!!");
	
	while (!feof(fptr)) {
		fscanf (fptr, "%s\t %d\t %d\t %d\t %c\t %s\t %s\n", &oyuncu[okunan].isim, &oyuncu[okunan].skor, &oyuncu[okunan].en, &oyuncu[okunan].boy, &oyuncu[okunan].hiz ,&oyuncu[okunan].tarih, &oyuncu[okunan].saat);
		okunan++;
		oyuncu = (skorBilgi *) realloc (oyuncu, sizeof(skorBilgi)*(okunan+1));
	}
	
	skorBilgi temp;
	
	for (int i = 1; i < okunan; i++) {
    	for (int j = 0; j < okunan - i; j++) {
        	if (oyuncu[j].skor < oyuncu[j+1].skor) {
            	temp = oyuncu[j+1];
            	oyuncu[j+1] = oyuncu[j];
            	oyuncu[j] = temp;
        	}
    	}
   }
	
	system ("cls");
	
	printf ("*********************** Liderlik Tablosu ***********************\n\n");
	for (int i = 0; i < 10; i++)
		printf ("%d) %s\t %d\t En : %d  Boy : %d  Hiz : %c\t %s %s\n", i+1, oyuncu[i].isim, oyuncu[i].skor,  oyuncu[i].en, oyuncu[i].boy, oyuncu[i].hiz, oyuncu[i].tarih, oyuncu[i].saat);
}

int main()
{
	giris();
	
    kurulum();

    while (son)
    {
        ciz();

        tus();

        islem();
    }
    
    getch();

    kayit();
    
    siralama();
    
    return 0;
}
