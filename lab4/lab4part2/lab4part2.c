#include <stdio.h>

int countingSevens(int input){
    int result = 0; 
    if (input < 0) {
        input = -input;
    }
    while(input!=0){
        int temp = input %10 ;
        if(temp==7){
            result++;
            if (input==7){
                result++; 
            }
            input/=10;
        }
        else{
            input/=10; 
        }
    }
    return result; 

}
int main (void){
    int input = 1; 
    int numberOfSevens=0; 
    int count = 0; // counting number of integers that are special numbers 
    do{
            printf("Input an integer (0 to stop):");
            scanf("%d", &input);
            numberOfSevens = countingSevens(input);
            if(numberOfSevens>=3){
                count++; 
            }
            
    }while(input!=0);

    printf("You entered %d pretty number(s)!", count);

    return 0; 
}