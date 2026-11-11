#include <stdio.h>
#include <math.h>

int main(void){
    const double k = 8.9875*pow(10,9);
    double q1 = 0; 
    double q2 = 0; 
    char charQ1 = 'd';
    char charQ2 = 'd';
    double distance = 0; 
    printf("Enter the value of the two charges separated by a space: ");
    scanf("%lf%cC %lf%cC", &q1, &charQ1,&q2, &charQ2);
    printf("Enter distance between charges in metres: ");
    scanf("%lf", &distance); 
    if(charQ1=='u'){
        q1=fabs(q1*pow(10.0,-6));  
    }
    else{
        q1=fabs(q1*pow(10,-9));
    }
     if(charQ2=='u'){
        q2=fabs(q2*pow(10,-6));  
    }
    else{
        q2=fabs(q2*pow(10,-9));
    }
    
    double force = k*q1*q2/pow(distance,2);

    if(force<1*pow(10,-6)){
        force = force/pow(10,-9);
        printf("The force between charges is %.2lf (less than 1uN)",force);
    }
    else if(force<1*pow(10,-3)){
        force = force/pow(10,-6);
        printf("The force between charges is %.2lfuN (less than 1mN)", force);
    }
    else if(force<1){
        force=force/pow(10,-3);
        printf("The force between charges is %.2lfmN (less than 1N)",force);
    }
    else {
        printf("The force between charges is %.2lfN (1N or greater)",force);
    }
    
    return 0 ; 
}
