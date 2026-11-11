#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


double randDouble(void) {
    return 2.0 * ((double)rand() / RAND_MAX) - 1.0;
}

bool inSafeZone(double x, double y){
    double area = ((x*x)+(y*y));
    if(area<=1){
        return true; 
    }
    return false; 
}


int main (void){
    int iterations = 0; 
    printf("Number of Monte Carlo iterations: ");   
    scanf("%d", &iterations);
    double x = 0; 
    double y = 0; 
    int count = 0;
    srand(67);
 
    for(int i =0; i<iterations; i++){
        x = randDouble(); 
        y = randDouble(); 
        if(inSafeZone(x,y)){
            count++; 
        }    
    }
    double probability = (double) count/iterations; 
    printf("Probability of safe landing: %.4lf" , probability);
    return 0 ; 
}
