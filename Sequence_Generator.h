#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct info
{
    int pos,posx;
    char seatx;
    int seaty;
    int luggage;
    int speed;
    char ent;
    // ent='F' means Front
    // end='B' means Back 
};

void kakshuffle(int *array, int n)
{
    if (n > 1)
    {
        for (int i = 1; i < n; i++)
        {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            int tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
        }
    }
}

void shuffle(info *array, int n)
{
    if (n > 1)
    {
        for (int i = 1; i < n; i++)
        {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            info tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
        }
    }
}

void shuffle_s(info *array, int m, int n)
{
    if (n > 1)
    {
        for (int i = m; i < n; i++)
        {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            info tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
        }
    }
}

void information(info person[],int npassenger,int seatx)
{
    srand(time(NULL));
    for(int i=1;i<=npassenger;i++)
    {
        person[i].seaty = floor(i/seatx)+1;
        person[npassenger].seaty = i/seatx;
        if ((i%seatx)==1)
            person[i].seatx = 'A';
        else if ((i%seatx)==2)
            person[i].seatx = 'B';
        else if ((i%seatx)==3)
            person[i].seatx = 'C';
        else if ((i%seatx)==4)
            person[i].seatx = 'D';
        else if ((i%seatx)==5)
            person[i].seatx = 'E';
        else if ((i%seatx)==0)
            person[i].seatx = 'F';
        int r = rand()%10+1;
        if(r<8)
            person[i].speed = 1;
        else
            person[i].speed = 2;
    }
    int ii,jj,kk;
    for(kk=1;kk<=npassenger;kk++)
    {
        int num[npassenger];
        for(ii=0;ii<npassenger;ii++)
        num[ii] = ii+1;
        kakshuffle(num,npassenger);
        for(jj=0;jj<npassenger;jj++)
        {
            if(jj<(20*npassenger/100)) person[num[jj]].luggage = 2;
            else if((20*npassenger/100)<=jj&&jj<(70*npassenger/100)) person[num[jj]].luggage = 1;
            else person[num[jj]].luggage = 0;
        }
    }

}

void random(info person[],int npassenger,int seatx,int x)
{
    srand(x);
    for(int i=1;i<=npassenger;i++)
    {
        person[i].seaty = floor(i/seatx)+1;
        person[npassenger].seaty = i/seatx;
        if ((i%seatx)==1)
            person[i].seatx = 'A';
        else if ((i%seatx)==2)
            person[i].seatx = 'B';
        else if ((i%seatx)==3)
            person[i].seatx = 'C';
        else if ((i%seatx)==4)
            person[i].seatx = 'D';
        else if ((i%seatx)==5)
            person[i].seatx = 'E';
        else if ((i%seatx)==0)
            person[i].seatx = 'F';
        int r = rand()%10+1;
        if(r<8)
            person[i].speed = 1;
        else
            person[i].speed = 2;
    }
    /*int ii,jj,kk;
    for(kk=1;kk<=npassenger;kk++)
    {
        int num[npassenger];
        for(ii=0;ii<npassenger;ii++)
        num[ii] = ii+1;
        kakshuffle(num,npassenger);
        for(jj=0;jj<npassenger;jj++)
        {
            if(jj<(60*npassenger/100)) person[num[jj]].luggage = 2;
            else if((60*npassenger/100)<=jj&&jj<(90*npassenger/100)) person[num[jj]].luggage = 1;
            else person[num[jj]].luggage = 0;
        }
    }*/

    shuffle(person,npassenger);
}


