#include <stdio.h>
#include <stdbool.h>
//
// Author:
//

#include "reversi.h"

void printBoard(char board[][26], int n) {
  printf("  ");
    for (int col = 0; col < n; col++) {
        printf("%c", 'a' + col);
    }
    printf("\n");

    for (int row = 0; row < n; row++) {
        printf("%c ", 'a' + row);
        for (int col = 0; col < n; col++) {
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}

bool positionInBounds(int n, int row, int col) {
  if (row>=0 && row<n && col>=0 && col<n){ //check if the row and col is out of bounds 
    return true; 
  }
  return false; 
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {// check if placing the tile at that position is possible in a specific direction
  if(deltaRow==0 && deltaCol==0){
    return false ; //can't check if it has no direction. 
  }
  // need to make sure position is empty
  if(!positionInBounds(n, row, col)|| board[row][col]!='U'){
    return false; 
  }
  char opp = ' '; 
  if(colour =='W'){ // figuring out who is the opponent
    opp='B';
  }
  else{
    opp = 'W';
  }

  int r = row+ deltaRow; // moving in one step direciton
  int c = col+deltaCol; 
  if(!positionInBounds(n,r,c)|| board[r][c]!=opp){
    return false; // too make sure first tile is the opponent
  }

  r+= deltaRow; 
  c+= deltaCol; 
  while(positionInBounds(n,r,c)){
    // if empty space is found then it is not valid 
    if(board[r][c]=='U'){
      return false; 
    }

    if(board[r][c]==colour){ // if we reach our own colour it is a valid move
      return true;
    }

    r+=deltaRow; // if we don't then it means the row and col need to be increase
    c+=deltaCol; 
  }

  return false; // there is no space on the board 
   
}

bool moveIsLegal(char board[][26], int n, int row, int col, char colour){
  
  if(board[row][col]!='U'){ //position must be empty 
    return false; 
  }

  // checking all the 8 different directions 

  for(int r1 = -1; r1<=1; r1++){
    for(int c1=-1; c1<=1;c1++){
      if( !(r1==0 && c1==0)){
        if (checkLegalInDirection(board, n, row, col, colour, r1, c1)){
          return true; 
        }
      }
    }
  }
  return false; 
}

void flipTiles(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
  int currentRow, currentCol; 
  char opp; 
  if(!checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) {
        return;
  }
   if (colour == 'W') {
        opp = 'B';
    } else {
        opp= 'W';
    }

    currentRow = row+deltaRow; 
    currentCol = col+deltaCol; 

    while(positionInBounds(n,currentRow, currentCol)&& board[currentRow][currentCol]==opp){
      board[currentRow][currentCol]= colour; 
      currentRow+= deltaRow; 
      currentCol+=deltaCol; 
    }
}
int main(void) {
  char board[26][26];
  int row,col, n; 
  char colour, rowChar, colChar; 
  int moveRow, moveCol; 
  int r, c ;

  printf("Enter the board dimension:");
  scanf("%d", &n);
  for(row=0; row <n;row++){
    for(col=0; col<n; col++){
      board[row][col]='U';
    }
  }
  //initializing the center of the board to WBWB
    board[n / 2 - 1][n / 2 - 1] = 'W';
    board[n / 2 - 1][n / 2] = 'B';
    board[n / 2][n / 2 - 1] = 'B';
    board[n / 2][n / 2] = 'W';  

    printBoard(board,n);

    printf("Enter board configuration:\n");
    while(1){
      scanf(" %c%c%c", &colour, &rowChar, &colChar);
      if(colour == '!' && rowChar =='!' && colChar == '!'){
        break; 
      }

      row = rowChar - 'a';
      col = colChar - 'a';
      board[row][col]= colour; 

    }

    printBoard(board, n);
    printf("Available moves for W:\n");
    for(row =0; row < n ;row++){
      for(col=0; col<n; col++){
        if(moveIsLegal(board, n, row, col, 'W')){
          printf("%c%c\n", 'a'+row, 'a'+col);
        }
      }
    }
    printf("Available moves for B:\n");
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (moveIsLegal(board, n, row, col, 'B')) {
                printf("%c%c\n", 'a' + row, 'a' + col);
            }
        }
    }

    printf("Enter a move:\n");
    scanf(" %c%c%c", &colour, &rowChar, &colChar);

    moveRow = rowChar - 'a';
    moveCol = colChar - 'a';

    if (positionInBounds(n, moveRow, moveCol) &&
        moveIsLegal(board, n, moveRow, moveCol, colour)) {
        printf("Valid move.\n");
        board[moveRow][moveCol] = colour;

        for (r = -1; r <= 1; r++) {
            for (c = -1; c <= 1; c++) {
                if (!(r == 0 && c == 0)) {
                    flipTiles(board, n, moveRow, moveCol, colour, r, c);
                }
            }
        }
    } else {
        printf("Invalid move.\n");
    }

    printBoard(board, n);
  return 0;
}
