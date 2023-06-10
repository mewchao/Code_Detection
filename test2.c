#include<stdio.h>
int isprime (int a);
int main(){
    int cnt=0;
    int i,j;
    for (i=1001;i<10000;i++){
        if (isprime(i/1000)&&isprime(i/100)&&isprime(i/10)&&isprime(i)){
            cnt++;
        }
    }
    printf("%d",cnt);
    return 0;
}
int isprime (int a){
    int i;
    if (a<2)  return 0;
    if(a==2)  return 1;
    else if(a%2==0) return 0;
    for (i=3;i*i<=a;i+=2){
        if (a%i==0)     return 0;
    }
    return 1;
}