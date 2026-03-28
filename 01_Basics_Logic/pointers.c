#include<stdio.h>
#define N 10
void max_min(int a[],int n , int *max ,int *min);
int main(void){
    int b[N],i,big,small;

    printf("Enter %d numbers:",N);
    for(i = 0; i < N ; i++)
        scanf("%d",&b[i]);
    max_min(b, N,&big,&small);

    printf("Largest: %d\n",big);
    printf("Smallest: %d\n",small);
    return 0;
}
void max_min(int a[],int n, int *max,int *min){
    int i;
    *max=*min =a[0];
    for(i = 1; i<n;i++){
        if (a[i]>*max)
            *max=a[i];
        else if(a[i]<*min)
            *min=a[i];
    }
}
void avg_sum(double a[], int n, double *avg, double *sum)
{
int i;
*sum = 0.0;
for (i = 0; i < n; i++)
*sum += a[i];
*avg = *sum / n;
}
void swap(int *p, int *q){
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;
}
void split_time(long total_sec, int *hr, int *min, int *sec){
    *hr=total_sec/3600;
    *min= (total_sec-*hr*3600)/60;
    *sec=(total_sec-(*hr*3600)-(*min*60));
}
void find_two_largest(int a[], int n, int *largest,int *second_largest){
    int i;
    if(a[0]>a[1]){
        *largest=a[0];
        *second_largest=a[1];
    }
    else{
        *largest=a[1];
        *second_largest=a[0];
    }
    for(int i=2;i<n;i++){
        if(a[i]>*largest){
            *second_largest=*largest;
            *largest=a[i];
        }
        else if(a[i]>*second_largest){
            *second_largest=a[i];
        }
    }
}
void split_date(int day_of_year, int year, int *month, int *day) {
    
    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[2] = 29;
    }

    int current_month = 1;

    while (day_of_year > days_in_month[current_month]) {
        day_of_year -= days_in_month[current_month];
        current_month++;
    }
    *month = current_month;
    *day = day_of_year;
}