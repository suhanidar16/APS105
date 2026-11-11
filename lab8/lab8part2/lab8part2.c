#include <stdio.h>
#include <stdbool.h>
//
// Author:
//
#include "lab8part2.h"
#include "liblab8part2.h"

int getScore(char board[][26], int n, int row, int col, char colour);

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

bool checkLegalInDirection( char board[][26], int n, int row, int col,
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

bool moveIsLegal( char board[][26], int n, int row, int col, char colour){
  
  if(!positionInBounds(n, row, col) || board[row][col] != 'U'){
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
   if (colour == 'W') { // finds color of opponent 
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

int makeMove(char board[][26], int n, char turn, int *row, int *col){ // this will find best move for computer
    int bestScore = -1000; // very low nummber so comparison is easier 
    int bestRow = 0;
    int bestCol = 0;
    int score = 0;

    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){

            if(board[r][c] == 'U'){

                if(moveIsLegal(board, n, r, c, turn)){// check if tile can be placed here 
                    score = getScore(board, n, r, c, turn); // takes the base score and then does the smart score after 

                    if((r == 0 && c == 0) || (r == 0 && c == n-1) || (r == n-1 && c == 0) || (r == n-1 && c == n-1)){ // corners are good to place because they can't be flipped 
                        score = score + 100; // giving extra points for corners 
                    }
                    else if(r == 0 || r == n-1 || c == 0 || c == n-1){ // edges are good to flip because they are hard to flip as well 
                        score = score + 10;
                    }

                    // positions near corners are bad because opp can take those position 
                    if(board[0][0] == 'U'){ // if corner is empty this spot is dangerous 
                        if((r == 0 && c == 1) || (r == 1 && c == 0) || (r == 1 && c == 1)){ // top right
                            score = score - 15;
                        }
                    }

                    if(board[0][n-1] == 'U'){   // top right corner is bad 
                        if((r == 0 && c == n-2) || (r == 1 && c == n-1) || (r == 1 && c == n-2)){
                            score = score - 15;
                        }
                    }

                    if(board[n-1][0] == 'U'){ // bottom left is bad 
                        if((r == n-2 && c == 0) || (r == n-1 && c == 1) || (r == n-2 && c == 1)){
                            score = score - 15;
                        }
                    }

                    if(board[n-1][n-1] == 'U'){ // bottom right corener 
                        if((r == n-2 && c == n-1) || (r == n-1 && c == n-2) || (r == n-2 && c == n-2)){
                            score = score - 15;
                        }
                    }

                    // comparing each score to get the best score 
                    if(score > bestScore){
                        bestScore = score;
                        bestRow = r;
                        bestCol = c;
                    }
                }
            }
        }
    }

    *row = bestRow;
    *col = bestCol;

    return 0;
}

void makeMoveOnBoard(char board[][26], int n, int row, int col, char colour){ // this will put the tile and flip needed ones
    
    for(int r = -1; r <= 1; r++){
        for(int c = -1; c <= 1; c++){
            if(!(r == 0 && c == 0)){
                flipTiles(board, n, row, col, colour, r, c); 
            }
        }
    }

    board[row][col] = colour; // finally place the tile
}

bool playerHasValidMove(char board[][26], int n, char colour){// checks the board to see if there are any valied moves 
    for(int row = 0; row<n; row++){
        for(int col=0; col<n;col++){
            if(moveIsLegal(board, n , row, col, colour)){
                return true;  // this will return true if there is a legal move 
            }
        }
    }
    return false; 
}

int getScore(char board[][26], int n, int row, int col, char colour){ // this will count total number of tiles flipped for one move
    
    int score = 0; 
    char opp = ' '; 

    if(colour == 'W'){ // figuring out opponent
        opp = 'B';
    }
    else{
        opp = 'W';
    }

    for(int r = -1; r <= 1; r++){ // this will be checking all directions
        for(int c = -1; c <= 1; c++){

            if(!(r == 0 && c == 0)){ // skip the acctually position wehre the piece hasn't moved yet 

                if(checkLegalInDirection(board, n, row, col, colour, r, c)){

                    int rr = row + r; // start one step away
                    int cc = col + c; 

                    while(positionInBounds(n, rr, cc) && board[rr][cc] == opp){
                        score++; // counting tiles flipped
                        rr += r; // keep going in direction
                        cc += c;
                    }
                }
            }
        }
    }

    return score; 
}

int bestMoveRow(char board[][26], int n, char colour){ // to get the best row to move in for the computer 
    int bestRow = -1;  // initializing to get best row and columb
    int bestCol = -1; 
    int bestScore = -1; 

    for(int row =0; row<n; row++){
        for(int col = 0; col<n; col++){
            if(moveIsLegal(board, n, row, col, colour)){
                int score = getScore(board, n, row, col, colour); // gets score for the possibility of move

                if(score > bestScore){ // check if score is the hightest or not
                    // it is > so it will only go to the lowest row  
                    bestScore = score; 
                    bestRow = row; 
                    bestCol = col; 
                }
            }
        }
    }
    return bestRow; 
}

int bestMoveCol(char board[][26], int n, char colour){ // this will get  the best move that can have for the computer 
    int bestRow =-1; 
    int bestCol = -1; 
    int bestScore = -1; 

    for(int row = 0; row< n; row++){
        for(int  col =0; col< n ; col++){
            if(moveIsLegal(board, n, row, col, colour)){
                if(moveIsLegal(board, n, row, col, colour)){
                    int score = getScore(board, n, row, col, colour); // count the score 

                    if(score> bestScore){ // finds the best move by finding the best score 
                        bestScore = score; 
                        bestRow = row; 
                        bestCol = col; 
                    }
                }
            }
        }
    }
    return bestCol; 
}

int countBlackTile(char board[][26], int n){ // this will count the number of blacktiles in the game 
    int count = 0; 
    for(int row = 0; row < n; row++){ // goes through the entire board and checks for if tile is black 
        for(int col = 0; col < n; col++){
            if(board[row][col]=='B'){
                count++; 
            }
        }
    }
    return count ; 
}

int countWhiteTile(char board[][26], int n){ // this counts number of white tiles
    int count = 0 ; 
    for(int row = 0; row<n ; row++){
        for(int col = 0; col<n; col++){ // goes through entire board and count++ if tile is white 
            if(board[row][col]=='W'){
                count++; 
            }
        }
    }
    return count; 
}

void printWinner(char board [][26], int n){
    int blackCount = countBlackTile(board, n);
    int whiteCount = countWhiteTile(board, n);;
    if(blackCount>whiteCount){
        printf("B player wins.\n");
    }
    else if(whiteCount> blackCount){
        printf("W player wins.\n");
    }
    else{
        printf("Draw!\n");
    }
}
int main(void) {
  char board[26][26];
  int row, col, n;
  char compColour, humColour, currentColour;// initializing the computer colour, human colour, and the current colour during the game 
  char rowChar, colChar; 
  int moveRow, moveCol;
  int bestRow, bestCol; // stores the value for the best row and col present. 

  printf("Enter the board dimension: "); // gets dimensions of the board
  scanf("%d", &n);

  printf("Computer plays (B/W): "); // choose colour of the computer 
  scanf(" %c", &compColour);

  if (compColour == 'B') {
    humColour = 'W';
  }
  else {
    humColour = 'B';
  }

  for (row = 0; row < n; row++) { // initializing entire board to row and columns 
    for (col = 0; col < n; col++) {
      board[row][col] = 'U';
    }
  }

  //initializing the center of the board to WBWB 
  int middle = n/2; // getting the center row/col of the board 
  board[middle - 1][middle - 1] = 'W';
  board[middle - 1][middle] = 'B';
  board[middle][middle - 1] = 'B';
  board[middle][middle] = 'W';

  printBoard(board, n);

  currentColour = 'B'; // black always goes first

  while (playerHasValidMove(board, n, 'B') || playerHasValidMove(board, n, 'W')) { // game will run until one of b or w has a valid move 
    if (playerHasValidMove(board, n, currentColour)) { // checks to see if player has a move 
      if (currentColour == compColour) { // to check if it is the turn of the computer 
        // makeMove(board, n, currentColour, &bestRow, &bestCol); // gets best move for computer
        // char tempR = 'a'+bestRow; 
        // char tempC = 'a' + bestCol; 
        // printf("Computer places %c at %c%c.\n", currentColour,  tempR, tempC); 
        // makeMoveOnBoard(board, n, bestRow, bestCol, currentColour); // actually places the tile and flips
        // printBoard(board, n);
        findSmarterMove(board, n, currentColour, &bestRow, &bestCol);
printf("Testing AI move (row, col): %c%c\n", bestRow + 'a', bestCol + 'a');
makeMoveOnBoard(board, n, bestRow, bestCol, currentColour);
printBoard(board, n);
      }
      else { // if it is not the computer colour then it is the users turns. 
        printf("Enter move for colour %c (RowCol): ", currentColour);
        scanf(" %c%c", &rowChar, &colChar);
        moveRow = rowChar - 'a'; 
        moveCol = colChar - 'a';

        if (positionInBounds(n, moveRow, moveCol) &&
            moveIsLegal(board, n, moveRow, moveCol, currentColour)) {
          makeMoveOnBoard(board, n, moveRow, moveCol, currentColour);
          printBoard(board, n);
        }
        else {
          printf("Invalid move.\n");
          printWinner(board, n);
          return 0;
        }
      }
    }
    else {
      printf("%c player has no valid move.\n", currentColour);
    }

    if (currentColour == 'B') {
      currentColour = 'W';
    }
    else {
      currentColour = 'B';
    }
  }

  printWinner(board, n);
  return 0;
}