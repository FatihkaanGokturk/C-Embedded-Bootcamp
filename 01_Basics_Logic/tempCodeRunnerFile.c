#include<stdio.h>
long countnumber(long long n){
    int count = 0;
        while(n !=0){
            n=n/10;
            count++;
        }
        return count;
    }
int find2dig(long long number){
    long long divide=1;
    int count=countnumber(number);
    for(int j=0;j<count-2;j++){
    divide*=10;
    }
    int twodigits=number/divide;
    return twodigits;
}
long long luhndouble(long long n){
    n=n*2;
    if(n>9){
        n=n%10+n/10;
        return n;
    
    }
    else{
        return n;
    }
}
int isValid(long long number){
    int count=countnumber(number);
    int sum=0;
    int temp;
    for (int i = 0 ; i < count ; i++ ){
        temp = number%10;
        number=number/10;
        if(i%2==1){
            sum+=luhndouble(temp);
        }
        else{
            sum+=temp;
        }
    }
    if(sum%10==0){
        return 1;
    }
    else{
        return 0;
    }
}
int main(void){
    int count;
    long long number;
        do{
        printf("Number: ");
        scanf("%lld",&number);
        count=countnumber(number);
    }
    while( count != 16 && count != 13 && count !=15 );
    long long numbercopy=number;
    int validity=isValid(number);
    if(validity==0){
        printf("INVALID");
        return 0;
    }
    else{
        int twodigits=find2dig(numbercopy);
        if(count==15 && (twodigits==34 || twodigits== 37)){
            printf("AMEX");
        }
        else if( count==16 &&(twodigits>=51 && twodigits<=55)){
            printf("MASTERCARD");
        }
        else if((count ==13 || count==16)&&twodigits/10==4){
            printf("VISA");
        }
        else{printf("INVALID");}
    }
    return 0;
}