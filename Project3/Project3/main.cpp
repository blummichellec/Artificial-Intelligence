/* Main Program
 
 The purpose of this project is to try and solve the 8-queens problem
 using the steepest ascent version of hill climbing search.
 
 20 random instances are generated, but only the successful ones are displayed.
 
 The program also calculates the percent successfulness of the program based on
 the number of solutions found.
 
 Michelle Blum
 CMPT 420 - Artificial Intelligence
 */

#include <iostream>
#include <random>
#include <vector>
#include <cstdlib>

using namespace std;

//Allows problem to easily transform to n-queens
//Allows user to see success-rate with greater or fewer tests
#define BOARD_SIZE 8
#define NUM_OF_TESTS 20

//Declare functions to be used in program
void printBoard( int (&Board)[BOARD_SIZE] );
int getCollisions( int (&Board)[BOARD_SIZE] );
bool steepestHillClimbing( int (&Board)[BOARD_SIZE], int &SearchCost );

int main()
{
    
    //Chrono library used because clock serves as measure of cost
    using namespace std::chrono;

    int Board1[BOARD_SIZE];
    int Board2[BOARD_SIZE];
    bool Success = 0;
    float SuccessCount = 0;
    int SearchCost = 0;
    int HillSearchCost = 0;
    
    high_resolution_clock::time_point T_init;
    high_resolution_clock::time_point T_final;
    duration<double> HillClimbDuration;
    
    for ( int n = 0; n < NUM_OF_TESTS; n++ ) {
        // Randomly generate board
        for ( int i = 0; i < BOARD_SIZE; i++ )
        {
            Board1[i] = rand() % BOARD_SIZE; // place Queen in random row in each col
            Board2[i] = rand() % BOARD_SIZE;
        }
        
        //steepestHillClimbing called
        T_init = high_resolution_clock::now();
        Success = steepestHillClimbing( Board1, SearchCost );
        T_final = high_resolution_clock::now();
        HillSearchCost += SearchCost;
        HillClimbDuration = duration_cast<duration<double>>( T_final - T_init );
        
        //Keep track of number of successes in order to perform statistical analysis
        if ( Success ) {
            SuccessCount += 1;
        }
    }
    
    //Determine success rate by dividing successful runs by the number of runs
    cout << "Steepest Hill Climbing Algorithm:\n\t";
    cout << (SuccessCount / NUM_OF_TESTS * 100) << "% Success rate.\n";
    
    return 0;
}

//Formats the board for printing
void printBoard( int (&Board)[BOARD_SIZE] )
{
    for ( int i = BOARD_SIZE-1; i >= 0; i-- ) {
        for ( int j = 0; j < BOARD_SIZE; j++ ) {
            if ( Board[j] == i ) {
                cout << "1 "; //let 1 represent the location of a Queen
            }
            else {
                cout << "0 ";
            }
            if ( j == BOARD_SIZE-1 ) {
                cout << "\n";
            }
        }
    }
    cout << endl;
    
    cout << "Row location of the 1 per column: ";
    for ( int i = 0; i < BOARD_SIZE; i++ )
    {
        if ( i < (BOARD_SIZE - 1) )
            cout << (BOARD_SIZE-Board[i]) << ", ";
        else
            cout << (BOARD_SIZE-Board[i]) << "\n\n";
    }
}

//Returns the number of collisions on the N-Queen Board
int getCollisions( int (&Board)[BOARD_SIZE] )
{
    int Collisions = 0;
    int Offset;
    for ( int i = 0; i < BOARD_SIZE; i++ )
    {
        for ( int j = i+1; j < BOARD_SIZE; j++ )
        {
            // Check for Queens in same row
            if ( Board[i] == Board[j] )
                ++Collisions;
            
            // Check for Queens in same diagonal
            Offset = j - i;
            if ( (Board[i] == Board[j] + Offset) || ( Board[i] == Board[j] - Offset ) )
                ++Collisions;
        }
    }
    return Collisions;
}

struct verticalMove
{
    int Row;
    int Col;
    int Collisions;
};

/*
 Performs the steepest ascent Hill Climbing Algorithm
 and returns whether or not it succeeds.
 */
bool steepestHillClimbing( int (&Board)[BOARD_SIZE], int &SearchCost ) {
    int Iterations = 0;
    
    while ( true )
    {
        //Check board for collisions
        int Collisions = getCollisions( Board );
        
        //List of collisions for every new state of board
        int ChildCollision[BOARD_SIZE * BOARD_SIZE];
        //Copy of current state of board to calculate collisions for list above
        int Child[BOARD_SIZE];
        for ( int i = 0; i < BOARD_SIZE; i++ ) {
            Child[i] = Board[i];
        }
        
        //Generate all possible new moves and find the resulting collisions
        for ( int i = 0; i < BOARD_SIZE; i++ )
        {
            for ( int j = 0; j < BOARD_SIZE; j++ ) {
                if ( Board[i] != j ) { //Look only at the new moves
                    Child[i] = j; //Make a move
                    //This is where the collisions get stored
                    ChildCollision[i * BOARD_SIZE + j] = getCollisions( Child );
                    Child[i] = Board[i]; //Reset child to same state as board
                }
                else
                    ChildCollision[i * BOARD_SIZE + j] = 100000; //Just in case
            }
        }
        
        // Find the moves with the fewest collisions (highest-valued)
        int LeastCollisions = Collisions;
        for ( int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++ ) {
            if ( ChildCollision[i] < LeastCollisions )
                LeastCollisions = ChildCollision[i];
        }
        
        if ( LeastCollisions >= Collisions ) {
            //Current state
            return false;
        }
        
        //Store the next states with the fewest collisions (best moves)
        vector<verticalMove> BestChildren;
        verticalMove Temp;
        for ( int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++ ) {
            if ( ChildCollision[i] == LeastCollisions ) {
                //Create move data
                Temp.Row = i / BOARD_SIZE;
                Temp.Col = i % BOARD_SIZE;
                Temp.Collisions = ChildCollision[i];
                
                //Store move data
                BestChildren.push_back( Temp );
            }
        }
        
        //Choose one of the best children
        if ( !(BestChildren.empty()) ) {
            //Choose a random best child
            int RandInt= rand() % BestChildren.size();
            Temp = BestChildren[RandInt];
            
            //Apply child (Temp) move to board
            Board[Temp.Row] = Temp.Col;
            
            if ( !(Temp.Collisions) ) { //No Collisions
                printBoard( Board );
                return true;
            }
        }
        ++Iterations;
    }
    return false;
}
