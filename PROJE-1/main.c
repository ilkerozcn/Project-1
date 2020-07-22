#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
struct oku
{
    float x;
    float y;
    float z;
};
struct oku1
{
    float x;
    float y;
    float z;
    int r;
    int g;
    int b;
};
struct bilgi
{
    char version[50];
    char alan[50];
    char nokta[50];
    char tip[50];
    int noktasayi[20];
    int hatadegeri[20];
    int datadegeri[20];
    int alandegeri[20];

};
struct
{
    //int b1,b2;
    double x;
    double y;
    double z;
    int r;
    int g;
    int b;
} nokta[20][100000];
int main()
{
    //int hatalisatir=0;
    double toplam;
    int by1[20];
   // int ky1[20];
    int by2[20];
   // int ky2[20];
    double max;
    double kurex,kurey,kurez;
    double ycap;
    int j;
    int k;
    int nktsayi=0;

    double uzak;
    double enb;
    double kenuz;
    struct bilgi inf;
    char str[60];
    char strnok[20];


    int tercih;
    char tx[20],ty[20],tr[20],tg[20],tz[20],tb[20];

    int dosya_sayi=0;
    char dosyasay[50][100];
    int byer1,byer2,kyer1,kyer2;
    DIR *dosyaisimoku;
    struct dirent *dosyaisim;
    dosyaisimoku = opendir (".");

    printf("1) Dosya Kontrolu\n");
    /*printf("2) En Yakin/Uzak Noktalar\n");
    printf("3) Kup\n");
    printf("4) Kure\n");
    printf("5) ORTALAMA\n\n");*/

    FILE *frp=fopen("output.txt","w");
    //printf("Nokta Uzakliklari Ortalamasi\n");

    if (dosyaisimoku != NULL)//ntk uzantili dosyalari okuma
    {
        while ((dosyaisim = readdir (dosyaisimoku))!=NULL)
        {

            int length = strlen(dosyaisim->d_name);

            if (strncmp(dosyaisim->d_name + length - 4, ".nkt", 4) == 0)
            {

                //puts (dosyaisim->d_name);
                strcpy(dosyasay[dosya_sayi],dosyaisim->d_name);
                dosya_sayi++;
            }
        }
//printf("%s",dosyasay[1]);
        //  char strnok[20];
        // char str[50];
        // printf("\n%d dosya sayisi\n",dosya_sayi);
        (void) closedir (dosyaisimoku);
    }
    scanf("%d",&tercih);
    if(tercih==1)
    {
        //DOSYA KONTROLU
        for(int i=0; i<dosya_sayi; i++)//Bilgi satilari kontrolu
        {
            inf.hatadegeri[i]=1;
            FILE *fp=fopen(dosyasay[i],"r");
            fgets(str,50,fp);
            fgets(str,50,fp);
            strcpy(inf.version,str);
            fgets(str,50,fp);
            strcpy(inf.alan,str);
            fscanf(fp,"%s %s",str,strnok);
            strcpy(inf.nokta,str);
            inf.noktasayi[i]=atof(strnok);
            fgets(str,50,fp);
            fgets(str,50,fp);
            strcpy(inf.tip,str);

            if(strstr(inf.version,"VERSION") && strstr(inf.version,"1") && inf.hatadegeri[i]==1) {}
            else
            {
                printf("%s Dosyanin Version bilgisi yanlis.\n",dosyasay[i]);
                fprintf(frp,"%s Dosyanin Version bilgisi yanlis.\n",dosyasay[i]);
                inf.hatadegeri[i]=0;
            }
            if(strstr(inf.alan,"ALANLAR") && inf.hatadegeri[i]==1)
                if(strstr(inf.alan,"x y z r g b")||strstr(inf.alan,"x y z"))
                {
                    if(strstr(inf.alan,"x y z r g b"))
                        inf.alandegeri[i]=1;
                    else
                        inf.alandegeri[i]=0;
                }
                else
                {
                    printf("%s Dosyasinin alan bilgisi yanlis.\n",dosyasay[i]);
                    fprintf(frp,"%s Dosyasinin alan bilgisi yanlis.\n",dosyasay[i]);
                    inf.hatadegeri[i]=0;
                }
            if(strstr(inf.nokta,"NOKTALAR") && inf.hatadegeri[i]==1) {}
            else
            {
                inf.hatadegeri[i]=0;
            }
            if(inf.hatadegeri[i]==1)
            {
                if(strstr(inf.tip,"ascii")||strstr(inf.tip,"binary"))
                {
                    if(strstr(inf.tip,"ascii"));
                    {
                        inf.datadegeri[i]=0;
                    }
                    if (strstr(inf.tip,"binary"))
                    {
                        inf.datadegeri[i]=1;
                    }
                }
                else
                {
                    printf("%s Dosyasinin data bilgisi yanlis.\n",dosyasay[i]);
                    fprintf(frp,"%s Dosyasinin data bilgisi yanlis.\n",dosyasay[i]);
                    inf.hatadegeri[i]=0;
                }
                nktsayi=0;
                if(inf.hatadegeri[i]==1 && inf.datadegeri[i]==0)
                {
                    while(!feof(fp))
                    {
                        // FILE *fp=fopen(dosyasay[i],"r");
                        fgets(str,50,fp);
                        nktsayi++;
                    }
                    if(inf.noktasayi[i]!=nktsayi-1)
                    {
                        printf("%s Verilen nokta degeri yanlis\n",dosyasay[i]);
                        fprintf(frp,"%s Verilen nokta degeri yanlis\n",dosyasay[i]);
                        inf.hatadegeri[i]=0;
                    }
                    else
                    {
                        //printf("Sayilan nokta sayisi: %d\n",nktsayi-1);
                        //printf("\n%s nokta sayisi dogru",dosyasay[i]);
                    }
                }

            }

            /* printf("\n%s\n",dosyasay[i]);
             printf("Nokta sayisi %d\n",inf.noktasayi[i]);
             printf("Hata degeri %d\n",inf.hatadegeri[i]);
             printf("Data degeri %d\n",inf.datadegeri[i]);
             printf("Alan degeri %d\n",inf.alandegeri[i]);*/
            rewind(fp);
            if(inf.hatadegeri[i]==1 && inf.datadegeri[i]==0 && inf.alandegeri[i]==0)
            {
                //printf("%s DOSYASININ NOKTALARI: \n",dosyasay[i]);
                //printf("%d",i);
                k=0;
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                while(!feof(fp) && k!=inf.noktasayi[i])
                {
                    fscanf(fp,"%s %s %s",tx,ty,tz);
                    nokta[i][k].x=atof(tx);
                    nokta[i][k].y=atof(ty);
                    nokta[i][k].z=atof(tz);
                    // printf("%lf %lf %lf\n",nokta[i][k].x,nokta[i][k].y,nokta[i][k].z);

                    k++;
                }
                // printf("%s DOSYASININ NOKTA ATAMASI TAMAMLANDI ",dosyasay[i]);
            }
            if(inf.hatadegeri[i]==1 && inf.datadegeri[i]==0 && inf.alandegeri[i]==1)
            {
                // printf("%s DOSYASININ NOKTALARI: \n",dosyasay[i]);
                //printf("%d",i);
                k=0;
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                while(!feof(fp) && k!=inf.noktasayi[i])
                {
                    fscanf(fp,"%s %s %s %s %s %s",tx,ty,tz,tr,tg,tb);
                    nokta[i][k].x=atof(tx);
                    nokta[i][k].y=atof(ty);
                    nokta[i][k].z=atof(tz);
                    nokta[i][k].r=atoi(tr);
                    nokta[i][k].g=atoi(tg);
                    nokta[i][k].b=atoi(tb);
                    //printf("%lf %lf %lf %d %d %d\n",nokta[i][k].x,nokta[i][k].y,nokta[i][k].z,nokta[i][k].r,nokta[i][k].g,nokta[i][k].b);
                    k++;
                }
                //printf("%s DOSYASININ NOKTA ATAMASI TAMAMLANDI ",dosyasay[i]);
            }
            //printf("%d",k);}
            fclose(fp);
        }
        for(int i=0; i<dosya_sayi; i++)//Bilgi satilari kontrolu
        {
            if(inf.hatadegeri[i]==1 && inf.datadegeri[i]==1 && inf.alandegeri[i]==0)
            {

                size_t sayi;
                FILE *fp = fopen(dosyasay[i], "rb");

                if(fp == NULL)
                {
                    printf("HATA!!!\n");
                    fprintf(frp,"HATA!!!\n");
                    exit(1);
                }
                char str[20];
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                int j=0;
                int sayac = 0;
                while(1)
                {

                    struct oku a1;
                    sayi = fread(&a1, sizeof(a1), 1, fp);
                    nokta[i][j].x=a1.x;
                    nokta[i][j].y=a1.y;
                    nokta[i][j].z=a1.z;
                    j++;
                    sayac++;

                    if(sayi < 1)
                    {
                        break;
                    }
                }
                fclose(fp);
            }
        }
        for(int i=0; i<dosya_sayi; i++)//Bilgi satilari kontrolu
        {
            if(inf.hatadegeri[i]==1 && inf.datadegeri[i]==1 && inf.alandegeri[i]==1)
            {

                size_t sayi;
                FILE *fp = fopen(dosyasay[i], "rb");

                if(fp == NULL)
                {
                    printf("HATA!!!\n");
                    fprintf(frp,"HATA!!!\n");
                    exit(1);
                }
                char str[20];
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                fgets(str,50,fp);
                int j=0;
                int sayac = 0;
                while(1)
                {
                    sayi=-1;
                    struct oku1 a2;
                    sayi = fread(&a2, sizeof(a2), 1, fp);
                    nokta[i][j].x=a2.x;
                    nokta[i][j].y=a2.y;
                    nokta[i][j].z=a2.z;
                    nokta[i][j].r=a2.r;
                    nokta[i][j].g=a2.g;
                    nokta[i][j].b=a2.b;
                    j++;
                    sayac++;

                    if(sayi < 1)
                    {
                        break;
                    }
                }
                fclose(fp);
            }
        }
        /*goto scm; */
    }
scm:
    printf("2) En Yakin/Uzak Noktalar\n");
    printf("3) Kup\n");
    printf("4) Kure\n");
    printf("5) ORTALAMA\n\n");
    printf("6) CIKIS");
    //KONTROL BITTI
    scanf("%d",&tercih);
    if(tercih==2)
    {
        /* for(int i=0;i<dosya_sayi;i++){
             if(inf.hatadegeri[i]==1 &&)

         }*/


        for(int i=0; i<dosya_sayi; i++)                    //EN UZAK EN YAKIN NOKTA BULMA ASCII
        {
            enb=0;
            uzak=0;
            if(inf.hatadegeri[i]==1 )
            {
                double enk=fabs(sqrt((pow(nokta[i][0].x-nokta[i][1].x,2))+(pow(nokta[i][0].y-nokta[i][1].y,2))+(pow(nokta[i][0].z-nokta[i][1].z,2))));
                printf("En yakin en uzak nokta bulunuyor\n");
                for(j=0; j<inf.noktasayi[i]; j++)
                {
                    for(int l=j+1; l<inf.noktasayi[i]; l++) //((x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2) 2 nokra arasý uzaklýk
                    {
                        uzak=fabs(sqrt((pow(nokta[i][j].x-nokta[i][l].x,2))+(pow(nokta[i][j].y-nokta[i][l].y,2))+(pow(nokta[i][j].z-nokta[i][l].z,2))));

                        if(enb<uzak)
                        {
                            enb=uzak;
                            byer1=j;
                            byer2=l;
                        }
                        if(enk>uzak)
                        {
                            enk=uzak;
                            kyer1=j;
                            kyer2=l;
                        }
                    }

                }

                if(inf.alandegeri[i]==1)
                {
                    printf("\n%s. DOSYA\n",dosyasay[i]);
                    printf("En uzak nokta degerleri \n%d. nokta     x: %lf y: %lf z: %lf r: %d g: %d b: %d\n",byer1,nokta[i][byer1].x,nokta[i][byer1].y,nokta[i][byer1].z,nokta[i][byer1].r,nokta[i][byer1].g,nokta[i][byer1].b);
                    printf("%d. nokta   x: %lf y: %lf z: %lf r: %d g: %d b: %d\n",byer2,nokta[i][byer2].x,nokta[i][byer2].y,nokta[i][byer2].z,nokta[i][byer2].r,nokta[i][byer2].g,nokta[i][byer2].b);
                    printf("En yakin nokta degerleri \n%d.nokta     x: %lf y: %lf z: %lf r: %d g: %d b: %d\n",kyer1,nokta[i][kyer1].x,nokta[i][kyer1].y,nokta[i][kyer1].z,nokta[i][kyer1].r,nokta[i][kyer1].g,nokta[i][kyer1].b);
                    printf("%d. nokta   x: %lf y: %lf z: %lf r: %d g: %d b: %d\n",kyer2,nokta[i][kyer2].x,nokta[i][kyer2].y,nokta[i][kyer2].z,nokta[i][kyer2].r,nokta[i][kyer2].g,nokta[i][kyer2].b);
                    by1[i]=byer1;
                    by2[i]=byer2;
                   // ky1[i]=kyer1;
                   // ky2[i]=kyer2;
                    fprintf(frp,"\n%s. DOSYA\n",dosyasay[i]);
                    fprintf(frp,"En uzak nokta degerleri \n%d. nokta     x: %lf y: %lf z: %lf r: %d g: %d b: %d\n",byer1,nokta[i][byer1].x,nokta[i][byer1].y,nokta[i][byer1].z,nokta[i][byer1].r,nokta[i][byer1].g,nokta[i][byer1].b);
                    fprintf(frp,"%d. nokta   x: %lf y: %lf z: %lf r: %d g: %d b: %d\n",byer2,nokta[i][byer2].x,nokta[i][byer2].y,nokta[i][byer2].z,nokta[i][byer2].r,nokta[i][byer2].g,nokta[i][byer2].b);
                    fprintf(frp,"En yakin nokta degerleri \n%d.nokta     x: %lf y: %lf z: %lf r: %d g: %d b: %d\n",kyer1,nokta[i][kyer1].x,nokta[i][kyer1].y,nokta[i][kyer1].z,nokta[i][kyer1].r,nokta[i][kyer1].g,nokta[i][kyer1].b);
                    fprintf(frp,"%d. nokta   x: %lf y: %lf z: %lf r: %d g: %d b: %d\n",kyer2,nokta[i][kyer2].x,nokta[i][kyer2].y,nokta[i][kyer2].z,nokta[i][kyer2].r,nokta[i][kyer2].g,nokta[i][kyer2].b);
                }
                else
                {
                    printf("\n%s. DOSYA\n",dosyasay[i]);
                    printf("En uzak nokta degerleri \n%d. nokta     x: %lf y: %lf z: %lf\n",byer1,nokta[i][byer1].x,nokta[i][byer1].y,nokta[i][byer1].z);
                    printf("%d. nokta   x: %lf y: %lf z: %lf \n",byer2,nokta[i][byer2].x,nokta[i][byer2].y,nokta[i][byer2].z);
                    printf("En yakin nokta degerleri \n%d.nokta     x: %lf y: %lf z: %lf \n",kyer1,nokta[i][kyer1].x,nokta[i][kyer1].y,nokta[i][kyer1].z);
                    printf("%d. nokta   x: %lf y: %lf z: %lf\n",kyer2,nokta[i][kyer2].x,nokta[i][kyer2].y,nokta[i][kyer2].z);
                    fprintf(frp,"\n%s. DOSYA\n",dosyasay[i]);
                    fprintf(frp,"En uzak nokta degerleri \n%d. nokta     x: %lf y: %lf z: %lf\n",byer1,nokta[i][byer1].x,nokta[i][byer1].y,nokta[i][byer1].z);
                    fprintf(frp,"%d. nokta   x: %lf y: %lf z: %lf\n",byer2,nokta[i][byer2].x,nokta[i][byer2].y,nokta[i][byer2].z);
                    fprintf(frp,"En yakin nokta degerleri \n%d.nokta     x: %lf y: %lf z: %lf \n",kyer1,nokta[i][kyer1].x,nokta[i][kyer1].y,nokta[i][kyer1].z);
                    fprintf(frp,"%d. nokta   x: %lf y: %lf z: %lf\n",kyer2,nokta[i][kyer2].x,nokta[i][kyer2].y,nokta[i][kyer2].z);
                    by1[i]=byer1;
                    by2[i]=byer2;
                 //   ky1[i]=kyer1;
                  //  ky2[i]=kyer2;
                }
            }


        }
        goto scm;
    }
    //scanf("%d",&tercih);
    if(tercih==3)
    {

        for(int i=0; i<dosya_sayi; i++)                 //NOKTALARI KAPSAYAN EN KUCUK KUP
        {
            //kenuz=0;
            if(inf.hatadegeri[i]==1 )
            {
                int b1,b2;
                b1=by1[i];
                b2=by2[i];

                printf("\n%s Noktalari kapsayan en kucuk kup\n",dosyasay[i]);
                fprintf(frp,"\n%s Noktalari kapsayan en kucuk kup\n",dosyasay[i]);
                uzak=fabs(sqrt((pow(nokta[i][b1].x-nokta[i][b2].x,2))+(pow(nokta[i][b1].y-nokta[i][b2].y,2))+(pow(nokta[i][b1].z-nokta[i][b2].z,2))));
                kenuz=(uzak/(sqrt(3)));
                printf("\nKupun kose nokta bilgileri\n");
                fprintf(frp,"\nKupun kose nokta bilgileri\n");

                printf("1.nokta %lf   %lf   %lf  \n",nokta[i][b1].x,nokta[i][b1].y,nokta[i][b1].z);
                printf("2.nokta %lf   %lf   %lf  \n",(nokta[i][b1].x-kenuz),nokta[i][b1].y,nokta[i][b1].z);
                printf("3.nokta %lf   %lf   %lf  \n",nokta[i][b1].x,(nokta[i][b1].y-kenuz),nokta[i][b1].z);
                printf("4.nokta %lf   %lf   %lf  \n",nokta[i][b1].x,nokta[i][b1].y,(nokta[i][b1].z-kenuz));
                printf("5.nokta %lf   %lf   %lf  \n",(nokta[i][b2].x+kenuz),nokta[i][b2].y,nokta[i][b2].z);
                printf("6.nokta %lf   %lf   %lf  \n",nokta[i][b2].x,(nokta[i][b2].y+kenuz),nokta[i][b2].z);
                printf("7.nokta %lf   %lf   %lf  \n",nokta[i][b2].x,nokta[i][b2].y,(nokta[i][b2].z+kenuz));
                printf("8.nokta %lf   %lf   %lf  \n",nokta[i][b2].x,nokta[i][b2].y,nokta[i][b2].z);

                fprintf(frp,"1.nokta %lf   %lf   %lf  \n",nokta[i][b1].x,nokta[i][b1].y,nokta[i][b1].z);
                fprintf(frp,"2.nokta %lf   %lf   %lf  \n",(nokta[i][b1].x-kenuz),nokta[i][b1].y,nokta[i][b1].z);
                fprintf(frp,"3.nokta %lf   %lf   %lf  \n",nokta[i][b1].x,(nokta[i][b1].y-kenuz),nokta[i][b1].z);
                fprintf(frp,"4.nokta %lf   %lf   %lf  \n",nokta[i][b1].x,nokta[i][b1].y,(nokta[i][b1].z-kenuz));
                fprintf(frp,"5.nokta %lf   %lf   %lf  \n",(nokta[i][b2].x+kenuz),nokta[i][b2].y,nokta[i][b2].z);
                fprintf(frp,"6.nokta %lf   %lf   %lf  \n",nokta[i][b2].x,(nokta[i][b2].y+kenuz),nokta[i][b2].z);
                fprintf(frp,"7.nokta %lf   %lf   %lf  \n",nokta[i][b2].x,nokta[i][b2].y,(nokta[i][b2].z+kenuz));
                fprintf(frp,"8.nokta %lf   %lf   %lf  \n",nokta[i][b2].x,nokta[i][b2].y,nokta[i][b2].z);


            }
        }

        goto scm;
    }
    //scanf("%d",&tercih);
    if(tercih==4)
    {
        printf("\nKurenin merkez koordinatlarini ve yaricap degerlerini giriniz\n");
        printf("x degeri = ");
        scanf("%lf",&kurex);
        fprintf(frp,"x değeri=%lf\n",kurex);
        printf("y degeri = ");
        scanf("%lf",&kurey);
        fprintf(frp,"x değeri=%lf\n",kurey);
        printf("z degeri = ");
        scanf("%lf",&kurez);
        fprintf(frp,"x değeri=%lf\n",kurez);
        printf("yaricap degeri = \n");
        scanf("%lf",&ycap);
        fprintf(frp,"yarıçap değeri=%lf\n",ycap);
        for(int i=0; i<dosya_sayi; i++)                 //KURE ICINDEKI DEGERLERI HESAPLAMA ASCII
        {
            if(inf.hatadegeri[i]==1 )
            {
                printf("\n%s DOSYASI KURE ICINDEKI NOKTALAR\n",dosyasay[i]);
                fprintf(frp,"\n%s DOSYASI KURE ICINDEKI NOKTALAR\n",dosyasay[i]);

                max=0;
                for(int m=0; m<inf.noktasayi[i]; m++)
                {
                    max=(fabs(sqrt(pow(kurex-nokta[i][m].x,2)+(pow(kurey-nokta[i][m].y,2))+(pow(kurez-nokta[i][m].z,2)))));
                    if(max<=ycap)
                    {
                        if(inf.alandegeri[i]==0)
                        {
                            printf("%.6lf   %.6lf   %.6lf\n",nokta[i][m].x,nokta[i][m].y,nokta[i][m].z);
                            fprintf(frp,"%.6lf   %.6lf   %.6lf\n",nokta[i][m].x,nokta[i][m].y,nokta[i][m].z);
                            max=0;
                        }
                        else
                        {
                            printf("%.6lf   %.6lf   %.6lf  %d  %d  %d\n",nokta[i][m].x,nokta[i][m].y,nokta[i][m].z,nokta[i][m].r,nokta[i][m].g,nokta[i][m].b);
                            fprintf(frp,"%.6lf   %.6lf   %.6lf  %d  %d  %d\n",nokta[i][m].x,nokta[i][m].y,nokta[i][m].z,nokta[i][m].r,nokta[i][m].g,nokta[i][m].b);
                            max=0;
                        }
                    }
                    max=0;
                }
            }
        }

        goto scm;
    }
    //scanf("%d",&tercih);
    if(tercih==5)
    {
        for(int i=0; i<dosya_sayi; i++)                 //Ortalama uzaklik
        {
            if(inf.hatadegeri[i]==1 )
            {

                toplam=0;
                for(j=0; j<inf.noktasayi[i]; j++)
                {
                    for(int l=j+1; l<inf.noktasayi[i]; l++) //((x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2) 2 nokra arasý uzaklýk
                    {
                        toplam=toplam+(fabs(sqrt((pow(nokta[i][j].x-nokta[i][l].x,2))+(pow(nokta[i][j].y-nokta[i][l].y,2))+(pow(nokta[i][j].z-nokta[i][l].z,2)))/(((inf.noktasayi[i])*(inf.noktasayi[i]-1))/2)));


                    }

                }

                printf("%s \n Ortalama uzaklik:  %lf\n",dosyasay[i],toplam);
                fprintf(frp,"%s \n Ortalama uzaklik:  %lf\n",dosyasay[i],toplam);
            }
        }

        goto scm;
    }

    fclose(frp);
    if(tercih==6)
    {
        return 0;
    }
}
