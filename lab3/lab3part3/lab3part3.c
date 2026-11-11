#include <stdio.h>
#include <math.h>

int main(void){
    // initilizing and getting dollar amount from user 
    int amount = 0; 
    printf("Please enter an amount in dollars ($): ");
    scanf("%d", &amount);
    //checking if it is a multiple of 5
    while(amount%5!=0){
        printf("The amount should be a multiple of $5: ");
        scanf("%d", &amount);
    }
    // initializing the type of variables 
    int hundreds = 0; 
    int fifties = 0;  
    int twenties = 0; 
    int  tens = 0; 
    int fives = 0; 
    // dividing by hundred to get number of hundred in this 
    hundreds = amount/100;
    int temp = 0 ;
    temp = amount%100;   
    // getting all the different number of 50, 20, 10, and 5s. 
    if(temp!=0){ 
       fifties = temp/50; 
       temp = temp%50; 
       if(temp!=0){ 
        twenties = temp/20;
        temp = temp%20; 
        if(temp!=0) {
            tens = temp/10; 
            temp = temp%10; 
            if(temp!=0){
            fives = temp/5; 
        } 
        }
       
       } 
    }
    // printing only if it has a value. 
    if(hundreds!=0){
        printf("$100: %d\n", hundreds);
    }
    if(fifties!=0){
        printf("$50: %d\n", fifties);
    }
    if(twenties!=0){
        printf("$20: %d\n" , twenties);
    }
    if(tens!=0){
        printf("$10: %d\n" , tens);
    }
    if(fives!=0){
        printf ("$5: %d\n", fives);
    }
    return 0; 
}