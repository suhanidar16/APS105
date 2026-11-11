#include <stdio.h>

#define WIDTH 7
#define HEIGHT 6
#define CONNECT 4
#define P1 'X'
#define P2 'O'
#define EMPTY '-'

void clearBoard (char board[][WIDTH]){ //clears board 
for (int row = 0; row<HEIGHT; row++){
    for(int col =0; col<WIDTH;col++){
        board[row][col]='-';
    }
}
}
void printBoard(char board[][WIDTH]){ // prints state of board
    printf("0 1 2 3 4 5 6\n"); 
    for(int row=HEIGHT-1; row>=0; row--){
        for(int col=0; col<WIDTH; col++){
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
}

int getPlayerColumnChoice(char board[][WIDTH], char p){
    int c = 80; // random number to keep while loop running when conditions are not met 
    int col = 0; 
    while(c>0){
        printf("Player %c enter column: ", p);
        scanf("%d", &col);
        if(col==-1){
            c=-1; 
        } 
        else if(col>6 || col<0){
            c=50; 
        }
       else {
        int count =0; // to check if column is full or not 
        for(int row = 0; row<HEIGHT; row++){
            if(board[row][col]!= '-'){
                count++; 
            }
        }
        if (count!=HEIGHT-1){
            c=-1; 
        }    
       }
    }
    return col; 
}

void makeMove(char board[][WIDTH], char p, int col){
    int row =0; 
    int c = 0; 
    while (row<8 && c==0){ // goes through row until it finds an empty row
        if(board[row][col]=='-'){
            board[row][col]=p;
            c=1;  
        }
        row++; // going to next row 
    }

}

int main (void){
    char board [HEIGHT][WIDTH];
    clearBoard(board);
    int col = 0; 
    int player = 1; 
    char p='-';
    while(col!=-1){
        printBoard(board);
        if(player%2==0){
            p='O';
            player++; 
        }
        else{
            p='X';
            player++; 
        }
        col = getPlayerColumnChoice(board, p); 
        makeMove(board, p,col);
        


    }
    return 0; 
}

