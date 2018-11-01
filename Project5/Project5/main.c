/*
 The purpose of this code is to use Recursive Backtracking
 in order to solve Sudoku.
 
 Project #5
 Michelle Blum
 Professor Tian
 CMPT 420 - Artificial Intelligence
 */

#include <stdio.h>

//Declare functions here
int solve(int, int);
int check_rows(int, int);
int check_columns(int, int);
int check_squares(int, int, int);
void printBoard(void);

//Input Sudoku board as a 9x9 array
//Place array outside of main to use in all functions
int sudoku[9][9] = {0, 0, 0, 9, 0, 2, 6, 0, 4,
    6, 0, 4, 3, 0, 0, 0, 7, 0,
    0, 7, 0, 1, 0, 4, 0, 0, 0,
    0, 0, 3, 0, 1, 9, 8, 0, 0,
    1, 5, 0, 0, 4, 0, 0, 9, 7,
    0, 0, 7, 8, 2, 0, 3, 0, 0,
    0, 0, 0, 2, 0, 6, 0, 5, 0,
    0, 3, 0, 0, 0, 7, 1, 0, 2,
    9, 0, 2, 5, 0, 1, 0, 0, 0};

int main() {
    
    int x = 0;
    int y = 0;
    
    //Print the input puzzle, solve the input puzzle, print the output puzzle
    printf("Input Puzzle: \n");
    printBoard();
    solve(x, y);
    printf("Output Puzzle: \n");
    printBoard();
    
    return 0;
}

//This function is used recursively to solve the Sudoko board
int solve(int x, int y) {
    
    int num = 1;
    int x_temp = 0;
    int y_temp = 0;
    
    //Check if array at index xy needs to be selected
    //This if-statement is for already chosen values
    if (sudoku[x][y] != 0) {
        
        //Reached the end of the matrix
        if (x == 8 && y == 8) {
            return 1;
        }
        
        //Check each row in the a column
        if (x < 8) {
            x++;
        }
        //Move onto next column
        else {
            if (y < 8) {
                x = 0;
                y++;
                
            }
        }
        
        //Recursively call here
        if (solve(x, y)) {
            return 1; //go forward
        }
        else {
            return 0; //go backward
        }
        
    }
    
    //When the value does need to be selected
    if (sudoku[x][y] == 0) {
        //Checks each value (0-9) to check if valid input for empy_temp space
        while (num <= 9) {
            //Check that each condition of Sudoku returns false
            if (!check_squares(x, y, num) && !check_rows(y, num) && !check_columns(x, num)) {
                //Assign the value that returned false for all conditions to that space
                sudoku[x][y] = num;
                
                //Reach end of matrix
                if (x == 8 && y == 8) {
                    return 1;
                }
                
                //Calculates total x-value
                //Where are we row-wise?
                if (x < 8) {
                    x_temp = x + 1;
                }
                //Calculates total y-value
                //Where are we column-wise
                else {
                    if (y < 8) {
                        x_temp = 0;
                        y_temp = y + 1;
                        
                    }
                }
                
                //x_temp and y_temp become new x and y values
                //Recursive call here
                if(solve(x_temp, y_temp)) {
                    return 1;
                }
            }
            num++;
            //ends while loop
        }
        //Should never reach here
        sudoku[x][y] = 0;
        return 0;
    }
    return 0;
}

//This function is used to print the Sudoko board
void printBoard() {
    
    //Outputs each value within matrix by using nested for loop
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

//This function is used to check for conflicting numbers column (looks at each row)
int check_rows(int y, int num) {
    
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][y] == num) {
            return 1;
        }
    }
    return 0;
}

//This function is used to check for conflicting numbers per row (looks at each column)
int check_columns(int x, int num) {
    
    for (int i = 0; i < 9; i++) {
        if (sudoku[x][i] == num) {
            return 1;
        }
    }
    return 0;
}

//This function is used to check for conflicting numbers per square
int check_squares(int x, int y, int num) {
    
    if (x < 3) {
        x = 0;
    }
    else if (x < 6) {
        x = 3;
    }
    else {
        x = 6;
    }
    
    if (y < 3) {
        y = 0;
    }
    else if (y < 6) {
        y = 3;
    }
    else {
        y = 6;
    }
    
    for (int i = x; i < x+3; i++) {
        for (int j = y; j < y+3; j++) {
            if (sudoku[i][j] == num) {
                return 1;
            }
        }
    }
    return 0;
}