void section(info person[],int npassenger,int seatx, int round, int bad, int x, int y)
{
    bad = bad/2;
    srand(time(NULL));
    int h = npassenger/(6*round);
    int g = 6*h;
    int sec[npassenger+5];
    for(int i=1;i<=npassenger;i++)
    {
        if (y==1)
        {
            if(i<=g) person[i].seaty = floor((i-1)/seatx)+1;
            else if((i>g)&&(i<=(2*g))) person[i].seaty = h+floor((i-g-1)/seatx)+1;
            else if(i>(2*g)) person[i].seaty = 2*h+floor((i-2*g-1)/seatx)+1;
        }
        else if (y==2)
        {
            if(i<=g) person[i].seaty = floor((i-1)/seatx)+1;
            else if((i>g)&&(i<=(2*g))) person[i].seaty = 2*h+floor((i-g-1)/seatx)+1;
            else if(i>(2*g)) person[i].seaty = h+floor((i-2*g-1)/seatx)+1;
        }
        else if (y==3)
        {
            if(i<=g) person[i].seaty = h+floor((i-1)/seatx)+1;
            else if(i>g&&i<=2*g) person[i].seaty = floor((i-g-1)/seatx)+1;
            else if(i>2*g) person[i].seaty = 2*h+floor((i-2*g-1)/seatx)+1;
        }
        else if (y==4)
        {
            if(i<=g) person[i].seaty = h+floor((i-1)/seatx)+1;
            else if(i>g&&i<=2*g) person[i].seaty = 2*h+floor((i-g-1)/seatx)+1;
            else if(i>2*g) person[i].seaty = floor((i-2*g-1)/seatx)+1;
        }
        else if (y==5)
        {
            if(i<=g) person[i].seaty = 2*h+floor((i-1)/seatx)+1;
            else if(i>g&&i<=2*g) person[i].seaty = floor((i-g-1)/seatx)+1;
            else if(i>2*g) person[i].seaty = h+floor((i-2*g-1)/seatx)+1;
        }
        else if (y==6)
        {
            if(i<=g) person[i].seaty = 2*h+floor((i-1)/seatx)+1;
            else if(i>h&&i<=2*g) person[i].seaty = h+floor((i-g-1)/seatx)+1;
            else if(i>2*g) person[i].seaty = floor((i-2*g-1)/seatx)+1;
        }

        if(i<=g) sec[i]=1;
        else if(i>h&&i<=2*g) sec[i]=2;
        else if(i>2*g) sec[i]=3;

        if ((i%seatx)==1)
            person[i].seatx = 'A';
        else if ((i%seatx)==2)
            person[i].seatx = 'B';
        else if ((i%seatx)==3)
            person[i].seatx = 'C';
        else if ((i%seatx)==4)
            person[i].seatx = 'D';
        else if ((i%seatx)==5)
            person[i].seatx = 'E';
        else if ((i%seatx)==0)
            person[i].seatx = 'F';

        person[i].luggage = 0;
        /*int num[npassenger];
        for(i=0;i<npassenger;i++)
        num[i] = i+1;
        kakshuffle(num,npassenger);
        for(i=0;i<npassenger;i++)
        {
            if(i<(20*npassenger/100)) person[num[i]].luggage = 2;
            else if((20*npassenger/100)<=i&&i<(70*npassenger/100)) person[num[i]].luggage = 1;
            else person[num[i]].luggage = 0;
        }*/

        int r = rand()%10+1;
        if(r<8)
            person[i].speed = 1;
        else
            person[i].speed = 2;
    }

    /*for(int j=1;j<=npassenger;j++)
        printf("%d ", person[j].seaty);
    printf("\n");*/
    int m = 1;
    int n = npassenger/round;
    while(m < npassenger)
    {
        shuffle_s(person,m,n);
        m = n+1;
        n = n+npassenger/round;
    }
    /*for(int i=1;i<=npassenger;i++)
        printf("%d ",person[i].seaty);
    printf("\n");*/

    info arr;
    int a;
    int b;
    bool already[npassenger+5]={};
    int i = 0;
    while(i<bad*npassenger/100)
    {
        a=0;
        b=0;
        while(already[a]== true||a==0)
        a = (rand() % (npassenger - 1 + 1)) + 1;
        //printf("%d",a);
        while(sec[b]==sec[a]||b==0||already[b]== true)
        {
            b = (rand() % (npassenger - 1 + 1)) + 1;
            //printf("%d",b);
        }
            arr = person[a];
            person[a] = person[b];
            person[b] = arr;
            already[a] = true;
            already[b] = true;
            //printf("%d ",a);
            //printf("%d\n",b);
            i++;
    }
    /*for(int i=1;i<=npassenger;i++)
        printf("%d ",person[i].seaty);
    printf("\n");*/
}


