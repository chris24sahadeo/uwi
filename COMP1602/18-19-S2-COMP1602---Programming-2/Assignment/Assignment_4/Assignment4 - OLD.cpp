#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#include <iostream>
   using namespace std;

#define MAXROWS    18 // maximum possible row size
#define MAXCOLS    24 // maximum possible column size

struct Cell {
   bool hasMine;
   bool isFlagged;
   bool isHidden;
   int number;
};

struct MouseEvent {
   bool leftButtonPressed;
   bool rightButtonPressed;
   int row;
   int col;
};



// These are graphics functions which create the graphics window.
// You do NOT have to write these functions. They are located in the
// file, Graphics.cpp.

void createWindow (int numRows, int numCols);
void displayWindow (Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int gameStatus);
void closeWindow (void);
MouseEvent waitForMouseClick(void);



// These are functions that create and manage the game.
// You MUST write the code for these functions.

 

// This function creates and initializes a Cell struct to default values.

Cell createCell() {
     Cell cell;
     cell.hasMine = false;
     cell.isFlagged = false;
     cell.isHidden = true;
     cell.number = 0;
     return cell;
}



// This function initializes all the cells in the 2D minesweeper board.

void initBoard(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols) {
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			cells[i][j] = createCell();
		}
	}
}



// This function randomly places a certain amount of mines (specified as a
// parameter, numMines) in the 2D board.

void placeMines(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int numMines) {
	srand(time(NULL));
	int i, j;
	for(int k = 1; k <= numMines; k++){
		i = rand()%numRows;
		j = rand()%numCols;
		while(cells[i][j].hasMine){
			i = rand()%numRows;
			j = rand()%numCols;
		}
		cells[i][j].hasMine = true;
	}
}



// Given a particular (row, col) location, this function determines if the
// location is valid for the given board. A location is valid if it is within
// the range of the rows and columns of the board.
     
bool isValidLocation (int numRows, int numCols, int row, int col) {
   return row >= 0 && row < numRows && col >= 0 && col < numCols;   
}



// This function finds the number that should be assigned to a given cell on
// the board (which is not a mine). This number is calculated based on the 
// number of adjacent mines.                     
                        
int getNumber (Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int row, int col) {
	int numMines = 0;	
	if(!cells[row][col].hasMine){
		for(int k = -1; k <= 1; k++){
			for(int l = -1; l <= 1; l++){
				if(isValidLocation(numRows, numCols, row+k, col+l) && cells[row+k][col+l].hasMine){
					numMines++;
				}					
			}
		}
	}	
	
    return numMines;   
}



// This function sets the number of all the cells on the board (which is not
// a mine). It calls the getNumber function to get the number for a particular
// cell.
    
void setNumbers(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols) { 
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			cells[i][j].number = getNumber(cells, numRows, numCols, i, j);
		}
	}
}



// This function determines if the current situation on the board is a "win"
// situation. A "win" situation occurs when all the hidden cells are mines.

bool hasWon (Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols) { 
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			if(cells[i][j].isHidden && !cells[i][j].hasMine)
				return false;
		}
	}
   
	return true;
}     



// This function is called when a player right-clicks on the mouse to indicate
// that a cell should be "marked" as having a mine. If a cell is already marked,
// it should be un-marked.

void mark(Cell cells[MAXROWS][MAXCOLS], int row, int col) {
    cells[row][col].isFlagged = !cells[row][col].isFlagged;
}



// This function is called to implement any behaviour you like when it is 
// determined that the player has lost the game.

void lose() {
	cout << "\n\nYOU LOST!!!\n\n";
}



// This function is called to implement any behaviour you like when it is 
// determined that the player has won the game.

void win() {
	cout << "\n\nYOU WON!!!\n\n";
}



// This function is called whenever the player left-clicks on a cell containing
// a blank (i.e., the number 0 has been assigned to cell). THE CODE GIVEN 
// SHOULD NOT BE MODIFIED.

void clearBlanks(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int row, int col) {
     
     if (row - 1 >= 0) {
         if ((!cells[row-1][col].hasMine) && (cells[row-1][col].isHidden)) {             
            cells[row-1][col].isHidden = false;
            if (cells[row-1][col].number == 0)
                clearBlanks(cells, numRows, numCols, row-1, col);
         }
     }
 
     if (row + 1 < numRows) {
         if ((!cells[row+1][col].hasMine) && (cells[row+1][col].isHidden)) {             
            cells[row+1][col].isHidden = false;
            if (cells[row+1][col].number == 0)
                clearBlanks(cells, numRows, numCols, row+1, col);
         }
     } 
     
     if (col - 1 >= 0) {
         if ((!cells[row-1][col].hasMine) && (cells[row-1][col].isHidden)) {             
            cells[row-1][col].isHidden = false;
            if (cells[row-1][col].number == 0)
                clearBlanks(cells, numRows, numCols, row-1, col);
         }
     }
 
     if (row + 1 < numRows) {
         if ((!cells[row+1][col].hasMine) && (cells[row+1][col].isHidden)) {             
            cells[row+1][col].isHidden = false;
            if (cells[row+1][col].number == 0)
                clearBlanks(cells, numRows, numCols, row+1, col);
         }
     }      
     
     if (col - 1 >= 0) {
         if ((!cells[row][col-1].hasMine) && (cells[row][col-1].isHidden)) {             
            cells[row][col-1].isHidden = false;
            if (cells[row][col-1].number == 0)
                clearBlanks(cells, numRows, numCols, row, col-1);
         }
     }     

     if (col + 1 < numCols) {
         if ((!cells[row][col+1].hasMine) && (cells[row][col+1].isHidden)) {             
            cells[row][col+1].isHidden = false;
            if (cells[row][col+1].number == 0)
                clearBlanks(cells, numRows, numCols, row, col+1);
         }
     }     
}



