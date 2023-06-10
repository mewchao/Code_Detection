#include<stdio.h>
int runnian (int a);
int is (int y,int m,int d);
int t (int y,int m,int d);
int main(){
    int Y,M,D,y,m,d;
    int s1=0,s2=0;
    scanf("%d %d %d",&y,&m,&d);
    scanf("%d %d %d",&Y,&M,&D);
    if (!is(y,m,d)||!is(Y,M,D))
        printf("error");
    else {
        s1=t(y,m,d);
        s2=t(Y,M,D);
        printf("%d\n",s2-s1);
    }
    return 0;
}
int t (int y,int m,int d){
    int s=0;
    for (int i=1;i<y;i++){
        if (runnian(i)) s+=366;
        else            s+=365;
    }
    for (int i=1;i<m;i++){
        if (i==1||i==3||i==5||i==7||i==8||i==10||i==12)      s+=31;
        else if (i==4||i==6||i==9||i==11)                    s+=30;
        else if (i==2&&runnian(y))                           s+=29;
        else if (i==2&&!runnian(y))                          s+=28;
    }
    s+=d-1;
    return s;
}
int runnian (int a){
    return a%(a%100?4:400)?0:1;
}
int is (int y,int m,int d){
    int k=1;
    if   (m<1||m>12)   k=0;
    else if (y<1||y>2100) k=0;
    else if (m==1||m==3||m==5||m==7||m==8||m==10||m==12){
        if(d<1||d>31) k=0;
    }
    else if (m==4||m==6||m==9||m==11){
        if (d<1||d>30) k=0;
    }
    else if (runnian(y)){
        if (m==2&&(d<1||d>29)) k=0;
    }
    else if (m==2&&(d<1||d>28)) k=0;

    return k;
}
