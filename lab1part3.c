#include <stdio.h>

int main (void){
    printf("Please provide a distance in metres:");
    double metre = 0; 
    scanf("%lf", &metre); 
    const double metresToInches = 100.0/2.54; 
    double inches = metre*metresToInches;
    int yards = (int)(inches/36);
    inches = inches - yards*36; 
    int feet = (int)(inches/12);
    inches = inches - feet*12;
    int inch = (int) inches; 
    double remainder = inches -  inch; 
    
    printf("%d yards, %d feet, %d inches, %.2lf inches remainder\n",
           yards, feet, inch, remainder);

    return 0;

}