void seat(info person[],int npassenger,int seatx, int bad,int x)
{
    bad = bad/2;
    srand(x);
    int n=npassenger/6;
    for(int i=1;i<=npassenger;i++)
    {
        if (5*n<i&&i<=npassenger){
            person[i].seatx = 'C';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
        }
        else if (4*n<i&&i<=5*n){
            person[i].seatx = 'D';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
        }
        else if (3*n<i&&i<=4*n){
            person[i].seatx = 'B';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
        }
        else if (2*n<i&&i<=3*n){
            person[i].seatx = 'E';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
        }
        else if (1*n<i&&i<=2*n){
            person[i].seatx = 'A';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
        }
        else if (0<i&&i<=1*n){
            person[i].seatx = 'F';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
        }
        person[i].luggage = 0;
        /*int num[npassenger];
        for(i=0;i<npassenger;i++)
        num[i] = i+1;
        kakshuffle(num,npassenger);
        for(i=0;i<npassenger;i++)
        {
            if(i<(20*npassenger/100)) person[num[i]].luggage = 2;
            else if((20*npassenger/100)<=i&&i<(70*npassenger/100)) person[num[i]].luggage = 1;
            else person[num[i]].luggage = 0;
        }*/
        int r = rand()%10+1;
        if(r<8)
            person[i].speed = 1;
        else
            person[i].speed = 2;
    }
    int m = 1;
    int c = 2*npassenger/seatx;
    while(m < npassenger)
    {
        shuffle_s(person,m,c);
        m = c+1;
        c = c+2*npassenger/seatx;
    }
    /*for(int i=1;i<=npassenger;i++)
        printf("%c ",person[i].seatx);
    printf("\n");*/
    info arr;
    int a;
    int b;
    bool already[npassenger+5]={};
    int i = 0;
    while(i<bad*npassenger/100)
    {
        a=0;
        b=0;
        while(already[a]== true||a==0)
        a = (rand() % (npassenger - 1 + 1)) + 1;
        //printf("%d",a);
        while(person[b].seatx==person[a].seatx||b==0||already[b]==true)
        {
            b = (rand() % (npassenger - 1 + 1)) + 1;
            //printf("%d",b);
        }
            arr = person[a];
            person[a] = person[b];
            person[b] = arr;
            already[a] = true;
            already[b] = true;
            i++;
    }
    /*for(int i=1;i<=npassenger;i++)
        printf("%c ",person[i].seatx);
    printf("\n");*/
}


void test_case1(info person[],int npassenger,int seatx,int seaty){
    int cnt=1,cntseat=0;
    bool already[10][40]={};
    while(cntseat<13){
        for(int i=seaty;i>0;i-=2){
            if(cntseat==0 or cntseat==2){
                if(already[1][i]) i--;
                person[cnt].seatx='A';
                already[1][i]=true;
                person[cnt].luggage=2;
            }
            else if(cntseat==1 or cntseat==3){
                if(already[7][i]) i--;
                person[cnt].seatx='F';
                already[7][i]=true;
                person[cnt].luggage=2;
            }
            else if(cntseat==4 or cntseat==6){
                if(already[2][i]) i--;
                person[cnt].seatx='B';
                already[2][i]=true;
                person[cnt].luggage=1;
            }
            else if(cntseat==5 or cntseat==7){
                if(already[6][i]) i--;
                person[cnt].seatx='E';
                already[6][i]=true;
                person[cnt].luggage=1;
            }
            else if(cntseat==8 or cntseat==10){
                if(already[3][i]) i--;
                person[cnt].seatx='C';
                already[3][i]=true;
            }
            else{
                if(already[5][i]) i--;
                person[cnt].seatx='D';
                already[5][i]=true;
            }
            person[cnt].speed=1;
            person[cnt++].seaty=i;
        }
        cntseat++;
    }
}

