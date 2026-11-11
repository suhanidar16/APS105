#include <stdio.h>
#include <stdbool.h>

#define WIDTH 7
#define HEIGHT 6
#define CONNECT 4
#define P1 'X'
#define P2 'O'
#define EMPTY '-'
bool checkLeft(char board[][WIDTH], int col, int row, char p){
    int counter = 1; 
        for(int c=1; c<=3; c++){
            if(board[row][col-c]==p){
                counter++; 
            }
        }
    return (counter==4);
}
bool checkRight(char board[][WIDTH], int col, int row, char p){
int counter = 1; 
        for(int c=1; c<=3; c++){
            if(board[row][col+c]==p){
                counter++; 
            }
        }
    return (counter==4);
}
bool checkUp(char board[][WIDTH], int col, int row, char p){
int counter = 1; 
        for(int c=1; c<=3; c++){
            if(board[row+c][col]==p){
                counter++; 
            }
        }
    return (counter==4);
}
bool checkDown(char board[][WIDTH], int col, int row, char p){
int counter = 1; 
        for(int c=1; c<=3; c++){
            if(board[row-c][col]==p){
                counter++; 
            }
        }
    return (counter==4);
}

bool checkDiagonals1(char board[][WIDTH], int col, int row, char p){
int counter = 1; 
        for(int c=1; c<=3; c++){
            if(board[row+c][col+c]==p){
                counter++; 
            }
        }
    return (counter==4);
}
bool checkDiagonals2(char board[][WIDTH], int col, int row, char p){
int counter = 1; 
        for(int c=1; c<=3; c++){
            if(board[row-c][col-c]==p){
                counter++; 
            }
        }
    return (counter==4);
}
bool checkDiagonals3(char board[][WIDTH], int col, int row, char p){
int counter = 1; 
        for(int c=1; c<=3; c++){
            if(board[row+c][col-c]==p){
                counter++; 
            }
        }
    return (counter==4);
}
bool checkDiagonals4(char board[][WIDTH], int col, int row, char p){
int counter = 1; 
        for(int c=1; c<=3; c++){
            if(board[row-c][col+c]==p){
                counter++; 
            }
        }
    return (counter==4);
}

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
        if (count < HEIGHT){ // If there is at least one empty spot
             c = -1; // Exit the loop
             } 
       }
    }
    return col; 
}

void makeMove(char board[][WIDTH], char p, int col){
    int row =0; 
    int c = 0; 
    while (row<HEIGHT && c==0){ // goes through row until it finds an empty row
        if(board[row][col]=='-'){
            board[row][col]=p;
            c=1;  
        }
        row++; // going to next row 
    }

}

bool checkPosition(char board[][WIDTH], int col, int row){
   char p = board[row][col]; // stores character in that position 
   bool checkLeft1 = false;
   bool checkRight1 = false; 
   bool checkUp1 = false; 
   bool checkDown1 = false; 
   bool checkDiagonal1 = false; 
   bool checkDiagonal2 = false; 
   bool checkDiagonal3 = false; 
   bool checkDiagonal4 = false; 
   
   if(p =='-'){
    return false; 
   }
   if(col >= 3){ 
   checkLeft1 = checkLeft(board, col, row, p);
    }
    if(WIDTH - col > 3){ // Should be > 3 to allow 3 more spots to the right
    checkRight1 = checkRight(board, col, row, p);
    }
    if(HEIGHT - row > 3){ // Check Up
    checkUp1 = checkUp(board, col, row, p); 
    }
    if(row >= 3){ // Check Down
    checkDown1 = checkDown(board, col, row, p); 
    }
    // Diagonal 1: Up-Right
    if(WIDTH - col > 3 && HEIGHT - row > 3) {
    checkDiagonal1 = checkDiagonals1(board, col, row, p); }

    // Diagonal 2: Down-Left
    if(col >= 3 && row >= 3) {
    checkDiagonal2 = checkDiagonals2(board, col, row, p); }

    // Diagonal 3: (Up-Left)
    if(col >= 3 && HEIGHT - row > 3) {
    checkDiagonal3 = checkDiagonals3(board, col, row, p); }

    // Diagonal 4: (Down-Right)
    if(WIDTH - col > 3 && row >= 3) {
    checkDiagonal4 = checkDiagonals4(board, col, row, p);
    }
    if(checkLeft1 || checkRight1|| checkUp1 || checkDown1|| checkDiagonal1 || checkDiagonal2|| checkDiagonal3 || checkDiagonal4){
        return true; 
    } 

    return false; 
    

}

bool checkForWin(char board[][WIDTH]){
    for(int r =0;r< HEIGHT; r++){
        for(int c=0; c<WIDTH; c++){
            if(checkPosition(board, c, r)){
                printBoard(board);
                printf("Player %c wins!\n", board[r][c]);
                return true; 
            }
        }
    }
    return false; 
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
        if(checkForWin(board)){
           
            col=-1; 
        }
    }
    return 0; 
}

