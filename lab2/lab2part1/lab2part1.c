#include <stdio.h>
#include <math.h>

int main (void){
    const double pi = 3.14159265; 
    double sideA = 0; 
    double sideB = 0; 
    double alpha = 0; 
    printf("Enter the length of side A: ");
    scanf("%lf",&sideA );
    printf("Enter the length of side B: ");
    scanf("%lf", &sideB);
    printf("Enter the measure of angle alpha in degrees: ");
    scanf("%lf", &alpha);
    alpha = alpha*pi/180; 
    
    double beta = asin(sideB*sin(alpha)/(sideA));
    double gamma = pi - beta-alpha; 
    double sideC=sin(gamma)*sideA/sin(alpha);
    alpha = alpha*180/pi;
    beta = beta*180/pi; 
    gamma = gamma*180/pi;
    printf("\nResults:\nSide A: %.2lf\nSide B: %.2lf\nSide C: %.2lf\nAngle Alpha: %.2lf degrees\nAngle Beta: %.2lf degrees\nAngle Gamma: %.2lf degrees", sideA, sideB, sideC, alpha, beta, gamma);
    return 0; 
}