void doubleaisle(info person[],int npassenger,int seatx,int seaty,int bad,int x)
{
    bad = bad/2;
    srand(x);
    int n=npassenger/7;
    for(int i=1;i<=npassenger;i++)
    {
        if (6*n<i&&i<=npassenger){
            person[i].seatx = 'E';
            person[i].seaty = (i-1)%(npassenger/seatx)+2;
        }
        else if (5*n<i&&i<=6*n){
            person[i].seatx = 'D';
            person[i].seaty = (i-1)%(npassenger/seatx)+2;
        }
        else if (4*n<i&&i<=5*n){
            person[i].seatx = 'C';
            person[i].seaty = (i-1)%(npassenger/seatx)+2;
        }
        else if (3*n<i&&i<=4*n){
            person[i].seatx = 'F';
            person[i].seaty = (i-1)%(npassenger/seatx)+2;
        }
        else if (2*n<i&&i<=3*n){
            person[i].seatx = 'B';
            person[i].seaty = (i-1)%(npassenger/seatx)+2;
        }
        else if (1*n<i&&i<=2*n){
            person[i].seatx = 'G';
            person[i].seaty = (i-1)%(npassenger/seatx)+2;
        }
        else if (0<i&&i<=1*n){
            person[i].seatx = 'A';
            person[i].seaty = (i-1)%(npassenger/seatx)+2;
        }
        /*int num[npassenger];
        for(i=0;i<npassenger;i++)
        num[i] = i+1;
        kakshuffle(num,npassenger);
        for(i=0;i<npassenger;i++)
        {
            if(i<(20*npassenger/100)) person[num[i]].luggage = 2;
            else if((20*npassenger/100)<=i&&i<(70*npassenger/100)) person[num[i]].luggage = 1;
            else person[num[i]].luggage = 0;
        }*/
        int r = rand()%10+1;
        if(r<8)
            person[i].speed = 1;
        else
            person[i].speed = 2;
        if(person[i].seaty<=seaty/2+1) 
            person[i].ent = 'F',person[i].posx=1;
        else 
            person[i].ent = 'B',person[i].posx=seaty+2;
    }
    /*for(int i=1;i<=npassenger;i++)
            printf("%c ",person[i].seatx);
            printf("\n");*/
    int m = 1;
    int c = 2*npassenger/seatx;
    while(m+npassenger/seatx < npassenger)
    {
        shuffle_s(person,m,c);
        shuffle_s(person,m,c-npassenger/seatx);  
        m = c+1;
        c = c+2*npassenger/seatx;
    }
    shuffle_s(person,m,c-npassenger/seatx);
    info arr;
    int a;
    int b;
    bool already[npassenger+5]={};
    int i = 0;
    while(i<bad*npassenger/100)
    {
        a=0;
        b=0;
        while(already[a]== true||a==0)
        a = (rand() % (npassenger - 1 + 1)) + 1;
        //printf("%d ",a);
        while(person[b].seatx==person[a].seatx||b==0||already[b]== true)
        {
            b = (rand() % (npassenger - 1 + 1)) + 1;
            //printf("%d",b);
        }
        //printf("%d\n",b);
            arr = person[a];
            person[a] = person[b];
            person[b] = arr;
            already[a] = true;
            already[b] = true;
            i++;
    }
}

