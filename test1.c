#include<stdio.h>
int isprime (int a);
int main()
{
    int n,i,j,k,flag=1;
    scanf("%d",&n);
    for (i=2;i<n&&flag;i++){
        for (j=i;j<n&&flag;j++){
            for (k=j;k<n&&flag;k++){
                if(isprime(k)*isprime(j)*isprime(i)!=0&&i+k+j==n)
                {
                    printf("%d=%d+%d+%d",n,i,j,k);
                    flag=0;
                }
            }
        }
    }
//	if (isprime(n)) printf("%d",n);
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