// This function is called when the player left-clicks on the mouse on a
// particular cell. It is possible that the cell is blank, has a number
// assigned to it, or contains a mine. If there are no more mines to be 
// discovered, it results in a "win" situation. It returns 0 to indicate
// that the game is still in progress, -1 to indicate that the game has
// been lost, or 1 to indicate that the game has been won.

int select(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int row, int col) {
	if(cells[row][col].isHidden){
		if(cells[row][col].hasMine)
			return -1;
	
		if(cells[row][col].number == 0)
			clearBlanks(cells, numRows, numCols, row, col);
		else
			cells[row][col].isHidden = false;
	}
	
	if(hasWon(cells, numRows, numCols))
		return 1;
		
	return 0;
}


 
// This function contains the code to play an entire game. It returns -1 to 
// indicate that the game has been lost, or 1 to indicate that the game has 
// been won. The value of gameStatus that is passed as a parameter to the
// displayWindow function can only be -1 (lose), 0 (in progress), or 1 (win).

int playGame (Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int numMines) {
    
    int gameStatus;
    MouseEvent event;
    
    initBoard(cells, numRows, numCols);
    placeMines(cells, numRows, numCols, numMines);
    setNumbers(cells, numRows, numCols);

    gameStatus = 0;    
    displayWindow(cells, numRows, numCols, gameStatus);
    
    while (gameStatus == 0) {

       event = waitForMouseClick();

       // check if player clicked on left mouse button or right mouse button
       // and take appropriate action.
       if(event.leftButtonPressed)
       		gameStatus = select(cells, numRows, numCols, event.row, event.col);
       	else if(event.rightButtonPressed)
       		mark(cells, event.row, event.col);
       
       displayWindow(cells, numRows, numCols, gameStatus);      
    }
    
    return gameStatus;
}

int main() { 

    Cell cells[MAXROWS][MAXCOLS];
    int numRows, numCols, numMines;
    
    int gameStatus;
    int wins = 0, losses = 0;
    
     // display welcome message to player 
    cout << "WELCOME TO MINESWEEPER!!!\n\n\nGAME SETUP...\n";
    
    
    // ask player to specify size of board (numRows, numCols) and number of mines
    cout << "Enter number of rows: ";
    cin >> numRows;
    while(numRows <= 0 || numRows > MAXROWS){
    	cout << "Invalid entry!\n\n";
    	cout << "Enter number of rows: ";
    	cin >> numRows;
	}
    
    cout << "Enter number of columns: ";
    cin >> numCols;
    while(numCols <= 0 || numCols > MAXCOLS){
    	cout << "Invalid entry!\n\n";
    	cout << "Enter number of columns: ";
    	cin >> numCols;
	}
	
    cout << "Enter number of mines: ";
    cin >> numMines;
    while(numMines <= 0 && numMines > ((numRows-1)*(numCols-1))){
    	cout << "Invalid entry!\n\n";
    	cout << "Enter number of columns: ";
    	cin >> numCols;
	}
	
	cout << "\n\n\n";
      
    createWindow(numRows, numCols);
                                // create graphics window of given dimension  
                                
    // repeatedly play a game of minesweeper until the player asks to stop
    char choice = 'y';
    while(choice == 'y' || choice == 'Y'){
    	gameStatus = playGame(cells, numRows, numCols, numMines);
    	
    	if(gameStatus == 1){
    		wins++;
    		win();
		}else{
			losses++;
			lose();
		}    		
    		
    	cout << "Play Again? (y/n): ";
    	cin >> choice;
    	while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N'){
    		cout << "Invalid choice!\n\n";
    		cout << "Play Again? (y/n): ";
    		cin >> choice;
		} 
	}
	
	
    
    // at end of games, indicate how many games were won and lost
    cout << "\n\n\nSTATISTICS...\n\n";
    cout << "Games Played: " << wins + losses << "\nGames Won: " << wins << "\nGames Lost: " << losses << endl << endl << endl;
    
    
    system("pause");

    closeWindow();            // close graphics window
      
    return 0; 
      
}