void repyramid(info person[],int bad,int x)
{
    int npassenger = 198;
    int seatx = 6;
    bad = bad/2;
    srand(x);
    int a=38,b=42,c=38,d=44,e=36,i=1;
    int j=0;
    int k=0;
    int sec[npassenger+5];
    while(i<=a)
    {
        person[i].seaty = j+15;
        person[i].seatx = 'A';
        person[i+1].seaty = j+15;
        person[i+1].seatx = 'F';
        i=i+2;
        j++;
        sec[i]=1;
    }
    j=0;
    k=0;
    //printf("%d",i);
    while(i<=a+b)
    {
        if(i-(a+1)<14)
        {
            person[i].seaty = j+8;
            person[i].seatx = 'A';
            person[i+1].seaty = j+8;
            person[i+1].seatx = 'F';
            i=i+2;
            j++;
        }
        else
        {
            person[i].seaty = k+20;
            person[i].seatx = 'B';
            person[i+1].seaty = k+20;
            person[i+1].seatx = 'E';
            i=i+2;
            k++;
        }
        sec[i]=2;
    }
    j=0;
    k=0;
    //printf("%d",i);
    while(i<=a+b+c)
    {
        if(i-(a+b+1)<14)
        {
            person[i].seaty = j+1;
            person[i].seatx = 'A';
            person[i+1].seaty = j+1;
            person[i+1].seatx = 'F';
            i=i+2;
            j++;
        }
        else
        {
            person[i].seaty = k+8;
            person[i].seatx = 'B';
            person[i+1].seaty = k+8;
            person[i+1].seatx = 'E';
            i=i+2;
            k++;
        }
        sec[i]=3;
    }
    j=0;
    k=0;
    //printf("%d",i);
    while(i<=a+b+c+d)
    {
        if(i-(a+b+c+1)<14)
        {
            person[i].seaty = j+1;
            person[i].seatx = 'B';
            person[i+1].seaty = j+1;
            person[i+1].seatx = 'E';
            i=i+2;
            j++;
        }
        else
        {
            person[i].seaty = k+19;
            person[i].seatx = 'C';
            person[i+1].seaty = k+19;
            person[i+1].seatx = 'D';
            i=i+2;
            k++;
        }
        sec[i]=4;
    }
    j=0;
    k=0;
    //printf("%d",i);
    while(i<=a+b+c+d+e)
    {
        person[i].seaty = j+1;
        person[i].seatx = 'C';
        person[i+1].seaty = j+1;
        person[i+1].seatx = 'D';
        i=i+2;
        j++;
        sec[i]=5;
    }
    /*for(i=1;i<=npassenger;i++)
    {
        printf("%d",person[i].seaty);
        printf("%c ",person[i].seatx);
    }
    printf("\n");*/
    shuffle_s(person,1,a);
    shuffle_s(person,a+1,a+b);
    shuffle_s(person,a+b+1,a+b+c);
    shuffle_s(person,a+b+c+1,a+b+c+d);
    shuffle_s(person,a+b+c+d+1,a+b+c+d+e);
    /*for(i=1;i<=npassenger;i++)
    {
        printf("%d",person[i].seaty);
        printf("%c ",person[i].seatx);
    }
    printf("\n");*/
    /*int num[npassenger];
        for(i=0;i<npassenger;i++)
        num[i] = i+1;
        kakshuffle(num,npassenger);
        for(i=0;i<npassenger;i++)
        {
            if(i<(20*npassenger/100)) person[num[i]].luggage = 2;
            else if((20*npassenger/100)<=i&&i<(70*npassenger/100)) person[num[i]].luggage = 1;
            else person[num[i]].luggage = 0;
        }*/
    for(i=1;i<=npassenger;i++)
    {
        int r = rand()%10+1;
        if(r<8)
            person[i].speed = 1;
        else
            person[i].speed = 2;
    }

    info arr;
    int o;
    int p;
    bool already[npassenger+5]={};
    i = 0;
    while(i<bad*npassenger/100)
    {
        o=0;
        p=0;
        while(already[o]== true||o==0)
        o = (rand() % (npassenger - 1 + 1)) + 1;
        //printf("%d ",o);
        //printf("%d",a);
        while(sec[p]==sec[o]||p==0||already[p]== true)
        {
            p = (rand() % (npassenger - 1 + 1)) + 1;
            //printf("%d",b);
        }
        //printf("%d\n",p);
            arr = person[o];
            person[o] = person[p];
            person[p] = arr;
            already[o] = true;
            already[p] = true;
            i++;
    }
    /*for(i=1;i<=npassenger;i++)
    {
        printf("%d",person[i].seaty);
        printf("%c ",person[i].seatx);
    }
    printf("\n");*/
}

