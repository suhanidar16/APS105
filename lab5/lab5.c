#include <stdio.h>
#define ARRAY_SIZE 17

void printArray(int array[]){ // prints array pattern 
    for(int row = 0; row<ARRAY_SIZE; row++){
            if(array[row]==1){
            printf("*");
            }
            else{
                printf(" ");
            }
    }
    printf("\n");

}

void initializeArray(int aliveIndex, int array[] ){ // initializes array and makes position entered by user alive
    for(int i =0; i < ARRAY_SIZE; i++){
        if(i==aliveIndex){
            array[i]= 1; 
        }
        else{
            array[i]=0; 
        }
    }
}

int getRuleOutcome(int rule, int left, int center, int right){
    int decimal = left * 4 + center * 2 + right; // converting LCR to decimal 
    int bin[8] = {0};
    for(int i = 0; i <= 7; i++){ // convert rule binary 
         bin[i] = rule % 2;
          rule /= 2;
    }
    return bin[decimal]; 
}

void calculateNextState(int currentArray[], int nextArray[], int rule){
    for(int i=0; i<ARRAY_SIZE; i++){
       
        if(i==0){ //boundary condition for first value in array 
            nextArray[i] = getRuleOutcome(rule, 0, currentArray[i], currentArray[i+1]); 
        }
        else if(i==16){ // boundary condition for last value 
            nextArray[i]= getRuleOutcome(rule, currentArray[i-1], currentArray[i], currentArray[0]);
        }
        else{// rule outcome for every other position 
            nextArray[i]= getRuleOutcome(rule, currentArray[i-1], currentArray[i], currentArray[i+1]);

        }
    }
}

void simulateGenerations(int iterations, int array[], int rule){
    int nextArray [17] ={0};
    for(int i = 0; i<iterations; i++){
       printArray(array); // prints pattern for current array 
       calculateNextState(array, nextArray, rule); // finds outcome for the next array 
       for(int j =0; j<ARRAY_SIZE;j++){
        array[j]= nextArray[j]; // assigns value of next array to current array 
       }
    }
}
int main(void){
    int aliveIndex, rule, iterations; 
    printf("Enter input: ");
    scanf("%d %d %d", &aliveIndex, &rule, &iterations);
    int array[17]= {0};
    initializeArray(aliveIndex, array);
    simulateGenerations(iterations, array, rule);

    return 0; 
}
