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
        person[i].luggage = 0;
        int r = rand()%10+1;
        if(r<8)
            person[i].speed = 1;
        else
            person[i].speed = 2;
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
        person[i].luggage = 0;
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
        int Prob0=60,Prob1=31,Prob2=8,Prob3=1,Prob4=0;
        for(jj=0;jj<npassenger;jj++)
        {
            if(jj<(Prob0*npassenger/100)) person[num[jj]].luggage = 0;
            else if((Prob0*npassenger/100)<=jj&&jj<((Prob0+Prob1)*npassenger/100)) person[num[jj]].luggage = 1;
            else if(((Prob0+Prob1)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2)*npassenger/100))) person[num[jj]].luggage = 2;
            else if(((Prob0+Prob1+Prob2)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3)*npassenger/100))) person[num[jj]].luggage = 3;
            else if(((Prob0+Prob1+Prob2+Prob3)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3+Prob4)*npassenger/100))) person[num[jj]].luggage = 4;
            else person[num[jj]].luggage = 5;
        }
    }
    shuffle(person,npassenger);
}


void section(info person[],int npassenger,int seatx, int bad, int x, int y)
{
    int round=3;
    bad = bad/2;
    srand(x);
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
        int Prob0=22,Prob1=33,Prob2=25,Prob3=13,Prob4=5;
        for(jj=0;jj<npassenger;jj++)
        {
            if(jj<(Prob0*npassenger/100)) person[num[jj]].luggage = 0;
            else if((Prob0*npassenger/100)<=jj&&jj<((Prob0+Prob1)*npassenger/100)) person[num[jj]].luggage = 1;
            else if(((Prob0+Prob1)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2)*npassenger/100))) person[num[jj]].luggage = 2;
            else if(((Prob0+Prob1+Prob2)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3)*npassenger/100))) person[num[jj]].luggage = 3;
            else if(((Prob0+Prob1+Prob2+Prob3)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3+Prob4)*npassenger/100))) person[num[jj]].luggage = 4;
            else person[num[jj]].luggage = 5;
        }
    }
    int m = 1;
    int n = npassenger/round;
    while(m < npassenger)
    {
        shuffle_s(person,m,n);
        m = n+1;
        n = n+npassenger/round;
    }
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
        while(sec[b]==sec[a]||b==0||already[b]== true)
            b = (rand() % (npassenger - 1 + 1)) + 1;
        arr = person[a];
        person[a] = person[b];
        person[b] = arr;
        already[a] = true;
        already[b] = true;
        i++;
    }
}

