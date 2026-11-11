#include <stdio.h>
#include <math.h>

int main (void){
    int combo =0; 
    printf("Enter an encrypted 4-digit combination: ");
    scanf("%d", &combo);
    int a= (combo - combo%1000)/1000; 
    int b = (combo - a*1000)/100;
    int c = (combo - a*1000-b*100)/10; 
    int d=combo%(a*1000+b*100+c*10);
    int temp = a; 
     a = d; 
     d = temp; 
     b = 9-b; 
     c = 9-c; 
    int realCombo = a*1000+b*100+c*10+d; 
    printf("The real combination is: %d", realCombo);
    return 0; 
}
