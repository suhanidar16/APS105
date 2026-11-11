#include <stdio.h>
#include <math.h>

int main (void){
    double d =0; 
    double height = 0; 
    // getting input from users, will run again if the input does not match condition 
    do{
        printf("Please enter the horizontal distance from the wall between 3 and 30 m:");
        scanf("%lf", &d);
    }while(d<3 || d>30); 
    do{
        printf("Please enter the target height between 3 and 6 m:");
        scanf("%lf", &height);
    }while(height<3 || height>6); 
    
    int alpha = 0; 
    double y=0; 
    double difference = 1; 
    double t =0; 
    int const v = 20; // assigning constant value to unchanging velocity 
    double const g = 9.81; // gravity as a constant
    double const pi = 3.14; // value of pi 
    while(alpha<=90 &&  difference>=0.3){
        // finding velocity in x and y direction 
        double vx = v*cosf(alpha*pi/180);
        double vy = v*sinf(alpha*pi/180);
        t = d/vx; // time taken for projection 
        y = 2+ (vy*t)- (0.5*g*pow(t,2));
        difference = fabs(y-height);
        alpha++;  
    }

    double a = alpha -1; 
    printf("The angle should be %.2lf", a);
return 0; 

}