void seat(info person[],int npassenger,int seatx, int bad,int x)
{
    bad = bad/2;
    srand(x);
    int n=npassenger/6;
    int sec[npassenger+5];
    for(int i=1;i<=npassenger;i++)
    {
        if (5*n<i&&i<=npassenger){
            person[i].seatx = 'C';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
            sec[i] = 1;
        }
        else if (4*n<i&&i<=5*n){
            person[i].seatx = 'D';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
            sec[i] = 1;
        }
        else if (3*n<i&&i<=4*n){
            person[i].seatx = 'B';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
            sec[i] = 2;
        }
        else if (2*n<i&&i<=3*n){
            person[i].seatx = 'E';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
            sec[i] = 2;
        }
        else if (1*n<i&&i<=2*n){
            person[i].seatx = 'A';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
            sec[i] = 3;
        }
        else if (0<i&&i<=1*n){
            person[i].seatx = 'F';
            person[i].seaty = (i-1)%(npassenger/seatx)+1;
            sec[i] = 3;
        }

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
    int ii,jj,kk;
    for(kk=1;kk<=npassenger;kk++)
    {
        int num[npassenger];
        for(ii=0;ii<npassenger;ii++)
        num[ii] = ii+1;
        kakshuffle(num,npassenger);
        int Prob0=22,Prob1=33,Prob2=25,Prob3=13,Prob4=5;
        for(jj=0;jj<npassenger;jj++)
        {
            if(jj<(Prob0*npassenger/100)) person[num[jj]].luggage = 0;
            else if((Prob0*npassenger/100)<=jj&&jj<((Prob0+Prob1)*npassenger/100)) person[num[jj]].luggage = 1;
            else if(((Prob0+Prob1)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2)*npassenger/100))) person[num[jj]].luggage = 2;
            else if(((Prob0+Prob1+Prob2)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3)*npassenger/100))) person[num[jj]].luggage = 3;
            else if(((Prob0+Prob1+Prob2+Prob3)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3+Prob4)*npassenger/100))) person[num[jj]].luggage = 4;
            else person[num[jj]].luggage = 5;
        }
    }
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
        while(sec[b]==sec[a]||b==0||already[b]== true)
            b = (rand() % (npassenger - 1 + 1)) + 1;
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
    shuffle_s(person,1,a);
    shuffle_s(person,a+1,a+b);
    shuffle_s(person,a+b+1,a+b+c);
    shuffle_s(person,a+b+c+1,a+b+c+d);
    shuffle_s(person,a+b+c+d+1,a+b+c+d+e);
    for(i=1;i<=npassenger;i++)
    {
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
        int Prob0=22,Prob1=33,Prob2=25,Prob3=13,Prob4=5;
        for(jj=0;jj<npassenger;jj++)
        {
            if(jj<(Prob0*npassenger/100)) person[num[jj]].luggage = 0;
            else if((Prob0*npassenger/100)<=jj&&jj<((Prob0+Prob1)*npassenger/100)) person[num[jj]].luggage = 1;
            else if(((Prob0+Prob1)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2)*npassenger/100))) person[num[jj]].luggage = 2;
            else if(((Prob0+Prob1+Prob2)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3)*npassenger/100))) person[num[jj]].luggage = 3;
            else if(((Prob0+Prob1+Prob2+Prob3)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3+Prob4)*npassenger/100))) person[num[jj]].luggage = 4;
            else person[num[jj]].luggage = 5;
        }
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
        while(sec[p]==sec[o]||p==0||already[p]== true)
            p = (rand() % (npassenger - 1 + 1)) + 1;
        arr = person[o];
        person[o] = person[p];
        person[p] = arr;
        already[o] = true;
        already[p] = true;
        i++;
    }    
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
    int g = 1;
    int c = 2*m;
    while(g < npassenger)
    {
        shuffle_s(person,g,c);
        g = c+1;
        c = c+2*m;
    }
    int ii,jj,kk;
    for(kk=1;kk<=npassenger;kk++)
    {
        int num[npassenger];
        for(ii=0;ii<npassenger;ii++)
        num[ii] = ii+1;
        kakshuffle(num,npassenger);
        int Prob0=22,Prob1=33,Prob2=25,Prob3=13,Prob4=5;
        for(jj=0;jj<npassenger;jj++)
        {
            if(jj<(Prob0*npassenger/100)) person[num[jj]].luggage = 0;
            else if((Prob0*npassenger/100)<=jj&&jj<((Prob0+Prob1)*npassenger/100)) person[num[jj]].luggage = 1;
            else if(((Prob0+Prob1)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2)*npassenger/100))) person[num[jj]].luggage = 2;
            else if(((Prob0+Prob1+Prob2)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3)*npassenger/100))) person[num[jj]].luggage = 3;
            else if(((Prob0+Prob1+Prob2+Prob3)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3+Prob4)*npassenger/100))) person[num[jj]].luggage = 4;
            else person[num[jj]].luggage = 5;
        }
    }
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
        while(sec[q]==sec[o]||q==0||already[q]== true)
        {
            q = (rand() % (npassenger - 1 + 1)) + 1;
            h++;
            if(h>10) break;
        }
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
    int ii,jj,kk;
    for(kk=1;kk<=npassenger;kk++)
    {
        int num[npassenger];
        for(ii=0;ii<npassenger;ii++)
        num[ii] = ii+1;
        kakshuffle(num,npassenger);
        int Prob0=60,Prob1=31,Prob2=8,Prob3=1,Prob4=0,Prob5=0;
        for(jj=0;jj<npassenger;jj++)
        {
            if(jj<(Prob0*npassenger/100)) person[num[jj]].luggage = 0;
            else if((Prob0*npassenger/100)<=jj&&jj<((Prob0+Prob1)*npassenger/100)) person[num[jj]].luggage = 1;
            else if(((Prob0+Prob1)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2)*npassenger/100))) person[num[jj]].luggage = 2;
            else if(((Prob0+Prob1+Prob2)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3)*npassenger/100))) person[num[jj]].luggage = 3;
            else if(((Prob0+Prob1+Prob2+Prob3)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3+Prob4)*npassenger/100))) person[num[jj]].luggage = 4;
             else if(((Prob0+Prob1+Prob2+Prob3+Prob4)*npassenger/100)<=jj&&jj<(((Prob0+Prob1+Prob2+Prob3+Prob4+Prob5)*npassenger/100))) person[num[jj]].luggage = 5;
            else person[num[jj]].luggage = 6;
        }
    }
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
        while(person[b].seatx==person[a].seatx||b==0||already[b]== true)
            b = (rand() % (npassenger - 1 + 1)) + 1;
        arr = person[a];
        person[a] = person[b];
        person[b] = arr;
        already[a] = true;
        already[b] = true;
        i++;
    }
}

