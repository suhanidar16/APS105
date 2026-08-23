#include <stdio.h>

int main(void){
    double dailyRate = 0; 
    int rentPeriod = 0; 
    printf("Enter the daily rate:"); 
    scanf("%lf", &dailyRate);
    printf("Enter the rental period (in days):");
    scanf( "%d", &rentPeriod );

    int free = rentPeriod%4; 
    const double HST = 1.13; 
    double charge = (rentPeriod - (rentPeriod/4))*dailyRate*HST; 

    printf("\nYour total free day(s) in this rental is: %d", free);
    printf("\nYour total charge including taxes is: %.2lf", charge);

    return 0; 
}

