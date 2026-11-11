#include <stdio.h>
#include <math.h>

int main(void){
    // initializing variables 
    int threshold = 0; 
    int boilingPoint = 0; 
    // gathering data from user
    printf("Enter the threshold in Celsius: ");
    scanf("%d",&threshold);

    printf("Enter the observed boiling point in Celsius: ");
    scanf("%d", &boilingPoint);

    // assigning variable the value of boiling points for each substance
    int water = 100; 
    int mercury = 357;
    int copper = 1187; 
    int silver = 2193; 
    int gold = 2660; 
// going from least to greatest boiling point to check if they match
// the boiling point with the threshold
    if(boilingPoint<water+threshold && boilingPoint> water-threshold){
        printf("The substance you tested is: Water");
    }
    else if(boilingPoint<mercury+threshold && boilingPoint> mercury-threshold){
        printf("The substance you tested is: Mercury");
    }
    else if(boilingPoint<copper+threshold && boilingPoint>copper-threshold){
        printf("The substance you tested is: Copper");
    }
    else if(boilingPoint<silver+threshold && boilingPoint> silver-threshold){
        printf("The substance you tested is: Silver");
    }
    else if(boilingPoint<gold+threshold && boilingPoint> gold-threshold){
        printf("The substance you tested is: Gold");
    }
    // if value doesnt match any of the substances it is unknown
    else{
        printf("Substance unknown.");
    }

}