void seatsection(info person[],int npassenger,int seatx, int bad, int x)
{
    bad = bad/2;
    srand(x);
    int round = 3;
    int n = npassenger/3;
    int p = npassenger/6;
    int m = n/6;
    int sec[npassenger];
    int i=0,j=0;
    while(j<3)
    {
        for(i=1;i<=n;i++)
        {
            if (5*m<i&&i<=n){
                person[j*n+i].seatx = 'C';
                person[j*n+i].seaty = p-(j*m+((i-1)%m));
                sec[j*n+i] = 3+3*j;
            }
            else if (4*m<i&&i<=5*m){
                person[j*n+i].seatx = 'D';
                person[j*n+i].seaty = p-(j*m+((i-1)%m));
                sec[j*n+i] = 3+3*j;
            }
            else if (3*m<i&&i<=4*m){
                person[j*n+i].seatx = 'B';
                person[j*n+i].seaty = p-(j*m+((i-1)%m));
                sec[j*n+i] = 2+3*j;
            }
            else if (2*m<i&&i<=3*m){
                person[j*n+i].seatx = 'E';
                person[j*n+i].seaty = p-(j*m+((i-1)%m));
                sec[j*n+i] = 2+3*j;
            }
            else if (1*m<i&&i<=2*m){
                person[j*n+i].seatx = 'A';
                person[j*n+i].seaty = p-(j*m+((i-1)%m));
                sec[j*n+i] = 1+3*j;
            }
            else if (0<i&&i<=1*m){
                person[j*n+i].seatx = 'F';
                person[j*n+i].seaty = p-(j*m+((i-1)%m));
                sec[j*n+i] = 1+3*j;
            }
        }
        j++;
    }

    /*for(i=1;i<=npassenger;i++)
    {
        printf("%d",person[i].seaty);
        printf("%c ",person[i].seatx);
    }printf("\n");*/

    int g = 1;
    int c = 2*m;

    while(g < npassenger)
    {
        shuffle_s(person,g,c);
        g = c+1;
        c = c+2*m;
    }

    /*for(i=1;i<=npassenger;i++)
    {
        printf("%d",person[i].seaty);
        printf("%c ",person[i].seatx);
    }printf("\n");*/

    /*int ii,jj,kk;
    for(kk=1;kk<=npassenger;kk++)
    {
        int num[npassenger];
        for(ii=0;ii<npassenger;ii++)
        num[ii] = ii+1;
        kakshuffle(num,npassenger);
        for(jj=0;jj<npassenger;jj++)
        {
            if(jj<(20*npassenger/100)) person[num[jj]].luggage = 2;
            else if((20*npassenger/100)<=jj&&jj<(70*npassenger/100)) person[num[jj]].luggage = 1;
            else person[num[jj]].luggage = 0;
        }
    }*/
    for(i=1;i<=npassenger;i++)
    {
        int r = rand()%10+1;
            if(r<8)
                person[i].speed = 1;
            else
                person[i].speed = 2;
    }
    info arr;
    int o;
    int q;
    bool already[npassenger+5]={};
    i = 0;
    while(i<bad*npassenger/100)
    {
        o=0;
        q=0;
        int h = 0;
        while(already[o]== true||o==0)
        o = (rand() % (npassenger - 1 + 1)) + 1;
        //printf("%d ",o);
        //printf("%d",a);
        while(sec[q]==sec[o]||q==0||already[q]== true)
        {
            q = (rand() % (npassenger - 1 + 1)) + 1;
            h++;
            if(h>500) break;
            //printf("%d",b);
        }
        //printf("%d\n",p);
        if(h<10)
        {
            arr = person[o];
            person[o] = person[q];
            person[q] = arr;
            already[o] = true;
            already[q] = true;
            i++;
        }
        else i++;
    }
}