void flying_wing(info person[],int bad,int x)
{
    bad=bad/2;
    srand(x);
    int i=1,j,sec[320],npassenger=318;
    j=0;
    while(j<25)
    {
        if(j/11==0) person[i].seatx='X';
        else person[i].seatx='S';
        sec[i]=1;
        j++;
        i++;
    }
    j=0;
    while(j<25)
    {
        if(j/11==0) person[i].seatx='W';
        else person[i].seatx='T';
        sec[i]=2;
        j++;
        i++;
    }
    j=0;
    while(j<25)
    {
        if(j/11==0) person[i].seatx='V';
        else person[i].seatx='U';
        sec[i]=3;
        j++;
        i++;
    }
    j=0;
    while(j<28)
    {
        if(j/14==0) person[i].seatx='R';
        else person[i].seatx='M';
        sec[i]=4;
        j++;
        i++;
    }
    j=0;
    while(j<28)
    {
        if(j/14==0) person[i].seatx='Q';
        else person[i].seatx='N';
        sec[i]=5;
        j++;
        i++;
    }
    j=0;
    while(j<28)
    {
        if(j/14==0) person[i].seatx='P';
        else person[i].seatx='O';
        sec[i]=6;
        j++;
        i++;
    }
    j=0;
    while(j<28)
    {
        if(j/14==0) person[i].seatx='L';
        else person[i].seatx='G';
        sec[i]=7;
        j++;
        i++;
    }
    j=0;
    while(j<28)
    {
        if(j/14==0) person[i].seatx='K';
        else person[i].seatx='H';
        sec[i]=8;
        j++;
        i++;
    }
    j=0;
    while(j<28)
    {
        if(j/14==0) person[i].seatx='J';
        else person[i].seatx='I';
        sec[i]=9;
        j++;
        i++;
    }
    j=0;
    while(j<25)
    {
        if(j/14==0) person[i].seatx='F';
        else person[i].seatx='A';
        sec[i]=10;
        j++;
        i++;
    }
    j=0;
    while(j<25)
    {
        if(j/14==0) person[i].seatx='E';
        else person[i].seatx='B';
        sec[i]=11;
        j++;
        i++;
    }
    j=0;
    while(j<25)
    {
        if(j/14==0) person[i].seatx='D';
        else
        {
            person[i].seatx='C';
        }
        sec[i]=12;
        j++;
        i++;
    }
    int k=0;
    i=1;
    for(k=1;k<=6;k++)
    {
        j=0;
        while(j<25)
        {
            if(j/11==0) person[i].seaty=j%11+1;
            else person[i].seaty=(j-11)%14+1;
            j++;
            i++;
        }
        k++;
    }
    k=0;
    for(k=1;k<=12;k++)
    {
        j=0;
        while(j<28)
        {
            if(j/14==0) person[i].seaty=j%14+1;
            else person[i].seaty=(j-14)%14+1;
            j++;
            i++;
        }
        k++;
    }
    k=0;
    for(k=1;k<=6;k++)
    {
        j=0;
        while(j<25)
        {
            if(j/14==0) person[i].seaty=j%14+1;
            else person[i].seaty=(j-14)%11+1;
            j++;
            i++;
        }
        k++;
    }
    int m = 1;
    int c = 25;
    while(m < 75)
    {
        shuffle_s(person,m,c);
        m = c+1;
        c = c+25;
    }
    c=c+3;
    while(m < 243)
    {
        shuffle_s(person,m,c);
        m = c+1;
        c = c+28;
    }
    c=c-3;
    while(m < 318)
    {
        shuffle_s(person,m,c);
        m = c+1;
        c = c+25;
    }
    for(i=0;i<=npassenger;i++)
    {
    int r = rand()%10+1;
    if(r<8)
        person[i].speed = 1;
    else
        person[i].speed = 2;
    }
    info arr;
    int a;
    int b;
    bool already[npassenger+5]={};
    i = 0;
    while(i<bad)
    {
        a = (rand() % (npassenger - 1 + 1)) + 1;
        b = (rand() % (npassenger - 1 + 1)) + 1;
        arr = person[a];
        person[a] = person[b];
        person[b] = arr;
        i++;
    }
}